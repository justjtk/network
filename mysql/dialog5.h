#ifndef DIALOG5_H
#define DIALOG5_H

#include <QDialog>

namespace Ui {
class Dialog5;
}

class Dialog5 : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog5(QWidget *parent = nullptr);
    QVector<QString> data;
    ~Dialog5();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Dialog5 *ui;
};

#endif // DIALOG5_H
