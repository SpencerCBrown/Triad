#include "includes/storageinterface.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDomNode>

StorageInterface::StorageInterface(QObject *parent) : QObject(parent)
{
    m_domDocument = new QDomDocument();
    QDomElement root = m_domDocument->createElement("MyNotes");
    m_domDocument->appendChild(root);
}

void StorageInterface::saveDoc()
{
    QString xml = m_domDocument->toString();
    QFile file("mynotes.xml.trd");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    stream << xml;
    file.close();
}

QVariant StorageInterface::createNode()
{
    QDomElement root = m_domDocument->firstChildElement();
    QDomElement* element = new QDomElement(m_domDocument->createElement("ContentContainer"));
    QDomText* tempNode = new QDomText(m_domDocument->createTextNode(""));
    element->appendChild(*tempNode);
    root.appendChild(*element);

    QVariant test = QVariant::fromValue(tempNode);
    return test;
}
