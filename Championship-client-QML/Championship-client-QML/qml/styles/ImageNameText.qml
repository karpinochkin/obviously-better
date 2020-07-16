import QtQuick 2.12

import QtGraphicalEffects 1.0
Text {
    property int size: 20

    anchors{
        margins: main.dp(5)
    }

    horizontalAlignment: Text.AlignHCenter

    font.bold: true
    color: "orange"
    layer.enabled: true
            layer.effect: DropShadow {
                verticalOffset: 2
                color: "#80000000"
                radius: 1
                samples: 3
            }

    fontSizeMode: Text.HorizontalFit
    minimumPointSize: 12
    font.pointSize: size
}
