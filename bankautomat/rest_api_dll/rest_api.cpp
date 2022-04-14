#include "rest_api.h"

Rest_api::Rest_api()
{
    base_url = "http://localhost:3000";
    objGet = new get(base_url);
    objLogin = new login(base_url);

    connect(this,SIGNAL(loginInSignal(QString,QString)),
            objLogin,SLOT(sendLogin(QString,QString)));

    connect(objLogin,SIGNAL(webTokenOutSignal(QByteArray)),
            this,SLOT(webTokenOutSlot(QByteArray)));

    connect(this,SIGNAL(getInSignal(QByteArray,QString,QString)),
            objGet,SLOT(sendGet(QByteArray,QString,QString)));

}

Rest_api::~Rest_api()
{
    delete objGet;
    objGet = nullptr;
    delete objLogin;
    objLogin = nullptr;
}

void Rest_api::loginInSlot(QString username, QString pin)
{
    emit loginInSignal(username, pin);
}

void Rest_api::webTokenOutSlot(QByteArray token)
{
    webToken = token;
    emit webTokenOutSignal(webToken);
}

void Rest_api::getInSlot()
{
    QString perse = "tilitapahtuma";
    QString paska = "1";
    emit getInSignal(webToken, perse, paska);
}


