#ifndef MYSERIALPORT_H
#define MYSERIALPORT_H
#include <QSerialPort>
#include <QDebug>
class MySerialport:public QObject
{    Q_OBJECT
public:
    MySerialport(QString portName="COM7",QObject *parent=nullptr);
     ~MySerialport();
     bool WriteToSerialPort(QByteArray cmd);
      QByteArray ReadFromSerialPort();
       bool SerialPortIsOpen(){ return m_Serialport->isOpen();}
        void closeSerialport();
 signals:
         void sig_SendTipInfo(bool result,QString Info);
          void sig_SendReadData(QByteArray data);
 private:
           QSerialPort *m_Serialport=nullptr;
};

#endif // MYSERIALPORT_H
