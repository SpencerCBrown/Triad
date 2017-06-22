#ifndef DOCUMENTHANDLER_H
#define DOCUMENTHANDLER_H

#include <QObject>
#include <QTextDocument>
#include <QQuickTextDocument>

class DocumentHandler : public QObject
{
    Q_OBJECT
public:
    explicit DocumentHandler(QObject *parent = nullptr);
    Q_PROPERTY(QQuickTextDocument* textDocument READ getTextDocument WRITE setTextDocument)
    void setTextDocument(QQuickTextDocument* textdoc);
    QQuickTextDocument* getTextDocument();
signals:
    void emitChanges();
public slots:
    void change();
private:
    QQuickTextDocument* m_textDocument;
};

#endif // DOCUMENTHANDLER_H
