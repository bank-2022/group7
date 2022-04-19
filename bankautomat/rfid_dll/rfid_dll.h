#ifndef RFID_DLL_H
#define RFID_DLL_H

#include "rfid_dll_global.h"
#include <QSerialPort>
#include <QObject>
#include <qstring.h>
#include <QDebug>

class RFID_DLL_EXPORT Rfid_dll : public QObject
{
    Q_OBJECT
public:
    Rfid_dll(QObject * parent = nullptr);
    ~Rfid_dll();
    QString returnId();

private:
    QSerialPort *serial;
    QString id;

private slots:
    void readId();

signals:
    void sendId(QString);
};

#endif // RFID_DLL_H
