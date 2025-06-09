#include "monthlygoals.h"
#include "ui_monthlygoals.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDate>

monthlygoals::monthlygoals(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::monthlygoals)
{
    ui->setupUi(this);

    // Validator for budget amount
    QDoubleValidator *validator = new QDoubleValidator(0.01, 1000000.0, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditAmount->setValidator(validator);

    // Month list
    QStringList months = {"January", "February", "March", "April", "May", "June",
                          "July", "August", "September", "October", "November", "December"};
    ui->comboBoxMonth->addItems(months);

    // Default year to current
    ui->spinBoxYear->setMinimum(2000);
    ui->spinBoxYear->setMaximum(2100);
    ui->spinBoxYear->setValue(QDate::currentDate().year());
}

monthlygoals::~monthlygoals()
{
    delete ui;
}

void monthlygoals::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Monthly Budget", msg);
}

void monthlygoals::on_buttonSubmit_clicked()
{
    QString month = ui->comboBoxMonth->currentText();
    int year = ui->spinBoxYear->value();
    QString budgetText = ui->lineEditAmount->text();

    if (budgetText.isEmpty()) {
        showMessage("Please enter a budget amount.");
        return;
    }

    double amount = budgetText.toDouble();
    if (amount <= 0.0) {
        showMessage("Budget must be greater than 0.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO monthly_goals (user_id, month, year, amount) "
                  "VALUES (:user_id, :month, :year, :amount) "
                  "ON CONFLICT(user_id, month, year) "
                  "DO UPDATE SET amount = excluded.amount");

    query.bindValue(":user_id", 1);
    query.bindValue(":month", month);
    query.bindValue(":year", year);
    query.bindValue(":amount", amount);

    query.exec();


    if (query.exec()) {
        showMessage("Monthly budget saved successfully!");
        this->close();
    } else {
        showMessage("Error: " + query.lastError().text());
    }
}
