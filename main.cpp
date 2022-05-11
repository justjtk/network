#include "mainwindow.h"

#include <QApplication>
#include"gmp.h"
//#include"gmpxx.h"
//#include"RSA.h"
//#include"MD5.h"
#include<QDebug>
#include<iostream>
#include"network.h"
#include<QBuffer>
using namespace std;

struct test{
    int a;
    QByteArray data;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //key_pair * p = get_key_pair();
    key_pair * p=new key_pair();
    char temp[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
    p->n=temp;
    char temp1[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
    p->d=temp1;
    p->e=65537;
    qDebug()<<"n = "<<p->n<<endl;
    qDebug()<<"d = "<<p->d<<endl;
    qDebug()<<"e = "<<p->e<<endl;


    QString str1="nice";
    test str;
    str.a=4;
    str.data="123456";
    QByteArray data;
    data.append(str.data);
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<str.a<<str.data;
    buffer.close();
    QBuffer buf(&data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);

    test str3;
    in>>str3.a>>str3.data;
    qDebug()<<str3.a<<str3.data;

    qDebug()<<sizeof(str)<<data.length();

    QByteArray sign;
    sign.append(str1);
    int i=1;
    int y=2;
    QTcpSocket *tcpClient=new QTcpSocket;

    tcpClient->connectToHost("127.0.0.1",6666);
    if(tcpClient->waitForConnected(3000))
    {
        //bool judge=package_message(i,y,data,tcpClient,p->n,p->e,p->n,p->d);//有数字签名
        //bool judge=package_message_noencrypt(i,y,data,tcpClient);//无加密无数字签名
        bool judge=package_message(i,y,data,tcpClient,p->n,p->e);//无数字签名有加密
        tcpClient->disconnectFromHost();
        tcpClient->waitForDisconnected();
    }
    else
    {
        tcpClient->disconnectFromHost();
        qDebug()<<"连接失败";
        tcpClient->waitForDisconnected();
    }


    return a.exec();

}
