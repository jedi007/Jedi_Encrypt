#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H


#include <QJsonDocument>
#include <QJsonObject>

#include <QMutex>

#define DF_crypt_lv "crypt_lv"

class SystemConfig
{
public:
    static SystemConfig* getinstance();
    void save();
    void read();

    QJsonObject obj;
    QString key;

private:
    SystemConfig();
    QString filename;

    static SystemConfig* p;
    static QMutex mutex;
};

#endif // SYSTEMCONFIG_H
