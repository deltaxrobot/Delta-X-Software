/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAdd;
    QAction *actionRemove;
    QAction *actionAbout;
    QAction *actionGcode;
    QAction *actionSoftware;
    QAction *actionExecute_All;
    QAction *actionDelta_X_1;
    QAction *actionExecute;
    QAction *actionBaudrate;
    QAction *actionScale;
    QAction *actionG_code_Program;
    QAction *actionRobot;
    QAction *actionProject;
    QAction *actionG_code_Program_2;
    QAction *actionRobot_2;
    QAction *actionProject_2;
    QAction *actionNew;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_2;
    QWidget *wgLeftPanel;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_5;
    QToolButton *tbOpenProject;
    QToolButton *tbSaveProject;
    QSpacerItem *verticalSpacer_3;
    QToolButton *tbHome;
    QToolButton *tbProject;
    QToolButton *tbVariable;
    QToolButton *tbMarket;
    QToolButton *tbDocument;
    QToolButton *tbCommunity;
    QToolButton *tbAuthority;
    QSpacerItem *verticalSpacer;
    QToolButton *tbSetting;
    QVBoxLayout *verticalLayout_11;
    QStackedWidget *swPageStack;
    QWidget *pVariable;
    QVBoxLayout *verticalLayout_4;
    QFrame *fVar;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_12;
    QLineEdit *leUpdateKey;
    QLabel *label_13;
    QLineEdit *leUpdateValue;
    QPushButton *pbUpdateVarDisplay;
    QPushButton *pbDeleteSelectedVar;
    QSpacerItem *horizontalSpacer_7;
    QTreeView *tvVariables;
    QWidget *pOperator;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_21;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_10;
    QLabel *lbOperatorTitile;
    QHBoxLayout *horizontalLayout_8;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_9;
    QFrame *frame;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pbStartSystem;
    QPushButton *pbStopSystem;
    QSpacerItem *verticalSpacer_4;
    QFrame *fOperatorRobotOnOffPanel;
    QGridLayout *layoutOperatorRobotOnOff;
    QWidget *wgOperatorDisplay;
    QHBoxLayout *horizontalLayout_11;
    QGraphicsView *gvOperatorViewer;
    QTreeWidget *twOperatorParameter;
    QPushButton *pbOperatorResetParameter;
    QPushButton *pbSwitchProgramer;
    QWidget *pHome;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_3;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QPushButton *pushButton_7;
    QPushButton *pushButton_9;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_3;
    QPlainTextEdit *plainTextEdit;
    QPushButton *pushButton_5;
    QSpacerItem *verticalSpacer_2;
    QWidget *pMarket;
    QWidget *pDocument;
    QWidget *pAuthority;
    QVBoxLayout *verticalLayout_5;
    QStackedWidget *swAuthority;
    QWidget *pProgramer;
    QVBoxLayout *verticalLayout_6;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_4;
    QListWidget *lwOperatorDisplayVariable;
    QPushButton *pbApplyOperator;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_9;
    QPushButton *pbAddOperatorDisplayWidget;
    QComboBox *cbOperatorRobotDisplay;
    QComboBox *cbOperatorDisplayWidget;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_3;
    QListWidget *lwOperatorDisplayWidget;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_8;
    QComboBox *cbOperatorProject;
    QLabel *label_16;
    QLineEdit *leOperatorTitle;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbDeleteOperatorVar;
    QListWidget *lwOperatorRobotGcodeProgram;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pbAddVarToOperatorDisplay;
    QLabel *label_10;
    QLineEdit *leOperatorVar;
    QLabel *label_14;
    QLineEdit *leOperatorVarName;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_15;
    QLineEdit *leAuthorityPassword;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_11;
    QPushButton *pbAddOperatorGcodeProgram;
    QComboBox *cbOperatorRobot;
    QComboBox *cbOperatorGcodeProgram;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pbDeleteOperatorDisplayWidget;
    QPushButton *pbDeleteOperatorGcodeProgram;
    QWidget *pCommunity;
    QWidget *pSetting;
    QVBoxLayout *verticalLayout_12;
    QLabel *lbSettingsTitle;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *pbResetSettings;
    QPushButton *pbBackupSettings;
    QPushButton *pbRestoreSettings;
    QSpacerItem *horizontalSpacer;
    QPushButton *pbSaveSetting;
    QTabWidget *twSettingsCategories;
    QWidget *tabGeneral;
    QVBoxLayout *vlGeneral;
    QScrollArea *saGeneral;
    QWidget *swGeneral;
    QVBoxLayout *vlGeneralContent;
    QWidget *tabDevice;
    QVBoxLayout *vlDevice;
    QScrollArea *saDevice;
    QWidget *swDevice;
    QVBoxLayout *vlDeviceContent;
    QWidget *tabCamera;
    QVBoxLayout *vlCamera;
    QScrollArea *saCamera;
    QWidget *swCamera;
    QVBoxLayout *vlCameraContent;
    QWidget *tabEditor;
    QVBoxLayout *vlEditor;
    QScrollArea *saEditor;
    QWidget *swEditor;
    QVBoxLayout *vlEditorContent;
    QWidget *tabAdvanced;
    QVBoxLayout *vlAdvanced;
    QScrollArea *saAdvanced;
    QWidget *swAdvanced;
    QVBoxLayout *vlAdvancedContent;
    QWidget *tabAuthority;
    QVBoxLayout *vlAuthority;
    QScrollArea *saAuthority;
    QWidget *swAuthority1;
    QVBoxLayout *vlAuthorityContent;
    QWidget *pProject;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *twProjectManager;
    QWidget *tabAddNewButton;
    QFrame *fFileMenu;
    QHBoxLayout *horizontalLayout_10;
    QTextEdit *teLoggingBox;
    QToolButton *tbExpandLoggingBox;
    QWidget *pFullTabDisplay;
    QVBoxLayout *layoutFullTabDisplay;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 700);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 480));
        QFont font;
        font.setBold(false);
        font.setKerning(true);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/delta_x_logo_96x96.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        actionAdd = new QAction(MainWindow);
        actionAdd->setObjectName(QString::fromUtf8("actionAdd"));
        actionRemove = new QAction(MainWindow);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionGcode = new QAction(MainWindow);
        actionGcode->setObjectName(QString::fromUtf8("actionGcode"));
        actionSoftware = new QAction(MainWindow);
        actionSoftware->setObjectName(QString::fromUtf8("actionSoftware"));
        actionExecute_All = new QAction(MainWindow);
        actionExecute_All->setObjectName(QString::fromUtf8("actionExecute_All"));
        actionDelta_X_1 = new QAction(MainWindow);
        actionDelta_X_1->setObjectName(QString::fromUtf8("actionDelta_X_1"));
        actionDelta_X_1->setCheckable(true);
        actionDelta_X_1->setChecked(true);
        actionExecute = new QAction(MainWindow);
        actionExecute->setObjectName(QString::fromUtf8("actionExecute"));
        actionBaudrate = new QAction(MainWindow);
        actionBaudrate->setObjectName(QString::fromUtf8("actionBaudrate"));
        actionScale = new QAction(MainWindow);
        actionScale->setObjectName(QString::fromUtf8("actionScale"));
        actionG_code_Program = new QAction(MainWindow);
        actionG_code_Program->setObjectName(QString::fromUtf8("actionG_code_Program"));
        actionRobot = new QAction(MainWindow);
        actionRobot->setObjectName(QString::fromUtf8("actionRobot"));
        actionProject = new QAction(MainWindow);
        actionProject->setObjectName(QString::fromUtf8("actionProject"));
        actionG_code_Program_2 = new QAction(MainWindow);
        actionG_code_Program_2->setObjectName(QString::fromUtf8("actionG_code_Program_2"));
        actionRobot_2 = new QAction(MainWindow);
        actionRobot_2->setObjectName(QString::fromUtf8("actionRobot_2"));
        actionProject_2 = new QAction(MainWindow);
        actionProject_2->setObjectName(QString::fromUtf8("actionProject_2"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setStyleSheet(QString::fromUtf8("/* ===========================================\n"
"   MAIN APPLICATION STYLES - Delta X Software\n"
"   =========================================== */\n"
"\n"
"/* Global Dark Theme */\n"
"QWidget#centralWidget {\n"
"    background-color: rgb(30, 30, 32);\n"
"}\n"
"\n"
"\n"
"\n"
"/* ===========================================\n"
"   TAB WIDGET STYLES\n"
"   =========================================== */\n"
"QTabWidget::pane {\n"
"    border: none;\n"
"}\n"
"\n"
"QTabBar::tab {\n"
"    background: #3f3f3f;\n"
"    color: #f5f5f5;\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    height: 25px;\n"
"    padding: 0px 10px 2px 10px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #007cd6;	\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #6f6f6f;	\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* ===========================================\n"
"   LEFT PANEL NAVIGATION\n"
"   =========================================== */\n"
"QWidget#wgLeftPanel {\n"
"    backgr"
                        "ound-color: #28282B;\n"
"    border: 1px solid #565659;\n"
"}\n"
"\n"
"QWidget#wgLeftPanel QToolButton {\n"
"    border: 0px;\n"
"    font-size: 14px;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#wgLeftPanel QToolButton:hover {\n"
"    background-color: #353538;\n"
"}\n"
"\n"
"QWidget#wgLeftPanel QToolButton:pressed {\n"
"    background-color: #3F3F42;\n"
"}\n"
"\n"
"/* Active/Selected Navigation Button */\n"
"QToolButton#tbProject {\n"
"    background-color: #3F3F42;\n"
"    border-right: 5px solid rgb(24, 70, 139);\n"
"}\n"
"\n"
"/* ===========================================\n"
"   PAGE SPECIFIC STYLES\n"
"   =========================================== */\n"
"/* Variable Page */\n"
"QWidget#pVariable {\n"
"    background-color: rgb(40, 40, 43);\n"
"}\n"
"\n"
"QWidget#pVariable QLabel {\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* Market Page */\n"
"QWidget#pMarket {\n"
"    background-color: rgb(85, 170, 255);\n"
"}\n"
"\n"
"/* Document Page */\n"
"QWidget#pDocument {\n"
"    background"
                        "-color: rgb(255, 170, 255);\n"
"}\n"
"\n"
"/* Community Page */\n"
"QWidget#pCommunity {\n"
"    background-color: rgb(255, 170, 127);\n"
"}\n"
"\n"
"/* Project Page */\n"
"QWidget#pProject {\n"
"    alternate-background-color: rgb(255, 235, 15);\n"
"}\n"
"\n"
"/* ===========================================\n"
"   SETTINGS PAGE STYLES\n"
"   =========================================== */\n"
"QWidget#pSetting {\n"
"    background-color: rgb(30, 30, 32);\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QLabel#lbSettingsTitle {\n"
"    color: rgb(255, 255, 255);\n"
"    margin-bottom: 10px;\n"
"}\n"
"\n"
"/* Settings Action Buttons Frame */\n"
"QWidget#pSetting QFrame#frame_3 {\n"
"    background-color: rgba(255, 255, 255, 0.1);\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
"\n"
"/* Settings Buttons */\n"
"QWidget#pSetting QPushButton#pbResetSettings {\n"
"    background-color: #6C5C99;\n"
"    border-radius: 5px;\n"
"    padding: 8px 16px;\n"
"    color: rgb(255, 255, 255);\n"
"   "
                        " font-weight: bold;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbResetSettings:hover {\n"
"    background-color: #7D6DAD;\n"
"    border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbResetSettings:pressed {\n"
"    background-color: #5B4B88;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbBackupSettings {\n"
"    background-color: #4A7C59;\n"
"    border-radius: 5px;\n"
"    padding: 8px 16px;\n"
"    color: rgb(255, 255, 255);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbBackupSettings:hover {\n"
"    background-color: #5A8B68;\n"
"    border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbBackupSettings:pressed {\n"
"    background-color: #3A6A49;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbRestoreSettings {\n"
"    background-color: #B8860B;\n"
"    border-radius: 5px;\n"
"    padding: 8px 16px;\n"
"    color: rgb(255, 255, 255);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbRestoreSettings:hover {\n"
"    backgrou"
                        "nd-color: #DAA520;\n"
"    border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbRestoreSettings:pressed {\n"
"    background-color: #996F0B;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbSaveSetting {\n"
"    background-color: #007ACC;\n"
"    border-radius: 5px;\n"
"    padding: 8px 16px;\n"
"    color: rgb(255, 255, 255);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbSaveSetting:hover {\n"
"    background-color: #1E90FF;\n"
"    border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbSaveSetting:pressed {\n"
"    background-color: #005299;\n"
"}\n"
"\n"
"/* Settings Tab Widget */\n"
"QWidget#pSetting QTabWidget#twSettingsCategories::pane {\n"
"    border: 1px solid #444444;\n"
"    border-radius: 5px;\n"
"}\n"
"\n"
"QWidget#pSetting QTabWidget#twSettingsCategories QTabBar::tab {\n"
"    background: rgb(68, 68, 68);\n"
"    color: #f5f5f5;\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    height: 30px;\n"
"    padding: 5px 15px;\n"
"    margin-r"
                        "ight: 2px;\n"
"}\n"
"\n"
"QWidget#pSetting QTabWidget#twSettingsCategories QTabBar::tab:selected {\n"
"    background: #007cd6;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QTabWidget#twSettingsCategories QTabBar::tab:hover {\n"
"    background: #6f6f6f;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* Settings Scroll Areas */\n"
"QWidget#pSetting QScrollArea {\n"
"    border: none;\n"
"    background: transparent;\n"
"}\n"
"\n"
"/* Settings Content Widgets - Fix White Background */\n"
"QWidget#pSetting QScrollArea QWidget {\n"
"    background-color: rgb(40, 40, 43);\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* Specific Content Widgets */\n"
"QWidget#swGeneral, QWidget#swDevice, QWidget#swCamera, \n"
"QWidget#swEditor, QWidget#swAdvanced, QWidget#swAuthority {\n"
"    background-color: rgb(40, 40, 43);\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* Settings Form Elements */\n"
"QWidget#pSetting QGroupBox {\n"
"    background-color: rgba(255, 255, 255, 0.05);\n"
"    bord"
                        "er: 1px solid rgba(255, 255, 255, 0.1);\n"
"    border-radius: 5px;\n"
"    margin-top: 10px;\n"
"    padding-top: 10px;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 5px 0 5px;\n"
"    color: rgb(255, 255, 255);\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QWidget#pSetting QLabel {\n"
"    color: rgb(255, 255, 255);\n"
"    background: transparent;\n"
"}\n"
"\n"
"QWidget#pSetting QLineEdit {\n"
"    background-color: rgb(60, 60, 65);\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    border-radius: 3px;\n"
"    padding: 5px;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QLineEdit:focus {\n"
"    border: 2px solid #007cd6;\n"
"}\n"
"\n"
"QWidget#pSetting QComboBox {\n"
"    background-color: rgb(60, 60, 65);\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    border-radius: 3px;\n"
"    padding: 5px;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QComboBox::drop"
                        "-down {\n"
"    border: none;\n"
"    background: rgb(80, 80, 85);\n"
"}\n"
"\n"
"QWidget#pSetting QComboBox::down-arrow {\n"
"    image: url(:/icon/Arrow Pointing Down_16px.png);\n"
"}\n"
"\n"
"QWidget#pSetting QComboBox QAbstractItemView {\n"
"    background-color: rgb(60, 60, 65);\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    selection-background-color: #007cd6;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QCheckBox {\n"
"    color: rgb(255, 255, 255);\n"
"    background: transparent;\n"
"}\n"
"\n"
"QWidget#pSetting QCheckBox::indicator {\n"
"    width: 16px;\n"
"    height: 16px;\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    border-radius: 2px;\n"
"    background-color: rgb(60, 60, 65);\n"
"}\n"
"\n"
"QWidget#pSetting QCheckBox::indicator:checked {\n"
"    background-color: #007cd6;\n"
"    border: 1px solid #007cd6;\n"
"}\n"
"\n"
"QWidget#pSetting QSpinBox {\n"
"    background-color: rgb(60, 60, 65);\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    border-radius: 3px;\n"
""
                        "    padding: 5px;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QSlider::groove:horizontal {\n"
"    border: 1px solid rgb(90, 90, 90);\n"
"    height: 8px;\n"
"    background: rgb(60, 60, 65);\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QWidget#pSetting QSlider::handle:horizontal {\n"
"    background: #007cd6;\n"
"    border: 1px solid #007cd6;\n"
"    width: 18px;\n"
"    border-radius: 9px;\n"
"    margin: -5px 0;\n"
"}\n"
"\n"
"QWidget#pSetting QSlider::sub-page:horizontal {\n"
"    background: #007cd6;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"/* Additional Dark Theme Fixes */\n"
"QWidget#pSetting QFrame {\n"
"    background-color: transparent;\n"
"    border: none;\n"
"}\n"
"\n"
"QWidget#pSetting QWidget {\n"
"    background-color: rgb(40, 40, 43);\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* Override for specific button groups */\n"
"QWidget#pSetting QFrame#frame_3 {\n"
"    background-color: rgba(255, 255, 255, 0.1);\n"
"    border-radius: 5px;\n"
"    padding: 5px;\n"
"}\n"
""
                        "\n"
"/* ===========================================\n"
"   OPERATOR PAGE STYLES\n"
"   =========================================== */\n"
"QWidget#lbOperatorTitile {\n"
"    padding: 50%;\n"
"}\n"
"\n"
"QWidget#wgOperatorDisplay {\n"
"    background-color: rgb(0, 170, 255);\n"
"}\n"
"\n"
"QWidget#gvOperatorViewer {\n"
"    background-color: rgb(238, 238, 238);\n"
"}\n"
"\n"
"/* Operator Control Buttons */\n"
"QPushButton#pbStartSystem {\n"
"    background-color: rgb(0, 255, 157);\n"
"    color: rgb(74, 74, 74);\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#pbStartSystem:hover {\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#pbStartSystem:pressed {\n"
"    background-color: rgb(0, 136, 255);\n"
"    border: 3px solid;\n"
"}\n"
"\n"
"QPushButton#pbStopSystem {\n"
"    background-color: rgb(255, 76, 76);\n"
"    color: rgb(74, 74, 74);\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#pbStopSystem:hover {\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton#pbStopSystem:pressed {\n"
"    "
                        "background-color: rgb(0, 136, 255);\n"
"    border: 3px solid;\n"
"}\n"
"\n"
"/* ===========================================\n"
"   HOME PAGE STYLES\n"
"   =========================================== */\n"
"QWidget#pHome QLabel:hover {\n"
"    color: rgb(0, 102, 255);\n"
"}\n"
"\n"
"/* ===========================================\n"
"   LOGGING SECTION\n"
"   =========================================== */\n"
"QTextEdit#teLoggingBox {\n"
"    color: #CDCDCD;\n"
"    border: none;\n"
"    background-color: #434347;\n"
"}\n"
"\n"
"/* ===========================================\n"
"   FINAL OVERRIDE FOR SETTINGS WHITE BACKGROUND\n"
"   =========================================== */\n"
"QWidget#pSetting * {\n"
"    background-color: rgb(40, 40, 43);\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"/* Keep button styles intact */\n"
"QWidget#pSetting QPushButton#pbResetSettings {\n"
"    background-color: #6C5C99;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbBackupSettings {\n"
" "
                        "   background-color: #4A7C59;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbRestoreSettings {\n"
"    background-color: #B8860B;\n"
"    color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QWidget#pSetting QPushButton#pbSaveSetting {\n"
"    background-color: #007ACC;\n"
"    color: rgb(255, 255, 255);\n"
"}"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setStyleSheet(QString::fromUtf8(""));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        page->setStyleSheet(QString::fromUtf8("#page\n"
"{	\n"
"	background-color: rgb(30, 30, 32);\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(page);
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        wgLeftPanel = new QWidget(page);
        wgLeftPanel->setObjectName(QString::fromUtf8("wgLeftPanel"));
        wgLeftPanel->setMinimumSize(QSize(80, 0));
        wgLeftPanel->setMaximumSize(QSize(80, 16777215));
        verticalLayout = new QVBoxLayout(wgLeftPanel);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        tbOpenProject = new QToolButton(wgLeftPanel);
        tbOpenProject->setObjectName(QString::fromUtf8("tbOpenProject"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tbOpenProject->sizePolicy().hasHeightForWidth());
        tbOpenProject->setSizePolicy(sizePolicy1);
        tbOpenProject->setMinimumSize(QSize(0, 30));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icons8_folder_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbOpenProject->setIcon(icon1);
        tbOpenProject->setIconSize(QSize(32, 32));
        tbOpenProject->setAutoRaise(true);

        verticalLayout->addWidget(tbOpenProject);

        tbSaveProject = new QToolButton(wgLeftPanel);
        tbSaveProject->setObjectName(QString::fromUtf8("tbSaveProject"));
        sizePolicy1.setHeightForWidth(tbSaveProject->sizePolicy().hasHeightForWidth());
        tbSaveProject->setSizePolicy(sizePolicy1);
        tbSaveProject->setMinimumSize(QSize(0, 30));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbSaveProject->setIcon(icon2);
        tbSaveProject->setIconSize(QSize(32, 32));
        tbSaveProject->setAutoRaise(true);

        verticalLayout->addWidget(tbSaveProject);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        tbHome = new QToolButton(wgLeftPanel);
        tbHome->setObjectName(QString::fromUtf8("tbHome"));
        sizePolicy1.setHeightForWidth(tbHome->sizePolicy().hasHeightForWidth());
        tbHome->setSizePolicy(sizePolicy1);
        tbHome->setMinimumSize(QSize(80, 0));
        tbHome->setStyleSheet(QString::fromUtf8(""));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/home_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbHome->setIcon(icon3);
        tbHome->setCheckable(false);
        tbHome->setChecked(false);
        tbHome->setPopupMode(QToolButton::DelayedPopup);
        tbHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbHome->setAutoRaise(false);

        verticalLayout->addWidget(tbHome);

        tbProject = new QToolButton(wgLeftPanel);
        tbProject->setObjectName(QString::fromUtf8("tbProject"));
        sizePolicy1.setHeightForWidth(tbProject->sizePolicy().hasHeightForWidth());
        tbProject->setSizePolicy(sizePolicy1);
        tbProject->setMinimumSize(QSize(80, 0));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/project_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbProject->setIcon(icon4);
        tbProject->setCheckable(false);
        tbProject->setChecked(false);
        tbProject->setPopupMode(QToolButton::DelayedPopup);
        tbProject->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbProject->setAutoRaise(false);

        verticalLayout->addWidget(tbProject);

        tbVariable = new QToolButton(wgLeftPanel);
        tbVariable->setObjectName(QString::fromUtf8("tbVariable"));
        sizePolicy1.setHeightForWidth(tbVariable->sizePolicy().hasHeightForWidth());
        tbVariable->setSizePolicy(sizePolicy1);
        tbVariable->setMinimumSize(QSize(80, 0));
        tbVariable->setStyleSheet(QString::fromUtf8(""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/variable_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbVariable->setIcon(icon5);
        tbVariable->setPopupMode(QToolButton::DelayedPopup);
        tbVariable->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbVariable->setAutoRaise(false);

        verticalLayout->addWidget(tbVariable);

        tbMarket = new QToolButton(wgLeftPanel);
        tbMarket->setObjectName(QString::fromUtf8("tbMarket"));
        sizePolicy1.setHeightForWidth(tbMarket->sizePolicy().hasHeightForWidth());
        tbMarket->setSizePolicy(sizePolicy1);
        tbMarket->setMinimumSize(QSize(80, 0));
        tbMarket->setStyleSheet(QString::fromUtf8(""));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/shopping_cart_promotion_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMarket->setIcon(icon6);
        tbMarket->setPopupMode(QToolButton::DelayedPopup);
        tbMarket->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbMarket->setAutoRaise(false);

        verticalLayout->addWidget(tbMarket);

        tbDocument = new QToolButton(wgLeftPanel);
        tbDocument->setObjectName(QString::fromUtf8("tbDocument"));
        sizePolicy1.setHeightForWidth(tbDocument->sizePolicy().hasHeightForWidth());
        tbDocument->setSizePolicy(sizePolicy1);
        tbDocument->setMinimumSize(QSize(80, 0));
        tbDocument->setStyleSheet(QString::fromUtf8(""));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/document_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbDocument->setIcon(icon7);
        tbDocument->setPopupMode(QToolButton::DelayedPopup);
        tbDocument->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbDocument->setAutoRaise(false);

        verticalLayout->addWidget(tbDocument);

        tbCommunity = new QToolButton(wgLeftPanel);
        tbCommunity->setObjectName(QString::fromUtf8("tbCommunity"));
        sizePolicy1.setHeightForWidth(tbCommunity->sizePolicy().hasHeightForWidth());
        tbCommunity->setSizePolicy(sizePolicy1);
        tbCommunity->setMinimumSize(QSize(80, 0));
        tbCommunity->setStyleSheet(QString::fromUtf8(""));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/charity_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbCommunity->setIcon(icon8);
        tbCommunity->setPopupMode(QToolButton::DelayedPopup);
        tbCommunity->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbCommunity->setAutoRaise(false);

        verticalLayout->addWidget(tbCommunity);

        tbAuthority = new QToolButton(wgLeftPanel);
        tbAuthority->setObjectName(QString::fromUtf8("tbAuthority"));
        sizePolicy1.setHeightForWidth(tbAuthority->sizePolicy().hasHeightForWidth());
        tbAuthority->setSizePolicy(sizePolicy1);
        tbAuthority->setMinimumSize(QSize(80, 0));
        tbAuthority->setStyleSheet(QString::fromUtf8(""));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icon/account_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbAuthority->setIcon(icon9);
        tbAuthority->setPopupMode(QToolButton::DelayedPopup);
        tbAuthority->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbAuthority->setAutoRaise(false);

        verticalLayout->addWidget(tbAuthority);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        tbSetting = new QToolButton(wgLeftPanel);
        tbSetting->setObjectName(QString::fromUtf8("tbSetting"));
        sizePolicy1.setHeightForWidth(tbSetting->sizePolicy().hasHeightForWidth());
        tbSetting->setSizePolicy(sizePolicy1);
        tbSetting->setMinimumSize(QSize(80, 0));
        tbSetting->setStyleSheet(QString::fromUtf8(""));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icon/settings_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbSetting->setIcon(icon10);
        tbSetting->setPopupMode(QToolButton::DelayedPopup);
        tbSetting->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbSetting->setAutoRaise(false);

        verticalLayout->addWidget(tbSetting);


        horizontalLayout_2->addWidget(wgLeftPanel);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        swPageStack = new QStackedWidget(page);
        swPageStack->setObjectName(QString::fromUtf8("swPageStack"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Ignored);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(swPageStack->sizePolicy().hasHeightForWidth());
        swPageStack->setSizePolicy(sizePolicy2);
        swPageStack->setMaximumSize(QSize(16777215, 16777215));
        swPageStack->setStyleSheet(QString::fromUtf8(""));
        swPageStack->setLineWidth(1);
        pVariable = new QWidget();
        pVariable->setObjectName(QString::fromUtf8("pVariable"));
        verticalLayout_4 = new QVBoxLayout(pVariable);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        fVar = new QFrame(pVariable);
        fVar->setObjectName(QString::fromUtf8("fVar"));
        fVar->setMinimumSize(QSize(0, 25));
        fVar->setFrameShape(QFrame::StyledPanel);
        fVar->setFrameShadow(QFrame::Raised);
        horizontalLayout_14 = new QHBoxLayout(fVar);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        label_12 = new QLabel(fVar);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_14->addWidget(label_12);

        leUpdateKey = new QLineEdit(fVar);
        leUpdateKey->setObjectName(QString::fromUtf8("leUpdateKey"));

        horizontalLayout_14->addWidget(leUpdateKey);

        label_13 = new QLabel(fVar);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        horizontalLayout_14->addWidget(label_13);

        leUpdateValue = new QLineEdit(fVar);
        leUpdateValue->setObjectName(QString::fromUtf8("leUpdateValue"));

        horizontalLayout_14->addWidget(leUpdateValue);

        pbUpdateVarDisplay = new QPushButton(fVar);
        pbUpdateVarDisplay->setObjectName(QString::fromUtf8("pbUpdateVarDisplay"));

        horizontalLayout_14->addWidget(pbUpdateVarDisplay);

        pbDeleteSelectedVar = new QPushButton(fVar);
        pbDeleteSelectedVar->setObjectName(QString::fromUtf8("pbDeleteSelectedVar"));

        horizontalLayout_14->addWidget(pbDeleteSelectedVar);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_7);


        verticalLayout_4->addWidget(fVar);

        tvVariables = new QTreeView(pVariable);
        tvVariables->setObjectName(QString::fromUtf8("tvVariables"));

        verticalLayout_4->addWidget(tvVariables);

        swPageStack->addWidget(pVariable);
        pOperator = new QWidget();
        pOperator->setObjectName(QString::fromUtf8("pOperator"));
        verticalLayout_8 = new QVBoxLayout(pOperator);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        label_21 = new QLabel(pOperator);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(true);
        label_21->setFont(font1);

        verticalLayout_8->addWidget(label_21);

        scrollArea_2 = new QScrollArea(pOperator);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 662, 297));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        lbOperatorTitile = new QLabel(scrollAreaWidgetContents_2);
        lbOperatorTitile->setObjectName(QString::fromUtf8("lbOperatorTitile"));
        QFont font2;
        font2.setPointSize(20);
        font2.setBold(true);
        lbOperatorTitile->setFont(font2);
        lbOperatorTitile->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(lbOperatorTitile);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        frame_2 = new QFrame(scrollAreaWidgetContents_2);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 100));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_2);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        frame = new QFrame(frame_2);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 100));
        frame->setMaximumSize(QSize(200, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_9 = new QVBoxLayout(frame);
        verticalLayout_9->setSpacing(50);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        pbStartSystem = new QPushButton(frame);
        pbStartSystem->setObjectName(QString::fromUtf8("pbStartSystem"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(pbStartSystem->sizePolicy().hasHeightForWidth());
        pbStartSystem->setSizePolicy(sizePolicy3);
        pbStartSystem->setMaximumSize(QSize(200, 100));
        pbStartSystem->setFont(font2);

        verticalLayout_9->addWidget(pbStartSystem);

        pbStopSystem = new QPushButton(frame);
        pbStopSystem->setObjectName(QString::fromUtf8("pbStopSystem"));
        sizePolicy3.setHeightForWidth(pbStopSystem->sizePolicy().hasHeightForWidth());
        pbStopSystem->setSizePolicy(sizePolicy3);
        pbStopSystem->setMaximumSize(QSize(200, 100));
        pbStopSystem->setFont(font2);

        verticalLayout_9->addWidget(pbStopSystem);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_4);

        fOperatorRobotOnOffPanel = new QFrame(frame);
        fOperatorRobotOnOffPanel->setObjectName(QString::fromUtf8("fOperatorRobotOnOffPanel"));
        fOperatorRobotOnOffPanel->setMinimumSize(QSize(0, 100));
        fOperatorRobotOnOffPanel->setFrameShape(QFrame::StyledPanel);
        fOperatorRobotOnOffPanel->setFrameShadow(QFrame::Raised);
        layoutOperatorRobotOnOff = new QGridLayout(fOperatorRobotOnOffPanel);
        layoutOperatorRobotOnOff->setSpacing(6);
        layoutOperatorRobotOnOff->setContentsMargins(11, 11, 11, 11);
        layoutOperatorRobotOnOff->setObjectName(QString::fromUtf8("layoutOperatorRobotOnOff"));

        verticalLayout_9->addWidget(fOperatorRobotOnOffPanel);


        horizontalLayout_9->addWidget(frame);

        wgOperatorDisplay = new QWidget(frame_2);
        wgOperatorDisplay->setObjectName(QString::fromUtf8("wgOperatorDisplay"));
        wgOperatorDisplay->setMinimumSize(QSize(400, 400));
        horizontalLayout_11 = new QHBoxLayout(wgOperatorDisplay);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        gvOperatorViewer = new QGraphicsView(wgOperatorDisplay);
        gvOperatorViewer->setObjectName(QString::fromUtf8("gvOperatorViewer"));
        sizePolicy.setHeightForWidth(gvOperatorViewer->sizePolicy().hasHeightForWidth());
        gvOperatorViewer->setSizePolicy(sizePolicy);

        horizontalLayout_11->addWidget(gvOperatorViewer);


        horizontalLayout_9->addWidget(wgOperatorDisplay);

        twOperatorParameter = new QTreeWidget(frame_2);
        twOperatorParameter->setObjectName(QString::fromUtf8("twOperatorParameter"));
        twOperatorParameter->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_9->addWidget(twOperatorParameter);

        pbOperatorResetParameter = new QPushButton(frame_2);
        pbOperatorResetParameter->setObjectName(QString::fromUtf8("pbOperatorResetParameter"));
        pbOperatorResetParameter->setMaximumSize(QSize(50, 16777215));
        pbOperatorResetParameter->setLayoutDirection(Qt::LeftToRight);
        pbOperatorResetParameter->setFlat(false);

        horizontalLayout_9->addWidget(pbOperatorResetParameter);


        horizontalLayout_8->addWidget(frame_2);


        verticalLayout_10->addLayout(horizontalLayout_8);

        pbSwitchProgramer = new QPushButton(scrollAreaWidgetContents_2);
        pbSwitchProgramer->setObjectName(QString::fromUtf8("pbSwitchProgramer"));
        sizePolicy.setHeightForWidth(pbSwitchProgramer->sizePolicy().hasHeightForWidth());
        pbSwitchProgramer->setSizePolicy(sizePolicy);
        pbSwitchProgramer->setMaximumSize(QSize(200, 50));
        pbSwitchProgramer->setFont(font1);

        verticalLayout_10->addWidget(pbSwitchProgramer);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_8->addWidget(scrollArea_2);

        swPageStack->addWidget(pOperator);
        pHome = new QWidget();
        pHome->setObjectName(QString::fromUtf8("pHome"));
        pHome->setMaximumSize(QSize(16777215, 16777215));
        pHome->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(pHome);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_4 = new QGroupBox(pHome);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        QFont font3;
        font3.setBold(true);
        groupBox_4->setFont(font3);
        gridLayout_3 = new QGridLayout(groupBox_4);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 1, 0, 1, 1);

        label = new QLabel(groupBox_4);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 2, 0, 1, 1);

        label_5 = new QLabel(groupBox_4);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_3->addWidget(label_5, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox_4);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_3->addWidget(label_6, 2, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox_4);

        groupBox = new QGroupBox(pHome);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setFont(font3);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(pushButton_2, 0, 1, 1, 1);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(pushButton_3, 1, 0, 1, 1);

        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(pushButton_4, 1, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox);

        groupBox_2 = new QGroupBox(pHome);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font3);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pushButton_6, 0, 0, 1, 1);

        pushButton_8 = new QPushButton(groupBox_2);
        pushButton_8->setObjectName(QString::fromUtf8("pushButton_8"));
        pushButton_8->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pushButton_8, 1, 0, 1, 1);

        pushButton_7 = new QPushButton(groupBox_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pushButton_7, 0, 1, 1, 1);

        pushButton_9 = new QPushButton(groupBox_2);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));
        pushButton_9->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pushButton_9, 1, 1, 1, 1);


        verticalLayout_3->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(pHome);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font3);
        horizontalLayout_3 = new QHBoxLayout(groupBox_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        plainTextEdit = new QPlainTextEdit(groupBox_3);
        plainTextEdit->setObjectName(QString::fromUtf8("plainTextEdit"));
        plainTextEdit->setMaximumSize(QSize(16777215, 70));

        horizontalLayout_3->addWidget(plainTextEdit);

        pushButton_5 = new QPushButton(groupBox_3);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

        horizontalLayout_3->addWidget(pushButton_5);


        verticalLayout_3->addWidget(groupBox_3);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        swPageStack->addWidget(pHome);
        pMarket = new QWidget();
        pMarket->setObjectName(QString::fromUtf8("pMarket"));
        swPageStack->addWidget(pMarket);
        pDocument = new QWidget();
        pDocument->setObjectName(QString::fromUtf8("pDocument"));
        swPageStack->addWidget(pDocument);
        pAuthority = new QWidget();
        pAuthority->setObjectName(QString::fromUtf8("pAuthority"));
        pAuthority->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_5 = new QVBoxLayout(pAuthority);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        swAuthority = new QStackedWidget(pAuthority);
        swAuthority->setObjectName(QString::fromUtf8("swAuthority"));
        pProgramer = new QWidget();
        pProgramer->setObjectName(QString::fromUtf8("pProgramer"));
        verticalLayout_6 = new QVBoxLayout(pProgramer);
        verticalLayout_6->setSpacing(0);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        scrollArea = new QScrollArea(pProgramer);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy4);
        scrollArea->setMinimumSize(QSize(0, 600));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 593, 700));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 700));
        verticalLayout_7 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_7 = new QLabel(scrollAreaWidgetContents);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font2);

        verticalLayout_7->addWidget(label_7);

        groupBox_5 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy5);
        groupBox_5->setMinimumSize(QSize(0, 0));
        QFont font4;
        font4.setBold(false);
        groupBox_5->setFont(font4);
        gridLayout_4 = new QGridLayout(groupBox_5);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        lwOperatorDisplayVariable = new QListWidget(groupBox_5);
        lwOperatorDisplayVariable->setObjectName(QString::fromUtf8("lwOperatorDisplayVariable"));
        sizePolicy.setHeightForWidth(lwOperatorDisplayVariable->sizePolicy().hasHeightForWidth());
        lwOperatorDisplayVariable->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lwOperatorDisplayVariable, 6, 0, 1, 1);

        pbApplyOperator = new QPushButton(groupBox_5);
        pbApplyOperator->setObjectName(QString::fromUtf8("pbApplyOperator"));
        pbApplyOperator->setFont(font1);

        gridLayout_4->addWidget(pbApplyOperator, 8, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_9 = new QLabel(groupBox_5);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(100, 0));

        horizontalLayout_5->addWidget(label_9);

        pbAddOperatorDisplayWidget = new QPushButton(groupBox_5);
        pbAddOperatorDisplayWidget->setObjectName(QString::fromUtf8("pbAddOperatorDisplayWidget"));

        horizontalLayout_5->addWidget(pbAddOperatorDisplayWidget);

        cbOperatorRobotDisplay = new QComboBox(groupBox_5);
        cbOperatorRobotDisplay->setObjectName(QString::fromUtf8("cbOperatorRobotDisplay"));

        horizontalLayout_5->addWidget(cbOperatorRobotDisplay);

        cbOperatorDisplayWidget = new QComboBox(groupBox_5);
        cbOperatorDisplayWidget->addItem(QString());
        cbOperatorDisplayWidget->setObjectName(QString::fromUtf8("cbOperatorDisplayWidget"));
        cbOperatorDisplayWidget->setMinimumSize(QSize(150, 0));

        horizontalLayout_5->addWidget(cbOperatorDisplayWidget);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        gridLayout_4->addLayout(horizontalLayout_5, 3, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_3, 4, 2, 1, 1);

        lwOperatorDisplayWidget = new QListWidget(groupBox_5);
        lwOperatorDisplayWidget->setObjectName(QString::fromUtf8("lwOperatorDisplayWidget"));
        sizePolicy.setHeightForWidth(lwOperatorDisplayWidget->sizePolicy().hasHeightForWidth());
        lwOperatorDisplayWidget->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lwOperatorDisplayWidget, 4, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(100, 0));

        horizontalLayout_4->addWidget(label_8);

        cbOperatorProject = new QComboBox(groupBox_5);
        cbOperatorProject->setObjectName(QString::fromUtf8("cbOperatorProject"));

        horizontalLayout_4->addWidget(cbOperatorProject);

        label_16 = new QLabel(groupBox_5);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        horizontalLayout_4->addWidget(label_16);

        leOperatorTitle = new QLineEdit(groupBox_5);
        leOperatorTitle->setObjectName(QString::fromUtf8("leOperatorTitle"));
        leOperatorTitle->setMinimumSize(QSize(200, 0));
        leOperatorTitle->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_4->addWidget(leOperatorTitle);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        gridLayout_4->addLayout(horizontalLayout_4, 0, 0, 1, 2);

        pbDeleteOperatorVar = new QPushButton(groupBox_5);
        pbDeleteOperatorVar->setObjectName(QString::fromUtf8("pbDeleteOperatorVar"));
        pbDeleteOperatorVar->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(pbDeleteOperatorVar, 6, 1, 1, 1);

        lwOperatorRobotGcodeProgram = new QListWidget(groupBox_5);
        lwOperatorRobotGcodeProgram->setObjectName(QString::fromUtf8("lwOperatorRobotGcodeProgram"));
        sizePolicy.setHeightForWidth(lwOperatorRobotGcodeProgram->sizePolicy().hasHeightForWidth());
        lwOperatorRobotGcodeProgram->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(lwOperatorRobotGcodeProgram, 2, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pbAddVarToOperatorDisplay = new QPushButton(groupBox_5);
        pbAddVarToOperatorDisplay->setObjectName(QString::fromUtf8("pbAddVarToOperatorDisplay"));

        horizontalLayout_6->addWidget(pbAddVarToOperatorDisplay);

        label_10 = new QLabel(groupBox_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(label_10);

        leOperatorVar = new QLineEdit(groupBox_5);
        leOperatorVar->setObjectName(QString::fromUtf8("leOperatorVar"));
        leOperatorVar->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(leOperatorVar);

        label_14 = new QLabel(groupBox_5);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_6->addWidget(label_14);

        leOperatorVarName = new QLineEdit(groupBox_5);
        leOperatorVarName->setObjectName(QString::fromUtf8("leOperatorVarName"));
        leOperatorVarName->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_6->addWidget(leOperatorVarName);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);


        gridLayout_4->addLayout(horizontalLayout_6, 5, 0, 1, 2);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label_15 = new QLabel(groupBox_5);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        horizontalLayout_7->addWidget(label_15);

        leAuthorityPassword = new QLineEdit(groupBox_5);
        leAuthorityPassword->setObjectName(QString::fromUtf8("leAuthorityPassword"));
        leAuthorityPassword->setFrame(true);
        leAuthorityPassword->setEchoMode(QLineEdit::Password);
        leAuthorityPassword->setCursorMoveStyle(Qt::LogicalMoveStyle);
        leAuthorityPassword->setClearButtonEnabled(false);

        horizontalLayout_7->addWidget(leAuthorityPassword);


        gridLayout_4->addLayout(horizontalLayout_7, 7, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_11 = new QLabel(groupBox_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMinimumSize(QSize(100, 0));

        horizontalLayout_12->addWidget(label_11);

        pbAddOperatorGcodeProgram = new QPushButton(groupBox_5);
        pbAddOperatorGcodeProgram->setObjectName(QString::fromUtf8("pbAddOperatorGcodeProgram"));

        horizontalLayout_12->addWidget(pbAddOperatorGcodeProgram);

        cbOperatorRobot = new QComboBox(groupBox_5);
        cbOperatorRobot->setObjectName(QString::fromUtf8("cbOperatorRobot"));

        horizontalLayout_12->addWidget(cbOperatorRobot);

        cbOperatorGcodeProgram = new QComboBox(groupBox_5);
        cbOperatorGcodeProgram->setObjectName(QString::fromUtf8("cbOperatorGcodeProgram"));
        cbOperatorGcodeProgram->setMinimumSize(QSize(150, 0));

        horizontalLayout_12->addWidget(cbOperatorGcodeProgram);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_6);


        gridLayout_4->addLayout(horizontalLayout_12, 1, 0, 1, 1);

        pbDeleteOperatorDisplayWidget = new QPushButton(groupBox_5);
        pbDeleteOperatorDisplayWidget->setObjectName(QString::fromUtf8("pbDeleteOperatorDisplayWidget"));
        pbDeleteOperatorDisplayWidget->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(pbDeleteOperatorDisplayWidget, 4, 1, 1, 1);

        pbDeleteOperatorGcodeProgram = new QPushButton(groupBox_5);
        pbDeleteOperatorGcodeProgram->setObjectName(QString::fromUtf8("pbDeleteOperatorGcodeProgram"));
        pbDeleteOperatorGcodeProgram->setMaximumSize(QSize(50, 16777215));

        gridLayout_4->addWidget(pbDeleteOperatorGcodeProgram, 2, 1, 1, 1);


        verticalLayout_7->addWidget(groupBox_5);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_6->addWidget(scrollArea);

        swAuthority->addWidget(pProgramer);

        verticalLayout_5->addWidget(swAuthority);

        swPageStack->addWidget(pAuthority);
        pCommunity = new QWidget();
        pCommunity->setObjectName(QString::fromUtf8("pCommunity"));
        swPageStack->addWidget(pCommunity);
        pSetting = new QWidget();
        pSetting->setObjectName(QString::fromUtf8("pSetting"));
        verticalLayout_12 = new QVBoxLayout(pSetting);
        verticalLayout_12->setSpacing(5);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(10, 10, 10, 10);
        lbSettingsTitle = new QLabel(pSetting);
        lbSettingsTitle->setObjectName(QString::fromUtf8("lbSettingsTitle"));
        QFont font5;
        font5.setPointSize(16);
        font5.setBold(true);
        lbSettingsTitle->setFont(font5);

        verticalLayout_12->addWidget(lbSettingsTitle);

        frame_3 = new QFrame(pSetting);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setMinimumSize(QSize(0, 50));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(frame_3);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        pbResetSettings = new QPushButton(frame_3);
        pbResetSettings->setObjectName(QString::fromUtf8("pbResetSettings"));
        pbResetSettings->setMinimumSize(QSize(100, 30));

        horizontalLayout_13->addWidget(pbResetSettings);

        pbBackupSettings = new QPushButton(frame_3);
        pbBackupSettings->setObjectName(QString::fromUtf8("pbBackupSettings"));
        pbBackupSettings->setMinimumSize(QSize(100, 30));

        horizontalLayout_13->addWidget(pbBackupSettings);

        pbRestoreSettings = new QPushButton(frame_3);
        pbRestoreSettings->setObjectName(QString::fromUtf8("pbRestoreSettings"));
        pbRestoreSettings->setMinimumSize(QSize(100, 30));

        horizontalLayout_13->addWidget(pbRestoreSettings);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer);

        pbSaveSetting = new QPushButton(frame_3);
        pbSaveSetting->setObjectName(QString::fromUtf8("pbSaveSetting"));
        pbSaveSetting->setMinimumSize(QSize(120, 30));

        horizontalLayout_13->addWidget(pbSaveSetting);


        verticalLayout_12->addWidget(frame_3);

        twSettingsCategories = new QTabWidget(pSetting);
        twSettingsCategories->setObjectName(QString::fromUtf8("twSettingsCategories"));
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));
        vlGeneral = new QVBoxLayout(tabGeneral);
        vlGeneral->setSpacing(6);
        vlGeneral->setContentsMargins(11, 11, 11, 11);
        vlGeneral->setObjectName(QString::fromUtf8("vlGeneral"));
        saGeneral = new QScrollArea(tabGeneral);
        saGeneral->setObjectName(QString::fromUtf8("saGeneral"));
        saGeneral->setWidgetResizable(true);
        swGeneral = new QWidget();
        swGeneral->setObjectName(QString::fromUtf8("swGeneral"));
        swGeneral->setGeometry(QRect(0, 0, 65, 18));
        vlGeneralContent = new QVBoxLayout(swGeneral);
        vlGeneralContent->setSpacing(6);
        vlGeneralContent->setContentsMargins(11, 11, 11, 11);
        vlGeneralContent->setObjectName(QString::fromUtf8("vlGeneralContent"));
        saGeneral->setWidget(swGeneral);

        vlGeneral->addWidget(saGeneral);

        twSettingsCategories->addTab(tabGeneral, QString());
        tabDevice = new QWidget();
        tabDevice->setObjectName(QString::fromUtf8("tabDevice"));
        vlDevice = new QVBoxLayout(tabDevice);
        vlDevice->setSpacing(6);
        vlDevice->setContentsMargins(11, 11, 11, 11);
        vlDevice->setObjectName(QString::fromUtf8("vlDevice"));
        saDevice = new QScrollArea(tabDevice);
        saDevice->setObjectName(QString::fromUtf8("saDevice"));
        saDevice->setWidgetResizable(true);
        swDevice = new QWidget();
        swDevice->setObjectName(QString::fromUtf8("swDevice"));
        swDevice->setGeometry(QRect(0, 0, 65, 18));
        vlDeviceContent = new QVBoxLayout(swDevice);
        vlDeviceContent->setSpacing(6);
        vlDeviceContent->setContentsMargins(11, 11, 11, 11);
        vlDeviceContent->setObjectName(QString::fromUtf8("vlDeviceContent"));
        saDevice->setWidget(swDevice);

        vlDevice->addWidget(saDevice);

        twSettingsCategories->addTab(tabDevice, QString());
        tabCamera = new QWidget();
        tabCamera->setObjectName(QString::fromUtf8("tabCamera"));
        vlCamera = new QVBoxLayout(tabCamera);
        vlCamera->setSpacing(6);
        vlCamera->setContentsMargins(11, 11, 11, 11);
        vlCamera->setObjectName(QString::fromUtf8("vlCamera"));
        saCamera = new QScrollArea(tabCamera);
        saCamera->setObjectName(QString::fromUtf8("saCamera"));
        saCamera->setWidgetResizable(true);
        swCamera = new QWidget();
        swCamera->setObjectName(QString::fromUtf8("swCamera"));
        swCamera->setGeometry(QRect(0, 0, 65, 18));
        vlCameraContent = new QVBoxLayout(swCamera);
        vlCameraContent->setSpacing(6);
        vlCameraContent->setContentsMargins(11, 11, 11, 11);
        vlCameraContent->setObjectName(QString::fromUtf8("vlCameraContent"));
        saCamera->setWidget(swCamera);

        vlCamera->addWidget(saCamera);

        twSettingsCategories->addTab(tabCamera, QString());
        tabEditor = new QWidget();
        tabEditor->setObjectName(QString::fromUtf8("tabEditor"));
        vlEditor = new QVBoxLayout(tabEditor);
        vlEditor->setSpacing(6);
        vlEditor->setContentsMargins(11, 11, 11, 11);
        vlEditor->setObjectName(QString::fromUtf8("vlEditor"));
        saEditor = new QScrollArea(tabEditor);
        saEditor->setObjectName(QString::fromUtf8("saEditor"));
        saEditor->setWidgetResizable(true);
        swEditor = new QWidget();
        swEditor->setObjectName(QString::fromUtf8("swEditor"));
        swEditor->setGeometry(QRect(0, 0, 65, 18));
        vlEditorContent = new QVBoxLayout(swEditor);
        vlEditorContent->setSpacing(6);
        vlEditorContent->setContentsMargins(11, 11, 11, 11);
        vlEditorContent->setObjectName(QString::fromUtf8("vlEditorContent"));
        saEditor->setWidget(swEditor);

        vlEditor->addWidget(saEditor);

        twSettingsCategories->addTab(tabEditor, QString());
        tabAdvanced = new QWidget();
        tabAdvanced->setObjectName(QString::fromUtf8("tabAdvanced"));
        vlAdvanced = new QVBoxLayout(tabAdvanced);
        vlAdvanced->setSpacing(6);
        vlAdvanced->setContentsMargins(11, 11, 11, 11);
        vlAdvanced->setObjectName(QString::fromUtf8("vlAdvanced"));
        saAdvanced = new QScrollArea(tabAdvanced);
        saAdvanced->setObjectName(QString::fromUtf8("saAdvanced"));
        saAdvanced->setWidgetResizable(true);
        swAdvanced = new QWidget();
        swAdvanced->setObjectName(QString::fromUtf8("swAdvanced"));
        swAdvanced->setGeometry(QRect(0, 0, 1073, 462));
        vlAdvancedContent = new QVBoxLayout(swAdvanced);
        vlAdvancedContent->setSpacing(6);
        vlAdvancedContent->setContentsMargins(11, 11, 11, 11);
        vlAdvancedContent->setObjectName(QString::fromUtf8("vlAdvancedContent"));
        saAdvanced->setWidget(swAdvanced);

        vlAdvanced->addWidget(saAdvanced);

        twSettingsCategories->addTab(tabAdvanced, QString());
        tabAuthority = new QWidget();
        tabAuthority->setObjectName(QString::fromUtf8("tabAuthority"));
        vlAuthority = new QVBoxLayout(tabAuthority);
        vlAuthority->setSpacing(6);
        vlAuthority->setContentsMargins(11, 11, 11, 11);
        vlAuthority->setObjectName(QString::fromUtf8("vlAuthority"));
        saAuthority = new QScrollArea(tabAuthority);
        saAuthority->setObjectName(QString::fromUtf8("saAuthority"));
        saAuthority->setWidgetResizable(true);
        swAuthority1 = new QWidget();
        swAuthority1->setObjectName(QString::fromUtf8("swAuthority1"));
        swAuthority1->setGeometry(QRect(0, 0, 65, 18));
        vlAuthorityContent = new QVBoxLayout(swAuthority1);
        vlAuthorityContent->setSpacing(6);
        vlAuthorityContent->setContentsMargins(11, 11, 11, 11);
        vlAuthorityContent->setObjectName(QString::fromUtf8("vlAuthorityContent"));
        saAuthority->setWidget(swAuthority1);

        vlAuthority->addWidget(saAuthority);

        twSettingsCategories->addTab(tabAuthority, QString());

        verticalLayout_12->addWidget(twSettingsCategories);

        swPageStack->addWidget(pSetting);
        pProject = new QWidget();
        pProject->setObjectName(QString::fromUtf8("pProject"));
        verticalLayout_2 = new QVBoxLayout(pProject);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        twProjectManager = new QTabWidget(pProject);
        twProjectManager->setObjectName(QString::fromUtf8("twProjectManager"));
        twProjectManager->setEnabled(true);
        twProjectManager->setMinimumSize(QSize(0, 0));
        twProjectManager->setMaximumSize(QSize(16777215, 16777215));
        QFont font6;
        font6.setPointSize(12);
        font6.setBold(false);
        font6.setKerning(true);
        twProjectManager->setFont(font6);
        twProjectManager->setStyleSheet(QString::fromUtf8(""));
        twProjectManager->setIconSize(QSize(32, 32));
        twProjectManager->setElideMode(Qt::ElideNone);
        twProjectManager->setTabsClosable(true);
        twProjectManager->setMovable(false);
        tabAddNewButton = new QWidget();
        tabAddNewButton->setObjectName(QString::fromUtf8("tabAddNewButton"));
        tabAddNewButton->setStyleSheet(QString::fromUtf8(""));
        twProjectManager->addTab(tabAddNewButton, QString());

        verticalLayout_2->addWidget(twProjectManager);

        swPageStack->addWidget(pProject);

        verticalLayout_11->addWidget(swPageStack);

        fFileMenu = new QFrame(page);
        fFileMenu->setObjectName(QString::fromUtf8("fFileMenu"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(fFileMenu->sizePolicy().hasHeightForWidth());
        fFileMenu->setSizePolicy(sizePolicy6);
        fFileMenu->setMinimumSize(QSize(0, 40));
        fFileMenu->setStyleSheet(QString::fromUtf8(""));
        fFileMenu->setFrameShape(QFrame::StyledPanel);
        fFileMenu->setFrameShadow(QFrame::Raised);
        horizontalLayout_10 = new QHBoxLayout(fFileMenu);
        horizontalLayout_10->setSpacing(5);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        teLoggingBox = new QTextEdit(fFileMenu);
        teLoggingBox->setObjectName(QString::fromUtf8("teLoggingBox"));
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Ignored);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(teLoggingBox->sizePolicy().hasHeightForWidth());
        teLoggingBox->setSizePolicy(sizePolicy7);
        teLoggingBox->setMinimumSize(QSize(0, 0));
        teLoggingBox->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_10->addWidget(teLoggingBox);

        tbExpandLoggingBox = new QToolButton(fFileMenu);
        tbExpandLoggingBox->setObjectName(QString::fromUtf8("tbExpandLoggingBox"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icon/Collapse Arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbExpandLoggingBox->setIcon(icon11);
        tbExpandLoggingBox->setCheckable(true);
        tbExpandLoggingBox->setAutoRaise(true);

        horizontalLayout_10->addWidget(tbExpandLoggingBox);


        verticalLayout_11->addWidget(fFileMenu);


        horizontalLayout_2->addLayout(verticalLayout_11);

        stackedWidget->addWidget(page);
        pFullTabDisplay = new QWidget();
        pFullTabDisplay->setObjectName(QString::fromUtf8("pFullTabDisplay"));
        layoutFullTabDisplay = new QVBoxLayout(pFullTabDisplay);
        layoutFullTabDisplay->setSpacing(0);
        layoutFullTabDisplay->setContentsMargins(11, 11, 11, 11);
        layoutFullTabDisplay->setObjectName(QString::fromUtf8("layoutFullTabDisplay"));
        layoutFullTabDisplay->setContentsMargins(0, 0, 0, 0);
        stackedWidget->addWidget(pFullTabDisplay);

        horizontalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        swPageStack->setCurrentIndex(0);
        swAuthority->setCurrentIndex(0);
        twSettingsCategories->setCurrentIndex(4);
        twProjectManager->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Delta X Software - Version 1.2.7", nullptr));
        actionAdd->setText(QCoreApplication::translate("MainWindow", "Add New", nullptr));
        actionRemove->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
        actionGcode->setText(QCoreApplication::translate("MainWindow", "Gcode", nullptr));
        actionSoftware->setText(QCoreApplication::translate("MainWindow", "Software", nullptr));
        actionExecute_All->setText(QCoreApplication::translate("MainWindow", "Execute All", nullptr));
        actionDelta_X_1->setText(QCoreApplication::translate("MainWindow", "Delta X 1", nullptr));
        actionExecute->setText(QCoreApplication::translate("MainWindow", "Execute", nullptr));
        actionBaudrate->setText(QCoreApplication::translate("MainWindow", "Baudrate", nullptr));
        actionScale->setText(QCoreApplication::translate("MainWindow", "Scale", nullptr));
        actionG_code_Program->setText(QCoreApplication::translate("MainWindow", "G-code Program", nullptr));
        actionRobot->setText(QCoreApplication::translate("MainWindow", "Robot", nullptr));
        actionProject->setText(QCoreApplication::translate("MainWindow", "Project", nullptr));
        actionG_code_Program_2->setText(QCoreApplication::translate("MainWindow", "G-code Program", nullptr));
        actionRobot_2->setText(QCoreApplication::translate("MainWindow", "Robot", nullptr));
        actionProject_2->setText(QCoreApplication::translate("MainWindow", "Project", nullptr));
        actionNew->setText(QCoreApplication::translate("MainWindow", "New", nullptr));
        tbOpenProject->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        tbSaveProject->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        tbHome->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
        tbProject->setText(QCoreApplication::translate("MainWindow", "Project", nullptr));
        tbVariable->setText(QCoreApplication::translate("MainWindow", "Variable", nullptr));
        tbMarket->setText(QCoreApplication::translate("MainWindow", "Market", nullptr));
        tbDocument->setText(QCoreApplication::translate("MainWindow", "Document", nullptr));
        tbCommunity->setText(QCoreApplication::translate("MainWindow", "Community", nullptr));
        tbAuthority->setText(QCoreApplication::translate("MainWindow", "Admin", nullptr));
        tbSetting->setText(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Key", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Value", nullptr));
        pbUpdateVarDisplay->setText(QCoreApplication::translate("MainWindow", "Update", nullptr));
        pbDeleteSelectedVar->setText(QCoreApplication::translate("MainWindow", "Delete", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "Operator", nullptr));
        lbOperatorTitile->setText(QCoreApplication::translate("MainWindow", "Delta Robot System", nullptr));
        pbStartSystem->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        pbStopSystem->setText(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = twOperatorParameter->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("MainWindow", "Value", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("MainWindow", "Name", nullptr));
        pbOperatorResetParameter->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pbSwitchProgramer->setText(QCoreApplication::translate("MainWindow", "> Programer", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Project", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "project 1", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Delta X S - Pick & Place - Conveyor + Vision", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "New Project", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Delta X 2 - Pick & Place", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Delta X 2 - Object Sorting - Vision", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "3D printing", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Instruction Manual", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Software User Manual", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "G-code Reference", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Program Syntax", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Robot Manual", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Application Case", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Simple Pick and Place", nullptr));
        pushButton_8->setText(QCoreApplication::translate("MainWindow", "Pick and Place with conveyor and vision", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Sorting with camera", nullptr));
        pushButton_9->setText(QCoreApplication::translate("MainWindow", "3D Printing", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Feedback", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Submit", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Administrator", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Operator Setting", nullptr));
        pbApplyOperator->setText(QCoreApplication::translate("MainWindow", "Operator", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        pbAddOperatorDisplayWidget->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        cbOperatorDisplayWidget->setItemText(0, QCoreApplication::translate("MainWindow", "CameraWindow", nullptr));

        label_8->setText(QCoreApplication::translate("MainWindow", "Project", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Title", nullptr));
        leOperatorTitle->setText(QCoreApplication::translate("MainWindow", "Delta Robot System", nullptr));
        pbDeleteOperatorVar->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        pbAddVarToOperatorDisplay->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Variable", nullptr));
#if QT_CONFIG(tooltip)
        leOperatorVar->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        leOperatorVar->setWhatsThis(QString());
#endif // QT_CONFIG(whatsthis)
        leOperatorVar->setText(QString());
        leOperatorVar->setPlaceholderText(QCoreApplication::translate("MainWindow", "#var", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        leOperatorVarName->setText(QString());
        leOperatorVarName->setPlaceholderText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        leAuthorityPassword->setText(QCoreApplication::translate("MainWindow", "1234", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Program", nullptr));
        pbAddOperatorGcodeProgram->setText(QCoreApplication::translate("MainWindow", "Add", nullptr));
        pbDeleteOperatorDisplayWidget->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        pbDeleteOperatorGcodeProgram->setText(QCoreApplication::translate("MainWindow", "x", nullptr));
        lbSettingsTitle->setText(QCoreApplication::translate("MainWindow", "Settings", nullptr));
        pbResetSettings->setText(QCoreApplication::translate("MainWindow", "Reset to Defaults", nullptr));
        pbBackupSettings->setText(QCoreApplication::translate("MainWindow", "Backup Settings", nullptr));
        pbRestoreSettings->setText(QCoreApplication::translate("MainWindow", "Restore Settings", nullptr));
        pbSaveSetting->setText(QCoreApplication::translate("MainWindow", "Save Settings", nullptr));
        twSettingsCategories->setTabText(twSettingsCategories->indexOf(tabGeneral), QCoreApplication::translate("MainWindow", "General", nullptr));
        twSettingsCategories->setTabText(twSettingsCategories->indexOf(tabDevice), QCoreApplication::translate("MainWindow", "Device", nullptr));
        twSettingsCategories->setTabText(twSettingsCategories->indexOf(tabCamera), QCoreApplication::translate("MainWindow", "Camera", nullptr));
        twSettingsCategories->setTabText(twSettingsCategories->indexOf(tabEditor), QCoreApplication::translate("MainWindow", "Editor", nullptr));
        twSettingsCategories->setTabText(twSettingsCategories->indexOf(tabAdvanced), QCoreApplication::translate("MainWindow", "Advanced", nullptr));
        twSettingsCategories->setTabText(twSettingsCategories->indexOf(tabAuthority), QCoreApplication::translate("MainWindow", "Authority", nullptr));
        twProjectManager->setTabText(twProjectManager->indexOf(tabAddNewButton), QCoreApplication::translate("MainWindow", "+", nullptr));
        teLoggingBox->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-size:7.8pt;\"><br /></p></body></html>", nullptr));
        tbExpandLoggingBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
