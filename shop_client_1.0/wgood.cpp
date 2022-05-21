#include "wgood.h"
#include "ui_wgood.h"
#include <QDebug>
#include "mainwindow.h"

WGood::WGood(QString uid,QMainWindow *p,QVector<QVector<QString>> buffer,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WGood)
{
    ui->setupUi(this);
    id=uid;
    pmwd=p;
    if(buffer[0][0]!="***")
        add_buffer=buffer;
//    ui->statusbar->hide();//隐藏状态栏
//    delete ui->statusbar;//删除状态栏
    connect(pmwd,SIGNAL(Transport_goods(int,int,QVector<QVector<QString>>,QVector<QByteArray>)),
            this,SLOT(Show_goods_1(int,int,QVector<QVector<QString>>,QVector<QByteArray>)));//接收并显示商品
    connect(pmwd,SIGNAL(Control_page_turn(int,int)),this,SLOT(Control_page_turn_btn(int,int)));//翻页控制
    connect(this,SIGNAL(Control_page_turn(int,int)),this,SLOT(Control_page_turn_btn(int,int)));//翻页控制
    //connect(wpay,SIGNAL(Goods_order(QByteArray)),pmwd,SLOT(Goods_order_pay(QByteArray)));//商品页直接购买

    QPushButton *btn1[6]={ui->pushButton_12,ui->pushButton_22,ui->pushButton_32,ui->pushButton_42,ui->pushButton_52,ui->pushButton_62};
    QPushButton *btn2[6]={ui->pushButton_11,ui->pushButton_21,ui->pushButton_31,ui->pushButton_41,ui->pushButton_51,ui->pushButton_61};
    for(int i=0;i<6;i++)
    {
        add_btn[i]=btn1[i];
        sub_btn[i]=btn2[i];
        connect(add_btn[i],SIGNAL(clicked(bool)),SLOT(add_num()));
        connect(sub_btn[i],SIGNAL(clicked(bool)),SLOT(sub_num()));
    }
}

WGood::~WGood()
{
    delete ui;
}

//刷新
void WGood::on_pushButton_clicked()
{
    emit Change_view_mode(1);
    emit Refresh_goods_list(6);
}

void WGood::on_pushButton_21_clicked()//补丁
{
    //wpay=new WPay(id);
    //wpay->show();
//    int n=ui->label_2_4->text().toInt();
//    if(n>0)n--;
//    ui->label_2_4->setText(QString::number(n));

//    for (int j=0; j<add_buffer.count(); j++)
//    {
//         if(add_buffer[j][0]==ui->label_2_0->text())
//         {
//             add_buffer[j][1]=QString::number(n);
//             break;
//         }
//    }
}

//左翻页
void WGood::on_pushButton_24_clicked()
{
    emit Refresh_goods_list(12);
    ui->pushButton_23->setEnabled(true);
}

//右翻页
void WGood::on_pushButton_23_clicked()
{
    emit Refresh_goods_list(0);
    ui->pushButton_24->setEnabled(true);
}

//显示商品
void WGood::Show_goods_1(int loc,int goods_num,QVector<QVector<QString>> goods_infm,QVector<QByteArray> goods_img)//显示商品
{
    //记录当页信息
    show_infm=goods_infm;
    //页码显示和按钮
    emit Control_page_turn(loc,goods_num);
    //搜索框、输入页码清空
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    //前n个商品进行显示
    for(int i=0;i<6;i++)
    {
        QLabel *label = this->findChild<QLabel *>("label_"+QString::number(i+1));
        label->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    }
    for(int i=0;i<goods_num;i++)//每个商品
    {
        QLabel *label_name = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_0");
        for(int j=0;j<5;j++)//每种属性
        {
            //显示信息的控件
            QLabel *label = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_"+QString::number(j));
            //显示信息
            QString value;
            if(j<4) value=goods_infm[i][j];
//            if(j==1) value="库存 "+value+" 件";
//            else if(j==2) value=" "+value+" ";
//            else if(j==3) value="¥ "+value;
            ////////////////////////
            else if(j==4)
            {
                //value="0";
                for (int p=0; p<add_buffer.count(); p++)
                {
                     if(add_buffer[p][0]==label_name->text())
                     {
                         value=add_buffer[p][1];
                         break;
                     }
                     else
                         value="0";
                }
            }
            ////////////////////////
            for(int k=0;k<2;k++)
            {
                QPushButton *btn=this->findChild<QPushButton *>("pushButton_"+QString::number(i+1)+QString::number(k+1));
                btn->raise();
            }
            if(value=="")value="0";
            label->setText(value);
            label->raise();
        }
        //显示图片
        QImage img=getImage(goods_img[i]);
        QLabel *label_img = this->findChild<QLabel *>("label"+QString::number(i+1));
        label_img->setPixmap(QPixmap::fromImage(img));
        label_img->setScaledContents(true);//铺满label
        label_img->raise();
    }
    //后6-n个商品显示空白
    for(int i=0;i<6-goods_num;i++)
    {
        QLabel *label = this->findChild<QLabel *>("label_"+QString::number(goods_num+i+1));
        label->raise();
    }
}

//显示页码，控制始末翻页按钮使能
void WGood::Control_page_turn_btn(int goods_loc,int goods_num)
{
    //qDebug()<<goods_loc;
    int page=goods_loc/6;
    if(goods_loc%6) page++;
    ui->label_page->setText(QString::number(page));

    if(goods_loc<=6)//控制左翻
        ui->pushButton_24->setEnabled(false);
    else
        ui->pushButton_24->setEnabled(true);

    if(goods_num<6)//控制右翻
        ui->pushButton_23->setEnabled(false);
    else
        ui->pushButton_23->setEnabled(true);

}

//跳转到指定页
void WGood::on_pushButton_25_clicked()
{
    QString page=ui->lineEdit_2->text();
    int n=page.toInt();//获取目标页码
    if(!(n>0))
    {
        QMessageBox::information(this,"notice"," 输入页码需要为正整数");
        ui->lineEdit_2->clear();
        return;
    }
    emit Get_goods_number(n);
}

//搜索商品
void WGood::on_pushButton_2_clicked()
{
    emit Change_view_mode(2);
    QString gname=ui->lineEdit->text();
    if(gname=="") return;
    emit Search_goods_list(gname);
}

//种类1：水果生鲜
void WGood::on_pushButton_3_clicked()
{
    emit Change_view_mode(3);
    emit Search_species_list(1);
}

//种类2：零食饮料
void WGood::on_pushButton_4_clicked()
{
    emit Change_view_mode(4);
    emit Search_species_list(2);
}

//种类3：日产用品
void WGood::on_pushButton_5_clicked()
{
    emit Change_view_mode(5);
    emit Search_species_list(3);
}

//种类4：美妆服饰
void WGood::on_pushButton_6_clicked()
{
    emit Change_view_mode(6);
    emit Search_species_list(4);
}

//种类5：手机数码
void WGood::on_pushButton_8_clicked()
{
    emit Change_view_mode(7);
    emit Search_species_list(5);
}

//种类6：家用电器
void WGood::on_pushButton_7_clicked()
{
    emit Change_view_mode(8);
    emit Search_species_list(6);
}

//增加数量
void WGood::add_num()
{
    int i=0;
    QPushButton *pbtn=qobject_cast<QPushButton *>(sender());
    for(i=0;i<6;i++)
    {
        if(add_btn[i]==pbtn)
            break;
    }
    QLabel *label_name = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_0");
    QLabel *label_price = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_2");
    QLabel *label_discount = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_3");
    QLabel *label_num = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_4");

    int n=label_num->text().toInt();
    n++;
    label_num->setText(QString::number(n));

    int find=0;
    for (int j=0; j<add_buffer.count(); j++)
    {
         if(add_buffer[j][0]==label_name->text())
         {
             find=1;
             add_buffer[j][1]=QString::number(n);
             break;
         }
    }
    if(find==0&&n>0)
    {
        QVector<QString> temp;
        temp<<label_name->text()<<label_num->text()<<label_price->text()<<label_discount->text();
        add_buffer.push_back(temp);
    }
    int a=0;
}

//减少数量
void WGood::sub_num()
{
    int i=0;
    QPushButton *pbtn=qobject_cast<QPushButton *>(sender());
    for(i=0;i<6;i++)
    {
        if(sub_btn[i]==pbtn)
            break;
    }
    QLabel *label_name = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_0");
    QLabel *label_price = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_2");
    QLabel *label_discount = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_3");
    QLabel *label_num = this->findChild<QLabel *>("label_"+QString::number(i+1)+"_4");
    int n=label_num->text().toInt();
    if(n>0)n--;
    label_num->setText(QString::number(n));

//    if(n==0)//当前已选商品数减少到0，从缓冲区add_buffer移除
//    {
//        int pos=0;
//        for(int k=0;k<add_buffer.count();k++)
//        {
//            if()
//        }
//    }

    for (int j=0; j<add_buffer.count(); j++)
    {
         if(add_buffer[j][0]==label_name->text())
         {
             //add_buffer[j][1]=QString::number(n);
             if(n==0)//当前已选商品数减少到0，从缓冲区add_buffer移除
                add_buffer.remove(j);
             else//当前商品数不为0，更改缓冲区add_buffer的对应商品数量
                add_buffer[j][1]=QString::number(n);
             break;
         }
    }
}

//加入购物车
void WGood::on_pushButton_add_to_trolley_clicked()
{
    if(!add_buffer.isEmpty())
    {
        emit addcart(id.toInt(),add_buffer);
        //add_buffer.clear();
    }
}

//立即购买
void WGood::on_pushButton_purchase_clicked()
{
    wpay=new WPay(id,add_buffer,0,this);
    connect(wpay,SIGNAL(Goods_order(QByteArray)),pmwd,SLOT(Goods_order_pay(QByteArray)));//商品页直接购买
    wpay->show();
}




