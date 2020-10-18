#include "myfilesystemmodel.h"

#include <QDebug>

#include <QDateTime>

MyFileSystemModel::MyFileSystemModel(QObject *parent) : QFileSystemModel(parent)
{

}

MyFileSystemModel::~MyFileSystemModel()
{

}

QModelIndex MyFileSystemModel::index(int row, int column, const QModelIndex &parent) const
{
    return QFileSystemModel::index(row,column,parent);
}

QModelIndex MyFileSystemModel::index(const QString &path, int column) const
{
    return QFileSystemModel::index(path,column);
}

QModelIndex MyFileSystemModel::parent(const QModelIndex &child) const
{
    return QFileSystemModel::parent(child);
}

int MyFileSystemModel::rowCount(const QModelIndex &parent) const
{
    return QFileSystemModel::rowCount(parent);
}

int MyFileSystemModel::columnCount(const QModelIndex &parent) const
{
    return 1;
    //return QFileSystemModel::columnCount(parent);
}

QVariant MyFileSystemModel::data(const QModelIndex &index, int role) const
{
    if(role != Qt::DisplayRole)
        return QFileSystemModel::data(index,role);

    QFileInfo finfo = fileInfo(index);
    if(index.column() == 0)
    {
        QString filename = finfo.baseName();
        if(filename.isEmpty())
            filename = finfo.absolutePath().replace("/","");
        else if( !finfo.suffix().isEmpty() )
            filename += "."+finfo.suffix();

        return filename;
    }
    else if(index.column() == 1)
    {
        QString file_birthtime = finfo.birthTime().toString("yyyy-MM-dd");
        return file_birthtime;
    }
    return QFileSystemModel::data(index,role);
}

QVariant MyFileSystemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
    {
        switch (section)
        {
            case 0:
                return "文件名";
                break;
            case 1:
                return "创建日期";
                break;
            default:
                return QVariant();
        }
    }
    return QVariant();
}
