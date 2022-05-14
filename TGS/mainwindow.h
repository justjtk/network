#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTcpServer>
#include <QMainWindow>
#include"network.h"
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

    void TGS_handel();
    ~MainWindow();

private slots:
   void socket_Read_Data();
private:
    Ui::MainWindow *ui;
};
struct Ticket {
QByteArray Key_cn;//c与tgs的des密钥
int IDc;
int ID;
QString TS;
int lifetime;//hour
};
struct Authenticator{
    int IDc;
    QString TS;
};

struct CtoTGS{
    int IDv;
    char* m_ticket_tgs;
    QByteArray authenticator;
};

struct TGStoC{
    QByteArray Kcv;
    int IDv;
    QString TS4;
    char* m_ticket_v;
};
#endif // MAINWINDOW_H
