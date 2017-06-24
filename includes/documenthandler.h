#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>
#include <QTextDocument>
#include <QQuickTextDocument>
#include <QDomNode>
#include <QVariant>
#include <QDomText>

class DocumentHandler : public QObject
{
    Q_OBJECT
public:
    explicit DocumentHandler(QObject *parent = nullptr);
    Q_PROPERTY(QQuickTextDocument* textDocument READ getTextDocument WRITE setTextDocument)
    Q_PROPERTY(QVariant node READ getNode WRITE setNode)

    void setTextDocument(QQuickTextDocument* textdoc);
    QQuickTextDocument* getTextDocument();
    void setNode(QVariant node);
    QVariant getNode();
signals:
    void emitChanges();
public slots:
    void change();
private:
    QQuickTextDocument* m_textDocument;
    QDomText* m_node;
};

#endif // DOCUMENTHANDLER_H
