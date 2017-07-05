#include "includes/storageinterface.h"
#include <QDebug>
#include <QDomNode>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

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

void StorageInterface::saveDoc()
{
    QFile file("mynotes.xml.trd");
    QString xml = m_domDocument->toString();
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    stream << xml;
    file.close();
}

QVariant StorageInterface::createNode()
{
    QDomElement root = m_domDocument->firstChildElement();
    QDomElement* element = new QDomElement(m_domDocument->createElement("ContentContainer"));
    QDomText tempNode = m_domDocument->createTextNode("");
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
    emit containersLoaded(m_loadedElements.length());
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
    return m_loadedElements.last()->firstChild().toText().data();
}

QDomElement* StorageInterface::popElement()
{
    if (m_loadedElements.isEmpty()) {
        qDebug() << "Severe logic error";
        return nullptr;
    }
    return m_loadedElements.takeLast();
}

StorageInterface::~StorageInterface()
{
    delete m_domDocument;
}
