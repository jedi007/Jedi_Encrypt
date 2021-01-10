#ifndef ENCRYPTLISTMODEL_H
#define ENCRYPTLISTMODEL_H

#include <QAbstractTableModel>
#include <QUuid>

class EncryptState
{
public:
    QString filename;
    double percent = 0;
    QUuid id;
};

class EncryptListModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    EncryptListModel(QObject *parent);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

//    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;
//    Qt::ItemFlags flags(const QModelIndex & index) const override ;

    void setPath(QString path);
    void readPath(QString path);

    QList<EncryptState> status;

private:
    void refresh();
};

#endif // ENCRYPTLISTMODEL_H
