import QtQuick 2.0
import QtQml.Models 2.2

FocusScope {
    id: root
    property alias notemodel: delegate.model
    clip: true
    signal modelSelectionIndexChanged(int newIndex)
    signal modelSelectionDepthChanged(int newDepth)
    // These properties could eventually save themselves to disk, so as to have a non-default selection upon application start.
    property var mSelectedIndex: 0
    property var mSelectedDepth: 0

    VisualDataModel {
        id: delegate
        rootIndex: modelIndex(mSelectedDepth)
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
        highlightFollowsCurrentItem: true
        currentIndex: mSelectedIndex
        Component.onCompleted: {
            modelSelectionDepthChanged(mSelectedDepth)
            modelSelectionIndexChanged(mSelectedIndex)
        }

        MouseArea {
            id: focusarea
            anchors.fill: parent
            onClicked: {
                mSelectedIndex = list.indexAt(mouse.x, mouse.y)
                modelSelectionIndexChanged(mSelectedIndex)
            }
            onDoubleClicked: {
                if (mSelectedDepth < 2) {
                    mSelectedDepth = mSelectedDepth + 1
                    modelSelectionDepthChanged(mSelectedDepth)
                }
            }
        }
    }
}
