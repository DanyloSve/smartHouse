#include "selectinvervaldailog.h"
#include "ui_selectinvervaldailog.h"

#include <QLocale>

SelectInvervalDailog::SelectInvervalDailog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectInvervalDailog)
{
    ui->setupUi(this);
    QLocale locale = {QLocale::Ukrainian};
    ui->calendarWidgetEnd->setLocale(locale);
    ui->calendarWidgetStart->setLocale(locale);
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

void SelectInvervalDailog::showSelectedDateTime()
{
      QLocale locale;
      ui->BttnSet->setText("З " + locale.toString(ui->calendarWidgetStart->selectedDate(), "dd.MM.yyyy") + " " +
                          " "+"до" + " " +locale.toString(ui->calendarWidgetEnd->selectedDate(), "dd.MM.yyyy"));
}

void SelectInvervalDailog::on_BttnSet_clicked()
{

    QDate start(ui->calendarWidgetStart->selectedDate());
    QDate end(ui->calendarWidgetEnd->selectedDate());
    emit sGetDateTimeInterval(start, end);
    this->close();
}
