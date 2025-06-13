#include "signup.h"
#include "ui_signup.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLineEdit>

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    ui->lineEditUsername->setPlaceholderText("Enter Username");
    ui->lineEditPassword->setPlaceholderText("Enter Password");
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
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
    QString username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();
    QString confirmPassword = ui->lineEditConfirmPwd->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        showMessage("Please fill in all fields.");
        return;
    }

    if (password != confirmPassword) {
        showMessage("Passwords do not match.");
        return;
    }

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT id FROM users WHERE username = :username");
    checkQuery.bindValue(":username", username);
    checkQuery.exec();

    if (checkQuery.next()) {
        showMessage("Username already exists.");
        return;
    }

    QSqlQuery insertQuery;
    insertQuery.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    insertQuery.bindValue(":username", username);
    insertQuery.bindValue(":password", password);

    if (insertQuery.exec()) {
        showMessage("Account created! You can now log in.");
        this->close();
    } else {
        showMessage("Signup failed: " + insertQuery.lastError().text());
    }
}
