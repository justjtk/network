#include "mainwindow.h"

#include <QApplication>
#include"gmp.h"
//#include"RSA.h"
#include"MD5.h"
#include<QDebug>
#include<iostream>
using namespace std;
struct Message
{
    unsigned int message_length;//报文长度
    char message_type;//报文类型
    char field_type;//字段类型
    unsigned char des_ip[4]={0,0,0,0};//目的IP
    unsigned char des_src[4]={0,0,0,0};//源IP
    unsigned int sign_length;//数字签名长度
    QByteArray *data;//数据内容
    QByteArray *sign;//数字签名
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    key_pair * p = get_key_pair();
//    qDebug()<<"n = "<<p->n<<endl;
//    qDebug()<<"d = "<<p->d<<endl;
//    qDebug()<<"e = "<<p->e<<endl;
//    string buf="你好";
//    string cipher_text = encrypt_str(buf, p->n, p->e);
//    qDebug()<<"密文为"<<cipher_text.c_str()<<endl;
//    string plain_text = decrypt_str(cipher_text, p->n, p->d);
//    qDebug()<<""<<plain_text.c_str()<<endl;
    key_pair * p = get_key_pair();
    qDebug()<<"n = "<<p->n<<endl;
    qDebug()<<"d = "<<p->d<<endl;
    qDebug()<<"e = "<<p->e<<endl;
    QString str="hello world";
    QByteArray *data=new QByteArray();
    data->append(str);
    QByteArray *sign=sign_create(data,p->n,p->e);
    //QByteArray *sign1=new QByteArray();
    //sign1->append(sign);
    bool judge=sign_judge(data,sign,p->n,p->d);
    qDebug()<<judge;
    return a.exec();

}
