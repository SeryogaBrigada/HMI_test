import QtQuick 2.9
import QtQuick.Controls 2.2
import qt.provider 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Aktualizr HMI GUI")

    Provider {
        id: provider
        onUpdateAvailable: stackView.visible = true
        onDownloadComplete: {
            stackView.push(downloadComplete)
            window.visible = true
        }
        onInstallationComplete: stackView.push(installationComplete)
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u2715" : "\u003C     " + qsTr("Update information")
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            font.bold: true
            onClicked: {
                if (stackView.depth > 1) {
                    Qt.quit()
                } else {
                    console.log("toolButton clicked")
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: mainView
        anchors.fill: parent
        visible: false
    }

    Component {
        id: mainView

        HomeForm {
            updates: provider.updates
            totalSize: provider.updateSize
            onDownloadClicked: {
                provider.downloadUpdates()
                stackView.push(downloadView)
            }
        }
    }

    Component {
        id: downloadView

        DownloadForm {
            progress: provider.downloadProgress
            onCancelClicked: Qt.quit()
            onHideClicked: window.visible = false
        }
    }

    Component {
        id: downloadComplete

        DownloadCompleteForm {
            onInstallClicked: {
                provider.installUpdates()
                stackView.push(installation)
            }
            onQuitClicked: Qt.quit()
        }
    }

    Component {
        id: installation

        InstallationForm {
            onCancelClicked: console.log("Cansel clicked")
        }
    }

    Component {
        id: installationComplete

        InstallationCompleteForm {
            onQuitClicked: Qt.quit()
        }
    }
}
