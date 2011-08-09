#ifndef PIDREGULATOR_H
#define PIDREGULATOR_H

#include <QtGui/QFrame>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>

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

public:
    PIDRegulator(QFrame *parent = 0);

private slots:
    void setSpeed();
    void setPos();
};

#endif // PIDREGULATOR_H
