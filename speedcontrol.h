#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include <QtGui/QFrame>

class QDial;
class QPushButton;
class QSlider;

class SpeedControl : public QFrame
{
    Q_OBJECT
public:
    SpeedControl(QWidget *parent = 0);

private:
    QDial *leftMotor;
    QDial *rightMotor;
    QPushButton *bSetTSpeed;
    QSlider *leftMaxSpeed;
    QSlider *leftAcc;
    QSlider *rightMaxSpeed;
    QSlider *rightAcc;
    QSlider *leftMotorPWM;
    QSlider *rightMotorPWM;
    QPushButton *butSetPWM;

private slots:
    void setSpeedLeft(int);
    void setSpeedRight(int);
    void setTSpeed();
    void setPWM();
};

#endif // SPEEDCONTROL_H
