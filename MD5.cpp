#include"MD5.h"

QByteArray*  sign_create(QByteArray *data ,char * n,int e)//数字签名生成与加密,并且拼接到正文后面
{
    QByteArray hash = QCryptographicHash::hash(*data, QCryptographicHash::Md5);
    QString strMD5 = hash.toHex();
    char *ch = strMD5.toLatin1().data();
    qDebug()<<ch;
    char *md5_encrypt=encrypt(ch,n,e);
    QByteArray* res=new QByteArray();
    res->append(md5_encrypt);
    //data->append(md5_encrypt);
    return res;
}
bool sign_judge(QByteArray *data,QByteArray *sign,char * n,char * d)//数字签名的校验
{
    QByteArray hash = QCryptographicHash::hash(*data, QCryptographicHash::Md5);
    QString strMD5 = hash.toHex();
    qDebug()<<strMD5;
    char *ch;
    ch = sign->data();
    char *md5_decrypt=decrypt(ch,n,d);
    qDebug()<<md5_decrypt;
    QString strMD5_1=QString(md5_decrypt);
    if(strMD5==strMD5_1)
        return true;
    else return false;
}
