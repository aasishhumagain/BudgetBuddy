#include <QApplication>
#include "databasemanager.h"
#include "login.h"


int main(int argc, char *argv[])

{
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);


    QApplication a(argc, argv);

    if (!DatabaseManager::instance().openDatabase()) {
        qDebug() << "Database failed to open!";
        return -1;
    }

    login loginWindow;
    loginWindow.show();

    return a.exec();
}
