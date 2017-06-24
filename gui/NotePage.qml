import QtQuick 2.0
import QtQuick.Controls 2.1
import net.spencer.storage 1.0

import "create_text_edit.js" as TEFactory
import "manipulate.js" as MEObject

Page {
    id: root
    property point selectedContainerOrigin;

    header: ToolBar {
        id: toolbar

        Row {
            ToolButton {
                id: boldButton
                text: "\uE800"
                font.family: "fontello"
                onClicked: MEObject.boldSelectedText(centralSurface.contentItem.childAt(selectedContainerOrigin.x, selectedContainerOrigin.y));
            }

            ToolButton {
                id: italicButton
                text: "\uE801"
                font.family: "fontello"
                onClicked: MEObject.italicizeSelectedText(centralSurface.contentItem.childAt(selectedContainerOrigin.x, selectedContainerOrigin.y));
            }
        }
    }

    Flickable {
        id: centralSurface
        anchors.fill: parent
        contentWidth: Math.max(contentItem.childrenRect.width, width)
        contentHeight: Math.max(contentItem.childrenRect.height, height - toolbar.height)

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var contentContainer = TEFactory.createTextEdit(mouse, centralSurface.contentItem, root, selectedContainerOrigin, access.createNode());
                selectedContainerOrigin = Qt.point(contentContainer.x, contentContainer.y);
                contentContainer.changedSelectedContainer.connect(changeSelectedOrigin);
            }
            id: inputArea
            z: -1
        }

        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar {}
    }

    StorageInterface {
        id: access
    }

    function changeSelectedOrigin(xpos, ypos) {
        selectedContainerOrigin = Qt.point(xpos, ypos);
    }
    function saveDoc() {
        access.saveDoc();
    }
}
