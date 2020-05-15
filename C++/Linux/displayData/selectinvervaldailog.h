#ifndef SELECTINVERVALDAILOG_H
#define SELECTINVERVALDAILOG_H

#include <QDialog>
#include <QDate>

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
    void sGetDateTimeInterval(QDate start, QDate end);

private slots:

    void on_calendarWidgetStart_selectionChanged();

    void on_calendarWidgetEnd_selectionChanged();

    void showSelectedDateTime();

    void on_BttnSet_clicked();

private:
    Ui::SelectInvervalDailog *ui;
};

#endif // SELECTINVERVALDAILOG_H
