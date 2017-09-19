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
//Copyright (C) 2017 Spencer Brown <spencerb@warpmail.net>

#ifndef DOMITEM_H
#define DOMITEM_H
#include <QDomNode>
#include <QHash>
#include <QObject>

Q_DECLARE_METATYPE(QDomNode)

class DomItem
{
public:
    DomItem(QDomNode &node, int row, DomItem *parent = 0);
    ~DomItem();
    /*!
     * \brief child accesses a contained DomItem represented by i.
     * \param i The index of the desired child DomItem
     * \return a DomItem
     *
     * This function accesses a child DomItem corresponding to the index i.  If no DomItem exists corresponding to that index, it tries to create one from a QDomNode in the underlying QDomDocument structure.
     */
    DomItem *child(int i);
    DomItem *child(); //! Convenience function to access the first child DomItem.
    DomItem *parent(); //! Returns the parent DomItem
    QDomNode node() const; //! Returns the internal QDomNode that DomItem wraps.
    int row(); //! Returns the row this DomItem is mapped to. (e.g. the index corresponding to this DomItem in the parent)

private:
    QDomNode domNode;
    QHash<int,DomItem*> childItems; //! This contains the child DomItems and maintains a persistent mapping of index to DomItem, even when contents are changed.
    DomItem *parentItem;
    int rowNumber;
};
#endif // DOMITEM_H
