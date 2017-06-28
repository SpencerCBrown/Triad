#include "includes/imagebaseconverter.h"

#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QMimeType>

#include <QDebug>

ImageBaseConverter::ImageBaseConverter(QObject *parent) : QObject(parent)
{

}

QString ImageBaseConverter::gen(QString path)
{
    path = path.right(path.length() - 7); //For some reason QIODevice::read() doesn't like fully qualified url strings, so I had to remove the file:// prefix.
    QFile imageFile(path);
    if (!imageFile.open(QIODevice::ReadOnly)) {
        qDebug() << imageFile.errorString();
    }
    QMimeDatabase db;
    QMimeType type = db.mimeTypeForFile(QFileInfo(imageFile));
    QString typeName = type.name();
    if (typeName == "image/jpeg") {
        typeName = "jpg";
    } else if (typeName == "image/png") {
        typeName = "png";
    } else {
        qDebug() << "Unsupported image filetype.  SHOUT at the developer to fix this.";
    }

    QByteArray buf(imageFile.readAll());
    QString imageB64 = buf.toBase64();
    QString formattedSrcAttr("<img alt=\"Embedded Image\" src=\"data:image/" + typeName + ";base64," + imageB64 + "\" />");
    return formattedSrcAttr;
}
