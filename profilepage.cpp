#include "profilepage.h"
#include "ui_profilepage.h"
#include <QMessageBox>
#include <qlineedit.h>
#include "databasemanager.h"
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>
#include "changepassword.h"


profilepage::profilepage(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profilepage),
    currentUserId(userId)
{
    ui->setupUi(this);

    // ✅ Use singleton instance
    QString userName = DatabaseManager::instance().getUserNameById(currentUserId);
    ui->labelWelcome->setText("Welcome, " + userName);
}

profilepage::~profilepage()
{
    delete ui;
}

void profilepage::on_buttonChangePassword_clicked()
{
    ChangePassword dlg(currentUserId, this);
    dlg.exec();  // The dialog runs its own checks and stays open on fail
}

void profilepage::on_buttonLogout_clicked()
{
    emit logoutRequested();  // Tell parent you want to logout
    this->close();
}


