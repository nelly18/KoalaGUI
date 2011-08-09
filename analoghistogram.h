#ifndef ANALOGHISTOGRAM_H
#define ANALOGHISTOGRAM_H

#include <qwt_plot_histogram.h>

class Histogram: public QwtPlotHistogram
{
public:
    Histogram(const QString &, const QColor &);
    void setColor(const QColor &);
    void setValues(int numValues, const QVector <double> &);
};


#endif // ANALOGHISTOGRAM_H
