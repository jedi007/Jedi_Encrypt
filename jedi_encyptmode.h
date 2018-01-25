#ifndef JEDI_ENCYPTMODE_H
#define JEDI_ENCYPTMODE_H

#include <QFile>
#include <QFileInfo>
#include <iostream>

#include<QThread>
#include<QDebug>
#include<QTextCodec>

#include <QTime>
#include <QSemaphore>
#include <QMutex>

#include "global.h"

class Jedi_encyptmode: public QThread
{
    Q_OBJECT
public:
    Jedi_encyptmode(QString filenametmp,int IDtmp);

    void makekeys(char subKeys[8]);
    void Encypt_alg();
    void Decypt_alg();

    void setoutfile_path(QString outfilename_path) {outfilename = outfilename_path;}
    void setmodel(QString model) {cyptmodel = model;}
    void setkey(QString keytmp) {key = keytmp;}

    void Encypt_block(char in[8], char subKeys[8], char out[8]);
    void En_c8_S_c8(char in[8]);

    void Decypt_block(char in[8], char subKeys[8], char out[8]);
    void De_c8_S_c8(char in[8]);

    void thread_pause();
    void thread_continue();

    QString outfilename;
    QString cyptmodel;
    static QStringList thread_static_list;
protected:
    void run();

private:
    QString filename;
    QString key;


    static int S[8][8];

    QMutex *pause_mutex;

public:
    double processval;
    qint64 T;
    qint64 fileLen;
    int ID;
    int cyptLV;

    QString statu;

signals:
    void refresh(int);

};
#endif // JEDI_ENCYPTMODE_H
