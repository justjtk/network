#include "wmodify.h"
#include "ui_wmodify.h"
#include"network.h"
#include<QBuffer>
WModify::WModify(Pubdata alldata,QImage img,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WModify)
{
    ui->setupUi(this);
    g_alldata=alldata;
    ui->label->setPixmap(QPixmap::fromImage(img));
    ui->lineEdit->setText(g_alldata.uname);
    ui->lineEdit_2->setText(g_alldata.upho);
}

WModify::~WModify()
{
    delete ui;
}

void WModify::on_pushButton_clicked()
{
    QString txt=QString("update user set uname=%1,uphe=%2 where userid=%3").arg(ui->lineEdit->text()).arg(ui->lineEdit_2->text()).arg(g_alldata.IDc);
    QByteArray infSend;
    QBuffer infbuffer(&infSend);
    infbuffer.open(QIODevice::WriteOnly);
    QDataStream infout(&infbuffer);
    infout<<txt;
    infbuffer.close();
    bool judge=package_message_DES(65,24,infSend,g_alldata.socket,g_alldata.Key_c_v,g_alldata.mykey_n,g_alldata.mykey_d);

}

