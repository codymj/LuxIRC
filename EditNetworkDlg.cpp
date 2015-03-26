/*
 * EditNetworkDlg.cpp
 *
 *  Created on: Mar 21, 2015
 *      Author: br0d1n
 */

#include <QByteArray>
#include <QDebug>
#include <QFile>
#include <QRegExp>
#include <QRegExpValidator>
#include <QTextStream>
#include "EditNetworkDlg.h"

EditNetworkDlg::EditNetworkDlg(QString &networkName) {
    setupUi(this);
    
    //QString network = networkName;
    
    // Set 1-99999 validator for port QLineEdit and set default port '6667'
    QRegExp portRegExp("[1-9]\\d{0,4}");
    QValidator *portValidator = new QRegExpValidator(portRegExp, this);
    portLE->setValidator(portValidator);
    portLE->setText("6667");
    
    // Ticking 'Use Global Information' disables per-network user info
    connect(globalInfoCkb, SIGNAL(toggled(bool)), this, SLOT(toggleUserInfo()));
    
    // Read in data from file
    readData(networkName);
}

EditNetworkDlg::~EditNetworkDlg() {
}

/*** Reads data from a file for specific network and loads data into data fields ***/
void EditNetworkDlg::readData(QString &networkName) {
    QFile file("networks.conf");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error opening 'networks.conf'";
    }

    // Loop until selected network is found
    QString line;
    while (!file.atEnd()) {
        line = file.readLine();
        line = line.trimmed();
        if (line.mid(2) == networkName) {
            qDebug() << networkName;
            // Network found. Parse info until the next blank line
            while (line != "\n") {
                populateData(line);
                line = file.readLine();
                // A hack -- for some reason file.atEnd() isn't breaking loop
                if (line == 0) {
                    break;
                }
            }
        }
    }
    file.close();
}

/*** Inputs data from file into a Network struct ***/
void EditNetworkDlg::populateData(QString &line) {
    QString id = line.left(2);      // First two chars in line (identifier) ex. N=
    QString lineData = line.mid(2); // The data on the rest of the line
    
    if (id == "N=") {networkLE->setText(lineData);}
    else if (id == "S=") {serverLE->setText(lineData);}
    else if (id == "p=") {portLE->setText(lineData);}
    else if (id == "I=") {nickLE->setText(lineData);}
    else if (id == "i=") {nick2LE->setText(lineData);}
    else if (id == "U=") {usernameLE->setText(lineData);}
    else if (id == "R=") {realNameLE->setText(lineData);}
    else if (id == "L=") {loginMethodCbo->setCurrentIndex(lineData.toInt());}
    else if (id == "P=") {passwordLE->setText(lineData);}
    else if (id == "J=") {joinChansLE->setText(lineData);}
    else if (id == "c=") {
        bool cBool;
        int lineToInt = lineData.toInt();
        if (lineToInt == 0) {cBool = 0;} 
        else {cBool = 1;}
        connectCkb->setChecked(cBool);
    }
    else if (id == "n=") {
        bool nBool;
        int lineToInt = lineData.toInt();
        if (lineToInt == 0) {nBool = 0;}
        else {nBool = 1;}
        sslCkb->setChecked(nBool);
    }
    else if (id == "a=") {
        bool aBool;
        int lineToInt = lineData.toInt();
        if (lineToInt == 0) {aBool = 0;}
        else {aBool = 1;}
        invalidCertCkb->setChecked(aBool);
    }
    else if (id == "g=") {
        bool gBool;
        int lineToInt = lineData.toInt();
        if (lineToInt == 0) {gBool = 0;}
        else {gBool = 1;}
        globalInfoCkb->setChecked(gBool);
    }
    else if (line == "\n") {
        return;
    }
    else {qDebug() << "Error in EditNetworkDlg::populateData";}
}

/*** Writes data from Network struct to file ***/
void EditNetworkDlg::writeData() {
    
}

/*** SLOT - Use global user info or per-server info ***/
void EditNetworkDlg::toggleUserInfo() {
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
