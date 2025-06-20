import QtQuick
import QtQuick.Controls
import QtQuick 2.15
import QtQuick.Controls 2.15
import t 1.0 //Registering a type


Window {
    id: root
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    SomeClass
    {
        id: myClass
    }

    Button{
        onClicked: myClass.funDisplay()
    }

    Rectangle
    {
        id : rect
        width: 200
        height: 200
        visible: true
        color: "red"
        // anchors.left : root.left
        // anchors.top: root.top
        anchors.left: root.contentItem.left
        anchors.top: root.contentItem.top
        anchors.margins: 20
        // anchors.leftMargin: 20
        // anchors.topMargin: 20
        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                rect.width = rect.width/2;
                rect.height = rect.height/2;
            }

            // onDoubleClicked:
            // {
            //     rect.width = rect.width *2;
            //     rect.height = rect.height *2;
            //     rect.color = "blue";
            // }
        }
    }

    //Registering a type
    // Button{
    //     id : btnReg
    //     anchors.top: root.contentItem.top
    //     anchors.right: root.contentItem.right
    //     anchors.rightMargin: 150
    //     anchors.topMargin: 20
    //     width: 150
    //     height: 50
    //     background: Rectangle
    //     {
    //         color : "Blue"
    //     }
    //     onClicked: myClass.myfun()
    // }


    //QQMLContext
    // Button
    // {
    //     id: btn
    //     width: 75
    //     height: 25
    //     background: Rectangle
    //     {
    //         color : "#2d89d5"
    //     }
    //     anchors.left: root.contentItem.left
    //     anchors.top: rect.bottom
    //     anchors.leftMargin: 145
    //     anchors.topMargin: 20
    //     onClicked: {
    //         classA.myfun();
    //     }
    // }
}




















