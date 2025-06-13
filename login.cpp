#include "login.h"
#include "ui_login.h"
#include "homepage.h"
#include <QSqlQuery>
#include <QMessageBox>
#include "signup.h"
#include "forgotpassword.h"


login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);

    // Mask password input
    ui->lineEditPassword->setEchoMode(QLineEdit::Password);
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
    QString email = ui->lineEditEmail->text();
    QString password = ui->lineEditPassword->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :email AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        showMessage("Login successful!");

        homepage *home = new homepage(this);
        home->show();
        this->hide(); // Hide the login window
    } else {
        showMessage("Invalid email or password.");
    }
}

void login::on_buttonSignup_clicked()
{
    signup *signupWindow = new signup(this);
    signupWindow->exec();  // Open the signup dialog as modal
}

void login::on_buttonForgotPassword_clicked()
{
    ForgotPassword *fp = new ForgotPassword(this);
    fp->exec();
}

