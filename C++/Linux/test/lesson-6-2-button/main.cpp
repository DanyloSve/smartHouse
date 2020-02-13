#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QPushButton>

class MyButton : public QWidget
{
  public:
    MyButton(QWidget *parent = nullptr);
};

MyButton::MyButton(QWidget *parent) : QWidget(parent)
{
    QPushButton *quitBttn = new QPushButton("Quit", this);
    quitBttn->setGeometry(50, 40 , 75, 30);

    connect(quitBttn, &QPushButton::clicked ,qApp, &QApplication::quit);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MyButton window;
    window.resize(250, 150);
    window.setWindowTitle("QPushButton");
    window.show();

    return a.exec();
}
