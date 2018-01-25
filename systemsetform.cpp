#include "systemsetform.h"
#include "ui_systemsetform.h"

SystemSetForm::SystemSetForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SystemSetForm)
{
    ui->setupUi(this);
    for(int i = 1;i<21;i++)
    {
        ui->comboBox->addItem(QString::number(i));
    }

    //读取配置文件-------------------------------------------------
    QString tmpoutfile = "";
    QFile fileDirdat;
    fileDirdat.setFileName("UseroutfileDirinfo.dat");
    if(fileDirdat.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString tmpi = "";
        QTextStream in(&fileDirdat);
        int slidervalue = 0;
        int maxthread_num_tmp = 1;
        in>>tmpi;
        in>>tmpoutfile;
        in>>slidervalue;
        in>>maxthread_num_tmp;

        IS_useinPath = tmpi.toInt();
        ui->horizontalSlider->setValue(slidervalue);
        ui->comboBox->setCurrentIndex(maxthread_num_tmp - 1);
        fileDirdat.close();
    }
    else
    {
        IS_useinPath = false;
    }    
    if(IS_useinPath)
    {
        ui->checkBox->setChecked(true);
        ui->outfile_label->setText("与源文件相同路径");
    }
    else
    {
        qDebug()<<"outfile:"<<tmpoutfile<<endl;
        if(tmpoutfile == "")
        {
            ui->outfile_label->setText(tr("未设置"));
        }
        else
        {
            ui->outfile_label->setText(tmpoutfile);
        }
    }
    //读取配置文件完毕-----------------------------------------------------------
}

SystemSetForm::~SystemSetForm()
{
    delete ui;
}

void SystemSetForm::on_pushButton_clicked()//确定
{
    if(ui->outfile_label->text() == "未设置")
    {
        QMessageBox::information(this,"注意","输出路径未设置，请先设置输出路径");
        return;
    }

    IS_useinPath = ui->checkBox->isChecked();
    if(ui->outfile_label->text() != "与源文件相同路径")
        outFliePath = ui->outfile_label->text();
    else
        outFliePath = "C:\\";
    gcyptLV = ui->horizontalSlider->value();
    maxthread_num = ui->comboBox->currentIndex() + 1;

    //记录打开文件夹路径----------------------------------------------------------
    QFile filesDirdat;
    filesDirdat.setFileName("UseroutfileDirinfo.dat");
    if(filesDirdat.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&filesDirdat);
        out<<int(IS_useinPath)<<" "<<outFliePath<<" "<<gcyptLV<<" "<<maxthread_num;
    }
    filesDirdat.close();
    //记录完毕---------------------------------------------------------------------
    signalmanage.Emit_setting_changed("");
    close();
}

void SystemSetForm::on_pushButton_2_clicked()//设置路径
{
    if(ui->checkBox->isChecked())
        return;

    QString plainFilepath=QFileDialog::getExistingDirectory(this,"Save File",QDir::currentPath());

    if(plainFilepath == "")
        return;

    qDebug()<<"plainFilepath:"<<plainFilepath<<endl;
    QString file_name, file_path;
    QFileInfo fi;
    fi = QFileInfo(plainFilepath);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    qDebug()<<"file_name  file_path:"<<file_name<<file_path<<endl;
    if(file_name=="")
    {
        ui->outfile_label->setText(plainFilepath);
    }
    else
    {
        plainFilepath=plainFilepath+"/";
        ui->outfile_label->setText(plainFilepath);
    }
}

void SystemSetForm::on_checkBox_stateChanged(int arg1)
{
    if(ui->checkBox->isChecked())
    {
        ui->outfile_label->setText("与源文件相同路径");
    }
    else
    {
        ui->outfile_label->setText("未设置");
    }
}

















