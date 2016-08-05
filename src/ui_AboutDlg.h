/********************************************************************************
** Form generated from reading UI file 'AboutDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ABOUTDLG_H
#define UI_ABOUTDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AboutDlg
{
public:
    QPushButton *closeBtn;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_4;
    QLabel *label_5;
    QSpacerItem *verticalSpacer_2;
    QLabel *label_3;
    QSpacerItem *verticalSpacer;
    QLabel *label_6;

    void setupUi(QDialog *AboutDlg)
    {
        if (AboutDlg->objectName().isEmpty())
            AboutDlg->setObjectName(QStringLiteral("AboutDlg"));
        AboutDlg->resize(600, 338);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AboutDlg->sizePolicy().hasHeightForWidth());
        AboutDlg->setSizePolicy(sizePolicy);
        AboutDlg->setMinimumSize(QSize(600, 338));
        AboutDlg->setMaximumSize(QSize(600, 338));
        closeBtn = new QPushButton(AboutDlg);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setGeometry(QRect(500, 300, 91, 27));
        layoutWidget = new QWidget(AboutDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(130, 0, 461, 291));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans"));
        font.setPointSize(40);
        label->setFont(font);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font1;
        font1.setFamily(QStringLiteral("DejaVu Sans"));
        label_2->setFont(font1);

        verticalLayout->addWidget(label_2);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout->addWidget(label_4);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout->addWidget(label_5);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setTextFormat(Qt::AutoText);
        label_3->setWordWrap(true);

        verticalLayout->addWidget(label_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        verticalLayout->addWidget(label_6);


        retranslateUi(AboutDlg);
        QObject::connect(closeBtn, SIGNAL(clicked()), AboutDlg, SLOT(close()));

        QMetaObject::connectSlotsByName(AboutDlg);
    } // setupUi

    void retranslateUi(QDialog *AboutDlg)
    {
        AboutDlg->setWindowTitle(QApplication::translate("AboutDlg", "About", 0));
        closeBtn->setText(QApplication::translate("AboutDlg", "Close", 0));
        label->setText(QApplication::translate("AboutDlg", "LuxIRC", 0));
        label_2->setText(QApplication::translate("AboutDlg", "Version: 0.0.0 (ALPHA)", 0));
        label_4->setText(QApplication::translate("AboutDlg", "Developer: Cody Johnson [<a href=\"mailto:codyj@protonmail.com\">codyj@protonmail.com</a>]", 0));
        label_5->setText(QApplication::translate("AboutDlg", "Source Code: <a href=\"https://github.com/codymj/LuxIRC\">https://github.com/codymj/LuxIRC</a>", 0));
        label_3->setText(QApplication::translate("AboutDlg", "LuxIRC is an easy to use, free and open source IRC client developed with C++ using the Qt toolkit. It is a personal project of mine helping me with developing in a GUI environment along with networking, version control and bug reporting. I will expand the program further by making it scriptable with Lua and Python. I am testing the program in Arch Linux, Windows 7 and Windows 10. I will try to get a Mac VM up and running to test in that environment in the near future.", 0));
        label_6->setText(QApplication::translate("AboutDlg", "Qt Website: <a href=\"http://www.qt.io/\">http://www.qt.io/</a>", 0));
    } // retranslateUi

};

namespace Ui {
    class AboutDlg: public Ui_AboutDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ABOUTDLG_H
