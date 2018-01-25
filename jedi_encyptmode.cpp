#include "jedi_encyptmode.h"

int Jedi_encyptmode::S[8][8] =  {{15,2,13,7,5,8,12,33},
                                 {48,23,0,16,11,50,22,10},
                                 {6,17,1,4,41,18,26,62},
                                 {25,37,39,42,3,49,9,59},
                                 {55,57,43,44,14,24,61,63},
                                 {32,28,30,20,19,27,21,29},
                                 {45,60,47,38,40,51,35,54},
                                 {31,46,36,52,56,34,58,53}};

Jedi_encyptmode::Jedi_encyptmode(QString filenametmp,int IDtmp)
{
    filename = filenametmp;
    outfilename = "";
    key = "";
    processval=0;
    cyptmodel = "待设置";
    ID = IDtmp;
    cyptLV = 0;
    statu = "";
    pause_mutex = new QMutex;
}

void Jedi_encyptmode::run()
{
    if(cyptmodel == "待设置")
        return;
    if(cyptmodel == "encypt")
    {
        //qDebug()<<"do encypt"<<endl;
        statu = "running";
        Encypt_alg();
    }
    else if(cyptmodel == "decypt")
    {
        //qDebug()<<"do decypt"<<endl;
        statu = "running";
        Decypt_alg();
    }
    signalmanage.Emit_onethread_finished(ID);
}

void Jedi_encyptmode::Encypt_alg()
{
    QTime timestart = QTime::currentTime();

    FILE *encyptfile,*outfile;
    int count = 0;
    char plainBlock[8],cipherBlock[8],subKeys[8];

    QTextCodec *code = QTextCodec::codecForName("System");
    std::string name = code->fromUnicode(filename).data();
    const char *cipherFile=name.c_str();
    //qDebug()<<"ID:"<<ID<<"cipherFile:"<<cipherFile<<endl;
    if((encyptfile = fopen(cipherFile,"rb")) == NULL)
    {
        qDebug()<<"ID:"<<ID<<"open cipherFile failed"<<endl;
        return;
    }

    //密文文件配置---------------------------------------------------------
    QString file_name, file_path;
    QFileInfo fi;
    fi = QFileInfo(filename);
    file_name = fi.fileName();
    file_path = fi.absolutePath();
    outfilename +="/Encypted--"+file_name+".mept";

    std::string name2 = code->fromUnicode(outfilename).data();
    const char *outFile=name2.c_str();
    if((outfile = fopen(outFile,"wb")) == NULL)
    {
        fclose(encyptfile);
        qDebug()<<"ID:"<<ID<<"open outfile failed"<<endl;
        return;
    }

    std::string filenametemp_stds = code->fromUnicode(file_name).data();
    const char *filenametemp_char=filenametemp_stds.c_str();
    char *filenametemp_charwrite=new char[512];
    memset(filenametemp_charwrite,'\0',512*sizeof(char));
    memcpy(filenametemp_charwrite,filenametemp_char,int(strlen(filenametemp_char)));
    fwrite(filenametemp_charwrite,sizeof(char),512,outfile);
    //密文文件配置完成--------------------------------------------------------

    //准备秘钥
    makekeys(subKeys);

    fseek(encyptfile,0,SEEK_END);   //将文件指针置尾
    long longfileLen = ftell(encyptfile);    //取文件指针当前位置

    if(longfileLen == -1)
    {
        QString qfliename = QString::fromLocal8Bit(cipherFile);
        QFile qfile(qfliename);
        fileLen = qfile.size();
    }
    else
        fileLen = longfileLen;
    rewind(encyptfile);             //将文件指针重指向文件头
    T=0;
    while(!feof(encyptfile))
    {
        //每次读8个字节，并返回成功读取的字节数
        if((count = fread(plainBlock,sizeof(char),8,encyptfile)) == 8 )
        {
            if(T%102400 == 0)
            {
                pause_mutex->lock();
                Q_EMIT refresh(ID);
                pause_mutex->unlock();
            }

            Encypt_block(plainBlock,subKeys,cipherBlock);
            fwrite(cipherBlock,sizeof(char),8,outfile);

            T +=8;
        }
        else
        {
            //qDebug()<<"fread failed and read count:"<<count<<endl;
        }
    }
    if(count<8&&count>0)
    {
        //填充
        memset(plainBlock + count,'\0',7 - count);
        plainBlock[7] = 8 - count;

        Encypt_block(plainBlock,subKeys,cipherBlock);
        fwrite(cipherBlock,sizeof(char),8,outfile);
        T +=8;
    }

    processval=1;
    Q_EMIT refresh(ID);
    fclose(encyptfile);
    fclose(outfile);

    //qDebug()<<"ID:"<<ID<<": thread use time:"<<timestart.elapsed()<<endl;
}

void Jedi_encyptmode::Decypt_alg()
{
    QTime timestart = QTime::currentTime();

    FILE *encyptfile,*outfile;
    int count = 0;
    T=0;
    char plainBlock[8],cipherBlock[8],subKeys[8];

    QTextCodec *code = QTextCodec::codecForName("System");
    std::string name = code->fromUnicode(filename).data();
    const char *cipherFile=name.c_str();
    //qDebug()<<"cipherFile:"<<cipherFile<<endl;
    if((encyptfile = fopen(cipherFile,"rb")) == NULL)
    {
        qDebug()<<"ID:"<<ID<<"open cipherFile failed"<<endl;
        return;
    }

    //获取密文大小
    fseek(encyptfile,0,SEEK_END);   //将文件指针置尾
    long longfileLen = ftell(encyptfile);    //取文件指针当前位置
    if(longfileLen == -1)
    {
        QString qfliename = QString::fromLocal8Bit(cipherFile);
        QFile qfile(qfliename);
        fileLen = qfile.size();
    }
    else
        fileLen = longfileLen;
    rewind(encyptfile);             //将文件指针重指向文件头
    //qDebug()<<"ID:"<<ID<<"线程里fileLen:"<<fileLen;


    //设置明文文件-----------------------------------------------------
    char *filename_temp2=new char[512];
    fread(filename_temp2,sizeof(char),512,encyptfile);
    T += 512;
    QString filename_temp=QString::fromLocal8Bit(filename_temp2);
    outfilename +="/Decypted--"+filename_temp;
    //qDebug()<<"ID:"<<ID<<"outfilename:"<<outfilename;

    std::string name2 = code->fromUnicode(outfilename).data();
    const char *outFile=name2.c_str();
    if((outfile = fopen(outFile,"wb")) == NULL)
    {
        fclose(encyptfile);
        qDebug()<<"ID:"<<ID<<"open outfile failed"<<endl;
        return;
    }
    //qDebug()<<"ID:"<<ID<<"open outfile success"<<endl;
    //设置明文文件完毕-----------------------------------------------------


    //准备秘钥
    makekeys(subKeys);

    while(!feof(encyptfile))
    {
        fread(plainBlock,sizeof(char),8,encyptfile);//解密时密文文件长度一定是8的整数倍
        Decypt_block(plainBlock,subKeys,cipherBlock);
        T += 8;

        if(T%102400 == 0)
        {
            pause_mutex->lock();
            Q_EMIT refresh(ID);
            pause_mutex->unlock();
        }

        if(T < fileLen)
        {
            fwrite(cipherBlock,sizeof(char),8,outfile);
        }
        else
        {
            break;
        }
    }
    //判断末尾是否被填充
    if(cipherBlock[7] < 8 && cipherBlock[7] > 0)
    {
        for(count = 8 - cipherBlock[7]; count < 7; count++)
        {
            if(cipherBlock[count] !='\0')
            {
                break;
            }
        }
    }
    if(count == 7)
    {//有填充
        //qDebug()<<"find tianchong in decypt"<<endl;
        fwrite(cipherBlock,sizeof(char),8 - cipherBlock[7],outfile);
        T -= cipherBlock[7];
    }
    else
    {//无填充
        //qDebug()<<"didn't find tianchong in decypt"<<endl;
        fwrite(cipherBlock,sizeof(char),8,outfile);
    }

    processval=1;
    Q_EMIT refresh(ID);
    fclose(encyptfile);
    fclose(outfile);
    //qDebug()<<"ID:"<<ID<<"encyptfile and outfile closed and T:"<<T<<endl;

    encyptfile = NULL;
    outfile = NULL;
    delete encyptfile;
    delete outfile;

    //qDebug()<<"ID:"<<ID<<": thread use time:"<<timestart.elapsed()<<endl;
}

void Jedi_encyptmode::makekeys(char subKeys[8])
{
    QTextCodec *code = QTextCodec::codecForName("System");
    std::string strc = code->fromUnicode(key).data();
    const char *keyp=strc.c_str();


//    char *keyp = key.toLocal8Bit().data();
    int count = key.size();

    QString str = "";
    QString strkeyp = "";
    for(int i = 0;i<count;i++)
    {
        str += QString::number(int(keyp[i]))+" ";
    }
    strkeyp = str;

    if(count>=8)
    {
        memcpy(subKeys,keyp,8);
    }
    else
    {
        memcpy(subKeys,keyp,count);
        memset(subKeys+count,'\0',7-count);
        subKeys[7]=8-count;
    }

    str = "";
    for(int i = 0;i<8;i++)
    {
        str += QString::number(int(subKeys[i]))+" ";
    }
    //qDebug()<<"ID:"<<ID<<"cyptLV:"<<cyptLV<<"key keyp subKeys:"<<key<<" "<<keyp<<" "<<str<<endl;
}


void Jedi_encyptmode::Encypt_block(char in[8], char subKeys[8], char out[8])
{
    for(int i=0;i<8;++i)
    {
        out[i] = in[i] ^ subKeys[i];
    }
    if(cyptLV==2)
    {
        En_c8_S_c8(out);
    }
    if(cyptLV==3)
    {
        for(int i=0;i<8;++i)
        {
            out[i] = out[i] ^ subKeys[i];
        }
    }

}

void Jedi_encyptmode::En_c8_S_c8(char in[8])
{
    char tmp[64];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            tmp[S[i][j]] = in[i]>>(7-j)&0X01;
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
        in[i] = tmpout;
    }
}

void Jedi_encyptmode::Decypt_block(char in[8], char subKeys[8], char out[8])
{
    if(cyptLV==3)
    {
        for(int i=0;i<8;++i)
        {
            in[i] = in[i] ^ subKeys[i];
        }
    }

    if(cyptLV==2)
    {
        De_c8_S_c8(in);
    }

    for(int i=0;i<8;++i)
    {
        out[i] = in[i] ^ subKeys[i];
    }
}

void Jedi_encyptmode::De_c8_S_c8(char in[8])
{
    char tmp[64];
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            tmp[i*8+j] = in[i]>>(7-j)&0X01;
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
        in[i] = tmpout;
    }
}

void Jedi_encyptmode::thread_pause()
{    
    if(statu == "running")
    {
        pause_mutex->lock();
        statu = "pause";
    }
}

void Jedi_encyptmode::thread_continue()
{
    if(statu == "pause")
    {
        pause_mutex->unlock();
        statu = "running";
    }
}
















