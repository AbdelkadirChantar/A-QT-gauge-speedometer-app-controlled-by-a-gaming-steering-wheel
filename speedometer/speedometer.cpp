#include "speedometer.h"
#include <QPainter>


Speedometer::Speedometer(QQuickItem *parent)
    :QQuickPaintedItem(parent),
    m_SpeedometerSize(500), // touch screen is 800 x 480
    m_StartAngle(50),
    m_AlignAngle(260), // it should be 360 - m_StartAngle*3 for good looking
    m_LowestRange(0),
    m_HighestRange(10400),
    m_Speed(2430),
    m_ArcWidth(10),
    m_OuterColor(QColor(12,16,247)),
    m_InnerColor(QColor(51,88,255,80)),
    m_TextColor(QColor(255,255,255)),
    m_BackgroundColor(Qt::transparent)
{

}

void Speedometer::paint(QPainter *painter)
{
    QRectF rect = this->boundingRect();
    painter->setRenderHint(QPainter::Antialiasing);
    QPen pen = painter->pen();
    pen.setCapStyle(Qt::FlatCap);

    double startAngle;
    double spanAngle;

    startAngle = m_StartAngle - 40;
    spanAngle = 0 - m_AlignAngle;

    //all arc
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_InnerColor);
    painter->setPen(pen);
   // painter->drawRect(rect);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, spanAngle * 16);
    painter->restore();

    //inner pie
    int ellipsedSize = m_SpeedometerSize/5;
    painter->save();
    pen.setWidth(m_ArcWidth/4);
    pen.setColor(m_OuterColor);
    painter->setBrush(m_InnerColor);
    painter->setPen(pen);
    painter->drawEllipse(QPointF(250,210), 114, 94);
    //painter->drawPie(rect.adjusted(pieSize, pieSize, -pieSize, -pieSize), startAngle * 16, spanAngle * 16);
    painter->restore();

    //text which shows the value
    painter->save();
    QFont font("Halvetica",24);
    painter->setFont(font);
    pen.setColor(m_TextColor);
    painter->setPen(pen);
    painter->drawText(rect.adjusted(m_SpeedometerSize/30, m_SpeedometerSize/30, -m_SpeedometerSize/30, -m_SpeedometerSize/3), Qt::AlignCenter  ,QString::number((int(m_Speed/40)),'f',1));
    painter->drawText(rect.adjusted(m_SpeedometerSize/30, m_SpeedometerSize/30, -m_SpeedometerSize/30, -m_SpeedometerSize/8), Qt::AlignCenter  ,tr("km/h"));
    painter->drawText(rect.adjusted(0,220 ,-350,0), Qt::AlignCenter  ,tr("0"));
    painter->drawText(rect.adjusted(0,60 ,-400,0), Qt::AlignCenter  ,tr("20"));
    painter->drawText(rect.adjusted(0,0 ,-400,-90), Qt::AlignCenter  ,tr("40"));
    painter->drawText(rect.adjusted(0,0 ,-320,-250), Qt::AlignCenter  ,tr("60"));
    painter->drawText(rect.adjusted(0,0 ,-200,-350), Qt::AlignCenter  ,tr("80"));
    painter->drawText(rect.adjusted(0,0 ,0,-400), Qt::AlignCenter  ,tr("120"));

    painter->drawText(rect.adjusted(190,0 ,0,-350), Qt::AlignCenter  ,tr("140"));
    painter->drawText(rect.adjusted(290,0 ,0,-250), Qt::AlignCenter  ,tr("180"));
    painter->drawText(rect.adjusted(370, 0,0,-90), Qt::AlignCenter  ,tr("200"));
    painter->drawText(rect.adjusted(380,60 ,0,0), Qt::AlignCenter  ,tr("220"));
    painter->drawText(rect.adjusted(320,220 ,0,0), Qt::AlignCenter  ,tr("260"));

    painter->restore();




    //current active progress
    painter->save();
    pen.setWidth(m_ArcWidth);
    pen.setColor(m_OuterColor);
    qreal valueToAngle = ((m_Speed - m_LowestRange)/(m_HighestRange - m_LowestRange)) * spanAngle;
    painter->setPen(pen);
    painter->drawArc(rect.adjusted(m_ArcWidth, m_ArcWidth, -m_ArcWidth, -m_ArcWidth), startAngle * 16, valueToAngle * 16);
    painter->restore();

}

qreal Speedometer::getSpeedometerSize()
{
    return m_SpeedometerSize;
}

qreal Speedometer::getStartAngle()
{
    return m_StartAngle;
}


qreal Speedometer::getAlignAngle()
{
    return m_AlignAngle;
}


qreal Speedometer::getLowestRange()
{
    return m_LowestRange;
}

qreal Speedometer::getHighestRange()
{
    return m_HighestRange;
}

qreal Speedometer::getSpeed()
{
    return m_Speed;
}

int Speedometer::getArcWidth()
{
    return m_ArcWidth;
}

QColor Speedometer::getOuterColor()
{
    return m_OuterColor;
}

QColor Speedometer::getInnerColor()
{
    return m_InnerColor;
}

QColor Speedometer::getTextColor()
{
    return m_TextColor;
}

QColor Speedometer::getBackgroundColor()
{
    return m_BackgroundColor;
}


void Speedometer::setSpeedometerSize(qreal size)
{
    if(m_SpeedometerSize == size)
        return;

    m_SpeedometerSize = size;
    emit speedometerSizeChanged();
}

void Speedometer::setStartAngle(qreal startAngle)
{
    if(m_StartAngle == startAngle)
        return;

    m_StartAngle = startAngle;

    emit startAngleChanged();
}

void Speedometer::setAlignAngle(qreal angle)
{
    if(m_StartAngle == angle)
        return;

    m_StartAngle = angle;

    emit alignAngleChanged();
}

void Speedometer::setLowestRange(qreal lowestRange)
{
    if(m_LowestRange == lowestRange)
        return;

    m_LowestRange = lowestRange;

    emit lowestRangeChanged();
}

void Speedometer::setHighestRange(qreal highestRange)
{
    if(m_HighestRange == highestRange)
        return;

    m_HighestRange = highestRange;

    emit highestRangeChanged();
}

void Speedometer::setSpeed(qreal speed)
{
    if(m_Speed == speed)
        return;

    m_Speed = speed;
    update();
    emit speedChanged();
}

void Speedometer::setArcWidth(int arcWidth)
{
    if(m_ArcWidth == arcWidth)
        return;

    m_ArcWidth = arcWidth;

    emit arcWidthChanged();
}

void Speedometer::setOuterColor(QColor outerColor)
{
    if(m_OuterColor == outerColor)
        return;

    m_OuterColor = outerColor;

    emit outerColorChanged();
}

void Speedometer::setInnerColor(QColor innerColor)
{
    if(m_InnerColor == innerColor)
        return;

    m_InnerColor = innerColor;

    emit innerColorChanged();
}

void Speedometer::setTextColor(QColor textColor)
{
    if(m_TextColor == textColor)
        return;

    m_TextColor = textColor;

    emit textColorChanged();
}

void Speedometer::setBackgroundColor(QColor backgroundColor)
{
    if(m_BackgroundColor == backgroundColor)
        return;

    m_BackgroundColor = backgroundColor;

    emit backgroundColorChanged();
}
