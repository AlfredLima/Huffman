import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.4


Row{
    property alias path: path
    property alias file: file
    property string txt: ""
    spacing: parent.width/50
    FileDialog {
        id: file
        title: qsTr("Selecione " + txt)
//        folder: shortcuts.home

        onAccepted: {
            path.text = (file.fileUrl) ;  path.text = path.text.replace("file://","")
            consoleTextArea.log(path.text + " selected")
            file.close()
        }
        onRejected: {
            consoleTextArea.log("Canceled")
            file.close()
        }
    }
    Text {
        id: name
        text: qsTr(txt)
    }
    Rectangle{
        height: mm(8)
        width: mm(35)
        radius: mm(2)
        TextEdit{
            anchors.fill: parent
            anchors.centerIn: parent
            id: path
            font.pixelSize: 20
            clip: true
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

        }
    }
    QButton{
        qbutton.radius: height/2
        qbutton.width : height
        qbutton.border.color: "white"
        txt.text: "..."
        mouse.onClicked: {
            file.open()
        }
    }
}
