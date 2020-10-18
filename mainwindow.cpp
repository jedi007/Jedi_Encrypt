#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myModel = new MyFileSystemModel(this);
    QString appPath = QApplication::applicationDirPath();
    myModel->setRootPath(appPath);

    ui->treeView->setModel( myModel );
    //ui->treeView->setCurrentIndex( myModel->index(appPath) );
    ui->treeView->setRootIndex( myModel->index(appPath) );

    resize(1600,900);

    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 4);
    ui->splitter->setStretchFactor(2, 9);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_import_dir_clicked()
{

}
