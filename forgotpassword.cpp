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

    // Labels
    QLabel *labelUsername = new QLabel("Username:");
    QLabel *labelNewPassword = new QLabel("Enter new password:");
    QLabel *labelConfirmPassword = new QLabel("Confirm new password:");

    // Inputs
    lineEditUsername = new QLineEdit();
    lineEditNewPassword = new QLineEdit();
    lineEditConfirmPassword = new QLineEdit();

    lineEditNewPassword->setEchoMode(QLineEdit::Password);
    lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

    // Show password checkbox - now placed BELOW both fields
    checkBoxShowPassword = new QCheckBox("Show password");
    checkBoxShowPassword->setStyleSheet("font: 600 10pt \"Segoe UI\"; color: black;");

    // Buttons
    buttonReset = new QPushButton("Reset Password");
    buttonCancel = new QPushButton("Cancel");

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
    mainLayout->addWidget(checkBoxShowPassword);  // Show password below all inputs
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
