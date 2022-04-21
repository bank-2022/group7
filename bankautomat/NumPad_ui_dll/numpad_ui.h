#ifndef NUMPAD_UI_H
#define NUMPAD_UI_H

#include <QDialog>
#include <QDebug>
#include <QCloseEvent>
#include "numpad_ui_global.h"


namespace Ui {
class numpad_ui;
}

class NUMPAD_UI_EXPORT numpad_ui : public QDialog
{
    Q_OBJECT

public:
    explicit numpad_ui(QWidget *parent = nullptr);
    ~numpad_ui();
    void clickedHandler(QString);

    void stringSizeLimiter(bool, int);
    void censorInput(bool);

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_btn1_2_clicked();

    void on_btn2_clicked();

    void on_btn3_clicked();

    void on_btn4_clicked();

    void on_btn5_clicked();

    void on_btn6_clicked();

    void on_btn7_clicked();

    void on_btn8_clicked();

    void on_btn9_clicked();

    void on_btn0_clicked();

    void on_btnClear_clicked();

    void on_btnEnter_clicked();

private:
    Ui::numpad_ui *ui;
    QString num;
    bool limitCondition;
    int maxLength;
signals:
     void returnNum(QString);
};

#endif // NUMPAD_UI_H
