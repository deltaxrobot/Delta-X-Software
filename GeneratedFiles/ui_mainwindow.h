/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <CameraWidget.h>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <codeeditor.h>
#include <drawingwidget.h>
#include <qwebengineview.h>

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
    QLabel *lbDebug;
    QLineEdit *leTerminal;
    QTabWidget *twDeltaManager;
    QWidget *tabDefaultDelta;
    QWidget *tabAddNewDelta;
    QTabWidget *twModule;
    QWidget *tBlockly;
    QWebEngineView *wevBlockly;
    QPushButton *pbExportBlocklyToGcode;
    QPushButton *pushButton_4;
    QWidget *tResultCameraArea;
    CameraWidget *lbScreenStreamer;
    QGroupBox *groupBox;
    QLabel *lbTrackingObject;
    QPushButton *pbObjectRect;
    QLineEdit *leYRec;
    QLineEdit *leXRec;
    QLineEdit *leYRec_2;
    QLabel *label_42;
    QLabel *label_43;
    QLabel *label_44;
    QGroupBox *groupBox_7;
    QLineEdit *leConvenyorSpeed;
    QLabel *label_45;
    QComboBox *cbConveyorDirection;
    QLabel *label_47;
    QGroupBox *groupBox_8;
    QPushButton *pbObjectLine;
    QLineEdit *leRealDistance;
    QLineEdit *leYCoordinate;
    QPushButton *pbObjectOrigin;
    QLineEdit *leXCoordinate;
    QLabel *label_38;
    QLabel *label_39;
    QLabel *label_12;
    QLabel *label_40;
    QPushButton *pbChangeXAxis;
    QGroupBox *groupBox_9;
    QPushButton *pbLoadCamera;
    QPushButton *pbLoadTestImage;
    QLabel *label_11;
    QLineEdit *leFPS;
    QGroupBox *groupBox_10;
    QPushButton *pbViewDataObjects;
    QPushButton *pbClearDetectObjects;
    QGroupBox *groupBox_13;
    QLabel *label_48;
    QLabel *lbTrackingObjectNumber;
    QLabel *label_50;
    QLabel *lbVisibleObjectNumber;
    QPushButton *pbSwitchWorkFlow;
    QPushButton *pbFilter;
    QPushButton *pbSelection;
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
    QTabWidget *twDeltaGeometry;
    QWidget *t3D;
    QPushButton *pbTurnOnROS;
    QWidget *widget;
    QFrame *frameROS;
    QGroupBox *groupBox_3;
    QComboBox *cbROSCameraView;
    QLabel *label;
    QGroupBox *groupBox_4;
    QLabel *label_2;
    QComboBox *cbEndEffector;
    QWidget *t2D;
    QWidget *wg2D;
    QSlider *vsZAdjsution;
    QSlider *vsAngleAdjsution;
    QLabel *label_15;
    QLabel *label_16;
    QGroupBox *groupBox_5;
    QLabel *label_28;
    QPushButton *pbRight;
    QPushButton *pbBackward;
    QComboBox *cbDivision;
    QPushButton *pbForward;
    QPushButton *pbLeft;
    QPushButton *pbUp;
    QPushButton *pbDown;
    QLabel *label_29;
    QLineEdit *leVelocity;
    QLabel *label_30;
    QLabel *label_31;
    QLineEdit *leAccel;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_46;
    QPushButton *pbConnect;
    QLabel *lbID;
    QGroupBox *gbGripper;
    QPushButton *pbGrip;
    QSlider *hsGripperAngle;
    QLineEdit *leGripperMin;
    QLineEdit *leGripperMax;
    QLabel *label_17;
    QLabel *label_27;
    QGroupBox *gbRelay;
    QPushButton *pbPump;
    QLabel *label_34;
    QPushButton *pbLaser;
    QLabel *label_35;
    QGroupBox *gbMovement1;
    QLineEdit *leY;
    QLineEdit *leZ;
    QPushButton *pbY;
    QPushButton *pbX;
    QLineEdit *leX;
    QLineEdit *leW;
    QPushButton *pbZ;
    QPushButton *pbW;
    QPushButton *pbHome;
    QTabWidget *twConveyor;
    QWidget *tConveyor;
    QComboBox *cbConveyorMode;
    QComboBox *cbConveyorValueType;
    QLineEdit *leConveyorvMovingValue;
    QPushButton *pbConveyorMove;
    QPushButton *pbConveyorConnect;
    QWidget *sSlidingRail;
    QPushButton *pbSlidingConnect;
    QPushButton *pbSlidingHome;
    QLineEdit *leSlidingSpeed;
    QLineEdit *leSlidingPosition;
    QPushButton *pbSlidingDisable;
    QLabel *label_36;
    QLabel *label_37;
    QCheckBox *checkBox;
    QLabel *label_52;
    QPushButton *pbFormat;
    QCheckBox *cbLockGcodeEditor;
    QCheckBox *cbAutoNumbering;
    QGroupBox *gbVar;
    QLabel *lbVar6;
    QLabel *lbVar4;
    QLineEdit *leVariable2;
    QLineEdit *leVariable4;
    QLineEdit *leVariable6;
    QLabel *lbVar5;
    QLabel *lbVar1;
    QLineEdit *leVariable3;
    QLineEdit *leVariable1;
    QLabel *lbVar3;
    QLineEdit *leVariable5;
    QLabel *lbVar2;
    QPushButton *pbExternalControllerConnect;
    QLabel *lbECComName;
    CodeEditor *pteGcodeArea;
    QComboBox *cbPositionToExecuteGcode;
    QCheckBox *cbFormatColor;
    QPushButton *pbExecuteGcodes;
    QGroupBox *gbAddGcode;
    QLabel *lbAg1;
    QLineEdit *leAg6;
    QLabel *lbAg2;
    QLineEdit *leAg5;
    QLabel *lbAg3;
    QLabel *lbAg5;
    QLabel *lbAg6;
    QLineEdit *leAg3;
    QLabel *lbAg4;
    QLineEdit *leAg4;
    QLineEdit *leAg2;
    QLineEdit *leAg1;
    QPushButton *pbGcodeReference;
    QPushButton *pbAddGcode;
    QComboBox *cbGcode;
    QPushButton *pbSaveGcode;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pbFindGcodeFile;
    QPushButton *pbRefreshGcodeFiles;
    QPushButton *pbAddNewProgram;
    QScrollArea *saProgramFiles;
    QWidget *wgProgramContainer;
    QFrame *frExProgram;
    QLineEdit *leExProgramName;
    QPushButton *pbExDeleteProgram;
    QLabel *lbExGCodeNumber;
    QPushButton *pbSortGcodeFiles;
    QPushButton *pbUploadProgram;
    QPushButton *pbImportGcodeFiles;
    QWidget *tab_3;
    QListWidget *listWidget;
    QTextEdit *textEdit;
    QPushButton *pbUploadProgram_2;
    QLabel *lbID_2;
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
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1293, 714);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1293, 714));
        MainWindow->setMaximumSize(QSize(1293, 714));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(true);
        MainWindow->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral("C:/Users/Admin/.designer/backup/delta_x_logo_96x96.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        actionAdd = new QAction(MainWindow);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionRemove = new QAction(MainWindow);
        actionRemove->setObjectName(QStringLiteral("actionRemove"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionGcode = new QAction(MainWindow);
        actionGcode->setObjectName(QStringLiteral("actionGcode"));
        actionSoftware = new QAction(MainWindow);
        actionSoftware->setObjectName(QStringLiteral("actionSoftware"));
        actionExecute_All = new QAction(MainWindow);
        actionExecute_All->setObjectName(QStringLiteral("actionExecute_All"));
        actionDelta_X_1 = new QAction(MainWindow);
        actionDelta_X_1->setObjectName(QStringLiteral("actionDelta_X_1"));
        actionDelta_X_1->setCheckable(true);
        actionDelta_X_1->setChecked(true);
        actionExecute = new QAction(MainWindow);
        actionExecute->setObjectName(QStringLiteral("actionExecute"));
        actionBaudrate = new QAction(MainWindow);
        actionBaudrate->setObjectName(QStringLiteral("actionBaudrate"));
        actionScale = new QAction(MainWindow);
        actionScale->setObjectName(QStringLiteral("actionScale"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        lbDebug = new QLabel(centralWidget);
        lbDebug->setObjectName(QStringLiteral("lbDebug"));
        lbDebug->setGeometry(QRect(10, 635, 396, 21));
        lbDebug->setStyleSheet(QLatin1String("background-color:rgb(70, 70, 70);\n"
"color:rgb(0, 235, 0);\n"
""));
        leTerminal = new QLineEdit(centralWidget);
        leTerminal->setObjectName(QStringLiteral("leTerminal"));
        leTerminal->setGeometry(QRect(75, 660, 331, 22));
        twDeltaManager = new QTabWidget(centralWidget);
        twDeltaManager->setObjectName(QStringLiteral("twDeltaManager"));
        twDeltaManager->setGeometry(QRect(0, 0, 871, 28));
        QFont font1;
        font1.setPointSize(12);
        twDeltaManager->setFont(font1);
        twDeltaManager->setStyleSheet(QStringLiteral("color: rgb(18, 190, 190);"));
        tabDefaultDelta = new QWidget();
        tabDefaultDelta->setObjectName(QStringLiteral("tabDefaultDelta"));
        twDeltaManager->addTab(tabDefaultDelta, QString());
        tabAddNewDelta = new QWidget();
        tabAddNewDelta->setObjectName(QStringLiteral("tabAddNewDelta"));
        twDeltaManager->addTab(tabAddNewDelta, QString());
        twModule = new QTabWidget(centralWidget);
        twModule->setObjectName(QStringLiteral("twModule"));
        twModule->setGeometry(QRect(418, 114, 476, 566));
        tBlockly = new QWidget();
        tBlockly->setObjectName(QStringLiteral("tBlockly"));
        wevBlockly = new QWebEngineView(tBlockly);
        wevBlockly->setObjectName(QStringLiteral("wevBlockly"));
        wevBlockly->setGeometry(QRect(5, 55, 461, 481));
        pbExportBlocklyToGcode = new QPushButton(tBlockly);
        pbExportBlocklyToGcode->setObjectName(QStringLiteral("pbExportBlocklyToGcode"));
        pbExportBlocklyToGcode->setGeometry(QRect(365, 12, 101, 36));
        pushButton_4 = new QPushButton(tBlockly);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(5, 12, 111, 36));
        twModule->addTab(tBlockly, QString());
        tResultCameraArea = new QWidget();
        tResultCameraArea->setObjectName(QStringLiteral("tResultCameraArea"));
        lbScreenStreamer = new CameraWidget(tResultCameraArea);
        lbScreenStreamer->setObjectName(QStringLiteral("lbScreenStreamer"));
        lbScreenStreamer->setGeometry(QRect(5, 225, 391, 306));
        lbScreenStreamer->setStyleSheet(QStringLiteral("background-color:rgb(230, 230, 230)"));
        lbScreenStreamer->setScaledContents(false);
        lbScreenStreamer->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBox = new QGroupBox(tResultCameraArea);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(370, 15, 96, 201));
        lbTrackingObject = new QLabel(groupBox);
        lbTrackingObject->setObjectName(QStringLiteral("lbTrackingObject"));
        lbTrackingObject->setGeometry(QRect(15, 105, 66, 56));
        lbTrackingObject->setStyleSheet(QStringLiteral("background-color:rgb(230, 230, 230)"));
        pbObjectRect = new QPushButton(groupBox);
        pbObjectRect->setObjectName(QStringLiteral("pbObjectRect"));
        pbObjectRect->setGeometry(QRect(5, 165, 86, 28));
        pbObjectRect->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral("icon/Rectangle_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbObjectRect->setIcon(icon1);
        leYRec = new QLineEdit(groupBox);
        leYRec->setObjectName(QStringLiteral("leYRec"));
        leYRec->setGeometry(QRect(50, 50, 36, 22));
        leXRec = new QLineEdit(groupBox);
        leXRec->setObjectName(QStringLiteral("leXRec"));
        leXRec->setGeometry(QRect(50, 25, 36, 22));
        leYRec_2 = new QLineEdit(groupBox);
        leYRec_2->setObjectName(QStringLiteral("leYRec_2"));
        leYRec_2->setGeometry(QRect(50, 75, 36, 22));
        label_42 = new QLabel(groupBox);
        label_42->setObjectName(QStringLiteral("label_42"));
        label_42->setGeometry(QRect(20, 30, 26, 16));
        label_43 = new QLabel(groupBox);
        label_43->setObjectName(QStringLiteral("label_43"));
        label_43->setGeometry(QRect(20, 50, 26, 16));
        label_44 = new QLabel(groupBox);
        label_44->setObjectName(QStringLiteral("label_44"));
        label_44->setGeometry(QRect(20, 75, 26, 16));
        groupBox_7 = new QGroupBox(tResultCameraArea);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(400, 395, 66, 136));
        leConvenyorSpeed = new QLineEdit(groupBox_7);
        leConvenyorSpeed->setObjectName(QStringLiteral("leConvenyorSpeed"));
        leConvenyorSpeed->setGeometry(QRect(15, 45, 41, 27));
        label_45 = new QLabel(groupBox_7);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setGeometry(QRect(15, 20, 46, 16));
        QFont font2;
        font2.setPointSize(8);
        label_45->setFont(font2);
        cbConveyorDirection = new QComboBox(groupBox_7);
        cbConveyorDirection->setObjectName(QStringLiteral("cbConveyorDirection"));
        cbConveyorDirection->setGeometry(QRect(15, 105, 41, 22));
        label_47 = new QLabel(groupBox_7);
        label_47->setObjectName(QStringLiteral("label_47"));
        label_47->setGeometry(QRect(10, 80, 56, 16));
        label_47->setFont(font2);
        groupBox_8 = new QGroupBox(tResultCameraArea);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setGeometry(QRect(145, 15, 221, 151));
        pbObjectLine = new QPushButton(groupBox_8);
        pbObjectLine->setObjectName(QStringLiteral("pbObjectLine"));
        pbObjectLine->setGeometry(QRect(5, 40, 96, 28));
        QIcon icon2;
        icon2.addFile(QStringLiteral("icon/Width_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbObjectLine->setIcon(icon2);
        leRealDistance = new QLineEdit(groupBox_8);
        leRealDistance->setObjectName(QStringLiteral("leRealDistance"));
        leRealDistance->setGeometry(QRect(110, 45, 101, 22));
        leYCoordinate = new QLineEdit(groupBox_8);
        leYCoordinate->setObjectName(QStringLiteral("leYCoordinate"));
        leYCoordinate->setGeometry(QRect(180, 80, 31, 22));
        pbObjectOrigin = new QPushButton(groupBox_8);
        pbObjectOrigin->setObjectName(QStringLiteral("pbObjectOrigin"));
        pbObjectOrigin->setGeometry(QRect(5, 75, 96, 28));
        QIcon icon3;
        icon3.addFile(QStringLiteral("icon/Scatter Plot_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbObjectOrigin->setIcon(icon3);
        leXCoordinate = new QLineEdit(groupBox_8);
        leXCoordinate->setObjectName(QStringLiteral("leXCoordinate"));
        leXCoordinate->setGeometry(QRect(125, 80, 31, 22));
        label_38 = new QLabel(groupBox_8);
        label_38->setObjectName(QStringLiteral("label_38"));
        label_38->setGeometry(QRect(110, 85, 21, 16));
        QFont font3;
        font3.setBold(false);
        font3.setItalic(false);
        font3.setUnderline(false);
        font3.setWeight(50);
        font3.setStrikeOut(false);
        label_38->setFont(font3);
        label_38->setMouseTracking(true);
        label_38->setTextFormat(Qt::AutoText);
        label_39 = new QLabel(groupBox_8);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setGeometry(QRect(165, 80, 21, 21));
        label_12 = new QLabel(groupBox_8);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(20, 20, 55, 16));
        label_40 = new QLabel(groupBox_8);
        label_40->setObjectName(QStringLiteral("label_40"));
        label_40->setGeometry(QRect(125, 20, 86, 16));
        pbChangeXAxis = new QPushButton(groupBox_8);
        pbChangeXAxis->setObjectName(QStringLiteral("pbChangeXAxis"));
        pbChangeXAxis->setGeometry(QRect(5, 110, 96, 26));
        QIcon icon4;
        icon4.addFile(QStringLiteral("icon/Arrow Pointing Down_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QStringLiteral("C:/Users/Admin/.designer/backup/icon/Right Arrow_16px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbChangeXAxis->setIcon(icon4);
        pbChangeXAxis->setCheckable(true);
        groupBox_9 = new QGroupBox(tResultCameraArea);
        groupBox_9->setObjectName(QStringLiteral("groupBox_9"));
        groupBox_9->setGeometry(QRect(5, 15, 131, 86));
        pbLoadCamera = new QPushButton(groupBox_9);
        pbLoadCamera->setObjectName(QStringLiteral("pbLoadCamera"));
        pbLoadCamera->setGeometry(QRect(5, 25, 46, 21));
        QIcon icon5;
        icon5.addFile(QStringLiteral("icon/webcam.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon5.addFile(QStringLiteral("C:/Users/Admin/.designer/backup/icon/stop.png"), QSize(), QIcon::Normal, QIcon::On);
        pbLoadCamera->setIcon(icon5);
        pbLoadCamera->setCheckable(true);
        pbLoadTestImage = new QPushButton(groupBox_9);
        pbLoadTestImage->setObjectName(QStringLiteral("pbLoadTestImage"));
        pbLoadTestImage->setGeometry(QRect(60, 25, 41, 21));
        QIcon icon6;
        icon6.addFile(QStringLiteral("icon/image.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLoadTestImage->setIcon(icon6);
        label_11 = new QLabel(groupBox_9);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(90, 55, 31, 16));
        leFPS = new QLineEdit(groupBox_9);
        leFPS->setObjectName(QStringLiteral("leFPS"));
        leFPS->setGeometry(QRect(5, 55, 76, 22));
        leFPS->setAlignment(Qt::AlignCenter);
        groupBox_10 = new QGroupBox(tResultCameraArea);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(5, 160, 276, 56));
        pbViewDataObjects = new QPushButton(groupBox_10);
        pbViewDataObjects->setObjectName(QStringLiteral("pbViewDataObjects"));
        pbViewDataObjects->setGeometry(QRect(10, 20, 141, 28));
        pbViewDataObjects->setStyleSheet(QStringLiteral(""));
        QIcon icon7;
        icon7.addFile(QStringLiteral("icon/icons8-object-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbViewDataObjects->setIcon(icon7);
        pbClearDetectObjects = new QPushButton(groupBox_10);
        pbClearDetectObjects->setObjectName(QStringLiteral("pbClearDetectObjects"));
        pbClearDetectObjects->setGeometry(QRect(155, 20, 111, 26));
        QIcon icon8;
        icon8.addFile(QStringLiteral("icon/Eraser_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbClearDetectObjects->setIcon(icon8);
        groupBox_13 = new QGroupBox(tResultCameraArea);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setGeometry(QRect(400, 225, 66, 126));
        label_48 = new QLabel(groupBox_13);
        label_48->setObjectName(QStringLiteral("label_48"));
        label_48->setGeometry(QRect(5, 25, 51, 16));
        label_48->setFont(font2);
        lbTrackingObjectNumber = new QLabel(groupBox_13);
        lbTrackingObjectNumber->setObjectName(QStringLiteral("lbTrackingObjectNumber"));
        lbTrackingObjectNumber->setGeometry(QRect(20, 50, 31, 16));
        QFont font4;
        font4.setPointSize(10);
        lbTrackingObjectNumber->setFont(font4);
        label_50 = new QLabel(groupBox_13);
        label_50->setObjectName(QStringLiteral("label_50"));
        label_50->setGeometry(QRect(10, 75, 51, 16));
        label_50->setFont(font2);
        lbVisibleObjectNumber = new QLabel(groupBox_13);
        lbVisibleObjectNumber->setObjectName(QStringLiteral("lbVisibleObjectNumber"));
        lbVisibleObjectNumber->setGeometry(QRect(20, 100, 31, 16));
        lbVisibleObjectNumber->setFont(font4);
        pbSwitchWorkFlow = new QPushButton(tResultCameraArea);
        pbSwitchWorkFlow->setObjectName(QStringLiteral("pbSwitchWorkFlow"));
        pbSwitchWorkFlow->setGeometry(QRect(360, 225, 36, 26));
        QIcon icon9;
        icon9.addFile(QStringLiteral("icon/icons8-next-page-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSwitchWorkFlow->setIcon(icon9);
        pbFilter = new QPushButton(tResultCameraArea);
        pbFilter->setObjectName(QStringLiteral("pbFilter"));
        pbFilter->setGeometry(QRect(285, 180, 71, 26));
        QIcon icon10;
        icon10.addFile(QStringLiteral("icon/Slider 2_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFilter->setIcon(icon10);
        pbSelection = new QPushButton(tResultCameraArea);
        pbSelection->setObjectName(QStringLiteral("pbSelection"));
        pbSelection->setGeometry(QRect(10, 120, 121, 26));
        QIcon icon11;
        icon11.addFile(QStringLiteral("icon/Cursor_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSelection->setIcon(icon11);
        twModule->addTab(tResultCameraArea, QString());
        tDrawing = new QWidget();
        tDrawing->setObjectName(QStringLiteral("tDrawing"));
        lbImageForDrawing = new QLabel(tDrawing);
        lbImageForDrawing->setObjectName(QStringLiteral("lbImageForDrawing"));
        lbImageForDrawing->setGeometry(QRect(10, 10, 246, 131));
        lbImageForDrawing->setStyleSheet(QStringLiteral("background-color: rgb(142, 254, 255);"));
        lbDrawingArea = new DrawingWidget(tDrawing);
        lbDrawingArea->setObjectName(QStringLiteral("lbDrawingArea"));
        lbDrawingArea->setGeometry(QRect(10, 154, 381, 380));
        lbDrawingArea->setStyleSheet(QStringLiteral("background-color: rgb(142, 254, 255);"));
        lbDrawingArea->setScaledContents(true);
        widget_2 = new QWidget(tDrawing);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(310, 10, 151, 21));
        widget_2->setStyleSheet(QStringLiteral("background-color: rgb(171, 225, 224);"));
        leDrawingThreshold = new QLineEdit(widget_2);
        leDrawingThreshold->setObjectName(QStringLiteral("leDrawingThreshold"));
        leDrawingThreshold->setGeometry(QRect(125, 4, 23, 15));
        QFont font5;
        font5.setPointSize(6);
        leDrawingThreshold->setFont(font5);
        hsDrawingThreshold = new QSlider(widget_2);
        hsDrawingThreshold->setObjectName(QStringLiteral("hsDrawingThreshold"));
        hsDrawingThreshold->setGeometry(QRect(5, 4, 111, 16));
        hsDrawingThreshold->setMaximum(255);
        hsDrawingThreshold->setSingleStep(1);
        hsDrawingThreshold->setValue(150);
        hsDrawingThreshold->setOrientation(Qt::Horizontal);
        widget_3 = new QWidget(tDrawing);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(215, 105, 37, 31));
        widget_3->setStyleSheet(QStringLiteral("background-color: rgb(221, 221, 221);"));
        lbImageWidth = new QLabel(widget_3);
        lbImageWidth->setObjectName(QStringLiteral("lbImageWidth"));
        lbImageWidth->setGeometry(QRect(2, 0, 39, 14));
        lbImageWidth->setFont(font5);
        lbImageWidth->setStyleSheet(QStringLiteral(""));
        lbImageHeight = new QLabel(widget_3);
        lbImageHeight->setObjectName(QStringLiteral("lbImageHeight"));
        lbImageHeight->setGeometry(QRect(2, 14, 35, 14));
        lbImageHeight->setFont(font5);
        lbImageHeight->setStyleSheet(QStringLiteral(""));
        widget_4 = new QWidget(tDrawing);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(265, 90, 43, 51));
        widget_4->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_18 = new QLabel(widget_4);
        label_18->setObjectName(QStringLiteral("label_18"));
        label_18->setGeometry(QRect(4, 5, 37, 16));
        label_18->setFont(font5);
        leHeightScale = new QLineEdit(widget_4);
        leHeightScale->setObjectName(QStringLiteral("leHeightScale"));
        leHeightScale->setGeometry(QRect(4, 25, 35, 18));
        widget_5 = new QWidget(tDrawing);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setGeometry(QRect(310, 90, 43, 51));
        widget_5->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_20 = new QLabel(widget_5);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(4, 5, 37, 16));
        label_20->setFont(font5);
        leWidthScale = new QLineEdit(widget_5);
        leWidthScale->setObjectName(QStringLiteral("leWidthScale"));
        leWidthScale->setGeometry(QRect(4, 25, 35, 18));
        widget_6 = new QWidget(tDrawing);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        widget_6->setGeometry(QRect(355, 90, 39, 51));
        widget_6->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_23 = new QLabel(widget_6);
        label_23->setObjectName(QStringLiteral("label_23"));
        label_23->setGeometry(QRect(2, 5, 35, 16));
        label_23->setFont(font5);
        label_23->setAlignment(Qt::AlignCenter);
        leSpace = new QLineEdit(widget_6);
        leSpace->setObjectName(QStringLiteral("leSpace"));
        leSpace->setGeometry(QRect(4, 25, 31, 18));
        pbDrawLine = new QPushButton(tDrawing);
        pbDrawLine->setObjectName(QStringLiteral("pbDrawLine"));
        pbDrawLine->setGeometry(QRect(400, 326, 28, 28));
        QIcon icon12;
        icon12.addFile(QStringLiteral("icon/Line_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawLine->setIcon(icon12);
        pbDrawRectangle = new QPushButton(tDrawing);
        pbDrawRectangle->setObjectName(QStringLiteral("pbDrawRectangle"));
        pbDrawRectangle->setGeometry(QRect(430, 326, 28, 28));
        QIcon icon13;
        icon13.addFile(QStringLiteral("icon/Rectangular_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawRectangle->setIcon(icon13);
        pbDrawArc = new QPushButton(tDrawing);
        pbDrawArc->setObjectName(QStringLiteral("pbDrawArc"));
        pbDrawArc->setGeometry(QRect(400, 356, 28, 28));
        QIcon icon14;
        icon14.addFile(QStringLiteral("icon/Circled Notch_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawArc->setIcon(icon14);
        pbDrawCircle = new QPushButton(tDrawing);
        pbDrawCircle->setObjectName(QStringLiteral("pbDrawCircle"));
        pbDrawCircle->setGeometry(QRect(430, 356, 28, 28));
        QIcon icon15;
        icon15.addFile(QStringLiteral("icon/Circle_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawCircle->setIcon(icon15);
        widget_7 = new QWidget(tDrawing);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        widget_7->setGeometry(QRect(405, 152, 53, 31));
        widget_7->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_19 = new QLabel(widget_7);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg1 = new QLineEdit(widget_7);
        leDrawAg1->setObjectName(QStringLiteral("leDrawAg1"));
        leDrawAg1->setGeometry(QRect(16, 6, 33, 22));
        widget_8 = new QWidget(tDrawing);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        widget_8->setGeometry(QRect(405, 186, 53, 31));
        widget_8->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_22 = new QLabel(widget_8);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg2 = new QLineEdit(widget_8);
        leDrawAg2->setObjectName(QStringLiteral("leDrawAg2"));
        leDrawAg2->setGeometry(QRect(16, 6, 33, 22));
        widget_9 = new QWidget(tDrawing);
        widget_9->setObjectName(QStringLiteral("widget_9"));
        widget_9->setGeometry(QRect(405, 220, 53, 31));
        widget_9->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_24 = new QLabel(widget_9);
        label_24->setObjectName(QStringLiteral("label_24"));
        label_24->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg3 = new QLineEdit(widget_9);
        leDrawAg3->setObjectName(QStringLiteral("leDrawAg3"));
        leDrawAg3->setGeometry(QRect(16, 6, 33, 22));
        widget_10 = new QWidget(tDrawing);
        widget_10->setObjectName(QStringLiteral("widget_10"));
        widget_10->setGeometry(QRect(405, 254, 53, 31));
        widget_10->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_25 = new QLabel(widget_10);
        label_25->setObjectName(QStringLiteral("label_25"));
        label_25->setGeometry(QRect(2, 8, 16, 16));
        label_25->setFont(font2);
        leDrawAg4 = new QLineEdit(widget_10);
        leDrawAg4->setObjectName(QStringLiteral("leDrawAg4"));
        leDrawAg4->setGeometry(QRect(16, 6, 33, 22));
        widget_11 = new QWidget(tDrawing);
        widget_11->setObjectName(QStringLiteral("widget_11"));
        widget_11->setGeometry(QRect(405, 288, 53, 31));
        widget_11->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        label_26 = new QLabel(widget_11);
        label_26->setObjectName(QStringLiteral("label_26"));
        label_26->setGeometry(QRect(6, 8, 16, 16));
        leDrawAg5 = new QLineEdit(widget_11);
        leDrawAg5->setObjectName(QStringLiteral("leDrawAg5"));
        leDrawAg5->setGeometry(QRect(16, 6, 33, 22));
        pbOpenPicture = new QPushButton(tDrawing);
        pbOpenPicture->setObjectName(QStringLiteral("pbOpenPicture"));
        pbOpenPicture->setGeometry(QRect(265, 10, 29, 21));
        QIcon icon16;
        icon16.addFile(QStringLiteral("icon/Full Image_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenPicture->setIcon(icon16);
        pbExportDrawingGcodes = new QPushButton(tDrawing);
        pbExportDrawingGcodes->setObjectName(QStringLiteral("pbExportDrawingGcodes"));
        pbExportDrawingGcodes->setGeometry(QRect(399, 485, 61, 46));
        pbPainting = new QPushButton(tDrawing);
        pbPainting->setObjectName(QStringLiteral("pbPainting"));
        pbPainting->setGeometry(QRect(400, 90, 61, 37));
        QIcon icon17;
        icon17.addFile(QStringLiteral("icon/Paint_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPainting->setIcon(icon17);
        pbPainting->setIconSize(QSize(20, 20));
        pbZoomIn = new QPushButton(tDrawing);
        pbZoomIn->setObjectName(QStringLiteral("pbZoomIn"));
        pbZoomIn->setGeometry(QRect(400, 386, 28, 28));
        QIcon icon18;
        icon18.addFile(QStringLiteral("icon/Zoom In_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomIn->setIcon(icon18);
        pbZoomOut = new QPushButton(tDrawing);
        pbZoomOut->setObjectName(QStringLiteral("pbZoomOut"));
        pbZoomOut->setGeometry(QRect(430, 386, 28, 28));
        QIcon icon19;
        icon19.addFile(QStringLiteral("icon/Zoom Out_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomOut->setIcon(icon19);
        label_21 = new QLabel(tDrawing);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(316, 505, 39, 16));
        pbCursor = new QPushButton(tDrawing);
        pbCursor->setObjectName(QStringLiteral("pbCursor"));
        pbCursor->setGeometry(QRect(430, 415, 28, 28));
        QIcon icon20;
        icon20.addFile(QStringLiteral("icon/Cursor-color_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCursor->setIcon(icon20);
        cbDrawingEffector = new QComboBox(tDrawing);
        cbDrawingEffector->setObjectName(QStringLiteral("cbDrawingEffector"));
        cbDrawingEffector->setGeometry(QRect(399, 455, 61, 22));
        widget_12 = new QWidget(tDrawing);
        widget_12->setObjectName(QStringLiteral("widget_12"));
        widget_12->setGeometry(QRect(265, 36, 69, 48));
        widget_12->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        cbDrawMethod = new QComboBox(widget_12);
        cbDrawMethod->setObjectName(QStringLiteral("cbDrawMethod"));
        cbDrawMethod->setGeometry(QRect(6, 20, 59, 22));
        label_13 = new QLabel(widget_12);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(8, 2, 55, 16));
        label_13->setFont(font5);
        widget_13 = new QWidget(tDrawing);
        widget_13->setObjectName(QStringLiteral("widget_13"));
        widget_13->setGeometry(QRect(340, 36, 123, 48));
        widget_13->setStyleSheet(QStringLiteral("background-color: rgb(234, 234, 234);"));
        cbConversionTool = new QComboBox(widget_13);
        cbConversionTool->setObjectName(QStringLiteral("cbConversionTool"));
        cbConversionTool->setGeometry(QRect(6, 20, 113, 22));
        label_14 = new QLabel(widget_13);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setGeometry(QRect(26, 2, 95, 16));
        label_14->setFont(font5);
        twModule->addTab(tDrawing, QString());
        twDeltaGeometry = new QTabWidget(centralWidget);
        twDeltaGeometry->setObjectName(QStringLiteral("twDeltaGeometry"));
        twDeltaGeometry->setGeometry(QRect(0, 112, 411, 521));
        t3D = new QWidget();
        t3D->setObjectName(QStringLiteral("t3D"));
        pbTurnOnROS = new QPushButton(t3D);
        pbTurnOnROS->setObjectName(QStringLiteral("pbTurnOnROS"));
        pbTurnOnROS->setGeometry(QRect(10, 20, 93, 28));
        widget = new QWidget(t3D);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 60, 405, 305));
        widget->setStyleSheet(QStringLiteral(""));
        frameROS = new QFrame(widget);
        frameROS->setObjectName(QStringLiteral("frameROS"));
        frameROS->setGeometry(QRect(0, 5, 400, 300));
        frameROS->setStyleSheet(QStringLiteral(""));
        frameROS->setFrameShape(QFrame::StyledPanel);
        frameROS->setFrameShadow(QFrame::Raised);
        groupBox_3 = new QGroupBox(t3D);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(15, 370, 146, 116));
        cbROSCameraView = new QComboBox(groupBox_3);
        cbROSCameraView->setObjectName(QStringLiteral("cbROSCameraView"));
        cbROSCameraView->setGeometry(QRect(95, 30, 41, 22));
        label = new QLabel(groupBox_3);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 81, 16));
        groupBox_4 = new QGroupBox(t3D);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(170, 370, 231, 116));
        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 30, 81, 16));
        cbEndEffector = new QComboBox(groupBox_4);
        cbEndEffector->setObjectName(QStringLiteral("cbEndEffector"));
        cbEndEffector->setGeometry(QRect(110, 30, 111, 22));
        twDeltaGeometry->addTab(t3D, QString());
        t2D = new QWidget();
        t2D->setObjectName(QStringLiteral("t2D"));
        wg2D = new QWidget(t2D);
        wg2D->setObjectName(QStringLiteral("wg2D"));
        wg2D->setGeometry(QRect(50, 10, 300, 300));
        wg2D->setStyleSheet(QStringLiteral("background-color: rgb(230, 230, 230);"));
        vsZAdjsution = new QSlider(t2D);
        vsZAdjsution->setObjectName(QStringLiteral("vsZAdjsution"));
        vsZAdjsution->setGeometry(QRect(10, 9, 22, 301));
        vsZAdjsution->setMaximum(300);
        vsZAdjsution->setOrientation(Qt::Vertical);
        vsAngleAdjsution = new QSlider(t2D);
        vsAngleAdjsution->setObjectName(QStringLiteral("vsAngleAdjsution"));
        vsAngleAdjsution->setGeometry(QRect(95, 326, 253, 22));
        vsAngleAdjsution->setMaximum(180);
        vsAngleAdjsution->setOrientation(Qt::Horizontal);
        label_15 = new QLabel(t2D);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(14, 324, 17, 16));
        label_16 = new QLabel(t2D);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(54, 328, 55, 16));
        groupBox_5 = new QGroupBox(t2D);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(7, 363, 406, 126));
        label_28 = new QLabel(groupBox_5);
        label_28->setObjectName(QStringLiteral("label_28"));
        label_28->setGeometry(QRect(345, 36, 31, 16));
        pbRight = new QPushButton(groupBox_5);
        pbRight->setObjectName(QStringLiteral("pbRight"));
        pbRight->setGeometry(QRect(106, 69, 37, 28));
        pbBackward = new QPushButton(groupBox_5);
        pbBackward->setObjectName(QStringLiteral("pbBackward"));
        pbBackward->setGeometry(QRect(70, 95, 37, 28));
        cbDivision = new QComboBox(groupBox_5);
        cbDivision->setObjectName(QStringLiteral("cbDivision"));
        cbDivision->setGeometry(QRect(283, 32, 51, 22));
        pbForward = new QPushButton(groupBox_5);
        pbForward->setObjectName(QStringLiteral("pbForward"));
        pbForward->setGeometry(QRect(70, 43, 37, 28));
        pbLeft = new QPushButton(groupBox_5);
        pbLeft->setObjectName(QStringLiteral("pbLeft"));
        pbLeft->setGeometry(QRect(34, 69, 37, 28));
        pbUp = new QPushButton(groupBox_5);
        pbUp->setObjectName(QStringLiteral("pbUp"));
        pbUp->setGeometry(QRect(154, 43, 37, 28));
        pbDown = new QPushButton(groupBox_5);
        pbDown->setObjectName(QStringLiteral("pbDown"));
        pbDown->setGeometry(QRect(154, 95, 37, 28));
        label_29 = new QLabel(groupBox_5);
        label_29->setObjectName(QStringLiteral("label_29"));
        label_29->setGeometry(QRect(223, 66, 55, 16));
        leVelocity = new QLineEdit(groupBox_5);
        leVelocity->setObjectName(QStringLiteral("leVelocity"));
        leVelocity->setGeometry(QRect(283, 66, 53, 22));
        label_30 = new QLabel(groupBox_5);
        label_30->setObjectName(QStringLiteral("label_30"));
        label_30->setGeometry(QRect(345, 72, 41, 16));
        label_31 = new QLabel(groupBox_5);
        label_31->setObjectName(QStringLiteral("label_31"));
        label_31->setGeometry(QRect(223, 98, 55, 16));
        leAccel = new QLineEdit(groupBox_5);
        leAccel->setObjectName(QStringLiteral("leAccel"));
        leAccel->setGeometry(QRect(283, 98, 53, 22));
        label_32 = new QLabel(groupBox_5);
        label_32->setObjectName(QStringLiteral("label_32"));
        label_32->setGeometry(QRect(345, 102, 55, 16));
        label_33 = new QLabel(groupBox_5);
        label_33->setObjectName(QStringLiteral("label_33"));
        label_33->setGeometry(QRect(223, 34, 55, 16));
        label_46 = new QLabel(groupBox_5);
        label_46->setObjectName(QStringLiteral("label_46"));
        label_46->setGeometry(QRect(85, 15, 126, 16));
        label_46->setFont(font2);
        twDeltaGeometry->addTab(t2D, QString());
        pbConnect = new QPushButton(centralWidget);
        pbConnect->setObjectName(QStringLiteral("pbConnect"));
        pbConnect->setGeometry(QRect(5, 40, 81, 41));
        pbConnect->setStyleSheet(QLatin1String("background-color: rgb(30, 88, 180);\n"
"color: rgb(255, 255, 255);"));
        QIcon icon21;
        icon21.addFile(QStringLiteral("C:/Users/Admin/.designer/backup/icon/disconnected.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon21.addFile(QStringLiteral("C:/Users/Admin/.designer/backup/icon/connected.png"), QSize(), QIcon::Normal, QIcon::On);
        pbConnect->setIcon(icon21);
        pbConnect->setIconSize(QSize(30, 20));
        lbID = new QLabel(centralWidget);
        lbID->setObjectName(QStringLiteral("lbID"));
        lbID->setGeometry(QRect(100, 45, 55, 16));
        gbGripper = new QGroupBox(centralWidget);
        gbGripper->setObjectName(QStringLiteral("gbGripper"));
        gbGripper->setGeometry(QRect(515, 28, 131, 80));
        pbGrip = new QPushButton(gbGripper);
        pbGrip->setObjectName(QStringLiteral("pbGrip"));
        pbGrip->setGeometry(QRect(10, 20, 45, 33));
        pbGrip->setAutoFillBackground(false);
        pbGrip->setAutoDefault(false);
        pbGrip->setFlat(false);
        hsGripperAngle = new QSlider(gbGripper);
        hsGripperAngle->setObjectName(QStringLiteral("hsGripperAngle"));
        hsGripperAngle->setGeometry(QRect(6, 60, 119, 16));
        hsGripperAngle->setMaximum(20);
        hsGripperAngle->setSingleStep(5);
        hsGripperAngle->setOrientation(Qt::Horizontal);
        leGripperMin = new QLineEdit(gbGripper);
        leGripperMin->setObjectName(QStringLiteral("leGripperMin"));
        leGripperMin->setGeometry(QRect(60, 34, 29, 17));
        leGripperMax = new QLineEdit(gbGripper);
        leGripperMax->setObjectName(QStringLiteral("leGripperMax"));
        leGripperMax->setGeometry(QRect(94, 34, 29, 17));
        label_17 = new QLabel(gbGripper);
        label_17->setObjectName(QStringLiteral("label_17"));
        label_17->setGeometry(QRect(66, 18, 25, 13));
        label_17->setFont(font5);
        label_27 = new QLabel(gbGripper);
        label_27->setObjectName(QStringLiteral("label_27"));
        label_27->setGeometry(QRect(100, 18, 25, 13));
        label_27->setFont(font5);
        gbRelay = new QGroupBox(centralWidget);
        gbRelay->setObjectName(QStringLiteral("gbRelay"));
        gbRelay->setGeometry(QRect(415, 28, 91, 80));
        pbPump = new QPushButton(gbRelay);
        pbPump->setObjectName(QStringLiteral("pbPump"));
        pbPump->setGeometry(QRect(15, 50, 31, 27));
        pbPump->setAutoFillBackground(false);
        QIcon icon22;
        icon22.addFile(QStringLiteral("icon/Toggle Off_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon22.addFile(QStringLiteral("icon/Toggle On_16px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbPump->setIcon(icon22);
        pbPump->setCheckable(true);
        pbPump->setChecked(false);
        pbPump->setAutoDefault(false);
        pbPump->setFlat(false);
        label_34 = new QLabel(gbRelay);
        label_34->setObjectName(QStringLiteral("label_34"));
        label_34->setGeometry(QRect(10, 20, 51, 20));
        label_34->setFont(font5);
        pbLaser = new QPushButton(gbRelay);
        pbLaser->setObjectName(QStringLiteral("pbLaser"));
        pbLaser->setGeometry(QRect(55, 50, 31, 27));
        pbLaser->setAutoFillBackground(false);
        pbLaser->setIcon(icon22);
        pbLaser->setCheckable(true);
        pbLaser->setChecked(false);
        pbLaser->setAutoDefault(false);
        pbLaser->setFlat(false);
        label_35 = new QLabel(gbRelay);
        label_35->setObjectName(QStringLiteral("label_35"));
        label_35->setGeometry(QRect(60, 20, 51, 20));
        label_35->setFont(font5);
        gbMovement1 = new QGroupBox(centralWidget);
        gbMovement1->setObjectName(QStringLiteral("gbMovement1"));
        gbMovement1->setGeometry(QRect(185, 28, 236, 80));
        leY = new QLineEdit(gbMovement1);
        leY->setObjectName(QStringLiteral("leY"));
        leY->setGeometry(QRect(110, 52, 36, 21));
        leZ = new QLineEdit(gbMovement1);
        leZ->setObjectName(QStringLiteral("leZ"));
        leZ->setGeometry(QRect(150, 52, 36, 21));
        pbY = new QPushButton(gbMovement1);
        pbY->setObjectName(QStringLiteral("pbY"));
        pbY->setGeometry(QRect(110, 22, 36, 27));
        pbX = new QPushButton(gbMovement1);
        pbX->setObjectName(QStringLiteral("pbX"));
        pbX->setGeometry(QRect(70, 22, 36, 27));
        leX = new QLineEdit(gbMovement1);
        leX->setObjectName(QStringLiteral("leX"));
        leX->setGeometry(QRect(70, 52, 36, 21));
        leW = new QLineEdit(gbMovement1);
        leW->setObjectName(QStringLiteral("leW"));
        leW->setGeometry(QRect(190, 52, 36, 21));
        pbZ = new QPushButton(gbMovement1);
        pbZ->setObjectName(QStringLiteral("pbZ"));
        pbZ->setGeometry(QRect(150, 22, 36, 27));
        pbW = new QPushButton(gbMovement1);
        pbW->setObjectName(QStringLiteral("pbW"));
        pbW->setGeometry(QRect(190, 22, 36, 27));
        pbHome = new QPushButton(gbMovement1);
        pbHome->setObjectName(QStringLiteral("pbHome"));
        pbHome->setGeometry(QRect(10, 22, 51, 51));
        QIcon icon23;
        icon23.addFile(QStringLiteral("icon/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbHome->setIcon(icon23);
        pbHome->setIconSize(QSize(30, 30));
        twConveyor = new QTabWidget(centralWidget);
        twConveyor->setObjectName(QStringLiteral("twConveyor"));
        twConveyor->setGeometry(QRect(655, 20, 236, 91));
        tConveyor = new QWidget();
        tConveyor->setObjectName(QStringLiteral("tConveyor"));
        cbConveyorMode = new QComboBox(tConveyor);
        cbConveyorMode->setObjectName(QStringLiteral("cbConveyorMode"));
        cbConveyorMode->setGeometry(QRect(95, 5, 71, 24));
        QFont font6;
        font6.setPointSize(7);
        cbConveyorMode->setFont(font6);
        cbConveyorValueType = new QComboBox(tConveyor);
        cbConveyorValueType->setObjectName(QStringLiteral("cbConveyorValueType"));
        cbConveyorValueType->setGeometry(QRect(110, 35, 56, 25));
        cbConveyorValueType->setFont(font6);
        leConveyorvMovingValue = new QLineEdit(tConveyor);
        leConveyorvMovingValue->setObjectName(QStringLiteral("leConveyorvMovingValue"));
        leConveyorvMovingValue->setGeometry(QRect(53, 35, 46, 25));
        leConveyorvMovingValue->setFont(font2);
        pbConveyorMove = new QPushButton(tConveyor);
        pbConveyorMove->setObjectName(QStringLiteral("pbConveyorMove"));
        pbConveyorMove->setGeometry(QRect(5, 35, 41, 25));
        pbConveyorConnect = new QPushButton(tConveyor);
        pbConveyorConnect->setObjectName(QStringLiteral("pbConveyorConnect"));
        pbConveyorConnect->setGeometry(QRect(5, 5, 81, 25));
        twConveyor->addTab(tConveyor, QString());
        sSlidingRail = new QWidget();
        sSlidingRail->setObjectName(QStringLiteral("sSlidingRail"));
        pbSlidingConnect = new QPushButton(sSlidingRail);
        pbSlidingConnect->setObjectName(QStringLiteral("pbSlidingConnect"));
        pbSlidingConnect->setGeometry(QRect(5, 5, 96, 26));
        QIcon icon24;
        icon24.addFile(QStringLiteral("icon/connected.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingConnect->setIcon(icon24);
        pbSlidingHome = new QPushButton(sSlidingRail);
        pbSlidingHome->setObjectName(QStringLiteral("pbSlidingHome"));
        pbSlidingHome->setGeometry(QRect(5, 35, 51, 26));
        QIcon icon25;
        icon25.addFile(QStringLiteral("icon/icons8-home-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingHome->setIcon(icon25);
        leSlidingSpeed = new QLineEdit(sSlidingRail);
        leSlidingSpeed->setObjectName(QStringLiteral("leSlidingSpeed"));
        leSlidingSpeed->setGeometry(QRect(110, 35, 36, 21));
        leSlidingPosition = new QLineEdit(sSlidingRail);
        leSlidingPosition->setObjectName(QStringLiteral("leSlidingPosition"));
        leSlidingPosition->setGeometry(QRect(170, 35, 41, 21));
        pbSlidingDisable = new QPushButton(sSlidingRail);
        pbSlidingDisable->setObjectName(QStringLiteral("pbSlidingDisable"));
        pbSlidingDisable->setGeometry(QRect(60, 35, 41, 26));
        QIcon icon26;
        icon26.addFile(QStringLiteral("icon/icons8-sleeping-in-bed-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingDisable->setIcon(icon26);
        label_36 = new QLabel(sSlidingRail);
        label_36->setObjectName(QStringLiteral("label_36"));
        label_36->setGeometry(QRect(110, 10, 46, 16));
        label_36->setFont(font2);
        label_37 = new QLabel(sSlidingRail);
        label_37->setObjectName(QStringLiteral("label_37"));
        label_37->setGeometry(QRect(170, 10, 51, 16));
        label_37->setFont(font2);
        twConveyor->addTab(sSlidingRail, QString());
        checkBox = new QCheckBox(centralWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(5, 85, 81, 20));
        checkBox->setChecked(true);
        label_52 = new QLabel(centralWidget);
        label_52->setObjectName(QStringLiteral("label_52"));
        label_52->setGeometry(QRect(10, 665, 55, 16));
        pbFormat = new QPushButton(centralWidget);
        pbFormat->setObjectName(QStringLiteral("pbFormat"));
        pbFormat->setGeometry(QRect(900, 410, 91, 36));
        QIcon icon27;
        icon27.addFile(QStringLiteral("icon/index.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFormat->setIcon(icon27);
        pbFormat->setIconSize(QSize(30, 30));
        cbLockGcodeEditor = new QCheckBox(centralWidget);
        cbLockGcodeEditor->setObjectName(QStringLiteral("cbLockGcodeEditor"));
        cbLockGcodeEditor->setGeometry(QRect(900, 115, 91, 20));
        cbLockGcodeEditor->setFont(font2);
        cbAutoNumbering = new QCheckBox(centralWidget);
        cbAutoNumbering->setObjectName(QStringLiteral("cbAutoNumbering"));
        cbAutoNumbering->setGeometry(QRect(905, 470, 121, 16));
        cbAutoNumbering->setChecked(true);
        gbVar = new QGroupBox(centralWidget);
        gbVar->setObjectName(QStringLiteral("gbVar"));
        gbVar->setGeometry(QRect(1215, 105, 71, 411));
        lbVar6 = new QLabel(gbVar);
        lbVar6->setObjectName(QStringLiteral("lbVar6"));
        lbVar6->setGeometry(QRect(15, 390, 41, 16));
        lbVar6->setStyleSheet(QStringLiteral("background-color: rgb(225, 225, 225);"));
        lbVar6->setAlignment(Qt::AlignCenter);
        lbVar4 = new QLabel(gbVar);
        lbVar4->setObjectName(QStringLiteral("lbVar4"));
        lbVar4->setGeometry(QRect(15, 300, 41, 16));
        lbVar4->setStyleSheet(QStringLiteral("background-color: rgb(225, 225, 225);"));
        lbVar4->setAlignment(Qt::AlignCenter);
        leVariable2 = new QLineEdit(gbVar);
        leVariable2->setObjectName(QStringLiteral("leVariable2"));
        leVariable2->setGeometry(QRect(15, 180, 41, 22));
        leVariable4 = new QLineEdit(gbVar);
        leVariable4->setObjectName(QStringLiteral("leVariable4"));
        leVariable4->setGeometry(QRect(16, 275, 41, 22));
        leVariable6 = new QLineEdit(gbVar);
        leVariable6->setObjectName(QStringLiteral("leVariable6"));
        leVariable6->setGeometry(QRect(15, 365, 41, 22));
        lbVar5 = new QLabel(gbVar);
        lbVar5->setObjectName(QStringLiteral("lbVar5"));
        lbVar5->setGeometry(QRect(15, 345, 41, 16));
        lbVar5->setStyleSheet(QStringLiteral("background-color: rgb(225, 225, 225);"));
        lbVar5->setAlignment(Qt::AlignCenter);
        lbVar1 = new QLabel(gbVar);
        lbVar1->setObjectName(QStringLiteral("lbVar1"));
        lbVar1->setGeometry(QRect(15, 160, 41, 16));
        lbVar1->setStyleSheet(QStringLiteral("background-color: rgb(225, 225, 225);"));
        lbVar1->setAlignment(Qt::AlignCenter);
        leVariable3 = new QLineEdit(gbVar);
        leVariable3->setObjectName(QStringLiteral("leVariable3"));
        leVariable3->setGeometry(QRect(15, 225, 41, 22));
        leVariable1 = new QLineEdit(gbVar);
        leVariable1->setObjectName(QStringLiteral("leVariable1"));
        leVariable1->setGeometry(QRect(14, 135, 41, 22));
        lbVar3 = new QLabel(gbVar);
        lbVar3->setObjectName(QStringLiteral("lbVar3"));
        lbVar3->setGeometry(QRect(15, 250, 41, 16));
        lbVar3->setStyleSheet(QStringLiteral("background-color: rgb(225, 225, 225);"));
        lbVar3->setAlignment(Qt::AlignCenter);
        leVariable5 = new QLineEdit(gbVar);
        leVariable5->setObjectName(QStringLiteral("leVariable5"));
        leVariable5->setGeometry(QRect(15, 320, 41, 22));
        lbVar2 = new QLabel(gbVar);
        lbVar2->setObjectName(QStringLiteral("lbVar2"));
        lbVar2->setGeometry(QRect(15, 205, 41, 16));
        lbVar2->setStyleSheet(QStringLiteral("background-color: rgb(225, 225, 225);"));
        lbVar2->setAlignment(Qt::AlignCenter);
        pbExternalControllerConnect = new QPushButton(gbVar);
        pbExternalControllerConnect->setObjectName(QStringLiteral("pbExternalControllerConnect"));
        pbExternalControllerConnect->setGeometry(QRect(0, 80, 71, 31));
        pbExternalControllerConnect->setFont(font6);
        lbECComName = new QLabel(gbVar);
        lbECComName->setObjectName(QStringLiteral("lbECComName"));
        lbECComName->setGeometry(QRect(10, 50, 55, 26));
        lbECComName->setTextFormat(Qt::AutoText);
        lbECComName->setScaledContents(false);
        lbECComName->setAlignment(Qt::AlignCenter);
        pteGcodeArea = new CodeEditor(centralWidget);
        pteGcodeArea->setObjectName(QStringLiteral("pteGcodeArea"));
        pteGcodeArea->setGeometry(QRect(900, 145, 310, 261));
        pteGcodeArea->setMinimumSize(QSize(310, 250));
        pteGcodeArea->setFont(font2);
        pteGcodeArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        cbPositionToExecuteGcode = new QComboBox(centralWidget);
        cbPositionToExecuteGcode->setObjectName(QStringLiteral("cbPositionToExecuteGcode"));
        cbPositionToExecuteGcode->setGeometry(QRect(1155, 470, 56, 21));
        cbPositionToExecuteGcode->setFont(font5);
        cbFormatColor = new QCheckBox(centralWidget);
        cbFormatColor->setObjectName(QStringLiteral("cbFormatColor"));
        cbFormatColor->setGeometry(QRect(905, 450, 71, 16));
        cbFormatColor->setChecked(true);
        pbExecuteGcodes = new QPushButton(centralWidget);
        pbExecuteGcodes->setObjectName(QStringLiteral("pbExecuteGcodes"));
        pbExecuteGcodes->setGeometry(QRect(1155, 410, 56, 56));
        pbExecuteGcodes->setAutoFillBackground(false);
        QIcon icon28;
        icon28.addFile(QStringLiteral("icon/Play_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon28.addFile(QStringLiteral("icon/Pause_96px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbExecuteGcodes->setIcon(icon28);
        pbExecuteGcodes->setIconSize(QSize(70, 70));
        pbExecuteGcodes->setCheckable(true);
        pbExecuteGcodes->setFlat(false);
        gbAddGcode = new QGroupBox(centralWidget);
        gbAddGcode->setObjectName(QStringLiteral("gbAddGcode"));
        gbAddGcode->setGeometry(QRect(900, 15, 386, 86));
        lbAg1 = new QLabel(gbAddGcode);
        lbAg1->setObjectName(QStringLiteral("lbAg1"));
        lbAg1->setGeometry(QRect(85, 30, 16, 20));
        lbAg1->setStyleSheet(QStringLiteral("background-color: rgb(124, 221, 235);"));
        lbAg1->setAlignment(Qt::AlignCenter);
        leAg6 = new QLineEdit(gbAddGcode);
        leAg6->setObjectName(QStringLiteral("leAg6"));
        leAg6->setGeometry(QRect(305, 29, 26, 21));
        leAg6->setReadOnly(false);
        lbAg2 = new QLabel(gbAddGcode);
        lbAg2->setObjectName(QStringLiteral("lbAg2"));
        lbAg2->setGeometry(QRect(128, 30, 16, 20));
        lbAg2->setStyleSheet(QStringLiteral("background-color: rgb(124, 221, 235);"));
        lbAg2->setAlignment(Qt::AlignCenter);
        leAg5 = new QLineEdit(gbAddGcode);
        leAg5->setObjectName(QStringLiteral("leAg5"));
        leAg5->setGeometry(QRect(265, 29, 26, 21));
        leAg5->setReadOnly(false);
        lbAg3 = new QLabel(gbAddGcode);
        lbAg3->setObjectName(QStringLiteral("lbAg3"));
        lbAg3->setGeometry(QRect(170, 30, 16, 20));
        lbAg3->setStyleSheet(QStringLiteral("background-color: rgb(124, 221, 235);"));
        lbAg3->setAlignment(Qt::AlignCenter);
        lbAg5 = new QLabel(gbAddGcode);
        lbAg5->setObjectName(QStringLiteral("lbAg5"));
        lbAg5->setGeometry(QRect(250, 30, 16, 20));
        lbAg5->setStyleSheet(QStringLiteral("background-color: rgb(124, 221, 235);"));
        lbAg5->setAlignment(Qt::AlignCenter);
        lbAg6 = new QLabel(gbAddGcode);
        lbAg6->setObjectName(QStringLiteral("lbAg6"));
        lbAg6->setGeometry(QRect(290, 30, 16, 20));
        lbAg6->setStyleSheet(QStringLiteral("background-color: rgb(124, 221, 235);"));
        leAg3 = new QLineEdit(gbAddGcode);
        leAg3->setObjectName(QStringLiteral("leAg3"));
        leAg3->setGeometry(QRect(185, 29, 26, 21));
        leAg3->setReadOnly(false);
        lbAg4 = new QLabel(gbAddGcode);
        lbAg4->setObjectName(QStringLiteral("lbAg4"));
        lbAg4->setGeometry(QRect(210, 30, 16, 20));
        lbAg4->setStyleSheet(QStringLiteral("background-color: rgb(124, 221, 235);"));
        lbAg4->setAlignment(Qt::AlignCenter);
        leAg4 = new QLineEdit(gbAddGcode);
        leAg4->setObjectName(QStringLiteral("leAg4"));
        leAg4->setGeometry(QRect(225, 29, 26, 21));
        leAg4->setReadOnly(false);
        leAg2 = new QLineEdit(gbAddGcode);
        leAg2->setObjectName(QStringLiteral("leAg2"));
        leAg2->setGeometry(QRect(143, 29, 26, 21));
        leAg2->setReadOnly(false);
        leAg1 = new QLineEdit(gbAddGcode);
        leAg1->setObjectName(QStringLiteral("leAg1"));
        leAg1->setGeometry(QRect(101, 29, 26, 21));
        leAg1->setFont(font2);
        leAg1->setReadOnly(false);
        pbGcodeReference = new QPushButton(gbAddGcode);
        pbGcodeReference->setObjectName(QStringLiteral("pbGcodeReference"));
        pbGcodeReference->setGeometry(QRect(140, 55, 86, 26));
        QIcon icon29;
        icon29.addFile(QStringLiteral("icon/Help_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbGcodeReference->setIcon(icon29);
        pbAddGcode = new QPushButton(gbAddGcode);
        pbAddGcode->setObjectName(QStringLiteral("pbAddGcode"));
        pbAddGcode->setGeometry(QRect(5, 55, 126, 26));
        QIcon icon30;
        icon30.addFile(QStringLiteral("icon/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbAddGcode->setIcon(icon30);
        pbAddGcode->setAutoDefault(false);
        pbAddGcode->setFlat(false);
        cbGcode = new QComboBox(gbAddGcode);
        cbGcode->setObjectName(QStringLiteral("cbGcode"));
        cbGcode->setGeometry(QRect(5, 25, 66, 26));
        lbAg1->raise();
        lbAg2->raise();
        lbAg3->raise();
        lbAg5->raise();
        lbAg6->raise();
        leAg3->raise();
        lbAg4->raise();
        leAg4->raise();
        leAg2->raise();
        leAg1->raise();
        pbGcodeReference->raise();
        pbAddGcode->raise();
        cbGcode->raise();
        leAg6->raise();
        leAg5->raise();
        pbSaveGcode = new QPushButton(centralWidget);
        pbSaveGcode->setObjectName(QStringLiteral("pbSaveGcode"));
        pbSaveGcode->setGeometry(QRect(1135, 105, 76, 36));
        QIcon icon31;
        icon31.addFile(QStringLiteral("icon/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSaveGcode->setIcon(icon31);
        pbSaveGcode->setIconSize(QSize(30, 30));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(900, 500, 391, 181));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pbFindGcodeFile = new QPushButton(tab);
        pbFindGcodeFile->setObjectName(QStringLiteral("pbFindGcodeFile"));
        pbFindGcodeFile->setGeometry(QRect(5, 80, 55, 31));
        QIcon icon32;
        icon32.addFile(QStringLiteral("icon/Search_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFindGcodeFile->setIcon(icon32);
        pbFindGcodeFile->setIconSize(QSize(16, 16));
        pbFindGcodeFile->setFlat(false);
        pbRefreshGcodeFiles = new QPushButton(tab);
        pbRefreshGcodeFiles->setObjectName(QStringLiteral("pbRefreshGcodeFiles"));
        pbRefreshGcodeFiles->setGeometry(QRect(5, 44, 55, 31));
        QIcon icon33;
        icon33.addFile(QStringLiteral("icon/Restart_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRefreshGcodeFiles->setIcon(icon33);
        pbRefreshGcodeFiles->setIconSize(QSize(16, 16));
        pbRefreshGcodeFiles->setFlat(false);
        pbAddNewProgram = new QPushButton(tab);
        pbAddNewProgram->setObjectName(QStringLiteral("pbAddNewProgram"));
        pbAddNewProgram->setGeometry(QRect(5, 8, 56, 31));
        pbAddNewProgram->setIcon(icon30);
        pbAddNewProgram->setIconSize(QSize(16, 16));
        pbAddNewProgram->setFlat(false);
        saProgramFiles = new QScrollArea(tab);
        saProgramFiles->setObjectName(QStringLiteral("saProgramFiles"));
        saProgramFiles->setEnabled(true);
        saProgramFiles->setGeometry(QRect(75, 11, 240, 140));
        saProgramFiles->setMinimumSize(QSize(240, 140));
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
        frExProgram->setGeometry(QRect(5, 10, 221, 61));
        frExProgram->setStyleSheet(QStringLiteral("background-color:rgb(209, 209, 209)"));
        frExProgram->setFrameShape(QFrame::StyledPanel);
        frExProgram->setFrameShadow(QFrame::Raised);
        leExProgramName = new QLineEdit(frExProgram);
        leExProgramName->setObjectName(QStringLiteral("leExProgramName"));
        leExProgramName->setEnabled(true);
        leExProgramName->setGeometry(QRect(10, 5, 160, 30));
        leExProgramName->setFont(font4);
        leExProgramName->setCursor(QCursor(Qt::SizeHorCursor));
        leExProgramName->setStyleSheet(QStringLiteral(""));
        pbExDeleteProgram = new QPushButton(frExProgram);
        pbExDeleteProgram->setObjectName(QStringLiteral("pbExDeleteProgram"));
        pbExDeleteProgram->setGeometry(QRect(180, 5, 30, 31));
        QIcon icon34;
        icon34.addFile(QStringLiteral("C:/Users/Admin/.designer/backup/icon/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbExDeleteProgram->setIcon(icon34);
        pbExDeleteProgram->setIconSize(QSize(30, 30));
        pbExDeleteProgram->setAutoDefault(false);
        pbExDeleteProgram->setFlat(true);
        lbExGCodeNumber = new QLabel(frExProgram);
        lbExGCodeNumber->setObjectName(QStringLiteral("lbExGCodeNumber"));
        lbExGCodeNumber->setGeometry(QRect(10, 40, 101, 16));
        saProgramFiles->setWidget(wgProgramContainer);
        pbSortGcodeFiles = new QPushButton(tab);
        pbSortGcodeFiles->setObjectName(QStringLiteral("pbSortGcodeFiles"));
        pbSortGcodeFiles->setGeometry(QRect(5, 116, 55, 31));
        QIcon icon35;
        icon35.addFile(QStringLiteral("icon/Sort_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSortGcodeFiles->setIcon(icon35);
        pbSortGcodeFiles->setIconSize(QSize(16, 16));
        pbSortGcodeFiles->setFlat(false);
        pbUploadProgram = new QPushButton(tab);
        pbUploadProgram->setObjectName(QStringLiteral("pbUploadProgram"));
        pbUploadProgram->setGeometry(QRect(325, 10, 56, 36));
        QIcon icon36;
        icon36.addFile(QStringLiteral("icon/icons8-upload-to-cloud-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbUploadProgram->setIcon(icon36);
        pbUploadProgram->setIconSize(QSize(32, 32));
        pbUploadProgram->setFlat(false);
        pbImportGcodeFiles = new QPushButton(tab);
        pbImportGcodeFiles->setObjectName(QStringLiteral("pbImportGcodeFiles"));
        pbImportGcodeFiles->setGeometry(QRect(325, 50, 56, 36));
        pbImportGcodeFiles->setIconSize(QSize(32, 32));
        pbImportGcodeFiles->setFlat(false);
        tabWidget->addTab(tab, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        listWidget = new QListWidget(tab_3);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(5, 10, 171, 136));
        textEdit = new QTextEdit(tab_3);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(185, 10, 166, 91));
        pbUploadProgram_2 = new QPushButton(tab_3);
        pbUploadProgram_2->setObjectName(QStringLiteral("pbUploadProgram_2"));
        pbUploadProgram_2->setGeometry(QRect(185, 110, 56, 36));
        QIcon icon37;
        icon37.addFile(QStringLiteral("C:/Users/Admin/.designer/backup/icon/icons8-download-from-cloud-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbUploadProgram_2->setIcon(icon37);
        pbUploadProgram_2->setIconSize(QSize(32, 32));
        pbUploadProgram_2->setFlat(false);
        tabWidget->addTab(tab_3, QString());
        lbID_2 = new QLabel(centralWidget);
        lbID_2->setObjectName(QStringLiteral("lbID_2"));
        lbID_2->setGeometry(QRect(100, 65, 71, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1293, 26));
        menuBar->setStyleSheet(QLatin1String("background-color: rgb(55, 58, 72);\n"
"color: rgb(166, 156, 157);\n"
"selection-color: rgb(255, 255, 255);\n"
"selection-background-color: rgb(0, 204, 204);"));
        menuBar->setDefaultUp(false);
        menuBar->setNativeMenuBar(true);
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        menuReferences = new QMenu(menuHelp);
        menuReferences->setObjectName(QStringLiteral("menuReferences"));
        menuEditor = new QMenu(menuBar);
        menuEditor->setObjectName(QStringLiteral("menuEditor"));
        menuExecute = new QMenu(menuEditor);
        menuExecute->setObjectName(QStringLiteral("menuExecute"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QStringLiteral("menuSetting"));
        menuConnection = new QMenu(menuSetting);
        menuConnection->setObjectName(QStringLiteral("menuConnection"));
        menuUI = new QMenu(menuSetting);
        menuUI->setObjectName(QStringLiteral("menuUI"));
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
        twModule->setCurrentIndex(1);
        twDeltaGeometry->setCurrentIndex(1);
        pbGrip->setDefault(false);
        pbPump->setDefault(false);
        pbLaser->setDefault(false);
        twConveyor->setCurrentIndex(0);
        pbAddGcode->setDefault(false);
        tabWidget->setCurrentIndex(0);
        pbExDeleteProgram->setDefault(true);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "IMWI - Delta X Software - Version 0.9.2", Q_NULLPTR));
        actionAdd->setText(QApplication::translate("MainWindow", "Add New", Q_NULLPTR));
        actionRemove->setText(QApplication::translate("MainWindow", "Remove", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        actionGcode->setText(QApplication::translate("MainWindow", "Gcode", Q_NULLPTR));
        actionSoftware->setText(QApplication::translate("MainWindow", "Software", Q_NULLPTR));
        actionExecute_All->setText(QApplication::translate("MainWindow", "Execute All", Q_NULLPTR));
        actionDelta_X_1->setText(QApplication::translate("MainWindow", "Delta X 1", Q_NULLPTR));
        actionExecute->setText(QApplication::translate("MainWindow", "Execute", Q_NULLPTR));
        actionBaudrate->setText(QApplication::translate("MainWindow", "Baudrate", Q_NULLPTR));
        actionScale->setText(QApplication::translate("MainWindow", "Scale", Q_NULLPTR));
        lbDebug->setText(QApplication::translate("MainWindow", "Debug :", Q_NULLPTR));
        twDeltaManager->setTabText(twDeltaManager->indexOf(tabDefaultDelta), QApplication::translate("MainWindow", "DeltaX 1", Q_NULLPTR));
        twDeltaManager->setTabText(twDeltaManager->indexOf(tabAddNewDelta), QApplication::translate("MainWindow", "+", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        twModule->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbExportBlocklyToGcode->setText(QApplication::translate("MainWindow", "Export G-code", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("MainWindow", "Execute Program", Q_NULLPTR));
        twModule->setTabText(twModule->indexOf(tBlockly), QApplication::translate("MainWindow", "Block Program", Q_NULLPTR));
        lbScreenStreamer->setText(QString());
        groupBox->setTitle(QApplication::translate("MainWindow", "Object", Q_NULLPTR));
        lbTrackingObject->setText(QString());
        pbObjectRect->setText(QApplication::translate("MainWindow", "Rec Tool", Q_NULLPTR));
        leYRec->setText(QApplication::translate("MainWindow", "127", Q_NULLPTR));
        leXRec->setText(QApplication::translate("MainWindow", "57", Q_NULLPTR));
        leYRec_2->setText(QApplication::translate("MainWindow", "20", Q_NULLPTR));
        label_42->setText(QApplication::translate("MainWindow", "W", Q_NULLPTR));
        label_43->setText(QApplication::translate("MainWindow", "L", Q_NULLPTR));
        label_44->setText(QApplication::translate("MainWindow", "H", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Conveyor", Q_NULLPTR));
        leConvenyorSpeed->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_45->setText(QApplication::translate("MainWindow", "Speed", Q_NULLPTR));
        cbConveyorDirection->clear();
        cbConveyorDirection->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "X", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Y", Q_NULLPTR)
        );
        label_47->setText(QApplication::translate("MainWindow", "Direction", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Measurement", Q_NULLPTR));
        pbObjectLine->setText(QApplication::translate("MainWindow", "Calib Line", Q_NULLPTR));
        leRealDistance->setText(QApplication::translate("MainWindow", "120", Q_NULLPTR));
        leYCoordinate->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbObjectOrigin->setToolTip(QApplication::translate("MainWindow", "Coordinate", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbObjectOrigin->setText(QApplication::translate("MainWindow", "Calib Point", Q_NULLPTR));
        leXCoordinate->setText(QApplication::translate("MainWindow", "150", Q_NULLPTR));
        label_38->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        label_39->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        label_40->setText(QApplication::translate("MainWindow", "Reality (mm)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbChangeXAxis->setToolTip(QApplication::translate("MainWindow", "Switch layers", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbChangeXAxis->setText(QApplication::translate("MainWindow", "X Direction", Q_NULLPTR));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbLoadCamera->setToolTip(QApplication::translate("MainWindow", "Load Camera", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbLoadCamera->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbLoadTestImage->setToolTip(QApplication::translate("MainWindow", "Load Image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbLoadTestImage->setText(QString());
        label_11->setText(QApplication::translate("MainWindow", "FPS", Q_NULLPTR));
        leFPS->setText(QApplication::translate("MainWindow", "15", Q_NULLPTR));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "Variable", Q_NULLPTR));
        pbViewDataObjects->setText(QApplication::translate("MainWindow", "View data objects", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbClearDetectObjects->setToolTip(QApplication::translate("MainWindow", "Select Process Region", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        pbClearDetectObjects->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        pbClearDetectObjects->setText(QApplication::translate("MainWindow", "Clear Objects", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("MainWindow", "Counter", Q_NULLPTR));
        label_48->setText(QApplication::translate("MainWindow", "Tracking", Q_NULLPTR));
        lbTrackingObjectNumber->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        label_50->setText(QApplication::translate("MainWindow", "Visible", Q_NULLPTR));
        lbVisibleObjectNumber->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbSwitchWorkFlow->setToolTip(QApplication::translate("MainWindow", "Switch layers", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbSwitchWorkFlow->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbFilter->setToolTip(QApplication::translate("MainWindow", "Object Filter", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbFilter->setText(QApplication::translate("MainWindow", "Filter", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbSelection->setToolTip(QApplication::translate("MainWindow", "Select Process Region", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbSelection->setText(QApplication::translate("MainWindow", "Detection Area", Q_NULLPTR));
        twModule->setTabText(twModule->indexOf(tResultCameraArea), QApplication::translate("MainWindow", "Object Detecting", Q_NULLPTR));
        lbImageForDrawing->setText(QString());
        lbDrawingArea->setText(QString());
        leDrawingThreshold->setText(QApplication::translate("MainWindow", "150", Q_NULLPTR));
        lbImageWidth->setText(QApplication::translate("MainWindow", "W: 208", Q_NULLPTR));
        lbImageHeight->setText(QApplication::translate("MainWindow", "H: 117", Q_NULLPTR));
        label_18->setText(QApplication::translate("MainWindow", "H Scale", Q_NULLPTR));
        leHeightScale->setText(QApplication::translate("MainWindow", "117", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "W Scale", Q_NULLPTR));
        leWidthScale->setText(QApplication::translate("MainWindow", "208", Q_NULLPTR));
        label_23->setText(QApplication::translate("MainWindow", "Space", Q_NULLPTR));
        leSpace->setText(QApplication::translate("MainWindow", "1", Q_NULLPTR));
        pbDrawLine->setText(QString());
        pbDrawRectangle->setText(QString());
        pbDrawArc->setText(QString());
        pbDrawCircle->setText(QString());
        label_19->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        leDrawAg1->setText(QString());
        label_22->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        label_24->setText(QApplication::translate("MainWindow", "H", Q_NULLPTR));
        label_25->setText(QApplication::translate("MainWindow", "W", Q_NULLPTR));
        label_26->setText(QApplication::translate("MainWindow", "O", Q_NULLPTR));
        pbOpenPicture->setText(QString());
        pbExportDrawingGcodes->setText(QApplication::translate("MainWindow", "Export\n"
"G-code", Q_NULLPTR));
        pbPainting->setText(QApplication::translate("MainWindow", "Draw", Q_NULLPTR));
        pbZoomIn->setText(QString());
        pbZoomOut->setText(QString());
        label_21->setText(QApplication::translate("MainWindow", "100%", Q_NULLPTR));
        pbCursor->setText(QString());
        cbDrawingEffector->clear();
        cbDrawingEffector->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Laser", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Pen", Q_NULLPTR)
        );
        cbDrawMethod->clear();
        cbDrawMethod->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Line", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Dot", Q_NULLPTR)
        );
        label_13->setText(QApplication::translate("MainWindow", "Move Type", Q_NULLPTR));
        cbConversionTool->clear();
        cbConversionTool->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Threshold", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Vectorize", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Gray", Q_NULLPTR)
        );
        label_14->setText(QApplication::translate("MainWindow", "Conversion Tool", Q_NULLPTR));
        twModule->setTabText(twModule->indexOf(tDrawing), QApplication::translate("MainWindow", "Drawing", Q_NULLPTR));
        pbTurnOnROS->setText(QApplication::translate("MainWindow", "Turn On ROS", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        cbROSCameraView->clear();
        cbROSCameraView->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2", Q_NULLPTR)
        );
        label->setText(QApplication::translate("MainWindow", "Change View", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Display", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "End Effector", Q_NULLPTR));
        cbEndEffector->clear();
        cbEndEffector->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Suction Cup", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Gripper", Q_NULLPTR)
         << QApplication::translate("MainWindow", "None", Q_NULLPTR)
        );
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t3D), QApplication::translate("MainWindow", "3D", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "Angle", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Movement", Q_NULLPTR));
        label_28->setText(QApplication::translate("MainWindow", "mm", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbRight->setToolTip(QApplication::translate("MainWindow", "Right (Shift +d)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbRight->setText(QApplication::translate("MainWindow", "R", Q_NULLPTR));
        pbRight->setShortcut(QApplication::translate("MainWindow", "Shift+D", Q_NULLPTR));
        pbBackward->setText(QApplication::translate("MainWindow", "B", Q_NULLPTR));
        pbBackward->setShortcut(QApplication::translate("MainWindow", "Shift+S", Q_NULLPTR));
        cbDivision->clear();
        cbDivision->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "0.5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1", Q_NULLPTR)
         << QApplication::translate("MainWindow", "5", Q_NULLPTR)
         << QApplication::translate("MainWindow", "10", Q_NULLPTR)
         << QApplication::translate("MainWindow", "50", Q_NULLPTR)
         << QApplication::translate("MainWindow", "100", Q_NULLPTR)
        );
        cbDivision->setCurrentText(QApplication::translate("MainWindow", "0.5", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbForward->setToolTip(QApplication::translate("MainWindow", "Forward (Shift + w)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbForward->setText(QApplication::translate("MainWindow", "F", Q_NULLPTR));
        pbForward->setShortcut(QApplication::translate("MainWindow", "Shift+W", Q_NULLPTR));
        pbLeft->setText(QApplication::translate("MainWindow", "L", Q_NULLPTR));
        pbLeft->setShortcut(QApplication::translate("MainWindow", "Shift+A", Q_NULLPTR));
        pbUp->setText(QApplication::translate("MainWindow", "U", Q_NULLPTR));
        pbUp->setShortcut(QApplication::translate("MainWindow", "Shift+R", Q_NULLPTR));
        pbDown->setText(QApplication::translate("MainWindow", "D", Q_NULLPTR));
        pbDown->setShortcut(QApplication::translate("MainWindow", "Shift+F", Q_NULLPTR));
        label_29->setText(QApplication::translate("MainWindow", "Velocity", Q_NULLPTR));
        leVelocity->setText(QApplication::translate("MainWindow", "200", Q_NULLPTR));
        label_30->setText(QApplication::translate("MainWindow", "mm/s", Q_NULLPTR));
        label_31->setText(QApplication::translate("MainWindow", "Accel", Q_NULLPTR));
        leAccel->setText(QApplication::translate("MainWindow", "1200", Q_NULLPTR));
        label_32->setText(QApplication::translate("MainWindow", "mm/s2", Q_NULLPTR));
        label_33->setText(QApplication::translate("MainWindow", "Division", Q_NULLPTR));
        label_46->setText(QApplication::translate("MainWindow", "(shift + a,d,w,s,r,f)", Q_NULLPTR));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t2D), QApplication::translate("MainWindow", "2D", Q_NULLPTR));
        pbConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        lbID->setText(QApplication::translate("MainWindow", "ID: 0", Q_NULLPTR));
        gbGripper->setTitle(QApplication::translate("MainWindow", "Gripper", Q_NULLPTR));
        pbGrip->setText(QApplication::translate("MainWindow", "Grip", Q_NULLPTR));
        leGripperMin->setText(QApplication::translate("MainWindow", "5", Q_NULLPTR));
        leGripperMax->setText(QApplication::translate("MainWindow", "100", Q_NULLPTR));
        label_17->setText(QApplication::translate("MainWindow", "min", Q_NULLPTR));
        label_27->setText(QApplication::translate("MainWindow", "max", Q_NULLPTR));
        gbRelay->setTitle(QApplication::translate("MainWindow", "Relay", Q_NULLPTR));
        pbPump->setText(QString());
        label_34->setText(QApplication::translate("MainWindow", "Vacuum", Q_NULLPTR));
        pbLaser->setText(QString());
        label_35->setText(QApplication::translate("MainWindow", "Laser", Q_NULLPTR));
        gbMovement1->setTitle(QApplication::translate("MainWindow", "Movement", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbY->setToolTip(QApplication::translate("MainWindow", "Update X Position Value", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbY->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbX->setToolTip(QApplication::translate("MainWindow", "Update X Position Value", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbX->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        leX->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbZ->setToolTip(QApplication::translate("MainWindow", "Update X Position Value", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbZ->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbW->setToolTip(QApplication::translate("MainWindow", "Update X Position Value", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbW->setText(QApplication::translate("MainWindow", "W", Q_NULLPTR));
        pbHome->setText(QString());
        cbConveyorMode->clear();
        cbConveyorMode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Manual", Q_NULLPTR)
         << QApplication::translate("MainWindow", "UART", Q_NULLPTR)
        );
        cbConveyorValueType->clear();
        cbConveyorValueType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "mm/s", Q_NULLPTR)
         << QApplication::translate("MainWindow", "mm", Q_NULLPTR)
        );
        leConveyorvMovingValue->setText(QApplication::translate("MainWindow", "-100", Q_NULLPTR));
        pbConveyorMove->setText(QApplication::translate("MainWindow", "Move", Q_NULLPTR));
        pbConveyorConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        twConveyor->setTabText(twConveyor->indexOf(tConveyor), QApplication::translate("MainWindow", "Conveyor X", Q_NULLPTR));
        pbSlidingConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbSlidingHome->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbSlidingHome->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbSlidingDisable->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbSlidingDisable->setText(QString());
        label_36->setText(QApplication::translate("MainWindow", "Speed", Q_NULLPTR));
        label_37->setText(QApplication::translate("MainWindow", "Position", Q_NULLPTR));
        twConveyor->setTabText(twConveyor->indexOf(sSlidingRail), QApplication::translate("MainWindow", "Sliding Rail X", Q_NULLPTR));
        checkBox->setText(QApplication::translate("MainWindow", "Auto", Q_NULLPTR));
        label_52->setText(QApplication::translate("MainWindow", "Terminal", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbFormat->setToolTip(QApplication::translate("MainWindow", "Format Gcode Lines", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbFormat->setText(QApplication::translate("MainWindow", "Format", Q_NULLPTR));
        cbLockGcodeEditor->setText(QApplication::translate("MainWindow", "Lock Editor", Q_NULLPTR));
        cbAutoNumbering->setText(QApplication::translate("MainWindow", "Auto Numbering", Q_NULLPTR));
        gbVar->setTitle(QApplication::translate("MainWindow", "Variables", Q_NULLPTR));
        lbVar6->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        lbVar4->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        leVariable2->setText(QApplication::translate("MainWindow", "#101", Q_NULLPTR));
        leVariable4->setText(QApplication::translate("MainWindow", "#103", Q_NULLPTR));
        leVariable6->setText(QApplication::translate("MainWindow", "#105", Q_NULLPTR));
        lbVar5->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        lbVar1->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        leVariable3->setText(QApplication::translate("MainWindow", "#102", Q_NULLPTR));
        leVariable1->setText(QApplication::translate("MainWindow", "#100", Q_NULLPTR));
        lbVar3->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
        leVariable5->setText(QApplication::translate("MainWindow", "#104", Q_NULLPTR));
        lbVar2->setText(QApplication::translate("MainWindow", "0", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbExternalControllerConnect->setToolTip(QApplication::translate("MainWindow", "Connect External Controller", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbExternalControllerConnect->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        lbECComName->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#535353;\">EC</span></p></body></html>", Q_NULLPTR));
        pteGcodeArea->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#000000;\">N05</span> <span style=\" font-weight:600;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N10 <span style=\" font-weight:600;\">M204</span> A1200</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N15 <span style=\" font-weight:600;\">G01</span> F200</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:"
                        "0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Declare a variable</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N20 <span style=\" font-style:italic;\">#100</span> = 0</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N30 <span style=\" font-style:italic;\">#100</span> = <span style=\" font-style:italic;\">#100</span> + 1</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#55aa00;\">;Ca"
                        "ll subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N35 <span style=\" font-weight:600;\">M98</span> P2000</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">; Begin subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N40 <span style=\" font-weight:600;\">O2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; te"
                        "xt-indent:0px;\">N45 <span style=\" font-weight:600;\">G01</span> Z-350</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N50 <span style=\" font-weight:600;\">G01</span> X-100</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N55 <span style=\" font-weight:600;\">G01</span> Z-370</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N60 <span style=\" font-weight:600;\">G01</span> Z-350</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N65 <span style=\" font-weight:600;\">G01</span> X100</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; ma"
                        "rgin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N70 <span style=\" font-weight:600;\">G01</span> Z-370</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N75 M99</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;End subprogram</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Loop 5 times</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N80 <span style=\" font-weight:600; color:#00aa00;\">IF</span> [<sp"
                        "an style=\" font-style:italic;\">#100</span> LE 5] <span style=\" font-weight:600; color:#00aa00;\">THEN</span> <span style=\" font-weight:600; color:#ff5500;\">GOTO</span> 30</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N85 <span style=\" font-weight:600;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> </p></body></html>", Q_NULLPTR));
        cbPositionToExecuteGcode->clear();
        cbPositionToExecuteGcode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "Begin", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Current", Q_NULLPTR)
        );
        cbFormatColor->setText(QApplication::translate("MainWindow", "Color", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbExecuteGcodes->setToolTip(QApplication::translate("MainWindow", "Execute Gcode", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbExecuteGcodes->setText(QString());
        gbAddGcode->setTitle(QApplication::translate("MainWindow", "Add G-code", Q_NULLPTR));
        lbAg1->setText(QApplication::translate("MainWindow", "X", Q_NULLPTR));
        leAg6->setText(QString());
        lbAg2->setText(QApplication::translate("MainWindow", "Y", Q_NULLPTR));
        leAg5->setText(QString());
        lbAg3->setText(QApplication::translate("MainWindow", "Z", Q_NULLPTR));
        lbAg5->setText(QApplication::translate("MainWindow", "F", Q_NULLPTR));
        lbAg6->setText(QString());
        leAg3->setText(QString());
        lbAg4->setText(QApplication::translate("MainWindow", "W", Q_NULLPTR));
        leAg4->setText(QString());
        leAg2->setText(QString());
        leAg1->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbGcodeReference->setToolTip(QApplication::translate("MainWindow", "Gcode Reference", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbGcodeReference->setText(QApplication::translate("MainWindow", "Reference", Q_NULLPTR));
        pbAddGcode->setText(QApplication::translate("MainWindow", "Add ( Ctrl + D )", Q_NULLPTR));
        pbAddGcode->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", Q_NULLPTR));
        cbGcode->clear();
        cbGcode->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "G01", Q_NULLPTR)
         << QApplication::translate("MainWindow", "G02", Q_NULLPTR)
         << QApplication::translate("MainWindow", "G03", Q_NULLPTR)
         << QApplication::translate("MainWindow", "G05", Q_NULLPTR)
         << QApplication::translate("MainWindow", "G28", Q_NULLPTR)
         << QApplication::translate("MainWindow", "M03", Q_NULLPTR)
         << QApplication::translate("MainWindow", "M04", Q_NULLPTR)
         << QApplication::translate("MainWindow", "M05", Q_NULLPTR)
         << QApplication::translate("MainWindow", "M204", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        pbSaveGcode->setToolTip(QApplication::translate("MainWindow", "Save Gcode Into File", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        pbSaveGcode->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbFindGcodeFile->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbFindGcodeFile->setText(QApplication::translate("MainWindow", "Find", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbRefreshGcodeFiles->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbRefreshGcodeFiles->setText(QApplication::translate("MainWindow", "F5   ", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbAddNewProgram->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbAddNewProgram->setText(QApplication::translate("MainWindow", "New ", Q_NULLPTR));
        leExProgramName->setText(QApplication::translate("MainWindow", "Program 1", Q_NULLPTR));
        pbExDeleteProgram->setText(QString());
        lbExGCodeNumber->setText(QApplication::translate("MainWindow", "100 Gcode Lines", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbSortGcodeFiles->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbSortGcodeFiles->setText(QApplication::translate("MainWindow", "Sort", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbUploadProgram->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbUploadProgram->setText(QString());
#ifndef QT_NO_TOOLTIP
        pbImportGcodeFiles->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbImportGcodeFiles->setText(QApplication::translate("MainWindow", "Import", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Offline", Q_NULLPTR));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Author:</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Description:</p></body></html>", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        pbUploadProgram_2->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        pbUploadProgram_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Online", Q_NULLPTR));
        lbID_2->setText(QApplication::translate("MainWindow", "PORT: 8844", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        menuReferences->setTitle(QApplication::translate("MainWindow", "References", Q_NULLPTR));
        menuEditor->setTitle(QApplication::translate("MainWindow", "Editor", Q_NULLPTR));
        menuExecute->setTitle(QApplication::translate("MainWindow", "Execute", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("MainWindow", ".............................................................", Q_NULLPTR));
        menuSetting->setTitle(QApplication::translate("MainWindow", "Setting", Q_NULLPTR));
        menuConnection->setTitle(QApplication::translate("MainWindow", "Connection", Q_NULLPTR));
        menuUI->setTitle(QApplication::translate("MainWindow", "UI", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
