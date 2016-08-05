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
#include <QtCore/QStringList>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTreeWidgetItem>
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
	void updateOutputTE(QString network, QMultiMap<QString,QString> data);

private:
   QString nickName;
   QList<Connection*> _connectionList;
   void connectActions();
   void receiveConnectObj(Connection*);
   void keyPressEvent(QKeyEvent *e);

   // QTreeWidget (List of networks and channels) functions
   void addConnectionToTree(Connection*);
   void rmConnectionFromTree(const QString &network);
   // void rmChannelFromTree(QString &channel);

private slots:
   void changeNick();
   void openNetworkDlg();
   void openAboutDlg();
   void updateTreeClick();
};

#endif   /* _MAINWINDOW_H_ */
