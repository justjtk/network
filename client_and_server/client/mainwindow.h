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
    key_pair* p = new key_pair();//自己的密钥
    QByteArray m_buffer;
    Message recv_mes;
    QByteArray DES_key;
    void message_handel();//处理收到的报文，并执行相应的操作
    //QMainWindow* getMainWindow();

private slots:

    void Login_check(QString, QString);//登录

    void Login_confirm();//处理登录反馈

    void Get_goods(int start,int end);//查询商品表指定位置

    void Show_goods();//显示商品查询结果

    void Refresh_goods(int);//刷新商品表

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
