#include "changepassword.h"
#include "databasemanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>

ChangePassword::ChangePassword(int userId, QWidget *parent) :
    QDialog(parent),
    currentUserId(userId)
{
    setWindowTitle("Change Password");
    setStyleSheet("background-color: rgb(202, 219, 194);");

    // Style string
    QString commonStyle = "font: 10pt \"Segoe UI\"; background-color: transparent; color: black;";

    // Labels
    QLabel *labelOldPassword = new QLabel("Enter old password:");
    QLabel *labelNewPassword = new QLabel("Enter new password:");
    QLabel *labelConfirmPassword = new QLabel("Confirm new password:");
    labelOldPassword->setStyleSheet(commonStyle);
    labelNewPassword->setStyleSheet(commonStyle);
    labelConfirmPassword->setStyleSheet(commonStyle);

    // Inputs
    lineEditOldPassword = new QLineEdit();
    lineEditNewPassword = new QLineEdit();
    lineEditConfirmPassword = new QLineEdit();

    lineEditOldPassword->setEchoMode(QLineEdit::Password);
    lineEditNewPassword->setEchoMode(QLineEdit::Password);
    lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

    lineEditOldPassword->setStyleSheet(commonStyle);
    lineEditNewPassword->setStyleSheet(commonStyle);
    lineEditConfirmPassword->setStyleSheet(commonStyle);

    // Show password checkbox
    checkBoxShowPassword = new QCheckBox("Show password");
    checkBoxShowPassword->setStyleSheet("font: 600 10pt \"Segoe UI\"; background-color: transparent; color: black;");

    // Main buttons
    buttonChange = new QPushButton("Change Password");
    buttonCancel = new QPushButton("Cancel");
    buttonChange->setStyleSheet(commonStyle);
    buttonCancel->setStyleSheet(commonStyle);

    // Form layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(labelOldPassword, lineEditOldPassword);
    formLayout->addRow(labelNewPassword, lineEditNewPassword);
    formLayout->addRow(labelConfirmPassword, lineEditConfirmPassword);

    // Button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonChange);
    buttonLayout->addWidget(buttonCancel);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(checkBoxShowPassword);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Connections
    connect(buttonChange, &QPushButton::clicked, this, &ChangePassword::on_buttonChange_clicked);
    connect(buttonCancel, &QPushButton::clicked, this, &ChangePassword::on_buttonCancel_clicked);
    connect(checkBoxShowPassword, &QCheckBox::toggled, this, &ChangePassword::on_checkBoxShowPassword_toggled);
}

ChangePassword::~ChangePassword()
{
    // Children auto-deleted by Qt
}

void ChangePassword::showMessage(const QString &msg)
{
    QMessageBox::information(this, "Change Password", msg);
}

void ChangePassword::on_buttonChange_clicked()
{
    QString oldPassword = lineEditOldPassword->text();
    QString newPassword = lineEditNewPassword->text();
    QString confirmPassword = lineEditConfirmPassword->text();

    if (oldPassword.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
        showMessage("Please fill in all fields.");
        return;
    }

    if (newPassword != confirmPassword) {
        showMessage("New passwords do not match.");
        return;
    }

    if (oldPassword == newPassword) {
        showMessage("New password must be different from the old password.");
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

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT password FROM users WHERE id = :id");
    query.bindValue(":id", currentUserId);

    if (!query.exec() || !query.next()) {
        showMessage("Failed to check old password.");
        return;
    }

    QString currentPassword = query.value(0).toString();
    if (currentPassword != oldPassword) {
        showMessage("Old password is incorrect.");
        return;
    }

    query.prepare("UPDATE users SET password = :password WHERE id = :id");
    query.bindValue(":password", newPassword);
    query.bindValue(":id", currentUserId);

    if (query.exec()) {
        showMessage("Password changed successfully!");
        accept();
    } else {
        showMessage("Failed to update password.");
    }
}

void ChangePassword::on_buttonCancel_clicked()
{
    reject();
}

void ChangePassword::on_checkBoxShowPassword_toggled(bool checked)
{
    QLineEdit::EchoMode mode = checked ? QLineEdit::Normal : QLineEdit::Password;
    lineEditOldPassword->setEchoMode(mode);
    lineEditNewPassword->setEchoMode(mode);
    lineEditConfirmPassword->setEchoMode(mode);
}
