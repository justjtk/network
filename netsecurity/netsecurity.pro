QT       += core gui
QT       +=network
QT += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DES.cpp \
    MD5.cpp \
    RSA.cpp \
    imagehandle.cpp \
    main.cpp \
    mainwindow.cpp \
    modifyinf.cpp \
    modifypsw.cpp \
    network.cpp \
    wmodify.cpp \
    wuser.cpp

HEADERS += \
    DES.h \
    MD5.h \
    RSA.h \
    imagehandle.h \
    kerberos.h \
    mainwindow.h \
    modifyinf.h \
    modifypsw.h \
    network.h \
    wmodify.h \
    wuser.h

FORMS += \
    mainwindow.ui \
    modifyinf.ui \
    modifypsw.ui \
    wmodify.ui \
    wuser.ui

LIBS += -llibgmp-10
win32: LIBS += -L$$PWD/ -llibgmp-10
INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target