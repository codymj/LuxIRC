/******************************************************************************
 * Channel.h                                                                  *
 *                                                                            *
 * Created on Aug 08, 2016                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QStringList>

class Channel {
public:
	Channel();
	~Channel();

	void setName(const QString name);
	QString getName() const;
	void pushMsg(const QString msg);
	QStringList getMsgs() const;
	void setSliderVal(int val);
	int getSliderVal() const;
	void setSliderMaxed(bool);
	bool isSliderMaxed() const;

private:
	QString _name;
	QStringList _msgs;
	QString _topic;
	QList<QString> _userList;
	int _sliderVal = 0;
	bool _sliderMaxed = true;

};

#endif // _CHANNEL_H_
