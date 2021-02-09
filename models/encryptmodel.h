#ifndef ENCRYPTMODEL_H
#define ENCRYPTMODEL_H

#include <QRunnable>
#include <QObject>

class EncryptState
{
public:
    QString filename;
    qint64 filesize = 1;
    qint64 oversize = 0;
    bool over = false;
    QString state_str;
};

class EncryptModel : public QRunnable
{

public:
    EncryptModel(EncryptState& t_state, QString t_key,QString t_outpath="",int t_crypt_lv = 1,int t_crypt_model = 0,bool t_delete_import_file = false);

    virtual void run() override;

private:
    EncryptState& state;
    FILE *infile = nullptr,*outfile = nullptr;
    QString key;
    QString outpath;
    int crypt_lv;
    int crypt_model;
    bool delete_import_file = false;

    void encypt_alg();
    void decypt_alg();

    void init_infile();

    void init_outpath();

    void encypt_init_outfile();
    void decypt_init_outfile();
};

#endif // ENCRYPTMODEL_H
