#include "numpad_ui.h"
#include "ui_numpad_ui.h"

numpad_ui::numpad_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::numpad_ui)
{
    ui->setupUi(this);
    numArvo = "";
}

numpad_ui::~numpad_ui()
{
    delete ui;
}

void numpad_ui::on_btn1_2_clicked()
{
    numArvo += "1";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn2_clicked()
{
    numArvo += "2";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn3_clicked()
{
    numArvo += "3";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn4_clicked()
{
    numArvo += "4";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn5_clicked()
{
    numArvo += "5";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn6_clicked()
{
    numArvo += "6";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn7_clicked()
{
    numArvo += "7";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn8_clicked()
{
    numArvo += "8";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn9_clicked()
{
    numArvo += "9";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btn0_clicked()
{
    numArvo += "0";
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btnClear_clicked()
{
    numArvo.clear();
    ui->lineEdit->setText(numArvo);
}


void numpad_ui::on_btnEnter_clicked()
{
    emit sendNumToExe(numArvo);
    qDebug() << numArvo;
}

