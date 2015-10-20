/******************************************************************************
 * AddNetworkDlg.h                                                            *
 *                                                                            *
 * Created on: Mar 21, 2015                                                   *
 * Author: ismann <ismann@protonmail.com>                                     *
 ******************************************************************************/

#ifndef ADDNETWORKDLG_H_
#define ADDNETWORKDLG_H_

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

#endif /* ADDNETWORKDLG_H_ */
