import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.0

//This can be replaced after the UI prototyping is complete
import "create_text_edit.js" as TEFactory

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("StaunchNotes")
    id: root

    header: ToolBar {
        /*RowLayout {
            anchors.fill: parent
            ToolButton {

            }
            Label {

            }
            ToolButton {

            }
        }*/
    }

    Flickable {
        anchors.fill: parent
        id: centralSurface
        contentWidth: Math.max(contentItem.childrenRect.width, implicitWidth)
        contentHeight: Math.max(contentItem.childrenRect.height, implicitHeight)
        implicitHeight: 640
        implicitWidth: 800

        MouseArea {
            anchors.fill: parent
            id: inputArea
            onClicked: TEFactory.createTextEdit(mouse, centralSurface.contentItem)
            z: -1
        }

        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar{}
    }
}
