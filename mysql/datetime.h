#ifndef DATETIME_H
#define DATETIME_H

#include <QDialog>

namespace Ui {
class datetime;
}

class datetime : public QDialog
{
    Q_OBJECT

public:
    explicit datetime(QWidget *parent = nullptr);
    ~datetime();

private:
    Ui::datetime *ui;
};

#endif // DATETIME_H
