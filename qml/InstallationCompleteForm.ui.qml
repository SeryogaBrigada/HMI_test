import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    id: page
    width: 600
    height: 400

    signal quitClicked

    Connections {
        target: quitButton
        onClicked: quitClicked()
    }

    Label {
        id: textLabel
        text: qsTr("Installation complete")
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 3
        font.bold: true
    }

    Button {
        id: quitButton
        anchors.top: textLabel.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: Qt.application.font.pixelSize * 1.6
        width: font.pixelSize * 9
        text: qsTr("QUIT")
    }
}
