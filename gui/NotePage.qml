import QtQuick 2.1
import QtQuick.Controls 2.1
import Qt.labs.platform 1.0
import net.spencer.storage 1.0
import net.spencer.image 1.0

import "create_text_edit.js" as TEFactory
import "manipulate.js" as MEObject

Page {
    id: root
    property string currentContainerID
    property int containerGenerationCounter: 0
    property var selectedContainer: 0

    header: ToolBar {
        id: toolbar

        Row {
            ToolButton {
                id: boldButton
                text: "\uE801"
                font.family: "fontello"
                onClicked: MEObject.boldSelectedText(selectedContainer);
            }

            ToolButton {
                id: italicButton
                text: "\uE802"
                font.family: "fontello"
                onClicked: MEObject.italicizeSelectedText(selectedContainer);
            }
            ToolButton {
                id: underlineTextButton
                text: "\uf0cd"
                font.family: "fontello"
                onClicked: MEObject.underlineSelectedText(selectedContainer);
            }
            ToolButton {
                id: imageInsertButton
                text: "\uE800"
                font.family: "fontello"
                onClicked:
                    imageSelectionDialog.open();
                ImageToString64 {
                    id: imageUriGen
                }
                FileDialog {
                    id: imageSelectionDialog
                    folder: StandardPaths.writableLocation(StandardPaths.PicturesLocation)
                    onAccepted: {
                        var formattedSrcString = imageUriGen.gen(imageSelectionDialog.file.toString());
                        MEObject.insertImage(selectedContainer, formattedSrcString);
                    }
                }
            }
        }
    }

    Flickable {
        id: centralSurface
        anchors.fill: parent
        contentWidth: Math.max(contentItem.childrenRect.width, width)
        contentHeight: Math.max(contentItem.childrenRect.height, height - toolbar.height)
        clip: true

        MouseArea {
            anchors.fill: parent
            onClicked: {
                var contentContainer = TEFactory.createTextEdit(mouse, centralSurface.contentItem, access.createNode(), containerGenerationCounter);
                if (mouse.source !== Qt.MouseEventNotSynthesized) {
                    contentContainer.createdByTouch = true;
                }
                contentContainer.containerFocused.connect(containerFocusChanged);
                contentContainer.containerDeleted.connect(containerDeleted);
                containerFocusChanged(containerGenerationCounter);
                containerGenerationCounter++;
            }
            id: inputArea
            z: -1
        }

        ScrollBar.horizontal: ScrollBar {}
        ScrollBar.vertical: ScrollBar {}
    }

    StorageInterface {
        id: access
        Component.onCompleted: finishLoading();
        onContainersLoaded: {
            while (numberOfLoadedElements > 0) {
                var contentContainer = TEFactory.loadTextEdit(centralSurface.contentItem, topXPos(), topYPos(), topContents(), popElement(), containerGenerationCounter);
                contentContainer.containerFocused.connect(containerFocusChanged);
                contentContainer.containerDeleted.connect(containerDeleted);
                containerGenerationCounter++;
                numberOfLoadedElements--;
            }
        }
    }

    function containerFocusChanged(containerID) {
        var children = centralSurface.contentItem.children;
        for (var i = 0; i < children.length; i++) {
            var container = children[i];
            if (container.containerID === containerID) {
                break;//final value of container is the focused child
            }
        }
        if (selectedContainer !== 0) {
            selectedContainer.containerIsFocused = false;
        }
        container.containerIsFocused = true;
        selectedContainer = container;
    }
    function containerDeleted(containerID) {
        var list = centralSurface.contentItem.children;
        for (var i = 0; i < list.length; i++) {
            if (list[i].containerID === containerID) {
                access.purgeElement(list[i].xmlNode);
                list[i].destroy();
            }
        }
    }

    function saveDoc() {
        access.saveDoc();
    }
}
