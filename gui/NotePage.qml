import QtQuick 2.0
import QtQuick.Controls 2.1
//import org.kde.kirigami 2.0 as Kirigami

//This can be replaced after the UI prototyping is complete
import "create_text_edit.js" as TEFactory
import "manipulate.js" as MEObject

Page {
    id: root
    property var activeContentContainer;

    header: ToolBar {
        id: toolbar

        ToolButton {
            id: boldButton
            onClicked: MEObject.boldSelectedText(activeContentContainer)
        }
    }

    Flickable {
        id: centralSurface
        anchors.fill: parent
        contentWidth: Math.max(contentItem.childrenRect.width, width)
        contentHeight: Math.max(contentItem.childrenRect.height, height - toolbar.height)//minus toolbar.height?  why?

        MouseArea {
            anchors.fill: parent
            id: inputArea
            onClicked: activeContentContainer = TEFactory.createTextEdit(mouse, centralSurface.contentItem, root)
            z: -1
        }

        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar {}
    }
}
