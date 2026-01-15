#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCoreApplication>

// 使用单例模式，保证全局只有一个数据库连接
class DatabaseManager
{
public:
    static DatabaseManager& instance(); // 获取实例的静态方法
    bool openDb();                      // 打开数据库连接
    QSqlDatabase getDb() const;         // 获取数据库对象
    void closeDb();                     // 关闭连接

private:
    DatabaseManager();                  // 构造函数私有化
    ~DatabaseManager();                 // 析构函数
    DatabaseManager(const DatabaseManager&) = delete;            // 禁止拷贝
    DatabaseManager& operator=(const DatabaseManager&) = delete; // 禁止赋值

    QSqlDatabase m_db;
    const QString DB_NAME = "lab6.db"; // 数据库文件名
};

#endif // DATABASEMANAGER_H
