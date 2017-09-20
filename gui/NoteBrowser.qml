import QtQuick 2.0
import QtQml.Models 2.2

FocusScope {
    id: root
    property alias notemodel: delegate.model
    onFocusChanged: print("focus changed about notebrowser")

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
        focus: true
        MouseArea {
            id: focusarea
        }
    }
}
