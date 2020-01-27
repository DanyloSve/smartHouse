#include <QCoreApplication>
#include <iostream>
#include <string>
#include <QSqlDatabase>
#include <QtSql>
#include <QTextStream>

int main(int argc, char *argv[])
{
    QTextStream in (stdin);
    //QCoreApplication::addLibraryPath("/home/daniel/GIT/test/testConnectionMySql/libqsqlmysql.so");
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // додаємо драйвер QMYSQLDriver для MYSQL *connection
    db.setHostName("127.0.0.1");
    db.setDatabaseName("shop");
    db.setUserName("qwerty");
    db.setPassword("@@@qwertyQWERTY123");


    if (db.open())
    {
        std::cout << "Connection established!\n";
    }
    else
    {
       std::cout << "Connection doesnot established!\n";
    }

    QSqlQuery query;
    query.exec("Select id, name FROM category;");

    while(query.next())
    {
        int id       = query.value(0).toInt();
        QString name = query.value(1).toString();
        qDebug() << "ID: " << id << "name:" << name;
    }

    qDebug() << "Insert:";
    qDebug() << "name";
    QString name ;
    in >> name;

    qDebug() << "discount";
    int discount;
    std::cin >> discount;

    qDebug() << "alias_name";
    QString alias_name ;
    in >> alias_name;

    query.prepare("INSERT INTO category (name, discount, alias_name) VALUES (:name, :discount, :alias_name)");
    query.bindValue(":name", (name));
    query.bindValue(":discount", discount);
    query.bindValue(":alias_name", alias_name);
    query.exec();

    query.exec("Select * FROM category;");

    qDebug() << "\n";
    while(query.next())
    {
        int id       = query.value(0).toInt();
        QString name = query.value(1).toString();
        int discount = query.value(2).toInt();
        QString alias_name = query.value(3).toString();
        qDebug() << "ID: " << id
                 << "name:" << name
                 << "discount" << discount
                 << "alias_name: " << alias_name;
    }

}
