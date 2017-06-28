function boldSelectedText(contentContainer) {
    if (contentContainer !== null) {
        contentContainer.content.font.bold = !contentContainer.content.font.bold
    }
}
function italicizeSelectedText(contentContainer) {
    if (contentContainer !== null) {
        contentContainer.content.font.italic = !contentContainer.content.font.italic
    }
}
function insertImage(contentContainer, srcString) {
    if (contentContainer !== null) {
        contentContainer.content.insert(contentContainer.content.cursorPosition, srcString);
        //contentContainer.content.insert(contentContainer.content.cursorPosition, "<img alt=\"Embedded Image\" src=\"data:image/jpg;base64," + imageB64 + "\" />");
    }
}
