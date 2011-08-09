#ifndef SCRIPTTAB_H
#define SCRIPTTAB_H

#include <QtCore/QThread>

#include <QtScript/QtScript>

#include <QtGui/QTextEdit>

#include "script.h"

class ScriptTab : public QWidget
{
    Q_OBJECT
public:
    explicit ScriptTab(QWidget *parent = 0);

protected:


private:
    Script  *scriptKoala;
    QTextEdit *te_script;
    //QThread scriptThread;
    QScriptEngine scriptEngine;
signals:

public slots:
    void slotApplyCode(int);
    void slotEvaluate();
};

#endif // SCRIPTTAB_H
