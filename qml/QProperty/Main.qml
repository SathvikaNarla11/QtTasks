import QtQuick
import QtQuick.Controls

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Column
    {
        anchors.centerIn: parent
        spacing: 20

        Text {
            id: txt
            text: "Current value : " +someClass.value  //qsTr("text")
            font.pixelSize: 24
        }

        Button
        {
            text: "Increase value"
            onClicked:
            {
                someClass.value += 1
            }
        }
    }
}
