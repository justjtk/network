#include "mainwindow.h"
#include "ui_mainwindow.h"
#include"imagehandle.h"
#include"DES.h"
#include<QTcpServer>
#include<QBuffer>
#include<QTime>
#include<QVariant>
#include<QImage>
#include <QStandardItem>
#include <QStandardItemModel>
#include "qsqltablemodel.h"
#include<QVector>
extern QSqlDatabase db;

static char Vkey_n[]="a42ec64809f7e777bae17b10d33bf5df4bb605d6124cda58fbe0d7322342bd3af61810e2ff62b33b0bcf09c5dd155d2a6e2fabd4ee655f78ad2cf19b0ada671893a843fe307e6eb9df63be5853dc97a48aeaf19996b05e471fb14bd0ee2a9f3d0d521c158d627855397900c218b78a6561228cf3064054de70a2b772e53d4f";
static char Vkey_d[]="54ac46d84a43cedd41c51dd9ec86c4e41740d5bbb48e6c216e2d63ee589f07c68bba97a2ea40f5dc62d7b0db998c7612f6e6a100dcbded41e85600788c5d5ca2ce5ec34c63b8644ddca22fe239a93bd93857687cce033315bf1ae523f1c3a2279f81c10b85960c691d706a1c210d97ae3ee5536f41412ea6f08c763fdbf269";
int e=65537;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

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
    //V_handel();
    message_handel();

}

void MainWindow::message_handel()//处理收到的报文，并执行相应的操作
{
    int message_type=int(recv_mes.message_type);//报文类型
    int field_type=int(recv_mes.field_type);//字段类型
    switch(message_type)
    {
    case 65://
    {
        switch(field_type)//
        {
        case 6:
            V_handel();
            break;
        case 8:
            modinf_handel();
            break;
        case 24:
            userinf_handel();
            break;
        case 25:
            modpsw_handel();
            break;
        }
        break;
    }

    }
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
    g_Key_cv=ticketnew.Key_cn;
    g_idc=ticketnew.IDc;
    //****查询c的公钥

    QSqlQuery query(db);
    QString txt=QString("select Upubkey from user where Uid=%1").arg(g_idc);
    bool sucess=query.exec(txt);
    if(query.first()){
        QString ckey_nstr=query.value(0).toString();
        std::string str=ckey_nstr.toStdString();
        g_Ckey_n=new char[strlen(str.c_str())+1];
        strcpy(g_Ckey_n,str.c_str());
    }


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

void MainWindow::userinf_handel(){
    //****des解密
    recv_mes.data=DES_de(g_Key_cv,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(g_Key_cv,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,g_Ckey_n,e);      //不要数字签名的话这一行去掉

    //****解析报文中的数据
    QString txtinf,txtorder,txtvip;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>txtinf>>txtorder>>txtvip;

    //****查询个人信息
    QString uname,uphe;//图片到时候要改
    QByteArray upic;
    QImage pic;
    QSqlQuery query(db);
    bool sucess=query.exec(txtinf);
    if(query.first()){
        uname=query.value(0).toString();
        uphe=query.value(1).toString();
        pic.loadFromData(query.value(2).toByteArray(),"JPG");
        upic=getImageData(pic);
    }

    //****查询vip
    bool vip=false;
    QSqlQuery queryvip(db);
    queryvip.exec(txtvip);
    if(queryvip.first()){
        vip=true;
    }

    //****查询订单信息
    QVector<QVector<QString>> orders;
    QSqlQueryModel* model= new QSqlQueryModel;
    model->setQuery(txtorder);
    int row=model->rowCount();
    int col=model->columnCount();
    for(int i=0;i<row;++i){
        QVector<QString> qstr;
        for(int j=0;j<col;++j){
           qstr.push_back(model->data(model->index(i,j)).toString());
        }
        orders.push_back(qstr);
    }
    int order_size=orders.size();

    //****打包发送
    QByteArray infSend;
    QBuffer infbuffer(&infSend);
    infbuffer.open(QIODevice::WriteOnly);
    QDataStream infout(&infbuffer);
    infout<<uname<<uphe<<upic<<order_size;
    if(order_size>0)infout<<vip<<orders;
    infbuffer.close();

    package_message_DES(65,24,infSend,socket,g_Key_cv,Vkey_n,Vkey_d);
    int adsk=1;
}

void MainWindow::modinf_handel(){
    //****des解密
    recv_mes.data=DES_de(g_Key_cv,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(g_Key_cv,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,g_Ckey_n,e);      //不要数字签名的话这一行去掉

    //****解析报文中的数据
    bool ifimg;
    QString txt;
    QByteArray upic;
    QString name,phone;
    int id;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>ifimg;
    if(ifimg)recin>>name>>phone>>upic>>id;
    else recin>>txt;

    QImage img=getImage(upic);
    ui->label->setPixmap(QPixmap::fromImage(img));
    QByteArray imageData;
    QBuffer buffer(&imageData);
    img.save(&buffer, "jpg");
    QVariant var(imageData);

    //****修改
    bool sucess;
    QSqlQuery query(db);
    if(ifimg){
        query.prepare("update user set uname=?,uphe=?,upic=? where uid=?");

        query.addBindValue(name);

        query.addBindValue(phone);

        query.addBindValue(var);

        query.addBindValue(id);

        sucess=query.exec();
        if(!sucess){
            QSqlError le=query.lastError();
            qDebug()<<le.text();
        }
    }
    else{
    sucess=query.exec(txt);}

    //****打包发送
    QByteArray infSend;
    QBuffer infbuffer(&infSend);
    infbuffer.open(QIODevice::WriteOnly);
    QDataStream infout(&infbuffer);
    infout<<sucess;
    infbuffer.close();

    package_message_DES(65,8,infSend,socket,g_Key_cv,Vkey_n,Vkey_d);
    int adsk=1;
}

void MainWindow::modpsw_handel(){
    //****des解密
    recv_mes.data=DES_de(g_Key_cv,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(g_Key_cv,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,g_Ckey_n,e);      //不要数字签名的话这一行去掉

    //****解析报文中的数据
    QString txtfind,oldpsw,newpsw;
    int userid;
    QBuffer recbuffer(&recv_mes.data);
    recbuffer.open(QIODevice::ReadOnly);
    QDataStream recin(&recbuffer);
    recin>>txtfind>>userid>>oldpsw>>newpsw;

    //****查询原来的密码
    QString dbpsw;
    QSqlQuery query(db);
    bool sucess=query.exec(txtfind);
    if(query.first()){
        dbpsw=query.value(0).toString();
    }

    bool ifmodpsw=false;
    QString newstrMD5,oldstrMD5;
    //****对比密码
    QByteArray oldpswarr,newpswarr;
    oldpswarr.append(oldpsw);
    newpswarr.append(newpsw);
    QByteArray oldhash = QCryptographicHash::hash(oldpswarr, QCryptographicHash::Md5);
    QByteArray newhash = QCryptographicHash::hash(newpswarr, QCryptographicHash::Md5);
    oldstrMD5 = oldhash.toHex();
    newstrMD5=newhash.toHex();
    if(oldstrMD5==dbpsw){
        ifmodpsw=true;
        QString txtupdate=QString("update user set upass='%1' where uid=%2").arg(newstrMD5).arg(userid);
        if(!query.exec(txtupdate)){
            ifmodpsw=false;;
        }
    }

    QByteArray infSend;
    QBuffer infbuffer(&infSend);
    infbuffer.open(QIODevice::WriteOnly);
    QDataStream infout(&infbuffer);
    infout<<ifmodpsw;
    infbuffer.close();

    package_message_DES(65,25,infSend,socket,g_Key_cv,Vkey_n,Vkey_d);
    int adsk=1;


}
