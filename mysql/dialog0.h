#ifndef DIALOG0_H
#define DIALOG0_H

#include <QDialog>
#include<QImage>
namespace Ui {
class Dialog0;
}

class Dialog0 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog0(QWidget *parent = nullptr);
    QVector<QString> data;
    QImage img;
    ~Dialog0();

private slots:
    void on_buttonBox_accepted();

    void on_pushButton_clicked();

private:
    Ui::Dialog0 *ui;
};

#endif // DIALOG0_H
