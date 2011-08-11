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

    void loadAnalogValues();
    int numberOfAnalogChannels() {
        return numberOfAnalogChannels_;
    }

public slots:
    void redrawAnalogGraph(QVector <double> values);

private:
    void populate();

private:
    int numberOfAnalogChannels_;
    Histogram *analogHistogram_;

};

#endif //ANALOGSENSORGRAPH_H
