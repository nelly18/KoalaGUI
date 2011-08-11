#include <QtCore/QTimer>
#include <QtCore/QPoint>

#include <QtGui/QScrollArea>
#include <QtGui/QFont>
#include <QtGui/QLayout>
#include <QtGui/QTableWidget>

#include "sensor.h"
#include "serialgate.h"

#include "proximitysensorpainter.h"

//extern SerialGate serialGate;

ProximitySensorPainter::ProximitySensorPainter(QWidget *parent):QLabel(parent)
{
    drawSensorsTimer_ = new QTimer(this);
    connect(drawSensorsTimer_, SIGNAL(timeout()), this, SLOT(proximitySensorTimeOut()));

    QVector <QPoint> points;
    points << QPoint(117, 7) << QPoint(87, 10) << QPoint(56, 18)
           << QPoint(30, 37) << QPoint(20, 99) << QPoint(20, 178)
           << QPoint(32, 244) << QPoint(94, 248) << QPoint(147, 7)
           << QPoint(178, 10) << QPoint(206, 18) << QPoint(232, 37)
           << QPoint(242, 98) << QPoint(242, 176) << QPoint(232, 244)
           << QPoint(168, 248);

    QLabel *l = new QLabel(this);

    l->setStyleSheet("background-image: url(:/res/koalaSkeleton.PNG);" "background-position: 0, 0;" "background-repeat: no-repeat;");

    for(int i = 0; i < numberOfProximitySensors; ++i) {
        Sensor *s = new Sensor(i, l);
        s->move (points.at(i));
        s->resize (20, 20);
        sensors_.push_back(s);
    }

    table_ = new QTableWidget(8, 2, this);
    table_->setStyleSheet("background-image: url(:/res/white.PNG);" "background-position: 0,0;");
    table_->setGeometry(400, 5, 216, 262);
    table_->setSelectionMode(QAbstractItemView::NoSelection);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table_->setAutoScroll(false);
    table_->setFrameShape(QFrame::NoFrame);

    QFont font;
    font.setPointSize(10);
    table_->setFont(font);

    QStringList list;
    list << "Left side" << "Right side";
    table_->setHorizontalHeaderLabels(list);

    for (int i = 0; i < numberOfProximitySensors; ++i) {
        for (int j = 0; j < 2; ++j) {
            table_->setItem(i, j, new QTableWidgetItem("0"));
        }
    }

    //QGroupBox *group = new QGroupBox(this);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(l, 0, 0);
    //layout->addWidget(table, 0, 1);

    setLayout(layout);

    colorPalette_ = 0;
}

ProximitySensorPainter::~ProximitySensorPainter()
{
    //delete drawSensorsTimer;
}

int ProximitySensorPainter::loadSensorsValues()
{
    //static const QRegExp re (n(,\\d*){16}\\n);
    SerialGate::instance()->send("N\n");
    const int numBytesToRead = 256;
    QString buff = SerialGate::instance()->recv(numBytesToRead);

    int num = 0;
    QString sNum;
    int i = 0;
    for(QVector <Sensor *> :: iterator it = sensors_.begin(),
                                     end = sensors_.end(); it != end; ++it) {
        sNum = buff.section(",", i + 1, i + 1);
        num = sNum.toInt();
        (*it)->setSensorValue(num);
        ++i;
    }
    return 1;
}

void ProximitySensorPainter::proximitySensorTimeOut()
{
    if (!SerialGate::instance()->state || !loadSensorsValues()) {
        return;
    }

    for(QVector <Sensor *> :: iterator it = sensors_.begin(),
                                     end = sensors_.end(); it != end; ++it) {
        (*it)->evaluateColor(colorPalette_);
    }

    QVector <Sensor *> :: iterator it = sensors_.begin();
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < numberOfProximitySensors / 2; ++j, ++it) {
            QTableWidgetItem *item = table_->item(j, i);
            item->setText(QString("%1").arg((*it)->sensorValue()));
            (*it)->update();
        }
    }
}

void ProximitySensorPainter::setColorPalette(int palette)
{
    colorPalette_ = palette;
}

void ProximitySensorPainter::resetSensorsColor()
{
    for(QVector <Sensor *> :: iterator it = sensors_.begin(),
                                     end = sensors_.end(); it != end; ++it) {
        (*it)->setColor(QColor(220, 220, 220));
    }
    update();
}
