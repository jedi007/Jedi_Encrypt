#ifndef JCRYPTSTRATEGY_H
#define JCRYPTSTRATEGY_H

#include <QByteArray>
#include <QString>

class JCryptStrategy
{
public:
    JCryptStrategy(QString t_key);
    virtual ~JCryptStrategy(){}

    virtual void handle(char in[8], char out[8]) = 0;

protected:
    void S8_en_block(char block[8]);
    void S8_de_block(char block[8]);

    char key[32];
    char tmp[64];
    static int S[8][8];
    int keyindex = 0;
};

class JCryptStrategy_low:public JCryptStrategy
{
public:
    JCryptStrategy_low(QString t_key);
    virtual ~JCryptStrategy_low(){}

    virtual void handle(char in[8], char out[8]);
};

class JCryptStrategy_mid:public JCryptStrategy
{
public:
    JCryptStrategy_mid(QString t_key);
    virtual ~JCryptStrategy_mid(){}

    virtual void handle(char in[8], char out[8]);
};

class JCryptStrategy_mid_de:public JCryptStrategy
{
public:
    JCryptStrategy_mid_de(QString t_key);
    virtual ~JCryptStrategy_mid_de(){}

    virtual void handle(char in[8], char out[8]);
};

class JCryptStrategy_hig:public JCryptStrategy
{
public:
    JCryptStrategy_hig(QString t_key);
    virtual ~JCryptStrategy_hig(){}

    virtual void handle(char in[8], char out[8]);
};

class JCryptStrategy_hig_de:public JCryptStrategy
{
public:
    JCryptStrategy_hig_de(QString t_key);
    virtual ~JCryptStrategy_hig_de(){}

    virtual void handle(char in[8], char out[8]);
};

class JCryptStrategy_controller
{
public:
    JCryptStrategy_controller(QString key,bool b_decrypt=false,int lv=1);
    ~JCryptStrategy_controller();
    void handler(char in[8], char out[8]);

private:
    JCryptStrategy* strategey = nullptr;
};

#endif // JCRYPTSTRATEGY_H
