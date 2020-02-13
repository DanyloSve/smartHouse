#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QFrame>
#include <QGridLayout>

class Cursors : public QWidget
{
public :
    Cursors(QWidget *parent = nullptr);
};

Cursors::Cursors(QWidget *parent)   : QWidget(parent)
{
    QFrame *frame1 = new QFrame(this);
    frame1->setFrameStyle(QFrame::Box);
    frame1->setCursor(Qt::WaitCursor);

    QFrame *frame2 = new QFrame(this);
    frame2->setFrameStyle(QFrame::Box);
    frame2->setCursor(Qt::SizeAllCursor);

    QFrame *frame3 = new QFrame(this);
    frame3->setFrameStyle(QFrame::Box);
    frame3->setCursor(Qt::PointingHandCursor);

    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(frame1, 0, 0);
    grid->addWidget(frame2, 0, 1);
    grid->addWidget(frame3, 0 ,3);

    setLayout(grid);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Cursors window;

    window.resize(350, 150);
    window.setWindowTitle("Cursors");
    window.show();

    return a.exec();
}
