#ifndef BATTERYCHARGE_H
#define BATTERYCHARGE_H

#include <QtGui/QProgressBar>

class QTimer;

class BatteryCharge : public QProgressBar
{
    Q_OBJECT

public:
    BatteryCharge(QWidget *parent = 0);

private slots:
    void batteryChargeTimerTimeOut();

public:
    QTimer *batteryChargeTimer;
};

#endif // BATTERYCHARGE_H
