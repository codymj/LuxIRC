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
	this->_chanList << "#lounge";
	this->_connectAtStart = false;
	this->_useGlobalInfo = true;
}

/*** Destructor ***/
Connection::~Connection() {

}

/*** Connection is ready ***/
void Connection::connectToNetwork() {
	this->run();
}

/*** Connects to network. This function is ran in a new thread. ***/
void Connection::run() {
	std::string response;

	// Attempt to connect to network
	_socket.connectToHost(_server, _port);
	if (_socket.waitForConnected(5000)) {
		// Send initial IRC information
		_socket.write(QString("NICK %1\r\n").arg(_nick).toUtf8());
		_socket.write(QString("USER %1 0 * :%2\r\n").arg(_username,_realName).toUtf8());
		_socket.write(QString("JOIN %1\r\n").arg(_chanListStr).toUtf8());

		// Connection loop
		while (true) {
			// Wait for new data from network
			_socket.waitForReadyRead();
			response = _socket.readAll().toStdString();
			emit dataReady(this->getNetwork(), networkData);

			// If data received
			if (!response.empty()) {
				// Store in our QString for access by outputTE
				networkData = QString::fromStdString(response);
				emit dataReady(this->getNetwork(), networkData);

				// Handle PING/PONG messages
				size_t spaceDelim = response.find(' ');
				if (response.substr(0, spaceDelim).compare("PING") == 0) {
					std::string pongStr = "PONG" + response.substr(spaceDelim);
					_socket.write(pongStr.c_str());
				}
			}
		}
		_socket.close();
	}
	else {
		networkData.push_back("Connection timed out...\n");
		emit dataReady(this->getNetwork(), networkData);
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

void Connection::setChanList(QString &chanList) {
	this->_chanListStr = chanList;
	this->_chanList << chanList.split(',');
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

QList<QString> Connection::getChanList() const {
	return this->_chanList;
}

QString Connection::getServer() const {
	return this->_server;
}