#include "wuser.h"
#include "ui_wuser.h"

WUser::WUser(QString uid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WUser)
{
    ui->setupUi(this);
    id=uid;
    ui->statusbar->hide();//隐藏状态栏
}

WUser::~WUser()
{
    delete ui;
}

void WUser::on_pushButton_2_clicked()
{
    wmodify=new WModify(id);
    wmodify->show();
}
