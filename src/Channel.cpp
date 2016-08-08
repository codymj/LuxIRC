/******************************************************************************
 * Channel.cpp                                                                *
 *                                                                            *
 * Created on Aug 08, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#include "Channel.h"

Channel::Channel() {
	
}

Channel::~Channel() {

}

void Channel::setName(const QString name) {
	this->_name = name;
}

QString Channel::getName() const {
	return this->_name;
}

void Channel::pushMsg(const QString msg) {
	this->_msgs << msg;
}

QStringList Channel::getMsgs() const {
	return this->_msgs;
}
