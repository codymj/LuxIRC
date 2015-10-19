/*
 * main.cpp
 *
 * 	Created on Mar 15, 2015
 * 		Author: br0d1n
 */

#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

   QApplication app(argc, argv);

   MainWindow mainWin;
   mainWin.show();
   return app.exec();
}
