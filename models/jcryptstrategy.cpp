#include "jcryptstrategy.h"

#include <QCryptographicHash>
#include <QDebug>

int JCryptStrategy::S[8][8] =  {{15,2,13,7,5,8,12,33},
                                 {48,23,0,16,11,50,22,10},
                                 {6,17,1,4,41,18,26,62},
                                 {25,37,39,42,3,49,9,59},
                                 {55,57,43,44,14,24,61,63},
                                 {32,28,30,20,19,27,21,29},
                                 {45,60,47,38,40,51,35,54},
                                 {31,46,36,52,56,34,58,53}};

JCryptStrategy::JCryptStrategy(QString t_key)
{
    memcpy(key,t_key.toUtf8().data(),16);
}

void JCryptStrategy::S8_en_block(QByteArray &block)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            tmp[S[i][j]] = block[i]>>(7-j)&0X01;
        }
    }

    char tmpout;
    for(int i=0;i<8;i++)
    {
        tmpout = '\0';
        for(int j=0;j<8;j++)
        {
            tmpout |= tmp[i*8+j]<<(7-j);
        }
        block[i] = tmpout;
    }
}

void JCryptStrategy::S8_de_block(QByteArray &block)
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            tmp[i*8+j] = block[i]>>(7-j)&0X01;
        }
    }

    char tmpout;
    for(int i=0;i<8;i++)
    {
        tmpout='\0';
        for(int j=0;j<8;j++)
        {
            tmpout |= tmp[S[i][j]]<<(7-j);
        }
        block[i] = tmpout;
    }
}

JCryptStrategy_low::JCryptStrategy_low(QString t_key):JCryptStrategy(t_key)
{

}

void JCryptStrategy_low::handle(char in[8], char out[8])
{
    for(int i=0;i<8;i++)
    {
        out[i] = in[i] ^ key[i];
    }
}

JCryptStrategy_mid::JCryptStrategy_mid(QString t_key):JCryptStrategy(t_key)
{

}

void JCryptStrategy_mid::handle(char in[8], char out[8])
{
//    block.resize(8);
//    for(int i=0;i<8;i++)
//    {
//        block[i] = block[i] ^ key[i];
//    }

//    S8_en_block(block);
}

JCryptStrategy_mid_de::JCryptStrategy_mid_de(QString t_key):JCryptStrategy(t_key)
{

}

void JCryptStrategy_mid_de::handle(char in[8], char out[8])
{
//    S8_de_block(block);

//    block.resize(8);
//    for(int i=0;i<8;i++)
//    {
//        block[i] = block[i] ^ key[i];
//    }
}

JCryptStrategy_controller::JCryptStrategy_controller(QString key, bool b_decrypt, int lv)
{
    QString ba = QString("LiJie888%1").arg(key);
    key = QCryptographicHash::hash(ba.toUtf8(), QCryptographicHash::Md5).toHex();
    qDebug()<<" new key size: "<<key.size()<<"   "<<key<<endl;

    switch (lv) {
        case 2 :
        {
            if(b_decrypt)
                strategey = new JCryptStrategy_mid_de(key);
            else
                strategey = new JCryptStrategy_mid(key);
            break;
        }
        case 3 :
        {
            if(b_decrypt)
                strategey = new JCryptStrategy_mid_de(key);
            else
                strategey = new JCryptStrategy_mid(key);
            break;
        }
        default:
            strategey = new JCryptStrategy_low(key);
    }
}

JCryptStrategy_controller::~JCryptStrategy_controller()
{
    if(strategey)
        delete  strategey;
}

void JCryptStrategy_controller::handler(char in[8], char out[8])
{
    strategey->handle(in,out);
}
