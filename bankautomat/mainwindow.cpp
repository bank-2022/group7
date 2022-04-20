#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    objRestApi = new Rest_api;

    ui->stackedWidget->setCurrentIndex(0);
    ui->summatWidget->setVisible(false);
    ui->valikkoWidget->setVisible(false);
    QFont f( "Comic Sans MS", 25, QFont::Bold);
    ui->otsikkoLabel->setFont(f);

    connect(this,SIGNAL(login(QString,QString)),
            objRestApi,SLOT(loginInSlot(QString,QString)));
    connect(this,SIGNAL(get()),
            objRestApi,SLOT(getInSlot()));
    connect(objRestApi,SIGNAL(webTokenOutSignal(QByteArray)),
            this,SLOT(loginHandler(QByteArray)));

<<<<<<< Updated upstream
    ui->pinCode->setEchoMode(QLineEdit::Password);
=======
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

    connect (objNumPad, &numpad_ui::sendNumToExe,
             this, &MainWindow::pinHandler);

    connect(oRfid, &Rfid_dll::sendId,
            this, &MainWindow::getRfid);

>>>>>>> Stashed changes
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objRestApi;
    objRestApi = nullptr;
<<<<<<< Updated upstream
=======
    delete oRfid;
    oRfid = nullptr;
    delete objNumPad;
    objNumPad = nullptr;
}

void MainWindow::processData(QString resource, QByteArray data)
{
    if (resource == "login"){
        webToken = data;
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
    }
>>>>>>> Stashed changes
}

void MainWindow::on_syotaPin_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
<<<<<<< Updated upstream
=======
    ui->pinCode->clear();
    objNumPad->show();
>>>>>>> Stashed changes
}


void MainWindow::on_kirjaudu_clicked()
{
<<<<<<< Updated upstream
    username = ui->idKortti->text();
=======

    kortinnro = ui->idKortti->text();
>>>>>>> Stashed changes
    pin = ui->pinCode->text();

    emit login(username, pin);
}


void MainWindow::on_tilitapahtumat_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->summatWidget->setVisible(false);
    ui->otsikkoLabel->setText("Tilitapahtumat");
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

void MainWindow::on_kirjauduUlos_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->summatWidget->setVisible(false);
    ui->valikkoWidget->setVisible(false);
    ui->otsikkoLabel->setText("");
}

void MainWindow::loginHandler(QByteArray webToken)
{
    if(webToken == "false") {
        ui->kirjautumisLabel->setText("PIN VÄÄRIN");
    } else {
        emit get();
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
