#include "mainwindow.h"
#include "ui_mainwindow.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionDelete_Min_triggered()
{
    ui->centralWidget->deleteMin();
}

void MainWindow::on_actionFill_Random_triggered()
{
    ui->centralWidget->fillWithRandomData();
}

void MainWindow::on_actionClear_Heap_triggered()
{
    ui->centralWidget->clearHeap();
}

void MainWindow::on_actionragnarsTest_triggered()
{
    ui->centralWidget->ragnarsTest();
}
