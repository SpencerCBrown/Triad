import QtQuick 2.0
import QtQml.Models 2.2

FocusScope {
    id: root
    property alias notemodel: delegate.model

    VisualDataModel {
        id: delegate
        rootIndex: modelIndex(0)
        delegate: Rectangle {
            height: 25
            width: 100
            Text { text: title}
        }
    }
    ListView {
        id: list
        anchors.fill: parent
        model: delegate
    }
}
