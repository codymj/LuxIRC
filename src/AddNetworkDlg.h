/***************************************************************************************************
 * AddNetworkDlg.h                                                                                 *
 *                                                                                                 *
 * Created on: Mar 21, 2015                                                                        *
 * Author: Cody Johnson <codyj@mail.usf.edu>                                                       *
 **************************************************************************************************/

#ifndef _ADDNETWORKDLG_H_
#define _ADDNETWORKDLG_H_

#include <QtCore/QString>
#include "ui_AddNetworkDlg.h"

class AddNetworkDlg : public QDialog, public Ui::AddNetworkDlg {
   Q_OBJECT

public:
   AddNetworkDlg();
   virtual ~AddNetworkDlg();

public slots:


private:
   void writeData();
   void streamDataIntoFile(QTextStream &);

private slots:
   void toggleUserInfo();
   void accept();

};

#endif /* _ADDNETWORKDLG_H_ */
