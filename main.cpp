#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QPlastiqueStyle>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle(new QPlastiqueStyle);
    MainWindow w;
    w.show();
    return a.exec();
}
