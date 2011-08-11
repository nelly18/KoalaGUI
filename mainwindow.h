#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define _CRT_NON_CONFORMING_SWPRINTFS

#include <QtGui/QMainWindow>

#include "colorpalettedialog.h"
#include "defines.h"

class ProximitySensorPainter;
namespace Ui {
    class MainWindow;
}

class Console;
class QTimer;
class ProximitySensorPainter;
class SpeedControl;
class PidRegulator;
class InputsOutputsTab;
class StatusBarWidget;
class ScriptTab;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Tabs {console, script, proximityS, analogS, speed, PID};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
   // bool eventFilter(QObject *obj, QEvent *event);

private:
    void readPidSettings();

private slots:
    void on_openButton_clicked();
    void on_changeTab();
    void consoleTimeOut(void);
    void newCommand(QString);
    void on_actionClearConsole_triggered();
    void on_actionQuit_triggered();
    void on_actionTimeouts_triggered();
    void on_actionColor_palette_triggered();

private:
    Ui::MainWindow *ui;
    ColorPaletteDialog colorDialog_;
    Console *consoleTab_;
    QTimer *consoleTimer_;
    ProximitySensorPainter *sensorFrame_;
    SpeedControl *speedControlTab_;
    PidRegulator *pidTab_;
    InputsOutputsTab *inOutTab_;
    StatusBarWidget *statusBarWidget_;
    ScriptTab *scriptTab_;
};

#endif // MAINWINDOW_H
