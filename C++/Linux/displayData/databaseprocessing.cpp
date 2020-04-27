#include "databaseprocessing.h"

#include <QSqlDatabase>
#include <QtSql>

DataBaseProcessing::DataBaseProcessing(QObject *parent) : QObject(parent)
{

}

bool DataBaseProcessing::connectToServer()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL"); // додаємо драйвер QMYSQLDriver для MYSQL *connection
    db.setHostName("45.87.0.162");
    db.setDatabaseName("smartHouse");
    db.setUserName("displayData");
    db.setPassword("@@@gENADIy.mELNYk+lINUx==4eVEr2020");

    return db.open();
}

void DataBaseProcessing::newDataInsertCheck()
{
    QSqlQuery query;
    int tmpId{mId[mId.size() - 1]};
    query.exec("Select `id` FROM `tblCollectedData` ORDER BY id DESC");
    while(query.next())
    {
        tmpId = query.value(0).toInt();
    }
    if (tmpId != mId[mId.size() - 1])
    {
        emit sDatabaseUpdate();
    }
}

void DataBaseProcessing::readFromDataBase()
{
    QSqlQuery query;
    query.exec("Select * FROM ("
               "SELECT * FROM `tblCollectedData` ORDER BY id DESC LIMIT 10"
               ") sub "
               "ORDER BY id ASC;");

    qDebug() << "\n";
    while(query.next())
    {
        mId.push_back(query.value(0).toInt());
        int placeId = query.value(1).toInt();
        mDateTime.push_back(query.value(2).toDateTime());
        mTemperature.push_back(query.value(3).toDouble() / 100);
        mHumidity.push_back(query.value(4).toDouble() / 100);
        mPressure.push_back(query.value(5).toDouble() / 100);
        mAltitude.push_back(query.value(6).toDouble() / 100);
    }


        for (int i{0}; i != 10; i++)
        {
            qDebug() << mId[i]
            << mDateTime[i]
            << mTemperature[i]
            << mHumidity[i]
            << mAltitude[i];

        }
}

QVector<double> DataBaseProcessing::getHumidity()
{
    return mHumidity;
}

QVector<double> DataBaseProcessing::getTemperature()
{
    return mTemperature;
}

QVector<double> DataBaseProcessing::getPressure()
{
    return mPressure;
}

QVector<double> DataBaseProcessing::getAltitude()
{
    return mAltitude;
}

QVector<QDateTime> DataBaseProcessing::getDateTime()
{
    return mDateTime;
}

void DataBaseProcessing::scroll(int side)
{

}
