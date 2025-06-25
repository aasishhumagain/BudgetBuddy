#include "login.h"
#include "ui_login.h"
#include "homepage.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "signup.h"
#include "forgotpassword.h"
#include <QIcon>
#include <QDebug>
#include <QFile>
#include <QCoreApplication>

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login),
    passwordVisible(false),
    currentUserId(-1)
{
    ui->setupUi(this);

    // Setup icon paths
    QString basePath = QCoreApplication::applicationDirPath();
    iconClosedPath = basePath + "/assets/eye_closed.png";
    iconOpenPath = basePath + "/assets/eye_open.png";

    if (!QFile::exists(iconClosedPath) || !QFile::exists(iconOpenPath)) {
        qWarning() << "⚠️ Eye icon(s) missing:" << iconClosedPath << iconOpenPath;
    }

    // Setup password field
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
    ui->buttonTogglePassword->setIcon(QIcon(iconClosedPath));
    ui->buttonTogglePassword->setIconSize(QSize(24, 24));
}

login::~login()
{
    delete ui;
}

void login::showMessage(const QString &message)
{
    QMessageBox::information(this, "Login", message);
}

void login::on_buttonLogin_clicked()
{
    QString Username = ui->lineEditUsername->text();
    QString password = ui->lineEditPassword->text();

    QSqlQuery query;
    query.prepare("SELECT id FROM users WHERE username = :username AND password = :password");
    query.bindValue(":username", Username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        int userId = query.value("id").toInt();
        showMessage("Login successful!");
        homepage *home = new homepage(userId, this);  // ✅ pass userId
        home->show();
        this->hide();
    }
    else {
        showMessage("Invalid Username or password.");
    }
}

void login::on_buttonSignup_clicked()
{
    signup *signupWindow = new signup(this);
    signupWindow->exec();
}

void login::on_buttonForgotPassword_clicked()
{
    ForgotPassword *fp = new ForgotPassword(this);
    fp->exec();
}

void login::on_buttonTogglePassword_clicked()
{
    passwordVisible = !passwordVisible;

    // Toggle visibility
    ui->lineEditPassword->setEchoMode(passwordVisible ? QLineEdit::Normal : QLineEdit::Password);
    ui->lineEditPassword->setFocus();
    ui->lineEditPassword->update();

    // Toggle icon
    ui->buttonTogglePassword->setIcon(QIcon(passwordVisible ? iconOpenPath : iconClosedPath));
}

// Getter function (optional, if needed elsewhere)
int login::getCurrentUserId() const
{
    return currentUserId;
}
