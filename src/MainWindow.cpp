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

   // Initialize nickname
   QTime time = QTime::currentTime();
   qsrand((uint)time.msec());
   int low = 10000;
   int high = 99999;
   QString prefix = "LuxIRC-";
   QString suffix = QString::number(qrand() % ((high + 1) - low) + low);
   _initialNick = prefix + suffix;
   changeNickBtn->setText(_initialNick);

   // Resize the splitter so the widgets look more aesthetic.
   // sizeList << chanView size << centralWidget size << nickView size;
   QList<int> sizeList;
   sizeList << 175 << 650 << 175;
   splitter->setSizes(sizeList);

   updateCharsLeftLbl(inputLE->text());
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
   connect(
      outputTE->verticalScrollBar(), SIGNAL(sliderMoved(int)),
      this, SLOT(storeOutputSliderPos(int))
   );
   connect(
      inputLE, SIGNAL(returnPressed()),
      this, SLOT(sendData())
   );
   connect(
      inputLE, SIGNAL(textEdited(const QString&)),
      this, SLOT(updateCharsLeftLbl(const QString &))
   );
}

/*******************************************************************************
SLOT - Updates the amount of characters left for typing a message
*******************************************************************************/
void MainWindow::updateCharsLeftLbl(const QString &msg) {
   // If msg begins with '/', command is being typed
   if (msg.startsWith('/')) {
      charsLeftLbl->setText("Characters left: n/a");
      return;
   }

   if (selectedChan == NULL) {
      charsLeftLbl->setText("Characters left: n/a");
      return;
   }

   // Num of chars: #<channel>
   int chanChars = selectedChan->getName().size();
   // "<hostname> PRIVMSG #<channel> :<msg>\r\n"
   int commandChars = 14;
   int msgChars = msg.size();
   int hostnameChars = selectedConn->getHostname().size();

   int charsLeft = 512 - hostnameChars - chanChars - commandChars - msgChars;
   inputLE->setMaxLength(512 - hostnameChars - chanChars - commandChars);
   QString charsLeftStr = QString::number(charsLeft);
   charsLeftLbl->setText("Characters left: " + charsLeftStr);
}

/*******************************************************************************
SLOT - When <enter> is pressed for inputLE, sends message to target Channel
*******************************************************************************/
void MainWindow::sendData() {
   QByteArray data, localDisplay;

   // If no text to send, return
   if (inputLE->text().isEmpty()) {
      return;
   }
   // Otherwise, get text to send then reset inputLE
   else {
      data = inputLE->text().toUtf8();
      localDisplay = data;
      inputLE->clear();
      updateCharsLeftLbl(inputLE->text());
   }

   // If a Channel is not selected
   if (selectedChan == NULL) {
      return;
   }
   // Otherwise, send data
   else {
      // Data sent to server
      data.append("\r\n");
      data.prepend(" :");
      data.prepend(selectedChan->getName().toUtf8());
      data.prepend("PRIVMSG ");
      selectedConn->dataForWriting.enqueue(data);

      // Data shown locally
      localDisplay.append("\n");
      localDisplay.prepend("| ");
      localDisplay.prepend(selectedConn->getNick().toUtf8());
      int spaces = selectedConn->getMaxNickLength() - 
         selectedConn->getNick().size();
      for (int i=0; i<=spaces; i++) {
         localDisplay.prepend(' ');
      }
      selectedChan->pushMsg(QString::fromUtf8(localDisplay));
      updateOutputTE();
   }
}

/*******************************************************************************
SLOT - Store the vertical slider position to prevent auto sliding
*******************************************************************************/
void MainWindow::storeOutputSliderPos(int pos) {
   // Handle empty networkTree
   if (selectedConn == NULL) {
      return;
   }

   // Store maximum scroll value for current Channel or Connection
   int max = outputTE->verticalScrollBar()->maximum();

   // Set scroll slider value for each Channel
   if (selectedChan != NULL) {
      if (max == pos) {
         selectedChan->setSliderMaxed(true);
      }
      else {
         selectedChan->setSliderMaxed(false);
      }
      selectedChan->setSliderVal(pos);
   }

   // Set scroll slider value for each topLevelItem (server notices)
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
Change nick name
*******************************************************************************/
void MainWindow::changeNick(const QString &nick) {
   // Set nick name text for changeNickBtn
   changeNickBtn->setText(nick);

   // Set the nick name for the selected Connection
   if (networkTree->topLevelItemCount() == 0) {
      return;
   }
   else {
      if (selectedConn->getNick() == nick) {
         return;
      }
      else {
         selectedConn->setNick(nick);
      }
   }
}

/*******************************************************************************
SLOT - Change nick name
*******************************************************************************/
void MainWindow::changeNick() {
   ChangeNickDlg *changeNickDlg = new ChangeNickDlg();
   QString nickName;

   if (networkTree->topLevelItemCount() == 0) {
      nickName = _initialNick;
   }
   else {
      nickName = selectedConn->getNick();
   }

   changeNickDlg->newNickLE->setText(nickName);
   changeNickDlg->newNickLE->selectAll();

   if (changeNickDlg->exec()) {
      nickName = changeNickDlg->newNickLE->text();
      _initialNick = nickName;

      // Handle empty field
      if (nickName == "") {
         return;
      }

      changeNickBtn->setText(nickName);
      if (networkTree->topLevelItemCount() == 0) {
         return;
      }
      else {
         selectedConn->setNick(nickName);
      }
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
      connect(
         connObj, SIGNAL(newChannel(Connection*, Channel*)),
         this, SLOT(createChannel(Connection*, Channel*))
      );
      connect(
         connObj, SIGNAL(topicChanged(Channel*)),
         this, SLOT(updateTopic(Channel*))
      );
      connect(
         connObj, SIGNAL(userListChanged(Channel*)),
         this, SLOT(updateUserList(Channel*))
      );
      _connectionList << connObj;
   }

   // Add Connection info to MainWindow::QTreeWidget
   addConnectionToTree(connObj);

   // Ready to connect to network
   connObj->connectionReady();
}

/*******************************************************************************
SLOT - Updates topic in topicLE for Channel
*******************************************************************************/
void MainWindow::updateUserList(Channel *chan) {
   if (selectedChan == chan) {
      // Get user list from Channel
      QList<QStringList> userList = chan->getUserList();

      // Clear MainWindow's QListWidget for populating/updating
      nickList->clear();

      int userCount = 0;
      for (int i=0; i<userList.size(); i++) {
         for (int j=0; j<userList.at(i).size(); j++) {
            nickList->addItem(userList.at(i).at(j));
         }
         userCount += userList.at(i).size();
      }
      
      // Update userCountLbl
      userCountLbl->setText(QString::number(userCount) + " users here");
   }
}

/*******************************************************************************
SLOT - Updates topic in topicLE for Channel
*******************************************************************************/
void MainWindow::updateTopic(Channel *chan) {
   if (selectedChan == chan) {
      topicLE->setText(chan->getTopic());
      topicLE->setCursorPosition(0);
   }
}

/*******************************************************************************
SLOT - Creates a new channel when user sends a message
*******************************************************************************/
void MainWindow::createChannel(Connection *connObj, Channel *chan) {
   QTreeWidgetItem *newChan = new QTreeWidgetItem;
   newChan->setText(0, chan->getName());

   for (int i=0; i<networkTree->topLevelItemCount(); i++) {
      if (networkTree->topLevelItem(i)->text(0) == connObj->getNetwork()) {
         networkTree->topLevelItem(i)->addChild(newChan);
      }
   }
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

   // Make sure nick name from connObj updates changeNickBtn
   changeNick(selectedConn->getNick());
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

      // If it is not a user private message, leave the Channel
      if (chan.startsWith('#')) {
         selectedConn->partChannel(selectedChan);
      }

      // And remove from networkTree's list of Channels
      delete currItem;
   }

   // Otherwise, currItem is Connection item, delete all channels & Connection
   else {
      int index = networkTree->indexOfTopLevelItem(currItem);
      int childCount = currItem->childCount();

      // Quit from the network
      selectedConn->sendQuit();

      // Delete all Channel items belonging to the parent Connection item
      if (childCount > 0) {
         for (int i=0; i<childCount; i++) {
            delete currItem->child(i);
         }
      }

      // Delete the Connection item
      delete networkTree->takeTopLevelItem(index);
      outputTE->clear();

      // If any more Connections exist in tree, update currentItem to the first
      if (networkTree->topLevelItemCount() > 0) {
         networkTree->setCurrentItem(networkTree->topLevelItem(0));
      }
      else {
         selectedConn = NULL;
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

   // If Channel in tree is selected
   if (currItem->parent()) {
      network = currItem->parent()->text(0);
      chan = currItem->text(0);
      for (int i=0; i<_connectionList.size(); i++) {
         if (_connectionList.at(i)->getNetwork() == network) {
            for (int j=0; j<_connectionList.at(i)->channels.size(); j++) {
               if (_connectionList.at(i)->channels.at(j)->getName() == chan) {
                  // Update selected Channel and Channel's info
                  selectedChan = _connectionList.at(i)->channels.at(j);
                  updateTopic(selectedChan);
                  updateUserList(selectedChan);
                  updateCharsLeftLbl(inputLE->text());

                  // Update selected Connection
                  selectedConn = _connectionList.at(i);
               }
            }
         }
      }
   }

   // Otherwise, a Connection is selected
   else {
      // Clear MainWindow data for Channels
      topicLE->clear();
      nickList->clearSelection();
      nickList->clearFocus();
      nickList->clear();
      userCountLbl->clear();

      // Update MainWindow data for selected Connection
      network = currItem->text(0);
      for (int i=0; i<_connectionList.size(); i++) {
         if (_connectionList.at(i)->getNetwork() == network) {
            selectedConn = _connectionList.at(i);
            selectedChan = NULL;
            updateCharsLeftLbl(inputLE->text());
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

   // Handle empty networkTree
   if (selectedConn == NULL) {
      return;
   }

   // If selectedChan = NULL then topLevelItem is selected, show notices
   if (selectedChan == NULL) {
      outputTE->setLineWrapMode(QTextEdit::WidgetWidth);
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
