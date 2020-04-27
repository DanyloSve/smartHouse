#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mDataBase = new DataBaseProcessing;

    mUpdateGraphicsTimer = new QTimer;
    connect(mUpdateGraphicsTimer, &QTimer::timeout, this, &MainWindow::displayAllData);
    mUpdateGraphicsTimer->start(cmUpadateGraphicsTimeMs);

    mUpdateClock = new QTimer;
    connect(mUpdateClock, &QTimer::timeout, this, &MainWindow::displayClock);
    mUpdateClock->start(cmUpdateClockTimeMs);

    if (mDataBase->connectToServer())
    {
        ui->pltTempr->setLocale(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
        ui->pltPress->setLocale(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
        ui->pltHum->setLocale(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
        displayAllData();
    }
}
void MainWindow::displayAllData()
{
   mDataBase->readFromDataBase();
   createTimeAxis();
   displayTemperature();
   displayHumidity();
   displayPressure();

   displayAverageData();
}

void MainWindow::displayTemperature()
{
    ui->pltTempr->addGraph();
    ui->pltTempr->graph(0)->setPen(QPen(Qt::blue));

    ui->pltTempr->graph(0)->setData(mTimeAxis, mDataBase->getTemperature());
    ui->pltTempr->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

    ui->pltTempr->graph(0)->rescaleAxes(true);
    ui->pltTempr->xAxis->setRange(mTimeAxis.first(), mTimeAxis.last());
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm\n");
    ui->pltTempr->xAxis->setTicker(dateTicker);
    ui->pltTempr->xAxis->ticker()->setTickCount(mDataBase->getDateTime().size());
    ui->pltTempr->yAxis->ticker()->setTickCount(mDataBase->getTemperature().size() / 2);
    ui->pltTempr->yAxis->setNumberFormat("f");
    ui->pltTempr->yAxis->setNumberPrecision(2);

    double deltaY{(maximum(mDataBase->getTemperature()) - minimum(mDataBase->getTemperature())) / mDataBase->getTemperature().size()};
    ui->pltTempr->yAxis->setRange(minimum(mDataBase->getTemperature()) - deltaY, maximum(mDataBase->getTemperature())+deltaY);

    ui->lblTemprIndicator->setText(QString::number(mDataBase->getTemperature()[mDataBase->getTemperature().size() - 1], 'f', 2) + " °C");
}

void MainWindow::displayHumidity()
{
    ui->pltHum->addGraph();
    ui->pltHum->graph(0)->setPen(QPen(Qt::blue));

    ui->pltHum->graph(0)->setData(mTimeAxis, mDataBase->getHumidity());
    ui->pltHum->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

    ui->pltHum->graph(0)->rescaleAxes(true);
    ui->pltHum->xAxis->setRange(mTimeAxis.first(), mTimeAxis.last());
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm\n");
    ui->pltHum->xAxis->setTicker(dateTicker);
    ui->pltHum->xAxis->ticker()->setTickCount(mDataBase->getDateTime().size());
    ui->pltHum->yAxis->ticker()->setTickCount(mDataBase->getHumidity().size() / 2);
    ui->pltHum->yAxis->setNumberFormat("f");
    ui->pltHum->yAxis->setNumberPrecision(2);

    double delta{(maximum(mDataBase->getHumidity()) - minimum(mDataBase->getHumidity())) / mDataBase->getHumidity().size()};
    ui->pltHum->yAxis->setRange(minimum(mDataBase->getHumidity()) - delta, maximum(mDataBase->getHumidity())+delta);

    ui->lblHumIndicator->setText(QString::number(mDataBase->getHumidity()[mDataBase->getHumidity().size() - 1], 'f', 2) + " %");
}

void MainWindow::displayPressure()
{
    ui->pltPress->addGraph();
    ui->pltPress->graph(0)->setPen(QPen(Qt::blue));

    ui->pltPress->graph(0)->setData(mTimeAxis, mDataBase->getPressure());
    ui->pltPress->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

    ui->pltPress->graph(0)->rescaleAxes(true);
    ui->pltPress->xAxis->setRange(mTimeAxis.first(), mTimeAxis.last());
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm\n");
    ui->pltPress->xAxis->setTicker(dateTicker);
    ui->pltPress->xAxis->ticker()->setTickCount(mDataBase->getDateTime().size());
    ui->pltPress->yAxis->ticker()->setTickCount(mDataBase->getPressure().size() / 2);
    ui->pltPress->yAxis->setNumberFormat("f");
    ui->pltPress->yAxis->setNumberPrecision(3);

    double delta{(maximum(mDataBase->getPressure()) - minimum(mDataBase->getPressure())) / mDataBase->getPressure().size()};
    ui->pltPress->yAxis->setRange(minimum(mDataBase->getPressure()) - delta, maximum(mDataBase->getPressure())+delta);

    ui->lblPressIndicator->setText(QString::number(mDataBase->getPressure()[mDataBase->getPressure().size() - 1], 'f', 2) + " mm");
}

double MainWindow::average(QVector<double> data)
{
    long double result{0};
    for (double itm : data)
    {
        result += itm;
    }
    return (double)result / (data.size());
}

void MainWindow::displayAverageData()
{
    ui->btnAverageData->setText("     Температура   " + QString::number(average(mDataBase->getTemperature()), 'f', 2) + " °C\n" +
                              + "     Вологість         " + QString::number(average(mDataBase->getHumidity()), 'f', 2) + " %\n" +
                              + "     Тиск                   " + QString::number(average(mDataBase->getPressure()), 'f', 2) + " mm\n" +
                                + "     Висота              " + QString::number(average(mDataBase->getAltitude()), 'f', 2) + " m");
}

void MainWindow::displayClock()
{
    QDateTime currentTime = QDateTime::currentDateTime();
    QLocale locale = {QLocale::Ukrainian};
    if (mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1] == currentTime)
    {
        ui->btnClock->setText("Сьогоднішня дата\n" + locale.toString(currentTime.date(), "dd.MM.yyyy") + '\n' + locale.toString(currentTime.date(), "dddd") + '\n'
                              + currentTime.toString("hh:mm"));
    }
    else
    {
        if (mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1].date() == mDataBase->getDateTime()[0].date())
        {
            ui->calendarWidget->addDate(mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1].date());

            ui->btnClock->setText("Дані за: \n" + locale.toString(mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1], "dd.MM.yyyy") + '\n'
                    + mDataBase->getDateTime()[0].toString("hh:mm") + " - "
                    + mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1].toString("hh:mm"));
        }
        else
        {
            ui->calendarWidget->addDate(mDataBase->getDateTime()[0].date());
            ui->calendarWidget->addDate(mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1].date());

            ui->btnClock->setText("Дані за: \n" + locale.toString(mDataBase->getDateTime()[0], "dd.MM.yyyy") + " - "
                                  +locale.toString(mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1], "dd.MM.yyyy") + '\n'
                    + mDataBase->getDateTime()[0].toString("hh:mm") + " - "
                    + mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1].toString("hh:mm"));
        }
    }
}

void MainWindow::createTimeAxis()
{
    for (QDateTime time : mDataBase->getDateTime())
    {
        mTimeAxis.push_back(time.toTime_t());
    }
}

double MainWindow::maximum(QVector<double> v)
{
    double tmp = v[0];
    for (double itm : v)
    {
            if (tmp < itm)
            {
                tmp = itm;
            }
    }
    return tmp;
}

double MainWindow::minimum(QVector<double> v)
{
    double tmp = v[0];
    for (double itm : v)
    {
            if (tmp > itm)
            {
                tmp = itm;
            }
    }
    return tmp;
}


MainWindow::~MainWindow()
{
    delete ui;
}



