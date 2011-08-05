#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QFrame>
#include <QLabel>
#include "batterycharge.h"

class StatusBarWidget : public QFrame
{
    Q_OBJECT

public:
    explicit StatusBarWidget(QWidget *parent = 0);
    BatteryCharge *charge;

private:
    QLabel *batteryVoltage;
    QLabel *consumption;
    QLabel *ambientTemp;
    QLabel *batteryTemp;

signals:

public slots:

};

#endif // STATUSBARWIDGET_H
