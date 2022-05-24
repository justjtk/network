/********************************************************************************
** Form generated from reading UI file 'dialog0.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG0_H
#define UI_DIALOG0_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog0
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_5;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QPushButton *pushButton;
    QLabel *label_6;

    void setupUi(QDialog *Dialog0)
    {
        if (Dialog0->objectName().isEmpty())
            Dialog0->setObjectName(QString::fromUtf8("Dialog0"));
        Dialog0->resize(597, 377);
        buttonBox = new QDialogButtonBox(Dialog0);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(60, 320, 341, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(Dialog0);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(160, 30, 201, 251));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(verticalLayoutWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        lineEdit_2 = new QLineEdit(verticalLayoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        lineEdit_3 = new QLineEdit(verticalLayoutWidget);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        verticalLayout->addWidget(lineEdit_3);

        lineEdit_4 = new QLineEdit(verticalLayoutWidget);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        verticalLayout->addWidget(lineEdit_4);

        lineEdit_5 = new QLineEdit(verticalLayoutWidget);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        verticalLayout->addWidget(lineEdit_5);

        verticalLayoutWidget_2 = new QWidget(Dialog0);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(70, 30, 96, 251));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);

        pushButton = new QPushButton(Dialog0);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(390, 230, 191, 31));
        label_6 = new QLabel(Dialog0);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(430, 70, 100, 100));

        retranslateUi(Dialog0);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog0, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog0, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog0);
    } // setupUi

    void retranslateUi(QDialog *Dialog0)
    {
        Dialog0->setWindowTitle(QCoreApplication::translate("Dialog0", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Dialog0", "    \345\225\206\345\223\201\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog0", "  \345\225\206\345\223\201\346\225\260\351\207\217", nullptr));
        label_3->setText(QCoreApplication::translate("Dialog0", "  \345\225\206\345\223\201\344\273\267\346\240\274", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog0", "\345\225\206\345\223\201\346\211\223\346\212\230\344\273\267\346\240\274", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog0", "\345\225\206\345\223\201\347\261\273\345\236\213", nullptr));
        pushButton->setText(QCoreApplication::translate("Dialog0", "\344\270\212\344\274\240\345\233\276\347\211\207", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog0", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog0: public Ui_Dialog0 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG0_H
