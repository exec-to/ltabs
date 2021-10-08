import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""

    color: "steelblue"

    border.color: "black"
    border.width: 1



    Text {
        id: _firstText

        anchors.verticalCenter: parent.verticalCenter
        anchors.left: parent.left
        anchors.fill: parent
        anchors.margins: 5
        text: root.displayText
        clip: true
        font.pointSize: 12
        font {
            bold: false
        }

    }
}




