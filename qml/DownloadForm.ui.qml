import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 600
    height: 400

    signal cancelClicked
    signal hideClicked

    property int progress: 75

    Connections {
        target: cancelButton
        onClicked: cancelClicked()
    }

    Connections {
        target: hideButton
        onClicked: hideClicked()
    }

    Label {
        id: topLabel
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        font.bold: true
        text: qsTr("Downloading the update package...")
    }

    Label {
        id: remainingTimeLabel
        anchors.top: topLabel.bottom
        anchors.topMargin: 40
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: topLabel.font.pixelSize * 1.5
        font.bold: true
        text: progress + "% " + qsTr("complete")
        clip: true
    }

    ProgressBar {
        id: progressBar
        anchors.top: remainingTimeLabel.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width - 120
        value: progress
        height: 20
        to: 100
    }

    Button {
        id: cancelButton
        anchors.top: progressBar.bottom
        anchors.topMargin: 40
        anchors.left: parent.left
        anchors.leftMargin: 60
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        width: font.pixelSize * 9
        text: qsTr("CANCEL")
    }

    Button {
        id: hideButton
        anchors.top: cancelButton.top
        anchors.right: parent.right
        anchors.rightMargin: 60
        font.pixelSize: cancelButton.font.pixelSize
        width: cancelButton.width
        text: qsTr("HIDE")
    }
}
