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
    state.filesize = finfo.size();
    QDataStream stream( &head , QIODevice::WriteOnly);
    stream<<filename;
    stream<<state.filesize;
    head.resize(1024);


    QFile outfile(outfilename);
    if( !outfile.open(QFile::WriteOnly) )
    {
        state.over = true;
        state.state_str = "输出文件打开失败";
        return;
    }

    QDataStream instream(&infile);
    QDataStream outstream(&outfile);

    outfile.write(head);
    //outstream<<head;

    int lv = SystemConfig::getinstance()->obj[DF_crypt_lv].toInt();
    JCryptStrategy_controller strategy(SystemConfig::getinstance()->key,false,lv);

    QByteArray bytes;
    while (!infile.atEnd()) {
        bytes = infile.read(8);

        strategy.handler(bytes);

        outfile.write(bytes);

        state.oversize += 8;
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
    state.filesize = 0;

    QByteArray head = infile.read(1024);
    QDataStream stream( &head , QIODevice::ReadOnly);
    stream>>outfilename;
    stream>>state.filesize;

    qDebug()<<"outfilename: "<<outfilename<<endl;
    qDebug()<<"filesize: "<<state.filesize;

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

        strategy.handler(bytes);

        if(state.filesize - state.oversize >7)
        {
            outfile.write(bytes);
            state.oversize += 8;
        }
        else
        {
            outfile.write(bytes,state.filesize-state.oversize);
            state.oversize = state.filesize;
        }
    }

    outfile.close();
}
