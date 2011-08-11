#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include <QtGui/QPen>

#include <qwt_scale_div.h>
#include <qwt_plot_grid.h>

#include "serialgate.h"
#include "analoghistogram.h"
#include "analogvaluesloader.h"

#include "analogsensorgraph.h"


AnalogGraph::AnalogGraph(QWidget *parent)
    : QwtPlot(parent), numberOfAnalogChannels_ (6)
{
    analogValuesLoader = new AnalogValuesLoader;
    connect(analogValuesLoader, SIGNAL(valuesChanged(values)),this, SLOT(redrawAnalogGraph(values)));
    analogValuesLoader->start();

    plotLayout()->setAlignCanvasToScales(true);

    QwtText textLeft("Analog value");
    QwtText textBottom("Analog channel");
    QFont font;
    font.setPointSize(12);
    font.setFamily("Arial");
    textLeft.setFont(font);
    textBottom.setFont(font);
    setAxisTitle(QwtPlot::yLeft, textLeft);
    setAxisTitle(QwtPlot::xBottom, textBottom);

    setAxisScale(QwtPlot::xBottom, 0, numberOfAnalogChannels_, 1);
    setAxisScale(QwtPlot::yLeft, 0, 1024, 200);

    QList<double> ticks[QwtScaleDiv::NTickTypes];
    for (int i = 0; i <= numberOfAnalogChannels_; i++) {
        ticks[QwtScaleDiv::MajorTick] << i;
    }

    QwtScaleDiv scaleDiv(
                ticks[QwtScaleDiv::MajorTick].first(),
                ticks[QwtScaleDiv::MajorTick].last(),
                ticks );

    setAxisScaleDiv(QwtPlot::xBottom, scaleDiv);

    populate();
    replot(); // creating the legend items
}

AnalogGraph::~AnalogGraph()
{

}

void AnalogGraph::populate()
{
    QwtPlotGrid *grid = new QwtPlotGrid;

    grid->enableX(false);
    grid->enableY(false);
    grid->enableXMin(false);
    grid->enableYMin(false);
    grid->setMajPen(QPen(Qt::black, 0, Qt::DotLine));

    grid->attach(this);

    analogHistogram_ = new Histogram("", QColor(80, 180, 220, 150));
    //analogHistogram_->setValues(analogChannels_);
    analogHistogram_->attach(this);
}

void AnalogGraph::redrawAnalogGraph(QVector <double> values)
{
     analogHistogram_->setValues(values);
     replot();
}


