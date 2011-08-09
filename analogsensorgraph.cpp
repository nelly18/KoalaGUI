#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include <QtGui/QPen>

#include <qwt_scale_div.h>
#include <qwt_plot_grid.h>

#include "serialgate.h"
#include "analoghistogram.h"

#include "analogsensorgraph.h"

extern SerialGate sg;

AnalogGraph::AnalogGraph(QWidget *parent):QwtPlot(parent)
{
    analogTimer = new QTimer(this);
    connect(analogTimer, SIGNAL(timeout()),this, SLOT(analogTimeOut()));

    numberOfAnalogChannels_ = 6;
    analogChannels.resize(numberOfAnalogChannels_);
    analogChannels.fill(0);

    plotLayout()->setAlignCanvasToScales(true);

    QwtText textLeft("Analog value");
    QwtText textBottom("Analog channel");
    QFont *font = new QFont;
    font->setPointSize(12);
    font->setFamily("Arial");
    textLeft.setFont(*font);
    textBottom.setFont(*font);
    setAxisTitle(QwtPlot::yLeft, textLeft);
    setAxisTitle(QwtPlot::xBottom, textBottom);

    setAxisScale(QwtPlot::xBottom, 0, numberOfAnalogChannels_, 1);
    setAxisScale(QwtPlot::yLeft, 0, 1024, 200);

    QList<double> ticks[QwtScaleDiv::NTickTypes];
    for (int i = 0; i <= numberOfAnalogChannels_; i++)
        ticks[QwtScaleDiv::MajorTick] << i;

    QwtScaleDiv scaleDiv(
    ticks[QwtScaleDiv::MajorTick].first(),
    ticks[QwtScaleDiv::MajorTick].last(),
    ticks );

    setAxisScaleDiv(QwtPlot::xBottom, scaleDiv);

    populate();
    //resize(180, 200);
    replot(); // creating the legend items

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

    analogHistogram = new Histogram("", QColor(80, 180, 220, 150));
    analogHistogram->setValues(numberOfAnalogChannels_, analogChannels);
    analogHistogram->attach(this);


}

void AnalogGraph::analogTimeOut()
{
    if (loadAnalogValues())
    {
        analogHistogram->setValues(numberOfAnalogChannels_, analogChannels);
        replot();
    }
}

void AnalogGraph::setAnalogChannels(int channel, int value)
{
    analogChannels[channel] = value;
}

int AnalogGraph::loadAnalogValues()
{
    QString buff = "";
    const int numBytesToRead = 256;
    double value = 0.0;
    int bytesReaded = 0;
    for (int i = 0; i < numberOfAnalogChannels_; i++)
    {
        sg.send(QString("I,%1\n").arg(i));
        bytesReaded = sg.recv(buff, numBytesToRead);
        qDebug() << bytesReaded;
            value = buff.section(",", 1, 1).toDouble();
            qDebug() << value;
            analogChannels[i] = value;
            buff = "";
    }

return 1;
}

AnalogGraph::~AnalogGraph()
{

}

int AnalogGraph::numberOfAnalogChannels()
{
    return numberOfAnalogChannels_;
}
