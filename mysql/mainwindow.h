#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSqlTableModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include<QString>
#include<QVector>
#include"dialog0.h"
#include"dialog1.h"
#include"dialog2.h"
#include"dialog3.h"
#include"dialog4.h"
#include"dialog5.h"
#include"selection.h"
#include"sign.h"
#include"network.h"
#include<QStandardItemModel>
#include<QBuffer>
#include"imagehandle.h"
#include"wlogin.h"
#include"kerberos.h"
#include"package_show.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;
    bool judgetable[6]={false};
    int tablenum[6]={5,4,4,4,8,9};
    QString tableid[6]={"good","cart","manager","user","vip","sale"};
    QVector<QString>tablename[6];
    //QSqlTableModel *model;
    QSqlTableModel * model;
    QString filter="";
    QStandardItemModel* good_model;
    QStandardItemModel* all_model;
    QStandardItemModel* search_model;
    key_pair * rsa_to_server=new key_pair();//服务器的密钥

    QVector<QImage> recv_img;


    Message recv_mes;
    QByteArray m_buffer;
    Pubdata g_allshare;
    //QString id;
    QTcpSocket* socket=new QTcpSocket();

    QByteArray login_data;
    QByteArray DES_key;

    QVector<QVector<QString>> pack_show_data;//抓包函数，每一行按顺序分别是，目的IP,源IP,报文类型，字段类型，数字签名，补充说明，报文内容（加密），解密内容（解密），密钥；
    long pack_show_num=0;//记录抓包报文的总数
    void send_pack_show_des(QVector<QString> need_data);
    package_show *capture_window=new package_show();
    void recv_pack_show(Message mes,QString data,QByteArray sign="0",QByteArray key="0");



    void message_handel();//处理收到的报文，并执行相应的操作
    void update_tableview();//接受服务端发送的图表数据，并且更新表格
    void connect_mysql();
    void changecombox();
    void showtable();
    void inittable();
    void ui_init();
    void show_picture();
    void Kerberos(int idc);
    void AS_handel();
    void TGS_handel();
    void C_handel();



    //------------- 测试--------------
    QVector<QVector<QString>> under_order;
    void order_handel();
private slots:
    void on_comboBox_currentIndexChanged(int index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void socket_Read_Data();
    void on_tableView_clicked(const QModelIndex &index);

    void Login_check(QString, QString);//登录

    void Login_confirm();//处理登录反馈
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    WLogin *wlogin=new WLogin(this);
    QString id, pwd;
};

#endif // MAINWINDOW_H
