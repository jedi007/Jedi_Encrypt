#ifndef SIGNALMANAGE_H
#define SIGNALMANAGE_H

#include <QObject>

class Signalmange:public QObject
{
    Q_OBJECT
public:
    Signalmange()
    {

    }
    void Emit_setting_changed(QString str)
    {
        Q_EMIT setting_changed(str);
    }
    void Emit_onethread_finished(int tmpi)
    {
        Q_EMIT onethread_finished(tmpi);
    }

signals:
    void setting_changed(QString);
    void onethread_finished(int);
};

#endif // SIGNALMANAGE_H
