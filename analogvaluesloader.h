#ifndef ANALOGVALUESLOADER_H
#define ANALOGVALUESLOADER_H

#include <QThread>

class AnalogValuesLoader : public QThread
{
public:
    AnalogValuesLoader();
protected:
    void run();
signals:
    void valuesChanged();
private:
    bool stoped_;
    QVector <double> values_;
    void loadAnalogValues();

};

#endif // ANALOGVALUESLOADER_H
