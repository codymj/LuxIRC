/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNetworkList;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QSplitter *splitter;
    QTreeWidget *chanView;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *topicBar;
    QTextEdit *textOutput;
    QHBoxLayout *horizontalLayout;
    QPushButton *changeNickBtn;
    QLineEdit *textInput;
    QListWidget *nickView;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuView;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1190, 674);
        actionNetworkList = new QAction(MainWindow);
        actionNetworkList->setObjectName(QStringLiteral("actionNetworkList"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QStringLiteral("splitter"));
        splitter->setOrientation(Qt::Horizontal);
        chanView = new QTreeWidget(splitter);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        chanView->setHeaderItem(__qtreewidgetitem);
        chanView->setObjectName(QStringLiteral("chanView"));
        splitter->addWidget(chanView);
        chanView->header()->setVisible(false);
        layoutWidget = new QWidget(splitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        topicBar = new QLineEdit(layoutWidget);
        topicBar->setObjectName(QStringLiteral("topicBar"));
        topicBar->setEnabled(true);
        topicBar->setReadOnly(true);

        verticalLayout->addWidget(topicBar);

        textOutput = new QTextEdit(layoutWidget);
        textOutput->setObjectName(QStringLiteral("textOutput"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textOutput->sizePolicy().hasHeightForWidth());
        textOutput->setSizePolicy(sizePolicy);
        textOutput->setReadOnly(true);
        textOutput->setAcceptRichText(false);

        verticalLayout->addWidget(textOutput);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        changeNickBtn = new QPushButton(layoutWidget);
        changeNickBtn->setObjectName(QStringLiteral("changeNickBtn"));
        changeNickBtn->setFlat(true);

        horizontalLayout->addWidget(changeNickBtn);

        textInput = new QLineEdit(layoutWidget);
        textInput->setObjectName(QStringLiteral("textInput"));

        horizontalLayout->addWidget(textInput);


        verticalLayout->addLayout(horizontalLayout);

        splitter->addWidget(layoutWidget);
        nickView = new QListWidget(splitter);
        nickView->setObjectName(QStringLiteral("nickView"));
        splitter->addWidget(nickView);

        verticalLayout_2->addWidget(splitter);

        MainWindow->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1190, 19));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionNetworkList);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LuxIRC", 0));
        actionNetworkList->setText(QApplication::translate("MainWindow", "&Network List", 0));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        changeNickBtn->setText(QApplication::translate("MainWindow", "NickName008", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "&File", 0));
        menuView->setTitle(QApplication::translate("MainWindow", "&View", 0));
        menuHelp->setTitle(QApplication::translate("MainWindow", "&Help", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
