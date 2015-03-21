/*
 * NetworkDlg.h
 *
 *  Created on: Mar 19, 2015
 *      Author: br0d1n
 */

#ifndef NETWORKDLG_H_
#define NETWORKDLG_H_

#include "ui_NetworkDlg.h"

class NetworkDlg : public QDialog, public Ui::NetworkDlg {
	Q_OBJECT

public:
	NetworkDlg();
	virtual ~NetworkDlg();

public slots:


private:


private slots:
	void openAddNetworkDlg();

};

#endif /* NETWORKDLG_H_ */
