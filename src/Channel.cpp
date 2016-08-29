/******************************************************************************
 * Channel.cpp                                                                *
 *                                                                            *
 * Created on Aug 08, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#include "Channel.h"

/*******************************************************************************
Constructor
*******************************************************************************/
Channel::Channel() {
}

/*******************************************************************************
Destructor
*******************************************************************************/
Channel::~Channel() {
}

/*******************************************************************************
Populate the user list for Channel
*******************************************************************************/
void Channel::populateUserList(const QString &list) {
	this->_userList.append(list.split(' '));
	emit userListChanged(this);
}

/*******************************************************************************
Adds the nick to user list for Channel
*******************************************************************************/
void Channel::addUserToList(const QString &nick) {
	this->_userList.append(nick);
	emit userListChanged(this);
}

/*******************************************************************************
Changes user's nick to newnick
*******************************************************************************/
bool Channel::changeUserNick(const QString &user, const QString &newNick) {
	bool found = false;
	for (int i=0; i<_userList.size(); i++) {
		if (_userList.at(i) == user) {
			found = true;
			_userList.removeAt(i);
			_userList.insert(i, newNick);
			break;
		}
	}
	emit userListChanged(this);
	return found;
}

/*******************************************************************************
Remove a user from user list for Channel. Returns true if user was found
*******************************************************************************/
bool Channel::removeFromUserList(const QString &user) {
	bool found = false;
	for (int i=0; i<_userList.size(); i++) {
		if (_userList.at(i) == user) {
			found = true;
			_userList.removeAt(i);
			break;
		}
	}
	qDebug() << _userList;
	emit userListChanged(this);
	return found;
}

/*******************************************************************************
Get'ers and set'ers
*******************************************************************************/
void Channel::setName(const QString &name) {
	this->_name = name;
}

QString Channel::getName() const {
	return this->_name;
}

void Channel::pushMsg(const QString &msg) {
	this->_msgs << msg;
}

QStringList Channel::getMsgs() const {
	return this->_msgs;
}

void Channel::setSliderVal(int val) {
	this->_sliderVal = val;
}

int Channel::getSliderVal() const {
	return this->_sliderVal;
}

void Channel::setSliderMaxed(bool b) {
	this->_sliderMaxed = b;
}

bool Channel::isSliderMaxed() const {
	return this->_sliderMaxed;
}

void Channel::setTopic(const QString &topic) {
	this->_topic = topic;
}

QString Channel::getTopic() const {
	return this->_topic;
}

QStringList Channel::getUserList() const {
	return this->_userList;
}
