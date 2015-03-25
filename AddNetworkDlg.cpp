/*
 * AddNetworkDlg.cpp
 *
 *  Created on: Mar 21, 2015
 *      Author: br0d1n
 */

#include <QRegExp>
#include <QRegExpValidator>
#include "AddNetworkDlg.h"

AddNetworkDlg::AddNetworkDlg() {
    setupUi(this);
    
    // Set 1-99999 validator for port line edit
    QRegExp portRegExp("[1-9]\\d{0,4}");
    QValidator *portValidator = new QRegExpValidator(portRegExp, this);
    portLE->setValidator(portValidator);
    
    // Ticking 'Use Global Information' disables per network user info
    connect(globalInfoCkb, SIGNAL(toggled(bool)), this, SLOT(toggleUserInfo()));
}

AddNetworkDlg::~AddNetworkDlg() {
}

/*** SLOT - This updates specific changes to the widget ***/
void AddNetworkDlg::updateWidget() {
}

/*** SLOT - Called from updateWidget() to use global user info or not ***/
void AddNetworkDlg::toggleUserInfo() {
    if (globalInfoCkb->isChecked()) {
        nickLE->setEnabled(false);
        nick2LE->setEnabled(false);
        usernameLE->setEnabled(false);
        realNameLE->setEnabled(false);
    }
    else {
        nickLE->setEnabled(true);
        nick2LE->setEnabled(true);
        usernameLE->setEnabled(true);
        realNameLE->setEnabled(true);
    }
}
