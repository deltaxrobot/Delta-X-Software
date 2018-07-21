/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pbConnect;
    QLabel *lbState;
    QScrollArea *saProgramFiles;
    QWidget *scrollAreaWidgetContents;
    QTextEdit *textEdit;
    QWidget *wgOpenGl;
    QLabel *lbDebug;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit_2;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton_4;
    QLabel *lbCameraArea;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1223, 792);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pbConnect = new QPushButton(centralWidget);
        pbConnect->setObjectName(QStringLiteral("pbConnect"));
        pbConnect->setGeometry(QRect(10, 10, 99, 61));
        lbState = new QLabel(centralWidget);
        lbState->setObjectName(QStringLiteral("lbState"));
        lbState->setGeometry(QRect(130, 30, 201, 17));
        lbState->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        saProgramFiles = new QScrollArea(centralWidget);
        saProgramFiles->setObjectName(QStringLiteral("saProgramFiles"));
        saProgramFiles->setGeometry(QRect(10, 150, 281, 591));
        saProgramFiles->setStyleSheet(QStringLiteral(""));
        saProgramFiles->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 279, 589));
        saProgramFiles->setWidget(scrollAreaWidgetContents);
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(310, 150, 361, 591));
        wgOpenGl = new QWidget(centralWidget);
        wgOpenGl->setObjectName(QStringLiteral("wgOpenGl"));
        wgOpenGl->setGeometry(QRect(810, 110, 391, 331));
        lbDebug = new QLabel(centralWidget);
        lbDebug->setObjectName(QStringLiteral("lbDebug"));
        lbDebug->setGeometry(QRect(10, 760, 1201, 17));
        lbDebug->setStyleSheet(QLatin1String("background-color:rgb(61, 61, 61);\n"
"color:rgb(1, 251, 255)"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(690, 110, 101, 27));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(690, 150, 21, 27));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(720, 150, 71, 27));
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(690, 190, 21, 27));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(720, 190, 71, 27));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(720, 230, 71, 27));
        pushButton_4 = new QPushButton(centralWidget);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(690, 230, 21, 27));
        lbCameraArea = new QLabel(centralWidget);
        lbCameraArea->setObjectName(QStringLiteral("lbCameraArea"));
        lbCameraArea->setGeometry(QRect(810, 450, 391, 291));
        lbCameraArea->setStyleSheet(QStringLiteral("background-color:rgb(255, 255, 255)"));
        lbCameraArea->setScaledContents(true);
        pushButton_5 = new QPushButton(centralWidget);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(10, 100, 99, 41));
        pushButton_6 = new QPushButton(centralWidget);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(310, 100, 99, 41));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Delta Softwareoftware", Q_NULLPTR));
        pbConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        lbState->setText(QApplication::translate("MainWindow", "Delta is not available !", Q_NULLPTR));
        lbDebug->setText(QApplication::translate("MainWindow", "Debug :", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Home", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        lbCameraArea->setText(QString());
        pushButton_5->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("MainWindow", "Execute", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
