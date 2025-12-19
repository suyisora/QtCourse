#include "idatabase.h"

void IDatabase::ininDatabase()
{
    database =QSqlDatabase :: addDatabase("QSQLITE");//添加 SQL LITE数据库驱动
    QString aFile = "../../lab3SQLite.db";
    database.setDatabaseName(aFile);//设置数据库名称

    if(!database.open()){//打开数据库
        qDebug() << "failed to open database";
    } else
        qDebug() << "open database is ok";
}


IDatabase::IDatabase(QObject *parent) : QObject(parent)
{
    ininDatabase();
}

