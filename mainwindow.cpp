#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "filetools.h"
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
    //ui->treeView->setRootIndex( myModel->index(appPath) );

    ui->treeView->setRootIndex( myModel->index("E:/加密测试") );

    resize(1280,800);

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
    //test=================================================

    QString str = "subsubdir测试 - 副本 (3)";
    QString hexstr = str.toLocal8Bit().toHex();

    qDebug()<<"hexstr: "<<hexstr<<endl;

    QString algstr = QString::fromLocal8Bit( FileTools::HexStringToByteArray(hexstr) );

    qDebug()<<"algstr: "<<algstr<<endl;
}

void MainWindow::on_pushButton_encrypt_dir_clicked()
{
    QString current_path = myModel->filePath(ui->treeView->currentIndex());

    if(current_path.isEmpty())
        current_path = myModel->filePath(ui->treeView->rootIndex());

    FileTools::encryptDirnames( current_path );
}

void MainWindow::on_pushButton_dencrypt_dir_clicked()
{
    QString current_path = myModel->filePath(ui->treeView->currentIndex());

    if(current_path.isEmpty())
        current_path = myModel->filePath(ui->treeView->rootIndex());

    FileTools::decryptDirnames( current_path );
}

void MainWindow::on_pushButton_import_file_clicked()
{

}
