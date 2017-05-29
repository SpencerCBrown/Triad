import QtQuick 2.0
import QtQuick.Controls 2.1

import "create_text_edit.js" as TEFactory
import "manipulate.js" as MEObject

Page {
    id: root
    property point selectedContainerOrigin;

    header: ToolBar {
        id: toolbar

        ToolButton {
            id: boldButton
            font.family: "fontello"
            text: "\uE800"
            onClicked: MEObject.boldSelectedText(centralSurface.contentItem.childAt(selectedContainerOrigin.x, selectedContainerOrigin.y))
        }
    }

    function changeSelectedOrigin(xpos, ypos) {
        selectedContainerOrigin = Qt.point(xpos, ypos);
    }

    Flickable {
        id: centralSurface
        anchors.fill: parent
        contentWidth: Math.max(contentItem.childrenRect.width, width)
        contentHeight: Math.max(contentItem.childrenRect.height, height - toolbar.height)

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var contentContainer = TEFactory.createTextEdit(mouse, centralSurface.contentItem, root, selectedContainerOrigin);
                selectedContainerOrigin = Qt.point(contentContainer.x, contentContainer.y);
                contentContainer.changedSelectedContainer.connect(changeSelectedOrigin);
            }
            id: inputArea
            z: -1
        }

        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar {}
    }
}
