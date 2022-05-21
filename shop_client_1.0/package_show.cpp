#include "package_show.h"
#include "ui_package_show.h"
#include<QTextCodec>
package_show::package_show(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::package_show)
{
    ui->setupUi(this);
    QPalette label_palette;
    QTextCodec *codec = QTextCodec::codecForName("GBK");



    label_palette.setColor(QPalette::Background, QColor("white"));

    ui->label->setAutoFillBackground(true);
    ui->label->setPalette(label_palette);
    ui->label_2->setAutoFillBackground(true);
    ui->label_2->setPalette(label_palette);
    ui->label_3->setAutoFillBackground(true);
    ui->label_3->setPalette(label_palette);
    model = new QStandardItemModel();

    model->setColumnCount(6);

    model->setHeaderData(0,Qt::Horizontal,QStringLiteral("目的IP"));
    model->setHeaderData(1,Qt::Horizontal,QStringLiteral("源IP"));
    model->setHeaderData(2,Qt::Horizontal,QStringLiteral("报文类型（子系统）"));
    model->setHeaderData(3,Qt::Horizontal,QStringLiteral("字段类型"));
    model->setHeaderData(4,Qt::Horizontal,QStringLiteral("数字签名"));
    model->setHeaderData(5,Qt::Horizontal,QStringLiteral("补充说明"));
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,200);
    ui->tableView->setColumnWidth(3,200);
    ui->tableView->setColumnWidth(4,300);
    ui->tableView->setColumnWidth(5,500);
}


package_show::~package_show()
{
    delete ui;
}


void package_show::update_tableview()
{
    ui->tableView->setModel(model);
    ui->tableView->setColumnWidth(0,200);
    ui->tableView->setColumnWidth(1,200);
    ui->tableView->setColumnWidth(2,200);
    ui->tableView->setColumnWidth(3,200);
    ui->tableView->setColumnWidth(4,300);
    ui->tableView->setColumnWidth(5,500);

}

void package_show::on_tableView_clicked(const QModelIndex &index)
{
    int choose_row=ui->tableView->currentIndex().row();
    ui->textEdit->clear();
    ui->textEdit_2->clear();
    ui->textEdit_3->clear();
    ui->textEdit->append(detailed_info[choose_row][0]);
    ui->textEdit_2->append(detailed_info[choose_row][1]);
    ui->textEdit_3->append(detailed_info[choose_row][2]);
}

