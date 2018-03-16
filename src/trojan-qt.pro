#-------------------------------------------------
#
# Project created by QtCreator 2018-03-14T15:04:30
#
#-------------------------------------------------


QT       += core gui widgets
DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = app
TARGET = trojan-qt
ICON = trojan-qt.icns

CONFIG += c++11

macx{
    INCLUDEPATH += /usr/local/include/
    INCLUDEPATH += /usr/local/opt/openssl/include/
    INCLUDEPATH += /usr/local/opt/boost/include/
    LIBS += -L/usr/local/lib -lpthread
    LIBS += -L/usr/local/opt/openssl/lib -lssl -lcrypto
    LIBS += -L/usr/local/opt/boost/lib -lboost_system
}



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
    Window.cpp \
    Button.cpp \
    IconButton.cpp

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
    Window.h \
    Button.h \
    Version.h \
    IconButton.h

RESOURCES += \
    img.qrc



