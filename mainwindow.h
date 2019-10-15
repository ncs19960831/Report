#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dayreport.h"

#include <QComboBox>
#include <QMainWindow>
#include <QTableWidget>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);


    ~MainWindow();

    int AddDayReport(unsigned int index);
    int DelDayReport(unsigned int index);
    int EditDayReport(unsigned int index);
    int SetDayreportToItem(DayReport* Dayreport,unsigned int Row);
    int GetItemToDayreport(DayReport *Dayreport, QString *DataString, int ItemIndex);
    int InitMainTable();
    int InitFilterTable();
    int UpdateFilterTable();
private slots:

    void on_pushButton_2_clicked();

    void on_FilterTableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

protected:
private:
    Ui::MainWindow *ui;
    QComboBox * FilterCombox[10];
};

#endif // MAINWINDOW_H
