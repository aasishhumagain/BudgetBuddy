#include "viewtransactions.h"
#include "ui_viewtransactions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QPrinter>
#include <QTextDocument>
#include <QInputDialog>
#include <QMenu>
#include "databasemanager.h"

viewtransactions::viewtransactions(QWidget *parent, int userId) :
    QDialog(parent),
    ui(new Ui::viewtransactions),
    currentUserId(userId)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);

    this->currentUserName = DatabaseManager::instance().getUserNameById(currentUserId);

    ui->comboBoxTypeFilter->addItems({"All", "Income", "Expense"});
    ui->comboBoxCategoryFilter->addItem("All");
    ui->comboBoxCategoryFilter->addItems({"Food", "Fuel", "Rent", "Shopping", "Salary", "Misc", "Monthly Goal"});

    QDate today = QDate::currentDate();
    QDate firstOfMonth(today.year(), today.month(), 1);
    ui->dateEditFrom->setDate(firstOfMonth);
    ui->dateEditTo->setDate(today);

    ui->tableWidgetTransactions->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->buttonBack, &QPushButton::clicked, this, &viewtransactions::onBackButtonClicked);
    connect(ui->buttonApplyFilter, &QPushButton::clicked, this, &viewtransactions::loadTransactionData);
    connect(ui->tableWidgetTransactions, &QTableWidget::customContextMenuRequested, this, &viewtransactions::showContextMenu);
    connect(ui->buttonClearFilter, &QPushButton::clicked, this, &viewtransactions::clearFilters);


    loadTransactionData();
}

viewtransactions::~viewtransactions()
{
    delete ui;
}

void viewtransactions::onBackButtonClicked()
{
    this->close();
}

void viewtransactions::loadTransactionData()
{
    ui->tableWidgetTransactions->setRowCount(0);
    ui->tableWidgetTransactions->setColumnCount(6);

    QStringList headers = {"ID", "Date", "Category", "Type", "Amount", "Remarks"};
    ui->tableWidgetTransactions->setHorizontalHeaderLabels(headers);
    ui->tableWidgetTransactions->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Stretch);
    ui->tableWidgetTransactions->setColumnHidden(0, true);

    QString selectedType = ui->comboBoxTypeFilter->currentText();
    QString selectedCategory = ui->comboBoxCategoryFilter->currentText();

    QDate fromDate = ui->dateEditFrom->date();
    QDate toDate = ui->dateEditTo->date();

    QDate startOfFromMonth(fromDate.year(), fromDate.month(), 1);
    QDate endOfToMonth(toDate.year(), toDate.month(), QDate(toDate.year(), toDate.month(), 1).daysInMonth());

    int row = 0;

    if (selectedCategory != "Monthly Goal") {
        QString sql = R"(
            SELECT id, date, category, type, amount, remarks
            FROM transactions
            WHERE user_id = :uid
              AND date >= :from_date AND date <= :to_date
        )";

        if (selectedType != "All") sql += " AND type = :type";
        if (selectedCategory != "All") sql += " AND category = :category";

        sql += " ORDER BY date DESC";

        QSqlQuery query;
        query.prepare(sql);
        query.bindValue(":uid", currentUserId);
        query.bindValue(":from_date", startOfFromMonth.toString("yyyy-MM-dd"));
        query.bindValue(":to_date", endOfToMonth.toString("yyyy-MM-dd"));

        if (selectedType != "All") {
            query.bindValue(":type", selectedType);
        }
        if (selectedCategory != "All") {
            query.bindValue(":category", selectedCategory);
        }

        if (query.exec()) {
            while (query.next()) {
                ui->tableWidgetTransactions->insertRow(row);
                for (int col = 0; col < 6; ++col) {
                    ui->tableWidgetTransactions->setItem(row, col, new QTableWidgetItem(query.value(col).toString()));
                }
                row++;
            }
        } else {
            qDebug() << "Transaction query failed:" << query.lastError().text();
        }
    }

    if (selectedCategory == "All" || selectedCategory == "Monthly Goal") {
        QSqlQuery goalQuery;
        goalQuery.prepare(R"(
            SELECT year, month, amount
            FROM monthly_goals
            WHERE user_id = :uid
        )");
        goalQuery.bindValue(":uid", currentUserId);

        if (!goalQuery.exec()) {
            qDebug() << "Monthly goal query failed:" << goalQuery.lastError().text();
            return;
        }

        while (goalQuery.next()) {
            int year = goalQuery.value(0).toInt();
            int month = goalQuery.value(1).toInt();
            double amount = goalQuery.value(2).toDouble();

            QDate goalDate(year, month, 1);
            if (goalDate < startOfFromMonth || goalDate > endOfToMonth)
                continue;

            QString monthStr = QDate(2000, month, 1).toString("MMMM");
            QString remarks = QString("Monthly Goal for %1 %2").arg(monthStr).arg(year);

            ui->tableWidgetTransactions->insertRow(row);
            ui->tableWidgetTransactions->setItem(row, 0, new QTableWidgetItem("-1"));
            ui->tableWidgetTransactions->setItem(row, 1, new QTableWidgetItem(goalDate.toString("yyyy-MM-dd")));
            ui->tableWidgetTransactions->setItem(row, 2, new QTableWidgetItem("Monthly Goal"));
            ui->tableWidgetTransactions->setItem(row, 3, new QTableWidgetItem("MonthlyGoal"));
            ui->tableWidgetTransactions->setItem(row, 4, new QTableWidgetItem(QString::number(amount)));
            ui->tableWidgetTransactions->setItem(row, 5, new QTableWidgetItem(remarks));
            row++;
        }
    }
}

void viewtransactions::on_buttonExport_clicked()
{
    QStringList formats = {"CSV", "PDF"};
    bool ok;
    QString selectedFormat = QInputDialog::getItem(this, "Export Format",
                                                   "Choose export format:",
                                                   formats, 0, false, &ok);
    if (!ok || selectedFormat.isEmpty()) return;

    bool exportAsCSV = (selectedFormat == "CSV");
    QString fileFilter = exportAsCSV ? "CSV Files (*.csv)" : "PDF Files (*.pdf)";
    QString defaultName = exportAsCSV ? "transactions.csv" : "transactions.pdf";

    QString fileName = QFileDialog::getSaveFileName(this, "Export Transactions",
                                                    QDir::homePath() + "/" + defaultName,
                                                    fileFilter);
    if (fileName.isEmpty()) return;

    if (exportAsCSV) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Error", "Could not open file for writing.");
            return;
        }
        QTextStream out(&file);
        out << "Date,Category,Type,Amount,Remarks\n";
        int rows = ui->tableWidgetTransactions->rowCount();
        for (int i = 0; i < rows; ++i) {
            QStringList rowData;
            for (int j = 1; j < 6; ++j) {
                QString cell = ui->tableWidgetTransactions->item(i, j)->text();
                cell.replace(",", " ");
                rowData << cell;
            }
            out << rowData.join(",") << "\n";
        }
        file.close();
        QMessageBox::information(this, "Success", "Transactions exported as CSV!");
    } else {
        QString html = "<h2>Welcome " + currentUserName + "! Your Transactions</h2>"
                                                          "<table border='1' cellspacing='0' cellpadding='4'>"
                                                          "<tr><th>Date</th><th>Category</th><th>Type</th><th>Amount</th><th>Remarks</th></tr>";
        int rows = ui->tableWidgetTransactions->rowCount();
        for (int i = 0; i < rows; ++i) {
            html += "<tr>";
            for (int j = 1; j < 6; ++j) {
                QString cell = ui->tableWidgetTransactions->item(i, j)->text();
                html += "<td>" + cell + "</td>";
            }
            html += "</tr>";
        }
        html += "</table>";

        QTextDocument doc;
        doc.setHtml(html);
        QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        doc.print(&printer);

        QMessageBox::information(this, "Success", "Transactions exported as PDF!");
    }
}

void viewtransactions::showContextMenu(const QPoint &pos)
{
    QModelIndex index = ui->tableWidgetTransactions->indexAt(pos);
    if (!index.isValid()) return;

    QMenu contextMenu(this);
    contextMenu.addAction("Edit", this, &viewtransactions::editSelectedTransaction);
    contextMenu.addAction("Delete", this, &viewtransactions::deleteSelectedTransaction);
    contextMenu.exec(ui->tableWidgetTransactions->viewport()->mapToGlobal(pos));
}

void viewtransactions::editSelectedTransaction()
{
    int row = ui->tableWidgetTransactions->currentRow();
    if (row < 0) return;

    QString id = ui->tableWidgetTransactions->item(row, 0)->text();
    if (id == "-1") {
        QMessageBox::warning(this, "Error", "Cannot edit Monthly Goal rows.");
        return;
    }

    QString currentAmount = ui->tableWidgetTransactions->item(row, 4)->text();
    bool ok;
    double newAmount = QInputDialog::getDouble(this, "Edit Amount",
                                               "Enter new amount:",
                                               currentAmount.toDouble(), 0, 1e9, 2, &ok);
    if (!ok) return;

    QSqlQuery query;
    query.prepare("UPDATE transactions SET amount = :amount WHERE id = :id");
    query.bindValue(":amount", newAmount);
    query.bindValue(":id", id);

    if (query.exec()) {
        QMessageBox::information(this, "Updated", "Transaction updated.");
        loadTransactionData();
    } else {
        QMessageBox::warning(this, "Error", "Update failed.");
    }
}

void viewtransactions::deleteSelectedTransaction()
{
    int row = ui->tableWidgetTransactions->currentRow();
    if (row < 0) return;

    QString id = ui->tableWidgetTransactions->item(row, 0)->text();
    if (id == "-1") {
        QMessageBox::warning(this, "Error", "Cannot delete Monthly Goal rows.");
        return;
    }

    if (QMessageBox::question(this, "Confirm", "Delete this transaction?") == QMessageBox::Yes) {
        QSqlQuery query;
        query.prepare("DELETE FROM transactions WHERE id = :id");
        query.bindValue(":id", id);
        if (query.exec()) {
            QMessageBox::information(this, "Deleted", "Transaction deleted.");
            loadTransactionData();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete.");
        }
    }
}

void viewtransactions::clearFilters()
{
    ui->comboBoxTypeFilter->setCurrentIndex(0);
    ui->comboBoxCategoryFilter->setCurrentIndex(0);

    QDate today = QDate::currentDate();
    QDate firstOfMonth(today.year(), today.month(), 1);
    ui->dateEditFrom->setDate(firstOfMonth);
    ui->dateEditTo->setDate(today);

    loadTransactionData();
}
