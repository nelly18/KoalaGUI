#include <QtGui/QPalette>

#include "analoghistogram.h"

Histogram::Histogram (const QString &title, const QColor &symbolColor)
    : QwtPlotHistogram (title)
{
    setStyle (QwtPlotHistogram::Columns);
    setColor (symbolColor);
}

void Histogram::setColor (const QColor &symbolColor)
{
    setPen (QPen (Qt::black));
    setBrush (symbolColor);

    QwtColumnSymbol *symbol = new QwtColumnSymbol (QwtColumnSymbol::Box);
    symbol->setFrameStyle (QwtColumnSymbol::Raised);
    symbol->setLineWidth (2);
    symbol->setPalette (symbolColor);
    setSymbol (symbol);
}

void Histogram::setValues (const QVector<double> &values)
{
    QVector<QwtIntervalSample> samples;
    int i = 0;

    for (QVector<double>::const_iterator it = values.constBegin(), end = values.constEnd(); it != end; ++it, ++i) {
        QwtInterval interval (double (i), i + 1.0);
        interval.setBorderFlags (QwtInterval::ExcludeMaximum);
        samples.push_back (QwtIntervalSample (*it, interval));
    }

    setData (new QwtIntervalSeriesData (samples));
}
