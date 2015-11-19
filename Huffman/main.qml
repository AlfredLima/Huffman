import QtQuick 2.5
import QtQuick.Controls 1.4
import QtQuick.Layouts 1.1
import QtQuick.Window 2.0

ApplicationWindow{
    id: ui
    function mm(value){
        return value*Screen.pixelDensity
    }
    function hQuota(percent){
        return (percent/100)*ui.height
    }
    function wQuota(percent){
        return (percent/100)*ui.width
    }
    visible: true
    width: mm(100)
    height: mm(60)

    Rectangle{
        id: menu
        color: "#232323"
        height: ui.height
        width: mm(30)
        ColumnLayout{
            anchors.centerIn: parent
            QButton{
                txt.text: "Comprimir"
                mouse.onClicked: {
                    _huff.Huff(choose.path.text,choose.path.text)
                }
            }
            QButton{
                txt.text: "Descomprimir"
                mouse.onClicked: {
                    _dehuff.DHuff(choose.path.text,choose.path.text)
                }
            }
        }
    }
    Rectangle{
        anchors.left: menu.right
        height: ui.height
        width: ui.width - menu.width
        color: "#006e9f"
        Image {
            source: "qrc:/data/img/11412394_407750046078820_6932822019341529347_n.jpg"
            anchors {
                right:parent.right
                bottom:parent.bottom
            }

            fillMode:Image.PreserveAspectFit

            width:(wQuota(30) > hQuota(30)) ? wQuota(30) : hQuota(30)
            height:width
        }
        ColumnLayout{
            anchors.centerIn: parent
            Rectangle{
                id: outName
                height: mm(8)
                width: mm(35)
                radius: mm(2)
                TextEdit{
                    anchors.fill: parent
                    anchors.centerIn: parent
                    font.pixelSize: 20
                    clip: true
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter

                }
            }
            QChoose{
                id: choose
            }
        }
    }
}
