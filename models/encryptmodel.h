#ifndef ENCRYPTMODEL_H
#define ENCRYPTMODEL_H

#include <QRunnable>
#include <QObject>

#include "encryptlistmodel.h"

class EncryptModel : public QRunnable
{

public:
    EncryptModel(EncryptState& t_state);

    virtual void run() override;

private:
    EncryptState& state;
};

#endif // ENCRYPTMODEL_H
