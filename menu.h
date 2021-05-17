#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QPushButton>
#include "mywidget.h"
#include <QLabel>

class menu : public QWidget
{
    Q_OBJECT
public:
    explicit menu(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void changeWin();
    ~menu();

signals:

public slots:

private:
    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;
    MyWidget win;
    QLabel *label;
};

#endif // MENU_H
