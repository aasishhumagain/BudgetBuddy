#include "transactions.h"
#include "ui_transactions.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QDebug>

// Category presets
const QStringList expenseCategories = {"Food", "Fuel", "Rent", "Shopping", "Misc"};
const QStringList incomeCategories = {"Salary", "Misc"};

transactions::transactions(QWidget *parent, int userId) :
    QDialog(parent),
    ui(new Ui::transactions),
    currentUserId(userId)
{
    ui->setupUi(this);

    // Amount validator
    QDoubleValidator *validator = new QDoubleValidator(0.01, 1000000.00, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->lineEditAmount->setValidator(validator);

    // Type selector
    ui->comboBoxType->addItems({"Expense", "Income"});
    ui->dateEdit->setCalendarPopup(true);
    ui->dateEdit->setDate(QDate::currentDate());

    // Connect events
    connect(ui->comboBoxType, &QComboBox::currentTextChanged, this, &transactions::on_typeChanged);
    connect(ui->buttonBack, &QPushButton::clicked, this, &transactions::on_buttonBack_clicked);

    // Set initial category options
    on_typeChanged(ui->comboBoxType->currentText());
}

transactions::~transactions()
{
    delete ui;
}

void transactions::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Transaction", msg);
}

void transactions::on_typeChanged(const QString &type)
{
    ui->comboBoxCategory->clear();

    if (type == "Income") {
        ui->comboBoxCategory->addItems(incomeCategories);
    } else if (type == "Expense") {
        ui->comboBoxCategory->addItems(expenseCategories);
    }
}

void transactions::on_buttonSubmit_clicked()
{
    QString amountText = ui->lineEditAmount->text();
    QString category = ui->comboBoxCategory->currentText();
    QString type = ui->comboBoxType->currentText();
    QDate date = ui->dateEdit->date();
    QString dateStr = date.toString("yyyy-MM-dd");
    QString remarks = ui->lineEditRemarks->text().trimmed();

    if (amountText.isEmpty()) {
        showMessage("Please enter an amount.");
        return;
    }

    double amount = amountText.toDouble();
    if (amount <= 0.0) {
        showMessage("Amount must be greater than zero.");
        return;
    }

    if (type == "Expense") {
        int year = date.year();
        int month = date.month();
        QString paddedMonth = QString("%1").arg(month, 2, 10, QLatin1Char('0'));
        QString monthStr = date.toString("yyyy-MM");

        QSqlQuery goalQuery;
        goalQuery.prepare(R"(
            SELECT SUM(amount)
            FROM monthly_goals
            WHERE user_id = :user_id AND year = :year AND month = :month
        )");
        goalQuery.bindValue(":user_id", currentUserId);
        goalQuery.bindValue(":year", year);
        goalQuery.bindValue(":month", paddedMonth);

        double totalGoal = 0;
        if (goalQuery.exec() && goalQuery.next()) {
            totalGoal = goalQuery.value(0).toDouble();
        }

        QSqlQuery sumQuery;
        sumQuery.prepare(R"(
            SELECT SUM(amount)
            FROM transactions
            WHERE user_id = :user_id AND type = 'Expense'
              AND strftime('%Y-%m', date) = :month_str
        )");
        sumQuery.bindValue(":user_id", currentUserId);
        sumQuery.bindValue(":month_str", monthStr);

        double totalSpent = 0;
        if (sumQuery.exec() && sumQuery.next()) {
            totalSpent = sumQuery.value(0).toDouble();
        }

        double afterAddition = totalSpent + amount;
        double remaining = totalGoal - totalSpent;
        double exceededBy = afterAddition - totalGoal;

        if (totalGoal > 0 && afterAddition > totalGoal) {
            QMessageBox::StandardButton reply = QMessageBox::warning(
                this,
                "⚠️ Monthly Limit Exceeded",
                QString("This expense exceeds your monthly goal!\n\n"
                        "Monthly Limit: %1\nSpent So Far: %2\nRemaining: %3\n"
                        "Attempting to Add: %4\nYou’d exceed by: %5\n\n"
                        "Do you still want to add this transaction?")
                    .arg(totalGoal)
                    .arg(totalSpent)
                    .arg(remaining)
                    .arg(amount)
                    .arg(exceededBy),
                QMessageBox::Yes | QMessageBox::Cancel
                );

            if (reply != QMessageBox::Yes) {
                return;
            }
        }
    }

    QSqlQuery query;
    query.prepare("INSERT INTO transactions (user_id, type, category, amount, date, remarks) "
                  "VALUES (:user_id, :type, :category, :amount, :date, :remarks)");
    query.bindValue(":user_id", currentUserId);
    query.bindValue(":type", type);
    query.bindValue(":category", category);
    query.bindValue(":amount", amount);
    query.bindValue(":date", dateStr);
    query.bindValue(":remarks", remarks);

    if (query.exec()) {
        showMessage("Transaction added successfully!");
        this->close();
    } else {
        showMessage("Failed to add transaction: " + query.lastError().text());
    }
}

void transactions::on_buttonBack_clicked()
{
    this->close();
}
