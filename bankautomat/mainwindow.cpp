#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objRestApi = new Rest_api;
    oRfid = new Rfid_dll;

    ui->pinCode->setEchoMode(QLineEdit::Password);
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
            objRestApi, &Rest_api::sendGet);

    connect(this, &MainWindow::requestPut,
            objRestApi, &Rest_api::sendGet);

    connect(this, &MainWindow::login,
            this, &MainWindow::loginHandler);

    connect(objRestApi, &Rest_api::returnData,
            this, &MainWindow::processData);

    connect(oRfid, &Rfid_dll::sendId,
            this, &MainWindow::getRfid);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete objRestApi;
    objRestApi = nullptr;
    delete oRfid;
    oRfid = nullptr;
}

void MainWindow::processData(QString resource, QByteArray data)
{
    if (resource == "login"){
            webToken = data;
            qDebug()<<webToken;
            emit login();
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
    ui->pinCode->clear();
}


void MainWindow::on_kirjaudu_clicked()
{
    kortinnro = ui->idKortti->text();
    pin = ui->pinCode->text();

    jsonObj.insert("idKortti", kortinnro);
    jsonObj.insert("pin", pin);

    QString resource = "login";

    emit requestLogin(resource, webToken, jsonObj);
}


void MainWindow::on_tilitapahtumat_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->summatWidget->setVisible(false);
    ui->otsikkoLabel->setText("Tilitapahtumat");

    QString resource = "tilitapahtuma/kortti" + kortinnro;
    emit requestGet(resource, webToken);
}


void MainWindow::on_nosto_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->summatWidget->setVisible(true);
    ui->otsikkoLabel->setText("Nosto");
}


void MainWindow::on_talletus_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->summatWidget->setVisible(true);
    ui->otsikkoLabel->setText("Talletus");
}


void MainWindow::on_tilisiirto_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->summatWidget->setVisible(true);
    ui->otsikkoLabel->setText("Tilisiirto");
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
    qDebug()<<id;
    id.remove(0,3).chop(3);
    qDebug()<<"Parsittu id: " + id;
    ui->idKortti->setText(id);
    ui->pinCode->clear();
}

void MainWindow::on_kirjauduUlos_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->summatWidget->setVisible(false);
    ui->valikkoWidget->setVisible(false);
    ui->otsikkoLabel->setText("");
    webToken = "";
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

void MainWindow::on_nosta10_clicked()
{

}


void MainWindow::on_nosta20_clicked()
{

}


void MainWindow::on_nosta50_clicked()
{

}


void MainWindow::on_nosta100_clicked()
{

}


void MainWindow::on_nosta500_clicked()
{

}


void MainWindow::on_muuSumma_clicked()
{

}
