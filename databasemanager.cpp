#include "databasemanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

DatabaseManager::DatabaseManager(QObject *parent) : QObject(parent)
{
    m_database = QSqlDatabase::addDatabase("QSQLITE");
    m_database.setDatabaseName("budgetbuddy.db");
}

DatabaseManager::~DatabaseManager()
{
    closeDatabase();
}

DatabaseManager& DatabaseManager::instance()
{
    static DatabaseManager instance;
    return instance;
}

QSqlDatabase DatabaseManager::getDatabase()
{
    return m_database;
}

bool DatabaseManager::openDatabase()
{
    if (!m_database.open()) {
        qDebug() << "Failed to open database:" << m_database.lastError().text();
        return false;
    }

    initializeTables();
    return true;
}

void DatabaseManager::closeDatabase()
{
    if (m_database.isOpen())
        m_database.close();
}

void DatabaseManager::initializeTables()
{
    QSqlQuery query;

    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "username TEXT UNIQUE,"
               "password TEXT,"
               "photo BLOB"
               ")");

    query.exec("CREATE TABLE IF NOT EXISTS transactions ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "type TEXT,"
               "category TEXT,"
               "amount REAL,"
               "date TEXT,"
               "remarks TEXT,"
               "FOREIGN KEY(user_id) REFERENCES users(id))");

    query.exec("CREATE TABLE IF NOT EXISTS monthly_goals ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "user_id INTEGER, "
               "month TEXT, "
               "year INTEGER, "
               "amount REAL, "
               "UNIQUE(user_id, month, year))");

    query.exec("CREATE TABLE IF NOT EXISTS alerts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "message TEXT,"
               "created_at TEXT,"
               "FOREIGN KEY(user_id) REFERENCES users(id))");
}


QString DatabaseManager::getUserNameById(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "User";
}

QString DatabaseManager::getUserPhotoPath(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT photo FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return QString();
}

bool DatabaseManager::updateUserPhoto(int userId, const QByteArray &imageData)
{
    QSqlQuery query;
    query.prepare("UPDATE users SET photo = :photo WHERE id = :id");
    query.bindValue(":photo", imageData);
    query.bindValue(":id", userId);
    return query.exec();
}

QByteArray DatabaseManager::getUserPhoto(int userId)
{
    QSqlQuery query;
    query.prepare("SELECT photo FROM users WHERE id = :id");
    query.bindValue(":id", userId);
    if (query.exec() && query.next()) {
        return query.value(0).toByteArray();
    }
    return QByteArray();
}

