#ifndef ANALOGSENSORGRAPH_H
#define ANALOGSENSORGRAPH_H

#include <qwt_plot_layout.h>

class Histogram;

class AnalogGraph: public QwtPlot
{
    Q_OBJECT

public:
    AnalogGraph(QWidget * = 0);
    ~AnalogGraph();

    int loadAnalogValues();
    void setAnalogChannels(int channel, int value);
    int numberOfAnalogChannels();

public slots:
    void analogTimeOut();

private:
    void populate();

public:
    QTimer *analogTimer;

private:
    int numberOfAnalogChannels_;
    QVector <double> analogChannels;
    Histogram *analogHistogram;
};

#endif //ANALOGSENSORGRAPH_H
