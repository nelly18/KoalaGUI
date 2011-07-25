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
    QPushButton *bSetSpeed;
    QPushButton *bSetTSpeed;

    QSlider *leftMaxSpeed;
    QSlider *leftAcc;
    QSlider *rightMaxSpeed;
    QSlider *rightAcc;
public:
    SpeedControl(QWidget *parent = 0);
protected:

private:

signals:

private slots:
    void setSpeed();
    void setTSpeed();
};

#endif // SPEEDCONTROL_H
