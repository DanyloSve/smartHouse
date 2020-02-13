#include "mainwindow.h"
#include "plusminus.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PlusMinus window;
    window.resize(300, 190);
    window.setWindowTitle("PLus minus");
    window.show();

    return a.exec();
}
