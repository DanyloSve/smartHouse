#ifndef SELECTINVERVALDAILOG_H
#define SELECTINVERVALDAILOG_H

#include <QDialog>
#include <QDateTime>

namespace Ui {
class SelectInvervalDailog;
}

class SelectInvervalDailog : public QDialog
{
    Q_OBJECT

public:
    explicit SelectInvervalDailog(QWidget *parent = nullptr);
    ~SelectInvervalDailog();

signals:
    void sGetDateTimeInterval(QDateTime start, QDateTime end);

private slots:

    void on_calendarWidgetStart_selectionChanged();

    void on_calendarWidgetEnd_selectionChanged();

    void on_timeEditStart_timeChanged(const QTime &time);

    void showSelectedDateTime();

    void on_timeEditEnd_timeChanged(const QTime &time);


    void on_BttnSet_clicked();

private:
    Ui::SelectInvervalDailog *ui;
};

#endif // SELECTINVERVALDAILOG_H
