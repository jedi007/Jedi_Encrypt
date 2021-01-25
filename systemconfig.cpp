#include "systemconfig.h"

#include <QFile>
#include <QMessageBox>

SystemConfig* SystemConfig::p = nullptr;
QMutex SystemConfig::mutex;

SystemConfig::SystemConfig()
{
    filename = "./config.dat";

    obj.insert(DF_crypt_lv,1);
    obj.insert(DF_no_outdir,true);
    obj.insert(DF_outdir_str,"");
    obj.insert(DF_threads_count,2);

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

void SystemConfig::save()
{
    QFile file(filename);
    if( !file.open(QFile::WriteOnly) )
    {
        //QMessageBox::information(nullptr,"设置失败","配置文件保存失败" );
        return;
    }

    QJsonDocument doc(obj);
    QByteArray bytes = doc.toJson();
    file.write( bytes );
    file.close();
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





