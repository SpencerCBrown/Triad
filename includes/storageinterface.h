#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include <QObject>
#include <QDomDocument>
#include <QVariant>
#include <QFile>

#include "includes/storageinterface.h"

Q_DECLARE_METATYPE(QDomElement *)

class StorageInterface : public QObject
{
    Q_OBJECT
public:
    explicit StorageInterface(QObject *parent = nullptr);
    ~StorageInterface();
    Q_PROPERTY(int childId READ getChildId WRITE setChildId)
    Q_INVOKABLE void saveDoc();
    Q_INVOKABLE double topXPos();
    Q_INVOKABLE double topYPos();
    Q_INVOKABLE QString topContents();
    Q_INVOKABLE void purgeElement(QVariant qdomelement);
signals:
    void containersLoaded(int numberOfLoadedElements);
    void idChanged(int id);
public slots:
    QVariant createNode();
    QVariant popElement(); //returns QDomElement*
    void finishLoading();
private:
    QDomDocument* m_domDocument;
    QList<QDomElement*> m_loadedElements;
    int m_childId;

    void createDocument();
    void loadDocument();
    void setChildId(int childId);
    int getChildId();
};

#endif // STORAGEINTERFACE_H
