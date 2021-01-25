#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QThreadPool>

#include "filetools.h"
#include "encryptmodel.h"
#include <QDebug>
#include <QMessageBox>

#include "systemconfig.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusModel = new EncryptListModel(this);
    ui->tableView->setModel(statusModel);

    initMymolde();

    resize(1600,900);

    ui->splitter->setStretchFactor(0, 2);
    ui->splitter->setStretchFactor(1, 4);
    ui->splitter->setStretchFactor(2, 9);

    ui->radioButton_Low->setChecked( SystemConfig::getinstance()->obj[DF_crypt_lv].toInt()==1 );
    ui->radioButton_Mid->setChecked( SystemConfig::getinstance()->obj[DF_crypt_lv].toInt()==2 );
    ui->radioButton_Hig->setChecked( SystemConfig::getinstance()->obj[DF_crypt_lv].toInt()==3 );

    if( SystemConfig::getinstance()->obj[DF_no_outdir].toBool() )
    {
        ui->checkBox_no_outdir->setChecked( true );
        ui->lineEdit_outdir->setEnabled(false);
        ui->pushButton_setoutdir->setEnabled(false);
    }
    else
    {
        ui->checkBox_no_outdir->setChecked( false );
        ui->lineEdit_outdir->setText(SystemConfig::getinstance()->obj[DF_outdir_str].toString());
    }
    ui->spinBox_threads_count->setValue( SystemConfig::getinstance()->obj[DF_threads_count].toInt() );

    pool.setMaxThreadCount( SystemConfig::getinstance()->obj[DF_threads_count].toInt() );

    connect(ui->tableView,&StatusView::changeEnabled,[=](bool b){
        if(b && !this->buttons_enable)
        {
            QMessageBox::information( this,"操作完成","所有任务均已完毕" );
            this->enableButtons(b);
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::enableButtons(bool b)
{
    ui->pushButton_encrypt_dir->setEnabled(b);
    ui->pushButton_dencrypt_dir->setEnabled(b);
    ui->pushButton_decrypt->setEnabled(b);
    ui->pushButton_encrypt->setEnabled(b);
    ui->treeView->setEnabled(b);
    ui->toolBox->setEnabled(b);
    buttons_enable = b;
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

void MainWindow::initMymolde()
{
    myModel = new MyFileSystemModel(this);
    QString appPath = QApplication::applicationDirPath();
    myModel->setRootPath(appPath);

    ui->treeView->setModel( myModel );
    ui->treeView->setCurrentIndex( myModel->index(appPath) );
    //ui->treeView->setRootIndex( myModel->index(appPath) );

}

void MainWindow::on_pushButton_encrypt_clicked()
{
    enableButtons(false);
    QApplication::processEvents();

    QList<EncryptState>& status = statusModel->status;
    for(int i=0;i<status.size();i++)
    {
        status[i].over = false;
        status[i].oversize = 0;

        EncryptModel* encrypt = new EncryptModel(status[i]);

        pool.start(encrypt);
    }

}

void MainWindow::on_pushButton_decrypt_clicked()
{
    enableButtons(false);
    QApplication::processEvents();

    QList<EncryptState>& status = statusModel->status;
    for(int i=0;i<status.size();i++)
    {
        status[i].over = false;
        status[i].oversize = 0;

        EncryptModel* encrypt = new EncryptModel(status[i]);
        encrypt->model = 1;

        pool.start(encrypt);
    }
}

void MainWindow::on_treeView_clicked(const QModelIndex &index)
{
    QString current_path = myModel->filePath(index);

    if(current_path.isEmpty()) return;

    statusModel->setPath(current_path);
}

void MainWindow::on_lineEdit_encrypt_key_textChanged(const QString &arg1)
{
    qDebug()<<" key change to "<< arg1 <<endl;
    SystemConfig::getinstance()->key = arg1;

}


void MainWindow::on_radioButton_Low_clicked()
{
    SystemConfig::getinstance()->obj.insert(DF_crypt_lv,1);
    SystemConfig::getinstance()->save();
}

void MainWindow::on_radioButton_Mid_clicked()
{
    SystemConfig::getinstance()->obj.insert(DF_crypt_lv,2);
    SystemConfig::getinstance()->save();
}

void MainWindow::on_radioButton_Hig_clicked()
{
    SystemConfig::getinstance()->obj.insert(DF_crypt_lv,3);
    SystemConfig::getinstance()->save();
}

void MainWindow::on_checkBox_no_outdir_stateChanged(int arg1)
{
    Q_UNUSED(arg1)

    bool checked = ui->checkBox_no_outdir->isChecked();
    SystemConfig::getinstance()->obj.insert(DF_no_outdir,checked);
    SystemConfig::getinstance()->save();

    ui->lineEdit_outdir->setEnabled(!checked);
    ui->lineEdit_outdir->setText( SystemConfig::getinstance()->obj[DF_outdir_str].toString() );
    ui->pushButton_setoutdir->setEnabled(!checked);
}

void MainWindow::on_pushButton_setoutdir_clicked()
{
    QString outdir = QFileDialog::getExistingDirectory(this,"Save File",
                                                       SystemConfig::getinstance()->obj[DF_outdir_str].toString());

    qDebug()<<"outdir "<<outdir<<endl;
    if(outdir == "")
        return;

    SystemConfig::getinstance()->obj.insert(DF_outdir_str,outdir);
    SystemConfig::getinstance()->save();

    ui->lineEdit_outdir->setText(outdir);
}

void MainWindow::on_spinBox_threads_count_valueChanged(int arg1)
{
    qDebug()<<" value change to: "<<arg1<<endl;
    SystemConfig::getinstance()->obj.insert(DF_threads_count,arg1);
    SystemConfig::getinstance()->save();

    pool.setMaxThreadCount(arg1);
}
