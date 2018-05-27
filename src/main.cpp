// =============================================================================
// main.cpp
//
// Created on: Mar 15, 2015
// Author: Cody Johnson <codyj@protonmail.com
// =============================================================================
#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set the default stylesheet
    //QFile file("./stylesheet.qss");
    //file.open(QFile::ReadOnly);
    //QString styleSheet = QLatin1String(file.readAll());
    //app.setStyleSheet(styleSheet);

    MainWindow mainWin;
    mainWin.show();
    return app.exec();
}
