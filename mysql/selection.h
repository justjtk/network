#ifndef SELECTION_H
#define SELECTION_H

#include <QDialog>

namespace Ui {
class selection;
}

class selection : public QDialog
{
    Q_OBJECT

public:
    explicit selection(QWidget *parent = nullptr);
    ~selection();
    QString str="";
private slots:
    void on_buttonBox_accepted();

private:
    Ui::selection *ui;
};

#endif // SELECTION_H
