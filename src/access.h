#ifndef ACCESS_H
#define ACCESS_H

#include <QObject>

class Access : public QObject
{
    Q_OBJECT
public:
    explicit Access(QObject *parent = 0);

signals:

public slots:
};

#endif // ACCESS_H