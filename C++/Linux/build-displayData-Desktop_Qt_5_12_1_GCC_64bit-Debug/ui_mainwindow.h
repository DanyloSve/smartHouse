/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "newcalendarwidget.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *lblHum;
    QLabel *lblTempr;
    QLabel *lblPress;
    QLabel *lblPressIndicator;
    QLabel *lblHumIndicator;
    QLabel *lblTemprIndicator;
    QCustomPlot *pltTempr;
    QCustomPlot *pltHum;
    QCustomPlot *pltPress;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btnAverageData;
    QPushButton *btnClock;
    NewCalendarWidget *calendarWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(986, 607);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setFlat(true);

        horizontalLayout->addWidget(pushButton);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        lblHum = new QLabel(centralwidget);
        lblHum->setObjectName(QString::fromUtf8("lblHum"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lblHum->sizePolicy().hasHeightForWidth());
        lblHum->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("Chandas"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        lblHum->setFont(font);
        lblHum->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lblHum, 2, 0, 1, 1);

        lblTempr = new QLabel(centralwidget);
        lblTempr->setObjectName(QString::fromUtf8("lblTempr"));
        lblTempr->setEnabled(true);
        sizePolicy1.setHeightForWidth(lblTempr->sizePolicy().hasHeightForWidth());
        lblTempr->setSizePolicy(sizePolicy1);
        lblTempr->setMinimumSize(QSize(0, 0));
        lblTempr->setFont(font);
        lblTempr->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lblTempr, 0, 0, 1, 1);

        lblPress = new QLabel(centralwidget);
        lblPress->setObjectName(QString::fromUtf8("lblPress"));
        sizePolicy1.setHeightForWidth(lblPress->sizePolicy().hasHeightForWidth());
        lblPress->setSizePolicy(sizePolicy1);
        lblPress->setFont(font);
        lblPress->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(lblPress, 4, 0, 1, 1);

        lblPressIndicator = new QLabel(centralwidget);
        lblPressIndicator->setObjectName(QString::fromUtf8("lblPressIndicator"));
        lblPressIndicator->setFont(font);

        gridLayout->addWidget(lblPressIndicator, 4, 1, 1, 1);

        lblHumIndicator = new QLabel(centralwidget);
        lblHumIndicator->setObjectName(QString::fromUtf8("lblHumIndicator"));
        lblHumIndicator->setFont(font);

        gridLayout->addWidget(lblHumIndicator, 2, 1, 1, 1);

        lblTemprIndicator = new QLabel(centralwidget);
        lblTemprIndicator->setObjectName(QString::fromUtf8("lblTemprIndicator"));
        lblTemprIndicator->setFont(font);

        gridLayout->addWidget(lblTemprIndicator, 0, 1, 1, 1);

        pltTempr = new QCustomPlot(centralwidget);
        pltTempr->setObjectName(QString::fromUtf8("pltTempr"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pltTempr->sizePolicy().hasHeightForWidth());
        pltTempr->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pltTempr, 1, 0, 1, 2);

        pltHum = new QCustomPlot(centralwidget);
        pltHum->setObjectName(QString::fromUtf8("pltHum"));
        sizePolicy2.setHeightForWidth(pltHum->sizePolicy().hasHeightForWidth());
        pltHum->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pltHum, 3, 0, 1, 2);

        pltPress = new QCustomPlot(centralwidget);
        pltPress->setObjectName(QString::fromUtf8("pltPress"));
        sizePolicy2.setHeightForWidth(pltPress->sizePolicy().hasHeightForWidth());
        pltPress->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(pltPress, 5, 0, 1, 2);


        verticalLayout->addLayout(gridLayout);

        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButton_3);


        horizontalLayout->addLayout(verticalLayout);

        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);
        pushButton_2->setFlat(true);

        horizontalLayout->addWidget(pushButton_2);


        gridLayout_2->addLayout(horizontalLayout, 0, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        btnAverageData = new QPushButton(centralwidget);
        btnAverageData->setObjectName(QString::fromUtf8("btnAverageData"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnAverageData->sizePolicy().hasHeightForWidth());
        btnAverageData->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setPointSize(16);
        btnAverageData->setFont(font1);
        btnAverageData->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 255, 255);\n"
"  border: 1px solid blue;\n"
"  text-align: left;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #BEBEBE, stop: 1 #D7D7D7);\n"
"}ho"));
        btnAverageData->setFlat(true);

        verticalLayout_2->addWidget(btnAverageData);

        btnClock = new QPushButton(centralwidget);
        btnClock->setObjectName(QString::fromUtf8("btnClock"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnClock->sizePolicy().hasHeightForWidth());
        btnClock->setSizePolicy(sizePolicy4);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Chandas"));
        font2.setPointSize(16);
        font2.setBold(true);
        font2.setWeight(75);
        btnClock->setFont(font2);
        btnClock->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  background-color: rgb(255, 255, 255);\n"
"   border: 1px solid blue;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                      stop: 0 #BEBEBE, stop: 1 #D7D7D7);\n"
"}"));
        btnClock->setFlat(true);

        verticalLayout_2->addWidget(btnClock);

        calendarWidget = new NewCalendarWidget(centralwidget);
        calendarWidget->setObjectName(QString::fromUtf8("calendarWidget"));
        QSizePolicy sizePolicy5(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(calendarWidget->sizePolicy().hasHeightForWidth());
        calendarWidget->setSizePolicy(sizePolicy5);

        verticalLayout_2->addWidget(calendarWidget);


        gridLayout_2->addLayout(verticalLayout_2, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QString());
        lblHum->setText(QApplication::translate("MainWindow", "\320\222\320\276\320\273\320\276\320\263\321\226\321\201\321\202\321\214", nullptr));
        lblTempr->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260", nullptr));
        lblPress->setText(QApplication::translate("MainWindow", "\320\242\320\270\321\201\320\272", nullptr));
        lblPressIndicator->setText(QApplication::translate("MainWindow", "0000.00", nullptr));
        lblHumIndicator->setText(QApplication::translate("MainWindow", "00.00 %", nullptr));
        lblTemprIndicator->setText(QApplication::translate("MainWindow", "00.00 \302\260C", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "PushButton", nullptr));
        pushButton_2->setText(QString());
        btnAverageData->setText(QApplication::translate("MainWindow", "     \320\242\320\265\320\274\320\277\320\265\321\200\320\260\321\202\321\203\321\200\320\260\n"
"     \320\222\320\276\320\273\320\276\320\263\321\226\321\201\321\202\321\214\n"
"     \320\242\320\270\321\201\320\272\n"
"     \320\222\320\270\321\201\320\276\321\202\320\260", nullptr));
        btnClock->setText(QApplication::translate("MainWindow", "\320\241\321\214\320\276\320\263\320\276\320\264\320\275\321\226\321\210\320\275\321\217 \320\264\320\260\321\202\320\260\n"
"18.06.2019\n"
"\320\275\320\265\320\264\321\226\320\273\321\217\n"
"10:50", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
