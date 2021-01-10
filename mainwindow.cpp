#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include "filetools.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusModel = new EncryptListModel(this);
    ui->tableView->setModel(statusModel);

    initMymolde();

    resize(1366,768);

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
    QString srcDirPath = QFileDialog::getExistingDirectory(
               this, "choose src Directory",
                "/");

    if (srcDirPath.isEmpty())
    {
        return;
    }
    else
    {
        qDebug() << "srcDirPath=" << srcDirPath;
        srcDirPath += "/";
    }

    ui->treeView->setRootIndex( myModel->index(srcDirPath) );


}

void MainWindow::on_pushButton_encrypt_dir_clicked()
{
    QString current_path = myModel->filePath(ui->treeView->currentIndex());

    if(current_path.isEmpty())
        current_path = myModel->filePath(ui->treeView->rootIndex());

    delete myModel;

    QString newnamepath = FileTools::encryptDirnames( current_path );

    initMymolde();
    ui->treeView->setCurrentIndex( myModel->index(newnamepath) );
}

void MainWindow::on_pushButton_dencrypt_dir_clicked()
{
    QString current_path = myModel->filePath(ui->treeView->currentIndex());

    if(current_path.isEmpty())
        current_path = myModel->filePath(ui->treeView->rootIndex());

    delete myModel;

    QString newnamepath = FileTools::decryptDirnames( current_path );

    initMymolde();
    ui->treeView->setCurrentIndex( myModel->index(newnamepath) );
}

void MainWindow::on_pushButton_import_file_clicked()
{

}

void MainWindow::initMymolde()
{
    myModel = new MyFileSystemModel(this);
    QString appPath = QApplication::applicationDirPath();
    myModel->setRootPath(appPath);

    ui->treeView->setModel( myModel );
    ui->treeView->setCurrentIndex( myModel->index(appPath) );
    //ui->treeView->setRootIndex( myModel->index(appPath) );

    connect( ui->treeView,&QTreeView::clicked,[=](const QModelIndex &index){
        QString current_path = myModel->filePath(index);

        if(current_path.isEmpty()) return;

        statusModel->setPath(current_path);
        qDebug()<<"current_path: "<<current_path<<endl;
    });
}

void MainWindow::on_pushButton_encrypt_clicked()
{

}

void MainWindow::on_pushButton_decrypt_clicked()
{

}
