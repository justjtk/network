#ifndef WUSER_H
#define WUSER_H

#include <QMainWindow>
#include <string>
#include "wmodify.h"
using namespace std;

namespace Ui {
class WUser;
}

class WUser : public QMainWindow
{
    Q_OBJECT

public:
    explicit WUser(QString uid,QWidget *parent = nullptr);
    ~WUser();

private slots:
    void on_pushButton_2_clicked();

private:
    QString id;
    Ui::WUser *ui;
    WModify* wmodify;
};

#endif // WUSER_H
