function boldSelectedText(children, id) {
    for (var i = 0; i < children.length; i++) {
        var container = children[i];
        if (container.containerID === id) {
            container.content.font.bold = !container.content.font.bold
            break;
        }
    }
}
function italicizeSelectedText(children, id) {
    for (var i = 0; i < children.length; i++) {
        var container = children[i];
        if (container.containerID === id) {
            container.content.font.italic = !container.content.font.italic
            break;
        }
    }
}
function insertImage(children, id, srcString) {
    for (var i = 0; i < children.length; i++) {
        var container = children[i];
        if (container.containerID === id) {
            container.content.insert(container.content.cursorPosition, srcString);
            break;
        }
    }
}
function underlineSelectedText(children, id) {
    for (var i = 0; i < children.length; i++) {
        var container = children[i];
        if (container.containerID === id) {
            container.content.font.underline = !container.content.font.underline
            break;
        }
    }
}
