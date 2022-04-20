#include "rest_api.h"

Rest_api::Rest_api()
{
    base_url = "http://localhost:3000";
}

Rest_api::~Rest_api()
{

}

void Rest_api::sendPost(QString resource, QByteArray webToken, QJsonObject jsonObj)
{
    resourceForExe = resource;
    QNetworkRequest request(base_url+"/"+resource);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveData(QNetworkReply*)));

        reply = manager->post(request, QJsonDocument(jsonObj).toJson());
}

void Rest_api::sendGet(QString resource, QByteArray webToken)
{
    resourceForExe = resource;
    QNetworkRequest request(base_url+"/"+resource);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveData(QNetworkReply*)));

    reply = manager->get(request);
}

void Rest_api::sendPut(QString resource, QByteArray webToken, QJsonObject jsonObj)
{
    resourceForExe = resource;
    QNetworkRequest request(base_url+"/"+resource);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(receiveData(QNetworkReply*)));

        reply = manager->put(request, QJsonDocument(jsonObj).toJson());
}

void Rest_api::receiveData(QNetworkReply *reply)
{
    response_data=reply->readAll();
    reply->deleteLater();
    manager->deleteLater();
    emit returnData(resourceForExe, response_data);
}
