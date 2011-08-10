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
        sensors_ << s;
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
//    layout->setSpacing(0);
//    layout->setColumnMinimumWidth(0, 281);
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
    SerialGate::instance()->send("N\n");

    QString buff;
    const int numBytesToRead = 256;
    SerialGate::instance()->recv(buff, numBytesToRead);

    int num = 0;
    QString sNum;
    for(int i = 0; i < numberOfProximitySensors; ++i) {
        sNum = buff.section(",", i + 1, i + 1);
        num = sNum.toInt();
        sensors_[i]->setSensorValue(num);
    }

    return 1;
}

void ProximitySensorPainter::proximitySensorTimeOut()
{
    if (!SerialGate::instance()->state || !loadSensorsValues()) {
        return;
    }

    for(int i = 0; i < numberOfProximitySensors; ++i) {
        sensors_.at(i)->evaluateColor(colorPalette_);
    }

    for (int i = 0, k = 0; i < 2; ++i) {
        for (int j = 0; j < numberOfProximitySensors / 2; ++j, ++k) {
            QTableWidgetItem *item = table_->item(j, i);
            item->setText(QString("%1").arg(sensors_.at(k)->sensorValue()));
            sensors_.at(k)->update();
        }
    }
    //update();
}

void ProximitySensorPainter::setColorPalette(int palette)
{
    colorPalette_ = palette;
}

void ProximitySensorPainter::resetSensorsColor()
{
    for(int i = 0; i < numberOfProximitySensors; ++i) {
        sensors_.at(i)->setColor(QColor(220, 220, 220));
    }

    update();
}
