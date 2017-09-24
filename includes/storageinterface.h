#ifndef STORAGEINTERFACE_H
#define STORAGEINTERFACE_H

#include <QObject>
#include <QDomDocument>
#include <QVariant>
#include <QFile>

#include "includes/storageinterface.h"
#include "includes/notemodel.h"

Q_DECLARE_METATYPE(QDomElement *)

/*!
 * \brief The StorageInterface class acts as a liason between the model and the UI.
 *
 * It keeps track of items, but in a non-implementation-defined way.  It has no knowledge of the DOM.
 */
class StorageInterface : public QObject
{
    Q_OBJECT
public:
    explicit StorageInterface(QObject *parent = nullptr);
    ~StorageInterface();
    Q_PROPERTY(int childId READ getChildId WRITE setChildId)
    Q_PROPERTY(NoteModel* nModel MEMBER m_dataModel)
    Q_INVOKABLE double topXPos();
    Q_INVOKABLE double topYPos();
    Q_INVOKABLE QString topContents();
    Q_INVOKABLE void purgeElement(QVariant qdomelement);
    Q_INVOKABLE void setContent(int index, QString contentsString);
    Q_INVOKABLE void setXPos(int index, double x_Pos);
    Q_INVOKABLE void setYPos(int index, double y_Pos);
    Q_INVOKABLE int pageChildContainers();
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
    NoteModel* m_dataModel;

    void createDocument();
    void loadDocument();
    void setChildId(int childId);
    int getChildId();
    void setModel(NoteModel* model);
    NoteModel* getModel();
};

#endif // STORAGEINTERFACE_H
