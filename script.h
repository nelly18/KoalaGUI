#ifndef SCRIPT_H
#define SCRIPT_H

#include <QObject>
#include "mythread.h"

class Script : public QObject
{
    Q_OBJECT
public:
    explicit Script(QObject *parent = 0);
private:
    MyThread scriptThread;
    int speedLeft;
    int speedRight;
    int minSpeed;

signals:

public slots:
    void setSpeed(int leftMotor, int rightMotor);
    void stop();
    void forward(int distance);
    void back(int distance);
    void turnLeft(int angle);
    void turnRight(int angle);
    void delay(int time);
};

#endif // SCRIPT_H
