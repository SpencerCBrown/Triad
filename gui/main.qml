import QtQuick 2.7
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Triad")
    id: root

    RowLayout {
        id: layout
        spacing: 0
        anchors.fill: parent

        NoteBrowser {
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: parent.height / 3
        }

        NotePage {
            id: notepage
            focus: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.preferredWidth: (parent.width / 3) * 2
        }
    }
    onClosing: {
        notepage.saveDoc();
    }
}
