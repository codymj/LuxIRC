/*
 * File:   main.cpp
 * Author: br0d1n
 *
 * Created on March 15, 2015, 11:00 PM
 */

#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);

    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
