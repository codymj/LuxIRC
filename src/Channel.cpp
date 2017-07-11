/***************************************************************************************************
 * Channel.cpp                                                                                     *
 *                                                                                                 *
 * Created on Aug 08, 2016                                                                         *
 * Author: Cody Johnson <codyj@protonmail.com>                                                     *
 **************************************************************************************************/

#include "Channel.h"

/***************************************************************************************************
Constructor
***************************************************************************************************/
Channel::Channel() {
}

/***************************************************************************************************
Destructor
***************************************************************************************************/
Channel::~Channel() {
}

/***************************************************************************************************
Parse user list for Channel
***************************************************************************************************/
void Channel::parseUserList() {
    // Copy _rawUserlist to temp
    QStringList temp = _rawUserList;

    // Clear lists for updating
    _owners.clear();
    _sops.clear();
    _ops.clear();
    _voiced.clear();
    _users.clear();

    // Sort by user type into separate lists
    for (int i=0; i<temp.size(); i++) {
        if (temp.at(i).startsWith('~')) {
            _owners << temp.takeAt(i);
        }
        else if (temp.at(i).startsWith('&')) {
            _sops << temp.takeAt(i);
        }
        else if (temp.at(i).startsWith('@')) {
            _ops << temp.takeAt(i);
        }
        else if (temp.at(i).startsWith('+')) {
            _voiced << temp.takeAt(i);
        }
    }

    // Only regular users left in temp
    _users = temp;

    // Sort each list and append by heirarchy: ~, &, @, +
    _owners.sort(Qt::CaseInsensitive);
    _sops.sort(Qt::CaseInsensitive);
    _ops.sort(Qt::CaseInsensitive);
    _hops.sort(Qt::CaseInsensitive);
    _voiced.sort(Qt::CaseInsensitive);
    _users.sort(Qt::CaseInsensitive);

    _userList.clear();
    _userList.append(_owners);
    _userList.append(_sops);
    _userList.append(_ops);
    _userList.append(_hops);
    _userList.append(_voiced);
    _userList.append(_users);

    emit userListChanged(this);
}

/***************************************************************************************************
Populate the user list for Channel
***************************************************************************************************/
void Channel::populateUserList(const QString &list) {
    _rawUserList.append(list.split(' '));
}

/***************************************************************************************************
Adds the nick to user list for Channel
***************************************************************************************************/
void Channel::addUserToList(const QString &nick) {
    this->_rawUserList.append(nick);
    parseUserList();
}

/***************************************************************************************************
Changes user's nick to newnick
***************************************************************************************************/
bool Channel::changeUserNick(const QString &user, const QString &newNick) {
    bool found = false;
    for (int i=0; i<_rawUserList.size(); i++) {
        if (_rawUserList.at(i) == user) {
            found = true;
            _rawUserList.removeAt(i);
            _rawUserList.insert(i, newNick);
            break;
        }
    }

    parseUserList();
    return found;
}

/***************************************************************************************************
Remove a user from user list for Channel. Returns true if user was found
***************************************************************************************************/
bool Channel::removeFromUserList(const QString &user) {
    bool found = false;
    for (int i=0; i<_rawUserList.size(); i++) {
        if (_rawUserList.at(i) == user) {
            found = true;
            _rawUserList.removeAt(i);
            break;
        }
    }

    parseUserList();
    emit userListChanged(this);
    return found;
}

/***************************************************************************************************
Get'ers and set'ers
***************************************************************************************************/
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

QList<QStringList> Channel::getUserList() const {
    return this->_userList;
}
