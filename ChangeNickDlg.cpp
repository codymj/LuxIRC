/*
 * ChangeNickDlg.cpp
 *
 * 	Created on Mar 15, 2015
 * 		Author: br0d1n
 */

#include "ChangeNickDlg.h"

ChangeNickDlg::ChangeNickDlg() {
	setupUi(this);

	// Set IRC nickname validator for QLineEdit
	QRegExp nickRegExp("[a-zA-Z\\[\\]\\`_\\^\\{\\|\\}][a-zA-Z0-9\\[\\]\\`_\\^\\{\\|\\}-]{1,31}");
	QValidator *nickValidator = new QRegExpValidator(nickRegExp, this);
	newNickLE->setValidator(nickValidator);
}

ChangeNickDlg::~ChangeNickDlg() {
}

void ChangeNickDlg::accept() {
	newNick = newNickLE->text();

	this->close();
}

QString ChangeNickDlg::getNewNick() {
	return newNick;
}
