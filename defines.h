#ifndef DEFINES_H
#define DEFINES_H

//const int numberOfAnalogChannels = 2;
const int numberOfProximitySensors = 16;
const int timeOutDrawSens = 60;
const int timeOutConsole = 5000;
const int timeOutAnalog = 30;
const int timeOutBatteryCharge = 5000;
const double colorParam = 0.498046875;
const double colorParam2 = 0.2490234375;
const int buffSize = 256;
const int numberOfDigitalInputs = 5;
const int numberOfDigitalOutputs = 5;

template <class X> X abs(X x)
{
    return ((x < 0)? -(x) : x);
}



#endif // DEFINES_H


