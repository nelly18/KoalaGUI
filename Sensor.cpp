#include <Sensor.h>
#include <QString>
#include <QStyle>
extern SerialGate sg;
#include <QDebug>
Sensor::Sensor(const int &sensor, const QPoint &c, const int &r, QWidget *parent) : QWidget(parent)
{
	sensorNumber = sensor;
	center = c;
	radii = r;
	//color.setRgb(220, 220, 220);
	color = Qt::red;
	sensorValue = 0;
}

void Sensor::setSensorValue(const int val)
{
	sensorValue = val;
}

QPoint Sensor::getCenter()
{
	return center;
}

int Sensor::getRadii()
{
	return radii;
}

int Sensor::getSensorValue()
{
	return sensorValue;
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

		brush.setColor(color);
		painter.setBrush(brush);
		painter.drawEllipse(0, 0, width (), height ());
		static int i = 1;
		qDebug() << size ();
		i++;
}
