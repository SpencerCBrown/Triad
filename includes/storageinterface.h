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
    ~StorageInterface();
    Q_INVOKABLE void saveDoc();
    Q_INVOKABLE double topXPos();
    Q_INVOKABLE double topYPos();
    Q_INVOKABLE QString topContents();
signals:
    void containersLoaded(int numberOfLoadedElements);
public slots:
    QVariant createNode();
    QDomElement* popElement();
private:
    QDomDocument* m_domDocument;
    QList<QDomElement*> m_loadedElements;

    void createDocument();
    void loadDocument();
};

#endif // STORAGEINTERFACE_H
