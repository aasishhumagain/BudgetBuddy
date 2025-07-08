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

viewtransactions::viewtransactions(QWidget *parent, int userId) :
    QDialog(parent),
    ui(new Ui::viewtransactions),
    currentUserId(userId)
{
    ui->setupUi(this);

    // Setup filters
    ui->comboBoxTypeFilter->addItems({"All", "Income", "Expense"});
    ui->comboBoxCategoryFilter->addItem("All");
    ui->comboBoxCategoryFilter->addItems({"Food", "Fuel", "Rent", "Shopping", "Salary", "Misc"});

    QDate today = QDate::currentDate();
    QDate firstOfMonth(today.year(), today.month(), 1);
    ui->dateEditFrom->setDate(firstOfMonth);
    ui->dateEditTo->setDate(today);

    connect(ui->buttonBack, &QPushButton::clicked, this, &viewtransactions::onBackButtonClicked);
    connect(ui->buttonApplyFilter, &QPushButton::clicked, this, &viewtransactions::loadTransactionData);


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
    ui->tableWidgetTransactions->setColumnCount(5);

    QStringList headers = {"Date", "Category", "Type", "Amount", "Remarks"};
    ui->tableWidgetTransactions->setHorizontalHeaderLabels(headers);
    ui->tableWidgetTransactions->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

    // Get filter values
    QString selectedType = ui->comboBoxTypeFilter->currentText();
    QString selectedCategory = ui->comboBoxCategoryFilter->currentText();
    QDate fromDate = ui->dateEditFrom->date();
    QDate toDate = ui->dateEditTo->date();

    QString sql = R"(
        SELECT date, category, type, amount, remarks
        FROM transactions
        WHERE user_id = :uid1
          AND date >= :from_date AND date <= :to_date
    )";

    if (selectedType != "All") {
        sql += " AND type = :type";
    }

    if (selectedCategory != "All") {
        sql += " AND category = :category";
    }

    sql += R"(
        UNION ALL

        SELECT
            printf('%04d-%02d-01', year, month) AS date,
            'Monthly Goal' AS category,
            'MonthlyGoal' AS type,
            amount,
            'Monthly Goal for ' ||
            CASE CAST(month AS INTEGER)
                WHEN 1 THEN 'January'
                WHEN 2 THEN 'February'
                WHEN 3 THEN 'March'
                WHEN 4 THEN 'April'
                WHEN 5 THEN 'May'
                WHEN 6 THEN 'June'
                WHEN 7 THEN 'July'
                WHEN 8 THEN 'August'
                WHEN 9 THEN 'September'
                WHEN 10 THEN 'October'
                WHEN 11 THEN 'November'
                WHEN 12 THEN 'December'
                ELSE 'Unknown'
            END || ' ' || year AS remarks
        FROM monthly_goals
        WHERE user_id = :uid2
          AND printf('%04d-%02d-01', year, month) >= :from_date
          AND printf('%04d-%02d-01', year, month) <= :to_date

        ORDER BY date DESC
    )";

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":uid1", currentUserId);
    query.bindValue(":uid2", currentUserId);
    query.bindValue(":from_date", fromDate.toString("yyyy-MM-dd"));
    query.bindValue(":to_date", toDate.toString("yyyy-MM-dd"));

    if (selectedType != "All") {
        query.bindValue(":type", selectedType);
    }

    if (selectedCategory != "All") {
        query.bindValue(":category", selectedCategory);
    }

    if (!query.exec()) {
        qDebug() << "SQL error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tableWidgetTransactions->insertRow(row);
        for (int col = 0; col < 5; ++col) {
            ui->tableWidgetTransactions->setItem(
                row, col,
                new QTableWidgetItem(query.value(col).toString())
                );
        }
        row++;
    }
}

void viewtransactions::on_buttonExport_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Export Transactions",
        QDir::homePath() + "/transactions.csv",
        "CSV Files (*.csv)"
        );

    if (fileName.isEmpty()) {
        return; // user cancelled
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Error", "Could not open file for writing.");
        return;
    }

    QTextStream out(&file);

    // Write header row
    out << "Date,Category,Type,Amount,Remarks\n";

    // Write each row
    int rows = ui->tableWidgetTransactions->rowCount();
    int cols = ui->tableWidgetTransactions->columnCount();

    for (int i = 0; i < rows; ++i) {
        QStringList rowData;
        for (int j = 0; j < cols; ++j) {
            QString cell = ui->tableWidgetTransactions->item(i, j)->text();
            // Escape commas
            cell.replace(",", " ");
            rowData << cell;
        }
        out << rowData.join(",") << "\n";
    }

    file.close();

    QMessageBox::information(this, "Success", "Transactions exported successfully!");
}
