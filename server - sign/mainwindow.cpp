#include "mainwindow.h"
#include "ui_mainwindow.h"
char RSA_n[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
char RSA_d[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
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
    server->listen(QHostAddress::Any, 6666);
    connect_mysql();

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
//    model=model_db("cart");
//    QByteArray data;
//    QBuffer buffer(&data);
//    buffer.open(QIODevice::WriteOnly);
//    QDataStream out(&buffer);
//    out<<model;
//    buffer.close();
    qDebug() << "client connect";
}

void MainWindow::socket_Read_Data()//当有数据过来之后读数据
{

    //buffer = socket->readAll();//读取缓冲区数据
    Message tempx=receive_message(socket,p->n,p->d);//无数字签名有加密

    QBuffer buf(&tempx.data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);

    test str3;
    in>>str3.a>>str3.data;
    qDebug()<<str3.a<<str3.data;
}


void MainWindow::connect_mysql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setPort(3306);
    db.setDatabaseName("canteen");       //这里输入你的数据库名
    db.setUserName("root");
    db.setPassword("Jtk010403");   //这里输入你的密码
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

