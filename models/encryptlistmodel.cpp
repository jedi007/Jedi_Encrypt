#include "encryptlistmodel.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

EncryptListModel::EncryptListModel(QObject *parent):QAbstractTableModel(parent)
{

}

int EncryptListModel::rowCount(const QModelIndex &parent) const
{
    return status.size();
}

int EncryptListModel::columnCount(const QModelIndex &parent) const
{
    return 2;
}

QVariant EncryptListModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    // generate a log message when this method gets called
    //qDebug() << QString("row %1, col%2, role %3").arg(row).arg(col).arg(role);

    switch(role){
    case Qt::DisplayRole:
        switch (col) {
            case 0:
            {
                return status.at(row).filename;
            }
            break;
            case 1:
            {
                return QString("%1%").arg(status.at(row).percent);
            }
            break;
        }
        break;
    }
    return QVariant();
}

QVariant EncryptListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
            case 0:
                return "文件名";
                break;
            case 1:
                return "完成率";
                break;
            default:
                return QVariant();
        }
    }
    return QVariant();
}

void EncryptListModel::setPath(QString path)
{
    qDebug()<<"EncryptListModel::setPath called "<<path<<endl;

    status.clear();

    readPath(path);

    refresh();
}

void EncryptListModel::readPath(QString path)
{
    QFileInfo finfo(path);
    if( finfo.isFile() )
    {
        qDebug()<<path<<" is file"<<endl;
        EncryptState state;
        state.filename = path;
        status.append(state);
        return;
    }
    else if (finfo.isDir())
    {
        qDebug()<<path<<" is dir"<<endl;
        QDir dir(path);

        QStringList list  = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Files, QDir::Name);

        qDebug()<<"list : "<<list<<endl;
        foreach (QString name, list)
        {
            readPath(path+"/"+name);
        }
    }
}

void EncryptListModel::refresh()
{
    beginResetModel();

    endResetModel();
}
