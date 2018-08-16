import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    width: 600
    height: 400

    signal cancelClicked

    Connections {
        target: cancelButton
        onClicked: cancelClicked()
    }

    Label {
        id: topLabel
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        font.bold: true
        text: qsTr("Installation has started")
    }

    TextArea {
        id: infoText
        anchors.top: topLabel.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 1.2
        width: parent.width - 120
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
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 3
        clip: true
        text: "2:00"
    }

    TextArea {
        id: infoText2
        anchors.top: estimatedTimeLabel.bottom
        anchors.topMargin: 10
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 1.2
        width: parent.width - 120
        wrapMode: Text.WordWrap
        text: qsTr("The vehicle will not be usable during installation, "
                   + "a message will be sent to your phone linked with your LINK&CO ID "
                   + "when the update is complete")
    }

    Button {
        id: cancelButton
        anchors.top: infoText2.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        width: font.pixelSize * 9
        text: qsTr("CANCEL")
    }
}
