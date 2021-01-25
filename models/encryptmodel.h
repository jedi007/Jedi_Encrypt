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
    QString outpath;

    void encypt_alg();
    void decypt_alg();

    void init_infile();

    void init_outpath();

    void encypt_init_outfile();
    void decypt_init_outfile();
};

#endif // ENCRYPTMODEL_H
