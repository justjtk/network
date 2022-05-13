#ifndef WGOOD_H
#define WGOOD_H

#include <QMainWindow>
#include <string>
#include "wpay.h"
using namespace std;

namespace Ui {
class WGood;
}

class WGood : public QMainWindow
{
    Q_OBJECT

public:
    explicit WGood(QString uid,QWidget *parent = nullptr);
    ~WGood();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    //void Select_kind(QString kind);

    void on_pushButton_21_clicked();

private:
    QString id;
    Ui::WGood *ui;
    WPay* wpay;
};

#endif // WGOOD_H
