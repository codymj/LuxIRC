/******************************************************************************
 * MainWindow.h                                                               *
 *                                                                            *
 * Created on Mar 15, 2015                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtCore/QDebug>
#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QString>
#include <QtWidgets/QMessageBox>
#include "ChangeNickDlg.h"
#include "AboutDlg.h"
#include "Connection.h"
#include "NetworkDlg.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow, public Ui::MainWindow {
   Q_OBJECT

public:
   MainWindow();
   virtual ~MainWindow();

public slots:
	void receiveConnectObj(Connection*);

private:
   QString nickName;
   void connectActions();
   QList<Connection*> _connectionList;

private slots:
   void changeNick();
   void openNetworkDlg();
   void openAboutDlg();
};

#endif   /* _MAINWINDOW_H_ */
