import QtQuick 2.0

Rectangle {
    id: root

    property string displayText: ""
//    alias nore recommended
//    readonly property alias internalText: _firstText

    color: "steelblue"

    border.color: "black"
    border.width: 1

    Text {
        id: _firstText
        anchors.centerIn: root
        text: root.displayText
        font.pointSize: 16
        font {
            bold: true
        }
    }
}




