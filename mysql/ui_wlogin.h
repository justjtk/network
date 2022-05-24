/********************************************************************************
** Form generated from reading UI file 'wlogin.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WLOGIN_H
#define UI_WLOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WLogin
{
public:
    QWidget *centralwidget;
    QWidget *widget;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WLogin)
    {
        if (WLogin->objectName().isEmpty())
            WLogin->setObjectName(QString::fromUtf8("WLogin"));
        WLogin->resize(755, 608);
        centralwidget = new QWidget(WLogin);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(110, 60, 530, 440));
        widget->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 245, 245), stop:1 rgb(255, 254, 245));\n"
"border-radius:10px;"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(210, 120, 121, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe \351\273\221\344\275\223 Std R"));
        font.setPointSize(20);
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignCenter);
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(150, 210, 251, 31));
        lineEdit_2 = new QLineEdit(widget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(150, 270, 251, 31));
        lineEdit_2->setEchoMode(QLineEdit::Password);
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 350, 251, 41));
        pushButton->setCursor(QCursor(Qt::PointingHandCursor));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(230, 50, 80, 60));
        label_4->setStyleSheet(QString::fromUtf8(""));
        WLogin->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WLogin);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 755, 26));
        WLogin->setMenuBar(menubar);
        statusbar = new QStatusBar(WLogin);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WLogin->setStatusBar(statusbar);

        retranslateUi(WLogin);

        QMetaObject::connectSlotsByName(WLogin);
    } // setupUi

    void retranslateUi(QMainWindow *WLogin)
    {
        WLogin->setWindowTitle(QCoreApplication::translate("WLogin", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("WLogin", "SHOP", nullptr));
        lineEdit->setText(QCoreApplication::translate("WLogin", "100001", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("WLogin", "123456", nullptr));
        pushButton->setText(QCoreApplication::translate("WLogin", "\347\231\273\345\275\225", nullptr));
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WLogin: public Ui_WLogin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WLOGIN_H
