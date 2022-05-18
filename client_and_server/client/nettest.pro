QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DES.cpp \
    MD5.cpp \
    RSA.cpp \
    homepage.cpp \
    imagehandle.cpp \
    main.cpp \
    mainwindow.cpp \
    network.cpp \
    wadmin.cpp \
    wgood.cpp \
    wireshark.cpp \
    wlogin.cpp \
    wmodify.cpp \
    wpay.cpp \
    wtrolley.cpp \
    wuser.cpp

HEADERS += \
    DES.h \
    MD5.h \
    RSA.h \
    homepage.h \
    imagehandle.h \
    mainwindow.h \
    network.h \
    wadmin.h \
    wgood.h \
    wireshark.h \
    wlogin.h \
    wmodify.h \
    wpay.h \
    wtrolley.h \
    wuser.h

FORMS += \
    homepage.ui \
    mainwindow.ui \
    wadmin.ui \
    wgood.ui \
    wireshark.ui \
    wlogin.ui \
    wmodify.ui \
    wpay.ui \
    wtrolley.ui \
    wuser.ui

LIBS += -llibgmp-10
win32: LIBS += -L$$PWD/ -llibgmp-10
INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#QMAKE_CXXFLAGS += -gstabs+
#QMAKE_CXXFLAGS_DEBUG += -gstabs+
#CONFIG += console

RESOURCES += \
    source.qrc

