#ifndef IMAGEBASECONVERTER_H
#define IMAGEBASECONVERTER_H

#include <QObject>

class ImageBaseConverter : public QObject
{
    Q_OBJECT
public:
    explicit ImageBaseConverter(QObject *parent = nullptr);

signals:

public slots:
};

#endif // IMAGEBASECONVERTER_H