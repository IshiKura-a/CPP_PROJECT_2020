#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  //a 是 应用程序对象,应用程序对象有且仅有一个
    MainWindow w;
    w.show();
    w.setWindowTitle("latex解析与计算");
    return a.exec();
}
