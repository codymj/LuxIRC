/******************************************************************************
 * NetworkDlg.cpp                                                             *
 *                                                                            *
 * Created on: Mar 19, 2015                                                   *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtWidgets/QListWidgetItem>
#include "NetworkDlg.h"

/*******************************************************************************
Constructor
*******************************************************************************/
NetworkDlg::NetworkDlg(QWidget *MainWindow) {
   setupUi(this);

   connect(addBtn, SIGNAL(clicked()), this, SLOT(openAddNetworkDlg()));
   connect(editBtn, SIGNAL(clicked()), this, SLOT(openEditNetworkDlg()));
   connect(removeBtn, SIGNAL(clicked()), this, SLOT(removeNetwork()));
   connect(
      networkList, SIGNAL(itemSelectionChanged()), this, SLOT(selectNetwork())
   );
   connect(connectBtn, SIGNAL(clicked()), this, SLOT(buildConnection()));
   connect(okBtn, SIGNAL(clicked()), this, SLOT(accept()));
   connect(cancelBtn, SIGNAL(clicked()), this, SLOT(reject()));
   connect(
      this, SIGNAL(connectionReady(Connection*)),
      MainWindow, SLOT(addConnectionObj(Connection*))
   );

   readData();
}

/*******************************************************************************
Destructor
*******************************************************************************/
NetworkDlg::~NetworkDlg() {
}

/*******************************************************************************
SLOT - Open the AddNetworkDlg
*******************************************************************************/
void NetworkDlg::openAddNetworkDlg() {
   AddNetworkDlg *addNetworkDlg = new AddNetworkDlg();
   connect(addNetworkDlg->saveBtn, SIGNAL(clicked()), this, SLOT(readData()));

   addNetworkDlg->exec();

   delete addNetworkDlg;
}

/*******************************************************************************
SLOT - Open the EditNetworkDlg
*******************************************************************************/
void NetworkDlg::openEditNetworkDlg() {
   EditNetworkDlg *editNetworkDlg = new EditNetworkDlg(selectedNetwork);

   if (editNetworkDlg->exec()) {
   }

   delete editNetworkDlg;
}

/***  ***/
/*******************************************************************************
SLOT - Selects network from emitted networkList indexChanged signal
*******************************************************************************/
void NetworkDlg::selectNetwork() {
   selectedNetwork = networkList->currentItem()->text();
   selectedNetwork = selectedNetwork.trimmed();
}

/*******************************************************************************
SLOT - Populates networkList with networks from 'networks.conf' file
*******************************************************************************/
void NetworkDlg::readData() {
   QDir config("./config");
   if (!config.exists()) {
      qDebug() << "Creating /config directory.";
      config.mkdir("config");
   }

   // Open networks.conf for reading
   QFile networks("./config/networks.conf");
   if (!networks.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Error opening networks.conf";
      return;
   }

   // Open luxirc.conf for reading
   QFile luxirc("./config/luxirc.conf");
   if (!luxirc.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Error opening luxirc.conf.";
      return;
   }

   QString line;

   // Load global user info into NetworkDlg
   while (!luxirc.atEnd()) {
      line = luxirc.readLine();
      if (line.left(2) == "I=") {
         gblNickLE->setText(line.mid(2).trimmed());
      }
      if (line.left(2) == "i=") {
         gblNick2LE->setText(line.mid(2).trimmed());
      }
      if (line.left(2) == "U=") {
         gblUsernameLE->setText(line.mid(2).trimmed());
      }
      if (line.left(2) == "R=") {
         gblRealNameLE->setText(line.mid(2).trimmed());
      }
   }

   // Clear networkList first
   networkList->clear();

   // Loop until all networks are found
   while (!networks.atEnd()) {
      line = networks.readLine();
      if (line.left(2) == "N=") {
         QString networkStr = line.mid(2);
         networkStr = networkStr.trimmed();
         networkList->addItem(networkStr);
      }
   }
   luxirc.close();
   networks.close();
   networkList->sortItems();
   networkList->setCurrentRow(0);
}

/*******************************************************************************
SLOT - Removes a network from the network list
*******************************************************************************/
void NetworkDlg::removeNetwork() {
   // Open networks.conf for reading
   QFile networks("./config/networks.conf");
   if (!networks.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Creating networks.conf file since it did not exist.";
   }

   // Open temp file for writing
   QFile temp("./config/temp");
   if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Creating temp file for writing.";
   }

   QTextStream write(&temp);
   QString networkName = selectedNetwork;
   QString line;

   while (!networks.atEnd()) {
      line = networks.readLine();

      // Found network to remove
      if (line.mid(2).trimmed() == networkName) {
         // Skip data for network
         while (line.left(2) != "\n") {
            line = networks.readLine();
            if (line == "") {
               break;   // If data is at end of file
            }
         }
         line = networks.readLine();
      }
      write << line;
   }
   networks.close();
   temp.close();
   networks.remove();
   temp.rename("config/networks.conf");
   readData();
}

/*******************************************************************************
SLOT - Accept override to save global user info into file luxirc.conf
*******************************************************************************/
void NetworkDlg::accept() {
   // Open luxirc.conf for reading
   QFile luxirc("./config/luxirc.conf");
   if (!luxirc.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Unable to open luxirc.conf";
   }

   // Open temp file for writing
   QFile temp("./config/temp");
   if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Creating temp file for writing.";
   }

   QTextStream write(&temp);

   write << "I=" << gblNickLE->text() << '\n';
   write << "i=" << gblNick2LE->text() << '\n';
   write << "U=" << gblUsernameLE->text() << '\n';
   write << "R=" << gblRealNameLE->text() << '\n';

   luxirc.close();
   temp.close();
   luxirc.remove();
   temp.rename("config/luxirc.conf");

   this->close();
}

/*******************************************************************************
SLOT - Builds Connection object from data file for selected network
*******************************************************************************/
void NetworkDlg::buildConnection() {
   Connection *connection = new Connection;

   QDir config("./config");
   if (!config.exists()) {
      qDebug() << "ERROR: ./config directory is gone.";
   }

   QFile networks("./config/networks.conf");
   if (!networks.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Error opening 'networks.conf'";
   }

   // Loop until selected network is found
   QString line;
   while (!networks.atEnd()) {
      line = networks.readLine();
      line = line.trimmed();
      if (line.mid(2) == this->selectedNetwork) {
         // Network found. Parse info until the next blank line
         while (line != "\n") {
            QString id = line.left(2);      // First two chars in line (ex. N=)
            QString lineData = line.mid(2); // The data on the rest of the line
            lineData = lineData.trimmed();

            if (id == "N=") {
               connection->setNetwork(lineData);
            } else if (id == "S=") {
               connection->setServer(lineData);
            } else if (id == "p=") {
               connection->setPort(lineData.toInt());
            } else if (id == "I=") {
               connection->setNick(lineData);
            } else if (id == "i=") {
               connection->setNick2(lineData);
            } else if (id == "U=") {
               connection->setUsername(lineData);
            } else if (id == "R=") {
               connection->setRealName(lineData);
            } else if (id == "L=") {
               connection->setLoginMethod(lineData.toInt());
            } else if (id == "P=") {
               connection->setPassword(lineData);
            } else if (id == "J=") {
               QStringList chans;
               chans << lineData.split(",");
               for (int i=0; i<chans.size(); i++) {
                  Channel *chan = new Channel;

                  chans.at(i).trimmed();     // Trim whitespace
                  if (chans.at(i) == "") {   // Skip blank strings
                     continue;
                  }
                  chan->setName(chans.at(i));

                  // Connect signals/slots
                  connect(
                     chan, SIGNAL(topicChanged(Channel*)),
                     connection, SIGNAL(topicChanged(Channel*))
                  );
                  connect(
                     chan, SIGNAL(userListChanged(Channel*)),
                     connection, SIGNAL(userListChanged(Channel*))
                  );
                  connection->channels.append(chan);
               }
               connection->setChans(lineData);
            } else if (id == "c=") {
               bool cBool;
               int lineToInt = lineData.toInt();
               if (lineToInt == 0) {
                  cBool = 0;
               } else {
                  cBool = 1;
               }
               connection->setConnectAtStart(cBool);
            } else if (id == "n=") {
               bool nBool;
               int lineToInt = lineData.toInt();
               if (lineToInt == 0) {
                  nBool = 0;
               } else {
                  nBool = 1;
               }
               connection->setUseSSL(nBool);
            } else if (id == "a=") {
               bool aBool;
               int lineToInt = lineData.toInt();
               if (lineToInt == 0) {
                  aBool = 0;
               } else {
                  aBool = 1;
               }
               connection->setAcceptInvalidSSLCert(aBool);
            } else if (id == "g=") {
               bool gBool;
               int lineToInt = lineData.toInt();
               if (lineToInt == 0) {
                  gBool = 0;
               } else {
                  gBool = 1;
               }
               connection->setUseGlobalInfo(gBool);
            } else {
               qDebug() << "Error in EditNetworkDlg::populateData";
            }
            line = networks.readLine();
            // A hack -- for some reason file.atEnd() isn't breaking loop
            if (line == 0) {
               break;
            }
         }
      }
   }
   networks.close();

   emit connectionReady(connection);
   this->close();
}
