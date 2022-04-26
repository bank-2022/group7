#include "rfid_dll.h"

Rfid_dll::Rfid_dll(QObject * parent)
{
    serial = new QSerialPort;
    serial->setPortName("com5");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);
    serial->open(QIODevice::ReadOnly);
    connect(serial, &QIODevice::readyRead, this, &Rfid_dll::readId);
}

Rfid_dll::~Rfid_dll()
{
    serial->close();
}

void Rfid_dll::readId()
{
    id = serial->readAll();
    emit readEvent();
}

QString Rfid_dll::returnId()
{
    return id;
}
