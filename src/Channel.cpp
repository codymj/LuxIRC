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
