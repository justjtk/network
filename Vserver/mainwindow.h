#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTcpServer>
#include <QMainWindow>
#include <QProcess>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
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
    Message recv_mes;
    QByteArray g_Key_cv;
    int g_idc;
    char* g_Ckey_n;

    void message_handel();
    void V_handel();
    void userinf_handel();
    void modinf_handel();
    void modpsw_handel();
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
struct CtoV{
   char* m_ticket_v;
   QByteArray authenticator;
};
struct VtoC{
   QString TS5;
};

#endif // MAINWINDOW_H
