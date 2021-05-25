import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import QTherion 1.0

Popup {
    id: root
    ColumnLayout {
        id: col
        TabBar {
            id: tabs
            Layout.fillWidth: true
            TabButton {
                text: "Project"
                width: implicitWidth
            }
        }
        StackLayout {
            id: stack
            Layout.fillWidth: true
            Layout.fillHeight: true
            currentIndex: tabs.currentIndex

            Flickable {
                id: projectFlickable
                contentWidth: grid.width
                contentHeight: grid.height
                GridLayout {
                    id: grid
                    width: projectFlickable.width
                    columns: 2

                    Label {
                        text: "Canvas width"
                    }
                    SpinBox {
                        from: 0
                        to: 10000
                        editable: true
                        value: QTherion.canvasWidth
                        onValueChanged: QTherion.canvasWidth = value
                    }
                    Label {
                        text: "Canvas height"
                    }
                    SpinBox {
                        from: 0
                        to: 10000
                        editable: true
                        value: QTherion.canvasHeight
                        onValueChanged: QTherion.canvasHeight = value
                    }
                }
            }
        }
    }
}
