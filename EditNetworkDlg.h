/*
 * EditNetworkDlg.h
 *
 *  Created on: Mar 21, 2015
 *      Author: br0d1n
 */

#ifndef EDITNETWORKDLG_H_
#define EDITNETWORKDLG_H_

#include <QtCore/QString>
#include "ui_EditNetworkDlg.h"

class EditNetworkDlg : public QDialog, public Ui::EditNetworkDlg {
    Q_OBJECT

public:
   EditNetworkDlg(QString &);
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
