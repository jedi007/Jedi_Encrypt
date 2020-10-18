#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>


#include "./models/sysconfig.h"


#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myModel = new MyFileSystemModel(this);
    QString appPath = QApplication::applicationDirPath();
    myModel->setRootPath(appPath);

    //ui->treeView->setModel( myModel );
    //ui->treeView->setCurrentIndex( myModel->index(appPath) );

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
    QString lastPath = SysConfig::initance()->json["lastOpenPath"].toString();

    //文件夹路径
    QString srcDirPath = QFileDialog::getExistingDirectory(
               this, "选择要操作的文件夹",lastPath);

    if(srcDirPath.isEmpty()) return;

    ui->treeView->setModel( myModel );
    ui->treeView->setRootIndex( myModel->index(srcDirPath) );
    SysConfig::initance()->json["lastOpenPath"] = srcDirPath;
    SysConfig::initance()->save();
}
