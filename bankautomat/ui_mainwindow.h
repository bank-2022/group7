/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *tervetuloaPage;
    QPushButton *syotaPin;
    QTextBrowser *textBrowser;
    QWidget *kirjauduPage;
    QLineEdit *idKortti;
    QPushButton *kirjaudu;
    QLabel *kirjautumisLabel;
    QPushButton *showNumpad;
    QWidget *mainPage;
    QLabel *saldoLabel;
    QLCDNumber *saldoLCD;
    QWidget *nostoPage;
    QWidget *naytaTiedotPage;
    QWidget *talletusPage;
    QWidget *tilitapahtumaPage;
    QTableView *tableView;
    QWidget *tilisiirtoPage;
    QPushButton *syotaTilinumero;
    QWidget *summatWidget;
    QPushButton *summa10;
    QPushButton *summa20;
    QPushButton *summa50;
    QPushButton *summa100;
    QPushButton *summa500;
    QPushButton *summaMuu;
    QWidget *valikkoWidget;
    QPushButton *kirjauduUlos;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *nosto;
    QPushButton *talletus;
    QPushButton *tilisiirto;
    QPushButton *tilitapahtumat;
    QPushButton *naytaTiedot;
    QLabel *otsikkoLabel;
    QLabel *logoutTimerTeksti;
    QLabel *logoutTimerNumero;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(866, 648);
        MainWindow->setMouseTracking(true);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(10, 0, 851, 631));
        tervetuloaPage = new QWidget();
        tervetuloaPage->setObjectName(QString::fromUtf8("tervetuloaPage"));
        syotaPin = new QPushButton(tervetuloaPage);
        syotaPin->setObjectName(QString::fromUtf8("syotaPin"));
        syotaPin->setGeometry(QRect(280, 320, 251, 141));
        textBrowser = new QTextBrowser(tervetuloaPage);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(210, 70, 381, 192));
        stackedWidget->addWidget(tervetuloaPage);
        kirjauduPage = new QWidget();
        kirjauduPage->setObjectName(QString::fromUtf8("kirjauduPage"));
        idKortti = new QLineEdit(kirjauduPage);
        idKortti->setObjectName(QString::fromUtf8("idKortti"));
        idKortti->setGeometry(QRect(360, 160, 108, 24));
        kirjaudu = new QPushButton(kirjauduPage);
        kirjaudu->setObjectName(QString::fromUtf8("kirjaudu"));
        kirjaudu->setGeometry(QRect(370, 260, 80, 24));
        kirjautumisLabel = new QLabel(kirjauduPage);
        kirjautumisLabel->setObjectName(QString::fromUtf8("kirjautumisLabel"));
        kirjautumisLabel->setGeometry(QRect(340, 300, 151, 61));
        showNumpad = new QPushButton(kirjauduPage);
        showNumpad->setObjectName(QString::fromUtf8("showNumpad"));
        showNumpad->setGeometry(QRect(350, 210, 131, 25));
        stackedWidget->addWidget(kirjauduPage);
        mainPage = new QWidget();
        mainPage->setObjectName(QString::fromUtf8("mainPage"));
        saldoLabel = new QLabel(mainPage);
        saldoLabel->setObjectName(QString::fromUtf8("saldoLabel"));
        saldoLabel->setGeometry(QRect(140, 150, 171, 41));
        saldoLCD = new QLCDNumber(mainPage);
        saldoLCD->setObjectName(QString::fromUtf8("saldoLCD"));
        saldoLCD->setGeometry(QRect(130, 200, 281, 61));
        stackedWidget->addWidget(mainPage);
        nostoPage = new QWidget();
        nostoPage->setObjectName(QString::fromUtf8("nostoPage"));
        stackedWidget->addWidget(nostoPage);
        naytaTiedotPage = new QWidget();
        naytaTiedotPage->setObjectName(QString::fromUtf8("naytaTiedotPage"));
        stackedWidget->addWidget(naytaTiedotPage);
        talletusPage = new QWidget();
        talletusPage->setObjectName(QString::fromUtf8("talletusPage"));
        stackedWidget->addWidget(talletusPage);
        tilitapahtumaPage = new QWidget();
        tilitapahtumaPage->setObjectName(QString::fromUtf8("tilitapahtumaPage"));
        tableView = new QTableView(tilitapahtumaPage);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(70, 140, 370, 221));
        stackedWidget->addWidget(tilitapahtumaPage);
        tilisiirtoPage = new QWidget();
        tilisiirtoPage->setObjectName(QString::fromUtf8("tilisiirtoPage"));
        syotaTilinumero = new QPushButton(tilisiirtoPage);
        syotaTilinumero->setObjectName(QString::fromUtf8("syotaTilinumero"));
        syotaTilinumero->setGeometry(QRect(260, 240, 111, 21));
        stackedWidget->addWidget(tilisiirtoPage);
        summatWidget = new QWidget(centralwidget);
        summatWidget->setObjectName(QString::fromUtf8("summatWidget"));
        summatWidget->setEnabled(true);
        summatWidget->setGeometry(QRect(150, 400, 341, 161));
        summa10 = new QPushButton(summatWidget);
        summa10->setObjectName(QString::fromUtf8("summa10"));
        summa10->setGeometry(QRect(30, 50, 80, 22));
        summa20 = new QPushButton(summatWidget);
        summa20->setObjectName(QString::fromUtf8("summa20"));
        summa20->setGeometry(QRect(130, 50, 80, 22));
        summa50 = new QPushButton(summatWidget);
        summa50->setObjectName(QString::fromUtf8("summa50"));
        summa50->setGeometry(QRect(230, 50, 80, 22));
        summa100 = new QPushButton(summatWidget);
        summa100->setObjectName(QString::fromUtf8("summa100"));
        summa100->setGeometry(QRect(30, 120, 80, 22));
        summa500 = new QPushButton(summatWidget);
        summa500->setObjectName(QString::fromUtf8("summa500"));
        summa500->setGeometry(QRect(130, 120, 80, 22));
        summaMuu = new QPushButton(summatWidget);
        summaMuu->setObjectName(QString::fromUtf8("summaMuu"));
        summaMuu->setGeometry(QRect(230, 120, 80, 22));
        valikkoWidget = new QWidget(centralwidget);
        valikkoWidget->setObjectName(QString::fromUtf8("valikkoWidget"));
        valikkoWidget->setGeometry(QRect(700, 40, 161, 571));
        kirjauduUlos = new QPushButton(valikkoWidget);
        kirjauduUlos->setObjectName(QString::fromUtf8("kirjauduUlos"));
        kirjauduUlos->setGeometry(QRect(20, 460, 121, 101));
        verticalLayoutWidget = new QWidget(valikkoWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(9, 9, 141, 371));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(7);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        nosto = new QPushButton(verticalLayoutWidget);
        nosto->setObjectName(QString::fromUtf8("nosto"));

        verticalLayout->addWidget(nosto);

        talletus = new QPushButton(verticalLayoutWidget);
        talletus->setObjectName(QString::fromUtf8("talletus"));

        verticalLayout->addWidget(talletus);

        tilisiirto = new QPushButton(verticalLayoutWidget);
        tilisiirto->setObjectName(QString::fromUtf8("tilisiirto"));

        verticalLayout->addWidget(tilisiirto);

        tilitapahtumat = new QPushButton(verticalLayoutWidget);
        tilitapahtumat->setObjectName(QString::fromUtf8("tilitapahtumat"));

        verticalLayout->addWidget(tilitapahtumat);

        naytaTiedot = new QPushButton(verticalLayoutWidget);
        naytaTiedot->setObjectName(QString::fromUtf8("naytaTiedot"));

        verticalLayout->addWidget(naytaTiedot);

        otsikkoLabel = new QLabel(centralwidget);
        otsikkoLabel->setObjectName(QString::fromUtf8("otsikkoLabel"));
        otsikkoLabel->setGeometry(QRect(50, 30, 361, 81));
        logoutTimerTeksti = new QLabel(centralwidget);
        logoutTimerTeksti->setObjectName(QString::fromUtf8("logoutTimerTeksti"));
        logoutTimerTeksti->setGeometry(QRect(610, 630, 231, 20));
        logoutTimerNumero = new QLabel(centralwidget);
        logoutTimerNumero->setObjectName(QString::fromUtf8("logoutTimerNumero"));
        logoutTimerNumero->setGeometry(QRect(820, 630, 41, 20));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Bankautomat", nullptr));
        syotaPin->setText(QApplication::translate("MainWindow", "sy\303\266t\303\244", nullptr));
        textBrowser->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:36pt;\">TERVETULOA</span><span style=\" font-size:9.75pt;\"> <br /><br /></span><span style=\" font-size:26pt;\">SY\303\226T\303\204 KORTTI</span></p></body></html>", nullptr));
        kirjaudu->setText(QApplication::translate("MainWindow", "Kirjaudu", nullptr));
        kirjautumisLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><br/></p></body></html>", nullptr));
        showNumpad->setText(QApplication::translate("MainWindow", "respawn numpad", nullptr));
        saldoLabel->setText(QApplication::translate("MainWindow", "Tilisi saldo:", nullptr));
        syotaTilinumero->setText(QApplication::translate("MainWindow", "Sy\303\266t\303\244 tilinumero", nullptr));
        summa10->setText(QApplication::translate("MainWindow", "10", nullptr));
        summa20->setText(QApplication::translate("MainWindow", "20", nullptr));
        summa50->setText(QApplication::translate("MainWindow", "50", nullptr));
        summa100->setText(QApplication::translate("MainWindow", "100", nullptr));
        summa500->setText(QApplication::translate("MainWindow", "500", nullptr));
        summaMuu->setText(QApplication::translate("MainWindow", "muu", nullptr));
        kirjauduUlos->setText(QApplication::translate("MainWindow", "Kirjaudu ulos", nullptr));
        nosto->setText(QApplication::translate("MainWindow", "Nosto", nullptr));
        talletus->setText(QApplication::translate("MainWindow", "Talletus", nullptr));
        tilisiirto->setText(QApplication::translate("MainWindow", "Tilisiirto", nullptr));
        tilitapahtumat->setText(QApplication::translate("MainWindow", "Selaa tilitapahtumia", nullptr));
        naytaTiedot->setText(QApplication::translate("MainWindow", "N\303\244yt\303\244 tietosi", nullptr));
        otsikkoLabel->setText(QApplication::translate("MainWindow", "<html><head/><body><p><br/></p></body></html>", nullptr));
        logoutTimerTeksti->setText(QApplication::translate("MainWindow", "automaattiseen uloskirjautumiseen aikaa :", nullptr));
        logoutTimerNumero->setText(QApplication::translate("MainWindow", "30", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
