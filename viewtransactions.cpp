#include "viewtransactions.h"
#include "ui_viewtransactions.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QTableWidgetItem>
#include <QHeaderView>
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
    // Setup table columns
    ui->tableWidgetTransactions->setRowCount(0);
    ui->tableWidgetTransactions->setColumnCount(5);

    QStringList headers = {"Date", "Category", "Type", "Amount", "Remarks"};
    ui->tableWidgetTransactions->setHorizontalHeaderLabels(headers);

    // Stretch Remarks column for better readability
    ui->tableWidgetTransactions->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Stretch);

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
            QString value = query.value(col).toString();
            ui->tableWidgetTransactions->setItem(row, col, new QTableWidgetItem(value));
        }
        row++;
    }
}
