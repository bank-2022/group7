QT       += core gui
QT       += network
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/rest_api_dll/build/release/ -lrest_api
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/rest_api_dll/build/debug/ -lrest_api

INCLUDEPATH += $$PWD/rest_api_dll
DEPENDPATH += $$PWD/rest_api_dll

win32: LIBS += -L$$PWD/rfid_dll/build/debug/ -lrfid_dll

INCLUDEPATH += $$PWD/rfid_dll
DEPENDPATH += $$PWD/rfid_dll
