#include "profilepage.h"
#include "ui_profilepage.h"
#include <QMessageBox>
#include <QLineEdit>
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
#include "login.h"

profilepage::profilepage(int userId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::profilepage),
    currentUserId(userId)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Window);
    this->setWindowState(Qt::WindowMaximized);

    QString userName = DatabaseManager::instance().getUserNameById(currentUserId);
    ui->labelWelcome->setText("Welcome, <b>" + userName.toUpper() + "!</b>");

    QByteArray imageData = DatabaseManager::instance().getUserPhoto(currentUserId);
    if (!imageData.isEmpty()) {
        QPixmap pix;
        pix.loadFromData(imageData);
        ui->labelPhoto->setPixmap(pix.scaled(ui->labelPhoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
    } else {
        ui->labelPhoto->setText("No photo");
    }

    connect(ui->buttonBack, &QPushButton::clicked, this, &profilepage::on_buttonBack_clicked);
}

profilepage::~profilepage()
{
    delete ui;
}

void profilepage::on_buttonBack_clicked()
{
    this->close();
}

void profilepage::on_buttonChangePassword_clicked()
{
    ChangePassword dlg(currentUserId, this);
    dlg.exec();
}

void profilepage::on_buttonLogout_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Logout",
        "Are you sure you want to logout?",
        QMessageBox::Yes | QMessageBox::Cancel
        );

    if (reply == QMessageBox::Yes) {
        this->close();

        login *loginPage = new login();
        loginPage->show();
    }
}

void profilepage::on_buttonChangePhoto_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Select Profile Photo",
        QDir::homePath(),
        "Images (*.png *.jpg *.jpeg *.bmp)"
        );

    if (filePath.isEmpty()) return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "Error", "Could not open file.");
        return;
    }

    QByteArray imageData = file.readAll();

    if (DatabaseManager::instance().updateUserPhoto(currentUserId, imageData)) {
        QPixmap pix;
        pix.loadFromData(imageData);
        ui->labelPhoto->setPixmap(pix.scaled(ui->labelPhoto->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        QMessageBox::information(this, "Success", "Profile photo updated!");
    } else {
        QMessageBox::warning(this, "Error", "Failed to save photo to database.");
    }
}
