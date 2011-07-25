#ifndef SENSOR_H
#define SENSOR_H
#include "defines.h"

#include <SerialGate.h>
#include <QColor>
#include <QPoint>
#include <QPainter>
#include <QFrame>


class Sensor : public QWidget
{
    Q_OBJECT

 public:
    explicit Sensor(const int &sensor, const QPoint &c, const int &r, QWidget *parent = 0);

    void setSensorValue(const int val);
    int getSensorValue();
    void evaluateColor(const int palette);
    QPoint getCenter();
    int getRadii();
    QColor getColor();

    void paintEvent(QPaintEvent *);

    enum Palettes {blueRed, blackWhite} ;
 private:
    int sensorNumber; //0-7 - left sensors; 8-15 - right sensors
    int sensorValue;
    QColor color;
    QPoint center;
    int radii;


};

#endif // SENSOR_H
