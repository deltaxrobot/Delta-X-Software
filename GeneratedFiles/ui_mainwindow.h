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
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "glwidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pbConnect;
    QLabel *lbState;
    QScrollArea *saProgramFiles;
    QWidget *wgProgramContainer;
    QFrame *frExProgram;
    QLineEdit *leExProgramName;
    QPushButton *pbExDeleteProgram;
    QLabel *lbExGCodeNumber;
    QLabel *lbDebug;
    QPushButton *pbHome;
    QPushButton *pbX;
    QLineEdit *leX;
    QPushButton *pbY;
    QLineEdit *leY;
    QLineEdit *leZ;
    QPushButton *pbZ;
    QPushButton *pbAddNewProgram;
    QPushButton *pbExecuteGcodes;
    QPushButton *pbSaveGcode;
    QPlainTextEdit *pteGcodeArea;
    QTabWidget *twDeltaGeometry;
    QWidget *t3D;
    GLWidget *wgOpenGl;
    QWidget *t2D;
    QWidget *wg2D;
    QSlider *vsZAdjsution;
    QWidget *tParameter;
    QWidget *widget;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *lineEdit_5;
    QLabel *label;
    QLabel *label_6;
    QLabel *label_2;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_8;
    QLineEdit *lineEdit_7;
    QLineEdit *lineEdit_8;
    QLineEdit *lineEdit_6;
    QLabel *label_7;
    QTabWidget *tabWidget;
    QWidget *tResultCameraArea;
    QLabel *lbCameraArea;
    QWidget *tab_2;
    QLineEdit *leTestImageUrl;
    QLabel *lbTestImage;
    QPushButton *pbHSV;
    QPushButton *pbLoadTestImage;
    QLineEdit *leTerminal;
    QPushButton *pbG01;
    QPushButton *pbG28;
    QPushButton *pbM03;
    QPushButton *pbM204;
    QPushButton *pbFormat;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1401, 822);
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
        saProgramFiles->setEnabled(true);
        saProgramFiles->setGeometry(QRect(10, 150, 291, 591));
        saProgramFiles->setStyleSheet(QStringLiteral(""));
        saProgramFiles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        saProgramFiles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        saProgramFiles->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        saProgramFiles->setWidgetResizable(false);
        wgProgramContainer = new QWidget();
        wgProgramContainer->setObjectName(QStringLiteral("wgProgramContainer"));
        wgProgramContainer->setGeometry(QRect(0, 0, 279, 589));
        frExProgram = new QFrame(wgProgramContainer);
        frExProgram->setObjectName(QStringLiteral("frExProgram"));
        frExProgram->setGeometry(QRect(10, 10, 261, 80));
        frExProgram->setStyleSheet(QStringLiteral("background-color:rgb(209, 209, 209)"));
        frExProgram->setFrameShape(QFrame::StyledPanel);
        frExProgram->setFrameShadow(QFrame::Raised);
        leExProgramName = new QLineEdit(frExProgram);
        leExProgramName->setObjectName(QStringLiteral("leExProgramName"));
        leExProgramName->setEnabled(true);
        leExProgramName->setGeometry(QRect(10, 10, 181, 41));
        QFont font;
        font.setPointSize(12);
        leExProgramName->setFont(font);
        leExProgramName->setCursor(QCursor(Qt::SizeHorCursor));
        leExProgramName->setStyleSheet(QStringLiteral(""));
        pbExDeleteProgram = new QPushButton(frExProgram);
        pbExDeleteProgram->setObjectName(QStringLiteral("pbExDeleteProgram"));
        pbExDeleteProgram->setGeometry(QRect(200, 10, 51, 41));
        pbExDeleteProgram->setAutoDefault(false);
        pbExDeleteProgram->setFlat(true);
        lbExGCodeNumber = new QLabel(frExProgram);
        lbExGCodeNumber->setObjectName(QStringLiteral("lbExGCodeNumber"));
        lbExGCodeNumber->setGeometry(QRect(10, 60, 101, 16));
        saProgramFiles->setWidget(wgProgramContainer);
        lbDebug = new QLabel(centralWidget);
        lbDebug->setObjectName(QStringLiteral("lbDebug"));
        lbDebug->setGeometry(QRect(10, 750, 1381, 31));
        lbDebug->setStyleSheet(QLatin1String("background-color:rgb(61, 61, 61);\n"
"color:rgb(1, 251, 255)"));
        pbHome = new QPushButton(centralWidget);
        pbHome->setObjectName(QStringLiteral("pbHome"));
        pbHome->setGeometry(QRect(1280, 120, 101, 27));
        pbX = new QPushButton(centralWidget);
        pbX->setObjectName(QStringLiteral("pbX"));
        pbX->setGeometry(QRect(1280, 160, 21, 27));
        leX = new QLineEdit(centralWidget);
        leX->setObjectName(QStringLiteral("leX"));
        leX->setGeometry(QRect(1310, 160, 71, 27));
        pbY = new QPushButton(centralWidget);
        pbY->setObjectName(QStringLiteral("pbY"));
        pbY->setGeometry(QRect(1280, 200, 21, 27));
        leY = new QLineEdit(centralWidget);
        leY->setObjectName(QStringLiteral("leY"));
        leY->setGeometry(QRect(1310, 200, 71, 27));
        leZ = new QLineEdit(centralWidget);
        leZ->setObjectName(QStringLiteral("leZ"));
        leZ->setGeometry(QRect(1310, 240, 71, 27));
        pbZ = new QPushButton(centralWidget);
        pbZ->setObjectName(QStringLiteral("pbZ"));
        pbZ->setGeometry(QRect(1280, 240, 21, 27));
        pbAddNewProgram = new QPushButton(centralWidget);
        pbAddNewProgram->setObjectName(QStringLiteral("pbAddNewProgram"));
        pbAddNewProgram->setGeometry(QRect(10, 100, 99, 41));
        pbExecuteGcodes = new QPushButton(centralWidget);
        pbExecuteGcodes->setObjectName(QStringLiteral("pbExecuteGcodes"));
        pbExecuteGcodes->setGeometry(QRect(320, 100, 99, 41));
        pbSaveGcode = new QPushButton(centralWidget);
        pbSaveGcode->setObjectName(QStringLiteral("pbSaveGcode"));
        pbSaveGcode->setGeometry(QRect(430, 100, 51, 41));
        pteGcodeArea = new QPlainTextEdit(centralWidget);
        pteGcodeArea->setObjectName(QStringLiteral("pteGcodeArea"));
        pteGcodeArea->setGeometry(QRect(320, 150, 411, 591));
        QFont font1;
        font1.setPointSize(14);
        pteGcodeArea->setFont(font1);
        twDeltaGeometry = new QTabWidget(centralWidget);
        twDeltaGeometry->setObjectName(QStringLiteral("twDeltaGeometry"));
        twDeltaGeometry->setGeometry(QRect(870, 90, 391, 341));
        t3D = new QWidget();
        t3D->setObjectName(QStringLiteral("t3D"));
        wgOpenGl = new GLWidget(t3D);
        wgOpenGl->setObjectName(QStringLiteral("wgOpenGl"));
        wgOpenGl->setGeometry(QRect(0, 10, 381, 301));
        twDeltaGeometry->addTab(t3D, QString());
        t2D = new QWidget();
        t2D->setObjectName(QStringLiteral("t2D"));
        wg2D = new QWidget(t2D);
        wg2D->setObjectName(QStringLiteral("wg2D"));
        wg2D->setGeometry(QRect(50, 10, 300, 300));
        vsZAdjsution = new QSlider(t2D);
        vsZAdjsution->setObjectName(QStringLiteral("vsZAdjsution"));
        vsZAdjsution->setGeometry(QRect(10, 9, 22, 301));
        vsZAdjsution->setMaximum(300);
        vsZAdjsution->setOrientation(Qt::Vertical);
        twDeltaGeometry->addTab(t2D, QString());
        tParameter = new QWidget();
        tParameter->setObjectName(QStringLiteral("tParameter"));
        widget = new QWidget(tParameter);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 10, 381, 301));
        label_9 = new QLabel(widget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(120, 130, 41, 20));
        label_9->setFont(font);
        label_9->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_10 = new QLabel(widget);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 130, 21, 20));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_5 = new QLineEdit(widget);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(40, 40, 81, 22));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 21, 20));
        label->setFont(font);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_6 = new QLabel(widget);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(10, 70, 21, 20));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(120, 10, 41, 20));
        label_2->setFont(font);
        label_2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_4 = new QLineEdit(widget);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(40, 10, 81, 22));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(120, 70, 41, 20));
        label_5->setFont(font);
        label_5->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 40, 21, 20));
        label_3->setFont(font);
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(120, 40, 41, 20));
        label_4->setFont(font);
        label_4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_8 = new QLabel(widget);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(120, 100, 41, 20));
        label_8->setFont(font);
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        lineEdit_7 = new QLineEdit(widget);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        lineEdit_7->setGeometry(QRect(40, 100, 81, 22));
        lineEdit_8 = new QLineEdit(widget);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        lineEdit_8->setGeometry(QRect(40, 130, 81, 22));
        lineEdit_6 = new QLineEdit(widget);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        lineEdit_6->setGeometry(QRect(40, 70, 81, 22));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 100, 21, 20));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        twDeltaGeometry->addTab(tParameter, QString());
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(870, 440, 391, 301));
        tResultCameraArea = new QWidget();
        tResultCameraArea->setObjectName(QStringLiteral("tResultCameraArea"));
        lbCameraArea = new QLabel(tResultCameraArea);
        lbCameraArea->setObjectName(QStringLiteral("lbCameraArea"));
        lbCameraArea->setGeometry(QRect(10, 10, 371, 251));
        lbCameraArea->setStyleSheet(QStringLiteral("background-color:rgb(255, 255, 255)"));
        lbCameraArea->setScaledContents(true);
        tabWidget->addTab(tResultCameraArea, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        leTestImageUrl = new QLineEdit(tab_2);
        leTestImageUrl->setObjectName(QStringLiteral("leTestImageUrl"));
        leTestImageUrl->setGeometry(QRect(10, 20, 301, 22));
        lbTestImage = new QLabel(tab_2);
        lbTestImage->setObjectName(QStringLiteral("lbTestImage"));
        lbTestImage->setGeometry(QRect(10, 50, 301, 211));
        lbTestImage->setStyleSheet(QStringLiteral("background-color:rgb(255, 255, 255)"));
        pbHSV = new QPushButton(tab_2);
        pbHSV->setObjectName(QStringLiteral("pbHSV"));
        pbHSV->setGeometry(QRect(320, 50, 61, 28));
        pbLoadTestImage = new QPushButton(tab_2);
        pbLoadTestImage->setObjectName(QStringLiteral("pbLoadTestImage"));
        pbLoadTestImage->setGeometry(QRect(320, 20, 61, 28));
        tabWidget->addTab(tab_2, QString());
        leTerminal = new QLineEdit(centralWidget);
        leTerminal->setObjectName(QStringLiteral("leTerminal"));
        leTerminal->setGeometry(QRect(10, 790, 1381, 22));
        pbG01 = new QPushButton(centralWidget);
        pbG01->setObjectName(QStringLiteral("pbG01"));
        pbG01->setGeometry(QRect(740, 150, 41, 28));
        pbG28 = new QPushButton(centralWidget);
        pbG28->setObjectName(QStringLiteral("pbG28"));
        pbG28->setGeometry(QRect(740, 190, 41, 28));
        pbM03 = new QPushButton(centralWidget);
        pbM03->setObjectName(QStringLiteral("pbM03"));
        pbM03->setGeometry(QRect(740, 230, 41, 28));
        pbM204 = new QPushButton(centralWidget);
        pbM204->setObjectName(QStringLiteral("pbM204"));
        pbM204->setGeometry(QRect(740, 270, 41, 28));
        pbFormat = new QPushButton(centralWidget);
        pbFormat->setObjectName(QStringLiteral("pbFormat"));
        pbFormat->setGeometry(QRect(740, 710, 61, 28));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        pbExDeleteProgram->setDefault(true);
        twDeltaGeometry->setCurrentIndex(1);
        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Delta Software", Q_NULLPTR));
        pbConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        lbState->setText(QApplication::translate("MainWindow", "Delta is not available !", Q_NULLPTR));
        leExProgramName->setText(QApplication::translate("MainWindow", "Program 1", Q_NULLPTR));
        pbExDeleteProgram->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        lbExGCodeNumber->setText(QApplication::translate("MainWindow", "100 Gcode Lines", Q_NULLPTR));
        lbDebug->setText(QApplication::translate("MainWindow", "Debug :", Q_NULLPTR));
        pbHome->setText(QApplication::translate("MainWindow", "Home", Q_NULLPTR));
        pbX->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        pbY->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        pbZ->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        pbAddNewProgram->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        pbExecuteGcodes->setText(QApplication::translate("MainWindow", "Execute", Q_NULLPTR));
        pbSaveGcode->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        pteGcodeArea->setPlainText(QApplication::translate("MainWindow", "G28\n"
"M03 S2000\n"
"M204 A4000", Q_NULLPTR));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t3D), QApplication::translate("MainWindow", "3D", Q_NULLPTR));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t2D), QApplication::translate("MainWindow", "2D", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "mm", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "b", Q_NULLPTR));
        lineEdit_5->setText(QString());
        label->setText(QApplication::translate("MainWindow", "f", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "re", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "mm", Q_NULLPTR));
        lineEdit_4->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "mm", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "rf", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "mm", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "mm", Q_NULLPTR));
        lineEdit_7->setText(QString());
        lineEdit_8->setText(QString());
        lineEdit_6->setText(QString());
        label_7->setText(QApplication::translate("MainWindow", "e", Q_NULLPTR));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(tParameter), QApplication::translate("MainWindow", "Parameter", Q_NULLPTR));
        lbCameraArea->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tResultCameraArea), QApplication::translate("MainWindow", "Result", Q_NULLPTR));
        lbTestImage->setText(QString());
        pbHSV->setText(QApplication::translate("MainWindow", "HSV", Q_NULLPTR));
        pbLoadTestImage->setText(QApplication::translate("MainWindow", "Load", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Test Image", Q_NULLPTR));
        pbG01->setText(QApplication::translate("MainWindow", "G01", Q_NULLPTR));
        pbG28->setText(QApplication::translate("MainWindow", "G28", Q_NULLPTR));
        pbM03->setText(QApplication::translate("MainWindow", "M03", Q_NULLPTR));
        pbM204->setText(QApplication::translate("MainWindow", "M204", Q_NULLPTR));
        pbFormat->setText(QApplication::translate("MainWindow", "Format", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
