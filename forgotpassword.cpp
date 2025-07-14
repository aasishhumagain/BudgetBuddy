#include "forgotpassword.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
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

    // Visibility toggle buttons
    toggleNewPasswordBtn = new QPushButton("👁️");
    toggleConfirmPasswordBtn = new QPushButton("👁️");
    toggleNewPasswordBtn->setFixedWidth(30);
    toggleConfirmPasswordBtn->setFixedWidth(30);

    // Buttons
    buttonReset = new QPushButton("Reset Password");
    buttonCancel = new QPushButton("Cancel");

    // Password layout with toggle
    QHBoxLayout *newPassLayout = new QHBoxLayout;
    newPassLayout->addWidget(lineEditNewPassword);
    newPassLayout->addWidget(toggleNewPasswordBtn);

    QHBoxLayout *confirmPassLayout = new QHBoxLayout;
    confirmPassLayout->addWidget(lineEditConfirmPassword);
    confirmPassLayout->addWidget(toggleConfirmPasswordBtn);

    // Form layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(labelUsername, lineEditUsername);
    formLayout->addRow(labelNewPassword, newPassLayout);
    formLayout->addRow(labelConfirmPassword, confirmPassLayout);

    // Button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonReset);
    buttonLayout->addWidget(buttonCancel);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Connections
    connect(buttonReset, &QPushButton::clicked, this, &ForgotPassword::on_buttonReset_clicked);
    connect(buttonCancel, &QPushButton::clicked, this, &ForgotPassword::on_buttonCancel_clicked);
    connect(toggleNewPasswordBtn, &QPushButton::clicked, this, &ForgotPassword::toggleNewPasswordVisibility);
    connect(toggleConfirmPasswordBtn, &QPushButton::clicked, this, &ForgotPassword::toggleConfirmPasswordVisibility);
}

ForgotPassword::~ForgotPassword()
{
    // Qt handles deletion of children automatically
}

void ForgotPassword::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Reset Password", msg);
}

void ForgotPassword::on_buttonReset_clicked()
{
    QString username = lineEditUsername->text();
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

    QSqlQuery query;
    query.prepare("UPDATE users SET password = :password WHERE username = :username");
    query.bindValue(":password", newPassword);
    query.bindValue(":username", username);

    if (query.exec() && query.numRowsAffected() > 0) {
        showMessage("Password updated successfully!");
        accept();  // Close dialog
    } else {
        showMessage("Username not found or update failed.");
    }
}

void ForgotPassword::on_buttonCancel_clicked()
{
    reject();  // Close dialog
}

void ForgotPassword::toggleNewPasswordVisibility()
{
    newPassVisible = !newPassVisible;
    lineEditNewPassword->setEchoMode(newPassVisible ? QLineEdit::Normal : QLineEdit::Password);
    toggleNewPasswordBtn->setText(newPassVisible ? "🙈" : "👁️");
}

void ForgotPassword::toggleConfirmPasswordVisibility()
{
    confirmPassVisible = !confirmPassVisible;
    lineEditConfirmPassword->setEchoMode(confirmPassVisible ? QLineEdit::Normal : QLineEdit::Password);
    toggleConfirmPasswordBtn->setText(confirmPassVisible ? "🙈" : "👁️");
}
