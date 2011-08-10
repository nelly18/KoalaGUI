#include <QtGui/QComboBox>
#include <QtGui/QPushButton>
#include <QtGui/QLayout>
#include <QtGui/QMessageBox>
#include <QtGui/QTextEdit>

#include "serialgate.h"
#include "script.h"

#include "scripttab.h"

extern SerialGate sg;

ScriptTab::ScriptTab(QWidget *parent)
    : QWidget(parent)
{
    scriptEdit_ = new QTextEdit;
    scriptEdit_->setFrameShape(QFrame::Panel);

    scriptKoala_ = new Script;
//    scriptKoala->moveToThread(&scriptThread);
//    scriptThread.start();

    QComboBox*  cb_readyScripts = new QComboBox;
    QStringList list;
    list << "Set speed" << "Bla1" << "Bla2" << "Bla3";
    cb_readyScripts->addItems(list);
    connect(cb_readyScripts, SIGNAL(activated(int)), SLOT(slotApplyCode(int)));
    slotApplyCode(0);

    QScriptValue scriptValueKoala = scriptEngine.newQObject(scriptKoala_);
    scriptEngine.globalObject().setProperty("koala", scriptValueKoala);

    QPushButton* pb_eval = new QPushButton("&Evaluate");
    connect(pb_eval, SIGNAL(clicked()), SLOT(slotEvaluate()));

    QGridLayout* grid = new QGridLayout;
    grid->addWidget(cb_readyScripts, 0, 1, 1, 1);
    grid->addWidget(scriptEdit_, 1, 0, 1, 3);
    grid->addWidget(pb_eval, 2, 1, 1, 1);
    setLayout(grid);
}


void ScriptTab::slotEvaluate()
{
    if (!sg.state) {
        QMessageBox::information (this, "", "Open serial port first");
        return;
    }

    const QScriptValue result = scriptEngine.evaluate(scriptEdit_->toPlainText());
    if (result.isError()) {
        QMessageBox::critical(0,
                              "Evaluating error",
                              result.toString(),
                              QMessageBox::Yes);
    } else {
        scriptKoala_->stop();
    }
}

void ScriptTab::slotApplyCode(int n)
{
    QString strCode;

    switch (n) {
        case 0:
            strCode = "koala.setSpeed(10, 10);\n"
                    "koala.forward(100);\n";
            break;
    }
    scriptEdit_->setPlainText(strCode);
}
