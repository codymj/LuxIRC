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
#include <QtCore/QStringList>
#include <QtConcurrent/QtConcurrent>
#include <QtNetwork/QTcpSocket>

class Connection {
public:
	Connection();
	~Connection();

	// Data returned from network to be accessed by outputTE
	QString networkData;

	// Get'er and set'er functions
	void setNetwork(QString &network);
	void setServer(QString &server);
	void setPort(int port);
	void setNick(QString &nick);
	void setNick2(QString &nick2);
	void setUsername(QString &username);
	void setRealName(QString &realName);
	void setLoginMethod(int lm);
	void setPassword(QString &pass);
	void setChanList(QString &chanList);
	void setConnectAtStart(bool &b);
	void setUseGlobalInfo(bool &b);
	void setUseSSL(bool &b);
	void setAcceptInvalidSSLCert(bool &b);
	QString getNetwork() const;
	QList<QString> getChanList() const;

private:
	// Data for network from networks.conf
	QString _network;
	QString _server;
	int _port;
	QString _nick;
	QString _nick2;
	QString _username;
	QString _realName;
	int _loginMethod;
	QString _password;
	QString _chanListStr;
	QList<QString> _chanList;
	bool _connectAtStart;
	bool _useGlobalInfo;
	bool _useSSL;
	bool _acceptInvalidSSLCert;

	// Getting and handling data from server
	QTcpSocket _socket;
	// Must be dynamically created:
	//     QList userList for each channel
	//     QStringList channelData messages separated for each channel
	//     QString topic for each channel

	void connectToNetwork();

signals:
	void dataReady(QString &network, QString &data);
};

#endif // _CONNECTION_H_
