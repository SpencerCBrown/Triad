#include "documenthandler.h"
#include <QDebug>

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
    emit emitChanges();
}
