#include "includes/documenthandler.h"
#include <QDebug>
#include "includes/storageinterface.h"

DocumentHandler::DocumentHandler(QObject *parent) : QObject(parent)
{
}

void DocumentHandler::setTextDocument(QQuickTextDocument *textdoc)
{
    m_textDocument = textdoc;
    connect(m_textDocument->textDocument(), SIGNAL(contentsChanged()), this, SLOT(change()));
}

QQuickTextDocument* DocumentHandler::getTextDocument()
{
    return m_textDocument;
}

void DocumentHandler::change()
{
    m_node->setNodeValue(m_textDocument->textDocument()->toHtml());
}

void DocumentHandler::setNode(QVariant node)
{
    if (!node.canConvert<QDomText*>()) {
        qDebug() << "Conversion failure";
    }
    QDomText* tempNode = qvariant_cast<QDomText*>(node);
    m_node = tempNode;
}

QVariant DocumentHandler::getNode()
{
    return QVariant::fromValue(m_node);
}
