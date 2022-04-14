#ifndef GET_H
#define GET_H
#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>
#include <QJsonObject>

class get : public QObject
{
    Q_OBJECT
public:
    get(QString);
public slots:
    void receiveGet(QNetworkReply *reply);
    void sendGet(QByteArray, QString, QString);
private:
    QString base_url;
    QByteArray response_data;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QByteArray webToken;
    QString endpoint;
    QString id;
signals:

};

#endif // GET_H
