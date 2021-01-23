#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H


#include <QJsonDocument>
#include <QJsonObject>

class SystemConfig
{
public:
    SystemConfig();

    void save();
    void read();

    QJsonObject obj;

private:
    QString filename;
};

#endif // SYSTEMCONFIG_H
