#include "sysconfig.h"

#define SYSCON_FILENAME "sysconfig.json"

#include <QDebug>

SysConfig* SysConfig::p = new SysConfig;

SysConfig::SysConfig()
{
    QFile config_file(SYSCON_FILENAME);
    if(config_file.exists() && config_file.open(QFile::ReadOnly))
    {
        QJsonParseError jsonError;
        QJsonDocument doucment = QJsonDocument::fromJson(config_file.readAll(), &jsonError);
        if (!doucment.isNull() && (jsonError.error == QJsonParseError::NoError))
        {
            if (doucment.isObject())
            {
                json = doucment.object();
                qDebug()<<"its json : "<<json<<endl;
            }
        }

        config_file.close();
    }
}

SysConfig *SysConfig::initance()
{
    return p;
}

bool SysConfig::save()
{
    QJsonDocument doc;
    doc.setObject(json);

    QByteArray data = doc.toJson();

    QFile config_file(SYSCON_FILENAME);
    if( config_file.open(QIODevice::WriteOnly) )
    {
        config_file.write(data);
        config_file.close();
        return true;
    }
    return false;
}
