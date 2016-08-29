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
Leaves a Channel
*******************************************************************************/
void Connection::partChannel(Channel *chan) {
	// QByteArray data = (QString(
	// 	"PART %1 %2\r\n").arg(chan->getName(),_partMsg).toUtf8()
	// );

	// TODO: handle /PART

	// Remove Channel from channels list
	for (int i=0; i<channels.size(); i++) {
		if (channels.at(i) == chan) {
			delete channels.takeAt(i);
			break;
		}
	}
}

/*******************************************************************************
Delete all Channels for this Connection
*******************************************************************************/
void Connection::deleteAllChannels() {
	for (int i=0; i<channels.size(); i++) {
		// TODO: handle /PART
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
		socket->write(QString(
			"JOIN %1\r\n").arg(_chansStr).toUtf8()
		);

		// Connection loop
		while (this->connected) {
			// Wait for new data from network
			socket->waitForReadyRead();

			// Make sure all data was received by checking "\r\n" at end
			bytesToRead = socket->bytesAvailable();
			data = socket->read(bytesToRead);
			
			// If waitForReadyRead() times out, blank data is written
			if (data.isEmpty()) {
				continue;
			}

			while (!data.endsWith("\r\n")) {
				if (!socket->waitForReadyRead(60000)) {
					qDebug() << "WaitForReadyRead timed out...";
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
void Connection::parseData(const QString &data) {
	qDebug() << data;
	QString prefix;
	QString command;
	QStringList trailing;
	QStringList args;
	QStringList parsedData;

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
	qDebug() << user;
	QString nick = user.section('!', 0, 0);
	qDebug() << nick;
	return nick;
}

/*******************************************************************************
Processes the data that has been parsed
data = ["test!~test@test.com", "PRIVMSG", "#channel", "Hi!", ...]
*******************************************************************************/
void Connection::processData(const QStringList &data) {
	// qDebug() << "---";
	// for (int i=0; i<data.size(); i++) {
	// 	qDebug() << data.at(i);
	// }
	// qDebug() << "---";

	// Command = 375 (Start of MOTD)
	// Command = 376 (End of MOTD)
	// Command = 372 (MOTD)
	if (data.at(1) == "375" || data.at(1) == "376" || data.at(1) == "372") {
		this->pushNotice(QString(data.at(3) + "\n"));
	}

	// Command = 332 (Topic)
	if (data.at(1) == "332") {
		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(3) == this->channels.at(i)->getName()) {
				this->channels.at(i)->setTopic(data.at(4));
				emit topicChanged(this->channels.at(i));
				break;
			}
		}
	}

	// Command = 353 (/NAMES list)
	// ":asimov.freenode.net 353 user6789 = ##math :name0 name1 name2 ..."
	//  ----------0--------- -1- ----2--- 3 --4--- --------5-------------
	if (data.at(1) == "353") {
		QString userListStr = data.at(5);
		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(4) == this->channels.at(i)->getName()) {
				this->channels.at(i)->populateUserList(userListStr);
				break;
			}
		}
	}

	// Command = "NICK"
	if (data.at(1) == "NICK") {
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
	if (data.at(1) == "PRIVMSG") {
		bool found = false;

		// Check if Channel already exists
		for (int i=0; i<this->channels.size(); i++) {
			// If so, append messages for that channel
			if (data.at(2) == this->channels.at(i)->getName()) {
				found = true;
				QString msg = parseNick(data.at(0));
				msg += ": ";
				msg += data.at(3);
				msg += '\n';
				this->channels.at(i)->pushMsg(msg);
				break;
			}
		}

		// Message from Channel not already in the channel list
		if (!found) {
			Channel *chan = new Channel;
			QString nick = parseNick(data.at(0));
			chan->setName(nick);
			QString msg = nick;
			msg += ": ";
			msg += data.at(3);
			msg += '\n';
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
		notice += '\n';
		this->pushNotice(notice);
	}

	// Command = "JOIN"
	else if (data.at(1) == "JOIN") {
		// Prevent double-adding ourself to the user/nick list
		if (parseNick(data.at(0)) == this->_nick) {
			return;
		}

		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(2) == this->channels.at(i)->getName()) {
				QString msg = "*** ";
				msg += data.at(0);
				msg += " joined ";
				msg += this->channels.at(i)->getName();
				msg += " ***";
				msg += '\n';

				// Add new user to Channel's user list
				QString nick = parseNick(data.at(0));
				this->channels.at(i)->addUserToList(nick);

				this->channels.at(i)->pushMsg(msg);
				break;
			}
		}
	}

	// Command = "PART"
	// ["test!~test@test.com", "PART", "#channel", "msg"]
	// ----------0-----------  --1--   ----2----   --3--
	else if (data.at(1) == "PART") {
		for (int i=0; i<this->channels.size(); i++) {
			if (data.at(2) == this->channels.at(i)->getName()) {
				QString msg = "*** ";
				msg += data.at(0);
				msg += " left ";
				msg += data.at(2);
				msg += " [";
				// Prevent segfault if there is no PART msg appended to data
				if (data.size() > 3) {
					msg += data.at(3);
				}
				msg += "] ***\n";

				// Remove user from Channel's user list
				QString nick = parseNick(data.at(0));
				if (this->channels.at(i)->removeFromUserList(nick)) {
					this->channels.at(i)->pushMsg(msg);
					break;
				}
			}
		}
	}

	// Command = "QUIT"
	else if (data.at(1) == "QUIT") {
		QString msg = "*** ";
		msg += data.at(0);
		msg += " quit. [";
		msg += data.at(2);
		msg += "] ***\n";

		// Loop through all Channels and remove user if it exists
		QString nick = parseNick(data.at(0));
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
