import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""
    property string textColorStyle: ""
    border.color: "slategray"
    border.width: 1

    Text {
        id: _firstText

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.fill: parent
        anchors.margins: 5
        text: root.displayText
        clip: true
        color: root.textColorStyle
        font.pointSize: 14
        font {
            family: "Courier"
//            bold: true
        }
    }
}



