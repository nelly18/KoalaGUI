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
    explicit Sensor(int sensor, QWidget *parent = 0);

    void setSensorValue(const int val);
    int getSensorValue();
    void evaluateColor(const int palette);
    QColor getColor();
    void setColor(QColor c);

    void paintEvent(QPaintEvent *);

    enum Palettes {blueRed, blackWhite} ;

 protected:
    virtual void resizeEvent ( QResizeEvent * event );

 private:
    int sensorNumber; //0-7 - left sensors; 8-15 - right sensors
    int sensorValue;
    QColor color;
};

#endif // SENSOR_H
