#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include <QObject>

class StorageInterface : public QObject
{
    Q_OBJECT
public:
    explicit StorageInterface(QObject *parent = nullptr);

signals:

public slots:
};

#endif // STORAGEINTERFACE_H