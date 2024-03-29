#include "mainwindow.h"
#include <QApplication>
#include "myserialport.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
   MySerialport ms;
    return a.exec();
}
