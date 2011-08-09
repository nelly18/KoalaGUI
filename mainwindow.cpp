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

    consoleTab_ = new Console(this);
    connect(consoleTab_, SIGNAL(onCommand(QString)), this, SLOT(newCommand(QString)));
    ui->tabWidget->addTab(consoleTab_, "Console");

    scriptTab_ = new ScriptTab;
    ui->tabWidget->addTab(scriptTab_, "Script");
//    QThread scriptThread;
//    scriptTab->moveToThread(&scriptThread);
//    scriptThread.start();

    consoleTimer_ = new QTimer(this);
    connect(consoleTimer_, SIGNAL(timeout()), this, SLOT(consoleTimeOut()));

    sensorFrame_ = new ProximitySensorPainter(this);
    ui->tabWidget->addTab(sensorFrame_, "Sensors");

    inOutTab_ = new InputsOutputsTab(this);
    connect(ui->openButton, SIGNAL(clicked()), inOutTab_, SLOT(openPortButtonClicked()));
    ui->tabWidget->addTab(inOutTab_, "I/O signals");

    speedControlTab_ = new SpeedControl(this);
    ui->tabWidget->addTab(speedControlTab_, "Speed");

    pidTab_ = new PidRegulator;
    ui->tabWidget->addTab(pidTab_, "PID");

    statusBarWidget_ = new StatusBarWidget(this);
    //ui->statusBar->addWidget(statusBarWidget, 1);
    setStatusBar(statusBarWidget_->statusBar);
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
            sensorFrame_->drawSensorsTimer_->stop();
            inOutTab_->analogFrame_->analogTimer_->stop();
            inOutTab_->manualTimer_->stop();
            consoleTimer_->start(timeOutConsole);
            break;

        case script:
            sensorFrame_->drawSensorsTimer_->stop();
            inOutTab_->analogFrame_->analogTimer_->stop();
            consoleTimer_->stop();
            break;

        case proximityS:
            consoleTimer_->stop();
            inOutTab_->analogFrame_->analogTimer_->stop();
            sensorFrame_->drawSensorsTimer_->start(timeOutDrawSens);
            break;

        case analogS:
            sensorFrame_->drawSensorsTimer_->stop();
            consoleTimer_->stop();
            inOutTab_->analogFrame_->analogTimer_->start(timeOutAnalog);
            break;
        case speed:
            sensorFrame_->drawSensorsTimer_->stop();
            inOutTab_->analogFrame_->analogTimer_->stop();
            consoleTimer_->stop();
            break;
        case PID:
            sensorFrame_->drawSensorsTimer_->stop();
            inOutTab_->analogFrame_->analogTimer_->stop();
            consoleTimer_->stop();
            break;
    }

}

void MainWindow::on_openButton_clicked()
{
    const int port = ui-> cbPort ->currentIndex() + 1;

    QString message;
    if (sg.state)
    {
        sensorFrame_ -> drawSensorsTimer_ -> stop();
        consoleTimer_ -> stop();
        inOutTab_ -> analogFrame_->analogTimer_->stop();
        statusBarWidget_->chargeBattery_->batteryChargeTimer_->stop();

        sg.close();

        ui -> openButton -> setText("Open port");
        message = QString("Serial port COM%1 closed").arg(port);
        consoleTab_->output(message);
        consoleTab_->isLocked = true;

        sensorFrame_->resetSensorsColor();

        return;
    }

    const QString qsSpeed = ui -> cbSpeed -> currentText();
    const int speed = qsSpeed.section(":", 1).toInt();

    if (sg.open(port, speed))
    {
        message = QString("Serial port COM%1 opened").arg(port);
        consoleTab_->isLocked = false;
        ui -> openButton -> setText("Close port");

        readPIDSettings();

        statusBarWidget_->chargeBattery_->batteryChargeTimer_->start(3000);

        switch (ui->tabWidget->currentIndex())
        {
        case console:
            //consoleTimer-> start(timeoutconsole);
            break;
        case script:
            break;
        case proximityS:
            sensorFrame_->drawSensorsTimer_->start(timeOutDrawSens);
            break;
        case analogS:
            inOutTab_->analogFrame_->analogTimer_->start(timeOutAnalog);
            break;
        }

    }
    else
    {
        message = QString("Serial port COM%1 openning error").arg(port);
        consoleTab_->isLocked = true;
    }

    consoleTab_->output(message);

}

void MainWindow::consoleTimeOut(void)
{
    QString buff;

    if(sg.recv(buff, 256))
        consoleTab_->output(buff);

}

void MainWindow::on_actionClearConsole_triggered()
{

     consoleTab_->clear();
     consoleTab_->insertPrompt(false);
}

void MainWindow::on_actionQuit_triggered()
{
     QApplication::quit();
}


void MainWindow::on_actionColor_palette_triggered()
{
    if (colorDialog_.exec() == QDialog::Accepted)
    {
        sensorFrame_->setColorPalette(colorDialog_.palette());
    }
}

void MainWindow::on_actionTimeouts_triggered()
{

}
void MainWindow::newCommand(QString command)
{
    sg.send(QString("%1\n").arg(command));
    consoleTab_->insertPrompt();
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
                 sg.send(QString("A,%1,%2,%3\n").arg(line2.section("-", 0, 0)).arg(line2.section("-", 1, 1)).arg(line2.section("-", 2, 2)));
                 flag = false;
             }
             else
                 sg.send(QString("F,%1,%2,%3\n").arg(line2.section("-", 0, 0)).arg(line2.section("-", 1, 1)).arg(line2.section("-", 2, 2)));
         }
    } while (!line.isNull());
}
