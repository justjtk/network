#-------------------------------------------------
#
# Project created by QtCreator 2021-06-30T16:21:50
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mysql
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        DES.cpp \
        MD5.cpp \
        RSA.cpp \
        dialog0.cpp \
        imagehandle.cpp \
        main.cpp \
        mainwindow.cpp \
        network.cpp \
        package_show.cpp \
        wlogin.cpp

HEADERS += \
        DES.h \
        MD5.h \
        RSA.h \
        dialog0.h \
        imagehandle.h \
        kerberos.h \
        mainwindow.h \
        network.h \
        package_show.h \
        wlogin.h

FORMS += \
        dialog0.ui \
        mainwindow.ui \
        package_show.ui \
        wlogin.ui


LIBS += -llibgmp-10
win32: LIBS += -L$$PWD/ -llibgmp-10
INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qss.qrc
