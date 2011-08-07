#include "statusbarwidget.h"
#include <QLayout>

StatusBarWidget::StatusBarWidget(QWidget *parent) :
    QStatusBar(parent)
{
    setStyleSheet("QStatusBar {"
//                  "background-color: #b8b8b8;"
                  "border-top: 1px ridge gray;"
                  "}"

                  "QStatusBar::item {"
//                "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
//                "stop: 0 #D8D8D8, stop: 0.4999 #E0E0E0 , stop: 0.5 #E8E8E8, stop: 1 #E0E0E0);"
                  "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                  "stop: 0 #E0E0E0, stop: 1 #EEEEEE);"
                  "border: 0px;"
                  "border-radius: 5px;"
                  "border: 1px solid gray;"
                  "margin: 0px;"
                  "padding: 3px"
                  "}");


     charge = new BatteryCharge(this);
     charge->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

     batteryVoltage = new QLabel("        ", this);
     batteryVoltage->setFrameStyle(QFrame::Panel | QFrame::Sunken);
     consumption = new QLabel("        ", this);
     consumption->setFrameStyle(QFrame::Panel | QFrame::Sunken);
     ambientTemp = new QLabel("        ", this);
     ambientTemp->setFrameStyle(QFrame::Panel | QFrame::Sunken);
     batteryTemp = new QLabel("        ", this);
     batteryTemp->setFrameStyle(QFrame::Panel | QFrame::Sunken);

     QHBoxLayout *layout = new QHBoxLayout;
     layout->addWidget(new QLabel("Battery charge level:"));
     layout->addWidget(charge);
     QFrame *fr_BatteryCharge = new QFrame(this);
     fr_BatteryCharge->setLayout(layout);

     QHBoxLayout *layout2 = new QHBoxLayout;
     layout2->addWidget(new QLabel("Battery voltage:", this));
     layout2->addWidget(batteryVoltage);
     QFrame *fr_batVolt = new QFrame(this);
     fr_batVolt->setLayout(layout2);

     QHBoxLayout *layout3 = new QHBoxLayout;
     layout3->addWidget(new QLabel("Consumption:", this));
     layout3->addWidget(consumption);
     QFrame *fr_cons = new QFrame(this);
     fr_cons->setLayout(layout3);

     QHBoxLayout *layout4 = new QHBoxLayout;
     layout4->addWidget(new QLabel("Ambient temperature:", this));
     layout4->addWidget(ambientTemp);
     QFrame *fr_amb = new QFrame;
     fr_amb->setLayout(layout4);

     QHBoxLayout *layout5 = new QHBoxLayout;
     layout5->addWidget(new QLabel("Battery temperature:", this));
     layout5->addWidget(batteryTemp);
     QFrame *fr_bat = new QFrame;
     fr_bat->setLayout(layout5);

     addPermanentWidget(fr_batVolt);
     addPermanentWidget(fr_cons);
     addPermanentWidget(fr_amb);
     addPermanentWidget(fr_bat);
     addPermanentWidget(fr_BatteryCharge);
}
