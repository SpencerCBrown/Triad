#include "includes/storageinterface.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDomNode>

StorageInterface::StorageInterface(QObject *parent) : QObject(parent)
{
    m_domDocument = new QDomDocument("mynotes");
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
    QDomText* tempNode = new QDomText(m_domDocument->createTextNode("TestNode"));
    m_domDocument->appendChild(*tempNode);
    QVariant test = QVariant::fromValue(tempNode);
    return test;
}
