#include "systemconfig.h"

#include <QFile>

SystemConfig* SystemConfig::p = nullptr;
QMutex SystemConfig::mutex;

SystemConfig::SystemConfig()
{
    filename = "./config.dat";

    obj.insert(DF_crypt_lv,1);
    obj.insert(DF_no_outdir,true);

    read();
}

SystemConfig *SystemConfig::getinstance()
{
    if( !p )
    {
        QMutexLocker locker(&mutex);
        if( !p )
        {
            p = new SystemConfig();
        }
    }
    return p;
}

bool SystemConfig::save()
{
    QFile file(filename);
    if( !file.open(QFile::WriteOnly) )
        return false;

    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();
    file.write( bytes );
    file.close();

    return true;
}

void SystemConfig::read()
{
    QFile file(filename);
    if( !file.open(QFile::ReadOnly) )
        return;

    QByteArray bytes = file.readAll();
    file.close();
    QJsonDocument doc = QJsonDocument::fromJson(bytes);
    obj = doc.object();
}





