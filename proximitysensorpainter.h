#ifndef PROXIMITYSENSORPAINTER_H
#define PROXIMITYSENSORPAINTER_H

#include <QtCore/QVector>

#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QTableWidget>

#include "sensor.h"
#include "defines.h"


class ProximitySensorPainter : public QLabel
{
    Q_OBJECT

    int getSensorsValues();
    int colorPalette;
    QTableWidget *table;

public:
    ProximitySensorPainter(QWidget *parent = 0) ;
    ~ProximitySensorPainter();
    QVector <Sensor *> sensors;
    QTimer *drawSensorsTimer;
    void setColorPalette(int palette);
    void resetSensorsColor();
private slots:

    void TimeOut(void);
};
#endif // PROXIMITYSENSORPAINTER_H

