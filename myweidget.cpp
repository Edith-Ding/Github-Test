#include "mywidget.h"
#include <QPainter>
#include <QPen>
#include <QLayout>
#include <QLabel>
#include <QString>
#include <time.h>
#include <QFont>
#include <QDebug>
#include <QRectF>
#include <QMediaPlayer>
#include <QDialog>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QLCDNumber>
#include <QPalette>
#include <QMediaPlaylist>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    cnt=40;
    str=" ";
    m=0;
    n=0;
           setStyleSheet(
                      "QPushButton{"
                      "border-style:outset;"
                      "border-width:4px;"
                      "padding:6px;"
                      "}"
                      "QLabel{"
                      "font:bold 20px Microsoft YaHei;"
                      "border-radius: 4px;"
                      "color:rgba(0,0,0,200);"
                      "}"
                      );

    setFixedSize(800,800);
    move(550,100);
    setWindowTitle("数独游戏");

    srand((unsigned)time(NULL));

    lcd=new QLCDNumber();
    lcd->setParent(this);
    lcd->resize(200,100);
    lcd->setDigitCount(8);
    lcd->setPalette(Qt::cyan);
    lcd->setSegmentStyle(QLCDNumber::Flat);
    QPalette lcdpat=lcd->palette();
    lcdpat.setColor(QPalette::Normal,QPalette::WindowText,Qt::black);
    lcd->setPalette(lcdpat);
    lcd->display(0);
    isStart=false;
    timer1000=new QTimer;
    steps=0;
    connect(timer1000,SIGNAL(timeout()),this,SLOT(updateTime1000()));


    QMediaPlaylist *list=new QMediaPlaylist();
    list->addMedia(QUrl("qrc:/new/prefix1/111.mp3"));
    list->setPlaybackMode(QMediaPlaylist::Loop);
    music=new QMediaPlayer();
    connect(music,SIGNAL(positionChanged(qint64)),this,SLOT(positionChanged(qint64)));
    music->setPlaylist(list);
    music->setVolume(50);

    QHBoxLayout *mainLayout=new QHBoxLayout();
    QVBoxLayout *lLayout=new QVBoxLayout();
    QFont font("Times New Roman");

    l3=new QLabel("计时器:");
    b9=new QPushButton("计时");
    b9->setMinimumSize(40,40);
    connect(b9,&QPushButton::clicked,this,[=](){
        if(!isStart)
        {
            timer1000->start(1000);
            b9->setDisabled(true);
            b10->setEnabled(true);
        }
        isStart=(!isStart);
    });
    b9->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b10=new QPushButton("清零");
    b10->setEnabled(false);
    connect(b10,&QPushButton::clicked,this,[=](){
        b10->setDisabled(true);
        b9->setEnabled(true);
        timer1000->stop();
        steps=0;
        lcd->display("0");
        isStart=false;
    });
    b10->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    l1=new QLabel("难度选择:");
    b1=new QPushButton("容易");
    b1->setMinimumSize(40,40);
    connect(b1,&QPushButton::clicked,this,[=](){cnt=40;init(cnt);ShowSu();});
    b1->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b2=new QPushButton("中等");
    b2->setMinimumSize(40,40);
    connect(b2,&QPushButton::clicked,this,[=](){cnt=45;init(cnt);ShowSu();});
    b2->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b3=new QPushButton("困难");
    b3->setMinimumSize(40,40);
    connect(b3,&QPushButton::clicked,this,[=](){cnt=50;init(cnt);ShowSu();});
    b3->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");



    l2=new QLabel("操作选择:");
    b4=new QPushButton("一键清空");
    b4->setMinimumSize(40,40);
    connect(b4,&QPushButton::clicked,this,[=](){
        int nRet=QMessageBox::question(NULL,"提示","努力了这么久，确定要清空吗？",QMessageBox::Yes,QMessageBox::No);
        if(QMessageBox::Yes==nRet){
            this->ShowSu();
        }
    });
    b4->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px; "
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b5=new QPushButton("检验");
    b5->setMinimumSize(40,40);
    connect(b5,&QPushButton::clicked,this,[=](){Check();});
    b5->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b6=new QPushButton("退出");
    b6->setMinimumSize(40,40);
    connect(b6,&QPushButton::clicked,this,[=](){
        int nRet=QMessageBox::question(NULL,"提示","这么好玩的游戏，不会真的有人想退出吧？",QMessageBox::Yes,QMessageBox::No);
        if(QMessageBox::Yes==nRet){
            this->close();
        }
    });
    b6->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b7=new QPushButton("音乐开");
    b7->setMinimumSize(40,40);
    connect(b7,&QPushButton::clicked,music,[=](){
        QString qtr1=b7->text();
        if(qtr1=="音乐关")
        {
            music->play();
            b7->setText("音乐开");
        }
        else if(qtr1=="音乐开")
        {
            music->pause();
            b7->setText("音乐关");
        }
    });
    b7->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b8=new QPushButton("一键填满");
    b8->setMinimumSize(40,40);
    connect(b8,&QPushButton::clicked,this,[=](){s->DigHole(0);ShowSu();});
    b8->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    b11=new QPushButton("提交");
    b11->setMinimumSize(40,40);
    connect(b11,&QPushButton::clicked,this,[=](){
        if(this->judge())
            QMessageBox::about(this,"提示","大佬，我们交朋友吧！^_^");
        else
            QMessageBox::about(this,"提示","游戏还未完成，请您继续努力！");
    });
    b11->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 20px 楷体;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

   // lLayout->setSpacing(50);
    lLayout->addWidget(l3);
    lLayout->addWidget(lcd);
    lLayout->addWidget(b9);
    lLayout->addWidget(b10);
    lLayout->addWidget(b7);
    lLayout->addWidget(l1);
    lLayout->addWidget(b1);
    lLayout->addWidget(b2);
    lLayout->addWidget(b3);
    lLayout->addWidget(l2);
    lLayout->addWidget(b4);
    lLayout->addWidget(b8);
    lLayout->addWidget(b5);
    lLayout->addWidget(b11);
    lLayout->addWidget(b6);

    QVBoxLayout *rLayout=new QVBoxLayout();
    QGridLayout *paLayout=new QGridLayout();
    paLayout->setMargin(75);
    paLayout->setSpacing(3);

    init(cnt);
    b=new QPushButton **[9];
    for(int i=0;i<9;i++)
    {
        b[i]=new QPushButton*[9];
        for(int j=0;j<9;j++)
        {
            b[i][j]=new QPushButton;
            b[i][j]->setFixedSize(55,50);
            b[i][j]->setFont(font);
            paLayout->addWidget(b[i][j],i,j);
            b[i][j]->setAccessibleName(QString::number(i*10+j));
        }
    }


    QHBoxLayout *seLayout=new QHBoxLayout();

    seb1=new QPushButton("1");
    seb1->setMinimumSize(40,40);
    connect(seb1,&QPushButton::clicked,this,[=](){str=seb1->text();});
    seb1->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    seb2=new QPushButton("2");
    seb2->setMinimumSize(40,40);
    connect(seb2,&QPushButton::clicked,this,[=](){str=seb2->text();});
    seb2->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    seb3=new QPushButton("3");
    seb3->setMinimumSize(40,40);
    connect(seb3,&QPushButton::clicked,this,[=](){str=seb3->text();});
    seb3->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");

    seb4=new QPushButton("4");
    seb4->setMinimumSize(40,40);
    connect(seb4,&QPushButton::clicked,this,[=](){str=seb4->text();});
    seb4->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");


    seb5=new QPushButton("5");
    seb5->setMinimumSize(40,40);
    connect(seb5,&QPushButton::clicked,this,[=](){str=seb5->text();});
    seb5->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");


    seb6=new QPushButton("6");
    seb6->setMinimumSize(40,40);
    connect(seb6,&QPushButton::clicked,this,[=](){str=seb6->text();});
    seb6->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");


    seb7=new QPushButton("7");
    seb7->setMinimumSize(40,40);
    connect(seb7,&QPushButton::clicked,this,[=](){str=seb7->text();});
    seb7->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");


    seb8=new QPushButton("8");
    seb8->setMinimumSize(40,40);
    connect(seb8,&QPushButton::clicked,this,[=](){str=seb8->text();});
    seb8->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");


    seb9=new QPushButton("9");
    seb9->setMinimumSize(40,40);
    connect(seb9,&QPushButton::clicked,this,[=](){str=seb9->text();});
    seb9->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");


    seb10=new QPushButton("×");
    seb10->setMinimumSize(40,40);
    connect(seb10,&QPushButton::clicked,this,[=](){str="";});
    seb10->setStyleSheet("QPushButton{"
                      "background-color:rgba(255,225,255,100);"
                      "border-color:rgba(0,0,0,100);"
                      "border-radius:10px;"
                      "font:bold 25px;"
                      "}"
                      "QPushButton:hover{"
                      "background-color:rgba(255,255,255,250);"
                      "border-color:rgba(0,0,0,250);"
                      "color:rgba(0,0,0,200);"
                      "}");


    seLayout->addWidget(seb1);
    seLayout->addWidget(seb2);
    seLayout->addWidget(seb3);
    seLayout->addWidget(seb4);
    seLayout->addWidget(seb5);
    seLayout->addWidget(seb6);
    seLayout->addWidget(seb7);
    seLayout->addWidget(seb8);
    seLayout->addWidget(seb9);
    seLayout->addWidget(seb10);

    rLayout->addLayout(paLayout);
    rLayout->addLayout(seLayout);

    mainLayout->addLayout(lLayout);
    mainLayout->addLayout(rLayout);

    this->setLayout(mainLayout);
}

void MyWidget::init(int cnt)
{
    s=new sudo();
    while(!(s->is_full(0,1)));
    s->DigHole(cnt);
}

void MyWidget::ShowSu()
{   
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(s->hole[i][j]==0)
            {
                b[i][j]->setText(QString::number(s->sudu[i][j]));
                b[i][j]->setStyleSheet("QPushButton{"
                                       "background-color:rgba(128,138,135,250);"
                                       "border-color:rgba(0,0,0,150);"
                                       "border-width:4px;"
                                       "border-radius:5px;"
                                       "font:bold 28px;"
                                       "color:rgba(0,0,0,250);"
                                       "}");
               b[i][j]->setDisabled(true);
            }
            else if(s->hole[i][j]==1)
            {
                 b[i][j]->setText(" ");
                 b[i][j]->setStyleSheet("QPushButton{"
                                        "color :blue;"
                                        "font:bold 28px;"
                                        "background-color:rgba(255,255,255,50);"
                                        "border-color:rgba(0,0,0,150);"
                                        "border-width:4px;"
                                        "border-radius:5px;}"
                                        "QPushButton:hover{"
                                        "background-color:rgba(255,255,255,250);"
                                        "border-color:rgba(0,0,0,250);"
                                        "}");
                 connect(b[i][j],&QPushButton::pressed,this,[=](){b[i][j]->setText(str);b[i][j]->setStyleSheet("QPushButton{"
                                                                                                               "color :green;"
                                                                                                               "font:bold 28px;"
                                                                                                               "border-width:4px;"
                                                                                                               "background-color:rgba(255,225,255,50);"
                                                                                                               "border-color:rgba(0,0,0,150);"
                                                                                                               "border-radius:5px;}"
                                                                                                               "QPushButton:hover{"
                                                                                                               "background-color:rgba(255,255,255,250);"
                                                                                                               "border-color:rgba(0,0,0,250);"
                                                                                                               "}");});
                 b[i][j]->setDisabled(false);
            }
        }
    }

}

void MyWidget::Check()
{
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(s->hole[i][j]==1 && b[i][j]->text()!=" ")
            {
               QString _str=b[i][j]->text();
               for(int m=0;m<9;m++)
               {
                   if(b[i][m]->text()==_str && m!=j)
                   {
                       b[i][j]->setStyleSheet("QPushButton{"
                                              "color :red;"
                                              "font:bold 28px;"
                                              "border-width:4px;"
                                              "background-color:rgba(255,255,255,50);"
                                              "border-color:rgba(0,0,0,150);"
                                              "border-radius:5px;}"
                                              "QPushButton:hover{"
                                              "background-color:rgba(255,255,255,250);"
                                              "border-color:rgba(0,0,0,250);"
                                              "color:rgba(0,0,0,200);"
                                              "}");
                   }
               }
               for(int n=0;n<9;n++)
               {
                   if(b[n][j]->text()==_str && n!=i)
                   {
                       b[i][j]->setStyleSheet("QPushButton{"
                                              "color :red;"
                                              "font:bold 28px;"
                                              "border-width:4px;"
                                              "background-color:rgba(255,255,255,50);"
                                              "border-color:rgba(0,0,0,150);"
                                              "border-radius:5px;}"
                                              "QPushButton:hover{"
                                              "background-color:rgba(255,255,255,250);"
                                              "border-color:rgba(0,0,0,250);"
                                              "color:rgba(0,0,0,200);"
                                              "}");
                   }
               }
               for(int n=i/3*3;n<(i/3*3+3);n++)
               {
                   for(int m=j/3*3;m<(j/3*3+3);m++)
                   {
                       if(b[n][m]->text()==_str && m!=j && n!=i)
                       {
                           b[i][j]->setStyleSheet("QPushButton{"
                                                  "color :red;"
                                                  "font:bold 28px;"
                                                  "border-width:4px;"
                                                  "background-color:rgba(255,255,255,50);"
                                                  "border-color:rgba(0,0,0,150);"
                                                  "border-radius:5px;}"
                                                  "QPushButton:hover{"
                                                  "background-color:rgba(255,255,255,250);"
                                                  "border-color:rgba(0,0,0,250);"
                                                  "color:rgba(0,0,0,200);"
                                                  "}");

                       }
                   }
               }
            }

        }
    }

}


void MyWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QRectF rect(192,117,525,480);
    QPen pen1(Qt::black,6);
    QPen pen2(Qt::black,3);

    p.setPen(pen1);
    p.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/shuishan.jpg"));
    p.drawRect(rect);
    p.setPen(pen2);
    p.drawLine(367,116,367,596);
    p.drawLine(541,116,541,596);
    p.drawLine(192,277,717,277);
    p.drawLine(192,436,717,436);

}

bool MyWidget::judge()
{
    for(int i=0;i<9;i++)
        for(int j=0;j<9;j++)
        {
            if(b[i][j]->text()=="")
                return false;
            for(int l=0;l<9;l++)
            {
                if(b[i][j]->text()==b[i][l]->text()&&l!=j)
                    return false;
                else if(b[i][j]->text()==b[l][j]->text()&&l!=i)
                    return false;
            }
            int m=(i/3)*3,n=(j/3)*3;
            for(int q=m;q<m+3;q++)
                for(int w=n;w<n+3;w++)
                {
                    if(b[i][j]->text()==b[q][w]->text()&&q!=i&&w!=j)
                        return false;
                }
        }
    return true;
}

void MyWidget::updateTime1000()
{
    steps++;
    lcd->display(QString("%1").arg(steps));
}


MyWidget::~MyWidget()
{

}
