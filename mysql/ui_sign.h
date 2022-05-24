/********************************************************************************
** Form generated from reading UI file 'sign.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGN_H
#define UI_SIGN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_sign
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;

    void setupUi(QDialog *sign)
    {
        if (sign->objectName().isEmpty())
            sign->setObjectName(QString::fromUtf8("sign"));
        sign->resize(400, 300);
        buttonBox = new QDialogButtonBox(sign);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        label = new QLabel(sign);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 90, 72, 15));
        lineEdit = new QLineEdit(sign);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(170, 80, 121, 31));
        label_2 = new QLabel(sign);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(100, 170, 72, 15));
        lineEdit_2 = new QLineEdit(sign);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(170, 160, 121, 31));
        lineEdit_2->setEchoMode(QLineEdit::Password);

        retranslateUi(sign);
        QObject::connect(buttonBox, SIGNAL(accepted()), sign, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), sign, SLOT(reject()));

        QMetaObject::connectSlotsByName(sign);
    } // setupUi

    void retranslateUi(QDialog *sign)
    {
        sign->setWindowTitle(QCoreApplication::translate("sign", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("sign", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("sign", "\345\257\206\347\240\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class sign: public Ui_sign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGN_H
