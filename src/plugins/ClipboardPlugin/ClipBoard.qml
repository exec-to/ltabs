import QtQuick 2.0
import ClipboardModel 1.0
import QtQuick.Window 2.2
import QtQuick.Controls 2.12


ListView {
    id: root
    orientation: ListView.Vertical
    anchors.fill: parent
    clip: true
    model: ClipboardModel {

    }

    Component {
        id: highlight
        Rectangle {
            width: root.width - 2
            height: root.height - 2
            color: "darkgray";
            y: root.currentItem.y
            Behavior on y { SpringAnimation { spring: 5; damping: 1; velocity: 10000 } }
        }
    }

    highlight: highlight
    highlightFollowsCurrentItem: true

    delegate: Item {
        width: root.width - 2
        height: 100

        ClipboardItem {
            id: currentItem
//            color: root.model.itemColor(index)
            color: "#323232"
            displayText: display ? display : ""
            textColorStyle: textcolor ? textcolor : "whitesmoke"
            anchors.fill: parent
            anchors.margins: 2


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
                                onClicked: {
                                    root.model.pinItem(index)
//                                    currentItem.color = root.model.itemColor(index)
                                    contextMenu.close()
                                }
                            }
                            Button {
                                id: but_del
                                width: 148
                                text: "Удалить"
                                onClicked: {
                                }
                            }
                            Button {
                                id: but_ssh
                                width: 148
                                text: "SSH ROOT"
                                onClicked: {
                                }
                            }

                            Button {
                                id: but_open
                                width: 148
                                text: "Открыть в браузере"
                                onClicked: {
                                }
                            }

                            Button {
                                id: but_host
                                width: 148
                                text: "Получить host"
                                onClicked: {
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
                        root.model.selectItem(index)
                        root.currentIndex = index
                        currentItem.color = root.model.itemColor(index)
                    }
                }

                onEntered: {
                       currentItem.color = 'slategray';
                }

                onExited: {
                        currentItem.color = root.model.itemColor(index)
                }

            }
        }
    }
}
