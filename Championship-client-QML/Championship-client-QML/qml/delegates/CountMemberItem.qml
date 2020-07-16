import QtQuick 2.0

Component {
    Rectangle {
        id: countMemberListMainRectangle
        width: countMembersListView.width - main.dp(20)
        height: countMembersListView.height / 6
        anchors {
            left: parent.left
            right: parent.right
        }

        color: "transparent"


        Rectangle {
            id: oneComponentFromCountMemberList
            anchors {
                fill: parent

                leftMargin: main.dp(20)
                rightMargin: main.dp(20)
                topMargin: main.dp(10)
                bottomMargin: main.dp(10)

                horizontalCenter: parent.horizontalCenter
            }

            radius: main.dp(5)
            border.width: main.dp(2)
            border.color: "#F29F05"

            color: !countMemberItemMouseArea.pressed ? "white" : "orange"
            scale: !countMemberItemMouseArea.pressed ? 1 : 0.9

            Rectangle {
                id: pointIconRectangle
                width: main.dp(25)
                height: main.dp(25)
                anchors {
                    verticalCenter: oneComponentFromCountMemberList.verticalCenter
                    left: oneComponentFromCountMemberList.left
                    leftMargin: main.dp(-10)
                }
                color: !countMemberItemMouseArea.pressed ? "white" : "transparent"

                Image {
                    id: pointIcon
                    anchors.fill: pointIconRectangle
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                    source: !countMemberItemMouseArea.pressed ? "qrc:/images/pointorange2.png" : "qrc:/images/pointorangeclicked.png"
                    scale: !countMemberItemMouseArea.pressed ? 1 : 0.9
                }
            }

            Text {
                id: itemText
                text: qsTr("Number of members: ") + val
                anchors.centerIn: oneComponentFromCountMemberList
                wrapMode: Text.WordWrap
                font.bold: true
                color: !countMemberItemMouseArea.pressed ? "orange" : "white"
                minimumPointSize: 10
                font.pointSize: 14

            }

            MouseArea {
                 id: countMemberItemMouseArea
                 anchors.fill: parent

                 onClicked: {
                     main.numberOfMembersSelected(val)
                     clickSound.play()

                 }
            }
        }
    }

}
