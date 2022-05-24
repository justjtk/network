#include "mainwindow.h"
#include <QApplication>
#include<QDir>
#include <QDebug>
#include <QStringList>
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    //QString strLibPath(QDir::toNativeSeparators(QApplication::applicationDirPath())+QDir::separator()+"plugins");
    //a.addLibraryPath(strLibPath);
    MainWindow w;
    w.connect_mysql();
    //w.show();

    return a.exec();
}
