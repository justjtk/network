#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"DES.h"
#include<QTcpServer>
#include<QBuffer>
#include<QTime>
extern QSqlDatabase db;

char Vkey_n[]="a42ec64809f7e777bae17b10d33bf5df4bb605d6124cda58fbe0d7322342bd3af61810e2ff62b33b0bcf09c5dd155d2a6e2fabd4ee655f78ad2cf19b0ada671893a843fe307e6eb9df63be5853dc97a48aeaf19996b05e471fb14bd0ee2a9f3d0d521c158d627855397900c218b78a6561228cf3064054de70a2b772e53d4f";
char Vkey_d[]="54ac46d84a43cedd41c51dd9ec86c4e41740d5bbb48e6c216e2d63ee589f07c68bba97a2ea40f5dc62d7b0db998c7612f6e6a100dcbded41e85600788c5d5ca2ce5ec34c63b8644ddca22fe239a93bd93857687cce033315bf1ae523f1c3a2279f81c10b85960c691d706a1c210d97ae3ee5536f41412ea6f08c763fdbf269";
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

    //TCP连接
    TCPServer=new QTcpServer;
    TCPServer->listen(QHostAddress::Any, 6668);
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
    V_handel();

}


void MainWindow::V_handel(){
    //****解析报文中的数据
    CtoV ctov;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>ctov.m_ticket_v>>ctov.authenticator;

    //****ticket_V 解密
    char* ticket_decrypt=decrypt(ctov.m_ticket_v,Vkey_n,Vkey_d);
    QByteArray ticket_decrypt_data(ticket_decrypt);
    ticket_decrypt_data.remove(0,1);
    ticket_decrypt_data=QByteArray::fromHex(ticket_decrypt_data);

    //****qbytearr change ticket_v
    QBuffer ticketbuf(&ticket_decrypt_data);
    ticketbuf.open(QIODevice::ReadOnly);
    QDataStream ticketin(&ticketbuf);
    Ticket ticketnew;
    ticketin>>ticketnew.Key_cn>>ticketnew.IDc>>ticketnew.ID>>ticketnew.TS>>ticketnew.lifetime;

    //****authenticator 解密
     QByteArray auth=DES_de(ticketnew.Key_cn,ctov.authenticator);

    //****qbytearr change authenticator
     Authenticator authresult;
     QBuffer authbuffer(&auth);
     authbuffer.open(QIODevice::ReadOnly);
     QDataStream authin(&authbuffer);
     authin>>authresult.IDc>>authresult.TS;

     //****VtoC
     VtoC vtoc;
     vtoc.TS5=authresult.TS;//TS5+1;

     //****VtoC转为QBytearr
     QByteArray qbytevtoc;
     QBuffer vtocbuffer(&qbytevtoc);
     vtocbuffer.open(QIODevice::WriteOnly);
     QDataStream vtocout(&vtocbuffer);
     vtocout<<vtoc.TS5;
     vtocbuffer.close();

     //****TGStoC加密并发送
     QByteArray vtocSend=DES_en(ticketnew.Key_cn,qbytevtoc);
     package_message_noencrypt(67,1,vtocSend,socket);
     int adb=1;

}
