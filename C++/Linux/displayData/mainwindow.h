#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <databaseprocessing.h>

#include <QDateTime>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    DataBaseProcessing *mDataBase;

    QVector <double> mTimeAxis;
    QTimer *mUpdateGraphicsTimer;
    QTimer *mUpdateClock;

    const int cmUpadateGraphicsTimeMs = 30000;
    const int cmUpdateClockTimeMs = 1000;

    void displayAllData();
    void displayTemperature();
    void displayHumidity();
    void displayPressure();
    double average(QVector<double> data);
    void displayAverageData();
    void displayClock();
    void createTimeAxis();
    double maximum(QVector<double> v);
    double minimum(QVector<double> v);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
