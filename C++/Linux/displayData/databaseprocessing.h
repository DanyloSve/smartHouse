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
    const int cmDataNumberLastInsert{12};
    const int cmDataNumberDay{12};
    const int cmMaxDataNumber{24};
    const int cmIntervalDataNumber{9};

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

signals:
    void sDatabaseUpdate();
};

#endif // DATABASEPROCESSING_H
