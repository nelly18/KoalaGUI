#ifndef SCRIPTTAB_H
#define SCRIPTTAB_H

#include <QtScript/QScriptEngine>

#include <QtGui/QWidget>

class Script;
class QTextEdit;

class ScriptTab : public QWidget
{
    Q_OBJECT

public:
    explicit ScriptTab(QWidget *parent = 0);

public slots:
    void slotApplyCode(int);
    void slotEvaluate();

private:
    Script  *scriptKoala_;
    QTextEdit *scriptEdit_;
    //QThread scriptThread;
    QScriptEngine scriptEngine;
};

#endif // SCRIPTTAB_H
