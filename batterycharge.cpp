#include <QtCore/QTimer>
#include <QtCore/QRegExp>
#include <QtCore/QDebug>

#include "serialgate.h"

#include "batterycharge.h"

//extern SerialGate serialGate;

BatteryCharge::BatteryCharge(QWidget *parent)
    : QProgressBar(parent)
{
    setStyleSheet( "QProgressBar {"
                   "border: 1px solid gray;"
                   "padding: 1px;"
                   "text-align: center;"
                   "border-bottom-right-radius: 7px;"
                   "border-top-right-radius: 7px;"
                   "}"
                  );
    batteryChargeTimer_ = new QTimer(this);
    connect(batteryChargeTimer_, SIGNAL(timeout()), this, SLOT(batteryChargeTimerTimeOut()));
}
void BatteryCharge::batteryChargeTimerTimeOut()
{
    static const QRegExp re ("s,(\\d*)\\n");
    SerialGate::instance()->send(QString("S\n"));
    const int numBytesToRead = 10;
    QString buff = SerialGate::instance()->recv(numBytesToRead);
    int batteryLevel = 0;
    if(re.exactMatch(buff)){
        batteryLevel = re.cap(1).toInt();
    }
    else{
        return;
    }

    const double colorSection = 4.66666666666;
    QString batteryColor;

    if (batteryLevel < colorSection) {
        batteryColor = "stop: 0 #f00, stop: 0.4999 #e00, stop: 0.5 #d00, stop: 1 #e00";
    } else if (batteryLevel < colorSection * 2) {
        batteryColor = "stop: 0 #ff0, stop: 0.4999 #ee0, stop: 0.5 #dd0, stop: 1 #ee0";
    } else {
        batteryColor = "stop: 0 #0f0, stop: 0.4999 #0e0, stop: 0.5 #0d0, stop: 1 #0e0";
    }

    QString cssQProgressBar = "QProgressBar{"
               "border: 1px solid gray;"
               "padding: 1px;"
               "text-align: center;"
               "border-bottom-right-radius: 7px;"
               "border-top-right-radius: 7px;"
               "}"
               "QProgressBar::chunk {"
               "border-bottom-right-radius: 7px;"
               "border-top-right-radius: 7px;"
               + QString("background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, %1);").arg(batteryColor)
               + "}";

    setStyleSheet(cssQProgressBar);
    const int batteryValue = 100 * batteryLevel / 14;
    setValue(batteryValue);
}

//class MyClass {
//MyClass (QStatusBar *statusBar = 0) : bar_ (statusBar) {
//  if (bar_) {
// prepareStatusBar ();
//}
//}


//QStatusBar *statusBar () const {
//  return bar_;
//}
//void setStatusBar (QStatusBar *statusBar) {
//  bar_ = statusBar;
//  prepareStatusBar ();
//}

//private:
//  void prepareStatusBar () {
//    SomeWidget *w;
//    bar_->addWidget (w);
//  }
//private:
//  QStatusBar *bar_;

//}
