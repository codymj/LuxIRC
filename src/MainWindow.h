/******************************************************************************
 * MainWindow.h                                                               *
 *                                                                            *
 * Created on Mar 15, 2015                                                    *
 * Author: ismann <ismann@protonmail.com>                                     *
 ******************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QString>
#include <QtCore/QList>
#include "ChangeNickDlg.h"
#include "NetworkDlg.h"
#include "AboutDlg.h"
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
   void openAboutDlg();
};

#endif   /* _MAINWINDOW_H */
