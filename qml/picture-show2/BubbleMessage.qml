import QtQuick 2.0
import my.library 1.0

Item {
    id: bubble_screen_root
    width: 640
    height: 480

    QTimer {
        id: blendoutTimer
        interval: 5000
        onTimeout : fade_bubble_out.start()
    }

    Rectangle {
        id: bubble_screen_content
        color: "#00000000"
        opacity: 0.0
        width: parent.width
        height: parent.height

        Image {
            id: bubble_screen_image
            width: parent.width / 4
            fillMode: Image.PreserveAspectFit
            anchors.bottom: (info_box.isVisible()) ? info_box.info_screen_content.anchors.top : parent.anchors.bottom
            anchors.bottomMargin: height / 6
            anchors.right: parent.right
            anchors.rightMargin:  height / 6
            source: "qrc:///img/bubble.png"
            smooth: true
            opacity: 0.8
        }

        Image {
            id: bubble_screen_imageInfo
            height: bubble_screen_image.height * 0.5
            fillMode: Image.PreserveAspectFit
            anchors.left: bubble_screen_image.left
            anchors.leftMargin: height / 6
            anchors.verticalCenter: bubble_screen_image.verticalCenter
            anchors.verticalCenterOffset: -(bubble_screen_image.height / 6)
            source: "qrc:///img/message_info.png"
            smooth: true
            opacity: 0.4
        }

        Text {
            id: bubble_screen_text
            font.pixelSize: bubble_screen_image.height / 7
            font.family: textFont.name
            horizontalAlignment: Text.AlignHCenter
            color: "#FFFFFF"
            wrapMode: Text.Wrap
            anchors.right: bubble_screen_image.right
            anchors.rightMargin: bubble_screen_image.height / 6
            anchors.left: bubble_screen_imageInfo.right
            anchors.leftMargin: bubble_screen_image.height / 20
            anchors.verticalCenter: bubble_screen_image.verticalCenter
            anchors.verticalCenterOffset: -(bubble_screen_image.height / 6)
            smooth: true;
            opacity: 0.8
            text: ""
        }
    }

    function show_hide_bubble(text, timeout) {
        if (bubble_screen_content.opacity === 0.0)
            bubble_screen_content.opacity = 0.01

        // show
        if (text !== "") {
            bubble_screen_text.text = text
            blendoutTimer.interval = timeout
            blendoutTimer.stop()
            fade_bubble_out.stop()
            fade_bubble.start()
        }
        // hide
        else {
            blendoutTimer.stop()
            if (bubble_screen_content.opacity === 0.0)
                return
            fade_bubble.stop()
            fade_bubble_out.start()
        }
    }

    ParallelAnimation {
        id: fade_bubble
        running: false

        onRunningChanged: {
            if (!fade_bubble.running) {
                blendoutTimer.start()
            }
        }

        NumberAnimation { target: bubble_screen_content; properties: "opacity"; to: 1.0; duration: 500; easing.type: Easing.InOutQuad }
    }

    ParallelAnimation {
        id: fade_bubble_out
        running: false

        NumberAnimation { target: bubble_screen_content; properties: "opacity"; to: 0.0; duration: 500; easing.type: Easing.InOutQuad }
    }



}
