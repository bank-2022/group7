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

    ui->pinCode->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete objRestApi;
    objRestApi = nullptr;
}

void MainWindow::on_syotaPin_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_kirjaudu_clicked()
{
    username = ui->idKortti->text();
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
