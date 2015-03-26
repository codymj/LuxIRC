/*
 * NetworkDlg.h
 *
 *  Created on: Mar 19, 2015
 *      Author: br0d1n
 */

#ifndef NETWORKDLG_H_
#define NETWORKDLG_H_

#include <QString>
#include "ui_NetworkDlg.h"

class NetworkDlg : public QDialog, public Ui::NetworkDlg {
    Q_OBJECT

public:
    NetworkDlg();
    virtual ~NetworkDlg();
    
    QString selectedNetwork;
    
public slots:

private:
    void readData();

private slots:
    void openAddNetworkDlg();
    void openEditNetworkDlg();
    void selectNetwork();

};

#endif /* NETWORKDLG_H_ */
