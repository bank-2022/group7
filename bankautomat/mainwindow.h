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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum states{
        eiKirjautunut,
        kirjautunut,
    };

    enum events{
        korttiSyotetty,
        pinSyotetty,
        pinVaarin,
        pinOikein,
        naytaEtusivu,
        nosto,
        talletus,
        tilisiirto,
        tilitapahtumat,
        naytaTiedot,
        kirjauduUlos,


        muuSumma,
        muuSummaSyotetty,
    };

    enum pages{
        tervetuloaPage,
        kirjauduPage,
        mainPage,
        nostoPage,
        tiedotPage,
        talletusPage,
        tilitapahtumaPage,
        tilisiirtoPage
    };

private slots:
    void processData(QString, QByteArray);
    void on_syotaPin_clicked();
    void on_tilitapahtumat_clicked();
    void on_nosto_clicked();
    void on_talletus_clicked();
    void on_tilisiirto_clicked();
    void on_kirjauduUlos_clicked();
    void loginHandler();
    void on_summa10_clicked();
    void on_summa20_clicked();
    void on_summa50_clicked();
    void on_summa100_clicked();
    void on_summa500_clicked();
    void on_summaMuu_clicked();
    void summaHandler(QString, events);
    void on_naytaTiedot_clicked();
    void numpadEnter_clicked();
    void on_showNumpad_clicked();

signals:
    void requestLogin(QString, QByteArray, QJsonObject);
    void requestPost(QString, QByteArray, QJsonObject);
    void requestGet(QString, QByteArray);
    void requestPut(QString, QByteArray, QJsonObject);
    void login();

private:
    Ui::MainWindow *ui;
    Rest_api *objRestApi;
    Rfid_dll *oRfid;
    QString kortinnro;
    QByteArray webToken;
    numpad_ui *objNumPad;
    QString nimi, osoite, puhnro, tilinro, saldo;

    states state;
    events event;

    void runStateMachine(states, events);
    void eiKirjautunutHandler(events);
    void kirjautunutHandler(events);
    void pageHandler(pages, bool, bool, QString);

};
#endif // MAINWINDOW_H
