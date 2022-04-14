#include "get.h"

get::get(QString url)
{
    base_url = url;
}

void get::sendGet(QByteArray webToken, QString paramEndpoint, QString paramID)
{
    endpoint = paramEndpoint;
    id = paramID;
    QNetworkRequest request(base_url+"/"+endpoint+"/"+id);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    //WEBTOKEN ALKU
    QByteArray myToken="Bearer "+webToken;
    request.setRawHeader(QByteArray("Authorization"),(myToken));
    //WEBTOKEN LOPPU

    manager = new QNetworkAccessManager(this);
    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(receiveGet(QNetworkReply*)));
    reply = manager->get(request);
}

void get::receiveGet(QNetworkReply *reply)
{
    QString data;
    QByteArray response_data=reply->readAll();
    QJsonDocument json_doc = QJsonDocument::fromJson(response_data);
    if (endpoint == "kortti/asiakas"){
        QJsonObject json_obj = json_doc.object();
        data = QString::number(json_obj["idAsiakas"].toInt())+","+
                json_obj["nimi"].toString()+","+
                json_obj["osoite"].toString()+","+
                json_obj["puhelinnumero"].toString();
    } else if (endpoint == "tilitapahtuma"){
        QJsonArray json_array = json_doc.array();
        foreach (const QJsonValue &value, json_array) {
            QJsonObject json_obj = value.toObject();
            data+=QString::number(json_obj["idTilitapahtuma"].toInt())+","+
                    json_obj["idTilinumero"].toString()+","+
                    json_obj["dateTime"].toString()+","+
                    QString::number(json_obj["summa"].toInt())+","+
                    json_obj["tilitapahtuma"].toString()+","+
                    QString::number(json_obj["idKortti"].toInt())+"\r";
        }
    };

    qDebug()<<data;
    reply->deleteLater();
    manager->deleteLater();
}
