#include "mainwindow.h"
#include "simplemenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Simplemenu window;

    window.resize(250, 150);
    window.setWindowTitle("Simple menu");
    window.show();

    return a.exec();
}
