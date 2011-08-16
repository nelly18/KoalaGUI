#ifndef SCRIPT_H
#define SCRIPT_H

#include <QtCore/QObject>


class Script : public QObject
{
    Q_OBJECT

public:
    explicit Script (QObject *parent = 0);

public slots:
    void setSpeed (int leftMotor, int rightMotor);
    void stop();
    void forward (int distance);
    void back (int distance);
    void turnLeft (int angle);
    void turnRight (int angle);
    void delay (int time);

private:
    int speedLeft_;
    int speedRight_;
    int minSpeed_;
};

#endif // SCRIPT_H
