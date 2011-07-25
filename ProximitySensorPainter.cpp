
#include <QtGui>
#include "ProximitySensorPainter.h"
#include <QScrollArea>
#include <QTimer>
#include <QPoint>
#include <QFont>
#include <QLayout>

extern SerialGate sg;
ProximitySensorPainter::ProximitySensorPainter(QWidget *parent):QLabel(parent)
{
	drawSensorsTimer = new QTimer(this);
	connect(drawSensorsTimer, SIGNAL(timeout()), this, SLOT(TimeOut()));

	//this->setStyleSheet("background-image: url(:/res/koalaSkeleton.PNG);" "background-position: 0,0;" "background-repeat: no-repeat;");

	QVector <QPoint> points;
	points << QPoint(127, 17) << QPoint(97, 20) << QPoint(66, 28) << QPoint(40, 47)<<
			  QPoint(30, 109) << QPoint(30, 188) << QPoint(42, 254) << QPoint(104, 258) <<
			  QPoint(157, 17) << QPoint(188, 20) << QPoint(216, 28) << QPoint(242, 47) <<
			  QPoint(252, 108) << QPoint(252, 186) << QPoint(242, 254) << QPoint(178, 258);

	QLabel *l = new QLabel;
	l->setStyleSheet("background-image: url(:/res/koalaSkeleton.PNG);" "background-position: 0,0;" "background-repeat: no-repeat;");
	for(int i = 0; i < numberOfProximitySensors; i++)
	{
		Sensor *s = new Sensor(i, points.at(i), sensorradius, l);
		s->move (points.at(i));
		s->resize (10, 10);
		sensors << s;
	}
	table = new QTableWidget(8, 2, this);
	table->setStyleSheet("background-image: url(:/res/white.PNG);" "background-position: 0,0;");
	table->setGeometry(400, 5, 216, 262);
	table->setSelectionMode(QAbstractItemView::NoSelection);
	table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	table->setAutoScroll(false);
	table->setFrameShape(QFrame::NoFrame);
	QFont font;
	font.setPointSize(10);
	table->setFont(font);

	QStringList list = (QStringList()<< "Left side" << "Right side");
	table->setHorizontalHeaderLabels(list);
	for (int i = 0; i < numberOfProximitySensors; i++)
	{
		for (int j = 0; j < 2; j++)
			table->setItem(i, j, new QTableWidgetItem("0"));
	}

	QGridLayout *layout = new QGridLayout;
//    layout->setColumnMinimumWidth(0, 281);
	layout->addWidget(l, 0, 0);
//    layout->addWidget(table, 0, 1);
	setLayout(layout);

	colorPalette = 0;
}

ProximitySensorPainter::~ProximitySensorPainter()
{
	//delete drawSensorsTimer;
}

int ProximitySensorPainter::getSensorsValues()
{
	sg.Send("N\n");

	int rcv = 0;
	QString qBuf = "";
	rcv = sg.Recv(qBuf);
	if (!rcv) return 0;

	int num; QString sNum;
	for(int i = 0; i < numberOfProximitySensors; i++)
	{
		sNum = qBuf.section(",", i + 1, i + 1);
		num = sNum.toInt();
		sensors[i]->setSensorValue(num);
	}

return 1;
}

void ProximitySensorPainter::TimeOut()
{
	if (!sg.state) return;

	if (!getSensorsValues()) return;

	for(int i = 0; i < numberOfProximitySensors; i++)
	{
		sensors[i]->evaluateColor(colorPalette);
	}
	for (int i = 0, k = 0; i < 2; i++)
	{
		for (int j = 0; j < numberOfProximitySensors / 2; j++, k++)
		{
			QTableWidgetItem *item = table->item(j, i);
			item->setText(QString("%1").arg(sensors[k]->getSensorValue()));
			sensors[k]->update();
		}
	}
	//update();
}

void ProximitySensorPainter::setColorPalette(int palette)
{
	colorPalette = palette;
}

//void ProximitySensorPainter::paintEvent(QPaintEvent *)
//{
//    QPainter painter(this);
//    QStyleOption opt;
//    opt.init(this);
//    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
//    painter.setRenderHint(QPainter::Antialiasing);

//    QPen pen(Qt::NoPen);
//    painter.setPen(pen);
//    QBrush brush(Qt::SolidPattern);

//    int r;
//    QPoint c;
//    QColor col;

//    for(int i = 0; i < numberOfProximitySensors; i++)
//    {
//        c = sensors.at(i)->getCenter();
//        r = sensors.at(i)->getRadii();
//        col = sensors.at(i)->getColor();

//        brush.setColor(col);
//        painter.setBrush(brush);
//        painter.drawEllipse(c, r, r);
//    }
//}
