#include "batterycharge.h"

BatteryCharge::BatteryCharge()
{
    setStyleSheet("QProgressBar::chunk {"
                  "background: QLinearGradient( x1: 0, y1: 1, x2: 0, y2: 1,"
                                                "stop: 0 #78d,"
                                                "stop: 0.4999 #46a,"
                                                "stop: 0.5 #45a,"
                                                "stop: 1 #238 );"
                  "border-bottom-right-radius: 7px;"
                  "border-top-right-radius: 7px;"
                  "border: 1px solid black;"
                  "}");
    setValue(100);
}
