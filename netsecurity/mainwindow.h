#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"network.h"
#include <QMainWindow>
#include<QTime>
#include <QProcess>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


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
struct VtoC{
   QString TS5;
};
struct Pubdata{
    QString TS1;
    QString TS5;
    int IDc;
    int IDv;
    QByteArray Key_c_tgs;
    QByteArray Key_c_v;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QTcpSocket *socket;
    QByteArray m_buffer;
    key_pair * p=new key_pair();//自己的密钥
    Message recv_mes;
    Pubdata g_allshare;

    void message_handel();
    void Kerberos(int idc);
    void AS_handel();
    void TGS_handel();
    void C_handel();
    ~MainWindow();
private slots:
   void socket_Read_Data();
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
