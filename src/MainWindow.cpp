/******************************************************************************
 * MainWindow.cpp                                                             *
 *                                                                            *
 * Created on Mar 15, 2015                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#include "MainWindow.h"

MainWindow::MainWindow() {
   setupUi(this);

   connectActions();

   // I'll create a method to handle initial data settings later.
   nickName = changeNickBtn->text();

   // Resize the splitter so the widgets look more aesthetic.
   // sizeList << chanView size << centralWidget size << nickView size;
   QList<int> sizeList;
   sizeList << 150 << 450 << 150;
   splitter->setSizes(sizeList);
}

MainWindow::~MainWindow() {
}

/*** Create menu actions ***/
void MainWindow::connectActions() {
   connect(
      openNetworkDlgAction, SIGNAL(triggered()), this, SLOT(openNetworkDlg())
   );
   connect(aboutAction, SIGNAL(triggered()), this, SLOT(openAboutDlg()));
   connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
   connect(changeNickBtn, SIGNAL(clicked()), this, SLOT(changeNick()));
}

/*** SLOT - Change nickname ***/
void MainWindow::changeNick() {
   ChangeNickDlg *changeNickDlg = new ChangeNickDlg();
   changeNickDlg->newNickLE->setText(nickName);
   changeNickDlg->newNickLE->selectAll();

   if (changeNickDlg->exec()) {
      // TODO: Handle blank line edit...
      nickName = changeNickDlg->newNickLE->text();
      changeNickBtn->setText(nickName);
   }

   // TODO:  Handle method to change nick via IRC protocol.

   delete changeNickDlg;
}

/*** SLOT - Open the Network Dialog ***/
void MainWindow::openNetworkDlg() {
   NetworkDlg *networkDlg = new NetworkDlg();
   networkDlg->exec();

   this->receiveConnectObj(networkDlg->tempConnection);

   delete networkDlg;
}

/*** SLOT - Open the About Dialog ***/
void MainWindow::openAboutDlg() {
   AboutDlg *aboutDlg = new AboutDlg();
   aboutDlg->exec();
   
   delete aboutDlg;
}

/*** SLOT - Receive Connection object from NetworkDlg ***/
// I will have to handle when connection is loaded, but disconnected
void MainWindow::receiveConnectObj(Connection *connObj) {
   // Check for duplicate connections by network name
   bool dupe = false;
   for (int i=0; i<_connectionList.size(); i++) {
      if (connObj->getNetwork() == _connectionList.at(i)->getNetwork()) {
         dupe = true;
      }
   }

   if (dupe) {
      QMessageBox mb;
      mb.setText("Network is already added.");
      mb.exec();
      return;
   }
   else {
      // Add tempConnection from NetworkDlg to our list
      _connectionList << connObj;
   }
}
