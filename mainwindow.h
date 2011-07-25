#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <QMainWindow>
#include "colorpalettedialog.h"
#include "defines.h"
#include <QFrame>
#include <QWidget>
#include "ProximitySensorPainter.h"
#include "AnalogSensorGraph.h"
#include "speedcontrol.h"
#include "pidregulator.h"
#include "inputsoutputstab.h"

class ProximitySensorPainter;
namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum Tabs {console, script, proximityS, analogS, speed, PID};
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    QTimer *consoleTimer;
    ProximitySensorPainter *sensorFrame;
    //AnalogGraph *analogFrame;
    SpeedControl *speedControlTab;
    PIDRegulator *PIDTab;
    InputsOutputsTab *inOutTab;

    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::MainWindow *ui;
    ColorPaletteDialog colorDialog;
private slots:
    void on_openButton_clicked();
    void on_changeTab();
    void TimeOut(void);

    void on_actionClearConsole_triggered();

    void on_actionQuit_triggered();
    void on_actionTimeouts_triggered();
    void on_actionColor_palette_triggered();
};

#endif // MAINWINDOW_H
