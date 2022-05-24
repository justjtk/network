#include "sign.h"
#include "ui_sign.h"

sign::sign(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::sign)
{
    ui->setupUi(this);
}

sign::~sign()
{
    delete ui;
}

void sign::on_buttonBox_accepted()
{
    name=ui->lineEdit->text();
    id=ui->lineEdit_2->text();
}

void sign::on_buttonBox_rejected()
{
    name="false";
    id="false";
}
