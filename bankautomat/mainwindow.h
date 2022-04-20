#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "rest_api.h"
#include "numpad_ui.h"

#include <QMainWindow>
#include <QDebug>
#include <QObject>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


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

    void pinHandler();

    void on_nosta10_clicked();

    void on_nosta20_clicked();

    void on_nosta50_clicked();

    void on_nosta100_clicked();

    void on_nosta500_clicked();

    void on_muuSumma_clicked();

    void on_naytaTiedot_clicked();

signals:
    void requestLogin(QString, QByteArray, QJsonObject);
    void requestPost(QString, QByteArray, QJsonObject);
    void requestGet(QString, QByteArray);
    void requestPut(QString, QByteArray, QJsonObject);
    void login();

private:
    Ui::MainWindow *ui;
    Rest_api *objRestApi;
    QString kortinnro;
    QString pin;
    QByteArray webToken;
    QJsonObject jsonObj;
    numpad_ui *objNumPad;


};
#endif // MAINWINDOW_H
