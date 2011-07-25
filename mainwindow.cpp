#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTimer>
#include <QDebug>
#include <QKeyEvent>
#include <QTextBlock>
#include <QColor>
#include <QLayout>
#include <QSpacerItem>

SerialGate sg;



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);    

    ui -> teConsole -> installEventFilter(this);

    consoleTimer = new QTimer(this);
    connect(consoleTimer, SIGNAL(timeout()), this, SLOT(TimeOut()));

    //analogFrame = new AnalogGraph(this);

    QString label("Sensors");
    sensorFrame = new ProximitySensorPainter;
    ui->tabWidget->addTab(sensorFrame, label);

//    QHBoxLayout *analogLayout = new  QHBoxLayout();
//    const int space = (windowwidth - numberOfAnalogChannels * histwidth)/2;
//    analogLayout->addSpacerItem(new QSpacerItem(space - 30, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
//    analogLayout->addWidget (analogFrame);
//    analogLayout->addSpacerItem(new QSpacerItem(space + 30, 20, QSizePolicy::Fixed, QSizePolicy::Fixed));
//    QWidget *analogTab = new QWidget();
//    analogTab->setLayout(analogLayout);

    label = "I/O signals";
    inOutTab = new InputsOutputsTab;
    ui->tabWidget->addTab(inOutTab, label);

    speedControlTab = new SpeedControl(this);
    ui->tabWidget->addTab(speedControlTab, "Speed");

    PIDTab = new PIDRegulator;
    ui->tabWidget->addTab(PIDTab, "PID");
}

MainWindow::~MainWindow()
{
    //delete sensorFrame;
    delete ui;
}
void MainWindow::on_changeTab()
{
    if (!sg.state) return;
    Tabs tab = (Tabs)ui->tabWidget->currentIndex();

    switch(tab)
    {
        case console:
            sensorFrame->drawSensorsTimer->stop();
            inOutTab->analogFrame->analogTimer->stop();
            //analogFrame->analogTimer->stop();
            consoleTimer->start(timeoutconsole);
            break;

        case script:
            break;

        case proximityS:
            consoleTimer->stop();
            //analogFrame->analogTimer->stop();
            inOutTab->analogFrame->analogTimer->stop();
            sensorFrame->drawSensorsTimer->start(timeoutdrawsens);
            break;

        case analogS:
            sensorFrame->drawSensorsTimer->stop();
            consoleTimer->stop();
            //analogFrame->analogTimer->start(timeoutanalog);
            inOutTab->analogFrame->analogTimer->start(timeoutanalog);
    }

}

void MainWindow::on_openButton_clicked()
{
    int port = ui-> cbPort ->currentIndex() + 1;
    ui -> teConsole -> setTextColor(QColor(0, 153, 0));
    QString message = "";
    if (sg.state)
    {
        sensorFrame->drawSensorsTimer->stop();
        consoleTimer->stop();
        //analogFrame->analogTimer->stop();
        inOutTab->analogFrame->analogTimer->stop();

        sg.Close();

        ui -> openButton -> setText("Open port");   
        message = QString("Serial port COM%1 closed\n").arg(port);
        ui -> teConsole -> insertPlainText(message);

        return;
    }

    QString qsSpeed = ui -> cbSpeed -> currentText();
    int speed = qsSpeed.section(":", 1).toInt();

    if (sg.Open(port, speed))
    {
        message = QString("Serial port COM%1 opened\n").arg(port);
        ui -> openButton -> setText("Close port");
        ui -> teConsole -> setFocus();

        Tabs tab = (Tabs)ui->tabWidget->currentIndex();

        switch (tab)
        {
        case console:
            consoleTimer-> start(timeoutconsole);
            break;
        case script:
            break;
        case proximityS:
            sensorFrame->drawSensorsTimer->start(timeoutdrawsens);
            break;
        case analogS:
            //analogFrame->analogTimer->start(timeoutanalog);
            inOutTab->analogFrame->analogTimer->start(timeoutanalog);
            break;
        }

    }
    else
    {
        ui -> teConsole -> setTextColor(QColor(200, 0, 0));
        message = QString("Serial port COM%1 openning error\n").arg(port);
    }
    ui -> teConsole -> insertPlainText(message);
    ui -> teConsole -> setTextColor(Qt::black);
}

void MainWindow::TimeOut(void)
{
    QString buff = "";

    int rcv = sg.Recv(buff);
        if(rcv > 0)
        {
            ui -> teConsole -> setTextColor(QColor(255,0,255));
            ui -> teConsole -> insertPlainText(buff);
        }
      ui -> teConsole -> setTextColor(Qt::black);
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{

    static QVector <QString> commands;
    static int position = 0;
    static bool keydown = false;
    if ((obj == ui -> teConsole) && (event->type() == QEvent::KeyPress))
    {
        QKeyEvent *keyEvent = (QKeyEvent*)event;
        if (keyEvent->key() == Qt::Key_Return)
        {
            int count = ui->teConsole->document()->blockCount();
            QTextBlock tb = ui->teConsole->document() -> findBlockByNumber(count - 1);

            QString qBuf = tb.text();

            sg.Send(QString("%1\n").arg(qBuf));

            if (commands.size())
            {
                if (qBuf != commands.first())
                    commands.prepend(qBuf);
            }
            else
                commands.prepend(qBuf);

            position = 0;
        }
        else if ((keyEvent->key() == Qt::Key_Up) && (commands.size()))
        {
            QTextCursor cur(ui->teConsole->document());
            cur.movePosition(QTextCursor::End);
            cur.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
            cur.removeSelectedText();
            ui -> teConsole -> setTextColor(Qt::black);

            if (keydown)
            {
                position++;
                keydown = false;
            }
            ui->teConsole->insertPlainText(commands[position]);
            if (position < commands.size() - 1) position++;

            return true;
        }
        else if ((keyEvent->key() == Qt::Key_Down) && (commands.size()))
        {
            QTextCursor cur(ui->teConsole->document());
            cur.movePosition(QTextCursor::End);
            cur.movePosition(QTextCursor::StartOfLine, QTextCursor::KeepAnchor);
            cur.removeSelectedText();
            ui -> teConsole -> setTextColor(Qt::black);

            if (position > 0) position--;
            ui->teConsole->insertPlainText(commands[position]);
            keydown = true;

            return true;
        }
    }
     return false;
 }

void MainWindow::on_actionClearConsole_triggered()
{
     ui->teConsole->clear();
}

void MainWindow::on_actionQuit_triggered()
{
     QApplication::quit();
}


void MainWindow::on_actionColor_palette_triggered()
{
    if (colorDialog.exec() == QDialog::Accepted)
    {
        sensorFrame->setColorPalette(colorDialog.getPalette());
    }
}

void MainWindow::on_actionTimeouts_triggered()
{

}
