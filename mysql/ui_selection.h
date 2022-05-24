/********************************************************************************
** Form generated from reading UI file 'selection.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECTION_H
#define UI_SELECTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_selection
{
public:
    QDialogButtonBox *buttonBox;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QDialog *selection)
    {
        if (selection->objectName().isEmpty())
            selection->setObjectName(QString::fromUtf8("selection"));
        selection->resize(351, 206);
        buttonBox = new QDialogButtonBox(selection);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-70, 150, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        comboBox = new QComboBox(selection);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(170, 80, 101, 31));
        label = new QLabel(selection);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 80, 121, 31));

        retranslateUi(selection);
        QObject::connect(buttonBox, SIGNAL(accepted()), selection, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), selection, SLOT(reject()));

        QMetaObject::connectSlotsByName(selection);
    } // setupUi

    void retranslateUi(QDialog *selection)
    {
        selection->setWindowTitle(QCoreApplication::translate("selection", "Dialog", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("selection", "goods", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("selection", "market", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("selection", "member", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("selection", "purchase", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("selection", "supplier", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("selection", "worker", nullptr));

        label->setText(QCoreApplication::translate("selection", "\350\257\267\351\200\211\346\213\251\350\246\201\345\257\274\345\205\245\347\232\204\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class selection: public Ui_selection {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECTION_H
