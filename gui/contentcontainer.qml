import QtQuick 2.7
import QtQuick.Controls 2.1
import net.spencer.dochandle 1.0

FocusScope {
    id: rootScope
    property alias textFocus: textArea.focus
    property alias xmlNode: documentInstance.node
    x: borderControl.x
    y: borderControl.y
    width: borderControl.width
    height: borderControl.height
    property bool isImplicitlySized: true
    property bool containerIsFocused;
    property string containerID;
    property alias content: textArea
    signal containerFocused(string ID);
    signal containerDeleted(string ID);

    Drag.active: dragArea.drag.active
    Drag.hotSpot.x: 10
    Drag.hotSpot.y: 10

    DocumentHandler {
        id: documentInstance
        textDocument: textArea.textDocument
        xpos: rootScope.x
        ypos: rootScope.y
    }

    Rectangle {
        id: borderControl
        color: "transparent"
        border.color: rootScope.containerIsFocused ? "black" : "transparent"
        height: textArea.height
        width: textArea.width

        TextArea {
            id: textArea
            anchors.topMargin: 10
            focus: true
            textFormat: TextEdit.RichText
            wrapMode: isImplicitlySized ? TextEdit.NoWrap : TextEdit.Wrap
            width: isImplicitlySized ? (contentWidth + leftPadding + rightPadding) : explicitWidth
            height: isImplicitlySized ? (contentHeight + topPadding + bottomPadding) : explicitHeight
            cursorPosition: length
            property int explicitWidth //need to handle padding issues
            property int explicitHeight //^^^
            onEditingFinished: {
                if (length == 0 && !containerIsFocused) { //does still return zero if images or tables, etc are displayed?
                    containerDeleted(containerID);
                    //rootScope.destroy();
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
            visible: rootScope.containerIsFocused
        }
    }
    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
        onClicked: {
            rootScope.focus = true
            rootScope.containerFocused(rootScope.containerID)
        }
    }
}
