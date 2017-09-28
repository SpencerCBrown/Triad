#include "includes/storageinterface.h"
#include <QDebug>
#include <QDomNode>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QModelIndex>

StorageInterface::StorageInterface(QObject *parent) : QObject(parent), m_modelParentIndexByDepth(3)
{
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

QModelIndex StorageInterface::getCurrentModelIndex()
{
    QModelIndex mIndex = QModelIndex();//m_dataModel->index(m_modelParentIndex)
    for (int i = 0; i < m_modelParentIndexByDepth.length(); ++i) {
        mIndex = m_dataModel->index(m_modelParentIndexByDepth.at(i), 0, mIndex);
    }
    return mIndex;
}

void StorageInterface::addContainer()
{
    QModelIndex parentNotepage = getCurrentModelIndex();
    m_dataModel->insertRows(0, 0, parentNotepage);
}

void StorageInterface::setContent(int index, QString contentsString)
{
    QModelIndex parentNotepage = getCurrentModelIndex();
    QModelIndex childContainer = m_dataModel->index(index, 0, parentNotepage);
    if (!childContainer.isValid()) {
        qDebug() << "invalid setcontent index";
    } else {
        m_dataModel->setData(childContainer, contentsString, NoteModel::NoteModelRoles::Content);
    }
}

void StorageInterface::setXPos(int index, double x_Pos)
{
    QModelIndex parentNotepage = getCurrentModelIndex();
    QModelIndex childContainer = m_dataModel->index(index, 0, parentNotepage);
    if (!childContainer.isValid()) {
        qDebug() << "Invalid setcontent index";
    } else {
        m_dataModel->setData(childContainer, x_Pos, NoteModel::NoteModelRoles::XPosition);
    }
}

void StorageInterface::setYPos(int index, double y_Pos)
{
    QModelIndex parentNotepage = getCurrentModelIndex();
    QModelIndex childContainer = m_dataModel->index(index, 0, parentNotepage);
    if (!childContainer.isValid()) {
        qDebug() << "Invalid setcontent index";
    } else {
        m_dataModel->setData(childContainer, y_Pos, NoteModel::NoteModelRoles::YPosition);
    }
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

void StorageInterface::setIndexForCurrentDepth(int index)
{
    m_modelParentIndexByDepth.replace(m_modelParentDepth, index);
}

int StorageInterface::getIndexForCurrentDepth()
{
    return m_modelParentIndexByDepth.at(m_modelParentDepth);
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

StorageInterface::~StorageInterface()
{
    delete m_domDocument;
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
