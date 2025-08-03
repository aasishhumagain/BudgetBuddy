#include "monthlygoals.h"
#include "ui_monthlygoals.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>
#include <QDebug>

monthlygoals::monthlygoals(int userId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::monthlygoals)
    , currentUserId(userId)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);

    ui->comboBoxMonth->addItems({
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    });

    ui->spinBoxYear->setRange(2000, 2100);
    ui->spinBoxYear->setValue(QDate::currentDate().year());

    connect(ui->buttonSubmit, &QPushButton::clicked, this, &monthlygoals::onSubmitClicked);
    connect(ui->buttonBack, &QPushButton::clicked, this, &monthlygoals::on_buttonBack_clicked);
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
    // Optional debug: print all monthly_goals
    QSqlQuery debugQuery;
    if (debugQuery.exec("SELECT user_id, year, month, amount FROM monthly_goals")) {
        while (debugQuery.next()) {
            qDebug() << "Goal Row - User:" << debugQuery.value(0).toInt()
            << "Year:" << debugQuery.value(1).toInt()
            << "Month:" << debugQuery.value(2).toString()
            << "Amount:" << debugQuery.value(3).toDouble();
        }
    } else {
        qDebug() << "DEBUG query failed:" << debugQuery.lastError().text();
    }

    int monthIndex = ui->comboBoxMonth->currentIndex(); // 0-based
    QString month = QString("%1").arg(monthIndex + 1, 2, 10, QChar('0')); // "01"-"12"
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
        ON CONFLICT(user_id, month, year)
        DO UPDATE SET amount = excluded.amount
    )");
    query.bindValue(":user_id", currentUserId);
    query.bindValue(":month", month);
    query.bindValue(":year", year);
    query.bindValue(":amount", amount);

    if (query.exec()) {
        showMessage("Monthly goal saved!");
        this->close();
    } else {
        showMessage("Error: " + query.lastError().text());
    }
}

void monthlygoals::on_buttonBack_clicked()
{
    this->close();
}
