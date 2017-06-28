#ifndef IMAGEBASECONVERTER_H
#define IMAGEBASECONVERTER_H

#include <QObject>

class ImageBaseConverter : public QObject
{
    Q_OBJECT
public:
    explicit ImageBaseConverter(QObject *parent = nullptr);
    Q_INVOKABLE QString gen(QString path);

signals:

public slots:
};

#endif // IMAGEBASECONVERTER_H
