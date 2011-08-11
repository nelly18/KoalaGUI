#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "serialgate.h"

#include "script.h"

Script::Script(QObject *parent) :
    QObject(parent), speedLeft_ (0), speedRight_ (0), minSpeed_ (0)
{
    moveToThread(&scriptThread_);
    scriptThread_.start();
}

void Script::setSpeed(int leftMotor, int rightMotor)
{
    speedLeft_ = leftMotor;
    speedRight_ = rightMotor;
    minSpeed_ = qMin(leftMotor, rightMotor);
    SerialGate::instance()->send(QString("D,%1,%2\n").arg(leftMotor).arg(rightMotor));
    qDebug() << thread();
}

void Script::stop()
{
    SerialGate::instance()->send(QString("D,0,0\n"));
}

void Script::forward(int distance)
{
    Q_UNUSED (distance);
    //int speed = minSpeed_ * 3;
    //int time = distance * 100 / speed;
    SerialGate::instance()->send(QString("D,%1,%1\n").arg(minSpeed_));
    scriptThread_.wait(5000);

}

void Script::back(int distance)
{
    Q_UNUSED (distance);
}

void Script::turnLeft(int angle)
{
    Q_UNUSED (angle);
}

void Script::turnRight(int angle)
{
    Q_UNUSED (angle);
}

void Script::delay(int time)
{
    Q_UNUSED (time);
}
