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

    // ✅ Use singleton instance
    QString userName = DatabaseManager::instance().getUserNameById(currentUserId);
    ui->labelWelcome->setText("Welcome, " + userName);

    QString photoPath = DatabaseManager::instance().getUserPhotoPath(currentUserId);
    if (!photoPath.isEmpty() && QFile::exists(photoPath)) {
        QPixmap pix(photoPath);
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

    // Make sure photo directory exists
    QString destDir = QCoreApplication::applicationDirPath() + "/user_photos";
    QDir().mkpath(destDir);

    // Properly declare QFileInfo and get the filename
    QFileInfo info(filePath);
    QString name = info.fileName();
    QString destPath = destDir + "/" + name;

    if (QFile::exists(destPath))
        QFile::remove(destPath);

    QFile::copy(filePath, destPath);

    // Save path in DB
    if (DatabaseManager::instance().updateUserPhotoPath(currentUserId, destPath)) {
        QPixmap pix(destPath);
        ui->labelPhoto->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QMessageBox::information(this, "Success", "Profile photo updated!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save photo to database.");
    }
}
