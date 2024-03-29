#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMainWindow>
#include <QDebug>
#include <QVector>
#include <QDateTime>
#include <QIODevice>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString init();
   QVector<QString> allQuery();
    int doorQuery(int m);
   int openAllDoor();
   int openDoor(int m);
      QSerialPort serial;
private slots:
   // void on_pushButton_clicked();

   // void on_pushButton_2_clicked();

   void on_queryButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
