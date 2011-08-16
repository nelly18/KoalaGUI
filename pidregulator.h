#ifndef PIDREGULATOR_H
#define PIDREGULATOR_H

#include <QtGui/QFrame>

class QLineEdit;
class QPushButton;

class PidRegulator : public QFrame
{
    Q_OBJECT

public:
    PidRegulator (QFrame *parent = 0);

private slots:
    void setSpeed();
    void setPos();

private:
    QLineEdit *speedPropEdit_;
    QLineEdit *speedIntEdit_;
    QLineEdit *speedDiffEdit_;
    QLineEdit *posPropEdit_;
    QLineEdit *posIntEdit_;
    QLineEdit *posDiffEdit_;
    QPushButton *butSetSpeedButton_;
    QPushButton *butSetPosButton_;
};

#endif // PIDREGULATOR_H
