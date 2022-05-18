#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qdebug.h>
#include <QMessageBox>
char RSA_n[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
char RSA_d[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
char DES_KEY[]="01010000010000000000010101010101010001000100000100000100000101000100010001010100010100010100010101000100000101010101010000010000";
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer();
    connect(server,&QTcpServer::newConnection,this,&MainWindow::server_New_Connect);//连接信号槽
    //密钥的初始化，之后可以去掉

    p->n=RSA_n;
    p->d=RSA_d;
    p->e=65537;
    DES_key_to_client=DES_KEY;
    DES_key_to_client=QByteArray::fromHex(DES_key_to_client);
    connect_mysql();
    sql_to_table();

    server->listen(QHostAddress::Any, 6666);
    qDebug()<<"start to listen"<<endl;

    //ui->tableView->setModel(good_model);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::server_New_Connect()   //当有新的连接来的时候
{
    //获取客户端连接
    socket = server->nextPendingConnection();
    QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
    QObject::connect(socket, &QTcpSocket::disconnected, this, &MainWindow::socket_Disconnected);
    Client_num++; //连接客户端的数量加一
    qDebug() << "client connect";


}

void MainWindow::socket_Read_Data()//当有数据过来之后读数据
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
        //qDebug()<<m_buffer.left(m_len).length();
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
        res.sign_length=header->sign_length;
        for(int i=0;i<4;i++)
        {
            res.des_ip[i]=header->des_ip[i];
            res.des_src[i]=header->des_src[i];

        }

        res.data=t2.left(header->message_length);
        res.sign=t2.right(header->sign_length);
        //后面为解密并且还原，这里需要注意，需要设计如何选择解密方法以及密钥，还有，不要忘记解密完要调用remove和fromHex

        buffer = m_buffer.right(total_length -all_len);
        total_length = buffer.size();
        m_buffer = buffer;

        if(0)
        {
///////////////////////////////////////////////////////////////RSA解密
//
//        res.sign=decrypt(res.sign.constData(),p->n,p->d);
//        res.data=decrypt(res.data.constData(),p->n,p->d);
//        //RSA解密,res为message类型，res.data为message的data部分
//        bool judge=sign_judge(res.data,res.sign,p->n,p->e);
//        //不要数字签名的话这一行去掉
//        res.data.remove(0,1);
//        //res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
//        res.data=QByteArray::fromHex(res.data);
          //解密的时候分开解密，并且分别存到数字签名和data的部分


///////////////////////////////////////////////////////////////DES解密
//
//      res.data=DES_de(DES_key_to_client,res.data);
//      //res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
//      res.sign=DES_de(DES_key_to_client,res.sign);
//      //不要数字签名的话这一行去掉，DES的解密，res为message类型，res.data为message的data部分
//      bool judge=sign_judge(res.data,res.sign,p->n,p->e);
//      //不要数字签名的话这一行去掉
//      qDebug()<<judge;


//        test str;
//        QBuffer buf(&res.data);
//        buf.open(QIODevice::ReadOnly);
//        QDataStream in(&buf);

//        in>>str.a>>str.data;
//        qDebug()<<str.data;
        }

        recv_mes=res;

        message_handel();//处理收到的报文

    }
}


void MainWindow::message_handel()//处理收到的报文，并执行相应的操作
{
    if(0)
    {
        ///////////////////////////////////////////////////////////////RSA解密
        //
        //        res.sign=decrypt(res.sign.constData(),p->n,p->d);
        //        res.data=decrypt(res.data.constData(),p->n,p->d);
        //        //RSA解密,res为message类型，res.data为message的data部分
        //        bool judge=sign_judge(res.data,res.sign,p->n,p->e);
        //        //不要数字签名的话这一行去掉
        //        res.data.remove(0,1);
        //        //res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
        //        res.data=QByteArray::fromHex(res.data);
                  //解密的时候分开解密，并且分别存到数字签名和data的部分

        ///////////////////////////////////////////////////////////////DES解密
        //
        //      res.data=DES_de(DES_key_to_client,res.data);
        //      //res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
        //      res.sign=DES_de(DES_key_to_client,res.sign);
        //      //不要数字签名的话这一行去掉，DES的解密，res为message类型，res.data为message的data部分
        //      bool judge=sign_judge(res.data,res.sign,p->n,p->e);
        //      //不要数字签名的话这一行去掉
        //      qDebug()<<judge;
    }
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

        case 65://普通用户控制报文
        {
            switch(field_type)
            {
            case 14://处理登陆请求
                qDebug()<<"logoin check";
                Login_Check();
                break;
            case 15://处理商品表查询
                qDebug()<<"inquire goods";
                Inquire_goods();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            }
        }

    }
}


void MainWindow::connect_mysql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("netshop");       //这里输入你的数据库名
    db.setUserName("root");
    db.setPassword("123456");   //这里输入你的密码
    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("无法打开数据库"), "无法创建数据库连接！ ", QMessageBox::Cancel);
        qDebug() << "不能连接" << "connect to mysql error" << db.lastError().text();
    }
    qDebug() << "连接成功" << "connect to mysql OK";
}

bool  MainWindow::modify_db(QString txt) {//增删改
    query = new QSqlQuery(db);

    if(!query->exec(txt))
    {
        QSqlError lastError = query->lastError();
        qDebug() << lastError.text();
        return false;
    }
    return true;
}

QSqlQuery MainWindow::query_db(QString txt) {//查询
    query = new QSqlQuery(db);
    if(!query->exec(txt))
    {
        QSqlError lastError = query->lastError();
        qDebug() << lastError.text();
    }
    return *query;
}

QSqlTableModel* MainWindow::model_db(QString txt) {//查询
   model = new QSqlTableModel();

   model->setTable(txt);
    if(model->select()){//不是空表
        qDebug()<<"返回成功";
        return model;
    }
    else
    {
        qDebug()<<"该表为空表";
        return model;
    }
}

void MainWindow::socket_Disconnected()   //当连接关闭的时候
{

}

void MainWindow::sql_to_table()
{
    model=model_db("cart");
    int row=model->rowCount();
    int col=model->columnCount();
    //QStandardItem *item;
    send_table.clear();
    //QStandardItemModel *res=new QStandardItemModel();
    QVector<QString> temp;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            //item=new QStandardItem();
            //res->setItem(i,j,item);
            temp.push_back(model->record(i).value(j).toString());

        }
        send_table.push_back(temp);
        temp.clear();
    }
    return;
}

void MainWindow::Login_Check()//登录检验
{
    recv_mes.data=DES_de(DES_key_to_client,recv_mes.data);
    //res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(DES_key_to_client,recv_mes.sign);
    //不要数字签名的话这一行去掉，DES的解密，res为message类型，res.data为message的data部分
    sign_judge(recv_mes.data,recv_mes.sign,p->n,p->e);
    //不要数字签名的话这一行去掉

    QBuffer buf(&recv_mes.data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
    QByteArray qbt_sql;
    in>>qbt_sql;
    QString sql(qbt_sql.data());
    buf.close();

    QByteArray data;
    QBuffer buff(&data);
    buff.open(QIODevice::WriteOnly);
    QDataStream out(&buff);

    QSqlQuery inquire;
    if(!inquire.exec(sql))
        QMessageBox::information(this,"notice","inquire failed!");

    bool iqur=inquire.next();
    if(iqur)
    {
        //返回登录成功
        out<<iqur;
        //返回个人信息
        for(int i=0;i<6;i++)
        {
            if(i<5)
            {
                QString qstr_value=inquire.value(i).toString();
                QByteArray qbt_value=qstr_value.toUtf8();
                //out<<qbt_value;
            }
            else
            {
                QImage head_img;
                head_img.loadFromData(inquire.value(i).toByteArray(),"JPG");
                QByteArray head_qbt=getImageData(head_img);
                out<<head_qbt;
            }
        }

    }
    else
    {
        //返回登录失败
        qDebug()<<"login error";
        out<<iqur;
    }
    buff.close();
    package_message_DES(67,6,data,socket,DES_key_to_client,p->n,p->d);
}

void MainWindow::Inquire_goods()
{
    recv_mes.data=DES_de(DES_key_to_client,recv_mes.data);
    //res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(DES_key_to_client,recv_mes.sign);
    //不要数字签名的话这一行去掉，DES的解密，res为message类型，res.data为message的data部分
    sign_judge(recv_mes.data,recv_mes.sign,p->n,p->e);
    //不要数字签名的话这一行去掉

    QBuffer buf(&recv_mes.data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
    QByteArray qbt_sql;
    in>>qbt_sql;
    QString sql(qbt_sql.data());
    buf.close();

    QByteArray data;
    QBuffer buff(&data);
    buff.open(QIODevice::WriteOnly);
    QDataStream out(&buff);

    QSqlQuery inquire;
    if(!inquire.exec(sql))
        QMessageBox::information(this,"notice","inquire failed!");

    QVector<QVector<QString>> goods_infm;
    QVector<QByteArray> goods_img;
    QVector<QString> temp;

    bool iqur=inquire.next();
    if(iqur)
    {
        //返回查询成功
        out<<iqur;
        //返回商品信息
        for(int i=0;i<6;i++)//遍历记录
        {
            temp.clear();
            for(int j=0;j<6;j++)//遍历字段
            {
                if(j<5)//信息
                {
                    QString qstr_value=inquire.value(j).toString();
                    //qDebug()<<qstr_value;
                    temp.push_back(qstr_value);
                }
                else//图片
                {
                    QImage img;
                    img.loadFromData(inquire.value(j).toByteArray(),"JPG");
                    QByteArray img_qbt=getImageData(img);
                    goods_img.push_back(img_qbt);
                }
            }
            goods_infm.push_back(temp);
            inquire.next();
            //break;//////////////////////////////////////////////////////////
        }
        //int a=2;
        //out<<a;
        out<<goods_infm<<goods_img;
        //out<<goods_infm;
    }
    else
    {
        //返回查询失败
        qDebug()<<"inquire goods error";
        out<<iqur;
    }
    buff.close();
    package_message_DES(3,2,data,socket,DES_key_to_client,p->n,p->d);
}



















