import QtQuick 2.7
import QtQuick.Controls 2.1

FocusScope {
    id: root
    property alias textFocus: textArea.focus
    x: borderControl.x
    y: borderControl.y
    width: borderControl.width
    height: borderControl.height

    Rectangle {
        id: borderControl
        color: "transparent"
        border.color: "black"
        height: textArea.height
        width: textArea.width
        visible: root.activeFocus

        TextArea {
            id: textArea
            anchors.topMargin: 10
            implicitHeight: 40
            implicitWidth: 200
            focus: true
        }

        Rectangle {
            id: rectangle
            height: 10
            color: "grey"
            border.color: "black"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
        }
    }
}
