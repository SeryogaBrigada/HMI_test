import QtQuick 2.9
import QtQuick.Controls 2.2
import qt.provider 1.0

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("Stack")

    Provider {
        id: provider
        onUpdateAvailable: stackView.initialItem = mainView
    }

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            text: stackView.depth > 1 ? "\u2715" : "\u003C" + "     " + qsTr("Update information")
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
   //     initialItem: mainView
        anchors.fill: parent
    }

    Component {
        id: mainView

        HomeForm {
            onDownloadClicked: stackView.push(downloadView)
        }
    }

    Component {
        id: downloadView

        DownloadForm {
            onCancelClicked: stackView.push(downloadComplete)
            onHideClicked: console.log("Hide clicked")
        }
    }

    Component {
        id: downloadComplete

        DownloadCompleteForm {
            onInstallClicked: stackView.push(installation)
            onQuitClicked: Qt.quit()
        }
    }

    Component {
        id: installation

        InstallationForm {
            onCancelClicked: console.log("Cansel clicked")
        }
    }
}
