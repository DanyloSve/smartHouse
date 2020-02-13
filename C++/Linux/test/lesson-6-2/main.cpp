#include "mainwindow.h"
#include "checkable.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Checkable window;
    window.resize(250, 180);
    window.setWindowTitle("Checkable menu");
    window.show();
    return a.exec();
}
