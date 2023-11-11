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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionDelete_Min_triggered();

    void on_actionFill_Random_triggered();

    void on_actionClear_Heap_triggered();

    void on_actionragnarsTest_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
