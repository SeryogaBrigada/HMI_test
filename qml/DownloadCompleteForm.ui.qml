import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    property real scale: 1.0
    property string estimatedMinutes: "44"

    implicitWidth: 1080 * scale
    implicitHeight: 1487 * scale

    signal installClicked
    signal quitClicked

    Connections {
        target: installButton
        onClicked: state != 'ConfirmState' ? state = 'ConfirmState' : installClicked()
    }

    Connections {
        target: quiteButton
        onClicked: quitClicked()
    }

    Label {
        id: topLabel
        anchors.top: parent.top
        anchors.topMargin: 80 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: parent.width / 21
        font.bold: true
        text: qsTr("Download complete")
        color: "#505050"
    }

    Column {
        id: attentionItem
        anchors.top: topLabel.bottom
        anchors.topMargin: 50 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        visible: false

        Label {
            font.pixelSize: topLabel.font.pixelSize * 0.6
            text: qsTr("You are about to start installing update 02")
        }

        Label {
            font.pixelSize: topLabel.font.pixelSize * 0.65
            font.bold: true
            text: qsTr("It cannot be aborted once installation gets started.")
        }
    }

    Label {
        id: estimatedTimeLabel
        anchors.top: attentionItem.bottom
        anchors.topMargin: 80 * scale
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: topLabel.font.pixelSize * 0.75
        font.bold: topLabel.font.bold
        clip: true
        text: qsTr("Estimated installation time: ") + estimatedMinutes + qsTr(
                  " minutes")
    }

    TextArea {
        id: infoText
        anchors.top: estimatedTimeLabel.bottom
        anchors.topMargin: 40 * scale
        anchors.left: parent.left
        anchors.leftMargin: 75 * scale
        anchors.right: parent.right
        anchors.rightMargin: 75 * scale
        font.pixelSize: topLabel.font.pixelSize * 0.7
        wrapMode: Text.WordWrap
        text: qsTr(
                  "Installation will begin 2 minutes after approval has been given, "
                  + "please leave the vehicle and do not leave anything or anyone inside the vehicle. "
                  + "While the installation is in progress, vehicle functions will not be available. "
                  + "The alarm will be disabled and the vehicle can only be opened mechanically. "
                  + "Once the installation is started, the update cannot be canceled or stopped. "
                  + "A message will be send to your phone linked with your LINK&CO ID when the installation is complete.")
    }

    Button {
        id: installButton
        anchors.top: infoText.bottom
        anchors.topMargin: 40 * scale
        anchors.left: parent.left
        anchors.leftMargin: 75 * scale
        font.pixelSize: topLabel.font.pixelSize * 0.8
        width: font.pixelSize * 9
        text: qsTr("INSTALL NOW")
    }

    Button {
        id: quiteButton
        anchors.top: installButton.top
        anchors.right: parent.right
        anchors.rightMargin: 75 * scale
        font.pixelSize: installButton.font.pixelSize
        text: qsTr("QUIT")
        width: installButton.width
    }

    states: [
        State {
            name: "ConfirmState"

            PropertyChanges {
                target: topLabel
                text: "\u23FC" + qsTr(" ATTENTION")
            }

            PropertyChanges {
                target: attentionItem
                visible: true
            }

            PropertyChanges {
                target: installButton
                text: qsTr("CONTINUE")
            }

            PropertyChanges {
                target: estimatedTimeLabel
                anchors.topMargin: 77 * scale
            }
        }
    ]
}
