#ifndef PACKAGE_SHOW_H
#define PACKAGE_SHOW_H

#include <QMainWindow>
#include<QStandardItemModel>
namespace Ui {
class package_show;
}

class package_show : public QMainWindow
{
    Q_OBJECT

public:
    explicit package_show(QWidget *parent = nullptr);
    ~package_show();
    QStandardItemModel *model;
    int now_row=0;
    int now_col=0;
    QVector<QVector<QString>> detailed_info;
    void update_tableview();
private slots:
    void on_tableView_clicked(const QModelIndex &index);

private:
    Ui::package_show *ui;
};

#endif // PACKAGE_SHOW_H
