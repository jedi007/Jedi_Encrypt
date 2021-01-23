#include "encryptmodel.h"

#include <QThread>
#include <QDebug>
#include <QDateTime>
#include <QFile>

int EncryptModel::S[8][8] =  {{15,2,13,7,5,8,12,33},
                                 {48,23,0,16,11,50,22,10},
                                 {6,17,1,4,41,18,26,62},
                                 {25,37,39,42,3,49,9,59},
                                 {55,57,43,44,14,24,61,63},
                                 {32,28,30,20,19,27,21,29},
                                 {45,60,47,38,40,51,35,54},
                                 {31,46,36,52,56,34,58,53}};

EncryptModel::EncryptModel(EncryptState& t_state):state(t_state)
{

}

void EncryptModel::run()
{
    qDebug()<<"state.id is "<< state.id.data1 <<" thread ID is  "<<QThread::currentThreadId()<<endl;
    state.state_str = "计算中...";
    for(int i=0;i<=20;i++)
    {
        QThread::msleep(100);
        state.percent = i;
    }

    encypt_alg();
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
        state.state_str = "文件打开失败";
        return;
    }
}

void EncryptModel::decypt_alg()
{

}
