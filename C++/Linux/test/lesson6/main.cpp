#include "mainwindow.h"

#include <QApplication>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget window;
    window.resize(250, 150);
    window.move(300, 300);
    window.setWindowTitle("ToolTip");
    window.setToolTip("QWidget");
    window.setWindowIcon(QIcon("download.png"));
    window.show();

    return a.exec();
}
