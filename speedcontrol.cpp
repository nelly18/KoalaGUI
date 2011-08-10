#include <QtCore/QString>

#include <QtGui/QLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#include <QtGui/QFont>
#include <QtGui/QGroupBox>
#include <QtGui/QDial>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

#include "serialgate.h"

#include "speedcontrol.h"

//extern SerialGate serialGate;

const int minrange = -100;
const int maxrange = 100;
const int step = 5;
const int start = 0;
const int diameter = 110;

SpeedControl::SpeedControl(QWidget *parent) : QFrame(parent)
{
    leftMotorDial_ = new QDial();
    rightMotorDial_ = new QDial();

    connect(leftMotorDial_, SIGNAL(valueChanged(int)), this, SLOT(setSpeedLeft(int)));
    connect(rightMotorDial_, SIGNAL(valueChanged(int)), this, SLOT(setSpeedRight(int)));

    leftMotorDial_->setGeometry(100, 100, diameter, diameter);
    rightMotorDial_->setGeometry(200, 100, diameter, diameter);

    leftMotorDial_->setNotchesVisible(true);
    rightMotorDial_->setNotchesVisible(true);

    leftMotorDial_->setRange(minrange, maxrange);
    rightMotorDial_->setRange(minrange, maxrange);

    leftMotorDial_->setPageStep(step);
    rightMotorDial_->setPageStep(step);

    leftMotorDial_->setSliderPosition(start);
    rightMotorDial_->setSliderPosition(start);

    leftMotorDial_->setTracking(true);
    rightMotorDial_->setTracking(true);

    QLabel *leftLabel = new QLabel("Set left motor speed (-100 - 100)");
    leftLabel->setAlignment(Qt::AlignCenter);
    leftLabel->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Maximum);

    QLabel *rightLabel = new QLabel("Set right motor speed (-100 - 100)");
    rightLabel->setAlignment(Qt::AlignCenter);
    rightLabel->setSizePolicy (QSizePolicy::Preferred, QSizePolicy::Maximum);

    QGridLayout *speed = new QGridLayout();
    speed->setRowMinimumHeight(0, 110);
    speed->setRowMinimumHeight(1, 110);
    speed->addWidget(leftMotorDial_, 0, 0, Qt::AlignCenter);
    speed->addWidget(leftLabel, 0, 0, Qt::AlignBottom);
    speed->addWidget(rightMotorDial_, 1, 0, Qt::AlignCenter);
    speed->addWidget(rightLabel, 1, 0, Qt::AlignBottom);

    QGroupBox *speedBox = new QGroupBox("Motors speed");
    speedBox->setLayout(speed);

    leftMaxSpeedSlider_ = new QSlider(Qt::Horizontal);
    leftAccSlider_ = new QSlider(Qt::Horizontal);
    rightMaxSpeedSlider_ = new QSlider(Qt::Horizontal);
    rightAccSlider_ = new QSlider(Qt::Horizontal);

    leftMaxSpeedSlider_->setTracking(false);
    leftAccSlider_->setTracking(false);
    rightMaxSpeedSlider_->setTracking(false);
    rightAccSlider_->setTracking(false);

    leftMaxSpeedSlider_->setRange(-100, 100);
    rightMaxSpeedSlider_->setRange(-100, 100);

    leftMaxSpeedSlider_->setValue(20);
    rightMaxSpeedSlider_->setValue(20);
    leftAccSlider_->setValue(64);
    rightAccSlider_->setValue(64);

    leftMaxSpeedSlider_->setTickPosition(QSlider::TicksAbove);
    leftAccSlider_->setTickPosition(QSlider::TicksAbove);
    rightMaxSpeedSlider_->setTickPosition(QSlider::TicksAbove);
    rightAccSlider_->setTickPosition(QSlider::TicksAbove);
    leftMaxSpeedSlider_->setTickInterval(20);
    leftAccSlider_->setTickInterval(20);
    rightMaxSpeedSlider_->setTickInterval(20);
    rightAccSlider_->setTickInterval(20);

    //QLabel *pic = new QLabel(this);
    //pic->setPixmap(QPixmap(":/res/speed.PNG"));

    QGridLayout *tSpeed = new QGridLayout();
    tSpeed->addWidget(new QLabel("Max speed left (-100 - 100)"), 0, 0);
    tSpeed->addWidget(new QLabel("Acc left (0-100)"), 1, 0);
    tSpeed->addWidget(new QLabel("Max speed right(-100 - 100)"), 2, 0);
    tSpeed->addWidget(new QLabel("Acc right (0-100)"), 3, 0);
    tSpeed->addWidget(leftMaxSpeedSlider_, 0, 1);
    tSpeed->addWidget(leftAccSlider_, 1, 1);
    tSpeed->addWidget(rightMaxSpeedSlider_, 2, 1);
    tSpeed->addWidget(rightAccSlider_, 3, 1);
    //tSpeed->addWidget(pic, 4, 0, 1, 2, Qt::AlignCenter);

    setTrapSpeedButton_  = new QPushButton("Set speed");
    setTrapSpeedButton_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(setTrapSpeedButton_, SIGNAL(clicked()), this, SLOT(setTSpeed()));
    tSpeed->addWidget(setTrapSpeedButton_, 4, 0, 1, 2, Qt::AlignTop|Qt::AlignHCenter);

    QGroupBox *tSpeedBox = new QGroupBox("Trapezoidal speed shape");
    tSpeedBox->setLayout(tSpeed);

    QLabel *l_leftMotor = new QLabel("Left motor PWM (-255 - 255)");
    QLabel *l_rightMotor = new QLabel("Right motor PWM (-255 - 255)");

    leftMotorPwmSlider_ = new QSlider(Qt::Horizontal);
    rightMotorPwmSlider_ = new QSlider(Qt::Horizontal);

    leftMotorPwmSlider_->setTracking(false);
    rightMotorPwmSlider_->setTracking(false);

    leftMotorPwmSlider_->setRange(-255, 255);
    rightMotorPwmSlider_->setRange(-255, 255);

    leftMotorPwmSlider_->setTickPosition(QSlider::TicksAbove);
    rightMotorPwmSlider_->setTickPosition(QSlider::TicksAbove);

    leftMotorPwmSlider_->setTickInterval(40);
    rightMotorPwmSlider_->setTickInterval(40);

    butSetPwmButton_ = new QPushButton("Set configuration");
    butSetPwmButton_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(butSetPwmButton_, SIGNAL(clicked()), this, SLOT(setPWM()));

    QGridLayout *gridPWM = new QGridLayout;
    gridPWM->addWidget(l_leftMotor, 0, 0);
    gridPWM->addWidget(l_rightMotor, 1, 0);
    gridPWM->addWidget(leftMotorPwmSlider_, 0, 1);
    gridPWM->addWidget(rightMotorPwmSlider_, 1, 1);
    gridPWM->addWidget(butSetPwmButton_, 2, 0, 1, 2, Qt::AlignTop|Qt::AlignHCenter);

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
    if (SerialGate::instance()->state) {
        SerialGate::instance()->send(QString("D,%1,%2\n").arg(speed).arg(rightMotorDial_->value()));
    } else {
        QMessageBox::information (this, "", "Open serial port first");
    }
}

void SpeedControl::setSpeedRight(int speed)
{
    if (SerialGate::instance()->state) {
        SerialGate::instance()->send(QString("D,%1,%2\n").arg(leftMotorDial_->value()).arg(speed));
    } else {
        QMessageBox::information (this, "", "Open serial port first");
    }
}

void SpeedControl::setTSpeed()
{
    if (SerialGate::instance()->state) {
        SerialGate::instance()->send(QString("J,%1,%2,%3,%4\n").arg(leftMaxSpeedSlider_->value())
                .arg(leftAccSlider_->value())
                .arg(rightMaxSpeedSlider_->value())
                .arg(rightAccSlider_->value()));
    } else {
        QMessageBox::information (this, "", "Open serial port first");
    }
}

void SpeedControl::setPWM()
{
    if (SerialGate::instance()->state) {
        SerialGate::instance()->send(QString("P,%1,%2\n").arg(leftMotorPwmSlider_->value()).arg(rightMotorPwmSlider_->value()));
    } else {
        QMessageBox::information (this, "", "Open serial port first");
    }
}
