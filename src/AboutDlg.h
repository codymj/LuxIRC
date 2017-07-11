/***************************************************************************************************
 * AboutDlg.h                                                                                      *
 *                                                                                                 *
 * Created on Oct 24, 2015                                                                         *
 * Author: Cody Johnson <codyj@mail.usf.edu>                                                       *
 **************************************************************************************************/

#ifndef _ABOUTDLG_H_
#define _ABOUTDLG_H_

#include "ui_AboutDlg.h"

class AboutDlg : public QDialog, public Ui::AboutDlg {
   Q_OBJECT
   
public:
   AboutDlg();
   virtual ~AboutDlg();
   
public slots:


private:


private slots:


};

#endif   /* _ABOUTDLG_H_ */
