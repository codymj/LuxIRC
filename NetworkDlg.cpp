/*
 * NetworkDlg.cpp
 *
 *  Created on: Mar 19, 2015
 *      Author: br0d1n
 */

#include "NetworkDlg.h"
#include "AddNetworkDlg.h"

NetworkDlg::NetworkDlg() {
	setupUi(this);

	connect(addBtn, SIGNAL(clicked()), this, SLOT(openAddNetworkDlg()));
}

NetworkDlg::~NetworkDlg() {
}

/*** SLOT - Open the AddNetworkDlg ***/
void NetworkDlg::openAddNetworkDlg() {
	AddNetworkDlg *addNetworkDlg = new AddNetworkDlg();

	if (addNetworkDlg->exec()) {
		// TODO: Handle the addition of networks into a file.
	}

	delete addNetworkDlg;
}
