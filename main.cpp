#include "w_battle.h"
#include "worship.h"
#include"mymenu.h"
#include"Button_Ship.h"
//#include"attackthread.h"
//#include "battle.h"
#include<QDebug>
#include <QApplication>
#include <QWidget>
#include <QImage>
#include <QResource>
#include<unistd.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMenu w;
    w.show();
    return a.exec();
}
