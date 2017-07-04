#include "includes/storageinterface.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDomNode>

StorageInterface::StorageInterface(QObject *parent) : QObject(parent), m_xmlFile("mynotes.xml.trd")
{
    m_domDocument = new QDomDocument();
    createDocument();
}

void StorageInterface::saveDoc()
{
    QString xml = m_domDocument->toString();
    m_xmlFile.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&m_xmlFile);
    stream << xml;
    m_xmlFile.close();
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
