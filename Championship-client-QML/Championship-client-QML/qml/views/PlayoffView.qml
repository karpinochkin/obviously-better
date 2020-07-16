import QtQuick 2.12
import QtQuick.Dialogs 1.3
import QtGraphicalEffects 1.0

Rectangle {
    id: playoffViewRectangle
    anchors.fill: parent
    color: mainView.color

    Connections {
        target: middlewareQML

        onSignalNextPlayoffStage : {
            count = 0
            main.showStageText()
        }

        onSignalSendPlayoffPair : {
            firstMemberName.text = qmlProperty.firstMemberInPairName
            firstMemberDescription.text = qmlProperty.firstMemberInPairDecription
            secondMemberName.text = qmlProperty.secondMemberInPairName
            secondMemberDescription.text = qmlProperty.secondMemberInPairDecription
            middlewareQML.getMemberImageForQML(qmlProperty.firstMemberInPairID)
            middlewareQML.getMemberImageForQML(qmlProperty.secondMemberInPairID)

            count++
            main.setStageText(count)

        }

        onSignalMemberImageLoaded: {
            if (qmlProperty.firstMemberInPairID === qmlProperty.secondMemberInPairID) {
                firstMemberImage.source = "image://members/" + qmlProperty.firstMemberInPairID
                secondMemberImage.source = "image://members/" + qmlProperty.secondMemberInPairID
                return
            }

            if (qmlProperty.firstMemberInPairID === qmlProperty.idMemberImageLoaded) {
                firstMemberImage.source = "image://members/" + qmlProperty.firstMemberInPairID
                return
            }

            if (qmlProperty.secondMemberInPairID === qmlProperty.idMemberImageLoaded) {
                secondMemberImage.source = "image://members/" + qmlProperty.secondMemberInPairID
                return
            }

        }
    }

    Rectangle {
        id: firstMemberRectangle
        color: "transparent"
        width: playoffViewRectangle.width - main.dp(20)
        height: playoffViewRectangle.height / 2.2
        anchors {
            top: parent.top
            margins: main.dp(20)
            horizontalCenter: playoffViewRectangle.horizontalCenter
        }

        scale: !firstMemberMouseMember.pressed ? 1 : 0.9
        Image {
            id: firstMemberImage
            anchors.fill: firstMemberRectangle
            width: firstMemberRectangle.width + main.dp(1)
            height: firstMemberRectangle.height + main.dp(1)
            smooth: true
            fillMode: Image.PreserveAspectCrop
        }

        Text {
            id: firstMemberName
            anchors.centerIn: parent
            color: "white"
            font.bold: true
            layer.enabled: true
            layer.effect: DropShadow {
                verticalOffset: 2
                color: "#80000000"
                radius: 1
                samples: 3
            }

            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 12
            font.pointSize: 16
        }

        Text {
            id: firstMemberDescription
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: firstMemberName.bottom
            color: "white"
            font.bold: true
            opacity: 0.8
            layer.enabled: true
            layer.effect: DropShadow {
                verticalOffset: 2
                color: "#80000000"
                radius: 1
                samples: 3
            }

            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 10
            font.pointSize: 12
        }

        MouseArea {
            id:firstMemberMouseMember
            anchors.fill: parent

            onClicked: {
                nextPair(qmlProperty.secondMemberInPairID)
                clickSound.play()
            }

        }
    }

    Rectangle {
        id: secondMemberRectangle
        color: "transparent"
        width: playoffViewRectangle.width - main.dp(20)
        height: playoffViewRectangle.height / 2.2
        anchors {
            bottom: playoffViewRectangle.bottom
            margins: main.dp(20)
            horizontalCenter: playoffViewRectangle.horizontalCenter
        }
        scale: !secondMemberMouseMember.pressed ? 1 : 0.9

        Image {
            id: secondMemberImage
            anchors.fill: secondMemberRectangle
            width: secondMemberRectangle.width + main.dp(1)
            height: secondMemberRectangle.height + main.dp(1)
            smooth: true
            fillMode: Image.PreserveAspectCrop
        }

        Text {
            id: secondMemberName
            anchors.centerIn: parent
            color: "white"
            font.bold: true
            layer.enabled: true
            layer.effect: DropShadow {
                verticalOffset: 2
                color: "#80000000"
                radius: 1
                samples: 3
            }

            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 12
            font.pointSize: 16
        }

        Text {
            id: secondMemberDescription
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.top: secondMemberName.bottom
            color: "white"
            font.bold: true
            opacity: 0.8
            layer.enabled: true
            layer.effect: DropShadow {
                verticalOffset: 2
                color: "#80000000"
                radius: 1
                samples: 3
            }

            fontSizeMode: Text.HorizontalFit
            minimumPointSize: 10
            font.pointSize: 12
        }

        MouseArea {
            id:secondMemberMouseMember
            anchors.fill: parent

            onClicked: {
                nextPair(qmlProperty.firstMemberInPairID)
                clickSound.play()
            }

        }
    }

    Rectangle {
        id: vsRectangle
        height: secondMemberRectangle.height / 3
        width: height
        color: "transparent"
        anchors.centerIn: playoffViewRectangle
        Image {
            id: versusIcon
            source: "qrc:/images/vs.png"
            anchors.fill: parent
            fillMode:  Image.PreserveAspectFit
        }
    }

    function nextPair(idElimination) {
        middlewareQML.eliminationPlayoffMember(idElimination)
        middlewareQML.getPlayoffPair()
    }

    property int count: 0

}
