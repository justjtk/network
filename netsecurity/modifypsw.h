#ifndef MODIFYPSW_H
#define MODIFYPSW_H
#include"kerberos.h"
#include"network.h"
#include <QDialog>

namespace Ui {
class modifypsw;
}

class modifypsw : public QDialog
{
    Q_OBJECT

public:
    explicit modifypsw(Pubdata alldata,QWidget *parent = nullptr);
    void deal_aftermod(Message recv_mes);
    Pubdata g_alldata;
    ~modifypsw();

private slots:
    void on_pushButton_clicked();

    void on_buttonBox_accepted();

private:
    Ui::modifypsw *ui;
};

#endif // MODIFYPSW_H
