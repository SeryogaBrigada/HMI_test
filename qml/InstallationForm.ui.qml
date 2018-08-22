import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    property real scale: 1.0
    property string estimatedMinutes: "2:00"

    implicitWidth: 1080 * scale
    implicitHeight: 1487 * scale

    signal cancelClicked

    Connections {
        target: cancelButton
        onClicked: cancelClicked()
    }

    Label {
        id: topLabel
        anchors.top: parent.top
        anchors.topMargin: 80 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: parent.width / 21
        font.bold: true
        text: qsTr("Installation has started")
    }

    TextArea {
        id: infoText
        anchors.top: topLabel.bottom
        anchors.topMargin: 50 * scale
        anchors.left: parent.left
        anchors.leftMargin: 75 * scale
        anchors.right: parent.right
        anchors.rightMargin: 75 * scale
        font.pixelSize: topLabel.font.pixelSize * 0.6
        wrapMode: Text.WordWrap
        text: qsTr(
                  "You have 2 minutes to leave and lock the vehicle. "
                  + "Do not stay or leave anyone inside the vehicle during installation. "
                  + "Do not use any controls or handles in the vehicle, as operations may "
                  + "interrupt or delay the installation.")
    }

    Label {
        id: estimatedTimeLabel
        anchors.top: infoText.bottom
        anchors.topMargin: 20 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: topLabel.font.pixelSize * 1.8
        clip: true
        text: estimatedMinutes
    }

    TextArea {
        id: infoText2
        anchors.top: estimatedTimeLabel.bottom
        anchors.topMargin: 20 * scale
        anchors.left: parent.left
        anchors.leftMargin: 75 * scale
        anchors.right: parent.right
        anchors.rightMargin: 75 * scale
        font.pixelSize: infoText.font.pixelSize
        wrapMode: Text.WordWrap
        text: qsTr("The vehicle will not be usable during installation, "
                   + "a message will be sent to your phone linked with your LINK&CO ID "
                   + "when the update is complete")
    }

    Button {
        id: cancelButton
        anchors.top: infoText2.bottom
        anchors.topMargin: 40 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: topLabel.font.pixelSize * 0.8
        width: font.pixelSize * 9
        text: qsTr("CANCEL")
    }
}
