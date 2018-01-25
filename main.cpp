#include "mainwindow.h"
#include <QApplication>

#include "global.h"

bool IS_useinPath = false;
QString outFliePath = "";
int gcyptLV = 0;
int maxthread_num = 0;
Signalmange signalmanage;



QStringList Jedi_encyptmode::thread_static_list;// 静态成员变量，再类中声明，类外定义。

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
