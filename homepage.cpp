#include "homepage.h"
#include "ui_homepage.h"
#include "transactions.h"
#include "monthlygoals.h"
#include "viewtransactions.h"
#include "analyzereport.h"
#include <QMessageBox>

homepage::homepage(int userId, QWidget *parent)
    : QDialog(parent),
    ui(new Ui::homepage),
    currentUserId(userId)
{
    ui->setupUi(this);
}

homepage::~homepage()
{
    delete ui;
}

void homepage::on_buttonAddTransaction_clicked()
{
    transactions *txnWindow = new transactions(this, currentUserId);
    txnWindow->exec();
}

void homepage::on_buttonViewTransaction_clicked()
{
    viewtransactions *vt = new viewtransactions(this, currentUserId);
    vt->exec();
}

void homepage::on_buttonSetGoal_clicked()
{
    monthlygoals *goalWindow = new monthlygoals(currentUserId, this);
    goalWindow->exec();
}

void homepage::on_buttonAnalyzeReport_clicked()
{
    analyzereport *report = new analyzereport(currentUserId, this);
    report->exec();
}
