#ifndef JCRYPTSTRATEGY_H
#define JCRYPTSTRATEGY_H

#include <QByteArray>
#include <QString>

class JCryptStrategy
{
public:
    JCryptStrategy(QString t_key);
    virtual ~JCryptStrategy(){}

    virtual void handle(QByteArray& block) = 0;

protected:
    void S8_en_block(QByteArray &block);
    void S8_de_block(QByteArray &block);

    QString key;
    char tmp[64];
    static int S[8][8];
};

class JCryptStrategy_low:public JCryptStrategy
{
public:
    JCryptStrategy_low(QString t_key);
    virtual ~JCryptStrategy_low(){}

    virtual void handle(QByteArray& block);
};

class JCryptStrategy_mid:public JCryptStrategy
{
public:
    JCryptStrategy_mid(QString t_key);
    virtual ~JCryptStrategy_mid(){}

    virtual void handle(QByteArray& block);
};

class JCryptStrategy_mid_de:public JCryptStrategy
{
public:
    JCryptStrategy_mid_de(QString t_key);
    virtual ~JCryptStrategy_mid_de(){}

    virtual void handle(QByteArray& block);
};

class JCryptStrategy_controller
{
public:
    JCryptStrategy_controller(QString key,bool b_decrypt=false,int lv=1);
    ~JCryptStrategy_controller();
    void handler(QByteArray& block);

private:
    JCryptStrategy* strategey = nullptr;
};

#endif // JCRYPTSTRATEGY_H
