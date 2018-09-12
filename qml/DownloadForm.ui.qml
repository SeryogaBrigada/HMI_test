import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    property real scale: 1.0
    property real progress: 75
    property string remainingTime: "0:00"

    implicitWidth: 1080 * scale
    implicitHeight: 1487 * scale

    signal cancelClicked
    signal hideClicked

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
        anchors.topMargin: 80 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: parent.width / 21
        font.bold: true
        text: qsTr("Downloading the update package...")
    }

    Label {
        id: remainingTimeLabel
        anchors.top: topLabel.bottom
        anchors.topMargin: 80 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: topLabel.font.pixelSize
        text: qsTr("Remaining time: ") + remainingTime
        clip: true
    }

    Label {
        id: progressLabel
        anchors.top: remainingTimeLabel.bottom
        anchors.topMargin: 80 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: topLabel.font.pixelSize * 1.5
        text: progress + "% " + qsTr("complete")
        clip: true
    }

    ProgressBar {
        id: progressBar
        anchors.top: progressLabel.bottom
        anchors.topMargin: 20 / scale
        anchors.left: parent.left
        anchors.leftMargin: 75 * scale
        anchors.right: parent.right
        anchors.rightMargin: 75 * scale
        value: progress
        to: 100
        clip: true
    }

    Button {
        id: cancelButton
        anchors.top: progressBar.bottom
        anchors.topMargin: 50 * scale
        anchors.left: parent.left
        anchors.leftMargin: 75 * scale
        font.pixelSize: topLabel.font.pixelSize * 0.8
        width: font.pixelSize * 9
        text: qsTr("CANCEL")
    }

    Button {
        id: hideButton
        anchors.top: cancelButton.top
        anchors.right: parent.right
        anchors.rightMargin: 75 * scale
        font.pixelSize: cancelButton.font.pixelSize
        width: cancelButton.width
        text: qsTr("HIDE")
    }
}
