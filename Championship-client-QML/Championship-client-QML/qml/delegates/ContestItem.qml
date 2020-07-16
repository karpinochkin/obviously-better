import QtQuick 2.12
import QtGraphicalEffects 1.0

import "qrc:/qml/styles"

Component {
    Rectangle {
        id: oneButtomFromMenu
        width: contestsGridView.cellWidth - main.dp(15)
        height: contestsGridView.cellHeight - main.dp(15)

        color: !buttonCoffieArea.pressed ? "white" : Qt.darker("white")
        radius: main.dp(10)
        scale: !buttonCoffieArea.pressed ? 1 : 0.9

        Image {
            id: imageContest
            anchors.centerIn: parent
            width: oneButtomFromMenu.width + main.dp(1)
            height: oneButtomFromMenu.height + main.dp(1)
            source: "image://contests/" + id
            smooth: true
            fillMode: Image.PreserveAspectCrop
        }
        GaussianBlur {
            anchors.fill: imageContest
            source: imageContest
            radius: 10
            samples: 16
        }

        Rectangle {
            id: viewRectangle
            width: imageContest.width
            height: imageContest.height / 10
            anchors.top: imageContest.top
            anchors.left: imageContest.left
            anchors.leftMargin: main.dp(5)
            anchors.topMargin: main.dp(5)
            anchors.horizontalCenter: imageNameText.horizontalCenter
            color: Qt.rgba(0, 0, 0, 0)

            Image {
                id: viewIcon
                width: viewRectangle.width / 10
                height: viewRectangle.height
                anchors.left: viewRectangle.left
                anchors.topMargin: main.dp(10)
                anchors.alignWhenCentered: left
                source: "qrc:/images/view.png"
                smooth: true
                fillMode: Image.PreserveAspectFit
            }

            Text {
                id: viewText
                width: viewRectangle.width - main.dp(10)
                height: viewRectangle.height
                //                anchors.centerIn: viewRectangle
                anchors.left: viewIcon.right
                anchors.leftMargin: main.dp(5)
                anchors.horizontalCenter: viewIcon.horizontalCenter
                text: countPlay
                verticalAlignment: Text.AlignVCenter
                color: "white"
                minimumPointSize: 8
                font.pointSize: 12
            }


        }

        ImageNameText{
            id: imageNameText
            width: imageContest.width - main.dp(10)
            height: imageContest.height / 5
            anchors.centerIn: imageContest
            text: name
            verticalAlignment: Text.AlignVCenter
            color: "white"
        }


        ImageDescriptionText{
            text: description
            width: imageContest.width
            height: imageContest.height / 5
            anchors.top: imageNameText.bottom
            anchors.topMargin: main.dp(5)
            anchors.horizontalCenter: imageNameText.horizontalCenter
            color: "white"
        }

        MouseArea {
            id: buttonCoffieArea
            anchors.fill: parent

            onClicked: {
                clickSound.play()
                selectAnim.start()
                main.prepareToOpenCountMembersWindow(index, id, false)
            }
            onPressed: {
            }

            onReleased: selectAnim.stop()
        }
        PropertyAnimation { id: selectAnim; target: oneButtomFromMenu; properties: "scale"; easing.type: Easing.OutBack; easing.amplitude: 3.0; easing.period: 1.5; from: 0; to: 1; duration: 400 }
    }
}
