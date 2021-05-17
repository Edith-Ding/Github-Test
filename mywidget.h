#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include "sudo.h"
#include <QString>
#include <QMediaPlayer>
#include<QDialog>
#include <QTime>
#include <QTimer>
#include <QDateTime>
#include <QLCDNumber>


class MyWidget : public QWidget
{
    Q_OBJECT

public:
    QMediaPlayer *music;

    explicit MyWidget(QWidget *parent = 0);
    void init(int cnt);
    void Check();
    bool judge();
    void paintEvent(QPaintEvent *);
    ~MyWidget();

private:
    QPushButton ***b;
    QPushButton *b1;
    QPushButton *b2;
    QPushButton *b3;
    QPushButton *b4;
    QPushButton *b5;
    QPushButton *b6;
    QPushButton *b7;
    QPushButton *b8;
    QPushButton *b9;
    QPushButton *b10;
    QPushButton *b11;

    QPushButton *seb1;
    QPushButton *seb2;
    QPushButton *seb3;
    QPushButton *seb4;
    QPushButton *seb5;
    QPushButton *seb6;
    QPushButton *seb7;
    QPushButton *seb8;
    QPushButton *seb9;
    QPushButton *seb10;

    QLabel *l1;
    QLabel *l2;
    QLabel *l3;
    QString str;

    sudo *s;
    int m;
    int n;
    int cnt;

    QDialog *log;
    QLCDNumber *lcd;
    QTimer *timer1000;
    int steps;
    bool isStart;

public slots:
    void ShowSu();
    void updateTime1000();


};

#endif // MYWIDGET_H
