#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QMainWindow>
#include <QApplication>

class Toolbar : public QMainWindow
{
    Q_OBJECT
public:
    Toolbar(QWidget *parent = nullptr);
};

#endif // TOOLBAR_H
