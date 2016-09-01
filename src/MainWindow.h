/******************************************************************************
 * MainWindow.h                                                               *
 *                                                                            *
 * Created on Mar 15, 2015                                                    *
 * Author: Cody Johnson <codyj@protonmail.com>                                *
 ******************************************************************************/

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtCore/QDebug>
#include <QtCore/QtGlobal>
#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTime>
#include <QtGui/QKeyEvent>
#include <QtGui/QTextCursor>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QScrollBar>
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
	void updateOutputTE();
   void addConnectionObj(Connection*);

private:
   QString _initialNick;
   QList<Connection*> _connectionList;
   QTextCursor _outputTECursor;
   Connection *selectedConn = NULL;
   Channel *selectedChan = NULL;

   // Private functions
   void connectActions();
   void keyPressEvent(QKeyEvent *e);
   void addConnectionToTree(Connection*);
   void removeItemFromTree();
   void changeNick(const QString&);

private slots:
   void updateCharsLeftLbl(const QString&);
   void changeNick();
   void openNetworkDlg();
   void openAboutDlg();
   void updateTreeClick();
   void storeOutputSliderPos(int);
   void deleteConnection(Connection*);
   void createChannel(Connection*, Channel*);
   void updateTopic(Channel*);
   void updateUserList(Channel*);
   void sendData();
};

#endif   /* _MAINWINDOW_H_ */
