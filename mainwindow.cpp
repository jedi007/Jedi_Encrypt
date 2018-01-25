#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->tableWidget->setColumnWidth(0,200);
    ui->tableWidget->setColumnWidth(4,200);
    ui->tableWidget->setColumnWidth(5,400);

    setForm = NULL;
    maxthread_num =0;

    connect(ui->actionshezhi,SIGNAL(triggered(bool)),this,SLOT(on_systemset()));
    connect(&signalmanage,SIGNAL(setting_changed(QString)),this,SLOT(on_settingchanged(QString)));
    connect(&signalmanage,SIGNAL(onethread_finished(int)),this,SLOT(on_onethread_finished(int)));

    //读取配置文件-------------------------------------------------
    QString tmpoutfile = "";
    QFile fileDirdat;
    fileDirdat.setFileName("UseroutfileDirinfo.dat");
    if(fileDirdat.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString tmpi = "";
        QTextStream in(&fileDirdat);
        int slidervalue = 0;

        in>>tmpi;
        in>>tmpoutfile;
        in>>slidervalue;
        in>>maxthread_num;
        qDebug()<<"tmpoutfile:"<<tmpoutfile<<endl;
        qDebug()<<"running success and maxthread_num:"<<maxthread_num<<endl;
        gcyptLV = slidervalue;
        IS_useinPath = tmpi.toInt();
    }
    else
    {
        IS_useinPath = false;
    }
    fileDirdat.close();
    if(IS_useinPath)
    {
    }
    else
    {
        qDebug()<<"tmpoutfile:"<<tmpoutfile<<endl;
        if(tmpoutfile == "C:\\")
        {
            IS_useinPath = true;
        }
        else
        {
            outFliePath = tmpoutfile;
        }
    }
    //读取配置文件完毕-----------------------------------------------------------
}

MainWindow::~MainWindow()
{
    delete ui;

    SAFE_DELETE_SINGLE(setForm)
}

void MainWindow::on_systemset()
{
    setForm = new SystemSetForm();

    setForm->show();
}

void MainWindow::on_settingchanged(QString str)
{
    qDebug()<<"get the signal"<<endl;
    for(int i = 0;i<mdatamange.size();++i)
    {
        if(mdatamange.at(i)->isfinished)
            continue;
        if(mdatamange.at(i)->encyptmodep->statu == "准备")
        {
            QString file_name, file_path;
            if(IS_useinPath)
            {
                QString strinFileName = mdatamange.at(i)->inFileName;
                QFileInfo fi;
                fi = QFileInfo(strinFileName);
                file_name = fi.fileName();
                file_path = fi.absolutePath();
                qDebug()<<"on_settingchanged file_path:"<<file_path<<endl;
            }
            else
            {
                file_path = outFliePath;
            }
            mdatamange.at(i)->encyptmodep->setoutfile_path(file_path);
            mdatamange.at(i)->encyptmodep->cyptLV = gcyptLV;
        }
    }
    refresh_all_Thread();
    replottablew();
}

void MainWindow::on_onethread_finished(int tmpi)
{
    refresh_all_Thread();
    replottablew();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    for(int i = 0;i<mdatamange.size();++i)
    {
        if( mdatamange.at(i)->labep->getdstr() != "完成")
        {
            qDebug()<<"in closeEvent mdatamange.size() mdatamange[i]->labep->getdstr() i:"<<mdatamange.size()<<mdatamange[i]->labep->getdstr()<<i<<endl;
            switch( QMessageBox::information( this, tr("信息"),
              tr("您还有未完成的项目，是否确认关闭?")+"\n\n"+"(关闭后未完成的项目将被清空)",
              tr("确定"), tr("取消"),
              0, 1 ) )
             {
                case 0:
                    close();
                    return;
                    break;
                case 1:
                    event->ignore();
                    return;
                    break;
               default:
                    return;
                    break;
             }
        }
    }

}

void MainWindow::replottablew()
{
    //ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(mdatamange.size());
    for(int i=0;i<mdatamange.size();i++)
    {
        //第一列-原文件
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(mdatamange.at(i)->inFileName));
        //第二列-文件大小
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(mdatamange.at(i)->inFilesize_str));
        //第三列-加密强度
        QString cyptLVstr = "";
        switch (mdatamange.at(i)->encyptmodep->cyptLV)
        {
        case 0:
            cyptLVstr = "初级";
            break;
        case 1:
            cyptLVstr = "中级";
            break;
        case 2:
            cyptLVstr = "高级";
            break;
        default:
            break;
        }
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(cyptLVstr));
        ui->tableWidget->item(i,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);        
        //第四列-算法
        ui->tableWidget->setItem(i,3,new QTableWidgetItem(mdatamange.at(i)->encyptmodep->cyptmodel));
        ui->tableWidget->item(i,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        //第五列-状态
        ui->tableWidget->setCellWidget(i,4,mdatamange.at(i)->labep);
        //第六列-输出路径
        ui->tableWidget->setItem(i,5,new QTableWidgetItem(mdatamange.at(i)->encyptmodep->outfilename));
        ui->tableWidget->item(i,5)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

}

void MainWindow::refresh_all_Thread()
{
    int running = 0;
    for(int i = 0;i<mdatamange.size();++i)
    {
        if(mdatamange.at(i)->encyptmodep->statu == "running")
        {
            running++;
            if(running > maxthread_num)
            {
                mdatamange.at(i)->encyptmodep->thread_pause();
                running--;
            }
        }
    }
    qDebug()<<"mdatamange.size():"<<mdatamange.size()<<" maxthread_num:"<<maxthread_num<<"  running:"<<running<<endl;
    for(int i = 0;i<mdatamange.size() && running < maxthread_num;++i)
    {
        if(mdatamange.at(i)->encyptmodep->statu == "准备")
        {
            mdatamange.at(i)->encyptmodep->start();
            running++;
            continue;
        }
        if(mdatamange.at(i)->encyptmodep->statu == "pause")
        {
            mdatamange.at(i)->encyptmodep->thread_continue();
            running++;
            continue;
        }
    }
}

void MainWindow::on_BTencypt_clicked()
{
    qDebug()<<"加密被按下"<<endl;
    QString key = ui->lineEdit->text();
    for(int i = 0;i<mdatamange.size();++i)
    {
       if(mdatamange.at(i)->encyptmodep->statu == "准备")
        {
           mdatamange.at(i)->encyptmodep->setkey(key);
           mdatamange.at(i)->encyptmodep->setmodel("encypt");
        }
    }
    refresh_all_Thread();
    replottablew();
}

void MainWindow::on_BTdecypt_clicked()
{
    qDebug()<<"解密被按下"<<endl;
    QString key = ui->lineEdit->text();
    for(int i=0;i<mdatamange.size();++i)
    {
        if(mdatamange.at(i)->encyptmodep->statu == "准备")
        {
            mdatamange.at(i)->encyptmodep->setkey(key);
            mdatamange.at(i)->encyptmodep->setmodel("decypt");
        }
    }
    refresh_all_Thread();
    replottablew();
}

void MainWindow::on_BTpause_clicked()
{
    qDebug()<<"暂停被点击"<<endl;
    for(int i =0;i<mdatamange.size();++i)
    {
        mdatamange.at(i)->encyptmodep->thread_pause();
    }
}

void MainWindow::on_BTcontinue_clicked()
{
    qDebug()<<"继续被点击"<<endl;
    refresh_all_Thread();
}

void MainWindow::on_BTimport_clicked()
{
    QString strDirName = "";

    //读取配置文件-------------------------------------------------
    QDir mdir;
    if (!mdir.exists(USER_DATA_PATH))
    {
        mdir.mkpath(USER_DATA_PATH);
    }

    QFile fileDirdat;
    fileDirdat.setFileName("UserfileDirinfo.dat");
    if(fileDirdat.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&fileDirdat);
        in>>strDirName;
    }
    else
    {
        strDirName = USER_DATA_PATH;
    }
    fileDirdat.close();

    QDir dir;
    if (!dir.exists(strDirName))
    {
        strDirName = USER_DATA_PATH;
    }
    //读取配置文件完毕-----------------------------------------------------------

    QStringList listFileName = QFileDialog::getOpenFileNames(0,
                                                             tr("Import Data Dialog"),
                                                             strDirName,
                                                             tr("Data Files(*)"));

    if (listFileName.count() == 0)
    {
        return;
    }
    for(int i = 0;i<listFileName.size();++i)
    {
        mdatamange.append(new datamange());
        int workindex = mdatamange.size() - 1;
        mdatamange.at(workindex)->index = mdatamange.size();
        mdatamange.at(workindex)->inFileName = listFileName.at(i);

        QFileInfo fileinfo;
        fileinfo = QFileInfo(listFileName.at(i));
        if(fileinfo.size()<1024)
        {
            mdatamange.at(workindex)->inFilesize_str = QString::number(fileinfo.size())+"Byte";
        }
        else if(fileinfo.size()<1024*1024)
        {
            double dbsize = double(fileinfo.size())/1024;
            mdatamange.at(workindex)->inFilesize_str = QString::number(dbsize,'f',2)+"KB";
        }
        else
        {
            double dbsize = double(fileinfo.size())/1024/1024;
            mdatamange.at(workindex)->inFilesize_str = QString::number(dbsize,'f',2)+"MB";
        }

        mdatamange.at(workindex)->set_encyptmodep(new Jedi_encyptmode(mdatamange.at(workindex)->inFileName,workindex),new Qprossbarlabel());
        //配置输出文件----------------------
        QString file_name, file_path;
        if(IS_useinPath)
        {
            QString strinFileName = mdatamange.at(workindex)->inFileName;
            QFileInfo fi;
            fi = QFileInfo(strinFileName);
            file_name = fi.fileName();
            file_path = fi.absolutePath();
            qDebug()<<"file_path:"<<file_path<<endl;
        }
        else
        {
            file_path = outFliePath;
        }
        mdatamange.at(workindex)->encyptmodep->setoutfile_path(file_path);
        //配置输出文件----------------------完毕
        mdatamange.at(workindex)->encyptmodep->cyptLV = gcyptLV;
        mdatamange.at(workindex)->encyptmodep->statu = "准备";
    }

    //记录打开文件夹路径----------------------------------------------------------
    QFile filesDirdat;
    filesDirdat.setFileName("UserfileDirinfo.dat");
    if(filesDirdat.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug()<<"缓存文件"<<endl;
        QFileInfo fileinfo;
        fileinfo = QFileInfo(listFileName.at(0));
        QString file_path = fileinfo.absolutePath();

        QTextStream out(&filesDirdat);
        out<<file_path;
    }
    filesDirdat.close();
    //记录完毕---------------------------------------------------------------------

    replottablew();
}
