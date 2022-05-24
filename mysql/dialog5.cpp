#include "dialog5.h"
#include "ui_dialog5.h"

Dialog5::Dialog5(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog5)
{
    ui->setupUi(this);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
}

Dialog5::~Dialog5()
{
    delete ui;
}

void Dialog5::on_buttonBox_accepted()
{
    data.push_back(ui->lineEdit->text());
    data.push_back(ui->lineEdit_2->text());
    data.push_back(ui->lineEdit_7->text());
    data.push_back(ui->lineEdit_3->text());
    data.push_back(ui->lineEdit_8->text());
    data.push_back(ui->lineEdit_4->text());
    data.push_back(ui->lineEdit_5->text());
    data.push_back(ui->dateEdit->date().toString(Qt::ISODate));
    data.push_back(ui->lineEdit_6->text());
}
