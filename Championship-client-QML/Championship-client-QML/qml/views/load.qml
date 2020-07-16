import QtQuick 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4

Rectangle {
    id: loadScreen
    anchors.fill: parent
    color: Qt.rgba(0, 0, 0, 1)

    BusyIndicator {
        id: loadIndicator
        anchors.bottom: parent.bottom
        height: main.dp(100)
        anchors.horizontalCenter: logo.horizontalCenter
        running: true
    }

    Image {
        id: logo
        source: "qrc:/images/logo.png"
        width: parent.width - main.dp(100)
        height: parent.height - main.dp(200)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.centerIn: parent
        fillMode: Image.PreserveAspectFit
        smooth: true
    }


}
