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

    int AddDayReport(int index);
    int DelDayReport(int index);
    int EditDayReport(int index);
    int SetDayreportToItem(DayReport* Dayreport,int Row);
    int InitMainTable();
    int InitFilterTable();
    int UpdateFilterTable();
    int GetItemToDayreport(DayReport *Dayreport, int ItemIndex);
    int EditDayreportToItem(DayReport *Dayreport, int Row);
    QVariantMap GetFilterList();
    QStringList *SelectComboBoxText(QList<QString> list, QTableWidget *TableWidget);
    bool ItemIsEmpty(QTableWidgetItem *TableWidgetItem);
    QList<QString> UpdateDisplayComboList(QTableWidget *TableWidget);
private slots:

    void AboutMsg();

    void on_pushButton_2_clicked();

    void on_FilterTableWidget_currentCellChanged(int currentRow, int currentColumn, int previousRow, int previousColumn);

    void on_About_triggered();

    void on_Report_clicked();

    void SwitchDateTime(const QString &text);

    void on_FilterTableWidget_itemChanged(QTableWidgetItem *item);

protected:
protected slots:
private:
    Ui::MainWindow *ui;
    QList< QStringList *> FilterComboxStringList;
};

#endif // MAINWINDOW_H
