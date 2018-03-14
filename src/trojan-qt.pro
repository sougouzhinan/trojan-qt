#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T15:04:30
#
#-------------------------------------------------


QT       += core gui widgets

TARGET = trojan-qt
TEMPLATE = app

CONFIG += c++11

macx{
    INCLUDEPATH += /usr/local/include/
    INCLUDEPATH += /usr/local/opt/openssl/include/
    LIBS += -L/usr/local/lib -lpthread -L/usr/local/opt/openssl/lib -lssl -lcrypto -L/usr/local/Cellar/boost/1.66.0/lib -lboost_system
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    trojan/src/clientsession.cpp \
    trojan/src/config.cpp \
    trojan/src/log.cpp \
    trojan/src/serversession.cpp \
    trojan/src/service.cpp \
    trojan/src/session.cpp \
    trojan/src/ssldefaults.cpp \
    trojan/src/trojanrequest.cpp \
    trojan/src/version.cpp \
    App.cpp \
    main.cpp \
    TextButton.cpp

HEADERS += \
    trojan/src/clientsession.h \
    trojan/src/config.h \
    trojan/src/log.h \
    trojan/src/serversession.h \
    trojan/src/service.h \
    trojan/src/session.h \
    trojan/src/ssldefaults.h \
    trojan/src/trojanrequest.h \
    trojan/src/version.h \
    App.h \
    TextButton.h


