#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTcpSocket>
#include<QBuffer>
char n[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
char d[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    int e=65537;
    ui->setupUi(this);
    /*连接AS，与AS发消息*/
    //****ctoas
    CtoAS ctoas;
    ctoas.IDc=11;
    ctoas.IDtgs=22;
    QTime time=QTime::currentTime();
    ctoas.TS1=time.toString("h:m:s.z");

    //****ctoas change to qbytearr
    QByteArray ctoasSend;//ctoasSend.append((char*)&ctoas, sizeof(CtoAS));
    QBuffer ctoasbuffer(&ctoasSend);
    ctoasbuffer.open(QIODevice::WriteOnly);
    QDataStream ctoasout(&ctoasbuffer);
    ctoasout<<ctoas.IDc<<ctoas.IDtgs<<ctoas.TS1;
    ctoasbuffer.close();

    Message recmes;

    QTcpSocket *tcpClient=new QTcpSocket;
        tcpClient->connectToHost("127.0.0.1",6666);
        if(tcpClient->waitForConnected(3000))
        {
            bool judge=package_message_noencrypt(0,1,ctoasSend,tcpClient);
            recmes=receive_message_nodecrypt(tcpClient);
            tcpClient->disconnectFromHost();
            tcpClient->waitForDisconnected();
        }
        else
        {
            tcpClient->disconnectFromHost();
            qDebug()<<"连接失败";
            tcpClient->waitForDisconnected();
        }

    //获取到了message,解析message中的内容
     //AStoC* astoc=(AStoC*)recmes.data.data();
     QBuffer as_ticketbuf(&recmes.data);
     as_ticketbuf.open(QIODevice::ReadOnly);
     QDataStream as_ticketin(&as_ticketbuf);
     char *asencrypt;char* ticket_encrypt;
     as_ticketin>>asencrypt>>ticket_encrypt;

     //****astoc 解密
     char* asdecrypt=decrypt(asencrypt,n,d);
     QByteArray asdecrypt_data(asdecrypt);
     asdecrypt_data.remove(0,1);
     asdecrypt_data=QByteArray::fromHex(asdecrypt_data);

     //****qbytearr change astoc
     QBuffer asbuf(&asdecrypt_data);
     asbuf.open(QIODevice::ReadOnly);
     QDataStream asin(&asbuf);
     AStoC astocnew;
     asin>>astocnew.Key_c_tgs>>astocnew.IDtgs>>astocnew.TS2>>astocnew.lifetime;

     /*
     //****ticket 解密
     char* ticket_decrypt=decrypt(ticket_encrypt,n,d);
     QByteArray ticket_decrypt_data(ticket_decrypt);
     ticket_decrypt_data.remove(0,1);
     ticket_decrypt_data=QByteArray::fromHex(ticket_decrypt_data);

     //****qbytearr change ticket
     QBuffer ticketbuf(&ticket_decrypt_data);
     ticketbuf.open(QIODevice::ReadOnly);
     QDataStream ticketin(&ticketbuf);
     Ticket ticketnew;
     ticketin>>ticketnew.Key_cn>>ticketnew.IDc>>ticketnew.ID>>ticketnew.TS>>ticketnew.lifetime;

     */
     int myid=123;
     /*连接TGS，与TGS发消息*/
     QByteArray ctotgsSend;
     QBuffer ctotgsbuffer(&ctotgsSend);
     ctotgsbuffer.open(QIODevice::WriteOnly);
     QDataStream ctotgsout(&ctotgsbuffer);
     ctotgsout<<myid<<ticket_encrypt<<ctoas.TS1;
     ctotgsbuffer.close();

     Message tgsrecmes;
     tcpClient=new QTcpSocket;
         tcpClient->connectToHost("127.0.0.1",6666);
         if(tcpClient->waitForConnected(3000))
         {
             bool judge=package_message_noencrypt(0,1,ctotgsSend,tcpClient);
             tgsrecmes=receive_message_nodecrypt(tcpClient);
             tcpClient->disconnectFromHost();
             tcpClient->waitForDisconnected();
         }
         else
         {
             tcpClient->disconnectFromHost();
             qDebug()<<"连接失败";
             tcpClient->waitForDisconnected();
         }


}

MainWindow::~MainWindow()
{

    delete ui;
}

