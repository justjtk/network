#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"DES.h"
#include<QTcpServer>
#include<QBuffer>
#include<QTime>
static char TGSkey_n[]="c432a812fda6c2b150efa577acf70721de1799acf9e789d054ceca82cc3af6f211ab3cf458b4016c32fc286c6d27d05baa5eccef0c594c2cb3d6eeca57cdc901911f4a990d062e2206a323bd0a3650607a9093cec0cc6eeb47b21316d643708f89e76c4a739f027ac6f93565dd68ffe4a5480f79b9163935238d6b05113003";
static char TGSkey_d[]="26401e067dcf4a3bd9a4af24d2e2e250170590df69655bb7f320d1d8884aa2a4750f6675d8e95731aa0b01328a616dbcc14d7434d2ba822060fb71589f9fae1fc1079cbe9d0a0aafcc378cd9edd29dbb151c3df3326207f77b153dfb7cbc8dba7e7f805c3cbe8d2e97b6770b8e3c2f718b1d53ec0f4348e197a5f8f431ef19";
int e=65537;
static char Vkey_n[]="a42ec64809f7e777bae17b10d33bf5df4bb605d6124cda58fbe0d7322342bd3af61810e2ff62b33b0bcf09c5dd155d2a6e2fabd4ee655f78ad2cf19b0ada671893a843fe307e6eb9df63be5853dc97a48aeaf19996b05e471fb14bd0ee2a9f3d0d521c158d627855397900c218b78a6561228cf3064054de70a2b772e53d4f";
static char Vkey_d[]="54ac46d84a43cedd41c51dd9ec86c4e41740d5bbb48e6c216e2d63ee589f07c68bba97a2ea40f5dc62d7b0db998c7612f6e6a100dcbded41e85600788c5d5ca2ce5ec34c63b8644ddca22fe239a93bd93857687cce033315bf1ae523f1c3a2279f81c10b85960c691d706a1c210d97ae3ee5536f41412ea6f08c763fdbf269";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //p->n=n;
    //p->d=d;
    //p->e=65537;
    ui->setupUi(this);
    //TCP连接
    TCPServer=new QTcpServer;
    TCPServer->listen(QHostAddress::Any, 6667);
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
    TGS_handel();

}


void MainWindow::TGS_handel(){
    //****解析报文中的数据
    CtoTGS ctotgs;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>ctotgs.IDv>>ctotgs.m_ticket_tgs>>ctotgs.authenticator;

    //****ticket_tgs 解密
    char* ticket_decrypt=decrypt(ctotgs.m_ticket_tgs,TGSkey_n,TGSkey_d);
    QByteArray ticket_decrypt_data(ticket_decrypt);
    ticket_decrypt_data.remove(0,1);
    ticket_decrypt_data=QByteArray::fromHex(ticket_decrypt_data);

    //****qbytearr change ticket_tgs
    QBuffer ticketbuf(&ticket_decrypt_data);
    ticketbuf.open(QIODevice::ReadOnly);
    QDataStream ticketin(&ticketbuf);
    Ticket ticketnew;
    ticketin>>ticketnew.Key_cn>>ticketnew.IDc>>ticketnew.ID>>ticketnew.TS>>ticketnew.lifetime;

    //****authenticator 解密
     QByteArray auth=DES_de(ticketnew.Key_cn,ctotgs.authenticator);

    //****qbytearr change authenticator
     Authenticator authresult;
     QBuffer authbuffer(&auth);
     authbuffer.open(QIODevice::ReadOnly);
     QDataStream authin(&authbuffer);
     authin>>authresult.IDc>>authresult.TS;

     //****生成ticket_v
     Ticket ticket_v;
     ticket_v.Key_cn=Get_K();
     ticket_v.IDc=ticketnew.IDc;
     ticket_v.ID=ctotgs.IDv;
     QTime ts4time=QTime::currentTime();
     ticket_v.TS=ts4time.toString("h:m:s.z");
     ticket_v.lifetime=24;

     //****ticket_v转为QBytearr
     QByteArray qbyteticket_v;
     QBuffer ticketvbuffer(&qbyteticket_v);
     ticketvbuffer.open(QIODevice::WriteOnly);
     QDataStream ticketvout(&ticketvbuffer);
     ticketvout<<ticket_v.Key_cn<<ticket_v.IDc<<ticket_v.ID<<ticket_v.TS<<ticket_v.lifetime;
     ticketvbuffer.close();

     //****ticket_v加密
     qbyteticket_v=qbyteticket_v.toHex();
     qbyteticket_v.insert(0,QByteArray("1"));
     char* qbyteticket_v_encrypt=encrypt(qbyteticket_v.data(),Vkey_n,e);

     //****TGStoC
     TGStoC tgstoc;
     tgstoc.IDv=ctotgs.IDv;
     tgstoc.Kcv=ticket_v.Key_cn;
     tgstoc.TS4=ticket_v.TS;
     tgstoc.m_ticket_v=qbyteticket_v_encrypt;

     //****TGStoC转为QBytearr
     QByteArray qbytetgstoc;
     QBuffer tgstocbuffer(&qbytetgstoc);
     tgstocbuffer.open(QIODevice::WriteOnly);
     QDataStream tgstocout(&tgstocbuffer);
     tgstocout<<tgstoc.IDv<<tgstoc.Kcv<<tgstoc.TS4<<tgstoc.m_ticket_v;
     tgstocbuffer.close();

     //****TGStoC加密并发送
     QByteArray tgstocSend=DES_en(ticketnew.Key_cn,qbytetgstoc);
     package_message_noencrypt(5,0,tgstocSend,socket);
     int adb=1;

}
