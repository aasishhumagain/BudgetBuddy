#include "homepage.h"
#include "ui_homepage.h"
#include "transactions.h"
#include "monthlygoals.h"
#include "viewtransactions.h"
#include "analyzereport.h"
#include "profilepage.h"
#include <QMessageBox>
#include "profilepage.h"
#include "login.h"


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

void homepage::on_buttonProfile_clicked()
{
    profilepage *profile = new profilepage(currentUserId, this);
    connect(profile, &profilepage::logoutRequested, this, &homepage::handleLogout);
    profile->exec();
}


void homepage::handleLogout()
{
    this->close();  // Close homepage
    // Maybe reopen login
    // Example:
    login *loginPage = new login();
    loginPage->show();
}
