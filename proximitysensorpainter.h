#ifndef PROXIMITYSENSORPAINTER_H
#define PROXIMITYSENSORPAINTER_H

#include <QtCore/QVector>

#include <QtGui/QLabel>

#include "defines.h"

class Sensor;
class QTableWidget;

class ProximitySensorPainter : public QLabel
{
    Q_OBJECT

public:
    ProximitySensorPainter(QWidget *parent = 0) ;
    ~ProximitySensorPainter();

    void setColorPalette(int palette);
    void resetSensorsColor();

private:
    int loadSensorsValues();

private slots:
    void proximitySensorTimeOut(void);

public:
    QVector <Sensor *> sensors_;
    QTimer *drawSensorsTimer_;

private:
    int colorPalette_;
    QTableWidget *table_;
};
#endif // PROXIMITYSENSORPAINTER_H

