#ifndef WGOOD_H
#define WGOOD_H

#include <QMainWindow>
#include <string>
#include "imagehandle.h"
#include "wpay.h"
using namespace std;

namespace Ui {
class WGood;
}

class WGood : public QMainWindow
{
    Q_OBJECT

public:
    explicit WGood(QString uid,QMainWindow *p,QWidget *parent = nullptr);
    ~WGood();


private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    //void Select_kind(QString kind);

    void on_pushButton_21_clicked();

    void Show_goods_1(QVector<QVector<QString>>,QVector<QByteArray>);

    void on_pushButton_24_clicked();

signals:
    void Refresh_goods_list(int);

private:
    QString id;
    QMainWindow *pmwd;
    Ui::WGood *ui;
    WPay* wpay;
};

#endif // WGOOD_H
