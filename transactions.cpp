#include "transactions.h"
#include "ui_transactions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDoubleValidator>

transactions::transactions(QWidget *parent, int userId) :
    QDialog(parent),
    ui(new Ui::transactions),
    currentUserId(userId)
{
    ui->setupUi(this);

    // Validator
    QDoubleValidator *validator = new QDoubleValidator(0.01, 1000000.00, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditAmount->setValidator(validator);

    // Defaults
    ui->comboBoxCategory->addItems({"Food", "Fuel", "Rent", "Shopping", "Salary", "Misc"});
    ui->comboBoxType->addItems({"Income", "Expense"});
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());
}

transactions::~transactions()
{
    delete ui;
}

void transactions::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Transaction", msg);
}

void transactions::on_buttonSubmit_clicked()
{
    QString amountText = ui->lineEditAmount->text();
    QString category = ui->comboBoxCategory->currentText();
    QString type = ui->comboBoxType->currentText();
    QString date = ui->dateEdit->date().toString("yyyy-MM-dd");

    if (amountText.isEmpty()) {
        showMessage("Please enter an amount.");
        return;
    }

    double amount = amountText.toDouble();
    if (amount <= 0.0) {
        showMessage("Amount must be greater than zero.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO transactions (user_id, type, category, amount, date) "
                  "VALUES (:user_id, :type, :category, :amount, :date)");
    query.bindValue(":user_id", currentUserId); // ✅ use the actual user ID
    query.bindValue(":type", type);
    query.bindValue(":category", category);
    query.bindValue(":amount", amount);
    query.bindValue(":date", date);

    if (query.exec()) {
        showMessage("Transaction added successfully!");
        this->close();
    } else {
        showMessage("Failed to add transaction: " + query.lastError().text());
    }
}
