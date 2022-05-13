#include "wmodify.h"
#include "ui_wmodify.h"

WModify::WModify(QString uid,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WModify)
{
    ui->setupUi(this);
    id=uid;
}

WModify::~WModify()
{
    delete ui;
}
