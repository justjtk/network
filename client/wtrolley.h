#ifndef WTROLLEY_H
#define WTROLLEY_H

#include <QMainWindow>
#include <string>
using namespace std;

namespace Ui {
class WTrolley;
}

class WTrolley : public QMainWindow
{
    Q_OBJECT

public:
    explicit WTrolley(QString uid,QWidget *parent = nullptr);
    ~WTrolley();

private:
    QString id;
    Ui::WTrolley *ui;
};

#endif // WTROLLEY_H
