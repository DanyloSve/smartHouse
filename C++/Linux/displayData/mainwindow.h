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

    void receiveLastData();
    void displayAllData();
    void displayTemperature();
    void displayHumidity();
    void displayPressure();
    double average(QVector<double> data);
    void displayAverageData();
    void displayClock();
    void createTimeAxis();
    void disconnectAllSignals();
    void connectAllSignals();


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:

    void displayInterval(QDate start, QDate end);

private slots:
    void on_btnClock_clicked();

    void on_calendarWidget_clicked(const QDate &date);

    void on_bttnBack_clicked();

    void on_bttnReturn_clicked();

    void on_bttnForward_clicked();

    void on_btnAverageData_clicked();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
