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
    QVector <uint> mRangeX;
    QVector <int> mId;

    uint mTickNumberX;
    int mTickNumberY;
    const uint cmDataNumberLastInsert{12};
    const uint cmDataNumberDay{12};
    const uint cmMaxDataNumber{24};
    const uint cmIntervalDataNumber{8};

    bool mToShowDate;


public:
    explicit DataBaseProcessing(QObject *parent = nullptr);
    bool connectToServer();
    void readLastInsert();
    void readDay(QDate day);   
    void readInterval(QDate &start, QDate &end);

    bool newDataInsertCheck();

    QVector <int>    getId();
    QVector <double> getHumidity();
    QVector <double> getTemperature();
    QVector <double> getPressure();
    QVector <double> getAltitude();
    QVector <QDateTime> getDateTime();
    QVector <uint> getRangeX();
    QVector <double> getRangeY(QVector <double> data);
    double maximum(QVector <double> data);
    double minimum(QVector <double> data);
    uint getTickNumberX();
    int getTickNumberY(QVector <double> data);

    void clearAllVectors();
    void scrollForward();
    void scrollBack();
    bool showDate();
    QVector <double> getTimeAxis();

signals:
    void sDatabaseUpdate();
};

#endif // DATABASEPROCESSING_H
