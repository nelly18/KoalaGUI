#include "pidregulator.h"
#include <QLabel>
#include <QLayout>
#include <QGroupBox>
#include <SerialGate.h>
#include <QMessageBox>


extern SerialGate sg;

PIDRegulator::PIDRegulator(QFrame *parent) : QFrame(parent)
{
    QLabel *pic = new QLabel;
    pic->setPixmap(QPixmap(":/res/PID.png"));

    QLabel *l_speedProp = new QLabel("Proportional");
    QLabel *l_speedInt = new QLabel("Integral");
    QLabel *l_speedDiff = new QLabel("Differential");

    l_speedProp->setFrameShape(QFrame::NoFrame);
    l_speedInt->setFrameShape(QFrame::NoFrame);
    l_speedDiff->setFrameShape(QFrame::NoFrame);

    speedProp = new QLineEdit("100");
    speedInt = new QLineEdit("800");
    speedDiff = new QLineEdit("100");

    butSetSpeed = new QPushButton("Set Configuration");
    connect(butSetSpeed, SIGNAL(clicked()), this, SLOT(setSpeed()));

    QGridLayout *gridSpeed = new QGridLayout;
    gridSpeed->addWidget(l_speedProp, 0, 0);
    gridSpeed->addWidget(l_speedInt, 1, 0);
    gridSpeed->addWidget(l_speedDiff, 2, 0);
    gridSpeed->addWidget(speedProp, 0, 1);
    gridSpeed->addWidget(speedInt, 1, 1);
    gridSpeed->addWidget(speedDiff, 2, 1);
    gridSpeed->addWidget(butSetSpeed, 3, 0, 1, 2, Qt::AlignBottom);

    QGroupBox *groupSpeed = new QGroupBox("PID speed controller configuration");
    groupSpeed->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    groupSpeed->setLayout(gridSpeed);

    QLabel *l_posProp = new QLabel("Proportional");
    QLabel *l_posInt = new QLabel("Integral");
    QLabel *l_posDiff = new QLabel("Differential");

    l_posProp->setFrameShape(QFrame::NoFrame);
    l_posInt->setFrameShape(QFrame::NoFrame);
    l_posDiff->setFrameShape(QFrame::NoFrame);

    posProp = new QLineEdit("400");
    posInt = new QLineEdit("4");
    posDiff = new QLineEdit("400");

    butSetPos = new QPushButton("Set Configuration");
    connect(butSetPos, SIGNAL(clicked()), this, SLOT(setPos()));

    QGridLayout *gridPos = new QGridLayout;
    gridPos->addWidget(l_posProp, 0, 0);
    gridPos->addWidget(l_posInt, 1, 0);
    gridPos->addWidget(l_posDiff, 2, 0);
    gridPos->addWidget(posProp, 0, 1);
    gridPos->addWidget(posInt, 1, 1);
    gridPos->addWidget(posDiff, 2, 1);
    gridPos->addWidget(butSetPos, 3, 0, 1, 2, Qt::AlignBottom);

    QGroupBox *groupPos = new QGroupBox("Position PID controller configuration");
    groupPos->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    groupPos->setLayout(gridPos);

    QLabel *l_leftMotor = new QLabel("Left motor PWM (-255 - 255)");
    QLabel *l_rightMotor = new QLabel("Right motor PWM (-255 - 255)");

    leftMotorPWM = new QSlider(Qt::Horizontal);
    rightMotorPWM = new QSlider(Qt::Horizontal);

    leftMotorPWM->setTracking(false);
    rightMotorPWM->setTracking(false);

    leftMotorPWM->setRange(-255, 255);
    rightMotorPWM->setRange(-255, 255);

    leftMotorPWM->setTickPosition(QSlider::TicksAbove);
    rightMotorPWM->setTickPosition(QSlider::TicksAbove);

    leftMotorPWM->setTickInterval(40);
    rightMotorPWM->setTickInterval(40);

    butSetPWM = new QPushButton("Set configuration");
    connect(butSetPWM, SIGNAL(clicked()), this, SLOT(setPWM()));

    QGridLayout *gridPWM = new QGridLayout;
    gridPWM->addWidget(l_leftMotor, 0, 0);
    gridPWM->addWidget(l_rightMotor, 1, 0);
    gridPWM->addWidget(leftMotorPWM, 0, 1);
    gridPWM->addWidget(rightMotorPWM, 1, 1);
    gridPWM->addWidget(butSetPWM, 2, 0, 1, 2, Qt::AlignBottom);

    QGroupBox *groupPWM = new QGroupBox("PWM configuration");
    groupPWM->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    groupPWM->setLayout(gridPWM);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(pic, 0, 0, 1, 3, Qt::AlignCenter);
    grid->addWidget(groupSpeed, 1, 0);
    grid->addWidget(groupPos, 1, 1);
    grid->addWidget(groupPWM, 1, 2);
    setLayout(grid);
}

void PIDRegulator::setSpeed()
{
    if (sg.state)
        sg.Send(QString("A,%1,%2,%3\n").arg(speedProp->text()).arg(speedInt->text()).arg(speedDiff->text()));
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
    }
}

void PIDRegulator::setPos()
{
    if (sg.state)
        sg.Send(QString("F,%1,%2,%3\n").arg(posProp->text()).arg(posInt->text()).arg(posDiff->text()));
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
    }
}

void PIDRegulator::setPWM()
{
    int leftMotorPWMValue = leftMotorPWM->value();
    int rightMotorPWMValue = rightMotorPWM->value();

    if (sg.state)
        sg.Send(QString("P,%1,%2\n").arg(leftMotorPWMValue).arg(rightMotorPWMValue));
    else
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
    }
}
