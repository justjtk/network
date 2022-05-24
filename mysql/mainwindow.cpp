#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include<QStringList>
#include<QColor>
#include<QFile>
#include<QInputDialog>
#include<QFileDialog>
#include<fstream>
#include<string>
#include<QTime>
using namespace std;
char RSA_n[]="b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
char RSA_d[]="59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
char DES_KEY[]="01010000010000000000010101010101010001000100000100000100000101000100010001010100010100010100010101000100000101010101010000010000";
char Vkey_n[]="a42ec64809f7e777bae17b10d33bf5df4bb605d6124cda58fbe0d7322342bd3af61810e2ff62b33b0bcf09c5dd155d2a6e2fabd4ee655f78ad2cf19b0ada671893a843fe307e6eb9df63be5853dc97a48aeaf19996b05e471fb14bd0ee2a9f3d0d521c158d627855397900c218b78a6561228cf3064054de70a2b772e53d4f";
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
//     QFile file(":/Aqua.qss");
//     file.open(QFile::ReadOnly);
//     QString styleSheet = tr(file.readAll());
//     this->setStyleSheet(styleSheet);
//     file.close();
    this->setStyleSheet("QMainWindow{background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgb(255, 245, 245), stop:1 rgb(255, 254, 245))}");
    ui_init();
    const QString write_button_style="QPushButton{"
                                     "background-color:rgb(255,255,255);"
                                     "border-radius: 13px; "
                                     "border:1px solid rgba(255,152,95,255);"
                                     "color:qlineargradient(spread:pad, x1:0, y1:0.034, x2:0.730337, y2:0.756045, stop:0 rgba(255, 181, 79, 255), stop:1 rgba(255, 133, 111, 255));"
                                     "font: bold 20px;"
                                     "font-family: 汉仪正圆-45W;}"
                                   "QPushButton:pressed {background-color: #dfdfdf;}";
    ui->pushButton->setStyleSheet(write_button_style);//pressed

    ui->pushButton_3->setStyleSheet(write_button_style);//pressed

    ui->pushButton_2->setStyleSheet(write_button_style);//pressed

    ui->pushButton_4->setStyleSheet(write_button_style);//pressed

    ui->tableView->verticalHeader()->hide();//隐藏行号方法

    ui->tableView->horizontalHeader()->setStyleSheet("QHeaderView::section, QTableCornerButton::section {padding: 1px;border: none;background-color:#fd9f9a;color:#fde1df;}");

    ui->tableView->setStyleSheet("QTableView::item::selected{"
                                 "background: QLinearGradient(x1: 0, y1: 0, x2: 0, y2: 0, stop: 0 #ffe1d7, stop: 0.25 #fcffe6, stop: 0.5 #f8ffcd, stop: 0.75 #fcffe6);color:rgb(0,0,0);}");

    //ui->tableView->setShowGrid(false);//隐藏单元格线

    //设置列宽不可变

//    ui->tableView->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);

//    ui->tableView->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);

//    ui->tableView->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);

//    ui->tableView->setColumnWidth(0,187);

//    ui->tableView->setColumnWidth(1,93);

//    ui->tableView->setColumnWidth(2,281);


    wlogin->show();
    connect(wlogin, SIGNAL(Send_uid_to_mwd(QString, QString)), this, SLOT(Login_check(QString, QString)));//登录成功传id

    rsa_to_server->n=RSA_n;
    rsa_to_server->d=RSA_d;
    rsa_to_server->e=65537;
    //DES_key=DES_KEY;
    //DES_key=QByteArray::fromHex(DES_key);
//    socket->connectToHost("127.0.0.1",6666);

//    if(socket->waitForConnected(30000))
//    {
//        qDebug()<<"连接成功";
//        QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
//    }
//    else
//    {
//        socket->disconnectFromHost();
//        qDebug()<<"连接失败";
//        socket->waitForDisconnected();
//    }
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
        message_handel();
    }

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
    case 67://收到服务器控制报文
    {
        switch(field_type)//检测报文类型
        {
        case 1:
            C_handel();
            break;
        case 11:
            order_handel();
            break;
        case 4:
            show_picture();
            break;
        case 6:
            Login_confirm();
            break;
        }
        break;
    }
    case 3://收到服务器报文
    {
        switch(field_type)//检测报文类型
        {
        case 3:
            update_tableview();
            break;
        case 1:
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

void MainWindow::update_tableview()
{
    QVector<QVector<QString>> recv_table;
    //QVector<QImage> recv_image;
    recv_img.clear();
    QVector<QByteArray> recv_img_byte;
    Message pac_show_mes=recv_mes;
    recv_mes.data=DES_de(DES_key,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(DES_key,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,Vkey_n,rsa_to_server->e);                  //不要数字签名的话这一行去掉

    QBuffer buffer(&recv_mes.data);
    buffer.open(QIODevice::ReadOnly);
    QDataStream in(&buffer);
    in>>recv_table;
    buffer.close();
    QString show_package_str="收到的数据表信息：\n";
    int table_id=0;
    for(int i=0;i<6;i++)
    {
        if(judgetable[i]==true)
        {
            table_id=i;
        }
    }

    QStandardItem *item;
    QStandardItemModel *res=new QStandardItemModel();
    res->setColumnCount(tablename[table_id].size());
    for(int i=0;i<tablename[table_id].size();i++)
    {
        res->setHeaderData(i,Qt::Horizontal,tablename[table_id][i]);
    }
    for(int i=0;i<recv_table.size();i++)
    {
        for(int j=0;j<recv_table[i].size();j++)
        {
            show_package_str+=recv_table[i][j]+"\t";
            item=new QStandardItem(recv_table[i][j]);
            res->setItem(i,j,item);
            res->item(i, j)->setTextAlignment(Qt::AlignCenter);
        }
    }
    recv_pack_show(pac_show_mes,show_package_str,recv_mes.sign,DES_key);
    good_model=res;
    all_model=good_model;
    ui->tableView->setModel(good_model);

    update();
}

void MainWindow::changecombox()
{
    for(int i=0;i<6;i++)
    {
        if(judgetable[i]==true)
        {
            ui->comboBox->clear();
            for(int j=0;j<tablename[i].size();j++)
            {
            ui->comboBox->addItem(tablename[i][j]);
            }
        }
    }
}




void MainWindow::connect_mysql()
{
    db = QSqlDatabase::addDatabase("QMYSQL");  //连接的MYSQL的数据库驱动
    db.setHostName("localhost");         //主机名
    db.setPort(3306);                    //端口
    db.setDatabaseName("netshop");          //数据库名
    db.setUserName("root");              //用户名
    db.setPassword("Jtk010403");            //密码
    db.open();

    //测试连接

    if(!db.open())
    {
        qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        return ;
    }
    else
    {
         qDebug()<<"连接成功"<<"connect to mysql OK";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showtable()
{
    for(int i=0;i<6;i++)
    {
        if(judgetable[i]==true)
        {
            QString txt=tableid[i];

            QByteArray send_data;
            QBuffer buffer(&send_data);
            buffer.open(QIODevice::WriteOnly);
            QDataStream out(&buffer);

            out<<txt;
            int i=66;
            int y=2;
            QVector<QString> pac_show_vec = package_message_DES(i,y,send_data,socket,DES_key,rsa_to_server->n,rsa_to_server->d);//数字签名DES加密
            QString show_det="要查询的表"+txt;
            pac_show_vec[7]=show_det;
            send_pack_show_des(pac_show_vec);
        }
    }

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{


}

void MainWindow::on_pushButton_clicked()
{
    QVector<QString>temp;
    QImage up_img;
    if(judgetable[0]==true)
    {
        Dialog0 * a=new Dialog0(this);
        a->exec();
        temp=a->data;
        up_img=a->img;
    }

    if(temp.empty())return;
    QByteArray img_data=getImageData(up_img);
    QByteArray send_data;
    QBuffer buffer(&send_data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out<<temp<<img_data;
    int i=2;
    int y=4;
    QVector<QString> pac_show_vec = package_message_DES(i,y,send_data,socket,DES_key,rsa_to_server->n,rsa_to_server->d);//数字签名DES加密
    QString show_det="插入的商品信息"+temp[0]+"\t"+temp[1]+"\t"+temp[2]+"\t"+temp[3]+"\t"+temp[4]+"\t图片为"+img_data.toHex();
    pac_show_vec[7]=show_det;
    send_pack_show_des(pac_show_vec);
}

void MainWindow::on_pushButton_2_clicked()
{

    int row = ui->tableView->currentIndex().row();//记录当前选择行
    if(QMessageBox::Yes == QMessageBox::question(this,"警告","确定删除第"+QString::number(row+1)+"行数据吗？",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes))
    {
        QString good_name=good_model->index(ui->tableView->currentIndex().row(),0).data().toString();
        QString send_sql=QString("delete from good where Gname='%1'").arg(good_name);
        QByteArray send_data;
        QBuffer buffer(&send_data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);

        out<<send_sql;
        int i=2;
        int y=2;

        QVector<QString> pac_show_vec = package_message_DES(i,y,send_data,socket,DES_key,rsa_to_server->n,rsa_to_server->d);//数字签名DES加密
        QString show_det="删除商品"+send_sql;
        pac_show_vec[7]=show_det;
        send_pack_show_des(pac_show_vec);
    }

}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(ui->comboBox->currentText()==tablename[0][ui->comboBox->currentIndex()])//只能改商品表
    {
        bool judge=false;
        QString temp = QInputDialog::getText(this,"change","修改当前表格内容",QLineEdit::Normal,index.data().toString(),&judge);
        if(judge==false)return;
        int now_row=ui->tableView->currentIndex().row();
        int now_col=ui->tableView->currentIndex().column();
        QString good_name=good_model->index(now_row,0).data().toString();
        QString goodid[6]={"Gname","Gnum","Gprice","Gdiscount","Gtype","Gimage"};
        QString send_sql;
        if(now_col==0)
        {
            send_sql=QString("update good set Gname='%1'where Gname='%2'").arg(temp).arg(good_name);
        }
        else
        {
            send_sql=QString("update good set %1=%2 where Gname='%3'").arg(goodid[now_col]).arg(temp).arg(good_name);
        }
        QByteArray send_data;
        QBuffer buffer(&send_data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);

        out<<send_sql;
        int i=2;
        int y=1;
        QVector<QString> pac_show_vec = package_message_DES(i,y,send_data,socket,DES_key,rsa_to_server->n,rsa_to_server->d);//数字签名DES加密
        QString show_det="更新商品信息"+send_sql;
        pac_show_vec[7]=show_det;
        send_pack_show_des(pac_show_vec);
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    QStandardItem *item;
    QStandardItemModel *res=new QStandardItemModel();
    int value=ui->comboBox->currentIndex();
    QString temp1=ui->comboBox->currentText();
    QString temp2=ui->lineEdit->text();
    ui->lineEdit->clear();
    int res_row=0;

    if(temp1!=""&&temp2!="")//不为空
    {
        int i_row=all_model->rowCount();
        int i_col=all_model->columnCount();
        for(int i=0;i<i_row;i++)
        {
                QString seach_target=all_model->index(i,value).data().toString();
                if(seach_target==temp2)
                {
                    for(int j=0;j<i_col;j++)
                    {
                       item=new QStandardItem(all_model->index(i,j).data().toString());
                       res->setItem(res_row,j,item);
                    }
                    res_row++;
                }
        }
        good_model=res;
        ui->tableView->setModel(good_model);
    }
    else
    {
        good_model=all_model;
        ui->tableView->setModel(all_model);
    }
    if(ui->comboBox->currentText()==tablename[0][ui->comboBox->currentIndex()])
    {
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);
        judgetable[0]=false;
    }
    else
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }

    ui->actiona->setChecked(false);
    ui->actionm->setChecked(false);
    ui->actiong->setChecked(false);
    ui->actions->setChecked(false);
    ui->actionw->setChecked(false);
    ui->actionp->setChecked(false);
}


void MainWindow::ui_init()
{
    connect(ui->actiong,&QAction::triggered,[=](){
    if(ui->actiong->isChecked()==false)
    {
    ui->actiong->setChecked(false);
    judgetable[0]=false;
    model = new QSqlTableModel(this,db);
    }
    else {
    for(int i=0;i<6;i++)
    {
        judgetable[i]=false;
    }
    ui->actiona->setChecked(false);
    ui->actionm->setChecked(false);
    ui->actionp->setChecked(false);
    ui->actions->setChecked(false);
    ui->actionw->setChecked(false);
    judgetable[0]=true;
    ui->actiong->setChecked(true);
    ui->pushButton->setEnabled(true);
    ui->pushButton_2->setEnabled(true);
    }
    changecombox();
    showtable();
    update();
    });
    connect(ui->actionw,&QAction::triggered,[=](){
    if(ui->actionw->isChecked()==false)
    {
    ui->actionw->setChecked(false);
    judgetable[1]=false;
    model = new QSqlTableModel(this,db);
    }
    else {
    for(int i=0;i<6;i++)
    {
        judgetable[i]=false;
    }
    ui->actiona->setChecked(false);
    ui->actionm->setChecked(false);
    ui->actionp->setChecked(false);
    ui->actions->setChecked(false);
    ui->actiong->setChecked(false);
    judgetable[1]=true;
    ui->actionw->setChecked(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    }
    changecombox();
    showtable();
    update();
    });
    connect(ui->actionm,&QAction::triggered,[=](){
    if(ui->actionm->isChecked()==false)
    {
    ui->actionm->setChecked(false);
    judgetable[2]=false;
    model = new QSqlTableModel(this,db);
    }
    else {
    for(int i=0;i<6;i++)
    {
        judgetable[i]=false;
    }
    ui->actiona->setChecked(false);
    ui->actiong->setChecked(false);
    ui->actionp->setChecked(false);
    ui->actions->setChecked(false);
    ui->actionw->setChecked(false);
    judgetable[2]=true;
    ui->actionm->setChecked(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    }
    changecombox();
    showtable();
    update();
    });
    connect(ui->actions,&QAction::triggered,[=](){
    if(ui->actions->isChecked()==false)
    {
    ui->actions->setChecked(false);
    judgetable[3]=false;
    model = new QSqlTableModel(this,db);
    }
    else {
    for(int i=0;i<6;i++)
    {
        judgetable[i]=false;
    }
    ui->actiona->setChecked(false);
    ui->actionm->setChecked(false);
    ui->actionp->setChecked(false);
    ui->actiong->setChecked(false);
    ui->actionw->setChecked(false);
    judgetable[3]=true;
    ui->actions->setChecked(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    }
    changecombox();
    showtable();
    update();
    });
    connect(ui->actionp,&QAction::triggered,[=](){
    if(ui->actionp->isChecked()==false)
    {
    ui->actionp->setChecked(false);
    judgetable[4]=false;
    model = new QSqlTableModel(this,db);
    }
    else {
    for(int i=0;i<6;i++)
    {
        judgetable[i]=false;
    }
    ui->actiona->setChecked(false);
    ui->actionm->setChecked(false);
    ui->actiong->setChecked(false);
    ui->actions->setChecked(false);
    ui->actionw->setChecked(false);
    judgetable[4]=true;
    ui->actionp->setChecked(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    }
    changecombox();
    showtable();
    update();
    });
    connect(ui->actiona,&QAction::triggered,[=](){
    if(ui->actiona->isChecked()==false)
    {
    ui->actiona->setChecked(false);
    judgetable[5]=false;
    model = new QSqlTableModel(this,db);
    }
    else {
    for(int i=0;i<6;i++)
    {
        judgetable[i]=false;
    }
    ui->actiong->setChecked(false);
    ui->actionm->setChecked(false);
    ui->actionp->setChecked(false);
    ui->actions->setChecked(false);
    ui->actionw->setChecked(false);
    judgetable[5]=true;
    ui->actiona->setChecked(true);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    }
    changecombox();
    showtable();
    update();
    });


    tablename[0].push_back("商品名");
    tablename[0].push_back("商品数量");
    tablename[0].push_back("商品价格");
    tablename[0].push_back("商品打折价格");
    tablename[0].push_back("商品类型");
    //tablename[0].push_back("商品图片");

    tablename[1].push_back("商品名");
    tablename[1].push_back("商品数量");
    tablename[1].push_back("商品价格");
    tablename[1].push_back("商品打折价格");
    tablename[1].push_back("用户ID");


    tablename[2].push_back("管理员ID");
    tablename[2].push_back("管理员密码");
    tablename[2].push_back("管理员密钥");
    tablename[3].push_back("用户ID");
    tablename[3].push_back("用户昵称");
    tablename[3].push_back("用户密码");
    tablename[3].push_back("用户会员卡号");
    tablename[3].push_back("用户电话");
    tablename[3].push_back("用户密钥");

    tablename[4].push_back("会员卡号");
    tablename[4].push_back("用户ID");
    tablename[4].push_back("到期时间");

    tablename[5].push_back("用户ID");
    tablename[5].push_back("商品名");
    tablename[5].push_back("商品数量");
    tablename[5].push_back("销售时间");
}


void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    if(judgetable[0]==true)//选中的是商品表
    {
        QString good_name=good_model->index(ui->tableView->currentIndex().row(),0).data().toString();
        QString send_sql=QString("select Gimage from good where Gname='%1'").arg(good_name);
        QByteArray send_data;
        QBuffer buffer(&send_data);
        buffer.open(QIODevice::WriteOnly);
        QDataStream out(&buffer);

        out<<send_sql;
        int i=2;
        int y=3;
        QVector<QString> pac_show_vec = package_message_DES(i,y,send_data,socket,DES_key,rsa_to_server->n,rsa_to_server->d);//数字签名DES加密
        QString show_det="请求商品图片"+send_sql;
        pac_show_vec[7]=show_det;
        send_pack_show_des(pac_show_vec);
        //ui->label->setPixmap(QPixmap::fromImage(recv_img[index.row()]));
    }
}


void MainWindow::show_picture()
{
    Message pac_show_mes=recv_mes;
    recv_mes.data=DES_de(DES_key,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(DES_key,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,Vkey_n,rsa_to_server->e);                  //不要数字签名的话这一行去掉

    QByteArray recv_picture;
    QBuffer buffer(&recv_mes.data);
    buffer.open(QIODevice::ReadOnly);
    QDataStream in(&buffer);
    in>>recv_picture;
    buffer.close();
    QString show_package_str="收到的图片二进制信息：/n"+recv_picture.toHex();
    recv_pack_show(pac_show_mes,show_package_str,recv_mes.sign,DES_key);
    ui->label->setPixmap(QPixmap::fromImage(getImage(recv_picture)));
}


void MainWindow::Login_check(QString uid, QString upass)//登录请求
{
    //cout << "login" << endl;
    id = uid;
    pwd = upass;
    QString sql = "SELECT * FROM user WHERE (uid=" + id + " AND upass=\"" + upass + "\")";
    QByteArray qbt_sql = sql.toUtf8();
    //qbt_sql = QByteArray::fromHex(qbt_sql);

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out << qbt_sql;
    buffer.close();

    login_data=data;
    Kerberos(uid.toInt());
    //数字签名DES加密
    //if (!judge) cout << "failed to send" << endl;
    //else cout << "success to send" << endl;
}

void MainWindow::Login_confirm()//登录确认
{
    //收包处理
    Message pac_show_mes=recv_mes;
    recv_mes.data=DES_de(DES_key,recv_mes.data);
    //res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(DES_key,recv_mes.sign);
    //不要数字签名的话这一行去掉，DES的解密，res为message类型，res.data为message的data部分
    sign_judge(recv_mes.data,recv_mes.sign,Vkey_n,rsa_to_server->e);
    //不要数字签名的话这一行去掉

    bool login;
    QBuffer buf(&recv_mes.data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
    in>>login;
    QString show_package_str="登录成功返回信息，0为失败，1为正确："+QString::number(login);
    recv_pack_show(pac_show_mes,show_package_str,recv_mes.sign,DES_key);
    buf.close();
    if(login)
    {
        ui->label_3->setText(id);
        this->show();
        wlogin->hide();
    }
    else
    {
        qDebug()<<"login failed";
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
            QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
            QVector<QString> pac_show_vec=package_message_noencrypt(65,4,ctoasSend,socket);
            QString show_det="客户发送给AS的获取票据许可票据请求报文：  IDc:"+QString::number(idc)+"   IDtgs:"+QString::number(ctoas.IDtgs)+"   TS1:"+ctoas.TS1;
            pac_show_vec[7]=show_det;
            send_pack_show_des(pac_show_vec);
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
     Message pac_show_mes=recv_mes;

     QBuffer as_ticketbuf(&recv_mes.data);
     as_ticketbuf.open(QIODevice::ReadOnly);
     QDataStream as_ticketin(&as_ticketbuf);
     char *asencrypt;char* ticket_encrypt;
     as_ticketin>>asencrypt>>ticket_encrypt;

     //****查一下本人的密钥

     switch(g_allshare.IDc)
     {
      case 100001:
         g_allshare.mykey_n=RSA_n;
         g_allshare.mykey_d=RSA_d;
         break;
     }

     //****astoc 解密
     char* asdecrypt=decrypt(asencrypt,g_allshare.mykey_n,g_allshare.mykey_d);
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
     socket->disconnectFromHost();
     socket->waitForDisconnected();

     QString show_data=QString("AS发送给C的报文：\n Ktgs为：%1 \n IDtgs为：%2 TS2为：%3 Lifetime2为：%4 \n Tickect_tgs为：%5").arg(QString(astocnew.Key_c_tgs.toHex())).arg(astocnew.IDtgs)
                  .arg(astocnew.TS2).arg(astocnew.lifetime).arg(QString(QByteArray(ticket_encrypt).toHex()));
     recv_pack_show(pac_show_mes,show_data,"0",QByteArray(g_allshare.mykey_d).toHex());
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

    QString show_det= QString("C发送给TGS的发送服务许可票据请求报文：IDv为%1 \n Ticket_tgs为：%2 \n Authenticator为 %3 \n 具体有IDc:%4  TS3:%5").arg(g_allshare.IDv)
                  .arg(QString(QByteArray(ticket_encrypt).toHex())).arg(QString(QByteArray(authbyte_en).toHex())).arg(auth.IDc).arg(auth.TS);
     //**** 包装报文
     QByteArray ctotgsSend;
     QBuffer ctotgsbuffer(&ctotgsSend);
     ctotgsbuffer.open(QIODevice::WriteOnly);
     QDataStream ctotgsout(&ctotgsbuffer);
     ctotgsout<<g_allshare.IDv<<ticket_encrypt<<authbyte_en;
     ctotgsbuffer.close();

     socket=new QTcpSocket;
         socket->connectToHost("192.168.22.17",6667);
         if(socket->waitForConnected(3000))
         {
             QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
             QVector<QString> pac_show_vec=package_message_noencrypt(65,5,ctotgsSend,socket);

             pac_show_vec[7]=show_det;
             send_pack_show_des(pac_show_vec);
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
     Message pac_show_mes=recv_mes;
     QByteArray rectgs=DES_de(g_allshare.Key_c_tgs,recv_mes.data);

     QBuffer tgstocbuf(&rectgs);
     tgstocbuf.open(QIODevice::ReadOnly);
     QDataStream tgstocin(&tgstocbuf);
     TGStoC tgstoc;
     tgstocin>>tgstoc.IDv>>tgstoc.Kcv>>tgstoc.TS4>>tgstoc.m_ticket_v;

     g_allshare.Key_c_v=tgstoc.Kcv;

     socket->disconnectFromHost();
     socket->waitForDisconnected();

     QString show_data=QString("TGS发送给C的报文：IDv为： %1 \nKcv为： %2 \nTS4为： %3\nTicket_v为：%4").arg(tgstoc.IDv)
             .arg(QString(tgstoc.Kcv.toHex())).arg(tgstoc.TS4).arg(QString(QByteArray(tgstoc.m_ticket_v).toHex()));
     recv_pack_show(pac_show_mes,show_data,"0",g_allshare.Key_c_tgs);

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

     QString show_det=QString("C发送给V的报文： Ticket_v为： %1\nAuthenticator为: %2 具体有IDc:%3  TS5:%4").arg(QString(QByteArray(tgstoc.m_ticket_v).toHex()))
             .arg(QString(authbyte_en.toHex())).arg(auth.IDc).arg(auth.TS);
     //**** 包装报文
     QByteArray ctotgsSend;
     QBuffer ctotgsbuffer(&ctotgsSend);
     ctotgsbuffer.open(QIODevice::WriteOnly);
     QDataStream ctotgsout(&ctotgsbuffer);
     ctotgsout<<tgstoc.m_ticket_v<<authbyte_en;
     ctotgsbuffer.close();

     socket=new QTcpSocket;
     socket->connectToHost("192.168.22.116",6668);
         if(socket->waitForConnected(3000))
         {
             QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);
             QVector<QString> pac_show_vec=package_message_noencrypt(65,6,ctotgsSend,socket);
             pac_show_vec[7]=show_det;
             send_pack_show_des(pac_show_vec);
         }
         else
         {
             socket->disconnectFromHost();
             qDebug()<<"连接失败";
             socket->waitForDisconnected();
         }
      g_allshare.socket=socket;

}

void MainWindow::C_handel(){
    //获取到了message,解析message中的内容
     //des解密
     Message pac_show_mes=recv_mes;
     QByteArray recv=DES_de(g_allshare.Key_c_v,recv_mes.data);
     //recv_pack_show(pac_show_mes,recv,"0",g_allshare.Key_c_v);
     QBuffer vtocbuf(&recv);
     vtocbuf.open(QIODevice::ReadOnly);
     QDataStream vtocin(&vtocbuf);
     VtoC vtoc;
     vtocin>>vtoc.TS5;
     DES_key=g_allshare.Key_c_v;

     QString show_data=QString("V发送给C的报文： TS5+1为：%1").arg(vtoc.TS5);
     recv_pack_show(pac_show_mes,show_data,"0",g_allshare.Key_c_v);
     QVector<QString> pac_show_vec = package_message_DES(66, 1, login_data, socket, DES_key, rsa_to_server->n, rsa_to_server->d);
     QString show_det="登录请求 SELECT * FROM user WHERE (uid=" + id + " AND upass=\"" + pwd + "\")";
     pac_show_vec[7]=show_det;
     send_pack_show_des(pac_show_vec);

}


void MainWindow::send_pack_show_des(QVector<QString> need_data)
{
    QStandardItem *item;
    for(int j=0;j<6;j++)
    {
        item=new QStandardItem(need_data[j]);
        capture_window->model->setItem(capture_window->now_row,j,item);
    }
    QVector<QString> detail_data;
    detail_data.push_back(need_data[6]);
    detail_data.push_back(need_data[7]);
    detail_data.push_back(need_data[8]);
    capture_window->detailed_info.push_back(detail_data);
    capture_window->now_row++;
    capture_window->update_tableview();
}

void MainWindow::on_pushButton_4_clicked()
{
    capture_window->show();
//    QVector<QString>temp;
//    temp.push_back("红烧牛肉面");
//    temp.push_back("5");
//    temp.push_back("5");
//    temp.push_back("5");
//    under_order.push_back(temp);
//    //在这上面的是缓存的初始化，因为这里没有缓存，我自己编了个，under_order变量是缓存本体，为QVector<QVector<string>>

//    QVector<QString> select_sql;
//    QVector<QString> update_sql;
//    QVector<QString> record_sql;
//    QVector<QString> delete_sql;
//    QString sel_sql="select Gnum from good where Gname='%1'";
//    QString upd_sql="update good set Gnum=Gnum - %1 where Gname='%2'";
//    QString inv_sql="insert into sale(Mid,Gname,Anum,Atime) values(%1,'%2',%3,'%4')";
//    QString del_cart=QString("delete from cart where Uid=%1").arg(id);
//    //这三行是提供sql语句模板，逻辑是，先查询商品表，比对数量是否正确，然后再更新商品表数量，最后添加销售记录，如果有购物车表的话，需要再加一条语句，就是删除购物车表项

//    QDateTime dateTime= QDateTime::currentDateTime();
//    QString date_str = dateTime .toString("yyyy-MM-dd hh:mm:ss");

//    //这下面是根据缓存生成对应的sql语句
//    for(int i=0;i<under_order.size();i++)
//    {
//        QString sel=sel_sql.arg(under_order[i][0]);
//        QString upd=upd_sql.arg(under_order[i][1]).arg(under_order[i][0]);
//        QString inv=inv_sql.arg(id).arg(under_order[i][0]).arg(under_order[i][1]).arg(date_str);
//        //QString del=del_sql.arg(under_order[i][0]).arg(id);
//        select_sql.push_back(sel);
//        update_sql.push_back(upd);
//        record_sql.push_back(inv);
//       // delete_sql.push_back(del);
//    }
//    QByteArray send_data;
//    QBuffer buffer(&send_data);
//    buffer.open(QIODevice::WriteOnly);
//    QDataStream out(&buffer);
//    //发送缓存加sql语句
//    out<<under_order<<select_sql<<update_sql<<record_sql<<del_cart;
//    int i=65;
//    int y=11;

//    QVector<QString> pac_show_vec = package_message_DES(i,y,send_data,socket,DES_key,rsa_to_server->n,rsa_to_server->d);//数字签名DES加密
}

void MainWindow::recv_pack_show(Message mes,QString data,QByteArray sign,QByteArray key)
{
    QVector<QString> recv_show_pac;
    QString dst_ip="";
    QString dst_src="";
    for(int i=0;i<4;i++)
    {
        //qDebug()<<(unsigned int)mes.des_ip[i];
        dst_ip+=QString::number((unsigned int)mes.des_ip[i]);
        dst_src+=QString::number((unsigned int)mes.des_src[i]);
        if(i!=3)
        {
            dst_ip+=".";
            dst_src+=".";
        }
    }
    recv_show_pac.push_back(dst_ip);
    recv_show_pac.push_back(dst_src);
    recv_show_pac.push_back(QString::number(int(recv_mes.message_type)));
    recv_show_pac.push_back(QString::number(int(recv_mes.field_type)));

    if(sign!="0")
         recv_show_pac.push_back(sign.toHex());
    else
        recv_show_pac.push_back(sign);
    recv_show_pac.push_back("nothing");
    recv_show_pac.push_back(mes.data.toHex());
    recv_show_pac.push_back(data);

    if(key!="0")
         recv_show_pac.push_back(key.toHex());
    else
        recv_show_pac.push_back(key);


    send_pack_show_des(recv_show_pac);
}


void MainWindow::order_handel()//下单反馈报文接包处理
{
    bool sucess;
    recv_mes.data=DES_de(DES_key,recv_mes.data);//res的data存放了数字签名和des的加密后的整体，所以解密的时候需要分开，直接这么调用就可以了
    recv_mes.sign=DES_de(DES_key,recv_mes.sign);   //不要数字签名这块去掉，DES的解密，res为message类型，res.data为message的data部分
    bool judge=sign_judge(recv_mes.data,recv_mes.sign,Vkey_n,rsa_to_server->e);                  //不要数字签名的话这一行去掉
    QBuffer buffer(&recv_mes.data);
    buffer.open(QIODevice::ReadOnly);
    QDataStream in(&buffer);
    in>>sucess;


    if(sucess==false)//如果下单失败，提醒用户，并且更新缓存，购物车这里不用更新缓存，应该是更新购物车表，并且根据购物车表更新缓存
    {
        //under_order.clear();
        //in>>under_order;
        QMessageBox::question(this,"错误","下单失败，可能商品已经被其他人买走，已经帮你更新最新的订单",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes);
    }
    else//提醒用户成功下单
    {
        QMessageBox::question(this,"成功","下单成功",QMessageBox::Yes | QMessageBox::No , QMessageBox::Yes);
    }
    buffer.close();
}


