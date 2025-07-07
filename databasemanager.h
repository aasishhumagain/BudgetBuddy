#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>

class DatabaseManager : public QObject
{
    Q_OBJECT

public:
    explicit DatabaseManager(QObject *parent = nullptr);
    ~DatabaseManager(); // ✅ Must be public

    static DatabaseManager& instance();

    QSqlDatabase getDatabase();
    bool openDatabase();
    void closeDatabase();

    QString getUserNameById(int userId); // ✅ Declare this!

    QString getUserPhotoPath(int userId);
    bool updateUserPhoto(int userId, const QByteArray &imageData);
    QByteArray getUserPhoto(int userId);


private:
    QSqlDatabase m_database;

    void initializeTables();
};

#endif // DATABASEMANAGER_H
