#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    w.setFixedSize(350, 550);   //固定窗体大小 禁止窗体通过鼠标放大缩小
    w.setGeometry(QRect(500, 200, 432, 628));

    return a.exec();
}
