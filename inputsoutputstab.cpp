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

extern SerialGate sg;

InputsOutputsTab::InputsOutputsTab(QWidget *parent) :
    QWidget(parent)
{
    analogFrame = new AnalogGraph(this);
    manualTimer = new QTimer(this);
    connect(manualTimer, SIGNAL(timeout()), this, SLOT(manualTimeOut()));

    QHBoxLayout *lay_digitalInputs = new QHBoxLayout;
    for (int i = 0; i < numberOfDigitalInputs; i++)
    {
        Sensor *s = new Sensor(i);
        digitalInputs << s;
        lay_digitalInputs->addWidget(digitalInputs.at(i));
        if (i != numberOfDigitalInputs - 1)
            lay_digitalInputs->addSpacerItem(new QSpacerItem(10, 10, QSizePolicy::Minimum, QSizePolicy::Fixed));
    }
    QGroupBox *group_digitalInputs = new QGroupBox("Digital inputs");
    group_digitalInputs->setLayout(lay_digitalInputs);

    QGridLayout *grid_outputs = new QGridLayout;
    QCheckBox *checkBox;
    const QString name = "Set state of digital output %1";
    for ( int i = 0 ; i < numberOfDigitalOutputs; ++i)
    {
        checkBox = new QCheckBox ( name.arg(i + 1 ));
        checkBox->setEnabled(false);
        connect( checkBox, SIGNAL (stateChanged( int )), this , SLOT (digitalOutputStateChanged( int )));
        chb_digitalOutput.push_back (checkBox);
        grid_outputs->addWidget(chb_digitalOutput.at(i), i, 0, Qt::AlignLeft);
    }

    QGroupBox *group_digitalOutputs = new QGroupBox("Digital outputs");
    group_digitalOutputs->setLayout(grid_outputs);

    for (int i = 0; i < analogFrame->numberOfAnalogChannels(); i ++)
    {
        QLineEdit *le = new QLineEdit("100");
        le_maxSpeed << le;
        QLineEdit *le2 = new QLineEdit("0");
        le_shift << le2;
    }

    QGridLayout *grid_manualControl = new QGridLayout;
    grid_manualControl->addWidget(new QLabel("Number of analog input:"), 0, 0);
    grid_manualControl->addWidget(new QLabel("Set maximum speed"), 1, 0);
    grid_manualControl->addWidget(new QLabel("Set shift"), 2, 0);
    QVector <QString> numbers;
    numbers << QString("1st") << QString("2d") << QString("3d") << QString("4th") << QString("5th") << QString("6th");
    for (int i = 0; i < analogFrame->numberOfAnalogChannels(); i ++)
    {
        grid_manualControl->addWidget(new QLabel(numbers.at(i)), 0, i + 1, Qt::AlignHCenter|Qt::AlignVCenter);
        grid_manualControl->addWidget(le_maxSpeed.at(i), 1, i + 1, Qt::AlignVCenter);
        grid_manualControl->addWidget(le_shift.at(i), 2, i + 1, Qt::AlignVCenter);
    }

    pb_start = new QPushButton("Start", this);
    connect(pb_start, SIGNAL(clicked()), this, SLOT(startManualControl()));
    pb_start->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    grid_manualControl->addWidget(pb_start, 3, 0, 1, analogFrame->numberOfAnalogChannels()+ 1, Qt::AlignHCenter|Qt::AlignBottom);

    QGroupBox *group_manual = new QGroupBox("Manual control");
    group_manual->setLayout(grid_manualControl);


    QGridLayout *grid = new QGridLayout(this);
    grid->addWidget(analogFrame, 0, 0, 3, 2);
    grid->addWidget(group_digitalInputs, 2, 2);
    grid->addWidget(group_digitalOutputs, 0, 2);
    grid->addWidget(group_manual, 1, 2);

    setLayout(grid);
}

void InputsOutputsTab::startManualControl()
{
    if (!sg.state)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
        return;
    }

    static bool manual = false;
    if (manual)
    {
        manual = false;
        pb_start->setText("Start");
        manualTimer->stop();
        sg.send("D,0,0\n");
    }
    else
    {
        manual = true;
        pb_start->setText("Stop");
        sg.send("D,0,0\n");
        manualTimer->start(60);
    }
}

void InputsOutputsTab::manualTimeOut()
{
    sg.send(QString("I,1\n"));
    QString buff = "";
    const int numBytesToRead = 4;
    sg.recv(buff, numBytesToRead);
    int speedLeft = le_shift.at(0)->text().toInt() + (buff.section(",", 1, 1).toInt()/1024) * le_maxSpeed.at(0)->text().toInt();

    sg.send(QString("I,0\n"));
    buff = "";
    sg.recv(buff, numBytesToRead);
    int speedRight = le_shift.at(1)->text().toInt() + (buff.section(",", 1, 1).toInt()/1024) * le_maxSpeed.at(1)->text().toInt();

    sg.send(QString("D,%1,%2\n").arg(speedLeft).arg(speedRight));
}

void InputsOutputsTab::digitalOutputStateChanged(int state)
{
    QCheckBox *box = qobject_cast <QCheckBox*> (sender ());
    int text = box->text().right(1).toInt() - 1;

    if (state)
        sg.send(QString("Q,%1,1\n").arg(text));
     else
        sg.send(QString("Q,%1,0\n").arg(text));
}

void InputsOutputsTab::openPortButtonClicked()
{
    if (sg.state)
        for (int i = 0; i < numberOfDigitalOutputs; i++ )
            chb_digitalOutput.at(i)->setEnabled(true);
    else
        for (int i = 0; i < numberOfDigitalOutputs; i++ )
            chb_digitalOutput.at(i)->setEnabled(false);
}
