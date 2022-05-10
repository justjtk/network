#include "mainwindow.h"

#include <QApplication>
#include"gmp.h"
//#include"MD5.h"
#include<QDebug>
#include<iostream>
#include<QTcpServer>
#include"network.h"
#include<QBuffer>
using namespace std;
struct test{
    int a;
    QString data;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QTcpServer *TCPServer=new QTcpServer;
    TCPServer->listen(QHostAddress::Any, 6666);
    TCPServer->waitForNewConnection(-1);
    QTcpSocket *socket=TCPServer->nextPendingConnection();
    qDebug()<<"连接成功";
    key_pair * p=new key_pair();
    char temp[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
    p->n=temp;
    char temp1[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
    p->d=temp1;
    p->e=65537;
    qDebug()<<"n = "<<p->n<<endl;
    qDebug()<<"d = "<<p->d<<endl;
    qDebug()<<"e = "<<p->e<<endl;
    Message tempx=receive_message(socket,p->n,p->d,p->n,p->e);

//    //test* str=(test*)temp.data.data();

    QBuffer buf(&tempx.data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);

    test str3;
    in>>str3.a>>str3.data;

    //mes_len msg;

//    unsigned int d=4;
//    msg.message_length=d;
//    QByteArray data1;

//    data1.append((char*)&msg, sizeof(msg));
//    mes_len *msg1=(mes_len*)data1.data();

   // qDebug()<<data1.length()<<msg1->message_length;

//    QString str="hello world";
//    QString str1="nice";
//    QByteArray data;
//    data.append(str);
//    QByteArray sign;
//    sign.append(str1);
//    Message mes;
//    mes.sign=sign;
//    mes.data=data;
//    QByteArray data1;
//    data1.append((char*)&mes, sizeof(mes));
//    Message *res=(Message*)data1.data();



//    key_pair * p = get_key_pair();
//    qDebug()<<"n = "<<p->n<<endl;
//    qDebug()<<"d = "<<p->d<<endl;
//    qDebug()<<"e = "<<p->e<<endl;
//    test str2;
//    str2.a=4;
//    str2.data="2.5";
//    QByteArray data;
//    QBuffer buffer(&data);
//    buffer.open(QIODevice::WriteOnly);
//    QDataStream out(&buffer);
//    out<<str2.a<<str2.data;
//    buffer.close();


//    //bool judge=sign_judge(data,sign,p->n,p->e);
//    QByteArray data1;

//    data1=data.toHex();
//    data1.insert(0,QByteArray("1"));

//    QByteArray sign=sign_create(data1,p->n,p->d);

//    QByteArray sign1;
//    sign1.append(sign);

//    int q=data1.length();
//    int f=sign1.length();



//    QByteArray data2(encrypt(data1.constData(),p->n,p->e));//加密完
//    QByteArray data3(decrypt(data2.constData(),p->n,p->d));

//    QByteArray sign2(encrypt(sign1.constData(),p->n,p->e));//加密完
//    QByteArray sign3(decrypt(sign2.constData(),p->n,p->d));//加密完

//    bool judge=sign_judge(data3,sign3,p->n,p->e);

//    data3.remove(0,1);
//    qDebug()<<judge;

    return a.exec();
}
