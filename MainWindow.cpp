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
	nickname = changeNickBtn->text();

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
	changeNickDlg->newNickLE->setText(nickname);
	changeNickDlg->newNickLE->selectAll();
	changeNickDlg->exec();

	nickname = changeNickDlg->getNewNick();
	changeNickBtn->setText(nickname);

	// TODO:  Handle method to change nick via IRC protocol.

	delete changeNickDlg;
}

/*** SLOT - Open the Network Dialog ***/
void MainWindow::openNetworkDlg() {
	NetworkDlg *networkDlg = new NetworkDlg();
	networkDlg->exec();

	delete networkDlg;
}
