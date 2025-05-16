import QtQuick 2.15

Rectangle
{
    anchors.margins: CONFIG.margins
    radius: CONFIG.radius
    color: "black"
    opacity: 0.3
    height: parent.height / 10
    width: height
    property alias source: theImage.source
    signal clicked;
    Image
    {
        id: theImage
        anchors.fill: parent
        anchors.margins: CONFIG.margins
    }
    MouseArea
    {
        anchors.fill: parent
        onClicked: parent.clicked()
    }

}
