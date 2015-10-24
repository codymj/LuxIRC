/******************************************************************************
 * AboutDlg.h                                                                 *
 *                                                                            *
 * Created on Oct 24, 2015                                                    *
 * Author: ismann <ismann@protonmail.com>                                     *
 ******************************************************************************/

#ifndef ABOUTDLG_H
#define ABOUTDLG_H

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

#endif   /* ABOUTDLG_H */
