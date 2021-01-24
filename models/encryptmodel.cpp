#include "encryptmodel.h"

#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QDataStream>
#include <QTextCodec>
#include <iostream>

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
    FILE *infile,*outfile;
    QTextCodec *code = QTextCodec::codecForName("System");

    std::string infilename = code->fromUnicode(state.filename).data();
    if((infile = fopen(infilename.c_str(),"rb")) == NULL)
    {
        state.over = true;
        state.state_str = "输入文件打开失败";
        return;
    }

    QFileInfo finfo(state.filename);
    QString filename = state.filename.split("/").last();
    QStringList namelist = filename.split(".");
    if(!finfo.suffix().isEmpty() && namelist.size() > 1 )
        namelist.removeLast();
    namelist.append("jcpt");
    QString qoutfilename =  QString("%1/%2").arg(finfo.path()).arg(namelist.join("."));
    qDebug()<<"qoutfilename: "<<qoutfilename;

    std::string outfilename = code->fromUnicode(qoutfilename).data();
    if((outfile = fopen(outfilename.c_str(),"wb")) == NULL)
    {
        fclose(infile);
        state.over = true;
        state.state_str = "输出文件打开失败";
        return;
    }

    QByteArray head;
    head.resize(1024);
    state.filesize = finfo.size();
    QDataStream stream( &head , QIODevice::WriteOnly);
    stream<<filename;
    stream<<state.filesize;

    int ok = fwrite(head.data(),sizeof(char),1024,outfile);
    qDebug()<<"write size "<<ok<<endl;
    qDebug()<<"write data "<<head.toHex()<<endl;

    int lv = SystemConfig::getinstance()->obj[DF_crypt_lv].toInt();
    JCryptStrategy_controller strategy(SystemConfig::getinstance()->key,false,lv);

    int count = 0;
    char inBlock[8],outBlock[8];
    while(!feof(infile))
    {
        //每次读8个字节，并返回成功读取的字节数
        if((count = fread(inBlock,sizeof(char),8,infile)) == 8 )
        {
            strategy.handler(inBlock,outBlock);
            fwrite(outBlock,sizeof(char),8,outfile);
            state.oversize += 8;
        }
        else
        {
            //qDebug()<<"fread failed and read count:"<<count<<endl;
        }
    }
    if(count<8&&count>0)
    {
        char lkey[9] = "JediEncr";
        for( int i=0;i<count;i++ )
        {
            outBlock[i] = inBlock[i] ^ lkey[i];
        }

        fwrite(outBlock,sizeof(char),count,outfile);
        state.oversize += count;
    }

    fclose(infile);
    fclose(outfile);

    state.over = true;
    state.state_str = "完成";
}

void EncryptModel::decypt_alg()
{
    FILE *infile,*outfile;
    QTextCodec *code = QTextCodec::codecForName("System");

    std::string infilename = code->fromUnicode(state.filename).data();
    if((infile = fopen(infilename.c_str(),"rb")) == NULL)
    {
        state.over = true;
        state.state_str = "输入文件打开失败";
        return;
    }

    QString qoutfilename;
    char chead[1024];
    fread(chead,sizeof(char),1024,infile);
    QByteArray head;
    head.setRawData(chead,1024);
    QDataStream stream( &head , QIODevice::ReadOnly);
    stream>>qoutfilename;
    stream>>state.filesize;
    qDebug()<<"qoutfilename: "<<qoutfilename<<endl;
    qDebug()<<"state.filesize: "<<state.filesize<<endl;
    qDebug()<<"read data "<<head.toHex()<<endl;

    QFileInfo finfo(state.filename);
    qoutfilename = QString("%1/decrypt_%2").arg(finfo.path()).arg(qoutfilename);
    qDebug()<<"qoutfilename: "<<qoutfilename<<endl;
    std::string outfilename = code->fromUnicode(qoutfilename).data();

    if((outfile = fopen(outfilename.c_str(),"wb")) == NULL)
    {
        fclose(infile);
        state.over = true;
        state.state_str = "输出文件打开失败";
        return;
    }

    int lv = SystemConfig::getinstance()->obj[DF_crypt_lv].toInt();
    JCryptStrategy_controller strategy(SystemConfig::getinstance()->key,true,lv);

    int count;
    char inBlock[8],outBlock[8];
    while(!feof(infile))
    {
        if((count = fread(inBlock,sizeof(char),8,infile)) == 8 )
        {
            strategy.handler(inBlock,outBlock);
            fwrite(outBlock,sizeof(char),8,outfile);
            state.oversize += 8;
        }
    }
    if(count<8&&count>0)
    {
        char lkey[9] = "JediEncr";
        for( int i=0;i<count;i++ )
        {
            outBlock[i] = inBlock[i] ^ lkey[i];
        }

        fwrite(outBlock,sizeof(char),count,outfile);
        state.oversize += count;
    }

    fclose(infile);
    fclose(outfile);

    state.over = true;
    state.state_str = "完成";
}
