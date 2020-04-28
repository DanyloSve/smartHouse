#ifndef DATABASEPROCESSING_H
#define DATABASEPROCESSING_H

#include <QObject>
#include <QVector>
#include <QDateTime>

#include <QSqlDatabase>
#include <QtSql>


class DataBaseProcessing : public QObject
{
    Q_OBJECT
    QSqlDatabase db;

    const ushort cmForward{1};
    const ushort cmBackward{2};
    const ushort cmUpdate{0};

    QVector <double> mHumidity;
    QVector <double> mTemperature;
    QVector <double> mPressure;
    QVector <double> mAltitude;
    QVector <QDateTime> mDateTime;
    QVector <int> mId;


public:
    explicit DataBaseProcessing(QObject *parent = nullptr);
    bool connectToServer();
    void readFromDataBase();

    bool newDataInsertCheck();

    QVector <double> getHumidity();
    QVector <double> getTemperature();
    QVector <double> getPressure();
    QVector <double> getAltitude();
    QVector <QDateTime> getDateTime();

    void scroll(int side);

signals:
    void sDatabaseUpdate();
};

#endif // DATABASEPROCESSING_H
