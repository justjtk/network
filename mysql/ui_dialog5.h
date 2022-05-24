/********************************************************************************
** Form generated from reading UI file 'dialog5.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG5_H
#define UI_DIALOG5_H

#include <QtCore/QDate>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog5
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit_6;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_8;
    QLabel *label_3;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label_7;

    void setupUi(QDialog *Dialog5)
    {
        if (Dialog5->objectName().isEmpty())
            Dialog5->setObjectName(QString::fromUtf8("Dialog5"));
        Dialog5->resize(573, 564);
        buttonBox = new QDialogButtonBox(Dialog5);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 500, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(Dialog5);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(200, 30, 211, 421));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        lineEdit_7 = new QLineEdit(verticalLayoutWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        verticalLayout->addWidget(lineEdit_7);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout->addWidget(lineEdit_3);

        lineEdit_8 = new QLineEdit(verticalLayoutWidget);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        verticalLayout->addWidget(lineEdit_8);

        lineEdit_4 = new QLineEdit(verticalLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(verticalLayoutWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        verticalLayout->addWidget(lineEdit_5);

        dateEdit = new QDateEdit(verticalLayoutWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setDate(QDate(2000, 1, 1));

        verticalLayout->addWidget(dateEdit);

        lineEdit_6 = new QLineEdit(verticalLayoutWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        verticalLayout->addWidget(lineEdit_6);

        verticalLayoutWidget_2 = new QWidget(Dialog5);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(110, 30, 91, 421));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_2->addWidget(label_8);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_9 = new QLabel(verticalLayoutWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_2->addWidget(label_9);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_2->addWidget(label_7);


        retranslateUi(Dialog5);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog5, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog5, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog5);
    } // setupUi

    void retranslateUi(QDialog *Dialog5)
    {
        Dialog5->setWindowTitle(QCoreApplication::translate("Dialog5", "Dialog", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("Dialog5", "yyyy-M-d", nullptr));
        label->setText(QCoreApplication::translate("Dialog5", "    \345\272\217\345\210\227ID", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog5", "    \345\225\206\345\223\201ID", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog5", "    \345\225\206\345\223\201\345\220\215", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog5", "  \344\276\233\345\272\224\345\225\206ID", nullptr));
        label_9->setText(QCoreApplication::translate("Dialog5", "  \344\276\233\345\272\224\345\225\206\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog5", "   \345\221\230\345\267\245ID", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog5", "  \351\224\200\345\224\256\346\225\260\351\207\217", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog5", "   \351\224\200\345\224\256\346\227\266\351\227\264", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog5", "    \344\274\232\345\221\230ID", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog5: public Ui_Dialog5 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG5_H
