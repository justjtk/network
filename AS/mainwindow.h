#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"network.h"
#include <QMainWindow>
#include<QTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
/*struct Message
{
    unsigned int message_length;//报文长度
    char message_type;//报文类型
    char field_type;//字段类型
    unsigned char des_ip[4]={0,0,0,0};//目的IP
    unsigned char des_src[4]={0,0,0,0};//源IP
    unsigned int sign_length;//数字签名长度
    QByteArray data;//数据内容
    QByteArray sign;//数字签名
};*/
struct CtoAS{
    int IDc;
    int IDtgs;
    QString TS1;
};
struct Ticket {
int Key_cn;//c与tgs的des密钥
int IDc;
int ID;
QString TS;
int lifetime;//hour
};

struct AStoC{
int Key_c_tgs;//c与tgs的des密钥
int IDtgs;
QString TS2;
int lifetime;
//char* m_ticket_tgs;//放着加密的ticket
};
#endif // MAINWINDOW_H
