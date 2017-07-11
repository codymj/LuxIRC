/***************************************************************************************************
 * MainWindow.h                                                                                    *
 *                                                                                                 *
 * Created on Mar 15, 2015                                                                         *
 * Author: Cody Johnson <codyj@protonmail.com>                                                     *
 **************************************************************************************************/

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include <QtCore/QDebug>
#include <QtCore/QtGlobal>
#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QTime>
#include <QtGui/QFont>
#include <QtGui/QFontMetrics>
#include <QtGui/QKeyEvent>
#include <QtGui/QTextBlockFormat>
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

   // Public data
   QList<int> splitterSizes;
   int mainWindowSize;
   int nickListSize;
   int networkTreeSize;
   int outputTESize;
   QFont font;

public slots:
   void updateOutputTE();
   void addConnectionObj(Connection*);
   void displayToOutputTE(QString&);

private:
   QString _initialNick;
   QList<Connection*> _connectionList;
   QTextBlockFormat _outputTEFormat;
   QTextCursor _outputTECursor;
   Connection *selectedConn = NULL;
   Channel *selectedChan = NULL;
   bool topicLEVisible;

   // Private functions
   void connectActions();
   void keyPressEvent(QKeyEvent *e);
   void addConnectionToTree(Connection*);
   void removeItemFromTree();
   void changeNick(const QString&);
   QString formatMsg(const QString&) const;
   void checkCmd(const QByteArray&);

private slots:
   void updateCharsLeftLbl(const QString&);
   void changeNick();
   void openNetworkDlg();
   void openAboutDlg();
   void updateTreeClick();
   void storeOutputSliderPos(int);
   void deleteConnection(Connection*);
   void updateChannels(Connection*);
   void updateTopic(Channel*);
   void updateUserList(Channel*);
   void sendData();
   void hideMenuBar();
   void restoreSplitterRatios();
   void storeSplitterSizes();

};

#endif   /* _MAINWINDOW_H_ */
