#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"DES.h"
#include<QTcpServer>
#include<QBuffer>
extern QSqlDatabase db;

//char Ckey1_n[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
//char Ckey1_d[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
int e=65537;
static char TGSkey_n[]="c432a812fda6c2b150efa577acf70721de1799acf9e789d054ceca82cc3af6f211ab3cf458b4016c32fc286c6d27d05baa5eccef0c594c2cb3d6eeca57cdc901911f4a990d062e2206a323bd0a3650607a9093cec0cc6eeb47b21316d643708f89e76c4a739f027ac6f93565dd68ffe4a5480f79b9163935238d6b05113003";
static char TGSkey_d[]="26401e067dcf4a3bd9a4af24d2e2e250170590df69655bb7f320d1d8884aa2a4750f6675d8e95731aa0b01328a616dbcc14d7434d2ba822060fb71589f9fae1fc1079cbe9d0a0aafcc378cd9edd29dbb151c3df3326207f77b153dfb7cbc8dba7e7f805c3cbe8d2e97b6770b8e3c2f718b1d53ec0f4348e197a5f8f431ef19";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
     //p->n=n;
     //p->d=d;
     //p->e=65537;
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

    //TCP连接
    TCPServer=new QTcpServer;
    TCPServer->listen(QHostAddress::Any, 6666);
    TCPServer->waitForNewConnection(-1);
    socket=TCPServer->nextPendingConnection();
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);


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
    AS_handel();

}


void MainWindow::AS_handel(){
    //****解析报文中的数据
    QBuffer recmesbuf(&recv_mes.data);
    recmesbuf.open(QIODevice::ReadOnly);
    QDataStream recmein(&recmesbuf);
    int ctoas_idc,ctoas_idtgs;
    QString ctoas_ts1;
    recmein>>ctoas_idc>>ctoas_idtgs>>ctoas_ts1;

    //****ticket
    Ticket tastoc;
    tastoc.ID=ctoas_idtgs;
    tastoc.IDc=ctoas_idc;
    tastoc.Key_cn=Get_K();//之后要改
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
    char* one_encrypt=encrypt(tdata.data(),TGSkey_n,e);

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

    //****查询c的公钥
    char* Ckey_n;
    QSqlQuery query(db);
    QString txt=QString("select Upubkey from user where Uid=%1").arg(ctoas_idc);
    bool sucess=query.exec(txt);
    if(query.first()){
        QString ckey_nstr=query.value(0).toString();
        std::string str=ckey_nstr.toStdString();
        Ckey_n=new char[strlen(str.c_str())+1];
        strcpy(Ckey_n,str.c_str());
    }


    //****astoc 加密
    asdata=asdata.toHex();
    asdata.insert(0,QByteArray("1"));
    char* asencrypt=encrypt(asdata.data(),Ckey_n,e);

    //****astoc and ticket send
    QByteArray as_ticket;
    QBuffer allbuffer(&as_ticket);
    allbuffer.open(QIODevice::WriteOnly);
    QDataStream allout(&allbuffer);
    allout<<asencrypt<<one_encrypt;
    allbuffer.close();
    package_message_noencrypt(4,0,as_ticket,socket);

    int adb=123;
}
