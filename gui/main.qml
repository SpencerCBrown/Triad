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
            Layout.minimumWidth: 50
            Layout.preferredWidth: parent.height / 3
            Layout.maximumWidth: 300
            Layout.minimumHeight: 150
        }

        NotePage {
            id: notepage
            focus: true
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumWidth: 100
            Layout.preferredWidth: (parent.width / 3) * 2
        }
    }
    onClosing: {
        notepage.saveDoc();
    }
}
