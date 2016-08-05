/********************************************************************************
** Form generated from reading UI file 'AddNetworkDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDNETWORKDLG_H
#define UI_ADDNETWORKDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AddNetworkDlg
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QCheckBox *connectCkb;
    QCheckBox *sslCkb;
    QCheckBox *invalidCertCkb;
    QCheckBox *globalInfoCkb;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelBtn;
    QPushButton *saveBtn;
    QWidget *layoutWidget2;
    QFormLayout *formLayout;
    QLabel *label_9;
    QLineEdit *networkLE;
    QLabel *label;
    QLineEdit *serverLE;
    QLabel *label_2;
    QLineEdit *portLE;
    QWidget *layoutWidget3;
    QFormLayout *formLayout_2;
    QLabel *label_3;
    QLineEdit *nickLE;
    QLabel *label_4;
    QLineEdit *nick2LE;
    QLabel *label_5;
    QLineEdit *usernameLE;
    QLabel *label_6;
    QLineEdit *realNameLE;
    QLabel *label_7;
    QComboBox *loginMethodCbo;
    QLabel *label_8;
    QLineEdit *passwordLE;
    QLabel *label_10;
    QLineEdit *joinChansLE;

    void setupUi(QDialog *AddNetworkDlg)
    {
        if (AddNetworkDlg->objectName().isEmpty())
            AddNetworkDlg->setObjectName(QStringLiteral("AddNetworkDlg"));
        AddNetworkDlg->setWindowModality(Qt::ApplicationModal);
        AddNetworkDlg->setEnabled(true);
        AddNetworkDlg->resize(542, 254);
        AddNetworkDlg->setMinimumSize(QSize(542, 254));
        AddNetworkDlg->setMaximumSize(QSize(542, 254));
        AddNetworkDlg->setInputMethodHints(Qt::ImhNone);
        AddNetworkDlg->setModal(true);
        layoutWidget = new QWidget(AddNetworkDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 100, 207, 100));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        connectCkb = new QCheckBox(layoutWidget);
        connectCkb->setObjectName(QStringLiteral("connectCkb"));

        verticalLayout->addWidget(connectCkb);

        sslCkb = new QCheckBox(layoutWidget);
        sslCkb->setObjectName(QStringLiteral("sslCkb"));

        verticalLayout->addWidget(sslCkb);

        invalidCertCkb = new QCheckBox(layoutWidget);
        invalidCertCkb->setObjectName(QStringLiteral("invalidCertCkb"));

        verticalLayout->addWidget(invalidCertCkb);

        globalInfoCkb = new QCheckBox(layoutWidget);
        globalInfoCkb->setObjectName(QStringLiteral("globalInfoCkb"));

        verticalLayout->addWidget(globalInfoCkb);

        layoutWidget1 = new QWidget(AddNetworkDlg);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(360, 220, 168, 24));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cancelBtn = new QPushButton(layoutWidget1);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout->addWidget(cancelBtn);

        saveBtn = new QPushButton(layoutWidget1);
        saveBtn->setObjectName(QStringLiteral("saveBtn"));

        horizontalLayout->addWidget(saveBtn);

        layoutWidget2 = new QWidget(AddNetworkDlg);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 10, 211, 80));
        formLayout = new QFormLayout(layoutWidget2);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget2);
        label_9->setObjectName(QStringLiteral("label_9"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_9);

        networkLE = new QLineEdit(layoutWidget2);
        networkLE->setObjectName(QStringLiteral("networkLE"));

        formLayout->setWidget(0, QFormLayout::FieldRole, networkLE);

        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        serverLE = new QLineEdit(layoutWidget2);
        serverLE->setObjectName(QStringLiteral("serverLE"));

        formLayout->setWidget(1, QFormLayout::FieldRole, serverLE);

        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_2);

        portLE = new QLineEdit(layoutWidget2);
        portLE->setObjectName(QStringLiteral("portLE"));
        portLE->setMaximumSize(QSize(60, 16777215));
        portLE->setInputMethodHints(Qt::ImhDigitsOnly);
        portLE->setMaxLength(5);

        formLayout->setWidget(2, QFormLayout::FieldRole, portLE);

        layoutWidget3 = new QWidget(AddNetworkDlg);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(231, 12, 303, 192));
        formLayout_2 = new QFormLayout(layoutWidget3);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget3);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        nickLE = new QLineEdit(layoutWidget3);
        nickLE->setObjectName(QStringLiteral("nickLE"));
        nickLE->setEnabled(true);
        nickLE->setMinimumSize(QSize(200, 0));
        nickLE->setMaximumSize(QSize(200, 16777215));

        formLayout_2->setWidget(0, QFormLayout::FieldRole, nickLE);

        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);

        nick2LE = new QLineEdit(layoutWidget3);
        nick2LE->setObjectName(QStringLiteral("nick2LE"));
        nick2LE->setMinimumSize(QSize(200, 0));
        nick2LE->setMaximumSize(QSize(200, 16777215));

        formLayout_2->setWidget(1, QFormLayout::FieldRole, nick2LE);

        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_5);

        usernameLE = new QLineEdit(layoutWidget3);
        usernameLE->setObjectName(QStringLiteral("usernameLE"));
        usernameLE->setMinimumSize(QSize(200, 0));
        usernameLE->setMaximumSize(QSize(200, 16777215));

        formLayout_2->setWidget(2, QFormLayout::FieldRole, usernameLE);

        label_6 = new QLabel(layoutWidget3);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_6);

        realNameLE = new QLineEdit(layoutWidget3);
        realNameLE->setObjectName(QStringLiteral("realNameLE"));
        realNameLE->setMinimumSize(QSize(200, 0));
        realNameLE->setMaximumSize(QSize(200, 16777215));

        formLayout_2->setWidget(3, QFormLayout::FieldRole, realNameLE);

        label_7 = new QLabel(layoutWidget3);
        label_7->setObjectName(QStringLiteral("label_7"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(95, 0));
        label_7->setMaximumSize(QSize(95, 16777215));

        formLayout_2->setWidget(4, QFormLayout::LabelRole, label_7);

        loginMethodCbo = new QComboBox(layoutWidget3);
        loginMethodCbo->setObjectName(QStringLiteral("loginMethodCbo"));
        loginMethodCbo->setMinimumSize(QSize(200, 0));
        loginMethodCbo->setMaximumSize(QSize(200, 16777215));

        formLayout_2->setWidget(4, QFormLayout::FieldRole, loginMethodCbo);

        label_8 = new QLabel(layoutWidget3);
        label_8->setObjectName(QStringLiteral("label_8"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_8);

        passwordLE = new QLineEdit(layoutWidget3);
        passwordLE->setObjectName(QStringLiteral("passwordLE"));
        passwordLE->setMinimumSize(QSize(200, 0));
        passwordLE->setMaximumSize(QSize(200, 16777215));
        passwordLE->setEchoMode(QLineEdit::Password);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, passwordLE);

        label_10 = new QLabel(layoutWidget3);
        label_10->setObjectName(QStringLiteral("label_10"));

        formLayout_2->setWidget(6, QFormLayout::LabelRole, label_10);

        joinChansLE = new QLineEdit(layoutWidget3);
        joinChansLE->setObjectName(QStringLiteral("joinChansLE"));

        formLayout_2->setWidget(6, QFormLayout::FieldRole, joinChansLE);


        retranslateUi(AddNetworkDlg);
        QObject::connect(saveBtn, SIGNAL(clicked()), AddNetworkDlg, SLOT(accept()));
        QObject::connect(cancelBtn, SIGNAL(clicked()), AddNetworkDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(AddNetworkDlg);
    } // setupUi

    void retranslateUi(QDialog *AddNetworkDlg)
    {
        AddNetworkDlg->setWindowTitle(QApplication::translate("AddNetworkDlg", "Add Network", 0));
        connectCkb->setText(QApplication::translate("AddNetworkDlg", "Connect at Start-Up", 0));
        sslCkb->setText(QApplication::translate("AddNetworkDlg", "Use SSL Encryption", 0));
        invalidCertCkb->setText(QApplication::translate("AddNetworkDlg", "Accept Invalid SSL Certificate", 0));
        globalInfoCkb->setText(QApplication::translate("AddNetworkDlg", "Use Global Information", 0));
        cancelBtn->setText(QApplication::translate("AddNetworkDlg", "&Cancel", 0));
        saveBtn->setText(QApplication::translate("AddNetworkDlg", "&Save", 0));
        label_9->setText(QApplication::translate("AddNetworkDlg", "Network:", 0));
        label->setText(QApplication::translate("AddNetworkDlg", "Server:", 0));
        label_2->setText(QApplication::translate("AddNetworkDlg", "Port:", 0));
        label_3->setText(QApplication::translate("AddNetworkDlg", "Nickname:", 0));
        label_4->setText(QApplication::translate("AddNetworkDlg", "Second Nick:", 0));
        label_5->setText(QApplication::translate("AddNetworkDlg", "Username:", 0));
        label_6->setText(QApplication::translate("AddNetworkDlg", "Real Name:", 0));
        label_7->setText(QApplication::translate("AddNetworkDlg", "Login Method:", 0));
        loginMethodCbo->clear();
        loginMethodCbo->insertItems(0, QStringList()
         << QApplication::translate("AddNetworkDlg", "Default", 0)
         << QApplication::translate("AddNetworkDlg", "Server Password (/SERVER <PASS>)", 0)
         << QApplication::translate("AddNetworkDlg", "NickServ (/msg NickServ Identify <PASS>)", 0)
        );
        label_8->setText(QApplication::translate("AddNetworkDlg", "Password:", 0));
        label_10->setText(QApplication::translate("AddNetworkDlg", "Channels:", 0));
        joinChansLE->setPlaceholderText(QApplication::translate("AddNetworkDlg", "#chan1,#chan2,#chan3", 0));
    } // retranslateUi

};

namespace Ui {
    class AddNetworkDlg: public Ui_AddNetworkDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDNETWORKDLG_H
