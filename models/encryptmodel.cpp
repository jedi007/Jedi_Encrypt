#include "encryptmodel.h"

#include <QThread>
#include <QDateTime>
#include <QFile>
#include <QFileInfo>
#include <QCryptographicHash>
#include <QTextCodec>
#include <iostream>
#include <QDataStream>
#include <QDir>

#include <QDebug>
#include "jcryptstrategy.h"

EncryptModel::EncryptModel(EncryptState& t_state, QString t_key,QString t_outpath,int t_crypt_lv,int t_crypt_model,bool t_delete_import_file)
    :state(t_state),key(t_key),outpath(t_outpath),crypt_lv(t_crypt_lv),crypt_model(t_crypt_model),delete_import_file(t_delete_import_file)
{

}

void EncryptModel::run()
{
    state.state_str = "计算中...";

    QTime t = QTime::currentTime();
    try

    {
        init_infile();
        init_outpath();

        if(crypt_model == 0)
        {
            encypt_init_outfile();
            encypt_alg();
        }
        else
        {
            decypt_init_outfile();
            decypt_alg();
        }

        fclose(infile);
        fclose(outfile);

        if(delete_import_file)
        {
            QFile deletefile(state.filename);
            bool ok = deletefile.remove();
            qDebug()<<"delete: "<<ok<<endl;
        }


        state.over = true;
        state.state_str = "完成";
    }
    catch (int err)
    {
        qDebug()<<"err is "<<err<<endl;
        QString errstrs[7] = {"null",
                              "输入文件打开失败","输出路径有误","输出文件打开失败",
                              "输入文件信息有误","解密配置信息不正确","输出文件打开失败",
                              };
        int index = err*-1;
        if(index < 0) index = 0;
        if(index > 6) index = 6;

        state.state_str = errstrs[index];

        if( index >= 2)
            fclose(infile);

        if( index >= 5)
            state.filesize = 1;
    }

    state.over = true;

    qDebug()<<state.filename<<"   t.elapsed(): "<<t.elapsed()<<endl;
}

void EncryptModel::encypt_alg()
{
    JCryptStrategy_controller strategy(key,false,crypt_lv);

    int count = 0;
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
}

void EncryptModel::decypt_alg()
{
    JCryptStrategy_controller strategy(key,true,crypt_lv);

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
}

void EncryptModel::init_infile()
{
    QTextCodec *code = QTextCodec::codecForName("System");
    std::string infilename = code->fromUnicode(state.filename).data();
    if((infile = fopen(infilename.c_str(),"rb")) == NULL)
        throw -1;
}

void EncryptModel::init_outpath()
{  
    if(outpath.isEmpty())
    {
        QFileInfo finfo(state.filename);
        outpath = finfo.path();
    }


    QFileInfo path_info(outpath);
    if( !path_info.isDir() )
    {
        QDir dir;
        dir.mkpath(outpath);
    }

    if( !path_info.isDir() )
        throw -2;
}

void EncryptModel::encypt_init_outfile()
{
    QTextCodec *code = QTextCodec::codecForName("System");

    QFileInfo finfo(state.filename);
    QString filename = state.filename.split("/").last();
    QStringList namelist = filename.split(".");
    if(!finfo.suffix().isEmpty() && namelist.size() > 1 )
        namelist.removeLast();
    namelist.append("jcpt");
    QString qoutfilename =  QString("%1/%2").arg(outpath).arg(namelist.join("."));

    std::string outfilename = code->fromUnicode(qoutfilename).data();
    if((outfile = fopen(outfilename.c_str(),"wb")) == NULL)
        throw -3;

    QByteArray head;
    head.resize(1024);
    state.filesize = finfo.size();
    QDataStream stream( &head , QIODevice::WriteOnly);
    stream<<filename;
    stream<<state.filesize;

    QString ba = QString("LiJie888%1_%2").arg(key).arg(crypt_lv);
    QString checkinfo = QCryptographicHash::hash(ba.toUtf8(), QCryptographicHash::Md5).toHex();
    stream<<checkinfo;

    fwrite(head.data(),sizeof(char),1024,outfile);
}

void EncryptModel::decypt_init_outfile()
{
    QTextCodec *code = QTextCodec::codecForName("System");

    char chead[1024];
    int count = fread(chead,sizeof(char),1024,infile);
    if( count != 1024 )
        throw -4;

    QByteArray head;
    QString qoutfilename,checkinfo;
    head.setRawData(chead,1024);
    QDataStream stream( &head , QIODevice::ReadOnly);
    stream>>qoutfilename;
    stream>>state.filesize;
    stream>>checkinfo;

    QString ba = QString("LiJie888%1_%2").arg(key).arg(crypt_lv);
    QString r_checkinfo = QCryptographicHash::hash(ba.toUtf8(), QCryptographicHash::Md5).toHex();
    if( checkinfo != r_checkinfo )
        throw -5;

    QFileInfo finfo(state.filename);
    qoutfilename = QString("%1/%2").arg(outpath).arg(qoutfilename);
    std::string outfilename = code->fromUnicode(qoutfilename).data();

    if((outfile = fopen(outfilename.c_str(),"wb")) == NULL)
        throw -6;
}
