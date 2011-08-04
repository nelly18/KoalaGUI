#ifndef SPEEDCONTROL_H
#define SPEEDCONTROL_H

#include <QFrame>
#include <QDial>
#include <QPushButton>
#include <QSlider>

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
