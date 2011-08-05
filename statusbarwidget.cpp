#include "statusbarwidget.h"
#include <QLayout>

StatusBarWidget::StatusBarWidget(QWidget *parent) :
    QFrame(parent)
{
    setFrameShape(QFrame::NoFrame);

    charge = new BatteryCharge;
    charge->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

    batteryVoltage = new QLabel("    ");
    consumption = new QLabel("    ");
    ambientTemp = new QLabel("    ");
    batteryTemp = new QLabel("    ");



    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(new QLabel("Battery charge level:"));
    layout->addWidget(charge);
    layout->addWidget(new QLabel("Battery voltage:"));
    layout->addWidget(batteryVoltage);
    layout->addWidget(new QLabel("Counsumption:"));
    layout->addWidget(consumption);
    layout->addWidget(new QLabel("Ambient temperature:"));
    layout->addWidget(ambientTemp);
    layout->addWidget(new QLabel("Battery tmperature:"));
    layout->addWidget(batteryTemp);
    layout->addSpacerItem(new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Fixed));
    setLayout(layout);
}
