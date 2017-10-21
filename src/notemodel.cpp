/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
// Copyright (C) 2017 Spencer Brown <spencerb@warpmail.net>

#include "includes/notemodel.h"
#include <QFile>
#include <QDebug>
#include <QDomNode>

NoteModel::NoteModel(QObject *parent)
    : QAbstractItemModel(parent), m_domDocument()
{
    QFile file("mynotes.xml.trd");
    if (file.exists()) {
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        m_domDocument.setContent(&file, false);
        file.close();
    }
    m_rootItem = new DomItem(m_domDocument, 0);
}

NoteModel::~NoteModel()
{
    saveToDisk();
    delete m_rootItem;
}

Qt::ItemFlags NoteModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return 0;
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsSelectable;
}

QHash<int, QByteArray> NoteModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Title] = "title";
    roles[Content] = "content";
    roles[XPosition] = "xPos";
    roles[YPosition] = "yPos";
    return roles;
}

QVariant NoteModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == NoteModelRoles::Title) {
        DomItem *item = static_cast<DomItem*>(index.internalPointer());
        QDomNode node = item->node();
        QDomNamedNodeMap atts = node.attributes();
        if (atts.contains("title")) {
            QDomAttr attr = atts.namedItem("title").toAttr();
            return attr.value();
        } else {
            return QVariant();
        }
    } else if (role == NoteModelRoles::Content) {
        DomItem *item = static_cast<DomItem*>(index.internalPointer());
        QDomNode node = item->node();
        if (node.nodeName() == "ContentContainer") {
            return node.firstChild().toCDATASection().data();
        }
        return QVariant();
    }
    return QVariant();
}

bool NoteModel::insertRows(int position, int count, const QModelIndex &index)
{
    Q_UNUSED(position)
    Q_UNUSED(count)

    if (!index.isValid()) {
        return false;
    }

    beginInsertRows(index, rowCount(index) + 1, rowCount(index) + 1);
    DomItem* parentItem = static_cast<DomItem*>(index.internalPointer());
    QDomNode parentNode = parentItem->node();
    QDomElement contentContainer = m_domDocument.createElement("ContentContainer");
    QDomCDATASection cdataContent = m_domDocument.createCDATASection("");
    contentContainer.appendChild(cdataContent);
    parentNode.appendChild(contentContainer);
    endInsertRows();
    return true;
}

bool NoteModel::removeRows(int position, int count, const QModelIndex &index)
{
    Q_UNUSED(position)
    Q_UNUSED(count)
    if (!index.isValid()) {
        return false;
    }

    beginRemoveRows(index, position, position + count - 1);
    //TODO implement
    endRemoveRows();
    return true;
}

QVariant NoteModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(section)
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    return QVariant();
}

QModelIndex NoteModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent)) {
        return QModelIndex();
    }
        DomItem *parentItem;

        if (!parent.isValid()) {
            parentItem = m_rootItem;
        } else {
            parentItem = static_cast<DomItem*>(parent.internalPointer());
        }
        DomItem *childItem = parentItem->child(row);
        if (childItem)
            return createIndex(row, column, childItem);
        else
            return QModelIndex();
}

bool NoteModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == NoteModelRoles::Content) {
        DomItem *item = static_cast<DomItem*>(index.parent().internalPointer());
        QDomNode node = item->node();

        QString currentContents = value.toString();
        QDomCDATASection section = node.toElement().firstChild().toCDATASection();
        QString oldContents = section.data();
        if (oldContents != currentContents) {
            section.setNodeValue(currentContents);
        }
        return true;
    } else if (index.isValid() && role == NoteModelRoles::Title) {
        //set title attribute of non-root node.
        return true;
    } else if (index.isValid() && role == NoteModelRoles::XPosition) {
        DomItem *item = static_cast<DomItem*>(index.parent().internalPointer());
        QDomNode node = item->node();
        QDomElement element = node.toElement();

        double xCoordinateValue = value.toDouble();
        element.setAttribute("XPos", xCoordinateValue);
        return true;
    } else if (index.isValid() && role == NoteModelRoles::YPosition) {
        DomItem *item = static_cast<DomItem*>(index.parent().internalPointer());
        QDomNode node = item->node();
        QDomElement element = node.toElement();

        double yCoordinateValue = value.toDouble();
        element.setAttribute("YPos", yCoordinateValue);
        return true;
    }
    return false;
}

void NoteModel::saveToDisk()
{
    QFile file("mynotes.xml.trd");
    QString xml = m_domDocument.toString();
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QTextStream stream(&file);
    stream << xml;
    file.close();
}

QModelIndex NoteModel::parent(const QModelIndex &child) const
{
    if (!child.isValid())
        return QModelIndex();

    DomItem *childItem = static_cast<DomItem*>(child.internalPointer());
    DomItem *parentItem = childItem->parent();

    if (!parentItem || parentItem == m_rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int NoteModel::rowCount(const QModelIndex &parent) const
{
    if (parent.column() > 0)
            return 0;

    DomItem *parentItem;

    if (!parent.isValid()) {
        parentItem = m_rootItem;
    } else {
        parentItem = static_cast<DomItem*>(parent.internalPointer());
    }

    return parentItem->node().childNodes().count();
}

int NoteModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 1;
}
