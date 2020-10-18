#ifndef SYSCONFIG_H
#define SYSCONFIG_H

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

class SysConfig
{
protected:
    SysConfig();

public:
    static SysConfig *initance();
    bool save();

    QJsonObject json;

private:
    static SysConfig* p;
};

#endif // SYSCONFIG_H
