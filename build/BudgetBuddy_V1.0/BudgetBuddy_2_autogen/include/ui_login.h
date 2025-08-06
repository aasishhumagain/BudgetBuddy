/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *labelOr;
    QPushButton *buttonForgotPassword;
    QCheckBox *checkBoxPassword;
    QLabel *labelBlob;
    QLineEdit *lineEditPassword;
    QLineEdit *lineEditUsername;
    QPushButton *buttonSignup;
    QLabel *labelTitle;
    QLabel *labelIcon;
    QPushButton *buttonLogin;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(1000, 800);
        login->setMinimumSize(QSize(0, 800));
        login->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 219, 194);"));
        labelOr = new QLabel(login);
        labelOr->setObjectName("labelOr");
        labelOr->setGeometry(QRect(620, 400, 111, 21));
        labelOr->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"font: 700 10pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        buttonForgotPassword = new QPushButton(login);
        buttonForgotPassword->setObjectName("buttonForgotPassword");
        buttonForgotPassword->setGeometry(QRect(630, 370, 111, 21));
        buttonForgotPassword->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: transparent;\n"
"font: 700 10pt \"Segoe UI\";\n"
"border : none;\n"
"border-color: transparent;"));
        checkBoxPassword = new QCheckBox(login);
        checkBoxPassword->setObjectName("checkBoxPassword");
        checkBoxPassword->setGeometry(QRect(810, 290, 111, 31));
        checkBoxPassword->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"color: rgb(0, 0, 0);"));
        labelBlob = new QLabel(login);
        labelBlob->setObjectName("labelBlob");
        labelBlob->setGeometry(QRect(320, 10, 691, 661));
        labelBlob->setStyleSheet(QString::fromUtf8("background: transparent;"));
        lineEditPassword = new QLineEdit(login);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(580, 280, 211, 41));
        lineEditPassword->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"font: 600 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);\n"
"border: 2px solid rgb(0, 0, 0);\n"
"border-radius : 10px;"));
        lineEditUsername = new QLineEdit(login);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setGeometry(QRect(580, 220, 211, 41));
        lineEditUsername->setStyleSheet(QString::fromUtf8("background-color: transparent;\n"
"font: 600 12pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);\n"
"border: 2px solid rgb(0, 0, 0);\n"
"border-radius : 10px;"));
        buttonSignup = new QPushButton(login);
        buttonSignup->setObjectName("buttonSignup");
        buttonSignup->setGeometry(QRect(610, 420, 161, 31));
        buttonSignup->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(101, 101, 152);\n"
"font: 700 14pt \"Segoe UI\";\n"
"border: 2px solid rgb(0, 0, 0);\n"
"border-radius : 8px;"));
        labelTitle = new QLabel(login);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(320, 120, 731, 81));
        labelTitle->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 700 48pt \"Segoe UI\";\n"
"background-color: transparent;"));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelIcon = new QLabel(login);
        labelIcon->setObjectName("labelIcon");
        labelIcon->setGeometry(QRect(829, 40, 350, 350));
        labelIcon->setStyleSheet(QString::fromUtf8("background: transparent;\n"
""));
        labelIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/icon.png")));
        buttonLogin = new QPushButton(login);
        buttonLogin->setObjectName("buttonLogin");
        buttonLogin->setGeometry(QRect(610, 340, 161, 31));
        buttonLogin->setStyleSheet(QString::fromUtf8(";\n"
"background-color: rgb(63, 129, 87);\n"
"font: 700 14pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);\n"
"border: 2px solid rgb(0, 0, 0);\n"
"border-radius : 8px;"));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "BudgetBuddy - Login", nullptr));
        labelOr->setText(QCoreApplication::translate("login", "    Not Registered?", nullptr));
        buttonForgotPassword->setText(QCoreApplication::translate("login", " Forgot Password?", nullptr));
        checkBoxPassword->setText(QCoreApplication::translate("login", "Show Password", nullptr));
        labelBlob->setText(QString());
        lineEditPassword->setPlaceholderText(QCoreApplication::translate("login", "Password", nullptr));
        lineEditUsername->setPlaceholderText(QCoreApplication::translate("login", "Username", nullptr));
        buttonSignup->setText(QCoreApplication::translate("login", "SIGN UP", nullptr));
        labelTitle->setText(QCoreApplication::translate("login", "BUDGETBUDDY", nullptr));
        labelIcon->setText(QString());
        buttonLogin->setText(QCoreApplication::translate("login", "LOG IN", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
