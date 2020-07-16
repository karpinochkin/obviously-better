import QtQuick 2.12

import QtGraphicalEffects 1.0
Text {
    property int size: 13

    anchors{
        margins: main.dp(15)
    }

    horizontalAlignment: Text.AlignHCenter
    wrapMode: Text.WordWrap

    font.bold: true
    color: "orange"
    opacity: 0.7

    fontSizeMode: Text.HorizontalFit
    minimumPointSize: 10
    font.pointSize: size
}
