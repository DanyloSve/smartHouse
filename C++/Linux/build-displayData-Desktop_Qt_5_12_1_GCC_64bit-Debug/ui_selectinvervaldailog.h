/********************************************************************************
** Form generated from reading UI file 'selectinvervaldailog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTINVERVALDAILOG_H
#define UI_SELECTINVERVALDAILOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelectInvervalDailog
{
public:
    QCalendarWidget *calendarWidgetStart;
    QCalendarWidget *calendarWidgetEnd;
    QFrame *line;
    QPushButton *BttnSet;

    void setupUi(QDialog *SelectInvervalDailog)
    {
        if (SelectInvervalDailog->objectName().isEmpty())
            SelectInvervalDailog->setObjectName(QString::fromUtf8("SelectInvervalDailog"));
        SelectInvervalDailog->resize(659, 308);
        calendarWidgetStart = new QCalendarWidget(SelectInvervalDailog);
        calendarWidgetStart->setObjectName(QString::fromUtf8("calendarWidgetStart"));
        calendarWidgetStart->setGeometry(QRect(0, 60, 321, 181));
        calendarWidgetEnd = new QCalendarWidget(SelectInvervalDailog);
        calendarWidgetEnd->setObjectName(QString::fromUtf8("calendarWidgetEnd"));
        calendarWidgetEnd->setGeometry(QRect(340, 60, 321, 181));
        line = new QFrame(SelectInvervalDailog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(320, 0, 20, 301));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        BttnSet = new QPushButton(SelectInvervalDailog);
        BttnSet->setObjectName(QString::fromUtf8("BttnSet"));
        BttnSet->setGeometry(QRect(0, 260, 661, 41));

        retranslateUi(SelectInvervalDailog);

        QMetaObject::connectSlotsByName(SelectInvervalDailog);
    } // setupUi

    void retranslateUi(QDialog *SelectInvervalDailog)
    {
        SelectInvervalDailog->setWindowTitle(QApplication::translate("SelectInvervalDailog", "Dialog", nullptr));
        BttnSet->setText(QApplication::translate("SelectInvervalDailog", "\320\222\320\270\320\261\320\265\321\200\321\226\321\202\321\214 \320\264\320\260\321\202\321\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SelectInvervalDailog: public Ui_SelectInvervalDailog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTINVERVALDAILOG_H
