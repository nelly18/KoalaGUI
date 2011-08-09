#include <QtGui/QMessageBox>
#include <QtCore/QTimer>
#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>
#include <QtGui/QTextBlock>
#include <QtGui/QColor>
#include <QtGui/QLayout>
#include <QtGui/QSpacerItem>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QThread>

#include "proximitysensorpainter.h"
#include "analogsensorgraph.h"
#include "speedcontrol.h"
#include "pidregulator.h"
#include "inputsoutputstab.h"
#include "console.h"
#include "statusbarwidget.h"
#include "scripttab.h"
#include "sensor.h"
#include "serialgate.h"
#include "batterycharge.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"

SerialGate sg;


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    consoleTab = new Console(this);
    connect(consoleTab, SIGNAL(onCommand(QString)), this, SLOT(newCommand(QString)));
    ui->tabWidget->addTab(consoleTab, "Console");

    scriptTab = new ScriptTab;
    ui->tabWidget->addTab(scriptTab, "Script");
//    QThread scriptThread;
//    scriptTab->moveToThread(&scriptThread);
//    scriptThread.start();

    consoleTimer = new QTimer(this);
    connect(consoleTimer, SIGNAL(timeout()), this, SLOT(TimeOut()));

    sensorFrame = new ProximitySensorPainter(this);
    ui->tabWidget->addTab(sensorFrame, "Sensors");

    inOutTab = new InputsOutputsTab(this);
    connect(ui->openButton, SIGNAL(clicked()), inOutTab, SLOT(openPortButtonClicked()));
    ui->tabWidget->addTab(inOutTab, "I/O signals");

    speedControlTab = new SpeedControl(this);
    ui->tabWidget->addTab(speedControlTab, "Speed");

    PIDTab = new PIDRegulator;
    ui->tabWidget->addTab(PIDTab, "PID");

    statusBarWidget = new StatusBarWidget(this);
    //ui->statusBar->addWidget(statusBarWidget, 1);
    setStatusBar(statusBarWidget->statusBar);
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
            inOutTab->manualTimer->stop();
            consoleTimer->start(timeoutconsole);
            break;

        case script:
            sensorFrame->drawSensorsTimer->stop();
            inOutTab->analogFrame->analogTimer->stop();
            consoleTimer->stop();
            break;

        case proximityS:
            consoleTimer->stop();
            inOutTab->analogFrame->analogTimer->stop();
            sensorFrame->drawSensorsTimer->start(timeoutdrawsens);
            break;

        case analogS:
            sensorFrame->drawSensorsTimer->stop();
            consoleTimer->stop();
            inOutTab->analogFrame->analogTimer->start(timeoutanalog);
            break;
        case speed:
            sensorFrame->drawSensorsTimer->stop();
            inOutTab->analogFrame->analogTimer->stop();
            consoleTimer->stop();
            break;
        case PID:
            sensorFrame->drawSensorsTimer->stop();
            inOutTab->analogFrame->analogTimer->stop();
            consoleTimer->stop();
            break;
    }

}

void MainWindow::on_openButton_clicked()
{
    const int port = ui-> cbPort ->currentIndex() + 1;

    QString message;
    if (sg.state)
    {
        sensorFrame -> drawSensorsTimer -> stop();
        consoleTimer -> stop();
        inOutTab -> analogFrame->analogTimer->stop();
        statusBarWidget->charge->batteryChargeTimer->stop();

        sg.Close();

        ui -> openButton -> setText("Open port");
        message = QString("Serial port COM%1 closed").arg(port);
        consoleTab->output(message);
        consoleTab->isLocked = true;

        sensorFrame->resetSensorsColor();

        return;
    }

    const QString qsSpeed = ui -> cbSpeed -> currentText();
    const int speed = qsSpeed.section(":", 1).toInt();

    if (sg.Open(port, speed))
    {
        message = QString("Serial port COM%1 opened").arg(port);
        consoleTab->isLocked = false;
        ui -> openButton -> setText("Close port");

        readPIDSettings();

        statusBarWidget->charge->batteryChargeTimer->start(3000);

        switch (ui->tabWidget->currentIndex())
        {
        case console:
            //consoleTimer-> start(timeoutconsole);
            break;
        case script:
            break;
        case proximityS:
            sensorFrame->drawSensorsTimer->start(timeoutdrawsens);
            break;
        case analogS:
            inOutTab->analogFrame->analogTimer->start(timeoutanalog);
            break;
        }

    }
    else
    {
        message = QString("Serial port COM%1 openning error").arg(port);
        consoleTab->isLocked = true;
    }

    consoleTab->output(message);

}

void MainWindow::TimeOut(void)
{
    QString buff;

    if(sg.Recv(buff, 256))
        consoleTab->output(buff);

}

void MainWindow::on_actionClearConsole_triggered()
{

     consoleTab->clear();
     consoleTab->insertPrompt(false);
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
void MainWindow::newCommand(QString command)
{
    sg.Send(QString("%1\n").arg(command));
    consoleTab->insertPrompt();
}

void MainWindow::readPIDSettings()
{
    QFile file("PIDsettings.txt");
    if (!file.open (QFile::ReadOnly))
    {
        QMessageBox::information (this, "", "PID settings file opening error");
        return;
    }
    QTextStream stream ( &file );
    QString line, line2;
    bool flag = true;
    do
    {
         line = stream.readLine();
         if (line.contains(":"))
         {
             line2 = line.section(":", 1);
             if (flag)
             {
                 sg.Send(QString("A,%1,%2,%3\n").arg(line2.section("-", 0, 0)).arg(line2.section("-", 1, 1)).arg(line2.section("-", 2, 2)));
                 flag = false;
             }
             else
                 sg.Send(QString("F,%1,%2,%3\n").arg(line2.section("-", 0, 0)).arg(line2.section("-", 1, 1)).arg(line2.section("-", 2, 2)));
         }
    } while (!line.isNull());
}
