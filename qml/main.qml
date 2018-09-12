import QtQuick 2.9
import QtQuick.Controls 2.2
import qt.provider 1.0

ApplicationWindow {
    id: window
    visible: true
    title: qsTr("Sachertorte")

    property real scale: applicationScale

    width: 1080 * scale
    height: 1487 * scale

    Provider {
        id: provider
        onNoUpdates: stackView.push(noUpdatesAvailablePage)
        onUpdateAvailable: stackView.push(updatesAvailablePage)

        onDownloadComplete: {
            stackView.push(downloadCompletePage)
            window.visible = true
        }
        onInstallationComplete: stackView.push(noUpdatesAvailablePage)
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u2715" : "\u003C     " + qsTr("Update information")
            font.pixelSize: window.width / 21
            font.bold: true
            onClicked: Qt.quit()
        }
    }

    StackView {
        id: stackView
        initialItem: busyPage
        anchors.fill: parent
        visible: true
    }

    Component {
        id: busyPage

        BusyPageForm {
            scale: applicationScale
        }
    }

    Component {
        id: noUpdatesAvailablePage

        NoUpdatesForm {
            scale: applicationScale
        }
    }

    Component {
        id: updatesAvailablePage

        UpdatesAvailableForm {
            scale: applicationScale
            updates: provider.updates
            totalSize: provider.updateSize
            onDownloadClicked: {
                provider.downloadUpdates()
                stackView.push(downloadPage)
            }
        }
    }

    Component {
        id: downloadPage

        DownloadForm {
            scale: applicationScale
            progress: provider.downloadProgress
            remainingTime: provider.remainingDownloadTime
            onCancelClicked: Qt.quit()
            onHideClicked: window.visible = false
        }
    }

    Component {
        id: downloadCompletePage

        DownloadCompleteForm {
            scale: applicationScale
            onInstallClicked: {
                provider.installUpdates()
                stackView.push(installationPage)
            }
            onQuitClicked: Qt.quit()
        }
    }

    Component {
        id: installationPage

        InstallationForm {
            scale: applicationScale
            onCancelClicked: console.log("Cansel clicked")
        }
    }
}
