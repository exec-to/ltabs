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
            anchors.fill: parent
            anchors.margins: 1

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: {
                    root.model.selectItem(index);
                }

                onEntered: {
//                    if (mouse.button == Qt.RightButton) {
//                                     parent.color = 'yellow';
//                    }
//                    else {
//                        parent.color = 'green';
//                    }
                       parent.color = 'grey';

                }

                onExited: {
                        parent.color = 'steelblue';
                }

            }
        }
    }
}
