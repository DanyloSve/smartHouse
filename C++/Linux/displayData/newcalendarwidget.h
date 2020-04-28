
#ifndef NEWCALENDARWIDGET_H
#define NEWCALENDARWIDGET_H

#include<QCalendarWidget>
#include <QColor>
#include <QDate>
#include <QPen>
#include <QBrush>

#include <QVector>
#include <QDate>


class NewCalendarWidget : public QCalendarWidget
{
Q_OBJECT

Q_PROPERTY(QColor color READ getColor WRITE setColor)

public:
   NewCalendarWidget(QWidget *parent = nullptr);
   ~NewCalendarWidget();

   void setColor(QColor& color);
   QColor getColor();
   void addDate(const QDate &date);
   QVector <QDate> getDates();
   void removeDate(const QDate &date);

protected:
   virtual void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const;

private:
   QVector <QDate> mDates;
   QDate m_currentDate;
   QPen m_outlinePen;
   QBrush m_transparentBrush;
};

#endif // NEWCALENDARWIDGET_H
