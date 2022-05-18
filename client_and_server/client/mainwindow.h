#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QBuffer>
#include <DES.h>
#include <string>
#include <iostream>
#include <QVector>
#include <QApplication>
#include "homepage.h"
#include "wlogin.h"
#include "wgood.h"
#include "wtrolley.h"
#include "wuser.h"
#include "network.h"
#include "imagehandle.h"
using namespace std;

struct test {
    int a;
    QByteArray data;
};

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QTcpSocket* socket = new QTcpSocket();
    key_pair* p = new key_pair();//�Լ�����Կ
    QByteArray m_buffer;
    Message recv_mes;
    QByteArray DES_key;
    void message_handel();//�����յ��ı��ģ���ִ����Ӧ�Ĳ���
    //QMainWindow* getMainWindow();

private slots:

    void Login_check(QString, QString);//��¼

    void Login_confirm();//�����¼����

    void Get_goods(int start,int end);//��ѯ��Ʒ��ָ��λ��

    void Show_goods();//��ʾ��Ʒ��ѯ���

    void Refresh_goods(int);//ˢ����Ʒ��

    void socket_Read_Data();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void Transport_goods(QVector<QVector<QString>>,QVector<QByteArray>);

private:
    QString id, pwd;
    Ui::MainWindow* ui;
    Homepage* home;
    WLogin* wlogin = new WLogin(this);
    WGood* wgood;
    WTrolley* wtrollry;
    WUser* wuser;
    QImage* head_picture;
    QImage* good_btn_pic;
    int goods_loacte=0;
};
#endif // MAINWINDOW_H
