import QtQuick 2.12
import QtQuick.Dialogs 1.3
import QtQuick.Controls 1.4
import QtGraphicalEffects 1.0
import "qrc:/qml/delegates"
import "qrc:/qml/highlighters"

Rectangle {
    id: countMemberRectangle
    anchors.fill: parent
    color: mainView.color

    Connections {
        target: middlewareQML

        onMembersCountForContestLoaded: {
            countMembersList.clear()
            middlewareQML.getValuesOfPowerOfTwo(qmlProperty.membersCountForContest)
        }

        onValueOfPowerOfTwoLoaded: {
            countMembersList.append( { val: qmlProperty.valueOfPowerOfTwo })
        }
    }

    Text {
        id: countMemberHeader
        anchors {
            top: countMemberRectangle.top
            topMargin: main.dp(20)
            horizontalCenter: countMemberRectangle.horizontalCenter
        }

        text: qsTr("Выберите количество участников")
        wrapMode: Text.WordWrap

        font.bold: true
        color: "orange"
        minimumPointSize: 12
        font.pointSize: 16

    }

    ListView {
        id: countMembersListView
        width: countMemberRectangle.width
        height: countMemberRectangle.height - countMemberHeader.height

        anchors {
            top: countMemberHeader.bottom
            bottom: countMemberRectangle.bottom
            topMargin: main.dp(15)
            horizontalCenter: countMemberRectangle.horizontalCenter
        }

        boundsBehavior: Flickable.StopAtBounds
        clip: true
        orientation: ListView.Vertical
        cacheBuffer: 200

        delegate: CountMemberItem{}

        model: ListModel { id: countMembersList }

    }

}


