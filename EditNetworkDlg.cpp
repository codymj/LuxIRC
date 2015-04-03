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
#include "NetworkDlg.h"

EditNetworkDlg::EditNetworkDlg(QString &networkName) {
    setupUi(this);

    // Set 1-99999 validator for port QLineEdit and set default port '6667'
    QRegExp portRegExp("[1-9]\\d{0,4}");
    QValidator *portValidator = new QRegExpValidator(portRegExp, this);
    portLE->setValidator(portValidator);
    portLE->setText("6667");

    // Ticking 'Use Global Information' disables per-network user info
    connect(globalInfoCkb, SIGNAL(toggled(bool)), this, SLOT(toggleUserInfo()));

    // Read in data from file
    readData(networkName);

	// Disable editing of network name
	networkLE->setEnabled(false);
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

/*** Inputs data from file into data widgets ***/
void EditNetworkDlg::populateData(QString &line) {
    QString id = line.left(2);      // First two chars in line (identifier) ex. N=
    QString lineData = line.mid(2); // The data on the rest of the line
	lineData = lineData.trimmed();

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

/*** Writes data from data widgets to file ***/
void EditNetworkDlg::writeData() {
	QFile file("networks.conf");
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Creating networks.conf file since it did not exist.";
	}

	QFile temp("temp");
	if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
		qDebug() << "Creating temp file for writing.";
	}

	QTextStream write(&temp);

	QString networkName = networkLE->text();
	QString line;
	while (!file.atEnd()) {
		line = file.readLine();

		// Found network to edit
		if (line.mid(2).trimmed() == networkName) {
			streamDataIntoFile(write);

			// Skip previous data for network
			while (line.left(2) != "\n") {
				line = file.readLine();
				if (line.isNull()) { break; }	// If data is at end of file
			}
			line = file.readLine();
		}
		write << line;
	}
	file.close();
	temp.close();
	file.remove();
	temp.rename("networks.conf");
}

/*** Helper method to stream data into a file ***/
void EditNetworkDlg::streamDataIntoFile(QTextStream &write) {
	write << "N=" + networkLE->text() + '\n';
	write << "S=" + serverLE->text() + '\n';
	write << "p=" + portLE->text() + '\n';
	write << "I=" + nickLE->text() + '\n';
	write << "i=" + nick2LE->text() + '\n';
	write << "U=" + usernameLE->text() + '\n';
	write << "R=" + realNameLE->text() + '\n';
	write << "L=" + QString::number(loginMethodCbo->currentIndex()) + '\n';
	write << "P=" + passwordLE->text() + '\n';
	write << "J=" + joinChansLE->text() + '\n';
	write << "c=" + QString::number(connectCkb->isChecked()) + '\n';
	write << "n=" + QString::number(sslCkb->isChecked()) + '\n';
	write << "a=" + QString::number(invalidCertCkb->isChecked()) + '\n';
	write << "g=" + QString::number(globalInfoCkb->isChecked()) + "\n\n";
}

/*** SLOT - Called when 'save' button is clicked ***/
void EditNetworkDlg::accept() {
	writeData();
	this->close();
}

/*** SLOT - Use global user info or per-server info ***/
void EditNetworkDlg::toggleUserInfo() {
	// Open luxirc.conf for reading
	QFile luxirc("luxirc.conf");
	if (!luxirc.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "Unable to open luxirc.conf";
	}

	QString line;
	QString nick;
	QString nick2;
	QString username;
	QString realName;

	// Load global user info into NetworkDlg
	while (!luxirc.atEnd()) {
		line = luxirc.readLine();
		if (line.left(2) == "I=") {
			nick = line.mid(2).trimmed();
		}
		if (line.left(2) == "i=") {
			nick2 = line.mid(2).trimmed();
		}
		if (line.left(2) == "U=") {
			username = line.mid(2).trimmed();
		}
		if (line.left(2) == "R=") {
			realName = line.mid(2).trimmed();
		}
	}

	if (globalInfoCkb->isChecked()) {
		nickLE->setText(nick);
		nickLE->setEnabled(false);
		nick2LE->setText(nick2);
		nick2LE->setEnabled(false);
		usernameLE->setText(username);
		usernameLE->setEnabled(false);
		realNameLE->setText(realName);
		realNameLE->setEnabled(false);
	}
	else {
		nickLE->setEnabled(true);
		nickLE->clear();
		nick2LE->setEnabled(true);
		nick2LE->clear();
		usernameLE->setEnabled(true);
		usernameLE->clear();
		realNameLE->setEnabled(true);
		realNameLE->clear();
	}

	luxirc.close();
}
