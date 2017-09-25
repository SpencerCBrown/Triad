import QtQuick 2.0
import QtQml.Models 2.2

FocusScope {
    id: root
    property alias notemodel: delegate.model
    clip: true
    signal modelSelectionChanged(int newIndex)
    property var mIndex: delegate.rootIndex

    VisualDataModel {
        id: delegate
        rootIndex: modelIndex(0)
        delegate: Rectangle {
            id: drect
            height: 25
            width: parent.width
            Text {
                text: title
            }
        }
    }
    ListView {
        id: list
        anchors.fill: parent
        model: delegate
        currentIndex: 1
        highlightFollowsCurrentItem: true
        MouseArea {
            id: focusarea
            anchors.fill: parent
            onClicked: {
                list.currentIndex = list.indexAt(mouse.x, mouse.y)
                modelSelectionChanged(list.currentIndex)
            }
        }
    }
}
