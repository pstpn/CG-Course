#include "mainwindow.h"
#include <QApplication>
#include <QStyleFactory>
#include <QDebug>

int main(int argc, char *argv[]) {
    
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    QApplication::setStyle("Fusion");

    return app.exec();
}
