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

    connect(objRestApi, &Rest_api::returnData,
            this, &MainWindow::processData);

    connect(objNumPad, &numpad_ui::numpadEnterClicked,
            this, &MainWindow::numpadEnter_clicked);

    connect(oRfid, &Rfid_dll::readEvent,
            this, &MainWindow::on_syotaPin_clicked);
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

void MainWindow::closeEvent(QCloseEvent *event)
{
    objNumPad->close();
    event->accept();
}

void MainWindow::kirjautumisHandler(events e)
{
    if (e == korttiSyotetty){
        event = korttiSyotetty;
        ui->stackedWidget->setCurrentIndex(kirjauduPage);
        objNumPad->stringSizeLimiter(true, 4);
        objNumPad->censorInput(true);
        objNumPad->show();

        kortinnro = oRfid->returnId();
        kortinnro.remove(0,3).chop(3);

        ui->kirjautumisLabel->clear();

    } else if (e == pinSyotetty){
        //kortinnro = ui->idKortti->text();
       kortinnro = "2"; //kovakoodaus testaamista varten
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
    } else if (e == kirjauduUlos){
        pageHandler(tervetuloaPage, false, false, "");
        webToken.clear();
    }
}

void MainWindow::loginHandler()
{
    if(webToken == "false") {
        kirjautumisHandler(pinVaarin);
    } else {
        kirjautumisHandler(pinOikein);
    }
}

void MainWindow::loggedInHandler(events e)
{
    if (e == naytaEtusivu){
        pageHandler(mainPage, true, false, "Terve, " + nimi);
    } else if (e == nosto){
        toimenpide = nosta;
        pageHandler(nostoPage, true, true, "Nosto");
    } else if (e == talletus){
        toimenpide = talleta;
        pageHandler(talletusPage, true, true, "Talletus");
    } else if (e == tilisiirto){
        toimenpide = siirra;
        pageHandler(tilisiirtoPage, true, true, "Tilisiirto");
    } else if (e == tilinumero){
        event = tilinumero;
        objNumPad->stringSizeLimiter(false, 0);
        objNumPad->censorInput(false);
        objNumPad->show();
    } else if (e == tilinumeroSyotetty){
        rcvTilinro = objNumPad->returnNum();
        objNumPad->close();
    } else if (e == muuSumma){
        event = muuSumma;
        objNumPad->stringSizeLimiter(false, 0);
        objNumPad->censorInput(false);
        objNumPad->show();
    } else if (e == muuSummaSyotetty){
        QString summa = objNumPad->returnNum();
        summaHandler(summa, toimenpide);
        objNumPad->close();
    } else if (e == haeTilitapahtumat){
        QString resource = "tilitapahtuma/tilinumero/" + tilinro;
        emit requestGet(resource, webToken);
    } else if (e == naytaTilitapahtumat){
        pageHandler(tilitapahtumaPage, true, false, "Tilitapahtumat");
    } else if (e == kayttajatiedot){
        pageHandler(tiedotPage, true, false, "Tietosi");


        ui->nimiLabel->setText(nimi);
        ui->osoiteLabel->setText(osoite);
        ui->puhnroLabel->setText(puhnro);
        ui->tilinroLabel->setText(tilinro);

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
    kirjautumisHandler(korttiSyotetty);
}

void MainWindow::numpadEnter_clicked()
{
    if (event == korttiSyotetty){
        kirjautumisHandler(pinSyotetty);
    } else if (event == muuSumma){
        loggedInHandler(muuSummaSyotetty);
    } else if (event == tilinumero){
        loggedInHandler(tilinumeroSyotetty);
    }
}

void MainWindow::on_nosto_clicked()
{
    loggedInHandler(nosto);
}

void MainWindow::on_talletus_clicked()
{
    loggedInHandler(talletus);
}

void MainWindow::on_tilisiirto_clicked()
{
    loggedInHandler(tilisiirto);
}

void MainWindow::on_syotaTilinumero_clicked()
{
    loggedInHandler(tilinumero);
}

void MainWindow::on_tilitapahtumat_clicked()
{
    loggedInHandler(haeTilitapahtumat);
}

void MainWindow::on_naytaTiedot_clicked()
{
    loggedInHandler(kayttajatiedot);
}

void MainWindow::on_kirjauduUlos_clicked()
{
    kirjautumisHandler(kirjauduUlos);
}

void MainWindow::on_summa10_clicked()
{
    summaHandler("10", toimenpide);
}

void MainWindow::on_summa20_clicked()
{
    summaHandler("20", toimenpide);
}

void MainWindow::on_summa50_clicked()
{
    summaHandler("50", toimenpide);
}

void MainWindow::on_summa100_clicked()
{
    summaHandler("100", toimenpide);
}

void MainWindow::on_summa500_clicked()
{
    summaHandler("500", toimenpide);
}

void MainWindow::on_summaMuu_clicked()
{
    loggedInHandler(muuSumma);
}

void MainWindow::summaHandler(QString summa, rahaliikenne toimenpide)
{
    QString resource;
    QJsonObject jsonObj;

    if(toimenpide == nosta){
        resource = "proseduuri/nosto";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("tilinro", tilinro);
        jsonObj.insert("rahasumma", summa);
    } else if(toimenpide == talleta){
        resource = "proseduuri/talletus";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("tilinro", tilinro);
        jsonObj.insert("rahasumma", summa);
    } else if(toimenpide == siirra){
        resource = "proseduuri/tilisiirto";
        jsonObj.insert("kortinnro", kortinnro);
        jsonObj.insert("sendertilinro", tilinro);
        jsonObj.insert("receivertilinro", rcvTilinro);
        jsonObj.insert("rahasumma", summa);
    }
    qDebug()<<jsonObj;
    rcvTilinro = "";
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
        loginHandler();
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

        loggedInHandler(naytaEtusivu);

    } else if (resource == "tilitapahtuma/tilinumero/" + tilinro){
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
        loggedInHandler(naytaTilitapahtumat);
    }

}

