#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rest_api.h"
#include "numpad_ui.h"
#include "rfid_dll.h"

#include <QMainWindow>
#include <QDebug>
#include <QObject>
#include <QSerialPort>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTimer>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum rahaliikenne{
        nosta,
        talleta,
        siirra
    };

    enum events{
        korttiSyotetty,
        korttiValidoitu,
        korttiInvalidoitu,
        pinSyotetty,
        pinVaarin,
        pinOikein,
        korttiLukittu,
        haeSaldoEtusivulle,
        naytaEtusivu,
        nosto,
        talletus,
        tilisiirto,
        tilinumero,
        haeTilitapahtumat,
        naytaTilitapahtumat,
        kayttajatiedot,
        kirjauduUlos,
        muuSumma,
        summaClicked,
        pinClicked,
        uusiPin,
        uudelleenPin,

    };

    enum pages{
        tervetuloaPage,
        mainPage,
        nostoPage,
        tiedotPage,
        talletusPage,
        tilitapahtumaPage,
        tilisiirtoPage,
        vikatilaPage,
    };

private slots:
    void incomingDataHandler(QString, QByteArray);
    void on_syotaPin_clicked();
    void on_tilitapahtumat_clicked();
    void on_nosto_clicked();
    void on_talletus_clicked();
    void on_tilisiirto_clicked();
    void on_kirjauduUlos_clicked();

    void on_summa10_clicked();
    void on_summa20_clicked();
    void on_summa50_clicked();
    void on_summa100_clicked();
    void on_summa500_clicked();
    void on_summaMuu_clicked();

    void on_naytaTiedot_clicked();
    void numpadEnter_clicked();
    void on_syotaTilinumero_clicked();

    void kylla_clicked();
    void ei_clicked();
    void NostaTalletaSiirra_clicked();

    void on_etusivu_clicked();

    void on_vaihdaPin_clicked();

signals:
    void requestLogin(QString, QByteArray, QJsonObject);
    void requestPost(QString, QByteArray, QJsonObject);
    void requestGet(QString, QByteArray);
    void requestPut(QString, QByteArray, QJsonObject);

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;
    numpad_ui *objNumPad;
    Rest_api *objRestApi;
    Rfid_dll *oRfid;
    QTimer *ajastin;

    QString kortinnro;
    QByteArray webToken;

    QString nimi, osoite, puhnro, tilinro, saldo;
    QString rcvTilinro;
    int loginAttempts;
    bool kirjautunutState;
    bool korttiValidointi;

    rahaliikenne toimenpide;
    events event;

    QString summa;
    QVector<QString> lukitutKortit;

    QString uusiPIN;

    void loginHandler();
    void kirjautumisHandler(events);
    void loggedInHandler(events);
    void pageHandler(pages, bool, bool, QString);
    void summaHandler(QString, rahaliikenne);
    void rahaliikenneHandler();
    void summaButtonsHandler();
    void tilinumeroHandler();
    void korttiOlemassaCheck();
    bool lukitutKortitCheck();
    void pinVaihtoHandler(events);
};
#endif // MAINWINDOW_H
