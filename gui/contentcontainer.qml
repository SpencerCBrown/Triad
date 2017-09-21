import QtQuick 2.7
import QtQuick.Controls 2.1
import net.spencer.dochandle 1.0

FocusScope {
    id: rootScope
    x: borderControl.x
    y: borderControl.y
    width: borderControl.width
    height: borderControl.height

    property alias textFocus: textArea.focus
    property alias xmlNode: documentInstance.node
    property alias content: textArea
    property bool isImplicitlySized: true
    property bool containerIsFocused
    property bool createdByTouch: false
    property string containerID;
    property int textPadding: 9

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
        border.color: (rootScope.containerIsFocused && (textArea.length > 0)) ? "black" : "transparent"
        height: textArea.height
        width: textArea.width

        TextArea {
            id: textArea
            topPadding: textPadding
            focus: true
            textFormat: TextEdit.RichText
            renderType: TextEdit.NativeRendering
            font.pointSize: 11
            font.family: "calibri"
            wrapMode: isImplicitlySized ? TextEdit.NoWrap : TextEdit.Wrap
            width: isImplicitlySized ? (contentWidth + leftPadding + rightPadding) : explicitWidth
            height: isImplicitlySized ? (contentHeight + topPadding + bottomPadding) : explicitHeight
            property int explicitHeight //^^^
            cursorPosition: length
            property int explicitWidth //need to handle padding issues
            onEditingFinished: {
                if (length == 0 && !containerIsFocused) { //does still return zero if images or tables, etc are displayed?
                    containerDeleted(containerID);
                    //rootScope.destroy();
                }
            }
        }
        Rectangle {
            id: handle
            height: textPadding
            color: "grey"
            border.color: "black"
            anchors.left: parent.left
            anchors.leftMargin: 0
            anchors.right: parent.right
            anchors.rightMargin: 0
            anchors.top: parent.top
            anchors.topMargin: 0
            visible: (rootScope.containerIsFocused && (textArea.length > 0))
        }
        Rectangle {
            id: cursorIndicator
            visible: (rootScope.containerIsFocused && (textArea.length <= 0) && rootScope.createdByTouch)
            x: textArea.cursorRectangle.x - (width / 2)
            y: textArea.cursorRectangle.y + textArea.cursorRectangle.height
            width: textArea.cursorRectangle.height
            height: textArea.cursorRectangle.height
            radius: textArea.cursorRectangle.height / 2
            border.width: 3
            color: "white"
        }
    }
    MouseArea {
        id: dragArea
        anchors.fill: parent
        drag.target: parent
        onClicked: {
            rootScope.focus = true
            rootScope.containerFocused(rootScope.containerID)
            textArea.cursorPosition = textArea.positionAt(mouse.x, mouse.y)
        }
    }
}
