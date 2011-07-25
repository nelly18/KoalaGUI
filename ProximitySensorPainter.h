#ifndef PROXIMITYSENSORPAINTER_H
#define PROXIMITYSENSORPAINTER_H
#include <QFrame>
#include "Sensor.h"
#include "defines.h"
#include <QLabel>
#include <QVector>
#include <QTableWidget>


class ProximitySensorPainter : public QLabel
{
    Q_OBJECT

    QVector <Sensor *> sensors;
    int getSensorsValues();
    int colorPalette;
    QTableWidget *table;

public:
    ProximitySensorPainter(QWidget *parent = 0) ;
    ~ProximitySensorPainter();
    QTimer *drawSensorsTimer;
    void setColorPalette(int palette);

protected:
    //void paintEvent(QPaintEvent *);
private slots:

    void TimeOut(void);
};
#endif // PROXIMITYSENSORPAINTER_H

