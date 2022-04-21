#include "numpad_ui.h"
#include "ui_numpad_ui.h"

numpad_ui::numpad_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::numpad_ui)
{
    ui->setupUi(this);
    limitCondition = false;
}

numpad_ui::~numpad_ui()
{
    delete ui;
}

void numpad_ui::closeEvent(QCloseEvent *event)
{
    ui->lineEdit->clear();
    num.clear();
    event->accept();
}


void numpad_ui::clickedHandler(QString numero)
{
    num.append(numero);
    stringSizeLimiter(limitCondition, maxLength);
    ui->lineEdit->setText(num);
}

void numpad_ui::stringSizeLimiter(bool isLimited, int strMax)
{
    if(isLimited == false){
        limitCondition = false;
    }
    else if(isLimited == true){
        limitCondition = true;
        maxLength = strMax;
        if(num.length() > maxLength){
            num.remove(maxLength, 1);
        }
    }
}

void numpad_ui::censorInput(bool isCensored)
{
    if(isCensored == false){
        ui->lineEdit->setEchoMode(QLineEdit::Normal);
    } else if(isCensored == true){
        ui->lineEdit->setEchoMode(QLineEdit::Password);
    }
}

void numpad_ui::on_btnEnter_clicked()
{
    emit returnNum(num);
    ui->lineEdit->clear();
    num.clear();

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
    num.clear();
}




