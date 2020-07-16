import QtQuick 2.0
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0
import QtQuick.Dialogs 1.3
import QtMultimedia 5.12
import "qrc:/qml/views"
import "qrc:/qml/delegates"

ApplicationWindow {
    id: main
    x: 0
    y: 0

    minimumWidth: main.dp(380)
    minimumHeight: main.dp(640)
    
    title: qsTr("Championship")
    visible: true
    onClosing: {
        if (middlewareQML.isAndroid())
        {
            close.accepted = false
        }
    }

    Audio {
           id: clickSound
           source: "qrc:/sounds/click.mp3"
       }

    header: Rectangle {
        id: headerRectangle
        height: main.height / 14
        width: main.width
        color: "#F29F05"
        visible: false

        state: "hide"
        states: [
            State {
                name: "hide"

            },
            State {
                name: "show"
                PropertyChanges {
                    target: headerRectangle
                    visible: true
                }
            }
        ]

        Image {
            id: logoHeader
            width: parent.width
            height: parent.height / 1.7
            anchors.centerIn: parent
            source: "qrc:/images/worldrating.png"
            smooth: true
            fillMode: Image.PreserveAspectFit
        }

        Text {
            id: stageText

            width: headerRectangle.width/4 /*- backButtonRectangle.width - logoHeader.width -main.dp(20)*/
            height: headerRectangle.height
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight

            anchors {
                rightMargin:  main.dp(15)
                verticalCenter: headerRectangle.verticalCenter
                right: headerRectangle.right
            }

            font.bold: true
            color: "white"
            minimumPointSize: 10
            font.pointSize: 14
            visible: false

            state: "hide"

            states: [
                State {
                    name: "hide"
                },
                State {
                    name: "show"
                    PropertyChanges {
                        target: stageText
                        visible: true
                    }
                }
            ]
        }

        Rectangle {
            id: backButtonRectangle
            width: main.dp(35)
            height: headerRectangle.height - main.dp(5)
            anchors {
                left: headerRectangle.left
                leftMargin: main.dp(10)
                verticalCenter: headerRectangle.verticalCenter
            }
            visible: false
            color: headerRectangle.color

            Image {
                id: backButton
                source: "qrc:/images/left.png"
                anchors.fill: backButtonRectangle
                smooth: true
                fillMode: Image.PreserveAspectFit


            }

            state: "hide"

            states: [
                State {
                    name: "hide"
                },
                State {
                    name: "show"
                    PropertyChanges {
                        target: backButtonRectangle
                        visible: true
                    }
                }
            ]

            MouseArea {
                id: backButtonMouseArea
                anchors.fill: backButtonRectangle
                onClicked: {
                    backView()
                    clickSound.play()
                }
            }
        }
    }

    footer: Rectangle {
        id: footerRectangle
        height: main.height / 14
        width: main.width
        color: "#F29F05"
        visible: false

        state: "hide"
        states: [
            State {
                name: "hide"

            },
            State {
                name: "show"
                PropertyChanges {
                    target: footerRectangle
                    visible: true
                }
            }
        ]

        Row {
            id: footerRow
            width: mailRectangle.width + rateRectangle.width + main.dp(15) + main.dp(5)
            height: footerRectangle.height
            anchors.centerIn: footerRectangle


            spacing: main.dp(15)
            Rectangle {
                id: mailRectangle
                width: main.dp(50)
                height: footerRectangle.height
                visible: true
                color: footerRectangle.color
                scale: !mailMouseArea.pressed ? 1 : 0.9

                Image {
                    id: mailImage
                    source: "qrc:/images/mail.png"
                    anchors.fill: mailRectangle
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    id: mailMouseArea
                    anchors.fill: parent

                    onClicked: {
                        onLinkActivated: Qt.openUrlExternally("mailto:ikespil@mail.ru")
                        clickSound.play()
                    }
                }
            }

            Rectangle {
                id: rateRectangle
                width: main.dp(50)
                height: footerRectangle.height
                scale: !rateMouseArea.pressed ? 1 : 0.9
                visible: true
                color: footerRectangle.color

                Image {
                    id: rateImage
                    source: "qrc:/images/rate.png"
                    anchors.fill: rateRectangle
                    smooth: true
                    fillMode: Image.PreserveAspectFit
                }

                MouseArea {
                    id: rateMouseArea
                    anchors.fill: parent

                    onClicked: {
                        onLinkActivated: Qt.openUrlExternally("22")
                        clickSound.play()
                    }
                }
            }
        }
    }

    Rectangle {
        anchors.fill: parent
        color: Qt.rgba(0, 0, 0, 1)
    }

    Loader {
        id: loader
        anchors.fill: parent
        source: "views/load.qml"
        visible: true
        state: "defaut"
        states: [
            State {
                name: "default"
            },
            State {
                name: "hide"
                PropertyChanges {
                    target: loader
                    visible: false
                }
            }
        ]
    }

    Connections {
        target: middlewareQML

        onContestLoaded: {
            contestsList.append( { id: qmlProperty.idContest,
                                    name: qmlProperty.nameContest,
                                    description: qmlProperty.descriptionContest,
                                    countPlay: qmlProperty.countPlayContest })
        }

        onContestsLoaded: {
            showMainView()
            animatePrevIconOpacity.start()
            animateNextIconOpacity.start()
        }

        onContestCountLoaded: {
            countPages = (qmlProperty.contestsCount + countItemsOnPage - 1) / countItemsOnPage // округление в большую сторону
            hideMainView()
            middlewareQML.getContestsByRangeFromServer(1 + (currentPage - 1) * countItemsOnPage, countItemsOnPage)

            pagesIconsController()
        }

        onValuesOfPowerOfTwoLoaded: {
            showCountMemberView()
        }

        onSignalPlayoffStarted : {
            hideCountMemberView()
            hideLoaderScreen()
            hideMainView()
            hideRatingScreen()
            showBackButton()
            showFooter()
            showHeader()

            middlewareQML.getPlayoffPair()
            showPlayoffScreen()
        }

        onSignalRatingProcessingWait : {
            hidePlayoffScreen()
            showLoaderScreen()
            hideFooter()
            hideHeader()
        }

        onSignalPlayoffFinished : {
            hideCountMemberView()
            hideLoaderScreen()
            hideMainView()
            hideStageText()
            hidePlayoffScreen()
            showRatingScreen()
            showBackButton()
            showFooter()
            showHeader()
        }

        onSignalErrorResponse: {
            responseErrorMessage.title = qsTr("Server error")
            responseErrorMessage.text = qmlProperty.errorResponse
            responseErrorMessage.open()
            showMainView()
        }
    }

    Rectangle {
        id: mainView
        anchors.fill: parent
        color: "white"
        visible: false
        state: "hide"
        states: [
            State {
                name: "hide"
            },
            State {
                name: "show"
                PropertyChanges {
                    target: mainView
                    visible: true
                }
            }
        ]

        MouseArea {
            width: main.width
            height: main.height
            preventStealing: true
            property real velocity: 0.0
            property int xStart: 0
            property int xPrev: 0
            property bool tracing: false
            onPressed: {
                xStart = mouse.x
                xPrev = mouse.x
                velocity = 0
                tracing = true
            }
            onPositionChanged: {
                if ( !tracing ) return
                var currVel = (mouse.x-xPrev)
                velocity = (velocity + currVel)/2.0
                xPrev = mouse.x
                if ( velocity > 15 && mouse.x > parent.width*0.2 ) {
                    tracing = false
                }
                else if (velocity < -15 && mouse.x < parent.width*0.2) {
                    tracing = false
                }
            }
            onReleased: {
                tracing = false
                if ( velocity > 15 && mouse.x > parent.width*0.2 ) {
                    prevSwipe()
                }
                else if (velocity < -15 && mouse.x < parent.width*0.2) {
                    nextSwipe()
                }
            }
        }

        Rectangle {
            id: prevPageButton
            height: mainView.height
            width: mainView.width / 19
            anchors.verticalCenter: mainView.verticalCenter
            anchors.left: mainView.left
            color: "white"
            opacity: 0.1

            Image {
                id: prevIcon
                anchors.fill: prevPageButton
                source: "qrc:/images/leftblack.png"
                fillMode: Image.PreserveAspectFit
                visible: false
                opacity: 1

                state: "hide"
                states: [
                    State {
                        name: "hide"

                    },
                    State {
                        name: "show"
                        PropertyChanges {
                            target: prevIcon
                            visible: true
                        }
                    }
                ]
                NumberAnimation {
                    id: animatePrevIconOpacity
                    target: prevIcon
                    properties: "opacity"
                    from: 0.0
                    to: 1
                    duration: 2000
                    loops: Animation.Infinite
                    easing {type: Easing.OutBack;}
                }

            }

            MouseArea {
                id: prevIconMouseArea
                anchors.fill: parent
                onClicked: {
                    prevSwipe()
                }
            }
        }

        Rectangle {
            id: nextPageButton
            height: mainView.height
            width: mainView.width / 19
            anchors.verticalCenter: mainView.verticalCenter
            anchors.right: mainView.right
            color: "white"
            opacity: 0.1

            Image {
                id: nextIcon
                anchors.fill: nextPageButton
                source: "qrc:/images/rightblack.png"
                fillMode: Image.PreserveAspectFit
                visible: false
                opacity: 1
                state: "hide"
                states: [
                    State {
                        name: "hide"

                    },
                    State {
                        name: "show"
                        PropertyChanges {
                            target: nextIcon
                            visible: true
                        }
                    }
                ]
                NumberAnimation {
                    id: animateNextIconOpacity
                    target: nextIcon
                    properties: "opacity"
                    from: 0.0
                    to: 1
                    duration: 2000
                    loops: Animation.Infinite
                    easing {type: Easing.OutBack;}
                }
            }

            MouseArea {
                id: nextIconMouseArea
                anchors.fill: nextPageButton
                onClicked: {
                     nextSwipe()
                }
            }


        }

        Rectangle {
            id: layoutContests
            height: mainView.height
            width: mainView.width - prevPageButton.width - prevPageButton.width - main.dp(5)
            color: "white"

            anchors {
                top: mainView.top
                verticalCenter: mainView.verticalCenter
                horizontalCenter: mainView.horizontalCenter
                bottomMargin: 1
                rightMargin: 1
            }

            GridView {
                id: contestsGridView
                anchors {
                    fill: layoutContests
                    topMargin: main.dp(15)
                    leftMargin: main.dp(5)
                }

                cellHeight: layoutContests.height / (countItemsOnPage/2) - main.dp(5)
                cellWidth: layoutContests.width / 2
                flow:GridView.TopToBottom
                clip: true
                delegate: ContestItem{}
                interactive: false

                model: ListModel { id: contestsList }

            }
        }

        property int wantedHeight: contestsGridView.height/main.dp(200)
        property int wantedWidth: contestsGridView.width/main.dp(175)

        function getCellHeightForMenuGridView()
        {
            return wantedHeight!=0 ? contestsGridView.height/wantedHeight : contestsGridView.height
        }

        function getCellWidthForMenuGridView()
        {
            return wantedWidth!=0 ? contestsGridView.width/wantedWidth : contestsGridView.width
        }
    }

    Loader {
        id: countMemberView
        anchors.fill: parent
        source: "views/countMember.qml"
        visible: false
        state: "hide"
        states: [
            State {
                name: "hide"
            },
            State {
                name: "show"
                PropertyChanges {
                    target: countMemberView
                    visible: true
                }
            }
        ]
    }

    Loader {
        id: playoffView
        anchors.fill: parent
        source: "views/PlayoffView.qml"
        visible: false
        state: "hide"
        states: [
            State {
                name: "hide"
            },
            State {
                name: "show"
                PropertyChanges {
                    target: playoffView
                    visible: true
                }
            }
        ]
    }

    Loader {
        id: ratingView
        anchors.fill: parent
        source: "views/RatingView.qml"
        visible: false
        state: "hide"
        states: [
            State {
                name: "hide"
            },
            State {
                name: "show"
                PropertyChanges {
                    target: ratingView
                    visible: true
                }
            }
        ]
    }

    MessageDialog {
        id: responseErrorMessage
        title: "error"
        text: "error"
        onAccepted: {
            responseErrorMessage.close()
        }
    }

    property int countItemsOnPage: 8
    property int currentPage: 1
    property int countPages: 0
    property int dpi: Screen.pixelDensity * 25.4
    property int numberOfMembersProperty: 0
    property int currentContestID: 0

    function dp(x){
        if(dpi < 120) {
            return x;
        } else if (dpi>350)
        {
            return x*(dpi/200)
        }
        else if (dpi>240)
        {
            return x*(dpi/200)
        }
        else if (dpi>200)
        {
            return x*(dpi/160)
        }
        else
        {
            return x*(dpi/120);
        }
    }

    function pagesIconsController() {
        if (currentPage != 1 && currentPage != countPages) {
            prevIcon.state = "show"
            nextIcon.state = "show"
            return
        }
        else if (currentPage === 1 && currentPage === countPages) {
            prevIcon.state = "hide"
            nextIcon.state = "hide"
            return
        }
        else {
            if (currentPage === 1) {
                prevIcon.state = "hide"
            } else {
                prevIcon.state = "show"
            }

            if (currentPage === countPages) {
                nextIcon.state = "hide"
            } else {
                nextIcon.state = "show"
            }

            return
        }
    }

    function prevSwipe() {
        if (currentPage != 1) {
            clickSound.play()
            contestsList.clear()
            currentPage = currentPage - 1
            middlewareQML.getContestsByRange(1 + (currentPage - 1) * countItemsOnPage, countItemsOnPage)
        }
        pagesIconsController()
    }

    function nextSwipe() {
        if (currentPage != countPages) {
            clickSound.play()
            contestsList.clear()
            currentPage = currentPage + 1
            middlewareQML.getContestsByRange(1 + (currentPage - 1) * countItemsOnPage, countItemsOnPage)
            pagesIconsController()
        }
    }

    function hideMainView() {
        mainView.state = "hide"
        hideFooter()
        hideHeader()
        showLoaderScreen()
    }

    function showMainView() {
        hideLoaderScreen()
        showFooter()
        showHeader()
        mainView.state = "show"
    }


    function prepareToOpenCountMembersWindow(idFromList, idContest, isAdvertisment) {
        setCurrentContestID(idContest)
        middlewareQML.getCountMembersForContest(idContest)
    }

    function showCountMemberView() {
        showBackButton()
        countMemberView.state = "show"
    }

    function hideCountMemberView() {
        countMemberView.state = "hide"
    }

    function showBackButton() {
        backButtonRectangle.state = "show"
    }

    function hideBackButton() {
        backButtonRectangle.state = "hide"
    }

    function showLoaderScreen() {
        loader.state = "show"
    }

    function hideLoaderScreen() {
        loader.state = "hide"
    }

    function showFooter() {
        footerRectangle.state = "show"
    }

    function hideFooter() {
        footerRectangle.state = "hide"
    }

    function showHeader() {
        headerRectangle.state = "show"
    }

    function hideHeader() {
        headerRectangle.state = "hide"
    }

    function hidePlayoffScreen() {
        playoffView.state = "hide"
    }

    function showPlayoffScreen() {
        playoffView.state = "show"
    }

    function hideRatingScreen() {
        ratingView.state = "hide"
    }

    function showRatingScreen() {
        ratingView.state = "show"
    }

    function showStageText() {
        stageText.state = "show"
    }

    function hideStageText() {
        stageText.state = "hide"
    }

    function setStageText(count) {
        stageText.text = qsTr("Stage :" + count + "/" + qmlProperty.countPairsInStage)
    }

    function backView() {
        hideBackButton()
        hideCountMemberView()
        hidePlayoffScreen()
        hideRatingScreen()
        hideStageText()

        showMainView()
    }

    function setCurrentContestID(id) {
        currentContestID = id
    }

    function numberOfMembersSelected(numberOfMembers) {
        requestMembers(numberOfMembers)
        hideCountMemberView()
        hideMainView()
        showLoaderScreen()
    }

    function requestMembers(numberOfMembers) {
        middlewareQML.startNewContest(currentContestID, numberOfMembers)
    }

}


