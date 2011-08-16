#include <QtCore/QTimer>

#include <QtGui/QLabel>
#include <QtGui/QLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QMessageBox>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

#include "analogsensorgraph.h"
#include "sensor.h"
#include "serialgate.h"

#include "inputsoutputstab.h"

InputsOutputsTab::InputsOutputsTab (QWidget *parent) :
    QWidget (parent)
{
    analogFrame_ = new AnalogGraph (this);
    manualTimer_ = new QTimer (this);
    connect (manualTimer_, SIGNAL (timeout()), this, SLOT (manualTimeOut()));

    QHBoxLayout *lay_digitalInputs = new QHBoxLayout;

    for (int i = 0; i < numberOfDigitalInputs; ++i) {
        Sensor *s = new Sensor (i);
        digitalInputs_.push_back (s);
        lay_digitalInputs->addWidget (s);

        if (i != numberOfDigitalInputs - 1) {
            lay_digitalInputs->addSpacerItem (new QSpacerItem (10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
        }
    }

    QGroupBox *group_digitalInputs = new QGroupBox ("Digital inputs");
    group_digitalInputs->setLayout (lay_digitalInputs);

    QGridLayout *grid_outputs = new QGridLayout;
    QCheckBox *checkBox = 0;
    const QString name = "Set state of digital output %1";

    for (int i = 0 ; i < numberOfDigitalOutputs; ++i) {
        checkBox = new QCheckBox (name.arg (i + 1));
        checkBox->setEnabled (false);
        connect (checkBox, SIGNAL (stateChanged (int)),
                 this , SLOT (digitalOutputStateChanged (int)));
        digitalOutputCheck_.push_back (checkBox);
        grid_outputs->addWidget (digitalOutputCheck_.at (i), i, 0, Qt::AlignLeft);
    }

    QGroupBox *group_digitalOutputs = new QGroupBox ("Digital outputs");
    group_digitalOutputs->setLayout (grid_outputs);

    for (int i = 0; i < analogFrame_->numberOfAnalogChannels(); ++i) {
        QLineEdit *le = new QLineEdit ("100");
        maxSpeedEdit_ << le;
        QLineEdit *le2 = new QLineEdit ("0");
        shiftEdit_ << le2;
    }

    QGridLayout *grid_manualControl = new QGridLayout;
    grid_manualControl->addWidget (new QLabel ("Number of analog input:"), 0, 0);
    grid_manualControl->addWidget (new QLabel ("Set maximum speed"), 1, 0);
    grid_manualControl->addWidget (new QLabel ("Set shift"), 2, 0);

    QVector <QString> numbers;
    numbers << QString ("1st")
            << QString ("2d")
            << QString ("3d")
            << QString ("4th")
            << QString ("5th")
            << QString ("6th");

    for (int i = 0; i < analogFrame_->numberOfAnalogChannels(); ++i) {
        grid_manualControl->addWidget (new QLabel (numbers.at (i)), 0, i + 1, Qt::AlignHCenter | Qt::AlignVCenter);
        grid_manualControl->addWidget (maxSpeedEdit_.at (i), 1, i + 1, Qt::AlignVCenter);
        grid_manualControl->addWidget (shiftEdit_.at (i), 2, i + 1, Qt::AlignVCenter);
    }

    startButton_ = new QPushButton ("Start", this);
    connect (startButton_, SIGNAL (clicked()), this, SLOT (startManualControl()));
    startButton_->setSizePolicy (QSizePolicy::Maximum, QSizePolicy::Maximum);
    grid_manualControl->addWidget (startButton_, 3, 0, 1, analogFrame_->numberOfAnalogChannels() + 1, Qt::AlignHCenter | Qt::AlignBottom);

    QGroupBox *group_manual = new QGroupBox ("Manual control");
    group_manual->setLayout (grid_manualControl);

    QGridLayout *grid = new QGridLayout (this);
    grid->addWidget (analogFrame_, 0, 0, 3, 2);
    grid->addWidget (group_digitalInputs, 2, 2);
    grid->addWidget (group_digitalOutputs, 0, 2);
    grid->addWidget (group_manual, 1, 2);

    setLayout (grid);
}

void InputsOutputsTab::startManualControl()
{
    if (!SerialGate::instance()->state) {
        QMessageBox::information (this, "", "Open serial port first");
        return;
    }

    static bool manual = false;

    if (manual) {
        startButton_->setText ("Start");
        manualTimer_->stop();
        SerialGate::instance()->send ("D,0,0\n");
    } else {
        startButton_->setText ("Stop");
        SerialGate::instance()->send ("D,0,0\n");
        manualTimer_->start (60);
    }

    manual = !manual;
}

void InputsOutputsTab::manualTimeOut()
{
    SerialGate::instance()->send (QString ("I,1\n"));
    const int numBytesToRead = 4;
    QString buff = SerialGate::instance()->recv (numBytesToRead);
    const int speedLeft = shiftEdit_.at (0)->text().toInt()
                          + (buff.section (",", 1, 1).toInt() / 1024) * maxSpeedEdit_.at (0)->text().toInt();

    SerialGate::instance()->send (QString ("I,0\n"));
    buff = SerialGate::instance()->recv (numBytesToRead);
    const int speedRight = shiftEdit_.at (1)->text().toInt()
                           + (buff.section (",", 1, 1).toInt() / 1024) * maxSpeedEdit_.at (1)->text().toInt();

    SerialGate::instance()->send (QString ("D,%1,%2\n").arg (speedLeft).arg (speedRight));
}

void InputsOutputsTab::digitalOutputStateChanged (int state)
{
    QCheckBox *box = qobject_cast <QCheckBox *> (sender ());
    Q_CHECK_PTR (box);

    const int text = box->text().right (1).toInt() - 1;

    SerialGate::instance()->send (QString ("Q,%1,%2\n").arg (text).arg (state ? 1 : 0));
}

void InputsOutputsTab::openPortButtonClicked()
{
    for (QVector < QCheckBox *>:: const_iterator it = digitalOutputCheck_ .begin(),
            end = digitalOutputCheck_ .end(); it != end; ++it) {
        (*it)->setEnabled (SerialGate::instance()->state);
    }
}
