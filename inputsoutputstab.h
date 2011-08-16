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

public:
    explicit InputsOutputsTab (QWidget *parent = 0);

public slots:
    void manualTimeOut();
    void startManualControl();
    void digitalOutputStateChanged (int state);
    void openPortButtonClicked();

public:
    AnalogGraph *analogFrame_;
    QTimer *manualTimer_;

private:
    QSpinBox *numAnalogInputsSpin_;
    QVector <Sensor *> digitalInputs_;
    QVector <QCheckBox *> digitalOutputCheck_;
    QVector <QLineEdit *> maxSpeedEdit_;
    QVector <QLineEdit *> shiftEdit_;
    QPushButton *startButton_;
};

#endif // INPUTSOUTPUTSTAB_H
