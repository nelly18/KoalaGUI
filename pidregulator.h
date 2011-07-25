#ifndef PIDREGULATOR_H
#define PIDREGULATOR_H
#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QSlider>

class PIDRegulator : public QFrame
{
    Q_OBJECT

    QLineEdit *speedProp;
    QLineEdit *speedInt;
    QLineEdit *speedDiff;

    QLineEdit *posProp;
    QLineEdit *posInt;
    QLineEdit *posDiff;

    QPushButton *butSetSpeed;
    QPushButton *butSetPos;

    QSlider *leftMotorPWM;
    QSlider *rightMotorPWM;

    QPushButton *butSetPWM;

public:
    PIDRegulator(QFrame *parent = 0);

private slots:
    void setSpeed();
    void setPos();
    void setPWM();
};

#endif // PIDREGULATOR_H
