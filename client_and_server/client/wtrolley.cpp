#include "wtrolley.h"
#include "ui_wtrolley.h"

WTrolley::WTrolley(QString uid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WTrolley)
{
    ui->setupUi(this);
    id=uid;
    ui->statusbar->hide();//隐藏状态栏
}

WTrolley::~WTrolley()
{
    delete ui;
}
