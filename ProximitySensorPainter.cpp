
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

    QVector <QPoint> points;
    points << QPoint(117, 7) << QPoint(87, 10) << QPoint(56, 18) << QPoint(30, 37)<<
              QPoint(20, 99) << QPoint(20, 178) << QPoint(32, 244) << QPoint(94, 248) <<
              QPoint(147, 7) << QPoint(178, 10) << QPoint(206, 18) << QPoint(232, 37) <<
              QPoint(242, 98) << QPoint(242, 176) << QPoint(232, 244) << QPoint(168, 248);

    QLabel *l = new QLabel(this);

    l->setStyleSheet("background-image: url(:/res/koalaSkeleton.PNG);" "background-position: 0, 0;" "background-repeat: no-repeat;");

    for(int i = 0; i < numberOfProximitySensors; i++)
    {
        Sensor *s = new Sensor(i, l);
        s->move (points.at(i));
        s->resize (20, 20);
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

    //QGroupBox *group = new QGroupBox(this);


    QGridLayout *layout = new QGridLayout;
//    layout->setSpacing(0);
//    layout->setColumnMinimumWidth(0, 281);
    layout->addWidget(l, 0, 0);
    //layout->addWidget(table, 0, 1);

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

    QString buff = "";
    const int numBytesToRead = 256;
    sg.Recv(buff, numBytesToRead);

    int num; QString sNum;
    for(int i = 0; i < numberOfProximitySensors; i++)
    {
        sNum = buff.section(",", i + 1, i + 1);
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
        sensors.at(i)->evaluateColor(colorPalette);
    }
    for (int i = 0, k = 0; i < 2; i++)
    {
        for (int j = 0; j < numberOfProximitySensors / 2; j++, k++)
        {
            QTableWidgetItem *item = table->item(j, i);
            item->setText(QString("%1").arg(sensors.at(k)->getSensorValue()));
            sensors.at(k)->update();
        }
    }
    //update();
}

void ProximitySensorPainter::setColorPalette(int palette)
{
    colorPalette = palette;
}

void ProximitySensorPainter::resetSensorsColor()
{
    for(int i = 0; i < numberOfProximitySensors; ++i)
    {
        sensors.at(i)->setColor(QColor(220, 220, 220));
    }
    update();
}
