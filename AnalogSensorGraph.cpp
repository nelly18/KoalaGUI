#include "AnalogSensorGraph.h"
extern SerialGate sg;


AnalogGraph::AnalogGraph(QWidget *parent):QwtPlot(parent)
{
	analogTimer = new QTimer(this);
	connect(analogTimer, SIGNAL(timeout()),this, SLOT(analogTimeOut()));

	numberOfAnalogChannels = 2;
	analogChannels.resize(numberOfAnalogChannels);
	analogChannels.fill(0);

	plotLayout()->setAlignCanvasToScales(true);

//    setAxisTitle(QwtPlot::yLeft, "Analog value");
//    setAxisTitle(QwtPlot::xBottom, "Analog channel");

	setAxisScale(QwtPlot::xBottom, 0, numberOfAnalogChannels, 1);
	setAxisScale(QwtPlot::yLeft, 0, 1024, 200);

	QList<double> ticks[QwtScaleDiv::NTickTypes];
	for (int i = 0; i <= numberOfAnalogChannels; i++)
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
	analogHistogram->setValues(numberOfAnalogChannels, analogChannels);
	analogHistogram->attach(this);


}

void AnalogGraph::analogTimeOut()
{
	if (getAnalogValues())
	{
		analogHistogram->setValues(numberOfAnalogChannels, analogChannels);
		replot();
	}
}

void AnalogGraph::setAnalogChannels(int channel, int value)
{
	analogChannels[channel] = value;
}

int AnalogGraph::getAnalogValues()
{
	QString buff = "";
	int rcv = 0;
	for (int i = 0; i < numberOfAnalogChannels; i++)
	{
		sg.Send(QString("I,%1\n").arg(i));
		//Sleep(3000);
		rcv = sg.Recv(buff);

		if (!rcv) return 0;

		setAnalogChannels(i, buff.section(",", 1, 1).toDouble());
		rcv = 0;
		buff = "";
	}

return 1;
}

void AnalogGraph::setnumberOfAnalogChannels(int n)
{
	numberOfAnalogChannels = n;
}
AnalogGraph::~AnalogGraph()
{
	//delete[] analogChannels;
}
