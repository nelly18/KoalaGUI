#ifndef ANALOGVALUESLOADER_H
#define ANALOGVALUESLOADER_H

#include <QtCore/QThread>
#include <QtCore/QVector>

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
    void valuesChanged(const QVector <double> &values);

protected:
    void run();

private:
    void loadAnalogValues();

private:
    bool stoped_;
    QVector <double> values_;

};

#endif // ANALOGVALUESLOADER_H
