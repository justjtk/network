#ifndef WPAY_H
#define WPAY_H

#include <QMainWindow>
#include <string>
using namespace std;

namespace Ui {
class WPay;
}

class WPay : public QMainWindow
{
    Q_OBJECT

public:
    explicit WPay(QString uid,QWidget *parent = nullptr);
    ~WPay();

private:
    Ui::WPay *ui;
    QString id;
};

#endif // WPAY_H
