#include "network.h"
#include<QNetworkInterface>
#include<QDataStream>
#include<QBuffer>
QString getMyIpString()
{
    QString ip_address;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses(); // 获取所有ip
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {

        QHostAddress ipAddr = ipAddressesList.at(i);
        if ((ipAddr.protocol() == QAbstractSocket::IPv4Protocol))// 筛选出ipv4
        {
            qDebug() << "----ipv4: " << ipAddr.toString();
            if (!ipAddr.toString().startsWith("169"))// 过滤掉网卡，路由器等的ip
            {
                ip_address = ipAddr.toString();
                break;
            }


        }
    }
    if (ip_address.isEmpty())
        ip_address = QHostAddress(QHostAddress::LocalHost).toString();
    return ip_address;
}

QVector<QString> package_message(char message_type,char field_type,QByteArray  messge,QTcpSocket *socket,char * n, int e,char *sign_n,char *sign_d)
{
    Message pac_mes;
    QVector<QString> return_mes;
    QString src_ip=socket->localAddress().toString();
    QString dst_ip=socket->peerAddress().toString();

    return_mes.push_back(dst_ip);
    return_mes.push_back(src_ip);
    return_mes.push_back(QString::number(int(message_type)));
    return_mes.push_back(QString::number(int(field_type)));
    //return_mes.push_back("nothing");

    pac_mes.message_length=messge.length();
    pac_mes.message_type=message_type;
    pac_mes.field_type=field_type;

    QStringList list=src_ip.split(".");

    int i=0;
    for(auto & str : list)//切分源IP
    {
        pac_mes.des_src[i]=str.toUInt();
        i++;
    }

    list=dst_ip.split(".");
    i=0;
    for(auto & str : list)//切分目的IP
    {
        pac_mes.des_ip[i]=str.toUInt();
        i++;
    }



    QByteArray rsa_f=messge;
    rsa_f=rsa_f.toHex();
    rsa_f.insert(0,QByteArray("1"));



    QByteArray rsa_begin(encrypt(rsa_f.constData(),n,e));
    if(sign_n==nullptr||sign_d==nullptr)
    {
    pac_mes.sign="0";
    pac_mes.sign_length=pac_mes.sign.length();

    return_mes.push_back("0");

    }
    else
    {
        QByteArray sign=sign_create(rsa_f,sign_n,sign_d);

        return_mes.push_back(QCryptographicHash::hash(rsa_f, QCryptographicHash::Md5).toHex());

        QByteArray rsa_sign(encrypt(sign.constData(),n,e));
        pac_mes.sign=rsa_sign;
        pac_mes.sign_length=rsa_sign.length();
    }

    return_mes.push_back("nothing");



    return_mes.push_back(rsa_begin.toHex());
    return_mes.push_back(messge.toHex());
    return_mes.push_back(n);

    pac_mes.data=rsa_begin;
    pac_mes.message_length=rsa_begin.length();


    int num=send_message(socket,pac_mes);

    return return_mes;
}

QVector<QString> package_message_noencrypt(char message_type,char field_type,QByteArray  messge,QTcpSocket *socket)
{
    Message pac_mes;
    QVector<QString> return_mes;

    QString src_ip=socket->localAddress().toString();
    QString dst_ip=socket->peerAddress().toString();
    pac_mes.message_length=messge.length();
    pac_mes.message_type=message_type;
    pac_mes.field_type=field_type;


    return_mes.push_back(dst_ip);
    return_mes.push_back(src_ip);
    return_mes.push_back(QString::number(int(message_type)));
    return_mes.push_back(QString::number(int(field_type)));


    QStringList list=src_ip.split(".");

    int i=0;
    for(auto & str : list)//切分源IP
    {
        pac_mes.des_src[i]=str.toUInt();
        i++;
    }

    list=dst_ip.split(".");
    i=0;
    for(auto & str : list)//切分目的IP
    {
        pac_mes.des_ip[i]=str.toUInt();
        i++;
    }

    pac_mes.data=messge;
    pac_mes.sign="0";
    pac_mes.sign_length=pac_mes.sign.length();
    pac_mes.message_length=pac_mes.data.length();

    int num=send_message(socket,pac_mes);

    return_mes.push_back("0");
    return_mes.push_back("nothing");
    return_mes.push_back(messge.toHex());
    return_mes.push_back(messge.toHex());
    return_mes.push_back("0");

    return return_mes;
}

QVector<QString> package_message_DES(char message_type,char field_type,QByteArray  messge,QTcpSocket *socket,QByteArray DES_key,char *sign_n,char *sign_d)
{
    Message pac_mes;

    QVector<QString> return_mes;


    QString src_ip=socket->localAddress().toString();
    QString dst_ip=socket->peerAddress().toString();
    pac_mes.message_length=messge.length();
    pac_mes.message_type=message_type;
    pac_mes.field_type=field_type;

    return_mes.push_back(dst_ip);
    return_mes.push_back(src_ip);
    return_mes.push_back(QString::number(int(message_type)));
    return_mes.push_back(QString::number(int(field_type)));

    QStringList list=src_ip.split(".");

    int i=0;
    for(auto & str : list)//切分源IP
    {
        pac_mes.des_src[i]=str.toUInt();
        i++;
    }

    list=dst_ip.split(".");
    i=0;
    for(auto & str : list)//切分目的IP
    {
        pac_mes.des_ip[i]=str.toUInt();
        i++;
    }



    QByteArray rsa_f=messge;
    //rsa_f=rsa_f.toHex();
    //rsa_f.insert(0,QByteArray("1"));


    //qDebug()<<"res"<<rsa_f.toHex();
    QByteArray rsa_begin(DES_en(DES_key,rsa_f));
    QByteArray c(DES_de(DES_key,rsa_begin));
    //qDebug()<<"res"<<c.toHex();
    if(sign_n==nullptr||sign_d==nullptr)
    {
    pac_mes.sign="0";
    pac_mes.sign_length=pac_mes.sign.length();

    return_mes.push_back("0");
    }
    else
    {
        QByteArray sign=sign_create(rsa_f,sign_n,sign_d);
        return_mes.push_back(QCryptographicHash::hash(rsa_f, QCryptographicHash::Md5).toHex());
        QByteArray rsa_sign(DES_en(DES_key,sign));
        pac_mes.sign=rsa_sign;
        //qDebug()<<"res"<<sign.toHex();
        pac_mes.sign_length=rsa_sign.length();
    }


    pac_mes.data=rsa_begin;
    pac_mes.message_length=rsa_begin.length();



    int num=send_message(socket,pac_mes);

    return_mes.push_back("nothing");
    return_mes.push_back(rsa_begin.toHex());
    return_mes.push_back(messge.toHex());
    return_mes.push_back(DES_key.toHex());

    return return_mes;
}





int send_message(QTcpSocket *socket,Message message)
{
    QByteArray m_data_block;
    QDataStream send_procedure(&m_data_block, QIODevice::WriteOnly);
    send_procedure.setVersion(QDataStream::Qt_5_12);
    mes_len msg;
    Mes header(message);
    msg.message_length=sizeof(header);

    send_procedure<<msg.message_length;
    //qDebug()<<m_data_block.length();

    QByteArray data2;
    data2.append((char *)&header, sizeof(header));

    send_procedure<<data2;
    //qDebug()<<data2.length()<<m_data_block.length();


    //qDebug()<<message.message_length;

    QByteArray data3(message.data);
    data3.append(message.sign);

    send_procedure<<data3;
    //qDebug()<<data3.length()<<m_data_block.length();
    socket->write(m_data_block);
    socket->waitForBytesWritten();
    return 0;
}




Message receive_message(QTcpSocket *socket,char * n, char * d,char * sign_n, int sign_e)
{
    //socket->waitForReadyRead();
    QByteArray t=socket->read(4);

    mes_len *msg1=(mes_len*)t.data();
    //socket->waitForReadyRead();
    QByteArray t1=socket->read(msg1->message_length);
    Mes *header=(Mes *)t1.data();
    //qDebug()<<int(header->field_type);
    //socket->waitForReadyRead();
    QByteArray t2=socket->read((header->message_length+header->sign_length));
    QString te=QString(t2.left(header->message_length));
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

    res.data=decrypt(t2.left(header->message_length).constData(),n,d);
    res.sign=decrypt(t2.right(header->sign_length).constData(),n,d);
    if(sign_n!=nullptr&&sign_e!=0)
    {
        bool judge=sign_judge(res.data,res.sign,sign_n,sign_e);
        //qDebug()<<judge;
    }
    res.data.remove(0,1);
    res.data=QByteArray::fromHex(res.data);



    return res;
}

Message receive_message_nodecrypt(QTcpSocket *socket)
{
    socket->waitForReadyRead();
    QByteArray t=socket->read(4);

    mes_len *msg1=(mes_len*)t.data();
    socket->waitForReadyRead();
    QByteArray t1=socket->read(msg1->message_length);
    Mes *header=(Mes *)t1.data();
    //qDebug()<<int(header->field_type);
    QByteArray t2=socket->read((header->message_length+header->sign_length));
    QString te=QString(t2.left(header->message_length));
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
    //res.data=decrypt(t2.left(header->message_length).constData(),n,d);
    //res.sign=decrypt(t2.right(header->sign_length).constData(),n,d);
    //bool judge=sign_judge(res.data,res.sign,sign_n,sign_e);
    //qDebug()<<judge;
    return res;
}



