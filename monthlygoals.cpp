#include "monthlygoals.h"
#include "ui_monthlygoals.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <qdatetime.h>

monthlygoals::monthlygoals(int userId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::monthlygoals)
    , currentUserId(userId)
{
    ui->setupUi(this);

    ui->comboBoxMonth->addItems({"01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12"});
    ui->spinBoxYear->setRange(2000, 2100);
    ui->spinBoxYear->setValue(QDate::currentDate().year());

    connect(ui->buttonSubmit, &QPushButton::clicked, this, &monthlygoals::onSubmitClicked);
}


monthlygoals::~monthlygoals()
{
    delete ui;
}

void monthlygoals::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Monthly Goal", msg);
}

void monthlygoals::onSubmitClicked()
{
    QString month = ui->comboBoxMonth->currentText();
    int year = ui->spinBoxYear->value();
    QString amountText = ui->lineEditAmount->text();

    if (amountText.isEmpty()) {
        showMessage("Please enter a budget amount.");
        return;
    }

    double amount = amountText.toDouble();
    if (amount <= 0.0) {
        showMessage("Amount must be greater than zero.");
        return;
    }

    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO monthly_goals (user_id, month, year, amount)
        VALUES (:user_id, :month, :year, :amount)
    )");
    query.bindValue(":user_id", currentUserId);
    query.bindValue(":month", month);
    query.bindValue(":year", year);
    query.bindValue(":amount", amount);

    if (query.exec()) {
        showMessage("Monthly goal set!");
        this->close();
    } else {
        showMessage("Error: " + query.lastError().text());
    }
}
