 # This file is part of the trojan project.
 # Trojan is an unidentifiable mechanism that helps you bypass GFW.
 # Copyright (C) 2018  Light Bob
 #
 # This program is free software: you can redistribute it and/or modify
 # it under the terms of the GNU General Public License as published by
 # the Free Software Foundation, either version 3 of the License, or
 # (at your option) any later version.
 #
 # This program is distributed in the hope that it will be useful,
 # but WITHOUT ANY WARRANTY; without even the implied warranty of
 # MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 # GNU General Public License for more details.
 #
 # You should have received a copy of the GNU General Public License
 # along with this program.  If not, see <http://www.gnu.org/licenses/>.


QT       += core gui widgets
DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = app
TARGET = Trojan
ICON = trojan-qt.icns

CONFIG += c++11

mac{
    QMAKE_INCDIR += /System/Library/Frameworks/AppKit.framework/Headers /System/Library/Frameworks/Security.framework/Headers /System/Library/Frameworks/ServiceManagement.framework/Headers
    QMAKE_LFLAGS += -framework IOKit -framework Cocoa -framework Security
    QMAKE_LFLAGS += -F /System/Library/Frameworks/Security.framework/
    LIBS += -framework Security
}

unix{
    INCLUDEPATH += /usr/local/include/
    INCLUDEPATH += /usr/local/opt/openssl/include/
    INCLUDEPATH += /usr/local/opt/boost/include/
    LIBS += -L/usr/local/lib -lpthread
    LIBS += -L/usr/local/opt/openssl/lib -lssl -lcrypto
    LIBS += -L/usr/local/opt/boost/lib -lboost_system

#    The right way to do it with pkg-config, but it points to the deprecated system OpenSSL.
#    CONFIG += link_pkgconfig
#    PKGCONFIG += openssl
}

SOURCES += \
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
    App.cpp \
    main.cpp \
    Window.cpp \
    Button.cpp \
    IconButton.cpp \
    BodyWidget.cpp \
    StackedWidget.cpp \
    ServiceThread.cpp \
    Global.cpp

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
    IconButton.h \
    BodyWidget.h \
    StackedWidget.h \
    ServiceThread.h \
    Global.h

RESOURCES += \
    img.qrc \
    file.qrc





