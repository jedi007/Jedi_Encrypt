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

    int model = 0;
private:
    EncryptState& state;

    void encypt_alg();
    void decypt_alg();
};

#endif // ENCRYPTMODEL_H
