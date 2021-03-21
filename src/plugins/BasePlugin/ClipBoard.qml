import QtQuick 2.0
import ClipboardModel 1.0

ListView {
    id: root
    orientation: ListView.Vertical
    anchors.fill: parent
    model: ClipboardModel {

    }

    delegate: Item {
        id: _backgroundDelegate
        width: root.width
        height: 100
        ClipboardItem {
            displayText: display
    //        displayText: index
    //        internalText.text: display
            anchors.fill: parent
            anchors.margins: 1

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    root.model.selectItem(index);
                }
            }
        }
    }
}
