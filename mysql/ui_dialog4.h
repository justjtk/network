/********************************************************************************
** Form generated from reading UI file 'dialog4.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG4_H
#define UI_DIALOG4_H

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

class Ui_Dialog4
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_5;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_6;
    QLineEdit *lineEdit_4;
    QDateEdit *dateEdit;
    QLineEdit *lineEdit_7;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_6;
    QLabel *label_3;
    QLabel *label_7;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_8;

    void setupUi(QDialog *Dialog4)
    {
        if (Dialog4->objectName().isEmpty())
            Dialog4->setObjectName(QString::fromUtf8("Dialog4"));
        Dialog4->resize(566, 449);
        buttonBox = new QDialogButtonBox(Dialog4);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 370, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(Dialog4);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(210, 30, 201, 291));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        lineEdit_5 = new QLineEdit(verticalLayoutWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        verticalLayout->addWidget(lineEdit_5);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout->addWidget(lineEdit_3);

        lineEdit_6 = new QLineEdit(verticalLayoutWidget);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        verticalLayout->addWidget(lineEdit_6);

        lineEdit_4 = new QLineEdit(verticalLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout->addWidget(lineEdit_4);

        dateEdit = new QDateEdit(verticalLayoutWidget);
        dateEdit->setObjectName(QString::fromUtf8("dateEdit"));
        dateEdit->setDate(QDate(2000, 1, 1));

        verticalLayout->addWidget(dateEdit);

        lineEdit_7 = new QLineEdit(verticalLayoutWidget);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        verticalLayout->addWidget(lineEdit_7);

        verticalLayoutWidget_2 = new QWidget(Dialog4);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(120, 30, 91, 291));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_2->addWidget(label_6);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_7 = new QLabel(verticalLayoutWidget_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_2->addWidget(label_7);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_2->addWidget(label_8);


        retranslateUi(Dialog4);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog4, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog4, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog4);
    } // setupUi

    void retranslateUi(QDialog *Dialog4)
    {
        Dialog4->setWindowTitle(QCoreApplication::translate("Dialog4", "Dialog", nullptr));
        dateEdit->setDisplayFormat(QCoreApplication::translate("Dialog4", "yyyy-M-d", nullptr));
        label->setText(QCoreApplication::translate("Dialog4", "    \345\272\217\345\210\227ID", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog4", "    \345\225\206\345\223\201ID", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog4", "    \345\225\206\345\223\201\345\220\215", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog4", "  \344\276\233\345\272\224\345\225\206ID", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog4", "  \344\276\233\350\264\247\345\225\206\345\220\215", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog4", "   \350\277\233\350\264\247\346\225\260\351\207\217", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog4", "   \350\277\233\350\264\247\346\227\266\351\227\264", nullptr));
        label_8->setText(QCoreApplication::translate("Dialog4", "  \350\277\233\350\264\247\345\215\225\344\273\267", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog4: public Ui_Dialog4 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG4_H
