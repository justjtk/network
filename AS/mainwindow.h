#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"network.h"
#include <QMainWindow>
#include<QTime>
#include<QTcpServer>
#include<QTcpSocket>
#include <QProcess>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QTcpServer *TCPServer;
    QTcpSocket *socket;
    QByteArray m_buffer;
    key_pair * p=new key_pair();//自己的密钥
    Message recv_mes;

    void AS_handel();
    ~MainWindow();
private slots:
   void socket_Read_Data();
private:
    Ui::MainWindow *ui;
};

struct CtoAS{
    int IDc;
    int IDtgs;
    QString TS1;
};
struct Ticket {
QByteArray Key_cn;//c与tgs的des密钥
int IDc;
int ID;
QString TS;
int lifetime;//hour
};

struct AStoC{
QByteArray Key_c_tgs;//c与tgs的des密钥
int IDtgs;
QString TS2;
int lifetime;
//char* m_ticket_tgs;//放着加密的ticket
};
#endif // MAINWINDOW_H
