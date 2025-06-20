import QtQuick
import t 1.0

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    Rectangle
    {
        SomeClass
        {
            id: myClass
        }

        id : rect
        width: 150
        height: 150
        color: "red"
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.topMargin: 10
        anchors.leftMargin: 10
        MouseArea
        {
            anchors.fill: parent
            onClicked: {
                rect.color = "slateblue"
                // classBase.display();
                myClass.display();
            }
        }
    }
}
