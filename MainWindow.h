/* 
 * MainWindow.h
 *
 * 	Created on Mar 15, 2015
 * 		Author: br0d1n
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QString>
#include <QList>
#include "ChangeNickDlg.h"
#include "NetworkDlg.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow {
    Q_OBJECT
    
public:
    MainWindow();
    virtual ~MainWindow();
    
public slots:

    
private:
	QString nickName;
	void connectActions();
    
private slots:
    void changeNick();
    void openNetworkDlg();
};

#endif	/* _MAINWINDOW_H */
