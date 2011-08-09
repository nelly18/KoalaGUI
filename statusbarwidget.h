#ifndef STATUSBARWIDGET_H
#define STATUSBARWIDGET_H

#include <QtGui/QFrame>
#include <QtGui/QLabel>
#include <QtGui/QStatusBar>

#include "batterycharge.h"

class StatusBarWidget : public QWidget//QStatusBar//QFrame
{
    Q_OBJECT

public:
    explicit StatusBarWidget(QWidget *parent = 0);
    BatteryCharge *charge;
    QStatusBar *statusBar;
private:
    QLabel *batteryVoltage;
    QLabel *consumption;
    QLabel *ambientTemp;
    QLabel *batteryTemp;

signals:

public slots:

};

#endif // STATUSBARWIDGET_H
