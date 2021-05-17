#include "menu.h"
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QPainter>
#include <QFont>
#include <QRectF>
#include <QVBoxLayout>
#include "mywidget.h"
#include <QPen>
#include <QIcon>
#include <QMessageBox>

menu::menu(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowTitle("菜单");
    setFixedSize(800,500);
    move(550,200);
    QFont font2("黑体",20);
    QFont font3("华文行楷",45);
    label=new QLabel("数独游戏",this);
    label->setFont(font3);
    label->move(300,200);

    b1=new QPushButton("开始游戏",this);
    b1->setMinimumSize(100,40);
    b1->move(350,350);
    b1->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,0);"
                      "border-radius:10px;"
                      "font:bold 28px 华文行楷;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b2=new QPushButton("退出游戏",this);
    b2->setMinimumSize(100,40);
    b2->move(350,400);
    b2->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,0);"
                      "border-radius:10px;"
                      "font:bold 28px 华文行楷;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b3=new QPushButton("关于游戏",this);
    b3->setMinimumSize(100,40);
    b3->move(350,450);
    b3->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,0);"
                      "border-radius:10px;"
                      "font:bold 28px 华文行楷;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    connect(b1,&QPushButton::clicked,this,[=](){changeWin();win.init(81);win.ShowSu();win.music->play();});
    connect(b2,&QPushButton::clicked,this,&menu::close);
    connect(b3,&QPushButton::clicked,this,[=](){
        QMessageBox::about(this,"关于游戏","数独盘面是个九宫，每一宫又分为九个小格。在这八十一格中给出一定的已知数字和解题条件，利用逻辑和推理，在其他的空格上填入1-9的数字。使1-9每个数字在每一行、每一列和每一宫中都只出现一次，所以又称“九宫格”。                               "
                                " ——软件1802班丁伟轩，刘洋"
                                "                             version 1.1");
    });
}

void menu::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/menu1.jpg"));
}

void menu::changeWin()
{
    win.show();
    this->hide();
}

menu::~menu()
{

}

