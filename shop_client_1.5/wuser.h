#ifndef WUSER_H
#define WUSER_H
#include <QTcpSocket>
#include <QMainWindow>
#include <string>
#include "modifyinf.h"
#include "modifypsw.h"
#include "vipregist.h"
#include "network.h"
#include "kerberos.h"
#include "interface.h"
using namespace std;

namespace Ui {
class WUser;
}

class WUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit WUser(Pubdata alldata,QMainWindow *p,QWidget *parent = nullptr);
    void deal_initi(Message recv_mes);
    modifyinf * modifyinfs;
    modifypsw * modifypsws;
    VIPregist * vipregists;
    bool vip;
    void VIP_handel(Message recv_mes);
    ~WUser();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void Transmit_img(QImage);

    void on_pushButton_clicked();

signals:
    void Transmit_img_to_mwd(QImage);
    void Send_to_wsk(QVector<QString>);
    void Send_to_wsk_recv(Message,QString,QByteArray,QByteArray );
    void Send_pack_show_des_usr(QVector<QString> need_data);

private:
    //QString id;
    QImage img;
    Pubdata g_alldata;
    Ui::WUser *ui;
    QMainWindow *pmwd;

};

#endif // WUSER_H
