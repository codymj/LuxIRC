/*
 * File:   ChangeNickDlg.cpp
 * Author: br0d1n
 *
 * Created on March 15, 2015, 11:11 PM
 */

#include "MainWindow.h"
#include "ChangeNickDlg.h"

ChangeNickDlg::ChangeNickDlg() {
	setupUi(this);

	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

ChangeNickDlg::~ChangeNickDlg() {
}
