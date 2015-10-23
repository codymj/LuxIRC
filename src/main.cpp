/******************************************************************************
 * main.cpp                                                                   *
 *                                                                            *
 * Created on Mar 15, 2015                                                    *
 * Author: ismann <ismann@protonmail.com>                                     *
 ******************************************************************************/

#include <QtWidgets/QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

   QApplication app(argc, argv);

   MainWindow mainWin;
   mainWin.show();
   return app.exec();
}
