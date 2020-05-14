#include "selectinvervaldailog.h"
#include "ui_selectinvervaldailog.h"

#include <QLocale>

SelectInvervalDailog::SelectInvervalDailog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectInvervalDailog)
{
    ui->setupUi(this);
    ui->timeEditStart->setDisplayFormat("HH:mm");
    ui->timeEditEnd->setDisplayFormat("HH:mm");

}

SelectInvervalDailog::~SelectInvervalDailog()
{
    delete ui;
}

void SelectInvervalDailog::on_calendarWidgetStart_selectionChanged()
{
    showSelectedDateTime();
}

void SelectInvervalDailog::on_calendarWidgetEnd_selectionChanged()
{
    showSelectedDateTime();
}

void SelectInvervalDailog::on_timeEditStart_timeChanged(const QTime &time)
{
    showSelectedDateTime();
}


void SelectInvervalDailog::showSelectedDateTime()
{
      QLocale locale;
      ui->BttnSet->setText("З " + locale.toString(ui->timeEditStart->time(), "hh : mm") + " "+
                           locale.toString(ui->calendarWidgetStart->selectedDate(), "dd.MM.yyyy") + " " +
                          "до" + " " + locale.toString(ui->timeEditEnd->time(), "hh : mm") + " "+
                          locale.toString(ui->calendarWidgetEnd->selectedDate(), "dd.MM.yyyy"));
}

void SelectInvervalDailog::on_timeEditEnd_timeChanged(const QTime &time)
{
    showSelectedDateTime();
}

void SelectInvervalDailog::on_BttnSet_clicked()
{

    QDateTime start(ui->calendarWidgetStart->selectedDate(),ui->timeEditStart->time());
    QDateTime end(ui->calendarWidgetEnd->selectedDate(),ui->timeEditEnd->time());
    emit sGetDateTimeInterval(start, end);
    this->close();
}
