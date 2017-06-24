#include "includes/notemodel.h"

NoteModel::NoteModel()
{

}

Qt::ItemFlags NoteModel::flags(const QModelIndex &index) const
{
    return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    return QVariant();
}

QVariant NoteModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return QVariant();
}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    return 0;
}

int NoteModel::columnCount(const QModelIndex &parent) const
{
    return 0;
}
