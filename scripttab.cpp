#include "scripttab.h"
#include <QComboBox>
#include <QPushButton>
#include <QLayout>
#include <QMessageBox>
#include <SerialGate.h>

extern SerialGate sg;

ScriptTab::ScriptTab(QWidget *parent) : QWidget(parent)
{
    te_script = new QTextEdit;
    te_script->setFrameShape(QFrame::Panel);

    scriptKoala = new Script;
//    scriptKoala->moveToThread(&scriptThread);
//    scriptThread.start();

    QComboBox*  cb_readyScripts = new QComboBox;
    QStringList list;
    list << "Set speed" << "Bla1" << "Bla2" << "Bla3";
    cb_readyScripts->addItems(list);
    connect(cb_readyScripts, SIGNAL(activated(int)), SLOT(slotApplyCode(int)));
    slotApplyCode(0);

    QScriptValue scriptValueKoala = scriptEngine.newQObject(scriptKoala);
    scriptEngine.globalObject().setProperty("koala", scriptValueKoala);

    QPushButton* pb_eval = new QPushButton("&Evaluate");
    connect(pb_eval, SIGNAL(clicked()), SLOT(slotEvaluate()));

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(cb_readyScripts, 0, 1, 1, 1);
    grid->addWidget(te_script, 1, 0, 1, 3);
    grid->addWidget(pb_eval, 2, 1, 1, 1);
    setLayout(grid);
}


void ScriptTab::slotEvaluate()
{
    if (!sg.state)
    {
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setText("Open serial port first");
        msgBox.exec();
        return;
    }

    QScriptValue result = scriptEngine.evaluate(te_script->toPlainText());
    if (result.isError()) {
        QMessageBox::critical(0,
                              "Evaluating error",
                              result.toString(),
                              QMessageBox::Yes
                             );
    }
    else
        scriptKoala->stop();
}

void ScriptTab::slotApplyCode(int n)
{
    QString strCode;
    switch (n) {
    case 0:
        strCode = "koala.setSpeed(10, 10);\n";
        break;


    }
    te_script->setPlainText(strCode);
}
