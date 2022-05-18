#ifndef WUSER_H
#define WUSER_H
#include <QTcpSocket>
#include <QMainWindow>
#include <string>
#include "modifyinf.h"
#include"modifypsw.h"
#include"network.h"
#include"kerberos.h"
using namespace std;

namespace Ui {
class WUser;
}

class WUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit WUser(Pubdata alldata,QWidget *parent = nullptr);
    void deal_initi(Message recv_mes);
    modifyinf * modifyinfs;
    modifypsw * modifypsws;
    ~WUser();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    //QString id;
    QImage img;
    Pubdata g_alldata;
    Ui::WUser *ui;

};

#endif // WUSER_H
