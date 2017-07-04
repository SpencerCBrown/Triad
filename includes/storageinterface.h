#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include <QObject>
#include <QDomDocument>
#include <QVariant>
#include <QFile>

Q_DECLARE_METATYPE(QDomElement *)

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
    QFile m_xmlFile;

    void createDocument();
};

#endif // STORAGEINTERFACE_H
