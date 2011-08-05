#ifndef BATTERYCHARGE_H
#define BATTERYCHARGE_H

#include <QProgressBar>
#include <QTimer>

class BatteryCharge : public QProgressBar
{
    Q_OBJECT
public:
    BatteryCharge(QWidget *parent = 0);
    QTimer *batteryChargeTimer;
private:

private slots:
    void batteryChargeTimerTimeOut();
};

#endif // BATTERYCHARGE_H
