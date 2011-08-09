#ifndef INPUTSOUTPUTSTAB_H
#define INPUTSOUTPUTSTAB_H

#include <QtGui/QWidget>
#include <QtGui/QSpinBox>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

#include "analogsensorgraph.h"
#include "sensor.h"

class InputsOutputsTab : public QWidget
{
    Q_OBJECT

    QSpinBox *sb_numAnalogInputs;
    QVector <Sensor *> digitalInputs;

    QVector <QCheckBox *> chb_digitalOutput;

    QVector <QLineEdit*> le_maxSpeed;
    QVector <QLineEdit*> le_shift;
    QPushButton *pb_start;


public:
    explicit InputsOutputsTab(QWidget *parent = 0);

    AnalogGraph *analogFrame;
    QTimer *manualTimer;

signals:

public slots:
    void manualTimeOut();
    void startManualControl();
    void digitalOutputStateChanged(int state);
    void openPortButtonClicked();
};

#endif // INPUTSOUTPUTSTAB_H
