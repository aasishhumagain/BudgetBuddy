#include "viewtransactions.h"
#include "ui_viewtransactions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QDebug>

viewtransactions::viewtransactions(QWidget *parent, int userId) :
    QDialog(parent),
    ui(new Ui::viewtransactions),
    currentUserId(userId)
{
    ui->setupUi(this);
    loadTransactionData();
    connect(ui->buttonBack, &QPushButton::clicked, this, &viewtransactions::onBackButtonClicked);
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

    QString sql = R"(
        SELECT date, category, type, amount, remarks
        FROM transactions
        WHERE user_id = :uid1

        UNION ALL

        SELECT
            printf('%04d-%02d-01', year, month) AS date,
            'Monthly Goal' AS category,
            'MonthlyGoal' AS type,
            amount,
            '' AS remarks
        FROM monthly_goals
        WHERE user_id = :uid2

        ORDER BY date DESC
    )";

    QSqlQuery query;
    query.prepare(sql);
    query.bindValue(":uid1", currentUserId);
    query.bindValue(":uid2", currentUserId);

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
