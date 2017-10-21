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
    ~DocumentHandler();
    Q_PROPERTY(QQuickTextDocument* textDocument READ getTextDocument WRITE setTextDocument)
    Q_PROPERTY(QVariant node READ getNode WRITE setNode)
    Q_PROPERTY(double xpos READ getXPos WRITE setXPos)
    Q_PROPERTY(double ypos READ getYPos WRITE setYPos)

    void setTextDocument(QQuickTextDocument* textdoc);
    QQuickTextDocument* getTextDocument();
    void setNode(QVariant node);
    QVariant getNode();
    double getXPos();
    void setXPos(double xpos);
    double getYPos();
    void setYPos(double ypos);
    QString getDocumentHtml();
signals:
    void xPositionChanged(double x_Pos);
    void yPositionChanged(double y_Pos);
    void contentsChanged(QString contentsString);
public slots:
    void change();
private:
    QQuickTextDocument* m_textDocument;
    QDomElement* m_containerElement;
    double m_xpos;
    double m_ypos;
};

#endif // DOCUMENTHANDLER_H
