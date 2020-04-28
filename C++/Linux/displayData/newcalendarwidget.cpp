#include <QPainter>
#include "newcalendarwidget.h"

NewCalendarWidget::NewCalendarWidget(QWidget *parent)
   : QCalendarWidget(parent)
{
   m_currentDate = QDate::currentDate();
   m_outlinePen.setColor(Qt::red);
   m_transparentBrush.setColor(Qt::transparent);
}

NewCalendarWidget::~NewCalendarWidget()
{

}

void NewCalendarWidget::setColor(QColor& color)
{
   m_outlinePen.setColor(color);
}

QColor NewCalendarWidget::getColor()
{
    return (m_outlinePen.color());
}

void NewCalendarWidget::addDate(const QDate &date)
{
    if (!mDates.contains(date))
    {
        mDates.push_back(date);
    }
}

QVector<QDate> NewCalendarWidget::getDates()
{
    return  mDates;
}

void NewCalendarWidget::removeDate(const QDate &date)
{
    for (int i{0}; i < mDates.size() - 1; i++)
    {
        if (date == mDates[i])
        {
         mDates.remove(i);
         break;
        }
    }
}


void NewCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
   QCalendarWidget::paintCell(painter, rect, date);

   if (date == m_currentDate)
   {
       painter->setPen(m_outlinePen);
       painter->setBrush(m_transparentBrush);
       painter->drawRect(rect.adjusted(0, 0, -1, -1));
   }

    if (!mDates.isEmpty())
    {
       if( mDates.contains(date) )
       {
           painter->setPen(Qt::blue);
           painter->setBrush(m_transparentBrush);
           painter->drawRect(rect.adjusted(0, 0, -1, -1));
       }
    }
}
