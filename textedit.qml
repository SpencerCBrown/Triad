import QtQuick 2.7
import QtQuick.Controls 2.1

FocusScope {
    id: root
    property alias textFocus: textArea.focus
    x: borderControl.x
    y: borderControl.y
    width: borderControl.width
    height: borderControl.height
    property bool isImplicitlySized: true

    Rectangle {
        id: borderControl
        color: "transparent"
        border.color: root.activeFocus ? "black" : "transparent"
        height: textArea.height
        width: textArea.width

        TextArea {
            id: textArea
            anchors.topMargin: 10
            focus: true
            wrapMode: isImplicitlySized ? TextEdit.NoWrap : TextEdit.Wrap
            width: isImplicitlySized ? (contentWidth + leftPadding + rightPadding) : explicitWidth
            height: isImplicitlySized ? (contentHeight + topPadding + bottomPadding) : explicitHeight
            property int explicitWidth //need to handle padding issues
            property int explicitHeight //^^^
            onEditingFinished: {
                if (length == 0) { //does still return zero if images or tables, etc are displayed?
                    root.destroy()
                }
            }
        }
        Rectangle {
            id: handle
            height: 10
            color: "grey"
            border.color: "black"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            visible: root.activeFocus
        }
    }
}
