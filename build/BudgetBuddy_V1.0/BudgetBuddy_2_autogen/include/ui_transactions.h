/********************************************************************************
** Form generated from reading UI file 'transactions.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRANSACTIONS_H
#define UI_TRANSACTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_transactions
{
public:
    QLabel *labelTitle;
    QLabel *labelAmount;
    QLineEdit *lineEditAmount;
    QLabel *labelCategory;
    QComboBox *comboBoxCategory;
    QLabel *labelType;
    QComboBox *comboBoxType;
    QLabel *labelDate;
    QDateEdit *dateEdit;
    QLabel *labelRemarks;
    QLineEdit *lineEditRemarks;
    QPushButton *buttonSubmit;
    QPushButton *buttonBack;

    void setupUi(QDialog *transactions)
    {
        if (transactions->objectName().isEmpty())
            transactions->setObjectName("transactions");
        transactions->resize(1080, 720);
        transactions->setStyleSheet(QString::fromUtf8("\n"
"    background-color: rgb(202, 219, 194);\n"
"   "));
        labelTitle = new QLabel(transactions);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(410, 50, 541, 81));
        labelTitle->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 35pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelAmount = new QLabel(transactions);
        labelAmount->setObjectName("labelAmount");
        labelAmount->setGeometry(QRect(450, 140, 111, 31));
        labelAmount->setStyleSheet(QString::fromUtf8("\n"
"font: 600 16pt \"Segoe UI\";\n"
"color: rgb(0, 0, 0);"));
        lineEditAmount = new QLineEdit(transactions);
        lineEditAmount->setObjectName("lineEditAmount");
        lineEditAmount->setGeometry(QRect(560, 134, 251, 51));
        lineEditAmount->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"     padding-left: 8px;\n"
"   "));
        lineEditAmount->setInputMethodHints(Qt::InputMethodHint::ImhPreferNumbers);
        labelCategory = new QLabel(transactions);
        labelCategory->setObjectName("labelCategory");
        labelCategory->setGeometry(QRect(450, 190, 111, 41));
        labelCategory->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        comboBoxCategory = new QComboBox(transactions);
        comboBoxCategory->setObjectName("comboBoxCategory");
        comboBoxCategory->setGeometry(QRect(560, 200, 251, 51));
        comboBoxCategory->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"        border-radius: 6px;\n"
"  border: 2px solid black;\n"
"     "));
        labelType = new QLabel(transactions);
        labelType->setObjectName("labelType");
        labelType->setGeometry(QRect(450, 254, 111, 41));
        labelType->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        comboBoxType = new QComboBox(transactions);
        comboBoxType->setObjectName("comboBoxType");
        comboBoxType->setGeometry(QRect(560, 266, 251, 51));
        comboBoxType->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;"));
        labelDate = new QLabel(transactions);
        labelDate->setObjectName("labelDate");
        labelDate->setGeometry(QRect(450, 330, 131, 41));
        labelDate->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        dateEdit = new QDateEdit(transactions);
        dateEdit->setObjectName("dateEdit");
        dateEdit->setGeometry(QRect(560, 330, 251, 51));
        dateEdit->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"  border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));
        labelRemarks = new QLabel(transactions);
        labelRemarks->setObjectName("labelRemarks");
        labelRemarks->setGeometry(QRect(450, 394, 111, 41));
        labelRemarks->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 16pt \"Segoe UI\";\n"
"     color: rgb(0, 0, 0);\n"
"   "));
        lineEditRemarks = new QLineEdit(transactions);
        lineEditRemarks->setObjectName("lineEditRemarks");
        lineEditRemarks->setGeometry(QRect(560, 396, 252, 51));
        lineEditRemarks->setStyleSheet(QString::fromUtf8("\n"
"     font: 600 11pt \"Segoe UI\";\n"
"     background: white;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"     padding-left: 8px;\n"
"   "));
        buttonSubmit = new QPushButton(transactions);
        buttonSubmit->setObjectName("buttonSubmit");
        buttonSubmit->setGeometry(QRect(560, 470, 251, 51));
        buttonSubmit->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 18pt \"Segoe UI\";\n"
"\n"
"background-color: #FFFFF0;\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));
        buttonBack = new QPushButton(transactions);
        buttonBack->setObjectName("buttonBack");
        buttonBack->setGeometry(QRect(560, 540, 251, 51));
        buttonBack->setStyleSheet(QString::fromUtf8("\n"
"     font: 700 18pt \"Segoe UI\";\n"
"\n"
"background-color: rgb(184, 184, 184);\n"
"     color: rgb(0, 0, 0);\n"
"     border: 2px solid black;\n"
"     border-radius: 6px;\n"
"   "));

        retranslateUi(transactions);

        QMetaObject::connectSlotsByName(transactions);
    } // setupUi

    void retranslateUi(QDialog *transactions)
    {
        transactions->setWindowTitle(QCoreApplication::translate("transactions", "BudgetBuddy -  Add Transaction", nullptr));
        labelTitle->setText(QCoreApplication::translate("transactions", "ADD TRANSACTIONS", nullptr));
        labelAmount->setText(QCoreApplication::translate("transactions", "Amount:", nullptr));
        lineEditAmount->setPlaceholderText(QCoreApplication::translate("transactions", "Enter amount", nullptr));
        labelCategory->setText(QCoreApplication::translate("transactions", "Category:", nullptr));
        labelType->setText(QCoreApplication::translate("transactions", "Type:", nullptr));
        labelDate->setText(QCoreApplication::translate("transactions", "Date:", nullptr));
        labelRemarks->setText(QCoreApplication::translate("transactions", "Remarks:", nullptr));
        lineEditRemarks->setPlaceholderText(QCoreApplication::translate("transactions", "Optional", nullptr));
        buttonSubmit->setText(QCoreApplication::translate("transactions", "SUBMIT", nullptr));
        buttonBack->setText(QCoreApplication::translate("transactions", "BACK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class transactions: public Ui_transactions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRANSACTIONS_H
