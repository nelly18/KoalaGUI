#ifndef BATTERYCHARGE_H
#define BATTERYCHARGE_H

#include <QtGui/QProgressBar>

class QTimer;

class BatteryCharge : public QProgressBar
{
    Q_OBJECT
public:
    BatteryCharge(QWidget *parent = 0);
    QTimer *batteryChargeTimer;
private slots:
    void batteryChargeTimerTimeOut();
};

#endif // BATTERYCHARGE_H
