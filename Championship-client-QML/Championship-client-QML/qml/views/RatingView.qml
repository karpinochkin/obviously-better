import QtQuick 2.0
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import "qrc:/qml/delegates"

Rectangle {
    id: ratingViewRectangle
    anchors.fill: parent
    color: mainView.color

    Connections {
        target: middlewareQML

        onSignalPlayoffRatingValueLoaded: {
            myRatingListModel.append({ idContest: qmlProperty.ratingIdContest,
                                     idMember: qmlProperty.ratingIdMember,
                                     points: qmlProperty.ratingPoints,
                                     nameMember: qmlProperty.ratingNameMember,
                                     number: qmlProperty.ratingItemNumber} )

        }

        onSignalPlayoffWorldRatingValueLoaded: {
            worldRatingListModel.append({ idContest: qmlProperty.ratingWorldIdContest,
                                            idMember: qmlProperty.ratingWorldIdMember,
                                            points: qmlProperty.ratingWorldPoints,
                                            nameMember: qmlProperty.ratingWorldNameMember,
                                            number: qmlProperty.ratingWorldItemNumber })
        }

        onSignalPlayoffStarted : {
            myRatingListModel.clear()
            worldRatingListModel.clear()
        }

        onSignalRatingWasSentToServer: {
            middlewareQML.getRatingByContest(qmlProperty.ratingIdContest)
        }

        onSignalPlayoffFinished: {

        }
    }

    TabView {
        id: tabView
        anchors.fill: parent
        anchors.margins: main.dp(5)

        Tab {
            id: tab1
            title: qsTr("My rating")
            Rectangle {
                id: tab1Rectangle
                anchors.fill: parent

                ListView {
                    id: myRatingListView
                    anchors.fill: parent
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    orientation: ListView.Vertical
                    cacheBuffer: 200

                    delegate: RatingItem{}

                    model: myRatingListModel
                }
            }
        }

        Tab {
            id: tab2
            title: qsTr("World rating (Top 20)")
            Rectangle {
                id: tab2Rectangle
                anchors.fill: parent

                ListView {
                    id: worldRatingListView
                    anchors.fill: parent
                    boundsBehavior: Flickable.StopAtBounds
                    clip: true
                    orientation: ListView.Vertical
                    cacheBuffer: 200

                    delegate: RatingItem{}

                    model: worldRatingListModel
                }
            }
        }
        style: TabViewStyle {
                frameOverlap: 1
                tab: Rectangle {
                    color: styleData.selected ? "white" :"orange"
                    border.color:  "orange"
                    implicitWidth: ratingViewRectangle.width / 2
                    implicitHeight: main.dp(50)
                    radius: 2
                    Text {
                        id: text
                        anchors.centerIn: parent
                        text: styleData.title
                        color: styleData.selected ? "orange" : "white"
                        font.bold: true
                    }
                }
                frame: Rectangle {
                    color: Qt.darker("white")
                    opacity: 0.2
                }
            }
    }
    ListModel { id: myRatingListModel }
    ListModel { id: worldRatingListModel }

}
