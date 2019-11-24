#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dayreport.h"
#include "uidayreport.h"
#include "mainwindow.h"
#include <math.h>
#include <QObject>
#include <QDebug>
#include <QTableWidget>
#include <QTableView>
#include <ui_mainwindow.h>
#include <QMessageBox>
#include <QComboBox>
#include "datamanage.h"
 DataManage* thisDataManage ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->InitMainTable();
    this->InitFilterTable();

}


void MainWindow::AboutMsg()
{
    QMessageBox::about(this,tr("版本信息"),tr("现在版本为0.0.01"));
}

int MainWindow::InitMainTable()
{
    QTableView * TableView = ui->MainTableView;
    thisDataManage = new DataManage (TableView) ;
    TableView->hideColumn(0);
    TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//使其不可编辑

    TableView->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
    TableView->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    TableView->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个
    return 0;
}

void MainWindow::SwitchDateTime(const QString &text)
{

    QTableWidget* TableWidget = ui->FilterTableWidget;
    QLineEdit* NormalLineEdit = new QLineEdit();
    int Row = TableWidget->currentRow();
    qDebug()<< "TRIG Combox ";
    QDateTimeEdit* DateTimeEdit = new QDateTimeEdit();
    QTableWidgetItem* TableWidgetItem = TableWidget->currentItem();
    QComboBox* Combox = (QComboBox*)TableWidget->cellWidget(Row,0);
    QString ssss = Combox->currentText();
    qDebug()<<ssss.toStdString().c_str() <<endl;
    qDebug()<<Combox->currentText().indexOf("时间")<<endl;
    qDebug()<<TableWidget->columnCount()<<endl;
    for (int i = 1; i < TableWidget->columnCount(); ++i) {

        if (Combox->currentText().indexOf("时间")>0)
        {
            TableWidget->setCellWidget(Row,i,new QDateTimeEdit());
        }
        else if (TableWidget->item(Row,i) == nullptr || TableWidget->item(Row,i)->text() == "")
        {
            TableWidget->setItem(Row,i,TableWidgetItem);
        }

   }

}


QStringList * MainWindow::SelectComboBoxText(QList<QString> list,QTableWidget* TableWidget)
{
    QStringList * ret = new QStringList();
    QComboBox * Combox = new QComboBox () ;
    //遍历当前所有的按钮，发现已经设置的项目之后，将其删除掉。
    for (int i = 0;i < TableWidget->rowCount();i++)
    {
        if ((TableWidget->item(i,1) != nullptr))
        {
            if (TableWidget->item(i,1)->text() == "")
                continue;
            //提取当前的下拉菜单，然后删除当前的选项
            Combox = (QComboBox*)TableWidget->cellWidget(i,0);
            list.removeOne(Combox->currentText());
        }
    }
    ret->append(list);
    return ret;
}
QList<QString> MainWindow::UpdateDisplayComboList(QTableWidget* TableWidget)
{
    //所有的数据-（列表内的数据∪显示的所有数据项） = 已经修改完成的数据项
    //内部列表内数据∩显示的所有数据项 = 多余的被修改的数据项
    QList<QString> DisplayList;

    QComboBox* Combox;
    //显示的所有数据项
    for (int i=0;i<TableWidget->rowCount();i++)
    {
        Combox = (QComboBox*)TableWidget->cellWidget(i,0);
        DisplayList.append(Combox->currentText());
    }
    return DisplayList;
}

bool MainWindow::ItemIsEmpty(QTableWidgetItem* TableWidgetItem)
{
    bool isEmpty;
    if (TableWidgetItem == nullptr)  //仅更新没有数据的窗口
    {
        if (TableWidgetItem->text() == "")
        {
            isEmpty = true;
        }
        else
        {
            isEmpty = false;
        }
    }
    else
    {
        isEmpty = false;
    }
    return isEmpty;
}

int MainWindow::UpdateFilterTable()
{
    static QList<QString> list;
    QTableWidget* TableWidget = ui->FilterTableWidget;
    QComboBox * Combox = new QComboBox () ;
    QWidget* NormalWidget = new QWidget ();
    QDateTimeEdit* DateTimeEdit = new QDateTimeEdit();
    int SelectRow,MaxRow;
    list.clear();
    list<<"序号"<<"机型"<<"事项"<<"目标"<<"实际进行"<<"差异及改善"<<"权重"<<"评估";

    SelectRow = TableWidget->currentRow();
    MaxRow = TableWidget->rowCount();

    //将整理完成的数据重新放置进入筛选窗口的空白筛选项
    QStringList *StringList = this->SelectComboBoxText(list,TableWidget);

    if (!this->ItemIsEmpty(TableWidget->item(TableWidget->rowCount()-1,1)) && !ItemIsEmpty(TableWidget->item(TableWidget->currentRow(),1)))  //仅更新没有数据的窗口
    {

        Combox->addItems(*StringList);
        qDebug()<<"Select"<<SelectRow<<"Max"<< MaxRow;
        //限制最大项
        if(TableWidget->currentRow() == (TableWidget->rowCount() - 1))
        {
            if (TableWidget->rowCount() <=list.count())
            {
                TableWidget->insertRow(MaxRow);
                TableWidget->setCellWidget(MaxRow,0,Combox);
            }
        }

    }
    else
    {
        TableWidget->removeRow(MaxRow);
    }
    QStringList NewList = this->UpdateDisplayComboList(TableWidget);

    QString AddString;
    QString DelString;
    //如果是修改了中间的一项，就把其他的项目给增加
    for (int i = 0;i<NewList.count();i++)
    {
        if (!StringList->removeOne(NewList.value(i)))
        {
            AddString = NewList.value(i);
            DelString = StringList->value(i);
        }
        else
        {
            NewList.removeAt(i);
        }
    }
    if (AddString.isNull()
            && AddString.isEmpty()
            && DelString.isNull()
            && DelString.isEmpty())
    {
        for (int i = 0; i < TableWidget->rowCount(); ++i)
        {
            Combox = (QComboBox *)TableWidget->item(i,0);
            Combox->addItem(AddString);
            Combox->removeItem(Combox->findText(DelString));
        }

    }


// delete StringList;
}

int MainWindow::InitFilterTable()
{
    QStringList FilterTableStringList;
//    FilterTableStringList<<"筛选项目"<<"起始"<<"结束";
    FilterTableStringList<<"筛选项目"<<"数据";
    QTableWidget* TableWidget = ui->FilterTableWidget;
    QStringList StringList;
    StringList<<"序号"<<"机型"<<"事项"<<"目标"<<"实际进行"<<"差异及改善"<<"开始时间"<<"结束时间"<<"权重"<<"评估";
    TableWidget->setColumnCount(FilterTableStringList.count());
    TableWidget->setRowCount(1);
    TableWidget->setHorizontalHeaderLabels(FilterTableStringList);

    TableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//整行选中的方式
//    TableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//禁止修改
    TableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//可以选中单个


        QComboBox* ComboBox = new QComboBox();
        ComboBox->addItems(StringList);

        FilterComboxStringList.append(&StringList);
        TableWidget->setCellWidget(0,0,ComboBox);

    return 0;
}

int MainWindow::SetDayreportToItem(DayReport* Dayreport,int Row)
{
    thisDataManage->SetNewData(Row,Dayreport);

}

int MainWindow::EditDayreportToItem(DayReport* Dayreport,int Row)
{
    thisDataManage->EditData(Row,Dayreport);

}

int MainWindow::GetItemToDayreport(DayReport* Dayreport, int ItemIndex)
{
    QTableView* MainTableView = ui->MainTableView;
    DataManage* DataManage = thisDataManage;
    if (MainTableView->model()->rowCount() <= 0)
    {
        return -1;
    }
    DataManage->GetOneData(ItemIndex,Dayreport);

    return 0;
}
int MainWindow::AddDayReport(int index)
{
    uidayreport * uidayreport = new class uidayreport(index);
    DayReport* Dayreport = new DayReport();

    uidayreport->exec();        //栓塞等待选择完成
    if (uidayreport->GetStatus())
    {
            Dayreport = uidayreport->GetReport();
            SetDayreportToItem(Dayreport,index);

    }

    delete uidayreport;
    return 0;
}

int MainWindow::DelDayReport(int index)
{
    thisDataManage->DelData(index);
    return 0;
}

int MainWindow::EditDayReport(int index)
{
    DayReport* Dayreport =new DayReport();
    GetItemToDayreport(Dayreport,index);
    uidayreport * uidayreport = new class uidayreport(Dayreport,(unsigned int)index);
    uidayreport->exec();
    if (uidayreport->GetStatus())
    {
        DayReport * Dayreport = uidayreport->GetReport();
        EditDayreportToItem(Dayreport,index);
    }
    return 0;
}

void MainWindow::on_pushButton_2_clicked()
{

    int index = ui->MainTableView->currentIndex().row();
    if (index<0)
    {
        index = ui->MainTableView->model()->rowCount();
    }
    int Select = ui->comboBox->currentIndex();
    index++;
    switch (Select) {
    case 0: {       //add
        AddDayReport(index);
    }break;
    case 2:{        //del
        index--;
        DelDayReport(index);
    }break;
    case 1:{        //modify
        EditDayReport(index);
    }break;
    default:
        break;
    }
    thisDataManage->SortNumber();
}

MainWindow::~MainWindow()
{
    delete ui;
}





QVariantMap MainWindow::GetFilterList()
{
    QTableWidget* TableWidget = ui->FilterTableWidget;
    QVariantMap ret;
    QComboBox * Combox;

    for (int i = 0;i<TableWidget->rowCount();i++)
    {
        if (TableWidget->item(i,1)  != nullptr)
        {
            if (TableWidget->item(i,1)->text() != "")
            {
                Combox = (QComboBox*)TableWidget->cellWidget(i,0);
                QString String = Combox->currentText();
                QVariant Value = TableWidget->item(i,1)->text();
                ret.insert(String,Value);
                qDebug()<<Value<<endl;
            }
        }


    }
    return ret;
}

void MainWindow::on_About_triggered()
{
    this->AboutMsg();
}

void MainWindow::on_Report_clicked()
{
    DataManage* Datamanage = thisDataManage;
    Datamanage->SaveDataBase();
}

void MainWindow::on_FilterTableWidget_itemChanged(QTableWidgetItem *item)
{

    MainWindow::UpdateFilterTable();
    qDebug()<<"trig";
//    this->GetFilterList();

}
