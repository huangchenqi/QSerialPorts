#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->queryTextEdit->append(init());
allQuery();//   QVector<QString> qs;
//   qs=allQuery();QVector<QString>::iterator iter;
//   for(iter=qs.begin();iter=qs.end();iter++){ ui->queryTextEdit->append(*iter);}
}

MainWindow::~MainWindow()
{
    delete ui;
}
QString MainWindow::init(){  //串口初始化
      QString q;
     serial.setPortName(QString("COM7"));
     serial.open(QIODevice::ReadWrite);
     if(serial.isOpen()){
     qDebug()<<QString::fromLocal8Bit("串口已经打开！")<<endl;
      q=QString::fromLocal8Bit("1");//串口打开。
     }
    else{
      qDebug()<<QString::fromLocal8Bit("串口打开失败！")<<endl;
     q=QString::fromLocal8Bit("0");//串口未打开。
     }
return q;
}
QVector<QString> MainWindow::allQuery(){
    serial.setPortName(QString("COM7"));
     serial.open(QIODevice::ReadWrite);
     if(serial.isOpen()){
        qDebug()<<QString::fromLocal8Bit("查询串口已经打开！")<<endl;
    }else{
        qDebug()<<QString::fromLocal8Bit("查询串口未打开！");
       ui->queryTextEdit->append(QString::fromLocal8Bit("查询串口未打开！"));
       init();}

        QByteArray query;
        query[0]=0x07;
        query[1]=0x12;
        query[2]=0x03;
        query[3]=0xE4;
        if(serial.QSerialPort::open(QIODevice::ReadWrite)){
                serial.write(query);
        qDebug()<<QString::fromLocal8Bit("查询串口！");
        }
        QDateTime startTime=QDateTime::currentDateTime();

        QByteArray queryStatus;
        QByteArray queryLockStatus;
        int queryStatusLength=7,outTime=2;
        queryStatus=serial.readAll();
        queryLockStatus.clear();
        while(true){
               QDateTime systemTime=QDateTime::currentDateTime();
             if(systemTime.secsTo(startTime)>outTime){
                 qDebug()<<QString::fromLocal8Bit("查询响应超时")<<endl;
             }
              if(queryStatus.size()==0){
                  continue;
              }
              if(queryStatus.size()==queryStatusLength){
                 queryLockStatus=queryStatus;
                 break;
              }
}


        QByteArray q;

             for(int i=5;i>2;i--){

            for(int j=0;j<8;j++){
                q.append((queryLockStatus[i]>>j)&0x01);
            }

        }
        QVector<QString>queryLock;
       for(int i=0;i<q.size();i++){//
           QString qs=QString::number(q[i],10);
         qDebug()<<qs;//ui->queryTextEdit->append(qs); // int ql=qs.toInt();
           queryLock[i]=qs;
       }

      return queryLock;
}
//返回某柜门查询结果
int MainWindow::doorQuery(int m){
    QSerialPort *port;
    port=new QSerialPort("COM7");
    if(port==NULL)
    {qDebug()<<QString::fromLocal8Bit("柜门串口未打开！");init();}
     else{
     qDebug()<<QString::fromLocal8Bit("柜门串口已经打开！")<<endl;}
        QByteArray query;
        query[0]=0x07;
        query[1]=0x12;
        query[2]=0x03;
        query[3]=0xE4;
        port->write(query);
        QDateTime startTime=QDateTime::currentDateTime();
       QByteArray queryStatus;
       QByteArray queryLockStatus;
       int queryStatusLength=7,outTime=2;
       queryLockStatus.clear();
       queryStatus=port->readAll();
       while(true){
           QDateTime systemTime=QDateTime::currentDateTime();

            if(systemTime.secsTo(startTime)>outTime){
                qDebug()<<QString::fromLocal8Bit("柜门响应超时")<<endl;
             if(queryStatus.size()==0){
                 continue;
             }
             if(queryStatus.size()==queryStatusLength){
                queryLockStatus=queryStatus;
                break;
             }
}
       }

       QByteArray q;
       int i,j;
       for(i=5;i>2;i--){
           for(j=0;j<8;j++){
               q.append((queryLockStatus[i]>>j)&0x01);
           }

       }
       QVector<int>queryLock;
       int doorLock;
      for(i=0;i<q.size();i++){//
          QString qs=QString::number(q[i],10);
          int ql=qs.toInt();//
          queryLock[i]=ql;
          if(i==m-1){
              doorLock=queryLock[i];
          }
      }

     return doorLock;

}
int MainWindow::openAllDoor(){//打开所有柜门
    QSerialPort *port;
    port=new QSerialPort("COM7");
    if(port==NULL)
    {qDebug()<<QString::fromLocal8Bit("开全串口未打开！");init();}
     else{
     qDebug()<<QString::fromLocal8Bit("开全串口已经打开！")<<endl;}
     QByteArray allDoor;
    allDoor[0]=0x07;
    allDoor[1]=0x11;
    allDoor[2]=0x03;
    allDoor[3]=0xE6;
    port->write(allDoor);
    QDateTime startTime=QDateTime::currentDateTime();
   QByteArray queryOpenStatus;
   QByteArray queryOpenLockStatus;
   int openAllDoorStatus,queryOpenStatusLength,outTime;//openAllDoor为0打开失败，1为成功
   queryOpenLockStatus.clear();
   queryOpenStatus=port->readAll();
   while(true){
       QDateTime systemTime=QDateTime::currentDateTime();
        if(systemTime.secsTo(startTime)>outTime){
            qDebug()<<QString::fromLocal8Bit("响应超时")<<endl;
        }
         if(queryOpenStatus.size()==0){
             continue;
         }
         if(queryOpenStatus.size()==queryOpenStatusLength){
            queryOpenLockStatus=queryOpenStatus;
            break;
         }
}
   if(queryOpenStatus.size()==queryOpenStatusLength){
    qDebug()<<QString::fromLocal8Bit("打开命令成功！")<<endl;
    openAllDoorStatus=1;
   }else{
       openAllDoorStatus=0;
   }

  return openAllDoorStatus;
}
int MainWindow::openDoor(int m){//打开某柜门
    QSerialPort *port;
    port=new QSerialPort("COM7");
    if(port==NULL){
        qDebug()<<QString::fromLocal8Bit("开门串口未打开！");
        init();}
     else{
     qDebug()<<QString::fromLocal8Bit("开门串口已经打开！")<<endl;}
    QByteArray check;
    check[0]=07;
    check[1]=10;
    check[2]=04;
    check.append(m);
    QByteArray queryStatusCheck;
    queryStatusCheck[0]=0;
    int i;
     for(i=0;i<check.size();i++){
          queryStatusCheck[i]=queryStatusCheck[i]+check[i];}
     queryStatusCheck[i]=~queryStatusCheck[i-1]+1;
  check[4]=queryStatusCheck[i];
  port->write(check);
  QDateTime startTime=QDateTime::currentDateTime();
 QByteArray queryOpenDoorStatus;
 QByteArray queryOpenDoorLockStatus;
 int openDoorStatus,queryOpenDoorStatusLength=5,outTime=2;//openDoorStatus为0打开失败，1为成功
 queryOpenDoorLockStatus.clear();
 queryOpenDoorStatus=port->readAll();
 while(true){
     QDateTime systemTime=QDateTime::currentDateTime();
      if(systemTime.secsTo(startTime)>outTime){
          qDebug()<<QString::fromLocal8Bit("开门响应超时")<<endl;
      }
       if(queryOpenDoorStatus.size()==0){
           continue;
       }
       if(queryOpenDoorStatus.size()==queryOpenDoorStatusLength){
          queryOpenDoorLockStatus=queryOpenDoorStatus;
          break;
       }
}
 if(queryOpenDoorStatus.size()==queryOpenDoorStatusLength){
  qDebug()<<QString::fromLocal8Bit("开门打开命令成功！")<<endl;
  openDoorStatus=1;
 }else{
     openDoorStatus=0;
 }
 return openDoorStatus;
}

void MainWindow::on_queryButton_clicked()
{

}
/*void MainWindow::on_pushButton_clicked()
{foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
       qDebug()<<"Name:"<<info.portName();
        qDebug()<<"Description:"<<info.description();
       qDebug()<<"Manufacturer:"<<info.manufacturer();
        qDebug()<<"Serial Number:"<<info.serialNumber();
        qDebug()<<"System Location:"<<info.systemLocation();
        ui->textEdit->append(info.portName());
        ui->textEdit->append(info.description());
        ui->textEdit->append(info.manufacturer());
   }

}*/
