#include "viewtransactions.h"
#include "ui_viewtransactions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QDebug>

void viewtransactions::onBackButtonClicked()
{
    this->close();  // or this->hide();
}

viewtransactions::viewtransactions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::viewtransactions)
{
    ui->setupUi(this);
    loadTransactionData();
}

viewtransactions::~viewtransactions()
{
    delete ui;
}

void viewtransactions::loadTransactionData()
{
    ui->tableWidgetTransactions->setRowCount(0);
    ui->tableWidgetTransactions->setColumnCount(4);
    connect(ui->buttonBack, &QPushButton::clicked, this, &viewtransactions::onBackButtonClicked);
    QStringList headers = {"Date", "Category", "Type", "Amount"};
    ui->tableWidgetTransactions->setHorizontalHeaderLabels(headers);

    QSqlQuery query;
    QString sql = R"(
        SELECT date, category, type, amount FROM transactions
        UNION ALL
        SELECT
            '01-' || month || '-' || year AS date,
            month,
            'MonthlyGoal',
            amount
        FROM monthly_goals
        ORDER BY date DESC
    )";

    if (!query.exec(sql)) {
        qDebug() << "SQL error:" << query.lastError().text();
        return;
    }

    int row = 0;
    while (query.next()) {
        ui->tableWidgetTransactions->insertRow(row);
        for (int col = 0; col < 4; ++col) {
            ui->tableWidgetTransactions->setItem(row, col,
                                                 new QTableWidgetItem(query.value(col).toString()));
        }
        row++;
    }
}
