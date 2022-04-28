/********************************************************************************
** Form generated from reading UI file 'numpad_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMPAD_UI_H
#define UI_NUMPAD_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_numpad_ui
{
public:
    QGridLayout *gridLayout;
    QPushButton *btn7;
    QPushButton *btn3;
    QPushButton *btn6;
    QPushButton *btn0;
    QPushButton *btn9;
    QPushButton *btn5;
    QPushButton *btnClear;
    QPushButton *btn4;
    QPushButton *btn1_2;
    QPushButton *btn8;
    QPushButton *btn2;
    QPushButton *btnEnter;
    QLineEdit *lineEdit;
    QPushButton *btnPiste;

    void setupUi(QDialog *numpad_ui)
    {
        if (numpad_ui->objectName().isEmpty())
            numpad_ui->setObjectName(QString::fromUtf8("numpad_ui"));
        numpad_ui->resize(270, 268);
        gridLayout = new QGridLayout(numpad_ui);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        btn7 = new QPushButton(numpad_ui);
        btn7->setObjectName(QString::fromUtf8("btn7"));

        gridLayout->addWidget(btn7, 2, 0, 1, 1);

        btn3 = new QPushButton(numpad_ui);
        btn3->setObjectName(QString::fromUtf8("btn3"));

        gridLayout->addWidget(btn3, 0, 2, 1, 1);

        btn6 = new QPushButton(numpad_ui);
        btn6->setObjectName(QString::fromUtf8("btn6"));

        gridLayout->addWidget(btn6, 1, 2, 1, 1);

        btn0 = new QPushButton(numpad_ui);
        btn0->setObjectName(QString::fromUtf8("btn0"));

        gridLayout->addWidget(btn0, 3, 1, 1, 1);

        btn9 = new QPushButton(numpad_ui);
        btn9->setObjectName(QString::fromUtf8("btn9"));

        gridLayout->addWidget(btn9, 2, 2, 1, 1);

        btn5 = new QPushButton(numpad_ui);
        btn5->setObjectName(QString::fromUtf8("btn5"));

        gridLayout->addWidget(btn5, 1, 1, 1, 1);

        btnClear = new QPushButton(numpad_ui);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        gridLayout->addWidget(btnClear, 3, 2, 1, 1);

        btn4 = new QPushButton(numpad_ui);
        btn4->setObjectName(QString::fromUtf8("btn4"));

        gridLayout->addWidget(btn4, 1, 0, 1, 1);

        btn1_2 = new QPushButton(numpad_ui);
        btn1_2->setObjectName(QString::fromUtf8("btn1_2"));

        gridLayout->addWidget(btn1_2, 0, 0, 1, 1);

        btn8 = new QPushButton(numpad_ui);
        btn8->setObjectName(QString::fromUtf8("btn8"));

        gridLayout->addWidget(btn8, 2, 1, 1, 1);

        btn2 = new QPushButton(numpad_ui);
        btn2->setObjectName(QString::fromUtf8("btn2"));

        gridLayout->addWidget(btn2, 0, 1, 1, 1);

        btnEnter = new QPushButton(numpad_ui);
        btnEnter->setObjectName(QString::fromUtf8("btnEnter"));

        gridLayout->addWidget(btnEnter, 4, 1, 1, 1);

        lineEdit = new QLineEdit(numpad_ui);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        gridLayout->addWidget(lineEdit, 7, 0, 1, 3);

        btnPiste = new QPushButton(numpad_ui);
        btnPiste->setObjectName(QString::fromUtf8("btnPiste"));

        gridLayout->addWidget(btnPiste, 3, 0, 1, 1);


        retranslateUi(numpad_ui);

        QMetaObject::connectSlotsByName(numpad_ui);
    } // setupUi

    void retranslateUi(QDialog *numpad_ui)
    {
        numpad_ui->setWindowTitle(QApplication::translate("numpad_ui", "Dialog", nullptr));
        btn7->setText(QApplication::translate("numpad_ui", "7", nullptr));
        btn3->setText(QApplication::translate("numpad_ui", "3", nullptr));
        btn6->setText(QApplication::translate("numpad_ui", "6", nullptr));
        btn0->setText(QApplication::translate("numpad_ui", "0", nullptr));
        btn9->setText(QApplication::translate("numpad_ui", "9", nullptr));
        btn5->setText(QApplication::translate("numpad_ui", "5", nullptr));
        btnClear->setText(QApplication::translate("numpad_ui", "Clear", nullptr));
        btn4->setText(QApplication::translate("numpad_ui", "4", nullptr));
        btn1_2->setText(QApplication::translate("numpad_ui", "1", nullptr));
        btn8->setText(QApplication::translate("numpad_ui", "8", nullptr));
        btn2->setText(QApplication::translate("numpad_ui", "2", nullptr));
        btnEnter->setText(QApplication::translate("numpad_ui", "Enter", nullptr));
        btnPiste->setText(QApplication::translate("numpad_ui", ".", nullptr));
    } // retranslateUi

};

namespace Ui {
    class numpad_ui: public Ui_numpad_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMPAD_UI_H
