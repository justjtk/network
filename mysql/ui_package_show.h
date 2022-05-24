/********************************************************************************
** Form generated from reading UI file 'package_show.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PACKAGE_SHOW_H
#define UI_PACKAGE_SHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_package_show
{
public:
    QWidget *centralwidget;
    QTableView *tableView;
    QLabel *label_3;
    QTextEdit *textEdit_2;
    QLabel *label_2;
    QTextEdit *textEdit;
    QLabel *label;
    QTextEdit *textEdit_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *package_show)
    {
        if (package_show->objectName().isEmpty())
            package_show->setObjectName(QString::fromUtf8("package_show"));
        package_show->resize(1301, 964);
        centralwidget = new QWidget(package_show);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tableView = new QTableView(centralwidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 0, 1301, 511));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(-10, 840, 81, 81));
        label_3->setFrameShape(QFrame::StyledPanel);
        textEdit_2 = new QTextEdit(centralwidget);
        textEdit_2->setObjectName(QString::fromUtf8("textEdit_2"));
        textEdit_2->setGeometry(QRect(70, 690, 1231, 121));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(-10, 690, 81, 121));
        label_2->setFrameShape(QFrame::StyledPanel);
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(70, 540, 1231, 111));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(-10, 540, 81, 111));
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Plain);
        textEdit_3 = new QTextEdit(centralwidget);
        textEdit_3->setObjectName(QString::fromUtf8("textEdit_3"));
        textEdit_3->setGeometry(QRect(70, 840, 1231, 81));
        package_show->setCentralWidget(centralwidget);
        menubar = new QMenuBar(package_show);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1301, 26));
        package_show->setMenuBar(menubar);
        statusbar = new QStatusBar(package_show);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        package_show->setStatusBar(statusbar);

        retranslateUi(package_show);

        QMetaObject::connectSlotsByName(package_show);
    } // setupUi

    void retranslateUi(QMainWindow *package_show)
    {
        package_show->setWindowTitle(QCoreApplication::translate("package_show", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("package_show", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">\345\257\206</span></p><p align=\"center\"><span style=\" font-weight:600;\">\351\222\245</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("package_show", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">\350\247\243</span></p><p align=\"center\"><span style=\" font-weight:600;\">\345\257\206</span></p><p align=\"center\"><span style=\" font-weight:600;\">\345\206\205</span></p><p align=\"center\"><span style=\" font-weight:600;\">\345\256\271</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("package_show", "<html><head/><body><p align=\"center\"><span style=\" font-weight:600;\">\346\212\245</span></p><p align=\"center\"><span style=\" font-weight:600;\">\346\226\207</span></p><p align=\"center\"><span style=\" font-weight:600;\">\345\206\205</span></p><p align=\"center\"><span style=\" font-weight:600;\">\345\256\271</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class package_show: public Ui_package_show {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PACKAGE_SHOW_H
