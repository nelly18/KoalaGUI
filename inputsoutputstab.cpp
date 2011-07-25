#include "inputsoutputstab.h"
#include <QLabel>
#include <QLayout>
#include <QGroupBox>


InputsOutputsTab::InputsOutputsTab(QWidget *parent) :
    QWidget(parent)
{
    analogFrame = new AnalogGraph(this);
    //analogFrame->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);

    QLabel *lab_numAnInputs = new QLabel("Number of analog inputs", this);

    sb_numAnalogInputs = new QSpinBox;
    //sb_numAnalogInputs->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    connect(sb_numAnalogInputs, SIGNAL(valueChanged(int)), this, SLOT(changeNumberOfAnalogInputs(int)));

    sb_numAnalogInputs->setMinimum(2);
    sb_numAnalogInputs->setMaximum(numberOfDigitalInputs);

    QGroupBox *group_digitalInputs = new QGroupBox("Digital inputs");
    QHBoxLayout *lay_digitalInputs = new QHBoxLayout;
    for (int i = 0; i < numberOfDigitalInputs; i++)
    {
        Sensor *s = new Sensor(i, QPoint(i*20 + 10, 20), sensorradius, group_digitalInputs);
        digitalInputs << s;
        lay_digitalInputs->addWidget(digitalInputs.at(i));
    }
    //group_digitalInputs->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    group_digitalInputs->setLayout(lay_digitalInputs);

    for (int i = 0; i < numberOfDigitalOutputs; i++)
    {
        cb_digitalOutput << new QComboBox;
        cb_digitalOutput.at(i)->addItem("PWM");
        cb_digitalOutput.at(i)->addItem("Digital");

        chb_digitalOutput << new QCheckBox(QString("Digital output %1").arg(i + 1));
    }

    QGridLayout *grid_outputs = new QGridLayout;

    for (int i = 0; i < numberOfDigitalOutputs; i++)
        {
            grid_outputs->addWidget(cb_digitalOutput.at(i), i, 0);
            grid_outputs->addWidget(chb_digitalOutput.at(i), i, 1);
        }

    QGroupBox *group_digitalOutputs = new QGroupBox("Digital outputs");
    //group_digitalOutputs->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    group_digitalOutputs->setLayout(grid_outputs);

    QGridLayout *grid = new QGridLayout(this);
    //grid->setHorizontalSpacing(50);
    grid->setColumnMinimumWidth(1, 125);
    grid->addWidget(analogFrame, 0, 0, 2, 2);
    grid->addWidget(lab_numAnInputs, 1, 0, Qt::AlignBottom);
    grid->addWidget(sb_numAnalogInputs, 1, 1, Qt::AlignBottom);
    grid->addWidget(group_digitalInputs, 0, 2);
    grid->addWidget(group_digitalOutputs, 1, 2);

    setLayout(grid);
}

void InputsOutputsTab::changeNumberOfAnalogInputs(int i)
{
    analogFrame->setnumberOfAnalogChannels(i);
    analogFrame->replot();
}

//void InputsOutputsTab::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing);

//    QPen pen(Qt::NoPen);
//    painter.setPen(pen);
//    QBrush brush(Qt::SolidPattern);

//    int r;
//    QPoint c;
//    QColor col;

//    for(int i = 0; i < numberOfDigitalInputs; i++)
//    {
//        c = digitalInputs.at(i)->getCenter();
//        r = digitalInputs.at(i)->getRadii();
//        col = digitalInputs.at(i)->getColor();

//        brush.setColor(col);
//        painter.setBrush(brush);
//        painter.drawEllipse(c, r, r);
//    }
//}
