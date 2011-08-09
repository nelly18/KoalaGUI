#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include <QtGui/QFrame>
#include <QtGui/QDial>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

class SpeedControl : public QFrame
{
    Q_OBJECT

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

public:
    SpeedControl(QWidget *parent = 0);
protected:

private:

signals:

private slots:
    void setSpeedLeft(int);
    void setSpeedRight(int);
    void setTSpeed();
    void setPWM();
};

#endif // SPEEDCONTROL_H
