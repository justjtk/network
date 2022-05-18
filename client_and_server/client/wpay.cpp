#include "wpay.h"
#include "ui_wpay.h"

WPay::WPay(QString uid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WPay)
{
    ui->setupUi(this);
    id=uid;
}

WPay::~WPay()
{
    delete ui;
}
