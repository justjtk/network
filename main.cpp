#include "mainwindow.h"

#include <QApplication>
#include"gmp.h"
#include"RSA.h"
#include<QDebug>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    key_pair * p = get_key_pair();
    qDebug()<<"n = "<<p->n<<endl;
    qDebug()<<"d = "<<p->d<<endl;
    qDebug()<<"e = "<<p->e<<endl;
    string buf="你好";
    string cipher_text = encrypt_str(buf, p->n, p->e);
    qDebug()<<"密文为"<<cipher_text.c_str()<<endl;
    string plain_text = decrypt_str(cipher_text, p->n, p->d);
    qDebug()<<""<<plain_text.c_str()<<endl;

    return a.exec();

}
