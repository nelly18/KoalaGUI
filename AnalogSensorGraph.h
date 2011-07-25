#ifndef ANALOGSENSORGRAPH_H
#define ANALOGSENSORGRAPH_H
#include <qwt_plot.h>
#include <QTimer>
#include "Sensor.h"
#include "defines.h"
#include <stdlib.h>
#include <qpen.h>
#include <qwt_plot_layout.h>
#include <qwt_legend.h>
#include <qwt_legend_item.h>
#include <qwt_plot_grid.h>
#include "analoghistogram.h"
#include <qwt_column_symbol.h>
#include <qwt_series_data.h>
#include <qwt_scale_div.h>
#include <QVector>

class AnalogGraph: public QwtPlot
{
    Q_OBJECT
    int numberOfAnalogChannels;
public:
    AnalogGraph(QWidget * = NULL);
    QTimer *analogTimer;
    int getAnalogValues();
    void setAnalogChannels(int channel, int value);
    void setnumberOfAnalogChannels(int);
    ~AnalogGraph();
private:
    void populate();
    QVector <double> analogChannels;
    Histogram *analogHistogram;

protected:


private Q_SLOTS:
    //void showItem(QwtPlotItem *, bool on);
   // void TimeOut(void);
private slots:
    void analogTimeOut();

};

#endif //ANALOGSENSORGRAPH_H
