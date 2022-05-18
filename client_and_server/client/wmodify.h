#ifndef WMODIFY_H
#define WMODIFY_H

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
    explicit WModify(QString uid,QWidget *parent = nullptr);
    ~WModify();

private:
    QString id;
    Ui::WModify *ui;
};

#endif // WMODIFY_H
