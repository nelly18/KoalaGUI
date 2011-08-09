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
    explicit StatusBarWidget(QWidget *parent = 0);

public:
    BatteryCharge *charge;
    QStatusBar *statusBar;

private:
    QLabel *batteryVoltage;
    QLabel *consumption;
    QLabel *ambientTemp;
    QLabel *batteryTemp;
};

#endif // STATUSBARWIDGET_H
