/*
 * EditNetworkDlg.h
 *
 *  Created on: Mar 21, 2015
 *      Author: br0d1n
 */

#ifndef EDITNETWORKDLG_H_
#define EDITNETWORKDLG_H_

#include <QString>
#include "ui_EditNetworkDlg.h"

/* Struct for holding network data
struct Network {
    QString name;
    QString server;
    int port;
    QString nick1;
    QString nick2;
    QString username;
    QString realName;
    int loginMethod;
    QString password;
    QString channels;
    bool connectAtStart;
    bool useSSL;
    bool acceptInvalidCert;
    bool useGlobalInfo;
};
*/

class EditNetworkDlg : public QDialog, public Ui::EditNetworkDlg {
    Q_OBJECT

public:
    EditNetworkDlg(QString &networkName);
    virtual ~EditNetworkDlg();

public slots:


private:
    void readData(QString &);
    void writeData();
	void streamDataIntoFile(QTextStream &);
    void populateData(QString &);

private slots:
    void toggleUserInfo();
	void accept();

};

#endif /* EDITNETWORKDLG_H_ */
