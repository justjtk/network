#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"DES.h"
#include <QTcpSocket>
#include<QBuffer>
extern QSqlDatabase db;
char Ckey1_n[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
char Ckey1_d[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
char Ckey2_n[]="5bd604ccbf3c196d459ca001f88fbdac217c974e2db797427666691c6922d8fc6e620857ef75729406c372891fe4834a2796c28e097ff34fdfd786017682b3cf03429d933242c18f508d37fbeeafd939c8cae11265b865e0087b368d966262b7767dc8652bc7b5247cfa7df9f05a1b820db94e95a6253869f60542d85ffc686b";
char Ckey2_d[]="48a6a92968e81c9d6b829abab46ed278480d8e8d547177022734a156ce7db8f70a4417a1a9585a8a6c475666d08a30ab0b62a30b46cca829ba458047cbff5e4b167a9787b50f67fd382340a4e8803bebdb52bca252616eabb36893744cf6aad9df412f50838e3f8862bfec4c584adf2d5c933aa90f878a38b395477e4ba0fb01";
char Ckey3_n[]="28bce507db6c54db4fc1c68715540de0eff698794003ffdf015852b0d670fba564471117c9b1b233a4ac874a7b9045ec922e6bc18216453eac7f87e68577120850d5ca55d36435a35fee50604ea0c690e9500d908f246a32781ab6c21b3a11a3fb610fa5901650de1854e90033bd80e7bb5f164929831c0cbd841ed2b2217d4f";
char Ckey3_d[]="1333341ec7e3fefa7e54ade4ecc078ea132efe1de775fb1a77dfd0d957b858625328cb7d92aa157b1199df09d3c2e3b1e413cce59f123000a1fc5968e46e8228bbad69852eb3cbe7c044461f6653111565eaedc33e00bf637defb2fcacf79706470bf622be0aedcf9f0abd4194bfa37b5337755478f6fd220e392f277e29d5c1";
int e=65537;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //p->n=n;
    //p->d=d;
    //p->e=65537;

    ui->setupUi(this);
    /*连接数据库*/
    QProcess process;
    process.start("C:/Program Files/MySQL/MySQL Server 5.7/bin/mysqld.exe");
    db= QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("netshop");       //这里输入你的数据库名
    db.setUserName("root");
    db.setPassword("dm089084...");   //这里输入你的密码
    if (!db.open()) {
    QMessageBox::critical(0, QObject::tr("无法打开数据库"),"无法创建数据库连接！ ", QMessageBox::Cancel);
    qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
    }
    qDebug()<<"连接成功"<<"connect to mysql OK";

    Kerberos(201900);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::socket_Read_Data()
{

    QByteArray buffer = socket->readAll();
    m_buffer.append(buffer);
    int total_length = m_buffer.size();
    while(total_length)
    {
        QDataStream recv_data(m_buffer);
        recv_data.setVersion(QDataStream::Qt_5_12);
        int m_len=sizeof(mes_len);
        if(total_length<m_len)
            break;//包长不够
        //mes_len *msg1=(mes_len*)m_buffer.left(m_len).data();
        unsigned int he_len;
        recv_data>>he_len;
        qDebug()<<m_buffer.left(m_len).length();
        int head_len=m_len+he_len+4;
        if(total_length<head_len)
            break;

        QByteArray t1;
        recv_data>>t1;
        Mes *header=(Mes *)t1.data();
        //Mes *header=(Mes *)m_buffer.mid(m_len,head_len).data();

        int all_len=head_len+header->message_length+header->sign_length+4;

        if(total_length<all_len)
            break;
        QByteArray t2;
        recv_data>>t2;
        //QByteArray t2=m_buffer.mid(head_len,all_len);
        Message res;
        res.message_length=header->message_length;
        res.message_type=header->message_type;
        res.field_type=header->field_type;
        for(int i=0;i<4;i++)
        {
            res.des_ip[i]=header->des_ip[i];
            res.des_src[i]=header->des_src[i];
            res.sign_length=header->sign_length;
        }

        res.data=t2.left(header->message_length);
        res.sign=t2.right(header->sign_length);
        recv_mes=res;

        buffer = m_buffer.right(total_length -all_len);
        total_length = buffer.size();
        m_buffer = buffer;

    }

    message_handel();
}

void MainWindow::message_handel()//处理收到的报文，并执行相应的操作
{
    int message_type=int(recv_mes.message_type);//报文类型
    int field_type=int(recv_mes.field_type);//字段类型
    switch(message_type)
    {
    case 0://收到错误报文
    {
        switch(field_type)//检测报文类型
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }

    case 1://收到普通用户报文
    {
        switch(field_type)//检测报文类型
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 2://收到管理员报文
    {
        switch(field_type)//检测报文类型
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 3://收到服务器报文
    {
        switch(field_type)//检测报文类型
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 67://收到服务器报文
    {
        switch(field_type)//检测报文类型
        {
        case 1:
            C_handel();
            break;
        case 2:
            break;
        }
        break;
    }
    case 4://收到AS报文
    {
        AS_handel();
        break;
    }

    case 5://收到tgs发的报文
    {
        TGS_handel();
        break;
    }
    }
}

void MainWindow::Kerberos(int idc){
    /*连接AS，与AS发消息*/
    //****ctoas
    CtoAS ctoas;
    ctoas.IDc=idc;//sql查询得到
    ctoas.IDtgs=22;
    QTime time=QTime::currentTime();
    ctoas.TS1=time.toString("h:m:s.z");
    g_allshare.TS1=ctoas.TS1;
    g_allshare.IDc=ctoas.IDc;
    g_allshare.IDv=33;

    //****ctoas change to qbytearr
    QByteArray ctoasSend;//ctoasSend.append((char*)&ctoas, sizeof(CtoAS));
    QBuffer ctoasbuffer(&ctoasSend);
    ctoasbuffer.open(QIODevice::WriteOnly);
    QDataStream ctoasout(&ctoasbuffer);
    ctoasout<<ctoas.IDc<<ctoas.IDtgs<<ctoas.TS1;
    ctoasbuffer.close();

    socket=new QTcpSocket;
    socket->connectToHost("127.0.0.1",6666);
        if(socket->waitForConnected(3000))
        {
            bool judge=package_message_noencrypt(0,1,ctoasSend,socket);
            QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
        }
        else
        {
            socket->disconnectFromHost();
            qDebug()<<"连接失败";
            socket->waitForDisconnected();
        }

}

void MainWindow::AS_handel(){
    //获取到了message,解析message中的内容
     //AStoC* astoc=(AStoC*)recmes.data.data();
     QBuffer as_ticketbuf(&recv_mes.data);
     as_ticketbuf.open(QIODevice::ReadOnly);
     QDataStream as_ticketin(&as_ticketbuf);
     char *asencrypt;char* ticket_encrypt;
     as_ticketin>>asencrypt>>ticket_encrypt;

     //****查一下本人的密钥
     char *mykey_n;
     char *mykey_d;
     switch(g_allshare.IDc)
     {
      case 201900:
         mykey_n=Ckey1_n;
         mykey_d=Ckey1_d;
         break;
     case 201901:
         mykey_n=Ckey2_n;
         mykey_d=Ckey2_d;
        break;
     case 201902:
         mykey_n=Ckey3_n;
         mykey_d=Ckey3_d;
        break;
     }

     //****astoc 解密
     char* asdecrypt=decrypt(asencrypt,mykey_n,mykey_d);
     QByteArray asdecrypt_data(asdecrypt);
     asdecrypt_data.remove(0,1);
     asdecrypt_data=QByteArray::fromHex(asdecrypt_data);

     //****qbytearr change astoc
     QBuffer asbuf(&asdecrypt_data);
     asbuf.open(QIODevice::ReadOnly);
     QDataStream asin(&asbuf);
     AStoC astocnew;
     asin>>astocnew.Key_c_tgs>>astocnew.IDtgs>>astocnew.TS2>>astocnew.lifetime;

     g_allshare.Key_c_tgs=astocnew.Key_c_tgs;
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

     socket->disconnectFromHost();
     socket->waitForDisconnected();

     /*连接TGS，与TGS发消息*/
     //**** Authenticator初始化和加密
     Authenticator auth;
     auth.IDc=g_allshare.IDc;
     QTime t3time=QTime::currentTime();
     auth.TS=t3time.toString("h:m:s.z");
     QByteArray authbyte;
     QBuffer authbuffer(&authbyte);
     authbuffer.open(QIODevice::WriteOnly);
     QDataStream authout(&authbuffer);
     authout<<auth.IDc<<auth.TS;
     authbuffer.close();
     QByteArray authbyte_en=DES_en(g_allshare.Key_c_tgs,authbyte);

     //**** 包装报文
     QByteArray ctotgsSend;
     QBuffer ctotgsbuffer(&ctotgsSend);
     ctotgsbuffer.open(QIODevice::WriteOnly);
     QDataStream ctotgsout(&ctotgsbuffer);
     ctotgsout<<g_allshare.IDv<<ticket_encrypt<<authbyte_en;
     ctotgsbuffer.close();

     socket=new QTcpSocket;
         socket->connectToHost("127.0.0.1",6667);
         if(socket->waitForConnected(3000))
         {
             bool judge=package_message_noencrypt(0,1,ctotgsSend,socket);
             QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
         }
         else
         {
             socket->disconnectFromHost();
             qDebug()<<"连接失败";
             socket->waitForDisconnected();
         }

}

void MainWindow::TGS_handel(){
    //获取到了message,解析message中的内容
     //des解密
     QByteArray rectgs=DES_de(g_allshare.Key_c_tgs,recv_mes.data);
     QBuffer tgstocbuf(&rectgs);
     tgstocbuf.open(QIODevice::ReadOnly);
     QDataStream tgstocin(&tgstocbuf);
     TGStoC tgstoc;
     tgstocin>>tgstoc.IDv>>tgstoc.Kcv>>tgstoc.TS4>>tgstoc.m_ticket_v;

     g_allshare.Key_c_v=tgstoc.Kcv;

     socket->disconnectFromHost();
     socket->waitForDisconnected();

     /*连接V，与V发消息*/
     //**** Authenticator初始化和加密
     Authenticator auth;
     auth.IDc=g_allshare.IDc;
     QTime t5time=QTime::currentTime();
     auth.TS=t5time.toString("h:m:s.z");
     QByteArray authbyte;
     QBuffer authbuffer(&authbyte);
     authbuffer.open(QIODevice::WriteOnly);
     QDataStream authout(&authbuffer);
     authout<<auth.IDc<<auth.TS;
     authbuffer.close();
     QByteArray authbyte_en=DES_en(g_allshare.Key_c_v,authbyte);

     //**** 包装报文
     QByteArray ctotgsSend;
     QBuffer ctotgsbuffer(&ctotgsSend);
     ctotgsbuffer.open(QIODevice::WriteOnly);
     QDataStream ctotgsout(&ctotgsbuffer);
     ctotgsout<<tgstoc.m_ticket_v<<authbyte_en;
     ctotgsbuffer.close();

     socket=new QTcpSocket;
         socket->connectToHost("127.0.0.1",6668);
         if(socket->waitForConnected(3000))
         {
             bool judge=package_message_noencrypt(0,1,ctotgsSend,socket);
             QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
         }
         else
         {
             socket->disconnectFromHost();
             qDebug()<<"连接失败";
             socket->waitForDisconnected();
         }

}

void MainWindow::C_handel(){
    //获取到了message,解析message中的内容
     //des解密
     QByteArray recv=DES_de(g_allshare.Key_c_v,recv_mes.data);
     QBuffer vtocbuf(&recv);
     vtocbuf.open(QIODevice::ReadOnly);
     QDataStream vtocin(&vtocbuf);
     VtoC vtoc;
     vtocin>>vtoc.TS5;

     socket->disconnectFromHost();
     socket->waitForDisconnected();
}
