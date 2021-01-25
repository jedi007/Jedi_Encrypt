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
    FILE *infile = nullptr,*outfile = nullptr;

    void encypt_alg();
    void decypt_alg();

    void init_infile();
};

#endif // ENCRYPTMODEL_H
