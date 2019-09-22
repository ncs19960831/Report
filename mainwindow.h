#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    AddDayReport(int index);
    DelDayReport(int index);
    EditDayReport(int index);

    ~MainWindow();

private slots:

    void on_pushButton_2_clicked();
    
protected:
    void resizeEvent(QResizeEvent *event);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
