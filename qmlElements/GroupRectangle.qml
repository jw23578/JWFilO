import QtQuick 2.15

Rectangle
{
    property bool selected: false
    anchors.margins: CONFIG.margins
    color: COLORS.groupBackground
    border.color: selected ? COLORS.selectedBorder : COLORS.groupBorder
    border.width: selected ? 2 : 1
    radius: CONFIG.radius
}
