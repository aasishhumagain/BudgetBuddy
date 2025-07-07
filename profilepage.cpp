#include "profilepage.h"
#include "ui_profilepage.h"
#include <QMessageBox>
#include <qlineedit.h>
#include "databasemanager.h"
#include <QInputDialog>
#include <QSqlQuery>
#include <QSqlError>
#include "changepassword.h"
#include <QFileDialog>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QPixmap>
#include <QCoreApplication>


profilepage::profilepage(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profilepage),
    currentUserId(userId)
{
    ui->setupUi(this);

    QByteArray imageData = DatabaseManager::instance().getUserPhoto(currentUserId);
    if (!imageData.isEmpty()) {
        QPixmap pix;
        pix.loadFromData(imageData);
        ui->labelPhoto->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        ui->labelPhoto->setText("No photo");
    }

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

void profilepage::on_buttonChangePhoto_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Profile Photo",
        QDir::homePath(),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );

    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file.");
        return;
    }

    QByteArray imageData = file.readAll();

    if (DatabaseManager::instance().updateUserPhoto(currentUserId, imageData)) {
        QPixmap pix;
        pix.loadFromData(imageData);
        ui->labelPhoto->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QMessageBox::information(this, "Success", "Profile photo updated!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save photo to database.");
    }
}
