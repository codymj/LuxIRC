/*
 * NetworkDlg.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: br0d1n
 */

#include <QDebug>
#include <QFile>
#include <QListWidgetItem>
#include <QString>
#include "NetworkDlg.h"
#include "EditNetworkDlg.h"

NetworkDlg::NetworkDlg() {
    setupUi(this);

    connect(addBtn, SIGNAL(clicked()), this, SLOT(openAddNetworkDlg()));
    connect(editBtn, SIGNAL(clicked()), this, SLOT(openEditNetworkDlg()));
	connect(removeBtn, SIGNAL(clicked()), this, SLOT(removeNetwork()));
    connect(networkList, SIGNAL(itemSelectionChanged()), this, SLOT(selectNetwork()));

	readData();
}

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
    QFile file("networks.conf");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error opening 'networks.conf'";
        return;
    }

	// Clear networkList first
	networkList->clear();

    // Loop until all networks are found
    while (!file.atEnd()) {
        QString line = file.readLine();
        if (line.left(2) == "N=") {
            QString networkStr = line.mid(2);
            networkStr = networkStr.trimmed();
            networkList->addItem(networkStr);
        }
    }
    file.close();
	networkList->sortItems();
	networkList->setCurrentRow(0);
}

/*** SLOT - Removes a network from the network list ***/
void NetworkDlg::removeNetwork() {
	QFile file("networks.conf");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Creating networks.conf file since it did not exist.";
	}

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
				if (line == "") { break; }	// If data is at end of file
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
