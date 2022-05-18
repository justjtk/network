#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QCoreApplication>



char RSA_n[] = "b8e1aa68799754e0e6aa176cf21cc352acad2a32513f07c651d9b3191e26adfdc0679b6f9c17000db180a20cbbfc1bb5c845aaabf60bb4bb512f6c8f91a5f54848d59e774c340128c898a21011d613bb7221bf0ce32c31b80b140101d54471479fc1559aada00a04a9f2b3fd773fbff864c1ae9fa52efdff39d3277d2cbb2f3";
char RSA_d[] = "59122f9d41e74cb745a9f0bb4631e150756cc00599eaf9fdebf52c3a0fb2a6e4b7cbb2b124cc57f440ee2e246074e78cbebe01a9f3525472627cac9ac69ae3fbf46d8efb38b0615e59e6ceca8f08a6f950e122bdcb1c5f01c06a30635a89f1ff77e4bbb0157a96caecce9eed92badccc2bf402516a2159564c326bf5ac01ef1";
char DES_KEY[] = "01010000010000000000010101010101010001000100000100000100000101000100010001010100010100010100010101000100000101010101010000010000";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusbar->hide();
    wlogin->show();
    wgood = new WGood(id,this);
    ui->scrollArea->setWidget(wgood);

    //��ȡ����ǰ����Ŀ¼
    //QString operation_path = QCoreApplication::applicationDirPath();
    //qDebug() << operation_path;

    connect(wlogin, SIGNAL(Send_uid_to_mwd(QString, QString)), this, SLOT(Login_check(QString, QString)));//��¼�ɹ���id
    connect(wgood,SIGNAL(Refresh_goods_list(int)),this,SLOT(Refresh_goods(int)));

    ui->statusbar->hide();//����״̬��
    delete ui->statusbar;//ɾ��״̬��

    p->n = RSA_n;
    p->d = RSA_d;
    DES_key = DES_KEY;
    p->e = 65537;
    DES_key = QByteArray::fromHex(DES_key);

    socket->connectToHost("127.0.0.1", 6666);

    if (socket->waitForConnected(3000))
    {
        //qDebug() << "connect ok";
        QObject::connect(socket, &QTcpSocket::readyRead, this, &MainWindow::socket_Read_Data);

        //*****���Ӳ��Դ��루34-51�У�*****//
        if (0)
        {
            //        test str;
            //        str.a=529;
            //        str.data="hello server,this is lcy!";

            //        QByteArray data;
            //        QBuffer buffer(&data);
            //        buffer.open(QIODevice::WriteOnly);
            //        QDataStream out(&buffer);
            //        out<<str.a<<str.data;
            //        buffer.close();

            //        int i=1;
            //        int y=2;
            //        bool judge=package_message_DES(i,y,data,socket,DES_key,p->n,p->d);//����ǩ��DES����
        }

    }
    else
    {
        socket->disconnectFromHost();
        qDebug() << "no connect";
        socket->waitForDisconnected();
    }

    //*****����ͼƬ���Դ��루61-72�У�*****//
    if (0)
    {
        QString filename(":/new/prefix1/head");
        if (!(head_picture->load(filename))) //����ͼ��
        {
            QMessageBox::information(this, tr("��ͼ��ʧ��"), tr("��ͼ��ʧ��"));
            delete head_picture;
            return;
        }
        ui->label_head->setPixmap(QPixmap::fromImage(*head_picture));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

//QMainWindow* MainWindow::getMainWindow()
//{
//    foreach (QWidget *w, qApp->topLevelWidgets())
//        if (QMainWindow* mainWin = qobject_cast<QMainWindow*>(w))
//            return mainWin;
//    return nullptr;
//}

void MainWindow::socket_Read_Data()
{

    QByteArray buffer = socket->readAll();
    m_buffer.append(buffer);
    int total_length = m_buffer.size();
    while (total_length)
    {
        QDataStream recv_data(m_buffer);
        recv_data.setVersion(QDataStream::Qt_5_12);
        int m_len = sizeof(mes_len);
        if (total_length < m_len)
            break;//��������
        //mes_len *msg1=(mes_len*)m_buffer.left(m_len).data();
        unsigned int he_len;
        recv_data >> he_len;
        //qDebug() << m_buffer.left(m_len).length();
        int head_len = m_len + he_len + 4;
        if (total_length < head_len)
            break;

        QByteArray t1;
        recv_data >> t1;
        Mes* header = (Mes*)t1.data();
        //Mes *header=(Mes *)m_buffer.mid(m_len,head_len).data();

        int all_len = head_len + header->message_length + header->sign_length + 4;

        if (total_length < all_len)
            break;

        QByteArray t2;
        recv_data >> t2;
        //QByteArray t2=m_buffer.mid(head_len,all_len);
        Message res;
        res.message_length = header->message_length;
        res.message_type = header->message_type;
        res.field_type = header->field_type;
        for (int i = 0; i < 4; i++)
        {
            res.des_ip[i] = header->des_ip[i];
            res.des_src[i] = header->des_src[i];
            res.sign_length = header->sign_length;
        }

        res.data = t2.left(header->message_length);
        res.sign = t2.right(header->sign_length);
        //����Ϊ���ܲ��һ�ԭ��������Ҫע�⣬��Ҫ������ѡ����ܷ����Լ���Կ�����У���Ҫ���ǽ�����Ҫ����remove��fromHex
        //����Ϊ���ܲ��һ�ԭ��������Ҫע�⣬��Ҫ������ѡ����ܷ����Լ���Կ�����У���Ҫ���ǽ�����Ҫ����remove��fromHex


        recv_mes = res;

        buffer = m_buffer.right(total_length - all_len);
        total_length = buffer.size();
        m_buffer = buffer;

        message_handel();//������

        //        res.sign=decrypt(res.sign.constData(),p->n,p->d);
        //        res.data=decrypt(res.data.constData(),p->n,p->d);    //RSA����,resΪmessage���ͣ�res.dataΪmessage��data����
        //        bool judge=sign_judge(res.data,res.sign,p->n,p->e);//��Ҫ����ǩ���Ļ���һ��ȥ��
        //        res.data.remove(0,1);                                                     //res��data���������ǩ����des�ļ��ܺ�����壬���Խ��ܵ�ʱ����Ҫ�ֿ���ֱ����ô���þͿ�����
        //        res.data=QByteArray::fromHex(res.data);                                   //���ܵ�ʱ��ֿ����ܣ����ҷֱ�浽����ǩ����data�Ĳ���


//        res.sign=DES_de(DES_key_to_client,res.sign);   //DES�Ľ��ܣ�resΪmessage���ͣ�res.dataΪmessage��data����

//        res.data=DES_de(DES_key_to_client,res.data);//res��data���������ǩ����des�ļ��ܺ�����壬���Խ��ܵ�ʱ����Ҫ�ֿ���ֱ����ô���þͿ�����
//        bool judge=sign_judge(res.data,res.sign,p->n,p->e);                  //��Ҫ����ǩ���Ļ���һ��ȥ��
//        qDebug()<<judge;



//        test str;
//        QBuffer buf(&recv_mes.data);
//        buf.open(QIODevice::ReadOnly);
//        QDataStream in(&buf);

//        in>>str.a>>str.data;
//        qDebug()<<str.data;
    }

}

void MainWindow::message_handel()//�����յ��ı��ģ���ִ����Ӧ�Ĳ���
{
    int message_type = int(recv_mes.message_type);//��������
    int field_type = int(recv_mes.field_type);//�ֶ�����
    switch (message_type)
    {
    case 0://�յ�������
    {
        switch (field_type)//��ⱨ������
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 1://�յ���ͨ�û�����
    {
        switch (field_type)
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 2://�յ�����Ա����
    {
        switch (field_type)
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 3://�յ�����������
    {
        switch (field_type)
        {
        case 0:
            break;
        case 1:
            break;
        case 2://������Ʒ��ѯ����
            Show_goods();//��ʾ��Ʒ��Ϣ
            break;
        }
        break;
    }
    case 4://�յ�AS����
    {
        switch (field_type)
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 5://�յ�tgs���ı���
    {
        switch (field_type)
        {
        case 0:
            break;
        case 1:
            break;
        }
        break;
    }
    case 67://�յ�����������
    {
        switch (field_type)
        {
        case 0:
            break;
        case 1:
            break;
        case 6://���յ�¼����
            Login_confirm();
            break;
        }
        break;
    }
    }
}

void MainWindow::on_pushButton_clicked()
{
    wgood = new WGood(id,this);
    ui->scrollArea->setWidget(wgood);
    goods_loacte-=6;
    Get_goods(goods_loacte,goods_loacte+6);
}

void MainWindow::on_pushButton_2_clicked()
{
    wtrollry = new WTrolley(id);
    ui->scrollArea->setWidget(wtrollry);
}

void MainWindow::on_pushButton_3_clicked()
{
    wuser = new WUser(id);
    ui->scrollArea->setWidget(wuser);
}

void MainWindow::Login_check(QString uid, QString upass)//��¼����
{
    //cout << "login" << endl;
    id = uid;
    pwd = upass;
    QString sql = "SELECT * FROM USER WHERE (uid=" + id + " AND upass=\"" + pwd + "\")";
    QByteArray qbt_sql = sql.toUtf8();
    //qbt_sql = QByteArray::fromHex(qbt_sql);

    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out << qbt_sql;
    buffer.close();
    bool judge = package_message_DES(65, 14, data, socket, DES_key, p->n, p->d);//����ǩ��DES����
    //if (!judge) cout << "failed to send" << endl;
    //else cout << "success to send" << endl;
}

void MainWindow::Login_confirm()//��¼ȷ��
{
    //�հ�����
    recv_mes.data=DES_de(DES_key,recv_mes.data);
    //res��data���������ǩ����des�ļ��ܺ�����壬���Խ��ܵ�ʱ����Ҫ�ֿ���ֱ����ô���þͿ�����
    recv_mes.sign=DES_de(DES_key,recv_mes.sign);
    //��Ҫ����ǩ���Ļ���һ��ȥ����DES�Ľ��ܣ�resΪmessage���ͣ�res.dataΪmessage��data����
    sign_judge(recv_mes.data,recv_mes.sign,p->n,p->e);
    //��Ҫ����ǩ���Ļ���һ��ȥ��
    bool login;
    QByteArray img;
    QBuffer buf(&recv_mes.data);
    buf.open(QIODevice::ReadOnly);
    QDataStream in(&buf);
    in>>login>>img;
    buf.close();
    if(login)
    {
        //qDebug()<<"login ok";
        ui->label_2->setText(id);
        QImage head_img=getImage(img);
        ui->label_head->setPixmap(QPixmap::fromImage(head_img));
        ui->label_head->setScaledContents(true);//����label
        this->show();
        wlogin->hide();
        Get_goods(goods_loacte,goods_loacte+6);//���ͻ�ȡ��Ʒ�������
    }
    else
    {
        qDebug()<<"login failed";
    }

}

void MainWindow::Get_goods(int start,int end)//������Ʒ��
{
    QString sql = "SELECT * FROM GOOD LIMIT "+QString::number(start)+","+QString::number(end)+";";
    QByteArray qbt_sql = sql.toUtf8();
    QByteArray data;
    QBuffer buffer(&data);
    buffer.open(QIODevice::WriteOnly);
    QDataStream out(&buffer);
    out << qbt_sql;
    buffer.close();
    bool judge = package_message_DES(65, 15, data, socket, DES_key, p->n, p->d);//����ǩ��DES����
    //if (!judge) cout << "failed to send" << endl;
    //else cout << "success to send" << endl;
    goods_loacte+=6;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!ע�⿼�ǳ��޵����
}

void MainWindow::Show_goods()//��ʾ��Ʒ��Ϣ
{
    //�հ�����
    recv_mes.data=DES_de(DES_key,recv_mes.data);
    //res��data���������ǩ����des�ļ��ܺ�����壬���Խ��ܵ�ʱ����Ҫ�ֿ���ֱ����ô���þͿ�����
    recv_mes.sign=DES_de(DES_key,recv_mes.sign);
    //��Ҫ����ǩ���Ļ���һ��ȥ����DES�Ľ��ܣ�resΪmessage���ͣ�res.dataΪmessage��data����
    sign_judge(recv_mes.data,recv_mes.sign,p->n,p->e);
    //��Ҫ����ǩ���Ļ���һ��ȥ��

    QVector<QVector<QString>> goods_infm;
    QVector<QByteArray> goods_img;
    QByteArray recv_img;
    QBuffer buf(&recv_mes.data);
    buf.open(QIODevice::ReadWrite);
    QDataStream in(&buf);
    buf.seek(1);
    in>>goods_infm>>goods_img;

    emit Transport_goods(goods_infm,goods_img);//�����ź�ʹ��Ʒҳ������ʾ


}

void MainWindow::Refresh_goods(int offset)
{
    qDebug()<<"Refresh";
    goods_loacte-=offset;
    Get_goods(goods_loacte,goods_loacte+6);
}





