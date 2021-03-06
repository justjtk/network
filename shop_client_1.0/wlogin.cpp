#include "wlogin.h"
#include "ui_wlogin.h"
#include <QDebug>

WLogin::WLogin(QMainWindow *p, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WLogin)
{
    ui->setupUi(this);
    uii=ui;
    p_mwd=p;
    ui->label_error->hide();
}

WLogin::~WLogin()
{
    delete ui;
}

void WLogin::on_pushButton_clicked()
{
    id=ui->lineEdit->text();
    pwd=ui->lineEdit_2->text();

    QByteArray pswd;
    pswd.append(pwd);
    QByteArray hash = QCryptographicHash::hash(pswd, QCryptographicHash::Md5);
    QString strMD5 = hash.toHex();
    pwd=strMD5;
    Send_log_id();
    //p_mwd->show();
    //this->hide();
}

void WLogin::Send_log_id()
{
    emit Send_uid_to_mwd(id,pwd);
}


