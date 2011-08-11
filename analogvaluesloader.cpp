#include "serialgate.h"

#include "analogvaluesloader.h"

AnalogValuesLoader::AnalogValuesLoader (int numberOfAnalogChannels, QObject *parent)
    : QThread (parent), stoped_ (true)
{
    values_.resize (numberOfAnalogChannels);
}

void AnalogValuesLoader::run()
{
    stoped_ = false;

    while (!stoped_) {
        loadAnalogValues ();
        emit valuesChanged (values_);
        sleep (timeOutAnalog);
    }
}

void AnalogValuesLoader::loadAnalogValues()
{
    const int numBytesToRead = 256;
    double value = 0.0;
    int i = 0;
    for (QVector<double>::iterator it = values_.begin (),
         end = values_.end (); it != end; ++it, ++i) {
        SerialGate::instance()->send(QString("I,%1\n").arg(i));
        const QString buff = SerialGate::instance()->recv(numBytesToRead);
        value = buff.section(",", 1, 1).toDouble();
        *it = value;
    }
}
