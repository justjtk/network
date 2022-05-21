#ifndef MODIFYINF_H
#define MODIFYINF_H
#include"kerberos.h"
#include"network.h"
#include <QDialog>

namespace Ui {
class modifyinf;
}

class modifyinf : public QDialog
{
    Q_OBJECT

public:
    explicit modifyinf(Pubdata alldata,QImage img,QWidget *parent = nullptr);
    void deal_aftermod(Message recv_mes);
    bool ifmodsuccess=false;
    bool ifimgchange=false;
    QImage currentimg;
    QImage beforeimg;
    Pubdata g_alldata;
    ~modifyinf();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void Change_mwd_head(QImage);
    void Send_to_wsk1(QVector<QString>);

private:

    Ui::modifyinf *ui;
};

#endif // MODIFYINF_H
