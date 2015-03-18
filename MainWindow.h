/* 
 * File:   MainWindow.h
 * Author: br0d1n
 *
 * Created on March 15, 2015, 11:09 PM
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QMainWindow>
#include "ChangeNickDlg.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
    
public:
    MainWindow();
    virtual ~MainWindow();
    
public slots:

    
private:
//	ChangeNickDlg *changeNickDlg;
	QString nickName;
    
private slots:
    void changeNick();
    
};

#endif	/* _MAINWINDOW_H */
