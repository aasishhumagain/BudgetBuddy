/********************************************************************************
** Form generated from reading UI file 'monthlygoals.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MONTHLYGOALS_H
#define UI_MONTHLYGOALS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_monthlygoals
{
public:
    QLabel *labelTitle;
    QLabel *labelMonth;
    QComboBox *comboBoxMonth;
    QLabel *labelYear;
    QSpinBox *spinBoxYear;
    QLabel *label;
    QLineEdit *lineEditAmount;
    QPushButton *buttonSubmit;
    QPushButton *buttonBack;

    void setupUi(QDialog *monthlygoals)
    {
        if (monthlygoals->objectName().isEmpty())
            monthlygoals->setObjectName("monthlygoals");
        monthlygoals->resize(1080, 720);
        monthlygoals->setStyleSheet(QString::fromUtf8("\n"
"    background-color: rgb(202, 219, 194);\n"
"   "));
        labelTitle = new QLabel(monthlygoals);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(370, 80, 631, 61));
        labelTitle->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 35pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelMonth = new QLabel(monthlygoals);
        labelMonth->setObjectName("labelMonth");
        labelMonth->setGeometry(QRect(460, 180, 120, 30));
        labelMonth->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 14pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        comboBoxMonth = new QComboBox(monthlygoals);
        comboBoxMonth->setObjectName("comboBoxMonth");
        comboBoxMonth->setGeometry(QRect(600, 180, 200, 35));
        comboBoxMonth->setStyleSheet(QString::fromUtf8("\n"
"\n"
"     font: 600 12pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));
        labelYear = new QLabel(monthlygoals);
        labelYear->setObjectName("labelYear");
        labelYear->setGeometry(QRect(460, 240, 120, 30));
        labelYear->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 14pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        spinBoxYear = new QSpinBox(monthlygoals);
        spinBoxYear->setObjectName("spinBoxYear");
        spinBoxYear->setGeometry(QRect(600, 240, 200, 35));
        spinBoxYear->setStyleSheet(QString::fromUtf8("\n"
"\n"
"     font: 600 12pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));
        spinBoxYear->setMinimum(2000);
        spinBoxYear->setMaximum(2030);
        label = new QLabel(monthlygoals);
        label->setObjectName("label");
        label->setGeometry(QRect(460, 300, 120, 30));
        label->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 14pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        lineEditAmount = new QLineEdit(monthlygoals);
        lineEditAmount->setObjectName("lineEditAmount");
        lineEditAmount->setGeometry(QRect(600, 300, 200, 35));
        lineEditAmount->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"     padding-left: 8px;\n"
"   "));
        lineEditAmount->setInputMethodHints(Qt::InputMethodHint::ImhDigitsOnly);
        buttonSubmit = new QPushButton(monthlygoals);
        buttonSubmit->setObjectName("buttonSubmit");
        buttonSubmit->setGeometry(QRect(600, 380, 200, 40));
        buttonSubmit->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 14pt \"Segoe UI\";\n"
"\n"
"background-color: #FFFFF0;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));
        buttonBack = new QPushButton(monthlygoals);
        buttonBack->setObjectName("buttonBack");
        buttonBack->setGeometry(QRect(600, 450, 200, 40));
        buttonBack->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 14pt \"Segoe UI\";\n"
"\n"
"background-color: rgb(184, 184, 184);\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));

        retranslateUi(monthlygoals);

        QMetaObject::connectSlotsByName(monthlygoals);
    } // setupUi

    void retranslateUi(QDialog *monthlygoals)
    {
        monthlygoals->setWindowTitle(QCoreApplication::translate("monthlygoals", "BudgetBuddy - Monthly Goals", nullptr));
        labelTitle->setText(QCoreApplication::translate("monthlygoals", "Set Monthly Goals", nullptr));
        labelMonth->setText(QCoreApplication::translate("monthlygoals", "Select Month:", nullptr));
        labelYear->setText(QCoreApplication::translate("monthlygoals", "Select Year:", nullptr));
        label->setText(QCoreApplication::translate("monthlygoals", "Input Budget:", nullptr));
        lineEditAmount->setPlaceholderText(QCoreApplication::translate("monthlygoals", "Amount", nullptr));
        buttonSubmit->setText(QCoreApplication::translate("monthlygoals", "SUBMIT", nullptr));
        buttonBack->setText(QCoreApplication::translate("monthlygoals", "BACK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class monthlygoals: public Ui_monthlygoals {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MONTHLYGOALS_H
