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

    // Labels
    QLabel *labelOldPassword = new QLabel("Enter old password:");
    QLabel *labelNewPassword = new QLabel("Enter new password:");
    QLabel *labelConfirmPassword = new QLabel("Confirm new password:");

    // Inputs
    lineEditOldPassword = new QLineEdit();
    lineEditNewPassword = new QLineEdit();
    lineEditConfirmPassword = new QLineEdit();

    lineEditOldPassword->setEchoMode(QLineEdit::Password);
    lineEditNewPassword->setEchoMode(QLineEdit::Password);
    lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

    // Toggle buttons
    toggleOldPasswordBtn = new QPushButton("👁️");
    toggleNewPasswordBtn = new QPushButton("👁️");
    toggleConfirmPasswordBtn = new QPushButton("👁️");

    toggleOldPasswordBtn->setFixedWidth(30);
    toggleNewPasswordBtn->setFixedWidth(30);
    toggleConfirmPasswordBtn->setFixedWidth(30);

    // Main buttons
    buttonChange = new QPushButton("Change Password");
    buttonCancel = new QPushButton("Cancel");

    // Layouts for inputs with toggles
    QHBoxLayout *oldPassLayout = new QHBoxLayout;
    oldPassLayout->addWidget(lineEditOldPassword);
    oldPassLayout->addWidget(toggleOldPasswordBtn);

    QHBoxLayout *newPassLayout = new QHBoxLayout;
    newPassLayout->addWidget(lineEditNewPassword);
    newPassLayout->addWidget(toggleNewPasswordBtn);

    QHBoxLayout *confirmPassLayout = new QHBoxLayout;
    confirmPassLayout->addWidget(lineEditConfirmPassword);
    confirmPassLayout->addWidget(toggleConfirmPasswordBtn);

    // Form layout
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow(labelOldPassword, oldPassLayout);
    formLayout->addRow(labelNewPassword, newPassLayout);
    formLayout->addRow(labelConfirmPassword, confirmPassLayout);

    // Button layout
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(buttonChange);
    buttonLayout->addWidget(buttonCancel);

    // Main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

    // Connections
    connect(buttonChange, &QPushButton::clicked, this, &ChangePassword::on_buttonChange_clicked);
    connect(buttonCancel, &QPushButton::clicked, this, &ChangePassword::on_buttonCancel_clicked);
    connect(toggleOldPasswordBtn, &QPushButton::clicked, this, &ChangePassword::toggleOldPasswordVisibility);
    connect(toggleNewPasswordBtn, &QPushButton::clicked, this, &ChangePassword::toggleNewPasswordVisibility);
    connect(toggleConfirmPasswordBtn, &QPushButton::clicked, this, &ChangePassword::toggleConfirmPasswordVisibility);
}

ChangePassword::~ChangePassword()
{
    // Children cleaned up by Qt
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
        return; // ❌ stays open
    }

    if (newPassword != confirmPassword) {
        showMessage("New passwords do not match.");
        return; // ❌ stays open
    }

    QSqlQuery query(DatabaseManager::instance().getDatabase());
    query.prepare("SELECT password FROM users WHERE id = :id");
    query.bindValue(":id", currentUserId);

    if (!query.exec() || !query.next()) {
        showMessage("Failed to check old password.");
        return; // ❌ stays open
    }

    QString currentPassword = query.value(0).toString();
    if (currentPassword != oldPassword) {
        showMessage("Old password is incorrect.");
        return; // ❌ stays open
    }

    query.prepare("UPDATE users SET password = :password WHERE id = :id");
    query.bindValue(":password", newPassword);
    query.bindValue(":id", currentUserId);

    if (query.exec()) {
        showMessage("Password changed successfully!");
        accept(); // ✅ closes only if success
    } else {
        showMessage("Failed to update password.");
    }
}

void ChangePassword::on_buttonCancel_clicked()
{
    reject();  // Close dialog
}

void ChangePassword::toggleOldPasswordVisibility()
{
    oldPassVisible = !oldPassVisible;
    lineEditOldPassword->setEchoMode(oldPassVisible ? QLineEdit::Normal : QLineEdit::Password);
    toggleOldPasswordBtn->setText(oldPassVisible ? "🙈" : "👁️");
}

void ChangePassword::toggleNewPasswordVisibility()
{
    newPassVisible = !newPassVisible;
    lineEditNewPassword->setEchoMode(newPassVisible ? QLineEdit::Normal : QLineEdit::Password);
    toggleNewPasswordBtn->setText(newPassVisible ? "🙈" : "👁️");
}

void ChangePassword::toggleConfirmPasswordVisibility()
{
    confirmPassVisible = !confirmPassVisible;
    lineEditConfirmPassword->setEchoMode(confirmPassVisible ? QLineEdit::Normal : QLineEdit::Password);
    toggleConfirmPasswordBtn->setText(confirmPassVisible ? "🙈" : "👁️");
}
