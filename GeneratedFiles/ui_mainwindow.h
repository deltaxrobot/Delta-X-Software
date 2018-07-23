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
    QWidget *wgProgramContainer;
    QFrame *frExProgram;
    QLineEdit *leExProgramName;
    QPushButton *pbExDeleteProgram;
    QLabel *lbExGCodeNumber;
    QTextEdit *teGcodeArea;
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
    QPushButton *pbAddNewProgram;
    QPushButton *pbExecuteGcodes;

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
        teGcodeArea = new QTextEdit(centralWidget);
        teGcodeArea->setObjectName(QStringLiteral("teGcodeArea"));
        teGcodeArea->setGeometry(QRect(310, 150, 361, 591));
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
        pbAddNewProgram = new QPushButton(centralWidget);
        pbAddNewProgram->setObjectName(QStringLiteral("pbAddNewProgram"));
        pbAddNewProgram->setGeometry(QRect(10, 100, 99, 41));
        pbExecuteGcodes = new QPushButton(centralWidget);
        pbExecuteGcodes->setObjectName(QStringLiteral("pbExecuteGcodes"));
        pbExecuteGcodes->setGeometry(QRect(310, 100, 99, 41));
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        pbExDeleteProgram->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Delta Softwareoftware", Q_NULLPTR));
        pbConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        lbState->setText(QApplication::translate("MainWindow", "Delta is not available !", Q_NULLPTR));
        leExProgramName->setText(QApplication::translate("MainWindow", "Program 1", Q_NULLPTR));
        pbExDeleteProgram->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        lbExGCodeNumber->setText(QApplication::translate("MainWindow", "100 Gcode Lines", Q_NULLPTR));
        teGcodeArea->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454 W90 U100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-in"
                        "dent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p sty"
                        "le=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block"
                        "-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G01 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</sp"
                        "an></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">G02 X231 Y121 Z454</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt;\"><br /></p></body></html>", Q_NULLPTR));
        lbDebug->setText(QApplication::translate("MainWindow", "Debug :", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MainWindow", "Home", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        lbCameraArea->setText(QString());
        pbAddNewProgram->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        pbExecuteGcodes->setText(QApplication::translate("MainWindow", "Execute", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
