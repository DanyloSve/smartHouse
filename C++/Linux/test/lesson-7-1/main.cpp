#include "mainwindow.h"
#include "anothermenu.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AnotherMenu window;

    window.resize(350, 200);
    window.setWindowIcon(QIcon("download.png"));
    window.setWindowTitle("AnotherMenu");
    window.show();
    return a.exec();
}
