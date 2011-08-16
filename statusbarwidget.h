#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QtGui/QWidget>

class BatteryCharge;
class QStatusBar;
class QLabel;

class StatusBarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit StatusBarWidget (QWidget *parent = 0);

public:
    BatteryCharge *chargeBattery_;
    QStatusBar *statusBar;

private:
    QLabel *batteryVoltageLabel_;
    QLabel *consumptionLabel_;
    QLabel *ambientTempLabel_;
    QLabel *batteryTempLabel_;
};

#endif // STATUSBARWIDGET_H
