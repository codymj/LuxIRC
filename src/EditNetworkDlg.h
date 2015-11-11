/******************************************************************************
 * EditNetworkDlg.h                                                           *
 *                                                                            *
 * Created on: Mar 21, 2015                                                   *
 * Author: Cody Johnson <codyj@mail.usf.edu>                                  *
 ******************************************************************************/

#ifndef _EDITNETWORKDLG_H_
#define _EDITNETWORKDLG_H_

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

#endif /* _EDITNETWORKDLG_H_ */
