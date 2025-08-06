/********************************************************************************
** Form generated from reading UI file 'homepage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOMEPAGE_H
#define UI_HOMEPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_homepage
{
public:
    QFrame *frame;
    QLabel *labelWelcome;
    QPushButton *buttonAddTransaction;
    QPushButton *buttonViewTransaction;
    QPushButton *buttonSetGoal;
    QPushButton *buttonAnalyzeReport;
    QPushButton *buttonProfile;
    QPushButton *buttonLogout;
    QLabel *labelIcon;

    void setupUi(QDialog *homepage)
    {
        if (homepage->objectName().isEmpty())
            homepage->setObjectName("homepage");
        homepage->resize(1080, 720);
        homepage->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 219, 194);"));
        frame = new QFrame(homepage);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(320, 90, 691, 461));
        frame->setAutoFillBackground(false);
        frame->setStyleSheet(QString::fromUtf8("\n"
"border: 2px solid rgb(0,0,0);\n"
"background-color: #FFFFF0;"));
        frame->setFrameShape(QFrame::Shape::StyledPanel);
        frame->setFrameShadow(QFrame::Shadow::Raised);
        labelWelcome = new QLabel(frame);
        labelWelcome->setObjectName("labelWelcome");
        labelWelcome->setGeometry(QRect(0, 0, 831, 81));
        labelWelcome->setStyleSheet(QString::fromUtf8("font: 700 32pt \"Segoe UI\";\n"
"background-color: transparent;\n"
"color: rgb(0, 0, 0);"));
        buttonAddTransaction = new QPushButton(frame);
        buttonAddTransaction->setObjectName("buttonAddTransaction");
        buttonAddTransaction->setGeometry(QRect(160, 110, 361, 71));
        buttonAddTransaction->setStyleSheet(QString::fromUtf8("\n"
"background-color: #FFFFF0;\n"
"border: 2px solid rgb(0,0,0);\n"
"border-radius : 20px;\n"
"font: 600 18pt \"Segoe UI\";\n"
"color:rgb(0, 0, 0)"));
        buttonViewTransaction = new QPushButton(frame);
        buttonViewTransaction->setObjectName("buttonViewTransaction");
        buttonViewTransaction->setGeometry(QRect(160, 190, 361, 71));
        buttonViewTransaction->setStyleSheet(QString::fromUtf8("\n"
"background-color: #FFFFF0;\n"
"border: 2px solid rgb(0,0,0);\n"
"border-radius : 20px;\n"
"font: 600 18pt \"Segoe UI\";\n"
"color:rgb(0, 0, 0)"));
        buttonSetGoal = new QPushButton(frame);
        buttonSetGoal->setObjectName("buttonSetGoal");
        buttonSetGoal->setGeometry(QRect(160, 270, 361, 71));
        buttonSetGoal->setStyleSheet(QString::fromUtf8("\n"
"background-color: #FFFFF0;\n"
"border: 2px solid rgb(0,0,0);\n"
"border-radius : 20px;\n"
"font: 600 18pt \"Segoe UI\";\n"
"color:rgb(0, 0, 0)"));
        buttonAnalyzeReport = new QPushButton(frame);
        buttonAnalyzeReport->setObjectName("buttonAnalyzeReport");
        buttonAnalyzeReport->setGeometry(QRect(160, 350, 361, 71));
        buttonAnalyzeReport->setStyleSheet(QString::fromUtf8("\n"
"background-color: #FFFFF0;\n"
"border: 2px solid rgb(0,0,0);\n"
"border-radius : 20px;\n"
"font: 600 18pt \"Segoe UI\";\n"
"color:rgb(0, 0, 0)"));
        buttonProfile = new QPushButton(homepage);
        buttonProfile->setObjectName("buttonProfile");
        buttonProfile->setGeometry(QRect(900, 50, 111, 31));
        buttonProfile->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(184, 184, 184);\n"
"font: 700 15pt \"Segoe UI\";\n"
"border: 2px solid rgb(0, 0, 0);\n"
"border-radius : 6px;"));
        buttonLogout = new QPushButton(homepage);
        buttonLogout->setObjectName("buttonLogout");
        buttonLogout->setGeometry(QRect(900, 560, 111, 31));
        buttonLogout->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"background-color: rgb(184, 184, 184);\n"
"font: 700 15pt \"Segoe UI\";\n"
"border: 2px solid rgb(0, 0, 0);\n"
"border-radius : 6px;"));
        labelIcon = new QLabel(homepage);
        labelIcon->setObjectName("labelIcon");
        labelIcon->setGeometry(QRect(-100, -30, 315, 315));
        labelIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/icon.png")));

        retranslateUi(homepage);

        QMetaObject::connectSlotsByName(homepage);
    } // setupUi

    void retranslateUi(QDialog *homepage)
    {
        homepage->setWindowTitle(QCoreApplication::translate("homepage", "BudgetBuddy - Home", nullptr));
        labelWelcome->setText(QCoreApplication::translate("homepage", "      Welcome, [USER] ", nullptr));
        buttonAddTransaction->setText(QCoreApplication::translate("homepage", "Add Transactions", nullptr));
        buttonViewTransaction->setText(QCoreApplication::translate("homepage", "View Transactions", nullptr));
        buttonSetGoal->setText(QCoreApplication::translate("homepage", "Set Monthly Goals", nullptr));
        buttonAnalyzeReport->setText(QCoreApplication::translate("homepage", "Analyze Report", nullptr));
        buttonProfile->setText(QCoreApplication::translate("homepage", "PROFILE", nullptr));
        buttonLogout->setText(QCoreApplication::translate("homepage", "LOGOUT", nullptr));
        labelIcon->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class homepage: public Ui_homepage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOMEPAGE_H
