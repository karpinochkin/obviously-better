import QtQuick 2.0

Component {
    Rectangle {
        id: ratingItemRactangle
        width: ratingViewRectangle.width - main.dp(20)
        height: ratingViewRectangle.height / 6
        anchors {
            left: parent.left
            right: parent.right
        }

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

            color: Qt.rgba(0,0,0,0.05)

            radius: main.dp(5)
            border.width: main.dp(2)
            border.color: "#F29F05"

            Image {
                id: ratingMemberImage
                width: oneComponentFromCountMemberList.width / 6
                height: oneComponentFromCountMemberList.height / 1.2
                anchors {
                    verticalCenter: oneComponentFromCountMemberList.verticalCenter
                    left: oneComponentFromCountMemberList.left
                    leftMargin: main.dp(10)
                }
                source: "image://members/" + idMember
                smooth: true
                fillMode: Image.PreserveAspectCrop
            }

            Text {
                id: ratingMemberName
                text: nameMember
                width: oneComponentFromCountMemberList.width - ratingMemberImage.width * 2 - main.dp(20)
                height: main.dp(18)
                horizontalAlignment: Text.AlignHCenter

                elide: Text.ElideMiddle
                anchors {
                    top: ratingMemberImage.top
                    horizontalCenter: oneComponentFromCountMemberList.horizontalCenter
                }

                font.bold: true
                color: "orange"
                minimumPointSize: 12
                font.pointSize: 18
            }

            Text {
                id: ratingMemberPoint
                text: qsTr("Points : ") + points.toPrecision(2);
                horizontalAlignment: Text.AlignHCenter

                wrapMode: Text.WordWrap
                anchors {
                    top: ratingMemberName.bottom
                    topMargin: main.dp(10)
                    horizontalCenter: oneComponentFromCountMemberList.horizontalCenter
                }
                font.bold: true
                color: "orange"
                opacity: 0.7
                minimumPointSize: 10
                font.pointSize: 12
            }

            Text {
                id: ratingMemberNumber
                text: qsTr("#") + number
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: main.dp(10)
                }

                font.bold: true
                color: "orange"
                minimumPointSize: 12
                font.pointSize: 18


            }
        }
    }
}
