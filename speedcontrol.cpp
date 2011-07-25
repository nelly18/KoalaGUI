#include "speedcontrol.h"
#include <QLayout>
#include <QLabel>
#include <QPushButton>
#include <SerialGate.h>
#include <QString>
#include <QMessageBox>
#include <QFont>
#include <QLine>
#include <QGroupBox>

extern SerialGate sg;

const int minrange = -100;
const int maxrange = 100;
const int step = 5;
const int start = 0;
const int diameter = 110;

SpeedControl::SpeedControl(QWidget *parent) : QFrame(parent)
{
    leftMotor = new QDial();
    rightMotor = new QDial();

    leftMotor->setGeometry(100, 100, diameter, diameter);
    rightMotor->setGeometry(200, 100, diameter, diameter);

    leftMotor->setNotchesVisible(true);
    rightMotor->setNotchesVisible(true);

    leftMotor->setRange(minrange, maxrange);
    rightMotor->setRange(minrange, maxrange);

    leftMotor->setPageStep(step);
    rightMotor->setPageStep(step);

    leftMotor->setSliderPosition(start);
    rightMotor->setSliderPosition(start);

    leftMotor->setTracking(false);
    rightMotor->setTracking(false);

    QLabel *leftLabel = new QLabel("Set left motor speed (-100 - 100)");
    leftLabel->setAlignment(Qt::AlignCenter);
    leftLabel->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Maximum);

    QLabel *rightLabel = new QLabel("Set right motor speed (-100 - 100)");
    rightLabel->setAlignment(Qt::AlignCenter);
    rightLabel->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Maximum);

    bSetSpeed  = new QPushButton("Set speed");
    connect(bSetSpeed, SIGNAL(clicked()), this, SLOT(setSpeed()));    

    QGridLayout *speed = new QGridLayout();
    speed->setRowMinimumHeight(0, 110);
    speed->setRowMinimumHeight(1, 110);
    speed->addWidget(leftMotor, 0, 0, Qt::AlignTop);
    speed->addWidget(leftLabel, 0, 0, Qt::AlignBottom);
    speed->addWidget(rightMotor, 1, 0, Qt::AlignTop);
    speed->addWidget(rightLabel, 1, 0, Qt::AlignBottom);
    speed->addWidget(bSetSpeed, 2, 0, 2, 1, Qt::AlignBottom);

    QGroupBox *speedBox = new QGroupBox("Motors speed");
    speedBox->setLayout(speed);

    leftMaxSpeed = new QSlider(Qt::Horizontal);
    leftAcc = new QSlider(Qt::Horizontal);
    rightMaxSpeed = new QSlider(Qt::Horizontal);
    rightAcc = new QSlider(Qt::Horizontal);

    leftMaxSpeed->setTracking(false);
    leftAcc->setTracking(false);
    rightMaxSpeed->setTracking(false);
    rightAcc->setTracking(false);

    leftMaxSpeed->setRange(-100, 100);
    rightMaxSpeed->setRange(-100, 100);

    leftMaxSpeed->setTickPosition(QSlider::TicksAbove);
    leftAcc->setTickPosition(QSlider::TicksAbove);
    rightMaxSpeed->setTickPosition(QSlider::TicksAbove);
    rightAcc->setTickPosition(QSlider::TicksAbove);
    leftMaxSpeed->setTickInterval(20);
    leftAcc->setTickInterval(20);
    rightMaxSpeed->setTickInterval(20);
    rightAcc->setTickInterval(20);

    QGridLayout *tSpeed = new QGridLayout();
    tSpeed->addWidget(new QLabel("Max speed left (-100 - 100)"), 0, 0);
    tSpeed->addWidget(new QLabel("Acc left (0-100)"), 1, 0);
    tSpeed->addWidget(new QLabel("Max speed right(-100 - 100)"), 2, 0);
    tSpeed->addWidget(new QLabel("Acc right (0-100)"), 3, 0);
    tSpeed->addWidget(leftMaxSpeed, 0, 1);
    tSpeed->addWidget(leftAcc, 1, 1);
    tSpeed->addWidget(rightMaxSpeed, 2, 1);
    tSpeed->addWidget(rightAcc, 3, 1);

    bSetTSpeed  = new QPushButton("Set speed");
    connect(bSetTSpeed, SIGNAL(clicked()), this, SLOT(setTSpeed()));
    tSpeed->addWidget(bSetTSpeed, 4, 0, 4, 2, Qt::AlignBottom);

    QGroupBox *tSpeedBox = new QGroupBox("Trapezoidal speed shape");
    tSpeedBox->setLayout(tSpeed);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(1,350);
    layout->addWidget(speedBox, 0, 0);
    layout->addWidget(tSpeedBox, 0, 1);
    setLayout(layout);

}

void SpeedControl::setSpeed()
{
    int leftSpeed = leftMotor->value();
    int rightSpeed = rightMotor->value();

    if (sg.state)
        sg.Send(QString("D,%1,%2\n").arg(leftSpeed).arg(rightSpeed));
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
    }

}

void SpeedControl::setTSpeed()
{
    int leftMaxSpeedValue = leftMaxSpeed->value();
    int leftAccValue = leftAcc->value();
    int rightMaxSpeedValue = rightMaxSpeed->value();
    int rightAccValue = rightAcc->value();

    if (sg.state)
        sg.Send(QString("J,%1,%2,%3,%4\n").arg(leftMaxSpeedValue).arg(leftAccValue).arg(rightMaxSpeedValue).arg(rightAccValue));
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
    }
}
