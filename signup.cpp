#include "signup.h"
#include "ui_signup.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <qlineedit.h>


signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirmPwd->setEchoMode(QLineEdit::Password);
}

signup::~signup()
{
    delete ui;
}

void signup::showMessage(const QString &msg) {
    QMessageBox::information(this, "Signup", msg);
}

void signup::on_buttonCreateAccount_clicked()
{
    QString name = ui->lineEditName->text();
    QString dob = ui->dateEdit->date().toString("yyyy-MM-dd");
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();
    QString confirmPassword = ui->lineEditConfirmPwd->text();

    if (name.isEmpty() || email.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        showMessage("Please fill in all fields.");
        return;
    }

    if (password != confirmPassword) {
        showMessage("Passwords do not match.");
        return;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM users WHERE username = :email");
    checkQuery.bindValue(":email", email);
    checkQuery.exec();

    if (checkQuery.next()) {
        showMessage("Email already registered.");
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (:email, :password)");
    insertQuery.bindValue(":email", email);
    insertQuery.bindValue(":password", password);

    if (insertQuery.exec()) {
        showMessage("Account created! You can now login.");
        close(); // Close signup window
    } else {
        showMessage("Signup failed: " + insertQuery.lastError().text());
    }
}
