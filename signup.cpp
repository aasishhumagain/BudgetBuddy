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
    QString username = ui->lineEditUsername->text().trimmed();
    QString password = ui->lineEditPassword->text();
    QString confirmPassword = ui->lineEditConfirmPwd->text();

    // Username empty check
    if (username.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username cannot be empty.");
        return;
    }

    // Username rules
    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (const QChar &ch : username) {
        if (ch.isUpper()) hasUpper = true;
        else if (ch.isLower()) hasLower = true;
        else if (ch.isDigit()) hasDigit = true;
        else hasSpecial = true;
    }

    if (hasSpecial) {
        QMessageBox::warning(this, "Error", "Username must not contain special characters.");
        return;
    }

    if (!(hasUpper && hasLower && hasDigit)) {
        QMessageBox::warning(this, "Error", "Username must contain at least 1 uppercase, 1 lowercase, and 1 number.");
        return;
    }

    // Password length
    if (password.length() < 8) {
        QMessageBox::warning(this, "Error", "Password must be at least 8 characters long.");
        return;
    }

    // Password rules
    bool passHasUpper = false, passHasLower = false, passHasDigit = false, passHasSpecial = false;
    for (const QChar &ch : password) {
        if (ch.isUpper()) passHasUpper = true;
        else if (ch.isLower()) passHasLower = true;
        else if (ch.isDigit()) passHasDigit = true;
        else passHasSpecial = true; // anything else is special
    }

    if (!(passHasUpper && passHasLower && passHasDigit && passHasSpecial)) {
        QMessageBox::warning(this, "Error", "Password must contain at least 1 uppercase, 1 lowercase, 1 number, and 1 special character.");
        return;
    }

    // Confirm match
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Passwords do not match.");
        return;
    }

    // Insert plain password (for dev only!)
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (:username, :password)");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (!query.exec()) {
        if (query.lastError().nativeErrorCode() == "19") { // UNIQUE constraint fail
            QMessageBox::warning(this, "Error", "Username already exists.");
        } else {
            QMessageBox::warning(this, "Error", "Signup failed: " + query.lastError().text());
        }
        return;
    }

    QMessageBox::information(this, "Success", "Account created! You can now log in.");
    this->accept();
}
