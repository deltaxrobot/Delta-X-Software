/********************************************************************************
** Form generated from reading UI file 'AccountWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ACCOUNTWINDOW_H
#define UI_ACCOUNTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountWindow
{
public:
    QAction *actionNew;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *AccountWindow)
    {
        if (AccountWindow->objectName().isEmpty())
            AccountWindow->setObjectName(QString::fromUtf8("AccountWindow"));
        AccountWindow->resize(800, 600);
        actionNew = new QAction(AccountWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        centralwidget = new QWidget(AccountWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        AccountWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(AccountWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 26));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        AccountWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(AccountWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        AccountWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionNew);

        retranslateUi(AccountWindow);

        QMetaObject::connectSlotsByName(AccountWindow);
    } // setupUi

    void retranslateUi(QMainWindow *AccountWindow)
    {
        AccountWindow->setWindowTitle(QCoreApplication::translate("AccountWindow", "MainWindow", nullptr));
        actionNew->setText(QCoreApplication::translate("AccountWindow", "New", nullptr));
        menuFile->setTitle(QCoreApplication::translate("AccountWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountWindow: public Ui_AccountWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTWINDOW_H
