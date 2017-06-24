#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include <QObject>
#include <QDomDocument>
#include <QVariant>

Q_DECLARE_METATYPE(QDomText *)

class StorageInterface : public QObject
{
    Q_OBJECT
public:
    explicit StorageInterface(QObject *parent = nullptr);
    Q_INVOKABLE void saveDoc();
signals:

public slots:
    QVariant createNode();
private:
    QDomDocument* m_domDocument;
};

#endif // STORAGEINTERFACE_H
