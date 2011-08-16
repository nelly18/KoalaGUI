#ifndef SENSOR_H
#define SENSOR_H

#include <QtGui/QWidget>
#include <QtGui/QColor>

#include "defines.h"

class Sensor : public QWidget
{
    Q_OBJECT

public:
    enum Palettes {blueRed, blackWhite};

public:
    explicit Sensor (int sensor, QWidget *parent = 0);

    void setSensorValue (const int val);
    int sensorValue();
    void setColor (QColor c);
    QColor color();
    void evaluateColor (const int palette);

protected:
    void paintEvent (QPaintEvent *);
    virtual void resizeEvent (QResizeEvent *event);

private:
    int sensorValue_;
    QColor color_;
};

#endif // SENSOR_H
