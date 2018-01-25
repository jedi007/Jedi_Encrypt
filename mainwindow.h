#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QLabel>

#include <windows.h>
#include "jedi_encyptmode.h"
#include "global.h"
#include "systemsetform.h"
#include "qprossbarlabel.h"
#include <QMessageBox>
#include <QCloseEvent>

#define USER_DATA_PATH "C:/Users/Administrator/Desktop"
#define OUTFILETEST "E:/outfiletest.txt"
#define OUTFILETEST2 "C:/outfiletest.txt"

namespace Ui {
class MainWindow;
}

class datamange:public QObject
{
    Q_OBJECT
public:
    datamange(int x = 0)
    {
        encyptmodep = NULL;
        labep = NULL;
        isfinished = false;
        inFileName = "";
        inFilesize_str = "";
        index = x;
    }

    void set_encyptmodep(Jedi_encyptmode * encyptmpp,Qprossbarlabel * labetmp)//NULL空指针不能建立信号连接，所以需要先对成员赋值
    {
        encyptmodep = encyptmpp;
        labep = labetmp;
        connect(encyptmodep,SIGNAL(refresh(int)),this,SLOT(on_labelrefresh(int)));
    }

    int index;
    bool isfinished;
    QString inFileName;
    QString inFilesize_str;
    Jedi_encyptmode * encyptmodep;
    Qprossbarlabel * labep;

private slots:
    void on_labelrefresh(int ID)
    {
        if(labep == NULL)
        {
            qDebug()<<"ID beiyong:"<<ID<<endl;
            return;
        }
        labep->setText(QString::number(encyptmodep->T)+"/"+QString::number(encyptmodep->fileLen));
        double dval = double(encyptmodep->T)/double(encyptmodep->fileLen);
        labep->setdval(dval);
        if(encyptmodep->processval == 1)
        {
            labep->setText("完成");
            isfinished = true;
            labep->setdval(1);
            encyptmodep->statu = "finished";
        }
    }

};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void closeEvent(QCloseEvent *event);

    void replottablew();
    void refresh_all_Thread();

private slots:
    void on_systemset();

    void on_settingchanged(QString str);

    void on_onethread_finished(int tmpi);

    void on_BTencypt_clicked();

    void on_BTdecypt_clicked();

    void on_BTpause_clicked();

    void on_BTcontinue_clicked();

    void on_BTimport_clicked();

private:
    Ui::MainWindow *ui;

    QList<datamange*> mdatamange; /*QList的[]方法可以修改数据，但是会拷贝实体，消耗资源更大
                                    使用QList的at()方法，以只读方式访问数据，但是无法修改数据
                                    所以配合QList可以兼具修改数据可低消耗访问*/

    SystemSetForm *setForm;
};

#endif // MAINWINDOW_H
