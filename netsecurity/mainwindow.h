#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include"network.h"
#include <QMainWindow>
#include<QTime>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


struct CtoAS{
    int IDc;
    int IDtgs;
    QString TS1;
};
struct Ticket {
int Key_cn;//c与tgs的des密钥
int IDc;
int ID;
QString TS;
int lifetime;//hour
};

struct AStoC{
int Key_c_tgs;//c与tgs的des密钥
int IDtgs;
QString TS2;
int lifetime;
//char* m_ticket_tgs;//放着加密的ticket
};

struct Authenticator{
    int IDc;
    QString TS;
};

struct CtoTGS{
    int IDv;
    char* m_ticket_tgs;
    char* authenticator;
};

struct TGStoC{
    char* Kcv;
    int IDv;
    QString TS4;
    char* m_ticket_v;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
