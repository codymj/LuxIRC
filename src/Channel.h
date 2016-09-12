/******************************************************************************
 * Channel.h                                                                  *
 *                                                                            *
 * Created on Aug 08, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QStringList>

class Channel : public QObject {
	Q_OBJECT

public:
	Channel();
	~Channel();

	// Get'er & set'er
	void setName(const QString &name);
	QString getName() const;
	void pushMsg(const QString &msg);
	QStringList getMsgs() const;
	void setSliderVal(int val);
	int getSliderVal() const;
	void setSliderMaxed(bool);
	bool isSliderMaxed() const;
	void setTopic(const QString &topic);
	QString getTopic() const;
	QList<QStringList> getUserList() const;

	// Public functions
	void populateUserList(const QString &list);
	void addUserToList(const QString &nick);
	bool removeFromUserList(const QString &user);
	void parseUserList();
	bool changeUserNick(const QString &user, const QString &newNick);

private:
	QString _name;
	QStringList _msgs;
	QString _topic;
	QStringList _rawUserList;
	QStringList _owners, _sops, _ops, _hops, _voiced, _users;
	QList<QStringList> _userList;
	int _sliderVal = 0;
	bool _sliderMaxed = true;

signals:
	void topicChanged(Channel*);
	void userListChanged(Channel*);
};

#endif // _CHANNEL_H_
