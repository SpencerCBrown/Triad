import QtQuick 2.0
import QtQuick.Controls 2.1

//This can be replaced after the UI prototyping is complete
import "create_text_edit.js" as TEFactory

Page {
    header: ToolBar {}

    Flickable {
        id: centralSurface
        anchors.fill: parent
        contentWidth: Math.max(contentItem.childrenRect.width, width)
        contentHeight: Math.max(contentItem.childrenRect.height, height)

        MouseArea {
            anchors.fill: parent
            id: inputArea
            onClicked: TEFactory.createTextEdit(mouse, centralSurface.contentItem)
            z: -1
        }

        ScrollBar.horizontal: ScrollBar {active: true}
        ScrollBar.vertical: ScrollBar {}
    }
}
