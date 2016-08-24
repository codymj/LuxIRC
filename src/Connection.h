/******************************************************************************
 * Connection.h                                                               *
 *                                                                            *
 * Created on Jul 25, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include <QtCore/QByteArray>
#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QMultiMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QThread>
#include <QtNetwork/QTcpSocket>
#include "Channel.h"

class Connection : public QThread {
	Q_OBJECT

public:
	Connection();
	~Connection();

	// Public data
	QList<Channel*> channels;	
	bool connected;

	// Public functions
	void connectionReady();
	void disconnect();

	// Get'er and set'er functions
	void setNetwork(QString &network);
	void setServer(QString &server);
	void setChans(QString &chans);
	void setPort(int port);
	void setNick(const QString &nick);
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
	QString getServer() const;
	QString getNick() const;
	void pushNotice(const QString msg);
	QStringList getNotices() const;
	void setSliderVal(int);
	int getSliderVal() const;
	void setSliderMaxed(bool);
	bool isSliderMaxed() const;

protected:
	void run();

private:
	// Data for network from networks.conf
	QString _network;			// Name of network
	QString _server;			// Ex: irc.freenode.net
	QString _chansStr;			// Comma separated list of channels
	int _port;					// Port of server to connect to
	QString _nick;
	QString _nick2;
	QString _username;
	QString _realName;
	int _loginMethod;
	QString _password;
	bool _connectAtStart;
	bool _useGlobalInfo;
	bool _useSSL;
	bool _acceptInvalidSSLCert;
	QStringList _notices;
	int _sliderVal = 0;
	bool _sliderMaxed = true;

	// Private data
	QTcpSocket *socket;
	int bytesToRead = 0;
	int bytesRemaining = 0;
	QByteArray data;
	QStringList dataLines;

	// Private functions
	void parseData(const QString &data);
	void processData(const QStringList &data);

signals:
	void dataAvailable();
	void topicChanged(Channel*);
	void newChannel(Connection*, Channel*);
	void deleteMe(Connection*);
};

#endif // _CONNECTION_H_
