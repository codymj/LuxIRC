/*
 * ChangeNickDlg.h
 *
 * 	Created on Mar 15, 2015
 * 		Author: br0d1n
 */

#ifndef _CHANGENICKDLG_H
#define	_CHANGENICKDLG_H

#include <QMessageBox>
#include <QRegExp>
#include <QRegExpValidator>
#include <QString>
#include "ui_ChangeNickDlg.h"

class ChangeNickDlg : public QDialog, public Ui::ChangeNickDlg {
    Q_OBJECT

public:
    ChangeNickDlg();
    virtual ~ChangeNickDlg();

	QString newNick;
	QString getNewNick();

public slots:

private:


private slots:
	void accept();

};

#endif	/* _CHANGENICKDLG_H */
