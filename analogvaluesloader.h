#ifndef ANALOGVALUESLOADER_H
#define ANALOGVALUESLOADER_H

#include <QtCore/QThread>
#include <QtCore/QVector>

typedef QVector < double > MyVector;

class AnalogValuesLoader : public QThread
{
    Q_OBJECT

public:
    explicit AnalogValuesLoader (int numberOfAnalogChannels, QObject *parent = 0);
    virtual ~AnalogValuesLoader ()
    {}

    void stop () {
        stoped_ = true;
    }

signals:
    void valuesChanged (const MyVector &values);

protected:
    void run();

private:
    void loadAnalogValues();

private:
    bool stoped_;
    MyVector values_;

};

#endif // ANALOGVALUESLOADER_H
