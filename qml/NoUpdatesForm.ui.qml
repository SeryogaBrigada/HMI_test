import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    property real scale: 1.0

    implicitWidth: 1080 * scale
    implicitHeight: 1487 * scale

    Label {
        text: qsTr("System is up to date.")
        anchors.verticalCenterOffset: -50 * scale
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: parent.width / 16
    }
}
