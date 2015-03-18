/* 
 * File:   ChangeNickDlg.h
 * Author: br0d1n
 *
 * Created on March 15, 2015, 11:11 PM
 */

#ifndef _CHANGENICKDLG_H
#define	_CHANGENICKDLG_H

#include <QDialog>
#include "ui_ChangeNickDlg.h"

class ChangeNickDlg : public QDialog, public Ui::ChangeNickDlg {
    Q_OBJECT

public:
    ChangeNickDlg();
    virtual ~ChangeNickDlg();
    
public slots:
    
    
private:


private slots:


};

#endif	/* _CHANGENICKDLG_H */
