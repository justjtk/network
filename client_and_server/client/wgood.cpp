#include "wgood.h"
#include "ui_wgood.h"
#include <QDebug>
#include "mainwindow.h"

WGood::WGood(QString uid,QMainWindow *p,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WGood)
{
    ui->setupUi(this);
    id=uid;
    pmwd=p;
    ui->statusbar->hide();//隐藏状态栏
    delete ui->statusbar;//删除状态栏
    connect(pmwd,SIGNAL(Transport_goods(QVector<QVector<QString>>,QVector<QByteArray>)),
            this,SLOT(Show_goods_1(QVector<QVector<QString>>,QVector<QByteArray>)));
}

WGood::~WGood()
{
    delete ui;
}

//刷新
void WGood::on_pushButton_clicked()
{
    emit Refresh_goods_list(6);
}

//搜索
void WGood::on_pushButton_2_clicked()
{

}

//立即购买
void WGood::on_pushButton_21_clicked()
{
    wpay=new WPay(id);
    wpay->show();
}

//左翻页
void WGood::on_pushButton_24_clicked()
{

}


void WGood::Show_goods_1(QVector<QVector<QString>> goods_infm,QVector<QByteArray> goods_img)
{
    for(int i=0;i<6;i++)//每个商品
    {
        for(int j=0;j<4;j++)//每种属性
        {
            QString value=goods_infm[i][j];
            if(j==1) value="库存 "+value+" 件";
            else if(j==3) value="¥"+value;
            QLabel *label = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_"+QString::number(j));
            label->setText(value);
        }
        QImage img=getImage(goods_img[i]);
        QLabel *label = this->findChild<QLabel *>("label"+QString::number(i+1));
        label->setPixmap(QPixmap::fromImage(img));
        label->setScaledContents(true);//铺满label
    }
}

