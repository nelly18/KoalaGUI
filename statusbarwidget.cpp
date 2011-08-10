#include <QtGui/QLayout>
#include <QtGui/QStatusBar>
#include <QtGui/QLabel>

#include "batterycharge.h"

#include "statusbarwidget.h"

StatusBarWidget::StatusBarWidget(QWidget *parent) : QWidget(parent)
{
    statusBar = new QStatusBar(this);
    statusBar->setStyleSheet("QStatusBar {"
                  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                  "stop: 0 #eee, stop: 0.4999 #ddd, stop: 0.5 #ccc, stop: 1 #ddd);"
                  "border-top: 1px ridge gray;"
                  "padding - left: 10px"
                  "}"

                  "QStatusBar::item {"
                  "border-width: 0px;"
                  "border-left: 1px ridge gray;"
                  "}");


     chargeBattery_ = new BatteryCharge(this);
     chargeBattery_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

     batteryVoltageLabel_ = new QLabel("0", this);
     consumptionLabel_ = new QLabel("0", this);
     ambientTempLabel_ = new QLabel("0", this);
     batteryTempLabel_ = new QLabel("0", this);


     QHBoxLayout *layout = new QHBoxLayout;
     layout->addWidget(new QLabel("Battery charge level:"));
     layout->addWidget(chargeBattery_);
     layout->setMargin(1);
     layout->setSpacing(10);
     QFrame *fr_BatteryCharge = new QFrame(this);
     fr_BatteryCharge->setLayout(layout);

     QHBoxLayout *layout2 = new QHBoxLayout;
     layout2->addWidget(new QLabel("Battery voltage:", this));
     layout2->addWidget(batteryVoltageLabel_);
     layout2->setMargin(0);
     layout2->setSpacing(10);
     QFrame *fr_batVolt = new QFrame(this);
     fr_batVolt->setLayout(layout2);

     QHBoxLayout *layout3 = new QHBoxLayout;
     layout3->addWidget(new QLabel("Consumption:", this));
     layout3->addWidget(consumptionLabel_);
     layout3->setMargin(0);
     layout3->setSpacing(10);
     QFrame *fr_cons = new QFrame(this);
     fr_cons->setLayout(layout3);

     QHBoxLayout *layout4 = new QHBoxLayout;
     layout4->addWidget(new QLabel("Ambient temperature:", this));
     layout4->addWidget(ambientTempLabel_);
     layout4->setMargin(0);
     layout4->setSpacing(10);
     QFrame *fr_amb = new QFrame;
     fr_amb->setLayout(layout4);

     QHBoxLayout *layout5 = new QHBoxLayout;
     layout5->addWidget(new QLabel("Battery temperature:", this));
     layout5->addWidget(batteryTempLabel_);
     layout5->setMargin(0);
     layout5->setSpacing(10);
     QFrame *fr_bat = new QFrame;
     fr_bat->setLayout(layout5);

     statusBar->addPermanentWidget(fr_batVolt);
     statusBar->addPermanentWidget(fr_cons);
     statusBar->addPermanentWidget(fr_amb);
     statusBar->addPermanentWidget(fr_bat);
     statusBar->addPermanentWidget(fr_BatteryCharge);
}
