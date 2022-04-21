#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objRestApi = new Rest_api;
    objNumPad = new numpad_ui;
    oRfid = new Rfid_dll;


    QFont f( "Comic Sans MS", 25, QFont::Bold);
    ui->otsikkoLabel->setFont(f);

    ui->stackedWidget->setCurrentIndex(0);
    ui->summatWidget->setVisible(false);
    ui->valikkoWidget->setVisible(false);

    connect(this, &MainWindow::requestLogin,
            objRestApi, &Rest_api::sendPost);

    connect(this, &MainWindow::requestGet,
            objRestApi, &Rest_api::sendGet);

    connect(this, &MainWindow::requestPost,
            objRestApi, &Rest_api::sendPost);

    connect(this, &MainWindow::requestPut,
            objRestApi, &Rest_api::sendPut);

    connect(this, &MainWindow::login,
            this, &MainWindow::loginHandler);

    connect(objRestApi, &Rest_api::returnData,
            this, &MainWindow::processData);

    connect(objNumPad, &numpad_ui::returnNum,
            this, &MainWindow::numpadHandler);

    connect(oRfid, &Rfid_dll::sendId,
            this, &MainWindow::getRfid);

    connect(this, &MainWindow::muuSumma,
            this, &MainWindow::summaHandler);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objRestApi;
    objRestApi = nullptr;
    delete oRfid;
    oRfid = nullptr;
    delete objNumPad;
    objNumPad = nullptr;
}

void MainWindow::processData(QString resource, QByteArray data)
{
    if (resource == "login"){
        qDebug()<<"KIRJAUTUMINEN";
        webToken = data;
        qDebug()<<data;
        emit login();
    } else if (resource == "kortti/asiakas/" + kortinnro){
        resource = "kortti/tili/" + kortinnro;
        emit requestGet(resource, webToken);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QString data = QString::number(jsonObj["idAsiakas"].toInt())+","
                +jsonObj["nimi"].toString()+","
                +jsonObj["osoite"].toString()+","
                +jsonObj["puhelinnumero"].toString();

        //qDebug()<<data;

    } else if(resource == "kortti/tili/" + kortinnro) {
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QString data = jsonObj["idTilinumero"].toString()+","
                +QString::number(jsonObj["saldo"].toDouble());
        //qDebug()<<data;
    } else if (resource == "tilitapahtuma/kortti/" + kortinnro){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonArray jsonArray = jsonDoc.array();
        QString data;
        foreach (const QJsonValue &value, jsonArray) {
            QJsonObject jsonObj = value.toObject();

            data+=QString::number(jsonObj["idTilitapahtuma"].toInt())+","
                    +jsonObj["idTilinumero"].toString()+","
                    +jsonObj["dateTime"].toString()+","
                    +QString::number(jsonObj["summa"].toInt())+","
                    +jsonObj["tilitapahtuma"].toString()+","
                    +QString::number(jsonObj["idKortti"].toInt())+"\r";
        }
    } else if (resource == "kortti/asiakas/" + kortinnro){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
            QJsonObject jsonObj = jsonDoc.object();
            QString data = QString::number(jsonObj["idAsiakas"].toInt())+","
                    +jsonObj["nimi"].toString()+","
                    +jsonObj["osoite"].toString()+","
                    +jsonObj["puhelinnumero"].toString();
            qDebug()<<data;
    }
}

void MainWindow::on_syotaPin_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    objNumPad->stringSizeLimiter(true, 4);
    objNumPad->censorInput(true);
    objNumPad->show();
    state = kirjaudu;
}

void MainWindow::on_kirjaudu_clicked()
{
    kortinnro = ui->idKortti->text();

    QJsonObject jsonObj;
    jsonObj.insert("idKortti", kortinnro);
    jsonObj.insert("pin", num);

    QString resource = "login";

    emit requestLogin(resource, webToken, jsonObj);

    num.clear();
}


void MainWindow::on_tilitapahtumat_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->summatWidget->setVisible(false);
    ui->otsikkoLabel->setText("Tilitapahtumat");

    QString resource = "tilitapahtuma/kortti/" + kortinnro;
    emit requestGet(resource, webToken);
}


void MainWindow::on_nosto_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->summatWidget->setVisible(true);
    ui->otsikkoLabel->setText("Nosto");
    state = nosto;
}


void MainWindow::on_talletus_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->summatWidget->setVisible(true);
    ui->otsikkoLabel->setText("Talletus");
    state = talletus;
}


void MainWindow::on_tilisiirto_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->summatWidget->setVisible(true);
    ui->otsikkoLabel->setText("Tilisiirto");
    state = tilisiirto;
}

void MainWindow::on_naytaTiedot_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->summatWidget->setVisible(false);
    ui->otsikkoLabel->setText("Tietosi");
}

void MainWindow::getRfid(QString id)
{
    ui->stackedWidget->setCurrentIndex(1);    
    id.remove(0,3).chop(3);    
    ui->idKortti->setText(id);
    ui->kirjautumisLabel->clear();
}

void MainWindow::numpadHandler(QString paramNum)
{
    if(state == kirjaudu){
        num = paramNum;
        objNumPad->close();
    } else {
        objNumPad->close();
        emit muuSumma(paramNum, state);
    }
}

void MainWindow::on_kirjauduUlos_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->summatWidget->setVisible(false);
    ui->valikkoWidget->setVisible(false);
    ui->otsikkoLabel->clear();
    num.clear();
    webToken.clear();
}

void MainWindow::loginHandler()
{
    if(webToken == "false") {
        ui->kirjautumisLabel->setText("PIN VÄÄRIN");
    } else {

        QString resource = "kortti/asiakas/" + kortinnro;
        emit requestGet(resource, webToken);

        ui->stackedWidget->setCurrentIndex(2);
        ui->valikkoWidget->setVisible(true);
        ui->otsikkoLabel->setText("Terve");
        QString saldo = "50000";
        ui->saldoLCD->display(saldo);
    }
}


void MainWindow::on_summa10_clicked()
{
    summaHandler("10", state);
}


void MainWindow::on_summa20_clicked()
{
    summaHandler("20", state);
}


void MainWindow::on_summa50_clicked()
{
    summaHandler("50", state);
}


void MainWindow::on_summa100_clicked()
{
    summaHandler("100", state);
}


void MainWindow::on_summa500_clicked()
{
    summaHandler("500", state);
}


void MainWindow::on_summaMuu_clicked()
{
    objNumPad->stringSizeLimiter(false, 0);
    objNumPad->censorInput(false);
    objNumPad->show();
}

void MainWindow::summaHandler(QString summa, states s)
{
    num = summa;
    QString resource;
    QJsonObject jsonObj;

    QString tilinro = "Tili_1";

    QString receiverTilinro = "Tili_2";

    if(s == nosto){
        resource = "proseduuri/nosto";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("tilinro", tilinro);
        jsonObj.insert("rahasumma", num);
    } else if(s == talletus){
        resource = "proseduuri/talletus";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("tilinro", tilinro);
        jsonObj.insert("rahasumma", num);
    } else if(s == tilisiirto){
        resource = "proseduuri/tilisiirto";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("sendertilinro", tilinro);
        jsonObj.insert("receivertilinro", receiverTilinro);
        jsonObj.insert("rahasumma", num);
    }
    qDebug()<<jsonObj;
    emit requestPost(resource, webToken, jsonObj);
}

void MainWindow::on_showNumpad_clicked()
{
    objNumPad->show();
}

