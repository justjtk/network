/********************************************************************************
** Form generated from reading UI file 'datetime.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATETIME_H
#define UI_DATETIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_datetime
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    void setupUi(QDialog *datetime)
    {
        if (datetime->objectName().isEmpty())
            datetime->setObjectName(QString::fromUtf8("datetime"));
        datetime->resize(400, 300);
        buttonBox = new QDialogButtonBox(datetime);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        gridLayoutWidget = new QWidget(datetime);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(89, 19, 241, 171));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(datetime);
        QObject::connect(buttonBox, SIGNAL(accepted()), datetime, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), datetime, SLOT(reject()));

        QMetaObject::connectSlotsByName(datetime);
    } // setupUi

    void retranslateUi(QDialog *datetime)
    {
        datetime->setWindowTitle(QCoreApplication::translate("datetime", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class datetime: public Ui_datetime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATETIME_H
