#include "forgotpassword.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>

ForgotPassword::ForgotPassword(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Reset Password");
    setStyleSheet("background-color: rgb(202, 219, 194);");

    QString commonStyle = "font: 10pt \"Segoe UI\"; background-color: transparent; color: black;";

    // Labels
    QLabel *labelUsername = new QLabel("Username:");
    QLabel *labelNewPassword = new QLabel("Enter new password:");
    QLabel *labelConfirmPassword = new QLabel("Confirm new password:");
    labelUsername->setStyleSheet(commonStyle);
    labelNewPassword->setStyleSheet(commonStyle);
    labelConfirmPassword->setStyleSheet(commonStyle);

    // Inputs
    lineEditUsername = new QLineEdit();
    lineEditNewPassword = new QLineEdit();
    lineEditConfirmPassword = new QLineEdit();

    lineEditNewPassword->setEchoMode(QLineEdit::Password);
    lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

    lineEditUsername->setStyleSheet(commonStyle);
    lineEditNewPassword->setStyleSheet(commonStyle);
    lineEditConfirmPassword->setStyleSheet(commonStyle);

    // Show password checkbox
    checkBoxShowPassword = new QCheckBox("Show password");
    checkBoxShowPassword->setStyleSheet("font: 600 10pt \"Segoe UI\"; background-color: transparent; color: black;");

    // Buttons
    buttonReset = new QPushButton("Reset Password");
    buttonCancel = new QPushButton("Cancel");
    buttonReset->setStyleSheet(commonStyle);
    buttonCancel->setStyleSheet(commonStyle);

    // Form layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(labelUsername, lineEditUsername);
    formLayout->addRow(labelNewPassword, lineEditNewPassword);
    formLayout->addRow(labelConfirmPassword, lineEditConfirmPassword);

    // Button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonReset);
    buttonLayout->addWidget(buttonCancel);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(checkBoxShowPassword);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Connections
    connect(buttonReset, &QPushButton::clicked, this, &ForgotPassword::on_buttonReset_clicked);
    connect(buttonCancel, &QPushButton::clicked, this, &ForgotPassword::on_buttonCancel_clicked);
    connect(checkBoxShowPassword, &QCheckBox::toggled, this, &ForgotPassword::on_checkBoxShowPassword_toggled);
}

ForgotPassword::~ForgotPassword()
{
    // Children auto-deleted
}

void ForgotPassword::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Reset Password", msg);
}

void ForgotPassword::on_buttonReset_clicked()
{
    QString username = lineEditUsername->text().trimmed();
    QString newPassword = lineEditNewPassword->text();
    QString confirmPassword = lineEditConfirmPassword->text();

    if (username.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        showMessage("Please fill in all fields.");
        return;
    }

    if (newPassword != confirmPassword) {
        showMessage("Passwords do not match.");
        return;
    }

    // Enforce password complexity
    if (newPassword.length() < 8) {
        showMessage("Password must be at least 8 characters long.");
        return;
    }

    bool hasUpper = false, hasLower = false, hasDigit = false, hasSpecial = false;
    for (const QChar &ch : newPassword) {
        if (ch.isUpper()) hasUpper = true;
        else if (ch.isLower()) hasLower = true;
        else if (ch.isDigit()) hasDigit = true;
        else hasSpecial = true;
    }

    if (!(hasUpper && hasLower && hasDigit && hasSpecial)) {
        showMessage("Password must contain at least 1 uppercase, 1 lowercase, 1 number, and 1 special character.");
        return;
    }

    // Check if old password is the same
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT password FROM users WHERE username = :username");
    checkQuery.bindValue(":username", username);
    if (checkQuery.exec() && checkQuery.next()) {
        QString oldPassword = checkQuery.value(0).toString();
        if (oldPassword == newPassword) {
            showMessage("Old and new passwords must not be the same.");
            return;
        }
    } else {
        showMessage("Username not found.");
        return;
    }

    // Update password
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET password = :password WHERE username = :username");
    updateQuery.bindValue(":password", newPassword);
    updateQuery.bindValue(":username", username);

    if (updateQuery.exec() && updateQuery.numRowsAffected() > 0) {
        showMessage("Password updated successfully!");
        accept();  // Close dialog
    } else {
        showMessage("Password update failed.");
    }
}

void ForgotPassword::on_buttonCancel_clicked()
{
    reject();  // Close dialog
}

void ForgotPassword::on_checkBoxShowPassword_toggled(bool checked)
{
    lineEditNewPassword->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
    lineEditConfirmPassword->setEchoMode(checked ? QLineEdit::Normal : QLineEdit::Password);
}
