import QtQuick
import "qmlElements"

Window {
    width: 1000
    height: 480
    visible: true
    visibility: "FullScreen"
    color: COLORS.background
    GroupRectangle
    {
        id: headLine
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        height: totalFileCount.contentHeight + 2 * CONFIG.margins
        FILOText
        {
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: parent.left
            anchors.margins: CONFIG.margins
            id: totalFileCount
            text: "FileCount: " + FILO.totalFileCount
        }
    }


    ListView
    {
        id: theTypeList
        anchors.left: parent.left
        anchors.top: headLine.bottom
        anchors.bottom: parent.bottom
        anchors.margins: CONFIG.margins
        width: 200
        model: FILO.typeModel
        spacing: 1
        highlight: Rectangle
        {
            color: COLORS.selectedContainer
            radius: CONFIG.radius
            width: theTypeList.width
            height: 100
        }
        delegate: GroupRectangle
        {
            selected: index == theTypeList.currentIndex
            color: "transparent"
            width: theTypeList.width
            height: 100
            FILOText
            {
                anchors.centerIn: parent
                text: type.id + ": " + type.count + " " + index + " " + theTypeList.currentIndex
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    theTypeList.currentIndex = index
                    FILO.typeClicked(type.id)
                }
            }
        }
    }
    ListView
    {
        id: theSuffixList
        anchors.left: theTypeList.right
        anchors.top: headLine.bottom
        anchors.bottom: parent.bottom
        anchors.margins: CONFIG.margins
        width: 200
        model: FILO.suffixModel
        spacing: 1
        highlight: Rectangle
        {
            color: COLORS.selectedContainer
            radius: CONFIG.radius
            width: theSuffixList.width
            height: 100
        }
        delegate: GroupRectangle
        {
            width: theSuffixList.width
            height: 100
            selected: index == theSuffixList.currentIndex
            color: "transparent"
            FILOText
            {
                anchors.centerIn: parent
                text: suffix.id + ": " + suffix.count
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    theSuffixList.currentIndex = index
                    FILO.suffixClicked(suffix.id)
                }
            }
        }
    }
    GroupRectangle
    {
        id: theCurrentFile
        anchors.right: parent.right
        anchors.top: headLine.bottom
        anchors.bottom: parent.bottom
        width: parent.width / 5
        Column
        {
            anchors.horizontalCenter: parent.horizontalCenter
            width: parent.width - CONFIG.margins * 2
            FILOText
            {
                text: FILO.theCurrentFile.fileNameWithoutExtension
            }
            FILOText
            {
                text: FILO.theCurrentFile.relativePath
            }
            FILOText
            {
                text: FILO.theCurrentFile.created
            }
            FILOText
            {
                text: FILO.theCurrentFile.changed
            }
            Image
            {
                width: parent.width
                height: width
                source: "file:" + FILO.theCurrentFile.id
                fillMode: Image.PreserveAspectFit
                autoTransform: true
                mipmap: true
                MouseArea
                {
                    anchors.fill: parent
                    onClicked: fullSizeImage.source = parent.source
                }
            }
        }
    }

    GroupRectangle
    {
        id: theGridViewrectangle
        anchors.left: theSuffixList.right
        anchors.right: theCurrentFile.left
        anchors.top: headLine.bottom
        anchors.bottom: parent.bottom
        GridView
        {
            id: theFileList
            anchors.fill: parent
            anchors.margins: CONFIG.margins
            clip: true
            model: FILO.fileModel
            focus: true
            cellHeight: 150
            onCurrentItemChanged:
            {
                FILO.theCurrentFile = currentItem.theFile
            }

            highlight: Rectangle
            {
                color: COLORS.selectedContainer
                radius: CONFIG.radius
                width: theFileList.cellWidth
                height: theFileList.cellHeight
            }
            delegate: Item
            {
                width: theFileList.cellWidth
                height: theFileList.cellHeight
                property var theFile: file
                GroupRectangle
                {
                    anchors.fill: parent
                    color: "transparent"
                    selected: index == theFileList.currentIndex
                    property var theFile: file
                    Column
                    {
                        anchors.margins: CONFIG.margins
                        anchors.top: parent.top
                        anchors.left: parent.left
                        FILOText
                        {
                            color: index == 0 || FILO.ddMMOfDateTime(FILO.getByIndex(index - 1).changed) !== FILO.ddMMOfDateTime(file.changed) ?
                                       COLORS.textHighlight : COLORS.textSecondary
                            text: FILO.ddMMOfDateTime(file.changed)
                        }
                        FILOText
                        {
                            color: index == 0 || FILO.yearOfDateTime(FILO.getByIndex(index - 1).changed) !== FILO.yearOfDateTime(file.changed) ?
                                       COLORS.textHighlight : COLORS.textSecondary
                            text: FILO.yearOfDateTime(file.changed)
                        }
                    }

                    Image
                    {
                        id: theImage
                        asynchronous: true
                        anchors.bottom: parent.bottom
                        anchors.left: parent.left
                        anchors.right: parent.right
                        height: width
                        anchors.margins: CONFIG.margins
                        source: "file:" + file.id
                        fillMode: Image.PreserveAspectFit
                        autoTransform: true
                        mipmap: true
                    }
                    MouseArea
                    {
                        anchors.fill: parent
                        onClicked: theFileList.currentIndex = index
                        onDoubleClicked: fullSizeImage.source = theImage.source
                    }
                }
            }
        }
    }
    GroupRectangle
    {
        visible: fullSizeImage.source != ""
        anchors.fill: parent
        Image
        {
            id: fullSizeImage
            anchors.fill: parent
            anchors.margins: CONFIG.margins
            fillMode: Image.PreserveAspectFit
            autoTransform: true
            mipmap: true
        }
        MouseArea
        {
            anchors.fill: parent
            onClicked: fullSizeImage.source = ""
        }
        FILOSquareImageButton
        {
            visible: theFileList.currentIndex > 0
            anchors.left: parent.left
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/images/square-arrow-left-svgrepo-com.svg"
            onClicked:
            {
                theFileList.currentIndex = theFileList.currentIndex - 1
                fullSizeImage.source = "file:" + FILO.theCurrentFile.id
            }
            height: parent.height / 10
        }

        FILOSquareImageButton
        {
            visible: theFileList.currentIndex < theFileList.count - 1
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/images/square-arrow-right-svgrepo-com.svg"
            onClicked:
            {
                theFileList.currentIndex = theFileList.currentIndex + 1
                fullSizeImage.source = "file:" + FILO.theCurrentFile.id
            }
            height: parent.height / 10
        }

        FILOSquareImageButton
        {
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            source: "qrc:/images/copy-svgrepo-com.svg"
            onClicked: FILO.imageToClibboard(FILO.theCurrentFile.id)
            height: parent.height / 10
        }

    }
}
