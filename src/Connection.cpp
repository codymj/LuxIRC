/******************************************************************************
 * Connection.cpp                                                             *
 *                                                                            *
 * Created on Jul 25, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#include "Connection.h"

/*** Default Constructor ***/
Connection::Connection() {
	// Initialize private data members to defaults
	this->_network = "Freenode";
	this->_server = "irc.freenode.net";
	this->_chansStr = "#LuxIRC,#qt";
	this->_port = 6667;
	this->_nick = "LuxIRCUser";
	this->_nick2 = "LuxIRCUser2";
	this->_username = "LuxIRC";
	this->_realName = "LuxIRC - A Qt/C++ IRC Client";
	this->_loginMethod = 0;
	this->_password = "";
	this->_connectAtStart = false;
	this->_useGlobalInfo = true;

	// Connect signals/slots
	connect(
		this, SIGNAL(finished()),
		this, SLOT(deleteLater())
	);

	this->connected = false;
}

/*** Destructor ***/
Connection::~Connection() {
}

/*** Connection is ready ***/
void Connection::connectionReady() {
	// Start thread for this Connection
	if (!this->connected) {
		this->start();
	}
}

/*** Connects to network. This function is ran in a new thread. ***/
void Connection::run() {
	QTcpSocket *socket = new QTcpSocket;

	// Attempt to connect to network
	socket->connectToHost(_server, _port);	
	if (socket->waitForConnected()) {
		// Mark this as connected
		this->connected = true;

		// Send initial IRC information
		socket->write(QString(
			"NICK %1\r\n").arg(_nick).toUtf8()
		);
		socket->write(QString(
			"USER %1 0 * :%2\r\n").arg(_username,_realName).toUtf8()
		);
		socket->write(QString(
			"JOIN %1\r\n").arg(_chansStr).toUtf8()
		);

		// Connection loop
		while (true) {
			if (!this->connected) {
				break;
			}

			// Wait for new data from network
			socket->waitForReadyRead(1000);

			// Get number of bytes available to read
			bytesToRead = socket->bytesAvailable();

			// If data received
			if (bytesToRead > 0) {
				// Store data into a std::string
				response = QString::fromUtf8(
					socket->read(bytesToRead)).toStdString();

				// Use prepend to stick new data at the top
				networkData.prepend(QString::fromStdString(response));

				// Parse data by channel
				parseChannels(networkData);
				emit dataAvailable();

				// Handle PING/PONG messages
				size_t spaceDelim = response.find(' ');
				if (response.substr(0, spaceDelim).compare("PING") == 0) {
					std::string pongStr = "PONG" + response.substr(spaceDelim);
					socket->write(pongStr.c_str());
				}
			}

			// Otherwise, keep waiting for data
			else {
				continue;
			}
		}
		delete socket;
	}
	else {
		// Handle unable to connect
	}
	this->quit();
	emit deleteMe(this);
}

/*** Separate messages by channel ***/
void Connection::parseChannels(const QStringList &data) {
	for (int i=0; i<this->channels.size(); i++) {
		// If data is a channel/user message
		if (data.at(0).contains(QString(
		"PRIVMSG " + this->channels.at(i)->getName()), Qt::CaseInsensitive)) {
			this->channels.at(i)->pushMsg(data.at(0));
		}

		// Otherwise, it is a server notice. Break to prevent duplicate lines
		else if (data.at(0).contains(QString("NOTICE "), Qt::CaseInsensitive)) {
			this->pushNotice(data.at(0));
			break;
		}

		// Handle any other data here if necessary
		else {
			return;
		}
	}
}

void Connection::disconnect() {
	this->connected = false;
}

void Connection::setNetwork(QString &network) {
	this->_network = network;
}

void Connection::setServer(QString &server) {
	this->_server = server;
}

void Connection::setChans(QString &chans) {
	this->_chansStr = chans;
}

void Connection::setPort(int port) {
	this->_port = port;
}

void Connection::setNick(QString &nick) {
	this->_nick = nick;
}

void Connection::setNick2(QString &nick2) {
	this->_nick2 = nick2;
}

void Connection::setUsername(QString &username) {
	this->_username = username;
}

void Connection::setRealName(QString &realName) {
	this->_realName = realName;
}

void Connection::setLoginMethod(int lm) {
	this->_loginMethod = lm;
}

void Connection::setPassword(QString &pass) {
	this->_password = pass;
}

void Connection::setConnectAtStart(bool &b) {
	this->_connectAtStart = b;
}

void Connection::setUseGlobalInfo(bool &b) {
	this->_useGlobalInfo = b;
}

void Connection::setUseSSL(bool &b) {
	this->_useSSL = b;
}

void Connection::setAcceptInvalidSSLCert(bool &b) {
	this->_acceptInvalidSSLCert = b;
}

QString Connection::getNetwork() const {
	return this->_network;
}

QString Connection::getServer() const {
	return this->_server;
}

void Connection::pushNotice(const QString msg) {
	this->_notices << msg;
}

QStringList Connection::getNotices() const {
	return this->_notices;
}

void Connection::setSliderVal(int val) {
	this->_sliderVal = val;
}

int Connection::getSliderVal() const {
	return this->_sliderVal;
}

void Connection::setSliderMaxed(bool b) {
	this->_sliderMaxed = b;
}

bool Connection::isSliderMaxed() const {
	return this->_sliderMaxed;
}
