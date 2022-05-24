#ifndef SIGN_H
#define SIGN_H

#include <QDialog>

namespace Ui {
class sign;
}

class sign : public QDialog
{
    Q_OBJECT

public:
    explicit sign(QWidget *parent = nullptr);
    ~sign();
    QString name;
    QString id;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::sign *ui;
};

#endif // SIGN_H
