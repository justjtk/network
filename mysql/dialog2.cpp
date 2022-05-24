#include "dialog2.h"
#include "ui_dialog2.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::on_buttonBox_accepted()
{
    data.push_back(ui->lineEdit->text());
    data.push_back(ui->lineEdit_2->text());
    data.push_back(ui->lineEdit_3->text());
    data.push_back(ui->lineEdit_4->text());
}
