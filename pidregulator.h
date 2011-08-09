#ifndef PIDREGULATOR_H
#define PIDREGULATOR_H

#include <QtGui/QFrame>

class QLineEdit;
class QPushButton;

class PIDRegulator : public QFrame
{
    Q_OBJECT
public:
    PIDRegulator(QFrame *parent = 0);
private:
    QLineEdit *speedProp;
    QLineEdit *speedInt;
    QLineEdit *speedDiff;
    QLineEdit *posProp;
    QLineEdit *posInt;
    QLineEdit *posDiff;
    QPushButton *butSetSpeed;
    QPushButton *butSetPos;
private slots:
    void setSpeed();
    void setPos();
};

#endif // PIDREGULATOR_H
