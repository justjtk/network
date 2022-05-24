#include "dialog3.h"
#include "ui_dialog3.h"

Dialog3::Dialog3(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog3)
{
    ui->setupUi(this);
}

Dialog3::~Dialog3()
{
    delete ui;
}

void Dialog3::on_buttonBox_accepted()
{
    data.push_back(ui->lineEdit->text());
    data.push_back(ui->lineEdit_2->text());
    data.push_back(ui->lineEdit_3->text());
    data.push_back(ui->lineEdit_4->text());
}
