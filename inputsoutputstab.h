#ifndef INPUTSOUTPUTSTAB_H
#define INPUTSOUTPUTSTAB_H

#include <QtGui/QWidget>

class QSpinBox;
class Sensor;
class QCheckBox;
class QLineEdit;
class QPushButton;
class AnalogGraph;
class QTimer;

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
