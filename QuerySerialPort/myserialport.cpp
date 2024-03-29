#include "myserialport.h"
MySerialport::MySerialport(QString portName,QObject *parent):QObject(parent)
{
m_Serialport=new QSerialPort();
m_Serialport->setPortName(portName);
m_Serialport->setParity(QSerialPort::NoParity);
m_Serialport->setFlowControl(QSerialPort::NoFlowControl);
qDebug()<<"Port Name:"<<portName;
if(!m_Serialport->open(QIODevice::ReadWrite)){
    emit sig_SendTipInfo(false,"opened failed");
    qDebug()<<"open failed";
}else{
    qDebug()<<"open successfully";
}
}
MySerialport::~MySerialport(){
    m_Serialport->clear();
    m_Serialport->close();
    m_Serialport->deleteLater();
}
bool MySerialport::WriteToSerialPort(QByteArray cmd){
    if(cmd.isEmpty()) return false;
    this->m_Serialport->clear();
    this->m_Serialport->write(cmd);
    this->m_Serialport->flush();
    this->m_Serialport->waitForBytesWritten(10);
    return true;
}
QByteArray MySerialport::ReadFromSerialPort(){
    QByteArray readData;
    int len;
    this->m_Serialport->waitForReadyRead(10000);
    readData.append(this->m_Serialport->readAll());
    while(this->m_Serialport->waitForReadyRead(10000)){
        readData.append(this->m_Serialport->readAll());
    }
    if(readData.isEmpty()) return QByteArray();
    if(readData.size()==len){
        qDebug()<<QString::fromLocal8Bit("正常");
    }else{
        qDebug()<<QString::fromLocal8Bit("异常");
    }
    return readData;
}
void MySerialport::closeSerialport(){
    if(!m_Serialport->isOpen()) return;
    m_Serialport->clear();
    m_Serialport->close();
}
