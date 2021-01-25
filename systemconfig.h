#ifndef SYSTEMCONFIG_H
#define SYSTEMCONFIG_H


#include <QJsonDocument>
#include <QJsonObject>

#include <QMutex>

#define DF_crypt_lv "crypt_lv"
#define DF_no_outdir "no_outdir"
#define DF_outdir_str "outdir_str"
#define DF_threads_count "threads_count"

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
