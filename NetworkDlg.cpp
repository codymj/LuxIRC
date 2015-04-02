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

/*** Populates networkList with networks from 'networks.conf' file ***/
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
	networkList->setCurrentRow(0);
}
