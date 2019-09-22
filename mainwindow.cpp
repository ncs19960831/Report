#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dayreport.h"
#include "uidayreport.h"
#include <math.h>
#include <QObject>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    ui = MainWindow::ui;
    static QSize OldSize;
    QSize size = MainWindow::size();

    int width,OldWidth;
    int heigth,OldHeight,newSize;
    QListView* listView = ui->listView;
    //    volatile double k_MainWindows;
    //    volatile double l_MainWIndows;
    double kx_MainWindows;
    double ky_MainWindows;
    width = size.rwidth();
    heigth = size.rheight();
    OldWidth = OldSize.rwidth();
    OldHeight = OldSize.rheight();
    OldSize = size;
    if ((width == 0) || \
        (OldWidth == 0) ||\
        (heigth == 0) ||\
        (OldHeight == 0) \
            )
    {
        return;

    }
    if (width != OldWidth || heigth != OldHeight)
    {

//            l_MainWIndows = sqrt(((width - OldHeight)*(higth - OldHeight)) \
                        + (width - OldWidth)*(width - OldWidth));
//            k_MainWindows = (higth - OldHeight)/(width - OldWidth);
        kx_MainWindows = (double)width / (double)OldWidth;
        ky_MainWindows = (double)heigth / (double)OldHeight;
        if (kx_MainWindows<=0 || ky_MainWindows <=0)
            return;
        newSize = listView->width();
        newSize *=kx_MainWindows;
        listView->setFixedWidth(newSize);
        listView->size().setWidth(newSize);

        newSize = listView->height();
        newSize *=ky_MainWindows;
        listView->setFixedHeight(newSize);
        listView->size().setHeight(newSize);
    }


  //  ui->MainList->size().setWidth(ui->MainList->size().width()*k_MainWindows);
  //  ui->MainList->size().setHeight(ui->MainList->size().height()*k_MainWindows);
  //  ui->listView->size().setWidth(ui->listView->size().width()*k_MainWindows);
  //  ui->listView->size().setHeight(ui->listView->size().height()*k_MainWindows);

}

MainWindow::~MainWindow()
{
    delete ui;
}

MainWindow::AddDayReport(int index)
{
    uidayreport * uidayreport = new class uidayreport();
    uidayreport->show();
    return 0;
}

MainWindow::DelDayReport(int index)
{
    return 0;
}

MainWindow::EditDayReport(int index)
{
    return 0;
}

void MainWindow::on_pushButton_2_clicked()
{

    int index = ui->comboBox->currentIndex();
    switch (index) {
    case 0: {       //add
        AddDayReport(index);
    }break;
    case 2:{        //del
        DelDayReport(index);
    }break;
    case 1:{        //modify
        EditDayReport(index);
    }break;
    default:
        break;
    }
}
