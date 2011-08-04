#ifndef DEFINES_H
#define DEFINES_H

//const int numberOfAnalogChannels = 2;
const int numberOfProximitySensors = 16;
const int sensorradius = 10;
const int timeoutdrawsens = 60;
const int timeoutconsole = 200;
const int timeoutanalog = 30;
const double colorparam = 0.498046875;
const double colorparam2 = 0.2490234375;
const int windowwidth = 500;
const int histwidth = 130;
const int buffer_size = 256;
const int numberOfDigitalInputs = 5;
const int numberOfDigitalOutputs = 5;

template <class X> X abs(X x)
{
    return ((x < 0)? -(x) : x);
}



#endif // DEFINES_H


