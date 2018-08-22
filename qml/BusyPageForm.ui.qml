import QtQuick 2.9
import QtQuick.Controls 2.2

Page {
    property real scale: 1.0

    implicitWidth: 1080 * scale
    implicitHeight: 1487 * scale

    BusyIndicator {
        anchors.centerIn: parent
        width: parent.width / 2
        height: parent.width / 2
        anchors.verticalCenterOffset: -50 * scale
    }
}
