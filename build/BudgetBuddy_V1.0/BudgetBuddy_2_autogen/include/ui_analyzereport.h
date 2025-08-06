/********************************************************************************
** Form generated from reading UI file 'analyzereport.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYZEREPORT_H
#define UI_ANALYZEREPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_analyzereport
{
public:
    QLabel *labelTitle;
    QLabel *labelChartType;
    QComboBox *comboBoxChartType;
    QLabel *labelFrom;
    QComboBox *comboBoxMonth;
    QPushButton *buttonApplyFilter;
    QPushButton *buttonClearFilter;
    QLabel *labelTotalIncome;
    QLabel *labelTotalExpenses;
    QLabel *labelTotalMonthlyGoal;
    QLabel *labelRemainingBudget;
    QLabel *labelNetBalance;
    QFrame *chartWidget;
    QLabel *labelHoverInfo;
    QLabel *labelWarnings;
    QPushButton *buttonBack;

    void setupUi(QDialog *analyzereport)
    {
        if (analyzereport->objectName().isEmpty())
            analyzereport->setObjectName("analyzereport");
        analyzereport->resize(1080, 720);
        analyzereport->setStyleSheet(QString::fromUtf8("background-color: rgb(202, 219, 194);"));
        labelTitle = new QLabel(analyzereport);
        labelTitle->setObjectName("labelTitle");
        labelTitle->setGeometry(QRect(420, 30, 521, 61));
        labelTitle->setStyleSheet(QString::fromUtf8("font: 700 35pt \"Segoe UI\"; color: black;"));
        labelTitle->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelChartType = new QLabel(analyzereport);
        labelChartType->setObjectName("labelChartType");
        labelChartType->setGeometry(QRect(550, 130, 91, 25));
        labelChartType->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        comboBoxChartType = new QComboBox(analyzereport);
        comboBoxChartType->setObjectName("comboBoxChartType");
        comboBoxChartType->setGeometry(QRect(650, 130, 150, 35));
        comboBoxChartType->setStyleSheet(QString::fromUtf8("font: 600 11pt \"Segoe UI\"; background: white; color: black; border: 2px solid black; border-radius: 5px;"));
        labelFrom = new QLabel(analyzereport);
        labelFrom->setObjectName("labelFrom");
        labelFrom->setGeometry(QRect(260, 130, 80, 25));
        labelFrom->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        comboBoxMonth = new QComboBox(analyzereport);
        comboBoxMonth->setObjectName("comboBoxMonth");
        comboBoxMonth->setGeometry(QRect(360, 130, 150, 35));
        comboBoxMonth->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; background: white; color: black; border: 2px solid black; border-radius: 6px;"));
        buttonApplyFilter = new QPushButton(analyzereport);
        buttonApplyFilter->setObjectName("buttonApplyFilter");
        buttonApplyFilter->setGeometry(QRect(820, 130, 150, 35));
        buttonApplyFilter->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; background-color: #FFFFF0; color: black; border: 2px solid black; border-radius: 6px;"));
        buttonClearFilter = new QPushButton(analyzereport);
        buttonClearFilter->setObjectName("buttonClearFilter");
        buttonClearFilter->setGeometry(QRect(990, 130, 150, 35));
        buttonClearFilter->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; background-color: #FFFFF0; color: black; border: 2px solid black; border-radius: 6px;"));
        labelTotalIncome = new QLabel(analyzereport);
        labelTotalIncome->setObjectName("labelTotalIncome");
        labelTotalIncome->setGeometry(QRect(300, 180, 300, 30));
        labelTotalIncome->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        labelTotalExpenses = new QLabel(analyzereport);
        labelTotalExpenses->setObjectName("labelTotalExpenses");
        labelTotalExpenses->setGeometry(QRect(740, 180, 300, 30));
        labelTotalExpenses->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        labelTotalMonthlyGoal = new QLabel(analyzereport);
        labelTotalMonthlyGoal->setObjectName("labelTotalMonthlyGoal");
        labelTotalMonthlyGoal->setGeometry(QRect(300, 220, 300, 30));
        labelTotalMonthlyGoal->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        labelRemainingBudget = new QLabel(analyzereport);
        labelRemainingBudget->setObjectName("labelRemainingBudget");
        labelRemainingBudget->setGeometry(QRect(740, 220, 300, 30));
        labelRemainingBudget->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        labelNetBalance = new QLabel(analyzereport);
        labelNetBalance->setObjectName("labelNetBalance");
        labelNetBalance->setGeometry(QRect(240, 250, 591, 31));
        labelNetBalance->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: black;"));
        labelNetBalance->setAlignment(Qt::AlignmentFlag::AlignCenter);
        chartWidget = new QFrame(analyzereport);
        chartWidget->setObjectName("chartWidget");
        chartWidget->setGeometry(QRect(300, 290, 700, 251));
        chartWidget->setStyleSheet(QString::fromUtf8("background: white; border: 2px solid black;"));
        chartWidget->setFrameShape(QFrame::Shape::StyledPanel);
        chartWidget->setFrameShadow(QFrame::Shadow::Raised);
        labelHoverInfo = new QLabel(analyzereport);
        labelHoverInfo->setObjectName("labelHoverInfo");
        labelHoverInfo->setGeometry(QRect(360, 580, 360, 20));
        labelHoverInfo->setStyleSheet(QString::fromUtf8("font: 600 12pt \"Segoe UI\"; color: rgb(0, 85, 255);"));
        labelHoverInfo->setAlignment(Qt::AlignmentFlag::AlignCenter);
        labelWarnings = new QLabel(analyzereport);
        labelWarnings->setObjectName("labelWarnings");
        labelWarnings->setGeometry(QRect(550, 550, 200, 30));
        labelWarnings->setStyleSheet(QString::fromUtf8("font: 600 16pt \"Segoe UI\"; color: red;"));
        labelWarnings->setAlignment(Qt::AlignmentFlag::AlignCenter);
        buttonBack = new QPushButton(analyzereport);
        buttonBack->setObjectName("buttonBack");
        buttonBack->setGeometry(QRect(550, 590, 200, 40));
        buttonBack->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Segoe UI\"; color: black; border: 2px solid black; border-radius: 6px; background-color: rgb(184, 184, 184);"));

        retranslateUi(analyzereport);

        QMetaObject::connectSlotsByName(analyzereport);
    } // setupUi

    void retranslateUi(QDialog *analyzereport)
    {
        analyzereport->setWindowTitle(QCoreApplication::translate("analyzereport", "BudgetBuddy - Report Analysis", nullptr));
        labelTitle->setText(QCoreApplication::translate("analyzereport", "Your Report Analysis", nullptr));
        labelChartType->setText(QCoreApplication::translate("analyzereport", "Chart Type:", nullptr));
        labelFrom->setText(QCoreApplication::translate("analyzereport", "Month:", nullptr));
        buttonApplyFilter->setText(QCoreApplication::translate("analyzereport", "Apply Filter", nullptr));
        buttonClearFilter->setText(QCoreApplication::translate("analyzereport", "Clear Filter", nullptr));
        labelTotalIncome->setText(QCoreApplication::translate("analyzereport", "Total Income:", nullptr));
        labelTotalExpenses->setText(QCoreApplication::translate("analyzereport", "Total Expenses:", nullptr));
        labelTotalMonthlyGoal->setText(QCoreApplication::translate("analyzereport", "Total Monthly Goal:", nullptr));
        labelRemainingBudget->setText(QCoreApplication::translate("analyzereport", "Remaining Budget:", nullptr));
        labelNetBalance->setText(QCoreApplication::translate("analyzereport", "Income - Expenses:", nullptr));
        labelWarnings->setText(QCoreApplication::translate("analyzereport", "Status:", nullptr));
        buttonBack->setText(QCoreApplication::translate("analyzereport", "BACK TO HOMEPAGE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class analyzereport: public Ui_analyzereport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYZEREPORT_H
