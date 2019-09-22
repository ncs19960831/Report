#include "mainwindow.h"
#include "dayreport.h"
#include <QApplication>
#include <QLabel>
#include <QListView>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}

