/******************************************************************************
 * MainWindow.cpp                                                             *
 *                                                                            *
 * Created on Mar 15, 2015                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#include "MainWindow.h"

/*******************************************************************************
Constructor
*******************************************************************************/
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

/*******************************************************************************
Destructor
*******************************************************************************/
MainWindow::~MainWindow() {
}

/*******************************************************************************
Create menu actions
*******************************************************************************/
void MainWindow::connectActions() {
   connect(
      openNetworkDlgAction, SIGNAL(triggered()), 
      this, SLOT(openNetworkDlg())
   );
   connect(
      aboutAction, SIGNAL(triggered()), 
      this, SLOT(openAboutDlg())
   );
   connect(
      exitAction, SIGNAL(triggered()), 
      this, SLOT(close())
   );
   connect(
      changeNickBtn, SIGNAL(clicked()), 
      this, SLOT(changeNick())
   );
   connect(
      this->networkTree, SIGNAL(itemSelectionChanged()), 
      this, SLOT(updateTreeClick())
   );
   connect(  // Need to expand this per network/channel
      this->outputTE->verticalScrollBar(), SIGNAL(valueChanged(int)),
      this, SLOT(storeOutputSliderPos(int))
   );
}

/*******************************************************************************
SLOT - Store the vertical slider position to prevent auto sliding
*******************************************************************************/
void MainWindow::storeOutputSliderPos(int pos) {
   int max = outputTE->verticalScrollBar()->maximum();
   if (selectedChan != NULL) {
      if (max == pos) {
         selectedChan->setSliderMaxed(true);
      }
      else {
         selectedChan->setSliderMaxed(false);
      }
      selectedChan->setSliderVal(pos);
   }
   else {
      if (max == pos) {
         selectedConn->setSliderMaxed(true);
      }
      else {
         selectedConn->setSliderMaxed(false);
      }
      selectedConn->setSliderVal(pos);
   }
}

/*******************************************************************************
SLOT - Change nickname
*******************************************************************************/
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

/*******************************************************************************
SLOT - Open the Network Dialog
*******************************************************************************/
void MainWindow::openNetworkDlg() {
   NetworkDlg *networkDlg = new NetworkDlg(this);
   networkDlg->exec();

   delete networkDlg;
}

/*******************************************************************************
SLOT - Open the About Dialog
*******************************************************************************/
void MainWindow::openAboutDlg() {
   AboutDlg *aboutDlg = new AboutDlg();
   aboutDlg->exec();
   
   delete aboutDlg;
}

/*******************************************************************************
SLOT - Receive Connection object from NetworkDlg
I will have to handle when connection is loaded, but disconnected
*******************************************************************************/
void MainWindow::addConnectionObj(Connection *connObj) {
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
      // Connect Connection signals to slots in MainWindow first
      connect(
         connObj, SIGNAL(dataAvailable()),
         this, SLOT(updateOutputTE())
      );
      connect(
         connObj, SIGNAL(deleteMe(Connection*)),
         this, SLOT(deleteConnection(Connection*))
      );
      _connectionList << connObj;
   }

   // Add Connection info to MainWindow::QTreeWidget
   addConnectionToTree(connObj);

   // Ready to connect to network
   connObj->connectionReady();
}

/*******************************************************************************
SLOT - Must wait for thread to finish, then delete object from connection list
*******************************************************************************/
void MainWindow::deleteConnection(Connection *connObj) {
   for (int i=0; i<_connectionList.size(); i++) {
      if (_connectionList.at(i) == connObj) {
         delete _connectionList.takeAt(i);
      }
   }
}

/*******************************************************************************
Adds a connection to the QTreeWidget
*******************************************************************************/
void MainWindow::addConnectionToTree(Connection *connObj) {
   // Build top-level item for tree
   QTreeWidgetItem *connItem = new QTreeWidgetItem;
   connItem->setText(0, connObj->getNetwork());
   for (int i=0; i<connObj->channels.size(); i++) {
      QTreeWidgetItem *chanChild = new QTreeWidgetItem;
      chanChild->setText(0, connObj->channels.at(i)->getName());
      connItem->addChild(chanChild);
   }

   // Add top-level item to tree, along with children
   networkTree->addTopLevelItem(connItem);
   connItem->setExpanded(true);
   networkTree->setCurrentItem(connItem);
}

/*******************************************************************************
Removes a connection from the QTreeWidget
*******************************************************************************/
void MainWindow::removeItemFromTree() {
   QTreeWidgetItem *currItem = networkTree->currentItem();
   QString conn = selectedConn->getNetwork();

   // If currItem is Channel item, find channel to remove from networkTree
   if (currItem->parent()) {
      QString chan = selectedChan->getName();
      delete currItem;

      // And remove from Connection's list of Channels
      for (int i=0; i<selectedConn->channels.size(); i++) {
         if (selectedConn->channels.at(i)->getName() == chan) {
            // TODO: Handle /part for channel
            delete selectedConn->channels.takeAt(i);
            break;
         }
      }
   }

   // Otherwise, currItem is Connection item, delete all channels & Connection
   else {

      int index = networkTree->indexOfTopLevelItem(currItem);
      int childCount = currItem->childCount();

      // Delete all Channel items belonging to the parent Connection item
      if (childCount > 0) {
         for (int i=0; i<childCount; i++) {
            delete currItem->child(i);
         }
      }

      // And remove from Connection's list of Channels
      for (int i=0; i<selectedConn->channels.size(); i++) {
         delete selectedConn->channels.takeAt(i);
      }

      // Delete the Connection item
      delete networkTree->takeTopLevelItem(index);

      // Delete the Connection in the list of Connection objects.
      for (int i=0; i<_connectionList.size(); i++) {
         if (_connectionList.at(i)->getNetwork() == conn) {
            if (_connectionList.at(i)->connected) {
               _connectionList.at(i)->disconnect();
               outputTE->append("Disconnected.");
            }
         }
      }
   }
}

/*******************************************************************************
Updates widgets when different channel is clicked in tree
*******************************************************************************/
void MainWindow::updateTreeClick() {
   QTreeWidgetItem *currItem = networkTree->currentItem();
   QString network;
   QString chan;

   // Handle an empty networkTree
   if (currItem == NULL) {
      return;
   }

   if (currItem->parent()) {
      network = currItem->parent()->text(0);
      chan = currItem->text(0);
      for (int i=0; i<_connectionList.size(); i++) {
         if (_connectionList.at(i)->getNetwork() == network) {
            for (int j=0; j<_connectionList.at(i)->channels.size(); j++) {
               if (_connectionList.at(i)->channels.at(j)->getName() == chan) {
                  selectedChan = _connectionList.at(i)->channels.at(j);
                  selectedConn = _connectionList.at(i);
               }
            }
         }
      }
   }
   else {
      network = currItem->text(0);
      for (int i=0; i<_connectionList.size(); i++) {
         if (_connectionList.at(i)->getNetwork() == network) {
            selectedConn = _connectionList.at(i);
            selectedChan = NULL;
         }
      }
   }
   updateOutputTE();
}

/*******************************************************************************
SLOT - Updates the TextEdit with new data
*******************************************************************************/
void MainWindow::updateOutputTE() {
   QTextCursor _outputTECursor(outputTE->textCursor());

   // If selectedChan = NULL then topLevelItem is selected, show notices
   if (selectedChan == NULL) {
      QStringList notices = selectedConn->getNotices();
      int sliderVal = selectedConn->getSliderVal();

      // Clear outputTE for appending data
      outputTE->clear();

      // Show notices
      for (int i=0; i<notices.size(); i++) {
         _outputTECursor.insertText(notices.at(i));
      }

      // Set scrollbar to last set position (bottom by default)
      if (selectedConn->isSliderMaxed()) {
         sliderVal = outputTE->verticalScrollBar()->maximum();
      }
      outputTE->verticalScrollBar()->setSliderPosition(sliderVal);
   }

   // Otherwise, a child is selected. Show messages for channel/user
   else {
      QStringList msgs = selectedChan->getMsgs();
      int sliderVal = selectedChan->getSliderVal();

      // Clear outputTE for appending data
      outputTE->clear();

      // Show messages
      for (int i=0; i<msgs.size(); i++) {
         _outputTECursor.insertText(msgs.at(i));
      }

      // Set scrollbar to last set position (bottom by default)
      if (selectedChan->isSliderMaxed()) {
         sliderVal = outputTE->verticalScrollBar()->maximum();
      }
      outputTE->verticalScrollBar()->setSliderPosition(sliderVal);
   }

   // Handle user pvt messages later

   // Update all other widgets in MainWindow (nickname, userlist, etc)
}

/*******************************************************************************
Handles keyboard commands
*******************************************************************************/
void MainWindow::keyPressEvent(QKeyEvent *e) {
   // Handle Ctrl+W
   if (
   (e->key() == Qt::Key_W) && (e->modifiers().testFlag(Qt::ControlModifier))) {
      // Handle empty tree widget
      if (networkTree->topLevelItemCount() == 0) {
         return;
      }
      else {
         removeItemFromTree();
      }
   }
}
