import QtQuick 2.12

Item {
    Rectangle {
        radius: main.dp(3)
        height: countMembersListView.count > 0 ? countMembersListView.currentItem.height - main.dp(5)*2 : 0
        width: countMembersListView.count > 0 ? countMembersListView.currentItem.width - main.dp(5)*2 : 0

        x: countMembersListView.count > 0 ? countMembersListView .currentItem.x + main.dp(5) : 0
        y: countMembersListView.count > 0 ? countMembersListView .currentItem.y + main.dp(5) : 0

        Behavior on y { SpringAnimation { spring: 3; damping: 0.3 } }

        color: "#518dbb"
    }
}

