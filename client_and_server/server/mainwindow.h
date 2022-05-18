#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"gmp.h"
//#include"MD5.h"
#include<QDebug>
#include<iostream>
#include<QTcpServer>
#include"network.h"
#include<QBuffer>
#include<QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSqlRecord>
#include <QVector>
#include <DES.h>
#include <QVector>
#include "imagehandle.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct test{
    int a;
    QByteArray data;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QTcpServer* server;
    QTcpSocket* socket;
    QList<QTcpSocket*> TcpSockets_List;
    int Client_num=0;
    key_pair * p=new key_pair();//自己的密钥
    QStandardItemModel* good_model;

    QVector<QVector<QString>> send_table;//发送给用户的数据库表格数据

    QSqlDatabase db;
    QSqlTableModel* model;
    QSqlQuery* query;

    QByteArray DES_key_to_client;//与client的DES密钥

    QByteArray m_buffer;//缓存，不要管

    Message recv_mes;//收到的报文

    void message_handel();//处理收到的报文，并执行相应的操作
    void connect_mysql();
    bool modify_db(QString txt);//增删改
    QSqlQuery query_db(QString txt) ;//查询
    QSqlTableModel* model_db(QString txt) ;//查询
    void sql_to_table();//sqltablemodel转QStandardItemModel

    //**********Leeee-客户端**********//
    void Login_Check();//登录认证
    void Inquire_goods();


private slots:
    void server_New_Connect();
    void socket_Read_Data();
    void socket_Disconnected();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
