/********************************************************************************
** Form generated from reading UI file 'ChangeNickDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHANGENICKDLG_H
#define UI_CHANGENICKDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChangeNickDlg
{
public:
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *newNickLineEdit;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *cancelButton;
    QPushButton *okButton;

    void setupUi(QDialog *ChangeNickDlg)
    {
        if (ChangeNickDlg->objectName().isEmpty())
            ChangeNickDlg->setObjectName(QStringLiteral("ChangeNickDlg"));
        ChangeNickDlg->resize(300, 100);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ChangeNickDlg->sizePolicy().hasHeightForWidth());
        ChangeNickDlg->setSizePolicy(sizePolicy);
        ChangeNickDlg->setMinimumSize(QSize(300, 100));
        ChangeNickDlg->setMaximumSize(QSize(300, 100));
        layoutWidget = new QWidget(ChangeNickDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 252, 27));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        newNickLineEdit = new QLineEdit(layoutWidget);
        newNickLineEdit->setObjectName(QStringLiteral("newNickLineEdit"));

        horizontalLayout->addWidget(newNickLineEdit);

        layoutWidget1 = new QWidget(ChangeNickDlg);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(120, 70, 168, 24));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        cancelButton = new QPushButton(layoutWidget1);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));

        horizontalLayout_2->addWidget(cancelButton);

        okButton = new QPushButton(layoutWidget1);
        okButton->setObjectName(QStringLiteral("okButton"));
        okButton->setDefault(true);

        horizontalLayout_2->addWidget(okButton);


        retranslateUi(ChangeNickDlg);

        QMetaObject::connectSlotsByName(ChangeNickDlg);
    } // setupUi

    void retranslateUi(QDialog *ChangeNickDlg)
    {
        ChangeNickDlg->setWindowTitle(QApplication::translate("ChangeNickDlg", "Change your nickname", 0));
        label->setText(QApplication::translate("ChangeNickDlg", "Enter new nick:", 0));
        cancelButton->setText(QApplication::translate("ChangeNickDlg", "&Cancel", 0));
        okButton->setText(QApplication::translate("ChangeNickDlg", "&Ok", 0));
    } // retranslateUi

};

namespace Ui {
    class ChangeNickDlg: public Ui_ChangeNickDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHANGENICKDLG_H
