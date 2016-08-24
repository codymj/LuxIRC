/******************************************************************************
 * Connection.cpp                                                             *
 *                                                                            *
 * Created on Jul 25, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#include "Connection.h"

/*******************************************************************************
Constructor
*******************************************************************************/
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

/*******************************************************************************
Destructor
*******************************************************************************/
Connection::~Connection() {
}

/*******************************************************************************
Connection is ready, start thread
*******************************************************************************/
void Connection::connectionReady() {
	// Start thread for this Connection
	if (!this->connected) {
		this->start();
	}
}

/*******************************************************************************
Connects to network. This function is ran in a new thread
*******************************************************************************/
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
		while (this->connected) {
			// Wait for new data from network
			socket->waitForReadyRead();

			// Make sure all data was received
			bytesToRead = socket->bytesAvailable();
			data = socket->read(bytesToRead);
			bytesRemaining = bytesToRead - data.size();
			while (bytesRemaining > 0) {
				if (!socket->waitForReadyRead()) {
					qDebug() << "ERROR: WaitForReadyRead timed out.";
					return;
				}
				data = socket->read(bytesRemaining);
				bytesRemaining -= data.size();
			}

			// If waitForReadyRead() times out, blank data is written
			if (data.isEmpty()) {
				continue;
			}

			// Handle PING
			if (data.contains("PING")) {
				// "PING :message" -> ["PING", ":message\r\n"]
				QList<QByteArray> pingSplit = data.split(' ');

				QByteArray pong = "PONG ";

				// Send in format: "PONG :message\r\n"
				pong.append(pingSplit.at(1));
				socket->write(QString(pong).toUtf8());

				// Restart loop, no need to parse this further
				continue;
			}

			// Use prepend to stick new data at the top
			networkData.prepend(QString::fromUtf8(data));

			// Parse data
			parseData(networkData);
			emit dataAvailable();
		}
		delete socket;
	}
	else {
		// Handle unable to connect
	}
	
	this->quit();
	emit deleteMe(this);
}

/*******************************************************************************
Parse data into prefix, command and args for processing
":test!~test@test.com PRIVMSG #channel :Hi!"
 -------prefix------- command ----args-----
*******************************************************************************/
void Connection::parseData(const QStringList &data) {
	qDebug() << data.at(0);
	QString prefix;
	QString command;
	QStringList trailing;
	QStringList args;

	// Get prefix
	if (data.at(0).at(0) == ':') {
		prefix = data.at(0).section(' ', 0, 0); // :test!~test@test.com
		prefix.remove(':');						// test!~test@test.com
	}

	// Get command & args
	if (data.at(0).contains(" :", Qt::CaseInsensitive)) {
		trailing = data.at(0).split(" :");
		// [":test!~test@test.com PRIVMSG #channel", "Hi!"]
		
		QStringList temp = trailing.at(0).split(' ');
		// [":test!~test@test.com", "PRIVMSG", "#channel"]
		
		temp.removeFirst();				// ["PRIVMSG", "#channel"]
		command = temp.takeFirst();		// "PRIVMSG"
		trailing.removeFirst();			// ["Hi!"]
		args << temp << trailing;		// ["#channel", "Hi!"]
	}

	QStringList parsedData;
	if (!prefix.isEmpty()) {
		parsedData << prefix;
	}
	if (!command.isEmpty()) {
		parsedData << command;
	}
	if (!args.isEmpty()) {
		parsedData << args;
	}
	processData(parsedData);
}

/*******************************************************************************
Processes the data that has been parsed
data = ["test!~test@test.com", "PRIVMSG", "#channel", "Hi!", ...]
*******************************************************************************/
void Connection::processData(const QStringList &data) {
	// Command = "PRIVMSG"
	if (data.at(1) == "PRIVMSG") {
		bool found = false;

		// Check if Channel already exists
		for (int i=0; i<this->channels.size(); i++) {
			// If so, append messages for that channel
			if (data.at(2) == this->channels.at(i)->getName()) {
				found = true;
				QString msg = data.at(0);
				msg += ": ";
				msg += data.at(3);
				this->channels.at(i)->pushMsg(msg);
				break;
			}
		}

		// Message from Channel not already in the channel list
		if (!found) {
			Channel *chan = new Channel;
			chan->setName(data.at(2));
			QString msg = data.at(0);
			msg += ": ";
			msg += data.at(3);
			chan->pushMsg(msg);
			this->channels.append(chan);
			emit newChannel(this, chan);
		}
	}

	// Command = "NOTICE"
	else if (data.at(1) == "NOTICE") {
		QString notice = data.at(0);
		notice += ": ";
		notice += data.at(3);
		this->pushNotice(notice);
	}

	// Command = "PING"
	
}

/*******************************************************************************
Sets the Connection to disconnected status
*******************************************************************************/
void Connection::disconnect() {
	this->connected = false;
}

/*******************************************************************************
Get'ers & set'ers
*******************************************************************************/
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

void Connection::setNick(const QString &nick) {
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

QString Connection::getNick() const {
	return this->_nick;
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
