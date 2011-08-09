#include <QtCore/QString>
#include <QtCore/QDebug>

#include <QtGui/QPainter>

#include "serialgate.h"

#include "sensor.h"

extern SerialGate sg;

Sensor::Sensor(int sensor, QWidget *parent) : QWidget(parent)
{
    color_.setRgb(220, 220, 220);
    sensorValue_ = 0;
}

void Sensor::setSensorValue(const int val)
{
    sensorValue_ = val;
}

int Sensor::sensorValue()
{
    return sensorValue_;
}

void Sensor::setColor(QColor c)
{
    color_ = c;
}

QColor Sensor::color()
{
    return color_;
}

void Sensor::evaluateColor(const int palette)
{
    int iColor = 0;
    Palettes pal = Palettes(palette);

    switch (pal)
    {
      case blueRed:
        if (sensorValue_ < 512)
        {
            iColor = sensorValue_ * colorParam;
            color_.setRgb(iColor, iColor, 255);
        }
        else
        {
            iColor = abs(sensorValue_ * colorParam - 510);
            color_.setRgb(255, iColor, iColor);
        }
        break;

      case blackWhite:
        iColor = sensorValue_ * colorParam2;
        color_.setRgb(iColor, iColor, iColor);
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

        brush.setColor(color_);
        painter.setBrush(brush);
        painter.drawEllipse(0, 0, width (), height ());
}

void Sensor::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED (event);
    setGeometry(x(), y(), qMin(width(), height()), qMin(width(), height()));
}
