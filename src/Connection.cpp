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
	this->_network = "";
	this->_server = "";
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
	this->start();
}

/*** Connects to network. This function is ran in a new thread. ***/
void Connection::run() {
	QTcpSocket *socket = new QTcpSocket;

	// Attempt to connect to network
	if (!this->connected) {
		socket->connectToHost(_server, _port);	
	}
	
	// Wait for successful connection
	if (socket->waitForConnected(5000)) {
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
			"JOIN %1\r\n").arg(chansStr).toUtf8()
		);

		// Connection loop
		while (true) {
			// Wait for new data from network
			socket->waitForReadyRead();

			// Get number of bytes available to read
			bytesToRead = socket->bytesAvailable();

			// If data received
			if (bytesToRead > 0) {
				// Store data into a std::string, send to outputTE
				response = QString::fromUtf8(
					socket->read(bytesToRead)).toStdString();

				networkData.prepend(QString::fromStdString(response));

				// Parse data into QMultiMap<channel,message>
				parseChannels(networkData);

				emit dataAvailable(this);

				// Handle PING/PONG messages
				size_t spaceDelim = response.find(' ');
				if (response.substr(0, spaceDelim).compare("PING") == 0) {
					std::string pongStr = "PONG" + response.substr(spaceDelim);
					socket->write(pongStr.c_str());
				}
			}
			else {
				continue;
			}
		}
		socket->close();
		this->connected = false;
		delete socket;
	}
	else {
		networkData.push_back("Connection timed out...\n");
		emit dataAvailable(this);
	}
}

/*** Separate messages by channel ***/
void Connection::parseChannels(const QStringList &data) {
	for (int i=0; i<this->channels.size(); i++) {
		if (data.at(0).contains(QString("PRIVMSG " + 
		this->channels.at(i).getName()), Qt::CaseInsensitive)) {
			this->channels[i].pushMsg(data.at(0));
		}
		else if (data.at(0).contains(QString("NOTICE "), Qt::CaseInsensitive)) {
			this->pushNotice(data.at(0));
		}
	}
}

void Connection::setNetwork(QString &network) {
	this->_network = network;
}

void Connection::setServer(QString &server) {
	this->_server = server;
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
