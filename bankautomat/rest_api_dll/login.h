#ifndef LOGIN_H
#define LOGIN_H
#include <QObject>
#include <QDebug>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

class login : public QObject
{
    Q_OBJECT
public:
    login(QString);
public slots:
    void sendLogin(QString, QString);
    void receiveLogin(QNetworkReply *reply);
private:
    QString base_url;
    QString username;
    QString pinkoodi;
    QByteArray response_data;
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
signals:
    void webTokenOutSignal(QByteArray);
};

#endif // LOGIN_H
