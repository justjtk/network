#include "dialog0.h"
#include "ui_dialog0.h"
#include<QFileDialog>
#include<QMessageBox>
Dialog0::Dialog0(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog0)
{
    ui->setupUi(this);
}

Dialog0::~Dialog0()
{
    delete ui;
}

void Dialog0::on_buttonBox_accepted()
{

   data.push_back(ui->lineEdit->text());
   data.push_back(ui->lineEdit_2->text());
   data.push_back(ui->lineEdit_3->text());
   data.push_back(ui->lineEdit_4->text());
   data.push_back(ui->lineEdit_5->text());
}

void Dialog0::on_pushButton_clicked()
{

    QString filename=QFileDialog::getOpenFileName(this,tr("选择图像"),"",tr("Images (*.jpg)"));
        if(filename.isEmpty())
            return;
        else
        {
            QImage img1;
            if(!(img1.load(filename))) //加载图像
            {
                QMessageBox::information(this, tr("打开图像失败"),tr("打开图像失败!"));
                return;
            }
            img=img1;
            ui->label_6->setPixmap(QPixmap::fromImage(img.scaled(ui->label_6->size())));
        }
}

