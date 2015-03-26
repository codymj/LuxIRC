/*
 * AddNetworkDlg.cpp
 *
 *  Created on: Mar 21, 2015
 *      Author: br0d1n
 */

#include <QByteArray>
#include <QFile>
#include <QRegExp>
#include <QRegExpValidator>
#include <QTextStream>
#include "AddNetworkDlg.h"

AddNetworkDlg::AddNetworkDlg() {
    setupUi(this);
    
    // Set 1-99999 validator for port QLineEdit and set default port '6667'
    QRegExp portRegExp("[1-9]\\d{0,4}");
    QValidator *portValidator = new QRegExpValidator(portRegExp, this);
    portLE->setValidator(portValidator);
    portLE->setText("6667");
    
    // Ticking 'Use Global Information' disables per-network user info
    connect(globalInfoCkb, SIGNAL(toggled(bool)), this, SLOT(toggleUserInfo()));
}

AddNetworkDlg::~AddNetworkDlg() {
}

/*** Writes data from Network struct to file ***/
void AddNetworkDlg::writeData() {
    
}

/*** SLOT - Use global user info or per-server info ***/
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
