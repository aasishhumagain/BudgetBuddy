#include "homepage.h"
#include "ui_homepage.h"
#include <QMessageBox>
#include "transactions.h"

homepage::homepage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::homepage)
{
    ui->setupUi(this);
}

homepage::~homepage()
{
    delete ui;
}

void homepage::on_buttonAddTransaction_clicked()
{
    transactions *txnWindow = new transactions(this);
    txnWindow->exec();
}

void homepage::on_buttonViewTransaction_clicked()
{
    QMessageBox::information(this, "Info", "View Transactions clicked!");
}

void homepage::on_buttonSetGoal_clicked()
{
    QMessageBox::information(this, "Info", "Set Monthly Goal clicked!");
}

void homepage::on_buttonAnalyzeReport_clicked()
{
    QMessageBox::information(this, "Info", "Analyze Report clicked!");
}
