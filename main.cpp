#include "mainwindow.h"

#include <QApplication>
#include<QSplashScreen>
#include<QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QSplashScreen *splashScreen=new QSplashScreen;
    splashScreen->setPixmap(QPixmap(":images/splashImg.png"));
    splashScreen->show();
    MainWindow w;
    QTimer::singleShot(4950,splashScreen,SLOT(close()));
    QTimer::singleShot(5000,&w,SLOT(show()));
    //w.show();
    return a.exec();
}
