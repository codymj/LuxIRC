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

	bool _connectAtStartup;
	bool _useGlobalInfo;

	// TODO - SSL options later

};

#endif // _CONNECTION_H_
