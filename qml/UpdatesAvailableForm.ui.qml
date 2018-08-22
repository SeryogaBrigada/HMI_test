import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    property real scale: 1.0
    property string updates: "— This is new\n— And is also new\n— And that is new"
    property string totalSize: "1234 MB"

    implicitWidth: 1080 * scale
    implicitHeight: 1487 * scale

    signal downloadClicked

    Connections {
        target: downlodButton
        onClicked: downloadClicked()
    }

    Label {
        id: discriptionLabel
        text: qsTr("Discription:")
        anchors.left: parent.left
        anchors.leftMargin: 50 * scale
        anchors.top: parent.top
        anchors.topMargin: 80 * scale
        font.pixelSize: parent.width / 21
    }

    ScrollView {
        id: scrollView
        anchors.top: discriptionLabel.bottom
        anchors.topMargin: 40 * scale
        anchors.left: discriptionLabel.left
        anchors.right: parent.right
        anchors.rightMargin: 50 * scale
        height: discriptionContextLabel.height
                > (parent.height * 0.6) ? (parent.height * 0.6) : discriptionContextLabel.height
        clip: true

        Label {
            id: discriptionContextLabel
            font.pixelSize: discriptionLabel.font.pixelSize * 0.8
            text: updates
        }
    }

    Column {
        anchors.top: scrollView.bottom
        anchors.topMargin: 40 * scale
        anchors.left: discriptionLabel.left
        spacing: 40 * scale

        Label {
            id: sizeLabel
            font.pixelSize: discriptionLabel.font.pixelSize
            text: qsTr("Size: ") + totalSize
        }

        Button {
            id: downlodButton
            font.pixelSize: sizeLabel.font.pixelSize * 0.8
            width: font.pixelSize * 9
            text: qsTr("Download")
        }

        Label {
            font.pixelSize: discriptionLabel.font.pixelSize * 0.6
            color: "#505050"
            text: qsTr("The download will not interfere with your use of the vehicle.\n"
                       + "Data charges may apply.")
        }
    }
}
