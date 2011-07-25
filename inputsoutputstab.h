#ifndef INPUTSOUTPUTSTAB_H
#define INPUTSOUTPUTSTAB_H
#include "AnalogSensorGraph.h"
#include <QWidget>
#include <QSpinBox>
#include "Sensor.h"
#include <QCheckBox>
#include <QComboBox>

class InputsOutputsTab : public QWidget
{
    Q_OBJECT

    QSpinBox *sb_numAnalogInputs;
    QVector <Sensor *> digitalInputs;

    QVector <QCheckBox *> chb_digitalOutput;
    QVector <QComboBox *> cb_digitalOutput;


    //void paintEvent(QPaintEvent *);

public:
    explicit InputsOutputsTab(QWidget *parent = 0);

    AnalogGraph *analogFrame;

signals:

public slots:
    void changeNumberOfAnalogInputs(int);
};

#endif // INPUTSOUTPUTSTAB_H
