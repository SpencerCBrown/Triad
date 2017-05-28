function createTextEdit(event, parent, container) {
        var xpos = event.x
        var ypos = event.y
        if (xpos < 100 && ypos < 50) {
            xpos = 0
            ypos = 0
        }

        if (parent.childAt(xpos, ypos) === inputArea) {
            var component = Qt.createComponent("contentcontainer.qml")
            var componentInstance = component.createObject(parent, {"x": xpos, "y": ypos, "focus": true})
            return componentInstance
        }
    }
