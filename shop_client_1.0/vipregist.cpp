#include "vipregist.h"
#include "ui_vipregist.h"
#include"network.h"
#include <QMessageBox>
#include<QBuffer>
VIPregist::VIPregist(Pubdata alldata,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VIPregist)
{
    ui->setupUi(this);
    g_alldata=alldata;
    ui->radioButton->setChecked(true);
}

VIPregist::~VIPregist()
{
    delete ui;
}

void VIPregist::on_radioButton_clicked()
{
    ui->radioButton->setChecked(true);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(false);
}


void VIPregist::on_radioButton_2_clicked()
{
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(true);
    ui->radioButton_3->setChecked(false);
}


void VIPregist::on_buttonBox_accepted()
{
    int type;
    if(ui->radioButton->isChecked()) type=1;
    if(ui->radioButton_2->isChecked()) type=2;
    if(ui->radioButton_3->isChecked()) type=3;
    QByteArray infSend;
    QBuffer infbuffer(&infSend);
    infbuffer.open(QIODevice::WriteOnly);
    QDataStream infout(&infbuffer);
    infout<<g_alldata.IDc<<g_alldata.uname<<type;
    infbuffer.close();
    package_message_DES(65,12,infSend,g_alldata.socket,g_alldata.Key_c_v,g_alldata.mykey_n,g_alldata.mykey_d);

}


void VIPregist::on_radioButton_3_clicked()
{
    ui->radioButton->setChecked(false);
    ui->radioButton_2->setChecked(false);
    ui->radioButton_3->setChecked(true);
}

