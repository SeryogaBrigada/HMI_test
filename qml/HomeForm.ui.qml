import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    width: 600
    height: 400

    signal downloadClicked

    property string updates: "— This is new\n— And is also new\n— And that is new"
    property string totalSize: "1234 MB"

    Connections {
        target: downlodButton
        onClicked: downloadClicked()
    }

    Label {
        id: discriptionLabel
        text: qsTr("Discription:")
        anchors.left: parent.left
        anchors.leftMargin: 30
        anchors.top: parent.top
        anchors.topMargin: 20
        font.pixelSize: Qt.application.font.pixelSize * 1.6
    }

    ScrollView {
        id: scrollView
        anchors.top: discriptionLabel.bottom
        anchors.topMargin: 20
        anchors.left: discriptionLabel.left
        height: discriptionContextLabel.height > 400 ? 400 : discriptionContextLabel.height
        width: parent.width - 60
        clip: true

        Label {
            id: discriptionContextLabel
            font.pixelSize: discriptionLabel.font.pixelSize
            text: updates
        }
    }

    Column {
        anchors.top: scrollView.bottom
        anchors.topMargin: 20
        anchors.left: discriptionLabel.left
        spacing: 10

        Label {
            id: sizeLabel
            font.pixelSize: discriptionLabel.font.pixelSize
            text: qsTr("Size: ") + totalSize
        }

        Button {
            id: downlodButton
            font.pixelSize: sizeLabel.font.pixelSize
            width: font.pixelSize * 9
            text: qsTr("Download")
        }

        Label {
            font.pixelSize: Qt.application.font.pixelSize * 1.2
            color: "#505050"
            text: qsTr("The download will not interfere with your use of the vehicle.\n"
                       + "Data charges may apply.")
        }
    }
}
