#include "dialog1.h"
#include "ui_dialog1.h"

Dialog1::Dialog1(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog1)
{
    ui->setupUi(this);
}

Dialog1::~Dialog1()
{
    delete ui;
}

void Dialog1::on_buttonBox_accepted()
{
    data.push_back(ui->lineEdit->text());
    data.push_back(ui->lineEdit_2->text());
    data.push_back(ui->lineEdit_3->text());
    data.push_back(ui->lineEdit_4->text());
}
