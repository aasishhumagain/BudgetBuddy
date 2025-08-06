/********************************************************************************
** Form generated from reading UI file 'profilepage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROFILEPAGE_H
#define UI_PROFILEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_profilepage
{
public:
    QLabel *labelWelcome;
    QLabel *labelPhoto;
    QPushButton *buttonChangePhoto;
    QPushButton *buttonChangePassword;
    QPushButton *buttonBack;

    void setupUi(QDialog *profilepage)
    {
        if (profilepage->objectName().isEmpty())
            profilepage->setObjectName("profilepage");
        profilepage->resize(1282, 650);
        profilepage->setStyleSheet(QString::fromUtf8("\n"
"    background-color: rgb(202, 219, 194);\n"
"   "));
        labelWelcome = new QLabel(profilepage);
        labelWelcome->setObjectName("labelWelcome");
        labelWelcome->setGeometry(QRect(370, 60, 600, 61));
        labelWelcome->setStyleSheet(QString::fromUtf8("\n"
"font: 700 40pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"    "));
        labelWelcome->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelPhoto = new QLabel(profilepage);
        labelPhoto->setObjectName("labelPhoto");
        labelPhoto->setGeometry(QRect(560, 140, 200, 200));
        labelPhoto->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 10pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"     background: white;\n"
"     border: 2px solid black;\n"
"     border-radius: 10px;\n"
"    "));
        labelPhoto->setAlignment(Qt::AlignmentFlag::AlignCenter);
        buttonChangePhoto = new QPushButton(profilepage);
        buttonChangePhoto->setObjectName("buttonChangePhoto");
        buttonChangePhoto->setGeometry(QRect(560, 360, 200, 40));
        buttonChangePhoto->setStyleSheet(QString::fromUtf8("font: 600 14pt \"Segoe UI\";\n"
"background-color: #FFFFF0;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"    "));
        buttonChangePassword = new QPushButton(profilepage);
        buttonChangePassword->setObjectName("buttonChangePassword");
        buttonChangePassword->setGeometry(QRect(560, 420, 200, 40));
        buttonChangePassword->setStyleSheet(QString::fromUtf8("font: 600 14pt \"Segoe UI\";\n"
"background-color: #FFFFF0;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"    "));
        buttonBack = new QPushButton(profilepage);
        buttonBack->setObjectName("buttonBack");
        buttonBack->setGeometry(QRect(560, 480, 200, 40));
        buttonBack->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 14pt \"Segoe UI\";\n"
"background-color: rgb(184, 184, 184);\n"
"   color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"    "));

        retranslateUi(profilepage);

        QMetaObject::connectSlotsByName(profilepage);
    } // setupUi

    void retranslateUi(QDialog *profilepage)
    {
        profilepage->setWindowTitle(QCoreApplication::translate("profilepage", "BudgetBuddy - Profile", nullptr));
        labelWelcome->setText(QCoreApplication::translate("profilepage", "Welcome!", nullptr));
        labelPhoto->setText(QCoreApplication::translate("profilepage", "[Photo]", nullptr));
        buttonChangePhoto->setText(QCoreApplication::translate("profilepage", "Change Photo", nullptr));
        buttonChangePassword->setText(QCoreApplication::translate("profilepage", "    Change Password", nullptr));
        buttonBack->setText(QCoreApplication::translate("profilepage", "Back to Homepage", nullptr));
    } // retranslateUi

};

namespace Ui {
    class profilepage: public Ui_profilepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROFILEPAGE_H
