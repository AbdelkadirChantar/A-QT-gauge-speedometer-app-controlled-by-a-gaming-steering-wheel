import QtQuick 2.15
import QtQuick.Window 2.15
import com.ulasdikme.speedometer 1.0
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.1
Window {
    visible: true
    width: 2800
    height: 2000
    title: qsTr("Hello World")
    color:"#000000"
    Speedometer
    {
        objectName: "speedoMeter"
        anchors.horizontalCenter:  parent.horizontalCenter
        width: speedometerSize
        height: speedometerSize
        startAngle: startAngle
        alignAngle: alignAngle
        lowestRange: lowestRange
        highestRange: highestRange
        speed: speed
        arcWidth: arcWidth
        outerColor: outerColor
        innerColor: innerColor
        textColor: textColor
        backgroundColor: backgroundColor
    }


}
