import QtQuick 2.0
import ClipboardModel 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.12

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

            Popup {
                id: contextMenu
                x: 50
                y: 50
                width: 150
                height: 134
                modal: true
                focus: true
                closePolicy: Popup.CloseOnEscape | Popup.CloseOnPressOutsideParent

                Column {
                            anchors.centerIn: parent
                            spacing: 1
                            Button {
                                id: but_pin
                                width: 148
                                anchors.left: contextMenu.left
                                text: "Закрепить"
                                highlighted: contextMenu.index === 0 ? true : false
                                onClicked: {
                                    //root.model.pin_to pin_array(index);
                                    contextMenu.close()
                                    contextMenu.index = 0
                                }
                            }
                            Button {
                                id: but_del
                                width: 148
                                text: "Удалить"
                                highlighted: contextMenu.index === 1 ? true : false
                                onClicked: {
                                    contextMenu.index = 1
                                }
                            }
                            Button {
                                id: but_ssh
                                width: 148
                                text: "SSH ROOT"
                                highlighted: contextMenu.index === 2 ? true : false
                                onClicked: {
                                    contextMenu.index = 2
                                }
                            }

                            Button {
                                id: but_open
                                width: 148
                                text: "Открыть в браузере"
                                highlighted: contextMenu.index === 2 ? true : false
                                onClicked: {
                                    contextMenu.index = 3
                                }
                            }

                            Button {
                                id: but_host
                                width: 148
                                text: "Получить host"
                                highlighted: contextMenu.index === 2 ? true : false
                                onClicked: {
                                    contextMenu.index = 4
                                }
                            }
                }
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.LeftButton | Qt.RightButton
                onClicked: {
                    if (mouse.button === Qt.RightButton) {
                        contextMenu.open()
                    }
                    else if (mouse.button === Qt.LeftButton) {
                        root.model.selectItem(index);
                    }
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
