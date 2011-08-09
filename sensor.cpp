#include "sensor.h"
#include <QString>
#include <QStyle>
extern SerialGate sg;
#include <QDebug>
Sensor::Sensor(int sensor, QWidget *parent) : QWidget(parent)
{
    sensorNumber = sensor;
    color.setRgb(220, 220, 220);
    sensorValue = 0;
}

void Sensor::setSensorValue(const int val)
{
    sensorValue = val;
}

int Sensor::getSensorValue()
{
    return sensorValue;
}

void Sensor::setColor(QColor c)
{
    color = c;
}

QColor Sensor::getColor()
{
    return color;
}

void Sensor::evaluateColor(const int palette)
{
    int iColor = 0;
    Palettes pal = Palettes(palette);

    switch (pal)
    {
      case blueRed:
        if (sensorValue < 512)
        {
            iColor = sensorValue * colorparam;
            color.setRgb(iColor, iColor, 255);
        }
        else
        {
            iColor = abs(sensorValue * colorparam - 510);
            color.setRgb(255, iColor, iColor);
        }
        break;

      case blackWhite:
        iColor = sensorValue * colorparam2;
        color.setRgb(iColor, iColor, iColor);
        break;
    }
}

void Sensor::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    QPen pen(Qt::NoPen);
    painter.setPen(pen);
    QBrush brush(Qt::SolidPattern);
    painter.setRenderHint(QPainter::Antialiasing);

        brush.setColor(color);
        painter.setBrush(brush);
        painter.drawEllipse(0, 0, width (), height ());
}

void Sensor::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED (event);
    setGeometry(x(), y(), qMin(width(), height()), qMin(width(), height()));
}
