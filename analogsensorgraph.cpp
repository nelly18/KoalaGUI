#include <QtCore/QDebug>
#include <QtCore/QTimer>

#include <QtGui/QPen>

#include <qwt_scale_div.h>
#include <qwt_plot_grid.h>

#include "serialgate.h"
#include "analoghistogram.h"

#include "analogsensorgraph.h"

//extern SerialGate serialGate;

AnalogGraph::AnalogGraph(QWidget *parent)
    : QwtPlot(parent), numberOfAnalogChannels_ (6)
{
    analogTimer_ = new QTimer(this);
    connect(analogTimer_, SIGNAL(timeout()),this, SLOT(analogTimeOut()));

    analogChannels_.fill(0, numberOfAnalogChannels_);

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
    //resize(180, 200);
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
    analogHistogram_->setValues(numberOfAnalogChannels_, analogChannels_);
    analogHistogram_->attach(this);
}

void AnalogGraph::analogTimeOut()
{
    if (loadAnalogValues()) {
        analogHistogram_->setValues(numberOfAnalogChannels_, analogChannels_);
        replot();
    }
}

void AnalogGraph::setAnalogChannels(int channel, int value)
{
    analogChannels_[channel] = value;
}

int AnalogGraph::loadAnalogValues()
{
    QString buff;
    const int numBytesToRead = 256;
    double value = 0.0;
    int bytesReaded = 0;
    for (int i = 0; i < numberOfAnalogChannels_; ++i) {
        SerialGate::instance()->send(QString("I,%1\n").arg(i));
        bytesReaded = SerialGate::instance()->recv(buff, numBytesToRead);
        qDebug() << bytesReaded;
        value = buff.section(",", 1, 1).toDouble();
        qDebug() << value;
        analogChannels_[i] = value;
        buff.clear ();
    }

    return 1;
}
