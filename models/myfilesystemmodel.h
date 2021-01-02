#ifndef MYFILESYSTEMMODELMY_H
#define MYFILESYSTEMMODELMY_H

#include <QFileSystemModel>

class MyFileSystemModel : public QFileSystemModel
{
    Q_OBJECT
public:
    explicit MyFileSystemModel(QObject *parent = nullptr);
    ~MyFileSystemModel();

    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
    QModelIndex index(const QString &path, int column = 0) const;

    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

    QString path(const QModelIndex &index);
};

#endif // MYFILESYSTEMMODELMY_H
