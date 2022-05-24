#include "selection.h"
#include "ui_selection.h"

selection::selection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::selection)
{
    ui->setupUi(this);
}

selection::~selection()
{
    delete ui;
}

void selection::on_buttonBox_accepted()
{
    str=ui->comboBox->currentText();
}
