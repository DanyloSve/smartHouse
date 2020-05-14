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

QVector<int> DataBaseProcessing::getId()
{
    return mId;
}

void DataBaseProcessing::readLastInsert()
{
    if (!db.open())
    {
        connectToServer();
    }

    clearAllVectors();

    QSqlQuery query;
    QString queryString = "Select * FROM ("
                          "SELECT * FROM `tblCollectedData` ORDER BY id DESC LIMIT %1"
                          ") sub "
                          "ORDER BY id ASC;";

    query.exec(queryString.arg(cmDataNumberLastInsert));

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


    if (!mTemperature.isEmpty() && !mHumidity.isEmpty() && !mPressure.isEmpty() && !mAltitude.isEmpty())
    {
        for (int i{0}; i != mDateTime.size() - 1; i++)
        {
            qDebug() << mId[i]
            << mDateTime[i]
            << mTemperature[i]
            << mHumidity[i]
            << mPressure[i]
            << mAltitude[i];

        }

        mRangeX.push_back(mDateTime[0].toTime_t());
        mRangeX.push_back(mDateTime[mDateTime.size() - 1].toTime_t());
        mTickNumberX = cmDataNumberLastInsert;
    }
}

void DataBaseProcessing::readDay(QDate day)
{
        if (!db.open())
        {
            connectToServer();
        }


    QVector <double> tmpTempr;
    QVector <double> tmpHum;
    QVector <double> tmpPress;
    QVector <double> tmpAlt;
    QVector <double> tmpId;
    QVector <QDateTime> tmpDateTime;


    QSqlQuery query;
    QString queryString = "SELECT * "
                          "FROM `tblCollectedData` "
                          "WHERE YEAR(`time`) = '%1' "
                          "AND  MONTH(`time`) = '%2'"
                          " AND DAY(`time`) = '%3';";
    query.exec(queryString.arg(day.year()).arg(day.month()).arg(day.day()));

    qDebug() << "\n";

    int temprCount{1};
    int humCount  {1};
    int pressCount{1};
    int altCount  {1};

    while(query.next())
    {
        if (tmpDateTime.isEmpty())
        {
            tmpDateTime.push_back(query.value(2).toDateTime());
            tmpTempr.push_back(query.value(3).toDouble() / 100);
            tmpHum.push_back(query.value(4).toDouble() / 100);
            tmpPress.push_back(query.value(5).toDouble() / 100);
            tmpAlt.push_back(query.value(6).toDouble() / 100);
            tmpId.push_back(query.value(0).toInt());
        }

        // якщо значення температури, вологості, тиску не є рівні 0
        if ( (query.value(2).toDateTime().time().hour() != tmpDateTime[tmpDateTime.size() - 1].time().hour())&&
                ((query.value(3).toDouble() / 100 != 0.0) &&
                (query.value(4).toDouble() / 100 != 0.0) &&
                (query.value(5).toDouble() / 100 != 0.0) &&
                (query.value(6).toDouble() / 100 != 0.0)))
        {
            if (!tmpTempr.isEmpty())
            {
                tmpTempr[tmpTempr.size() - 1] /= temprCount;
            }
            if (!tmpHum.isEmpty())
            {
                tmpHum   [tmpHum.size()    - 1] /= humCount;
            }
            if (!tmpPress.isEmpty())
            {
                tmpPress   [tmpPress.size()    - 1] /= pressCount;
            }
            if (!tmpAlt.isEmpty())
            {
                tmpAlt  [tmpAlt.size()    - 1] /= altCount;
            }

            tmpId.push_back(query.value(0).toInt());
            tmpDateTime.push_back(query.value(2).toDateTime());


            tmpTempr.push_back(query.value(3).toDouble() / 100);
            tmpHum.push_back(query.value(4).toDouble() / 100);
            tmpPress.push_back(query.value(5).toDouble() / 100);
            tmpAlt.push_back(query.value(6).toDouble() / 100);

            temprCount = 1;
            humCount   = 1;
            pressCount = 1;
            altCount   = 1;
        }
        else
        {
            if (query.value(3).toDouble() / 100 != 0.0)
            {
                tmpTempr[tmpTempr.size() - 1] += query.value(3).toDouble() / 100;
                temprCount++;
            }
            if (query.value(4).toDouble() / 100 != 0.0)
            {
                tmpHum   [tmpHum.size()    - 1] += query.value(4).toDouble() / 100;
                humCount++;
            }
            if (query.value(5).toDouble() / 100 != 0.0)
            {
                tmpPress   [tmpPress.size()    - 1] += query.value(5).toDouble() / 100;
                pressCount++;
            }
            if (query.value(6).toDouble() / 100 != 0.0)
            {
                tmpAlt   [tmpAlt.size()    - 1] += query.value(6).toDouble() / 100;
                altCount++;
            }
        }

    }

    if (!tmpDateTime.isEmpty() && !tmpTempr.isEmpty() && !tmpHum.isEmpty() && !tmpPress.isEmpty() && !tmpAlt.isEmpty())
    {
                clearAllVectors();

                tmpTempr[tmpTempr.size() - 1] /= temprCount;
                tmpHum  [tmpHum.size()    - 1] /= humCount;
                tmpPress   [tmpPress.size()    - 1] /= pressCount;
                tmpAlt   [tmpAlt.size()    - 1] /= altCount;


                QDateTime tmp(QDate(tmpDateTime[0].date().year(), tmpDateTime[0].date().month(), tmpDateTime[0].date().day()),
                        QTime(0,0,0));

                mRangeX.push_back(tmp.toTime_t());
                mRangeX.push_back(tmp.toTime_t() + 24 * 3600);
                mTickNumberX = cmDataNumberDay;


        for (int i{0}; i != tmpTempr.size(); i++)
        {
            mId.push_back(tmpId[i]);
            mTemperature.push_back(tmpTempr[i]);
            mHumidity.push_back(tmpHum[i]);
            mPressure.push_back(tmpPress[i]);
            mAltitude.push_back(tmpAlt[i]);
            mDateTime.push_back(tmpDateTime[i]);
        }

    }
}

///////////////////------------------------------------------------->
void DataBaseProcessing::readInterval(QDateTime &start, QDateTime &end)
{
    if (!db.open())
    {
        connectToServer();
    }


QVector <double> tmpTempr;
QVector <double> tmpHum;
QVector <double> tmpPress;
QVector <double> tmpAlt;
QVector <double> tmpId;
QVector <QDateTime> tmpDateTime;


QSqlQuery query;
QString queryString = "SELECT * FROM `tblCollectedData`"
                      " WHERE 'time' >= '%1 %2' AND 'time' <= '%3 %4';";

query.exec(queryString.arg(start.date().toString("yyyy-MM-dd")).arg(start.time().toString("hh:mm"))
           .arg(end.date().toString("yyyy-MM-dd")).arg(end.time().toString("hh:mm")));

int temprCount{1};
int humCount  {1};
int pressCount{1};
int altCount  {1};

while(query.next())
{
    if (tmpDateTime.isEmpty())
    {
        tmpDateTime.push_back(query.value(2).toDateTime());
        tmpTempr.push_back(query.value(3).toDouble() / 100);
        tmpHum.push_back(query.value(4).toDouble() / 100);
        tmpPress.push_back(query.value(5).toDouble() / 100);
        tmpAlt.push_back(query.value(6).toDouble() / 100);
        tmpId.push_back(query.value(0).toInt());
    }

    // якщо значення температури, вологості, тиску не є рівні 0
    if ( (query.value(2).toDateTime().time().hour() != tmpDateTime[tmpDateTime.size() - 1].time().hour())&&
            ((query.value(3).toDouble() / 100 != 0.0) &&
            (query.value(4).toDouble() / 100 != 0.0) &&
            (query.value(5).toDouble() / 100 != 0.0) &&
            (query.value(6).toDouble() / 100 != 0.0)))
    {
        if (!tmpTempr.isEmpty())
        {
            tmpTempr[tmpTempr.size() - 1] /= temprCount;
        }
        if (!tmpHum.isEmpty())
        {
            tmpHum   [tmpHum.size()    - 1] /= humCount;
        }
        if (!tmpPress.isEmpty())
        {
            tmpPress   [tmpPress.size()    - 1] /= pressCount;
        }
        if (!tmpAlt.isEmpty())
        {
            tmpAlt  [tmpAlt.size()    - 1] /= altCount;
        }

        tmpId.push_back(query.value(0).toInt());
        tmpDateTime.push_back(query.value(2).toDateTime());


        tmpTempr.push_back(query.value(3).toDouble() / 100);
        tmpHum.push_back(query.value(4).toDouble() / 100);
        tmpPress.push_back(query.value(5).toDouble() / 100);
        tmpAlt.push_back(query.value(6).toDouble() / 100);

        temprCount = 1;
        humCount   = 1;
        pressCount = 1;
        altCount   = 1;
    }
    else
    {
        if (query.value(3).toDouble() / 100 != 0.0)
        {
            tmpTempr[tmpTempr.size() - 1] += query.value(3).toDouble() / 100;
            temprCount++;
        }
        if (query.value(4).toDouble() / 100 != 0.0)
        {
            tmpHum   [tmpHum.size()    - 1] += query.value(4).toDouble() / 100;
            humCount++;
        }
        if (query.value(5).toDouble() / 100 != 0.0)
        {
            tmpPress   [tmpPress.size()    - 1] += query.value(5).toDouble() / 100;
            pressCount++;
        }
        if (query.value(6).toDouble() / 100 != 0.0)
        {
            tmpAlt   [tmpAlt.size()    - 1] += query.value(6).toDouble() / 100;
            altCount++;
        }
    }

}

if (!tmpDateTime.isEmpty() && !tmpTempr.isEmpty() && !tmpHum.isEmpty() && !tmpPress.isEmpty() && !tmpAlt.isEmpty())
{
            clearAllVectors();

            tmpTempr[tmpTempr.size() - 1] /= temprCount;
            tmpHum  [tmpHum.size()    - 1] /= humCount;
            tmpPress   [tmpPress.size()    - 1] /= pressCount;
            tmpAlt   [tmpAlt.size()    - 1] /= altCount;


            QDateTime tmp(QDate(tmpDateTime[0].date().year(), tmpDateTime[0].date().month(), tmpDateTime[0].date().day()),
                    QTime(0,0,0));

            mRangeX.push_back(tmp.toTime_t());
            mRangeX.push_back(tmp.toTime_t() + 24 * 3600);
            mTickNumberX = cmDataNumberDay;


    for (int i{0}; i != tmpTempr.size(); i++)
    {
        mId.push_back(tmpId[i]);
        mTemperature.push_back(tmpTempr[i]);
        mHumidity.push_back(tmpHum[i]);
        mPressure.push_back(tmpPress[i]);
        mAltitude.push_back(tmpAlt[i]);
        mDateTime.push_back(tmpDateTime[i]);
    }

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

QVector<double> DataBaseProcessing::getRangeX()
{
    return mRangeX;
}

QVector<double> DataBaseProcessing::getRangeY(QVector <double> data)
{
    QVector<double> result;
    double delta = 1;
    if (maximum(data) - minimum(data) <= 0.01 && maximum(data) - minimum(data) >= -0.01 )
    {
        delta = 1;
    }
    else
    {
        delta = (maximum(data) - minimum(data)) / (data.size());
    }
    result.push_back(minimum(data) - delta);
    result.push_back(maximum(data) + delta);

    return result;
}

double DataBaseProcessing::maximum(QVector<double> data)
{
    double result = data[0];
    for (double itm : data)
    {
            if (result > itm)
            {
                result = itm;
            }
    }
    return result;
}

double DataBaseProcessing::minimum(QVector<double> data)
{
    double result = data[0];
    for (double itm : data)
    {
            if (result < itm)
            {
                result = itm;
            }
    }
    return result;
}

int DataBaseProcessing::getTickNumberX()
{
    return mTickNumberX;
}

int DataBaseProcessing::getTickNumberY(QVector <double> data)
{
    QVector <double> tmp;
    tmp.push_back(data[0]);

    for (int i{0}; i != data.size(); i++)
    {
        for (int j{0}; j != tmp.size(); j++)
        {
            if (tmp[j] >= data[i] * 0.999 && tmp[j] <= data[i] * 1.001)
            {
                continue;
            }
            else
            {
                tmp.push_back(data[i]);
            }
        }
    }

    if (tmp.size() <= 3)
    {
        return  3;
    }
    else
    {
        if (tmp.size() >= 6)
        {
           return 5;
        }
        else
        {
            return  tmp.size();
        }
    }
}

void DataBaseProcessing::clearAllVectors()
{
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

    if (!mRangeX.isEmpty())
    {
        mRangeX.erase(mRangeX.begin(), mRangeX.end());
    }
}

void DataBaseProcessing::scrollForward()
{
    if (!db.open())
    {
        connectToServer();
    }

    QSqlQuery query;

    QString queryString = "Select * FROM ("
                          "SELECT * FROM `tblCollectedData` ORDER BY id DESC LIMIT 1"
                          ") sub "
                          "ORDER BY id ASC;";
     query.exec(queryString);
     int tmpId = mId[mId.size() - 1];
     while(query.next())
     {
         tmpId = query.value(0).toInt();
     }

    if (tmpId != mId[mId.size() - 1])
    {
    queryString = "SELECT * FROM `tblCollectedData`"
                  "WHERE `id` BETWEEN '%1' AND '%2';";

    int deltaId {mId[1] - mId[0]};
    query.exec(queryString.arg(mId[0] + deltaId).arg(mId[mId.size() - 1] + deltaId));

    clearAllVectors();
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


    if (!mTemperature.isEmpty() && !mHumidity.isEmpty() && !mPressure.isEmpty() && !mAltitude.isEmpty())
    {
        for (int i{0}; i != mDateTime.size() - 1; i++)
        {
            qDebug() << mId[i]
            << mDateTime[i]
            << mTemperature[i]
            << mHumidity[i]
            << mPressure[i]
            << mAltitude[i];

        }

        mRangeX.push_back(mDateTime[0].toTime_t());
        mRangeX.push_back(mDateTime[mDateTime.size() - 1].toTime_t());
        mTickNumberX = cmDataNumberLastInsert;
    }

   }
}
void DataBaseProcessing::scrollBack()
{
    if (!db.open())
    {
        connectToServer();
    }

    QSqlQuery query;
    QString queryString = "SELECT * FROM `tblCollectedData`"
                          "WHERE `id` BETWEEN '%1' AND '%2';";

    int deltaId {mId[1] - mId[0]};
    qDebug()<<deltaId;
    query.exec(queryString.arg(mId[0] - deltaId).arg(mId[mId.size() - 1] - deltaId));

    clearAllVectors();
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


    if (!mTemperature.isEmpty() && !mHumidity.isEmpty() && !mPressure.isEmpty() && !mAltitude.isEmpty())
    {
        for (int i{0}; i != mDateTime.size() - 1; i++)
        {
            qDebug() << mId[i]
            << mDateTime[i]
            << mTemperature[i]
            << mHumidity[i]
            << mPressure[i]
            << mAltitude[i];

        }

        mRangeX.push_back(mDateTime[0].toTime_t());
        mRangeX.push_back(mDateTime[mDateTime.size() - 1].toTime_t());
        mTickNumberX = cmDataNumberLastInsert;
    }

}


