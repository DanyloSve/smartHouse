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
    db.setHostName("45.87.0.162");
    db.setDatabaseName("smartHouse");
    db.setUserName("displayData");
    db.setPassword("@@@gENADIy.mELNYk+lINUx==4eVEr2020");


    if (db.open())
    {
        std::cout << "Connection established!\n";
    }
    else
    {
       std::cout << "Connection doesnot established!\n";
    }

    QSqlQuery query;
//    query.exec("INSERT INTO testTable(text) VALUES ('Hello from Arduino')");

//    while(query.next())
//    {
//        int id       = query.value(0).toInt();
//        QString name = query.value(1).toString();
//        qDebug() << "ID: " << id << "name:" << name;
//    }

//    qDebug() << "Insert:";
//    qDebug() << "name";
//    QString name ;
//    in >> name;

//    qDebug() << "discount";
//    int discount;
//    std::cin >> discount;

//    qDebug() << "alias_name";
//    QString alias_name ;
//    in >> alias_name;

//    query.prepare("INSERT INTO category (name, discount, alias_name) VALUES (:name, :discount, :alias_name)");
//    query.bindValue(":name", (name));
//    query.bindValue(":discount", discount);
//    query.bindValue(":alias_name", alias_name);
//    query.exec();

    query.exec("Select * FROM ("
               "SELECT * FROM `tblCollectedData` ORDER BY id DESC LIMIT 10"
               ") sub "
               "ORDER BY id ASC;");

    qDebug() << "\n";
    while(query.next())
    {
        int id       = query.value(0).toInt();
        int placeId = query.value(1).toInt();
        QDateTime time = query.value(2).toDateTime();
        int tempr = query.value(3).toInt();
        int hum = query.value(4).toInt();
        int press = query.value(5).toInt();
        int alt = query.value(6).toInt();

        qDebug() << "ID: " << id
                 << "place Id:" << placeId
                 << "time:" << time
                 << "tempr: " << tempr
                 << "hum: " << hum
                 << "press: " << press
                 << "alt: " << alt;
    }

}
