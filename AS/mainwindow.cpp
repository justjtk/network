#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QTcpServer>
#include<QBuffer>
char n[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
char d[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
    int e=65537;
    //TCP连接
    QTcpServer *TCPServer=new QTcpServer;
    TCPServer->listen(QHostAddress::Any, 6666);
    TCPServer->waitForNewConnection(-1);
    QTcpSocket *socket=TCPServer->nextPendingConnection();
    Message recmes=receive_message_nodecrypt(socket);

    //****解析报文中的数据
    QBuffer recmesbuf(&recmes.data);
    recmesbuf.open(QIODevice::ReadOnly);
    QDataStream recmein(&recmesbuf);
    int ctoas_idc,ctoas_idtgs;
    QString ctoas_ts1;
    recmein>>ctoas_idc>>ctoas_idtgs>>ctoas_ts1;

    //****ticket
    Ticket tastoc;
    tastoc.ID=ctoas_idtgs;
    tastoc.IDc=ctoas_idc;
    tastoc.Key_cn=0;//之后要改
    QTime ts2time=QTime::currentTime();
    tastoc.TS=ts2time.toString("h:m:s.z");
    tastoc.lifetime=24;//oneday
    //****ticket change to qbytearr
    QByteArray tdata;
    QBuffer tbuffer(&tdata);
    tbuffer.open(QIODevice::WriteOnly);
    QDataStream tout(&tbuffer);
    tout<<tastoc.Key_cn<<tastoc.IDc<<tastoc.ID<<tastoc.TS<<tastoc.lifetime;
    tbuffer.close();
    tdata=tdata.toHex();
    tdata.insert(0,QByteArray("1"));
    //****one encryp
    char* one_encrypt=encrypt(tdata.data(),n,e);

    /*
    //****two encrypt
    QByteArray twodata(one_encrypt);
    twodata=twodata.toHex();
    twodata.insert(0,QByteArray("1"));
    char* two_encrypt=encrypt(twodata.left(10).data(),n,e);

    //****one ticket dencrypt
    char * result=decrypt(two_encrypt,n,d);
    QByteArray qresult(result);
    qresult.remove(0,1);
    qresult=QByteArray::fromHex(qresult);
    char *miao=qresult.data();

    //****two ticket dencrypt
    char * tworesult=decrypt(qresult.data(),n,d);
    QByteArray twoqresult(tworesult);
    twoqresult.remove(0,1);
    twoqresult=QByteArray::fromHex(twoqresult);

    QBuffer buf(&twoqresult);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
    Ticket tastocnew;
    in>>tastocnew.Key_cn>>tastocnew.IDc>>tastocnew.ID>>tastocnew.TS>>tastocnew.lifetime;*/

    //*****astoc
    AStoC astoc;
    astoc.IDtgs=ctoas_idtgs;
    astoc.TS2=ts2time.toString("h:m:s.z");
    astoc.lifetime=24;//oneday
    //astoc.m_ticket_tgs=encrypt(tdata.data(),n,e);
    astoc.Key_c_tgs=tastoc.Key_cn;

    //****astoc change qbytearr
    QByteArray asdata;
    QBuffer buffer(&asdata);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<astoc.Key_c_tgs<<astoc.IDtgs<<astoc.TS2<<astoc.lifetime;
    buffer.close();

    //****astoc 加密
    asdata=asdata.toHex();
    asdata.insert(0,QByteArray("1"));
    char* asencrypt=encrypt(asdata.data(),n,e);

    //****astoc and ticket send
    QByteArray as_ticket;
    QBuffer allbuffer(&as_ticket);
    allbuffer.open(QIODevice::WriteOnly);
    QDataStream allout(&allbuffer);
    allout<<asencrypt<<one_encrypt;
    allbuffer.close();
    package_message_noencrypt(1,4,as_ticket,socket);

    /*
    //****astoc and ticket recieve
    QBuffer as_ticketbuf(&as_ticket);
    as_ticketbuf.open(QIODevice::ReadOnly);
    QDataStream as_ticketin(&as_ticketbuf);
    char *jtk;char* dm;
    as_ticketin>>jtk>>dm;

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
    asin>>astocnew.Key_c_tgs>>astocnew.IDtgs>>astocnew.TS2>>astocnew.lifetime;*/

    /*
    QTcpServer *TCPServer=new QTcpServer;
    TCPServer->listen(QHostAddress::Any, 6666);
    TCPServer->waitForNewConnection(-1);
    QTcpSocket *socket=TCPServer->nextPendingConnection();
    Message recmes=receive_message_nodecrypt(socket);
    CtoAS* ctoas=(CtoAS*)recmes.data.data();
    //
    Ticket tastoc;
    tastoc.ID=ctoas->IDtgs;
    tastoc.IDc=ctoas->IDc;
    tastoc.Key_cn=0;//之后要改
    tastoc.TS=QTime::currentTime().hour();
    tastoc.lifetime=24;//oneday
    AStoC astoc;
    astoc.IDtgs=ctoas->IDtgs;
    QByteArray t;
    t.append((char*)&tastoc, sizeof(Ticket));
    t=t.toHex();
    t.insert(0,QByteArray("1"));
    astoc.m_ticket_tgs=encrypt(t.data(),n,e);
    astoc.Key_c_tgs=tastoc.Key_cn;
    //
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<astoc.Key_c_tgs<<astoc.IDtgs<<astoc.TS2<<astoc.lifetime<<astoc.m_ticket_tgs;
    buffer.close();
    package_message(1,4,data,socket,n,e);*/
    int adb=123;
}

MainWindow::~MainWindow()
{

    delete ui;
}

