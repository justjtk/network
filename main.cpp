#include "mainwindow.h"

#include <QApplication>
#include"gmp.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    mpz_t t;
    mpz_init(t);
    mpz_ui_pow_ui(t,2,100);
    gmp_printf("%Zd\n",t);
    return a.exec();
}
