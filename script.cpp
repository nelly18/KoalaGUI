#include <QtGui/QMessageBox>
#include <QtCore/QDebug>

#include "script.h"
#include "serialgate.h"

extern SerialGate sg;

Script::Script(QObject *parent) :
    QObject(parent)
{
    moveToThread(&scriptThread);
    scriptThread.start();

    speedLeft = 0;
    speedRight = 0;
    minSpeed = 0;
}

void Script::setSpeed(int leftMotor, int rightMotor)
{
    speedLeft = leftMotor;
    speedRight = rightMotor;
    minSpeed = qMin(leftMotor, rightMotor);
    sg.Send(QString("D,%1,%2\n").arg(leftMotor).arg(rightMotor));
    qDebug() << thread();
}

void Script::stop()
{
    sg.Send(QString("D,0,0\n"));
}

void Script::forward(int distance)
{
    int speed = minSpeed * 3;
    int time = distance * 100 / speed;
    sg.Send(QString("D,%1,%1\n").arg(minSpeed));
    scriptThread.wait(5000);

}

void Script::back(int distance)
{

}

void Script::turnLeft(int angle)
{

}

void Script::turnRight(int angle)
{

}

void Script::delay(int time)
{

}
