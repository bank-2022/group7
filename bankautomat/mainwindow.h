#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rest_api.h"
#include "numpad_ui.h"
#include "rfid_dll.h"

#include <QMainWindow>
#include <QDebug>
#include <QObject>
#include <QSerialPort>

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
        nosto,
        talletus,
        tilisiirto
    };

private slots:
    void processData(QString, QByteArray);

    void on_syotaPin_clicked();

    void on_kirjaudu_clicked();

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

    void summaHandler(QString, states);

    void on_naytaTiedot_clicked();

    void getRfid(QString id);

    void numpadHandler(QString);

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
    QString num;
    QByteArray webToken;
    numpad_ui *objNumPad;

    states state;


};
#endif // MAINWINDOW_H
