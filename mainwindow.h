#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStandardItemModel>
#include"network.h"
#include<QBuffer>
#include<DES.h>
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
    QTcpSocket* socket=new QTcpSocket();
    key_pair * p=new key_pair();//自己的密钥
    QByteArray m_buffer;
    Message recv_mes;
    QByteArray DES_key;
    void message_handel();//处理收到的报文，并执行相应的操作
private slots:
    void socket_Read_Data();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
