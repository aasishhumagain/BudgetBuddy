#include "signup.h"
#include "ui_signup.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDebug>

signup::signup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::signup)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);

    // Set placeholder text
    ui->lineEditUsername->setPlaceholderText("Enter Username");
    ui->lineEditPassword->setPlaceholderText("Enter Password");
    ui->lineEditConfirmPwd->setPlaceholderText("Confirm Password");

    // Start with password fields hidden
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->lineEditConfirmPwd->setEchoMode(QLineEdit::Password);

    // Connect checkbox for visibility toggle
    connect(ui->checkBoxShowPassword, &QCheckBox::toggled, this, &signup::on_checkBoxShowPassword_toggled);
}

signup::~signup()
{
    delete ui;
}

void signup::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Signup", msg);
}

void signup::on_checkBoxShowPassword_toggled(bool checked)
{
    ui->lineEditPassword->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    ui->lineEditConfirmPwd->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}

void signup::on_buttonCreateAccount_clicked()
{
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text();
    QString confirmPassword = ui->lineEditConfirmPwd->text();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username cannot be empty.");
        return;
    }

    // Allow only letters and digits in username
    for (const QChar &ch : username) {
        if (!ch.isLetterOrNumber()) {
            QMessageBox::warning(this, "Error", "Username must not contain special characters.");
            return;
        }
    }

    if (password.length() < 8) {
        QMessageBox::warning(this, "Error", "Password must be at least 8 characters long.");
        return;
    }

    // Password rules: must include upper, lower, digit, special
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (const QChar &ch : password) {
        if (ch.isUpper()) hasUpper = true;
        else if (ch.isLower()) hasLower = true;
        else if (ch.isDigit()) hasDigit = true;
        else hasSpecial = true;
    }

    if (!(hasUpper && hasLower && hasDigit && hasSpecial)) {
        QMessageBox::warning(this, "Error", "Password must contain at least 1 uppercase, 1 lowercase, 1 number, and 1 special character.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        if (query.lastError().nativeErrorCode() == "19") {
            QMessageBox::warning(this, "Error", "Username already exists.");
        } else {
            QMessageBox::warning(this, "Error", "Signup failed: " + query.lastError().text());
        }
        return;
    }

    QMessageBox::information(this, "Success", "Account created! You can now log in.");
    this->accept();
}
