/********************************************************************************
** Form generated from reading UI file 'RobotWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTWINDOW_H
#define UI_ROBOTWINDOW_H

#include <DrawingWidget.h>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <codeeditor.h>
#include <imageviewer.h>

QT_BEGIN_NAMESPACE

class Ui_RobotWindow
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
    QVBoxLayout *verticalLayout_15;
    QTabWidget *twDeltaManager;
    QWidget *tabDefaultDelta;
    QWidget *tabAddNewDelta;
    QFrame *frame_11;
    QHBoxLayout *horizontalLayout_34;
    QLabel *label_122;
    QLineEdit *leIP;
    QLabel *label_123;
    QLineEdit *lePort;
    QToolButton *tbServerConfig;
    QSpacerItem *horizontalSpacer_26;
    QWidget *tabManagerLayout;
    QVBoxLayout *verticalLayout_46;
    QSplitter *splitter_2;
    QWidget *ModuleTabManagerWidget;
    QVBoxLayout *ModuleTabManagerLayout;
    QTabWidget *twModule;
    QWidget *tGcodeEditor;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_30;
    QSpacerItem *horizontalSpacer_3;
    QRadioButton *rbEditorCurrent;
    QPushButton *pbExecuteGcodes;
    QLabel *label_7;
    QRadioButton *rbEditorStart;
    QSpacerItem *horizontalSpacer_2;
    QComboBox *cbProgramThreadID;
    QFrame *frame_10;
    QHBoxLayout *horizontalLayout_9;
    QToolButton *pbOpenGcodeDocs;
    QToolButton *pbSaveGcode;
    QToolButton *pbCreateNewGcode;
    QToolButton *pbFormat;
    QSpacerItem *horizontalSpacer_13;
    QCheckBox *cbEditGcodeEditor;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_119;
    QToolButton *tbAddG28;
    QLabel *label_120;
    QToolButton *tbAddG01;
    QToolButton *tbAddG02;
    QLabel *label_121;
    QToolButton *tbAddG04;
    QLabel *label_127;
    QToolButton *tbAddM03;
    QToolButton *tbAddM05;
    QLabel *label_131;
    QToolButton *tbAddM07;
    QToolButton *tbAddM08;
    QSpacerItem *verticalSpacer_15;
    QVBoxLayout *verticalLayout_13;
    CodeEditor *pteGcodeArea;
    QFrame *fGcodePara;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_49;
    QLineEdit *lineEdit;
    QLabel *label_118;
    QLineEdit *lineEdit_2;
    QLabel *label_134;
    QLineEdit *lineEdit_3;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_135;
    QLineEdit *lineEdit_4;
    QLabel *label_141;
    QLineEdit *lineEdit_5;
    QLabel *label_142;
    QLineEdit *lineEdit_6;
    QLabel *label_148;
    QLineEdit *lineEdit_7;
    QLabel *label_149;
    QLineEdit *lineEdit_8;
    QLabel *label_150;
    QLineEdit *lineEdit_9;
    QLabel *label_151;
    QLineEdit *lineEdit_10;
    QLabel *label_152;
    QLineEdit *lineEdit_11;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_3;
    QToolButton *tbOpenGcodePath;
    QLineEdit *leGcodeExplorer;
    QHBoxLayout *horizontalLayout_6;
    QToolButton *tbBackGcodeFolder;
    QToolButton *tbNewGcodeFile;
    QToolButton *tbRefreshExplorer;
    QToolButton *tbDeleteGcodeFile;
    QSpacerItem *horizontalSpacer_10;
    QTreeView *tvGcodeExplorer;
    QWidget *tab;
    QSpacerItem *verticalSpacer_9;
    QWidget *tObjectDetecting;
    QVBoxLayout *verticalLayout_25;
    QScrollArea *saObjectDetecting;
    QWidget *wObjectDetecting;
    QVBoxLayout *verticalLayout_17;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_191;
    QComboBox *cbSelectedDetecting;
    QSpacerItem *horizontalSpacer_49;
    QSplitter *splitter;
    QGroupBox *gbImageViewer;
    QVBoxLayout *vlImageViewer;
    QFrame *fImageViewer;
    QHBoxLayout *horizontalLayout_30;
    QFrame *frame_16;
    QVBoxLayout *verticalLayout_7;
    QPushButton *pbFindChessboardTool;
    QPushButton *pbWarpTool;
    QPushButton *pbAreaTool;
    QPushButton *pbCalibPointTool;
    QPushButton *pbMappingPointTool;
    QSpacerItem *verticalSpacer_12;
    QFrame *frame_8;
    QVBoxLayout *verticalLayout_50;
    QToolButton *pbGetSizeTool;
    QPushButton *pbFilterTool;
    QPushButton *pbOpenObjectTable;
    QPushButton *pbClearObject;
    QSpacerItem *verticalSpacer_13;
    ImageViewer *gvImageViewer;
    QFrame *frame_17;
    QVBoxLayout *verticalLayout_10;
    QLabel *label_213;
    QComboBox *cbImageOutput;
    QLabel *lbDisplayRatio_2;
    QLabel *lbDisplayRatio_3;
    QSpacerItem *verticalSpacer_10;
    QLabel *lbDisplayRatio;
    QLabel *lbMatSize;
    QFrame *fObjectDetectingTool;
    QVBoxLayout *verticalLayout_32;
    QGroupBox *gbImageProvider;
    QVBoxLayout *verticalLayout_39;
    QFrame *fImageProvider;
    QVBoxLayout *verticalLayout_51;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_176;
    QComboBox *cbSourceForImageProvider;
    QSpacerItem *horizontalSpacer_44;
    QLabel *label_6;
    QComboBox *cbEncoderForCamera;
    QFrame *fWebcamSource;
    QHBoxLayout *horizontalLayout_11;
    QToolButton *pbLoadCamera;
    QSpacerItem *horizontalSpacer_45;
    QFrame *fImageSource;
    QHBoxLayout *horizontalLayout_27;
    QToolButton *pbLoadTestImage;
    QSpacerItem *horizontalSpacer_64;
    QFrame *fCameraPara;
    QHBoxLayout *horizontalLayout_28;
    QLabel *label_178;
    QLineEdit *leImageWidth;
    QLabel *label_179;
    QLineEdit *leImageHeight;
    QLabel *label_73;
    QLineEdit *leCaptureInterval;
    QLabel *label_128;
    QToolButton *pbStartAcquisition;
    QToolButton *pbCapture;
    QLabel *lbCameraState;
    QSpacerItem *horizontalSpacer_65;
    QGroupBox *gbCameraCalibration;
    QVBoxLayout *verticalLayout_29;
    QFrame *fCameraCalibrationFrame;
    QVBoxLayout *verticalLayout_52;
    QPushButton *pbCalibStep1;
    QFrame *fCalibStep1;
    QGridLayout *gridLayout_27;
    QLabel *label_109;
    QLabel *label_110;
    QPushButton *pbCalibStep2;
    QFrame *fCalibStep2;
    QGridLayout *gridLayout_26;
    QLineEdit *leRealityPoint2X;
    QLineEdit *leRealityPoint1Y;
    QPushButton *pbCalibPoint1;
    QLabel *label_140;
    QPushButton *pbImageMapping;
    QLineEdit *leRealityPoint2Y;
    QLineEdit *leRealityPoint1X;
    QLabel *label_133;
    QLabel *label_139;
    QLabel *label_39;
    QLabel *label_132;
    QLabel *label_38;
    QPushButton *pbCalibPoint2;
    QGroupBox *gbCameraObject;
    QVBoxLayout *verticalLayout_40;
    QFrame *fVisionObjectFrame;
    QVBoxLayout *verticalLayout_31;
    QHBoxLayout *horizontalLayout_29;
    QSpacerItem *horizontalSpacer_43;
    QFrame *frame_13;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_126;
    QComboBox *cbDetectingAlgorithm;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_45;
    QLineEdit *leObjectOverlay;
    QFrame *fBlobPanel;
    QGridLayout *gridLayout_14;
    QLineEdit *leMaxWRec;
    QLabel *label_172;
    QLineEdit *leMinLRec;
    QLineEdit *leMaxLRec;
    QLineEdit *leWRec;
    QLabel *label_173;
    QLineEdit *leLRec;
    QLabel *label_175;
    QLabel *label_43;
    QLabel *label_163;
    QLabel *label_54;
    QLineEdit *leMinWRec;
    QLabel *label_55;
    QComboBox *cbObjectType;
    QLabel *label_42;
    QSpacerItem *horizontalSpacer_66;
    QLabel *label_174;
    QFrame *fExternalScriptPanel;
    QGridLayout *gridLayout_28;
    QPushButton *pbRunExternalScript;
    QComboBox *cbImageSource;
    QLabel *label_180;
    QLabel *label_183;
    QLabel *label_187;
    QLabel *label_185;
    QLabel *label_146;
    QPushButton *pbExternalScriptOpen;
    QLabel *label_184;
    QLabel *label_145;
    QPushButton *pbExternalScriptHelp;
    QLabel *label_186;
    QLabel *label_182;
    QLabel *label_181;
    QLineEdit *lePythonUrl;
    QPushButton *pbOpenScriptExample;
    QFrame *fCirclePanel;
    QGridLayout *gridLayout_29;
    QLineEdit *leCenterThreshold;
    QSpacerItem *horizontalSpacer_8;
    QLineEdit *leEdgeThreshold;
    QLabel *label_193;
    QLabel *label_190;
    QLabel *label_192;
    QLineEdit *leMaxRadius;
    QLabel *label_194;
    QLabel *label_195;
    QLineEdit *leMinRadius;
    QLabel *label_188;
    QGridLayout *gridLayout_33;
    QGridLayout *gridLayout_12;
    QGroupBox *gbCameraVariable;
    QVBoxLayout *verticalLayout_34;
    QHBoxLayout *horizontalLayout_31;
    QLabel *label_196;
    QLineEdit *leDetectingObjectListName;
    QSpacerItem *horizontalSpacer_50;
    QFrame *fVisionVariableFrame;
    QVBoxLayout *verticalLayout_35;
    QHBoxLayout *horizontalLayout_25;
    QPushButton *pbViewDataObjects;
    QPushButton *pbClearDetectObjects;
    QSpacerItem *horizontalSpacer_9;
    QGridLayout *gridLayout_15;
    QLabel *lbTrackingObjectNumber;
    QLabel *label_155;
    QLabel *label_56;
    QLabel *label_50;
    QLineEdit *leLimitMinX;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_44;
    QLabel *lbVisibleObjectNumber;
    QLabel *label_48;
    QLineEdit *leLimitMaxX;
    QLabel *label_156;
    QLabel *label_157;
    QLineEdit *leLimitMinY;
    QLineEdit *leLimitMaxY;
    QSpacerItem *verticalSpacer_11;
    QWidget *tPointTool;
    QVBoxLayout *verticalLayout_14;
    QScrollArea *saObjectDetecting_2;
    QWidget *wObjectDetecting_2;
    QVBoxLayout *verticalLayout_18;
    QSplitter *splitter_3;
    QFrame *fObjectDetectingTool_2;
    QVBoxLayout *verticalLayout_59;
    QGroupBox *gbImageProvider_2;
    QVBoxLayout *verticalLayout_60;
    QFrame *frame_15;
    QGridLayout *gridLayout_16;
    QLineEdit *leDeviationAngle;
    QLabel *label_164;
    QComboBox *cbTrackingEncoderSource;
    QLabel *label_144;
    QSpacerItem *horizontalSpacer_24;
    QCheckBox *cbReverseEncoderValue;
    QLabel *label_167;
    QComboBox *cbSelectedTracking;
    QComboBox *cbTrackingDirection;
    QLabel *label_168;
    QLabel *label_160;
    QLabel *label_169;
    QLineEdit *leSelectedTrackingObjectList;
    QGroupBox *gbCameraCalibration_3;
    QVBoxLayout *verticalLayout_63;
    QFrame *frame_19;
    QGridLayout *gridLayout_44;
    QLineEdit *leAnglePoint2X;
    QPushButton *pbCalculateAngle;
    QLineEdit *leAnglePoint1Y;
    QLineEdit *leAnglePoint2Y;
    QLabel *label_189;
    QLabel *label_206;
    QLineEdit *leAngleResult;
    QLineEdit *leAnglePoint1X;
    QLabel *label_224;
    QPushButton *pbAnglePoint1;
    QPushButton *pbAnglePoint2;
    QGroupBox *gbCameraCalibration_4;
    QVBoxLayout *verticalLayout_67;
    QFrame *frame_22;
    QGridLayout *gridLayout_45;
    QLineEdit *leAnglePoint2X_2;
    QLineEdit *leAnglePoint2Y_2;
    QLineEdit *leAngleResult_2;
    QLabel *label_226;
    QLabel *label_227;
    QLabel *label_228;
    QLineEdit *leAngleResult_3;
    QLabel *label_229;
    QLineEdit *leAnglePoint1X_2;
    QLabel *label_197;
    QLabel *label_209;
    QPushButton *pbCalculateAngle_2;
    QLineEdit *leAnglePoint1Y_2;
    QGroupBox *gbCameraCalibration_2;
    QVBoxLayout *verticalLayout_62;
    QPushButton *pbAddVariablePoint_2;
    QFrame *frame_18;
    QGridLayout *gridLayout_41;
    QLabel *label_202;
    QLabel *label_203;
    QLabel *label_204;
    QLineEdit *leSourcePoint1X;
    QLabel *label_166;
    QLabel *label_200;
    QLabel *label_165;
    QLabel *label_201;
    QLineEdit *leMatrix1Name;
    QLabel *label_177;
    QLineEdit *leSourcePoint2Y;
    QLineEdit *leSourcePoint2X;
    QLineEdit *leSourcePoint1Y;
    QLabel *label_205;
    QLineEdit *leDestinationPoint1X;
    QLineEdit *leDestinationPoint2X;
    QLineEdit *leDestinationPoint1Y;
    QLineEdit *leDestinationPoint2Y;
    QPushButton *pbCalculateMappingMatrixTool;
    QGroupBox *gbCameraObject_2;
    QVBoxLayout *verticalLayout_64;
    QPushButton *pbAddVariablePoint;
    QFrame *frame_14;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_136;
    QLineEdit *lePoint1Name;
    QLabel *label_137;
    QLineEdit *lePoint1X;
    QLabel *label_138;
    QLineEdit *lePoint1Y;
    QLabel *label_143;
    QLineEdit *lePoint1Z;
    QGroupBox *gbCameraObject_3;
    QVBoxLayout *verticalLayout_65;
    QPushButton *pbAddVariablePoint_3;
    QFrame *frame_20;
    QGridLayout *gridLayout_42;
    QLabel *label_210;
    QLineEdit *leMPoint3Y;
    QLabel *label_218;
    QLabel *label_211;
    QLineEdit *leMPoint1Y;
    QLabel *label_212;
    QLabel *label_216;
    QLineEdit *lePointMatrixName;
    QLineEdit *leMPoint4X;
    QLineEdit *leMPoint2Y;
    QLineEdit *leMPoint3X;
    QLabel *label_217;
    QLineEdit *leMPoint1X;
    QLineEdit *leMPoint4Y;
    QLineEdit *leMPoint2X;
    QLabel *label_219;
    QPushButton *pbCalculatePointMatrixTool;
    QGroupBox *gbCameraObject_4;
    QVBoxLayout *verticalLayout_66;
    QFrame *frame_21;
    QGridLayout *gridLayout_43;
    QLineEdit *leTestPointY;
    QLineEdit *leTargetTestPointY;
    QLineEdit *leTargetTestPointX;
    QLineEdit *leTestMatrixName;
    QPushButton *pbCalculateTestPoint;
    QLineEdit *leTestPointX;
    QLabel *label_215;
    QLabel *label_223;
    QLabel *label_222;
    QLabel *label_221;
    QLabel *label_214;
    QSpacerItem *verticalSpacer_18;
    QWidget *tDrawing;
    QVBoxLayout *verticalLayout_26;
    QScrollArea *scrollArea_6;
    QWidget *scrollAreaWidgetContents_6;
    QVBoxLayout *verticalLayout_38;
    QVBoxLayout *verticalLayout_37;
    QFrame *frame_4;
    QVBoxLayout *verticalLayout_21;
    QToolButton *pbOpenPicture;
    QHBoxLayout *horizontalLayout_24;
    QFrame *frame_2;
    QLabel *lbImageForDrawing;
    QWidget *widget;
    QVBoxLayout *verticalLayout_36;
    QWidget *widget_3;
    QGridLayout *gridLayout_23;
    QLabel *lbImageWidth;
    QLabel *lbImageHeight;
    QSpacerItem *verticalSpacer_4;
    QWidget *widget_2;
    QGridLayout *gridLayout_25;
    QComboBox *cbConversionTool;
    QSlider *hsDrawingThreshold;
    QLineEdit *leDrawingThreshold;
    QLabel *label_14;
    QLabel *label_105;
    QCheckBox *cbReverseDrawing;
    QFrame *frame_5;
    QVBoxLayout *verticalLayout_47;
    QToolButton *pbPainting;
    QFrame *frame_7;
    QGridLayout *gridLayout_24;
    QLabel *label_20;
    QLabel *label_18;
    QSpacerItem *horizontalSpacer_40;
    QComboBox *cbLockDrawingArea;
    QLabel *label_104;
    QLineEdit *leWidthScale;
    QLineEdit *leHeightScale;
    QLabel *label_21;
    QFrame *frame_3;
    DrawingWidget *lbDrawingArea;
    QHBoxLayout *horizontalLayout_23;
    QWidget *widget_11;
    QHBoxLayout *horizontalLayout_22;
    QLabel *label_26;
    QLineEdit *leDrawAg5;
    QWidget *widget_10;
    QHBoxLayout *horizontalLayout_21;
    QLabel *label_25;
    QLineEdit *leDrawAg4;
    QWidget *widget_9;
    QHBoxLayout *horizontalLayout_20;
    QLabel *label_24;
    QLineEdit *leDrawAg3;
    QWidget *widget_8;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_22;
    QLineEdit *leDrawAg2;
    QWidget *widget_7;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_19;
    QLineEdit *leDrawAg1;
    QGridLayout *gridLayout_11;
    QSpacerItem *horizontalSpacer_5;
    QToolButton *pbDrawLine;
    QToolButton *pbDrawRectangle;
    QToolButton *pbZoomIn;
    QToolButton *pbCursor;
    QToolButton *pbDrawArc;
    QToolButton *pbDrawCircle;
    QToolButton *pbZoomOut;
    QFrame *frame_6;
    QVBoxLayout *verticalLayout_48;
    QToolButton *pbExportDrawingGcodes;
    QGridLayout *gridLayout_22;
    QLabel *label_96;
    QLabel *label_101;
    QLabel *label_13;
    QSpacerItem *horizontalSpacer_33;
    QLabel *label_97;
    QLineEdit *leTravelSpeed;
    QComboBox *cbDrawMethod;
    QComboBox *cbDrawingEffector;
    QLineEdit *leSafeZHeight;
    QLineEdit *leDrawingAcceleration;
    QLabel *label_102;
    QLabel *label_93;
    QLabel *label_95;
    QLabel *label_100;
    QLabel *label_98;
    QLineEdit *leDrawingSpeed;
    QLabel *label_99;
    QLabel *label_23;
    QLineEdit *leSpace;
    QLabel *label_103;
    QSpacerItem *verticalSpacer_6;
    QWidget *TermiteTab;
    QVBoxLayout *verticalLayout_11;
    QScrollArea *scrollArea_7;
    QWidget *scrollAreaWidgetContents_7;
    QVBoxLayout *verticalLayout_27;
    QGridLayout *gridLayout_4;
    QTextEdit *teDebug;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *leTerminal;
    QComboBox *cbDeviceSender;
    QWidget *DeviceTabManagerWidget;
    QVBoxLayout *GeometryTabManagerLayout;
    QTabWidget *twDevices;
    QWidget *tRobot;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea_2;
    QWidget *wgJoggingScrollWidget;
    QVBoxLayout *verticalLayout_5;
    QFrame *groupRobotConnection;
    QHBoxLayout *horizontalLayout_14;
    QVBoxLayout *verticalLayout_12;
    QPushButton *pbConnect;
    QCheckBox *cbAutoConnect;
    QFrame *fRobotPosition;
    QGridLayout *gridLayout_19;
    QLabel *lbY;
    QLabel *label_88;
    QLabel *lbW;
    QLabel *lbV;
    QLabel *lbU;
    QLabel *label_94;
    QLabel *lbX;
    QLabel *lbZ;
    QLabel *label_90;
    QLabel *label_86;
    QLabel *label_92;
    QLabel *label_84;
    QComboBox *cbSelectedRobot;
    QLabel *label;
    QToolButton *tbDisableRobot;
    QToolButton *tbRequestPosition;
    QSpacerItem *horizontalSpacer_4;
    QFrame *frameRobotConnection;
    QHBoxLayout *horizontalLayout_13;
    QTabWidget *RobotTabWidget;
    QWidget *ConfigurationTab;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_31;
    QLabel *lbComName;
    QComboBox *cbRobotModel;
    QLabel *label_65;
    QLabel *lbBaudrate;
    QLabel *label_91;
    QLabel *label_113;
    QLabel *label_10;
    QComboBox *cbRobotDOF;
    QWidget *MoveTab;
    QVBoxLayout *verticalLayout_53;
    QTabWidget *tabWidget_2;
    QWidget *tab_4;
    QVBoxLayout *verticalLayout_16;
    QFrame *framePositionParameter;
    QGridLayout *gridLayout_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_106;
    QPushButton *pbsubY;
    QLineEdit *leY;
    QPushButton *pbplusY;
    QLabel *label_9;
    QHBoxLayout *horizontalLayout;
    QLabel *label_40;
    QPushButton *pbsubX;
    QLineEdit *leX;
    QPushButton *pbplusX;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_107;
    QPushButton *pbsubZ;
    QLineEdit *leZ;
    QPushButton *pbplusZ;
    QLabel *label_66;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_108;
    QPushButton *pbsubW;
    QLineEdit *leW;
    QPushButton *pbplusW;
    QLabel *label_81;
    QHBoxLayout *horizontalLayout_32;
    QLabel *label_111;
    QPushButton *pbsubU;
    QLineEdit *leU;
    QPushButton *pbplusU;
    QLabel *label_87;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_112;
    QPushButton *pbsubV;
    QLineEdit *leV;
    QPushButton *pbplusV;
    QLabel *label_89;
    QGridLayout *gridLayout;
    QLabel *label_29;
    QLabel *label_116;
    QLabel *label_63;
    QLineEdit *leAccel;
    QLabel *label_32;
    QLabel *label_117;
    QLineEdit *leVelocity;
    QLineEdit *leStartSpeed;
    QLabel *label_62;
    QSpacerItem *verticalSpacer_5;
    QLineEdit *leEndSpeed;
    QLabel *label_30;
    QLabel *label_31;
    QLabel *label_64;
    QLabel *label_47;
    QLineEdit *leEndSpeed_2;
    QWidget *ButtonTab;
    QComboBox *cbDivision;
    QToolButton *pbHome;
    QLabel *label_33;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QToolButton *pbLeft;
    QToolButton *pbRight;
    QToolButton *pbBackward;
    QToolButton *pbForward;
    QToolButton *pbSubRoll;
    QToolButton *pbPlusRoll;
    QToolButton *pbPlusYaw;
    QToolButton *pbSubYaw;
    QToolButton *pbPlusPitch;
    QToolButton *pbSubPitch;
    QToolButton *pbDown;
    QToolButton *pbUp;
    QWidget *SliderTab;
    QVBoxLayout *verticalLayout_55;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_44;
    QFrame *frame;
    QGridLayout *gridLayout_10;
    QLabel *label_53;
    QComboBox *cbWorkingSize;
    QWidget *fXYWorkingArea;
    QWidget *wg2D;
    QLabel *label_15;
    QSlider *vsZAdjsution;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_17;
    QLabel *label_72;
    QDial *d5axis;
    QDial *d6axis;
    QLabel *label_69;
    QLabel *label_71;
    QDial *d4axis;
    QLabel *lb4AxisValue;
    QLabel *lb5AxisValue;
    QLabel *lb6AxisValue;
    QGridLayout *gridLayout_9;
    QLabel *label_60;
    QLabel *label_61;
    QSlider *vs6AxisAdjsution;
    QLabel *label_16;
    QSlider *vs5AxisAdjsution;
    QSlider *vsAngleAdjsution;
    QSpacerItem *verticalSpacer_7;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_54;
    QFrame *gbJoystick;
    QVBoxLayout *verticalLayout_45;
    QWidget *wgJoystickParameter;
    QGridLayout *gridLayout_20;
    QLabel *label_79;
    QComboBox *cbJoystickDevice;
    QLabel *label_41;
    QLineEdit *leJoystickRange;
    QLineEdit *leJoystickSensibility;
    QLabel *label_51;
    QSpacerItem *horizontalSpacer_32;
    QSpacerItem *verticalSpacer_8;
    QWidget *IOTab;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget_3;
    QWidget *OutputTab;
    QVBoxLayout *verticalLayout_3;
    QWidget *wgOldOutput;
    QHBoxLayout *horizontalLayout_7;
    QGroupBox *gbRelay;
    QGridLayout *gridLayout_3;
    QLabel *label_34;
    QLabel *label_35;
    QPushButton *pbPump;
    QPushButton *pbLaser;
    QGroupBox *gbGripper;
    QGridLayout *gridLayout_13;
    QGridLayout *gridLayout_6;
    QLabel *label_17;
    QLabel *label_27;
    QPushButton *pbGrip;
    QLineEdit *leGripperMin;
    QLineEdit *leGripperMax;
    QHBoxLayout *horizontalLayout_15;
    QSlider *hsGripperAngle;
    QLabel *lbGripperValue;
    QSpacerItem *horizontalSpacer_46;
    QGroupBox *gbOutput;
    QVBoxLayout *verticalLayout_42;
    QWidget *wgRelayOutput;
    QGridLayout *gridLayout_35;
    QSpacerItem *horizontalSpacer_47;
    QCheckBox *cbDx;
    QCheckBox *cbRx;
    QLabel *label_67;
    QLineEdit *leRx;
    QLineEdit *leDx;
    QWidget *wgDigitalOutput;
    QGridLayout *gridLayout_34;
    QLabel *label_68;
    QSpacerItem *horizontalSpacer_48;
    QCheckBox *cbD1;
    QCheckBox *cbD2;
    QCheckBox *cbD3;
    QCheckBox *cbD0;
    QSpacerItem *horizontalSpacer_69;
    QCheckBox *cbD4;
    QCheckBox *cbD5;
    QCheckBox *cbD6;
    QCheckBox *cbD7;
    QSpacerItem *verticalSpacer;
    QWidget *InputTab;
    QGroupBox *gbInput;
    QVBoxLayout *verticalLayout_43;
    QHBoxLayout *horizontalLayout_37;
    QLabel *label_70;
    QSpacerItem *horizontalSpacer_16;
    QLabel *lbI0Value;
    QSpacerItem *horizontalSpacer_15;
    QCheckBox *cbToggle0;
    QPushButton *pbReadI0;
    QSpacerItem *horizontalSpacer_51;
    QHBoxLayout *horizontalLayout_38;
    QLabel *label_74;
    QSpacerItem *horizontalSpacer_17;
    QLabel *lbI1Value;
    QSpacerItem *horizontalSpacer_18;
    QCheckBox *cbToggle1;
    QPushButton *pbReadI1;
    QSpacerItem *horizontalSpacer_52;
    QHBoxLayout *horizontalLayout_39;
    QLabel *label_76;
    QSpacerItem *horizontalSpacer_19;
    QLabel *lbI2Value;
    QSpacerItem *horizontalSpacer_20;
    QCheckBox *cbToggle2;
    QPushButton *pbReadI2;
    QSpacerItem *horizontalSpacer_53;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_78;
    QSpacerItem *horizontalSpacer_21;
    QLabel *lbI3Value;
    QSpacerItem *horizontalSpacer_22;
    QCheckBox *cbToggle3;
    QPushButton *pbReadI3;
    QSpacerItem *horizontalSpacer_54;
    QHBoxLayout *horizontalLayout_43;
    QLineEdit *leIx;
    QSpacerItem *horizontalSpacer_29;
    QLabel *lbIxValue;
    QSpacerItem *horizontalSpacer_30;
    QCheckBox *cbTogglex;
    QPushButton *pbReadIx;
    QSpacerItem *horizontalSpacer_57;
    QHBoxLayout *horizontalLayout_45;
    QLabel *label_83;
    QSpacerItem *horizontalSpacer_34;
    QLabel *lbA0Value;
    QSpacerItem *horizontalSpacer_35;
    QLineEdit *leA0Delay;
    QPushButton *pbReadA0;
    QSpacerItem *horizontalSpacer_58;
    QHBoxLayout *horizontalLayout_46;
    QLabel *label_85;
    QSpacerItem *horizontalSpacer_36;
    QLabel *lbA1Value;
    QSpacerItem *horizontalSpacer_37;
    QLineEdit *leA1Delay;
    QPushButton *pbReadA1;
    QSpacerItem *horizontalSpacer_59;
    QHBoxLayout *horizontalLayout_47;
    QLineEdit *leAx;
    QSpacerItem *horizontalSpacer_38;
    QLabel *lbAxValue;
    QSpacerItem *horizontalSpacer_39;
    QLineEdit *leAxDelay;
    QPushButton *pbReadAx;
    QSpacerItem *horizontalSpacer_60;
    QWidget *ConveyorTab;
    QVBoxLayout *verticalLayout_22;
    QHBoxLayout *horizontalLayout_48;
    QPushButton *pbConveyorConnect;
    QLabel *label_2;
    QComboBox *cbSelectedConveyor;
    QLabel *label_28;
    QComboBox *cbConveyorType;
    QLabel *lbConveyorCOMName;
    QSpacerItem *horizontalSpacer;
    QFrame *fConveyorX;
    QGridLayout *gridLayout_7;
    QLineEdit *leConveyorXPosition;
    QComboBox *cbConveyorValueType;
    QLabel *lbUnitOfConveyorMoving;
    QLabel *label_57;
    QLabel *label_46;
    QComboBox *cbConveyorMode;
    QLabel *label_12;
    QLineEdit *leConveyorXSpeed;
    QLabel *label_52;
    QLabel *lbSpeedOfPositionMode;
    QFrame *fConveyorXHub;
    QGridLayout *gridLayout_18;
    QLabel *label_77;
    QLineEdit *leSubConveyor1Position;
    QLabel *label_115;
    QLabel *label_114;
    QComboBox *cbSubConveyor2Mode;
    QLineEdit *leSubConveyor1Speed;
    QLabel *label_75;
    QLabel *label_82;
    QLineEdit *leSubConveyor2Position;
    QLineEdit *leSubConveyor2Speed;
    QComboBox *cbSubConveyor3Mode;
    QLineEdit *leSubConveyor3Speed;
    QComboBox *cbSubConveyor1Mode;
    QLabel *label_80;
    QLineEdit *leSubConveyor3Position;
    QFrame *fConveyorCustom;
    QGridLayout *gridLayout_39;
    QLineEdit *pbStopCustomConveyor2Command;
    QPushButton *pbStartCustomConveyor3;
    QPushButton *pbStopCustomConveyor3;
    QLabel *label_147;
    QLineEdit *pbStartCustomConveyor2Command;
    QPushButton *pbStopCustomConveyor2;
    QLineEdit *pbStopCustomConveyor3Command;
    QLabel *label_153;
    QPushButton *pbStartCustomConveyor1;
    QPushButton *pbStopCustomConveyor1;
    QLineEdit *pbStopCustomConveyor1Command;
    QLineEdit *pbStartCustomConveyor1Command;
    QPushButton *pbStartCustomConveyor2;
    QLineEdit *pbStartCustomConveyor3Command;
    QLabel *label_154;
    QSpacerItem *verticalSpacer_2;
    QWidget *EncoderTab;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_51;
    QPushButton *pbConnectEncoder;
    QLabel *label_11;
    QComboBox *cbSelectedEncoder;
    QLabel *label_124;
    QComboBox *cbEncoderType;
    QLabel *lbEncoderCOMname;
    QSpacerItem *horizontalSpacer_14;
    QGridLayout *gridLayout_21;
    QLineEdit *leEncoderVelocity;
    QLineEdit *leEncoderInterval;
    QLineEdit *leEncoderCurrentPosition;
    QLabel *label_130;
    QPushButton *pbReadEncoder;
    QPushButton *pbSetEncoderVelocity;
    QPushButton *pbSetEncoderInterval;
    QSpacerItem *horizontalSpacer_23;
    QPushButton *pbResetEncoder;
    QLabel *label_129;
    QLabel *label_125;
    QCheckBox *cbEncoderActive;
    QSpacerItem *verticalSpacer_14;
    QWidget *SliderTab1;
    QVBoxLayout *verticalLayout_23;
    QHBoxLayout *horizontalLayout_49;
    QPushButton *pbSlidingConnect;
    QLabel *label_161;
    QComboBox *cbSelectedSlider;
    QLabel *lbSliderCOMName;
    QSpacerItem *horizontalSpacer_12;
    QGridLayout *gridLayout_8;
    QLineEdit *leSlidingPosition;
    QPushButton *pbSlidingDisable;
    QLabel *label_58;
    QLabel *label_37;
    QPushButton *pbSlidingHome;
    QLineEdit *leSlidingSpeed;
    QLabel *label_36;
    QLabel *label_59;
    QSpacerItem *verticalSpacer_3;
    QWidget *MCUTab;
    QVBoxLayout *verticalLayout_24;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_50;
    QPushButton *pbExternalControllerConnect;
    QLabel *label_162;
    QComboBox *cbSelectedDevice;
    QLabel *lbExternalCOMName;
    QSpacerItem *horizontalSpacer_25;
    QTextEdit *teReceiveFromMCU;
    QLineEdit *leTransmitToMCU;
    QWidget *PlusDeviceTab;

    void setupUi(QMainWindow *RobotWindow)
    {
        if (RobotWindow->objectName().isEmpty())
            RobotWindow->setObjectName(QString::fromUtf8("RobotWindow"));
        RobotWindow->resize(1210, 630);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RobotWindow->sizePolicy().hasHeightForWidth());
        RobotWindow->setSizePolicy(sizePolicy);
        RobotWindow->setMinimumSize(QSize(700, 400));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        font.setKerning(true);
        RobotWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("delta_x_logo_96x96.ico"), QSize(), QIcon::Normal, QIcon::Off);
        RobotWindow->setWindowIcon(icon);
        RobotWindow->setLayoutDirection(Qt::LeftToRight);
        RobotWindow->setStyleSheet(QString::fromUtf8("QLabel\n"
"{\n"
"	color: rgb(118, 118, 118);\n"
"}\n"
"/*\n"
"QWidget\n"
"{	\n"
"	background-color: rgb(255, 255, 255);\n"
"}*/\n"
"\n"
"/*\n"
"QScrollBar:horizontal {\n"
"    \n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"QScrollBar::handle:vertical {	\n"
"	\n"
"	background-color: rgb(118, 118, 118);\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"   \n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {	\n"
"	background-color: rgb(118, 118, 118);\n"
"}\n"
"\n"
"\n"
"QTabBar::tab\n"
"{\n"
"	padding: 10px;\n"
"}\n"
"\n"
"\n"
"QScrollArea\n"
"{\n"
"	border:none;\n"
"}\n"
"*/\n"
"/*\n"
"QMainWindow\n"
"{\n"
"	background-color: rgb(255,255,255);\n"
"}\n"
"\n"
"QPushButton\n"
"{	\n"
"	color: rgb(50, 50, 50);\n"
"	border: 1px solid rgb(50, 50, 50);\n"
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
""
                        "QGroupBox{\n"
"	color: rgb(50, 50, 50);\n"
"	border: 1px solid rgb(176, 176, 176);\n"
"	background: rgb(255, 255, 255);\n"
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
"	subcontrol-origin: padding;\n"
"    subcontrol-position: top right;\n"
"    width: 25px;\n"
"\n"
"    border-left-width: 1px;\n"
"    border-left-color: darkgray;\n"
"    border-left-style: solid; \n"
"    border-top-right-radius: 3px; \n"
"    border-bottom-right-radius: 3px;	\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(:/icon/icons8_expand_arrow_16px.png);\n"
"}\n"
"\n"
"QCheckBox, QComboBox, QLabel{\n"
"	color: rgb(50, 50, 50);\n"
"	background: none;\n"
"}\n"
"\n"
"\n"
"QScrollBar:horizontal {\n"
"    background: rgb(185, 185, 185);\n"
"}\n"
"QScrollBar::handle:vertical {	\n"
"	background-color: rgb(172, 172, 172);\n"
"}"
                        "\n"
"\n"
"QScrollBar:vertical {\n"
"    background: rgb(185, 185, 185);\n"
"}\n"
"\n"
"QScrollBar::handle:horizontal {	\n"
"	background-color: rgb(172, 172, 172);\n"
"}\n"
"\n"
"\n"
"QTabBar::tab\n"
"{\n"
"	padding: 10px;\n"
"}\n"
"\n"
"\n"
"QScrollArea\n"
"{\n"
"	border:none;\n"
"}\n"
"\n"
"*/\n"
"\n"
"QGroupBox {\n"
"}\n"
"\n"
"QGroupBox:disabled {\n"
"	color: palette(shadow);\n"
"}\n"
"\n"
"QGroupBox[overrided=\"true\"] {\n"
"	color: red;\n"
"}\n"
"\n"
"QGroupBox[overrided=\"false\"] {\n"
"	color: palette(windowtext);\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::title {\n"
"	margin-top: 1px;\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::indicator {\n"
"	padding: 0 -2 -0 2;\n"
"	width: 13;\n"
"	height: 13;\n"
"}\n"
"\n"
"QGroupBox::indicator:checked {	\n"
"	image: url(:/icon/collapse.png);\n"
"}\n"
"\n"
"QGroupBox::indicator:unchecked {	\n"
"	image: url(:/icon/expand.png);\n"
"}"));
        actionAdd = new QAction(RobotWindow);
        actionAdd->setObjectName(QString::fromUtf8("actionAdd"));
        actionRemove = new QAction(RobotWindow);
        actionRemove->setObjectName(QString::fromUtf8("actionRemove"));
        actionAbout = new QAction(RobotWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionGcode = new QAction(RobotWindow);
        actionGcode->setObjectName(QString::fromUtf8("actionGcode"));
        actionSoftware = new QAction(RobotWindow);
        actionSoftware->setObjectName(QString::fromUtf8("actionSoftware"));
        actionExecute_All = new QAction(RobotWindow);
        actionExecute_All->setObjectName(QString::fromUtf8("actionExecute_All"));
        actionDelta_X_1 = new QAction(RobotWindow);
        actionDelta_X_1->setObjectName(QString::fromUtf8("actionDelta_X_1"));
        actionDelta_X_1->setCheckable(true);
        actionDelta_X_1->setChecked(true);
        actionExecute = new QAction(RobotWindow);
        actionExecute->setObjectName(QString::fromUtf8("actionExecute"));
        actionBaudrate = new QAction(RobotWindow);
        actionBaudrate->setObjectName(QString::fromUtf8("actionBaudrate"));
        actionScale = new QAction(RobotWindow);
        actionScale->setObjectName(QString::fromUtf8("actionScale"));
        centralWidget = new QWidget(RobotWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_15 = new QVBoxLayout(centralWidget);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        twDeltaManager = new QTabWidget(centralWidget);
        twDeltaManager->setObjectName(QString::fromUtf8("twDeltaManager"));
        twDeltaManager->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(twDeltaManager->sizePolicy().hasHeightForWidth());
        twDeltaManager->setSizePolicy(sizePolicy1);
        twDeltaManager->setMinimumSize(QSize(0, 0));
        twDeltaManager->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setKerning(true);
        twDeltaManager->setFont(font1);
        twDeltaManager->setLayoutDirection(Qt::LeftToRight);
        twDeltaManager->setStyleSheet(QString::fromUtf8("QTabWidget::pane { /* The tab widget frame */\n"
"    border: none;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    left: 10px; /* move to the right by 5px */\n"
"}\n"
"\n"
"/* Style the tab using the tab sub-control. Note that\n"
"    it reads QTabBar _not_ QTabWidget */\n"
"QTabBar::tab {\n"
"    background: rgb(200, 200, 200);\n"
"	color: rgb(100, 100, 100);\n"
"    border-radius: 13px;\n"
"    min-height: 25px;\n"
"    padding: 2px 20px 2px 20px;\n"
"	margin-left:5px;\n"
"	margin-right:5px;\n"
"	margin-top:2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: rgb(33, 125, 206);	\n"
"	color: rgb(255, 255, 255);\n"
"	border-radius: 13px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 5px; /* make non-selected tabs look smaller */\n"
"}\n"
"\n"
""));
        twDeltaManager->setTabPosition(QTabWidget::North);
        tabDefaultDelta = new QWidget();
        tabDefaultDelta->setObjectName(QString::fromUtf8("tabDefaultDelta"));
        twDeltaManager->addTab(tabDefaultDelta, QString());
        tabAddNewDelta = new QWidget();
        tabAddNewDelta->setObjectName(QString::fromUtf8("tabAddNewDelta"));
        twDeltaManager->addTab(tabAddNewDelta, QString());

        verticalLayout_15->addWidget(twDeltaManager);

        frame_11 = new QFrame(centralWidget);
        frame_11->setObjectName(QString::fromUtf8("frame_11"));
        frame_11->setMinimumSize(QSize(0, 25));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Raised);
        horizontalLayout_34 = new QHBoxLayout(frame_11);
        horizontalLayout_34->setSpacing(10);
        horizontalLayout_34->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_34->setContentsMargins(0, 0, 0, 0);
        label_122 = new QLabel(frame_11);
        label_122->setObjectName(QString::fromUtf8("label_122"));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_122->setFont(font2);
        label_122->setAlignment(Qt::AlignCenter);

        horizontalLayout_34->addWidget(label_122);

        leIP = new QLineEdit(frame_11);
        leIP->setObjectName(QString::fromUtf8("leIP"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(leIP->sizePolicy().hasHeightForWidth());
        leIP->setSizePolicy(sizePolicy2);
        leIP->setFrame(false);
        leIP->setDragEnabled(false);
        leIP->setReadOnly(true);
        leIP->setClearButtonEnabled(false);

        horizontalLayout_34->addWidget(leIP);

        label_123 = new QLabel(frame_11);
        label_123->setObjectName(QString::fromUtf8("label_123"));
        label_123->setFont(font2);
        label_123->setAlignment(Qt::AlignCenter);

        horizontalLayout_34->addWidget(label_123);

        lePort = new QLineEdit(frame_11);
        lePort->setObjectName(QString::fromUtf8("lePort"));
        sizePolicy.setHeightForWidth(lePort->sizePolicy().hasHeightForWidth());
        lePort->setSizePolicy(sizePolicy);
        lePort->setFrame(false);
        lePort->setDragEnabled(false);
        lePort->setReadOnly(true);
        lePort->setClearButtonEnabled(false);

        horizontalLayout_34->addWidget(lePort);

        tbServerConfig = new QToolButton(frame_11);
        tbServerConfig->setObjectName(QString::fromUtf8("tbServerConfig"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icons8_edit_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbServerConfig->setIcon(icon1);

        horizontalLayout_34->addWidget(tbServerConfig);

        horizontalSpacer_26 = new QSpacerItem(853, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_34->addItem(horizontalSpacer_26);


        verticalLayout_15->addWidget(frame_11);

        tabManagerLayout = new QWidget(centralWidget);
        tabManagerLayout->setObjectName(QString::fromUtf8("tabManagerLayout"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabManagerLayout->sizePolicy().hasHeightForWidth());
        tabManagerLayout->setSizePolicy(sizePolicy3);
        tabManagerLayout->setMinimumSize(QSize(0, 0));
        tabManagerLayout->setStyleSheet(QString::fromUtf8("QTabWidget::pane { /* The tab widget frame */\n"
"    border: none;\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"    left: 10px; /* move to the right by 5px */\n"
"}\n"
"\n"
"/* Style the tab using the tab sub-control. Note that\n"
"    it reads QTabBar _not_ QTabWidget */\n"
"QTabBar::tab {\n"
"    background: rgb(200, 200, 200);\n"
"	color: rgb(100, 100, 100);\n"
"   /* border-radius: 13px;*/\n"
"    height: 25px;\n"
"    padding: 0px 20px 2px 20px;\n"
"	margin-left:5px;\n"
"	margin-right:5px;\n"
"	margin-top:2px;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"    background: rgb(33, 125, 206);	\n"
"	color: rgb(255, 255, 255);\n"
"	/*border-radius: 13px;*/\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"    margin-top: 5px; /* make non-selected tabs look smaller */\n"
"}"));
        verticalLayout_46 = new QVBoxLayout(tabManagerLayout);
        verticalLayout_46->setSpacing(0);
        verticalLayout_46->setContentsMargins(11, 11, 11, 11);
        verticalLayout_46->setObjectName(QString::fromUtf8("verticalLayout_46"));
        verticalLayout_46->setContentsMargins(0, 0, 0, 0);
        splitter_2 = new QSplitter(tabManagerLayout);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setMinimumSize(QSize(0, 220));
        splitter_2->setStyleSheet(QString::fromUtf8("QSplitter::handle:horizontal {    \n"
"	\n"
"	image: url(:/icon/divider_50px.png);\n"
"}"));
        splitter_2->setOrientation(Qt::Horizontal);
        splitter_2->setOpaqueResize(false);
        splitter_2->setHandleWidth(20);
        ModuleTabManagerWidget = new QWidget(splitter_2);
        ModuleTabManagerWidget->setObjectName(QString::fromUtf8("ModuleTabManagerWidget"));
        ModuleTabManagerWidget->setMinimumSize(QSize(0, 0));
        ModuleTabManagerWidget->setStyleSheet(QString::fromUtf8(""));
        ModuleTabManagerLayout = new QVBoxLayout(ModuleTabManagerWidget);
        ModuleTabManagerLayout->setSpacing(0);
        ModuleTabManagerLayout->setContentsMargins(11, 11, 11, 11);
        ModuleTabManagerLayout->setObjectName(QString::fromUtf8("ModuleTabManagerLayout"));
        ModuleTabManagerLayout->setContentsMargins(0, 0, 0, 0);
        twModule = new QTabWidget(ModuleTabManagerWidget);
        twModule->setObjectName(QString::fromUtf8("twModule"));
        twModule->setEnabled(true);
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(false);
        font3.setWeight(50);
        twModule->setFont(font3);
        twModule->setFocusPolicy(Qt::TabFocus);
        twModule->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::title {\n"
"	margin-top: 1px;\n"
"}\n"
"\n"
"QGroupBox[checkable=\"true\"]::indicator {\n"
"	padding: 0 -2 -0 2;\n"
"	width: 13;\n"
"	height: 13;\n"
"}\n"
"\n"
"QGroupBox::indicator:checked {	\n"
"	image: url(:/icon/collapse.png);\n"
"}\n"
"\n"
"QGroupBox::indicator:unchecked {	\n"
"	image: url(:/icon/expand.png);\n"
"}\n"
"\n"
"QToolBox::tab\n"
"{	\n"
"	background-image: url(:/icon/icons8_collapse_arrow_10px.png);\n"
"	background-repeat: no-repeat;\n"
"	background-origin: content;\n"
"	padding-left: 5px;\n"
"	padding-top: 2px;\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(33, 125, 206);\n"
"}\n"
"QToolBox::tab:selected\n"
"{	\n"
"	background-image: url(:/icon/icons8_expand_arrow_10px.png);\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(33, 125, 206);\n"
"}\n"
"/*\n"
"QToolBox QScrollArea>QWidget>QWidget\n"
"{\n"
"  background: rgb(255, 255, 255);\n"
"}*/"));
        twModule->setTabShape(QTabWidget::Rounded);
        twModule->setUsesScrollButtons(true);
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
        gridLayout_30 = new QGridLayout();
        gridLayout_30->setSpacing(6);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_30->addItem(horizontalSpacer_3, 2, 5, 1, 1);

        rbEditorCurrent = new QRadioButton(tGcodeEditor);
        rbEditorCurrent->setObjectName(QString::fromUtf8("rbEditorCurrent"));
        rbEditorCurrent->setChecked(false);

        gridLayout_30->addWidget(rbEditorCurrent, 2, 6, 1, 1);

        pbExecuteGcodes = new QPushButton(tGcodeEditor);
        pbExecuteGcodes->setObjectName(QString::fromUtf8("pbExecuteGcodes"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pbExecuteGcodes->sizePolicy().hasHeightForWidth());
        pbExecuteGcodes->setSizePolicy(sizePolicy4);
        pbExecuteGcodes->setMinimumSize(QSize(70, 0));
        QFont font4;
        font4.setPointSize(10);
        pbExecuteGcodes->setFont(font4);
        pbExecuteGcodes->setAutoFillBackground(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/Play_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/icon/Pause_96px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbExecuteGcodes->setIcon(icon2);
        pbExecuteGcodes->setIconSize(QSize(30, 30));
        pbExecuteGcodes->setCheckable(true);
        pbExecuteGcodes->setFlat(false);

        gridLayout_30->addWidget(pbExecuteGcodes, 0, 7, 3, 1);

        label_7 = new QLabel(tGcodeEditor);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_30->addWidget(label_7, 0, 0, 1, 1);

        rbEditorStart = new QRadioButton(tGcodeEditor);
        rbEditorStart->setObjectName(QString::fromUtf8("rbEditorStart"));
        rbEditorStart->setChecked(true);

        gridLayout_30->addWidget(rbEditorStart, 0, 6, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_30->addItem(horizontalSpacer_2, 0, 5, 1, 1);

        cbProgramThreadID = new QComboBox(tGcodeEditor);
        cbProgramThreadID->addItem(QString());
        cbProgramThreadID->addItem(QString());
        cbProgramThreadID->addItem(QString());
        cbProgramThreadID->addItem(QString());
        cbProgramThreadID->setObjectName(QString::fromUtf8("cbProgramThreadID"));

        gridLayout_30->addWidget(cbProgramThreadID, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_30);

        frame_10 = new QFrame(tGcodeEditor);
        frame_10->setObjectName(QString::fromUtf8("frame_10"));
        frame_10->setMinimumSize(QSize(0, 0));
        frame_10->setFrameShape(QFrame::StyledPanel);
        frame_10->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(frame_10);
        horizontalLayout_9->setSpacing(2);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(2, 2, 2, 2);
        pbOpenGcodeDocs = new QToolButton(frame_10);
        pbOpenGcodeDocs->setObjectName(QString::fromUtf8("pbOpenGcodeDocs"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icons8_help_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenGcodeDocs->setIcon(icon3);
        pbOpenGcodeDocs->setIconSize(QSize(32, 32));
        pbOpenGcodeDocs->setAutoRaise(true);

        horizontalLayout_9->addWidget(pbOpenGcodeDocs);

        pbSaveGcode = new QToolButton(frame_10);
        pbSaveGcode->setObjectName(QString::fromUtf8("pbSaveGcode"));
        sizePolicy.setHeightForWidth(pbSaveGcode->sizePolicy().hasHeightForWidth());
        pbSaveGcode->setSizePolicy(sizePolicy);
        pbSaveGcode->setMinimumSize(QSize(30, 30));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icons8_save_52px_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSaveGcode->setIcon(icon4);
        pbSaveGcode->setIconSize(QSize(32, 32));
        pbSaveGcode->setAutoRaise(true);

        horizontalLayout_9->addWidget(pbSaveGcode);

        pbCreateNewGcode = new QToolButton(frame_10);
        pbCreateNewGcode->setObjectName(QString::fromUtf8("pbCreateNewGcode"));
        sizePolicy.setHeightForWidth(pbCreateNewGcode->sizePolicy().hasHeightForWidth());
        pbCreateNewGcode->setSizePolicy(sizePolicy);
        pbCreateNewGcode->setMinimumSize(QSize(30, 30));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/icons8_add_new_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCreateNewGcode->setIcon(icon5);
        pbCreateNewGcode->setIconSize(QSize(32, 32));
        pbCreateNewGcode->setAutoRaise(true);

        horizontalLayout_9->addWidget(pbCreateNewGcode);

        pbFormat = new QToolButton(frame_10);
        pbFormat->setObjectName(QString::fromUtf8("pbFormat"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/icons8_view_details_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFormat->setIcon(icon6);
        pbFormat->setIconSize(QSize(32, 32));
        pbFormat->setAutoRaise(true);

        horizontalLayout_9->addWidget(pbFormat);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_13);

        cbEditGcodeEditor = new QCheckBox(frame_10);
        cbEditGcodeEditor->setObjectName(QString::fromUtf8("cbEditGcodeEditor"));
        QFont font5;
        font5.setPointSize(8);
        font5.setBold(false);
        font5.setWeight(50);
        font5.setKerning(true);
        cbEditGcodeEditor->setFont(font5);
        cbEditGcodeEditor->setIcon(icon1);
        cbEditGcodeEditor->setIconSize(QSize(32, 32));
        cbEditGcodeEditor->setChecked(true);

        horizontalLayout_9->addWidget(cbEditGcodeEditor);


        verticalLayout->addWidget(frame_10);

        scrollArea = new QScrollArea(tGcodeEditor);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 471, 1200));
        scrollAreaWidgetContents->setMinimumSize(QSize(450, 1200));
        verticalLayout_19 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_119 = new QLabel(scrollAreaWidgetContents);
        label_119->setObjectName(QString::fromUtf8("label_119"));

        verticalLayout_2->addWidget(label_119);

        tbAddG28 = new QToolButton(scrollAreaWidgetContents);
        tbAddG28->setObjectName(QString::fromUtf8("tbAddG28"));

        verticalLayout_2->addWidget(tbAddG28);

        label_120 = new QLabel(scrollAreaWidgetContents);
        label_120->setObjectName(QString::fromUtf8("label_120"));

        verticalLayout_2->addWidget(label_120);

        tbAddG01 = new QToolButton(scrollAreaWidgetContents);
        tbAddG01->setObjectName(QString::fromUtf8("tbAddG01"));

        verticalLayout_2->addWidget(tbAddG01);

        tbAddG02 = new QToolButton(scrollAreaWidgetContents);
        tbAddG02->setObjectName(QString::fromUtf8("tbAddG02"));

        verticalLayout_2->addWidget(tbAddG02);

        label_121 = new QLabel(scrollAreaWidgetContents);
        label_121->setObjectName(QString::fromUtf8("label_121"));

        verticalLayout_2->addWidget(label_121);

        tbAddG04 = new QToolButton(scrollAreaWidgetContents);
        tbAddG04->setObjectName(QString::fromUtf8("tbAddG04"));

        verticalLayout_2->addWidget(tbAddG04);

        label_127 = new QLabel(scrollAreaWidgetContents);
        label_127->setObjectName(QString::fromUtf8("label_127"));

        verticalLayout_2->addWidget(label_127);

        tbAddM03 = new QToolButton(scrollAreaWidgetContents);
        tbAddM03->setObjectName(QString::fromUtf8("tbAddM03"));

        verticalLayout_2->addWidget(tbAddM03);

        tbAddM05 = new QToolButton(scrollAreaWidgetContents);
        tbAddM05->setObjectName(QString::fromUtf8("tbAddM05"));

        verticalLayout_2->addWidget(tbAddM05);

        label_131 = new QLabel(scrollAreaWidgetContents);
        label_131->setObjectName(QString::fromUtf8("label_131"));

        verticalLayout_2->addWidget(label_131);

        tbAddM07 = new QToolButton(scrollAreaWidgetContents);
        tbAddM07->setObjectName(QString::fromUtf8("tbAddM07"));

        verticalLayout_2->addWidget(tbAddM07);

        tbAddM08 = new QToolButton(scrollAreaWidgetContents);
        tbAddM08->setObjectName(QString::fromUtf8("tbAddM08"));

        verticalLayout_2->addWidget(tbAddM08);

        verticalSpacer_15 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_15);


        horizontalLayout_16->addLayout(verticalLayout_2);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        pteGcodeArea = new CodeEditor(scrollAreaWidgetContents);
        pteGcodeArea->setObjectName(QString::fromUtf8("pteGcodeArea"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pteGcodeArea->sizePolicy().hasHeightForWidth());
        pteGcodeArea->setSizePolicy(sizePolicy5);
        pteGcodeArea->setMinimumSize(QSize(310, 500));
        pteGcodeArea->setFont(font5);
        pteGcodeArea->setStyleSheet(QString::fromUtf8(""));
        pteGcodeArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pteGcodeArea->setReadOnly(false);
        pteGcodeArea->setTextInteractionFlags(Qt::TextEditorInteraction);

        verticalLayout_13->addWidget(pteGcodeArea);

        fGcodePara = new QFrame(scrollAreaWidgetContents);
        fGcodePara->setObjectName(QString::fromUtf8("fGcodePara"));
        horizontalLayout_12 = new QHBoxLayout(fGcodePara);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_49 = new QLabel(fGcodePara);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        horizontalLayout_12->addWidget(label_49);

        lineEdit = new QLineEdit(fGcodePara);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        horizontalLayout_12->addWidget(lineEdit);

        label_118 = new QLabel(fGcodePara);
        label_118->setObjectName(QString::fromUtf8("label_118"));

        horizontalLayout_12->addWidget(label_118);

        lineEdit_2 = new QLineEdit(fGcodePara);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        horizontalLayout_12->addWidget(lineEdit_2);

        label_134 = new QLabel(fGcodePara);
        label_134->setObjectName(QString::fromUtf8("label_134"));

        horizontalLayout_12->addWidget(label_134);

        lineEdit_3 = new QLineEdit(fGcodePara);
        lineEdit_3->setObjectName(QString::fromUtf8("lineEdit_3"));

        horizontalLayout_12->addWidget(lineEdit_3);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_11);

        label_135 = new QLabel(fGcodePara);
        label_135->setObjectName(QString::fromUtf8("label_135"));

        horizontalLayout_12->addWidget(label_135);

        lineEdit_4 = new QLineEdit(fGcodePara);
        lineEdit_4->setObjectName(QString::fromUtf8("lineEdit_4"));

        horizontalLayout_12->addWidget(lineEdit_4);

        label_141 = new QLabel(fGcodePara);
        label_141->setObjectName(QString::fromUtf8("label_141"));

        horizontalLayout_12->addWidget(label_141);

        lineEdit_5 = new QLineEdit(fGcodePara);
        lineEdit_5->setObjectName(QString::fromUtf8("lineEdit_5"));

        horizontalLayout_12->addWidget(lineEdit_5);

        label_142 = new QLabel(fGcodePara);
        label_142->setObjectName(QString::fromUtf8("label_142"));

        horizontalLayout_12->addWidget(label_142);

        lineEdit_6 = new QLineEdit(fGcodePara);
        lineEdit_6->setObjectName(QString::fromUtf8("lineEdit_6"));

        horizontalLayout_12->addWidget(lineEdit_6);

        label_148 = new QLabel(fGcodePara);
        label_148->setObjectName(QString::fromUtf8("label_148"));

        horizontalLayout_12->addWidget(label_148);

        lineEdit_7 = new QLineEdit(fGcodePara);
        lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));

        horizontalLayout_12->addWidget(lineEdit_7);

        label_149 = new QLabel(fGcodePara);
        label_149->setObjectName(QString::fromUtf8("label_149"));

        horizontalLayout_12->addWidget(label_149);

        lineEdit_8 = new QLineEdit(fGcodePara);
        lineEdit_8->setObjectName(QString::fromUtf8("lineEdit_8"));

        horizontalLayout_12->addWidget(lineEdit_8);

        label_150 = new QLabel(fGcodePara);
        label_150->setObjectName(QString::fromUtf8("label_150"));

        horizontalLayout_12->addWidget(label_150);

        lineEdit_9 = new QLineEdit(fGcodePara);
        lineEdit_9->setObjectName(QString::fromUtf8("lineEdit_9"));

        horizontalLayout_12->addWidget(lineEdit_9);

        label_151 = new QLabel(fGcodePara);
        label_151->setObjectName(QString::fromUtf8("label_151"));

        horizontalLayout_12->addWidget(label_151);

        lineEdit_10 = new QLineEdit(fGcodePara);
        lineEdit_10->setObjectName(QString::fromUtf8("lineEdit_10"));

        horizontalLayout_12->addWidget(lineEdit_10);

        label_152 = new QLabel(fGcodePara);
        label_152->setObjectName(QString::fromUtf8("label_152"));

        horizontalLayout_12->addWidget(label_152);

        lineEdit_11 = new QLineEdit(fGcodePara);
        lineEdit_11->setObjectName(QString::fromUtf8("lineEdit_11"));

        horizontalLayout_12->addWidget(lineEdit_11);


        verticalLayout_13->addWidget(fGcodePara);


        horizontalLayout_16->addLayout(verticalLayout_13);


        verticalLayout_19->addLayout(horizontalLayout_16);

        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 500));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        verticalLayout_9 = new QVBoxLayout(tab_3);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_3 = new QLabel(tab_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_8->addWidget(label_3);

        tbOpenGcodePath = new QToolButton(tab_3);
        tbOpenGcodePath->setObjectName(QString::fromUtf8("tbOpenGcodePath"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/icons8_folder_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbOpenGcodePath->setIcon(icon7);

        horizontalLayout_8->addWidget(tbOpenGcodePath);

        leGcodeExplorer = new QLineEdit(tab_3);
        leGcodeExplorer->setObjectName(QString::fromUtf8("leGcodeExplorer"));

        horizontalLayout_8->addWidget(leGcodeExplorer);


        verticalLayout_9->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        tbBackGcodeFolder = new QToolButton(tab_3);
        tbBackGcodeFolder->setObjectName(QString::fromUtf8("tbBackGcodeFolder"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/icon/icons8_back_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbBackGcodeFolder->setIcon(icon8);

        horizontalLayout_6->addWidget(tbBackGcodeFolder);

        tbNewGcodeFile = new QToolButton(tab_3);
        tbNewGcodeFile->setObjectName(QString::fromUtf8("tbNewGcodeFile"));
        tbNewGcodeFile->setIcon(icon5);

        horizontalLayout_6->addWidget(tbNewGcodeFile);

        tbRefreshExplorer = new QToolButton(tab_3);
        tbRefreshExplorer->setObjectName(QString::fromUtf8("tbRefreshExplorer"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/icon/icons8_refresh_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbRefreshExplorer->setIcon(icon9);

        horizontalLayout_6->addWidget(tbRefreshExplorer);

        tbDeleteGcodeFile = new QToolButton(tab_3);
        tbDeleteGcodeFile->setObjectName(QString::fromUtf8("tbDeleteGcodeFile"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/icon/icons8_close_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbDeleteGcodeFile->setIcon(icon10);

        horizontalLayout_6->addWidget(tbDeleteGcodeFile);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_10);


        verticalLayout_9->addLayout(horizontalLayout_6);

        tvGcodeExplorer = new QTreeView(tab_3);
        tvGcodeExplorer->setObjectName(QString::fromUtf8("tvGcodeExplorer"));

        verticalLayout_9->addWidget(tvGcodeExplorer);

        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout_19->addWidget(tabWidget);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_19->addItem(verticalSpacer_9);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        twModule->addTab(tGcodeEditor, QString());
        tObjectDetecting = new QWidget();
        tObjectDetecting->setObjectName(QString::fromUtf8("tObjectDetecting"));
        tObjectDetecting->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_25 = new QVBoxLayout(tObjectDetecting);
        verticalLayout_25->setSpacing(5);
        verticalLayout_25->setContentsMargins(11, 11, 11, 11);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(0, 5, 0, 0);
        saObjectDetecting = new QScrollArea(tObjectDetecting);
        saObjectDetecting->setObjectName(QString::fromUtf8("saObjectDetecting"));
        saObjectDetecting->setLineWidth(1);
        saObjectDetecting->setWidgetResizable(true);
        wObjectDetecting = new QWidget();
        wObjectDetecting->setObjectName(QString::fromUtf8("wObjectDetecting"));
        wObjectDetecting->setGeometry(QRect(0, -892, 493, 4000));
        wObjectDetecting->setMinimumSize(QSize(100, 4000));
        wObjectDetecting->setStyleSheet(QString::fromUtf8("QWidget#wObjectDetecting\n"
"{	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
""));
        verticalLayout_17 = new QVBoxLayout(wObjectDetecting);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_191 = new QLabel(wObjectDetecting);
        label_191->setObjectName(QString::fromUtf8("label_191"));

        horizontalLayout_17->addWidget(label_191);

        cbSelectedDetecting = new QComboBox(wObjectDetecting);
        cbSelectedDetecting->addItem(QString());
        cbSelectedDetecting->addItem(QString());
        cbSelectedDetecting->addItem(QString());
        cbSelectedDetecting->addItem(QString());
        cbSelectedDetecting->setObjectName(QString::fromUtf8("cbSelectedDetecting"));
        QSizePolicy sizePolicy6(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(cbSelectedDetecting->sizePolicy().hasHeightForWidth());
        cbSelectedDetecting->setSizePolicy(sizePolicy6);

        horizontalLayout_17->addWidget(cbSelectedDetecting);

        horizontalSpacer_49 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_49);


        verticalLayout_17->addLayout(horizontalLayout_17);

        splitter = new QSplitter(wObjectDetecting);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy3.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy3);
        splitter->setStyleSheet(QString::fromUtf8("QSplitter::handle:vertical \n"
"{	\n"
"	background: rgb(37, 197, 255);\n"
"}"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(10);
        gbImageViewer = new QGroupBox(splitter);
        gbImageViewer->setObjectName(QString::fromUtf8("gbImageViewer"));
        sizePolicy1.setHeightForWidth(gbImageViewer->sizePolicy().hasHeightForWidth());
        gbImageViewer->setSizePolicy(sizePolicy1);
        gbImageViewer->setMinimumSize(QSize(0, 0));
        gbImageViewer->setMaximumSize(QSize(16777215, 16777215));
        QFont font6;
        font6.setPointSize(10);
        font6.setBold(true);
        font6.setWeight(75);
        gbImageViewer->setFont(font6);
        gbImageViewer->setCheckable(true);
        vlImageViewer = new QVBoxLayout(gbImageViewer);
        vlImageViewer->setSpacing(0);
        vlImageViewer->setContentsMargins(11, 11, 11, 11);
        vlImageViewer->setObjectName(QString::fromUtf8("vlImageViewer"));
        vlImageViewer->setContentsMargins(0, 0, 0, 0);
        fImageViewer = new QFrame(gbImageViewer);
        fImageViewer->setObjectName(QString::fromUtf8("fImageViewer"));
        fImageViewer->setFrameShape(QFrame::StyledPanel);
        fImageViewer->setFrameShadow(QFrame::Raised);
        horizontalLayout_30 = new QHBoxLayout(fImageViewer);
        horizontalLayout_30->setSpacing(5);
        horizontalLayout_30->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        horizontalLayout_30->setContentsMargins(5, 5, 5, 5);
        frame_16 = new QFrame(fImageViewer);
        frame_16->setObjectName(QString::fromUtf8("frame_16"));
        frame_16->setMinimumSize(QSize(30, 0));
        frame_16->setFrameShape(QFrame::StyledPanel);
        frame_16->setFrameShadow(QFrame::Raised);
        verticalLayout_7 = new QVBoxLayout(frame_16);
        verticalLayout_7->setSpacing(5);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        verticalLayout_7->setContentsMargins(0, 5, 0, 5);
        pbFindChessboardTool = new QPushButton(frame_16);
        pbFindChessboardTool->setObjectName(QString::fromUtf8("pbFindChessboardTool"));
        pbFindChessboardTool->setMinimumSize(QSize(30, 30));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icon/icons8_chessboard_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFindChessboardTool->setIcon(icon11);
        pbFindChessboardTool->setIconSize(QSize(24, 24));
        pbFindChessboardTool->setCheckable(true);
        pbFindChessboardTool->setFlat(true);

        verticalLayout_7->addWidget(pbFindChessboardTool);

        pbWarpTool = new QPushButton(frame_16);
        pbWarpTool->setObjectName(QString::fromUtf8("pbWarpTool"));
        pbWarpTool->setMinimumSize(QSize(30, 30));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icon/icons8_opacity_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbWarpTool->setIcon(icon12);
        pbWarpTool->setIconSize(QSize(24, 24));
        pbWarpTool->setCheckable(true);
        pbWarpTool->setFlat(true);

        verticalLayout_7->addWidget(pbWarpTool);

        pbAreaTool = new QPushButton(frame_16);
        pbAreaTool->setObjectName(QString::fromUtf8("pbAreaTool"));
        pbAreaTool->setMinimumSize(QSize(30, 30));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icon/icons8_rectangle_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbAreaTool->setIcon(icon13);
        pbAreaTool->setIconSize(QSize(24, 24));
        pbAreaTool->setCheckable(true);
        pbAreaTool->setFlat(true);

        verticalLayout_7->addWidget(pbAreaTool);

        pbCalibPointTool = new QPushButton(frame_16);
        pbCalibPointTool->setObjectName(QString::fromUtf8("pbCalibPointTool"));
        pbCalibPointTool->setMinimumSize(QSize(30, 30));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/icon/icons8_select_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCalibPointTool->setIcon(icon14);
        pbCalibPointTool->setIconSize(QSize(24, 24));
        pbCalibPointTool->setCheckable(true);
        pbCalibPointTool->setFlat(true);

        verticalLayout_7->addWidget(pbCalibPointTool);

        pbMappingPointTool = new QPushButton(frame_16);
        pbMappingPointTool->setObjectName(QString::fromUtf8("pbMappingPointTool"));
        pbMappingPointTool->setMinimumSize(QSize(30, 30));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icon/icons8_target_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbMappingPointTool->setIcon(icon15);
        pbMappingPointTool->setIconSize(QSize(24, 24));
        pbMappingPointTool->setCheckable(true);
        pbMappingPointTool->setFlat(true);

        verticalLayout_7->addWidget(pbMappingPointTool);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_7->addItem(verticalSpacer_12);


        horizontalLayout_30->addWidget(frame_16);

        frame_8 = new QFrame(fImageViewer);
        frame_8->setObjectName(QString::fromUtf8("frame_8"));
        frame_8->setMinimumSize(QSize(20, 0));
        frame_8->setFrameShape(QFrame::StyledPanel);
        frame_8->setFrameShadow(QFrame::Raised);
        verticalLayout_50 = new QVBoxLayout(frame_8);
        verticalLayout_50->setSpacing(5);
        verticalLayout_50->setContentsMargins(11, 11, 11, 11);
        verticalLayout_50->setObjectName(QString::fromUtf8("verticalLayout_50"));
        verticalLayout_50->setContentsMargins(0, 5, 0, 5);
        pbGetSizeTool = new QToolButton(frame_8);
        pbGetSizeTool->setObjectName(QString::fromUtf8("pbGetSizeTool"));
        pbGetSizeTool->setMinimumSize(QSize(30, 30));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icon/icons8_page_size_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbGetSizeTool->setIcon(icon16);
        pbGetSizeTool->setIconSize(QSize(24, 24));
        pbGetSizeTool->setCheckable(true);
        pbGetSizeTool->setAutoRaise(true);

        verticalLayout_50->addWidget(pbGetSizeTool);

        pbFilterTool = new QPushButton(frame_8);
        pbFilterTool->setObjectName(QString::fromUtf8("pbFilterTool"));
        pbFilterTool->setMinimumSize(QSize(30, 30));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icon/Slider 2_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFilterTool->setIcon(icon17);
        pbFilterTool->setIconSize(QSize(24, 24));
        pbFilterTool->setFlat(true);

        verticalLayout_50->addWidget(pbFilterTool);

        pbOpenObjectTable = new QPushButton(frame_8);
        pbOpenObjectTable->setObjectName(QString::fromUtf8("pbOpenObjectTable"));
        pbOpenObjectTable->setMinimumSize(QSize(30, 30));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icon/icons8-object-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenObjectTable->setIcon(icon18);
        pbOpenObjectTable->setIconSize(QSize(24, 24));
        pbOpenObjectTable->setFlat(true);

        verticalLayout_50->addWidget(pbOpenObjectTable);

        pbClearObject = new QPushButton(frame_8);
        pbClearObject->setObjectName(QString::fromUtf8("pbClearObject"));
        pbClearObject->setMinimumSize(QSize(30, 30));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/icon/Eraser_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbClearObject->setIcon(icon19);
        pbClearObject->setIconSize(QSize(24, 24));
        pbClearObject->setFlat(true);

        verticalLayout_50->addWidget(pbClearObject);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_50->addItem(verticalSpacer_13);


        horizontalLayout_30->addWidget(frame_8);

        gvImageViewer = new ImageViewer(fImageViewer);
        gvImageViewer->setObjectName(QString::fromUtf8("gvImageViewer"));
        sizePolicy3.setHeightForWidth(gvImageViewer->sizePolicy().hasHeightForWidth());
        gvImageViewer->setSizePolicy(sizePolicy3);

        horizontalLayout_30->addWidget(gvImageViewer);

        frame_17 = new QFrame(fImageViewer);
        frame_17->setObjectName(QString::fromUtf8("frame_17"));
        frame_17->setMinimumSize(QSize(30, 0));
        frame_17->setFrameShape(QFrame::StyledPanel);
        frame_17->setFrameShadow(QFrame::Raised);
        verticalLayout_10 = new QVBoxLayout(frame_17);
        verticalLayout_10->setSpacing(5);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(5, 5, 5, 5);
        label_213 = new QLabel(frame_17);
        label_213->setObjectName(QString::fromUtf8("label_213"));

        verticalLayout_10->addWidget(label_213);

        cbImageOutput = new QComboBox(frame_17);
        cbImageOutput->addItem(QString());
        cbImageOutput->addItem(QString());
        cbImageOutput->addItem(QString());
        cbImageOutput->setObjectName(QString::fromUtf8("cbImageOutput"));
        cbImageOutput->setEnabled(false);
        QSizePolicy sizePolicy7(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(cbImageOutput->sizePolicy().hasHeightForWidth());
        cbImageOutput->setSizePolicy(sizePolicy7);
        cbImageOutput->setMinimumSize(QSize(90, 0));

        verticalLayout_10->addWidget(cbImageOutput);

        lbDisplayRatio_2 = new QLabel(frame_17);
        lbDisplayRatio_2->setObjectName(QString::fromUtf8("lbDisplayRatio_2"));

        verticalLayout_10->addWidget(lbDisplayRatio_2);

        lbDisplayRatio_3 = new QLabel(frame_17);
        lbDisplayRatio_3->setObjectName(QString::fromUtf8("lbDisplayRatio_3"));

        verticalLayout_10->addWidget(lbDisplayRatio_3);

        verticalSpacer_10 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer_10);

        lbDisplayRatio = new QLabel(frame_17);
        lbDisplayRatio->setObjectName(QString::fromUtf8("lbDisplayRatio"));

        verticalLayout_10->addWidget(lbDisplayRatio);

        lbMatSize = new QLabel(frame_17);
        lbMatSize->setObjectName(QString::fromUtf8("lbMatSize"));

        verticalLayout_10->addWidget(lbMatSize);


        horizontalLayout_30->addWidget(frame_17);


        vlImageViewer->addWidget(fImageViewer);

        splitter->addWidget(gbImageViewer);
        fObjectDetectingTool = new QFrame(splitter);
        fObjectDetectingTool->setObjectName(QString::fromUtf8("fObjectDetectingTool"));
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy8.setHorizontalStretch(0);
        sizePolicy8.setVerticalStretch(30);
        sizePolicy8.setHeightForWidth(fObjectDetectingTool->sizePolicy().hasHeightForWidth());
        fObjectDetectingTool->setSizePolicy(sizePolicy8);
        fObjectDetectingTool->setMinimumSize(QSize(0, 0));
        fObjectDetectingTool->setFrameShape(QFrame::StyledPanel);
        fObjectDetectingTool->setFrameShadow(QFrame::Raised);
        verticalLayout_32 = new QVBoxLayout(fObjectDetectingTool);
        verticalLayout_32->setSpacing(6);
        verticalLayout_32->setContentsMargins(11, 11, 11, 11);
        verticalLayout_32->setObjectName(QString::fromUtf8("verticalLayout_32"));
        verticalLayout_32->setContentsMargins(0, 0, 0, 0);
        gbImageProvider = new QGroupBox(fObjectDetectingTool);
        gbImageProvider->setObjectName(QString::fromUtf8("gbImageProvider"));
        gbImageProvider->setEnabled(true);
        gbImageProvider->setFont(font6);
        gbImageProvider->setCheckable(true);
        verticalLayout_39 = new QVBoxLayout(gbImageProvider);
        verticalLayout_39->setSpacing(7);
        verticalLayout_39->setContentsMargins(11, 11, 11, 11);
        verticalLayout_39->setObjectName(QString::fromUtf8("verticalLayout_39"));
        verticalLayout_39->setContentsMargins(-1, 10, -1, 11);
        fImageProvider = new QFrame(gbImageProvider);
        fImageProvider->setObjectName(QString::fromUtf8("fImageProvider"));
        fImageProvider->setMinimumSize(QSize(0, 100));
        fImageProvider->setFrameShape(QFrame::StyledPanel);
        fImageProvider->setFrameShadow(QFrame::Raised);
        verticalLayout_51 = new QVBoxLayout(fImageProvider);
        verticalLayout_51->setSpacing(5);
        verticalLayout_51->setContentsMargins(11, 11, 11, 11);
        verticalLayout_51->setObjectName(QString::fromUtf8("verticalLayout_51"));
        verticalLayout_51->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_176 = new QLabel(fImageProvider);
        label_176->setObjectName(QString::fromUtf8("label_176"));

        horizontalLayout_10->addWidget(label_176);

        cbSourceForImageProvider = new QComboBox(fImageProvider);
        cbSourceForImageProvider->addItem(QString());
        cbSourceForImageProvider->addItem(QString());
        cbSourceForImageProvider->addItem(QString());
        cbSourceForImageProvider->addItem(QString());
        cbSourceForImageProvider->setObjectName(QString::fromUtf8("cbSourceForImageProvider"));
        cbSourceForImageProvider->setMinimumSize(QSize(200, 0));

        horizontalLayout_10->addWidget(cbSourceForImageProvider);

        horizontalSpacer_44 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_44);

        label_6 = new QLabel(fImageProvider);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_10->addWidget(label_6);

        cbEncoderForCamera = new QComboBox(fImageProvider);
        cbEncoderForCamera->addItem(QString());
        cbEncoderForCamera->addItem(QString());
        cbEncoderForCamera->addItem(QString());
        cbEncoderForCamera->addItem(QString());
        cbEncoderForCamera->setObjectName(QString::fromUtf8("cbEncoderForCamera"));

        horizontalLayout_10->addWidget(cbEncoderForCamera);


        verticalLayout_51->addLayout(horizontalLayout_10);

        fWebcamSource = new QFrame(fImageProvider);
        fWebcamSource->setObjectName(QString::fromUtf8("fWebcamSource"));
        fWebcamSource->setMinimumSize(QSize(0, 20));
        fWebcamSource->setMaximumSize(QSize(16777215, 50));
        fWebcamSource->setStyleSheet(QString::fromUtf8("QFrame#fWebcamSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}"));
        fWebcamSource->setFrameShape(QFrame::StyledPanel);
        fWebcamSource->setFrameShadow(QFrame::Raised);
        horizontalLayout_11 = new QHBoxLayout(fWebcamSource);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(5, 5, 5, 5);
        pbLoadCamera = new QToolButton(fWebcamSource);
        pbLoadCamera->setObjectName(QString::fromUtf8("pbLoadCamera"));
        sizePolicy.setHeightForWidth(pbLoadCamera->sizePolicy().hasHeightForWidth());
        pbLoadCamera->setSizePolicy(sizePolicy);
        pbLoadCamera->setMinimumSize(QSize(0, 0));
        QFont font7;
        font7.setPointSize(8);
        font7.setBold(false);
        font7.setWeight(50);
        pbLoadCamera->setFont(font7);
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/icon/webcam.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLoadCamera->setIcon(icon20);
        pbLoadCamera->setIconSize(QSize(30, 30));
        pbLoadCamera->setCheckable(true);
        pbLoadCamera->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbLoadCamera->setAutoRaise(true);

        horizontalLayout_11->addWidget(pbLoadCamera);

        horizontalSpacer_45 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_45);


        verticalLayout_51->addWidget(fWebcamSource);

        fImageSource = new QFrame(fImageProvider);
        fImageSource->setObjectName(QString::fromUtf8("fImageSource"));
        fImageSource->setMinimumSize(QSize(0, 20));
        fImageSource->setMaximumSize(QSize(16777215, 50));
        fImageSource->setStyleSheet(QString::fromUtf8("QFrame#fImageSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}"));
        fImageSource->setFrameShape(QFrame::StyledPanel);
        fImageSource->setFrameShadow(QFrame::Raised);
        horizontalLayout_27 = new QHBoxLayout(fImageSource);
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        horizontalLayout_27->setContentsMargins(5, 5, 5, 5);
        pbLoadTestImage = new QToolButton(fImageSource);
        pbLoadTestImage->setObjectName(QString::fromUtf8("pbLoadTestImage"));
        sizePolicy.setHeightForWidth(pbLoadTestImage->sizePolicy().hasHeightForWidth());
        pbLoadTestImage->setSizePolicy(sizePolicy);
        pbLoadTestImage->setMinimumSize(QSize(0, 0));
        pbLoadTestImage->setMaximumSize(QSize(120, 16777215));
        QFont font8;
        font8.setPointSize(8);
        pbLoadTestImage->setFont(font8);
        QIcon icon21;
        icon21.addFile(QString::fromUtf8(":/icon/icons8_image_30px_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLoadTestImage->setIcon(icon21);
        pbLoadTestImage->setIconSize(QSize(30, 30));
        pbLoadTestImage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbLoadTestImage->setAutoRaise(true);

        horizontalLayout_27->addWidget(pbLoadTestImage);

        horizontalSpacer_64 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_64);


        verticalLayout_51->addWidget(fImageSource);

        fCameraPara = new QFrame(fImageProvider);
        fCameraPara->setObjectName(QString::fromUtf8("fCameraPara"));
        fCameraPara->setMinimumSize(QSize(0, 20));
        fCameraPara->setMaximumSize(QSize(16777215, 50));
        fCameraPara->setStyleSheet(QString::fromUtf8("QFrame#fPluginSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}"));
        fCameraPara->setFrameShape(QFrame::StyledPanel);
        fCameraPara->setFrameShadow(QFrame::Raised);
        horizontalLayout_28 = new QHBoxLayout(fCameraPara);
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(5, 5, 5, 5);
        label_178 = new QLabel(fCameraPara);
        label_178->setObjectName(QString::fromUtf8("label_178"));
        label_178->setFont(font8);
        label_178->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_28->addWidget(label_178);

        leImageWidth = new QLineEdit(fCameraPara);
        leImageWidth->setObjectName(QString::fromUtf8("leImageWidth"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(leImageWidth->sizePolicy().hasHeightForWidth());
        leImageWidth->setSizePolicy(sizePolicy9);
        leImageWidth->setMinimumSize(QSize(0, 10));
        leImageWidth->setMaximumSize(QSize(40, 25));
        leImageWidth->setFont(font8);
        leImageWidth->setAlignment(Qt::AlignCenter);

        horizontalLayout_28->addWidget(leImageWidth);

        label_179 = new QLabel(fCameraPara);
        label_179->setObjectName(QString::fromUtf8("label_179"));
        label_179->setFont(font8);
        label_179->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_28->addWidget(label_179);

        leImageHeight = new QLineEdit(fCameraPara);
        leImageHeight->setObjectName(QString::fromUtf8("leImageHeight"));
        sizePolicy9.setHeightForWidth(leImageHeight->sizePolicy().hasHeightForWidth());
        leImageHeight->setSizePolicy(sizePolicy9);
        leImageHeight->setMinimumSize(QSize(0, 10));
        leImageHeight->setMaximumSize(QSize(40, 25));
        leImageHeight->setFont(font8);
        leImageHeight->setAlignment(Qt::AlignCenter);

        horizontalLayout_28->addWidget(leImageHeight);

        label_73 = new QLabel(fCameraPara);
        label_73->setObjectName(QString::fromUtf8("label_73"));
        label_73->setMaximumSize(QSize(50, 16777215));
        label_73->setFont(font8);

        horizontalLayout_28->addWidget(label_73);

        leCaptureInterval = new QLineEdit(fCameraPara);
        leCaptureInterval->setObjectName(QString::fromUtf8("leCaptureInterval"));
        sizePolicy9.setHeightForWidth(leCaptureInterval->sizePolicy().hasHeightForWidth());
        leCaptureInterval->setSizePolicy(sizePolicy9);
        leCaptureInterval->setMinimumSize(QSize(0, 10));
        leCaptureInterval->setMaximumSize(QSize(40, 25));
        leCaptureInterval->setFont(font8);
        leCaptureInterval->setAlignment(Qt::AlignCenter);

        horizontalLayout_28->addWidget(leCaptureInterval);

        label_128 = new QLabel(fCameraPara);
        label_128->setObjectName(QString::fromUtf8("label_128"));
        label_128->setMaximumSize(QSize(50, 16777215));
        label_128->setFont(font8);

        horizontalLayout_28->addWidget(label_128);

        pbStartAcquisition = new QToolButton(fCameraPara);
        pbStartAcquisition->setObjectName(QString::fromUtf8("pbStartAcquisition"));
        pbStartAcquisition->setEnabled(true);
        sizePolicy.setHeightForWidth(pbStartAcquisition->sizePolicy().hasHeightForWidth());
        pbStartAcquisition->setSizePolicy(sizePolicy);
        pbStartAcquisition->setMinimumSize(QSize(0, 0));
        pbStartAcquisition->setFont(font8);
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/icon/icons8-play-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon22.addFile(QString::fromUtf8(":/icon/icons8-pause-48.png"), QSize(), QIcon::Normal, QIcon::On);
        icon22.addFile(QString::fromUtf8("icon/icons8-play-48.png"), QSize(), QIcon::Selected, QIcon::Off);
        pbStartAcquisition->setIcon(icon22);
        pbStartAcquisition->setIconSize(QSize(30, 30));
        pbStartAcquisition->setCheckable(true);
        pbStartAcquisition->setChecked(false);
        pbStartAcquisition->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbStartAcquisition->setAutoRaise(true);

        horizontalLayout_28->addWidget(pbStartAcquisition);

        pbCapture = new QToolButton(fCameraPara);
        pbCapture->setObjectName(QString::fromUtf8("pbCapture"));
        pbCapture->setEnabled(true);
        pbCapture->setMinimumSize(QSize(0, 0));
        pbCapture->setFont(font8);
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/icon/icons8-screenshot-40.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCapture->setIcon(icon23);
        pbCapture->setIconSize(QSize(30, 30));
        pbCapture->setCheckable(false);
        pbCapture->setChecked(false);
        pbCapture->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbCapture->setAutoRaise(true);

        horizontalLayout_28->addWidget(pbCapture);

        lbCameraState = new QLabel(fCameraPara);
        lbCameraState->setObjectName(QString::fromUtf8("lbCameraState"));
        lbCameraState->setEnabled(true);
        lbCameraState->setMaximumSize(QSize(20, 20));
        lbCameraState->setPixmap(QPixmap(QString::fromUtf8("icon/icons8-connection-status-on-48.png")));
        lbCameraState->setScaledContents(true);

        horizontalLayout_28->addWidget(lbCameraState);

        horizontalSpacer_65 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_65);


        verticalLayout_51->addWidget(fCameraPara);


        verticalLayout_39->addWidget(fImageProvider);


        verticalLayout_32->addWidget(gbImageProvider);

        gbCameraCalibration = new QGroupBox(fObjectDetectingTool);
        gbCameraCalibration->setObjectName(QString::fromUtf8("gbCameraCalibration"));
        gbCameraCalibration->setFont(font6);
        gbCameraCalibration->setCheckable(true);
        gbCameraCalibration->setChecked(true);
        verticalLayout_29 = new QVBoxLayout(gbCameraCalibration);
        verticalLayout_29->setSpacing(6);
        verticalLayout_29->setContentsMargins(11, 11, 11, 11);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        fCameraCalibrationFrame = new QFrame(gbCameraCalibration);
        fCameraCalibrationFrame->setObjectName(QString::fromUtf8("fCameraCalibrationFrame"));
        fCameraCalibrationFrame->setMinimumSize(QSize(0, 200));
        fCameraCalibrationFrame->setFrameShape(QFrame::StyledPanel);
        fCameraCalibrationFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_52 = new QVBoxLayout(fCameraCalibrationFrame);
        verticalLayout_52->setSpacing(6);
        verticalLayout_52->setContentsMargins(11, 11, 11, 11);
        verticalLayout_52->setObjectName(QString::fromUtf8("verticalLayout_52"));
        pbCalibStep1 = new QPushButton(fCameraCalibrationFrame);
        pbCalibStep1->setObjectName(QString::fromUtf8("pbCalibStep1"));
        pbCalibStep1->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	height: 25px;\n"
"	text-align: left;\n"
"	padding-left: 50px;\n"
"}"));
        pbCalibStep1->setCheckable(true);
        pbCalibStep1->setChecked(true);

        verticalLayout_52->addWidget(pbCalibStep1);

        fCalibStep1 = new QFrame(fCameraCalibrationFrame);
        fCalibStep1->setObjectName(QString::fromUtf8("fCalibStep1"));
        gridLayout_27 = new QGridLayout(fCalibStep1);
        gridLayout_27->setSpacing(6);
        gridLayout_27->setContentsMargins(11, 11, 11, 11);
        gridLayout_27->setObjectName(QString::fromUtf8("gridLayout_27"));
        label_109 = new QLabel(fCalibStep1);
        label_109->setObjectName(QString::fromUtf8("label_109"));
        label_109->setMinimumSize(QSize(0, 25));

        gridLayout_27->addWidget(label_109, 0, 0, 1, 2);

        label_110 = new QLabel(fCalibStep1);
        label_110->setObjectName(QString::fromUtf8("label_110"));
        label_110->setMinimumSize(QSize(0, 25));

        gridLayout_27->addWidget(label_110, 1, 0, 1, 1);


        verticalLayout_52->addWidget(fCalibStep1);

        pbCalibStep2 = new QPushButton(fCameraCalibrationFrame);
        pbCalibStep2->setObjectName(QString::fromUtf8("pbCalibStep2"));
        pbCalibStep2->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	height: 25px;\n"
"	text-align: left;\n"
"	padding-left: 50px;\n"
"}"));
        pbCalibStep2->setCheckable(true);
        pbCalibStep2->setChecked(true);

        verticalLayout_52->addWidget(pbCalibStep2);

        fCalibStep2 = new QFrame(fCameraCalibrationFrame);
        fCalibStep2->setObjectName(QString::fromUtf8("fCalibStep2"));
        gridLayout_26 = new QGridLayout(fCalibStep2);
        gridLayout_26->setSpacing(6);
        gridLayout_26->setContentsMargins(11, 11, 11, 11);
        gridLayout_26->setObjectName(QString::fromUtf8("gridLayout_26"));
        leRealityPoint2X = new QLineEdit(fCalibStep2);
        leRealityPoint2X->setObjectName(QString::fromUtf8("leRealityPoint2X"));
        sizePolicy.setHeightForWidth(leRealityPoint2X->sizePolicy().hasHeightForWidth());
        leRealityPoint2X->setSizePolicy(sizePolicy);
        leRealityPoint2X->setMinimumSize(QSize(0, 0));
        leRealityPoint2X->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint2X, 5, 2, 1, 1);

        leRealityPoint1Y = new QLineEdit(fCalibStep2);
        leRealityPoint1Y->setObjectName(QString::fromUtf8("leRealityPoint1Y"));
        sizePolicy.setHeightForWidth(leRealityPoint1Y->sizePolicy().hasHeightForWidth());
        leRealityPoint1Y->setSizePolicy(sizePolicy);
        leRealityPoint1Y->setMinimumSize(QSize(0, 0));
        leRealityPoint1Y->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint1Y, 4, 4, 1, 1);

        pbCalibPoint1 = new QPushButton(fCalibStep2);
        pbCalibPoint1->setObjectName(QString::fromUtf8("pbCalibPoint1"));
        pbCalibPoint1->setFlat(true);

        gridLayout_26->addWidget(pbCalibPoint1, 4, 1, 1, 1);

        label_140 = new QLabel(fCalibStep2);
        label_140->setObjectName(QString::fromUtf8("label_140"));
        label_140->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_140, 5, 5, 1, 1);

        pbImageMapping = new QPushButton(fCalibStep2);
        pbImageMapping->setObjectName(QString::fromUtf8("pbImageMapping"));
        pbImageMapping->setMinimumSize(QSize(0, 45));
        pbImageMapping->setMaximumSize(QSize(200, 16777215));
        pbImageMapping->setAutoFillBackground(false);
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/icon/icons8_grid_3_48px_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbImageMapping->setIcon(icon24);
        pbImageMapping->setIconSize(QSize(30, 30));
        pbImageMapping->setCheckable(true);
        pbImageMapping->setChecked(false);
        pbImageMapping->setAutoDefault(false);
        pbImageMapping->setFlat(false);

        gridLayout_26->addWidget(pbImageMapping, 6, 0, 1, 3);

        leRealityPoint2Y = new QLineEdit(fCalibStep2);
        leRealityPoint2Y->setObjectName(QString::fromUtf8("leRealityPoint2Y"));
        sizePolicy.setHeightForWidth(leRealityPoint2Y->sizePolicy().hasHeightForWidth());
        leRealityPoint2Y->setSizePolicy(sizePolicy);
        leRealityPoint2Y->setMinimumSize(QSize(0, 0));
        leRealityPoint2Y->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint2Y, 5, 4, 1, 1);

        leRealityPoint1X = new QLineEdit(fCalibStep2);
        leRealityPoint1X->setObjectName(QString::fromUtf8("leRealityPoint1X"));
        sizePolicy.setHeightForWidth(leRealityPoint1X->sizePolicy().hasHeightForWidth());
        leRealityPoint1X->setSizePolicy(sizePolicy);
        leRealityPoint1X->setMinimumSize(QSize(0, 0));
        leRealityPoint1X->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint1X, 4, 2, 1, 1);

        label_133 = new QLabel(fCalibStep2);
        label_133->setObjectName(QString::fromUtf8("label_133"));
        label_133->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_133, 4, 5, 1, 1);

        label_139 = new QLabel(fCalibStep2);
        label_139->setObjectName(QString::fromUtf8("label_139"));
        label_139->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_139, 5, 3, 1, 1);

        label_39 = new QLabel(fCalibStep2);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setAlignment(Qt::AlignCenter);

        gridLayout_26->addWidget(label_39, 3, 4, 1, 1);

        label_132 = new QLabel(fCalibStep2);
        label_132->setObjectName(QString::fromUtf8("label_132"));
        label_132->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_132, 4, 3, 1, 1);

        label_38 = new QLabel(fCalibStep2);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setMinimumSize(QSize(0, 0));
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
        label_38->setAlignment(Qt::AlignCenter);

        gridLayout_26->addWidget(label_38, 3, 2, 1, 1);

        pbCalibPoint2 = new QPushButton(fCalibStep2);
        pbCalibPoint2->setObjectName(QString::fromUtf8("pbCalibPoint2"));
        pbCalibPoint2->setFlat(true);

        gridLayout_26->addWidget(pbCalibPoint2, 5, 1, 1, 1);


        verticalLayout_52->addWidget(fCalibStep2);


        verticalLayout_29->addWidget(fCameraCalibrationFrame);


        verticalLayout_32->addWidget(gbCameraCalibration);

        gbCameraObject = new QGroupBox(fObjectDetectingTool);
        gbCameraObject->setObjectName(QString::fromUtf8("gbCameraObject"));
        gbCameraObject->setFont(font6);
        gbCameraObject->setCheckable(true);
        verticalLayout_40 = new QVBoxLayout(gbCameraObject);
        verticalLayout_40->setSpacing(6);
        verticalLayout_40->setContentsMargins(11, 11, 11, 11);
        verticalLayout_40->setObjectName(QString::fromUtf8("verticalLayout_40"));
        verticalLayout_40->setContentsMargins(-1, 10, -1, -1);
        fVisionObjectFrame = new QFrame(gbCameraObject);
        fVisionObjectFrame->setObjectName(QString::fromUtf8("fVisionObjectFrame"));
        fVisionObjectFrame->setMinimumSize(QSize(0, 0));
        verticalLayout_31 = new QVBoxLayout(fVisionObjectFrame);
        verticalLayout_31->setSpacing(6);
        verticalLayout_31->setContentsMargins(11, 11, 11, 11);
        verticalLayout_31->setObjectName(QString::fromUtf8("verticalLayout_31"));
        verticalLayout_31->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        horizontalSpacer_43 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_29->addItem(horizontalSpacer_43);


        verticalLayout_31->addLayout(horizontalLayout_29);

        frame_13 = new QFrame(fVisionObjectFrame);
        frame_13->setObjectName(QString::fromUtf8("frame_13"));
        frame_13->setMinimumSize(QSize(0, 0));
        frame_13->setFrameShape(QFrame::StyledPanel);
        frame_13->setFrameShadow(QFrame::Raised);
        horizontalLayout_26 = new QHBoxLayout(frame_13);
        horizontalLayout_26->setSpacing(10);
        horizontalLayout_26->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        horizontalLayout_26->setContentsMargins(0, 0, 0, 0);
        label_126 = new QLabel(frame_13);
        label_126->setObjectName(QString::fromUtf8("label_126"));

        horizontalLayout_26->addWidget(label_126);

        cbDetectingAlgorithm = new QComboBox(frame_13);
        cbDetectingAlgorithm->addItem(QString());
        cbDetectingAlgorithm->addItem(QString());
        cbDetectingAlgorithm->addItem(QString());
        cbDetectingAlgorithm->setObjectName(QString::fromUtf8("cbDetectingAlgorithm"));

        horizontalLayout_26->addWidget(cbDetectingAlgorithm);

        horizontalSpacer_6 = new QSpacerItem(239, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_26->addItem(horizontalSpacer_6);

        label_45 = new QLabel(frame_13);
        label_45->setObjectName(QString::fromUtf8("label_45"));

        horizontalLayout_26->addWidget(label_45);

        leObjectOverlay = new QLineEdit(frame_13);
        leObjectOverlay->setObjectName(QString::fromUtf8("leObjectOverlay"));
        QSizePolicy sizePolicy10(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(leObjectOverlay->sizePolicy().hasHeightForWidth());
        leObjectOverlay->setSizePolicy(sizePolicy10);
        leObjectOverlay->setMinimumSize(QSize(0, 30));
        leObjectOverlay->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_26->addWidget(leObjectOverlay);


        verticalLayout_31->addWidget(frame_13);

        fBlobPanel = new QFrame(fVisionObjectFrame);
        fBlobPanel->setObjectName(QString::fromUtf8("fBlobPanel"));
        fBlobPanel->setMinimumSize(QSize(0, 0));
        fBlobPanel->setStyleSheet(QString::fromUtf8("QFrame#fBlobPanel\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}"));
        fBlobPanel->setFrameShape(QFrame::StyledPanel);
        fBlobPanel->setFrameShadow(QFrame::Raised);
        gridLayout_14 = new QGridLayout(fBlobPanel);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        leMaxWRec = new QLineEdit(fBlobPanel);
        leMaxWRec->setObjectName(QString::fromUtf8("leMaxWRec"));
        sizePolicy10.setHeightForWidth(leMaxWRec->sizePolicy().hasHeightForWidth());
        leMaxWRec->setSizePolicy(sizePolicy10);
        leMaxWRec->setMinimumSize(QSize(0, 20));
        leMaxWRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMaxWRec, 3, 8, 1, 1);

        label_172 = new QLabel(fBlobPanel);
        label_172->setObjectName(QString::fromUtf8("label_172"));
        label_172->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_172, 3, 5, 1, 1);

        leMinLRec = new QLineEdit(fBlobPanel);
        leMinLRec->setObjectName(QString::fromUtf8("leMinLRec"));
        sizePolicy10.setHeightForWidth(leMinLRec->sizePolicy().hasHeightForWidth());
        leMinLRec->setSizePolicy(sizePolicy10);
        leMinLRec->setMinimumSize(QSize(0, 20));
        leMinLRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMinLRec, 4, 6, 1, 1);

        leMaxLRec = new QLineEdit(fBlobPanel);
        leMaxLRec->setObjectName(QString::fromUtf8("leMaxLRec"));
        sizePolicy10.setHeightForWidth(leMaxLRec->sizePolicy().hasHeightForWidth());
        leMaxLRec->setSizePolicy(sizePolicy10);
        leMaxLRec->setMinimumSize(QSize(0, 20));
        leMaxLRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMaxLRec, 4, 8, 1, 1);

        leWRec = new QLineEdit(fBlobPanel);
        leWRec->setObjectName(QString::fromUtf8("leWRec"));
        sizePolicy10.setHeightForWidth(leWRec->sizePolicy().hasHeightForWidth());
        leWRec->setSizePolicy(sizePolicy10);
        leWRec->setMinimumSize(QSize(0, 30));
        leWRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leWRec, 3, 2, 1, 1);

        label_173 = new QLabel(fBlobPanel);
        label_173->setObjectName(QString::fromUtf8("label_173"));
        label_173->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_173, 3, 7, 1, 1);

        leLRec = new QLineEdit(fBlobPanel);
        leLRec->setObjectName(QString::fromUtf8("leLRec"));
        sizePolicy10.setHeightForWidth(leLRec->sizePolicy().hasHeightForWidth());
        leLRec->setSizePolicy(sizePolicy10);
        leLRec->setMinimumSize(QSize(0, 30));
        leLRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leLRec, 4, 2, 1, 1);

        label_175 = new QLabel(fBlobPanel);
        label_175->setObjectName(QString::fromUtf8("label_175"));
        label_175->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_175, 4, 7, 1, 1);

        label_43 = new QLabel(fBlobPanel);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        gridLayout_14->addWidget(label_43, 4, 1, 1, 1);

        label_163 = new QLabel(fBlobPanel);
        label_163->setObjectName(QString::fromUtf8("label_163"));

        gridLayout_14->addWidget(label_163, 0, 1, 1, 1);

        label_54 = new QLabel(fBlobPanel);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        gridLayout_14->addWidget(label_54, 3, 3, 1, 1);

        leMinWRec = new QLineEdit(fBlobPanel);
        leMinWRec->setObjectName(QString::fromUtf8("leMinWRec"));
        sizePolicy10.setHeightForWidth(leMinWRec->sizePolicy().hasHeightForWidth());
        leMinWRec->setSizePolicy(sizePolicy10);
        leMinWRec->setMinimumSize(QSize(0, 20));
        leMinWRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMinWRec, 3, 6, 1, 1);

        label_55 = new QLabel(fBlobPanel);
        label_55->setObjectName(QString::fromUtf8("label_55"));

        gridLayout_14->addWidget(label_55, 4, 3, 1, 1);

        cbObjectType = new QComboBox(fBlobPanel);
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->addItem(QString());
        cbObjectType->setObjectName(QString::fromUtf8("cbObjectType"));
        cbObjectType->setEnabled(true);
        cbObjectType->setMinimumSize(QSize(0, 30));

        gridLayout_14->addWidget(cbObjectType, 0, 2, 1, 1);

        label_42 = new QLabel(fBlobPanel);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_14->addWidget(label_42, 3, 1, 1, 1);

        horizontalSpacer_66 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_66, 3, 9, 1, 1);

        label_174 = new QLabel(fBlobPanel);
        label_174->setObjectName(QString::fromUtf8("label_174"));
        label_174->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_174, 4, 5, 1, 1);


        verticalLayout_31->addWidget(fBlobPanel);

        fExternalScriptPanel = new QFrame(fVisionObjectFrame);
        fExternalScriptPanel->setObjectName(QString::fromUtf8("fExternalScriptPanel"));
        fExternalScriptPanel->setMinimumSize(QSize(0, 50));
        fExternalScriptPanel->setStyleSheet(QString::fromUtf8("QFrame#fExternalScriptPanel\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}"));
        fExternalScriptPanel->setFrameShape(QFrame::StyledPanel);
        fExternalScriptPanel->setFrameShadow(QFrame::Raised);
        gridLayout_28 = new QGridLayout(fExternalScriptPanel);
        gridLayout_28->setSpacing(6);
        gridLayout_28->setContentsMargins(11, 11, 11, 11);
        gridLayout_28->setObjectName(QString::fromUtf8("gridLayout_28"));
        pbRunExternalScript = new QPushButton(fExternalScriptPanel);
        pbRunExternalScript->setObjectName(QString::fromUtf8("pbRunExternalScript"));
        sizePolicy10.setHeightForWidth(pbRunExternalScript->sizePolicy().hasHeightForWidth());
        pbRunExternalScript->setSizePolicy(sizePolicy10);
        pbRunExternalScript->setMaximumSize(QSize(30, 16777215));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/icon/icons8_play_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon25.addFile(QString::fromUtf8(":/icon/Pause_96px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbRunExternalScript->setIcon(icon25);
        pbRunExternalScript->setCheckable(true);

        gridLayout_28->addWidget(pbRunExternalScript, 0, 3, 1, 1);

        cbImageSource = new QComboBox(fExternalScriptPanel);
        cbImageSource->addItem(QString());
        cbImageSource->addItem(QString());
        cbImageSource->addItem(QString());
        cbImageSource->setObjectName(QString::fromUtf8("cbImageSource"));

        gridLayout_28->addWidget(cbImageSource, 1, 1, 1, 1);

        label_180 = new QLabel(fExternalScriptPanel);
        label_180->setObjectName(QString::fromUtf8("label_180"));

        gridLayout_28->addWidget(label_180, 2, 0, 1, 1);

        label_183 = new QLabel(fExternalScriptPanel);
        label_183->setObjectName(QString::fromUtf8("label_183"));

        gridLayout_28->addWidget(label_183, 2, 3, 1, 2);

        label_187 = new QLabel(fExternalScriptPanel);
        label_187->setObjectName(QString::fromUtf8("label_187"));

        gridLayout_28->addWidget(label_187, 4, 1, 1, 3);

        label_185 = new QLabel(fExternalScriptPanel);
        label_185->setObjectName(QString::fromUtf8("label_185"));

        gridLayout_28->addWidget(label_185, 4, 0, 1, 1);

        label_146 = new QLabel(fExternalScriptPanel);
        label_146->setObjectName(QString::fromUtf8("label_146"));

        gridLayout_28->addWidget(label_146, 1, 0, 1, 1);

        pbExternalScriptOpen = new QPushButton(fExternalScriptPanel);
        pbExternalScriptOpen->setObjectName(QString::fromUtf8("pbExternalScriptOpen"));
        sizePolicy10.setHeightForWidth(pbExternalScriptOpen->sizePolicy().hasHeightForWidth());
        pbExternalScriptOpen->setSizePolicy(sizePolicy10);
        pbExternalScriptOpen->setMaximumSize(QSize(30, 16777215));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/icon/icons8_folder_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbExternalScriptOpen->setIcon(icon26);

        gridLayout_28->addWidget(pbExternalScriptOpen, 0, 2, 1, 1);

        label_184 = new QLabel(fExternalScriptPanel);
        label_184->setObjectName(QString::fromUtf8("label_184"));

        gridLayout_28->addWidget(label_184, 3, 0, 1, 1);

        label_145 = new QLabel(fExternalScriptPanel);
        label_145->setObjectName(QString::fromUtf8("label_145"));

        gridLayout_28->addWidget(label_145, 0, 0, 1, 1);

        pbExternalScriptHelp = new QPushButton(fExternalScriptPanel);
        pbExternalScriptHelp->setObjectName(QString::fromUtf8("pbExternalScriptHelp"));
        sizePolicy10.setHeightForWidth(pbExternalScriptHelp->sizePolicy().hasHeightForWidth());
        pbExternalScriptHelp->setSizePolicy(sizePolicy10);
        pbExternalScriptHelp->setMaximumSize(QSize(30, 16777215));

        gridLayout_28->addWidget(pbExternalScriptHelp, 0, 4, 1, 1);

        label_186 = new QLabel(fExternalScriptPanel);
        label_186->setObjectName(QString::fromUtf8("label_186"));

        gridLayout_28->addWidget(label_186, 3, 1, 1, 1);

        label_182 = new QLabel(fExternalScriptPanel);
        label_182->setObjectName(QString::fromUtf8("label_182"));

        gridLayout_28->addWidget(label_182, 2, 2, 1, 1);

        label_181 = new QLabel(fExternalScriptPanel);
        label_181->setObjectName(QString::fromUtf8("label_181"));

        gridLayout_28->addWidget(label_181, 2, 1, 1, 1);

        lePythonUrl = new QLineEdit(fExternalScriptPanel);
        lePythonUrl->setObjectName(QString::fromUtf8("lePythonUrl"));
        sizePolicy9.setHeightForWidth(lePythonUrl->sizePolicy().hasHeightForWidth());
        lePythonUrl->setSizePolicy(sizePolicy9);
        lePythonUrl->setMinimumSize(QSize(0, 30));
        lePythonUrl->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_28->addWidget(lePythonUrl, 0, 1, 1, 1);

        pbOpenScriptExample = new QPushButton(fExternalScriptPanel);
        pbOpenScriptExample->setObjectName(QString::fromUtf8("pbOpenScriptExample"));

        gridLayout_28->addWidget(pbOpenScriptExample, 5, 0, 1, 1);


        verticalLayout_31->addWidget(fExternalScriptPanel);

        fCirclePanel = new QFrame(fVisionObjectFrame);
        fCirclePanel->setObjectName(QString::fromUtf8("fCirclePanel"));
        fCirclePanel->setMinimumSize(QSize(0, 200));
        fCirclePanel->setMaximumSize(QSize(16777215, 16777215));
        fCirclePanel->setStyleSheet(QString::fromUtf8("QFrame#fCirclePanel\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}"));
        fCirclePanel->setFrameShape(QFrame::StyledPanel);
        fCirclePanel->setFrameShadow(QFrame::Raised);
        gridLayout_29 = new QGridLayout(fCirclePanel);
        gridLayout_29->setSpacing(6);
        gridLayout_29->setContentsMargins(11, 11, 11, 11);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        leCenterThreshold = new QLineEdit(fCirclePanel);
        leCenterThreshold->setObjectName(QString::fromUtf8("leCenterThreshold"));
        sizePolicy10.setHeightForWidth(leCenterThreshold->sizePolicy().hasHeightForWidth());
        leCenterThreshold->setSizePolicy(sizePolicy10);
        leCenterThreshold->setMinimumSize(QSize(0, 30));
        leCenterThreshold->setMaximumSize(QSize(50, 16777215));

        gridLayout_29->addWidget(leCenterThreshold, 3, 1, 1, 2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_29->addItem(horizontalSpacer_8, 2, 4, 1, 1);

        leEdgeThreshold = new QLineEdit(fCirclePanel);
        leEdgeThreshold->setObjectName(QString::fromUtf8("leEdgeThreshold"));
        sizePolicy10.setHeightForWidth(leEdgeThreshold->sizePolicy().hasHeightForWidth());
        leEdgeThreshold->setSizePolicy(sizePolicy10);
        leEdgeThreshold->setMinimumSize(QSize(0, 30));
        leEdgeThreshold->setMaximumSize(QSize(50, 16777215));

        gridLayout_29->addWidget(leEdgeThreshold, 2, 1, 1, 2);

        label_193 = new QLabel(fCirclePanel);
        label_193->setObjectName(QString::fromUtf8("label_193"));

        gridLayout_29->addWidget(label_193, 4, 3, 1, 1);

        label_190 = new QLabel(fCirclePanel);
        label_190->setObjectName(QString::fromUtf8("label_190"));

        gridLayout_29->addWidget(label_190, 3, 0, 1, 1);

        label_192 = new QLabel(fCirclePanel);
        label_192->setObjectName(QString::fromUtf8("label_192"));

        gridLayout_29->addWidget(label_192, 4, 0, 1, 1);

        leMaxRadius = new QLineEdit(fCirclePanel);
        leMaxRadius->setObjectName(QString::fromUtf8("leMaxRadius"));
        sizePolicy10.setHeightForWidth(leMaxRadius->sizePolicy().hasHeightForWidth());
        leMaxRadius->setSizePolicy(sizePolicy10);
        leMaxRadius->setMinimumSize(QSize(0, 30));
        leMaxRadius->setMaximumSize(QSize(50, 16777215));

        gridLayout_29->addWidget(leMaxRadius, 5, 1, 1, 1);

        label_194 = new QLabel(fCirclePanel);
        label_194->setObjectName(QString::fromUtf8("label_194"));

        gridLayout_29->addWidget(label_194, 5, 0, 1, 1);

        label_195 = new QLabel(fCirclePanel);
        label_195->setObjectName(QString::fromUtf8("label_195"));

        gridLayout_29->addWidget(label_195, 5, 3, 1, 1);

        leMinRadius = new QLineEdit(fCirclePanel);
        leMinRadius->setObjectName(QString::fromUtf8("leMinRadius"));
        sizePolicy10.setHeightForWidth(leMinRadius->sizePolicy().hasHeightForWidth());
        leMinRadius->setSizePolicy(sizePolicy10);
        leMinRadius->setMinimumSize(QSize(0, 30));
        leMinRadius->setMaximumSize(QSize(50, 16777215));

        gridLayout_29->addWidget(leMinRadius, 4, 1, 1, 1);

        label_188 = new QLabel(fCirclePanel);
        label_188->setObjectName(QString::fromUtf8("label_188"));

        gridLayout_29->addWidget(label_188, 2, 0, 1, 1);


        verticalLayout_31->addWidget(fCirclePanel);


        verticalLayout_40->addWidget(fVisionObjectFrame);

        gridLayout_33 = new QGridLayout();
        gridLayout_33->setSpacing(6);
        gridLayout_33->setObjectName(QString::fromUtf8("gridLayout_33"));
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        gridLayout_12->setContentsMargins(6, -1, -1, -1);

        gridLayout_33->addLayout(gridLayout_12, 1, 0, 2, 1);


        verticalLayout_40->addLayout(gridLayout_33);


        verticalLayout_32->addWidget(gbCameraObject);

        gbCameraVariable = new QGroupBox(fObjectDetectingTool);
        gbCameraVariable->setObjectName(QString::fromUtf8("gbCameraVariable"));
        gbCameraVariable->setFont(font6);
        gbCameraVariable->setStyleSheet(QString::fromUtf8(""));
        gbCameraVariable->setFlat(false);
        gbCameraVariable->setCheckable(true);
        verticalLayout_34 = new QVBoxLayout(gbCameraVariable);
        verticalLayout_34->setSpacing(6);
        verticalLayout_34->setContentsMargins(11, 11, 11, 11);
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        label_196 = new QLabel(gbCameraVariable);
        label_196->setObjectName(QString::fromUtf8("label_196"));

        horizontalLayout_31->addWidget(label_196);

        leDetectingObjectListName = new QLineEdit(gbCameraVariable);
        leDetectingObjectListName->setObjectName(QString::fromUtf8("leDetectingObjectListName"));

        horizontalLayout_31->addWidget(leDetectingObjectListName);

        horizontalSpacer_50 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_50);


        verticalLayout_34->addLayout(horizontalLayout_31);

        fVisionVariableFrame = new QFrame(gbCameraVariable);
        fVisionVariableFrame->setObjectName(QString::fromUtf8("fVisionVariableFrame"));
        fVisionVariableFrame->setMinimumSize(QSize(0, 0));
        fVisionVariableFrame->setFrameShape(QFrame::StyledPanel);
        fVisionVariableFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_35 = new QVBoxLayout(fVisionVariableFrame);
        verticalLayout_35->setSpacing(6);
        verticalLayout_35->setContentsMargins(11, 11, 11, 11);
        verticalLayout_35->setObjectName(QString::fromUtf8("verticalLayout_35"));
        verticalLayout_35->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        pbViewDataObjects = new QPushButton(fVisionVariableFrame);
        pbViewDataObjects->setObjectName(QString::fromUtf8("pbViewDataObjects"));
        pbViewDataObjects->setMinimumSize(QSize(150, 30));
        pbViewDataObjects->setMaximumSize(QSize(200, 16777215));
        pbViewDataObjects->setStyleSheet(QString::fromUtf8(""));
        pbViewDataObjects->setIcon(icon18);

        horizontalLayout_25->addWidget(pbViewDataObjects);

        pbClearDetectObjects = new QPushButton(fVisionVariableFrame);
        pbClearDetectObjects->setObjectName(QString::fromUtf8("pbClearDetectObjects"));
        pbClearDetectObjects->setMinimumSize(QSize(150, 30));
        pbClearDetectObjects->setMaximumSize(QSize(200, 16777215));
        pbClearDetectObjects->setIcon(icon19);

        horizontalLayout_25->addWidget(pbClearDetectObjects);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_9);


        verticalLayout_35->addLayout(horizontalLayout_25);

        gridLayout_15 = new QGridLayout();
        gridLayout_15->setSpacing(6);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        lbTrackingObjectNumber = new QLabel(fVisionVariableFrame);
        lbTrackingObjectNumber->setObjectName(QString::fromUtf8("lbTrackingObjectNumber"));
        lbTrackingObjectNumber->setFont(font5);

        gridLayout_15->addWidget(lbTrackingObjectNumber, 1, 1, 1, 1);

        label_155 = new QLabel(fVisionVariableFrame);
        label_155->setObjectName(QString::fromUtf8("label_155"));

        gridLayout_15->addWidget(label_155, 3, 3, 1, 1);

        label_56 = new QLabel(fVisionVariableFrame);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout_15->addWidget(label_56, 3, 1, 1, 1);

        label_50 = new QLabel(fVisionVariableFrame);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setFont(font5);

        gridLayout_15->addWidget(label_50, 2, 0, 1, 1);

        leLimitMinX = new QLineEdit(fVisionVariableFrame);
        leLimitMinX->setObjectName(QString::fromUtf8("leLimitMinX"));

        gridLayout_15->addWidget(leLimitMinX, 3, 2, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_7, 1, 3, 1, 1);

        label_44 = new QLabel(fVisionVariableFrame);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_15->addWidget(label_44, 3, 0, 1, 1);

        lbVisibleObjectNumber = new QLabel(fVisionVariableFrame);
        lbVisibleObjectNumber->setObjectName(QString::fromUtf8("lbVisibleObjectNumber"));
        lbVisibleObjectNumber->setFont(font5);

        gridLayout_15->addWidget(lbVisibleObjectNumber, 2, 1, 1, 1);

        label_48 = new QLabel(fVisionVariableFrame);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setFont(font5);

        gridLayout_15->addWidget(label_48, 1, 0, 1, 1);

        leLimitMaxX = new QLineEdit(fVisionVariableFrame);
        leLimitMaxX->setObjectName(QString::fromUtf8("leLimitMaxX"));

        gridLayout_15->addWidget(leLimitMaxX, 3, 4, 1, 1);

        label_156 = new QLabel(fVisionVariableFrame);
        label_156->setObjectName(QString::fromUtf8("label_156"));

        gridLayout_15->addWidget(label_156, 4, 1, 1, 1);

        label_157 = new QLabel(fVisionVariableFrame);
        label_157->setObjectName(QString::fromUtf8("label_157"));

        gridLayout_15->addWidget(label_157, 4, 3, 1, 1);

        leLimitMinY = new QLineEdit(fVisionVariableFrame);
        leLimitMinY->setObjectName(QString::fromUtf8("leLimitMinY"));

        gridLayout_15->addWidget(leLimitMinY, 4, 2, 1, 1);

        leLimitMaxY = new QLineEdit(fVisionVariableFrame);
        leLimitMaxY->setObjectName(QString::fromUtf8("leLimitMaxY"));

        gridLayout_15->addWidget(leLimitMaxY, 4, 4, 1, 1);


        verticalLayout_35->addLayout(gridLayout_15);


        verticalLayout_34->addWidget(fVisionVariableFrame);


        verticalLayout_32->addWidget(gbCameraVariable);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_32->addItem(verticalSpacer_11);

        splitter->addWidget(fObjectDetectingTool);

        verticalLayout_17->addWidget(splitter);

        saObjectDetecting->setWidget(wObjectDetecting);

        verticalLayout_25->addWidget(saObjectDetecting);

        twModule->addTab(tObjectDetecting, QString());
        tPointTool = new QWidget();
        tPointTool->setObjectName(QString::fromUtf8("tPointTool"));
        verticalLayout_14 = new QVBoxLayout(tPointTool);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        saObjectDetecting_2 = new QScrollArea(tPointTool);
        saObjectDetecting_2->setObjectName(QString::fromUtf8("saObjectDetecting_2"));
        saObjectDetecting_2->setLineWidth(1);
        saObjectDetecting_2->setWidgetResizable(true);
        wObjectDetecting_2 = new QWidget();
        wObjectDetecting_2->setObjectName(QString::fromUtf8("wObjectDetecting_2"));
        wObjectDetecting_2->setGeometry(QRect(0, 0, 471, 4000));
        wObjectDetecting_2->setMinimumSize(QSize(100, 4000));
        wObjectDetecting_2->setStyleSheet(QString::fromUtf8("QWidget#wObjectDetecting\n"
"{	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
""));
        verticalLayout_18 = new QVBoxLayout(wObjectDetecting_2);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        splitter_3 = new QSplitter(wObjectDetecting_2);
        splitter_3->setObjectName(QString::fromUtf8("splitter_3"));
        sizePolicy3.setHeightForWidth(splitter_3->sizePolicy().hasHeightForWidth());
        splitter_3->setSizePolicy(sizePolicy3);
        splitter_3->setStyleSheet(QString::fromUtf8("QSplitter::handle:vertical \n"
"{	\n"
"	background: rgb(37, 197, 255);\n"
"}"));
        splitter_3->setOrientation(Qt::Vertical);
        splitter_3->setHandleWidth(10);
        fObjectDetectingTool_2 = new QFrame(splitter_3);
        fObjectDetectingTool_2->setObjectName(QString::fromUtf8("fObjectDetectingTool_2"));
        sizePolicy8.setHeightForWidth(fObjectDetectingTool_2->sizePolicy().hasHeightForWidth());
        fObjectDetectingTool_2->setSizePolicy(sizePolicy8);
        fObjectDetectingTool_2->setMinimumSize(QSize(0, 0));
        fObjectDetectingTool_2->setFrameShape(QFrame::StyledPanel);
        fObjectDetectingTool_2->setFrameShadow(QFrame::Raised);
        verticalLayout_59 = new QVBoxLayout(fObjectDetectingTool_2);
        verticalLayout_59->setSpacing(6);
        verticalLayout_59->setContentsMargins(11, 11, 11, 11);
        verticalLayout_59->setObjectName(QString::fromUtf8("verticalLayout_59"));
        verticalLayout_59->setContentsMargins(0, 0, 0, 0);
        gbImageProvider_2 = new QGroupBox(fObjectDetectingTool_2);
        gbImageProvider_2->setObjectName(QString::fromUtf8("gbImageProvider_2"));
        gbImageProvider_2->setEnabled(true);
        gbImageProvider_2->setFont(font6);
        gbImageProvider_2->setCheckable(true);
        verticalLayout_60 = new QVBoxLayout(gbImageProvider_2);
        verticalLayout_60->setSpacing(7);
        verticalLayout_60->setContentsMargins(11, 11, 11, 11);
        verticalLayout_60->setObjectName(QString::fromUtf8("verticalLayout_60"));
        verticalLayout_60->setContentsMargins(-1, 10, -1, 11);
        frame_15 = new QFrame(gbImageProvider_2);
        frame_15->setObjectName(QString::fromUtf8("frame_15"));
        frame_15->setMinimumSize(QSize(0, 0));
        frame_15->setFrameShape(QFrame::StyledPanel);
        frame_15->setFrameShadow(QFrame::Raised);
        gridLayout_16 = new QGridLayout(frame_15);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        leDeviationAngle = new QLineEdit(frame_15);
        leDeviationAngle->setObjectName(QString::fromUtf8("leDeviationAngle"));

        gridLayout_16->addWidget(leDeviationAngle, 4, 2, 1, 1);

        label_164 = new QLabel(frame_15);
        label_164->setObjectName(QString::fromUtf8("label_164"));

        gridLayout_16->addWidget(label_164, 2, 0, 1, 1);

        cbTrackingEncoderSource = new QComboBox(frame_15);
        cbTrackingEncoderSource->addItem(QString());
        cbTrackingEncoderSource->addItem(QString());
        cbTrackingEncoderSource->addItem(QString());
        cbTrackingEncoderSource->setObjectName(QString::fromUtf8("cbTrackingEncoderSource"));
        sizePolicy.setHeightForWidth(cbTrackingEncoderSource->sizePolicy().hasHeightForWidth());
        cbTrackingEncoderSource->setSizePolicy(sizePolicy);
        cbTrackingEncoderSource->setMinimumSize(QSize(0, 0));

        gridLayout_16->addWidget(cbTrackingEncoderSource, 2, 2, 1, 1);

        label_144 = new QLabel(frame_15);
        label_144->setObjectName(QString::fromUtf8("label_144"));

        gridLayout_16->addWidget(label_144, 1, 0, 1, 1);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_16->addItem(horizontalSpacer_24, 1, 6, 1, 1);

        cbReverseEncoderValue = new QCheckBox(frame_15);
        cbReverseEncoderValue->setObjectName(QString::fromUtf8("cbReverseEncoderValue"));

        gridLayout_16->addWidget(cbReverseEncoderValue, 2, 6, 1, 1);

        label_167 = new QLabel(frame_15);
        label_167->setObjectName(QString::fromUtf8("label_167"));

        gridLayout_16->addWidget(label_167, 3, 0, 1, 1);

        cbSelectedTracking = new QComboBox(frame_15);
        cbSelectedTracking->addItem(QString());
        cbSelectedTracking->addItem(QString());
        cbSelectedTracking->addItem(QString());
        cbSelectedTracking->addItem(QString());
        cbSelectedTracking->setObjectName(QString::fromUtf8("cbSelectedTracking"));
        sizePolicy6.setHeightForWidth(cbSelectedTracking->sizePolicy().hasHeightForWidth());
        cbSelectedTracking->setSizePolicy(sizePolicy6);

        gridLayout_16->addWidget(cbSelectedTracking, 0, 2, 1, 1);

        cbTrackingDirection = new QComboBox(frame_15);
        cbTrackingDirection->addItem(QString());
        cbTrackingDirection->addItem(QString());
        cbTrackingDirection->setObjectName(QString::fromUtf8("cbTrackingDirection"));
        cbTrackingDirection->setMinimumSize(QSize(0, 0));

        gridLayout_16->addWidget(cbTrackingDirection, 3, 2, 1, 1);

        label_168 = new QLabel(frame_15);
        label_168->setObjectName(QString::fromUtf8("label_168"));

        gridLayout_16->addWidget(label_168, 4, 0, 1, 1);

        label_160 = new QLabel(frame_15);
        label_160->setObjectName(QString::fromUtf8("label_160"));

        gridLayout_16->addWidget(label_160, 0, 0, 1, 1);

        label_169 = new QLabel(frame_15);
        label_169->setObjectName(QString::fromUtf8("label_169"));

        gridLayout_16->addWidget(label_169, 4, 3, 1, 1);

        leSelectedTrackingObjectList = new QLineEdit(frame_15);
        leSelectedTrackingObjectList->setObjectName(QString::fromUtf8("leSelectedTrackingObjectList"));

        gridLayout_16->addWidget(leSelectedTrackingObjectList, 1, 2, 1, 1);


        verticalLayout_60->addWidget(frame_15);

        gbCameraCalibration_3 = new QGroupBox(gbImageProvider_2);
        gbCameraCalibration_3->setObjectName(QString::fromUtf8("gbCameraCalibration_3"));
        gbCameraCalibration_3->setFont(font6);
        gbCameraCalibration_3->setCheckable(true);
        gbCameraCalibration_3->setChecked(true);
        verticalLayout_63 = new QVBoxLayout(gbCameraCalibration_3);
        verticalLayout_63->setSpacing(6);
        verticalLayout_63->setContentsMargins(11, 11, 11, 11);
        verticalLayout_63->setObjectName(QString::fromUtf8("verticalLayout_63"));
        frame_19 = new QFrame(gbCameraCalibration_3);
        frame_19->setObjectName(QString::fromUtf8("frame_19"));
        frame_19->setMinimumSize(QSize(0, 0));
        frame_19->setFrameShape(QFrame::StyledPanel);
        frame_19->setFrameShadow(QFrame::Raised);
        gridLayout_44 = new QGridLayout(frame_19);
        gridLayout_44->setSpacing(6);
        gridLayout_44->setContentsMargins(11, 11, 11, 11);
        gridLayout_44->setObjectName(QString::fromUtf8("gridLayout_44"));
        leAnglePoint2X = new QLineEdit(frame_19);
        leAnglePoint2X->setObjectName(QString::fromUtf8("leAnglePoint2X"));

        gridLayout_44->addWidget(leAnglePoint2X, 3, 3, 1, 1);

        pbCalculateAngle = new QPushButton(frame_19);
        pbCalculateAngle->setObjectName(QString::fromUtf8("pbCalculateAngle"));

        gridLayout_44->addWidget(pbCalculateAngle, 4, 2, 1, 1);

        leAnglePoint1Y = new QLineEdit(frame_19);
        leAnglePoint1Y->setObjectName(QString::fromUtf8("leAnglePoint1Y"));

        gridLayout_44->addWidget(leAnglePoint1Y, 1, 5, 1, 1);

        leAnglePoint2Y = new QLineEdit(frame_19);
        leAnglePoint2Y->setObjectName(QString::fromUtf8("leAnglePoint2Y"));

        gridLayout_44->addWidget(leAnglePoint2Y, 3, 5, 1, 1);

        label_189 = new QLabel(frame_19);
        label_189->setObjectName(QString::fromUtf8("label_189"));
        label_189->setAlignment(Qt::AlignCenter);

        gridLayout_44->addWidget(label_189, 0, 3, 1, 1);

        label_206 = new QLabel(frame_19);
        label_206->setObjectName(QString::fromUtf8("label_206"));
        label_206->setAlignment(Qt::AlignCenter);

        gridLayout_44->addWidget(label_206, 0, 5, 1, 1);

        leAngleResult = new QLineEdit(frame_19);
        leAngleResult->setObjectName(QString::fromUtf8("leAngleResult"));

        gridLayout_44->addWidget(leAngleResult, 5, 3, 1, 1);

        leAnglePoint1X = new QLineEdit(frame_19);
        leAnglePoint1X->setObjectName(QString::fromUtf8("leAnglePoint1X"));

        gridLayout_44->addWidget(leAnglePoint1X, 1, 3, 1, 1);

        label_224 = new QLabel(frame_19);
        label_224->setObjectName(QString::fromUtf8("label_224"));

        gridLayout_44->addWidget(label_224, 5, 2, 1, 1);

        pbAnglePoint1 = new QPushButton(frame_19);
        pbAnglePoint1->setObjectName(QString::fromUtf8("pbAnglePoint1"));
        pbAnglePoint1->setFlat(true);

        gridLayout_44->addWidget(pbAnglePoint1, 1, 2, 1, 1);

        pbAnglePoint2 = new QPushButton(frame_19);
        pbAnglePoint2->setObjectName(QString::fromUtf8("pbAnglePoint2"));
        pbAnglePoint2->setFlat(true);

        gridLayout_44->addWidget(pbAnglePoint2, 3, 2, 1, 1);


        verticalLayout_63->addWidget(frame_19);


        verticalLayout_60->addWidget(gbCameraCalibration_3);

        gbCameraCalibration_4 = new QGroupBox(gbImageProvider_2);
        gbCameraCalibration_4->setObjectName(QString::fromUtf8("gbCameraCalibration_4"));
        gbCameraCalibration_4->setFont(font6);
        gbCameraCalibration_4->setCheckable(true);
        gbCameraCalibration_4->setChecked(true);
        verticalLayout_67 = new QVBoxLayout(gbCameraCalibration_4);
        verticalLayout_67->setSpacing(6);
        verticalLayout_67->setContentsMargins(11, 11, 11, 11);
        verticalLayout_67->setObjectName(QString::fromUtf8("verticalLayout_67"));
        frame_22 = new QFrame(gbCameraCalibration_4);
        frame_22->setObjectName(QString::fromUtf8("frame_22"));
        frame_22->setMinimumSize(QSize(0, 0));
        frame_22->setFrameShape(QFrame::StyledPanel);
        frame_22->setFrameShadow(QFrame::Raised);
        gridLayout_45 = new QGridLayout(frame_22);
        gridLayout_45->setSpacing(6);
        gridLayout_45->setContentsMargins(11, 11, 11, 11);
        gridLayout_45->setObjectName(QString::fromUtf8("gridLayout_45"));
        leAnglePoint2X_2 = new QLineEdit(frame_22);
        leAnglePoint2X_2->setObjectName(QString::fromUtf8("leAnglePoint2X_2"));

        gridLayout_45->addWidget(leAnglePoint2X_2, 3, 2, 1, 1);

        leAnglePoint2Y_2 = new QLineEdit(frame_22);
        leAnglePoint2Y_2->setObjectName(QString::fromUtf8("leAnglePoint2Y_2"));

        gridLayout_45->addWidget(leAnglePoint2Y_2, 3, 4, 1, 1);

        leAngleResult_2 = new QLineEdit(frame_22);
        leAngleResult_2->setObjectName(QString::fromUtf8("leAngleResult_2"));

        gridLayout_45->addWidget(leAngleResult_2, 3, 1, 1, 1);

        label_226 = new QLabel(frame_22);
        label_226->setObjectName(QString::fromUtf8("label_226"));
        label_226->setAlignment(Qt::AlignCenter);

        gridLayout_45->addWidget(label_226, 2, 1, 1, 1);

        label_227 = new QLabel(frame_22);
        label_227->setObjectName(QString::fromUtf8("label_227"));
        label_227->setAlignment(Qt::AlignCenter);

        gridLayout_45->addWidget(label_227, 2, 2, 1, 1);

        label_228 = new QLabel(frame_22);
        label_228->setObjectName(QString::fromUtf8("label_228"));
        label_228->setAlignment(Qt::AlignCenter);

        gridLayout_45->addWidget(label_228, 2, 4, 1, 1);

        leAngleResult_3 = new QLineEdit(frame_22);
        leAngleResult_3->setObjectName(QString::fromUtf8("leAngleResult_3"));

        gridLayout_45->addWidget(leAngleResult_3, 3, 0, 1, 1);

        label_229 = new QLabel(frame_22);
        label_229->setObjectName(QString::fromUtf8("label_229"));
        label_229->setAlignment(Qt::AlignCenter);

        gridLayout_45->addWidget(label_229, 2, 0, 1, 1);

        leAnglePoint1X_2 = new QLineEdit(frame_22);
        leAnglePoint1X_2->setObjectName(QString::fromUtf8("leAnglePoint1X_2"));

        gridLayout_45->addWidget(leAnglePoint1X_2, 1, 0, 1, 1);

        label_197 = new QLabel(frame_22);
        label_197->setObjectName(QString::fromUtf8("label_197"));
        label_197->setAlignment(Qt::AlignCenter);

        gridLayout_45->addWidget(label_197, 0, 0, 1, 1);

        label_209 = new QLabel(frame_22);
        label_209->setObjectName(QString::fromUtf8("label_209"));
        label_209->setAlignment(Qt::AlignCenter);

        gridLayout_45->addWidget(label_209, 0, 1, 1, 1);

        pbCalculateAngle_2 = new QPushButton(frame_22);
        pbCalculateAngle_2->setObjectName(QString::fromUtf8("pbCalculateAngle_2"));

        gridLayout_45->addWidget(pbCalculateAngle_2, 1, 2, 1, 1);

        leAnglePoint1Y_2 = new QLineEdit(frame_22);
        leAnglePoint1Y_2->setObjectName(QString::fromUtf8("leAnglePoint1Y_2"));

        gridLayout_45->addWidget(leAnglePoint1Y_2, 1, 1, 1, 1);


        verticalLayout_67->addWidget(frame_22);


        verticalLayout_60->addWidget(gbCameraCalibration_4);


        verticalLayout_59->addWidget(gbImageProvider_2);

        gbCameraCalibration_2 = new QGroupBox(fObjectDetectingTool_2);
        gbCameraCalibration_2->setObjectName(QString::fromUtf8("gbCameraCalibration_2"));
        gbCameraCalibration_2->setFont(font6);
        gbCameraCalibration_2->setCheckable(true);
        gbCameraCalibration_2->setChecked(true);
        verticalLayout_62 = new QVBoxLayout(gbCameraCalibration_2);
        verticalLayout_62->setSpacing(6);
        verticalLayout_62->setContentsMargins(11, 11, 11, 11);
        verticalLayout_62->setObjectName(QString::fromUtf8("verticalLayout_62"));
        pbAddVariablePoint_2 = new QPushButton(gbCameraCalibration_2);
        pbAddVariablePoint_2->setObjectName(QString::fromUtf8("pbAddVariablePoint_2"));

        verticalLayout_62->addWidget(pbAddVariablePoint_2);

        frame_18 = new QFrame(gbCameraCalibration_2);
        frame_18->setObjectName(QString::fromUtf8("frame_18"));
        frame_18->setMinimumSize(QSize(0, 0));
        frame_18->setFrameShape(QFrame::StyledPanel);
        frame_18->setFrameShadow(QFrame::Raised);
        gridLayout_41 = new QGridLayout(frame_18);
        gridLayout_41->setSpacing(6);
        gridLayout_41->setContentsMargins(11, 11, 11, 11);
        gridLayout_41->setObjectName(QString::fromUtf8("gridLayout_41"));
        label_202 = new QLabel(frame_18);
        label_202->setObjectName(QString::fromUtf8("label_202"));
        label_202->setAlignment(Qt::AlignCenter);

        gridLayout_41->addWidget(label_202, 0, 6, 1, 1);

        label_203 = new QLabel(frame_18);
        label_203->setObjectName(QString::fromUtf8("label_203"));

        gridLayout_41->addWidget(label_203, 1, 3, 1, 1);

        label_204 = new QLabel(frame_18);
        label_204->setObjectName(QString::fromUtf8("label_204"));

        gridLayout_41->addWidget(label_204, 3, 3, 1, 1);

        leSourcePoint1X = new QLineEdit(frame_18);
        leSourcePoint1X->setObjectName(QString::fromUtf8("leSourcePoint1X"));

        gridLayout_41->addWidget(leSourcePoint1X, 1, 4, 1, 1);

        label_166 = new QLabel(frame_18);
        label_166->setObjectName(QString::fromUtf8("label_166"));

        gridLayout_41->addWidget(label_166, 1, 2, 1, 1);

        label_200 = new QLabel(frame_18);
        label_200->setObjectName(QString::fromUtf8("label_200"));

        gridLayout_41->addWidget(label_200, 3, 2, 1, 1);

        label_165 = new QLabel(frame_18);
        label_165->setObjectName(QString::fromUtf8("label_165"));

        gridLayout_41->addWidget(label_165, 1, 0, 1, 1);

        label_201 = new QLabel(frame_18);
        label_201->setObjectName(QString::fromUtf8("label_201"));

        gridLayout_41->addWidget(label_201, 2, 3, 1, 1);

        leMatrix1Name = new QLineEdit(frame_18);
        leMatrix1Name->setObjectName(QString::fromUtf8("leMatrix1Name"));

        gridLayout_41->addWidget(leMatrix1Name, 1, 1, 1, 1);

        label_177 = new QLabel(frame_18);
        label_177->setObjectName(QString::fromUtf8("label_177"));
        label_177->setAlignment(Qt::AlignCenter);

        gridLayout_41->addWidget(label_177, 0, 4, 1, 1);

        leSourcePoint2Y = new QLineEdit(frame_18);
        leSourcePoint2Y->setObjectName(QString::fromUtf8("leSourcePoint2Y"));

        gridLayout_41->addWidget(leSourcePoint2Y, 2, 6, 1, 1);

        leSourcePoint2X = new QLineEdit(frame_18);
        leSourcePoint2X->setObjectName(QString::fromUtf8("leSourcePoint2X"));

        gridLayout_41->addWidget(leSourcePoint2X, 2, 4, 1, 1);

        leSourcePoint1Y = new QLineEdit(frame_18);
        leSourcePoint1Y->setObjectName(QString::fromUtf8("leSourcePoint1Y"));

        gridLayout_41->addWidget(leSourcePoint1Y, 1, 6, 1, 1);

        label_205 = new QLabel(frame_18);
        label_205->setObjectName(QString::fromUtf8("label_205"));

        gridLayout_41->addWidget(label_205, 4, 3, 1, 1);

        leDestinationPoint1X = new QLineEdit(frame_18);
        leDestinationPoint1X->setObjectName(QString::fromUtf8("leDestinationPoint1X"));

        gridLayout_41->addWidget(leDestinationPoint1X, 3, 4, 1, 1);

        leDestinationPoint2X = new QLineEdit(frame_18);
        leDestinationPoint2X->setObjectName(QString::fromUtf8("leDestinationPoint2X"));

        gridLayout_41->addWidget(leDestinationPoint2X, 4, 4, 1, 1);

        leDestinationPoint1Y = new QLineEdit(frame_18);
        leDestinationPoint1Y->setObjectName(QString::fromUtf8("leDestinationPoint1Y"));

        gridLayout_41->addWidget(leDestinationPoint1Y, 3, 6, 1, 1);

        leDestinationPoint2Y = new QLineEdit(frame_18);
        leDestinationPoint2Y->setObjectName(QString::fromUtf8("leDestinationPoint2Y"));

        gridLayout_41->addWidget(leDestinationPoint2Y, 4, 6, 1, 1);

        pbCalculateMappingMatrixTool = new QPushButton(frame_18);
        pbCalculateMappingMatrixTool->setObjectName(QString::fromUtf8("pbCalculateMappingMatrixTool"));

        gridLayout_41->addWidget(pbCalculateMappingMatrixTool, 2, 1, 1, 1);


        verticalLayout_62->addWidget(frame_18);


        verticalLayout_59->addWidget(gbCameraCalibration_2);

        gbCameraObject_2 = new QGroupBox(fObjectDetectingTool_2);
        gbCameraObject_2->setObjectName(QString::fromUtf8("gbCameraObject_2"));
        gbCameraObject_2->setFont(font6);
        gbCameraObject_2->setCheckable(true);
        verticalLayout_64 = new QVBoxLayout(gbCameraObject_2);
        verticalLayout_64->setSpacing(6);
        verticalLayout_64->setContentsMargins(11, 11, 11, 11);
        verticalLayout_64->setObjectName(QString::fromUtf8("verticalLayout_64"));
        verticalLayout_64->setContentsMargins(-1, 10, -1, -1);
        pbAddVariablePoint = new QPushButton(gbCameraObject_2);
        pbAddVariablePoint->setObjectName(QString::fromUtf8("pbAddVariablePoint"));

        verticalLayout_64->addWidget(pbAddVariablePoint);

        frame_14 = new QFrame(gbCameraObject_2);
        frame_14->setObjectName(QString::fromUtf8("frame_14"));
        frame_14->setMinimumSize(QSize(0, 0));
        frame_14->setFrameShape(QFrame::StyledPanel);
        frame_14->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame_14);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_136 = new QLabel(frame_14);
        label_136->setObjectName(QString::fromUtf8("label_136"));

        horizontalLayout_5->addWidget(label_136);

        lePoint1Name = new QLineEdit(frame_14);
        lePoint1Name->setObjectName(QString::fromUtf8("lePoint1Name"));

        horizontalLayout_5->addWidget(lePoint1Name);

        label_137 = new QLabel(frame_14);
        label_137->setObjectName(QString::fromUtf8("label_137"));

        horizontalLayout_5->addWidget(label_137);

        lePoint1X = new QLineEdit(frame_14);
        lePoint1X->setObjectName(QString::fromUtf8("lePoint1X"));

        horizontalLayout_5->addWidget(lePoint1X);

        label_138 = new QLabel(frame_14);
        label_138->setObjectName(QString::fromUtf8("label_138"));

        horizontalLayout_5->addWidget(label_138);

        lePoint1Y = new QLineEdit(frame_14);
        lePoint1Y->setObjectName(QString::fromUtf8("lePoint1Y"));

        horizontalLayout_5->addWidget(lePoint1Y);

        label_143 = new QLabel(frame_14);
        label_143->setObjectName(QString::fromUtf8("label_143"));

        horizontalLayout_5->addWidget(label_143);

        lePoint1Z = new QLineEdit(frame_14);
        lePoint1Z->setObjectName(QString::fromUtf8("lePoint1Z"));

        horizontalLayout_5->addWidget(lePoint1Z);


        verticalLayout_64->addWidget(frame_14);

        gbCameraObject_3 = new QGroupBox(gbCameraObject_2);
        gbCameraObject_3->setObjectName(QString::fromUtf8("gbCameraObject_3"));
        gbCameraObject_3->setFont(font6);
        gbCameraObject_3->setCheckable(true);
        verticalLayout_65 = new QVBoxLayout(gbCameraObject_3);
        verticalLayout_65->setSpacing(6);
        verticalLayout_65->setContentsMargins(11, 11, 11, 11);
        verticalLayout_65->setObjectName(QString::fromUtf8("verticalLayout_65"));
        verticalLayout_65->setContentsMargins(-1, 10, -1, -1);
        pbAddVariablePoint_3 = new QPushButton(gbCameraObject_3);
        pbAddVariablePoint_3->setObjectName(QString::fromUtf8("pbAddVariablePoint_3"));

        verticalLayout_65->addWidget(pbAddVariablePoint_3);

        frame_20 = new QFrame(gbCameraObject_3);
        frame_20->setObjectName(QString::fromUtf8("frame_20"));
        frame_20->setMinimumSize(QSize(0, 0));
        frame_20->setFrameShape(QFrame::StyledPanel);
        frame_20->setFrameShadow(QFrame::Raised);
        gridLayout_42 = new QGridLayout(frame_20);
        gridLayout_42->setSpacing(6);
        gridLayout_42->setContentsMargins(11, 11, 11, 11);
        gridLayout_42->setObjectName(QString::fromUtf8("gridLayout_42"));
        label_210 = new QLabel(frame_20);
        label_210->setObjectName(QString::fromUtf8("label_210"));
        label_210->setAlignment(Qt::AlignCenter);

        gridLayout_42->addWidget(label_210, 0, 5, 1, 1);

        leMPoint3Y = new QLineEdit(frame_20);
        leMPoint3Y->setObjectName(QString::fromUtf8("leMPoint3Y"));

        gridLayout_42->addWidget(leMPoint3Y, 3, 5, 1, 1);

        label_218 = new QLabel(frame_20);
        label_218->setObjectName(QString::fromUtf8("label_218"));
        label_218->setAlignment(Qt::AlignCenter);

        gridLayout_42->addWidget(label_218, 0, 3, 1, 1);

        label_211 = new QLabel(frame_20);
        label_211->setObjectName(QString::fromUtf8("label_211"));

        gridLayout_42->addWidget(label_211, 1, 2, 1, 1);

        leMPoint1Y = new QLineEdit(frame_20);
        leMPoint1Y->setObjectName(QString::fromUtf8("leMPoint1Y"));

        gridLayout_42->addWidget(leMPoint1Y, 1, 5, 1, 1);

        label_212 = new QLabel(frame_20);
        label_212->setObjectName(QString::fromUtf8("label_212"));

        gridLayout_42->addWidget(label_212, 3, 2, 1, 1);

        label_216 = new QLabel(frame_20);
        label_216->setObjectName(QString::fromUtf8("label_216"));

        gridLayout_42->addWidget(label_216, 1, 0, 1, 1);

        lePointMatrixName = new QLineEdit(frame_20);
        lePointMatrixName->setObjectName(QString::fromUtf8("lePointMatrixName"));

        gridLayout_42->addWidget(lePointMatrixName, 1, 1, 1, 1);

        leMPoint4X = new QLineEdit(frame_20);
        leMPoint4X->setObjectName(QString::fromUtf8("leMPoint4X"));

        gridLayout_42->addWidget(leMPoint4X, 4, 3, 1, 1);

        leMPoint2Y = new QLineEdit(frame_20);
        leMPoint2Y->setObjectName(QString::fromUtf8("leMPoint2Y"));

        gridLayout_42->addWidget(leMPoint2Y, 2, 5, 1, 1);

        leMPoint3X = new QLineEdit(frame_20);
        leMPoint3X->setObjectName(QString::fromUtf8("leMPoint3X"));

        gridLayout_42->addWidget(leMPoint3X, 3, 3, 1, 1);

        label_217 = new QLabel(frame_20);
        label_217->setObjectName(QString::fromUtf8("label_217"));

        gridLayout_42->addWidget(label_217, 2, 2, 1, 1);

        leMPoint1X = new QLineEdit(frame_20);
        leMPoint1X->setObjectName(QString::fromUtf8("leMPoint1X"));

        gridLayout_42->addWidget(leMPoint1X, 1, 3, 1, 1);

        leMPoint4Y = new QLineEdit(frame_20);
        leMPoint4Y->setObjectName(QString::fromUtf8("leMPoint4Y"));

        gridLayout_42->addWidget(leMPoint4Y, 4, 5, 1, 1);

        leMPoint2X = new QLineEdit(frame_20);
        leMPoint2X->setObjectName(QString::fromUtf8("leMPoint2X"));

        gridLayout_42->addWidget(leMPoint2X, 2, 3, 1, 1);

        label_219 = new QLabel(frame_20);
        label_219->setObjectName(QString::fromUtf8("label_219"));

        gridLayout_42->addWidget(label_219, 4, 2, 1, 1);

        pbCalculatePointMatrixTool = new QPushButton(frame_20);
        pbCalculatePointMatrixTool->setObjectName(QString::fromUtf8("pbCalculatePointMatrixTool"));

        gridLayout_42->addWidget(pbCalculatePointMatrixTool, 2, 1, 1, 1);


        verticalLayout_65->addWidget(frame_20);


        verticalLayout_64->addWidget(gbCameraObject_3);


        verticalLayout_59->addWidget(gbCameraObject_2);

        gbCameraObject_4 = new QGroupBox(fObjectDetectingTool_2);
        gbCameraObject_4->setObjectName(QString::fromUtf8("gbCameraObject_4"));
        gbCameraObject_4->setFont(font6);
        gbCameraObject_4->setCheckable(true);
        verticalLayout_66 = new QVBoxLayout(gbCameraObject_4);
        verticalLayout_66->setSpacing(6);
        verticalLayout_66->setContentsMargins(11, 11, 11, 11);
        verticalLayout_66->setObjectName(QString::fromUtf8("verticalLayout_66"));
        verticalLayout_66->setContentsMargins(-1, 10, -1, -1);
        frame_21 = new QFrame(gbCameraObject_4);
        frame_21->setObjectName(QString::fromUtf8("frame_21"));
        frame_21->setMinimumSize(QSize(0, 0));
        frame_21->setFrameShape(QFrame::StyledPanel);
        frame_21->setFrameShadow(QFrame::Raised);
        gridLayout_43 = new QGridLayout(frame_21);
        gridLayout_43->setSpacing(6);
        gridLayout_43->setContentsMargins(11, 11, 11, 11);
        gridLayout_43->setObjectName(QString::fromUtf8("gridLayout_43"));
        leTestPointY = new QLineEdit(frame_21);
        leTestPointY->setObjectName(QString::fromUtf8("leTestPointY"));
        QSizePolicy sizePolicy11(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(leTestPointY->sizePolicy().hasHeightForWidth());
        leTestPointY->setSizePolicy(sizePolicy11);

        gridLayout_43->addWidget(leTestPointY, 2, 3, 1, 1);

        leTargetTestPointY = new QLineEdit(frame_21);
        leTargetTestPointY->setObjectName(QString::fromUtf8("leTargetTestPointY"));
        sizePolicy11.setHeightForWidth(leTargetTestPointY->sizePolicy().hasHeightForWidth());
        leTargetTestPointY->setSizePolicy(sizePolicy11);

        gridLayout_43->addWidget(leTargetTestPointY, 5, 3, 1, 1);

        leTargetTestPointX = new QLineEdit(frame_21);
        leTargetTestPointX->setObjectName(QString::fromUtf8("leTargetTestPointX"));
        sizePolicy11.setHeightForWidth(leTargetTestPointX->sizePolicy().hasHeightForWidth());
        leTargetTestPointX->setSizePolicy(sizePolicy11);

        gridLayout_43->addWidget(leTargetTestPointX, 5, 2, 1, 1);

        leTestMatrixName = new QLineEdit(frame_21);
        leTestMatrixName->setObjectName(QString::fromUtf8("leTestMatrixName"));
        QSizePolicy sizePolicy12(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(leTestMatrixName->sizePolicy().hasHeightForWidth());
        leTestMatrixName->setSizePolicy(sizePolicy12);
        leTestMatrixName->setMinimumSize(QSize(0, 0));

        gridLayout_43->addWidget(leTestMatrixName, 2, 5, 1, 1);

        pbCalculateTestPoint = new QPushButton(frame_21);
        pbCalculateTestPoint->setObjectName(QString::fromUtf8("pbCalculateTestPoint"));
        sizePolicy11.setHeightForWidth(pbCalculateTestPoint->sizePolicy().hasHeightForWidth());
        pbCalculateTestPoint->setSizePolicy(sizePolicy11);

        gridLayout_43->addWidget(pbCalculateTestPoint, 3, 2, 1, 1);

        leTestPointX = new QLineEdit(frame_21);
        leTestPointX->setObjectName(QString::fromUtf8("leTestPointX"));
        sizePolicy11.setHeightForWidth(leTestPointX->sizePolicy().hasHeightForWidth());
        leTestPointX->setSizePolicy(sizePolicy11);

        gridLayout_43->addWidget(leTestPointX, 2, 2, 1, 1);

        label_215 = new QLabel(frame_21);
        label_215->setObjectName(QString::fromUtf8("label_215"));
        label_215->setAlignment(Qt::AlignCenter);

        gridLayout_43->addWidget(label_215, 1, 2, 1, 2);

        label_223 = new QLabel(frame_21);
        label_223->setObjectName(QString::fromUtf8("label_223"));

        gridLayout_43->addWidget(label_223, 2, 4, 1, 1);

        label_222 = new QLabel(frame_21);
        label_222->setObjectName(QString::fromUtf8("label_222"));
        label_222->setAlignment(Qt::AlignCenter);

        gridLayout_43->addWidget(label_222, 1, 5, 1, 1);

        label_221 = new QLabel(frame_21);
        label_221->setObjectName(QString::fromUtf8("label_221"));
        label_221->setAlignment(Qt::AlignCenter);

        gridLayout_43->addWidget(label_221, 4, 2, 1, 1);

        label_214 = new QLabel(frame_21);
        label_214->setObjectName(QString::fromUtf8("label_214"));
        label_214->setAlignment(Qt::AlignCenter);

        gridLayout_43->addWidget(label_214, 4, 3, 1, 1);


        verticalLayout_66->addWidget(frame_21);


        verticalLayout_59->addWidget(gbCameraObject_4);

        verticalSpacer_18 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_59->addItem(verticalSpacer_18);

        splitter_3->addWidget(fObjectDetectingTool_2);

        verticalLayout_18->addWidget(splitter_3);

        saObjectDetecting_2->setWidget(wObjectDetecting_2);

        verticalLayout_14->addWidget(saObjectDetecting_2);

        twModule->addTab(tPointTool, QString());
        tDrawing = new QWidget();
        tDrawing->setObjectName(QString::fromUtf8("tDrawing"));
        verticalLayout_26 = new QVBoxLayout(tDrawing);
        verticalLayout_26->setSpacing(6);
        verticalLayout_26->setContentsMargins(11, 11, 11, 11);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        scrollArea_6 = new QScrollArea(tDrawing);
        scrollArea_6->setObjectName(QString::fromUtf8("scrollArea_6"));
        scrollArea_6->setWidgetResizable(true);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 471, 1600));
        scrollAreaWidgetContents_6->setMinimumSize(QSize(450, 1600));
        scrollAreaWidgetContents_6->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_38 = new QVBoxLayout(scrollAreaWidgetContents_6);
        verticalLayout_38->setSpacing(6);
        verticalLayout_38->setContentsMargins(11, 11, 11, 11);
        verticalLayout_38->setObjectName(QString::fromUtf8("verticalLayout_38"));
        verticalLayout_37 = new QVBoxLayout();
        verticalLayout_37->setSpacing(6);
        verticalLayout_37->setObjectName(QString::fromUtf8("verticalLayout_37"));
        frame_4 = new QFrame(scrollAreaWidgetContents_6);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        sizePolicy10.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy10);
        frame_4->setMinimumSize(QSize(0, 75));
        frame_4->setMaximumSize(QSize(16777215, 16777215));
        frame_4->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QToolButton\n"
"{\n"
"	border: 1px solid rgb(131, 131, 131);\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
"QToolButton::hover\n"
"{\n"
"	border: 1px solid rgb(32, 140, 255);\n"
"	background-color: rgb(217, 240, 255);\n"
"}"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        verticalLayout_21 = new QVBoxLayout(frame_4);
        verticalLayout_21->setSpacing(0);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        verticalLayout_21->setContentsMargins(5, 5, 0, 5);
        pbOpenPicture = new QToolButton(frame_4);
        pbOpenPicture->setObjectName(QString::fromUtf8("pbOpenPicture"));
        QSizePolicy sizePolicy13(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(pbOpenPicture->sizePolicy().hasHeightForWidth());
        pbOpenPicture->setSizePolicy(sizePolicy13);
        pbOpenPicture->setMinimumSize(QSize(0, 0));
        pbOpenPicture->setMaximumSize(QSize(16777215, 16777215));
        QFont font10;
        font10.setPointSize(10);
        font10.setBold(false);
        font10.setWeight(50);
        pbOpenPicture->setFont(font10);
        pbOpenPicture->setLayoutDirection(Qt::LeftToRight);
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/icon/icons8_image_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenPicture->setIcon(icon27);
        pbOpenPicture->setIconSize(QSize(64, 64));
        pbOpenPicture->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbOpenPicture->setAutoRaise(false);

        verticalLayout_21->addWidget(pbOpenPicture);


        verticalLayout_37->addWidget(frame_4);

        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        frame_2 = new QFrame(scrollAreaWidgetContents_6);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(0, 250));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        lbImageForDrawing = new QLabel(frame_2);
        lbImageForDrawing->setObjectName(QString::fromUtf8("lbImageForDrawing"));
        lbImageForDrawing->setGeometry(QRect(10, 10, 281, 226));
        sizePolicy.setHeightForWidth(lbImageForDrawing->sizePolicy().hasHeightForWidth());
        lbImageForDrawing->setSizePolicy(sizePolicy);
        lbImageForDrawing->setMinimumSize(QSize(0, 0));
        lbImageForDrawing->setStyleSheet(QString::fromUtf8("/*background-color: rgb(142, 254, 255);*/\n"
"QLabel\n"
"{\n"
"	/*background-color: rgb(255, 255, 255);*/\n"
"	border: 1px solid rgb(140, 140, 140);\n"
"	border-radius: 5px;\n"
"}"));
        lbImageForDrawing->setScaledContents(false);

        horizontalLayout_24->addWidget(frame_2);

        widget = new QWidget(scrollAreaWidgetContents_6);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setMaximumSize(QSize(100, 16777215));
        verticalLayout_36 = new QVBoxLayout(widget);
        verticalLayout_36->setSpacing(6);
        verticalLayout_36->setContentsMargins(11, 11, 11, 11);
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        widget_3 = new QWidget(widget);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8(""));
        gridLayout_23 = new QGridLayout(widget_3);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        lbImageWidth = new QLabel(widget_3);
        lbImageWidth->setObjectName(QString::fromUtf8("lbImageWidth"));
        lbImageWidth->setFont(font5);
        lbImageWidth->setStyleSheet(QString::fromUtf8(""));

        gridLayout_23->addWidget(lbImageWidth, 0, 0, 1, 1);

        lbImageHeight = new QLabel(widget_3);
        lbImageHeight->setObjectName(QString::fromUtf8("lbImageHeight"));
        lbImageHeight->setFont(font5);
        lbImageHeight->setStyleSheet(QString::fromUtf8(""));

        gridLayout_23->addWidget(lbImageHeight, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_23->addItem(verticalSpacer_4, 2, 0, 1, 1);


        verticalLayout_36->addWidget(widget_3);


        horizontalLayout_24->addWidget(widget);


        verticalLayout_37->addLayout(horizontalLayout_24);

        widget_2 = new QWidget(scrollAreaWidgetContents_6);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setMinimumSize(QSize(0, 50));
        widget_2->setMaximumSize(QSize(16777215, 80));
        widget_2->setStyleSheet(QString::fromUtf8("/*background-color: rgb(171, 225, 224);*/"));
        gridLayout_25 = new QGridLayout(widget_2);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        cbConversionTool = new QComboBox(widget_2);
        cbConversionTool->addItem(QString());
        cbConversionTool->addItem(QString());
        cbConversionTool->addItem(QString());
        cbConversionTool->setObjectName(QString::fromUtf8("cbConversionTool"));
        cbConversionTool->setMinimumSize(QSize(0, 30));

        gridLayout_25->addWidget(cbConversionTool, 1, 1, 1, 1);

        hsDrawingThreshold = new QSlider(widget_2);
        hsDrawingThreshold->setObjectName(QString::fromUtf8("hsDrawingThreshold"));
        hsDrawingThreshold->setMaximum(255);
        hsDrawingThreshold->setSingleStep(1);
        hsDrawingThreshold->setValue(150);
        hsDrawingThreshold->setOrientation(Qt::Horizontal);

        gridLayout_25->addWidget(hsDrawingThreshold, 1, 2, 1, 1);

        leDrawingThreshold = new QLineEdit(widget_2);
        leDrawingThreshold->setObjectName(QString::fromUtf8("leDrawingThreshold"));
        leDrawingThreshold->setMinimumSize(QSize(0, 30));
        leDrawingThreshold->setMaximumSize(QSize(60, 16777215));
        leDrawingThreshold->setFont(font5);

        gridLayout_25->addWidget(leDrawingThreshold, 1, 3, 1, 1);

        label_14 = new QLabel(widget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font5);

        gridLayout_25->addWidget(label_14, 1, 0, 1, 1);

        label_105 = new QLabel(widget_2);
        label_105->setObjectName(QString::fromUtf8("label_105"));
        label_105->setFont(font5);

        gridLayout_25->addWidget(label_105, 2, 0, 1, 1);

        cbReverseDrawing = new QCheckBox(widget_2);
        cbReverseDrawing->setObjectName(QString::fromUtf8("cbReverseDrawing"));

        gridLayout_25->addWidget(cbReverseDrawing, 2, 1, 1, 1);


        verticalLayout_37->addWidget(widget_2);

        frame_5 = new QFrame(scrollAreaWidgetContents_6);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        sizePolicy3.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy3);
        frame_5->setMinimumSize(QSize(0, 75));
        frame_5->setMaximumSize(QSize(16777215, 16777215));
        frame_5->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QToolButton\n"
"{\n"
"	border: 1px solid rgb(131, 131, 131);\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
"QToolButton::hover\n"
"{\n"
"	border: 1px solid rgb(32, 140, 255);\n"
"	background-color: rgb(217, 240, 255);\n"
"}"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        verticalLayout_47 = new QVBoxLayout(frame_5);
        verticalLayout_47->setSpacing(0);
        verticalLayout_47->setContentsMargins(11, 11, 11, 11);
        verticalLayout_47->setObjectName(QString::fromUtf8("verticalLayout_47"));
        verticalLayout_47->setContentsMargins(5, 5, 0, 5);
        pbPainting = new QToolButton(frame_5);
        pbPainting->setObjectName(QString::fromUtf8("pbPainting"));
        sizePolicy13.setHeightForWidth(pbPainting->sizePolicy().hasHeightForWidth());
        pbPainting->setSizePolicy(sizePolicy13);
        pbPainting->setMinimumSize(QSize(0, 0));
        pbPainting->setMaximumSize(QSize(16777215, 16777215));
        pbPainting->setFont(font10);
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/icon/icons8_pencil_drawing_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPainting->setIcon(icon28);
        pbPainting->setIconSize(QSize(64, 64));
        pbPainting->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbPainting->setAutoRaise(false);
        pbPainting->setArrowType(Qt::NoArrow);

        verticalLayout_47->addWidget(pbPainting);


        verticalLayout_37->addWidget(frame_5);

        frame_7 = new QFrame(scrollAreaWidgetContents_6);
        frame_7->setObjectName(QString::fromUtf8("frame_7"));
        frame_7->setMinimumSize(QSize(0, 50));
        frame_7->setFrameShape(QFrame::StyledPanel);
        frame_7->setFrameShadow(QFrame::Raised);
        gridLayout_24 = new QGridLayout(frame_7);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        label_20 = new QLabel(frame_7);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setFont(font5);

        gridLayout_24->addWidget(label_20, 0, 1, 1, 1);

        label_18 = new QLabel(frame_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font5);

        gridLayout_24->addWidget(label_18, 0, 2, 1, 1);

        horizontalSpacer_40 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_24->addItem(horizontalSpacer_40, 1, 4, 1, 1);

        cbLockDrawingArea = new QComboBox(frame_7);
        cbLockDrawingArea->addItem(QString());
        cbLockDrawingArea->addItem(QString());
        cbLockDrawingArea->setObjectName(QString::fromUtf8("cbLockDrawingArea"));

        gridLayout_24->addWidget(cbLockDrawingArea, 1, 3, 1, 1);

        label_104 = new QLabel(frame_7);
        label_104->setObjectName(QString::fromUtf8("label_104"));

        gridLayout_24->addWidget(label_104, 0, 3, 1, 1);

        leWidthScale = new QLineEdit(frame_7);
        leWidthScale->setObjectName(QString::fromUtf8("leWidthScale"));
        leWidthScale->setMinimumSize(QSize(0, 30));
        leWidthScale->setMaximumSize(QSize(100, 16777215));

        gridLayout_24->addWidget(leWidthScale, 1, 2, 1, 1);

        leHeightScale = new QLineEdit(frame_7);
        leHeightScale->setObjectName(QString::fromUtf8("leHeightScale"));
        leHeightScale->setMinimumSize(QSize(0, 30));
        leHeightScale->setMaximumSize(QSize(100, 16777215));

        gridLayout_24->addWidget(leHeightScale, 1, 1, 1, 1);


        verticalLayout_37->addWidget(frame_7);

        label_21 = new QLabel(scrollAreaWidgetContents_6);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        verticalLayout_37->addWidget(label_21);

        frame_3 = new QFrame(scrollAreaWidgetContents_6);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy10.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy10);
        frame_3->setMinimumSize(QSize(300, 300));
        frame_3->setMaximumSize(QSize(300, 300));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        lbDrawingArea = new DrawingWidget(frame_3);
        lbDrawingArea->setObjectName(QString::fromUtf8("lbDrawingArea"));
        lbDrawingArea->setGeometry(QRect(0, 0, 300, 300));
        sizePolicy.setHeightForWidth(lbDrawingArea->sizePolicy().hasHeightForWidth());
        lbDrawingArea->setSizePolicy(sizePolicy);
        lbDrawingArea->setMinimumSize(QSize(300, 300));
        lbDrawingArea->setMaximumSize(QSize(300, 300));
        lbDrawingArea->setStyleSheet(QString::fromUtf8("/*background-color: rgb(142, 254, 255);*/\n"
"QLabel\n"
"{\n"
"	/*background-color: rgb(255, 255, 255);*/\n"
"	border: 1px solid rgb(140, 140, 140);\n"
"	border-radius: 150px;\n"
"}"));
        lbDrawingArea->setScaledContents(true);

        verticalLayout_37->addWidget(frame_3);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(0);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        widget_11 = new QWidget(scrollAreaWidgetContents_6);
        widget_11->setObjectName(QString::fromUtf8("widget_11"));
        widget_11->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        horizontalLayout_22 = new QHBoxLayout(widget_11);
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        label_26 = new QLabel(widget_11);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_22->addWidget(label_26);

        leDrawAg5 = new QLineEdit(widget_11);
        leDrawAg5->setObjectName(QString::fromUtf8("leDrawAg5"));
        QSizePolicy sizePolicy14(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(leDrawAg5->sizePolicy().hasHeightForWidth());
        leDrawAg5->setSizePolicy(sizePolicy14);
        leDrawAg5->setMinimumSize(QSize(0, 20));
        leDrawAg5->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_22->addWidget(leDrawAg5);


        horizontalLayout_23->addWidget(widget_11);

        widget_10 = new QWidget(scrollAreaWidgetContents_6);
        widget_10->setObjectName(QString::fromUtf8("widget_10"));
        widget_10->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        horizontalLayout_21 = new QHBoxLayout(widget_10);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        label_25 = new QLabel(widget_10);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        label_25->setFont(font5);

        horizontalLayout_21->addWidget(label_25);

        leDrawAg4 = new QLineEdit(widget_10);
        leDrawAg4->setObjectName(QString::fromUtf8("leDrawAg4"));
        sizePolicy14.setHeightForWidth(leDrawAg4->sizePolicy().hasHeightForWidth());
        leDrawAg4->setSizePolicy(sizePolicy14);
        leDrawAg4->setMinimumSize(QSize(0, 20));
        leDrawAg4->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_21->addWidget(leDrawAg4);


        horizontalLayout_23->addWidget(widget_10);

        widget_9 = new QWidget(scrollAreaWidgetContents_6);
        widget_9->setObjectName(QString::fromUtf8("widget_9"));
        widget_9->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        horizontalLayout_20 = new QHBoxLayout(widget_9);
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        label_24 = new QLabel(widget_9);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_20->addWidget(label_24);

        leDrawAg3 = new QLineEdit(widget_9);
        leDrawAg3->setObjectName(QString::fromUtf8("leDrawAg3"));
        sizePolicy14.setHeightForWidth(leDrawAg3->sizePolicy().hasHeightForWidth());
        leDrawAg3->setSizePolicy(sizePolicy14);
        leDrawAg3->setMinimumSize(QSize(0, 20));
        leDrawAg3->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_20->addWidget(leDrawAg3);


        horizontalLayout_23->addWidget(widget_9);

        widget_8 = new QWidget(scrollAreaWidgetContents_6);
        widget_8->setObjectName(QString::fromUtf8("widget_8"));
        widget_8->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        horizontalLayout_19 = new QHBoxLayout(widget_8);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_22 = new QLabel(widget_8);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_19->addWidget(label_22);

        leDrawAg2 = new QLineEdit(widget_8);
        leDrawAg2->setObjectName(QString::fromUtf8("leDrawAg2"));
        sizePolicy14.setHeightForWidth(leDrawAg2->sizePolicy().hasHeightForWidth());
        leDrawAg2->setSizePolicy(sizePolicy14);
        leDrawAg2->setMinimumSize(QSize(0, 20));
        leDrawAg2->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_19->addWidget(leDrawAg2);


        horizontalLayout_23->addWidget(widget_8);

        widget_7 = new QWidget(scrollAreaWidgetContents_6);
        widget_7->setObjectName(QString::fromUtf8("widget_7"));
        widget_7->setStyleSheet(QString::fromUtf8("background-color: rgb(234, 234, 234);"));
        horizontalLayout_18 = new QHBoxLayout(widget_7);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_19 = new QLabel(widget_7);
        label_19->setObjectName(QString::fromUtf8("label_19"));

        horizontalLayout_18->addWidget(label_19);

        leDrawAg1 = new QLineEdit(widget_7);
        leDrawAg1->setObjectName(QString::fromUtf8("leDrawAg1"));
        sizePolicy14.setHeightForWidth(leDrawAg1->sizePolicy().hasHeightForWidth());
        leDrawAg1->setSizePolicy(sizePolicy14);
        leDrawAg1->setMinimumSize(QSize(0, 20));
        leDrawAg1->setMaximumSize(QSize(100, 16777215));

        horizontalLayout_18->addWidget(leDrawAg1);


        horizontalLayout_23->addWidget(widget_7);


        verticalLayout_37->addLayout(horizontalLayout_23);

        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(10);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_11->addItem(horizontalSpacer_5, 0, 4, 1, 1);

        pbDrawLine = new QToolButton(scrollAreaWidgetContents_6);
        pbDrawLine->setObjectName(QString::fromUtf8("pbDrawLine"));
        sizePolicy12.setHeightForWidth(pbDrawLine->sizePolicy().hasHeightForWidth());
        pbDrawLine->setSizePolicy(sizePolicy12);
        pbDrawLine->setMinimumSize(QSize(0, 0));
        pbDrawLine->setMaximumSize(QSize(70, 16777215));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/icon/Line_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawLine->setIcon(icon29);
        pbDrawLine->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawLine->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawLine, 0, 0, 1, 1);

        pbDrawRectangle = new QToolButton(scrollAreaWidgetContents_6);
        pbDrawRectangle->setObjectName(QString::fromUtf8("pbDrawRectangle"));
        sizePolicy12.setHeightForWidth(pbDrawRectangle->sizePolicy().hasHeightForWidth());
        pbDrawRectangle->setSizePolicy(sizePolicy12);
        pbDrawRectangle->setMinimumSize(QSize(0, 0));
        pbDrawRectangle->setMaximumSize(QSize(70, 16777215));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/icon/Rectangular_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawRectangle->setIcon(icon30);
        pbDrawRectangle->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawRectangle->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawRectangle, 0, 1, 1, 1);

        pbZoomIn = new QToolButton(scrollAreaWidgetContents_6);
        pbZoomIn->setObjectName(QString::fromUtf8("pbZoomIn"));
        sizePolicy12.setHeightForWidth(pbZoomIn->sizePolicy().hasHeightForWidth());
        pbZoomIn->setSizePolicy(sizePolicy12);
        pbZoomIn->setMinimumSize(QSize(0, 0));
        pbZoomIn->setMaximumSize(QSize(70, 16777215));
        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/icon/Zoom In_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomIn->setIcon(icon31);
        pbZoomIn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbZoomIn->setAutoRaise(true);

        gridLayout_11->addWidget(pbZoomIn, 0, 2, 1, 1);

        pbCursor = new QToolButton(scrollAreaWidgetContents_6);
        pbCursor->setObjectName(QString::fromUtf8("pbCursor"));
        sizePolicy12.setHeightForWidth(pbCursor->sizePolicy().hasHeightForWidth());
        pbCursor->setSizePolicy(sizePolicy12);
        pbCursor->setMinimumSize(QSize(0, 0));
        pbCursor->setMaximumSize(QSize(70, 16777215));
        QIcon icon32;
        icon32.addFile(QString::fromUtf8(":/icon/Cursor-color_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCursor->setIcon(icon32);
        pbCursor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbCursor->setAutoRaise(true);

        gridLayout_11->addWidget(pbCursor, 0, 3, 1, 1);

        pbDrawArc = new QToolButton(scrollAreaWidgetContents_6);
        pbDrawArc->setObjectName(QString::fromUtf8("pbDrawArc"));
        sizePolicy12.setHeightForWidth(pbDrawArc->sizePolicy().hasHeightForWidth());
        pbDrawArc->setSizePolicy(sizePolicy12);
        pbDrawArc->setMinimumSize(QSize(0, 0));
        pbDrawArc->setMaximumSize(QSize(70, 16777215));
        QIcon icon33;
        icon33.addFile(QString::fromUtf8(":/icon/Circled Notch_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawArc->setIcon(icon33);
        pbDrawArc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawArc->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawArc, 1, 0, 1, 1);

        pbDrawCircle = new QToolButton(scrollAreaWidgetContents_6);
        pbDrawCircle->setObjectName(QString::fromUtf8("pbDrawCircle"));
        sizePolicy12.setHeightForWidth(pbDrawCircle->sizePolicy().hasHeightForWidth());
        pbDrawCircle->setSizePolicy(sizePolicy12);
        pbDrawCircle->setMinimumSize(QSize(0, 0));
        pbDrawCircle->setMaximumSize(QSize(70, 16777215));
        QIcon icon34;
        icon34.addFile(QString::fromUtf8(":/icon/Circle_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawCircle->setIcon(icon34);
        pbDrawCircle->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawCircle->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawCircle, 1, 1, 1, 1);

        pbZoomOut = new QToolButton(scrollAreaWidgetContents_6);
        pbZoomOut->setObjectName(QString::fromUtf8("pbZoomOut"));
        sizePolicy12.setHeightForWidth(pbZoomOut->sizePolicy().hasHeightForWidth());
        pbZoomOut->setSizePolicy(sizePolicy12);
        pbZoomOut->setMinimumSize(QSize(0, 0));
        pbZoomOut->setMaximumSize(QSize(70, 16777215));
        QIcon icon35;
        icon35.addFile(QString::fromUtf8(":/icon/Zoom Out_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomOut->setIcon(icon35);
        pbZoomOut->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbZoomOut->setAutoRaise(true);

        gridLayout_11->addWidget(pbZoomOut, 1, 2, 1, 1);


        verticalLayout_37->addLayout(gridLayout_11);

        frame_6 = new QFrame(scrollAreaWidgetContents_6);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        sizePolicy3.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
        frame_6->setSizePolicy(sizePolicy3);
        frame_6->setMinimumSize(QSize(0, 75));
        frame_6->setMaximumSize(QSize(16777215, 16777215));
        frame_6->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QToolButton\n"
"{\n"
"	border: 1px solid rgb(131, 131, 131);\n"
"	border-radius: 5px;\n"
"}\n"
"\n"
"QToolButton::hover\n"
"{\n"
"	border: 1px solid rgb(32, 140, 255);\n"
"	background-color: rgb(217, 240, 255);\n"
"}"));
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        verticalLayout_48 = new QVBoxLayout(frame_6);
        verticalLayout_48->setSpacing(0);
        verticalLayout_48->setContentsMargins(11, 11, 11, 11);
        verticalLayout_48->setObjectName(QString::fromUtf8("verticalLayout_48"));
        verticalLayout_48->setContentsMargins(5, 5, 0, 5);
        pbExportDrawingGcodes = new QToolButton(frame_6);
        pbExportDrawingGcodes->setObjectName(QString::fromUtf8("pbExportDrawingGcodes"));
        sizePolicy13.setHeightForWidth(pbExportDrawingGcodes->sizePolicy().hasHeightForWidth());
        pbExportDrawingGcodes->setSizePolicy(sizePolicy13);
        pbExportDrawingGcodes->setMinimumSize(QSize(185, 65));
        pbExportDrawingGcodes->setMaximumSize(QSize(16777215, 16777215));
        pbExportDrawingGcodes->setFont(font10);
        QIcon icon36;
        icon36.addFile(QString::fromUtf8(":/icon/icons8_code_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbExportDrawingGcodes->setIcon(icon36);
        pbExportDrawingGcodes->setIconSize(QSize(64, 64));
        pbExportDrawingGcodes->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbExportDrawingGcodes->setAutoRaise(false);

        verticalLayout_48->addWidget(pbExportDrawingGcodes);


        verticalLayout_37->addWidget(frame_6);

        gridLayout_22 = new QGridLayout();
        gridLayout_22->setSpacing(15);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        gridLayout_22->setContentsMargins(-1, 5, -1, 5);
        label_96 = new QLabel(scrollAreaWidgetContents_6);
        label_96->setObjectName(QString::fromUtf8("label_96"));
        sizePolicy4.setHeightForWidth(label_96->sizePolicy().hasHeightForWidth());
        label_96->setSizePolicy(sizePolicy4);
        label_96->setMinimumSize(QSize(0, 0));
        label_96->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_96, 4, 0, 1, 1);

        label_101 = new QLabel(scrollAreaWidgetContents_6);
        label_101->setObjectName(QString::fromUtf8("label_101"));
        sizePolicy.setHeightForWidth(label_101->sizePolicy().hasHeightForWidth());
        label_101->setSizePolicy(sizePolicy);
        label_101->setMinimumSize(QSize(0, 0));
        QFont font11;
        font11.setItalic(false);
        label_101->setFont(font11);
        label_101->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_101, 6, 2, 1, 1);

        label_13 = new QLabel(scrollAreaWidgetContents_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font5);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_13, 1, 0, 1, 1);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_22->addItem(horizontalSpacer_33, 0, 2, 1, 1);

        label_97 = new QLabel(scrollAreaWidgetContents_6);
        label_97->setObjectName(QString::fromUtf8("label_97"));
        sizePolicy4.setHeightForWidth(label_97->sizePolicy().hasHeightForWidth());
        label_97->setSizePolicy(sizePolicy4);
        label_97->setMinimumSize(QSize(0, 0));
        label_97->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_97, 6, 0, 1, 1);

        leTravelSpeed = new QLineEdit(scrollAreaWidgetContents_6);
        leTravelSpeed->setObjectName(QString::fromUtf8("leTravelSpeed"));
        leTravelSpeed->setMinimumSize(QSize(0, 30));
        leTravelSpeed->setMaximumSize(QSize(150, 16777215));

        gridLayout_22->addWidget(leTravelSpeed, 4, 1, 1, 1);

        cbDrawMethod = new QComboBox(scrollAreaWidgetContents_6);
        cbDrawMethod->addItem(QString());
        cbDrawMethod->addItem(QString());
        cbDrawMethod->setObjectName(QString::fromUtf8("cbDrawMethod"));
        cbDrawMethod->setMinimumSize(QSize(0, 30));
        cbDrawMethod->setMaximumSize(QSize(150, 16777215));

        gridLayout_22->addWidget(cbDrawMethod, 1, 1, 1, 1);

        cbDrawingEffector = new QComboBox(scrollAreaWidgetContents_6);
        cbDrawingEffector->addItem(QString());
        cbDrawingEffector->addItem(QString());
        cbDrawingEffector->setObjectName(QString::fromUtf8("cbDrawingEffector"));
        sizePolicy3.setHeightForWidth(cbDrawingEffector->sizePolicy().hasHeightForWidth());
        cbDrawingEffector->setSizePolicy(sizePolicy3);
        cbDrawingEffector->setMinimumSize(QSize(0, 30));
        cbDrawingEffector->setMaximumSize(QSize(150, 16777215));

        gridLayout_22->addWidget(cbDrawingEffector, 0, 1, 1, 1);

        leSafeZHeight = new QLineEdit(scrollAreaWidgetContents_6);
        leSafeZHeight->setObjectName(QString::fromUtf8("leSafeZHeight"));
        leSafeZHeight->setMinimumSize(QSize(0, 30));
        leSafeZHeight->setMaximumSize(QSize(150, 16777215));

        gridLayout_22->addWidget(leSafeZHeight, 3, 1, 1, 1);

        leDrawingAcceleration = new QLineEdit(scrollAreaWidgetContents_6);
        leDrawingAcceleration->setObjectName(QString::fromUtf8("leDrawingAcceleration"));
        leDrawingAcceleration->setMinimumSize(QSize(0, 30));
        leDrawingAcceleration->setMaximumSize(QSize(150, 16777215));

        gridLayout_22->addWidget(leDrawingAcceleration, 7, 1, 1, 1);

        label_102 = new QLabel(scrollAreaWidgetContents_6);
        label_102->setObjectName(QString::fromUtf8("label_102"));
        sizePolicy.setHeightForWidth(label_102->sizePolicy().hasHeightForWidth());
        label_102->setSizePolicy(sizePolicy);
        label_102->setMinimumSize(QSize(0, 0));
        label_102->setFont(font11);
        label_102->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_102, 7, 2, 1, 1);

        label_93 = new QLabel(scrollAreaWidgetContents_6);
        label_93->setObjectName(QString::fromUtf8("label_93"));
        QSizePolicy sizePolicy15(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy15.setHorizontalStretch(0);
        sizePolicy15.setVerticalStretch(0);
        sizePolicy15.setHeightForWidth(label_93->sizePolicy().hasHeightForWidth());
        label_93->setSizePolicy(sizePolicy15);
        label_93->setMinimumSize(QSize(0, 0));
        label_93->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_93, 0, 0, 1, 1);

        label_95 = new QLabel(scrollAreaWidgetContents_6);
        label_95->setObjectName(QString::fromUtf8("label_95"));
        sizePolicy4.setHeightForWidth(label_95->sizePolicy().hasHeightForWidth());
        label_95->setSizePolicy(sizePolicy4);
        label_95->setMinimumSize(QSize(0, 0));
        label_95->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_95, 3, 0, 1, 1);

        label_100 = new QLabel(scrollAreaWidgetContents_6);
        label_100->setObjectName(QString::fromUtf8("label_100"));
        sizePolicy.setHeightForWidth(label_100->sizePolicy().hasHeightForWidth());
        label_100->setSizePolicy(sizePolicy);
        label_100->setMinimumSize(QSize(0, 0));
        label_100->setFont(font11);
        label_100->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_100, 4, 2, 1, 1);

        label_98 = new QLabel(scrollAreaWidgetContents_6);
        label_98->setObjectName(QString::fromUtf8("label_98"));
        sizePolicy4.setHeightForWidth(label_98->sizePolicy().hasHeightForWidth());
        label_98->setSizePolicy(sizePolicy4);
        label_98->setMinimumSize(QSize(0, 0));
        label_98->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_98, 7, 0, 1, 1);

        leDrawingSpeed = new QLineEdit(scrollAreaWidgetContents_6);
        leDrawingSpeed->setObjectName(QString::fromUtf8("leDrawingSpeed"));
        leDrawingSpeed->setMinimumSize(QSize(0, 30));
        leDrawingSpeed->setMaximumSize(QSize(150, 16777215));

        gridLayout_22->addWidget(leDrawingSpeed, 6, 1, 1, 1);

        label_99 = new QLabel(scrollAreaWidgetContents_6);
        label_99->setObjectName(QString::fromUtf8("label_99"));
        sizePolicy.setHeightForWidth(label_99->sizePolicy().hasHeightForWidth());
        label_99->setSizePolicy(sizePolicy);
        label_99->setMinimumSize(QSize(0, 0));
        label_99->setFont(font11);
        label_99->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_99, 3, 2, 1, 1);

        label_23 = new QLabel(scrollAreaWidgetContents_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font5);
        label_23->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_23, 2, 0, 1, 1);

        leSpace = new QLineEdit(scrollAreaWidgetContents_6);
        leSpace->setObjectName(QString::fromUtf8("leSpace"));
        leSpace->setMinimumSize(QSize(0, 30));
        leSpace->setMaximumSize(QSize(150, 16777215));

        gridLayout_22->addWidget(leSpace, 2, 1, 1, 1);

        label_103 = new QLabel(scrollAreaWidgetContents_6);
        label_103->setObjectName(QString::fromUtf8("label_103"));
        sizePolicy.setHeightForWidth(label_103->sizePolicy().hasHeightForWidth());
        label_103->setSizePolicy(sizePolicy);
        label_103->setMinimumSize(QSize(0, 0));
        label_103->setFont(font11);
        label_103->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_103, 2, 2, 1, 1);


        verticalLayout_37->addLayout(gridLayout_22);


        verticalLayout_38->addLayout(verticalLayout_37);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_38->addItem(verticalSpacer_6);

        scrollArea_6->setWidget(scrollAreaWidgetContents_6);

        verticalLayout_26->addWidget(scrollArea_6);

        twModule->addTab(tDrawing, QString());
        TermiteTab = new QWidget();
        TermiteTab->setObjectName(QString::fromUtf8("TermiteTab"));
        verticalLayout_11 = new QVBoxLayout(TermiteTab);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        scrollArea_7 = new QScrollArea(TermiteTab);
        scrollArea_7->setObjectName(QString::fromUtf8("scrollArea_7"));
        scrollArea_7->setWidgetResizable(true);
        scrollAreaWidgetContents_7 = new QWidget();
        scrollAreaWidgetContents_7->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_7"));
        scrollAreaWidgetContents_7->setGeometry(QRect(0, 0, 492, 513));
        verticalLayout_27 = new QVBoxLayout(scrollAreaWidgetContents_7);
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setContentsMargins(11, 11, 11, 11);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        teDebug = new QTextEdit(scrollAreaWidgetContents_7);
        teDebug->setObjectName(QString::fromUtf8("teDebug"));
        QFont font12;
        font12.setBold(false);
        font12.setItalic(false);
        font12.setWeight(50);
        font12.setKerning(true);
        teDebug->setFont(font12);
        teDebug->setStyleSheet(QString::fromUtf8("color: rgb(255, 82, 87);"));

        gridLayout_4->addWidget(teDebug, 0, 1, 1, 1);

        label_4 = new QLabel(scrollAreaWidgetContents_7);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        label_5 = new QLabel(scrollAreaWidgetContents_7);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        leTerminal = new QLineEdit(scrollAreaWidgetContents_7);
        leTerminal->setObjectName(QString::fromUtf8("leTerminal"));
        leTerminal->setMinimumSize(QSize(0, 30));

        gridLayout_4->addWidget(leTerminal, 1, 1, 1, 1);

        cbDeviceSender = new QComboBox(scrollAreaWidgetContents_7);
        cbDeviceSender->addItem(QString());
        cbDeviceSender->addItem(QString());
        cbDeviceSender->addItem(QString());
        cbDeviceSender->addItem(QString());
        cbDeviceSender->addItem(QString());
        cbDeviceSender->addItem(QString());
        cbDeviceSender->setObjectName(QString::fromUtf8("cbDeviceSender"));

        gridLayout_4->addWidget(cbDeviceSender, 1, 2, 1, 1);


        verticalLayout_27->addLayout(gridLayout_4);

        scrollArea_7->setWidget(scrollAreaWidgetContents_7);

        verticalLayout_11->addWidget(scrollArea_7);

        twModule->addTab(TermiteTab, QString());

        ModuleTabManagerLayout->addWidget(twModule);

        splitter_2->addWidget(ModuleTabManagerWidget);
        DeviceTabManagerWidget = new QWidget(splitter_2);
        DeviceTabManagerWidget->setObjectName(QString::fromUtf8("DeviceTabManagerWidget"));
        DeviceTabManagerWidget->setMinimumSize(QSize(0, 0));
        DeviceTabManagerWidget->setMaximumSize(QSize(900, 16777215));
        DeviceTabManagerWidget->setStyleSheet(QString::fromUtf8(""));
        GeometryTabManagerLayout = new QVBoxLayout(DeviceTabManagerWidget);
        GeometryTabManagerLayout->setSpacing(0);
        GeometryTabManagerLayout->setContentsMargins(11, 11, 11, 11);
        GeometryTabManagerLayout->setObjectName(QString::fromUtf8("GeometryTabManagerLayout"));
        GeometryTabManagerLayout->setContentsMargins(0, 0, 0, 0);
        twDevices = new QTabWidget(DeviceTabManagerWidget);
        twDevices->setObjectName(QString::fromUtf8("twDevices"));
        twDevices->setMinimumSize(QSize(0, 0));
        twDevices->setFont(font3);
        twDevices->setStyleSheet(QString::fromUtf8(""));
        twDevices->setTabPosition(QTabWidget::North);
        twDevices->setElideMode(Qt::ElideNone);
        twDevices->setTabsClosable(false);
        tRobot = new QWidget();
        tRobot->setObjectName(QString::fromUtf8("tRobot"));
        verticalLayout_4 = new QVBoxLayout(tRobot);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea_2 = new QScrollArea(tRobot);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        wgJoggingScrollWidget = new QWidget();
        wgJoggingScrollWidget->setObjectName(QString::fromUtf8("wgJoggingScrollWidget"));
        wgJoggingScrollWidget->setGeometry(QRect(0, 0, 607, 800));
        wgJoggingScrollWidget->setMinimumSize(QSize(0, 800));
        wgJoggingScrollWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_5 = new QVBoxLayout(wgJoggingScrollWidget);
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, 10, 5, 0);
        groupRobotConnection = new QFrame(wgJoggingScrollWidget);
        groupRobotConnection->setObjectName(QString::fromUtf8("groupRobotConnection"));
        sizePolicy10.setHeightForWidth(groupRobotConnection->sizePolicy().hasHeightForWidth());
        groupRobotConnection->setSizePolicy(sizePolicy10);
        groupRobotConnection->setMaximumSize(QSize(16777215, 16777215));
        groupRobotConnection->setFont(font8);
        groupRobotConnection->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_14 = new QHBoxLayout(groupRobotConnection);
        horizontalLayout_14->setSpacing(5);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(30, 0, -1, 5);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        pbConnect = new QPushButton(groupRobotConnection);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));
        pbConnect->setMinimumSize(QSize(0, 30));
        pbConnect->setFont(font10);
        pbConnect->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	background-color: rgb(36, 36, 36);\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"}\n"
"QPushButton:hover\n"
"{\n"
"	\n"
"	background-color: rgb(129, 129, 129);\n"
"}\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(41, 155, 255);\n"
"}\n"
""));
        QIcon icon37;
        icon37.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/disconnected.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon37.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/connected.png"), QSize(), QIcon::Normal, QIcon::On);
        pbConnect->setIcon(icon37);
        pbConnect->setIconSize(QSize(30, 20));
        pbConnect->setCheckable(true);

        verticalLayout_12->addWidget(pbConnect);

        cbAutoConnect = new QCheckBox(groupRobotConnection);
        cbAutoConnect->setObjectName(QString::fromUtf8("cbAutoConnect"));
        cbAutoConnect->setFont(font8);
        cbAutoConnect->setStyleSheet(QString::fromUtf8(""));
        cbAutoConnect->setChecked(true);

        verticalLayout_12->addWidget(cbAutoConnect);


        horizontalLayout_14->addLayout(verticalLayout_12);

        fRobotPosition = new QFrame(groupRobotConnection);
        fRobotPosition->setObjectName(QString::fromUtf8("fRobotPosition"));
        fRobotPosition->setMinimumSize(QSize(0, 40));
        fRobotPosition->setMaximumSize(QSize(16777215, 16777215));
        fRobotPosition->setStyleSheet(QString::fromUtf8("QLabel\n"
"{	\n"
"	background-color: rgb(239, 252, 255);\n"
"	color: rgb(33, 125, 206)\n"
"}"));
        gridLayout_19 = new QGridLayout(fRobotPosition);
        gridLayout_19->setSpacing(7);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        gridLayout_19->setContentsMargins(0, 0, -1, 0);
        lbY = new QLabel(fRobotPosition);
        lbY->setObjectName(QString::fromUtf8("lbY"));
        lbY->setMinimumSize(QSize(30, 20));
        lbY->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbY, 1, 5, 1, 1);

        label_88 = new QLabel(fRobotPosition);
        label_88->setObjectName(QString::fromUtf8("label_88"));
        label_88->setMinimumSize(QSize(0, 20));
        label_88->setFont(font2);
        label_88->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_88, 0, 6, 1, 1);

        lbW = new QLabel(fRobotPosition);
        lbW->setObjectName(QString::fromUtf8("lbW"));
        lbW->setMinimumSize(QSize(30, 20));
        lbW->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbW, 1, 7, 1, 1);

        lbV = new QLabel(fRobotPosition);
        lbV->setObjectName(QString::fromUtf8("lbV"));
        lbV->setMinimumSize(QSize(30, 20));
        lbV->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbV, 1, 9, 1, 1);

        lbU = new QLabel(fRobotPosition);
        lbU->setObjectName(QString::fromUtf8("lbU"));
        lbU->setMinimumSize(QSize(30, 20));
        lbU->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbU, 1, 8, 1, 1);

        label_94 = new QLabel(fRobotPosition);
        label_94->setObjectName(QString::fromUtf8("label_94"));
        label_94->setMinimumSize(QSize(0, 20));
        label_94->setFont(font2);
        label_94->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_94, 0, 9, 1, 1);

        lbX = new QLabel(fRobotPosition);
        lbX->setObjectName(QString::fromUtf8("lbX"));
        lbX->setMinimumSize(QSize(30, 20));
        lbX->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbX, 1, 4, 1, 1);

        lbZ = new QLabel(fRobotPosition);
        lbZ->setObjectName(QString::fromUtf8("lbZ"));
        lbZ->setMinimumSize(QSize(30, 20));
        lbZ->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbZ, 1, 6, 1, 1);

        label_90 = new QLabel(fRobotPosition);
        label_90->setObjectName(QString::fromUtf8("label_90"));
        label_90->setMinimumSize(QSize(0, 20));
        label_90->setFont(font2);
        label_90->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_90, 0, 7, 1, 1);

        label_86 = new QLabel(fRobotPosition);
        label_86->setObjectName(QString::fromUtf8("label_86"));
        label_86->setMinimumSize(QSize(0, 20));
        label_86->setFont(font2);
        label_86->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_86, 0, 5, 1, 1);

        label_92 = new QLabel(fRobotPosition);
        label_92->setObjectName(QString::fromUtf8("label_92"));
        label_92->setMinimumSize(QSize(0, 20));
        label_92->setFont(font2);
        label_92->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_92, 0, 8, 1, 1);

        label_84 = new QLabel(fRobotPosition);
        label_84->setObjectName(QString::fromUtf8("label_84"));
        label_84->setMinimumSize(QSize(0, 20));
        label_84->setFont(font2);
        label_84->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_84, 0, 4, 1, 1);

        cbSelectedRobot = new QComboBox(fRobotPosition);
        cbSelectedRobot->addItem(QString());
        cbSelectedRobot->addItem(QString());
        cbSelectedRobot->addItem(QString());
        cbSelectedRobot->addItem(QString());
        cbSelectedRobot->setObjectName(QString::fromUtf8("cbSelectedRobot"));
        sizePolicy6.setHeightForWidth(cbSelectedRobot->sizePolicy().hasHeightForWidth());
        cbSelectedRobot->setSizePolicy(sizePolicy6);

        gridLayout_19->addWidget(cbSelectedRobot, 1, 3, 1, 1);

        label = new QLabel(fRobotPosition);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label, 0, 3, 1, 1);


        horizontalLayout_14->addWidget(fRobotPosition);

        tbDisableRobot = new QToolButton(groupRobotConnection);
        tbDisableRobot->setObjectName(QString::fromUtf8("tbDisableRobot"));
        sizePolicy.setHeightForWidth(tbDisableRobot->sizePolicy().hasHeightForWidth());
        tbDisableRobot->setSizePolicy(sizePolicy);
        tbDisableRobot->setMinimumSize(QSize(20, 20));
        QIcon icon38;
        icon38.addFile(QString::fromUtf8(":/icon/icons8_switch_off_52px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon38.addFile(QString::fromUtf8(":/icon/icons8_switch_on_52px.png"), QSize(), QIcon::Normal, QIcon::On);
        icon38.addFile(QString::fromUtf8(":/icon/icons8_switch_on_52px.png"), QSize(), QIcon::Active, QIcon::On);
        tbDisableRobot->setIcon(icon38);
        tbDisableRobot->setIconSize(QSize(32, 32));
        tbDisableRobot->setCheckable(true);
        tbDisableRobot->setChecked(true);
        tbDisableRobot->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbDisableRobot->setAutoRaise(true);

        horizontalLayout_14->addWidget(tbDisableRobot);

        tbRequestPosition = new QToolButton(groupRobotConnection);
        tbRequestPosition->setObjectName(QString::fromUtf8("tbRequestPosition"));
        sizePolicy.setHeightForWidth(tbRequestPosition->sizePolicy().hasHeightForWidth());
        tbRequestPosition->setSizePolicy(sizePolicy);
        tbRequestPosition->setMinimumSize(QSize(20, 20));
        QIcon icon39;
        icon39.addFile(QString::fromUtf8(":/icon/icons8_my_location_52px_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbRequestPosition->setIcon(icon39);
        tbRequestPosition->setIconSize(QSize(32, 32));
        tbRequestPosition->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbRequestPosition->setAutoRaise(true);

        horizontalLayout_14->addWidget(tbRequestPosition);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_4);

        frameRobotConnection = new QFrame(groupRobotConnection);
        frameRobotConnection->setObjectName(QString::fromUtf8("frameRobotConnection"));
        frameRobotConnection->setMinimumSize(QSize(0, 50));
        frameRobotConnection->setMaximumSize(QSize(16777215, 50));
        frameRobotConnection->setFont(font12);
        frameRobotConnection->setStyleSheet(QString::fromUtf8("border: none;"));
        frameRobotConnection->setFrameShape(QFrame::StyledPanel);
        frameRobotConnection->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(frameRobotConnection);
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);

        horizontalLayout_14->addWidget(frameRobotConnection);


        verticalLayout_5->addWidget(groupRobotConnection);

        RobotTabWidget = new QTabWidget(wgJoggingScrollWidget);
        RobotTabWidget->setObjectName(QString::fromUtf8("RobotTabWidget"));
        RobotTabWidget->setMinimumSize(QSize(0, 300));
        ConfigurationTab = new QWidget();
        ConfigurationTab->setObjectName(QString::fromUtf8("ConfigurationTab"));
        layoutWidget = new QWidget(ConfigurationTab);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 15, 201, 101));
        gridLayout_31 = new QGridLayout(layoutWidget);
        gridLayout_31->setSpacing(6);
        gridLayout_31->setContentsMargins(11, 11, 11, 11);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        gridLayout_31->setContentsMargins(0, 0, 0, 0);
        lbComName = new QLabel(layoutWidget);
        lbComName->setObjectName(QString::fromUtf8("lbComName"));
        lbComName->setFont(font8);
        lbComName->setStyleSheet(QString::fromUtf8(""));

        gridLayout_31->addWidget(lbComName, 3, 1, 1, 1);

        cbRobotModel = new QComboBox(layoutWidget);
        cbRobotModel->addItem(QString());
        cbRobotModel->addItem(QString());
        cbRobotModel->addItem(QString());
        cbRobotModel->addItem(QString());
        cbRobotModel->setObjectName(QString::fromUtf8("cbRobotModel"));
        cbRobotModel->setMinimumSize(QSize(80, 0));

        gridLayout_31->addWidget(cbRobotModel, 1, 1, 1, 1);

        label_65 = new QLabel(layoutWidget);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        label_65->setFont(font2);
        label_65->setAlignment(Qt::AlignCenter);

        gridLayout_31->addWidget(label_65, 4, 0, 1, 1);

        lbBaudrate = new QLabel(layoutWidget);
        lbBaudrate->setObjectName(QString::fromUtf8("lbBaudrate"));
        lbBaudrate->setFont(font8);
        lbBaudrate->setStyleSheet(QString::fromUtf8(""));

        gridLayout_31->addWidget(lbBaudrate, 4, 1, 1, 1);

        label_91 = new QLabel(layoutWidget);
        label_91->setObjectName(QString::fromUtf8("label_91"));
        label_91->setFont(font2);
        label_91->setAlignment(Qt::AlignCenter);

        gridLayout_31->addWidget(label_91, 1, 0, 1, 1);

        label_113 = new QLabel(layoutWidget);
        label_113->setObjectName(QString::fromUtf8("label_113"));
        label_113->setFont(font2);
        label_113->setAlignment(Qt::AlignCenter);

        gridLayout_31->addWidget(label_113, 2, 0, 1, 1);

        label_10 = new QLabel(layoutWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font2);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_31->addWidget(label_10, 3, 0, 1, 1);

        cbRobotDOF = new QComboBox(layoutWidget);
        cbRobotDOF->addItem(QString());
        cbRobotDOF->addItem(QString());
        cbRobotDOF->addItem(QString());
        cbRobotDOF->addItem(QString());
        cbRobotDOF->setObjectName(QString::fromUtf8("cbRobotDOF"));
        cbRobotDOF->setMinimumSize(QSize(80, 0));

        gridLayout_31->addWidget(cbRobotDOF, 2, 1, 1, 1);

        RobotTabWidget->addTab(ConfigurationTab, QString());
        MoveTab = new QWidget();
        MoveTab->setObjectName(QString::fromUtf8("MoveTab"));
        verticalLayout_53 = new QVBoxLayout(MoveTab);
        verticalLayout_53->setSpacing(6);
        verticalLayout_53->setContentsMargins(11, 11, 11, 11);
        verticalLayout_53->setObjectName(QString::fromUtf8("verticalLayout_53"));
        tabWidget_2 = new QTabWidget(MoveTab);
        tabWidget_2->setObjectName(QString::fromUtf8("tabWidget_2"));
        tabWidget_2->setStyleSheet(QString::fromUtf8("QFrame#ButtonGroupFrame{\n"
"	border: 1px solid rgb(118, 118, 118);\n"
"	border-radius: 5px;\n"
"}"));
        tabWidget_2->setTabPosition(QTabWidget::North);
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        verticalLayout_16 = new QVBoxLayout(tab_4);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        framePositionParameter = new QFrame(tab_4);
        framePositionParameter->setObjectName(QString::fromUtf8("framePositionParameter"));
        framePositionParameter->setMaximumSize(QSize(460, 16777215));
        framePositionParameter->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	border: 1px solid rgb(206, 206, 206);\n"
"}\n"
"QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        gridLayout_5 = new QGridLayout(framePositionParameter);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 0, 5, 0);
        label_106 = new QLabel(framePositionParameter);
        label_106->setObjectName(QString::fromUtf8("label_106"));
        label_106->setFont(font6);

        horizontalLayout_2->addWidget(label_106);

        pbsubY = new QPushButton(framePositionParameter);
        pbsubY->setObjectName(QString::fromUtf8("pbsubY"));
        pbsubY->setMinimumSize(QSize(20, 20));
        pbsubY->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(pbsubY);

        leY = new QLineEdit(framePositionParameter);
        leY->setObjectName(QString::fromUtf8("leY"));
        leY->setMinimumSize(QSize(50, 30));
        leY->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_2->addWidget(leY);

        pbplusY = new QPushButton(framePositionParameter);
        pbplusY->setObjectName(QString::fromUtf8("pbplusY"));
        pbplusY->setMinimumSize(QSize(20, 20));
        pbplusY->setMaximumSize(QSize(20, 20));

        horizontalLayout_2->addWidget(pbplusY);

        label_9 = new QLabel(framePositionParameter);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(label_9);


        gridLayout_5->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 0, 5, 0);
        label_40 = new QLabel(framePositionParameter);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setFont(font6);

        horizontalLayout->addWidget(label_40);

        pbsubX = new QPushButton(framePositionParameter);
        pbsubX->setObjectName(QString::fromUtf8("pbsubX"));
        pbsubX->setMinimumSize(QSize(20, 20));
        pbsubX->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(pbsubX);

        leX = new QLineEdit(framePositionParameter);
        leX->setObjectName(QString::fromUtf8("leX"));
        leX->setMinimumSize(QSize(20, 30));
        leX->setMaximumSize(QSize(70, 16777215));

        horizontalLayout->addWidget(leX);

        pbplusX = new QPushButton(framePositionParameter);
        pbplusX->setObjectName(QString::fromUtf8("pbplusX"));
        pbplusX->setMinimumSize(QSize(20, 20));
        pbplusX->setMaximumSize(QSize(20, 20));

        horizontalLayout->addWidget(pbplusX);

        label_8 = new QLabel(framePositionParameter);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setMaximumSize(QSize(30, 16777215));

        horizontalLayout->addWidget(label_8);


        gridLayout_5->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 0, 5, 0);
        label_107 = new QLabel(framePositionParameter);
        label_107->setObjectName(QString::fromUtf8("label_107"));
        label_107->setFont(font6);

        horizontalLayout_3->addWidget(label_107);

        pbsubZ = new QPushButton(framePositionParameter);
        pbsubZ->setObjectName(QString::fromUtf8("pbsubZ"));
        pbsubZ->setMinimumSize(QSize(20, 20));
        pbsubZ->setMaximumSize(QSize(20, 20));

        horizontalLayout_3->addWidget(pbsubZ);

        leZ = new QLineEdit(framePositionParameter);
        leZ->setObjectName(QString::fromUtf8("leZ"));
        leZ->setMinimumSize(QSize(50, 30));
        leZ->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_3->addWidget(leZ);

        pbplusZ = new QPushButton(framePositionParameter);
        pbplusZ->setObjectName(QString::fromUtf8("pbplusZ"));
        pbplusZ->setMinimumSize(QSize(20, 20));
        pbplusZ->setMaximumSize(QSize(20, 20));

        horizontalLayout_3->addWidget(pbplusZ);

        label_66 = new QLabel(framePositionParameter);
        label_66->setObjectName(QString::fromUtf8("label_66"));
        label_66->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_3->addWidget(label_66);


        gridLayout_5->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 0, 5, 0);
        label_108 = new QLabel(framePositionParameter);
        label_108->setObjectName(QString::fromUtf8("label_108"));
        label_108->setFont(font6);

        horizontalLayout_4->addWidget(label_108);

        pbsubW = new QPushButton(framePositionParameter);
        pbsubW->setObjectName(QString::fromUtf8("pbsubW"));
        pbsubW->setMinimumSize(QSize(20, 20));
        pbsubW->setMaximumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(pbsubW);

        leW = new QLineEdit(framePositionParameter);
        leW->setObjectName(QString::fromUtf8("leW"));
        leW->setMinimumSize(QSize(50, 30));
        leW->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_4->addWidget(leW);

        pbplusW = new QPushButton(framePositionParameter);
        pbplusW->setObjectName(QString::fromUtf8("pbplusW"));
        pbplusW->setMinimumSize(QSize(20, 20));
        pbplusW->setMaximumSize(QSize(20, 20));

        horizontalLayout_4->addWidget(pbplusW);

        label_81 = new QLabel(framePositionParameter);
        label_81->setObjectName(QString::fromUtf8("label_81"));
        label_81->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_4->addWidget(label_81);


        gridLayout_5->addLayout(horizontalLayout_4, 0, 1, 1, 1);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(10);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        horizontalLayout_32->setContentsMargins(5, 0, 5, 0);
        label_111 = new QLabel(framePositionParameter);
        label_111->setObjectName(QString::fromUtf8("label_111"));
        label_111->setFont(font6);

        horizontalLayout_32->addWidget(label_111);

        pbsubU = new QPushButton(framePositionParameter);
        pbsubU->setObjectName(QString::fromUtf8("pbsubU"));
        pbsubU->setMinimumSize(QSize(20, 20));
        pbsubU->setMaximumSize(QSize(20, 20));

        horizontalLayout_32->addWidget(pbsubU);

        leU = new QLineEdit(framePositionParameter);
        leU->setObjectName(QString::fromUtf8("leU"));
        leU->setMinimumSize(QSize(50, 30));
        leU->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_32->addWidget(leU);

        pbplusU = new QPushButton(framePositionParameter);
        pbplusU->setObjectName(QString::fromUtf8("pbplusU"));
        pbplusU->setMinimumSize(QSize(20, 20));
        pbplusU->setMaximumSize(QSize(20, 20));

        horizontalLayout_32->addWidget(pbplusU);

        label_87 = new QLabel(framePositionParameter);
        label_87->setObjectName(QString::fromUtf8("label_87"));
        label_87->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_32->addWidget(label_87);


        gridLayout_5->addLayout(horizontalLayout_32, 1, 1, 1, 1);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(10);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        horizontalLayout_33->setContentsMargins(5, 0, 5, 0);
        label_112 = new QLabel(framePositionParameter);
        label_112->setObjectName(QString::fromUtf8("label_112"));
        label_112->setFont(font6);

        horizontalLayout_33->addWidget(label_112);

        pbsubV = new QPushButton(framePositionParameter);
        pbsubV->setObjectName(QString::fromUtf8("pbsubV"));
        pbsubV->setMinimumSize(QSize(20, 20));
        pbsubV->setMaximumSize(QSize(20, 20));

        horizontalLayout_33->addWidget(pbsubV);

        leV = new QLineEdit(framePositionParameter);
        leV->setObjectName(QString::fromUtf8("leV"));
        leV->setMinimumSize(QSize(50, 30));
        leV->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_33->addWidget(leV);

        pbplusV = new QPushButton(framePositionParameter);
        pbplusV->setObjectName(QString::fromUtf8("pbplusV"));
        pbplusV->setMinimumSize(QSize(20, 20));
        pbplusV->setMaximumSize(QSize(20, 20));

        horizontalLayout_33->addWidget(pbplusV);

        label_89 = new QLabel(framePositionParameter);
        label_89->setObjectName(QString::fromUtf8("label_89"));
        label_89->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_33->addWidget(label_89);


        gridLayout_5->addLayout(horizontalLayout_33, 2, 1, 1, 1);


        verticalLayout_16->addWidget(framePositionParameter);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(10, -1, 0, -1);
        label_29 = new QLabel(tab_4);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_29, 0, 0, 1, 1);

        label_116 = new QLabel(tab_4);
        label_116->setObjectName(QString::fromUtf8("label_116"));
        label_116->setMaximumSize(QSize(60, 16777215));
        label_116->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_116, 1, 3, 1, 1);

        label_63 = new QLabel(tab_4);
        label_63->setObjectName(QString::fromUtf8("label_63"));
        label_63->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_63, 0, 5, 1, 1);

        leAccel = new QLineEdit(tab_4);
        leAccel->setObjectName(QString::fromUtf8("leAccel"));
        leAccel->setMinimumSize(QSize(0, 30));
        leAccel->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leAccel, 1, 1, 1, 1);

        label_32 = new QLabel(tab_4);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_32, 1, 2, 1, 1);

        label_117 = new QLabel(tab_4);
        label_117->setObjectName(QString::fromUtf8("label_117"));
        label_117->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_117, 1, 5, 1, 1);

        leVelocity = new QLineEdit(tab_4);
        leVelocity->setObjectName(QString::fromUtf8("leVelocity"));
        leVelocity->setMinimumSize(QSize(0, 30));
        leVelocity->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leVelocity, 0, 1, 1, 1);

        leStartSpeed = new QLineEdit(tab_4);
        leStartSpeed->setObjectName(QString::fromUtf8("leStartSpeed"));
        leStartSpeed->setMinimumSize(QSize(0, 30));
        leStartSpeed->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leStartSpeed, 0, 4, 1, 1);

        label_62 = new QLabel(tab_4);
        label_62->setObjectName(QString::fromUtf8("label_62"));
        label_62->setMaximumSize(QSize(60, 16777215));
        label_62->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_62, 0, 3, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_5, 5, 1, 1, 1);

        leEndSpeed = new QLineEdit(tab_4);
        leEndSpeed->setObjectName(QString::fromUtf8("leEndSpeed"));
        leEndSpeed->setMinimumSize(QSize(0, 30));
        leEndSpeed->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leEndSpeed, 1, 4, 1, 1);

        label_30 = new QLabel(tab_4);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_30, 0, 2, 1, 1);

        label_31 = new QLabel(tab_4);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_31, 1, 0, 1, 1);

        label_64 = new QLabel(tab_4);
        label_64->setObjectName(QString::fromUtf8("label_64"));
        label_64->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_64, 2, 2, 1, 1);

        label_47 = new QLabel(tab_4);
        label_47->setObjectName(QString::fromUtf8("label_47"));
        label_47->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_47, 2, 0, 1, 1);

        leEndSpeed_2 = new QLineEdit(tab_4);
        leEndSpeed_2->setObjectName(QString::fromUtf8("leEndSpeed_2"));
        leEndSpeed_2->setMinimumSize(QSize(0, 30));
        leEndSpeed_2->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leEndSpeed_2, 2, 1, 1, 1);


        verticalLayout_16->addLayout(gridLayout);

        tabWidget_2->addTab(tab_4, QString());
        ButtonTab = new QWidget();
        ButtonTab->setObjectName(QString::fromUtf8("ButtonTab"));
        cbDivision = new QComboBox(ButtonTab);
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->setObjectName(QString::fromUtf8("cbDivision"));
        cbDivision->setGeometry(QRect(115, 15, 51, 22));
        cbDivision->setMinimumSize(QSize(0, 20));
        cbDivision->setMaximumSize(QSize(100, 16777215));
        cbDivision->setSizeAdjustPolicy(QComboBox::AdjustToContents);
        pbHome = new QToolButton(ButtonTab);
        pbHome->setObjectName(QString::fromUtf8("pbHome"));
        pbHome->setGeometry(QRect(15, 45, 60, 76));
        pbHome->setMinimumSize(QSize(60, 60));
        pbHome->setFont(font4);
        QIcon icon40;
        icon40.addFile(QString::fromUtf8(":/icon/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbHome->setIcon(icon40);
        pbHome->setIconSize(QSize(40, 40));
        pbHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        label_33 = new QLabel(ButtonTab);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(20, 15, 86, 19));
        label_33->setMaximumSize(QSize(120, 16777215));
        layoutWidget1 = new QWidget(ButtonTab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(75, 45, 209, 147));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setSpacing(5);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        pbLeft = new QToolButton(layoutWidget1);
        pbLeft->setObjectName(QString::fromUtf8("pbLeft"));
        QIcon icon41;
        icon41.addFile(QString::fromUtf8(":/icon/icons8-back-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLeft->setIcon(icon41);
        pbLeft->setIconSize(QSize(40, 40));
        pbLeft->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbLeft, 0, 2, 2, 1);

        pbRight = new QToolButton(layoutWidget1);
        pbRight->setObjectName(QString::fromUtf8("pbRight"));
        QIcon icon42;
        icon42.addFile(QString::fromUtf8(":/icon/icons8-forward-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRight->setIcon(icon42);
        pbRight->setIconSize(QSize(40, 40));
        pbRight->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbRight, 0, 4, 2, 1);

        pbBackward = new QToolButton(layoutWidget1);
        pbBackward->setObjectName(QString::fromUtf8("pbBackward"));
        QIcon icon43;
        icon43.addFile(QString::fromUtf8(":/icon/icons8-expand-arrow-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbBackward->setIcon(icon43);
        pbBackward->setIconSize(QSize(40, 40));
        pbBackward->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbBackward, 1, 3, 1, 1);

        pbForward = new QToolButton(layoutWidget1);
        pbForward->setObjectName(QString::fromUtf8("pbForward"));
        pbForward->setStyleSheet(QString::fromUtf8(""));
        QIcon icon44;
        icon44.addFile(QString::fromUtf8(":/icon/icons8-collapse-arrow-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbForward->setIcon(icon44);
        pbForward->setIconSize(QSize(40, 40));
        pbForward->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbForward, 0, 3, 1, 1);

        pbSubRoll = new QToolButton(ButtonTab);
        pbSubRoll->setObjectName(QString::fromUtf8("pbSubRoll"));
        pbSubRoll->setGeometry(QRect(80, 205, 48, 70));
        pbSubRoll->setIcon(icon41);
        pbSubRoll->setIconSize(QSize(40, 40));
        pbSubRoll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbPlusRoll = new QToolButton(ButtonTab);
        pbPlusRoll->setObjectName(QString::fromUtf8("pbPlusRoll"));
        pbPlusRoll->setGeometry(QRect(80, 285, 48, 70));
        pbPlusRoll->setIcon(icon42);
        pbPlusRoll->setIconSize(QSize(40, 40));
        pbPlusRoll->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbPlusYaw = new QToolButton(ButtonTab);
        pbPlusYaw->setObjectName(QString::fromUtf8("pbPlusYaw"));
        pbPlusYaw->setGeometry(QRect(155, 285, 48, 70));
        pbPlusYaw->setIcon(icon42);
        pbPlusYaw->setIconSize(QSize(40, 40));
        pbPlusYaw->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbSubYaw = new QToolButton(ButtonTab);
        pbSubYaw->setObjectName(QString::fromUtf8("pbSubYaw"));
        pbSubYaw->setGeometry(QRect(155, 205, 48, 70));
        pbSubYaw->setIcon(icon41);
        pbSubYaw->setIconSize(QSize(40, 40));
        pbSubYaw->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbPlusPitch = new QToolButton(ButtonTab);
        pbPlusPitch->setObjectName(QString::fromUtf8("pbPlusPitch"));
        pbPlusPitch->setGeometry(QRect(230, 285, 48, 70));
        pbPlusPitch->setIcon(icon42);
        pbPlusPitch->setIconSize(QSize(40, 40));
        pbPlusPitch->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbSubPitch = new QToolButton(ButtonTab);
        pbSubPitch->setObjectName(QString::fromUtf8("pbSubPitch"));
        pbSubPitch->setGeometry(QRect(230, 205, 48, 70));
        pbSubPitch->setIcon(icon41);
        pbSubPitch->setIconSize(QSize(40, 40));
        pbSubPitch->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDown = new QToolButton(ButtonTab);
        pbDown->setObjectName(QString::fromUtf8("pbDown"));
        pbDown->setGeometry(QRect(315, 120, 48, 67));
        pbDown->setIcon(icon43);
        pbDown->setIconSize(QSize(40, 40));
        pbDown->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbUp = new QToolButton(ButtonTab);
        pbUp->setObjectName(QString::fromUtf8("pbUp"));
        pbUp->setGeometry(QRect(315, 45, 48, 67));
        pbUp->setIcon(icon44);
        pbUp->setIconSize(QSize(40, 40));
        pbUp->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbUp->setAutoRaise(false);
        tabWidget_2->addTab(ButtonTab, QString());
        SliderTab = new QWidget();
        SliderTab->setObjectName(QString::fromUtf8("SliderTab"));
        verticalLayout_55 = new QVBoxLayout(SliderTab);
        verticalLayout_55->setSpacing(6);
        verticalLayout_55->setContentsMargins(11, 11, 11, 11);
        verticalLayout_55->setObjectName(QString::fromUtf8("verticalLayout_55"));
        scrollArea_3 = new QScrollArea(SliderTab);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 135, 300));
        scrollAreaWidgetContents_3->setMinimumSize(QSize(0, 300));
        scrollAreaWidgetContents_3->setMaximumSize(QSize(16777215, 600));
        verticalLayout_44 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_44->setSpacing(6);
        verticalLayout_44->setContentsMargins(11, 11, 11, 11);
        verticalLayout_44->setObjectName(QString::fromUtf8("verticalLayout_44"));
        frame = new QFrame(scrollAreaWidgetContents_3);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(200, 16777215));
        gridLayout_10 = new QGridLayout(frame);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        label_53 = new QLabel(frame);
        label_53->setObjectName(QString::fromUtf8("label_53"));
        label_53->setMaximumSize(QSize(40, 16777215));

        gridLayout_10->addWidget(label_53, 1, 0, 1, 1);

        cbWorkingSize = new QComboBox(frame);
        cbWorkingSize->addItem(QString());
        cbWorkingSize->addItem(QString());
        cbWorkingSize->addItem(QString());
        cbWorkingSize->addItem(QString());
        cbWorkingSize->setObjectName(QString::fromUtf8("cbWorkingSize"));
        cbWorkingSize->setMinimumSize(QSize(60, 0));
        cbWorkingSize->setMaximumSize(QSize(100, 16777215));

        gridLayout_10->addWidget(cbWorkingSize, 1, 1, 1, 1);


        verticalLayout_44->addWidget(frame);

        fXYWorkingArea = new QWidget(scrollAreaWidgetContents_3);
        fXYWorkingArea->setObjectName(QString::fromUtf8("fXYWorkingArea"));
        fXYWorkingArea->setMinimumSize(QSize(0, 320));
        wg2D = new QWidget(fXYWorkingArea);
        wg2D->setObjectName(QString::fromUtf8("wg2D"));
        wg2D->setGeometry(QRect(30, 5, 200, 200));
        sizePolicy13.setHeightForWidth(wg2D->sizePolicy().hasHeightForWidth());
        wg2D->setSizePolicy(sizePolicy13);
        wg2D->setMinimumSize(QSize(200, 200));
        wg2D->setMaximumSize(QSize(16777215, 16777215));
        wg2D->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_15 = new QLabel(fXYWorkingArea);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(6, 210, 16, 19));
        QSizePolicy sizePolicy16(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy16.setHorizontalStretch(0);
        sizePolicy16.setVerticalStretch(0);
        sizePolicy16.setHeightForWidth(label_15->sizePolicy().hasHeightForWidth());
        label_15->setSizePolicy(sizePolicy16);
        vsZAdjsution = new QSlider(fXYWorkingArea);
        vsZAdjsution->setObjectName(QString::fromUtf8("vsZAdjsution"));
        vsZAdjsution->setGeometry(QRect(6, 6, 16, 201));
        sizePolicy7.setHeightForWidth(vsZAdjsution->sizePolicy().hasHeightForWidth());
        vsZAdjsution->setSizePolicy(sizePolicy7);
        vsZAdjsution->setMaximum(300);
        vsZAdjsution->setOrientation(Qt::Vertical);
        layoutWidget2 = new QWidget(fXYWorkingArea);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(255, 10, 102, 296));
        gridLayout_17 = new QGridLayout(layoutWidget2);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        gridLayout_17->setContentsMargins(0, 0, 0, 0);
        label_72 = new QLabel(layoutWidget2);
        label_72->setObjectName(QString::fromUtf8("label_72"));
        label_72->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_72, 5, 0, 1, 1);

        d5axis = new QDial(layoutWidget2);
        d5axis->setObjectName(QString::fromUtf8("d5axis"));
        d5axis->setMinimum(-180);
        d5axis->setMaximum(180);
        d5axis->setOrientation(Qt::Horizontal);
        d5axis->setInvertedAppearance(false);
        d5axis->setInvertedControls(false);
        d5axis->setWrapping(false);
        d5axis->setNotchesVisible(false);

        gridLayout_17->addWidget(d5axis, 2, 0, 1, 1);

        d6axis = new QDial(layoutWidget2);
        d6axis->setObjectName(QString::fromUtf8("d6axis"));
        d6axis->setMinimum(-180);
        d6axis->setMaximum(180);
        d6axis->setOrientation(Qt::Horizontal);
        d6axis->setInvertedAppearance(false);
        d6axis->setInvertedControls(false);
        d6axis->setWrapping(false);
        d6axis->setNotchesVisible(false);

        gridLayout_17->addWidget(d6axis, 4, 0, 1, 1);

        label_69 = new QLabel(layoutWidget2);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_69, 1, 0, 1, 1);

        label_71 = new QLabel(layoutWidget2);
        label_71->setObjectName(QString::fromUtf8("label_71"));
        label_71->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_71, 3, 0, 1, 1);

        d4axis = new QDial(layoutWidget2);
        d4axis->setObjectName(QString::fromUtf8("d4axis"));
        d4axis->setMinimum(-180);
        d4axis->setMaximum(180);
        d4axis->setOrientation(Qt::Horizontal);
        d4axis->setInvertedAppearance(false);
        d4axis->setInvertedControls(false);
        d4axis->setWrapping(false);
        d4axis->setNotchesVisible(false);

        gridLayout_17->addWidget(d4axis, 0, 0, 1, 1);

        lb4AxisValue = new QLabel(layoutWidget2);
        lb4AxisValue->setObjectName(QString::fromUtf8("lb4AxisValue"));

        gridLayout_17->addWidget(lb4AxisValue, 0, 1, 1, 1);

        lb5AxisValue = new QLabel(layoutWidget2);
        lb5AxisValue->setObjectName(QString::fromUtf8("lb5AxisValue"));

        gridLayout_17->addWidget(lb5AxisValue, 2, 1, 1, 1);

        lb6AxisValue = new QLabel(layoutWidget2);
        lb6AxisValue->setObjectName(QString::fromUtf8("lb6AxisValue"));

        gridLayout_17->addWidget(lb6AxisValue, 4, 1, 1, 1);


        verticalLayout_44->addWidget(fXYWorkingArea);

        gridLayout_9 = new QGridLayout();
        gridLayout_9->setSpacing(6);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        label_60 = new QLabel(scrollAreaWidgetContents_3);
        label_60->setObjectName(QString::fromUtf8("label_60"));

        gridLayout_9->addWidget(label_60, 1, 0, 1, 1);

        label_61 = new QLabel(scrollAreaWidgetContents_3);
        label_61->setObjectName(QString::fromUtf8("label_61"));

        gridLayout_9->addWidget(label_61, 2, 0, 1, 1);

        vs6AxisAdjsution = new QSlider(scrollAreaWidgetContents_3);
        vs6AxisAdjsution->setObjectName(QString::fromUtf8("vs6AxisAdjsution"));
        vs6AxisAdjsution->setMinimumSize(QSize(0, 30));
        vs6AxisAdjsution->setMinimum(-180);
        vs6AxisAdjsution->setMaximum(180);
        vs6AxisAdjsution->setValue(0);
        vs6AxisAdjsution->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(vs6AxisAdjsution, 2, 1, 1, 1);

        label_16 = new QLabel(scrollAreaWidgetContents_3);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_9->addWidget(label_16, 0, 0, 1, 1);

        vs5AxisAdjsution = new QSlider(scrollAreaWidgetContents_3);
        vs5AxisAdjsution->setObjectName(QString::fromUtf8("vs5AxisAdjsution"));
        vs5AxisAdjsution->setMinimumSize(QSize(0, 30));
        vs5AxisAdjsution->setMinimum(-180);
        vs5AxisAdjsution->setMaximum(180);
        vs5AxisAdjsution->setValue(0);
        vs5AxisAdjsution->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(vs5AxisAdjsution, 1, 1, 1, 1);

        vsAngleAdjsution = new QSlider(scrollAreaWidgetContents_3);
        vsAngleAdjsution->setObjectName(QString::fromUtf8("vsAngleAdjsution"));
        vsAngleAdjsution->setMinimumSize(QSize(0, 30));
        vsAngleAdjsution->setMinimum(-360);
        vsAngleAdjsution->setMaximum(360);
        vsAngleAdjsution->setValue(0);
        vsAngleAdjsution->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(vsAngleAdjsution, 0, 1, 1, 1);


        verticalLayout_44->addLayout(gridLayout_9);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_44->addItem(verticalSpacer_7);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_55->addWidget(scrollArea_3);

        tabWidget_2->addTab(SliderTab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        verticalLayout_54 = new QVBoxLayout(tab_2);
        verticalLayout_54->setSpacing(6);
        verticalLayout_54->setContentsMargins(11, 11, 11, 11);
        verticalLayout_54->setObjectName(QString::fromUtf8("verticalLayout_54"));
        gbJoystick = new QFrame(tab_2);
        gbJoystick->setObjectName(QString::fromUtf8("gbJoystick"));
        gbJoystick->setMaximumSize(QSize(16777215, 16777215));
        gbJoystick->setFont(font6);
        verticalLayout_45 = new QVBoxLayout(gbJoystick);
        verticalLayout_45->setSpacing(0);
        verticalLayout_45->setContentsMargins(11, 11, 11, 11);
        verticalLayout_45->setObjectName(QString::fromUtf8("verticalLayout_45"));
        verticalLayout_45->setContentsMargins(0, 20, 0, 0);
        wgJoystickParameter = new QWidget(gbJoystick);
        wgJoystickParameter->setObjectName(QString::fromUtf8("wgJoystickParameter"));
        gridLayout_20 = new QGridLayout(wgJoystickParameter);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        gridLayout_20->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_20->setHorizontalSpacing(20);
        gridLayout_20->setVerticalSpacing(5);
        gridLayout_20->setContentsMargins(10, 10, 10, 10);
        label_79 = new QLabel(wgJoystickParameter);
        label_79->setObjectName(QString::fromUtf8("label_79"));
        label_79->setMaximumSize(QSize(300, 16777215));

        gridLayout_20->addWidget(label_79, 2, 0, 1, 1);

        cbJoystickDevice = new QComboBox(wgJoystickParameter);
        cbJoystickDevice->setObjectName(QString::fromUtf8("cbJoystickDevice"));
        cbJoystickDevice->setMinimumSize(QSize(0, 0));
        cbJoystickDevice->setMaximumSize(QSize(150, 16777215));

        gridLayout_20->addWidget(cbJoystickDevice, 0, 1, 1, 1);

        label_41 = new QLabel(wgJoystickParameter);
        label_41->setObjectName(QString::fromUtf8("label_41"));
        label_41->setMaximumSize(QSize(300, 16777215));

        gridLayout_20->addWidget(label_41, 0, 0, 1, 1);

        leJoystickRange = new QLineEdit(wgJoystickParameter);
        leJoystickRange->setObjectName(QString::fromUtf8("leJoystickRange"));
        leJoystickRange->setMaximumSize(QSize(150, 16777215));

        gridLayout_20->addWidget(leJoystickRange, 1, 1, 1, 1);

        leJoystickSensibility = new QLineEdit(wgJoystickParameter);
        leJoystickSensibility->setObjectName(QString::fromUtf8("leJoystickSensibility"));
        leJoystickSensibility->setMaximumSize(QSize(150, 16777215));

        gridLayout_20->addWidget(leJoystickSensibility, 2, 1, 1, 1);

        label_51 = new QLabel(wgJoystickParameter);
        label_51->setObjectName(QString::fromUtf8("label_51"));
        label_51->setMaximumSize(QSize(300, 16777215));

        gridLayout_20->addWidget(label_51, 1, 0, 1, 1);

        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_20->addItem(horizontalSpacer_32, 0, 2, 1, 1);


        verticalLayout_45->addWidget(wgJoystickParameter);


        verticalLayout_54->addWidget(gbJoystick);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_54->addItem(verticalSpacer_8);

        tabWidget_2->addTab(tab_2, QString());

        verticalLayout_53->addWidget(tabWidget_2);

        RobotTabWidget->addTab(MoveTab, QString());
        IOTab = new QWidget();
        IOTab->setObjectName(QString::fromUtf8("IOTab"));
        verticalLayout_6 = new QVBoxLayout(IOTab);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tabWidget_3 = new QTabWidget(IOTab);
        tabWidget_3->setObjectName(QString::fromUtf8("tabWidget_3"));
        tabWidget_3->setTabPosition(QTabWidget::North);
        OutputTab = new QWidget();
        OutputTab->setObjectName(QString::fromUtf8("OutputTab"));
        verticalLayout_3 = new QVBoxLayout(OutputTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        wgOldOutput = new QWidget(OutputTab);
        wgOldOutput->setObjectName(QString::fromUtf8("wgOldOutput"));
        horizontalLayout_7 = new QHBoxLayout(wgOldOutput);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        gbRelay = new QGroupBox(wgOldOutput);
        gbRelay->setObjectName(QString::fromUtf8("gbRelay"));
        gbRelay->setMaximumSize(QSize(150, 16777215));
        gbRelay->setFont(font2);
        gridLayout_3 = new QGridLayout(gbRelay);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_34 = new QLabel(gbRelay);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setMaximumSize(QSize(16777215, 20));
        label_34->setFont(font5);
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_34, 0, 0, 1, 1);

        label_35 = new QLabel(gbRelay);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setMaximumSize(QSize(16777215, 20));
        label_35->setFont(font5);
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_35, 0, 1, 1, 1);

        pbPump = new QPushButton(gbRelay);
        pbPump->setObjectName(QString::fromUtf8("pbPump"));
        pbPump->setMinimumSize(QSize(50, 30));
        pbPump->setAutoFillBackground(false);
        QIcon icon45;
        icon45.addFile(QString::fromUtf8(":/icon/Toggle Off_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon45.addFile(QString::fromUtf8(":/icon/Toggle On_16px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbPump->setIcon(icon45);
        pbPump->setIconSize(QSize(16, 16));
        pbPump->setCheckable(true);
        pbPump->setChecked(false);
        pbPump->setAutoDefault(false);
        pbPump->setFlat(false);

        gridLayout_3->addWidget(pbPump, 1, 0, 1, 1);

        pbLaser = new QPushButton(gbRelay);
        pbLaser->setObjectName(QString::fromUtf8("pbLaser"));
        pbLaser->setMinimumSize(QSize(50, 30));
        pbLaser->setAutoFillBackground(false);
        pbLaser->setIcon(icon45);
        pbLaser->setIconSize(QSize(16, 16));
        pbLaser->setCheckable(true);
        pbLaser->setChecked(false);
        pbLaser->setAutoDefault(false);
        pbLaser->setFlat(false);

        gridLayout_3->addWidget(pbLaser, 1, 1, 1, 1);


        horizontalLayout_7->addWidget(gbRelay);

        gbGripper = new QGroupBox(wgOldOutput);
        gbGripper->setObjectName(QString::fromUtf8("gbGripper"));
        gbGripper->setMaximumSize(QSize(250, 16777215));
        gbGripper->setFont(font2);
        gridLayout_13 = new QGridLayout(gbGripper);
        gridLayout_13->setSpacing(6);
        gridLayout_13->setContentsMargins(11, 11, 11, 11);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        gridLayout_13->setContentsMargins(-1, 20, -1, -1);
        gridLayout_6 = new QGridLayout();
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        label_17 = new QLabel(gbGripper);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setFont(font5);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_17, 0, 1, 1, 1);

        label_27 = new QLabel(gbGripper);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font5);
        label_27->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_27, 0, 2, 1, 1);

        pbGrip = new QPushButton(gbGripper);
        pbGrip->setObjectName(QString::fromUtf8("pbGrip"));
        pbGrip->setMinimumSize(QSize(60, 30));
        pbGrip->setMaximumSize(QSize(30, 16777215));
        pbGrip->setAutoFillBackground(false);
        pbGrip->setAutoDefault(false);
        pbGrip->setFlat(false);

        gridLayout_6->addWidget(pbGrip, 1, 0, 1, 1);

        leGripperMin = new QLineEdit(gbGripper);
        leGripperMin->setObjectName(QString::fromUtf8("leGripperMin"));
        leGripperMin->setMinimumSize(QSize(30, 30));
        leGripperMin->setMaximumSize(QSize(40, 16777215));

        gridLayout_6->addWidget(leGripperMin, 1, 1, 1, 1);

        leGripperMax = new QLineEdit(gbGripper);
        leGripperMax->setObjectName(QString::fromUtf8("leGripperMax"));
        leGripperMax->setMinimumSize(QSize(30, 30));
        leGripperMax->setMaximumSize(QSize(40, 16777215));

        gridLayout_6->addWidget(leGripperMax, 1, 2, 1, 1);


        gridLayout_13->addLayout(gridLayout_6, 0, 0, 1, 1);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        hsGripperAngle = new QSlider(gbGripper);
        hsGripperAngle->setObjectName(QString::fromUtf8("hsGripperAngle"));
        sizePolicy14.setHeightForWidth(hsGripperAngle->sizePolicy().hasHeightForWidth());
        hsGripperAngle->setSizePolicy(sizePolicy14);
        hsGripperAngle->setMinimumSize(QSize(0, 30));
        hsGripperAngle->setMaximum(20);
        hsGripperAngle->setSingleStep(5);
        hsGripperAngle->setOrientation(Qt::Horizontal);

        horizontalLayout_15->addWidget(hsGripperAngle);

        lbGripperValue = new QLabel(gbGripper);
        lbGripperValue->setObjectName(QString::fromUtf8("lbGripperValue"));
        lbGripperValue->setMinimumSize(QSize(40, 0));
        QFont font13;
        font13.setPointSize(7);
        font13.setBold(false);
        font13.setWeight(50);
        font13.setKerning(true);
        lbGripperValue->setFont(font13);

        horizontalLayout_15->addWidget(lbGripperValue);


        gridLayout_13->addLayout(horizontalLayout_15, 1, 0, 1, 1);


        horizontalLayout_7->addWidget(gbGripper);

        horizontalSpacer_46 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_46);


        verticalLayout_3->addWidget(wgOldOutput);

        gbOutput = new QGroupBox(OutputTab);
        gbOutput->setObjectName(QString::fromUtf8("gbOutput"));
        gbOutput->setMinimumSize(QSize(0, 180));
        gbOutput->setFont(font6);
        verticalLayout_42 = new QVBoxLayout(gbOutput);
        verticalLayout_42->setSpacing(6);
        verticalLayout_42->setContentsMargins(11, 11, 11, 11);
        verticalLayout_42->setObjectName(QString::fromUtf8("verticalLayout_42"));
        verticalLayout_42->setContentsMargins(-1, 20, -1, -1);
        wgRelayOutput = new QWidget(gbOutput);
        wgRelayOutput->setObjectName(QString::fromUtf8("wgRelayOutput"));
        wgRelayOutput->setMinimumSize(QSize(0, 40));
        gridLayout_35 = new QGridLayout(wgRelayOutput);
        gridLayout_35->setSpacing(6);
        gridLayout_35->setContentsMargins(11, 11, 11, 11);
        gridLayout_35->setObjectName(QString::fromUtf8("gridLayout_35"));
        horizontalSpacer_47 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_35->addItem(horizontalSpacer_47, 0, 5, 1, 1);

        cbDx = new QCheckBox(wgRelayOutput);
        cbDx->setObjectName(QString::fromUtf8("cbDx"));
        cbDx->setMaximumSize(QSize(20, 16777215));

        gridLayout_35->addWidget(cbDx, 0, 1, 1, 1);

        cbRx = new QCheckBox(wgRelayOutput);
        cbRx->setObjectName(QString::fromUtf8("cbRx"));
        cbRx->setMaximumSize(QSize(20, 16777215));

        gridLayout_35->addWidget(cbRx, 0, 3, 1, 1);

        label_67 = new QLabel(wgRelayOutput);
        label_67->setObjectName(QString::fromUtf8("label_67"));
        label_67->setMinimumSize(QSize(70, 0));
        QFont font14;
        font14.setBold(false);
        font14.setWeight(50);
        label_67->setFont(font14);

        gridLayout_35->addWidget(label_67, 0, 0, 1, 1);

        leRx = new QLineEdit(wgRelayOutput);
        leRx->setObjectName(QString::fromUtf8("leRx"));
        leRx->setMaximumSize(QSize(30, 16777215));

        gridLayout_35->addWidget(leRx, 0, 4, 1, 1);

        leDx = new QLineEdit(wgRelayOutput);
        leDx->setObjectName(QString::fromUtf8("leDx"));
        leDx->setMaximumSize(QSize(30, 16777215));

        gridLayout_35->addWidget(leDx, 0, 2, 1, 1);


        verticalLayout_42->addWidget(wgRelayOutput);

        wgDigitalOutput = new QWidget(gbOutput);
        wgDigitalOutput->setObjectName(QString::fromUtf8("wgDigitalOutput"));
        wgDigitalOutput->setMinimumSize(QSize(0, 40));
        gridLayout_34 = new QGridLayout(wgDigitalOutput);
        gridLayout_34->setSpacing(6);
        gridLayout_34->setContentsMargins(11, 11, 11, 11);
        gridLayout_34->setObjectName(QString::fromUtf8("gridLayout_34"));
        label_68 = new QLabel(wgDigitalOutput);
        label_68->setObjectName(QString::fromUtf8("label_68"));
        label_68->setMinimumSize(QSize(70, 0));
        label_68->setFont(font14);

        gridLayout_34->addWidget(label_68, 0, 0, 1, 1);

        horizontalSpacer_48 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_34->addItem(horizontalSpacer_48, 0, 9, 1, 1);

        cbD1 = new QCheckBox(wgDigitalOutput);
        cbD1->setObjectName(QString::fromUtf8("cbD1"));
        cbD1->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD1, 0, 2, 1, 1);

        cbD2 = new QCheckBox(wgDigitalOutput);
        cbD2->setObjectName(QString::fromUtf8("cbD2"));
        cbD2->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD2, 0, 3, 1, 1);

        cbD3 = new QCheckBox(wgDigitalOutput);
        cbD3->setObjectName(QString::fromUtf8("cbD3"));
        cbD3->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD3, 0, 4, 1, 1);

        cbD0 = new QCheckBox(wgDigitalOutput);
        cbD0->setObjectName(QString::fromUtf8("cbD0"));
        cbD0->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD0, 0, 1, 1, 1);

        horizontalSpacer_69 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_34->addItem(horizontalSpacer_69, 1, 9, 1, 1);

        cbD4 = new QCheckBox(wgDigitalOutput);
        cbD4->setObjectName(QString::fromUtf8("cbD4"));
        cbD4->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD4, 1, 1, 1, 1);

        cbD5 = new QCheckBox(wgDigitalOutput);
        cbD5->setObjectName(QString::fromUtf8("cbD5"));
        cbD5->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD5, 1, 2, 1, 1);

        cbD6 = new QCheckBox(wgDigitalOutput);
        cbD6->setObjectName(QString::fromUtf8("cbD6"));
        cbD6->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD6, 1, 3, 1, 1);

        cbD7 = new QCheckBox(wgDigitalOutput);
        cbD7->setObjectName(QString::fromUtf8("cbD7"));
        cbD7->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD7, 1, 4, 1, 1);


        verticalLayout_42->addWidget(wgDigitalOutput);


        verticalLayout_3->addWidget(gbOutput);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        tabWidget_3->addTab(OutputTab, QString());
        InputTab = new QWidget();
        InputTab->setObjectName(QString::fromUtf8("InputTab"));
        gbInput = new QGroupBox(InputTab);
        gbInput->setObjectName(QString::fromUtf8("gbInput"));
        gbInput->setGeometry(QRect(15, 15, 407, 380));
        gbInput->setMinimumSize(QSize(0, 380));
        gbInput->setFont(font6);
        verticalLayout_43 = new QVBoxLayout(gbInput);
        verticalLayout_43->setSpacing(6);
        verticalLayout_43->setContentsMargins(11, 11, 11, 11);
        verticalLayout_43->setObjectName(QString::fromUtf8("verticalLayout_43"));
        verticalLayout_43->setContentsMargins(-1, 20, -1, -1);
        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        label_70 = new QLabel(gbInput);
        label_70->setObjectName(QString::fromUtf8("label_70"));
        label_70->setMinimumSize(QSize(30, 0));
        label_70->setMaximumSize(QSize(25, 16777215));
        label_70->setFont(font14);

        horizontalLayout_37->addWidget(label_70);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_16);

        lbI0Value = new QLabel(gbInput);
        lbI0Value->setObjectName(QString::fromUtf8("lbI0Value"));

        horizontalLayout_37->addWidget(lbI0Value);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_15);

        cbToggle0 = new QCheckBox(gbInput);
        cbToggle0->setObjectName(QString::fromUtf8("cbToggle0"));
        cbToggle0->setMinimumSize(QSize(110, 0));
        cbToggle0->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_37->addWidget(cbToggle0);

        pbReadI0 = new QPushButton(gbInput);
        pbReadI0->setObjectName(QString::fromUtf8("pbReadI0"));
        pbReadI0->setMinimumSize(QSize(50, 0));

        horizontalLayout_37->addWidget(pbReadI0);

        horizontalSpacer_51 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_51);


        verticalLayout_43->addLayout(horizontalLayout_37);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        label_74 = new QLabel(gbInput);
        label_74->setObjectName(QString::fromUtf8("label_74"));
        label_74->setMinimumSize(QSize(30, 0));
        label_74->setMaximumSize(QSize(25, 16777215));
        label_74->setFont(font14);

        horizontalLayout_38->addWidget(label_74);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_17);

        lbI1Value = new QLabel(gbInput);
        lbI1Value->setObjectName(QString::fromUtf8("lbI1Value"));

        horizontalLayout_38->addWidget(lbI1Value);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_18);

        cbToggle1 = new QCheckBox(gbInput);
        cbToggle1->setObjectName(QString::fromUtf8("cbToggle1"));
        cbToggle1->setMinimumSize(QSize(110, 0));
        cbToggle1->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_38->addWidget(cbToggle1);

        pbReadI1 = new QPushButton(gbInput);
        pbReadI1->setObjectName(QString::fromUtf8("pbReadI1"));
        pbReadI1->setMinimumSize(QSize(50, 0));

        horizontalLayout_38->addWidget(pbReadI1);

        horizontalSpacer_52 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_52);


        verticalLayout_43->addLayout(horizontalLayout_38);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        label_76 = new QLabel(gbInput);
        label_76->setObjectName(QString::fromUtf8("label_76"));
        label_76->setMinimumSize(QSize(30, 0));
        label_76->setMaximumSize(QSize(25, 16777215));
        label_76->setFont(font14);

        horizontalLayout_39->addWidget(label_76);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_19);

        lbI2Value = new QLabel(gbInput);
        lbI2Value->setObjectName(QString::fromUtf8("lbI2Value"));

        horizontalLayout_39->addWidget(lbI2Value);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_20);

        cbToggle2 = new QCheckBox(gbInput);
        cbToggle2->setObjectName(QString::fromUtf8("cbToggle2"));
        cbToggle2->setMinimumSize(QSize(110, 0));
        cbToggle2->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_39->addWidget(cbToggle2);

        pbReadI2 = new QPushButton(gbInput);
        pbReadI2->setObjectName(QString::fromUtf8("pbReadI2"));
        pbReadI2->setMinimumSize(QSize(50, 0));

        horizontalLayout_39->addWidget(pbReadI2);

        horizontalSpacer_53 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_53);


        verticalLayout_43->addLayout(horizontalLayout_39);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        label_78 = new QLabel(gbInput);
        label_78->setObjectName(QString::fromUtf8("label_78"));
        label_78->setMinimumSize(QSize(30, 0));
        label_78->setMaximumSize(QSize(25, 16777215));
        label_78->setFont(font14);

        horizontalLayout_40->addWidget(label_78);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_21);

        lbI3Value = new QLabel(gbInput);
        lbI3Value->setObjectName(QString::fromUtf8("lbI3Value"));

        horizontalLayout_40->addWidget(lbI3Value);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_22);

        cbToggle3 = new QCheckBox(gbInput);
        cbToggle3->setObjectName(QString::fromUtf8("cbToggle3"));
        cbToggle3->setMinimumSize(QSize(110, 0));
        cbToggle3->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_40->addWidget(cbToggle3);

        pbReadI3 = new QPushButton(gbInput);
        pbReadI3->setObjectName(QString::fromUtf8("pbReadI3"));
        pbReadI3->setMinimumSize(QSize(50, 0));

        horizontalLayout_40->addWidget(pbReadI3);

        horizontalSpacer_54 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_54);


        verticalLayout_43->addLayout(horizontalLayout_40);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        leIx = new QLineEdit(gbInput);
        leIx->setObjectName(QString::fromUtf8("leIx"));
        leIx->setMinimumSize(QSize(30, 0));
        leIx->setMaximumSize(QSize(25, 16777215));
        leIx->setFont(font14);

        horizontalLayout_43->addWidget(leIx);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_29);

        lbIxValue = new QLabel(gbInput);
        lbIxValue->setObjectName(QString::fromUtf8("lbIxValue"));

        horizontalLayout_43->addWidget(lbIxValue);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_30);

        cbTogglex = new QCheckBox(gbInput);
        cbTogglex->setObjectName(QString::fromUtf8("cbTogglex"));
        cbTogglex->setMinimumSize(QSize(110, 0));
        cbTogglex->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_43->addWidget(cbTogglex);

        pbReadIx = new QPushButton(gbInput);
        pbReadIx->setObjectName(QString::fromUtf8("pbReadIx"));
        pbReadIx->setMinimumSize(QSize(50, 0));

        horizontalLayout_43->addWidget(pbReadIx);

        horizontalSpacer_57 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_57);


        verticalLayout_43->addLayout(horizontalLayout_43);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        label_83 = new QLabel(gbInput);
        label_83->setObjectName(QString::fromUtf8("label_83"));
        label_83->setMinimumSize(QSize(30, 0));
        label_83->setMaximumSize(QSize(25, 16777215));
        label_83->setFont(font14);

        horizontalLayout_45->addWidget(label_83);

        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_34);

        lbA0Value = new QLabel(gbInput);
        lbA0Value->setObjectName(QString::fromUtf8("lbA0Value"));

        horizontalLayout_45->addWidget(lbA0Value);

        horizontalSpacer_35 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_35);

        leA0Delay = new QLineEdit(gbInput);
        leA0Delay->setObjectName(QString::fromUtf8("leA0Delay"));
        leA0Delay->setMinimumSize(QSize(110, 0));
        leA0Delay->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_45->addWidget(leA0Delay);

        pbReadA0 = new QPushButton(gbInput);
        pbReadA0->setObjectName(QString::fromUtf8("pbReadA0"));
        pbReadA0->setMinimumSize(QSize(50, 0));

        horizontalLayout_45->addWidget(pbReadA0);

        horizontalSpacer_58 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_58);


        verticalLayout_43->addLayout(horizontalLayout_45);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        label_85 = new QLabel(gbInput);
        label_85->setObjectName(QString::fromUtf8("label_85"));
        label_85->setMinimumSize(QSize(30, 0));
        label_85->setMaximumSize(QSize(25, 16777215));
        label_85->setFont(font14);

        horizontalLayout_46->addWidget(label_85);

        horizontalSpacer_36 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_36);

        lbA1Value = new QLabel(gbInput);
        lbA1Value->setObjectName(QString::fromUtf8("lbA1Value"));

        horizontalLayout_46->addWidget(lbA1Value);

        horizontalSpacer_37 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_37);

        leA1Delay = new QLineEdit(gbInput);
        leA1Delay->setObjectName(QString::fromUtf8("leA1Delay"));
        leA1Delay->setMinimumSize(QSize(110, 0));
        leA1Delay->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_46->addWidget(leA1Delay);

        pbReadA1 = new QPushButton(gbInput);
        pbReadA1->setObjectName(QString::fromUtf8("pbReadA1"));
        pbReadA1->setMinimumSize(QSize(50, 0));

        horizontalLayout_46->addWidget(pbReadA1);

        horizontalSpacer_59 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_46->addItem(horizontalSpacer_59);


        verticalLayout_43->addLayout(horizontalLayout_46);

        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        leAx = new QLineEdit(gbInput);
        leAx->setObjectName(QString::fromUtf8("leAx"));
        leAx->setMinimumSize(QSize(30, 0));
        leAx->setMaximumSize(QSize(25, 16777215));
        leAx->setFont(font14);

        horizontalLayout_47->addWidget(leAx);

        horizontalSpacer_38 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_47->addItem(horizontalSpacer_38);

        lbAxValue = new QLabel(gbInput);
        lbAxValue->setObjectName(QString::fromUtf8("lbAxValue"));

        horizontalLayout_47->addWidget(lbAxValue);

        horizontalSpacer_39 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_47->addItem(horizontalSpacer_39);

        leAxDelay = new QLineEdit(gbInput);
        leAxDelay->setObjectName(QString::fromUtf8("leAxDelay"));
        leAxDelay->setMinimumSize(QSize(110, 0));
        leAxDelay->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_47->addWidget(leAxDelay);

        pbReadAx = new QPushButton(gbInput);
        pbReadAx->setObjectName(QString::fromUtf8("pbReadAx"));
        pbReadAx->setMinimumSize(QSize(50, 0));

        horizontalLayout_47->addWidget(pbReadAx);

        horizontalSpacer_60 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_47->addItem(horizontalSpacer_60);


        verticalLayout_43->addLayout(horizontalLayout_47);

        tabWidget_3->addTab(InputTab, QString());

        verticalLayout_6->addWidget(tabWidget_3);

        RobotTabWidget->addTab(IOTab, QString());

        verticalLayout_5->addWidget(RobotTabWidget);

        scrollArea_2->setWidget(wgJoggingScrollWidget);

        verticalLayout_4->addWidget(scrollArea_2);

        QIcon icon46;
        icon46.addFile(QString::fromUtf8(":/icon/deltaicon.png"), QSize(), QIcon::Normal, QIcon::Off);
        twDevices->addTab(tRobot, icon46, QString());
        ConveyorTab = new QWidget();
        ConveyorTab->setObjectName(QString::fromUtf8("ConveyorTab"));
        verticalLayout_22 = new QVBoxLayout(ConveyorTab);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        horizontalLayout_48->setContentsMargins(10, -1, -1, -1);
        pbConveyorConnect = new QPushButton(ConveyorTab);
        pbConveyorConnect->setObjectName(QString::fromUtf8("pbConveyorConnect"));
        pbConveyorConnect->setMinimumSize(QSize(100, 30));
        pbConveyorConnect->setMaximumSize(QSize(120, 40));
        QFont font15;
        font15.setPointSize(12);
        pbConveyorConnect->setFont(font15);
        pbConveyorConnect->setStyleSheet(QString::fromUtf8(""));
        pbConveyorConnect->setCheckable(true);

        horizontalLayout_48->addWidget(pbConveyorConnect);

        label_2 = new QLabel(ConveyorTab);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_48->addWidget(label_2);

        cbSelectedConveyor = new QComboBox(ConveyorTab);
        cbSelectedConveyor->addItem(QString());
        cbSelectedConveyor->addItem(QString());
        cbSelectedConveyor->addItem(QString());
        cbSelectedConveyor->addItem(QString());
        cbSelectedConveyor->setObjectName(QString::fromUtf8("cbSelectedConveyor"));

        horizontalLayout_48->addWidget(cbSelectedConveyor);

        label_28 = new QLabel(ConveyorTab);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_48->addWidget(label_28);

        cbConveyorType = new QComboBox(ConveyorTab);
        cbConveyorType->addItem(QString());
        cbConveyorType->addItem(QString());
        cbConveyorType->addItem(QString());
        cbConveyorType->setObjectName(QString::fromUtf8("cbConveyorType"));
        cbConveyorType->setMinimumSize(QSize(100, 0));

        horizontalLayout_48->addWidget(cbConveyorType);

        lbConveyorCOMName = new QLabel(ConveyorTab);
        lbConveyorCOMName->setObjectName(QString::fromUtf8("lbConveyorCOMName"));
        QFont font16;
        font16.setPointSize(11);
        lbConveyorCOMName->setFont(font16);
        lbConveyorCOMName->setStyleSheet(QString::fromUtf8("color: rgb(41, 155, 255);"));

        horizontalLayout_48->addWidget(lbConveyorCOMName);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_48->addItem(horizontalSpacer);


        verticalLayout_22->addLayout(horizontalLayout_48);

        fConveyorX = new QFrame(ConveyorTab);
        fConveyorX->setObjectName(QString::fromUtf8("fConveyorX"));
        gridLayout_7 = new QGridLayout(fConveyorX);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(20);
        gridLayout_7->setVerticalSpacing(10);
        gridLayout_7->setContentsMargins(10, 10, 10, 10);
        leConveyorXPosition = new QLineEdit(fConveyorX);
        leConveyorXPosition->setObjectName(QString::fromUtf8("leConveyorXPosition"));
        leConveyorXPosition->setMinimumSize(QSize(0, 30));
        leConveyorXPosition->setMaximumSize(QSize(200, 16777215));
        QFont font17;
        font17.setPointSize(11);
        font17.setBold(false);
        font17.setWeight(50);
        font17.setKerning(true);
        leConveyorXPosition->setFont(font17);

        gridLayout_7->addWidget(leConveyorXPosition, 3, 1, 1, 1);

        cbConveyorValueType = new QComboBox(fConveyorX);
        cbConveyorValueType->addItem(QString());
        cbConveyorValueType->addItem(QString());
        cbConveyorValueType->setObjectName(QString::fromUtf8("cbConveyorValueType"));
        cbConveyorValueType->setMinimumSize(QSize(0, 30));
        cbConveyorValueType->setMaximumSize(QSize(200, 16777215));
        cbConveyorValueType->setFont(font17);
        cbConveyorValueType->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(cbConveyorValueType, 1, 1, 1, 1);

        lbUnitOfConveyorMoving = new QLabel(fConveyorX);
        lbUnitOfConveyorMoving->setObjectName(QString::fromUtf8("lbUnitOfConveyorMoving"));
        lbUnitOfConveyorMoving->setEnabled(false);
        lbUnitOfConveyorMoving->setFont(font5);

        gridLayout_7->addWidget(lbUnitOfConveyorMoving, 3, 2, 1, 1);

        label_57 = new QLabel(fConveyorX);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        label_57->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_57, 2, 0, 1, 1);

        label_46 = new QLabel(fConveyorX);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_46, 1, 0, 1, 1);

        cbConveyorMode = new QComboBox(fConveyorX);
        cbConveyorMode->addItem(QString());
        cbConveyorMode->addItem(QString());
        cbConveyorMode->setObjectName(QString::fromUtf8("cbConveyorMode"));
        cbConveyorMode->setMinimumSize(QSize(0, 30));
        cbConveyorMode->setMaximumSize(QSize(200, 16777215));
        cbConveyorMode->setFont(font17);

        gridLayout_7->addWidget(cbConveyorMode, 0, 1, 1, 1);

        label_12 = new QLabel(fConveyorX);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_12, 3, 0, 1, 1);

        leConveyorXSpeed = new QLineEdit(fConveyorX);
        leConveyorXSpeed->setObjectName(QString::fromUtf8("leConveyorXSpeed"));
        leConveyorXSpeed->setEnabled(true);
        leConveyorXSpeed->setMinimumSize(QSize(0, 30));
        leConveyorXSpeed->setMaximumSize(QSize(200, 16777215));
        leConveyorXSpeed->setFont(font17);
        leConveyorXSpeed->setClearButtonEnabled(false);

        gridLayout_7->addWidget(leConveyorXSpeed, 2, 1, 1, 1);

        label_52 = new QLabel(fConveyorX);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_52, 0, 0, 1, 1);

        lbSpeedOfPositionMode = new QLabel(fConveyorX);
        lbSpeedOfPositionMode->setObjectName(QString::fromUtf8("lbSpeedOfPositionMode"));
        lbSpeedOfPositionMode->setEnabled(false);
        lbSpeedOfPositionMode->setFont(font5);

        gridLayout_7->addWidget(lbSpeedOfPositionMode, 2, 2, 1, 1);


        verticalLayout_22->addWidget(fConveyorX);

        fConveyorXHub = new QFrame(ConveyorTab);
        fConveyorXHub->setObjectName(QString::fromUtf8("fConveyorXHub"));
        gridLayout_18 = new QGridLayout(fConveyorXHub);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        gridLayout_18->setHorizontalSpacing(20);
        gridLayout_18->setVerticalSpacing(10);
        gridLayout_18->setContentsMargins(10, 10, 10, 10);
        label_77 = new QLabel(fConveyorXHub);
        label_77->setObjectName(QString::fromUtf8("label_77"));
        label_77->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_18->addWidget(label_77, 4, 0, 1, 1);

        leSubConveyor1Position = new QLineEdit(fConveyorXHub);
        leSubConveyor1Position->setObjectName(QString::fromUtf8("leSubConveyor1Position"));
        leSubConveyor1Position->setEnabled(true);
        leSubConveyor1Position->setMinimumSize(QSize(0, 30));
        leSubConveyor1Position->setMaximumSize(QSize(200, 16777215));
        leSubConveyor1Position->setFont(font17);
        leSubConveyor1Position->setClearButtonEnabled(false);

        gridLayout_18->addWidget(leSubConveyor1Position, 4, 1, 1, 1);

        label_115 = new QLabel(fConveyorXHub);
        label_115->setObjectName(QString::fromUtf8("label_115"));
        label_115->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_18->addWidget(label_115, 1, 0, 1, 1);

        label_114 = new QLabel(fConveyorXHub);
        label_114->setObjectName(QString::fromUtf8("label_114"));
        label_114->setAlignment(Qt::AlignCenter);

        gridLayout_18->addWidget(label_114, 0, 3, 1, 1);

        cbSubConveyor2Mode = new QComboBox(fConveyorXHub);
        cbSubConveyor2Mode->addItem(QString());
        cbSubConveyor2Mode->addItem(QString());
        cbSubConveyor2Mode->setObjectName(QString::fromUtf8("cbSubConveyor2Mode"));
        cbSubConveyor2Mode->setMinimumSize(QSize(0, 30));
        cbSubConveyor2Mode->setMaximumSize(QSize(200, 16777215));
        cbSubConveyor2Mode->setFont(font17);
        cbSubConveyor2Mode->setStyleSheet(QString::fromUtf8(""));

        gridLayout_18->addWidget(cbSubConveyor2Mode, 1, 2, 1, 1);

        leSubConveyor1Speed = new QLineEdit(fConveyorXHub);
        leSubConveyor1Speed->setObjectName(QString::fromUtf8("leSubConveyor1Speed"));
        leSubConveyor1Speed->setMinimumSize(QSize(0, 30));
        leSubConveyor1Speed->setMaximumSize(QSize(200, 16777215));
        leSubConveyor1Speed->setFont(font17);

        gridLayout_18->addWidget(leSubConveyor1Speed, 3, 1, 1, 1);

        label_75 = new QLabel(fConveyorXHub);
        label_75->setObjectName(QString::fromUtf8("label_75"));
        label_75->setAlignment(Qt::AlignCenter);

        gridLayout_18->addWidget(label_75, 0, 1, 1, 1);

        label_82 = new QLabel(fConveyorXHub);
        label_82->setObjectName(QString::fromUtf8("label_82"));
        label_82->setAlignment(Qt::AlignCenter);

        gridLayout_18->addWidget(label_82, 0, 2, 1, 1);

        leSubConveyor2Position = new QLineEdit(fConveyorXHub);
        leSubConveyor2Position->setObjectName(QString::fromUtf8("leSubConveyor2Position"));
        leSubConveyor2Position->setEnabled(true);
        leSubConveyor2Position->setMinimumSize(QSize(0, 30));
        leSubConveyor2Position->setMaximumSize(QSize(200, 16777215));
        leSubConveyor2Position->setFont(font17);
        leSubConveyor2Position->setClearButtonEnabled(false);

        gridLayout_18->addWidget(leSubConveyor2Position, 4, 2, 1, 1);

        leSubConveyor2Speed = new QLineEdit(fConveyorXHub);
        leSubConveyor2Speed->setObjectName(QString::fromUtf8("leSubConveyor2Speed"));
        leSubConveyor2Speed->setEnabled(true);
        leSubConveyor2Speed->setMinimumSize(QSize(0, 30));
        leSubConveyor2Speed->setMaximumSize(QSize(200, 16777215));
        leSubConveyor2Speed->setFont(font17);
        leSubConveyor2Speed->setClearButtonEnabled(false);

        gridLayout_18->addWidget(leSubConveyor2Speed, 3, 2, 1, 1);

        cbSubConveyor3Mode = new QComboBox(fConveyorXHub);
        cbSubConveyor3Mode->addItem(QString());
        cbSubConveyor3Mode->addItem(QString());
        cbSubConveyor3Mode->setObjectName(QString::fromUtf8("cbSubConveyor3Mode"));
        cbSubConveyor3Mode->setMinimumSize(QSize(0, 30));
        cbSubConveyor3Mode->setMaximumSize(QSize(200, 16777215));
        cbSubConveyor3Mode->setFont(font17);
        cbSubConveyor3Mode->setStyleSheet(QString::fromUtf8(""));

        gridLayout_18->addWidget(cbSubConveyor3Mode, 1, 3, 1, 1);

        leSubConveyor3Speed = new QLineEdit(fConveyorXHub);
        leSubConveyor3Speed->setObjectName(QString::fromUtf8("leSubConveyor3Speed"));
        leSubConveyor3Speed->setEnabled(true);
        leSubConveyor3Speed->setMinimumSize(QSize(0, 30));
        leSubConveyor3Speed->setMaximumSize(QSize(200, 16777215));
        leSubConveyor3Speed->setFont(font17);
        leSubConveyor3Speed->setClearButtonEnabled(false);

        gridLayout_18->addWidget(leSubConveyor3Speed, 3, 3, 1, 1);

        cbSubConveyor1Mode = new QComboBox(fConveyorXHub);
        cbSubConveyor1Mode->addItem(QString());
        cbSubConveyor1Mode->addItem(QString());
        cbSubConveyor1Mode->setObjectName(QString::fromUtf8("cbSubConveyor1Mode"));
        cbSubConveyor1Mode->setMinimumSize(QSize(0, 30));
        cbSubConveyor1Mode->setMaximumSize(QSize(200, 16777215));
        cbSubConveyor1Mode->setFont(font17);
        cbSubConveyor1Mode->setStyleSheet(QString::fromUtf8(""));

        gridLayout_18->addWidget(cbSubConveyor1Mode, 1, 1, 1, 1);

        label_80 = new QLabel(fConveyorXHub);
        label_80->setObjectName(QString::fromUtf8("label_80"));
        label_80->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_18->addWidget(label_80, 3, 0, 1, 1);

        leSubConveyor3Position = new QLineEdit(fConveyorXHub);
        leSubConveyor3Position->setObjectName(QString::fromUtf8("leSubConveyor3Position"));
        leSubConveyor3Position->setEnabled(true);
        leSubConveyor3Position->setMinimumSize(QSize(0, 30));
        leSubConveyor3Position->setMaximumSize(QSize(200, 16777215));
        leSubConveyor3Position->setFont(font17);
        leSubConveyor3Position->setClearButtonEnabled(false);

        gridLayout_18->addWidget(leSubConveyor3Position, 4, 3, 1, 1);


        verticalLayout_22->addWidget(fConveyorXHub);

        fConveyorCustom = new QFrame(ConveyorTab);
        fConveyorCustom->setObjectName(QString::fromUtf8("fConveyorCustom"));
        gridLayout_39 = new QGridLayout(fConveyorCustom);
        gridLayout_39->setSpacing(6);
        gridLayout_39->setContentsMargins(11, 11, 11, 11);
        gridLayout_39->setObjectName(QString::fromUtf8("gridLayout_39"));
        gridLayout_39->setHorizontalSpacing(20);
        gridLayout_39->setVerticalSpacing(10);
        gridLayout_39->setContentsMargins(10, 10, 10, 10);
        pbStopCustomConveyor2Command = new QLineEdit(fConveyorCustom);
        pbStopCustomConveyor2Command->setObjectName(QString::fromUtf8("pbStopCustomConveyor2Command"));
        pbStopCustomConveyor2Command->setEnabled(true);
        pbStopCustomConveyor2Command->setMinimumSize(QSize(0, 30));
        pbStopCustomConveyor2Command->setMaximumSize(QSize(200, 16777215));
        pbStopCustomConveyor2Command->setFont(font17);
        pbStopCustomConveyor2Command->setClearButtonEnabled(false);

        gridLayout_39->addWidget(pbStopCustomConveyor2Command, 4, 1, 1, 1);

        pbStartCustomConveyor3 = new QPushButton(fConveyorCustom);
        pbStartCustomConveyor3->setObjectName(QString::fromUtf8("pbStartCustomConveyor3"));
        pbStartCustomConveyor3->setMinimumSize(QSize(0, 30));

        gridLayout_39->addWidget(pbStartCustomConveyor3, 1, 2, 1, 1);

        pbStopCustomConveyor3 = new QPushButton(fConveyorCustom);
        pbStopCustomConveyor3->setObjectName(QString::fromUtf8("pbStopCustomConveyor3"));
        pbStopCustomConveyor3->setMinimumSize(QSize(0, 30));

        gridLayout_39->addWidget(pbStopCustomConveyor3, 3, 2, 1, 1);

        label_147 = new QLabel(fConveyorCustom);
        label_147->setObjectName(QString::fromUtf8("label_147"));
        label_147->setAlignment(Qt::AlignCenter);

        gridLayout_39->addWidget(label_147, 0, 2, 1, 1);

        pbStartCustomConveyor2Command = new QLineEdit(fConveyorCustom);
        pbStartCustomConveyor2Command->setObjectName(QString::fromUtf8("pbStartCustomConveyor2Command"));
        pbStartCustomConveyor2Command->setEnabled(true);
        pbStartCustomConveyor2Command->setMinimumSize(QSize(0, 30));
        pbStartCustomConveyor2Command->setMaximumSize(QSize(200, 16777215));
        pbStartCustomConveyor2Command->setFont(font17);
        pbStartCustomConveyor2Command->setClearButtonEnabled(false);

        gridLayout_39->addWidget(pbStartCustomConveyor2Command, 2, 1, 1, 1);

        pbStopCustomConveyor2 = new QPushButton(fConveyorCustom);
        pbStopCustomConveyor2->setObjectName(QString::fromUtf8("pbStopCustomConveyor2"));
        pbStopCustomConveyor2->setMinimumSize(QSize(0, 30));

        gridLayout_39->addWidget(pbStopCustomConveyor2, 3, 1, 1, 1);

        pbStopCustomConveyor3Command = new QLineEdit(fConveyorCustom);
        pbStopCustomConveyor3Command->setObjectName(QString::fromUtf8("pbStopCustomConveyor3Command"));
        pbStopCustomConveyor3Command->setEnabled(true);
        pbStopCustomConveyor3Command->setMinimumSize(QSize(0, 30));
        pbStopCustomConveyor3Command->setMaximumSize(QSize(200, 16777215));
        pbStopCustomConveyor3Command->setFont(font17);
        pbStopCustomConveyor3Command->setClearButtonEnabled(false);

        gridLayout_39->addWidget(pbStopCustomConveyor3Command, 4, 2, 1, 1);

        label_153 = new QLabel(fConveyorCustom);
        label_153->setObjectName(QString::fromUtf8("label_153"));
        label_153->setAlignment(Qt::AlignCenter);

        gridLayout_39->addWidget(label_153, 0, 0, 1, 1);

        pbStartCustomConveyor1 = new QPushButton(fConveyorCustom);
        pbStartCustomConveyor1->setObjectName(QString::fromUtf8("pbStartCustomConveyor1"));
        pbStartCustomConveyor1->setMinimumSize(QSize(0, 30));

        gridLayout_39->addWidget(pbStartCustomConveyor1, 1, 0, 1, 1);

        pbStopCustomConveyor1 = new QPushButton(fConveyorCustom);
        pbStopCustomConveyor1->setObjectName(QString::fromUtf8("pbStopCustomConveyor1"));
        pbStopCustomConveyor1->setMinimumSize(QSize(0, 30));

        gridLayout_39->addWidget(pbStopCustomConveyor1, 3, 0, 1, 1);

        pbStopCustomConveyor1Command = new QLineEdit(fConveyorCustom);
        pbStopCustomConveyor1Command->setObjectName(QString::fromUtf8("pbStopCustomConveyor1Command"));
        pbStopCustomConveyor1Command->setEnabled(true);
        pbStopCustomConveyor1Command->setMinimumSize(QSize(0, 30));
        pbStopCustomConveyor1Command->setMaximumSize(QSize(200, 16777215));
        pbStopCustomConveyor1Command->setFont(font17);
        pbStopCustomConveyor1Command->setClearButtonEnabled(false);

        gridLayout_39->addWidget(pbStopCustomConveyor1Command, 4, 0, 1, 1);

        pbStartCustomConveyor1Command = new QLineEdit(fConveyorCustom);
        pbStartCustomConveyor1Command->setObjectName(QString::fromUtf8("pbStartCustomConveyor1Command"));
        pbStartCustomConveyor1Command->setMinimumSize(QSize(0, 30));
        pbStartCustomConveyor1Command->setMaximumSize(QSize(200, 16777215));
        pbStartCustomConveyor1Command->setFont(font17);

        gridLayout_39->addWidget(pbStartCustomConveyor1Command, 2, 0, 1, 1);

        pbStartCustomConveyor2 = new QPushButton(fConveyorCustom);
        pbStartCustomConveyor2->setObjectName(QString::fromUtf8("pbStartCustomConveyor2"));
        pbStartCustomConveyor2->setMinimumSize(QSize(0, 30));

        gridLayout_39->addWidget(pbStartCustomConveyor2, 1, 1, 1, 1);

        pbStartCustomConveyor3Command = new QLineEdit(fConveyorCustom);
        pbStartCustomConveyor3Command->setObjectName(QString::fromUtf8("pbStartCustomConveyor3Command"));
        pbStartCustomConveyor3Command->setEnabled(true);
        pbStartCustomConveyor3Command->setMinimumSize(QSize(0, 30));
        pbStartCustomConveyor3Command->setMaximumSize(QSize(200, 16777215));
        pbStartCustomConveyor3Command->setFont(font17);
        pbStartCustomConveyor3Command->setClearButtonEnabled(false);

        gridLayout_39->addWidget(pbStartCustomConveyor3Command, 2, 2, 1, 1);

        label_154 = new QLabel(fConveyorCustom);
        label_154->setObjectName(QString::fromUtf8("label_154"));
        label_154->setAlignment(Qt::AlignCenter);

        gridLayout_39->addWidget(label_154, 0, 1, 1, 1);


        verticalLayout_22->addWidget(fConveyorCustom);

        verticalSpacer_2 = new QSpacerItem(20, 304, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_22->addItem(verticalSpacer_2);

        twDevices->addTab(ConveyorTab, QString());
        EncoderTab = new QWidget();
        EncoderTab->setObjectName(QString::fromUtf8("EncoderTab"));
        verticalLayout_8 = new QVBoxLayout(EncoderTab);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_51 = new QHBoxLayout();
        horizontalLayout_51->setSpacing(6);
        horizontalLayout_51->setObjectName(QString::fromUtf8("horizontalLayout_51"));
        horizontalLayout_51->setContentsMargins(10, -1, -1, -1);
        pbConnectEncoder = new QPushButton(EncoderTab);
        pbConnectEncoder->setObjectName(QString::fromUtf8("pbConnectEncoder"));
        pbConnectEncoder->setMinimumSize(QSize(100, 30));
        pbConnectEncoder->setMaximumSize(QSize(120, 40));
        pbConnectEncoder->setFont(font15);
        pbConnectEncoder->setStyleSheet(QString::fromUtf8(""));
        pbConnectEncoder->setCheckable(true);

        horizontalLayout_51->addWidget(pbConnectEncoder);

        label_11 = new QLabel(EncoderTab);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_51->addWidget(label_11);

        cbSelectedEncoder = new QComboBox(EncoderTab);
        cbSelectedEncoder->addItem(QString());
        cbSelectedEncoder->addItem(QString());
        cbSelectedEncoder->addItem(QString());
        cbSelectedEncoder->addItem(QString());
        cbSelectedEncoder->setObjectName(QString::fromUtf8("cbSelectedEncoder"));

        horizontalLayout_51->addWidget(cbSelectedEncoder);

        label_124 = new QLabel(EncoderTab);
        label_124->setObjectName(QString::fromUtf8("label_124"));

        horizontalLayout_51->addWidget(label_124);

        cbEncoderType = new QComboBox(EncoderTab);
        cbEncoderType->addItem(QString());
        cbEncoderType->addItem(QString());
        cbEncoderType->addItem(QString());
        cbEncoderType->setObjectName(QString::fromUtf8("cbEncoderType"));
        cbEncoderType->setMinimumSize(QSize(100, 0));

        horizontalLayout_51->addWidget(cbEncoderType);

        lbEncoderCOMname = new QLabel(EncoderTab);
        lbEncoderCOMname->setObjectName(QString::fromUtf8("lbEncoderCOMname"));
        lbEncoderCOMname->setFont(font16);
        lbEncoderCOMname->setStyleSheet(QString::fromUtf8("color: rgb(41, 155, 255);"));

        horizontalLayout_51->addWidget(lbEncoderCOMname);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_51->addItem(horizontalSpacer_14);


        verticalLayout_8->addLayout(horizontalLayout_51);

        gridLayout_21 = new QGridLayout();
        gridLayout_21->setSpacing(6);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        gridLayout_21->setContentsMargins(10, -1, -1, -1);
        leEncoderVelocity = new QLineEdit(EncoderTab);
        leEncoderVelocity->setObjectName(QString::fromUtf8("leEncoderVelocity"));
        sizePolicy.setHeightForWidth(leEncoderVelocity->sizePolicy().hasHeightForWidth());
        leEncoderVelocity->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(leEncoderVelocity, 3, 1, 1, 1);

        leEncoderInterval = new QLineEdit(EncoderTab);
        leEncoderInterval->setObjectName(QString::fromUtf8("leEncoderInterval"));
        sizePolicy.setHeightForWidth(leEncoderInterval->sizePolicy().hasHeightForWidth());
        leEncoderInterval->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(leEncoderInterval, 2, 1, 1, 1);

        leEncoderCurrentPosition = new QLineEdit(EncoderTab);
        leEncoderCurrentPosition->setObjectName(QString::fromUtf8("leEncoderCurrentPosition"));
        sizePolicy.setHeightForWidth(leEncoderCurrentPosition->sizePolicy().hasHeightForWidth());
        leEncoderCurrentPosition->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(leEncoderCurrentPosition, 4, 1, 1, 1);

        label_130 = new QLabel(EncoderTab);
        label_130->setObjectName(QString::fromUtf8("label_130"));

        gridLayout_21->addWidget(label_130, 4, 0, 1, 1);

        pbReadEncoder = new QPushButton(EncoderTab);
        pbReadEncoder->setObjectName(QString::fromUtf8("pbReadEncoder"));

        gridLayout_21->addWidget(pbReadEncoder, 4, 2, 1, 1);

        pbSetEncoderVelocity = new QPushButton(EncoderTab);
        pbSetEncoderVelocity->setObjectName(QString::fromUtf8("pbSetEncoderVelocity"));

        gridLayout_21->addWidget(pbSetEncoderVelocity, 3, 2, 1, 1);

        pbSetEncoderInterval = new QPushButton(EncoderTab);
        pbSetEncoderInterval->setObjectName(QString::fromUtf8("pbSetEncoderInterval"));

        gridLayout_21->addWidget(pbSetEncoderInterval, 2, 2, 1, 1);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_21->addItem(horizontalSpacer_23, 2, 4, 1, 1);

        pbResetEncoder = new QPushButton(EncoderTab);
        pbResetEncoder->setObjectName(QString::fromUtf8("pbResetEncoder"));

        gridLayout_21->addWidget(pbResetEncoder, 4, 3, 1, 1);

        label_129 = new QLabel(EncoderTab);
        label_129->setObjectName(QString::fromUtf8("label_129"));

        gridLayout_21->addWidget(label_129, 3, 0, 1, 1);

        label_125 = new QLabel(EncoderTab);
        label_125->setObjectName(QString::fromUtf8("label_125"));

        gridLayout_21->addWidget(label_125, 2, 0, 1, 1);

        cbEncoderActive = new QCheckBox(EncoderTab);
        cbEncoderActive->setObjectName(QString::fromUtf8("cbEncoderActive"));
        cbEncoderActive->setChecked(true);

        gridLayout_21->addWidget(cbEncoderActive, 1, 0, 1, 1);


        verticalLayout_8->addLayout(gridLayout_21);

        verticalSpacer_14 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_14);

        twDevices->addTab(EncoderTab, QString());
        SliderTab1 = new QWidget();
        SliderTab1->setObjectName(QString::fromUtf8("SliderTab1"));
        verticalLayout_23 = new QVBoxLayout(SliderTab1);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        horizontalLayout_49->setContentsMargins(10, -1, -1, -1);
        pbSlidingConnect = new QPushButton(SliderTab1);
        pbSlidingConnect->setObjectName(QString::fromUtf8("pbSlidingConnect"));
        pbSlidingConnect->setMinimumSize(QSize(100, 30));
        pbSlidingConnect->setMaximumSize(QSize(120, 50));
        pbSlidingConnect->setFont(font15);
        QIcon icon47;
        icon47.addFile(QString::fromUtf8("icon/connected.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingConnect->setIcon(icon47);

        horizontalLayout_49->addWidget(pbSlidingConnect);

        label_161 = new QLabel(SliderTab1);
        label_161->setObjectName(QString::fromUtf8("label_161"));

        horizontalLayout_49->addWidget(label_161);

        cbSelectedSlider = new QComboBox(SliderTab1);
        cbSelectedSlider->addItem(QString());
        cbSelectedSlider->addItem(QString());
        cbSelectedSlider->addItem(QString());
        cbSelectedSlider->addItem(QString());
        cbSelectedSlider->setObjectName(QString::fromUtf8("cbSelectedSlider"));

        horizontalLayout_49->addWidget(cbSelectedSlider);

        lbSliderCOMName = new QLabel(SliderTab1);
        lbSliderCOMName->setObjectName(QString::fromUtf8("lbSliderCOMName"));
        lbSliderCOMName->setFont(font16);
        lbSliderCOMName->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_49->addWidget(lbSliderCOMName);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_49->addItem(horizontalSpacer_12);


        verticalLayout_23->addLayout(horizontalLayout_49);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(10);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(10, 10, 10, 10);
        leSlidingPosition = new QLineEdit(SliderTab1);
        leSlidingPosition->setObjectName(QString::fromUtf8("leSlidingPosition"));
        leSlidingPosition->setMinimumSize(QSize(0, 30));
        leSlidingPosition->setMaximumSize(QSize(200, 40));

        gridLayout_8->addWidget(leSlidingPosition, 3, 1, 1, 1);

        pbSlidingDisable = new QPushButton(SliderTab1);
        pbSlidingDisable->setObjectName(QString::fromUtf8("pbSlidingDisable"));
        pbSlidingDisable->setMinimumSize(QSize(0, 30));
        pbSlidingDisable->setMaximumSize(QSize(200, 40));
        pbSlidingDisable->setFont(font16);
        QIcon icon48;
        icon48.addFile(QString::fromUtf8("icon/icons8-sleeping-in-bed-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingDisable->setIcon(icon48);

        gridLayout_8->addWidget(pbSlidingDisable, 0, 1, 1, 1);

        label_58 = new QLabel(SliderTab1);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setFont(font5);

        gridLayout_8->addWidget(label_58, 2, 2, 1, 1);

        label_37 = new QLabel(SliderTab1);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setFont(font5);
        label_37->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_37, 3, 0, 1, 1);

        pbSlidingHome = new QPushButton(SliderTab1);
        pbSlidingHome->setObjectName(QString::fromUtf8("pbSlidingHome"));
        pbSlidingHome->setMinimumSize(QSize(0, 30));
        pbSlidingHome->setMaximumSize(QSize(200, 40));
        pbSlidingHome->setFont(font16);
        QIcon icon49;
        icon49.addFile(QString::fromUtf8("icon/icons8-home-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingHome->setIcon(icon49);

        gridLayout_8->addWidget(pbSlidingHome, 1, 1, 1, 1);

        leSlidingSpeed = new QLineEdit(SliderTab1);
        leSlidingSpeed->setObjectName(QString::fromUtf8("leSlidingSpeed"));
        leSlidingSpeed->setMinimumSize(QSize(0, 30));
        leSlidingSpeed->setMaximumSize(QSize(200, 40));

        gridLayout_8->addWidget(leSlidingSpeed, 2, 1, 1, 1);

        label_36 = new QLabel(SliderTab1);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setFont(font5);
        label_36->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_36, 2, 0, 1, 1);

        label_59 = new QLabel(SliderTab1);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setFont(font5);

        gridLayout_8->addWidget(label_59, 3, 2, 1, 1);


        verticalLayout_23->addLayout(gridLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 296, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_23->addItem(verticalSpacer_3);

        twDevices->addTab(SliderTab1, QString());
        MCUTab = new QWidget();
        MCUTab->setObjectName(QString::fromUtf8("MCUTab"));
        verticalLayout_24 = new QVBoxLayout(MCUTab);
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setContentsMargins(11, 11, 11, 11);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        widget1 = new QWidget(MCUTab);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setMaximumSize(QSize(16777215, 40));
        horizontalLayout_50 = new QHBoxLayout(widget1);
        horizontalLayout_50->setSpacing(10);
        horizontalLayout_50->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_50->setObjectName(QString::fromUtf8("horizontalLayout_50"));
        horizontalLayout_50->setContentsMargins(0, 0, 10, 10);
        pbExternalControllerConnect = new QPushButton(widget1);
        pbExternalControllerConnect->setObjectName(QString::fromUtf8("pbExternalControllerConnect"));
        sizePolicy.setHeightForWidth(pbExternalControllerConnect->sizePolicy().hasHeightForWidth());
        pbExternalControllerConnect->setSizePolicy(sizePolicy);
        pbExternalControllerConnect->setMinimumSize(QSize(100, 30));
        pbExternalControllerConnect->setMaximumSize(QSize(120, 50));
        QFont font18;
        font18.setPointSize(12);
        font18.setBold(false);
        font18.setWeight(50);
        font18.setKerning(true);
        pbExternalControllerConnect->setFont(font18);

        horizontalLayout_50->addWidget(pbExternalControllerConnect);

        label_162 = new QLabel(widget1);
        label_162->setObjectName(QString::fromUtf8("label_162"));

        horizontalLayout_50->addWidget(label_162);

        cbSelectedDevice = new QComboBox(widget1);
        cbSelectedDevice->addItem(QString());
        cbSelectedDevice->addItem(QString());
        cbSelectedDevice->addItem(QString());
        cbSelectedDevice->addItem(QString());
        cbSelectedDevice->setObjectName(QString::fromUtf8("cbSelectedDevice"));

        horizontalLayout_50->addWidget(cbSelectedDevice);

        lbExternalCOMName = new QLabel(widget1);
        lbExternalCOMName->setObjectName(QString::fromUtf8("lbExternalCOMName"));
        lbExternalCOMName->setMaximumSize(QSize(16777215, 30));
        lbExternalCOMName->setFont(font16);
        lbExternalCOMName->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_50->addWidget(lbExternalCOMName);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_50->addItem(horizontalSpacer_25);


        verticalLayout_24->addWidget(widget1);

        teReceiveFromMCU = new QTextEdit(MCUTab);
        teReceiveFromMCU->setObjectName(QString::fromUtf8("teReceiveFromMCU"));

        verticalLayout_24->addWidget(teReceiveFromMCU);

        leTransmitToMCU = new QLineEdit(MCUTab);
        leTransmitToMCU->setObjectName(QString::fromUtf8("leTransmitToMCU"));
        leTransmitToMCU->setMinimumSize(QSize(0, 30));

        verticalLayout_24->addWidget(leTransmitToMCU);

        twDevices->addTab(MCUTab, QString());
        PlusDeviceTab = new QWidget();
        PlusDeviceTab->setObjectName(QString::fromUtf8("PlusDeviceTab"));
        twDevices->addTab(PlusDeviceTab, QString());

        GeometryTabManagerLayout->addWidget(twDevices);

        splitter_2->addWidget(DeviceTabManagerWidget);

        verticalLayout_46->addWidget(splitter_2);


        verticalLayout_15->addWidget(tabManagerLayout);

        RobotWindow->setCentralWidget(centralWidget);

        retranslateUi(RobotWindow);
        QObject::connect(pbCalibStep2, SIGNAL(toggled(bool)), fCalibStep2, SLOT(setVisible(bool)));
        QObject::connect(gbImageProvider, SIGNAL(toggled(bool)), fImageProvider, SLOT(setVisible(bool)));
        QObject::connect(gbCameraCalibration, SIGNAL(toggled(bool)), fCameraCalibrationFrame, SLOT(setVisible(bool)));
        QObject::connect(pbCalibStep1, SIGNAL(toggled(bool)), fCalibStep1, SLOT(setVisible(bool)));
        QObject::connect(gbCameraVariable, SIGNAL(toggled(bool)), fVisionVariableFrame, SLOT(setVisible(bool)));
        QObject::connect(gbCameraObject, SIGNAL(toggled(bool)), fVisionObjectFrame, SLOT(setVisible(bool)));

        twDeltaManager->setCurrentIndex(0);
        twModule->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);
        pbImageMapping->setDefault(false);
        cbImageSource->setCurrentIndex(0);
        twDevices->setCurrentIndex(2);
        RobotTabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(0);
        cbDivision->setCurrentIndex(1);
        tabWidget_3->setCurrentIndex(0);
        pbPump->setDefault(false);
        pbLaser->setDefault(false);
        pbGrip->setDefault(false);


        QMetaObject::connectSlotsByName(RobotWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RobotWindow)
    {
        RobotWindow->setWindowTitle(QCoreApplication::translate("RobotWindow", "Delta X Software - Version 0.9.5", nullptr));
        actionAdd->setText(QCoreApplication::translate("RobotWindow", "Add New", nullptr));
        actionRemove->setText(QCoreApplication::translate("RobotWindow", "Remove", nullptr));
        actionAbout->setText(QCoreApplication::translate("RobotWindow", "About", nullptr));
        actionGcode->setText(QCoreApplication::translate("RobotWindow", "Gcode", nullptr));
        actionSoftware->setText(QCoreApplication::translate("RobotWindow", "Software", nullptr));
        actionExecute_All->setText(QCoreApplication::translate("RobotWindow", "Execute All", nullptr));
        actionDelta_X_1->setText(QCoreApplication::translate("RobotWindow", "robot 1", nullptr));
        actionExecute->setText(QCoreApplication::translate("RobotWindow", "Execute", nullptr));
        actionBaudrate->setText(QCoreApplication::translate("RobotWindow", "Baudrate", nullptr));
        actionScale->setText(QCoreApplication::translate("RobotWindow", "Scale", nullptr));
        twDeltaManager->setTabText(twDeltaManager->indexOf(tabDefaultDelta), QCoreApplication::translate("RobotWindow", "robot 1", nullptr));
        twDeltaManager->setTabText(twDeltaManager->indexOf(tabAddNewDelta), QCoreApplication::translate("RobotWindow", "+", nullptr));
        label_122->setText(QCoreApplication::translate("RobotWindow", "IP", nullptr));
        leIP->setText(QCoreApplication::translate("RobotWindow", "127.0.0.1", nullptr));
        label_123->setText(QCoreApplication::translate("RobotWindow", "Port", nullptr));
        lePort->setText(QCoreApplication::translate("RobotWindow", "8844", nullptr));
#if QT_CONFIG(tooltip)
        tbServerConfig->setToolTip(QCoreApplication::translate("RobotWindow", "Config", nullptr));
#endif // QT_CONFIG(tooltip)
        tbServerConfig->setText(QString());
#if QT_CONFIG(tooltip)
        twModule->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        rbEditorCurrent->setText(QCoreApplication::translate("RobotWindow", "Current", nullptr));
#if QT_CONFIG(tooltip)
        pbExecuteGcodes->setToolTip(QCoreApplication::translate("RobotWindow", "Execute Gcode", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExecuteGcodes->setText(QCoreApplication::translate("RobotWindow", "Run", nullptr));
        label_7->setText(QCoreApplication::translate("RobotWindow", "Thread", nullptr));
        rbEditorStart->setText(QCoreApplication::translate("RobotWindow", "Begin", nullptr));
        cbProgramThreadID->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbProgramThreadID->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbProgramThreadID->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbProgramThreadID->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

#if QT_CONFIG(tooltip)
        pbOpenGcodeDocs->setToolTip(QCoreApplication::translate("RobotWindow", "Gcode Docs", nullptr));
#endif // QT_CONFIG(tooltip)
        pbOpenGcodeDocs->setText(QCoreApplication::translate("RobotWindow", "Format", nullptr));
#if QT_CONFIG(tooltip)
        pbSaveGcode->setToolTip(QCoreApplication::translate("RobotWindow", "Save Gcode Into File", nullptr));
#endif // QT_CONFIG(tooltip)
        pbSaveGcode->setText(QString());
#if QT_CONFIG(tooltip)
        pbCreateNewGcode->setToolTip(QCoreApplication::translate("RobotWindow", "Creat New Editor", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCreateNewGcode->setText(QString());
#if QT_CONFIG(tooltip)
        pbFormat->setToolTip(QCoreApplication::translate("RobotWindow", "Format Gcode Lines", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFormat->setText(QCoreApplication::translate("RobotWindow", "Format", nullptr));
        cbEditGcodeEditor->setText(QCoreApplication::translate("RobotWindow", "Edit", nullptr));
        label_119->setText(QCoreApplication::translate("RobotWindow", "Home", nullptr));
#if QT_CONFIG(tooltip)
        tbAddG28->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddG28->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddG28->setText(QCoreApplication::translate("RobotWindow", "G28", nullptr));
        label_120->setText(QCoreApplication::translate("RobotWindow", "Move", nullptr));
#if QT_CONFIG(tooltip)
        tbAddG01->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddG01->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddG01->setText(QCoreApplication::translate("RobotWindow", "G01", nullptr));
#if QT_CONFIG(tooltip)
        tbAddG02->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddG02->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddG02->setText(QCoreApplication::translate("RobotWindow", "G02", nullptr));
        label_121->setText(QCoreApplication::translate("RobotWindow", "Sleep", nullptr));
#if QT_CONFIG(tooltip)
        tbAddG04->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddG04->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddG04->setText(QCoreApplication::translate("RobotWindow", "G04", nullptr));
        label_127->setText(QCoreApplication::translate("RobotWindow", "Output", nullptr));
#if QT_CONFIG(tooltip)
        tbAddM03->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddM03->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddM03->setText(QCoreApplication::translate("RobotWindow", "M03", nullptr));
#if QT_CONFIG(tooltip)
        tbAddM05->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddM05->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddM05->setText(QCoreApplication::translate("RobotWindow", "M05", nullptr));
        label_131->setText(QCoreApplication::translate("RobotWindow", "Input", nullptr));
#if QT_CONFIG(tooltip)
        tbAddM07->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddM07->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddM07->setText(QCoreApplication::translate("RobotWindow", "M07", nullptr));
#if QT_CONFIG(tooltip)
        tbAddM08->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbAddM08->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbAddM08->setText(QCoreApplication::translate("RobotWindow", "M08", nullptr));
        pteGcodeArea->setHtml(QCoreApplication::translate("RobotWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Delta X 2 Example</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" color:#000000;\">N05</span> <span style=\" font-weight:600;\">G28</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-righ"
                        "t:0px; -qt-block-indent:0; text-indent:0px; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Acceleration</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N10 <span style=\" font-weight:600;\">M204</span> A1200</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Speed</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N15 <span style=\" font-weight:600;\">G01</span> F200</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:"
                        "0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Declare variables</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N20 <span style=\" font-style:italic;\">#100</span> = 0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N30 <span style=\" font-style:italic;\">#100</span> = <span style=\" font-style:italic;\">#100</span> + 1</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#55aa00;\">;Call subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-lef"
                        "t:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N35 <span style=\" font-weight:600;\">M98</span> P2000</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">; Begin subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N40 <span style=\" font-weight:600;\">O2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N45 <span style=\" font-weight:600;\">G01</span> Z-350</p>\n"
"<p sty"
                        "le=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N50 <span style=\" font-weight:600;\">G01</span> X-100</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N55 <span style=\" font-weight:600;\">G01</span> Z-370</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N60 <span style=\" font-weight:600;\">G01</span> Z-350</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N65 <span style=\" font-weight:600;\">G01</span> X100</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N70 <span styl"
                        "e=\" font-weight:600;\">G01</span> Z-370</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N75 M99</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;End subprogram</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-style:italic; color:#00aa00;\">;Loop 5 times</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N80 <span style=\" font-weight:600; color:#00aa00;\">IF</span> [<span style=\" font-style:italic;\">#100</span> LE 5] <span style=\" font-weight:600; col"
                        "or:#00aa00;\">THEN</span> <span style=\" font-weight:600; color:#ff5500;\">GOTO</span> 30</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">N85 <span style=\" font-weight:600;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> </p></body></html>", nullptr));
        label_49->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_118->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_134->setText(QCoreApplication::translate("RobotWindow", "Z", nullptr));
        label_135->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        label_141->setText(QCoreApplication::translate("RobotWindow", "U", nullptr));
        label_142->setText(QCoreApplication::translate("RobotWindow", "V", nullptr));
        label_148->setText(QCoreApplication::translate("RobotWindow", "F", nullptr));
        label_149->setText(QCoreApplication::translate("RobotWindow", "A", nullptr));
        label_150->setText(QCoreApplication::translate("RobotWindow", "S", nullptr));
        label_151->setText(QCoreApplication::translate("RobotWindow", "E", nullptr));
        label_152->setText(QCoreApplication::translate("RobotWindow", "J", nullptr));
        label_3->setText(QCoreApplication::translate("RobotWindow", "Path", nullptr));
#if QT_CONFIG(tooltip)
        tbOpenGcodePath->setToolTip(QCoreApplication::translate("RobotWindow", "Open gcode folder", nullptr));
#endif // QT_CONFIG(tooltip)
        tbOpenGcodePath->setText(QString());
#if QT_CONFIG(tooltip)
        tbBackGcodeFolder->setToolTip(QCoreApplication::translate("RobotWindow", "Back", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbBackGcodeFolder->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbBackGcodeFolder->setText(QString());
#if QT_CONFIG(tooltip)
        tbNewGcodeFile->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbNewGcodeFile->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbNewGcodeFile->setText(QString());
#if QT_CONFIG(tooltip)
        tbRefreshExplorer->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbRefreshExplorer->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbRefreshExplorer->setText(QString());
#if QT_CONFIG(tooltip)
        tbDeleteGcodeFile->setToolTip(QCoreApplication::translate("RobotWindow", "New", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        tbDeleteGcodeFile->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        tbDeleteGcodeFile->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("RobotWindow", "Explorer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("RobotWindow", "Cloud", nullptr));
        twModule->setTabText(twModule->indexOf(tGcodeEditor), QCoreApplication::translate("RobotWindow", "Gcode Editor", nullptr));
        label_191->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
        cbSelectedDetecting->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbSelectedDetecting->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbSelectedDetecting->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbSelectedDetecting->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

        gbImageViewer->setTitle(QCoreApplication::translate("RobotWindow", "Image Viewer", nullptr));
#if QT_CONFIG(tooltip)
        pbFindChessboardTool->setToolTip(QCoreApplication::translate("RobotWindow", "Warp Perspective", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFindChessboardTool->setText(QString());
#if QT_CONFIG(tooltip)
        pbWarpTool->setToolTip(QCoreApplication::translate("RobotWindow", "Warp Perspective", nullptr));
#endif // QT_CONFIG(tooltip)
        pbWarpTool->setText(QString());
#if QT_CONFIG(tooltip)
        pbAreaTool->setToolTip(QCoreApplication::translate("RobotWindow", "Warp Perspective", nullptr));
#endif // QT_CONFIG(tooltip)
        pbAreaTool->setText(QString());
#if QT_CONFIG(tooltip)
        pbCalibPointTool->setToolTip(QCoreApplication::translate("RobotWindow", "Set Calib Point", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCalibPointTool->setText(QString());
#if QT_CONFIG(tooltip)
        pbMappingPointTool->setToolTip(QCoreApplication::translate("RobotWindow", "Check Point Position On Camera", nullptr));
#endif // QT_CONFIG(tooltip)
        pbMappingPointTool->setText(QString());
#if QT_CONFIG(tooltip)
        pbGetSizeTool->setToolTip(QCoreApplication::translate("RobotWindow", "Get size tool", nullptr));
#endif // QT_CONFIG(tooltip)
        pbGetSizeTool->setText(QString());
#if QT_CONFIG(tooltip)
        pbFilterTool->setToolTip(QCoreApplication::translate("RobotWindow", "Blob Filter", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFilterTool->setText(QString());
#if QT_CONFIG(tooltip)
        pbOpenObjectTable->setToolTip(QCoreApplication::translate("RobotWindow", "Open Object Table", nullptr));
#endif // QT_CONFIG(tooltip)
        pbOpenObjectTable->setText(QString());
#if QT_CONFIG(tooltip)
        pbClearObject->setToolTip(QCoreApplication::translate("RobotWindow", "Clear All Objects", nullptr));
#endif // QT_CONFIG(tooltip)
        pbClearObject->setText(QString());
        label_213->setText(QCoreApplication::translate("RobotWindow", "Output", nullptr));
        cbImageOutput->setItemText(0, QCoreApplication::translate("RobotWindow", "Calibrating", nullptr));
        cbImageOutput->setItemText(1, QCoreApplication::translate("RobotWindow", "Detecting", nullptr));
        cbImageOutput->setItemText(2, QCoreApplication::translate("RobotWindow", "Original", nullptr));

        lbDisplayRatio_2->setText(QCoreApplication::translate("RobotWindow", "Zoom:", nullptr));
        lbDisplayRatio_3->setText(QCoreApplication::translate("RobotWindow", "Ctrl + Scroll", nullptr));
        lbDisplayRatio->setText(QCoreApplication::translate("RobotWindow", "Ratio: 100%", nullptr));
        lbMatSize->setText(QCoreApplication::translate("RobotWindow", "Re: 800x500", nullptr));
        gbImageProvider->setTitle(QCoreApplication::translate("RobotWindow", "Image Provider", nullptr));
        label_176->setText(QCoreApplication::translate("RobotWindow", "Source", nullptr));
        cbSourceForImageProvider->setItemText(0, QCoreApplication::translate("RobotWindow", "Webcam", nullptr));
        cbSourceForImageProvider->setItemText(1, QCoreApplication::translate("RobotWindow", "Industrial Camera", nullptr));
        cbSourceForImageProvider->setItemText(2, QCoreApplication::translate("RobotWindow", "Images", nullptr));
        cbSourceForImageProvider->setItemText(3, QCoreApplication::translate("RobotWindow", "Socket", nullptr));

        label_6->setText(QCoreApplication::translate("RobotWindow", "Encoder", nullptr));
        cbEncoderForCamera->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbEncoderForCamera->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbEncoderForCamera->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbEncoderForCamera->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

#if QT_CONFIG(tooltip)
        pbLoadCamera->setToolTip(QCoreApplication::translate("RobotWindow", "Load Camera", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLoadCamera->setText(QCoreApplication::translate("RobotWindow", "Load Camera", nullptr));
#if QT_CONFIG(tooltip)
        pbLoadTestImage->setToolTip(QCoreApplication::translate("RobotWindow", "Load Image", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLoadTestImage->setText(QCoreApplication::translate("RobotWindow", "Load Image", nullptr));
        label_178->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        leImageWidth->setText(QCoreApplication::translate("RobotWindow", "800", nullptr));
        label_179->setText(QCoreApplication::translate("RobotWindow", "H", nullptr));
        leImageHeight->setText(QCoreApplication::translate("RobotWindow", "500", nullptr));
        label_73->setText(QCoreApplication::translate("RobotWindow", "Interval", nullptr));
        leCaptureInterval->setText(QCoreApplication::translate("RobotWindow", "500", nullptr));
        label_128->setText(QCoreApplication::translate("RobotWindow", "ms", nullptr));
#if QT_CONFIG(tooltip)
        pbStartAcquisition->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Play and Pause</p><p>M98 PpauseCamera</p><p>M98 PresumeCamera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pbStartAcquisition->setText(QString());
#if QT_CONFIG(tooltip)
        pbCapture->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Capture</p><p>M98 PcaptureCamera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCapture->setText(QString());
        lbCameraState->setText(QString());
        gbCameraCalibration->setTitle(QCoreApplication::translate("RobotWindow", "Calibration", nullptr));
        pbCalibStep1->setText(QCoreApplication::translate("RobotWindow", "Step 1: Identify the 4 corners of the square for perspective correction", nullptr));
        label_109->setText(QCoreApplication::translate("RobotWindow", "Image 1", nullptr));
        label_110->setText(QCoreApplication::translate("RobotWindow", "Image 2", nullptr));
        pbCalibStep2->setText(QCoreApplication::translate("RobotWindow", "Step 2: Coordinate correction", nullptr));
        leRealityPoint2X->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        leRealityPoint1Y->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        pbCalibPoint1->setText(QCoreApplication::translate("RobotWindow", "Point 1", nullptr));
#if QT_CONFIG(shortcut)
        pbCalibPoint1->setShortcut(QCoreApplication::translate("RobotWindow", "!", nullptr));
#endif // QT_CONFIG(shortcut)
        label_140->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
#if QT_CONFIG(tooltip)
        pbImageMapping->setToolTip(QCoreApplication::translate("RobotWindow", "Perspective Transformation", nullptr));
#endif // QT_CONFIG(tooltip)
        pbImageMapping->setText(QCoreApplication::translate("RobotWindow", "Calculate Mapping Matrix", nullptr));
        leRealityPoint2Y->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        leRealityPoint1X->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_133->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_139->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_39->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_132->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_38->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        pbCalibPoint2->setText(QCoreApplication::translate("RobotWindow", "Point 2", nullptr));
#if QT_CONFIG(shortcut)
        pbCalibPoint2->setShortcut(QCoreApplication::translate("RobotWindow", "@", nullptr));
#endif // QT_CONFIG(shortcut)
        gbCameraObject->setTitle(QCoreApplication::translate("RobotWindow", "Object", nullptr));
        label_126->setText(QCoreApplication::translate("RobotWindow", "Detection algorithm", nullptr));
        cbDetectingAlgorithm->setItemText(0, QCoreApplication::translate("RobotWindow", "Find Blobs", nullptr));
        cbDetectingAlgorithm->setItemText(1, QCoreApplication::translate("RobotWindow", "Find Circles", nullptr));
        cbDetectingAlgorithm->setItemText(2, QCoreApplication::translate("RobotWindow", "External Script", nullptr));

        label_45->setText(QCoreApplication::translate("RobotWindow", "Overlay", nullptr));
        leObjectOverlay->setText(QCoreApplication::translate("RobotWindow", "1.0", nullptr));
        leMaxWRec->setText(QCoreApplication::translate("RobotWindow", "1.5", nullptr));
        label_172->setText(QCoreApplication::translate("RobotWindow", "Min", nullptr));
        leMinLRec->setText(QCoreApplication::translate("RobotWindow", "0.5", nullptr));
        leMaxLRec->setText(QCoreApplication::translate("RobotWindow", "1.5", nullptr));
        leWRec->setText(QCoreApplication::translate("RobotWindow", "30", nullptr));
        label_173->setText(QCoreApplication::translate("RobotWindow", "Max", nullptr));
        leLRec->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
        label_175->setText(QCoreApplication::translate("RobotWindow", "Max", nullptr));
        label_43->setText(QCoreApplication::translate("RobotWindow", "Length", nullptr));
        label_163->setText(QCoreApplication::translate("RobotWindow", "Type", nullptr));
        label_54->setText(QCoreApplication::translate("RobotWindow", "pixel", nullptr));
        leMinWRec->setText(QCoreApplication::translate("RobotWindow", "0.5", nullptr));
        label_55->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        cbObjectType->setItemText(0, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbObjectType->setItemText(1, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbObjectType->setItemText(2, QCoreApplication::translate("RobotWindow", "3", nullptr));
        cbObjectType->setItemText(3, QCoreApplication::translate("RobotWindow", "4", nullptr));
        cbObjectType->setItemText(4, QCoreApplication::translate("RobotWindow", "5", nullptr));
        cbObjectType->setItemText(5, QCoreApplication::translate("RobotWindow", "+", nullptr));

        label_42->setText(QCoreApplication::translate("RobotWindow", "Width", nullptr));
        label_174->setText(QCoreApplication::translate("RobotWindow", "Min", nullptr));
        pbRunExternalScript->setText(QString());
        cbImageSource->setItemText(0, QCoreApplication::translate("RobotWindow", "Origin Image", nullptr));
        cbImageSource->setItemText(1, QCoreApplication::translate("RobotWindow", "Calibrated Image", nullptr));
        cbImageSource->setItemText(2, QCoreApplication::translate("RobotWindow", "Color Filtered Image", nullptr));

        label_180->setText(QCoreApplication::translate("RobotWindow", "Host IP", nullptr));
        label_183->setText(QCoreApplication::translate("RobotWindow", "8844", nullptr));
        label_187->setText(QCoreApplication::translate("RobotWindow", "string: \"#Object = [x],[y],[width],[height],[angle];\"", nullptr));
        label_185->setText(QCoreApplication::translate("RobotWindow", "Receive format", nullptr));
        label_146->setText(QCoreApplication::translate("RobotWindow", "Transmission Image", nullptr));
        pbExternalScriptOpen->setText(QString());
        label_184->setText(QCoreApplication::translate("RobotWindow", "Sending format", nullptr));
        label_145->setText(QCoreApplication::translate("RobotWindow", "Python Url", nullptr));
        pbExternalScriptHelp->setText(QCoreApplication::translate("RobotWindow", "?", nullptr));
        label_186->setText(QCoreApplication::translate("RobotWindow", "byte: \"[width][height][channel][data]\"", nullptr));
        label_182->setText(QCoreApplication::translate("RobotWindow", "Port", nullptr));
        label_181->setText(QCoreApplication::translate("RobotWindow", "127.0.0.1", nullptr));
        lePythonUrl->setText(QCoreApplication::translate("RobotWindow", "script-example/mushroom-2.0.py", nullptr));
        pbOpenScriptExample->setText(QCoreApplication::translate("RobotWindow", "Open script example", nullptr));
        leCenterThreshold->setText(QCoreApplication::translate("RobotWindow", "30", nullptr));
        leEdgeThreshold->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        label_193->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_190->setText(QCoreApplication::translate("RobotWindow", "Center Threshold", nullptr));
        label_192->setText(QCoreApplication::translate("RobotWindow", "Min Radius", nullptr));
        leMaxRadius->setText(QCoreApplication::translate("RobotWindow", "30", nullptr));
        label_194->setText(QCoreApplication::translate("RobotWindow", "Max Radius", nullptr));
        label_195->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        leMinRadius->setText(QCoreApplication::translate("RobotWindow", "5", nullptr));
        label_188->setText(QCoreApplication::translate("RobotWindow", "Edge Threshold", nullptr));
        gbCameraVariable->setTitle(QCoreApplication::translate("RobotWindow", "Variable", nullptr));
        label_196->setText(QCoreApplication::translate("RobotWindow", "Detecting Object List Name", nullptr));
        leDetectingObjectListName->setText(QCoreApplication::translate("RobotWindow", "#Objects", nullptr));
        pbViewDataObjects->setText(QCoreApplication::translate("RobotWindow", "Object Table", nullptr));
#if QT_CONFIG(tooltip)
        pbClearDetectObjects->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Clear All Objects in Memory</p><p>M98 PclearObjects --&gt; Clear All</p><p>M98 PdeleteFirstObject --&gt; Delete First</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbClearDetectObjects->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbClearDetectObjects->setText(QCoreApplication::translate("RobotWindow", "Clear Objects", nullptr));
        lbTrackingObjectNumber->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_155->setText(QCoreApplication::translate("RobotWindow", "Max X", nullptr));
        label_56->setText(QCoreApplication::translate("RobotWindow", "Min X", nullptr));
        label_50->setText(QCoreApplication::translate("RobotWindow", "Visible", nullptr));
        leLimitMinX->setText(QCoreApplication::translate("RobotWindow", "-300", nullptr));
        label_44->setText(QCoreApplication::translate("RobotWindow", "Limit Area", nullptr));
        lbVisibleObjectNumber->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_48->setText(QCoreApplication::translate("RobotWindow", "Tracking", nullptr));
        leLimitMaxX->setText(QCoreApplication::translate("RobotWindow", "1200", nullptr));
        label_156->setText(QCoreApplication::translate("RobotWindow", "Min Y", nullptr));
        label_157->setText(QCoreApplication::translate("RobotWindow", "Max Y", nullptr));
        leLimitMinY->setText(QCoreApplication::translate("RobotWindow", "-400", nullptr));
        leLimitMaxY->setText(QCoreApplication::translate("RobotWindow", "400", nullptr));
        twModule->setTabText(twModule->indexOf(tObjectDetecting), QCoreApplication::translate("RobotWindow", "Object Detecting", nullptr));
        gbImageProvider_2->setTitle(QCoreApplication::translate("RobotWindow", "Tracking Manager", nullptr));
        leDeviationAngle->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_164->setText(QCoreApplication::translate("RobotWindow", "Encoder", nullptr));
        cbTrackingEncoderSource->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbTrackingEncoderSource->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbTrackingEncoderSource->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));

        label_144->setText(QCoreApplication::translate("RobotWindow", "List", nullptr));
        cbReverseEncoderValue->setText(QCoreApplication::translate("RobotWindow", "Reverse Value", nullptr));
        label_167->setText(QCoreApplication::translate("RobotWindow", "Direction", nullptr));
        cbSelectedTracking->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbSelectedTracking->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbSelectedTracking->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbSelectedTracking->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

        cbTrackingDirection->setItemText(0, QCoreApplication::translate("RobotWindow", "X", nullptr));
        cbTrackingDirection->setItemText(1, QCoreApplication::translate("RobotWindow", "Y", nullptr));

        label_168->setText(QCoreApplication::translate("RobotWindow", "Deviation angle", nullptr));
        label_160->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
        label_169->setText(QCoreApplication::translate("RobotWindow", "degree", nullptr));
        leSelectedTrackingObjectList->setText(QCoreApplication::translate("RobotWindow", "#Objects", nullptr));
        gbCameraCalibration_3->setTitle(QCoreApplication::translate("RobotWindow", "Angle", nullptr));
        pbCalculateAngle->setText(QCoreApplication::translate("RobotWindow", "Calculate", nullptr));
        label_189->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_206->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_224->setText(QCoreApplication::translate("RobotWindow", "Angle (degree)", nullptr));
        pbAnglePoint1->setText(QCoreApplication::translate("RobotWindow", "Point 1", nullptr));
        pbAnglePoint2->setText(QCoreApplication::translate("RobotWindow", "Point 2", nullptr));
        gbCameraCalibration_4->setTitle(QCoreApplication::translate("RobotWindow", "Vector", nullptr));
        label_226->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_227->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_228->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        leAngleResult_3->setText(QCoreApplication::translate("RobotWindow", "#Vector1", nullptr));
        label_229->setText(QCoreApplication::translate("RobotWindow", "Name", nullptr));
        label_197->setText(QCoreApplication::translate("RobotWindow", "Speed", nullptr));
        label_209->setText(QCoreApplication::translate("RobotWindow", "Angle", nullptr));
        pbCalculateAngle_2->setText(QCoreApplication::translate("RobotWindow", "Calculate", nullptr));
        gbCameraCalibration_2->setTitle(QCoreApplication::translate("RobotWindow", "Matrix", nullptr));
        pbAddVariablePoint_2->setText(QCoreApplication::translate("RobotWindow", "Add Matrix", nullptr));
        label_202->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_203->setText(QCoreApplication::translate("RobotWindow", "Point 1", nullptr));
        label_204->setText(QCoreApplication::translate("RobotWindow", "Point 1", nullptr));
        label_166->setText(QCoreApplication::translate("RobotWindow", "Source", nullptr));
        label_200->setText(QCoreApplication::translate("RobotWindow", "Destination", nullptr));
        label_165->setText(QCoreApplication::translate("RobotWindow", "Name", nullptr));
        label_201->setText(QCoreApplication::translate("RobotWindow", "Point 2", nullptr));
        leMatrix1Name->setText(QCoreApplication::translate("RobotWindow", "#Matrix1", nullptr));
        label_177->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_205->setText(QCoreApplication::translate("RobotWindow", "Point 2", nullptr));
        pbCalculateMappingMatrixTool->setText(QCoreApplication::translate("RobotWindow", "Calculate", nullptr));
        gbCameraObject_2->setTitle(QCoreApplication::translate("RobotWindow", "Point", nullptr));
        pbAddVariablePoint->setText(QCoreApplication::translate("RobotWindow", "Add Point", nullptr));
        label_136->setText(QCoreApplication::translate("RobotWindow", "Name", nullptr));
        lePoint1Name->setText(QCoreApplication::translate("RobotWindow", "#Point1", nullptr));
        label_137->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_138->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_143->setText(QCoreApplication::translate("RobotWindow", "Z", nullptr));
        gbCameraObject_3->setTitle(QCoreApplication::translate("RobotWindow", "Point Matrix", nullptr));
        pbAddVariablePoint_3->setText(QCoreApplication::translate("RobotWindow", "Add Point", nullptr));
        label_210->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_218->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_211->setText(QCoreApplication::translate("RobotWindow", "Point 1", nullptr));
        label_212->setText(QCoreApplication::translate("RobotWindow", "Point 3", nullptr));
        label_216->setText(QCoreApplication::translate("RobotWindow", "Name", nullptr));
        lePointMatrixName->setText(QCoreApplication::translate("RobotWindow", "#PointMatrix", nullptr));
        label_217->setText(QCoreApplication::translate("RobotWindow", "Point 2", nullptr));
        label_219->setText(QCoreApplication::translate("RobotWindow", "Point 4", nullptr));
        pbCalculatePointMatrixTool->setText(QCoreApplication::translate("RobotWindow", "Calculate", nullptr));
        gbCameraObject_4->setTitle(QCoreApplication::translate("RobotWindow", "Test", nullptr));
        leTestMatrixName->setText(QCoreApplication::translate("RobotWindow", "#PointMatrix", nullptr));
        pbCalculateTestPoint->setText(QCoreApplication::translate("RobotWindow", "Calculate", nullptr));
        label_215->setText(QCoreApplication::translate("RobotWindow", "Point", nullptr));
        label_223->setText(QCoreApplication::translate("RobotWindow", "multiply", nullptr));
        label_222->setText(QCoreApplication::translate("RobotWindow", "Matrix", nullptr));
        label_221->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_214->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        twModule->setTabText(twModule->indexOf(tPointTool), QCoreApplication::translate("RobotWindow", "Point Tool", nullptr));
        pbOpenPicture->setText(QCoreApplication::translate("RobotWindow", "Load Image", nullptr));
        lbImageForDrawing->setText(QString());
        lbImageWidth->setText(QCoreApplication::translate("RobotWindow", "W: 300", nullptr));
        lbImageHeight->setText(QCoreApplication::translate("RobotWindow", "H: 100", nullptr));
        cbConversionTool->setItemText(0, QCoreApplication::translate("RobotWindow", "Threshold", nullptr));
        cbConversionTool->setItemText(1, QCoreApplication::translate("RobotWindow", "Vectorize", nullptr));
        cbConversionTool->setItemText(2, QCoreApplication::translate("RobotWindow", "Gray", nullptr));

        leDrawingThreshold->setText(QCoreApplication::translate("RobotWindow", "150", nullptr));
        label_14->setText(QCoreApplication::translate("RobotWindow", "Conversion Tool", nullptr));
        label_105->setText(QCoreApplication::translate("RobotWindow", "Reverse", nullptr));
        cbReverseDrawing->setText(QString());
        pbPainting->setText(QCoreApplication::translate("RobotWindow", "Draw", nullptr));
        label_20->setText(QCoreApplication::translate("RobotWindow", "Height", nullptr));
        label_18->setText(QCoreApplication::translate("RobotWindow", "Width", nullptr));
        cbLockDrawingArea->setItemText(0, QCoreApplication::translate("RobotWindow", "Height", nullptr));
        cbLockDrawingArea->setItemText(1, QCoreApplication::translate("RobotWindow", "Width", nullptr));

        label_104->setText(QCoreApplication::translate("RobotWindow", "Lock", nullptr));
        leWidthScale->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        leHeightScale->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        label_21->setText(QCoreApplication::translate("RobotWindow", "100%", nullptr));
        lbDrawingArea->setText(QString());
        label_26->setText(QCoreApplication::translate("RobotWindow", "O", nullptr));
        label_25->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        label_24->setText(QCoreApplication::translate("RobotWindow", "H", nullptr));
        label_22->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_19->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        leDrawAg1->setText(QString());
        pbDrawLine->setText(QCoreApplication::translate("RobotWindow", "Line", nullptr));
        pbDrawRectangle->setText(QCoreApplication::translate("RobotWindow", "Rectangle", nullptr));
        pbZoomIn->setText(QCoreApplication::translate("RobotWindow", "Zoom In", nullptr));
        pbCursor->setText(QCoreApplication::translate("RobotWindow", "Cursor", nullptr));
        pbDrawArc->setText(QCoreApplication::translate("RobotWindow", "Arc", nullptr));
        pbDrawCircle->setText(QCoreApplication::translate("RobotWindow", "Circle", nullptr));
        pbZoomOut->setText(QCoreApplication::translate("RobotWindow", "Zoom Out", nullptr));
        pbExportDrawingGcodes->setText(QCoreApplication::translate("RobotWindow", "Export G-code", nullptr));
        label_96->setText(QCoreApplication::translate("RobotWindow", "Travel Speed", nullptr));
        label_101->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        label_13->setText(QCoreApplication::translate("RobotWindow", "Move Type", nullptr));
        label_97->setText(QCoreApplication::translate("RobotWindow", "Drawing Speed", nullptr));
        cbDrawMethod->setItemText(0, QCoreApplication::translate("RobotWindow", "Line", nullptr));
        cbDrawMethod->setItemText(1, QCoreApplication::translate("RobotWindow", "Dot", nullptr));

        cbDrawingEffector->setItemText(0, QCoreApplication::translate("RobotWindow", "Laser", nullptr));
        cbDrawingEffector->setItemText(1, QCoreApplication::translate("RobotWindow", "Pen", nullptr));

        label_102->setText(QCoreApplication::translate("RobotWindow", "mm/s2", nullptr));
        label_93->setText(QCoreApplication::translate("RobotWindow", "Drawing Tool", nullptr));
        label_95->setText(QCoreApplication::translate("RobotWindow", "Drawing Z Height", nullptr));
        label_100->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        label_98->setText(QCoreApplication::translate("RobotWindow", "Acceleration", nullptr));
        label_99->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_23->setText(QCoreApplication::translate("RobotWindow", "Density", nullptr));
        leSpace->setText(QCoreApplication::translate("RobotWindow", "1", nullptr));
        label_103->setText(QCoreApplication::translate("RobotWindow", "mm/dot(line)", nullptr));
        twModule->setTabText(twModule->indexOf(tDrawing), QCoreApplication::translate("RobotWindow", "Drawing", nullptr));
        teDebug->setHtml(QCoreApplication::translate("RobotWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("RobotWindow", "Sender", nullptr));
        label_5->setText(QCoreApplication::translate("RobotWindow", "Receiver", nullptr));
        cbDeviceSender->setItemText(0, QCoreApplication::translate("RobotWindow", "Software", nullptr));
        cbDeviceSender->setItemText(1, QCoreApplication::translate("RobotWindow", "Robot", nullptr));
        cbDeviceSender->setItemText(2, QCoreApplication::translate("RobotWindow", "Conveyor", nullptr));
        cbDeviceSender->setItemText(3, QCoreApplication::translate("RobotWindow", "Slider", nullptr));
        cbDeviceSender->setItemText(4, QCoreApplication::translate("RobotWindow", "External MCU", nullptr));
        cbDeviceSender->setItemText(5, QCoreApplication::translate("RobotWindow", "Encoder", nullptr));

        twModule->setTabText(twModule->indexOf(TermiteTab), QCoreApplication::translate("RobotWindow", "Termite", nullptr));
        pbConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        cbAutoConnect->setText(QCoreApplication::translate("RobotWindow", "Auto", nullptr));
        lbY->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_88->setText(QCoreApplication::translate("RobotWindow", "Z", nullptr));
        lbW->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbV->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbU->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_94->setText(QCoreApplication::translate("RobotWindow", "V", nullptr));
        lbX->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbZ->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_90->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        label_86->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_92->setText(QCoreApplication::translate("RobotWindow", "U", nullptr));
        label_84->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        cbSelectedRobot->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbSelectedRobot->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbSelectedRobot->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbSelectedRobot->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

        label->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
#if QT_CONFIG(tooltip)
        tbDisableRobot->setToolTip(QCoreApplication::translate("RobotWindow", "Creat New Editor", nullptr));
#endif // QT_CONFIG(tooltip)
        tbDisableRobot->setText(QCoreApplication::translate("RobotWindow", "Hold", nullptr));
#if QT_CONFIG(tooltip)
        tbRequestPosition->setToolTip(QCoreApplication::translate("RobotWindow", "Creat New Editor", nullptr));
#endif // QT_CONFIG(tooltip)
        tbRequestPosition->setText(QCoreApplication::translate("RobotWindow", "Position", nullptr));
        lbComName->setText(QCoreApplication::translate("RobotWindow", "NONE", nullptr));
        cbRobotModel->setItemText(0, QCoreApplication::translate("RobotWindow", "Delta X 1", nullptr));
        cbRobotModel->setItemText(1, QCoreApplication::translate("RobotWindow", "Delta X 2", nullptr));
        cbRobotModel->setItemText(2, QCoreApplication::translate("RobotWindow", "Delta X S", nullptr));
        cbRobotModel->setItemText(3, QCoreApplication::translate("RobotWindow", "Custom", nullptr));

        label_65->setText(QCoreApplication::translate("RobotWindow", "Baudrate", nullptr));
        lbBaudrate->setText(QCoreApplication::translate("RobotWindow", "115200", nullptr));
        label_91->setText(QCoreApplication::translate("RobotWindow", "Model", nullptr));
        label_113->setText(QCoreApplication::translate("RobotWindow", "DOF", nullptr));
        label_10->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
        cbRobotDOF->setItemText(0, QCoreApplication::translate("RobotWindow", "3 DOF", nullptr));
        cbRobotDOF->setItemText(1, QCoreApplication::translate("RobotWindow", "4 DOF", nullptr));
        cbRobotDOF->setItemText(2, QCoreApplication::translate("RobotWindow", "5 DOF", nullptr));
        cbRobotDOF->setItemText(3, QCoreApplication::translate("RobotWindow", "6 DOF", nullptr));

        RobotTabWidget->setTabText(RobotTabWidget->indexOf(ConfigurationTab), QCoreApplication::translate("RobotWindow", "Configuration", nullptr));
        label_106->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        pbsubY->setText(QCoreApplication::translate("RobotWindow", "-", nullptr));
#if QT_CONFIG(shortcut)
        pbsubY->setShortcut(QCoreApplication::translate("RobotWindow", "2", nullptr));
#endif // QT_CONFIG(shortcut)
        pbplusY->setText(QCoreApplication::translate("RobotWindow", "+", nullptr));
#if QT_CONFIG(shortcut)
        pbplusY->setShortcut(QCoreApplication::translate("RobotWindow", "8", nullptr));
#endif // QT_CONFIG(shortcut)
        label_9->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_40->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        pbsubX->setText(QCoreApplication::translate("RobotWindow", "-", nullptr));
#if QT_CONFIG(shortcut)
        pbsubX->setShortcut(QCoreApplication::translate("RobotWindow", "4", nullptr));
#endif // QT_CONFIG(shortcut)
        leX->setText(QString());
        pbplusX->setText(QCoreApplication::translate("RobotWindow", "+", nullptr));
#if QT_CONFIG(shortcut)
        pbplusX->setShortcut(QCoreApplication::translate("RobotWindow", "6", nullptr));
#endif // QT_CONFIG(shortcut)
        label_8->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_107->setText(QCoreApplication::translate("RobotWindow", "Z", nullptr));
        pbsubZ->setText(QCoreApplication::translate("RobotWindow", "-", nullptr));
#if QT_CONFIG(shortcut)
        pbsubZ->setShortcut(QCoreApplication::translate("RobotWindow", "3", nullptr));
#endif // QT_CONFIG(shortcut)
        pbplusZ->setText(QCoreApplication::translate("RobotWindow", "+", nullptr));
#if QT_CONFIG(shortcut)
        pbplusZ->setShortcut(QCoreApplication::translate("RobotWindow", "9", nullptr));
#endif // QT_CONFIG(shortcut)
        label_66->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_108->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        pbsubW->setText(QCoreApplication::translate("RobotWindow", "-", nullptr));
#if QT_CONFIG(shortcut)
        pbsubW->setShortcut(QCoreApplication::translate("RobotWindow", "1", nullptr));
#endif // QT_CONFIG(shortcut)
        pbplusW->setText(QCoreApplication::translate("RobotWindow", "+", nullptr));
#if QT_CONFIG(shortcut)
        pbplusW->setShortcut(QCoreApplication::translate("RobotWindow", "7", nullptr));
#endif // QT_CONFIG(shortcut)
        label_81->setText(QCoreApplication::translate("RobotWindow", "deg", nullptr));
        label_111->setText(QCoreApplication::translate("RobotWindow", "U", nullptr));
        pbsubU->setText(QCoreApplication::translate("RobotWindow", "-", nullptr));
        pbplusU->setText(QCoreApplication::translate("RobotWindow", "+", nullptr));
        label_87->setText(QCoreApplication::translate("RobotWindow", "deg", nullptr));
        label_112->setText(QCoreApplication::translate("RobotWindow", "V", nullptr));
        pbsubV->setText(QCoreApplication::translate("RobotWindow", "-", nullptr));
        pbplusV->setText(QCoreApplication::translate("RobotWindow", "+", nullptr));
        label_89->setText(QCoreApplication::translate("RobotWindow", "deg", nullptr));
        label_29->setText(QCoreApplication::translate("RobotWindow", "Velocity", nullptr));
        label_116->setText(QCoreApplication::translate("RobotWindow", "End", nullptr));
        label_63->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        leAccel->setText(QString());
        leAccel->setPlaceholderText(QCoreApplication::translate("RobotWindow", "None", nullptr));
        label_32->setText(QCoreApplication::translate("RobotWindow", "mm/s2", nullptr));
        label_117->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        leVelocity->setText(QString());
        leVelocity->setPlaceholderText(QCoreApplication::translate("RobotWindow", "None", nullptr));
        leStartSpeed->setText(QString());
        leStartSpeed->setPlaceholderText(QCoreApplication::translate("RobotWindow", "None", nullptr));
        label_62->setText(QCoreApplication::translate("RobotWindow", "Start", nullptr));
        leEndSpeed->setText(QString());
        leEndSpeed->setPlaceholderText(QCoreApplication::translate("RobotWindow", "None", nullptr));
        label_30->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        label_31->setText(QCoreApplication::translate("RobotWindow", "Accel", nullptr));
        label_64->setText(QCoreApplication::translate("RobotWindow", "mm/s3", nullptr));
        label_47->setText(QCoreApplication::translate("RobotWindow", "Jerk", nullptr));
        leEndSpeed_2->setText(QString());
        leEndSpeed_2->setPlaceholderText(QCoreApplication::translate("RobotWindow", "None", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_4), QCoreApplication::translate("RobotWindow", "Parameter", nullptr));
        cbDivision->setItemText(0, QCoreApplication::translate("RobotWindow", "0.5", nullptr));
        cbDivision->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbDivision->setItemText(2, QCoreApplication::translate("RobotWindow", "5", nullptr));
        cbDivision->setItemText(3, QCoreApplication::translate("RobotWindow", "10", nullptr));
        cbDivision->setItemText(4, QCoreApplication::translate("RobotWindow", "50", nullptr));
        cbDivision->setItemText(5, QCoreApplication::translate("RobotWindow", "100", nullptr));

        cbDivision->setCurrentText(QCoreApplication::translate("RobotWindow", "1", nullptr));
        pbHome->setText(QCoreApplication::translate("RobotWindow", "Home", nullptr));
        label_33->setText(QCoreApplication::translate("RobotWindow", "Step (mm)", nullptr));
#if QT_CONFIG(tooltip)
        pbLeft->setToolTip(QCoreApplication::translate("RobotWindow", "Left (shift + w)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbLeft->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbLeft->setText(QCoreApplication::translate("RobotWindow", "X-", nullptr));
#if QT_CONFIG(shortcut)
        pbLeft->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+A", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbRight->setToolTip(QCoreApplication::translate("RobotWindow", "Right (Shift +d)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbRight->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbRight->setText(QCoreApplication::translate("RobotWindow", "X+", nullptr));
#if QT_CONFIG(shortcut)
        pbRight->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+D", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbBackward->setToolTip(QCoreApplication::translate("RobotWindow", "Backward (shift + s)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbBackward->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbBackward->setText(QCoreApplication::translate("RobotWindow", "Y-", nullptr));
#if QT_CONFIG(shortcut)
        pbBackward->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbForward->setToolTip(QCoreApplication::translate("RobotWindow", "Forward (Shift + w)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbForward->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbForward->setText(QCoreApplication::translate("RobotWindow", "Y+", nullptr));
#if QT_CONFIG(shortcut)
        pbForward->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+W", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbSubRoll->setToolTip(QCoreApplication::translate("RobotWindow", "Left (shift + w)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbSubRoll->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbSubRoll->setText(QCoreApplication::translate("RobotWindow", "W-", nullptr));
#if QT_CONFIG(shortcut)
        pbSubRoll->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+A", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbPlusRoll->setToolTip(QCoreApplication::translate("RobotWindow", "Right (Shift +d)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbPlusRoll->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbPlusRoll->setText(QCoreApplication::translate("RobotWindow", "W+", nullptr));
#if QT_CONFIG(shortcut)
        pbPlusRoll->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+D", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbPlusYaw->setToolTip(QCoreApplication::translate("RobotWindow", "Right (Shift +d)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbPlusYaw->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbPlusYaw->setText(QCoreApplication::translate("RobotWindow", "U+", nullptr));
#if QT_CONFIG(shortcut)
        pbPlusYaw->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+D", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbSubYaw->setToolTip(QCoreApplication::translate("RobotWindow", "Left (shift + w)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbSubYaw->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbSubYaw->setText(QCoreApplication::translate("RobotWindow", "U-", nullptr));
#if QT_CONFIG(shortcut)
        pbSubYaw->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+A", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbPlusPitch->setToolTip(QCoreApplication::translate("RobotWindow", "Right (Shift +d)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbPlusPitch->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbPlusPitch->setText(QCoreApplication::translate("RobotWindow", "V+", nullptr));
#if QT_CONFIG(shortcut)
        pbPlusPitch->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+D", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbSubPitch->setToolTip(QCoreApplication::translate("RobotWindow", "Left (shift + w)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbSubPitch->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbSubPitch->setText(QCoreApplication::translate("RobotWindow", "V-", nullptr));
#if QT_CONFIG(shortcut)
        pbSubPitch->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+A", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbDown->setToolTip(QCoreApplication::translate("RobotWindow", "Down (shift + f)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbDown->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbDown->setText(QCoreApplication::translate("RobotWindow", "Z-", nullptr));
#if QT_CONFIG(shortcut)
        pbDown->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+F", nullptr));
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        pbUp->setToolTip(QCoreApplication::translate("RobotWindow", "Up (shift + r)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbUp->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbUp->setText(QCoreApplication::translate("RobotWindow", "Z+", nullptr));
#if QT_CONFIG(shortcut)
        pbUp->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+R", nullptr));
#endif // QT_CONFIG(shortcut)
        tabWidget_2->setTabText(tabWidget_2->indexOf(ButtonTab), QCoreApplication::translate("RobotWindow", "Button", nullptr));
        label_53->setText(QCoreApplication::translate("RobotWindow", "Size", nullptr));
        cbWorkingSize->setItemText(0, QCoreApplication::translate("RobotWindow", "300 x 300", nullptr));
        cbWorkingSize->setItemText(1, QCoreApplication::translate("RobotWindow", "400 x 400", nullptr));
        cbWorkingSize->setItemText(2, QCoreApplication::translate("RobotWindow", "600 x 600", nullptr));
        cbWorkingSize->setItemText(3, QCoreApplication::translate("RobotWindow", "800 x 800 ", nullptr));

        label_15->setText(QCoreApplication::translate("RobotWindow", "Z", nullptr));
        label_72->setText(QCoreApplication::translate("RobotWindow", "6-Axis", nullptr));
        label_69->setText(QCoreApplication::translate("RobotWindow", "4-Axis", nullptr));
        label_71->setText(QCoreApplication::translate("RobotWindow", "5-Axis", nullptr));
        lb4AxisValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lb5AxisValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lb6AxisValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_60->setText(QCoreApplication::translate("RobotWindow", "5-Axis", nullptr));
        label_61->setText(QCoreApplication::translate("RobotWindow", "6-Axis", nullptr));
        label_16->setText(QCoreApplication::translate("RobotWindow", "4-Axis", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(SliderTab), QCoreApplication::translate("RobotWindow", "Slider", nullptr));
        label_79->setText(QCoreApplication::translate("RobotWindow", "Sensibility", nullptr));
        cbJoystickDevice->setCurrentText(QString());
        label_41->setText(QCoreApplication::translate("RobotWindow", "Device", nullptr));
        leJoystickRange->setText(QCoreApplication::translate("RobotWindow", "1", nullptr));
        leJoystickSensibility->setText(QCoreApplication::translate("RobotWindow", "0.7", nullptr));
        label_51->setText(QCoreApplication::translate("RobotWindow", "Range", nullptr));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QCoreApplication::translate("RobotWindow", "Joystick", nullptr));
        RobotTabWidget->setTabText(RobotTabWidget->indexOf(MoveTab), QCoreApplication::translate("RobotWindow", "Move", nullptr));
        gbRelay->setTitle(QCoreApplication::translate("RobotWindow", "On/Off", nullptr));
        label_34->setText(QCoreApplication::translate("RobotWindow", "Vacuum", nullptr));
        label_35->setText(QCoreApplication::translate("RobotWindow", "Laser", nullptr));
        pbPump->setText(QString());
        pbLaser->setText(QString());
        gbGripper->setTitle(QCoreApplication::translate("RobotWindow", "RC Servo Gripper", nullptr));
        label_17->setText(QCoreApplication::translate("RobotWindow", "min", nullptr));
        label_27->setText(QCoreApplication::translate("RobotWindow", "max", nullptr));
        pbGrip->setText(QCoreApplication::translate("RobotWindow", "Grip", nullptr));
        leGripperMin->setText(QCoreApplication::translate("RobotWindow", "5", nullptr));
        leGripperMax->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        lbGripperValue->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        gbOutput->setTitle(QCoreApplication::translate("RobotWindow", "Output", nullptr));
        cbDx->setText(QString());
        cbRx->setText(QString());
        label_67->setText(QCoreApplication::translate("RobotWindow", "Custom", nullptr));
        leRx->setText(QCoreApplication::translate("RobotWindow", "R0", nullptr));
        leDx->setText(QCoreApplication::translate("RobotWindow", "D0", nullptr));
        label_68->setText(QCoreApplication::translate("RobotWindow", "Digital", nullptr));
        cbD1->setText(QCoreApplication::translate("RobotWindow", "D1", nullptr));
        cbD2->setText(QCoreApplication::translate("RobotWindow", "D2", nullptr));
        cbD3->setText(QCoreApplication::translate("RobotWindow", "D3", nullptr));
        cbD0->setText(QCoreApplication::translate("RobotWindow", "D0", nullptr));
        cbD4->setText(QCoreApplication::translate("RobotWindow", "D4", nullptr));
        cbD5->setText(QCoreApplication::translate("RobotWindow", "D5", nullptr));
        cbD6->setText(QCoreApplication::translate("RobotWindow", "D6", nullptr));
        cbD7->setText(QCoreApplication::translate("RobotWindow", "D7", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(OutputTab), QCoreApplication::translate("RobotWindow", "Output", nullptr));
        gbInput->setTitle(QCoreApplication::translate("RobotWindow", "Input", nullptr));
        label_70->setText(QCoreApplication::translate("RobotWindow", "I0", nullptr));
        lbI0Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
#if QT_CONFIG(tooltip)
        cbToggle0->setToolTip(QCoreApplication::translate("RobotWindow", "The robot will respond when the value of digital input pin changes", nullptr));
#endif // QT_CONFIG(tooltip)
        cbToggle0->setText(QCoreApplication::translate("RobotWindow", "wait toggle", nullptr));
        pbReadI0->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        label_74->setText(QCoreApplication::translate("RobotWindow", "I1", nullptr));
        lbI1Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
#if QT_CONFIG(tooltip)
        cbToggle1->setToolTip(QCoreApplication::translate("RobotWindow", "The robot will respond when the value of digital input pin changes", nullptr));
#endif // QT_CONFIG(tooltip)
        cbToggle1->setText(QCoreApplication::translate("RobotWindow", "wait toggle", nullptr));
        pbReadI1->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        label_76->setText(QCoreApplication::translate("RobotWindow", "I2", nullptr));
        lbI2Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
#if QT_CONFIG(tooltip)
        cbToggle2->setToolTip(QCoreApplication::translate("RobotWindow", "The robot will respond when the value of digital input pin changes", nullptr));
#endif // QT_CONFIG(tooltip)
        cbToggle2->setText(QCoreApplication::translate("RobotWindow", "wait toggle", nullptr));
        pbReadI2->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        label_78->setText(QCoreApplication::translate("RobotWindow", "I3", nullptr));
        lbI3Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
#if QT_CONFIG(tooltip)
        cbToggle3->setToolTip(QCoreApplication::translate("RobotWindow", "The robot will respond when the value of digital input pin changes", nullptr));
#endif // QT_CONFIG(tooltip)
        cbToggle3->setText(QCoreApplication::translate("RobotWindow", "wait toggle", nullptr));
        pbReadI3->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        leIx->setText(QCoreApplication::translate("RobotWindow", "I4", nullptr));
        leIx->setPlaceholderText(QCoreApplication::translate("RobotWindow", "I", nullptr));
        lbIxValue->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
#if QT_CONFIG(tooltip)
        cbTogglex->setToolTip(QCoreApplication::translate("RobotWindow", "The robot will respond when the value of digital input pin changes", nullptr));
#endif // QT_CONFIG(tooltip)
        cbTogglex->setText(QCoreApplication::translate("RobotWindow", "wait toggle", nullptr));
        pbReadIx->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        label_83->setText(QCoreApplication::translate("RobotWindow", "A0", nullptr));
        lbA0Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
        leA0Delay->setPlaceholderText(QCoreApplication::translate("RobotWindow", "0 ms", nullptr));
        pbReadA0->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        label_85->setText(QCoreApplication::translate("RobotWindow", "A1", nullptr));
        lbA1Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
        leA1Delay->setPlaceholderText(QCoreApplication::translate("RobotWindow", "0 ms", nullptr));
        pbReadA1->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        leAx->setText(QCoreApplication::translate("RobotWindow", "A2", nullptr));
        leAx->setPlaceholderText(QCoreApplication::translate("RobotWindow", "I", nullptr));
        lbAxValue->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
        leAxDelay->setPlaceholderText(QCoreApplication::translate("RobotWindow", "0 ms", nullptr));
        pbReadAx->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        tabWidget_3->setTabText(tabWidget_3->indexOf(InputTab), QCoreApplication::translate("RobotWindow", "Input", nullptr));
        RobotTabWidget->setTabText(RobotTabWidget->indexOf(IOTab), QCoreApplication::translate("RobotWindow", "IO", nullptr));
        twDevices->setTabText(twDevices->indexOf(tRobot), QCoreApplication::translate("RobotWindow", "Robot", nullptr));
        pbConveyorConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        label_2->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
        cbSelectedConveyor->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbSelectedConveyor->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbSelectedConveyor->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbSelectedConveyor->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

        label_28->setText(QCoreApplication::translate("RobotWindow", "Type", nullptr));
        cbConveyorType->setItemText(0, QCoreApplication::translate("RobotWindow", "Conveyor X", nullptr));
        cbConveyorType->setItemText(1, QCoreApplication::translate("RobotWindow", "Conveyor Hub X", nullptr));
        cbConveyorType->setItemText(2, QCoreApplication::translate("RobotWindow", "Custom", nullptr));

        lbConveyorCOMName->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
#if QT_CONFIG(tooltip)
        leConveyorXPosition->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \342\200\223 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Seg"
                        "oe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSys"
                        "temFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background"
                        "-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        leConveyorXPosition->setText(QCoreApplication::translate("RobotWindow", "-100", nullptr));
        cbConveyorValueType->setItemText(0, QCoreApplication::translate("RobotWindow", "Continuous", nullptr));
        cbConveyorValueType->setItemText(1, QCoreApplication::translate("RobotWindow", "Position", nullptr));

        lbUnitOfConveyorMoving->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_57->setText(QCoreApplication::translate("RobotWindow", "Speed", nullptr));
        label_46->setText(QCoreApplication::translate("RobotWindow", "Moving Mode", nullptr));
        cbConveyorMode->setItemText(0, QCoreApplication::translate("RobotWindow", "Manual", nullptr));
        cbConveyorMode->setItemText(1, QCoreApplication::translate("RobotWindow", "UART", nullptr));

#if QT_CONFIG(tooltip)
        cbConveyorMode->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p><a name=\"31\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">310 \342\200\223 Set Mode</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description: .</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Se"
                        "goe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M310 [&lt;index&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">1: Serial Mode.</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">0: Volume Mode.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_12->setText(QCoreApplication::translate("RobotWindow", "Position", nullptr));
#if QT_CONFIG(tooltip)
        leConveyorXSpeed->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leConveyorXSpeed->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
        label_52->setText(QCoreApplication::translate("RobotWindow", "Control Mode", nullptr));
        lbSpeedOfPositionMode->setText(QCoreApplication::translate("RobotWindow", "mm/s2", nullptr));
        label_77->setText(QCoreApplication::translate("RobotWindow", "Position (mm)", nullptr));
#if QT_CONFIG(tooltip)
        leSubConveyor1Position->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leSubConveyor1Position->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
        label_115->setText(QCoreApplication::translate("RobotWindow", "Moving Mode", nullptr));
        label_114->setText(QCoreApplication::translate("RobotWindow", "C3", nullptr));
        cbSubConveyor2Mode->setItemText(0, QCoreApplication::translate("RobotWindow", "Continuous", nullptr));
        cbSubConveyor2Mode->setItemText(1, QCoreApplication::translate("RobotWindow", "Position", nullptr));

#if QT_CONFIG(tooltip)
        leSubConveyor1Speed->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \342\200\223 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Seg"
                        "oe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSys"
                        "temFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background"
                        "-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        leSubConveyor1Speed->setText(QCoreApplication::translate("RobotWindow", "-100", nullptr));
        label_75->setText(QCoreApplication::translate("RobotWindow", "C1", nullptr));
        label_82->setText(QCoreApplication::translate("RobotWindow", "C2", nullptr));
#if QT_CONFIG(tooltip)
        leSubConveyor2Position->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leSubConveyor2Position->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
#if QT_CONFIG(tooltip)
        leSubConveyor2Speed->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leSubConveyor2Speed->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
        cbSubConveyor3Mode->setItemText(0, QCoreApplication::translate("RobotWindow", "Continuous", nullptr));
        cbSubConveyor3Mode->setItemText(1, QCoreApplication::translate("RobotWindow", "Position", nullptr));

#if QT_CONFIG(tooltip)
        leSubConveyor3Speed->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leSubConveyor3Speed->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
        cbSubConveyor1Mode->setItemText(0, QCoreApplication::translate("RobotWindow", "Continuous", nullptr));
        cbSubConveyor1Mode->setItemText(1, QCoreApplication::translate("RobotWindow", "Position", nullptr));

        label_80->setText(QCoreApplication::translate("RobotWindow", "Speed (mm/s2)", nullptr));
#if QT_CONFIG(tooltip)
        leSubConveyor3Position->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leSubConveyor3Position->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
#if QT_CONFIG(tooltip)
        pbStopCustomConveyor2Command->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbStopCustomConveyor2Command->setText(QCoreApplication::translate("RobotWindow", "robot0 M05 D1", nullptr));
        pbStartCustomConveyor3->setText(QCoreApplication::translate("RobotWindow", "Start", nullptr));
        pbStopCustomConveyor3->setText(QCoreApplication::translate("RobotWindow", "Stop", nullptr));
        label_147->setText(QCoreApplication::translate("RobotWindow", "C3", nullptr));
#if QT_CONFIG(tooltip)
        pbStartCustomConveyor2Command->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbStartCustomConveyor2Command->setText(QCoreApplication::translate("RobotWindow", "robot0 M03 D1", nullptr));
        pbStopCustomConveyor2->setText(QCoreApplication::translate("RobotWindow", "Stop", nullptr));
#if QT_CONFIG(tooltip)
        pbStopCustomConveyor3Command->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbStopCustomConveyor3Command->setText(QCoreApplication::translate("RobotWindow", "robot0 M05 D2", nullptr));
        label_153->setText(QCoreApplication::translate("RobotWindow", "C1", nullptr));
        pbStartCustomConveyor1->setText(QCoreApplication::translate("RobotWindow", "Start", nullptr));
        pbStopCustomConveyor1->setText(QCoreApplication::translate("RobotWindow", "Stop", nullptr));
#if QT_CONFIG(tooltip)
        pbStopCustomConveyor1Command->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbStopCustomConveyor1Command->setText(QCoreApplication::translate("RobotWindow", "robot0 M05 D0", nullptr));
#if QT_CONFIG(tooltip)
        pbStartCustomConveyor1Command->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \342\200\223 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Seg"
                        "oe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSys"
                        "temFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background"
                        "-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pbStartCustomConveyor1Command->setText(QCoreApplication::translate("RobotWindow", "robot0 M03 D0", nullptr));
        pbStartCustomConveyor2->setText(QCoreApplication::translate("RobotWindow", "Start", nullptr));
#if QT_CONFIG(tooltip)
        pbStartCustomConveyor3Command->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbStartCustomConveyor3Command->setText(QCoreApplication::translate("RobotWindow", "robot0 M03 D2", nullptr));
        label_154->setText(QCoreApplication::translate("RobotWindow", "C2", nullptr));
        twDevices->setTabText(twDevices->indexOf(ConveyorTab), QCoreApplication::translate("RobotWindow", "Conveyor", nullptr));
        pbConnectEncoder->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        label_11->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
        cbSelectedEncoder->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbSelectedEncoder->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbSelectedEncoder->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbSelectedEncoder->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

        label_124->setText(QCoreApplication::translate("RobotWindow", "Type", nullptr));
        cbEncoderType->setItemText(0, QCoreApplication::translate("RobotWindow", "Encoder X", nullptr));
        cbEncoderType->setItemText(1, QCoreApplication::translate("RobotWindow", "Sub Encoder", nullptr));
        cbEncoderType->setItemText(2, QCoreApplication::translate("RobotWindow", "Virtual Encoder", nullptr));

        lbEncoderCOMname->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
        leEncoderVelocity->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        leEncoderInterval->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        leEncoderCurrentPosition->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        label_130->setText(QCoreApplication::translate("RobotWindow", "Current Position (mm)", nullptr));
        pbReadEncoder->setText(QCoreApplication::translate("RobotWindow", "Read", nullptr));
        pbSetEncoderVelocity->setText(QCoreApplication::translate("RobotWindow", "Set", nullptr));
        pbSetEncoderInterval->setText(QCoreApplication::translate("RobotWindow", "Set", nullptr));
        pbResetEncoder->setText(QCoreApplication::translate("RobotWindow", "Reset", nullptr));
        label_129->setText(QCoreApplication::translate("RobotWindow", "Velocity (mm/s)", nullptr));
        label_125->setText(QCoreApplication::translate("RobotWindow", "Timer (ms)", nullptr));
        cbEncoderActive->setText(QCoreApplication::translate("RobotWindow", "Active", nullptr));
        twDevices->setTabText(twDevices->indexOf(EncoderTab), QCoreApplication::translate("RobotWindow", "Encoder", nullptr));
        pbSlidingConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        label_161->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
        cbSelectedSlider->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbSelectedSlider->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbSelectedSlider->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbSelectedSlider->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

        lbSliderCOMName->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
#if QT_CONFIG(tooltip)
        pbSlidingDisable->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbSlidingDisable->setText(QCoreApplication::translate("RobotWindow", "Disable motors", nullptr));
        label_58->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        label_37->setText(QCoreApplication::translate("RobotWindow", "Position", nullptr));
#if QT_CONFIG(tooltip)
        pbSlidingHome->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbSlidingHome->setText(QCoreApplication::translate("RobotWindow", "Home", nullptr));
        label_36->setText(QCoreApplication::translate("RobotWindow", "Speed", nullptr));
        label_59->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        twDevices->setTabText(twDevices->indexOf(SliderTab1), QCoreApplication::translate("RobotWindow", "Slider", nullptr));
#if QT_CONFIG(tooltip)
        pbExternalControllerConnect->setToolTip(QCoreApplication::translate("RobotWindow", "Connect External Controller", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExternalControllerConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        label_162->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
        cbSelectedDevice->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbSelectedDevice->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbSelectedDevice->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));
        cbSelectedDevice->setItemText(3, QCoreApplication::translate("RobotWindow", "+", nullptr));

        lbExternalCOMName->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
        leTransmitToMCU->setText(QString());
        leTransmitToMCU->setPlaceholderText(QCoreApplication::translate("RobotWindow", "Transmit to MCU", nullptr));
        twDevices->setTabText(twDevices->indexOf(MCUTab), QCoreApplication::translate("RobotWindow", "External Device", nullptr));
        twDevices->setTabText(twDevices->indexOf(PlusDeviceTab), QCoreApplication::translate("RobotWindow", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotWindow: public Ui_RobotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTWINDOW_H
