#ifndef PLUSMINUS_H
#define PLUSMINUS_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLabel>

class PlusMinus : public QWidget
{
  Q_OBJECT

public:
    PlusMinus(QWidget *parent = nullptr);

private slots:
    void OnPlus();
    void OnMinus();

private:
    QLabel *lbl;
};


#endif // PLUSMINUS_H
