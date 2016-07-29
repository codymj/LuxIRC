/******************************************************************************
 * NetworkDlg.h                                                               *
 *                                                                            *
 * Created on: Mar 19, 2015                                                   *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#ifndef _NETWORKDLG_H_
#define _NETWORKDLG_H_

#include <QtCore/QString>
#include "ui_NetworkDlg.h"
#include "AddNetworkDlg.h"
#include "EditNetworkDlg.h"
#include "Connection.h"

class MainWindow;

class NetworkDlg : public QDialog, public Ui::NetworkDlg {
    Q_OBJECT

public:
   NetworkDlg();
   virtual ~NetworkDlg();

   Connection *tempConnection = NULL;

public slots:
   void buildConnection();

private:
   QString selectedNetwork;

private slots:
   void openAddNetworkDlg();
   void openEditNetworkDlg();
   void selectNetwork();
   void readData();
   void removeNetwork();
   void accept();

signals:
   void sendConnectObj(Connection*);

};

#endif /* _NETWORKDLG_H_ */
