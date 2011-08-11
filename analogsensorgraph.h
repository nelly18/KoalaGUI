#ifndef ANALOGSENSORGRAPH_H
#define ANALOGSENSORGRAPH_H

#include <qwt_plot_layout.h>

class Histogram;
class AnalogValuesLoader;

class AnalogGraph: public QwtPlot
{
    Q_OBJECT

public:
    AnalogGraph(QWidget * = 0);
    ~AnalogGraph();

    int numberOfAnalogChannels() const {
        return numberOfAnalogChannels_;
    }

public slots:
    void redrawAnalogGraph(const QVector <double> &values);

private:
    void populate();

private:
    int numberOfAnalogChannels_;
    Histogram *analogHistogram_;
    AnalogValuesLoader *analogValuesLoader_;
};

#endif //ANALOGSENSORGRAPH_H
