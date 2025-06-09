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
               "password TEXT)");

    query.exec("CREATE TABLE IF NOT EXISTS transactions ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "type TEXT,"
               "category TEXT,"
               "amount REAL,"
               "date TEXT,"
               "FOREIGN KEY(user_id) REFERENCES users(id))");

    query.exec("CREATE TABLE IF NOT EXISTS monthly_budget ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "month TEXT,"
               "budget_amount REAL,"
               "FOREIGN KEY(user_id) REFERENCES users(id))");

    query.exec("CREATE TABLE IF NOT EXISTS alerts ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "user_id INTEGER,"
               "message TEXT,"
               "created_at TEXT,"
               "FOREIGN KEY(user_id) REFERENCES users(id))");
}
