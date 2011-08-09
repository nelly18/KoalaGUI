#include <QtCore/QString>

#include <QtGui/QLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#include <QtGui/QFont>
#include <QtGui/QGroupBox>

#include "speedcontrol.h"
#include "serialgate.h"

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

    connect(leftMotor, SIGNAL(valueChanged(int)), this, SLOT(setSpeedLeft(int)));
    connect(rightMotor, SIGNAL(valueChanged(int)), this, SLOT(setSpeedRight(int)));

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

    leftMotor->setTracking(true);
    rightMotor->setTracking(true);

    QLabel *leftLabel = new QLabel("Set left motor speed (-100 - 100)");
    leftLabel->setAlignment(Qt::AlignCenter);
    leftLabel->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Maximum);

    QLabel *rightLabel = new QLabel("Set right motor speed (-100 - 100)");
    rightLabel->setAlignment(Qt::AlignCenter);
    rightLabel->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Maximum);

    QGridLayout *speed = new QGridLayout();
    speed->setRowMinimumHeight(0, 110);
    speed->setRowMinimumHeight(1, 110);
    speed->addWidget(leftMotor, 0, 0, Qt::AlignCenter);
    speed->addWidget(leftLabel, 0, 0, Qt::AlignBottom);
    speed->addWidget(rightMotor, 1, 0, Qt::AlignCenter);
    speed->addWidget(rightLabel, 1, 0, Qt::AlignBottom);

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

    leftMaxSpeed->setValue(20);
    rightMaxSpeed->setValue(20);
    leftAcc->setValue(64);
    rightAcc->setValue(64);

    leftMaxSpeed->setTickPosition(QSlider::TicksAbove);
    leftAcc->setTickPosition(QSlider::TicksAbove);
    rightMaxSpeed->setTickPosition(QSlider::TicksAbove);
    rightAcc->setTickPosition(QSlider::TicksAbove);
    leftMaxSpeed->setTickInterval(20);
    leftAcc->setTickInterval(20);
    rightMaxSpeed->setTickInterval(20);
    rightAcc->setTickInterval(20);

    //QLabel *pic = new QLabel(this);
    //pic->setPixmap(QPixmap(":/res/speed.PNG"));

    QGridLayout *tSpeed = new QGridLayout();
    tSpeed->addWidget(new QLabel("Max speed left (-100 - 100)"), 0, 0);
    tSpeed->addWidget(new QLabel("Acc left (0-100)"), 1, 0);
    tSpeed->addWidget(new QLabel("Max speed right(-100 - 100)"), 2, 0);
    tSpeed->addWidget(new QLabel("Acc right (0-100)"), 3, 0);
    tSpeed->addWidget(leftMaxSpeed, 0, 1);
    tSpeed->addWidget(leftAcc, 1, 1);
    tSpeed->addWidget(rightMaxSpeed, 2, 1);
    tSpeed->addWidget(rightAcc, 3, 1);
    //tSpeed->addWidget(pic, 4, 0, 1, 2, Qt::AlignCenter);

    bSetTSpeed  = new QPushButton("Set speed");
    bSetTSpeed->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(bSetTSpeed, SIGNAL(clicked()), this, SLOT(setTSpeed()));
    tSpeed->addWidget(bSetTSpeed, 4, 0, 1, 2, Qt::AlignTop|Qt::AlignHCenter);

    QGroupBox *tSpeedBox = new QGroupBox("Trapezoidal speed shape");
    tSpeedBox->setLayout(tSpeed);

    QLabel *l_leftMotor = new QLabel("Left motor PWM (-255 - 255)");
    QLabel *l_rightMotor = new QLabel("Right motor PWM (-255 - 255)");

    leftMotorPWM = new QSlider(Qt::Horizontal);
    rightMotorPWM = new QSlider(Qt::Horizontal);

    leftMotorPWM->setTracking(false);
    rightMotorPWM->setTracking(false);

    leftMotorPWM->setRange(-255, 255);
    rightMotorPWM->setRange(-255, 255);

    leftMotorPWM->setTickPosition(QSlider::TicksAbove);
    rightMotorPWM->setTickPosition(QSlider::TicksAbove);

    leftMotorPWM->setTickInterval(40);
    rightMotorPWM->setTickInterval(40);

    butSetPWM = new QPushButton("Set configuration");
    butSetPWM->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(butSetPWM, SIGNAL(clicked()), this, SLOT(setPWM()));

    QGridLayout *gridPWM = new QGridLayout;
    gridPWM->addWidget(l_leftMotor, 0, 0);
    gridPWM->addWidget(l_rightMotor, 1, 0);
    gridPWM->addWidget(leftMotorPWM, 0, 1);
    gridPWM->addWidget(rightMotorPWM, 1, 1);
    gridPWM->addWidget(butSetPWM, 2, 0, 1, 2, Qt::AlignTop|Qt::AlignHCenter);

    QGroupBox *groupPWM = new QGroupBox("PWM configuration");
    //groupPWM->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    groupPWM->setLayout(gridPWM);

    QGridLayout *layout = new QGridLayout;
    layout->setColumnMinimumWidth(1,350);
    layout->addWidget(speedBox, 0, 0, 2, 1);
    layout->addWidget(tSpeedBox, 0, 1);
    layout->addWidget(groupPWM, 1, 1);
    setLayout(layout);

}

void SpeedControl::setSpeedLeft(int speed)
{
    int rightSpeed = rightMotor->value();

    if (sg.state)
        sg.Send(QString("D,%1,%2\n").arg(speed).arg(rightSpeed));
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
    }
}

void SpeedControl::setSpeedRight(int speed)
{
    int leftSpeed = leftMotor->value();

    if (sg.state)
        sg.Send(QString("D,%1,%2\n").arg(leftSpeed).arg(speed));
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

void SpeedControl::setPWM()
{
    int leftMotorPWMValue = leftMotorPWM->value();
    int rightMotorPWMValue = rightMotorPWM->value();

    if (sg.state)
        sg.Send(QString("P,%1,%2\n").arg(leftMotorPWMValue).arg(rightMotorPWMValue));
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
    }
}
