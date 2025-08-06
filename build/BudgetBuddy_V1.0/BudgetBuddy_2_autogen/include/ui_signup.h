/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_signup
{
public:
    QLabel *labelTitle;
    QLabel *labelUsername;
    QLineEdit *lineEditUsername;
    QLabel *labelPassword;
    QLineEdit *lineEditPassword;
    QCheckBox *checkBoxShowPassword;
    QLabel *labelConfirmPwd;
    QLineEdit *lineEditConfirmPwd;
    QPushButton *buttonCreateAccount;

    void setupUi(QDialog *signup)
    {
        if (signup->objectName().isEmpty())
            signup->setObjectName("signup");
        signup->resize(1080, 720);
        signup->setStyleSheet(QString::fromUtf8("\n"
"    background-color: rgb(202, 219, 194);\n"
"   "));
        labelTitle = new QLabel(signup);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(480, 130, 431, 40));
        labelTitle->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 35pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"    "));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelUsername = new QLabel(signup);
        labelUsername->setObjectName("labelUsername");
        labelUsername->setGeometry(QRect(480, 230, 100, 25));
        labelUsername->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"    "));
        lineEditUsername = new QLineEdit(signup);
        lineEditUsername->setObjectName("lineEditUsername");
        lineEditUsername->setGeometry(QRect(620, 230, 200, 35));
        lineEditUsername->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"     background: white;\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"     padding-left: 8px;\n"
"    "));
        labelPassword = new QLabel(signup);
        labelPassword->setObjectName("labelPassword");
        labelPassword->setGeometry(QRect(480, 280, 100, 25));
        labelPassword->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"    "));
        lineEditPassword = new QLineEdit(signup);
        lineEditPassword->setObjectName("lineEditPassword");
        lineEditPassword->setGeometry(QRect(620, 280, 200, 35));
        lineEditPassword->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"     background: white;\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"     padding-left: 8px;\n"
"    "));
        lineEditPassword->setEchoMode(QLineEdit::EchoMode::Password);
        checkBoxShowPassword = new QCheckBox(signup);
        checkBoxShowPassword->setObjectName("checkBoxShowPassword");
        checkBoxShowPassword->setGeometry(QRect(840, 280, 151, 31));
        checkBoxShowPassword->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 10pt \"Segoe UI\";\n"
"     color: black;\n"
"    "));
        labelConfirmPwd = new QLabel(signup);
        labelConfirmPwd->setObjectName("labelConfirmPwd");
        labelConfirmPwd->setGeometry(QRect(419, 330, 201, 25));
        labelConfirmPwd->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"    "));
        lineEditConfirmPwd = new QLineEdit(signup);
        lineEditConfirmPwd->setObjectName("lineEditConfirmPwd");
        lineEditConfirmPwd->setGeometry(QRect(620, 330, 200, 35));
        lineEditConfirmPwd->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"     background: white;\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"     padding-left: 8px;\n"
"    "));
        lineEditConfirmPwd->setEchoMode(QLineEdit::EchoMode::Password);
        buttonCreateAccount = new QPushButton(signup);
        buttonCreateAccount->setObjectName("buttonCreateAccount");
        buttonCreateAccount->setGeometry(QRect(620, 400, 200, 45));
        buttonCreateAccount->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"\n"
"background-color: rgb(147, 147, 147);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));

        retranslateUi(signup);

        QMetaObject::connectSlotsByName(signup);
    } // setupUi

    void retranslateUi(QDialog *signup)
    {
        signup->setWindowTitle(QCoreApplication::translate("signup", "BudgetBuddy - Signup", nullptr));
        labelTitle->setText(QCoreApplication::translate("signup", "Create an Account", nullptr));
        labelUsername->setText(QCoreApplication::translate("signup", "Username:", nullptr));
        lineEditUsername->setPlaceholderText(QCoreApplication::translate("signup", "Enter username", nullptr));
        labelPassword->setText(QCoreApplication::translate("signup", "Password:", nullptr));
        lineEditPassword->setPlaceholderText(QCoreApplication::translate("signup", "Enter password", nullptr));
        checkBoxShowPassword->setText(QCoreApplication::translate("signup", "Show password", nullptr));
        labelConfirmPwd->setText(QCoreApplication::translate("signup", "Confirm Password:", nullptr));
        lineEditConfirmPwd->setPlaceholderText(QCoreApplication::translate("signup", "Re-enter password", nullptr));
        buttonCreateAccount->setText(QCoreApplication::translate("signup", "SIGN UP", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signup: public Ui_signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
