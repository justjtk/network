#include "dialog4.h"
#include "ui_dialog4.h"

Dialog4::Dialog4(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog4)
{
    ui->setupUi(this);
    ui->dateEdit->setDateTime(QDateTime::currentDateTime());
}

Dialog4::~Dialog4()
{
    delete ui;
}

void Dialog4::on_buttonBox_accepted()
{
    data.push_back(ui->lineEdit->text());
    data.push_back(ui->lineEdit_2->text());
    data.push_back(ui->lineEdit_5->text());
    data.push_back(ui->lineEdit_3->text());
    data.push_back(ui->lineEdit_6->text());
    data.push_back(ui->lineEdit_4->text());
    data.push_back(ui->dateEdit->date().toString(Qt::ISODate));
    data.push_back(ui->lineEdit_7->text());
}
