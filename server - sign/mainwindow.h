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
#include<QStandardItemModel>
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
    int Client_num;
    key_pair * p=new key_pair();//自己的密钥
    QStandardItemModel good_model;
    QSqlDatabase db;
    QSqlTableModel* model;
    QSqlQuery* query;

    void connect_mysql();
    bool modify_db(QString txt);//增删改

    QSqlQuery query_db(QString txt) ;//查询

    QSqlTableModel* model_db(QString txt) ;//查询

private slots:
    void server_New_Connect();
    void socket_Read_Data();
    void socket_Disconnected();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
