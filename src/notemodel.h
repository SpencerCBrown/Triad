#ifndef NOTEMODEL_H
#define NOTEMODEL_H

#include <QAbstractItemModel>
#include <QFlags>

class NoteModel : public QAbstractItemModel
{
public:
    NoteModel();

    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
};

#endif // NOTEMODEL_H
