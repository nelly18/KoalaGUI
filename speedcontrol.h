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

private slots:
    void setSpeedLeft(int);
    void setSpeedRight(int);
    void setTSpeed();
    void setPWM();

private:
    QDial *leftMotorDial_;
    QDial *rightMotorDial_;
    QPushButton *setTrapSpeedButton_;
    QSlider *leftMaxSpeedSlider_;
    QSlider *leftAccSlider_;
    QSlider *rightMaxSpeedSlider_;
    QSlider *rightAccSlider_;
    QSlider *leftMotorPwmSlider_;
    QSlider *rightMotorPwmSlider_;
    QPushButton *butSetPwmButton_;
};

#endif // SPEEDCONTROL_H
