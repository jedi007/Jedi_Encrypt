#include "encryptmodel.h"

#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QDataStream>

#include "systemconfig.h"
#include "jcryptstrategy.h"

EncryptModel::EncryptModel(EncryptState& t_state):state(t_state)
{

}

void EncryptModel::run()
{
    qDebug()<<"state.id is "<< state.id.data1 <<" thread ID is  "<<QThread::currentThreadId()<<endl;
    state.state_str = "计算中...";
    for(int i=0;i<=3;i++)
    {
        QThread::msleep(100);
        state.percent = i;
    }
    if(model == 0)
        encypt_alg();
    else
        decypt_alg();
    qDebug().noquote() << QString("End   thread %1 at %2").arg( state.id.data1 ).arg(QDateTime::currentDateTime().toString("mm:ss.z"));
}

void EncryptModel::encypt_alg()
{
    QFile infile(state.filename);
    if( !infile.exists() )
    {
        state.over = true;
        state.state_str = "文件不存在";
        return;
    }

    if( !infile.open(QFile::ReadOnly) )
    {
        state.over = true;
        state.state_str = "输入文件打开失败";
        return;
    }

    QFileInfo finfo(state.filename);
    qDebug()<<" finfo.path(): "<<finfo.path()<<endl;

    QString filename = state.filename.split("/").last();
    QStringList namelist = filename.split(".");
    if(!finfo.suffix().isEmpty() && namelist.size() > 1 )
        namelist.removeLast();
    namelist.append("jcpt");
    QString outfilename =  QString("%1/%2").arg(finfo.path()).arg(namelist.join("."));
    qDebug()<<"outfilename: "<<outfilename;

    QByteArray head;
    QDataStream stream( &head , QIODevice::WriteOnly);
    stream<<filename;
    stream<<finfo.size();
    head.resize(1024);


    QFile outfile(outfilename);
    if( !outfile.open(QFile::WriteOnly) )
    {
        state.over = true;
        state.state_str = "输出文件打开失败";
        return;
    }

    outfile.write(head);

    int lv = SystemConfig::getinstance()->obj[DF_crypt_lv].toInt();
    JCryptStrategy_controller strategy(SystemConfig::getinstance()->key,false,lv);

    while (!infile.atEnd()) {
        QByteArray bytes = infile.read(8);
        qDebug()<<"bytes"<<bytes.size()<<endl;


        strategy.handler(bytes);

        outfile.write(bytes);

    }

    outfile.close();
}

void EncryptModel::decypt_alg()
{
    QFile infile(state.filename);
    if( !infile.exists() )
    {
        state.over = true;
        state.state_str = "文件不存在";
        return;
    }

    if( !infile.open(QFile::ReadOnly) )
    {
        state.over = true;
        state.state_str = "输入文件打开失败";
        return;
    }

    QString outfilename;
    qint64 filesize = 0;

    QByteArray head = infile.read(1024);
    QDataStream stream( &head , QIODevice::ReadOnly);
    stream>>outfilename;
    stream>>filesize;

    qDebug()<<"outfilename: "<<outfilename<<endl;
    qDebug()<<"filesize: "<<filesize;

    QFileInfo finfo(state.filename);
    QFile outfile( QString("%1/decrypt_%2").arg(finfo.path()).arg(outfilename) );
    if( !outfile.open(QFile::WriteOnly) )
    {
        state.over = true;
        state.state_str = "输出文件打开失败";
        return;
    }

    int lv = SystemConfig::getinstance()->obj[DF_crypt_lv].toInt();
    JCryptStrategy_controller strategy(SystemConfig::getinstance()->key,true,lv);

    while (!infile.atEnd()) {
        QByteArray bytes = infile.read(8);
        qDebug()<<"bytes"<<bytes.size()<<endl;


        strategy.handler(bytes);

        outfile.write(bytes);

    }

    outfile.close();
}
