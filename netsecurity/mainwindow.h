#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"network.h"
#include"wuser.h"
#include <QMainWindow>
#include<QTime>
#include"kerberos.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    QTcpSocket *socket;
    QByteArray m_buffer;
    Message recv_mes;
    Pubdata g_allshare;
    WUser* myuser;

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
