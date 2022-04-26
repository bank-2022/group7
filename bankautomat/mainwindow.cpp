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

    ui->stackedWidget->setCurrentIndex(tervetuloaPage);

    //Tableviewin asetukset
    QHeaderView *hView;
    hView = ui->tableView->horizontalHeader();
    hView->setSectionResizeMode(QHeaderView::ResizeToContents);

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

    connect(objNumPad, &numpad_ui::numpadEnterClicked,
            this, &MainWindow::numpadEnter_clicked);

    connect(oRfid, &Rfid_dll::readEvent,
            this, &MainWindow::on_syotaPin_clicked);

    state = eiKirjautunut;
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


void MainWindow::runStateMachine(states s, events e)
{
    switch(s) {
    case eiKirjautunut:
        eiKirjautunutHandler(e);
        break;
    case kirjautunut:
        kirjautunutHandler(e);
        break;
    }
}

void MainWindow::eiKirjautunutHandler(events e)
{
    if (e == korttiSyotetty){
        ui->stackedWidget->setCurrentIndex(kirjauduPage);
        objNumPad->stringSizeLimiter(true, 4);
        objNumPad->censorInput(true);
        objNumPad->show();

        kortinnro = oRfid->returnId();
        kortinnro.remove(0,3).chop(3);
        ui->idKortti->setText(kortinnro);
        ui->kirjautumisLabel->clear();

    } else if (e == pinSyotetty){
        //kortinnro = ui->idKortti->text();
        QString pin = objNumPad->returnNum();
        QJsonObject jsonObj;
        jsonObj.insert("idKortti", kortinnro);
        jsonObj.insert("pin", pin);
        QString resource = "login";
        emit requestLogin(resource, webToken, jsonObj);
    } else if (e == pinVaarin){
        ui->kirjautumisLabel->setText("PIN VÄÄRIN");
    } else if (e == pinOikein){
        objNumPad->close();
        QString resource = "kortti/asiakasjatili/" + kortinnro;
        emit requestGet(resource, webToken);
        runStateMachine(kirjautunut, naytaEtusivu);
    }
}

void MainWindow::loginHandler()
{
    if(webToken == "false") {
        runStateMachine(state, pinVaarin);
    } else {
        runStateMachine(state, pinOikein);
    }
}

void MainWindow::kirjautunutHandler(events e)
{
    if (e == naytaEtusivu){
        state = kirjautunut;
        pageHandler(mainPage, true, false, "Terve" + nimi);
    } else if (e == nosto){
        event = nosto;
        pageHandler(nostoPage, true, true, "Nosto");
    } else if (e == talletus){
        event = talletus;
        pageHandler(talletusPage, true, true, "Talletus");
    } else if (e == tilisiirto){
        event = tilisiirto;
        pageHandler(tilisiirtoPage, true, true, "Tilisiirto");
    } else if (e == tilitapahtumat){
        QString resource = "tilitapahtuma/tilinumero/" + tilinro; //kortin vai tilin perusteella?
        qDebug()<<resource;
        emit requestGet(resource, webToken);
        pageHandler(tilitapahtumaPage, true, false, "Tilitapahtumat");
    } else if (e == naytaTiedot){
        pageHandler(tiedotPage, true, false, "Tietosi");
    } else if (e == muuSumma){
        objNumPad->stringSizeLimiter(false, 0);
        objNumPad->censorInput(false);
        objNumPad->show();
    } else if (e == muuSummaSyotetty){
        QString summa = objNumPad->returnNum();
        summaHandler(summa, event);
    } else if (e == kirjauduUlos){
        state = eiKirjautunut;
        pageHandler(tervetuloaPage, false, false, "");
        webToken.clear();
    }
}

void MainWindow::pageHandler(pages sivu, bool valikko, bool summat, QString teksti)
{
    ui->stackedWidget->setCurrentIndex(sivu);
    ui->valikkoWidget->setVisible(valikko);
    ui->summatWidget->setVisible(summat);
    ui->otsikkoLabel->setText(teksti);
}

void MainWindow::on_syotaPin_clicked()
{
    runStateMachine(state, korttiSyotetty);
}

void MainWindow::numpadEnter_clicked()
{
    if (state == eiKirjautunut){
        runStateMachine(state, pinSyotetty);
    } else if (state == kirjautunut){
        runStateMachine(state, muuSummaSyotetty);
    }
}

void MainWindow::on_nosto_clicked()
{
    runStateMachine(state, nosto);
}

void MainWindow::on_talletus_clicked()
{
    runStateMachine(state, talletus);
}

void MainWindow::on_tilisiirto_clicked()
{
    runStateMachine(state, tilisiirto);
}

void MainWindow::on_tilitapahtumat_clicked()
{
    runStateMachine(state, tilitapahtumat);
}

void MainWindow::on_naytaTiedot_clicked()
{
    runStateMachine(state, naytaTiedot);
}

void MainWindow::on_kirjauduUlos_clicked()
{
    runStateMachine(state, kirjauduUlos);
}

void MainWindow::on_summa10_clicked()
{
    summaHandler("10", event);
}

void MainWindow::on_summa20_clicked()
{
    summaHandler("20", event);
}

void MainWindow::on_summa50_clicked()
{
    summaHandler("50", event);
}

void MainWindow::on_summa100_clicked()
{
    summaHandler("100", event);
}

void MainWindow::on_summa500_clicked()
{
    summaHandler("500", event);
}

void MainWindow::on_summaMuu_clicked()
{
    runStateMachine(state, muuSumma);
}

void MainWindow::summaHandler(QString summa, events e)
{
    QString resource;
    QJsonObject jsonObj;
    QString receiverTilinro = "Tili_2";

    if(e == nosto){
        resource = "proseduuri/nosto";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("tilinro", tilinro);
        jsonObj.insert("rahasumma", summa);
    } else if(e == talletus){
        resource = "proseduuri/talletus";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("tilinro", tilinro);
        jsonObj.insert("rahasumma", summa);
    } else if(e == tilisiirto){
        resource = "proseduuri/tilisiirto";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("sendertilinro", tilinro);
        jsonObj.insert("receivertilinro", receiverTilinro);
        jsonObj.insert("rahasumma", summa);
    }
    qDebug()<<jsonObj;
    emit requestPost(resource, webToken, jsonObj);
}

void MainWindow::on_showNumpad_clicked()
{
    objNumPad->show();
}

void MainWindow::processData(QString resource, QByteArray data)
{
    if (resource == "login"){
        webToken = data;
        emit login();
    } else if (resource == "kortti/asiakasjatili/" + kortinnro){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();

        //QString idAsiakas = QString::number(jsonObj["idAsiakas"].toInt());
        nimi = jsonObj["nimi"].toString();
        osoite = jsonObj["osoite"].toString();
        puhnro = jsonObj["puhelinnumero"].toString();
        tilinro = jsonObj["idTilinumero"].toString();
        saldo = QString::number(jsonObj["saldo"].toDouble()); //ei näy oikein

        qDebug()<<nimi;
        qDebug()<<osoite;
        qDebug()<<saldo;
        qDebug()<<tilinro;

    } else if (resource == "tilitapahtuma/tilinumero/" + tilinro){ //kortin vai tilin perusteella?
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonArray json_array = jsonDoc.array();

        QStandardItemModel *table_model = new QStandardItemModel(10,3);
        table_model->setHeaderData(0, Qt::Horizontal, QObject::tr("Aikaleima"));
        table_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Summa"));
        table_model->setHeaderData(2, Qt::Horizontal, QObject::tr("Tyyppi"));

        for(int row = 0;row<json_array.size();row++){
            QJsonValue value = json_array.at(row);
            QJsonObject jsonObj = value.toObject();

            QString date = jsonObj["dateTime"].toString();
            date.replace("-","/").replace("T"," ").chop(5);

            QStandardItem *Aikaleima = new QStandardItem(date);
            table_model->setItem(row, 0, Aikaleima);
            QStandardItem *Summa = new QStandardItem(QString::number(jsonObj["summa"].toDouble()));
            table_model->setItem(row, 1, Summa);
            QStandardItem *Tyyppi = new QStandardItem(jsonObj["tilitapahtuma"].toString());
            table_model->setItem(row, 2, Tyyppi);
        }
        ui->tableView->setModel(table_model);
    }
}

