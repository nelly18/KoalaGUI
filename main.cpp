#include <QtGui/QApplication>
#include <QtGui/QPlastiqueStyle>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(new QPlastiqueStyle);
    a.setStyleSheet ( "QGroupBox {"
                          "background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                          "stop: 0 #E0E0E0, stop: 1 #EEEEEE);"
                          "border: 1px solid gray;"
                          "border-radius: 4px;"
                          "margin-top: 8px; "
                          "padding: 5px;"
                      "}"

                      "QGroupBox::title {"
                         "subcontrol-origin: margin;"
                         "subcontrol-position: top center;"
                         "padding: 0 3px;"
                      "}"
                      "QMainWindow {background-color: #E0E0E0;}"
                      "QTabWidget {background-color: #E0E0E0;}"
                      "QMenuBar {background-color: #E0E0E0;}"
                      );

    MainWindow w;
    w.resize(800, 600);
    w.show();
    return a.exec();
}
