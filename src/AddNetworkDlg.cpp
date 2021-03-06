// =============================================================================
// AddNetworkDlg.cpp
//
// Created on: Mar 21, 2015
// Author: Cody Johnson <codyj@mail.usf.edu>
// =============================================================================
#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QDir>
#include <QtCore/QFile>
#include <QtCore/QRegExp>
#include <QtCore/QString>
#include <QtCore/QTextStream>
#include <QtGui/QRegExpValidator>
#include <QtWidgets/QMessageBox>
#include "AddNetworkDlg.h"

// Constructor
// -----------------------------------------------------------------------------
AddNetworkDlg::AddNetworkDlg() {
    setupUi(this);

    // Set 1-99999 validator for port QLineEdit and set default port '6667'
    QRegExp portRegExp("[1-9]\\d{0,4}");
    QValidator *portValidator = new QRegExpValidator(portRegExp, this);
    portLE->setValidator(portValidator);
    portLE->setText("6667");

    // TODO: Set a nick name validator

    // Ticking 'Use Global Information' disables per-network user info
    connect(globalInfoCkb, SIGNAL(toggled(bool)), this, SLOT(toggleUserInfo()));
}


// Destructor
// -----------------------------------------------------------------------------
AddNetworkDlg::~AddNetworkDlg() {
}


// Writes data from data widgets to file
// -----------------------------------------------------------------------------
void AddNetworkDlg::writeData() {
    QDir config("./config");
    if (!config.exists()) {
        qDebug() << "Creating /config directory.";
        config.mkdir("config");
    }

    QFile networks("config/networks.conf");
    if (!networks.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Creating networks.conf file since it did not exist.";
    }

    QFile temp("config/temp");
    if (!temp.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Creating temp file for writing.";
    }

    QTextStream write(&temp);

    // Make sure network doesn't already exist, if exists, ask to overwrite
    QString networkName = networkLE->text();
    QString line;
    while (!networks.atEnd()) {
        line = networks.readLine();

        // Network already in file, ask to overwrite
        if (line.mid(2).trimmed() == networkName) {
            QMessageBox msgBox;
            msgBox.setText("This network already exists.");
            msgBox.setInformativeText("Overwrite?");
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Cancel);

            int rtrn = msgBox.exec();
            switch (rtrn) {
                case QMessageBox::Ok:
                    streamDataIntoFile(write);
                    // Skip previous data for network
                    while (line.left(2) != "\n") {
                        line = networks.readLine();
                        if (line == 0) {
                            break;
                        }
                    }
                    // Write rest of the file into temp
                    while (!networks.atEnd()) {
                        line = networks.readLine();
                        write << line;
                        line = line.trimmed();
                    }
                    networks.close();
                    temp.close();
                    networks.remove();
                    temp.rename("config/networks.conf");
                    return;
                case QMessageBox::Cancel:
                    return;
            }
        }
        write << line;
    }

    // Network was not found in file, entering new network info to file
    streamDataIntoFile(write);
    networks.close();
    temp.close();
    networks.remove();
    temp.rename("config/networks.conf");
}


// Helper method to stream data into a file
// -----------------------------------------------------------------------------
void AddNetworkDlg::streamDataIntoFile(QTextStream &write) {
    write << '\n';
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
    write << "g=" + QString::number(globalInfoCkb->isChecked()) + "\n";
}


// SLOT - Called when 'save' button is clicked
// -----------------------------------------------------------------------------
void AddNetworkDlg::accept() {
    writeData();
    this->close();
}


// SLOT - Use global user info or per-server info
// -----------------------------------------------------------------------------
void AddNetworkDlg::toggleUserInfo() {
    // Open luxirc.conf for reading
    QFile luxirc("config/luxirc.conf");
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
    } else {
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
