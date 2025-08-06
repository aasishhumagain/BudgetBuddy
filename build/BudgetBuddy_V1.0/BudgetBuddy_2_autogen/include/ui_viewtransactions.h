/********************************************************************************
** Form generated from reading UI file 'viewtransactions.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEWTRANSACTIONS_H
#define UI_VIEWTRANSACTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>

QT_BEGIN_NAMESPACE

class Ui_viewtransactions
{
public:
    QLabel *labelTitle;
    QLabel *labelType;
    QComboBox *comboBoxTypeFilter;
    QLabel *labelCategory;
    QComboBox *comboBoxCategoryFilter;
    QLabel *labelFrom;
    QDateEdit *dateEditFrom;
    QLabel *labelTo;
    QDateEdit *dateEditTo;
    QPushButton *buttonApplyFilter;
    QPushButton *buttonClearFilter;
    QPushButton *buttonExport;
    QTableWidget *tableWidgetTransactions;
    QPushButton *buttonBack;

    void setupUi(QDialog *viewtransactions)
    {
        if (viewtransactions->objectName().isEmpty())
            viewtransactions->setObjectName("viewtransactions");
        viewtransactions->resize(1282, 650);
        viewtransactions->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 219, 194);"));
        labelTitle = new QLabel(viewtransactions);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(390, 19, 611, 61));
        labelTitle->setStyleSheet(QString::fromUtf8("font: 700 35pt \"Segoe UI\"; color: black;"));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelType = new QLabel(viewtransactions);
        labelType->setObjectName("labelType");
        labelType->setGeometry(QRect(300, 100, 80, 25));
        labelType->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        comboBoxTypeFilter = new QComboBox(viewtransactions);
        comboBoxTypeFilter->setObjectName("comboBoxTypeFilter");
        comboBoxTypeFilter->setGeometry(QRect(400, 100, 150, 35));
        comboBoxTypeFilter->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; background: white; color: black; border: 2px solid black; border-radius: 6px;"));
        labelCategory = new QLabel(viewtransactions);
        labelCategory->setObjectName("labelCategory");
        labelCategory->setGeometry(QRect(670, 100, 91, 25));
        labelCategory->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        comboBoxCategoryFilter = new QComboBox(viewtransactions);
        comboBoxCategoryFilter->setObjectName("comboBoxCategoryFilter");
        comboBoxCategoryFilter->setGeometry(QRect(770, 100, 150, 35));
        comboBoxCategoryFilter->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; background: white; color: black; border: 2px solid black; border-radius: 6px;"));
        labelFrom = new QLabel(viewtransactions);
        labelFrom->setObjectName("labelFrom");
        labelFrom->setGeometry(QRect(300, 160, 80, 25));
        labelFrom->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        dateEditFrom = new QDateEdit(viewtransactions);
        dateEditFrom->setObjectName("dateEditFrom");
        dateEditFrom->setGeometry(QRect(400, 160, 150, 35));
        dateEditFrom->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; background: white; color: black; border: 2px solid black; border-radius: 6px;"));
        labelTo = new QLabel(viewtransactions);
        labelTo->setObjectName("labelTo");
        labelTo->setGeometry(QRect(670, 160, 80, 25));
        labelTo->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        dateEditTo = new QDateEdit(viewtransactions);
        dateEditTo->setObjectName("dateEditTo");
        dateEditTo->setGeometry(QRect(770, 160, 150, 35));
        dateEditTo->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; background: white; color: black; border: 2px solid black; border-radius: 6px;"));
        buttonApplyFilter = new QPushButton(viewtransactions);
        buttonApplyFilter->setObjectName("buttonApplyFilter");
        buttonApplyFilter->setGeometry(QRect(560, 220, 191, 40));
        buttonApplyFilter->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; background-color: #FFFFF0; color: black; border: 2px solid black; border-radius: 6px;"));
        buttonClearFilter = new QPushButton(viewtransactions);
        buttonClearFilter->setObjectName("buttonClearFilter");
        buttonClearFilter->setGeometry(QRect(920, 220, 191, 40));
        buttonClearFilter->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; background-color: #FFFFF0; color: black; border: 2px solid black; border-radius: 6px;"));
        buttonExport = new QPushButton(viewtransactions);
        buttonExport->setObjectName("buttonExport");
        buttonExport->setGeometry(QRect(190, 220, 191, 40));
        buttonExport->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; background-color: #FFFFF0; color: black; border: 2px solid black; border-radius: 6px;"));
        tableWidgetTransactions = new QTableWidget(viewtransactions);
        tableWidgetTransactions->setObjectName("tableWidgetTransactions");
        tableWidgetTransactions->setGeometry(QRect(190, 270, 920, 261));
        tableWidgetTransactions->setStyleSheet(QString::fromUtf8("\n"
"     QTableWidget {\n"
"       background-color: white;\n"
"       color: black;\n"
"       font: 12pt \"Segoe UI\";\n"
"     }\n"
"     QHeaderView::section {\n"
"       background-color: #dcdcdc;\n"
"       font-weight: bold;\n"
"       border: 1px solid black;\n"
"     }\n"
"     QTableWidget::item {\n"
"       padding: 5px;\n"
"     }\n"
"    "));
        buttonBack = new QPushButton(viewtransactions);
        buttonBack->setObjectName("buttonBack");
        buttonBack->setGeometry(QRect(550, 550, 221, 40));
        buttonBack->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Segoe UI\";background-color: rgb(184, 184, 184);; color: black; border: 2px solid black; border-radius: 6px;"));

        retranslateUi(viewtransactions);

        QMetaObject::connectSlotsByName(viewtransactions);
    } // setupUi

    void retranslateUi(QDialog *viewtransactions)
    {
        viewtransactions->setWindowTitle(QCoreApplication::translate("viewtransactions", "BudgetBuddy - View Transactions", nullptr));
        labelTitle->setText(QCoreApplication::translate("viewtransactions", "YOUR TRANSACTIONS", nullptr));
        labelType->setText(QCoreApplication::translate("viewtransactions", "Type:", nullptr));
        labelCategory->setText(QCoreApplication::translate("viewtransactions", "Category:", nullptr));
        labelFrom->setText(QCoreApplication::translate("viewtransactions", "From:", nullptr));
        labelTo->setText(QCoreApplication::translate("viewtransactions", "To:", nullptr));
        buttonApplyFilter->setText(QCoreApplication::translate("viewtransactions", "Apply Filter", nullptr));
        buttonClearFilter->setText(QCoreApplication::translate("viewtransactions", "Clear Filter", nullptr));
        buttonExport->setText(QCoreApplication::translate("viewtransactions", "Export Transactions", nullptr));
        buttonBack->setText(QCoreApplication::translate("viewtransactions", "BACK TO HOMEPAGE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class viewtransactions: public Ui_viewtransactions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEWTRANSACTIONS_H
