/*
 * AddNetworkDlg.h
 *
 *  Created on: Mar 21, 2015
 *      Author: br0d1n
 */

#ifndef ADDNETWORKDLG_H_
#define ADDNETWORKDLG_H_

#include <QString>
#include "ui_AddNetworkDlg.h"

class AddNetworkDlg : public QDialog, public Ui::AddNetworkDlg {
    Q_OBJECT

public:
    AddNetworkDlg();
    virtual ~AddNetworkDlg();

public slots:


private:
    void writeData();

private slots:
    void toggleUserInfo();
    void accept();

};

#endif /* ADDNETWORKDLG_H_ */
