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

    if (mDataBase->connectToServer())
    {
        mUpdateGraphicsTimer = new QTimer;
        connect(mUpdateGraphicsTimer, &QTimer::timeout, this, &MainWindow::receiveLastData);
        mUpdateGraphicsTimer->start(cmUpadateGraphicsTimeMs);

        mUpdateClock = new QTimer;
        connect(mUpdateClock, &QTimer::timeout, this, &MainWindow::displayClock);
        mUpdateClock->start(cmUpdateClockTimeMs);


        ui->pltTempr->setLocale(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
        ui->pltPress->setLocale(QLocale(QLocale::Ukrainian, QLocale::Ukraine));
        ui->pltHum->setLocale(QLocale(QLocale::Ukrainian, QLocale::Ukraine));

        receiveLastData();
    }
}
void MainWindow::receiveLastData()
{
    mDataBase->readLastInsert();
    displayAllData();
}

void MainWindow::displayAllData()
{
    createTimeAxis();
    if (!mTimeAxis.isEmpty() &&
            !mDataBase->getTemperature().isEmpty() &&
            !mDataBase->getHumidity().isEmpty() &&
            !mDataBase->getPressure().isEmpty() &&
            !mDataBase->getHumidity().isEmpty())
    {
         displayTemperature();
         displayHumidity();
         displayPressure();
         displayAverageData();
    }
}

void MainWindow::displayTemperature()
{
    ui->pltTempr->rescaleAxes();
    ui->pltTempr->addGraph();
    ui->pltTempr->graph(0)->setPen(QPen(Qt::blue));

    ui->pltTempr->graph(0)->setData(mTimeAxis, mDataBase->getTemperature());
    ui->pltTempr->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

    ui->pltTempr->graph(0)->rescaleAxes(true);

    ui->pltTempr->xAxis->setRange(mDataBase->getRangeX()[0], mDataBase->getRangeX()[1] + (mDataBase->getRangeX()[1] - mDataBase->getRangeX()[0]) /(2* mDataBase->getDateTime().size()));
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm\n");
    ui->pltTempr->xAxis->setTicker(dateTicker);
    ui->pltTempr->xAxis->ticker()->setTickCount(mDataBase->getTickNumberX());

    ui->pltTempr->yAxis->setNumberFormat("f");
    ui->pltTempr->yAxis->setNumberPrecision(2);

    ui->pltTempr->yAxis->setRange(mDataBase->getRangeY(mDataBase->getTemperature())[0], mDataBase->getRangeY(mDataBase->getTemperature())[1]);
    ui->pltTempr->yAxis->ticker()->setTickCount(mDataBase->getTickNumberY(mDataBase->getTemperature()));

    ui->lblTemprIndicator->setText(QString::number(mDataBase->getTemperature()[mDataBase->getTemperature().size() - 1], 'f', 2) + " °C");

    ui->pltTempr->replot();
}

void MainWindow::displayHumidity()
{
    ui->pltHum->rescaleAxes();

    ui->pltHum->addGraph();
    ui->pltHum->graph(0)->setPen(QPen(Qt::blue));

    ui->pltHum->graph(0)->setData(mTimeAxis, mDataBase->getHumidity());
    ui->pltHum->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

    ui->pltHum->graph(0)->rescaleAxes(true);
     ui->pltHum->xAxis->setRange(mDataBase->getRangeX()[0], mDataBase->getRangeX()[1] + (mDataBase->getRangeX()[1] - mDataBase->getRangeX()[0]) / (2* mDataBase->getDateTime().size()));
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm\n");
    ui->pltHum->xAxis->setTicker(dateTicker);
    ui->pltHum->xAxis->ticker()->setTickCount(mDataBase->getTickNumberX());
    ui->pltHum->yAxis->setNumberFormat("f");
    ui->pltHum->yAxis->setNumberPrecision(2);

    ui->pltHum->yAxis->setRange(mDataBase->getRangeY(mDataBase->getHumidity())[0], mDataBase->getRangeY(mDataBase->getHumidity())[1]);
    ui->pltHum->yAxis->ticker()->setTickCount(mDataBase->getTickNumberY(mDataBase->getHumidity()));

    ui->lblHumIndicator->setText(QString::number(mDataBase->getHumidity()[mDataBase->getHumidity().size() - 1], 'f', 2) + " %");
    ui->pltHum->replot();
}

void MainWindow::displayPressure()
{
    ui->pltPress->rescaleAxes();
    ui->pltPress->addGraph();
    ui->pltPress->graph(0)->setPen(QPen(Qt::blue));

    ui->pltPress->graph(0)->setData(mTimeAxis, mDataBase->getPressure());
    ui->pltPress->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);

    ui->pltPress->graph(0)->rescaleAxes(true);
    ui->pltPress->xAxis->setRange(mDataBase->getRangeX()[0], mDataBase->getRangeX()[1] + (mDataBase->getRangeX()[1] - mDataBase->getRangeX()[0]) /(2* mDataBase->getDateTime().size()));
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("hh:mm\n");
    ui->pltPress->xAxis->setTicker(dateTicker);
    ui->pltPress->xAxis->ticker()->setTickCount(mDataBase->getTickNumberX());

    ui->pltPress->yAxis->setNumberFormat("f");
    ui->pltPress->yAxis->setNumberPrecision(3);

    ui->pltPress->yAxis->setRange(mDataBase->getRangeY(mDataBase->getPressure())[0], mDataBase->getRangeY(mDataBase->getPressure())[1]);
    ui->pltPress->yAxis->ticker()->setTickCount(mDataBase->getTickNumberY(mDataBase->getPressure()));
    ui->lblPressIndicator->setText(QString::number(mDataBase->getPressure()[mDataBase->getPressure().size() - 1], 'f', 2) + " mm");

    ui->pltPress->replot();
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
    if (mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1].date() == currentTime.date())
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


            for (QDateTime dateTime : mDataBase->getDateTime())
            {
                ui->calendarWidget->addDate(dateTime.date());
            }

            ui->btnClock->setText("Дані за: \n" + locale.toString(mDataBase->getDateTime()[0], "dd.MM.yyyy") + " - "
                                  +locale.toString(mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1], "dd.MM.yyyy") + '\n'
                    + mDataBase->getDateTime()[0].toString("hh:mm") + " - "
                    + mDataBase->getDateTime()[mDataBase->getDateTime().size() - 1].toString("hh:mm"));
        }
    }
}

void MainWindow::createTimeAxis()
{
    if (!mDataBase->getDateTime().isEmpty())
    {

        if (!mTimeAxis.isEmpty())
        {
            mTimeAxis.erase(mTimeAxis.begin(), mTimeAxis.end());
        }


        for (QDateTime time : mDataBase->getDateTime())
        {
            mTimeAxis.push_back(time.toTime_t());
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnClock_clicked()
{
    this->disconnect(mUpdateGraphicsTimer, &QTimer::timeout, this, &MainWindow::displayAllData);
    //this->disconnect();
    QDate day(QDateTime::currentDateTime().date());
    mDataBase->readDay(day);
    displayAllData();
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{
    this->disconnect(mUpdateGraphicsTimer, &QTimer::timeout, this, &MainWindow::displayAllData);
    //this->disconnect();
    QDate day(ui->calendarWidget->selectedDate());
    mDataBase->readDay(day);

    if (!mDataBase->getDateTime().isEmpty())
    {
        displayAllData();
    }
//    else
//    {
//        on_btnClock_clicked();
//    }
}
