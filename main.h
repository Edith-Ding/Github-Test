#include "menu.h"
#include <QApplication>
#include <QSplashScreen>
#include <QDateTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap lodingPix(":/new/prefix1/bugei.jpg");
    QSplashScreen splash(lodingPix);
    splash.show();
    QDateTime time = QDateTime::currentDateTime();
        QDateTime currentTime = QDateTime::currentDateTime();
        while (time.secsTo(currentTime) <= 1)
        {
            currentTime = QDateTime::currentDateTime();
            a.processEvents();
        };

    a.processEvents();
    menu m;
    m.show();
    splash.finish(&m);
    return a.exec();
}
