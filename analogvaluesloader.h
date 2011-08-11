#ifndef ANALOGVALUESLOADER_H
#define ANALOGVALUESLOADER_H

#include <QtCore/QThread>
#include <QtCore/QVector>

class AnalogValuesLoader : public QThread
{
    Q_OBJECT

public:
    AnalogValuesLoader();
protected:
    void run();
signals:
    void valuesChanged(QVector <double> values);
private:
    bool stoped_;
    QVector <double> values_;
    void loadAnalogValues();

};

#endif // ANALOGVALUESLOADER_H
