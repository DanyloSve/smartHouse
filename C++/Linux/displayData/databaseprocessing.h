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
    QVector <double> mRangeX;
    QVector <int> mId;

    int mTickNumberX;
    int mTickNumberY;
    const int cmDataNumberLastInsert{10};
    const int cmDataNumberDay{12};


public:
    explicit DataBaseProcessing(QObject *parent = nullptr);
    bool connectToServer();
    void readLastInsert();
    void readDay(QDate day);

    bool newDataInsertCheck();


    QVector <double> getHumidity();
    QVector <double> getTemperature();
    QVector <double> getPressure();
    QVector <double> getAltitude();
    QVector <QDateTime> getDateTime();
    QVector <double> getRangeX();
    QVector <double> getRangeY(QVector <double> data);
    double maximum(QVector <double> data);
    double minimum(QVector <double> data);
    int getTickNumberX();
    int getTickNumberY(QVector <double> data);

    void scroll(int side);

signals:
    void sDatabaseUpdate();
};

#endif // DATABASEPROCESSING_H
