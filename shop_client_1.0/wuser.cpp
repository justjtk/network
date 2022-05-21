#include "wuser.h"
#include "ui_wuser.h"
#include"DES.h"
#include"imagehandle.h"
#include <QMessageBox>
#include<QBuffer>
#include<QTableView>
#include <QStandardItem>
#include <QStandardItemModel>
static char Vkey_n[]="a42ec64809f7e777bae17b10d33bf5df4bb605d6124cda58fbe0d7322342bd3af61810e2ff62b33b0bcf09c5dd155d2a6e2fabd4ee655f78ad2cf19b0ada671893a843fe307e6eb9df63be5853dc97a48aeaf19996b05e471fb14bd0ee2a9f3d0d521c158d627855397900c218b78a6561228cf3064054de70a2b772e53d4f";
extern int e;
WUser::WUser(Pubdata alldata,QMainWindow *p,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WUser)
{
    ui->setupUi(this);
    pmwd=p;
    g_alldata=alldata;
    //ui->statusbar->hide();//隐藏状态栏
    ui->label->setScaledContents(true);//铺满label
    QString txtinf=QString("select uname,uphe,upic from user where uid=%1").arg(g_alldata.IDc);
    QString txtorder=QString("select gname,anum,atime from sale where mid=%1").arg(g_alldata.IDc);
    QString txtvip=QString("select endtime from vip where uid=%1").arg(g_alldata.IDc);
    QByteArray infSend;
    QBuffer infbuffer(&infSend);
    infbuffer.open(QIODevice::WriteOnly);
    QDataStream infout(&infbuffer);
    infout<<txtinf<<txtorder<<txtvip;
    infbuffer.close();
    QVector<QString> pac_show_vec=package_message_DES(65,24,infSend,g_alldata.socket,g_alldata.Key_c_v,g_alldata.mykey_n,g_alldata.mykey_d);
    QString show_det="请求商品图片";
    pac_show_vec[7]=show_det;
    emit Send_to_wsk(pac_show_vec);
    //send_pack_show_des(pac_show_vec);
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
    QString uname,uphe,datestring;
    QByteArray upic;
    int order_size;
    QVector<QVector<QString>> orders;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>uname>>uphe>>upic>>vip;
    if(vip)recin>>datestring;
    recin>>order_size;
    if(order_size!=0)recin>>orders;

    g_alldata.uname=uname;
    g_alldata.upho=uphe;

    //****还原图片
    img=getImage(upic);

    //***显示vip
    if(vip){
        ui->label_6->setText(QString(QString("vip(")+datestring+QString("到期)")));//到时候设置奢华的字体！！！
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
    modifyinfs=new modifyinf(g_alldata,img,this);
    connect(modifyinfs,SIGNAL(Change_mwd_head(QImage)),pmwd,SLOT(Change_head(QImage)));
    connect(modifyinfs,SIGNAL(Send_to_wsk1(QVector<QString>)),pmwd,SLOT(Send_pack_show(QVector<QString>)));
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
    connect(modifypsws,SIGNAL(Send_to_wsk2(QVector<QString>)),pmwd,SLOT(Send_pack_show(QVector<QString>)));
    modifypsws->show();
}

void WUser::Transmit_img(QImage img)
{
    emit Transmit_img_to_mwd(img);
}

void WUser::on_pushButton_clicked()
{
    if(vip){
        QMessageBox::information(this,"提示","您已经是尊贵的VIP用户了");
        return;
    }
    vipregists=new VIPregist(g_alldata);
    vipregists->show();
    if(vipregists->exec()==QDialog::Accepted){

    }
}

void WUser::VIP_handel(Message recv_mes){
    //****des解密
    recv_mes.data=DES_de(g_alldata.Key_c_v,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(g_alldata.Key_c_v,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,Vkey_n,e);      //不要数字签名的话这一行去掉

    //****解析报文
    bool success;
    QString datestring;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>success>>datestring;
    if(success){
    vip=true;
    ui->label_6->setText(QString("vip(")+datestring+QString("到期)"));
    ui->label_6->setVisible(true);
    }
}
