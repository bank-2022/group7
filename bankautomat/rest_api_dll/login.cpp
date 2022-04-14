#include "login.h"

login::login(QString url)
{
    base_url = url;
}

void login::sendLogin(QString username, QString pin)
{
    QJsonObject jsonObj;
    jsonObj.insert("idKortti", username);
    jsonObj.insert("pin", pin);
    QNetworkRequest request(base_url+"/login");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(receiveLogin(QNetworkReply*)));
    reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void login::receiveLogin(QNetworkReply *reply)
{
    response_data = reply->readAll();
    reply->deleteLater();
    manager->deleteLater();
    emit webTokenOutSignal(response_data);
}
