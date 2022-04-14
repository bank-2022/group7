#ifndef REST_API_H
#define REST_API_H

#include "rest_api_global.h"
#include "get.h"
#include "login.h"

#include <QObject>
#include <QDebug>

class REST_API_EXPORT Rest_api : public QObject
{
    Q_OBJECT
public:
    Rest_api();
    ~Rest_api();
public slots:
    void loginInSlot(QString, QString);
    void getInSlot();
    void webTokenOutSlot(QByteArray);
private:
    QString base_url;
    get *objGet;
    login *objLogin;
    QByteArray webToken;
signals:
    void loginInSignal(QString, QString);
    void getInSignal(QByteArray, QString, QString);
    void webTokenOutSignal(QByteArray);

};

#endif // REST_API_H
