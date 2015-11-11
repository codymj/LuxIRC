/******************************************************************************
 * NetworkDlg.h                                                               *
 *                                                                            *
 * Created on: Mar 19, 2015                                                   *
 * Author: Cody Johnson <codyj@mail.usf.edu>                                  *
 ******************************************************************************/

#ifndef _NETWORKDLG_H_
#define _NETWORKDLG_H_

#include <QtCore/QString>
#include "ui_NetworkDlg.h"
#include "AddNetworkDlg.h"
#include "EditNetworkDlg.h"

class NetworkDlg : public QDialog, public Ui::NetworkDlg {
    Q_OBJECT

public:
   NetworkDlg();
   virtual ~NetworkDlg();

public slots:

private:
   QString selectedNetwork;

private slots:
   void openAddNetworkDlg();
   void openEditNetworkDlg();
   void selectNetwork();
   void readData();
   void removeNetwork();
   void accept();

};

#endif /* _NETWORKDLG_H_ */
