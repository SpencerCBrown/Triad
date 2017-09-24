#include "includes/storageinterface.h"
#include <QDebug>
#include <QDomNode>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QModelIndex>

StorageInterface::StorageInterface(QObject *parent) : QObject(parent)
{
    QFile file("mynotes.xml.trd");
    m_domDocument = new QDomDocument();
    if (file.exists()) {
        loadDocument();
    } else {
        createDocument();
    }
}

QVariant StorageInterface::createNode()
{
    QDomElement root = m_domDocument->firstChildElement();
    QDomElement* element = new QDomElement(m_domDocument->createElement("ContentContainer"));
    QDomCDATASection tempNode = m_domDocument->createCDATASection("");
    element->appendChild(tempNode);
    root.appendChild(*element);

    QVariant test = QVariant::fromValue(element);
    return test;
}

void StorageInterface::createDocument()
{
    QDomElement root = m_domDocument->createElement("MyNotes");
    m_domDocument->appendChild(root);
}

void StorageInterface::loadDocument()
{
    QFile file("mynotes.xml.trd");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    m_domDocument->setContent(&file, false);
    QDomElement rootElement = m_domDocument->firstChildElement();
    if (rootElement.childNodes().length() >= 1) {
        QDomElement tempElement = rootElement.firstChildElement();
        m_loadedElements.append(new QDomElement(tempElement));
        tempElement = tempElement.nextSiblingElement();
        while (!tempElement.isNull()) {
            m_loadedElements.append(new QDomElement(tempElement));
            tempElement = tempElement.nextSiblingElement();
        }
    }
    file.close();
}

void StorageInterface::setContent(int index, QString contentsString)
{
    //TODO implement
}

void StorageInterface::setXPos(int index, double x_Pos)
{
    //TODO
}

void StorageInterface::setYPos(int index, double y_Pos)
{
    //TODO
}

void StorageInterface::setChildId(int childId)
{
    m_childId = childId;
    emit idChanged(m_childId);
}

int StorageInterface::getChildId()
{
    return m_childId;
}

double StorageInterface::topXPos()
{
    return m_loadedElements.last()->attribute("XPos").toDouble();
}

double StorageInterface::topYPos()
{
    return m_loadedElements.last()->attribute("YPos").toDouble();
}

QString StorageInterface::topContents()
{
    return m_loadedElements.last()->firstChild().toCDATASection().data();
}

QVariant StorageInterface::popElement()
{
    if (m_loadedElements.isEmpty()) {
        qDebug() << "Severe logic error";
        return QVariant();
    }
    return QVariant::fromValue(m_loadedElements.takeLast());
}

StorageInterface::~StorageInterface()
{
    delete m_domDocument;
}

void StorageInterface::finishLoading()
{
    emit containersLoaded(m_loadedElements.length());
}

int StorageInterface::pageChildContainers()
{
    //TODO return number of children (contentContainers) in active NotePage
    //temporarily hardcoded
    QModelIndex rootItem = m_dataModel->index(0, 0);
    if (rootItem.isValid()) {
        QModelIndex notebook = m_dataModel->index(0, 0, rootItem);
        if (notebook.isValid()) {
            QModelIndex section = m_dataModel->index(0, 0, notebook);
            if (section.isValid()) {
                QModelIndex notepage = m_dataModel->index(0, 0, section);
                if (notepage.isValid()) {
                    return m_dataModel->rowCount(notepage);
                }
            }
        }
    }
    return -1;
}

void StorageInterface::setModel(NoteModel* model)
{
    m_dataModel = model;
}

NoteModel* StorageInterface::getModel()
{
    //return QVariant::fromValue(m_dataModel);
    return m_dataModel;
}

void StorageInterface::purgeElement(QVariant qdomelement)
{
    if (!qdomelement.canConvert<QDomElement*>()) {
        qDebug() << "Conversion failure";
    }
    QDomElement* tempElement = qvariant_cast<QDomElement*>(qdomelement);
    m_domDocument->firstChildElement().removeChild(*tempElement);
}
