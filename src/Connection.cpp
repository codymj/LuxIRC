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
	this->_partMsg = "Leaving.";
	this->_quitMsg = "Quitting.";
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
Delete all Channels for this Connection
*******************************************************************************/
void Connection::sendQuit() {
	QByteArray data = (QString(
		"QUIT %1\r\n").arg(_partMsg).toUtf8()
	);
	dataForWriting.enqueue(data);
	disconnect();
}

/*******************************************************************************
Leaves a Channel
*******************************************************************************/
void Connection::partChannel(Channel *chan) {
	QByteArray data = (QString(
		"PART %1 %2\r\n").arg(chan->getName(),_partMsg).toUtf8()
	);

	// Remove Channel from channels list
	for (int i=0; i<channels.size(); i++) {
		if (channels.at(i) == chan) {
			dataForWriting.enqueue(data);
			delete channels.takeAt(i);
			break;
		}
	}

	emit channelListChanged(this);
}

/*******************************************************************************
Delete all Channels for this Connection
*******************************************************************************/
void Connection::deleteAllChannels() {
	for (int i=0; i<channels.size(); i++) {
		QByteArray data = (QString(
			"PART %1 %2\r\n").arg(channels.at(i)->getName(),_partMsg).toUtf8()
		);
		dataForWriting.enqueue(data);
		delete channels.takeAt(i);
	}
}

/*******************************************************************************
Connects to network. This function is ran in a new thread
*******************************************************************************/
void Connection::run() {
	socket = new QTcpSocket;

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
		if (!_chansStr.isEmpty()) {
			socket->write(QString(
				"JOIN %1\r\n").arg(_chansStr).toUtf8()
			);
		}

		// Connection loop
		while (true) {
			// Wait for new data from network
			socket->waitForReadyRead(1000);

			// Check if we have any data to write, and if so, send to host
			if (!dataForWriting.isEmpty()) {
				while (!dataForWriting.isEmpty()) {
					QByteArray data = dataForWriting.dequeue();
					socket->write(data);
				}
			}

			// Check for available data and read
			bytesToRead = socket->bytesAvailable();
			data = socket->read(bytesToRead);
			
			// If waitForReadyRead() times out, no data is received
			if (data.isEmpty()) {
				continue;
			}

			// Ensure all data received is in full chunks ending with "\r\n"
			while (!data.endsWith("\r\n")) {
				if (!socket->waitForReadyRead(60000)) {
					qDebug() << "WaitForReadyRead timed out.";
					continue;
				}
				bytesToRead = socket->bytesAvailable();
				data.append(socket->read(bytesToRead));
			}

			// Handle PING
			if (data.contains("PING :")) {
				// "PING :message\r\n" -> ["PING", ":message\r\n"]
				QList<QByteArray> pingSplit = data.split(' ');

				// Send in format: "PONG :message\r\n"
				QByteArray pong = "PONG ";
				pong.append(pingSplit.at(1));
				socket->write(QString(pong).toUtf8());

				// Restart loop, no need to parse this further
				continue;
			}

			// Parse data
			QString dataStr = QString::fromUtf8(data);
			dataLines = dataStr.split("\r\n");
			for (int i=0; i<dataLines.size(); i++) {
				if (!dataLines.at(i).isEmpty()) {
					parseData(dataLines.at(i));
					emit dataAvailable();
				}
			}

			// Check if we're still connected
			if (!connected) {
				socket->disconnectFromHost();
				break;
			}
		}
	}
	else {
		// Handle unable to connect
	}

	delete socket;
	this->quit();
	emit deleteMe(this);
}

/*******************************************************************************
Parse data into prefix, command and args for processing
":test!~test@test.com PRIVMSG #channel :Hi!"
 -------prefix------- command ----args-----
*******************************************************************************/
void Connection::parseData(const QString &data) {
	qDebug() << data;
	QString prefix;
	QString command;
	QStringList trailing;
	QStringList args;
	QStringList parsedData;

	// Get network's max nick length to pad nicks with spaces (for style)
	if (data.contains("NICKLEN=", Qt::CaseInsensitive)) {
		QString temp = data.section("NICKLEN=", 1, 1);
		maxNickLength = temp.section(' ', 0, 0).toInt();
	}

	// Store hostname
	QString hostnameMatcher = QString(":" + _nick + "!~" + _username + "@");
	if (data.contains(hostnameMatcher, Qt::CaseInsensitive)) {
		_myHostname = data.section(' ', 0, 0);
		qDebug() << _myHostname;
	}

	// Get prefix
	if (data.at(0) == ':') {
		prefix = data.section(' ', 0, 0);	// :test!~test@test.com
		prefix.remove(':');					// test!~test@test.com
	}
	else {
		qDebug() << data;
		this->pushNotice(data);
		return;
	}

	// Get command & args
	if (data.contains(" :", Qt::CaseInsensitive)) {
		trailing = data.split(" :");
		// [":test!~test@test.com PRIVMSG #channel", "Hi!", ...]
		
		QStringList temp = trailing.at(0).split(' ');
		// [":test!~test@test.com", "PRIVMSG", "#channel"]
		
		temp.removeFirst();				// ["PRIVMSG", "#channel"]
		command = temp.takeFirst();		// "PRIVMSG"
		trailing.removeFirst();			// ["Hi!", ...]
		args << temp << trailing;		// ["#channel", "Hi!", ...]
	}
	else {
		// [":test!~test@test.com", "JOIN", "#channel", ...]
		trailing = data.split(' ');
		
		trailing.removeFirst();			// ["JOIN", "#channel", ...]
		command = trailing.takeFirst();	// "JOIN"
		args << trailing;				// ["#channel", ...]
	}

	// Assemble parsed data for processing. Empty/NULL = segfault!
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
Parses user's nick name from source string:
test!~testing@tested.com -> test
*******************************************************************************/
QString Connection::parseNick(const QString &user) const {
	QString nick = user.section('!', 0, 0);
	return nick;
}

/*******************************************************************************
Processes the data that has been parsed
data = ["test!~test@test.com", "PRIVMSG", "#channel", "Hi!", ...]
*******************************************************************************/
void Connection::processData(const QStringList &data) {
	// Command = 375 (Start of MOTD)
	// Command = 376 (End of MOTD)
	// Command = 372 (MOTD)
	if (data.at(1) == "375" || data.at(1) == "376" || data.at(1) == "372") {
		this->pushNotice(QString(data.at(3) + "\n"));
	}

	// Command = 332 (TOPIC)
	else if (data.at(1) == "332" || data.at(1) == "TOPIC") {
		if (data.at(1) == "332") {
			for (int i=0; i<this->channels.size(); i++) {
				if (data.at(3) == this->channels.at(i)->getName()) {
					this->channels.at(i)->setTopic(data.at(4));
					emit topicChanged(this->channels.at(i));
					break;
				}
			}
		}
		if (data.at(1) == "TOPIC") {
			for (int i=0; i<this->channels.size(); i++) {
				if (data.at(2) == this->channels.at(i)->getName()) {
					this->channels.at(i)->setTopic(data.at(3));
					emit topicChanged(this->channels.at(i));
					break;
				}
			}
		}
	}

	// Command = 353 (/NAMES list)
	// ":asimov.freenode.net 353 user6789 = ##math :name0 name1 name2 ..."
	//  ----------0--------- -1- ----2--- 3 --4--- --------5-------------
	else if (data.at(1) == "353") {
		QString userListStr = data.at(5);
		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(4) == this->channels.at(i)->getName()) {
				this->channels.at(i)->populateUserList(userListStr);
				break;
			}
		}
	}

	// Command = 366 (End of /NAMES list)
	// ":leguin.freenode.net 366 user6789 ##math :End of /NAMES list."
	//  -----------0-------- -1- ----2--- --3--- ---------4----------
	else if (data.at(1) == "366") {
		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(3) == this->channels.at(i)->getName()) {
				this->channels.at(i)->parseUserList();
				break;
			}
		}
	}

	// Command = "NICK"
	else if (data.at(1) == "NICK") {
		QString nick = parseNick(data.at(0));
		QString msg = "*** ";
		msg += nick;
		msg += " changed name to ";
		msg += data.at(2);
		msg += " ***\n";

		// Loop through each Channel
		for (int i=0; i<this->channels.size(); i++) {
			if (this->channels.at(i)->changeUserNick(nick, data.at(2))) {
				this->channels.at(i)->pushMsg(msg);
			}
		}
	}

	// Command = "PRIVMSG"
	// ":ismann!~ismann@unaffiliated/ismann PRIVMSG user6789 :sup"
	// ":ismann!~ismann@unaffiliated/ismann PRIVMSG #channel :sup"
	//  --------------0-------------------- ---1--- ----2--- --3-
	else if (data.at(1) == "PRIVMSG") {
		QString nick = parseNick(data.at(0));
		QString rawNick = nick;
		int numOfSpaces = maxNickLength - nick.size();
		for (int i=0; i<numOfSpaces; i++) {
			nick.prepend(' ');
		}
		nick += "| ";

		// Check if Channel already exists
		bool found = false;
		bool pvtMsg = false;
		for (int i=0; i<this->channels.size(); i++) {
			// If so, append messages for that channel
			if (data.at(2) == this->channels.at(i)->getName()) {
				found = true;
				QString msg = nick;
				msg += data.at(3);
				msg += '\n';
				this->channels.at(i)->pushMsg(msg);
				break;
			}

			// Check if message is a private message
			else if (!data.at(2).startsWith('#')) {
				pvtMsg = true;
				if (nick == this->channels.at(i)->getName()) {
					found = true;
					QString msg = nick;
					msg += data.at(3);
					msg += '\n';
					this->channels.at(i)->pushMsg(msg);
					break;
				}
			}
		}

		// Message from Channel not already in the channel list
		if (!found && pvtMsg) {
			Channel *chan = new Channel;
			chan->setName(rawNick);
			QString msg = nick;
			msg += data.at(3);
			msg += '\n';
			chan->pushMsg(msg);
			this->channels.append(chan);
			emit channelListChanged(this);
		}
	}

	// Command = "NOTICE"
	else if (data.at(1) == "NOTICE") {
		QString nick = parseNick(data.at(0));
		QString rawNick = nick;
		int numOfSpaces = maxNickLength - nick.size();
		for (int i=0; i<numOfSpaces; i++) {
			nick.prepend(' ');
		}
		nick += "| ";

		QString notice = nick;
		notice += data.at(3);
		notice += '\n';
		this->pushNotice(notice);
	}

	// Command = "JOIN"
	// ["test!~test@test.com", "JOIN", "#channel"]
	// ----------0-----------  --1--   ----2----
	else if (data.at(1) == "JOIN") {
		QString nick = parseNick(data.at(0));
		// We joined a channel
		if (nick == this->_nick) {
			Channel *chan = new Channel;
			chan->setName(data.at(2));
			this->channels.append(chan);
			emit channelListChanged(this);
			return;
		}

		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(2) == this->channels.at(i)->getName()) {
				QString msg;
				for (int i=0; i<maxNickLength; i++) {
					msg.prepend(' ');
				}
				msg += ">> ";
				msg += nick;
				msg += " joined ";
				msg += this->channels.at(i)->getName();
				msg += '\n';

				// Add new user to Channel's user list
				this->channels.at(i)->addUserToList(nick);

				// Push message to correct Channel
				this->channels.at(i)->pushMsg(msg);
				break;
			}
		}
	}

	// Command = "PART"
	// ["test!~test@test.com", "PART", "#channel", "msg"]
	// ----------0-----------  --1--   ----2----   --3--
	else if (data.at(1) == "PART") {
		QString nick = parseNick(data.at(0));
		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(2) == this->channels.at(i)->getName()) {
				QString msg;
				for (int i=0; i<=maxNickLength; i++) {
					msg.prepend(' ');
				}
				msg += "<< ";
				msg += nick;
				msg += " left. ";
				msg += data.at(2);
				msg += " [";
				// Prevent segfault if there is no PART msg appended to data
				if (data.size() > 3) {
					msg += data.at(3);
				}
				msg += "]\n";

				// Remove user from Channel's user list
				if (this->channels.at(i)->removeFromUserList(nick)) {
					this->channels.at(i)->pushMsg(msg);
					break;
				}
			}
		}
	}

	// Command = "QUIT"
	else if (data.at(1) == "QUIT") {
		QString nick = parseNick(data.at(0));
		QString msg;
		for (int i=0; i<maxNickLength; i++) {
			msg.prepend(' ');
		}
		msg += "<< ";
		msg += nick;
		msg += " quit. [";
		msg += data.at(2);
		msg += "]\n";

		// Loop through all Channels and remove user if it exists
		for (int i=0; i<this->channels.size(); i++) {
			if (this->channels.at(i)->removeFromUserList(nick)) {
				this->channels.at(i)->pushMsg(msg);
			}
		}
	}

	// Otherwise ?
	else {
		return;
	}
}

/*******************************************************************************
Parses user-entered command entered from MainWindow and sends to server
*******************************************************************************/
void Connection::sendCmd(const QByteArray &data) {
	QByteArray dataCpy = data;
	QList<QByteArray> args;
	args << dataCpy.split(' ');

	// '/join [#channel0,#channel1,...,#channelX] [key0,key1,...,keyX]'
	if (args.at(0).startsWith("/join")) {
		QList<QByteArray> chans;
		chans << args.at(1).split(',');
		QByteArray cmd = "JOIN ";
		for (int i=0; i<chans.size(); i++) {
			if (chans.at(i).startsWith('#')) {
				cmd += chans.at(i);
				cmd += ',';
			}
			else {
				continue;
			}
		}
		cmd += "\r\n";
		this->dataForWriting.enqueue(cmd);
	}

	// '/part' [#channel0,#channel1,...,#channelX]
	else if (args.at(0).startsWith("/part")) {
		QList<QByteArray> chans;
		chans << args.at(1).split(',');
		QByteArray cmd = "PART ";
		for (int i=0; i<chans.size(); i++) {
			for (int j=0; j<this->channels.size(); j++) {
				if (QString::fromUtf8(chans.at(i)) ==
				this->channels.at(j)->getName()) {
					partChannel(this->channels.at(j));
				}
			}
		}
	}

	//
	else {
		return;
	}
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
	QByteArray sendNick = "NICK ";
	sendNick.append(QString(_nick + "\r\n").toUtf8());
	this->dataForWriting.enqueue(sendNick);
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

QString Connection::getHostname() const {
	return this->_myHostname;
}

int Connection::getMaxNickLength() const {
	return this->maxNickLength;
}
