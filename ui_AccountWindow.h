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
#include <QtWidgets/QFrame>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AccountWindow
{
public:
    QAction *actionNew;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *splitter;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;
    QToolButton *toolButton;
    QRadioButton *radioButton;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButton_2;
    QToolButton *toolButton_2;
    QPushButton *pushButton_3;
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
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(10);
        sizePolicy.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy);
        splitter->setOrientation(Qt::Vertical);
        frame = new QFrame(splitter);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMaximumSize(QSize(16777215, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);

        toolButton = new QToolButton(frame);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));

        verticalLayout->addWidget(toolButton);

        radioButton = new QRadioButton(frame);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        verticalLayout->addWidget(radioButton);

        splitter->addWidget(frame);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(20);
        sizePolicy2.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy2);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButton_2 = new QPushButton(frame_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);

        toolButton_2 = new QToolButton(frame_2);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        verticalLayout_2->addWidget(toolButton_2);

        pushButton_3 = new QPushButton(frame_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        verticalLayout_2->addWidget(pushButton_3);

        splitter->addWidget(frame_2);

        verticalLayout_3->addWidget(splitter);

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
        pushButton->setText(QCoreApplication::translate("AccountWindow", "PushButton", nullptr));
        toolButton->setText(QCoreApplication::translate("AccountWindow", "...", nullptr));
        radioButton->setText(QCoreApplication::translate("AccountWindow", "RadioButton", nullptr));
        pushButton_2->setText(QCoreApplication::translate("AccountWindow", "PushButton", nullptr));
        toolButton_2->setText(QCoreApplication::translate("AccountWindow", "...", nullptr));
        pushButton_3->setText(QCoreApplication::translate("AccountWindow", "PushButton", nullptr));
        menuFile->setTitle(QCoreApplication::translate("AccountWindow", "File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AccountWindow: public Ui_AccountWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ACCOUNTWINDOW_H
