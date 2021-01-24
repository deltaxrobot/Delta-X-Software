/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <CameraWidget.h>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <codeeditor.h>
#include <drawingwidget.h>

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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_16;
    QVBoxLayout *verticalLayout_15;
    QTabWidget *twDeltaManager;
    QWidget *tabDefaultDelta;
    QWidget *tabAddNewDelta;
    QFrame *horizontalFrame;
    QHBoxLayout *horizontalLayout_14;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_12;
    QPushButton *pbConnect;
    QCheckBox *cbAutoConnect;
    QVBoxLayout *verticalLayout_11;
    QLabel *lbID;
    QLabel *lbPort;
    QLabel *lbIP;
    QSpacerItem *horizontalSpacer_4;
    QSplitter *splitter;
    QTabWidget *twDeltaGeometry;
    QWidget *t3D;
    QVBoxLayout *verticalLayout_23;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_24;
    QPushButton *pbTurnOnROS;
    QWidget *widget;
    QFrame *frameROS;
    QHBoxLayout *horizontalLayout_16;
    QGroupBox *groupBox_3;
    QComboBox *cbROSCameraView;
    QLabel *label;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QComboBox *cbRobotVersion;
    QLabel *label_2;
    QComboBox *cbEndEffector;
    QLabel *label_3;
    QPushButton *btDeleteAllObjects;
    QWidget *t2D;
    QVBoxLayout *verticalLayout_22;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QWidget *wg2D;
    QSlider *vsZAdjsution;
    QLabel *label_15;
    QWidget *widget1;
    QGridLayout *gridLayout_9;
    QLabel *label_61;
    QLabel *label_16;
    QLabel *label_60;
    QSlider *vsAngleAdjsution_3;
    QSlider *vsAngleAdjsution_2;
    QSlider *vsAngleAdjsution;
    QWidget *widget2;
    QGridLayout *gridLayout_10;
    QLabel *label_53;
    QLabel *label_41;
    QLabel *lbXCursor;
    QLabel *label_51;
    QLabel *lbYCursor;
    QWidget *tJogging;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *gbMovement1;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pbHome;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_6;
    QLineEdit *leX;
    QPushButton *pbX;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QLineEdit *leY;
    QPushButton *pbY;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_9;
    QLineEdit *leZ;
    QPushButton *pbZ;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_10;
    QLineEdit *leW;
    QPushButton *pbW;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout_2;
    QPushButton *pbBackward;
    QPushButton *pbDown;
    QPushButton *pbLeft;
    QPushButton *pbForward;
    QPushButton *pbRight;
    QPushButton *pbUp;
    QGridLayout *gridLayout;
    QLabel *label_33;
    QComboBox *cbDivision;
    QLabel *label_28;
    QLabel *label_29;
    QLineEdit *leVelocity;
    QLabel *label_30;
    QLabel *label_31;
    QLineEdit *leAccel;
    QLabel *label_32;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *gbRelay;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_3;
    QLabel *label_34;
    QLabel *label_35;
    QPushButton *pbPump;
    QPushButton *pbLaser;
    QGroupBox *gbGripper;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_17;
    QGridLayout *gridLayout_6;
    QLabel *label_17;
    QLabel *label_27;
    QPushButton *pbGrip;
    QLineEdit *leGripperMin;
    QLineEdit *leGripperMax;
    QHBoxLayout *horizontalLayout_15;
    QSlider *hsGripperAngle;
    QLabel *lbGripperValue;
    QGroupBox *groupBox_5;
    QGroupBox *groupBox_6;
    QSpacerItem *verticalSpacer;
    QWidget *xExternal;
    QVBoxLayout *verticalLayout_19;
    QTabWidget *twConveyor;
    QWidget *tConveyor;
    QVBoxLayout *verticalLayout_18;
    QPushButton *pbConveyorConnect;
    QGridLayout *gridLayout_7;
    QLabel *label_12;
    QLabel *label_57;
    QLineEdit *leSpeedOfPositionMode;
    QLabel *lbSpeedOfPositionMode;
    QLineEdit *leConveyorvMovingValue;
    QLabel *label_52;
    QComboBox *cbConveyorMode;
    QLabel *label_46;
    QComboBox *cbConveyorValueType;
    QSpacerItem *verticalSpacer_2;
    QWidget *sSlidingRail;
    QVBoxLayout *verticalLayout_20;
    QPushButton *pbSlidingConnect;
    QGridLayout *gridLayout_8;
    QLabel *label_36;
    QLabel *label_58;
    QLabel *label_59;
    QLabel *label_37;
    QLineEdit *leSlidingPosition;
    QLineEdit *leSlidingSpeed;
    QPushButton *pbSlidingHome;
    QPushButton *pbSlidingDisable;
    QSpacerItem *verticalSpacer_3;
    QWidget *tExternalMCU;
    QVBoxLayout *verticalLayout_21;
    QPushButton *pbExternalControllerConnect;
    QLineEdit *leReceiveFromMCU;
    QLineEdit *leTransmitToMCU;
    QSpacerItem *verticalSpacer_4;
    QWidget *tTerminal;
    QWidget *layoutWidget3;
    QGridLayout *gridLayout_4;
    QTextEdit *teDebug;
    QLabel *label_4;
    QLineEdit *leTerminal;
    QLabel *label_5;
    QTabWidget *twModule;
    QWidget *tGcodeEditor;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_10;
    QGroupBox *gbAddGcode;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_8;
    QComboBox *cbGcode;
    QLabel *lbAg1;
    QLineEdit *leAg1;
    QLabel *lbAg2;
    QLineEdit *leAg2;
    QLabel *lbAg3;
    QLineEdit *leAg3;
    QLabel *lbAg4;
    QLineEdit *leAg4;
    QLabel *lbAg5;
    QLineEdit *leAg5;
    QLabel *lbAg6;
    QLineEdit *leAg6;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pbAddGcode;
    QPushButton *pbGcodeReference;
    QSpacerItem *horizontalSpacer;
    QGroupBox *gbVar;
    QHBoxLayout *horizontalLayout_10;
    QLineEdit *leVariable1;
    QLabel *lbVar1;
    QLineEdit *leVariable2;
    QLabel *lbVar2;
    QLineEdit *leVariable3;
    QLabel *lbVar3;
    QLineEdit *leVariable4;
    QLabel *lbVar4;
    QLineEdit *leVariable5;
    QLabel *lbVar5;
    QLineEdit *leVariable6;
    QLabel *lbVar6;
    QHBoxLayout *horizontalLayout_11;
    QCheckBox *cbLockGcodeEditor;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pbSaveGcode;
    CodeEditor *pteGcodeArea;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_8;
    QPushButton *pbFormat;
    QCheckBox *cbFormatColor;
    QCheckBox *cbAutoNumbering;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_9;
    QPushButton *pbExecuteGcodes;
    QComboBox *cbPositionToExecuteGcode;
    QTabWidget *tabWidget;
    QWidget *tab;
    QScrollArea *saProgramFiles;
    QWidget *wgProgramContainer;
    QFrame *frExProgram;
    QLineEdit *leExProgramName;
    QPushButton *pbExDeleteProgram;
    QLabel *lbExGCodeNumber;
    QWidget *layoutWidget4;
    QVBoxLayout *verticalLayout_13;
    QPushButton *pbUploadProgram;
    QPushButton *pbImportGcodeFiles;
    QWidget *layoutWidget5;
    QVBoxLayout *verticalLayout_14;
    QPushButton *pbAddNewProgram;
    QPushButton *pbRefreshGcodeFiles;
    QPushButton *pbFindGcodeFile;
    QPushButton *pbSortGcodeFiles;
    QWidget *tab_3;
    QListWidget *listWidget;
    QTextEdit *textEdit;
    QPushButton *pbUploadProgram_2;
    QWidget *tResultCameraArea;
    QGroupBox *groupBox;
    QLabel *lbTrackingObject;
    QPushButton *pbObjectRect;
    QLineEdit *leLRec;
    QLineEdit *leWRec;
    QLineEdit *leHRec;
    QLabel *label_42;
    QLabel *label_43;
    QLabel *label_44;
    QLabel *label_54;
    QLabel *label_55;
    QLabel *label_56;
    QComboBox *cbObjectType;
    QGroupBox *groupBox_7;
    QLineEdit *leConvenyorSpeed;
    QLabel *label_45;
    QComboBox *cbConveyorDirection;
    QLabel *label_47;
    QLabel *label_49;
    QGroupBox *groupBox_8;
    QPushButton *pbObjectLine;
    QLineEdit *leRealDistance;
    QLineEdit *leYCoordinate;
    QPushButton *pbObjectOrigin;
    QLineEdit *leXCoordinate;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_40;
    QPushButton *pbChangeXAxis;
    QCheckBox *cbDisplayCalibInfo;
    QGroupBox *groupBox_9;
    QPushButton *pbLoadCamera;
    QPushButton *pbLoadTestImage;
    QLabel *label_11;
    QLineEdit *leFPS;
    QPushButton *pbPlayPauseCamera;
    QPushButton *pbCaptureCamera;
    QPushButton *pbLoadCameraSetting;
    QPushButton *pbSaveCameraSetting;
    QLabel *lbCameraState;
    QGroupBox *groupBox_10;
    QPushButton *pbViewDataObjects;
    QPushButton *pbClearDetectObjects;
    QLabel *label_50;
    QLabel *label_48;
    QLabel *lbTrackingObjectNumber;
    QLabel *lbVisibleObjectNumber;
    QPushButton *pbFilter;
    QPushButton *pbTransformPerspective;
    QScrollArea *saCamera;
    QWidget *saCameraArea;
    CameraWidget *lbScreenStreamer;
    QPushButton *pbExpandCameraWidget;
    QPushButton *pbCameraWindowMode;
    QComboBox *lbCameraLayer;
    QWidget *tDrawing;
    QLabel *lbImageForDrawing;
    DrawingWidget *lbDrawingArea;
    QWidget *widget_2;
    QLineEdit *leDrawingThreshold;
    QSlider *hsDrawingThreshold;
    QWidget *widget_3;
    QLabel *lbImageWidth;
    QLabel *lbImageHeight;
    QWidget *widget_4;
    QLabel *label_18;
    QLineEdit *leHeightScale;
    QWidget *widget_5;
    QLabel *label_20;
    QLineEdit *leWidthScale;
    QWidget *widget_6;
    QLabel *label_23;
    QLineEdit *leSpace;
    QPushButton *pbDrawLine;
    QPushButton *pbDrawRectangle;
    QPushButton *pbDrawArc;
    QPushButton *pbDrawCircle;
    QWidget *widget_7;
    QLabel *label_19;
    QLineEdit *leDrawAg1;
    QWidget *widget_8;
    QLabel *label_22;
    QLineEdit *leDrawAg2;
    QWidget *widget_9;
    QLabel *label_24;
    QLineEdit *leDrawAg3;
    QWidget *widget_10;
    QLabel *label_25;
    QLineEdit *leDrawAg4;
    QWidget *widget_11;
    QLabel *label_26;
    QLineEdit *leDrawAg5;
    QPushButton *pbOpenPicture;
    QPushButton *pbExportDrawingGcodes;
    QPushButton *pbPainting;
    QPushButton *pbZoomIn;
    QPushButton *pbZoomOut;
    QLabel *label_21;
    QPushButton *pbCursor;
    QComboBox *cbDrawingEffector;
    QWidget *widget_12;
    QComboBox *cbDrawMethod;
    QLabel *label_13;
    QWidget *widget_13;
    QComboBox *cbConversionTool;
    QLabel *label_14;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QMenu *menuReferences;
    QMenu *menuEditor;
    QMenu *menuExecute;
    QMenu *menu_2;
    QMenu *menuSetting;
    QMenu *menuConnection;
    QMenu *menuUI;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 775);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 480));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(true);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("delta_x_logo_96x96.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("QMainWindow\n"
"{\n"
"	background-color: rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton\n"
"{	\n"
"	color: rgb(50, 50, 50);\n"
"	border: 1px solid rgb(50, 50, 50);\n"
"	border-radius: 2px;\n"
"	background: none;\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{	\n"
"	color: rgb(255, 255, 255);\n"
"	background: rgb(50, 50, 50);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{	\n"
"	color: rgb(50, 50, 50);\n"
"	background: none;\n"
"}\n"
"\n"
"QGroupBox{\n"
"	color: rgb(50, 50, 50);\n"
"	border: 1px solid rgb(222, 222, 222);\n"
"	background: none;\n"
"}\n"
"\n"
"QLineEdit{\n"
"	color: rgb(50, 50, 50);\n"
"	border: 1px solid rgb(50, 50, 50);\n"
"	background: none;\n"
"}\n"
"\n"
"QComboBox\n"
"{\n"
"	border: 1px solid rgb(50, 50, 50);\n"
"	border-radius: 2px;\n"
"}\n"
"\n"
"QComboBox:drop-down\n"
"{\n"
"	padding:3px;\n"
"	height: 10px;\n"
"	width: 10px;\n"
"	image: url(:/icons8_expand_arrow_16px.png);\n"
"}\n"
"\n"
"QCheckBox, QComboBox, QLabel{\n"
"	color: rgb(50, 50, 50);\n"
"	background: none;\n"
"}"));
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
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_16 = new QVBoxLayout(centralWidget);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        twDeltaManager = new QTabWidget(centralWidget);
        twDeltaManager->setObjectName(QString::fromUtf8("twDeltaManager"));
        twDeltaManager->setEnabled(true);
        twDeltaManager->setMaximumSize(QSize(16777215, 30));
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setKerning(true);
        twDeltaManager->setFont(font1);
        twDeltaManager->setStyleSheet(QString::fromUtf8("color: rgb(18, 190, 190);"));
        tabDefaultDelta = new QWidget();
        tabDefaultDelta->setObjectName(QString::fromUtf8("tabDefaultDelta"));
        twDeltaManager->addTab(tabDefaultDelta, QString());
        tabAddNewDelta = new QWidget();
        tabAddNewDelta->setObjectName(QString::fromUtf8("tabAddNewDelta"));
        twDeltaManager->addTab(tabAddNewDelta, QString());

        verticalLayout_15->addWidget(twDeltaManager);

        horizontalFrame = new QFrame(centralWidget);
        horizontalFrame->setObjectName(QString::fromUtf8("horizontalFrame"));
        horizontalFrame->setMaximumSize(QSize(16777215, 100));
        horizontalLayout_14 = new QHBoxLayout(horizontalFrame);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        frame = new QFrame(horizontalFrame);
        frame->setObjectName(QString::fromUtf8("frame"));
        QFont font2;
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        font2.setKerning(true);
        frame->setFont(font2);
        frame->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(54, 54, 54);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(frame);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(5, 5, 5, 5);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        pbConnect = new QPushButton(frame);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));
        pbConnect->setMinimumSize(QSize(0, 40));
        pbConnect->setStyleSheet(QString::fromUtf8("background-color: rgb(41, 155, 255);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 4px;\n"
"border: none;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/disconnected.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/connected.png"), QSize(), QIcon::Normal, QIcon::On);
        pbConnect->setIcon(icon1);
        pbConnect->setIconSize(QSize(30, 20));

        verticalLayout_12->addWidget(pbConnect);

        cbAutoConnect = new QCheckBox(frame);
        cbAutoConnect->setObjectName(QString::fromUtf8("cbAutoConnect"));
        cbAutoConnect->setChecked(true);

        verticalLayout_12->addWidget(cbAutoConnect);


        horizontalLayout_13->addLayout(verticalLayout_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        lbID = new QLabel(frame);
        lbID->setObjectName(QString::fromUtf8("lbID"));
        QFont font3;
        font3.setPointSize(7);
        lbID->setFont(font3);

        verticalLayout_11->addWidget(lbID);

        lbPort = new QLabel(frame);
        lbPort->setObjectName(QString::fromUtf8("lbPort"));
        lbPort->setFont(font3);

        verticalLayout_11->addWidget(lbPort);

        lbIP = new QLabel(frame);
        lbIP->setObjectName(QString::fromUtf8("lbIP"));
        lbIP->setFont(font3);

        verticalLayout_11->addWidget(lbIP);


        horizontalLayout_13->addLayout(verticalLayout_11);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);


        horizontalLayout_14->addWidget(frame);


        verticalLayout_15->addWidget(horizontalFrame);

        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setMinimumSize(QSize(0, 300));
        splitter->setOrientation(Qt::Horizontal);
        twDeltaGeometry = new QTabWidget(splitter);
        twDeltaGeometry->setObjectName(QString::fromUtf8("twDeltaGeometry"));
        twDeltaGeometry->setMinimumSize(QSize(420, 0));
        t3D = new QWidget();
        t3D->setObjectName(QString::fromUtf8("t3D"));
        verticalLayout_23 = new QVBoxLayout(t3D);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        scrollArea_4 = new QScrollArea(t3D);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 410, 507));
        verticalLayout_24 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setContentsMargins(11, 11, 11, 11);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        verticalLayout_24->setContentsMargins(5, 5, 5, 5);
        pbTurnOnROS = new QPushButton(scrollAreaWidgetContents_4);
        pbTurnOnROS->setObjectName(QString::fromUtf8("pbTurnOnROS"));
        pbTurnOnROS->setMinimumSize(QSize(100, 30));
        pbTurnOnROS->setMaximumSize(QSize(150, 16777215));

        verticalLayout_24->addWidget(pbTurnOnROS);

        widget = new QWidget(scrollAreaWidgetContents_4);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMinimumSize(QSize(400, 300));
        widget->setStyleSheet(QString::fromUtf8(""));
        frameROS = new QFrame(widget);
        frameROS->setObjectName(QString::fromUtf8("frameROS"));
        frameROS->setGeometry(QRect(0, 5, 400, 300));
        frameROS->setStyleSheet(QString::fromUtf8("background-color: rgb(226, 226, 226);"));
        frameROS->setFrameShape(QFrame::StyledPanel);
        frameROS->setFrameShadow(QFrame::Raised);

        verticalLayout_24->addWidget(widget);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 0));
        groupBox_3->setMaximumSize(QSize(150, 16777215));
        cbROSCameraView = new QComboBox(groupBox_3);
        cbROSCameraView->addItem(QString());
        cbROSCameraView->addItem(QString());
        cbROSCameraView->addItem(QString());
        cbROSCameraView->setObjectName(QString::fromUtf8("cbROSCameraView"));
        cbROSCameraView->setGeometry(QRect(95, 30, 41, 22));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 81, 16));

        horizontalLayout_16->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        layoutWidget = new QWidget(groupBox_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 206, 74));
        gridLayout_5 = new QGridLayout(layoutWidget);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        gridLayout_5->setContentsMargins(0, 0, 0, 0);
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        cbRobotVersion = new QComboBox(layoutWidget);
        cbRobotVersion->addItem(QString());
        cbRobotVersion->addItem(QString());
        cbRobotVersion->setObjectName(QString::fromUtf8("cbRobotVersion"));

        gridLayout_5->addWidget(cbRobotVersion, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMaximumSize(QSize(80, 16777215));

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        cbEndEffector = new QComboBox(layoutWidget);
        cbEndEffector->addItem(QString());
        cbEndEffector->addItem(QString());
        cbEndEffector->addItem(QString());
        cbEndEffector->setObjectName(QString::fromUtf8("cbEndEffector"));
        cbEndEffector->setMaximumSize(QSize(120, 16777215));

        gridLayout_5->addWidget(cbEndEffector, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_5->addWidget(label_3, 2, 0, 1, 1);

        btDeleteAllObjects = new QPushButton(layoutWidget);
        btDeleteAllObjects->setObjectName(QString::fromUtf8("btDeleteAllObjects"));

        gridLayout_5->addWidget(btDeleteAllObjects, 2, 1, 1, 1);


        horizontalLayout_16->addWidget(groupBox_4);


        verticalLayout_24->addLayout(horizontalLayout_16);

        scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_23->addWidget(scrollArea_4);

        twDeltaGeometry->addTab(t3D, QString());
        t2D = new QWidget();
        t2D->setObjectName(QString::fromUtf8("t2D"));
        verticalLayout_22 = new QVBoxLayout(t2D);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        scrollArea_3 = new QScrollArea(t2D);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 369, 600));
        scrollAreaWidgetContents_3->setMinimumSize(QSize(0, 600));
        wg2D = new QWidget(scrollAreaWidgetContents_3);
        wg2D->setObjectName(QString::fromUtf8("wg2D"));
        wg2D->setGeometry(QRect(45, 95, 300, 300));
        wg2D->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        vsZAdjsution = new QSlider(scrollAreaWidgetContents_3);
        vsZAdjsution->setObjectName(QString::fromUtf8("vsZAdjsution"));
        vsZAdjsution->setGeometry(QRect(15, 100, 22, 301));
        vsZAdjsution->setMaximum(300);
        vsZAdjsution->setOrientation(Qt::Vertical);
        label_15 = new QLabel(scrollAreaWidgetContents_3);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(20, 420, 17, 16));
        widget1 = new QWidget(scrollAreaWidgetContents_3);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(55, 420, 301, 105));
        gridLayout_9 = new QGridLayout(widget1);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        gridLayout_9->setContentsMargins(0, 0, 0, 0);
        label_61 = new QLabel(widget1);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        gridLayout_9->addWidget(label_61, 2, 0, 1, 1);

        label_16 = new QLabel(widget1);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_9->addWidget(label_16, 0, 0, 1, 1);

        label_60 = new QLabel(widget1);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout_9->addWidget(label_60, 1, 0, 1, 1);

        vsAngleAdjsution_3 = new QSlider(widget1);
        vsAngleAdjsution_3->setObjectName(QString::fromUtf8("vsAngleAdjsution_3"));
        vsAngleAdjsution_3->setMaximum(180);
        vsAngleAdjsution_3->setValue(1);
        vsAngleAdjsution_3->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(vsAngleAdjsution_3, 2, 1, 1, 1);

        vsAngleAdjsution_2 = new QSlider(widget1);
        vsAngleAdjsution_2->setObjectName(QString::fromUtf8("vsAngleAdjsution_2"));
        vsAngleAdjsution_2->setMaximum(180);
        vsAngleAdjsution_2->setValue(1);
        vsAngleAdjsution_2->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(vsAngleAdjsution_2, 1, 1, 1, 1);

        vsAngleAdjsution = new QSlider(widget1);
        vsAngleAdjsution->setObjectName(QString::fromUtf8("vsAngleAdjsution"));
        vsAngleAdjsution->setMaximum(180);
        vsAngleAdjsution->setValue(1);
        vsAngleAdjsution->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(vsAngleAdjsution, 0, 1, 1, 1);

        widget2 = new QWidget(scrollAreaWidgetContents_3);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setGeometry(QRect(45, 10, 81, 64));
        gridLayout_10 = new QGridLayout(widget2);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        gridLayout_10->setContentsMargins(0, 0, 0, 0);
        label_53 = new QLabel(widget2);
        label_53->setObjectName(QString::fromUtf8("label_53"));

        gridLayout_10->addWidget(label_53, 0, 0, 1, 2);

        label_41 = new QLabel(widget2);
        label_41->setObjectName(QString::fromUtf8("label_41"));

        gridLayout_10->addWidget(label_41, 1, 0, 1, 1);

        lbXCursor = new QLabel(widget2);
        lbXCursor->setObjectName(QString::fromUtf8("lbXCursor"));

        gridLayout_10->addWidget(lbXCursor, 1, 1, 1, 1);

        label_51 = new QLabel(widget2);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_10->addWidget(label_51, 2, 0, 1, 1);

        lbYCursor = new QLabel(widget2);
        lbYCursor->setObjectName(QString::fromUtf8("lbYCursor"));

        gridLayout_10->addWidget(lbYCursor, 2, 1, 1, 1);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_22->addWidget(scrollArea_3);

        twDeltaGeometry->addTab(t2D, QString());
        tJogging = new QWidget();
        tJogging->setObjectName(QString::fromUtf8("tJogging"));
        verticalLayout_4 = new QVBoxLayout(tJogging);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea_2 = new QScrollArea(tJogging);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 369, 800));
        scrollAreaWidgetContents_2->setMinimumSize(QSize(0, 800));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        gbMovement1 = new QGroupBox(scrollAreaWidgetContents_2);
        gbMovement1->setObjectName(QString::fromUtf8("gbMovement1"));
        gbMovement1->setMinimumSize(QSize(0, 350));
        gbMovement1->setMaximumSize(QSize(360, 400));
        verticalLayout_3 = new QVBoxLayout(gbMovement1);
        verticalLayout_3->setSpacing(11);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(11, 30, 11, 11);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(20);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pbHome = new QPushButton(gbMovement1);
        pbHome->setObjectName(QString::fromUtf8("pbHome"));
        pbHome->setMinimumSize(QSize(70, 70));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("icon/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbHome->setIcon(icon2);
        pbHome->setIconSize(QSize(50, 50));

        horizontalLayout_5->addWidget(pbHome);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(-1, 0, -1, 0);
        label_6 = new QLabel(gbMovement1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(50, 0));
        label_6->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label_6);

        leX = new QLineEdit(gbMovement1);
        leX->setObjectName(QString::fromUtf8("leX"));

        horizontalLayout->addWidget(leX);

        pbX = new QPushButton(gbMovement1);
        pbX->setObjectName(QString::fromUtf8("pbX"));
        pbX->setMinimumSize(QSize(30, 30));
        QFont font4;
        font4.setPointSize(10);
        pbX->setFont(font4);

        horizontalLayout->addWidget(pbX);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, 0);
        label_8 = new QLabel(gbMovement1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMinimumSize(QSize(50, 0));
        label_8->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_8);

        leY = new QLineEdit(gbMovement1);
        leY->setObjectName(QString::fromUtf8("leY"));

        horizontalLayout_2->addWidget(leY);

        pbY = new QPushButton(gbMovement1);
        pbY->setObjectName(QString::fromUtf8("pbY"));
        pbY->setMinimumSize(QSize(30, 30));
        pbY->setFont(font4);

        horizontalLayout_2->addWidget(pbY);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(-1, 0, -1, 0);
        label_9 = new QLabel(gbMovement1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMinimumSize(QSize(50, 0));
        label_9->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(label_9);

        leZ = new QLineEdit(gbMovement1);
        leZ->setObjectName(QString::fromUtf8("leZ"));

        horizontalLayout_3->addWidget(leZ);

        pbZ = new QPushButton(gbMovement1);
        pbZ->setObjectName(QString::fromUtf8("pbZ"));
        pbZ->setMinimumSize(QSize(30, 30));
        pbZ->setFont(font4);

        horizontalLayout_3->addWidget(pbZ);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(-1, 0, -1, 0);
        label_10 = new QLabel(gbMovement1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setMinimumSize(QSize(50, 0));
        label_10->setAlignment(Qt::AlignCenter);

        horizontalLayout_4->addWidget(label_10);

        leW = new QLineEdit(gbMovement1);
        leW->setObjectName(QString::fromUtf8("leW"));

        horizontalLayout_4->addWidget(leW);

        pbW = new QPushButton(gbMovement1);
        pbW->setObjectName(QString::fromUtf8("pbW"));
        pbW->setMinimumSize(QSize(30, 30));
        pbW->setFont(font4);

        horizontalLayout_4->addWidget(pbW);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pbBackward = new QPushButton(gbMovement1);
        pbBackward->setObjectName(QString::fromUtf8("pbBackward"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("icon/icons8-expand-arrow-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbBackward->setIcon(icon3);
        pbBackward->setIconSize(QSize(40, 40));

        gridLayout_2->addWidget(pbBackward, 1, 1, 1, 1);

        pbDown = new QPushButton(gbMovement1);
        pbDown->setObjectName(QString::fromUtf8("pbDown"));
        pbDown->setIcon(icon3);
        pbDown->setIconSize(QSize(40, 40));

        gridLayout_2->addWidget(pbDown, 1, 3, 1, 1);

        pbLeft = new QPushButton(gbMovement1);
        pbLeft->setObjectName(QString::fromUtf8("pbLeft"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("icon/icons8-back-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLeft->setIcon(icon4);
        pbLeft->setIconSize(QSize(40, 40));

        gridLayout_2->addWidget(pbLeft, 0, 0, 2, 1);

        pbForward = new QPushButton(gbMovement1);
        pbForward->setObjectName(QString::fromUtf8("pbForward"));
        pbForward->setStyleSheet(QString::fromUtf8(""));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("icon/icons8-collapse-arrow-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbForward->setIcon(icon5);
        pbForward->setIconSize(QSize(40, 40));

        gridLayout_2->addWidget(pbForward, 0, 1, 1, 1);

        pbRight = new QPushButton(gbMovement1);
        pbRight->setObjectName(QString::fromUtf8("pbRight"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("icon/icons8-forward-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRight->setIcon(icon6);
        pbRight->setIconSize(QSize(40, 40));

        gridLayout_2->addWidget(pbRight, 0, 2, 2, 1);

        pbUp = new QPushButton(gbMovement1);
        pbUp->setObjectName(QString::fromUtf8("pbUp"));
        pbUp->setIcon(icon5);
        pbUp->setIconSize(QSize(40, 40));

        gridLayout_2->addWidget(pbUp, 0, 3, 1, 1);


        horizontalLayout_6->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_33 = new QLabel(gbMovement1);
        label_33->setObjectName(QString::fromUtf8("label_33"));

        gridLayout->addWidget(label_33, 0, 0, 1, 1);

        cbDivision = new QComboBox(gbMovement1);
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->setObjectName(QString::fromUtf8("cbDivision"));

        gridLayout->addWidget(cbDivision, 0, 1, 1, 1);

        label_28 = new QLabel(gbMovement1);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        gridLayout->addWidget(label_28, 0, 2, 1, 1);

        label_29 = new QLabel(gbMovement1);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        gridLayout->addWidget(label_29, 1, 0, 1, 1);

        leVelocity = new QLineEdit(gbMovement1);
        leVelocity->setObjectName(QString::fromUtf8("leVelocity"));

        gridLayout->addWidget(leVelocity, 1, 1, 1, 1);

        label_30 = new QLabel(gbMovement1);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout->addWidget(label_30, 1, 2, 1, 1);

        label_31 = new QLabel(gbMovement1);
        label_31->setObjectName(QString::fromUtf8("label_31"));

        gridLayout->addWidget(label_31, 2, 0, 1, 1);

        leAccel = new QLineEdit(gbMovement1);
        leAccel->setObjectName(QString::fromUtf8("leAccel"));

        gridLayout->addWidget(leAccel, 2, 1, 1, 1);

        label_32 = new QLabel(gbMovement1);
        label_32->setObjectName(QString::fromUtf8("label_32"));

        gridLayout->addWidget(label_32, 2, 2, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);


        verticalLayout_3->addLayout(horizontalLayout_6);


        verticalLayout_5->addWidget(gbMovement1);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 400));
        verticalLayout_6 = new QVBoxLayout(groupBox_2);
        verticalLayout_6->setSpacing(10);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(10, 30, 10, 10);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        gbRelay = new QGroupBox(groupBox_2);
        gbRelay->setObjectName(QString::fromUtf8("gbRelay"));
        layoutWidget1 = new QWidget(gbRelay);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(5, 20, 132, 96));
        gridLayout_3 = new QGridLayout(layoutWidget1);
        gridLayout_3->setSpacing(10);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(10, 10, 10, 10);
        label_34 = new QLabel(layoutWidget1);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setMaximumSize(QSize(16777215, 20));
        QFont font5;
        font5.setPointSize(7);
        font5.setBold(false);
        font5.setWeight(50);
        font5.setKerning(true);
        label_34->setFont(font5);
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_34, 0, 0, 1, 1);

        label_35 = new QLabel(layoutWidget1);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setMaximumSize(QSize(16777215, 20));
        label_35->setFont(font5);
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_35, 0, 1, 1, 1);

        pbPump = new QPushButton(layoutWidget1);
        pbPump->setObjectName(QString::fromUtf8("pbPump"));
        pbPump->setAutoFillBackground(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("icon/Toggle Off_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8("icon/Toggle On_16px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbPump->setIcon(icon7);
        pbPump->setCheckable(true);
        pbPump->setChecked(false);
        pbPump->setAutoDefault(false);
        pbPump->setFlat(false);

        gridLayout_3->addWidget(pbPump, 1, 0, 1, 1);

        pbLaser = new QPushButton(layoutWidget1);
        pbLaser->setObjectName(QString::fromUtf8("pbLaser"));
        pbLaser->setAutoFillBackground(false);
        pbLaser->setIcon(icon7);
        pbLaser->setCheckable(true);
        pbLaser->setChecked(false);
        pbLaser->setAutoDefault(false);
        pbLaser->setFlat(false);

        gridLayout_3->addWidget(pbLaser, 1, 1, 1, 1);

        gridLayout_3->setRowStretch(0, 1);
        gridLayout_3->setRowStretch(1, 1);
        gridLayout_3->setColumnStretch(0, 1);
        gridLayout_3->setColumnStretch(1, 1);
        gridLayout_3->setColumnMinimumWidth(0, 1);
        gridLayout_3->setColumnMinimumWidth(1, 1);
        gridLayout_3->setRowMinimumHeight(0, 1);
        gridLayout_3->setRowMinimumHeight(1, 1);

        horizontalLayout_7->addWidget(gbRelay);

        gbGripper = new QGroupBox(groupBox_2);
        gbGripper->setObjectName(QString::fromUtf8("gbGripper"));
        layoutWidget2 = new QWidget(gbGripper);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(5, 18, 156, 86));
        verticalLayout_17 = new QVBoxLayout(layoutWidget2);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(0, 0, 0, 0);
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_17 = new QLabel(layoutWidget2);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font5);

        gridLayout_6->addWidget(label_17, 0, 1, 1, 1);

        label_27 = new QLabel(layoutWidget2);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font5);

        gridLayout_6->addWidget(label_27, 0, 2, 1, 1);

        pbGrip = new QPushButton(layoutWidget2);
        pbGrip->setObjectName(QString::fromUtf8("pbGrip"));
        pbGrip->setMinimumSize(QSize(60, 30));
        pbGrip->setAutoFillBackground(false);
        pbGrip->setAutoDefault(false);
        pbGrip->setFlat(false);

        gridLayout_6->addWidget(pbGrip, 1, 0, 1, 1);

        leGripperMin = new QLineEdit(layoutWidget2);
        leGripperMin->setObjectName(QString::fromUtf8("leGripperMin"));

        gridLayout_6->addWidget(leGripperMin, 1, 1, 1, 1);

        leGripperMax = new QLineEdit(layoutWidget2);
        leGripperMax->setObjectName(QString::fromUtf8("leGripperMax"));

        gridLayout_6->addWidget(leGripperMax, 1, 2, 1, 1);


        verticalLayout_17->addLayout(gridLayout_6);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        hsGripperAngle = new QSlider(layoutWidget2);
        hsGripperAngle->setObjectName(QString::fromUtf8("hsGripperAngle"));
        hsGripperAngle->setMaximum(20);
        hsGripperAngle->setSingleStep(5);
        hsGripperAngle->setOrientation(Qt::Horizontal);

        horizontalLayout_15->addWidget(hsGripperAngle);

        lbGripperValue = new QLabel(layoutWidget2);
        lbGripperValue->setObjectName(QString::fromUtf8("lbGripperValue"));
        lbGripperValue->setFont(font5);

        horizontalLayout_15->addWidget(lbGripperValue);


        verticalLayout_17->addLayout(horizontalLayout_15);


        horizontalLayout_7->addWidget(gbGripper);


        verticalLayout_6->addLayout(horizontalLayout_7);

        groupBox_5 = new QGroupBox(groupBox_2);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));

        verticalLayout_6->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_2);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));

        verticalLayout_6->addWidget(groupBox_6);


        verticalLayout_5->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_4->addWidget(scrollArea_2);

        twDeltaGeometry->addTab(tJogging, QString());
        xExternal = new QWidget();
        xExternal->setObjectName(QString::fromUtf8("xExternal"));
        verticalLayout_19 = new QVBoxLayout(xExternal);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        twConveyor = new QTabWidget(xExternal);
        twConveyor->setObjectName(QString::fromUtf8("twConveyor"));
        twConveyor->setTabPosition(QTabWidget::West);
        tConveyor = new QWidget();
        tConveyor->setObjectName(QString::fromUtf8("tConveyor"));
        verticalLayout_18 = new QVBoxLayout(tConveyor);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        pbConveyorConnect = new QPushButton(tConveyor);
        pbConveyorConnect->setObjectName(QString::fromUtf8("pbConveyorConnect"));
        pbConveyorConnect->setMinimumSize(QSize(100, 50));
        pbConveyorConnect->setMaximumSize(QSize(150, 50));
        QFont font6;
        font6.setPointSize(12);
        pbConveyorConnect->setFont(font6);
        pbConveyorConnect->setStyleSheet(QString::fromUtf8(""));
        pbConveyorConnect->setCheckable(true);

        verticalLayout_18->addWidget(pbConveyorConnect);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(20);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(10, 10, 10, 10);
        label_12 = new QLabel(tConveyor);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_7->addWidget(label_12, 3, 0, 1, 1);

        label_57 = new QLabel(tConveyor);
        label_57->setObjectName(QString::fromUtf8("label_57"));

        gridLayout_7->addWidget(label_57, 4, 0, 1, 1);

        leSpeedOfPositionMode = new QLineEdit(tConveyor);
        leSpeedOfPositionMode->setObjectName(QString::fromUtf8("leSpeedOfPositionMode"));
        leSpeedOfPositionMode->setEnabled(false);
        leSpeedOfPositionMode->setMinimumSize(QSize(0, 30));
        QFont font7;
        font7.setPointSize(8);
        font7.setBold(false);
        font7.setWeight(50);
        font7.setKerning(true);
        leSpeedOfPositionMode->setFont(font7);
        leSpeedOfPositionMode->setClearButtonEnabled(false);

        gridLayout_7->addWidget(leSpeedOfPositionMode, 4, 1, 1, 1);

        lbSpeedOfPositionMode = new QLabel(tConveyor);
        lbSpeedOfPositionMode->setObjectName(QString::fromUtf8("lbSpeedOfPositionMode"));
        lbSpeedOfPositionMode->setEnabled(false);
        lbSpeedOfPositionMode->setFont(font5);

        gridLayout_7->addWidget(lbSpeedOfPositionMode, 4, 2, 1, 1);

        leConveyorvMovingValue = new QLineEdit(tConveyor);
        leConveyorvMovingValue->setObjectName(QString::fromUtf8("leConveyorvMovingValue"));
        leConveyorvMovingValue->setMinimumSize(QSize(0, 30));
        leConveyorvMovingValue->setFont(font7);

        gridLayout_7->addWidget(leConveyorvMovingValue, 3, 1, 1, 1);

        label_52 = new QLabel(tConveyor);
        label_52->setObjectName(QString::fromUtf8("label_52"));

        gridLayout_7->addWidget(label_52, 0, 0, 1, 1);

        cbConveyorMode = new QComboBox(tConveyor);
        cbConveyorMode->addItem(QString());
        cbConveyorMode->addItem(QString());
        cbConveyorMode->setObjectName(QString::fromUtf8("cbConveyorMode"));
        cbConveyorMode->setMinimumSize(QSize(0, 30));
        cbConveyorMode->setFont(font5);

        gridLayout_7->addWidget(cbConveyorMode, 0, 1, 1, 1);

        label_46 = new QLabel(tConveyor);
        label_46->setObjectName(QString::fromUtf8("label_46"));

        gridLayout_7->addWidget(label_46, 1, 0, 1, 1);

        cbConveyorValueType = new QComboBox(tConveyor);
        cbConveyorValueType->addItem(QString());
        cbConveyorValueType->addItem(QString());
        cbConveyorValueType->setObjectName(QString::fromUtf8("cbConveyorValueType"));
        cbConveyorValueType->setMinimumSize(QSize(0, 30));
        cbConveyorValueType->setFont(font5);
        cbConveyorValueType->setStyleSheet(QString::fromUtf8("QComboBox:drop-down\n"
"{\n"
"	padding:3px;\n"
"	height: 10px;\n"
"	width: 10px;\n"
"	image: url(:/icons8_expand_arrow_16px.png);\n"
"}"));

        gridLayout_7->addWidget(cbConveyorValueType, 1, 1, 1, 1);


        verticalLayout_18->addLayout(gridLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_2);

        twConveyor->addTab(tConveyor, QString());
        sSlidingRail = new QWidget();
        sSlidingRail->setObjectName(QString::fromUtf8("sSlidingRail"));
        verticalLayout_20 = new QVBoxLayout(sSlidingRail);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        pbSlidingConnect = new QPushButton(sSlidingRail);
        pbSlidingConnect->setObjectName(QString::fromUtf8("pbSlidingConnect"));
        pbSlidingConnect->setMinimumSize(QSize(0, 50));
        pbSlidingConnect->setMaximumSize(QSize(150, 16777215));
        pbSlidingConnect->setFont(font6);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("icon/connected.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingConnect->setIcon(icon8);

        verticalLayout_20->addWidget(pbSlidingConnect);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(10);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(10, 10, 10, 10);
        label_36 = new QLabel(sSlidingRail);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setFont(font7);

        gridLayout_8->addWidget(label_36, 2, 0, 1, 1);

        label_58 = new QLabel(sSlidingRail);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setFont(font7);

        gridLayout_8->addWidget(label_58, 2, 2, 1, 1);

        label_59 = new QLabel(sSlidingRail);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setFont(font7);

        gridLayout_8->addWidget(label_59, 3, 2, 1, 1);

        label_37 = new QLabel(sSlidingRail);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setFont(font7);

        gridLayout_8->addWidget(label_37, 3, 0, 1, 1);

        leSlidingPosition = new QLineEdit(sSlidingRail);
        leSlidingPosition->setObjectName(QString::fromUtf8("leSlidingPosition"));
        leSlidingPosition->setMinimumSize(QSize(0, 30));

        gridLayout_8->addWidget(leSlidingPosition, 3, 1, 1, 1);

        leSlidingSpeed = new QLineEdit(sSlidingRail);
        leSlidingSpeed->setObjectName(QString::fromUtf8("leSlidingSpeed"));
        leSlidingSpeed->setMinimumSize(QSize(0, 30));

        gridLayout_8->addWidget(leSlidingSpeed, 2, 1, 1, 1);

        pbSlidingHome = new QPushButton(sSlidingRail);
        pbSlidingHome->setObjectName(QString::fromUtf8("pbSlidingHome"));
        pbSlidingHome->setMinimumSize(QSize(0, 40));
        pbSlidingHome->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("icon/icons8-home-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingHome->setIcon(icon9);

        gridLayout_8->addWidget(pbSlidingHome, 1, 1, 1, 1);

        pbSlidingDisable = new QPushButton(sSlidingRail);
        pbSlidingDisable->setObjectName(QString::fromUtf8("pbSlidingDisable"));
        pbSlidingDisable->setMinimumSize(QSize(0, 40));
        pbSlidingDisable->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("icon/icons8-sleeping-in-bed-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingDisable->setIcon(icon10);

        gridLayout_8->addWidget(pbSlidingDisable, 0, 1, 1, 1);


        verticalLayout_20->addLayout(gridLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_20->addItem(verticalSpacer_3);

        twConveyor->addTab(sSlidingRail, QString());
        tExternalMCU = new QWidget();
        tExternalMCU->setObjectName(QString::fromUtf8("tExternalMCU"));
        verticalLayout_21 = new QVBoxLayout(tExternalMCU);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        pbExternalControllerConnect = new QPushButton(tExternalMCU);
        pbExternalControllerConnect->setObjectName(QString::fromUtf8("pbExternalControllerConnect"));
        pbExternalControllerConnect->setMinimumSize(QSize(150, 50));
        pbExternalControllerConnect->setMaximumSize(QSize(150, 16777215));
        pbExternalControllerConnect->setFont(font1);

        verticalLayout_21->addWidget(pbExternalControllerConnect);

        leReceiveFromMCU = new QLineEdit(tExternalMCU);
        leReceiveFromMCU->setObjectName(QString::fromUtf8("leReceiveFromMCU"));
        leReceiveFromMCU->setMinimumSize(QSize(0, 300));
        leReceiveFromMCU->setReadOnly(true);
        leReceiveFromMCU->setClearButtonEnabled(false);

        verticalLayout_21->addWidget(leReceiveFromMCU);

        leTransmitToMCU = new QLineEdit(tExternalMCU);
        leTransmitToMCU->setObjectName(QString::fromUtf8("leTransmitToMCU"));
        leTransmitToMCU->setMinimumSize(QSize(0, 30));

        verticalLayout_21->addWidget(leTransmitToMCU);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_21->addItem(verticalSpacer_4);

        twConveyor->addTab(tExternalMCU, QString());

        verticalLayout_19->addWidget(twConveyor);

        twDeltaGeometry->addTab(xExternal, QString());
        tTerminal = new QWidget();
        tTerminal->setObjectName(QString::fromUtf8("tTerminal"));
        layoutWidget3 = new QWidget(tTerminal);
        layoutWidget3->setObjectName(QString::fromUtf8("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(5, 10, 376, 391));
        gridLayout_4 = new QGridLayout(layoutWidget3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        teDebug = new QTextEdit(layoutWidget3);
        teDebug->setObjectName(QString::fromUtf8("teDebug"));
        teDebug->setFont(font2);
        teDebug->setStyleSheet(QString::fromUtf8("color: rgb(255, 82, 87);"));

        gridLayout_4->addWidget(teDebug, 0, 1, 1, 1);

        label_4 = new QLabel(layoutWidget3);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        leTerminal = new QLineEdit(layoutWidget3);
        leTerminal->setObjectName(QString::fromUtf8("leTerminal"));

        gridLayout_4->addWidget(leTerminal, 1, 1, 1, 1);

        label_5 = new QLabel(layoutWidget3);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        twDeltaGeometry->addTab(tTerminal, QString());
        splitter->addWidget(twDeltaGeometry);
        twModule = new QTabWidget(splitter);
        twModule->setObjectName(QString::fromUtf8("twModule"));
        twModule->setEnabled(true);
        twModule->setFocusPolicy(Qt::TabFocus);
        twModule->setTabShape(QTabWidget::Rounded);
        twModule->setUsesScrollButtons(false);
        twModule->setDocumentMode(false);
        twModule->setTabsClosable(false);
        twModule->setMovable(false);
        twModule->setTabBarAutoHide(false);
        tGcodeEditor = new QWidget();
        tGcodeEditor->setObjectName(QString::fromUtf8("tGcodeEditor"));
        verticalLayout = new QVBoxLayout(tGcodeEditor);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(tGcodeEditor);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, -372, 450, 900));
        scrollAreaWidgetContents->setMinimumSize(QSize(450, 900));
        verticalLayout_10 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        gbAddGcode = new QGroupBox(scrollAreaWidgetContents);
        gbAddGcode->setObjectName(QString::fromUtf8("gbAddGcode"));
        verticalLayout_7 = new QVBoxLayout(gbAddGcode);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(-1, 20, -1, -1);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        cbGcode = new QComboBox(gbAddGcode);
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->addItem(QString());
        cbGcode->setObjectName(QString::fromUtf8("cbGcode"));
        cbGcode->setMinimumSize(QSize(60, 0));
        cbGcode->setLayoutDirection(Qt::LeftToRight);
        cbGcode->setAutoFillBackground(false);
        cbGcode->setIconSize(QSize(20, 20));
        cbGcode->setFrame(true);

        horizontalLayout_8->addWidget(cbGcode);

        lbAg1 = new QLabel(gbAddGcode);
        lbAg1->setObjectName(QString::fromUtf8("lbAg1"));
        lbAg1->setStyleSheet(QString::fromUtf8(""));
        lbAg1->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(lbAg1);

        leAg1 = new QLineEdit(gbAddGcode);
        leAg1->setObjectName(QString::fromUtf8("leAg1"));
        leAg1->setFont(font7);
        leAg1->setReadOnly(false);

        horizontalLayout_8->addWidget(leAg1);

        lbAg2 = new QLabel(gbAddGcode);
        lbAg2->setObjectName(QString::fromUtf8("lbAg2"));
        lbAg2->setStyleSheet(QString::fromUtf8(""));
        lbAg2->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(lbAg2);

        leAg2 = new QLineEdit(gbAddGcode);
        leAg2->setObjectName(QString::fromUtf8("leAg2"));
        leAg2->setReadOnly(false);

        horizontalLayout_8->addWidget(leAg2);

        lbAg3 = new QLabel(gbAddGcode);
        lbAg3->setObjectName(QString::fromUtf8("lbAg3"));
        lbAg3->setStyleSheet(QString::fromUtf8(""));
        lbAg3->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(lbAg3);

        leAg3 = new QLineEdit(gbAddGcode);
        leAg3->setObjectName(QString::fromUtf8("leAg3"));
        leAg3->setReadOnly(false);

        horizontalLayout_8->addWidget(leAg3);

        lbAg4 = new QLabel(gbAddGcode);
        lbAg4->setObjectName(QString::fromUtf8("lbAg4"));
        lbAg4->setStyleSheet(QString::fromUtf8(""));
        lbAg4->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(lbAg4);

        leAg4 = new QLineEdit(gbAddGcode);
        leAg4->setObjectName(QString::fromUtf8("leAg4"));
        leAg4->setReadOnly(false);

        horizontalLayout_8->addWidget(leAg4);

        lbAg5 = new QLabel(gbAddGcode);
        lbAg5->setObjectName(QString::fromUtf8("lbAg5"));
        lbAg5->setStyleSheet(QString::fromUtf8(""));
        lbAg5->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(lbAg5);

        leAg5 = new QLineEdit(gbAddGcode);
        leAg5->setObjectName(QString::fromUtf8("leAg5"));
        leAg5->setReadOnly(false);

        horizontalLayout_8->addWidget(leAg5);

        lbAg6 = new QLabel(gbAddGcode);
        lbAg6->setObjectName(QString::fromUtf8("lbAg6"));
        lbAg6->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_8->addWidget(lbAg6);

        leAg6 = new QLineEdit(gbAddGcode);
        leAg6->setObjectName(QString::fromUtf8("leAg6"));
        leAg6->setReadOnly(false);

        horizontalLayout_8->addWidget(leAg6);


        verticalLayout_7->addLayout(horizontalLayout_8);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pbAddGcode = new QPushButton(gbAddGcode);
        pbAddGcode->setObjectName(QString::fromUtf8("pbAddGcode"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("icon/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbAddGcode->setIcon(icon11);
        pbAddGcode->setAutoDefault(false);
        pbAddGcode->setFlat(false);

        horizontalLayout_9->addWidget(pbAddGcode);

        pbGcodeReference = new QPushButton(gbAddGcode);
        pbGcodeReference->setObjectName(QString::fromUtf8("pbGcodeReference"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("icon/Help_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbGcodeReference->setIcon(icon12);

        horizontalLayout_9->addWidget(pbGcodeReference);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer);


        verticalLayout_7->addLayout(horizontalLayout_9);


        verticalLayout_10->addWidget(gbAddGcode);

        gbVar = new QGroupBox(scrollAreaWidgetContents);
        gbVar->setObjectName(QString::fromUtf8("gbVar"));
        horizontalLayout_10 = new QHBoxLayout(gbVar);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(-1, 20, -1, -1);
        leVariable1 = new QLineEdit(gbVar);
        leVariable1->setObjectName(QString::fromUtf8("leVariable1"));

        horizontalLayout_10->addWidget(leVariable1);

        lbVar1 = new QLabel(gbVar);
        lbVar1->setObjectName(QString::fromUtf8("lbVar1"));
        lbVar1->setMinimumSize(QSize(20, 0));
        lbVar1->setStyleSheet(QString::fromUtf8(""));
        lbVar1->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lbVar1);

        leVariable2 = new QLineEdit(gbVar);
        leVariable2->setObjectName(QString::fromUtf8("leVariable2"));

        horizontalLayout_10->addWidget(leVariable2);

        lbVar2 = new QLabel(gbVar);
        lbVar2->setObjectName(QString::fromUtf8("lbVar2"));
        lbVar2->setMinimumSize(QSize(20, 0));
        lbVar2->setStyleSheet(QString::fromUtf8(""));
        lbVar2->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lbVar2);

        leVariable3 = new QLineEdit(gbVar);
        leVariable3->setObjectName(QString::fromUtf8("leVariable3"));

        horizontalLayout_10->addWidget(leVariable3);

        lbVar3 = new QLabel(gbVar);
        lbVar3->setObjectName(QString::fromUtf8("lbVar3"));
        lbVar3->setMinimumSize(QSize(20, 0));
        lbVar3->setStyleSheet(QString::fromUtf8(""));
        lbVar3->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lbVar3);

        leVariable4 = new QLineEdit(gbVar);
        leVariable4->setObjectName(QString::fromUtf8("leVariable4"));

        horizontalLayout_10->addWidget(leVariable4);

        lbVar4 = new QLabel(gbVar);
        lbVar4->setObjectName(QString::fromUtf8("lbVar4"));
        lbVar4->setMinimumSize(QSize(20, 0));
        lbVar4->setStyleSheet(QString::fromUtf8(""));
        lbVar4->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lbVar4);

        leVariable5 = new QLineEdit(gbVar);
        leVariable5->setObjectName(QString::fromUtf8("leVariable5"));

        horizontalLayout_10->addWidget(leVariable5);

        lbVar5 = new QLabel(gbVar);
        lbVar5->setObjectName(QString::fromUtf8("lbVar5"));
        lbVar5->setMinimumSize(QSize(20, 0));
        lbVar5->setStyleSheet(QString::fromUtf8(""));
        lbVar5->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lbVar5);

        leVariable6 = new QLineEdit(gbVar);
        leVariable6->setObjectName(QString::fromUtf8("leVariable6"));

        horizontalLayout_10->addWidget(leVariable6);

        lbVar6 = new QLabel(gbVar);
        lbVar6->setObjectName(QString::fromUtf8("lbVar6"));
        lbVar6->setMinimumSize(QSize(20, 0));
        lbVar6->setStyleSheet(QString::fromUtf8(""));
        lbVar6->setAlignment(Qt::AlignCenter);

        horizontalLayout_10->addWidget(lbVar6);


        verticalLayout_10->addWidget(gbVar);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        cbLockGcodeEditor = new QCheckBox(scrollAreaWidgetContents);
        cbLockGcodeEditor->setObjectName(QString::fromUtf8("cbLockGcodeEditor"));
        cbLockGcodeEditor->setFont(font7);

        horizontalLayout_11->addWidget(cbLockGcodeEditor);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_2);

        pbSaveGcode = new QPushButton(scrollAreaWidgetContents);
        pbSaveGcode->setObjectName(QString::fromUtf8("pbSaveGcode"));
        pbSaveGcode->setMinimumSize(QSize(80, 30));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8("icon/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSaveGcode->setIcon(icon13);
        pbSaveGcode->setIconSize(QSize(20, 20));

        horizontalLayout_11->addWidget(pbSaveGcode);


        verticalLayout_10->addLayout(horizontalLayout_11);

        pteGcodeArea = new CodeEditor(scrollAreaWidgetContents);
        pteGcodeArea->setObjectName(QString::fromUtf8("pteGcodeArea"));
        pteGcodeArea->setMinimumSize(QSize(310, 250));
        pteGcodeArea->setFont(font7);
        pteGcodeArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

        verticalLayout_10->addWidget(pteGcodeArea);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        pbFormat = new QPushButton(scrollAreaWidgetContents);
        pbFormat->setObjectName(QString::fromUtf8("pbFormat"));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("icon/index.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFormat->setIcon(icon14);
        pbFormat->setIconSize(QSize(30, 30));

        verticalLayout_8->addWidget(pbFormat);

        cbFormatColor = new QCheckBox(scrollAreaWidgetContents);
        cbFormatColor->setObjectName(QString::fromUtf8("cbFormatColor"));
        cbFormatColor->setChecked(true);

        verticalLayout_8->addWidget(cbFormatColor);

        cbAutoNumbering = new QCheckBox(scrollAreaWidgetContents);
        cbAutoNumbering->setObjectName(QString::fromUtf8("cbAutoNumbering"));
        cbAutoNumbering->setChecked(true);

        verticalLayout_8->addWidget(cbAutoNumbering);


        horizontalLayout_12->addLayout(verticalLayout_8);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_3);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        pbExecuteGcodes = new QPushButton(scrollAreaWidgetContents);
        pbExecuteGcodes->setObjectName(QString::fromUtf8("pbExecuteGcodes"));
        pbExecuteGcodes->setAutoFillBackground(false);
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("icon/Play_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon15.addFile(QString::fromUtf8("icon/Pause_96px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbExecuteGcodes->setIcon(icon15);
        pbExecuteGcodes->setIconSize(QSize(70, 70));
        pbExecuteGcodes->setCheckable(true);
        pbExecuteGcodes->setFlat(false);

        verticalLayout_9->addWidget(pbExecuteGcodes);

        cbPositionToExecuteGcode = new QComboBox(scrollAreaWidgetContents);
        cbPositionToExecuteGcode->addItem(QString());
        cbPositionToExecuteGcode->addItem(QString());
        cbPositionToExecuteGcode->setObjectName(QString::fromUtf8("cbPositionToExecuteGcode"));
        QFont font8;
        font8.setPointSize(6);
        font8.setBold(false);
        font8.setWeight(50);
        font8.setKerning(true);
        cbPositionToExecuteGcode->setFont(font8);

        verticalLayout_9->addWidget(cbPositionToExecuteGcode);


        horizontalLayout_12->addLayout(verticalLayout_9);


        verticalLayout_10->addLayout(horizontalLayout_12);

        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        saProgramFiles = new QScrollArea(tab);
        saProgramFiles->setObjectName(QString::fromUtf8("saProgramFiles"));
        saProgramFiles->setEnabled(true);
        saProgramFiles->setGeometry(QRect(85, 15, 256, 236));
        saProgramFiles->setMinimumSize(QSize(240, 140));
        saProgramFiles->setStyleSheet(QString::fromUtf8(""));
        saProgramFiles->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        saProgramFiles->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        saProgramFiles->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        saProgramFiles->setWidgetResizable(false);
        wgProgramContainer = new QWidget();
        wgProgramContainer->setObjectName(QString::fromUtf8("wgProgramContainer"));
        wgProgramContainer->setGeometry(QRect(0, 0, 279, 589));
        frExProgram = new QFrame(wgProgramContainer);
        frExProgram->setObjectName(QString::fromUtf8("frExProgram"));
        frExProgram->setGeometry(QRect(5, 10, 221, 61));
        frExProgram->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border-radius: 2px;\n"
"border: 1px solid rgb(50, 50, 50)\n"
"}\n"
"\n"
"QLabel{\n"
"border: none\n"
"}"));
        frExProgram->setFrameShape(QFrame::StyledPanel);
        frExProgram->setFrameShadow(QFrame::Raised);
        leExProgramName = new QLineEdit(frExProgram);
        leExProgramName->setObjectName(QString::fromUtf8("leExProgramName"));
        leExProgramName->setEnabled(true);
        leExProgramName->setGeometry(QRect(10, 5, 160, 30));
        leExProgramName->setFont(font4);
        leExProgramName->setCursor(QCursor(Qt::SizeHorCursor));
        leExProgramName->setStyleSheet(QString::fromUtf8(""));
        pbExDeleteProgram = new QPushButton(frExProgram);
        pbExDeleteProgram->setObjectName(QString::fromUtf8("pbExDeleteProgram"));
        pbExDeleteProgram->setGeometry(QRect(180, 5, 30, 31));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbExDeleteProgram->setIcon(icon16);
        pbExDeleteProgram->setIconSize(QSize(30, 30));
        pbExDeleteProgram->setAutoDefault(false);
        pbExDeleteProgram->setFlat(true);
        lbExGCodeNumber = new QLabel(frExProgram);
        lbExGCodeNumber->setObjectName(QString::fromUtf8("lbExGCodeNumber"));
        lbExGCodeNumber->setGeometry(QRect(10, 40, 101, 16));
        lbExGCodeNumber->setStyleSheet(QString::fromUtf8(""));
        saProgramFiles->setWidget(wgProgramContainer);
        layoutWidget4 = new QWidget(tab);
        layoutWidget4->setObjectName(QString::fromUtf8("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(355, 15, 71, 91));
        verticalLayout_13 = new QVBoxLayout(layoutWidget4);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        pbUploadProgram = new QPushButton(layoutWidget4);
        pbUploadProgram->setObjectName(QString::fromUtf8("pbUploadProgram"));
        pbUploadProgram->setMinimumSize(QSize(40, 40));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8("icon/icons8-upload-to-cloud-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbUploadProgram->setIcon(icon17);
        pbUploadProgram->setIconSize(QSize(32, 32));
        pbUploadProgram->setFlat(false);

        verticalLayout_13->addWidget(pbUploadProgram);

        pbImportGcodeFiles = new QPushButton(layoutWidget4);
        pbImportGcodeFiles->setObjectName(QString::fromUtf8("pbImportGcodeFiles"));
        pbImportGcodeFiles->setMinimumSize(QSize(40, 40));
        pbImportGcodeFiles->setIconSize(QSize(32, 32));
        pbImportGcodeFiles->setFlat(false);

        verticalLayout_13->addWidget(pbImportGcodeFiles);

        layoutWidget5 = new QWidget(tab);
        layoutWidget5->setObjectName(QString::fromUtf8("layoutWidget5"));
        layoutWidget5->setGeometry(QRect(5, 15, 66, 183));
        verticalLayout_14 = new QVBoxLayout(layoutWidget5);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        pbAddNewProgram = new QPushButton(layoutWidget5);
        pbAddNewProgram->setObjectName(QString::fromUtf8("pbAddNewProgram"));
        pbAddNewProgram->setMinimumSize(QSize(40, 40));
        pbAddNewProgram->setIcon(icon11);
        pbAddNewProgram->setIconSize(QSize(16, 16));
        pbAddNewProgram->setFlat(false);

        verticalLayout_14->addWidget(pbAddNewProgram);

        pbRefreshGcodeFiles = new QPushButton(layoutWidget5);
        pbRefreshGcodeFiles->setObjectName(QString::fromUtf8("pbRefreshGcodeFiles"));
        pbRefreshGcodeFiles->setMinimumSize(QSize(40, 40));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8("icon/Restart_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRefreshGcodeFiles->setIcon(icon18);
        pbRefreshGcodeFiles->setIconSize(QSize(16, 16));
        pbRefreshGcodeFiles->setFlat(false);

        verticalLayout_14->addWidget(pbRefreshGcodeFiles);

        pbFindGcodeFile = new QPushButton(layoutWidget5);
        pbFindGcodeFile->setObjectName(QString::fromUtf8("pbFindGcodeFile"));
        pbFindGcodeFile->setMinimumSize(QSize(40, 40));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8("icon/Search_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFindGcodeFile->setIcon(icon19);
        pbFindGcodeFile->setIconSize(QSize(16, 16));
        pbFindGcodeFile->setFlat(false);

        verticalLayout_14->addWidget(pbFindGcodeFile);

        pbSortGcodeFiles = new QPushButton(layoutWidget5);
        pbSortGcodeFiles->setObjectName(QString::fromUtf8("pbSortGcodeFiles"));
        pbSortGcodeFiles->setMinimumSize(QSize(40, 40));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8("icon/Sort_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSortGcodeFiles->setIcon(icon20);
        pbSortGcodeFiles->setIconSize(QSize(16, 16));
        pbSortGcodeFiles->setFlat(false);

        verticalLayout_14->addWidget(pbSortGcodeFiles);

        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        listWidget = new QListWidget(tab_3);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(5, 10, 171, 136));
        textEdit = new QTextEdit(tab_3);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(185, 10, 166, 91));
        pbUploadProgram_2 = new QPushButton(tab_3);
        pbUploadProgram_2->setObjectName(QString::fromUtf8("pbUploadProgram_2"));
        pbUploadProgram_2->setGeometry(QRect(185, 110, 56, 36));
        QIcon icon21;
        icon21.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/icons8-download-from-cloud-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbUploadProgram_2->setIcon(icon21);
        pbUploadProgram_2->setIconSize(QSize(32, 32));
        pbUploadProgram_2->setFlat(false);
        tabWidget->addTab(tab_3, QString());

        verticalLayout_10->addWidget(tabWidget);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        twModule->addTab(tGcodeEditor, QString());
        tResultCameraArea = new QWidget();
        tResultCameraArea->setObjectName(QString::fromUtf8("tResultCameraArea"));
        groupBox = new QGroupBox(tResultCameraArea);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(235, 5, 91, 216));
        lbTrackingObject = new QLabel(groupBox);
        lbTrackingObject->setObjectName(QString::fromUtf8("lbTrackingObject"));
        lbTrackingObject->setGeometry(QRect(10, 105, 66, 36));
        lbTrackingObject->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230)"));
        pbObjectRect = new QPushButton(groupBox);
        pbObjectRect->setObjectName(QString::fromUtf8("pbObjectRect"));
        pbObjectRect->setGeometry(QRect(5, 180, 81, 31));
        pbObjectRect->setStyleSheet(QString::fromUtf8(""));
        QIcon icon22;
        icon22.addFile(QString::fromUtf8("icon/Rectangle_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbObjectRect->setIcon(icon22);
        leLRec = new QLineEdit(groupBox);
        leLRec->setObjectName(QString::fromUtf8("leLRec"));
        leLRec->setGeometry(QRect(25, 50, 31, 22));
        leWRec = new QLineEdit(groupBox);
        leWRec->setObjectName(QString::fromUtf8("leWRec"));
        leWRec->setGeometry(QRect(25, 25, 31, 22));
        leHRec = new QLineEdit(groupBox);
        leHRec->setObjectName(QString::fromUtf8("leHRec"));
        leHRec->setGeometry(QRect(25, 75, 31, 22));
        label_42 = new QLabel(groupBox);
        label_42->setObjectName(QString::fromUtf8("label_42"));
        label_42->setGeometry(QRect(10, 30, 26, 16));
        label_43 = new QLabel(groupBox);
        label_43->setObjectName(QString::fromUtf8("label_43"));
        label_43->setGeometry(QRect(10, 55, 26, 16));
        label_44 = new QLabel(groupBox);
        label_44->setObjectName(QString::fromUtf8("label_44"));
        label_44->setGeometry(QRect(10, 80, 26, 16));
        label_54 = new QLabel(groupBox);
        label_54->setObjectName(QString::fromUtf8("label_54"));
        label_54->setGeometry(QRect(60, 30, 31, 16));
        label_55 = new QLabel(groupBox);
        label_55->setObjectName(QString::fromUtf8("label_55"));
        label_55->setGeometry(QRect(60, 55, 31, 16));
        label_56 = new QLabel(groupBox);
        label_56->setObjectName(QString::fromUtf8("label_56"));
        label_56->setGeometry(QRect(60, 80, 31, 16));
        cbObjectType = new QComboBox(groupBox);
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->setObjectName(QString::fromUtf8("cbObjectType"));
        cbObjectType->setEnabled(false);
        cbObjectType->setGeometry(QRect(10, 150, 71, 22));
        groupBox_7 = new QGroupBox(tResultCameraArea);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(405, 360, 71, 166));
        leConvenyorSpeed = new QLineEdit(groupBox_7);
        leConvenyorSpeed->setObjectName(QString::fromUtf8("leConvenyorSpeed"));
        leConvenyorSpeed->setGeometry(QRect(15, 75, 41, 27));
        label_45 = new QLabel(groupBox_7);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setGeometry(QRect(15, 25, 46, 16));
        label_45->setFont(font7);
        cbConveyorDirection = new QComboBox(groupBox_7);
        cbConveyorDirection->addItem(QString());
        cbConveyorDirection->addItem(QString());
        cbConveyorDirection->setObjectName(QString::fromUtf8("cbConveyorDirection"));
        cbConveyorDirection->setGeometry(QRect(10, 135, 46, 22));
        label_47 = new QLabel(groupBox_7);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setGeometry(QRect(10, 110, 56, 16));
        label_47->setFont(font7);
        label_49 = new QLabel(groupBox_7);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setGeometry(QRect(15, 45, 46, 16));
        label_49->setFont(font7);
        groupBox_8 = new QGroupBox(tResultCameraArea);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(5, 90, 221, 131));
        pbObjectLine = new QPushButton(groupBox_8);
        pbObjectLine->setObjectName(QString::fromUtf8("pbObjectLine"));
        pbObjectLine->setGeometry(QRect(5, 25, 101, 31));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8("icon/Width_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbObjectLine->setIcon(icon23);
        leRealDistance = new QLineEdit(groupBox_8);
        leRealDistance->setObjectName(QString::fromUtf8("leRealDistance"));
        leRealDistance->setGeometry(QRect(135, 30, 31, 22));
        leYCoordinate = new QLineEdit(groupBox_8);
        leYCoordinate->setObjectName(QString::fromUtf8("leYCoordinate"));
        leYCoordinate->setGeometry(QRect(185, 65, 31, 22));
        pbObjectOrigin = new QPushButton(groupBox_8);
        pbObjectOrigin->setObjectName(QString::fromUtf8("pbObjectOrigin"));
        pbObjectOrigin->setGeometry(QRect(5, 60, 101, 31));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8("icon/Scatter Plot_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbObjectOrigin->setIcon(icon24);
        leXCoordinate = new QLineEdit(groupBox_8);
        leXCoordinate->setObjectName(QString::fromUtf8("leXCoordinate"));
        leXCoordinate->setGeometry(QRect(135, 65, 31, 22));
        label_38 = new QLabel(groupBox_8);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(120, 70, 21, 16));
        QFont font9;
        font9.setBold(false);
        font9.setItalic(false);
        font9.setUnderline(false);
        font9.setWeight(50);
        font9.setStrikeOut(false);
        font9.setKerning(true);
        label_38->setFont(font9);
        label_38->setMouseTracking(true);
        label_38->setTextFormat(Qt::AutoText);
        label_39 = new QLabel(groupBox_8);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(175, 65, 21, 21));
        label_40 = new QLabel(groupBox_8);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(175, 35, 31, 16));
        pbChangeXAxis = new QPushButton(groupBox_8);
        pbChangeXAxis->setObjectName(QString::fromUtf8("pbChangeXAxis"));
        pbChangeXAxis->setGeometry(QRect(5, 95, 101, 31));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8("icon/Arrow Pointing Down_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon25.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/Right Arrow_16px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbChangeXAxis->setIcon(icon25);
        pbChangeXAxis->setCheckable(true);
        cbDisplayCalibInfo = new QCheckBox(groupBox_8);
        cbDisplayCalibInfo->setObjectName(QString::fromUtf8("cbDisplayCalibInfo"));
        cbDisplayCalibInfo->setGeometry(QRect(115, 105, 71, 16));
        cbDisplayCalibInfo->setChecked(true);
        groupBox_9 = new QGroupBox(tResultCameraArea);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setEnabled(true);
        groupBox_9->setGeometry(QRect(5, 5, 221, 81));
        pbLoadCamera = new QPushButton(groupBox_9);
        pbLoadCamera->setObjectName(QString::fromUtf8("pbLoadCamera"));
        pbLoadCamera->setGeometry(QRect(35, 20, 46, 31));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8("icon/webcam.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon26.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/stop.png"), QSize(), QIcon::Normal, QIcon::On);
        pbLoadCamera->setIcon(icon26);
        pbLoadCamera->setCheckable(true);
        pbLoadTestImage = new QPushButton(groupBox_9);
        pbLoadTestImage->setObjectName(QString::fromUtf8("pbLoadTestImage"));
        pbLoadTestImage->setGeometry(QRect(165, 20, 46, 31));
        QIcon icon27;
        icon27.addFile(QString::fromUtf8("icon/image.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLoadTestImage->setIcon(icon27);
        label_11 = new QLabel(groupBox_9);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(90, 55, 31, 16));
        leFPS = new QLineEdit(groupBox_9);
        leFPS->setObjectName(QString::fromUtf8("leFPS"));
        leFPS->setGeometry(QRect(35, 55, 46, 16));
        leFPS->setAlignment(Qt::AlignCenter);
        pbPlayPauseCamera = new QPushButton(groupBox_9);
        pbPlayPauseCamera->setObjectName(QString::fromUtf8("pbPlayPauseCamera"));
        pbPlayPauseCamera->setGeometry(QRect(90, 25, 21, 21));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8("icon/icons8-play-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon28.addFile(QString::fromUtf8("icon/icons8-pause-48.png"), QSize(), QIcon::Normal, QIcon::On);
        icon28.addFile(QString::fromUtf8("icon/icons8-play-48.png"), QSize(), QIcon::Selected, QIcon::Off);
        pbPlayPauseCamera->setIcon(icon28);
        pbPlayPauseCamera->setIconSize(QSize(15, 15));
        pbPlayPauseCamera->setCheckable(true);
        pbPlayPauseCamera->setChecked(false);
        pbPlayPauseCamera->setFlat(false);
        pbCaptureCamera = new QPushButton(groupBox_9);
        pbCaptureCamera->setObjectName(QString::fromUtf8("pbCaptureCamera"));
        pbCaptureCamera->setGeometry(QRect(115, 20, 36, 36));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8("icon/icons8-screenshot-40.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCaptureCamera->setIcon(icon29);
        pbCaptureCamera->setIconSize(QSize(30, 30));
        pbCaptureCamera->setCheckable(false);
        pbCaptureCamera->setChecked(false);
        pbCaptureCamera->setFlat(true);
        pbLoadCameraSetting = new QPushButton(groupBox_9);
        pbLoadCameraSetting->setObjectName(QString::fromUtf8("pbLoadCameraSetting"));
        pbLoadCameraSetting->setGeometry(QRect(190, 55, 21, 21));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8("icon/icons8-load-resume-template-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLoadCameraSetting->setIcon(icon30);
        pbLoadCameraSetting->setIconSize(QSize(15, 15));
        pbLoadCameraSetting->setCheckable(true);
        pbLoadCameraSetting->setChecked(false);
        pbLoadCameraSetting->setFlat(false);
        pbSaveCameraSetting = new QPushButton(groupBox_9);
        pbSaveCameraSetting->setObjectName(QString::fromUtf8("pbSaveCameraSetting"));
        pbSaveCameraSetting->setGeometry(QRect(165, 55, 21, 21));
        QIcon icon31;
        icon31.addFile(QString::fromUtf8("icon/icons8-save-64.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSaveCameraSetting->setIcon(icon31);
        pbSaveCameraSetting->setIconSize(QSize(15, 15));
        pbSaveCameraSetting->setCheckable(true);
        pbSaveCameraSetting->setChecked(false);
        pbSaveCameraSetting->setFlat(false);
        lbCameraState = new QLabel(groupBox_9);
        lbCameraState->setObjectName(QString::fromUtf8("lbCameraState"));
        lbCameraState->setEnabled(false);
        lbCameraState->setGeometry(QRect(10, 30, 15, 15));
        lbCameraState->setPixmap(QPixmap(QString::fromUtf8("icon/icons8-connection-status-on-48.png")));
        lbCameraState->setScaledContents(true);
        groupBox_10 = new QGroupBox(tResultCameraArea);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(335, 5, 131, 136));
        groupBox_10->setStyleSheet(QString::fromUtf8(""));
        pbViewDataObjects = new QPushButton(groupBox_10);
        pbViewDataObjects->setObjectName(QString::fromUtf8("pbViewDataObjects"));
        pbViewDataObjects->setGeometry(QRect(5, 20, 121, 31));
        pbViewDataObjects->setStyleSheet(QString::fromUtf8(""));
        QIcon icon32;
        icon32.addFile(QString::fromUtf8("icon/icons8-object-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbViewDataObjects->setIcon(icon32);
        pbClearDetectObjects = new QPushButton(groupBox_10);
        pbClearDetectObjects->setObjectName(QString::fromUtf8("pbClearDetectObjects"));
        pbClearDetectObjects->setGeometry(QRect(5, 55, 121, 31));
        QIcon icon33;
        icon33.addFile(QString::fromUtf8("icon/Eraser_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbClearDetectObjects->setIcon(icon33);
        label_50 = new QLabel(groupBox_10);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setGeometry(QRect(15, 115, 51, 16));
        label_50->setFont(font7);
        label_48 = new QLabel(groupBox_10);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setGeometry(QRect(15, 90, 51, 16));
        label_48->setFont(font7);
        lbTrackingObjectNumber = new QLabel(groupBox_10);
        lbTrackingObjectNumber->setObjectName(QString::fromUtf8("lbTrackingObjectNumber"));
        lbTrackingObjectNumber->setGeometry(QRect(90, 90, 31, 16));
        QFont font10;
        font10.setPointSize(10);
        font10.setBold(false);
        font10.setWeight(50);
        font10.setKerning(true);
        lbTrackingObjectNumber->setFont(font10);
        lbVisibleObjectNumber = new QLabel(groupBox_10);
        lbVisibleObjectNumber->setObjectName(QString::fromUtf8("lbVisibleObjectNumber"));
        lbVisibleObjectNumber->setGeometry(QRect(90, 115, 31, 16));
        lbVisibleObjectNumber->setFont(font10);
        pbFilter = new QPushButton(tResultCameraArea);
        pbFilter->setObjectName(QString::fromUtf8("pbFilter"));
        pbFilter->setGeometry(QRect(410, 225, 61, 36));
        QIcon icon34;
        icon34.addFile(QString::fromUtf8("icon/Slider 2_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFilter->setIcon(icon34);
        pbTransformPerspective = new QPushButton(tResultCameraArea);
        pbTransformPerspective->setObjectName(QString::fromUtf8("pbTransformPerspective"));
        pbTransformPerspective->setGeometry(QRect(335, 145, 91, 31));
        pbTransformPerspective->setAutoFillBackground(false);
        pbTransformPerspective->setIcon(icon7);
        pbTransformPerspective->setCheckable(true);
        pbTransformPerspective->setChecked(false);
        pbTransformPerspective->setAutoDefault(false);
        pbTransformPerspective->setFlat(false);
        saCamera = new QScrollArea(tResultCameraArea);
        saCamera->setObjectName(QString::fromUtf8("saCamera"));
        saCamera->setGeometry(QRect(5, 225, 400, 300));
        saCamera->setStyleSheet(QString::fromUtf8(""));
        saCamera->setWidgetResizable(false);
        saCameraArea = new QWidget();
        saCameraArea->setObjectName(QString::fromUtf8("saCameraArea"));
        saCameraArea->setGeometry(QRect(0, 0, 400, 300));
        saCameraArea->setStyleSheet(QString::fromUtf8(""));
        lbScreenStreamer = new CameraWidget(saCameraArea);
        lbScreenStreamer->setObjectName(QString::fromUtf8("lbScreenStreamer"));
        lbScreenStreamer->setGeometry(QRect(0, 0, 400, 300));
        lbScreenStreamer->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230)"));
        lbScreenStreamer->setScaledContents(false);
        lbScreenStreamer->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        saCamera->setWidget(saCameraArea);
        pbExpandCameraWidget = new QPushButton(tResultCameraArea);
        pbExpandCameraWidget->setObjectName(QString::fromUtf8("pbExpandCameraWidget"));
        pbExpandCameraWidget->setGeometry(QRect(430, 185, 36, 31));
        QIcon icon35;
        icon35.addFile(QString::fromUtf8("icon/icons8-expand-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbExpandCameraWidget->setIcon(icon35);
        pbExpandCameraWidget->setCheckable(true);
        pbExpandCameraWidget->setChecked(false);
        pbCameraWindowMode = new QPushButton(tResultCameraArea);
        pbCameraWindowMode->setObjectName(QString::fromUtf8("pbCameraWindowMode"));
        pbCameraWindowMode->setGeometry(QRect(430, 145, 36, 31));
        QIcon icon36;
        icon36.addFile(QString::fromUtf8("icon/icons8-maximize-window-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCameraWindowMode->setIcon(icon36);
        lbCameraLayer = new QComboBox(tResultCameraArea);
        lbCameraLayer->addItem(QString());
        lbCameraLayer->addItem(QString());
        lbCameraLayer->addItem(QString());
        lbCameraLayer->setObjectName(QString::fromUtf8("lbCameraLayer"));
        lbCameraLayer->setGeometry(QRect(335, 185, 91, 31));
        twModule->addTab(tResultCameraArea, QString());
        tDrawing = new QWidget();
        tDrawing->setObjectName(QString::fromUtf8("tDrawing"));
        lbImageForDrawing = new QLabel(tDrawing);
        lbImageForDrawing->setObjectName(QString::fromUtf8("lbImageForDrawing"));
        lbImageForDrawing->setGeometry(QRect(10, 10, 246, 131));
        lbImageForDrawing->setStyleSheet(QString::fromUtf8("background-color: rgb(142, 254, 255);"));
        lbDrawingArea = new DrawingWidget(tDrawing);
        lbDrawingArea->setObjectName(QString::fromUtf8("lbDrawingArea"));
        lbDrawingArea->setGeometry(QRect(10, 154, 381, 380));
        lbDrawingArea->setStyleSheet(QString::fromUtf8("background-color: rgb(142, 254, 255);"));
        lbDrawingArea->setScaledContents(true);
        widget_2 = new QWidget(tDrawing);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(310, 10, 151, 21));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(171, 225, 224);"));
        leDrawingThreshold = new QLineEdit(widget_2);
        leDrawingThreshold->setObjectName(QString::fromUtf8("leDrawingThreshold"));
        leDrawingThreshold->setGeometry(QRect(125, 4, 23, 15));
        leDrawingThreshold->setFont(font8);
        hsDrawingThreshold = new QSlider(widget_2);
        hsDrawingThreshold->setObjectName(QString::fromUtf8("hsDrawingThreshold"));
        hsDrawingThreshold->setGeometry(QRect(5, 4, 111, 16));
        hsDrawingThreshold->setMaximum(255);
        hsDrawingThreshold->setSingleStep(1);
        hsDrawingThreshold->setValue(150);
        hsDrawingThreshold->setOrientation(Qt::Horizontal);
        widget_3 = new QWidget(tDrawing);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(215, 105, 37, 31));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(221, 221, 221);"));
        lbImageWidth = new QLabel(widget_3);
        lbImageWidth->setObjectName(QString::fromUtf8("lbImageWidth"));
        lbImageWidth->setGeometry(QRect(2, 0, 39, 14));
        lbImageWidth->setFont(font8);
        lbImageWidth->setStyleSheet(QString::fromUtf8(""));
        lbImageHeight = new QLabel(widget_3);
        lbImageHeight->setObjectName(QString::fromUtf8("lbImageHeight"));
        lbImageHeight->setGeometry(QRect(2, 14, 35, 14));
        lbImageHeight->setFont(font8);
        lbImageHeight->setStyleSheet(QString::fromUtf8(""));
        widget_4 = new QWidget(tDrawing);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(265, 90, 43, 51));
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_18 = new QLabel(widget_4);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(4, 5, 37, 16));
        label_18->setFont(font8);
        leHeightScale = new QLineEdit(widget_4);
        leHeightScale->setObjectName(QString::fromUtf8("leHeightScale"));
        leHeightScale->setGeometry(QRect(4, 25, 35, 18));
        widget_5 = new QWidget(tDrawing);
        widget_5->setObjectName(QString::fromUtf8("widget_5"));
        widget_5->setGeometry(QRect(310, 90, 43, 51));
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_20 = new QLabel(widget_5);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(4, 5, 37, 16));
        label_20->setFont(font8);
        leWidthScale = new QLineEdit(widget_5);
        leWidthScale->setObjectName(QString::fromUtf8("leWidthScale"));
        leWidthScale->setGeometry(QRect(4, 25, 35, 18));
        widget_6 = new QWidget(tDrawing);
        widget_6->setObjectName(QString::fromUtf8("widget_6"));
        widget_6->setGeometry(QRect(355, 90, 39, 51));
        widget_6->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_23 = new QLabel(widget_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(2, 5, 35, 16));
        label_23->setFont(font8);
        label_23->setAlignment(Qt::AlignCenter);
        leSpace = new QLineEdit(widget_6);
        leSpace->setObjectName(QString::fromUtf8("leSpace"));
        leSpace->setGeometry(QRect(4, 25, 31, 18));
        pbDrawLine = new QPushButton(tDrawing);
        pbDrawLine->setObjectName(QString::fromUtf8("pbDrawLine"));
        pbDrawLine->setGeometry(QRect(400, 326, 28, 28));
        QIcon icon37;
        icon37.addFile(QString::fromUtf8("icon/Line_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawLine->setIcon(icon37);
        pbDrawRectangle = new QPushButton(tDrawing);
        pbDrawRectangle->setObjectName(QString::fromUtf8("pbDrawRectangle"));
        pbDrawRectangle->setGeometry(QRect(430, 326, 28, 28));
        QIcon icon38;
        icon38.addFile(QString::fromUtf8("icon/Rectangular_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawRectangle->setIcon(icon38);
        pbDrawArc = new QPushButton(tDrawing);
        pbDrawArc->setObjectName(QString::fromUtf8("pbDrawArc"));
        pbDrawArc->setGeometry(QRect(400, 356, 28, 28));
        QIcon icon39;
        icon39.addFile(QString::fromUtf8("icon/Circled Notch_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawArc->setIcon(icon39);
        pbDrawCircle = new QPushButton(tDrawing);
        pbDrawCircle->setObjectName(QString::fromUtf8("pbDrawCircle"));
        pbDrawCircle->setGeometry(QRect(430, 356, 28, 28));
        QIcon icon40;
        icon40.addFile(QString::fromUtf8("icon/Circle_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawCircle->setIcon(icon40);
        widget_7 = new QWidget(tDrawing);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setGeometry(QRect(405, 152, 53, 31));
        widget_7->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_19 = new QLabel(widget_7);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg1 = new QLineEdit(widget_7);
        leDrawAg1->setObjectName(QString::fromUtf8("leDrawAg1"));
        leDrawAg1->setGeometry(QRect(16, 6, 33, 22));
        widget_8 = new QWidget(tDrawing);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setGeometry(QRect(405, 186, 53, 31));
        widget_8->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_22 = new QLabel(widget_8);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg2 = new QLineEdit(widget_8);
        leDrawAg2->setObjectName(QString::fromUtf8("leDrawAg2"));
        leDrawAg2->setGeometry(QRect(16, 6, 33, 22));
        widget_9 = new QWidget(tDrawing);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setGeometry(QRect(405, 220, 53, 31));
        widget_9->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_24 = new QLabel(widget_9);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg3 = new QLineEdit(widget_9);
        leDrawAg3->setObjectName(QString::fromUtf8("leDrawAg3"));
        leDrawAg3->setGeometry(QRect(16, 6, 33, 22));
        widget_10 = new QWidget(tDrawing);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        widget_10->setGeometry(QRect(405, 254, 53, 31));
        widget_10->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_25 = new QLabel(widget_10);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setGeometry(QRect(2, 8, 16, 16));
        label_25->setFont(font7);
        leDrawAg4 = new QLineEdit(widget_10);
        leDrawAg4->setObjectName(QString::fromUtf8("leDrawAg4"));
        leDrawAg4->setGeometry(QRect(16, 6, 33, 22));
        widget_11 = new QWidget(tDrawing);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        widget_11->setGeometry(QRect(405, 288, 53, 31));
        widget_11->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        label_26 = new QLabel(widget_11);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        label_26->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg5 = new QLineEdit(widget_11);
        leDrawAg5->setObjectName(QString::fromUtf8("leDrawAg5"));
        leDrawAg5->setGeometry(QRect(16, 6, 33, 22));
        pbOpenPicture = new QPushButton(tDrawing);
        pbOpenPicture->setObjectName(QString::fromUtf8("pbOpenPicture"));
        pbOpenPicture->setGeometry(QRect(265, 10, 29, 21));
        QIcon icon41;
        icon41.addFile(QString::fromUtf8("icon/Full Image_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenPicture->setIcon(icon41);
        pbExportDrawingGcodes = new QPushButton(tDrawing);
        pbExportDrawingGcodes->setObjectName(QString::fromUtf8("pbExportDrawingGcodes"));
        pbExportDrawingGcodes->setGeometry(QRect(399, 485, 61, 46));
        pbPainting = new QPushButton(tDrawing);
        pbPainting->setObjectName(QString::fromUtf8("pbPainting"));
        pbPainting->setGeometry(QRect(400, 90, 61, 37));
        QIcon icon42;
        icon42.addFile(QString::fromUtf8("icon/Paint_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPainting->setIcon(icon42);
        pbPainting->setIconSize(QSize(20, 20));
        pbZoomIn = new QPushButton(tDrawing);
        pbZoomIn->setObjectName(QString::fromUtf8("pbZoomIn"));
        pbZoomIn->setGeometry(QRect(400, 386, 28, 28));
        QIcon icon43;
        icon43.addFile(QString::fromUtf8("icon/Zoom In_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomIn->setIcon(icon43);
        pbZoomOut = new QPushButton(tDrawing);
        pbZoomOut->setObjectName(QString::fromUtf8("pbZoomOut"));
        pbZoomOut->setGeometry(QRect(430, 386, 28, 28));
        QIcon icon44;
        icon44.addFile(QString::fromUtf8("icon/Zoom Out_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomOut->setIcon(icon44);
        label_21 = new QLabel(tDrawing);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(316, 505, 39, 16));
        pbCursor = new QPushButton(tDrawing);
        pbCursor->setObjectName(QString::fromUtf8("pbCursor"));
        pbCursor->setGeometry(QRect(430, 415, 28, 28));
        QIcon icon45;
        icon45.addFile(QString::fromUtf8("icon/Cursor-color_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCursor->setIcon(icon45);
        cbDrawingEffector = new QComboBox(tDrawing);
        cbDrawingEffector->addItem(QString());
        cbDrawingEffector->addItem(QString());
        cbDrawingEffector->setObjectName(QString::fromUtf8("cbDrawingEffector"));
        cbDrawingEffector->setGeometry(QRect(399, 455, 61, 22));
        widget_12 = new QWidget(tDrawing);
        widget_12->setObjectName(QString::fromUtf8("widget_12"));
        widget_12->setGeometry(QRect(265, 36, 69, 48));
        widget_12->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        cbDrawMethod = new QComboBox(widget_12);
        cbDrawMethod->addItem(QString());
        cbDrawMethod->addItem(QString());
        cbDrawMethod->setObjectName(QString::fromUtf8("cbDrawMethod"));
        cbDrawMethod->setGeometry(QRect(6, 20, 59, 22));
        label_13 = new QLabel(widget_12);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(8, 2, 55, 16));
        label_13->setFont(font8);
        widget_13 = new QWidget(tDrawing);
        widget_13->setObjectName(QString::fromUtf8("widget_13"));
        widget_13->setGeometry(QRect(340, 36, 123, 48));
        widget_13->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        cbConversionTool = new QComboBox(widget_13);
        cbConversionTool->addItem(QString());
        cbConversionTool->addItem(QString());
        cbConversionTool->addItem(QString());
        cbConversionTool->setObjectName(QString::fromUtf8("cbConversionTool"));
        cbConversionTool->setGeometry(QRect(6, 20, 113, 22));
        label_14 = new QLabel(widget_13);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(26, 2, 95, 16));
        label_14->setFont(font8);
        twModule->addTab(tDrawing, QString());
        splitter->addWidget(twModule);

        verticalLayout_15->addWidget(splitter);


        verticalLayout_16->addLayout(verticalLayout_15);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 26));
        menuBar->setStyleSheet(QString::fromUtf8("QMenuBar\n"
"{\n"
"background-color: rgb(41, 155, 255);\n"
"color: rgb(255, 255, 255);\n"
"}\n"
"QMenuBar:selected\n"
"{\n"
"color: rgb(72, 72, 72);\n"
"}\n"
"QMenu\n"
"{\n"
"background-color: rgb(41, 155, 255);\n"
"color: rgb(255, 255, 255);\n"
"selection-color: rgb(255, 255, 255);\n"
"selection-background-color: rgb(0, 204, 204);\n"
"}\n"
""));
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuReferences = new QMenu(menuHelp);
        menuReferences->setObjectName(QString::fromUtf8("menuReferences"));
        menuEditor = new QMenu(menuBar);
        menuEditor->setObjectName(QString::fromUtf8("menuEditor"));
        menuExecute = new QMenu(menuEditor);
        menuExecute->setObjectName(QString::fromUtf8("menuExecute"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        menuSetting->setStyleSheet(QString::fromUtf8(""));
        menuConnection = new QMenu(menuSetting);
        menuConnection->setObjectName(QString::fromUtf8("menuConnection"));
        menuUI = new QMenu(menuSetting);
        menuUI->setObjectName(QString::fromUtf8("menuUI"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menuSetting->menuAction());
        menuBar->addAction(menuEditor->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(menuReferences->menuAction());
        menuHelp->addAction(actionAbout);
        menuReferences->addAction(actionGcode);
        menuReferences->addAction(actionSoftware);
        menuEditor->addSeparator();
        menuEditor->addAction(menuExecute->menuAction());
        menuExecute->addAction(actionExecute);
        menuExecute->addAction(actionExecute_All);
        menuExecute->addSeparator();
        menuExecute->addAction(actionDelta_X_1);
        menuSetting->addAction(menuConnection->menuAction());
        menuSetting->addAction(menuUI->menuAction());
        menuConnection->addAction(actionBaudrate);
        menuUI->addAction(actionScale);

        retranslateUi(MainWindow);

        twDeltaManager->setCurrentIndex(0);
        twDeltaGeometry->setCurrentIndex(0);
        cbDivision->setCurrentIndex(1);
        pbPump->setDefault(false);
        pbLaser->setDefault(false);
        pbGrip->setDefault(false);
        twConveyor->setCurrentIndex(2);
        twModule->setCurrentIndex(0);
        pbAddGcode->setDefault(false);
        tabWidget->setCurrentIndex(0);
        pbExDeleteProgram->setDefault(true);
        pbTransformPerspective->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "IMWI - Delta X Software - Version 0.9.5", nullptr));
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
        twDeltaManager->setTabText(twDeltaManager->indexOf(tabDefaultDelta), QCoreApplication::translate("MainWindow", "DeltaX 1", nullptr));
        twDeltaManager->setTabText(twDeltaManager->indexOf(tabAddNewDelta), QCoreApplication::translate("MainWindow", "+", nullptr));
        pbConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        cbAutoConnect->setText(QCoreApplication::translate("MainWindow", "Auto", nullptr));
        lbID->setText(QCoreApplication::translate("MainWindow", "ID: 0", nullptr));
        lbPort->setText(QCoreApplication::translate("MainWindow", "PORT: 8844", nullptr));
        lbIP->setText(QCoreApplication::translate("MainWindow", "IP: localhost", nullptr));
        pbTurnOnROS->setText(QCoreApplication::translate("MainWindow", "Turn On ROS", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
        cbROSCameraView->setItemText(0, QCoreApplication::translate("MainWindow", "0", nullptr));
        cbROSCameraView->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));
        cbROSCameraView->setItemText(2, QCoreApplication::translate("MainWindow", "2", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "Change View", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "Display", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Robot", nullptr));
        cbRobotVersion->setItemText(0, QCoreApplication::translate("MainWindow", "Delta X 1", nullptr));
        cbRobotVersion->setItemText(1, QCoreApplication::translate("MainWindow", "Delta X 2", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "End Effector", nullptr));
        cbEndEffector->setItemText(0, QCoreApplication::translate("MainWindow", "Suction Cup", nullptr));
        cbEndEffector->setItemText(1, QCoreApplication::translate("MainWindow", "Gripper", nullptr));
        cbEndEffector->setItemText(2, QCoreApplication::translate("MainWindow", "None", nullptr));

        label_3->setText(QCoreApplication::translate("MainWindow", "Objects", nullptr));
#if QT_CONFIG(tooltip)
        btDeleteAllObjects->setToolTip(QCoreApplication::translate("MainWindow", "Update X Position Value", nullptr));
#endif // QT_CONFIG(tooltip)
        btDeleteAllObjects->setText(QCoreApplication::translate("MainWindow", "Delete All", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t3D), QCoreApplication::translate("MainWindow", "3D", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_61->setText(QCoreApplication::translate("MainWindow", "6-Axis", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "4-Axis", nullptr));
        label_60->setText(QCoreApplication::translate("MainWindow", "5-Axis", nullptr));
        label_53->setText(QCoreApplication::translate("MainWindow", "Cursor", nullptr));
        label_41->setText(QCoreApplication::translate("MainWindow", "X:", nullptr));
        lbXCursor->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_51->setText(QCoreApplication::translate("MainWindow", "Y:", nullptr));
        lbYCursor->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t2D), QCoreApplication::translate("MainWindow", "2D", nullptr));
        gbMovement1->setTitle(QCoreApplication::translate("MainWindow", "Movement", nullptr));
        pbHome->setText(QString());
        label_6->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        leX->setText(QString());
#if QT_CONFIG(tooltip)
        pbX->setToolTip(QCoreApplication::translate("MainWindow", "Update X Position Value", nullptr));
#endif // QT_CONFIG(tooltip)
        pbX->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(tooltip)
        pbY->setToolTip(QCoreApplication::translate("MainWindow", "Update Y Position Value", nullptr));
#endif // QT_CONFIG(tooltip)
        pbY->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(tooltip)
        pbZ->setToolTip(QCoreApplication::translate("MainWindow", "Update Z Position Value", nullptr));
#endif // QT_CONFIG(tooltip)
        pbZ->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(tooltip)
        pbW->setToolTip(QCoreApplication::translate("MainWindow", "Update W Position Value", nullptr));
#endif // QT_CONFIG(tooltip)
        pbW->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
#if QT_CONFIG(tooltip)
        pbBackward->setToolTip(QCoreApplication::translate("MainWindow", "Backward (shift + s)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbBackward->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbBackward->setText(QString());
#if QT_CONFIG(shortcut)
        pbBackward->setShortcut(QCoreApplication::translate("MainWindow", "Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbDown->setToolTip(QCoreApplication::translate("MainWindow", "Down (shift + f)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbDown->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbDown->setText(QString());
#if QT_CONFIG(shortcut)
        pbDown->setShortcut(QCoreApplication::translate("MainWindow", "Shift+F", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbLeft->setToolTip(QCoreApplication::translate("MainWindow", "Left (shift + w)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbLeft->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbLeft->setText(QString());
#if QT_CONFIG(shortcut)
        pbLeft->setShortcut(QCoreApplication::translate("MainWindow", "Shift+A", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbForward->setToolTip(QCoreApplication::translate("MainWindow", "Forward (Shift + w)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbForward->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbForward->setText(QString());
#if QT_CONFIG(shortcut)
        pbForward->setShortcut(QCoreApplication::translate("MainWindow", "Shift+W", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbRight->setToolTip(QCoreApplication::translate("MainWindow", "Right (Shift +d)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbRight->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbRight->setText(QString());
#if QT_CONFIG(shortcut)
        pbRight->setShortcut(QCoreApplication::translate("MainWindow", "Shift+D", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbUp->setToolTip(QCoreApplication::translate("MainWindow", "Up (shift + r)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbUp->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbUp->setText(QString());
#if QT_CONFIG(shortcut)
        pbUp->setShortcut(QCoreApplication::translate("MainWindow", "Shift+R", nullptr));
#endif // QT_CONFIG(shortcut)
        label_33->setText(QCoreApplication::translate("MainWindow", "Division", nullptr));
        cbDivision->setItemText(0, QCoreApplication::translate("MainWindow", "0.5", nullptr));
        cbDivision->setItemText(1, QCoreApplication::translate("MainWindow", "1", nullptr));
        cbDivision->setItemText(2, QCoreApplication::translate("MainWindow", "5", nullptr));
        cbDivision->setItemText(3, QCoreApplication::translate("MainWindow", "10", nullptr));
        cbDivision->setItemText(4, QCoreApplication::translate("MainWindow", "50", nullptr));
        cbDivision->setItemText(5, QCoreApplication::translate("MainWindow", "100", nullptr));

        cbDivision->setCurrentText(QCoreApplication::translate("MainWindow", "1", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "Velocity", nullptr));
        leVelocity->setText(QCoreApplication::translate("MainWindow", "200", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "Accel", nullptr));
        leAccel->setText(QCoreApplication::translate("MainWindow", "1200", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "mm/s2", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "IO", nullptr));
        gbRelay->setTitle(QCoreApplication::translate("MainWindow", "Relay", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "Vacuum", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "Laser", nullptr));
        pbPump->setText(QString());
        pbLaser->setText(QString());
        gbGripper->setTitle(QCoreApplication::translate("MainWindow", "Gripper", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "min", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "max", nullptr));
        pbGrip->setText(QCoreApplication::translate("MainWindow", "Grip", nullptr));
        leGripperMin->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        leGripperMax->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        lbGripperValue->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        groupBox_5->setTitle(QCoreApplication::translate("MainWindow", "Output", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("MainWindow", "Input", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(tJogging), QCoreApplication::translate("MainWindow", "Jogging", nullptr));
        pbConveyorConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Value of Moving", nullptr));
        label_57->setText(QCoreApplication::translate("MainWindow", "Velocity in Position Mode", nullptr));
        leSpeedOfPositionMode->setText(QCoreApplication::translate("MainWindow", "50", nullptr));
        lbSpeedOfPositionMode->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        leConveyorvMovingValue->setText(QCoreApplication::translate("MainWindow", "-100", nullptr));
        label_52->setText(QCoreApplication::translate("MainWindow", "Control Mode", nullptr));
        cbConveyorMode->setItemText(0, QCoreApplication::translate("MainWindow", "Manual", nullptr));
        cbConveyorMode->setItemText(1, QCoreApplication::translate("MainWindow", "UART", nullptr));

        label_46->setText(QCoreApplication::translate("MainWindow", "Moving Mode", nullptr));
        cbConveyorValueType->setItemText(0, QCoreApplication::translate("MainWindow", "Speed", nullptr));
        cbConveyorValueType->setItemText(1, QCoreApplication::translate("MainWindow", "Position", nullptr));

        twConveyor->setTabText(twConveyor->indexOf(tConveyor), QCoreApplication::translate("MainWindow", "Conveyor X", nullptr));
        pbSlidingConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        label_58->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        label_59->setText(QCoreApplication::translate("MainWindow", "mm/s2", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "Position", nullptr));
#if QT_CONFIG(tooltip)
        pbSlidingHome->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbSlidingHome->setText(QCoreApplication::translate("MainWindow", "Home", nullptr));
#if QT_CONFIG(tooltip)
        pbSlidingDisable->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbSlidingDisable->setText(QCoreApplication::translate("MainWindow", "Disable motors", nullptr));
        twConveyor->setTabText(twConveyor->indexOf(sSlidingRail), QCoreApplication::translate("MainWindow", "Sliding Rail X", nullptr));
#if QT_CONFIG(tooltip)
        pbExternalControllerConnect->setToolTip(QCoreApplication::translate("MainWindow", "Connect External Controller", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExternalControllerConnect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        leReceiveFromMCU->setText(QString());
        leReceiveFromMCU->setPlaceholderText(QCoreApplication::translate("MainWindow", "Receive from MCU", nullptr));
        leTransmitToMCU->setText(QString());
        leTransmitToMCU->setPlaceholderText(QCoreApplication::translate("MainWindow", "Transmit to MCU", nullptr));
        twConveyor->setTabText(twConveyor->indexOf(tExternalMCU), QCoreApplication::translate("MainWindow", "External MCU", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(xExternal), QCoreApplication::translate("MainWindow", "External", nullptr));
        teDebug->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Debug:</p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Sender", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Receiver", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(tTerminal), QCoreApplication::translate("MainWindow", "Terminal", nullptr));
#if QT_CONFIG(tooltip)
        twModule->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        gbAddGcode->setTitle(QCoreApplication::translate("MainWindow", "Add G-code", nullptr));
        cbGcode->setItemText(0, QCoreApplication::translate("MainWindow", "G01", nullptr));
        cbGcode->setItemText(1, QCoreApplication::translate("MainWindow", "G02", nullptr));
        cbGcode->setItemText(2, QCoreApplication::translate("MainWindow", "G03", nullptr));
        cbGcode->setItemText(3, QCoreApplication::translate("MainWindow", "G05", nullptr));
        cbGcode->setItemText(4, QCoreApplication::translate("MainWindow", "G28", nullptr));
        cbGcode->setItemText(5, QCoreApplication::translate("MainWindow", "M03", nullptr));
        cbGcode->setItemText(6, QCoreApplication::translate("MainWindow", "M04", nullptr));
        cbGcode->setItemText(7, QCoreApplication::translate("MainWindow", "M05", nullptr));
        cbGcode->setItemText(8, QCoreApplication::translate("MainWindow", "M204", nullptr));

        lbAg1->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        leAg1->setText(QString());
        lbAg2->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        leAg2->setText(QString());
        lbAg3->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        leAg3->setText(QString());
        lbAg4->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        leAg4->setText(QString());
        lbAg5->setText(QCoreApplication::translate("MainWindow", "F", nullptr));
        leAg5->setText(QString());
        lbAg6->setText(QString());
        leAg6->setText(QString());
        pbAddGcode->setText(QCoreApplication::translate("MainWindow", "Add ( Ctrl + D )", nullptr));
#if QT_CONFIG(shortcut)
        pbAddGcode->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+D", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbGcodeReference->setToolTip(QCoreApplication::translate("MainWindow", "Gcode Reference", nullptr));
#endif // QT_CONFIG(tooltip)
        pbGcodeReference->setText(QCoreApplication::translate("MainWindow", "Reference", nullptr));
        gbVar->setTitle(QCoreApplication::translate("MainWindow", "Variables", nullptr));
        leVariable1->setText(QCoreApplication::translate("MainWindow", "#100", nullptr));
        lbVar1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        leVariable2->setText(QCoreApplication::translate("MainWindow", "#101", nullptr));
        lbVar2->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        leVariable3->setText(QCoreApplication::translate("MainWindow", "#102", nullptr));
        lbVar3->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        leVariable4->setText(QCoreApplication::translate("MainWindow", "#103", nullptr));
        lbVar4->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        leVariable5->setText(QCoreApplication::translate("MainWindow", "#104", nullptr));
        lbVar5->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        leVariable6->setText(QCoreApplication::translate("MainWindow", "#105", nullptr));
        lbVar6->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        cbLockGcodeEditor->setText(QCoreApplication::translate("MainWindow", "Lock Editor", nullptr));
#if QT_CONFIG(tooltip)
        pbSaveGcode->setToolTip(QCoreApplication::translate("MainWindow", "Save Gcode Into File", nullptr));
#endif // QT_CONFIG(tooltip)
        pbSaveGcode->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        pteGcodeArea->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;====Vision functions==========</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;M98 PpauseCamera</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;M98 PresumeCamera</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-"
                        "left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;M98 PcaptureCamera</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;M98 PdeleteFirstObject</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;M98 PclearObjects</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;========================</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-style:italic; color:#00aa00;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; "
                        "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#000000;\">N05</span> <span style=\" font-weight:600;\">G28</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Acceleration</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N10 <span style=\" font-weight:600;\">M204</span> A1200</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Speed</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-inden"
                        "t:0; text-indent:0px;\">N15 <span style=\" font-weight:600;\">G01</span> F200</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Declare variables</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N20 <span style=\" font-style:italic;\">#100</span> = 0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N30 <span style=\" font-style:italic;\">#100</span> = <span style=\" font-style:italic;\">#100</span> + 1</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br />"
                        "</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#55aa00;\">;Call subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N35 <span style=\" font-weight:600;\">M98</span> P2000</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">; Begin subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N40 <span style=\" font-weight:600;\">O2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-le"
                        "ft:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N45 <span style=\" font-weight:600;\">G01</span> Z-350</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N50 <span style=\" font-weight:600;\">G01</span> X-100</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N55 <span style=\" font-weight:600;\">G01</span> Z-370</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N60 <span style=\" font-weight:600;\">G01</span> Z-350</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; m"
                        "argin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N65 <span style=\" font-weight:600;\">G01</span> X100</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N70 <span style=\" font-weight:600;\">G01</span> Z-370</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N75 M99</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;End subprogram</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Loop 5 times</span></p>\n"
"<p s"
                        "tyle=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N80 <span style=\" font-weight:600; color:#00aa00;\">IF</span> [<span style=\" font-style:italic;\">#100</span> LE 5] <span style=\" font-weight:600; color:#00aa00;\">THEN</span> <span style=\" font-weight:600; color:#ff5500;\">GOTO</span> 30</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N85 <span style=\" font-weight:600;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> </p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        pbFormat->setToolTip(QCoreApplication::translate("MainWindow", "Format Gcode Lines", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFormat->setText(QCoreApplication::translate("MainWindow", "Format", nullptr));
        cbFormatColor->setText(QCoreApplication::translate("MainWindow", "Color", nullptr));
        cbAutoNumbering->setText(QCoreApplication::translate("MainWindow", "Auto Numbering", nullptr));
#if QT_CONFIG(tooltip)
        pbExecuteGcodes->setToolTip(QCoreApplication::translate("MainWindow", "Execute Gcode", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExecuteGcodes->setText(QString());
        cbPositionToExecuteGcode->setItemText(0, QCoreApplication::translate("MainWindow", "Begin", nullptr));
        cbPositionToExecuteGcode->setItemText(1, QCoreApplication::translate("MainWindow", "Current", nullptr));

        leExProgramName->setText(QCoreApplication::translate("MainWindow", "Program 1", nullptr));
        pbExDeleteProgram->setText(QString());
        lbExGCodeNumber->setText(QCoreApplication::translate("MainWindow", "100 Gcode Lines", nullptr));
#if QT_CONFIG(tooltip)
        pbUploadProgram->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbUploadProgram->setText(QString());
#if QT_CONFIG(tooltip)
        pbImportGcodeFiles->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbImportGcodeFiles->setText(QCoreApplication::translate("MainWindow", "Import", nullptr));
#if QT_CONFIG(tooltip)
        pbAddNewProgram->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbAddNewProgram->setText(QCoreApplication::translate("MainWindow", "New ", nullptr));
#if QT_CONFIG(tooltip)
        pbRefreshGcodeFiles->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbRefreshGcodeFiles->setText(QCoreApplication::translate("MainWindow", "F5   ", nullptr));
#if QT_CONFIG(tooltip)
        pbFindGcodeFile->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbFindGcodeFile->setText(QCoreApplication::translate("MainWindow", "Find", nullptr));
#if QT_CONFIG(tooltip)
        pbSortGcodeFiles->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbSortGcodeFiles->setText(QCoreApplication::translate("MainWindow", "Sort", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWindow", "Offline", nullptr));
        textEdit->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Author:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Description:</p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        pbUploadProgram_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbUploadProgram_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Online", nullptr));
        twModule->setTabText(twModule->indexOf(tGcodeEditor), QCoreApplication::translate("MainWindow", "Gcode Editor", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Object", nullptr));
        lbTrackingObject->setText(QString());
#if QT_CONFIG(tooltip)
        pbObjectRect->setToolTip(QCoreApplication::translate("MainWindow", "Bound the object size", nullptr));
#endif // QT_CONFIG(tooltip)
        pbObjectRect->setText(QCoreApplication::translate("MainWindow", "Rec Tool", nullptr));
        leLRec->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        leWRec->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        leHRec->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        label_42->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        label_43->setText(QCoreApplication::translate("MainWindow", "L", nullptr));
        label_44->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        label_54->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_55->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_56->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        cbObjectType->setItemText(0, QCoreApplication::translate("MainWindow", "Type 1", nullptr));
        cbObjectType->setItemText(1, QCoreApplication::translate("MainWindow", "Type 2", nullptr));
        cbObjectType->setItemText(2, QCoreApplication::translate("MainWindow", "Type 3", nullptr));
        cbObjectType->setItemText(3, QCoreApplication::translate("MainWindow", "Type 4", nullptr));
        cbObjectType->setItemText(4, QCoreApplication::translate("MainWindow", "Type 5", nullptr));
        cbObjectType->setItemText(5, QCoreApplication::translate("MainWindow", "Type 6", nullptr));
        cbObjectType->setItemText(6, QCoreApplication::translate("MainWindow", "Type 7", nullptr));
        cbObjectType->setItemText(7, QCoreApplication::translate("MainWindow", "Type 8", nullptr));
        cbObjectType->setItemText(8, QCoreApplication::translate("MainWindow", "Type 9", nullptr));
        cbObjectType->setItemText(9, QCoreApplication::translate("MainWindow", "Type 10", nullptr));

        groupBox_7->setTitle(QCoreApplication::translate("MainWindow", "Conveyor", nullptr));
        leConvenyorSpeed->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_45->setText(QCoreApplication::translate("MainWindow", "Speed", nullptr));
        cbConveyorDirection->setItemText(0, QCoreApplication::translate("MainWindow", "X", nullptr));
        cbConveyorDirection->setItemText(1, QCoreApplication::translate("MainWindow", "Y", nullptr));

        label_47->setText(QCoreApplication::translate("MainWindow", "Direction", nullptr));
        label_49->setText(QCoreApplication::translate("MainWindow", "(mm/s)", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("MainWindow", "Measurement", nullptr));
#if QT_CONFIG(tooltip)
        pbObjectLine->setToolTip(QCoreApplication::translate("MainWindow", "Calibrating length", nullptr));
#endif // QT_CONFIG(tooltip)
        pbObjectLine->setText(QCoreApplication::translate("MainWindow", "Calib Line", nullptr));
        leRealDistance->setText(QCoreApplication::translate("MainWindow", "100", nullptr));
        leYCoordinate->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(tooltip)
        pbObjectOrigin->setToolTip(QCoreApplication::translate("MainWindow", "Set a calibrating point", nullptr));
#endif // QT_CONFIG(tooltip)
        pbObjectOrigin->setText(QCoreApplication::translate("MainWindow", "Calib Point", nullptr));
        leXCoordinate->setText(QCoreApplication::translate("MainWindow", "150", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "(mm)", nullptr));
#if QT_CONFIG(tooltip)
        pbChangeXAxis->setToolTip(QCoreApplication::translate("MainWindow", "Change direction of coordinates", nullptr));
#endif // QT_CONFIG(tooltip)
        pbChangeXAxis->setText(QCoreApplication::translate("MainWindow", "X Direction", nullptr));
        cbDisplayCalibInfo->setText(QCoreApplication::translate("MainWindow", "Display", nullptr));
        groupBox_9->setTitle(QCoreApplication::translate("MainWindow", "Camera", nullptr));
#if QT_CONFIG(tooltip)
        pbLoadCamera->setToolTip(QCoreApplication::translate("MainWindow", "Load Camera", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLoadCamera->setText(QString());
#if QT_CONFIG(tooltip)
        pbLoadTestImage->setToolTip(QCoreApplication::translate("MainWindow", "Load Image", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLoadTestImage->setText(QString());
        label_11->setText(QCoreApplication::translate("MainWindow", "FPS", nullptr));
        leFPS->setText(QCoreApplication::translate("MainWindow", "15", nullptr));
#if QT_CONFIG(tooltip)
        pbPlayPauseCamera->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Play and Pause</p><p>M98 PpauseCamera</p><p>M98 PresumeCamera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pbPlayPauseCamera->setText(QString());
#if QT_CONFIG(tooltip)
        pbCaptureCamera->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Capture</p><p>M98 PcaptureCamera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCaptureCamera->setText(QString());
#if QT_CONFIG(tooltip)
        pbLoadCameraSetting->setToolTip(QCoreApplication::translate("MainWindow", "Load Setting", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLoadCameraSetting->setText(QString());
#if QT_CONFIG(tooltip)
        pbSaveCameraSetting->setToolTip(QCoreApplication::translate("MainWindow", "Save Setting", nullptr));
#endif // QT_CONFIG(tooltip)
        pbSaveCameraSetting->setText(QString());
        lbCameraState->setText(QString());
        groupBox_10->setTitle(QCoreApplication::translate("MainWindow", "Variable", nullptr));
        pbViewDataObjects->setText(QCoreApplication::translate("MainWindow", "Object Table", nullptr));
#if QT_CONFIG(tooltip)
        pbClearDetectObjects->setToolTip(QCoreApplication::translate("MainWindow", "<html><head/><body><p>Clear All Objects in Memory</p><p>M98 PclearObjects --&gt; Clear All</p><p>M98 PdeleteFirstObject --&gt; Delete First</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbClearDetectObjects->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbClearDetectObjects->setText(QCoreApplication::translate("MainWindow", "Clear Objects", nullptr));
        label_50->setText(QCoreApplication::translate("MainWindow", "Visible", nullptr));
        label_48->setText(QCoreApplication::translate("MainWindow", "Tracking", nullptr));
        lbTrackingObjectNumber->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lbVisibleObjectNumber->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
#if QT_CONFIG(tooltip)
        pbFilter->setToolTip(QCoreApplication::translate("MainWindow", "Camera Filter", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFilter->setText(QCoreApplication::translate("MainWindow", "Filter", nullptr));
#if QT_CONFIG(tooltip)
        pbTransformPerspective->setToolTip(QCoreApplication::translate("MainWindow", "Perspective Transformation", nullptr));
#endif // QT_CONFIG(tooltip)
        pbTransformPerspective->setText(QCoreApplication::translate("MainWindow", "Transform", nullptr));
        lbScreenStreamer->setText(QString());
#if QT_CONFIG(tooltip)
        pbExpandCameraWidget->setToolTip(QCoreApplication::translate("MainWindow", "Expand Camera Widget", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExpandCameraWidget->setText(QString());
#if QT_CONFIG(tooltip)
        pbCameraWindowMode->setToolTip(QCoreApplication::translate("MainWindow", "Window Mode", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCameraWindowMode->setText(QString());
        lbCameraLayer->setItemText(0, QCoreApplication::translate("MainWindow", "Result", nullptr));
        lbCameraLayer->setItemText(1, QCoreApplication::translate("MainWindow", "Processing", nullptr));
        lbCameraLayer->setItemText(2, QCoreApplication::translate("MainWindow", "Origin", nullptr));

#if QT_CONFIG(tooltip)
        lbCameraLayer->setToolTip(QCoreApplication::translate("MainWindow", "Select Camera Layer", nullptr));
#endif // QT_CONFIG(tooltip)
        lbCameraLayer->setCurrentText(QCoreApplication::translate("MainWindow", "Result", nullptr));
        twModule->setTabText(twModule->indexOf(tResultCameraArea), QCoreApplication::translate("MainWindow", "Object Detecting", nullptr));
        lbImageForDrawing->setText(QString());
        lbDrawingArea->setText(QString());
        leDrawingThreshold->setText(QCoreApplication::translate("MainWindow", "150", nullptr));
        lbImageWidth->setText(QCoreApplication::translate("MainWindow", "W: 208", nullptr));
        lbImageHeight->setText(QCoreApplication::translate("MainWindow", "H: 117", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "H Scale", nullptr));
        leHeightScale->setText(QCoreApplication::translate("MainWindow", "117", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "W Scale", nullptr));
        leWidthScale->setText(QCoreApplication::translate("MainWindow", "208", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "Space", nullptr));
        leSpace->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        pbDrawLine->setText(QString());
        pbDrawRectangle->setText(QString());
        pbDrawArc->setText(QString());
        pbDrawCircle->setText(QString());
        label_19->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        leDrawAg1->setText(QString());
        label_22->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "H", nullptr));
        label_25->setText(QCoreApplication::translate("MainWindow", "W", nullptr));
        label_26->setText(QCoreApplication::translate("MainWindow", "O", nullptr));
        pbOpenPicture->setText(QString());
        pbExportDrawingGcodes->setText(QCoreApplication::translate("MainWindow", "Export\n"
"G-code", nullptr));
        pbPainting->setText(QCoreApplication::translate("MainWindow", "Draw", nullptr));
        pbZoomIn->setText(QString());
        pbZoomOut->setText(QString());
        label_21->setText(QCoreApplication::translate("MainWindow", "100%", nullptr));
        pbCursor->setText(QString());
        cbDrawingEffector->setItemText(0, QCoreApplication::translate("MainWindow", "Laser", nullptr));
        cbDrawingEffector->setItemText(1, QCoreApplication::translate("MainWindow", "Pen", nullptr));

        cbDrawMethod->setItemText(0, QCoreApplication::translate("MainWindow", "Line", nullptr));
        cbDrawMethod->setItemText(1, QCoreApplication::translate("MainWindow", "Dot", nullptr));

        label_13->setText(QCoreApplication::translate("MainWindow", "Move Type", nullptr));
        cbConversionTool->setItemText(0, QCoreApplication::translate("MainWindow", "Threshold", nullptr));
        cbConversionTool->setItemText(1, QCoreApplication::translate("MainWindow", "Vectorize", nullptr));
        cbConversionTool->setItemText(2, QCoreApplication::translate("MainWindow", "Gray", nullptr));

        label_14->setText(QCoreApplication::translate("MainWindow", "Conversion Tool", nullptr));
        twModule->setTabText(twModule->indexOf(tDrawing), QCoreApplication::translate("MainWindow", "Drawing", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
        menuReferences->setTitle(QCoreApplication::translate("MainWindow", "References", nullptr));
        menuEditor->setTitle(QCoreApplication::translate("MainWindow", "Editor", nullptr));
        menuExecute->setTitle(QCoreApplication::translate("MainWindow", "Execute", nullptr));
        menu_2->setTitle(QCoreApplication::translate("MainWindow", ".............................................................", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("MainWindow", "Setting", nullptr));
        menuConnection->setTitle(QCoreApplication::translate("MainWindow", "Connection", nullptr));
        menuUI->setTitle(QCoreApplication::translate("MainWindow", "UI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
