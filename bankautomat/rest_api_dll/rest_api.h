#ifndef REST_API_H
#define REST_API_H

#include "rest_api_global.h"

#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

class REST_API_EXPORT Rest_api : public QObject
{
    Q_OBJECT
public:
    Rest_api();
    ~Rest_api();
public slots:
    void sendPost(QString, QByteArray, QJsonObject);
    void sendGet(QString, QByteArray);
    void sendPut(QString, QByteArray, QJsonObject);
    void receiveData(QNetworkReply *reply);
private:
    QString base_url;
    QByteArray webToken;
    QByteArray response_data;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString resourceForExe;
signals:
    void returnData(QString, QByteArray);
};

#endif // REST_API_H
