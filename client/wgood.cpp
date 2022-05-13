#include "wgood.h"
#include "ui_wgood.h"
#include <QDebug>

WGood::WGood(QString uid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WGood)
{
    ui->setupUi(this);
    id=uid;
    ui->statusbar->hide();//隐藏状态栏
    delete ui->statusbar;//删除状态栏
}

WGood::~WGood()
{
    delete ui;
}

//刷新
void WGood::on_pushButton_clicked()
{

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
