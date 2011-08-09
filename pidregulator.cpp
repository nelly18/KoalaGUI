#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QMessageBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

#include "serialgate.h"

#include "pidregulator.h"

extern SerialGate sg;

PidRegulator::PidRegulator(QFrame *parent)
    : QFrame(parent)
{
    QLabel *pic = new QLabel;
    pic->setPixmap(QPixmap(":/res/PID.png"));

    QLabel *l_speedProp = new QLabel("Proportional");
    QLabel *l_speedInt = new QLabel("Integral");
    QLabel *l_speedDiff = new QLabel("Differential");

    l_speedProp->setFrameShape(QFrame::NoFrame);
    l_speedInt->setFrameShape(QFrame::NoFrame);
    l_speedDiff->setFrameShape(QFrame::NoFrame);

    speedPropEdit_ = new QLineEdit("100");
    speedIntEdit_ = new QLineEdit("800");
    speedDiffEdit_ = new QLineEdit("100");

    butSetSpeedButton_ = new QPushButton("Set Configuration");
    butSetSpeedButton_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(butSetSpeedButton_, SIGNAL(clicked()), this, SLOT(setSpeed()));

    QGridLayout *gridSpeed = new QGridLayout;
    gridSpeed->addWidget(l_speedProp, 0, 0);
    gridSpeed->addWidget(l_speedInt, 1, 0);
    gridSpeed->addWidget(l_speedDiff, 2, 0);
    gridSpeed->addWidget(speedPropEdit_, 0, 1);
    gridSpeed->addWidget(speedIntEdit_, 1, 1);
    gridSpeed->addWidget(speedDiffEdit_, 2, 1);
    gridSpeed->addWidget(butSetSpeedButton_, 3, 0, 1, 2, Qt::AlignTop|Qt::AlignHCenter);

    QGroupBox *groupSpeed = new QGroupBox("PID speed controller configuration");
    groupSpeed->setLayout(gridSpeed);

    QLabel *l_posProp = new QLabel("Proportional");
    QLabel *l_posInt = new QLabel("Integral");
    QLabel *l_posDiff = new QLabel("Differential");

    l_posProp->setFrameShape(QFrame::NoFrame);
    l_posInt->setFrameShape(QFrame::NoFrame);
    l_posDiff->setFrameShape(QFrame::NoFrame);

    posPropEdit_ = new QLineEdit("400");
    posIntEdit_ = new QLineEdit("4");
    posDiffEdit_ = new QLineEdit("400");

    butSetPosButton_ = new QPushButton("Set Configuration");
    butSetPosButton_->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(butSetPosButton_, SIGNAL(clicked()), this, SLOT(setPos()));

    QGridLayout *gridPos = new QGridLayout;
    gridPos->addWidget(l_posProp, 0, 0);
    gridPos->addWidget(l_posInt, 1, 0);
    gridPos->addWidget(l_posDiff, 2, 0);
    gridPos->addWidget(posPropEdit_, 0, 1);
    gridPos->addWidget(posIntEdit_, 1, 1);
    gridPos->addWidget(posDiffEdit_, 2, 1);
    gridPos->addWidget(butSetPosButton_, 3, 0, 1, 2, Qt::AlignTop|Qt::AlignHCenter);

    QGroupBox *groupPos = new QGroupBox("Position PID controller configuration");
    groupPos->setLayout(gridPos);

    QGridLayout *grid = new QGridLayout;
    grid->addWidget(pic, 0, 0, 2, 1, Qt::AlignCenter);
    grid->addWidget(groupSpeed, 0, 1);
    grid->addWidget(groupPos, 1, 1);

    setLayout(grid);
}

void PidRegulator::setSpeed()
{
    if (sg.state) {
        sg.send(QString("A,%1,%2,%3\n").arg(speedPropEdit_->text()).arg(speedIntEdit_->text()).arg(speedDiffEdit_->text()));
    } else {
        QMessageBox::information (this, "", "Open serial port first");
    }
}

void PidRegulator::setPos()
{
    if (sg.state) {
        sg.send(QString("F,%1,%2,%3\n").arg(posPropEdit_->text()).arg(posIntEdit_->text()).arg(posDiffEdit_->text()));
    } else {
        QMessageBox::information (this, "", "Open serial port first");
    }
}


