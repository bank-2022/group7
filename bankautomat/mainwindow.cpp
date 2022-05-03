#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loginAttempts = 0;

    objRestApi = new Rest_api;
    objNumPad = new numpad_ui;
    oRfid = new Rfid_dll;
    ajastin = new QTimer;

    QFont f("Comic Sans MS", 25, QFont::Bold);
    QFont f2("Comic Sans MS", 18, QFont::Bold);
    QFont f3("Arial", 15);
    ui->tervetuloaLabel->setFont(f);
    ui->tervetuloaLabel->setAlignment(Qt::AlignCenter);
    ui->tervetuloaLabel->setText(" Tervetuloa! <br> Syötä kortti.");
    ui->paaOtsikkoLabel->setFont(f);
    ui->paaOtsikkoLabel->clear();
    ui->vikatilaLabel->setFont(f);

    ui->rahaliikenneLabel->setAlignment(Qt::AlignCenter);
    ui->rahaliikenneLabel->setFont(f3);

    ui->saldoLabel->setStyleSheet("font: 18pt;");
    ui->saldoLCD->setStyleSheet("font: 18pt;");
    ui->saldoLabel->setFont(f2);
    ui->saldoLCD->setFont(f2);
    ui->saldoLCD->setAlignment(Qt::AlignCenter);

    ui->saldoLabel->setStyleSheet("QLabel {background-color : black; color : white; }");
    ui->label_5->setStyleSheet("QLabel {color : black; }"); // nimi label
    ui->label_6->setStyleSheet("QLabel {color : black; }"); // osoite label
    ui->label_7->setStyleSheet("QLabel {color : black; }"); // puhelinnumero label
    ui->label_8->setStyleSheet("QLabel {color : black; }"); // tilinumero label

    ui->stackedWidget->setCurrentIndex(tervetuloaPage);

    //Tilitapahtumien viewin asetukset
    QHeaderView *hView;
    hView = ui->tilitapahtumaView->horizontalHeader();
    hView->setSectionResizeMode(QHeaderView::ResizeToContents);

    //Tilitapahtumien filtteröinti combobox asetukset
    ui->filtteriDropdown->addItem("Kaikki");
    ui->filtteriDropdown->addItem("Nostot");
    ui->filtteriDropdown->addItem("Talletukset");
    ui->filtteriDropdown->addItem("Siirrot");

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
            this, &MainWindow::incomingDataHandler);

    connect(objNumPad, &numpad_ui::numpadEnterClicked,
            this, &MainWindow::numpadEnter_clicked);

    connect(oRfid, &Rfid_dll::readEvent,
            this, &MainWindow::on_syotaPin_clicked);

    connect(ajastin, &QTimer::timeout,
            this, &MainWindow::on_kirjauduUlos_clicked);

    connect(ui->filtteriDropdown, QOverload<int>::of(&QComboBox::activated),
            this, [=](int index){tilitapahtumaSuodatus(index);});


    kirjautunutState = false;

    qApp->installEventFilter(this);
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
    delete ajastin;
    ajastin = nullptr;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    objNumPad->close();
    event->accept();
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {
            ajastin->start(4000);
            qDebug()<<"moro";
        } else {
            return QObject::eventFilter(obj, event);
        }
    return false;
}

void MainWindow::kirjautumisHandler(events e)
{    
    if (e == korttiSyotetty && kirjautunutState == false){
        korttiOlemassaCheck();
    }
    else if (e == korttiValidoitu){
        if(lukitutKortitCheck() == true){
            kirjautumisHandler(korttiLukittu);
        } else if(lukitutKortitCheck() == false){
            event = korttiSyotetty;
            objNumPad->setWindowTitle("Syötä PIN");
            objNumPad->show();
            objNumPad->stringSizeLimiter(true, 4);
            objNumPad->censorInput(true);

            qDebug()<<kortinnro;
        }
    } else if (e == korttiInvalidoitu){
        ajastin->start(5000);
        pageHandler(vikatilaPage, false, "");
        ui->vikatilaLabel->setText("Korttia ei tunnistettu!");
    } else if (e == pinSyotetty){
        QString pin = objNumPad->returnNum();
        QJsonObject jsonObj;
        jsonObj.insert("idKortti", kortinnro);
        jsonObj.insert("pin", pin);
        QString resource = "login";
        emit requestLogin(resource, webToken, jsonObj);
    } else if (e == pinVaarin){
        loginAttempts++;
        qDebug()<<loginAttempts;
        if(loginAttempts == 3){
            kirjautumisHandler(korttiLukittu);
        }
    } else if (e == pinOikein){
        objNumPad->close();
        QString resource = "kortti/asiakasjatili/" + kortinnro;
        loginAttempts = 0;
        kirjautunutState = true;
        emit requestGet(resource, webToken);
    } else if (e == korttiLukittu){
        ajastin->start(5000);
        objNumPad->close();
        if(this->lukitutKortitCheck()==false){
            lukitutKortit.append(kortinnro);
        }
        pageHandler(vikatilaPage, false, "");
        ui->vikatilaLabel->setText("Pin väärin. Kortti lukittu!");

    } else if (e == kirjauduUlos){
        pageHandler(tervetuloaPage, false, "");
        kortinnro.clear();
        webToken.clear();
        ajastin->stop();
        objNumPad->close();
        kirjautunutState = false;
        loginAttempts = 0;
    }
}

void MainWindow::loginHandler()
{
    if(webToken == "false") {
        if (event == korttiSyotetty){
            kirjautumisHandler(pinVaarin);
        } else if (event == pinSyotetty){
            pinVaihtoHandler(pinVaarin);
        }
    } else {
        if (event == korttiSyotetty){
            kirjautumisHandler(pinOikein);
        } else if (event == pinSyotetty){
            pinVaihtoHandler(pinOikein);
        }
    }
}

void MainWindow::loggedInHandler(events e)
{
    if (e == haeSaldoEtusivulle){
        QString resource = "tili/saldo/" + tilinro;
        emit requestGet(resource, webToken);
    } else if (e == naytaEtusivu){
        ui->saldoLCD->setText(saldo);
        objNumPad->close();
        pageHandler(mainPage, true, "Terve, " + nimi);
    } else if (e == nosto){
        toimenpide = nosta;
        ui->vahvistusWidget->hide();
        ui->rahaliikenneLabel->setText("Syötä summa");
        summa.clear();
        objNumPad->close();
        pageHandler(rahaliikennePage, true, "Nosto");
    } else if (e == talletus){
        toimenpide = talleta;
        ui->vahvistusWidget->hide();
        ui->rahaliikenneLabel->setText("Syötä summa");
        summa.clear();
        objNumPad->close();
        pageHandler(rahaliikennePage, true, "Talletus");
    } else if (e == tilisiirto){
        toimenpide = siirra;
        ui->vahvistusWidget->hide();
        ui->rahaliikenneLabel->setText("Syötä summa");
        summa.clear();
        rcvTilinro.clear();
        objNumPad->close();
        pageHandler(rahaliikennePage, true, "Tilisiirto");
    } else if (e == haeTilitapahtumat){
        QString resource = "tilitapahtuma/tilinumero/" + tilinro;
        emit requestGet(resource, webToken);
    } else if (e == naytaTilitapahtumat){
        objNumPad->close();
        pageHandler(tilitapahtumaPage, true, "Tilitapahtumat");
    } else if (e == kayttajatiedot){
        ui->nimiLabel->setText(nimi);
        ui->osoiteLabel->setText(osoite);
        ui->puhnroLabel->setText(puhnro);
        ui->tilinroLabel->setText(tilinro);
        objNumPad->close();
        pageHandler(tiedotPage, true, "Tietosi");
    }
}

void MainWindow::pageHandler(pages sivu, bool valikko, QString teksti)
{
    ui->stackedWidget->setCurrentIndex(sivu);
    ui->valikkoWidget->setVisible(valikko);
    ui->paaOtsikkoLabel->setText(teksti);
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
        summaButtonsHandler();
    } else if (event == tilinumero){
        summaButtonsHandler();
    } else if (event == pinClicked){
        pinVaihtoHandler(pinSyotetty);
    } else if (event == uusiPin){
        pinVaihtoHandler(uusiPin);
    } else if (event == uudelleenPin){
        pinVaihtoHandler(uudelleenPin);
    }
}

void MainWindow::on_etusivu_clicked()
{
    loggedInHandler(haeSaldoEtusivulle);
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
    event = summaClicked;
    summa = "10";
    summaButtonsHandler();
}

void MainWindow::on_summa20_clicked()
{
    event = summaClicked;
    summa = "20";
    summaButtonsHandler();
}

void MainWindow::on_summa50_clicked()
{
    event = summaClicked;
    summa = "50";
    summaButtonsHandler();
}

void MainWindow::on_summa100_clicked()
{
    event = summaClicked;
    summa = "100";
    summaButtonsHandler();
}

void MainWindow::on_summa500_clicked()
{
    event = summaClicked;
    summa = "500";
    summaButtonsHandler();
}

void MainWindow::on_summaMuu_clicked()
{
    event = muuSumma;
    ui->rahaliikenneLabel->clear();
    ui->vahvistusWidget->hide();
    objNumPad->setWindowTitle("Syötä summa");
    objNumPad->stringSizeLimiter(false, 0);
    objNumPad->censorInput(false);
    objNumPad->show();
}

void MainWindow::korttiOlemassaCheck()
{
    kortinnro = oRfid->returnId();
    kortinnro.remove(0,3).chop(3);

    kortinnro = "0A005968A0"; //kovakoodaus testaamista varten

    QString resource = "korttiCheck/" + kortinnro;
    emit requestGet(resource, webToken);
}

bool MainWindow::lukitutKortitCheck()
{
    bool cardLocked;
    for(int i = 0;i<lukitutKortit.size();i++){
        qDebug()<<"Lukittujen korttien lista: " + lukitutKortit.value(i);
        if(kortinnro == lukitutKortit.value(i)){
            cardLocked = true;
            return cardLocked;
        }
    }
    cardLocked = false;
    return cardLocked;
}

void MainWindow::on_vaihdaPin_clicked()
{
    pinVaihtoHandler(pinClicked);
}

void MainWindow::pinVaihtoHandler(events e)
{
    if (e == pinClicked){
        event = pinClicked;
        objNumPad->setWindowTitle("Syötä PIN");
        objNumPad->stringSizeLimiter(true, 4);
        objNumPad->censorInput(true);
        objNumPad->show();
    } else if (e == pinSyotetty){
        event = pinSyotetty;
        kirjautumisHandler(pinSyotetty);
    } else if (e == pinVaarin){
        event = pinClicked;
        objNumPad->setWindowTitle("PIN väärin, yritä uudelleen");
    } else if (e == pinOikein){
        event = uusiPin;
        objNumPad->setWindowTitle("Syötä uusi PIN");
    } else if (e == uusiPin){
        uusiPIN = objNumPad->returnNum();
        event = uudelleenPin;
        objNumPad->setWindowTitle("Syötä uusi PIN uudelleen");
    } else if (e == uudelleenPin){
        QString pin = objNumPad->returnNum();
        if (pin == uusiPIN){
            QJsonObject jsonObj;
            jsonObj.insert("pin", pin);
            QString resource = "kortti/pin/" + kortinnro;
            emit requestPut(resource, webToken, jsonObj);
            objNumPad->close();
            ui->vaihdaPinLabel->setText("PIN vaihdettu");
            QTimer::singleShot(3000, this, [this]() { ui->vaihdaPinLabel->clear(); } );

        } else {
            event = uudelleenPin;
            objNumPad->setWindowTitle("PIN ei täsmää, yritä uudelleen");
        }
    }
}

void MainWindow::tilitapahtumaSuodatus(int i)
{
    QString resource;
    if(i == 0){resource = "tilitapahtuma/tilinumero/" + tilinro;}
    if(i == 1){resource = "tilitapahtuma/nosto/" + tilinro;}
    if(i == 2){resource = "tilitapahtuma/talletus/" + tilinro;}
    if(i == 3){resource = "tilitapahtuma/siirto/" + tilinro;}
    emit requestGet(resource,webToken);
}

void MainWindow::summaButtonsHandler()
{
    if(event == muuSumma){
        summa = objNumPad->returnNum();
        qDebug()<<summa;
    }
    if(toimenpide == nosta){
        objNumPad->close();
        ui->vahvistusWidget->show();
        ui->rahaliikenneLabel->setText("Haluatko varmasti nostaa <b>" + summa + "</b> rahaa?");
    } else if(toimenpide == talleta){
        objNumPad->close();
        ui->vahvistusWidget->show();
        ui->rahaliikenneLabel->setText("Haluatko varmasti tallettaa <b>" + summa + "</b> rahaa?");
    } else if(event == tilinumero){
        rcvTilinro = objNumPad->returnNum();
        objNumPad->close();
        qDebug()<<rcvTilinro;
        ui->vahvistusWidget->show();
        ui->rahaliikenneLabel->setText("Haluatko varmasti siirtää <b>" + summa + "</b> rahaa tilille <b>" + rcvTilinro + "</b> ?");
    } else if(toimenpide == siirra){
        event = tilinumero;
        ui->rahaliikenneLabel->clear();
        ui->vahvistusWidget->hide();
        objNumPad->setWindowTitle("Syötä tilinumero");
        objNumPad->stringSizeLimiter(false, 0);
        objNumPad->censorInput(false);
        objNumPad->show();
    }
}

void MainWindow::on_kyllaButton_clicked()
{
    if(toimenpide == nosta){
        ui->rahaliikenneLabel->setText("Nosto onnistui!");
        QTimer::singleShot(3000, this, [this]() { ui->rahaliikenneLabel->setText("Syötä summa"); } );
        ui->vahvistusWidget->hide();
    } else if(toimenpide == talleta){
        ui->rahaliikenneLabel->setText("Talletus onnistui!");
        QTimer::singleShot(3000, this, [this]() { ui->rahaliikenneLabel->setText("Syötä summa"); } );
        ui->vahvistusWidget->hide();
    } else if(toimenpide == siirra){
        ui->rahaliikenneLabel->setText("Tilisiirto onnistui!");
        QTimer::singleShot(3000, this, [this]() { ui->rahaliikenneLabel->setText("Syötä summa"); } );
        ui->vahvistusWidget->hide();
    }

    rahaliikenneHandler();
}

void MainWindow::on_eiButton_clicked()
{
    if(toimenpide == nosta){
        loggedInHandler(nosto);
    } else if(toimenpide == talleta){
        loggedInHandler(talletus);
    } else if(toimenpide == siirra){
        loggedInHandler(tilisiirto);
    }
}

void MainWindow::rahaliikenneHandler()
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
    rcvTilinro.clear();
    summa.clear();
    emit requestPost(resource, webToken, jsonObj);
}

void MainWindow::incomingDataHandler(QString resource, QByteArray data)
{
    if (resource == "login"){
        webToken = data;
        loginHandler();
    } else if (resource == "korttiCheck/" + kortinnro){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        QString korttiValidointi = jsonObj["idKortti"].toString();
        if(kortinnro == korttiValidointi){
            kirjautumisHandler(korttiValidoitu);
        }
        else{
            kirjautumisHandler(korttiInvalidoitu);
        }

    } else if (resource == "kortti/asiakasjatili/" + kortinnro){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        nimi = jsonObj["nimi"].toString();
        osoite = jsonObj["osoite"].toString();
        puhnro = jsonObj["puhelinnumero"].toString();
        tilinro = jsonObj["idTilinumero"].toString();
        saldo = QString::number(jsonObj["saldo"].toDouble(), 'f', 0);
        loggedInHandler(naytaEtusivu);
    } else if (resource == "tili/saldo/" + tilinro){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonObject jsonObj = jsonDoc.object();
        saldo = QString::number(jsonObj["saldo"].toDouble(), 'f', 0);
        loggedInHandler(naytaEtusivu);
    } else if (resource == "tilitapahtuma/tilinumero/" + tilinro ||
               resource == "tilitapahtuma/nosto/" + tilinro ||
               resource == "tilitapahtuma/talletus/" + tilinro ||
               resource == "tilitapahtuma/siirto/" + tilinro){
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);
        QJsonArray json_array = jsonDoc.array();

        QStandardItemModel *tilitapahtumaModel = new QStandardItemModel(json_array.size(),3);
        tilitapahtumaModel->setHeaderData(0, Qt::Horizontal, QObject::tr("Aika"));
        tilitapahtumaModel->setHeaderData(1, Qt::Horizontal, QObject::tr("Summa"));
        tilitapahtumaModel->setHeaderData(2, Qt::Horizontal, QObject::tr("Tapahtuma"));

        for(int row = 0;row<json_array.size();row++){
            QJsonValue value = json_array.at(row);
            QJsonObject jsonObj = value.toObject();

            QStandardItem *Aikaleima = new QStandardItem(jsonObj["aikaleima"].toString());
            tilitapahtumaModel->setItem(row, 0, Aikaleima);
            QStandardItem *Summa = new QStandardItem(QString::number(jsonObj["summa"].toDouble()));
            tilitapahtumaModel->setItem(row, 1, Summa);
            QStandardItem *Tyyppi = new QStandardItem(jsonObj["tilitapahtuma"].toString());
            tilitapahtumaModel->setItem(row, 2, Tyyppi);

            Aikaleima->setTextAlignment(Qt::AlignCenter);
            Summa->setTextAlignment(Qt::AlignCenter);
            Tyyppi->setTextAlignment(Qt::AlignCenter);
        }
        ui->tilitapahtumaView->setModel(tilitapahtumaModel);
        loggedInHandler(naytaTilitapahtumat);
    }
}



