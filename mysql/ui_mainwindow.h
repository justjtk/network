/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiong;
    QAction *actionw;
    QAction *actionm;
    QAction *actions;
    QAction *actionp;
    QAction *actiona;
    QAction *export_2;
    QAction *Import;
    QAction *gtos;
    QAction *stog;
    QWidget *centralWidget;
    QTableView *tableView;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *comboBox;
    QPushButton *pushButton_3;
    QLabel *label;
    QLabel *label_4;
    QPushButton *pushButton_4;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1169, 775);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actiong = new QAction(MainWindow);
        actiong->setObjectName(QString::fromUtf8("actiong"));
        actiong->setCheckable(true);
        actionw = new QAction(MainWindow);
        actionw->setObjectName(QString::fromUtf8("actionw"));
        actionw->setCheckable(true);
        actionw->setMenuRole(QAction::TextHeuristicRole);
        actionm = new QAction(MainWindow);
        actionm->setObjectName(QString::fromUtf8("actionm"));
        actionm->setCheckable(true);
        actions = new QAction(MainWindow);
        actions->setObjectName(QString::fromUtf8("actions"));
        actions->setCheckable(true);
        actionp = new QAction(MainWindow);
        actionp->setObjectName(QString::fromUtf8("actionp"));
        actionp->setCheckable(true);
        actiona = new QAction(MainWindow);
        actiona->setObjectName(QString::fromUtf8("actiona"));
        actiona->setCheckable(true);
        export_2 = new QAction(MainWindow);
        export_2->setObjectName(QString::fromUtf8("export_2"));
        Import = new QAction(MainWindow);
        Import->setObjectName(QString::fromUtf8("Import"));
        gtos = new QAction(MainWindow);
        gtos->setObjectName(QString::fromUtf8("gtos"));
        stog = new QAction(MainWindow);
        stog->setObjectName(QString::fromUtf8("stog"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tableView = new QTableView(centralWidget);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(250, 0, 921, 721));
        tableView->setStyleSheet(QString::fromUtf8("QTableView {\n"
"    color: white;                                       /*\350\241\250\346\240\274\345\206\205\346\226\207\345\255\227\351\242\234\350\211\262*/\n"
"    gridline-color: black;                              /*\350\241\250\346\240\274\345\206\205\346\241\206\351\242\234\350\211\262*/\n"
"    background-color: rgb(108, 108, 108);               /*\350\241\250\346\240\274\345\206\205\350\203\214\346\231\257\350\211\262*/\n"
"    alternate-background-color: rgb(64, 64, 64);\n"
"    selection-color: white;                             /*\351\200\211\344\270\255\345\214\272\345\237\237\347\232\204\346\226\207\345\255\227\351\242\234\350\211\262*/\n"
"    selection-background-color: rgb(77, 77, 77);        /*\351\200\211\344\270\255\345\214\272\345\237\237\347\232\204\350\203\214\346\231\257\350\211\262*/\n"
"    border: 2px groove gray;\n"
"    border-radius: 0px;\n"
"    padding: 2px 4px;\n"
"}\n"
"\n"
"/*QTableView \345\267\246\344\270\212\350\247\222\346\240\267\345\274\217*/\n"
"QTableView QTableCor"
                        "nerButton::section {\n"
"   /*  background: red;\n"
"    border: 2px outset red;*/\n"
"    color: red;\n"
"    background-color: rgb(64, 64, 64);\n"
"    border: 5px solid #f6f7fa;\n"
"    border-radius:0px;\n"
"    border-color: rgb(64, 64, 64);\n"
" }\n"
"\n"
" QTableView {\n"
"    color: white;                                       /*\350\241\250\346\240\274\345\206\205\346\226\207\345\255\227\351\242\234\350\211\262*/\n"
"    gridline-color: black;                              /*\350\241\250\346\240\274\345\206\205\346\241\206\351\242\234\350\211\262*/\n"
"    background-color: rgb(108, 108, 108);               /*\350\241\250\346\240\274\345\206\205\350\203\214\346\231\257\350\211\262*/\n"
"    alternate-background-color: rgb(64, 64, 64);\n"
"    selection-color: white;                             /*\351\200\211\344\270\255\345\214\272\345\237\237\347\232\204\346\226\207\345\255\227\351\242\234\350\211\262*/\n"
"    selection-background-color: rgb(77, 77, 77);        /*\351\200\211\344\270\255\345\214\272\345"
                        "\237\237\347\232\204\350\203\214\346\231\257\350\211\262*/\n"
"    border: 2px groove gray;\n"
"    border-radius: 0px;\n"
"    padding: 2px 4px;\n"
"}\n"
"\n"
"QHeaderView {\n"
"    color: white;\n"
"    font: bold 10pt;\n"
"    background-color: rgb(108, 108, 108);\n"
"    border: 0px solid rgb(144, 144, 144);\n"
"    border:0px solid rgb(191,191,191);\n"
"    border-left-color: rgba(255, 255, 255, 0);\n"
"    border-top-color: rgba(255, 255, 255, 0);\n"
"    border-radius:0px;\n"
"    min-height:29px;\n"
"}\n"
"\n"
"QHeaderView::section {\n"
"    color: white;\n"
"    background-color: rgb(64, 64, 64);\n"
"    border: 5px solid #f6f7fa;\n"
"    border-radius:0px;\n"
"    border-color: rgb(64, 64, 64);\n"
"} \n"
""));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(20, 180, 171, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 350, 161, 81));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(20, 460, 161, 81));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 10, 111, 41));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 70, 111, 41));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(20, 130, 171, 31));
        comboBox->setStyleSheet(QString::fromUtf8("\n"
"background-color: #fff9fa;"));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 230, 161, 81));
        pushButton_3->setStyleSheet(QString::fromUtf8("border-color: rgb(253, 159, 154);"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 600, 100, 100));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 560, 91, 31));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(130, 20, 93, 28));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1169, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(actiong);
        menu->addAction(actionw);
        menu->addAction(actionm);
        menu->addAction(actions);
        menu->addAction(actionp);
        menu->addAction(actiona);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actiong->setText(QCoreApplication::translate("MainWindow", "\345\225\206\345\223\201\350\241\250", nullptr));
        actionw->setText(QCoreApplication::translate("MainWindow", "\350\264\255\347\211\251\350\275\246\350\241\250", nullptr));
        actionm->setText(QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230\350\241\250", nullptr));
        actions->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267\350\241\250", nullptr));
        actionp->setText(QCoreApplication::translate("MainWindow", "\344\274\232\345\221\230\350\241\250", nullptr));
        actiona->setText(QCoreApplication::translate("MainWindow", "\351\224\200\345\224\256\350\241\250", nullptr));
        export_2->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\207\272\346\225\260\346\215\256", nullptr));
        Import->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245\346\225\260\346\215\256", nullptr));
        gtos->setText(QCoreApplication::translate("MainWindow", "\351\243\237\345\223\201\345\220\215\346\237\245\344\276\233\345\272\224\345\225\206\345\220\215", nullptr));
        stog->setText(QCoreApplication::translate("MainWindow", "\344\276\233\345\272\224\345\225\206\345\220\215\346\237\245\351\243\237\345\223\201\345\220\215", nullptr));
        lineEdit->setText(QString());
        lineEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\346\237\245\350\257\242\345\206\205\345\256\271", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\347\256\241\347\220\206\345\221\230ID\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\346\237\245\350\257\242", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\225\206\345\223\201\345\233\276\347\211\207\351\242\204\350\247\210\345\214\272", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", " \345\225\206\345\223\201\346\230\276\347\244\272", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "\346\212\223\345\214\205\346\230\276\347\244\272", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\345\233\276\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
