QT += core gui widgets
TARGET = trojan-gui
TEMPLATE = app

SOURCES += \
    trojan/src/authenticator.cpp \
    trojan/src/clientsession.cpp \
    trojan/src/config.cpp \
    trojan/src/log.cpp \
    trojan/src/serversession.cpp \
    trojan/src/service.cpp \
    trojan/src/session.cpp \
    trojan/src/socks5address.cpp \
    trojan/src/ssldefaults.cpp \
    trojan/src/trojanrequest.cpp \
    trojan/src/udppacket.cpp \
    trojan/src/version.cpp \
    main.cpp \
    widget.cpp \
    trojanthread.cpp \
    configdialog.cpp

HEADERS += \
    trojan/src/authenticator.h \
    trojan/src/clientsession.h \
    trojan/src/config.h \
    trojan/src/log.h \
    trojan/src/serversession.h \
    trojan/src/service.h \
    trojan/src/session.h \
    trojan/src/socks5address.h \
    trojan/src/ssldefaults.h \
    trojan/src/trojanrequest.h \
    trojan/src/udppacket.h \
    trojan/src/version.h \
    widget.h \
    trojanthread.h \
    configdialog.h

FORMS += \
    widget.ui \
    configdialog.ui

unix {
    INCLUDEPATH += /usr/include/mysql
    LIBS += -lboost_system -lssl -lcrypto -lmysqlclient
}
