#include "databaseprocessing.h"


DataBaseProcessing::DataBaseProcessing(QObject *parent) : QObject(parent)
{

}

bool DataBaseProcessing::connectToServer()
{
    db = QSqlDatabase::addDatabase("QMYSQL"); // додаємо драйвер QMYSQLDriver для MYSQL *connection
    db.setHostName("45.87.0.162");
    db.setDatabaseName("smartHouse");
    db.setUserName("displayData");
    db.setPassword("@@@gENADIy.mELNYk+lINUx==4eVEr2020");

    return db.open();
}

bool DataBaseProcessing::newDataInsertCheck()
{
    QSqlQuery query;
    int tmpId{mId[mId.size() - 1]};
    query.exec("SELECT MAX(`id`) FROM `tblCollectedData`;");
    while(query.next())
    {
        tmpId = query.value(0).toInt();
    }

    if (tmpId != mId[mId.size() - 1])
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void DataBaseProcessing::readFromDataBase()
{
    if (!db.open())
    {
        connectToServer();
    }

    if (!mId.isEmpty())
    {
        mId.erase(mId.begin(), mId.end());
    }

    if (!mDateTime.isEmpty())
    {
        mDateTime.erase(mDateTime.begin(), mDateTime.end());
    }

    if (!mTemperature.isEmpty())
    {
        mTemperature.erase(mTemperature.begin(), mTemperature.end());
    }

    if (!mHumidity.isEmpty())
    {
        mHumidity.erase(mHumidity.begin(), mHumidity.end());
    }

    if (!mPressure.isEmpty())
    {
        mPressure.erase(mPressure.begin(), mPressure.end());
    }

    if (!mAltitude.isEmpty())
    {
        mAltitude.erase(mAltitude.begin(), mAltitude.end());
    }

//    eraseQVector(mId);
//    eraseQVector(mDateTime);
//    eraseQVector(mTemperature);
//    eraseQVector(mHumidity);
//    eraseQVector(mPressure);
//    eraseQVector(mAltitude);

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


        for (int i{0}; i != mDateTime.size() - 1; i++)
        {
            qDebug() << mId[i]
            << mDateTime[i]
            << mTemperature[i]
            << mHumidity[i]
            << mPressure[i]
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

