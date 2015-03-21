/*
 * MainWindow.cpp
 *
 * 	Created on Mar 15, 2015
 * 		Author: br0d1n
 */

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
	connect(openNetworkDlgAction, SIGNAL(triggered()), this, SLOT(openNetworkDlg()));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
	connect(changeNickBtn, SIGNAL(clicked()), this, SLOT(changeNick()));
}

/*** SLOT - Change nickname ***/
void MainWindow::changeNick() {
	ChangeNickDlg *changeNickDlg = new ChangeNickDlg();
	changeNickDlg->newNickLineEdit->setText(nickName);
	changeNickDlg->newNickLineEdit->selectAll();

	if (changeNickDlg->exec()) {
		// TODO: Handle blank line edit...
		nickName = changeNickDlg->newNickLineEdit->text();
		changeNickBtn->setText(nickName);
	}

	// TODO:  Handle method to change nick via IRC protocol.

	delete changeNickDlg;
}

/*** SLOT - Open the Network Dialog ***/
void MainWindow::openNetworkDlg() {
	NetworkDlg *networkDlg = new NetworkDlg();

	if (networkDlg->exec()) {
		// TODO: Handle saving of networks (should I do this in MainWindow or NetworkDlg?)
	}

	delete networkDlg;
}
