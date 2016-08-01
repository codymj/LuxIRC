/******************************************************************************
 * Connection.h                                                               *
 *                                                                            *
 * Created on Jul 25, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <QtCore/QList>
#include <QtCore/QString>

class Connection {
public:
	Connection();
	~Connection();

	void setNetwork(QString &network) {
		this->_network = network;
	}

	void setServer(QString &server) {
		this->_server = server;
	}

	void setPort(int port) {
		this->_port = port;
	}

	void setNick(QString &nick) {
		this->_nick = nick;
	}

	void setNick2(QString &nick2) {
		this->_nick2 = nick2;
	}

	void setUsername(QString &username) {
		this->_username = username;
	}

	void setRealName(QString &realName) {
		this->_realName = realName;
	}

	void setLoginMethod(int lm) {
		this->_loginMethod = lm;
	}

	void setPassword(QString &pass) {
		this->_password = pass;
	}

	void setChanList(QString &chanList) {
		this->_chanList << chanList.split(',');
	}

	void setConnectAtStart(bool &b) {
		this->_connectAtStart = b;
	}

	void setUseGlobalInfo(bool &b) {
		this->_useGlobalInfo = b;
	}

	void setUseSSL(bool &b) {
		this->_useSSL = b;
	}

	void setAcceptInvalidSSLCert(bool &b) {
		this->_acceptInvalidSSLCert = b;
	}

	QString getNetwork() const {
		return this->_network;
	}

	QList<QString> getChanList() const {
		return this->_chanList;
	}

private:
	QString _network;
	QString _server;
	int _port;
	QString _nick;
	QString _nick2;
	QString _username;
	QString _realName;
	int _loginMethod;
	QString _password;
	QList<QString> _chanList;

	bool _connectAtStart;
	bool _useGlobalInfo;
	bool _useSSL;
	bool _acceptInvalidSSLCert;

};

#endif // _CONNECTION_H_
