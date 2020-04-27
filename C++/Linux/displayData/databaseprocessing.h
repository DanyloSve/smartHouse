#ifndef DATABASEPROCESSING_H
#define DATABASEPROCESSING_H

#include <QObject>
#include <QVector>
#include <QDateTime>


class DataBaseProcessing : public QObject
{
    Q_OBJECT
    const ushort cmForward{1};
    const ushort cmBackward{2};
    const ushort cmUpdate{0};

    QVector <double> mHumidity;
    QVector <double> mTemperature;
    QVector <double> mPressure;
    QVector <double> mAltitude;
    QVector <QDateTime> mDateTime;
    QVector <int> mId;

    void newDataInsertCheck();
public:
    explicit DataBaseProcessing(QObject *parent = nullptr);
    bool connectToServer();
    void readFromDataBase();

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
