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
   // Check if connObj is NULL (initial value), return to prevent segfault
   if (connObj == NULL) {
      return;
   }

   // Check for duplicate connections by network name
   bool dupe = false;
   for (int i=0; i<_connectionList.size(); i++) {
      if (connObj->getNetwork() == _connectionList.at(i)->getNetwork()) {
         dupe = true;
      }
   }

   // If a duplicate is found, notify user and return to MainWindow
   if (dupe) {
      QMessageBox mb;
      mb.setText("Network is already added.");
      mb.exec();
      return;
   }

   // Otherwise, append the Connection object to the list
   else {
      _connectionList << connObj;
   }

   // Add Connection info to MainWindow::QTreeWidget
   addConnectionToTree(connObj);
}

/*** Adds a connection to the QTreeWidget ***/
void MainWindow::addConnectionToTree(Connection *connObj) {
   // Build top-level item for tree
   QTreeWidgetItem *connItem = new QTreeWidgetItem;
   connItem->setText(0, connObj->getNetwork());
   for (int i=0; i<connObj->getChanList().size(); i++) {
      QTreeWidgetItem *chanChild = new QTreeWidgetItem;
      chanChild->setText(0, connObj->getChanList().at(i));
      connItem->addChild(chanChild);
   }

   // Add top-level item to tree, along with children
   this->networkTree->addTopLevelItem(connItem);
   connItem->setExpanded(true);
}

/*** Removes a connection from the QTreeWidget ***/
void MainWindow::rmConnectionFromTree(const QString &network) {
   // Find network (top-level item) in the QTreeWidget
   int childCount = this->networkTree->topLevelItemCount();
   for (int i=0; i<childCount; i++) {
      if (this->networkTree->topLevelItem(i)->text(0) == network) {
         // Delete all channel widget items in the network widget parent item
         int childCount = this->networkTree->topLevelItem(i)->childCount();
         for (int j=0; j<childCount; j++) {
            delete this->networkTree->topLevelItem(i)->child(j);
         }
         // Delete network tree widget item
         delete this->networkTree->topLevelItem(i);
      }
   }
   // Remove Connection from _connectionList
   for (int i=0; i<_connectionList.size(); i++) {
      if (_connectionList.at(i)->getNetwork() == network) {
         delete _connectionList.at(i);
         _connectionList.removeAt(i);
      }
   }
}

/*** Removes a channel from the QTreeWidget's topLevelItem (network) ***/
// void MainWindow::rmChannelFromTree(QString &channel) {}

/*** Handles keyboard commands ***/
void MainWindow::keyPressEvent(QKeyEvent *e) {
   // Handle Ctrl+W
   if (
   (e->key() == Qt::Key_W) && (e->modifiers().testFlag(Qt::ControlModifier))) {
      // Handle empty tree widget
      if (this->networkTree->topLevelItemCount() == 0) {
         return;
      }
      else if (!this->networkTree->currentItem()->parent()) {
         rmConnectionFromTree(this->networkTree->currentItem()->text(0));
      }
      else {
         return;
      }
   }
   else {
      return;
   }
}

/*** SLOT - Updates widgets when different channel is clicked in tree ***/
void MainWindow::updateTreeClick() {
   // Get which channel the clicked tree item represents

   // Update outputTE by getting the QStringList of messages parsed for that
   // channel, stored in Connection object

   // Update inputLE's target network and channel

   // Update topicLE's text
}

void MainWindow::updateOutputTE(QString &network, QString &data) {

}
