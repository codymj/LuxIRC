/*
 * File:   MainWindow.cpp
 * Author: br0d1n
 *
 * Created on March 15, 2015, 11:09 PM
 */

#include <QString>
#include <QList>
#include "MainWindow.h"

MainWindow::MainWindow() {
	setupUi(this);

	nickName = changeNickBtn->text();

	// Resize the splitter so the widgets look more aesthetic.
	// sizeList << chanView size << centralWidget size << nickView size;
	QList<int> sizeList;
	sizeList << 150 << 450 << 150;
	splitter->setSizes(sizeList);

	connect(changeNickBtn, SIGNAL(clicked()), this, SLOT(changeNick()));
}

MainWindow::~MainWindow() {
}

/*** SLOT .:. Change nickname ***/
void MainWindow::changeNick() {
	ChangeNickDlg changeNickDlg;
	changeNickDlg.newNickLineEdit->setText(nickName);
	changeNickDlg.newNickLineEdit->selectAll();
	changeNickDlg.show();
	changeNickDlg.raise();
	changeNickDlg.activateWindow();

	if (changeNickDlg.exec()) {
		// TODO: Handle blank line edit...
		nickName = changeNickDlg.newNickLineEdit->text();
		changeNickBtn->setText(nickName);
	}

	// TODO:  Handle method to change nick via IRC protocol.
}
