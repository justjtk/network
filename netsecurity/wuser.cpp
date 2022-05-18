#include "wuser.h"
#include "ui_wuser.h"
#include"DES.h"
#include"imagehandle.h"

#include<QBuffer>
#include<QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
static char Vkey_n[]="a42ec64809f7e777bae17b10d33bf5df4bb605d6124cda58fbe0d7322342bd3af61810e2ff62b33b0bcf09c5dd155d2a6e2fabd4ee655f78ad2cf19b0ada671893a843fe307e6eb9df63be5853dc97a48aeaf19996b05e471fb14bd0ee2a9f3d0d521c158d627855397900c218b78a6561228cf3064054de70a2b772e53d4f";
extern int e;
WUser::WUser(Pubdata alldata,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WUser)
{
    ui->setupUi(this);
    g_alldata=alldata;
    //ui->statusbar->hide();//隐藏状态栏

    QString txtinf=QString("select uname,uphe,upic from user where uid=%1").arg(g_alldata.IDc);
    QString txtorder=QString("select gname,anum,atime from sale where mid=%1").arg(g_alldata.IDc);
    QString txtvip=QString("select mname,anum,atime from vip where mid=%1").arg(g_alldata.IDc);
    QByteArray infSend;
    QBuffer infbuffer(&infSend);
    infbuffer.open(QIODevice::WriteOnly);
    QDataStream infout(&infbuffer);
    infout<<txtinf<<txtorder<<txtvip;
    infbuffer.close();
    bool judge=package_message_DES(65,24,infSend,g_alldata.socket,g_alldata.Key_c_v,g_alldata.mykey_n,g_alldata.mykey_d);
    ui->label_8->setText(QString("%1").arg(g_alldata.IDc));
}

WUser::~WUser()
{
    delete ui;
}

void WUser::deal_initi(Message recv_mes){
    //****des解密
    recv_mes.data=DES_de(g_alldata.Key_c_v,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(g_alldata.Key_c_v,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,Vkey_n,e);      //不要数字签名的话这一行去掉

    //****解析报文
    QString uname,uphe;
    QByteArray upic;
    int order_size;
    bool vip;
    QVector<QVector<QString>> orders;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>uname>>uphe>>upic>>vip>>order_size;
    if(order_size!=0)recin>>orders;

    g_alldata.uname=uname;
    g_alldata.upho=uphe;

    //****还原图片
    img=getImage(upic);

    //***显示vip
    if(vip){
        ui->label_6->setText(QString("vip"));//到时候设置奢华的字体！！！
    }
    else{
        ui->label_6->setVisible(false);
    }

    //***显示ui
     ui->label_2->setText(uname);
     ui->label_9->setText(uphe);
     ui->label->setPixmap(QPixmap::fromImage(img));
     //****显示订单
     if(order_size!=0){
         // ui->label_7->setStyleSheet("background:transparent");
           ui->label_7->setVisible(false);
         QStandardItem *item;
         QStandardItemModel *ordertable=new QStandardItemModel();
         for(int i=0;i<orders.size();++i){
             for(int j=0;j<orders[i].size();++j){
                 item=new QStandardItem(orders[i][j]);
                 ordertable->setItem(i,j,item);
             }
         }
         ui->tableView->setModel(ordertable);
     }

}
void WUser::on_pushButton_2_clicked()
{
    modifyinfs=new modifyinf(g_alldata,img);
    //modifyinfs->setModal(false);
    modifyinfs->show();
    if(modifyinfs->exec()==QDialog::Rejected&&modifyinfs->ifmodsuccess==true){
        g_alldata.uname=modifyinfs->g_alldata.uname;
        g_alldata.upho=modifyinfs->g_alldata.upho;
        img=modifyinfs->currentimg;
        ui->label_2->setText(g_alldata.uname);
        ui->label_9->setText(g_alldata.upho);
        ui->label->setPixmap(QPixmap::fromImage(modifyinfs->currentimg.scaled(ui->label->size())));
    }

}

void WUser::on_pushButton_3_clicked()
{
    modifypsws=new modifypsw(g_alldata);
    modifypsws->show();
}

