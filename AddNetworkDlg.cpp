/*
 * AddNetworkDlg.cpp
 *
 *  Created on: Mar 21, 2015
 *      Author: br0d1n
 */

#include "AddNetworkDlg.h"

AddNetworkDlg::AddNetworkDlg() {
    setupUi(this);
    
    connect(globalInfoCkb, SIGNAL(toggled(bool)), this, SLOT(updateWidget()));
}

AddNetworkDlg::~AddNetworkDlg() {
}

/*** SLOT - This updates specific changes to the widget ***/
void AddNetworkDlg::updateWidget() {
    toggleServerInfo();
}

/*** SLOT - Called from updateWidget() to use global user info or not ***/
void AddNetworkDlg::toggleServerInfo() {
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
