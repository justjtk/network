#ifndef WMODIFY_H
#define WMODIFY_H
#include"kerberos.h"
#include <QMainWindow>
#include <string>
using namespace std;

namespace Ui {
class WModify;
}

class WModify : public QMainWindow
{
    Q_OBJECT

public:
    explicit WModify(Pubdata alldata,QImage img,QWidget *parent = nullptr);
    ~WModify();

private slots:
    void on_pushButton_clicked();

private:
    Pubdata g_alldata;
    Ui::WModify *ui;
};

#endif // WMODIFY_H
