#include "signup.h"
#include "ui_signup.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QFile>
#include <QCoreApplication>
#include <QDebug>

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup),
    passwordVisible(false)
{
    ui->setupUi(this);

    ui->lineEditUsername->setPlaceholderText("Enter Username");
    ui->lineEditPassword->setPlaceholderText("Enter Password");
    ui->lineEditConfirmPwd->setPlaceholderText("Confirm Password");

    // Set password fields to Password mode initially
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirmPwd->setEchoMode(QLineEdit::Password);

    // Load icons from assets folder
    QString basePath = QCoreApplication::applicationDirPath();
    iconClosedPath = basePath + "/assets/eye_closed.png";
    iconOpenPath = basePath + "/assets/eye_open.png";

    if (!QFile::exists(iconClosedPath) || !QFile::exists(iconOpenPath)) {
        qWarning() << "❗ Eye icon(s) not found!";
    }

    // Set initial icon and connect toggle button
    ui->buttonTogglePassword->setIcon(QIcon(iconClosedPath));
    ui->buttonTogglePassword->setIconSize(QSize(24, 24));
}

signup::~signup()
{
    delete ui;
}

void signup::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Signup", msg);
}

void signup::on_buttonTogglePassword_clicked()
{
    passwordVisible = !passwordVisible;

    // Explicitly force echo modes again for both fields
    ui->lineEditPassword->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);
    ui->lineEditConfirmPwd->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);

    // Update icon
    ui->buttonTogglePassword->setIcon(QIcon(passwordVisible ? iconOpenPath : iconClosedPath));

    // Debug logs
    qDebug() << "Password toggle clicked. Now visible:" << passwordVisible;
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
