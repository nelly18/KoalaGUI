#include <QtGui/QPalette>

#include "analoghistogram.h"

Histogram::Histogram(const QString &title, const QColor &symbolColor)
    : QwtPlotHistogram(title)
{
    setStyle(QwtPlotHistogram::Columns);
    setColor(symbolColor);
}

void Histogram::setColor(const QColor &symbolColor)
{
    setPen(QPen(Qt::black));
    setBrush(symbolColor);

    QwtColumnSymbol *symbol = new QwtColumnSymbol(QwtColumnSymbol::Box);
    symbol->setFrameStyle(QwtColumnSymbol::Raised);
    symbol->setLineWidth(2);
    symbol->setPalette(symbolColor);
    setSymbol(symbol);
}

void Histogram::setValues(int numValues, const QVector<double> &values)
{
    QVector<QwtIntervalSample> samples(numValues);
    for ( int i = 0; i < numValues; i++ )
    {
        QwtInterval interval(double(i), i + 1.0);
        interval.setBorderFlags(QwtInterval::ExcludeMaximum);
        samples[i] = QwtIntervalSample(values[i], interval);
    }

    setData(new QwtIntervalSeriesData(samples));
}
