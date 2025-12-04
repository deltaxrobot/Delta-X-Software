/********************************************************************************
** Form generated from reading UI file 'testwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWINDOW_H
#define UI_TESTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TestWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *openCameraButton;
    QSplitter *splitter;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QFrame *frame_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *cameraLabel;
    QWidget *tab_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *TestWindow)
    {
        if (TestWindow->objectName().isEmpty())
            TestWindow->setObjectName("TestWindow");
        TestWindow->resize(800, 600);
        centralwidget = new QWidget(TestWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        openCameraButton = new QPushButton(centralwidget);
        openCameraButton->setObjectName("openCameraButton");

        verticalLayout_4->addWidget(openCameraButton);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Horizontal);
        frame_2 = new QFrame(splitter);
        frame_2->setObjectName("frame_2");
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame_2);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(frame_2);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        frame_3 = new QFrame(tab);
        frame_3->setObjectName("frame_3");
        frame_3->setMinimumSize(QSize(400, 0));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        verticalLayout_5 = new QVBoxLayout(frame_3);
        verticalLayout_5->setObjectName("verticalLayout_5");
        cameraLabel = new QLabel(frame_3);
        cameraLabel->setObjectName("cameraLabel");

        verticalLayout_5->addWidget(cameraLabel);


        verticalLayout_3->addWidget(frame_3);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        splitter->addWidget(frame_2);
        frame = new QFrame(splitter);
        frame->setObjectName("frame");
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frame);
        verticalLayout_2->setObjectName("verticalLayout_2");
        tabWidget_2 = new QTabWidget(frame);
        tabWidget_2->setObjectName("tabWidget_2");
        tab_3 = new QWidget();
        tab_3->setObjectName("tab_3");
        tabWidget_2->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName("tab_4");
        tabWidget_2->addTab(tab_4, QString());

        verticalLayout_2->addWidget(tabWidget_2);

        splitter->addWidget(frame);

        verticalLayout_4->addWidget(splitter);

        TestWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(TestWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        TestWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(TestWindow);
        statusbar->setObjectName("statusbar");
        TestWindow->setStatusBar(statusbar);

        retranslateUi(TestWindow);

        QMetaObject::connectSlotsByName(TestWindow);
    } // setupUi

    void retranslateUi(QMainWindow *TestWindow)
    {
        TestWindow->setWindowTitle(QCoreApplication::translate("TestWindow", "MainWindow", nullptr));
        openCameraButton->setText(QCoreApplication::translate("TestWindow", "PushButton", nullptr));
        cameraLabel->setText(QCoreApplication::translate("TestWindow", "TextLabel", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("TestWindow", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("TestWindow", "Tab 2", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_3), QCoreApplication::translate("TestWindow", "Tab 1", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("TestWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TestWindow: public Ui_TestWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWINDOW_H
