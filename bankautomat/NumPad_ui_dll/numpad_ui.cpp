#include "numpad_ui.h"
#include "ui_numpad_ui.h"

numpad_ui::numpad_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::numpad_ui)
{
    ui->setupUi(this);
}

numpad_ui::~numpad_ui()
{
    delete ui;
}

void numpad_ui::clickedHandler(QString numero)
{
    pin.append(numero);
    ui->lineEdit->setText(pin);
}

void numpad_ui::on_btnEnter_clicked()
{
    emit sendNumToExe(pin);
}

void numpad_ui::on_btn1_2_clicked()
{
    clickedHandler("1");
}


void numpad_ui::on_btn2_clicked()
{
    clickedHandler("2");
}


void numpad_ui::on_btn3_clicked()
{
    clickedHandler("3");
}


void numpad_ui::on_btn4_clicked()
{
    clickedHandler("4");
}


void numpad_ui::on_btn5_clicked()
{
    clickedHandler("5");
}


void numpad_ui::on_btn6_clicked()
{
    clickedHandler("6");
}


void numpad_ui::on_btn7_clicked()
{
    clickedHandler("7");
}


void numpad_ui::on_btn8_clicked()
{
    clickedHandler("8");
}


void numpad_ui::on_btn9_clicked()
{
    clickedHandler("9");
}


void numpad_ui::on_btn0_clicked()
{
    clickedHandler("0");
}


void numpad_ui::on_btnClear_clicked()
{
    ui->lineEdit->clear();
    pin.clear();
}




