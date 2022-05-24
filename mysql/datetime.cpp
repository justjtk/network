#include "datetime.h"
#include "ui_datetime.h"

datetime::datetime(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::datetime)
{
    ui->setupUi(this);
}

datetime::~datetime()
{
    delete ui;
}
