#ifndef ANALOGSENSORGRAPH_H
#define ANALOGSENSORGRAPH_H

#include <qwt_plot_layout.h>

class Histogram;

class AnalogGraph: public QwtPlot
{
    Q_OBJECT
    int numberOfAnalogChannels;
public:
    AnalogGraph(QWidget * = NULL);
    ~AnalogGraph();

    QTimer *analogTimer;
    int getAnalogValues();
    void setAnalogChannels(int channel, int value);

    void setNumberOfAnalogChannels(int);
    int getNumberOfAnalogChannels();

private:
    void populate();
    QVector <double> analogChannels;
    Histogram *analogHistogram;

protected:


private Q_SLOTS:

private slots:
    void analogTimeOut();

};

#endif //ANALOGSENSORGRAPH_H
