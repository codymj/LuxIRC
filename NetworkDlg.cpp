/*
 * NetworkDlg.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: br0d1n
 */

#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtWidgets/QListWidgetItem>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include "NetworkDlg.h"
#include "EditNetworkDlg.h"

/*** Constructor ***/
NetworkDlg::NetworkDlg() {
   setupUi(this);

   connect(addBtn, SIGNAL(clicked()), this, SLOT(openAddNetworkDlg()));
   connect(editBtn, SIGNAL(clicked()), this, SLOT(openEditNetworkDlg()));
   connect(removeBtn, SIGNAL(clicked()), this, SLOT(removeNetwork()));
   connect(networkList, SIGNAL(itemSelectionChanged()), this, SLOT(selectNetwork()));

   readData();
}

/*** Destructor ***/
NetworkDlg::~NetworkDlg() {
}

/*** SLOT - Open the AddNetworkDlg ***/
void NetworkDlg::openAddNetworkDlg() {
   AddNetworkDlg *addNetworkDlg = new AddNetworkDlg();
   connect(addNetworkDlg->saveBtn, SIGNAL(clicked()), this, SLOT(readData()));

   addNetworkDlg->exec();

   delete addNetworkDlg;
}

/*** SLOT - Open the EditNetworkDlg ***/
void NetworkDlg::openEditNetworkDlg() {
   EditNetworkDlg *editNetworkDlg = new EditNetworkDlg(selectedNetwork);

   if (editNetworkDlg->exec()) {
   }

   delete editNetworkDlg;
}

/*** SLOT - Selects network from emitted networkList indexChanged signal ***/
void NetworkDlg::selectNetwork() {
   selectedNetwork = networkList->currentItem()->text();
   selectedNetwork = selectedNetwork.trimmed();
}

/*** SLOT - Populates networkList with networks from 'networks.conf' file ***/
void NetworkDlg::readData() {
   // Open networks.conf for reading
   QFile networks("networks.conf");
   if (!networks.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Error opening networks.conf";
      return;
   }

   // Open luxirc.conf for reading
   QFile luxirc("luxirc.conf");
   if (!luxirc.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Error opening luxirc.conf.";
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

/*** SLOT - Removes a network from the network list ***/
void NetworkDlg::removeNetwork() {
   // Open networks.conf for reading
   QFile file("networks.conf");
   if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      qDebug() << "Creating networks.conf file since it did not exist.";
   }

   // Open temp file for writing
   QFile temp("temp");
   if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Creating temp file for writing.";
   }

   QTextStream write(&temp);
   QString networkName = selectedNetwork;
   QString line;

   while (!file.atEnd()) {
      line = file.readLine();

      // Found network to remove
      if (line.mid(2).trimmed() == networkName) {
         // Skip data for network
         while (line.left(2) != "\n") {
            line = file.readLine();
            if (line == "") {
               break;   // If data is at end of file
            }
         }
         line = file.readLine();
      }
      write << line;
   }
   file.close();
   temp.close();
   file.remove();
   temp.rename("networks.conf");
   readData();
}

/*** SLOT - Accept override to save global user info into file luxirc.conf ***/
void NetworkDlg::accept() {
   // Open luxirc.conf for reading
   QFile luxirc("luxirc.conf");
   if (!luxirc.open(QIODevice::WriteOnly | QIODevice::Text)) {
      qDebug() << "Unable to open luxirc.conf";
   }

   // Open temp file for writing
   QFile temp("temp");
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
   temp.rename("luxirc.conf");

   this->close();
}
