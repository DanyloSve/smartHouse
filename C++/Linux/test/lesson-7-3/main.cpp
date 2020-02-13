#include "mainwindow.h"
#include "toolbar.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Toolbar window;

    window.resize(300, 200);
    window.setWindowTitle("QToolBar");
    window.setWindowIcon(QIcon("download.png"));
    window.show();

    return a.exec();
}
