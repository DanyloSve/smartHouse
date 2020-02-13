#include "mainwindow.h"
#include "skeleton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Skeleton window;

    window.resize(350, 250);
    window.setWindowTitle("Application skeleton");
    window.setWindowIcon(QIcon("download.png"));
    window.show();
    return a.exec();
}
