#include "toolbar.h"

#include <QToolBar>
#include <QIcon>
#include <QAction>

Toolbar::Toolbar(QWidget *parent) : QMainWindow(parent)
{
    QPixmap newpix("save.png");
    QPixmap openpix("open.png");
    QPixmap quitpix("quit.png");

    QToolBar *toolbar = addToolBar("main toolbar");

    toolbar->addAction(QIcon(newpix), "New File");
    toolbar->addAction(QIcon(openpix), "Open File");
    toolbar->addSeparator();
    QAction *quit = toolbar->addAction(QIcon(quitpix), "Quit Appolication");

    connect(quit, &QAction::triggered, qApp, &QApplication::quit);

}
