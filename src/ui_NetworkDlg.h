/********************************************************************************
** Form generated from reading UI file 'NetworkDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NETWORKDLG_H
#define UI_NETWORKDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkDlg
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancelBtn;
    QPushButton *connectBtn;
    QWidget *layoutWidget1;
    QFormLayout *formLayout;
    QLineEdit *gblNickLE;
    QLabel *label_2;
    QLineEdit *gblNick2LE;
    QLabel *label_3;
    QLineEdit *gblUsernameLE;
    QLabel *label_4;
    QLineEdit *gblRealNameLE;
    QLabel *label;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout;
    QListWidget *networkList;
    QVBoxLayout *verticalLayout;
    QPushButton *addBtn;
    QPushButton *editBtn;
    QSpacerItem *verticalSpacer;
    QPushButton *removeBtn;
    QLabel *label_5;

    void setupUi(QDialog *NetworkDlg)
    {
        if (NetworkDlg->objectName().isEmpty())
            NetworkDlg->setObjectName(QStringLiteral("NetworkDlg"));
        NetworkDlg->resize(322, 356);
        NetworkDlg->setMinimumSize(QSize(322, 356));
        NetworkDlg->setMaximumSize(QSize(322, 356));
        NetworkDlg->setFocusPolicy(Qt::StrongFocus);
        layoutWidget = new QWidget(NetworkDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(9, 320, 301, 26));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancelBtn = new QPushButton(layoutWidget);
        cancelBtn->setObjectName(QStringLiteral("cancelBtn"));

        horizontalLayout_2->addWidget(cancelBtn);

        connectBtn = new QPushButton(layoutWidget);
        connectBtn->setObjectName(QStringLiteral("connectBtn"));

        horizontalLayout_2->addWidget(connectBtn);

        layoutWidget1 = new QWidget(NetworkDlg);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 10, 301, 116));
        formLayout = new QFormLayout(layoutWidget1);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        gblNickLE = new QLineEdit(layoutWidget1);
        gblNickLE->setObjectName(QStringLiteral("gblNickLE"));

        formLayout->setWidget(0, QFormLayout::FieldRole, gblNickLE);

        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        gblNick2LE = new QLineEdit(layoutWidget1);
        gblNick2LE->setObjectName(QStringLiteral("gblNick2LE"));

        formLayout->setWidget(1, QFormLayout::FieldRole, gblNick2LE);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        gblUsernameLE = new QLineEdit(layoutWidget1);
        gblUsernameLE->setObjectName(QStringLiteral("gblUsernameLE"));

        formLayout->setWidget(2, QFormLayout::FieldRole, gblUsernameLE);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        gblRealNameLE = new QLineEdit(layoutWidget1);
        gblRealNameLE->setObjectName(QStringLiteral("gblRealNameLE"));

        formLayout->setWidget(3, QFormLayout::FieldRole, gblRealNameLE);

        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        layoutWidget2 = new QWidget(NetworkDlg);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 160, 301, 141));
        horizontalLayout = new QHBoxLayout(layoutWidget2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        networkList = new QListWidget(layoutWidget2);
        networkList->setObjectName(QStringLiteral("networkList"));

        horizontalLayout->addWidget(networkList);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        addBtn = new QPushButton(layoutWidget2);
        addBtn->setObjectName(QStringLiteral("addBtn"));

        verticalLayout->addWidget(addBtn);

        editBtn = new QPushButton(layoutWidget2);
        editBtn->setObjectName(QStringLiteral("editBtn"));

        verticalLayout->addWidget(editBtn);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        removeBtn = new QPushButton(layoutWidget2);
        removeBtn->setObjectName(QStringLiteral("removeBtn"));

        verticalLayout->addWidget(removeBtn);


        horizontalLayout->addLayout(verticalLayout);

        label_5 = new QLabel(NetworkDlg);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(10, 140, 71, 16));
#ifndef QT_NO_SHORTCUT
        label_2->setBuddy(gblNick2LE);
        label_3->setBuddy(gblUsernameLE);
        label_4->setBuddy(gblRealNameLE);
        label->setBuddy(gblNickLE);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(gblNickLE, gblNick2LE);
        QWidget::setTabOrder(gblNick2LE, gblUsernameLE);
        QWidget::setTabOrder(gblUsernameLE, gblRealNameLE);
        QWidget::setTabOrder(gblRealNameLE, addBtn);
        QWidget::setTabOrder(addBtn, editBtn);
        QWidget::setTabOrder(editBtn, cancelBtn);
        QWidget::setTabOrder(cancelBtn, networkList);

        retranslateUi(NetworkDlg);

        QMetaObject::connectSlotsByName(NetworkDlg);
    } // setupUi

    void retranslateUi(QDialog *NetworkDlg)
    {
        NetworkDlg->setWindowTitle(QApplication::translate("NetworkDlg", "Networks", 0));
        cancelBtn->setText(QApplication::translate("NetworkDlg", "&Cancel", 0));
        connectBtn->setText(QApplication::translate("NetworkDlg", "Co&nnect", 0));
        label_2->setText(QApplication::translate("NetworkDlg", "Second Nic&kname:", 0));
        label_3->setText(QApplication::translate("NetworkDlg", "&Username:", 0));
        label_4->setText(QApplication::translate("NetworkDlg", "Rea&l Name:", 0));
        label->setText(QApplication::translate("NetworkDlg", "&Nickname:", 0));
        addBtn->setText(QApplication::translate("NetworkDlg", "&Add", 0));
        editBtn->setText(QApplication::translate("NetworkDlg", "&Edit", 0));
        removeBtn->setText(QApplication::translate("NetworkDlg", "Remove", 0));
        label_5->setText(QApplication::translate("NetworkDlg", "Networks:", 0));
    } // retranslateUi

};

namespace Ui {
    class NetworkDlg: public Ui_NetworkDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKDLG_H
