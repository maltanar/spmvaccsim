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

void MainWindow::on_btnClear_clicked()
{
    ui->lstMatrices->clear();
}

void MainWindow::on_btnAddMatrices_clicked()
{
    QStringList matrices = ui->txtMatrices->text().split(",");

    foreach(const QString &matrix, matrices)
    {
        ui->lstMatrices->addItem(matrix.trimmed().replace("/","-"));
    }
}
