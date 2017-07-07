function boldSelectedText(container) {
    container.content.font.bold = !container.content.font.bold
}
function italicizeSelectedText(container) {
    container.content.font.italic = !container.content.font.italic
}
function insertImage(container, srcString) {
    container.content.insert(container.content.cursorPosition, srcString);
}
function underlineSelectedText(container) {
    container.content.font.underline = !container.content.font.underline
}
