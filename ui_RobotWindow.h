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
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolButton>
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
    QGroupBox *groupRobotConnection;
    QHBoxLayout *horizontalLayout_14;
    QFrame *frameRobotConnection;
    QHBoxLayout *horizontalLayout_13;
    QVBoxLayout *verticalLayout_12;
    QPushButton *pbConnect;
    QVBoxLayout *verticalLayout_11;
    QFrame *fConnectionInfo;
    QGridLayout *gridLayout_17;
    QLabel *lbComName;
    QLabel *lbBaudrate;
    QLabel *label_122;
    QLabel *label_64;
    QLabel *label_65;
    QLabel *label_6;
    QLabel *label_10;
    QComboBox *cbRobotModel;
    QCheckBox *cbAutoConnect;
    QLabel *label_91;
    QLabel *lbID;
    QLabel *label_123;
    QLabel *lbIP;
    QLabel *lbLocalPort;
    QSpacerItem *horizontalSpacer_4;
    QFrame *fRobotPosition;
    QGridLayout *gridLayout_19;
    QLabel *label_92;
    QLabel *label_84;
    QLabel *label_90;
    QLabel *label_94;
    QLabel *label_88;
    QLabel *label_86;
    QLabel *lbX;
    QLabel *lbY;
    QLabel *lbZ;
    QLabel *lbW;
    QLabel *lbU;
    QLabel *lbV;
    QWidget *tabManagerLayout;
    QVBoxLayout *verticalLayout_46;
    QSplitter *splitter_2;
    QWidget *GeometryTabManagerWidget;
    QVBoxLayout *GeometryTabManagerLayout;
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
    QGridLayout *gridLayout_21;
    QLabel *label;
    QComboBox *cbROSCameraView;
    QGroupBox *groupBox_4;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    QComboBox *cbRobotVersion;
    QLabel *label_2;
    QComboBox *cbEndEffector;
    QLabel *label_3;
    QPushButton *btDeleteAllObjects;
    QSpacerItem *verticalSpacer_5;
    QWidget *t2D;
    QVBoxLayout *verticalLayout_22;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_44;
    QFrame *frame;
    QGridLayout *gridLayout_10;
    QLabel *label_53;
    QComboBox *cbWorkingSize;
    QFrame *fXYWorkingArea;
    QGridLayout *gridLayout_18;
    QSlider *vsZAdjsution;
    QWidget *wg2D;
    QLabel *label_15;
    QGridLayout *gridLayout_9;
    QLabel *label_60;
    QLabel *label_61;
    QSlider *vs6AxisAdjsution;
    QSlider *vsAngleAdjsution;
    QLabel *label_16;
    QSlider *vs5AxisAdjsution;
    QLabel *lb4AxisValue;
    QLabel *lb5AxisValue;
    QLabel *lb6AxisValue;
    QSpacerItem *verticalSpacer_7;
    QWidget *tJogging;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea_2;
    QWidget *wgJoggingScrollWidget;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *gbMovement1;
    QVBoxLayout *verticalLayout_3;
    QFrame *framePositionButton;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *pbHome;
    QFrame *framePositionParameter;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_40;
    QPushButton *pbsubX;
    QLineEdit *leX;
    QPushButton *pbplusX;
    QLabel *label_8;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_106;
    QPushButton *pbsubY;
    QLineEdit *leY;
    QPushButton *pbplusY;
    QLabel *label_9;
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
    QSpacerItem *horizontalSpacer_63;
    QWidget *wgControlButton;
    QHBoxLayout *horizontalLayout_6;
    QGridLayout *gridLayout_2;
    QToolButton *pbDown;
    QToolButton *pbForward;
    QToolButton *pbRight;
    QToolButton *pbBackward;
    QToolButton *pbLeft;
    QToolButton *pbUp;
    QGridLayout *gridLayout;
    QLabel *label_62;
    QLineEdit *leVelocity;
    QLabel *label_33;
    QLabel *label_28;
    QComboBox *cbDivision;
    QLabel *label_32;
    QLabel *label_63;
    QLabel *label_30;
    QLabel *label_29;
    QLineEdit *leAccel;
    QLineEdit *leStartSpeed;
    QLabel *label_31;
    QLabel *label_116;
    QLineEdit *leEndSpeed;
    QLabel *label_117;
    QSpacerItem *horizontalSpacer_61;
    QGroupBox *gbJoystick;
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
    QGroupBox *gbIO;
    QVBoxLayout *verticalLayout_6;
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
    QCheckBox *cbD13;
    QSpacerItem *horizontalSpacer_69;
    QCheckBox *cbD7;
    QCheckBox *cbD1;
    QCheckBox *cbD2;
    QCheckBox *cbD5;
    QCheckBox *cbD10;
    QCheckBox *cbD9;
    QCheckBox *cbD3;
    QSpacerItem *horizontalSpacer_48;
    QCheckBox *cbD8;
    QCheckBox *cbD6;
    QCheckBox *cbD12;
    QLabel *label_68;
    QCheckBox *cbD0;
    QCheckBox *cbD4;
    QCheckBox *cbD14;
    QCheckBox *cbD15;
    QCheckBox *cbD11;
    QWidget *wgPWMOutput;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_69;
    QLabel *label_72;
    QLineEdit *leP0Value;
    QSpacerItem *horizontalSpacer_14;
    QLabel *label_73;
    QLineEdit *leP1Value;
    QSpacerItem *horizontalSpacer_28;
    QLineEdit *lePx;
    QLineEdit *lePxValue;
    QSpacerItem *horizontalSpacer_49;
    QWidget *wgRCServoOutput;
    QHBoxLayout *horizontalLayout_44;
    QLabel *label_71;
    QLabel *label_75;
    QLineEdit *leS0Value;
    QSpacerItem *horizontalSpacer_27;
    QLabel *label_77;
    QLineEdit *leS1Value;
    QSpacerItem *horizontalSpacer_31;
    QLineEdit *leSx;
    QLineEdit *leSxValue;
    QSpacerItem *horizontalSpacer_50;
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
    QHBoxLayout *horizontalLayout_41;
    QLabel *label_80;
    QSpacerItem *horizontalSpacer_23;
    QLabel *lbI4Value;
    QSpacerItem *horizontalSpacer_24;
    QCheckBox *cbToggle4;
    QPushButton *pbReadI4;
    QSpacerItem *horizontalSpacer_55;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_82;
    QSpacerItem *horizontalSpacer_25;
    QLabel *lbI5Value;
    QSpacerItem *horizontalSpacer_26;
    QCheckBox *cbToggle5;
    QPushButton *pbReadI5;
    QSpacerItem *horizontalSpacer_56;
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
    QSpacerItem *verticalSpacer;
    QWidget *xExternal;
    QVBoxLayout *verticalLayout_19;
    QTabWidget *twConveyor;
    QWidget *tConveyor;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_48;
    QPushButton *pbConveyorConnect;
    QLabel *lbConveyorCOMName;
    QGridLayout *gridLayout_7;
    QLabel *label_46;
    QComboBox *cbConveyorValueType;
    QLabel *label_52;
    QComboBox *cbConveyorMode;
    QLabel *label_12;
    QLineEdit *leConveyorvMovingValue;
    QLabel *lbUnitOfConveyorMoving;
    QLabel *label_57;
    QLabel *lbSpeedOfPositionMode;
    QLineEdit *leSpeedOfPositionMode;
    QSpacerItem *verticalSpacer_2;
    QWidget *sSlidingRail;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_49;
    QPushButton *pbSlidingConnect;
    QLabel *lbSliderCOMName;
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
    QWidget *tExternalMCU;
    QVBoxLayout *verticalLayout_20;
    QWidget *widget1;
    QHBoxLayout *horizontalLayout_50;
    QPushButton *pbExternalControllerConnect;
    QLabel *lbExternalCOMName;
    QTextEdit *teReceiveFromMCU;
    QLineEdit *leTransmitToMCU;
    QWidget *tTerminal;
    QVBoxLayout *verticalLayout_28;
    QScrollArea *scrollArea_7;
    QWidget *scrollAreaWidgetContents_7;
    QVBoxLayout *verticalLayout_27;
    QGridLayout *gridLayout_4;
    QTextEdit *teDebug;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *leTerminal;
    QComboBox *cbDeviceSender;
    QWidget *ModuleTabManagerWidget;
    QVBoxLayout *ModuleTabManagerLayout;
    QTabWidget *twModule;
    QWidget *tGcodeEditor;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_30;
    QPushButton *pbExecuteGcodes;
    QSpacerItem *horizontalSpacer_2;
    QRadioButton *rbEditorCurrent;
    QRadioButton *rbEditorStart;
    QCheckBox *cbLockGcodeEditor;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_8;
    QToolButton *pbFormat;
    QCheckBox *cbFormatColor;
    QCheckBox *cbAutoNumbering;
    QLabel *lbGcodeProgramingIssues;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_9;
    QToolButton *pbSaveGcode;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_30;
    CodeEditor *pteGcodeArea;
    QTabWidget *tabWidget;
    QWidget *tab;
    QScrollArea *saProgramFiles;
    QWidget *wgProgramContainer;
    QFrame *frExProgram;
    QLineEdit *leExProgramName;
    QPushButton *pbExDeleteProgram;
    QLabel *lbExGCodeNumber;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_13;
    QPushButton *pbUploadProgram;
    QPushButton *pbImportGcodeFiles;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_14;
    QPushButton *pbAddNewProgram;
    QPushButton *pbRefreshGcodeFiles;
    QPushButton *pbFindGcodeFile;
    QPushButton *pbSortGcodeFiles;
    QLabel *lbExGCodeNumber_2;
    QLineEdit *leGcodeProgramPath;
    QPushButton *pbOpenGcodeProgramPath;
    QWidget *tab_3;
    QListWidget *listWidget;
    QTextEdit *textEdit;
    QPushButton *pbUploadProgram_2;
    QSpacerItem *verticalSpacer_9;
    QWidget *tObjectDetecting;
    QVBoxLayout *verticalLayout_25;
    QScrollArea *saObjectDetecting;
    QWidget *wObjectDetecting;
    QVBoxLayout *verticalLayout_17;
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
    QPushButton *pbCameraWindowMode;
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
    QFrame *fWebcamSource;
    QHBoxLayout *horizontalLayout_11;
    QToolButton *pbLoadCamera;
    QLabel *label_11;
    QLineEdit *leFPS;
    QLabel *label_124;
    QLineEdit *leCameraWidth;
    QLabel *label_125;
    QLineEdit *leCameraHeight;
    QSpacerItem *horizontalSpacer_45;
    QToolButton *pbPlayPauseCamera;
    QToolButton *pbCaptureCamera;
    QLabel *lbCameraState;
    QFrame *fImageSource;
    QHBoxLayout *horizontalLayout_27;
    QToolButton *pbLoadTestImage;
    QSpacerItem *horizontalSpacer_64;
    QFrame *fPluginSource;
    QHBoxLayout *horizontalLayout_28;
    QCheckBox *cbExternalImageSource;
    QLabel *label_177;
    QComboBox *comboBox_2;
    QLabel *label_178;
    QLineEdit *leImageWidth;
    QLabel *label_179;
    QLineEdit *leImageHeight;
    QSpacerItem *horizontalSpacer_65;
    QGroupBox *gbCameraCalibration;
    QVBoxLayout *verticalLayout_29;
    QFrame *fCameraCalibrationFrame;
    QVBoxLayout *verticalLayout_52;
    QPushButton *pbCalibStep1;
    QFrame *fCalibStep1;
    QGridLayout *gridLayout_27;
    QSpacerItem *horizontalSpacer_42;
    QLineEdit *leChessWidth;
    QLineEdit *leChessHeight;
    QLabel *label_109;
    QPushButton *pbTransformPerspective;
    QLabel *label_110;
    QPushButton *pbFindChessboard;
    QPushButton *pbCalibStep2;
    QFrame *fCalibStep2;
    QGridLayout *gridLayout_26;
    QPushButton *pbImageMapping;
    QLabel *label_39;
    QLineEdit *leRealityPoint2Y;
    QLineEdit *leRealityPoint1Y;
    QLabel *label_133;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_140;
    QPushButton *pbObjectOrigin;
    QLabel *label_38;
    QLineEdit *leRealityPoint1X;
    QLabel *label_132;
    QLineEdit *leRealityPoint2X;
    QLabel *label_139;
    QCheckBox *cbMoveOnConveyor1;
    QPushButton *pbCalibPoint1;
    QPushButton *pbCalibPoint2;
    QGroupBox *gbCameraObject;
    QVBoxLayout *verticalLayout_40;
    QFrame *fVisionObjectFrame;
    QVBoxLayout *verticalLayout_31;
    QHBoxLayout *horizontalLayout_29;
    QSpacerItem *horizontalSpacer_43;
    QComboBox *cbObjectType;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QFrame *frame_13;
    QHBoxLayout *horizontalLayout_26;
    QLabel *label_126;
    QComboBox *cbDetectingAlgorithm;
    QSpacerItem *horizontalSpacer_6;
    QFrame *fBlobPanel;
    QGridLayout *gridLayout_14;
    QLabel *label_172;
    QLineEdit *leMaxWRec;
    QLineEdit *leMaxLRec;
    QLabel *label_55;
    QLineEdit *leWRec;
    QToolButton *pbObjectRect;
    QLabel *label_56;
    QLabel *label_44;
    QLineEdit *leMinLRec;
    QLineEdit *leLRec;
    QPushButton *pbFilter;
    QLabel *label_43;
    QLabel *label_173;
    QLineEdit *leHRec;
    QSpacerItem *horizontalSpacer_66;
    QLabel *label_54;
    QLabel *label_174;
    QLabel *label_42;
    QLineEdit *leMinWRec;
    QLabel *lbTrackingObject;
    QLabel *label_175;
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
    QPushButton *pushButton_3;
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
    QFrame *fVisionVariableFrame;
    QVBoxLayout *verticalLayout_35;
    QHBoxLayout *horizontalLayout_25;
    QPushButton *pbViewDataObjects;
    QPushButton *pbClearDetectObjects;
    QSpacerItem *horizontalSpacer_9;
    QGridLayout *gridLayout_15;
    QLabel *label_50;
    QLabel *lbVisibleObjectNumber;
    QLabel *lbTrackingObjectNumber;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_48;
    QFrame *frame_9;
    QLabel *label_155;
    QLabel *label_156;
    QLabel *label_157;
    QLabel *label_158;
    QLabel *label_159;
    QGroupBox *gbConveyorForTracking;
    QVBoxLayout *verticalLayout_41;
    QFrame *fTracking;
    QVBoxLayout *verticalLayout_33;
    QLabel *label_150;
    QFrame *gridFrame;
    QGridLayout *gridLayout_32;
    QSpacerItem *horizontalSpacer_62;
    QLabel *label_152;
    QLabel *label_151;
    QLineEdit *leTrackingError;
    QLabel *label_127;
    QGridLayout *gridLayout_16;
    QLineEdit *leConvenyorSpeed;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *pbReadProximitySensor;
    QPushButton *pbBackwardConveyor;
    QLineEdit *leMovingDistanceConveyorControl;
    QPushButton *pbResetEncoderPosition;
    QLabel *label_189;
    QLineEdit *leForwardConveyorGcode;
    QLineEdit *leTurnOffConveyorGcode;
    QRadioButton *rbEncoderEnable;
    QLabel *label_148;
    QLabel *label_191;
    QLineEdit *leBackwardConveyorGcode;
    QLabel *label_45;
    QLabel *label_163;
    QLabel *lbProximitySensorValue;
    QLabel *leEncoderCom;
    QPushButton *pbTurnOffConveyor;
    QLabel *label_121;
    QLabel *label_162;
    QLineEdit *leEncoderVelocity;
    QLineEdit *leConveyorDeviationAngle;
    QPushButton *pbConnectEncdoer;
    QLabel *label_161;
    QCheckBox *cbEncoderPositionInverse;
    QLabel *label_49;
    QLabel *label_160;
    QLabel *label_119;
    QRadioButton *rbVirtualEncoderEnable;
    QLabel *label_118;
    QPushButton *pbForwardConveyor;
    QComboBox *cbConveyorDirectionControl;
    QLabel *label_120;
    QCheckBox *cbAutoReadProximitySensor;
    QLineEdit *leEncoderPosition;
    QFrame *frame_11;
    QGridLayout *gridLayout_37;
    QLabel *label_170;
    QLineEdit *leConveyorPoint2X;
    QPushButton *pbCalibConveyorAngle;
    QLineEdit *leConveyorPoint1X;
    QLabel *label_197;
    QLabel *label_199;
    QLineEdit *leConveyorPoint1Y;
    QLabel *label_198;
    QLineEdit *leConveyorPoint2Y;
    QPushButton *pbGetConveyorPoint1X;
    QPushButton *pbGetConveyorPoint1Y;
    QPushButton *pbGetConveyorPoint2X;
    QPushButton *pbGetConveyorPoint2Y;
    QLabel *label_196;
    QLabel *label_149;
    QFrame *frame_12;
    QGridLayout *gridLayout_38;
    QLineEdit *leConveyorPoint3X;
    QLineEdit *leConveyorPoint3Y;
    QLabel *label_169;
    QLabel *label_168;
    QLabel *label_171;
    QLabel *label_167;
    QFrame *fVisionConveyorFrame;
    QVBoxLayout *verticalLayout_49;
    QSpacerItem *verticalSpacer_11;
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
    QWidget *widget2;
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
    QMenuBar *mbRobot;
    QMenu *menuHelp;
    QMenu *menuReferences;
    QMenu *menuEditor;
    QMenu *menuExecute;
    QMenu *menuSetting;
    QMenu *menuConnection;
    QMenu *menuUI;

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
        font.setKerning(true);
        RobotWindow->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8("delta_x_logo_96x96.ico"), QSize(), QIcon::Normal, QIcon::Off);
        RobotWindow->setWindowIcon(icon);
        RobotWindow->setLayoutDirection(Qt::LeftToRight);
        RobotWindow->setStyleSheet(QString::fromUtf8("/*\n"
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
""
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
"}\n"
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
"QGr"
                        "oupBox[checkable=\"true\"]::indicator {\n"
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
        twDeltaManager->setMinimumSize(QSize(0, 0));
        twDeltaManager->setMaximumSize(QSize(16777215, 40));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
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

        groupRobotConnection = new QGroupBox(centralWidget);
        groupRobotConnection->setObjectName(QString::fromUtf8("groupRobotConnection"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupRobotConnection->sizePolicy().hasHeightForWidth());
        groupRobotConnection->setSizePolicy(sizePolicy1);
        groupRobotConnection->setMaximumSize(QSize(16777215, 16777215));
        QFont font2;
        font2.setPointSize(8);
        groupRobotConnection->setFont(font2);
        groupRobotConnection->setStyleSheet(QString::fromUtf8(""));
        groupRobotConnection->setCheckable(true);
        horizontalLayout_14 = new QHBoxLayout(groupRobotConnection);
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(30, 0, -1, 5);
        frameRobotConnection = new QFrame(groupRobotConnection);
        frameRobotConnection->setObjectName(QString::fromUtf8("frameRobotConnection"));
        frameRobotConnection->setMinimumSize(QSize(0, 50));
        frameRobotConnection->setMaximumSize(QSize(16777215, 50));
        QFont font3;
        font3.setBold(false);
        font3.setItalic(false);
        font3.setKerning(true);
        frameRobotConnection->setFont(font3);
        frameRobotConnection->setStyleSheet(QString::fromUtf8("/*background-color: rgb(255, 255, 255);\n"
"color: rgb(54, 54, 54);\n"
"border: none;*/"));
        frameRobotConnection->setFrameShape(QFrame::StyledPanel);
        frameRobotConnection->setFrameShadow(QFrame::Raised);
        horizontalLayout_13 = new QHBoxLayout(frameRobotConnection);
        horizontalLayout_13->setSpacing(0);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(0, 0, 0, 0);
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        pbConnect = new QPushButton(frameRobotConnection);
        pbConnect->setObjectName(QString::fromUtf8("pbConnect"));
        pbConnect->setMinimumSize(QSize(0, 30));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(false);
        pbConnect->setFont(font4);
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
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/disconnected.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon1.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/connected.png"), QSize(), QIcon::Normal, QIcon::On);
        pbConnect->setIcon(icon1);
        pbConnect->setIconSize(QSize(30, 20));

        verticalLayout_12->addWidget(pbConnect);


        horizontalLayout_13->addLayout(verticalLayout_12);

        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));

        horizontalLayout_13->addLayout(verticalLayout_11);

        fConnectionInfo = new QFrame(frameRobotConnection);
        fConnectionInfo->setObjectName(QString::fromUtf8("fConnectionInfo"));
        fConnectionInfo->setStyleSheet(QString::fromUtf8(""));
        gridLayout_17 = new QGridLayout(fConnectionInfo);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        gridLayout_17->setHorizontalSpacing(10);
        gridLayout_17->setVerticalSpacing(2);
        gridLayout_17->setContentsMargins(20, 0, -1, 0);
        lbComName = new QLabel(fConnectionInfo);
        lbComName->setObjectName(QString::fromUtf8("lbComName"));
        lbComName->setFont(font2);
        lbComName->setStyleSheet(QString::fromUtf8(""));

        gridLayout_17->addWidget(lbComName, 2, 3, 1, 1);

        lbBaudrate = new QLabel(fConnectionInfo);
        lbBaudrate->setObjectName(QString::fromUtf8("lbBaudrate"));
        lbBaudrate->setFont(font2);
        lbBaudrate->setStyleSheet(QString::fromUtf8(""));

        gridLayout_17->addWidget(lbBaudrate, 2, 4, 1, 1);

        label_122 = new QLabel(fConnectionInfo);
        label_122->setObjectName(QString::fromUtf8("label_122"));
        QFont font5;
        font5.setBold(true);
        label_122->setFont(font5);
        label_122->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_122, 0, 5, 1, 1);

        label_64 = new QLabel(fConnectionInfo);
        label_64->setObjectName(QString::fromUtf8("label_64"));
        label_64->setFont(font5);
        label_64->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_64, 0, 0, 1, 1);

        label_65 = new QLabel(fConnectionInfo);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        label_65->setFont(font5);
        label_65->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_65, 0, 4, 1, 1);

        label_6 = new QLabel(fConnectionInfo);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFont(font5);
        label_6->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_6, 0, 2, 1, 1);

        label_10 = new QLabel(fConnectionInfo);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font5);
        label_10->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_10, 0, 3, 1, 1);

        cbRobotModel = new QComboBox(fConnectionInfo);
        cbRobotModel->addItem(QString());
        cbRobotModel->addItem(QString());
        cbRobotModel->addItem(QString());
        cbRobotModel->addItem(QString());
        cbRobotModel->setObjectName(QString::fromUtf8("cbRobotModel"));
        cbRobotModel->setMinimumSize(QSize(80, 0));

        gridLayout_17->addWidget(cbRobotModel, 2, 1, 1, 1);

        cbAutoConnect = new QCheckBox(fConnectionInfo);
        cbAutoConnect->setObjectName(QString::fromUtf8("cbAutoConnect"));
        cbAutoConnect->setFont(font2);
        cbAutoConnect->setStyleSheet(QString::fromUtf8(""));
        cbAutoConnect->setChecked(true);

        gridLayout_17->addWidget(cbAutoConnect, 2, 0, 1, 1);

        label_91 = new QLabel(fConnectionInfo);
        label_91->setObjectName(QString::fromUtf8("label_91"));
        label_91->setFont(font5);
        label_91->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_91, 0, 1, 1, 1);

        lbID = new QLabel(fConnectionInfo);
        lbID->setObjectName(QString::fromUtf8("lbID"));
        lbID->setFont(font2);
        lbID->setStyleSheet(QString::fromUtf8(""));

        gridLayout_17->addWidget(lbID, 2, 2, 1, 1);

        label_123 = new QLabel(fConnectionInfo);
        label_123->setObjectName(QString::fromUtf8("label_123"));
        label_123->setFont(font5);
        label_123->setAlignment(Qt::AlignCenter);

        gridLayout_17->addWidget(label_123, 0, 6, 1, 1);

        lbIP = new QLabel(fConnectionInfo);
        lbIP->setObjectName(QString::fromUtf8("lbIP"));
        lbIP->setFont(font2);
        lbIP->setStyleSheet(QString::fromUtf8(""));

        gridLayout_17->addWidget(lbIP, 2, 5, 1, 1);

        lbLocalPort = new QLabel(fConnectionInfo);
        lbLocalPort->setObjectName(QString::fromUtf8("lbLocalPort"));
        lbLocalPort->setFont(font2);
        lbLocalPort->setStyleSheet(QString::fromUtf8(""));

        gridLayout_17->addWidget(lbLocalPort, 2, 6, 1, 1);


        horizontalLayout_13->addWidget(fConnectionInfo);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_4);

        fRobotPosition = new QFrame(frameRobotConnection);
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
        label_92 = new QLabel(fRobotPosition);
        label_92->setObjectName(QString::fromUtf8("label_92"));
        label_92->setMinimumSize(QSize(0, 20));
        label_92->setFont(font5);
        label_92->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_92, 0, 4, 1, 1);

        label_84 = new QLabel(fRobotPosition);
        label_84->setObjectName(QString::fromUtf8("label_84"));
        label_84->setMinimumSize(QSize(0, 20));
        label_84->setFont(font5);
        label_84->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_84, 0, 0, 1, 1);

        label_90 = new QLabel(fRobotPosition);
        label_90->setObjectName(QString::fromUtf8("label_90"));
        label_90->setMinimumSize(QSize(0, 20));
        label_90->setFont(font5);
        label_90->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_90, 0, 3, 1, 1);

        label_94 = new QLabel(fRobotPosition);
        label_94->setObjectName(QString::fromUtf8("label_94"));
        label_94->setMinimumSize(QSize(0, 20));
        label_94->setFont(font5);
        label_94->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_94, 0, 5, 1, 1);

        label_88 = new QLabel(fRobotPosition);
        label_88->setObjectName(QString::fromUtf8("label_88"));
        label_88->setMinimumSize(QSize(0, 20));
        label_88->setFont(font5);
        label_88->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_88, 0, 2, 1, 1);

        label_86 = new QLabel(fRobotPosition);
        label_86->setObjectName(QString::fromUtf8("label_86"));
        label_86->setMinimumSize(QSize(0, 20));
        label_86->setFont(font5);
        label_86->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(label_86, 0, 1, 1, 1);

        lbX = new QLabel(fRobotPosition);
        lbX->setObjectName(QString::fromUtf8("lbX"));
        lbX->setMinimumSize(QSize(30, 20));
        lbX->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbX, 1, 0, 1, 1);

        lbY = new QLabel(fRobotPosition);
        lbY->setObjectName(QString::fromUtf8("lbY"));
        lbY->setMinimumSize(QSize(30, 20));
        lbY->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbY, 1, 1, 1, 1);

        lbZ = new QLabel(fRobotPosition);
        lbZ->setObjectName(QString::fromUtf8("lbZ"));
        lbZ->setMinimumSize(QSize(30, 20));
        lbZ->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbZ, 1, 2, 1, 1);

        lbW = new QLabel(fRobotPosition);
        lbW->setObjectName(QString::fromUtf8("lbW"));
        lbW->setMinimumSize(QSize(30, 20));
        lbW->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbW, 1, 3, 1, 1);

        lbU = new QLabel(fRobotPosition);
        lbU->setObjectName(QString::fromUtf8("lbU"));
        lbU->setMinimumSize(QSize(30, 20));
        lbU->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbU, 1, 4, 1, 1);

        lbV = new QLabel(fRobotPosition);
        lbV->setObjectName(QString::fromUtf8("lbV"));
        lbV->setMinimumSize(QSize(30, 20));
        lbV->setAlignment(Qt::AlignCenter);

        gridLayout_19->addWidget(lbV, 1, 5, 1, 1);


        horizontalLayout_13->addWidget(fRobotPosition);


        horizontalLayout_14->addWidget(frameRobotConnection);


        verticalLayout_15->addWidget(groupRobotConnection);

        tabManagerLayout = new QWidget(centralWidget);
        tabManagerLayout->setObjectName(QString::fromUtf8("tabManagerLayout"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabManagerLayout->sizePolicy().hasHeightForWidth());
        tabManagerLayout->setSizePolicy(sizePolicy2);
        tabManagerLayout->setMinimumSize(QSize(0, 0));
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
        GeometryTabManagerWidget = new QWidget(splitter_2);
        GeometryTabManagerWidget->setObjectName(QString::fromUtf8("GeometryTabManagerWidget"));
        GeometryTabManagerWidget->setMinimumSize(QSize(0, 0));
        GeometryTabManagerWidget->setMaximumSize(QSize(800, 16777215));
        GeometryTabManagerWidget->setStyleSheet(QString::fromUtf8(""));
        GeometryTabManagerLayout = new QVBoxLayout(GeometryTabManagerWidget);
        GeometryTabManagerLayout->setSpacing(0);
        GeometryTabManagerLayout->setContentsMargins(11, 11, 11, 11);
        GeometryTabManagerLayout->setObjectName(QString::fromUtf8("GeometryTabManagerLayout"));
        GeometryTabManagerLayout->setContentsMargins(0, 0, 0, 0);
        twDeltaGeometry = new QTabWidget(GeometryTabManagerWidget);
        twDeltaGeometry->setObjectName(QString::fromUtf8("twDeltaGeometry"));
        twDeltaGeometry->setMinimumSize(QSize(0, 0));
        QFont font6;
        font6.setPointSize(11);
        font6.setBold(false);
        twDeltaGeometry->setFont(font6);
        twDeltaGeometry->setStyleSheet(QString::fromUtf8(""));
        twDeltaGeometry->setTabPosition(QTabWidget::North);
        twDeltaGeometry->setElideMode(Qt::ElideNone);
        t3D = new QWidget();
        t3D->setObjectName(QString::fromUtf8("t3D"));
        verticalLayout_23 = new QVBoxLayout(t3D);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        scrollArea_4 = new QScrollArea(t3D);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setMinimumSize(QSize(0, 0));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 533, 600));
        scrollAreaWidgetContents_4->setMinimumSize(QSize(0, 600));
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
        groupBox_3->setMinimumSize(QSize(0, 124));
        groupBox_3->setMaximumSize(QSize(200, 16777215));
        gridLayout_21 = new QGridLayout(groupBox_3);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMinimumSize(QSize(100, 0));

        gridLayout_21->addWidget(label, 0, 0, 1, 1);

        cbROSCameraView = new QComboBox(groupBox_3);
        cbROSCameraView->addItem(QString());
        cbROSCameraView->addItem(QString());
        cbROSCameraView->addItem(QString());
        cbROSCameraView->setObjectName(QString::fromUtf8("cbROSCameraView"));
        cbROSCameraView->setMinimumSize(QSize(0, 30));

        gridLayout_21->addWidget(cbROSCameraView, 0, 1, 1, 1);


        horizontalLayout_16->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_4);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 150));
        groupBox_4->setMaximumSize(QSize(16777215, 16777215));
        layoutWidget = new QWidget(groupBox_4);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 240, 106));
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
        cbRobotVersion->setMinimumSize(QSize(0, 30));

        gridLayout_5->addWidget(cbRobotVersion, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setMinimumSize(QSize(120, 0));
        label_2->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_5->addWidget(label_2, 1, 0, 1, 1);

        cbEndEffector = new QComboBox(layoutWidget);
        cbEndEffector->addItem(QString());
        cbEndEffector->addItem(QString());
        cbEndEffector->addItem(QString());
        cbEndEffector->setObjectName(QString::fromUtf8("cbEndEffector"));
        cbEndEffector->setMinimumSize(QSize(0, 30));
        cbEndEffector->setMaximumSize(QSize(120, 16777215));

        gridLayout_5->addWidget(cbEndEffector, 1, 1, 1, 1);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_5->addWidget(label_3, 2, 0, 1, 1);

        btDeleteAllObjects = new QPushButton(layoutWidget);
        btDeleteAllObjects->setObjectName(QString::fromUtf8("btDeleteAllObjects"));
        btDeleteAllObjects->setMinimumSize(QSize(0, 30));

        gridLayout_5->addWidget(btDeleteAllObjects, 2, 1, 1, 1);


        horizontalLayout_16->addWidget(groupBox_4);


        verticalLayout_24->addLayout(horizontalLayout_16);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_24->addItem(verticalSpacer_5);

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
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 533, 1200));
        scrollAreaWidgetContents_3->setMinimumSize(QSize(0, 1200));
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

        fXYWorkingArea = new QFrame(scrollAreaWidgetContents_3);
        fXYWorkingArea->setObjectName(QString::fromUtf8("fXYWorkingArea"));
        gridLayout_18 = new QGridLayout(fXYWorkingArea);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        vsZAdjsution = new QSlider(fXYWorkingArea);
        vsZAdjsution->setObjectName(QString::fromUtf8("vsZAdjsution"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(vsZAdjsution->sizePolicy().hasHeightForWidth());
        vsZAdjsution->setSizePolicy(sizePolicy3);
        vsZAdjsution->setMaximum(300);
        vsZAdjsution->setOrientation(Qt::Vertical);

        gridLayout_18->addWidget(vsZAdjsution, 0, 0, 1, 1);

        wg2D = new QWidget(fXYWorkingArea);
        wg2D->setObjectName(QString::fromUtf8("wg2D"));
        sizePolicy.setHeightForWidth(wg2D->sizePolicy().hasHeightForWidth());
        wg2D->setSizePolicy(sizePolicy);
        wg2D->setMinimumSize(QSize(300, 300));
        wg2D->setMaximumSize(QSize(16777215, 16777215));
        wg2D->setStyleSheet(QString::fromUtf8(""));

        gridLayout_18->addWidget(wg2D, 0, 1, 1, 1);

        label_15 = new QLabel(fXYWorkingArea);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_18->addWidget(label_15, 1, 0, 1, 1);


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

        vsAngleAdjsution = new QSlider(scrollAreaWidgetContents_3);
        vsAngleAdjsution->setObjectName(QString::fromUtf8("vsAngleAdjsution"));
        vsAngleAdjsution->setMinimumSize(QSize(0, 30));
        vsAngleAdjsution->setMinimum(-360);
        vsAngleAdjsution->setMaximum(360);
        vsAngleAdjsution->setValue(0);
        vsAngleAdjsution->setOrientation(Qt::Horizontal);

        gridLayout_9->addWidget(vsAngleAdjsution, 0, 1, 1, 1);

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

        lb4AxisValue = new QLabel(scrollAreaWidgetContents_3);
        lb4AxisValue->setObjectName(QString::fromUtf8("lb4AxisValue"));

        gridLayout_9->addWidget(lb4AxisValue, 0, 2, 1, 1);

        lb5AxisValue = new QLabel(scrollAreaWidgetContents_3);
        lb5AxisValue->setObjectName(QString::fromUtf8("lb5AxisValue"));

        gridLayout_9->addWidget(lb5AxisValue, 1, 2, 1, 1);

        lb6AxisValue = new QLabel(scrollAreaWidgetContents_3);
        lb6AxisValue->setObjectName(QString::fromUtf8("lb6AxisValue"));

        gridLayout_9->addWidget(lb6AxisValue, 2, 2, 1, 1);


        verticalLayout_44->addLayout(gridLayout_9);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_44->addItem(verticalSpacer_7);

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
        wgJoggingScrollWidget = new QWidget();
        wgJoggingScrollWidget->setObjectName(QString::fromUtf8("wgJoggingScrollWidget"));
        wgJoggingScrollWidget->setGeometry(QRect(0, 0, 533, 2000));
        wgJoggingScrollWidget->setMinimumSize(QSize(0, 2000));
        wgJoggingScrollWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_5 = new QVBoxLayout(wgJoggingScrollWidget);
        verticalLayout_5->setSpacing(10);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, 10, 5, 0);
        gbMovement1 = new QGroupBox(wgJoggingScrollWidget);
        gbMovement1->setObjectName(QString::fromUtf8("gbMovement1"));
        gbMovement1->setMinimumSize(QSize(0, 0));
        gbMovement1->setMaximumSize(QSize(16777215, 16777215));
        QFont font7;
        font7.setPointSize(10);
        font7.setBold(true);
        gbMovement1->setFont(font7);
        gbMovement1->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_3 = new QVBoxLayout(gbMovement1);
        verticalLayout_3->setSpacing(11);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(11, 20, 11, 10);
        framePositionButton = new QFrame(gbMovement1);
        framePositionButton->setObjectName(QString::fromUtf8("framePositionButton"));
        framePositionButton->setMinimumSize(QSize(0, 0));
        framePositionButton->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_5 = new QHBoxLayout(framePositionButton);
        horizontalLayout_5->setSpacing(10);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pbHome = new QToolButton(framePositionButton);
        pbHome->setObjectName(QString::fromUtf8("pbHome"));
        pbHome->setMinimumSize(QSize(70, 70));
        QFont font8;
        font8.setPointSize(10);
        pbHome->setFont(font8);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/home.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbHome->setIcon(icon2);
        pbHome->setIconSize(QSize(50, 50));
        pbHome->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        horizontalLayout_5->addWidget(pbHome);

        framePositionParameter = new QFrame(framePositionButton);
        framePositionParameter->setObjectName(QString::fromUtf8("framePositionParameter"));
        framePositionParameter->setMaximumSize(QSize(230, 16777215));
        framePositionParameter->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	border: 1px solid rgb(206, 206, 206);\n"
"}\n"
"QLabel\n"
"{\n"
"	border: none;\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(framePositionParameter);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 0, 5, 0);
        label_40 = new QLabel(framePositionParameter);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setFont(font7);

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


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(10);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(5, 0, 5, 0);
        label_106 = new QLabel(framePositionParameter);
        label_106->setObjectName(QString::fromUtf8("label_106"));
        label_106->setFont(font7);

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


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(10);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(5, 0, 5, 0);
        label_107 = new QLabel(framePositionParameter);
        label_107->setObjectName(QString::fromUtf8("label_107"));
        label_107->setFont(font7);

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


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(10);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(5, 0, 5, 0);
        label_108 = new QLabel(framePositionParameter);
        label_108->setObjectName(QString::fromUtf8("label_108"));
        label_108->setFont(font7);

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


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(10);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        horizontalLayout_32->setContentsMargins(5, 0, 5, 0);
        label_111 = new QLabel(framePositionParameter);
        label_111->setObjectName(QString::fromUtf8("label_111"));
        label_111->setFont(font7);

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


        verticalLayout_2->addLayout(horizontalLayout_32);

        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(10);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        horizontalLayout_33->setContentsMargins(5, 0, 5, 0);
        label_112 = new QLabel(framePositionParameter);
        label_112->setObjectName(QString::fromUtf8("label_112"));
        label_112->setFont(font7);

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


        verticalLayout_2->addLayout(horizontalLayout_33);


        horizontalLayout_5->addWidget(framePositionParameter);

        horizontalSpacer_63 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_63);


        verticalLayout_3->addWidget(framePositionButton);

        wgControlButton = new QWidget(gbMovement1);
        wgControlButton->setObjectName(QString::fromUtf8("wgControlButton"));
        wgControlButton->setMaximumSize(QSize(16777215, 16777215));
        horizontalLayout_6 = new QHBoxLayout(wgControlButton);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(-1, 1, -1, -1);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(5);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pbDown = new QToolButton(wgControlButton);
        pbDown->setObjectName(QString::fromUtf8("pbDown"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icons8-expand-arrow-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDown->setIcon(icon3);
        pbDown->setIconSize(QSize(40, 40));
        pbDown->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbDown, 1, 5, 1, 1);

        pbForward = new QToolButton(wgControlButton);
        pbForward->setObjectName(QString::fromUtf8("pbForward"));
        pbForward->setStyleSheet(QString::fromUtf8(""));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/icon/icons8-collapse-arrow-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbForward->setIcon(icon4);
        pbForward->setIconSize(QSize(40, 40));
        pbForward->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbForward, 0, 3, 1, 1);

        pbRight = new QToolButton(wgControlButton);
        pbRight->setObjectName(QString::fromUtf8("pbRight"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/icon/icons8-forward-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRight->setIcon(icon5);
        pbRight->setIconSize(QSize(40, 40));
        pbRight->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbRight, 0, 4, 2, 1);

        pbBackward = new QToolButton(wgControlButton);
        pbBackward->setObjectName(QString::fromUtf8("pbBackward"));
        pbBackward->setIcon(icon3);
        pbBackward->setIconSize(QSize(40, 40));
        pbBackward->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbBackward, 1, 3, 1, 1);

        pbLeft = new QToolButton(wgControlButton);
        pbLeft->setObjectName(QString::fromUtf8("pbLeft"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/icon/icons8-back-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLeft->setIcon(icon6);
        pbLeft->setIconSize(QSize(40, 40));
        pbLeft->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        gridLayout_2->addWidget(pbLeft, 0, 2, 2, 1);

        pbUp = new QToolButton(wgControlButton);
        pbUp->setObjectName(QString::fromUtf8("pbUp"));
        pbUp->setIcon(icon4);
        pbUp->setIconSize(QSize(40, 40));
        pbUp->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbUp->setAutoRaise(false);

        gridLayout_2->addWidget(pbUp, 0, 5, 1, 1);


        horizontalLayout_6->addLayout(gridLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(10, -1, 0, -1);
        label_62 = new QLabel(wgControlButton);
        label_62->setObjectName(QString::fromUtf8("label_62"));
        label_62->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_62, 3, 0, 1, 1);

        leVelocity = new QLineEdit(wgControlButton);
        leVelocity->setObjectName(QString::fromUtf8("leVelocity"));
        leVelocity->setMinimumSize(QSize(0, 30));
        leVelocity->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leVelocity, 1, 1, 1, 1);

        label_33 = new QLabel(wgControlButton);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_33, 0, 0, 1, 1);

        label_28 = new QLabel(wgControlButton);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_28, 0, 2, 1, 1);

        cbDivision = new QComboBox(wgControlButton);
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->addItem(QString());
        cbDivision->setObjectName(QString::fromUtf8("cbDivision"));
        cbDivision->setMinimumSize(QSize(0, 30));
        cbDivision->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(cbDivision, 0, 1, 1, 1);

        label_32 = new QLabel(wgControlButton);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_32, 2, 2, 1, 1);

        label_63 = new QLabel(wgControlButton);
        label_63->setObjectName(QString::fromUtf8("label_63"));
        label_63->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_63, 3, 2, 1, 1);

        label_30 = new QLabel(wgControlButton);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_30, 1, 2, 1, 1);

        label_29 = new QLabel(wgControlButton);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_29, 1, 0, 1, 1);

        leAccel = new QLineEdit(wgControlButton);
        leAccel->setObjectName(QString::fromUtf8("leAccel"));
        leAccel->setMinimumSize(QSize(0, 30));
        leAccel->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leAccel, 2, 1, 1, 1);

        leStartSpeed = new QLineEdit(wgControlButton);
        leStartSpeed->setObjectName(QString::fromUtf8("leStartSpeed"));
        leStartSpeed->setMinimumSize(QSize(0, 30));
        leStartSpeed->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leStartSpeed, 3, 1, 1, 1);

        label_31 = new QLabel(wgControlButton);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_31, 2, 0, 1, 1);

        label_116 = new QLabel(wgControlButton);
        label_116->setObjectName(QString::fromUtf8("label_116"));
        label_116->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label_116, 4, 0, 1, 1);

        leEndSpeed = new QLineEdit(wgControlButton);
        leEndSpeed->setObjectName(QString::fromUtf8("leEndSpeed"));
        leEndSpeed->setMinimumSize(QSize(0, 30));
        leEndSpeed->setMaximumSize(QSize(100, 16777215));

        gridLayout->addWidget(leEndSpeed, 4, 1, 1, 1);

        label_117 = new QLabel(wgControlButton);
        label_117->setObjectName(QString::fromUtf8("label_117"));
        label_117->setStyleSheet(QString::fromUtf8("color: rgb(95, 95, 95);"));

        gridLayout->addWidget(label_117, 4, 2, 1, 1);


        horizontalLayout_6->addLayout(gridLayout);

        horizontalSpacer_61 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_61);


        verticalLayout_3->addWidget(wgControlButton);

        gbJoystick = new QGroupBox(gbMovement1);
        gbJoystick->setObjectName(QString::fromUtf8("gbJoystick"));
        gbJoystick->setMaximumSize(QSize(16777215, 16777215));
        gbJoystick->setFont(font7);
        gbJoystick->setFlat(false);
        gbJoystick->setCheckable(true);
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


        verticalLayout_3->addWidget(gbJoystick);


        verticalLayout_5->addWidget(gbMovement1);

        gbIO = new QGroupBox(wgJoggingScrollWidget);
        gbIO->setObjectName(QString::fromUtf8("gbIO"));
        gbIO->setMinimumSize(QSize(0, 0));
        gbIO->setMaximumSize(QSize(16777215, 16777215));
        gbIO->setFont(font7);
        verticalLayout_6 = new QVBoxLayout(gbIO);
        verticalLayout_6->setSpacing(10);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(10, 30, 10, 10);
        wgOldOutput = new QWidget(gbIO);
        wgOldOutput->setObjectName(QString::fromUtf8("wgOldOutput"));
        horizontalLayout_7 = new QHBoxLayout(wgOldOutput);
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        gbRelay = new QGroupBox(wgOldOutput);
        gbRelay->setObjectName(QString::fromUtf8("gbRelay"));
        gbRelay->setMaximumSize(QSize(150, 16777215));
        gbRelay->setFont(font5);
        gridLayout_3 = new QGridLayout(gbRelay);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_34 = new QLabel(gbRelay);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setMaximumSize(QSize(16777215, 20));
        QFont font9;
        font9.setPointSize(8);
        font9.setBold(false);
        font9.setKerning(true);
        label_34->setFont(font9);
        label_34->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_34, 0, 0, 1, 1);

        label_35 = new QLabel(gbRelay);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setMaximumSize(QSize(16777215, 20));
        label_35->setFont(font9);
        label_35->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_35, 0, 1, 1, 1);

        pbPump = new QPushButton(gbRelay);
        pbPump->setObjectName(QString::fromUtf8("pbPump"));
        pbPump->setMinimumSize(QSize(50, 30));
        pbPump->setAutoFillBackground(false);
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/icon/Toggle Off_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/icon/Toggle On_16px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbPump->setIcon(icon7);
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
        pbLaser->setIcon(icon7);
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
        gbGripper->setFont(font5);
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
        label_17->setFont(font9);
        label_17->setAlignment(Qt::AlignCenter);

        gridLayout_6->addWidget(label_17, 0, 1, 1, 1);

        label_27 = new QLabel(gbGripper);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setFont(font9);
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
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(hsGripperAngle->sizePolicy().hasHeightForWidth());
        hsGripperAngle->setSizePolicy(sizePolicy4);
        hsGripperAngle->setMinimumSize(QSize(0, 30));
        hsGripperAngle->setMaximum(20);
        hsGripperAngle->setSingleStep(5);
        hsGripperAngle->setOrientation(Qt::Horizontal);

        horizontalLayout_15->addWidget(hsGripperAngle);

        lbGripperValue = new QLabel(gbGripper);
        lbGripperValue->setObjectName(QString::fromUtf8("lbGripperValue"));
        lbGripperValue->setMinimumSize(QSize(40, 0));
        QFont font10;
        font10.setPointSize(7);
        font10.setBold(false);
        font10.setKerning(true);
        lbGripperValue->setFont(font10);

        horizontalLayout_15->addWidget(lbGripperValue);


        gridLayout_13->addLayout(horizontalLayout_15, 1, 0, 1, 1);


        horizontalLayout_7->addWidget(gbGripper);

        horizontalSpacer_46 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_46);


        verticalLayout_6->addWidget(wgOldOutput);

        gbOutput = new QGroupBox(gbIO);
        gbOutput->setObjectName(QString::fromUtf8("gbOutput"));
        gbOutput->setMinimumSize(QSize(0, 180));
        gbOutput->setFont(font7);
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
        QFont font11;
        font11.setBold(false);
        label_67->setFont(font11);

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
        cbD13 = new QCheckBox(wgDigitalOutput);
        cbD13->setObjectName(QString::fromUtf8("cbD13"));
        cbD13->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD13, 1, 8, 1, 1);

        horizontalSpacer_69 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_34->addItem(horizontalSpacer_69, 1, 9, 1, 1);

        cbD7 = new QCheckBox(wgDigitalOutput);
        cbD7->setObjectName(QString::fromUtf8("cbD7"));
        cbD7->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD7, 1, 1, 1, 1);

        cbD1 = new QCheckBox(wgDigitalOutput);
        cbD1->setObjectName(QString::fromUtf8("cbD1"));
        cbD1->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD1, 0, 2, 1, 1);

        cbD2 = new QCheckBox(wgDigitalOutput);
        cbD2->setObjectName(QString::fromUtf8("cbD2"));
        cbD2->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD2, 0, 3, 1, 1);

        cbD5 = new QCheckBox(wgDigitalOutput);
        cbD5->setObjectName(QString::fromUtf8("cbD5"));
        cbD5->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD5, 0, 7, 1, 1);

        cbD10 = new QCheckBox(wgDigitalOutput);
        cbD10->setObjectName(QString::fromUtf8("cbD10"));
        cbD10->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD10, 1, 4, 1, 1);

        cbD9 = new QCheckBox(wgDigitalOutput);
        cbD9->setObjectName(QString::fromUtf8("cbD9"));
        cbD9->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD9, 1, 3, 1, 1);

        cbD3 = new QCheckBox(wgDigitalOutput);
        cbD3->setObjectName(QString::fromUtf8("cbD3"));
        cbD3->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD3, 0, 4, 1, 1);

        horizontalSpacer_48 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_34->addItem(horizontalSpacer_48, 0, 9, 1, 1);

        cbD8 = new QCheckBox(wgDigitalOutput);
        cbD8->setObjectName(QString::fromUtf8("cbD8"));
        cbD8->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD8, 1, 2, 1, 1);

        cbD6 = new QCheckBox(wgDigitalOutput);
        cbD6->setObjectName(QString::fromUtf8("cbD6"));
        cbD6->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD6, 0, 8, 1, 1);

        cbD12 = new QCheckBox(wgDigitalOutput);
        cbD12->setObjectName(QString::fromUtf8("cbD12"));
        cbD12->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD12, 1, 7, 1, 1);

        label_68 = new QLabel(wgDigitalOutput);
        label_68->setObjectName(QString::fromUtf8("label_68"));
        label_68->setMinimumSize(QSize(70, 0));
        label_68->setFont(font11);

        gridLayout_34->addWidget(label_68, 0, 0, 1, 1);

        cbD0 = new QCheckBox(wgDigitalOutput);
        cbD0->setObjectName(QString::fromUtf8("cbD0"));
        cbD0->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD0, 0, 1, 1, 1);

        cbD4 = new QCheckBox(wgDigitalOutput);
        cbD4->setObjectName(QString::fromUtf8("cbD4"));
        cbD4->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD4, 0, 6, 1, 1);

        cbD14 = new QCheckBox(wgDigitalOutput);
        cbD14->setObjectName(QString::fromUtf8("cbD14"));
        cbD14->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD14, 2, 1, 1, 1);

        cbD15 = new QCheckBox(wgDigitalOutput);
        cbD15->setObjectName(QString::fromUtf8("cbD15"));
        cbD15->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD15, 2, 2, 1, 1);

        cbD11 = new QCheckBox(wgDigitalOutput);
        cbD11->setObjectName(QString::fromUtf8("cbD11"));
        cbD11->setMinimumSize(QSize(45, 0));

        gridLayout_34->addWidget(cbD11, 1, 6, 1, 1);


        verticalLayout_42->addWidget(wgDigitalOutput);

        wgPWMOutput = new QWidget(gbOutput);
        wgPWMOutput->setObjectName(QString::fromUtf8("wgPWMOutput"));
        wgPWMOutput->setMinimumSize(QSize(0, 40));
        horizontalLayout_36 = new QHBoxLayout(wgPWMOutput);
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        label_69 = new QLabel(wgPWMOutput);
        label_69->setObjectName(QString::fromUtf8("label_69"));
        label_69->setMinimumSize(QSize(70, 0));
        label_69->setMaximumSize(QSize(60, 16777215));
        label_69->setFont(font11);

        horizontalLayout_36->addWidget(label_69);

        label_72 = new QLabel(wgPWMOutput);
        label_72->setObjectName(QString::fromUtf8("label_72"));
        label_72->setMinimumSize(QSize(30, 0));

        horizontalLayout_36->addWidget(label_72);

        leP0Value = new QLineEdit(wgPWMOutput);
        leP0Value->setObjectName(QString::fromUtf8("leP0Value"));
        leP0Value->setMinimumSize(QSize(50, 0));
        leP0Value->setMaximumSize(QSize(50, 16777215));
        leP0Value->setFrame(true);
        leP0Value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leP0Value->setReadOnly(false);

        horizontalLayout_36->addWidget(leP0Value);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_36->addItem(horizontalSpacer_14);

        label_73 = new QLabel(wgPWMOutput);
        label_73->setObjectName(QString::fromUtf8("label_73"));
        label_73->setMinimumSize(QSize(30, 0));

        horizontalLayout_36->addWidget(label_73);

        leP1Value = new QLineEdit(wgPWMOutput);
        leP1Value->setObjectName(QString::fromUtf8("leP1Value"));
        leP1Value->setMinimumSize(QSize(50, 0));
        leP1Value->setMaximumSize(QSize(50, 16777215));
        leP1Value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_36->addWidget(leP1Value);

        horizontalSpacer_28 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_36->addItem(horizontalSpacer_28);

        lePx = new QLineEdit(wgPWMOutput);
        lePx->setObjectName(QString::fromUtf8("lePx"));
        lePx->setMinimumSize(QSize(30, 0));
        lePx->setMaximumSize(QSize(20, 16777215));
        lePx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_36->addWidget(lePx);

        lePxValue = new QLineEdit(wgPWMOutput);
        lePxValue->setObjectName(QString::fromUtf8("lePxValue"));
        lePxValue->setMinimumSize(QSize(50, 0));
        lePxValue->setMaximumSize(QSize(50, 16777215));
        lePxValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_36->addWidget(lePxValue);

        horizontalSpacer_49 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_36->addItem(horizontalSpacer_49);


        verticalLayout_42->addWidget(wgPWMOutput);

        wgRCServoOutput = new QWidget(gbOutput);
        wgRCServoOutput->setObjectName(QString::fromUtf8("wgRCServoOutput"));
        wgRCServoOutput->setMinimumSize(QSize(0, 40));
        horizontalLayout_44 = new QHBoxLayout(wgRCServoOutput);
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        label_71 = new QLabel(wgRCServoOutput);
        label_71->setObjectName(QString::fromUtf8("label_71"));
        label_71->setMinimumSize(QSize(70, 0));
        label_71->setMaximumSize(QSize(60, 16777215));
        label_71->setFont(font11);

        horizontalLayout_44->addWidget(label_71);

        label_75 = new QLabel(wgRCServoOutput);
        label_75->setObjectName(QString::fromUtf8("label_75"));
        label_75->setMinimumSize(QSize(30, 0));

        horizontalLayout_44->addWidget(label_75);

        leS0Value = new QLineEdit(wgRCServoOutput);
        leS0Value->setObjectName(QString::fromUtf8("leS0Value"));
        leS0Value->setMinimumSize(QSize(50, 0));
        leS0Value->setMaximumSize(QSize(50, 16777215));
        leS0Value->setFrame(true);
        leS0Value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        leS0Value->setReadOnly(false);

        horizontalLayout_44->addWidget(leS0Value);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_27);

        label_77 = new QLabel(wgRCServoOutput);
        label_77->setObjectName(QString::fromUtf8("label_77"));
        label_77->setMinimumSize(QSize(30, 0));

        horizontalLayout_44->addWidget(label_77);

        leS1Value = new QLineEdit(wgRCServoOutput);
        leS1Value->setObjectName(QString::fromUtf8("leS1Value"));
        leS1Value->setMinimumSize(QSize(50, 0));
        leS1Value->setMaximumSize(QSize(50, 16777215));
        leS1Value->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_44->addWidget(leS1Value);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_31);

        leSx = new QLineEdit(wgRCServoOutput);
        leSx->setObjectName(QString::fromUtf8("leSx"));
        leSx->setMinimumSize(QSize(30, 0));
        leSx->setMaximumSize(QSize(20, 16777215));
        leSx->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_44->addWidget(leSx);

        leSxValue = new QLineEdit(wgRCServoOutput);
        leSxValue->setObjectName(QString::fromUtf8("leSxValue"));
        leSxValue->setMinimumSize(QSize(50, 0));
        leSxValue->setMaximumSize(QSize(50, 16777215));
        leSxValue->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_44->addWidget(leSxValue);

        horizontalSpacer_50 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_50);


        verticalLayout_42->addWidget(wgRCServoOutput);


        verticalLayout_6->addWidget(gbOutput);

        gbInput = new QGroupBox(gbIO);
        gbInput->setObjectName(QString::fromUtf8("gbInput"));
        gbInput->setMinimumSize(QSize(0, 380));
        gbInput->setFont(font7);
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
        label_70->setFont(font11);

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
        label_74->setFont(font11);

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
        label_76->setFont(font11);

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
        label_78->setFont(font11);

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

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        label_80 = new QLabel(gbInput);
        label_80->setObjectName(QString::fromUtf8("label_80"));
        label_80->setMinimumSize(QSize(30, 0));
        label_80->setMaximumSize(QSize(25, 16777215));
        label_80->setFont(font11);

        horizontalLayout_41->addWidget(label_80);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_23);

        lbI4Value = new QLabel(gbInput);
        lbI4Value->setObjectName(QString::fromUtf8("lbI4Value"));

        horizontalLayout_41->addWidget(lbI4Value);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_24);

        cbToggle4 = new QCheckBox(gbInput);
        cbToggle4->setObjectName(QString::fromUtf8("cbToggle4"));
        cbToggle4->setMinimumSize(QSize(110, 0));
        cbToggle4->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_41->addWidget(cbToggle4);

        pbReadI4 = new QPushButton(gbInput);
        pbReadI4->setObjectName(QString::fromUtf8("pbReadI4"));
        pbReadI4->setMinimumSize(QSize(50, 0));

        horizontalLayout_41->addWidget(pbReadI4);

        horizontalSpacer_55 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_55);


        verticalLayout_43->addLayout(horizontalLayout_41);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(6);
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        label_82 = new QLabel(gbInput);
        label_82->setObjectName(QString::fromUtf8("label_82"));
        label_82->setMinimumSize(QSize(30, 0));
        label_82->setMaximumSize(QSize(25, 16777215));
        label_82->setFont(font11);

        horizontalLayout_42->addWidget(label_82);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_25);

        lbI5Value = new QLabel(gbInput);
        lbI5Value->setObjectName(QString::fromUtf8("lbI5Value"));

        horizontalLayout_42->addWidget(lbI5Value);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_26);

        cbToggle5 = new QCheckBox(gbInput);
        cbToggle5->setObjectName(QString::fromUtf8("cbToggle5"));
        cbToggle5->setMinimumSize(QSize(110, 0));
        cbToggle5->setMaximumSize(QSize(110, 16777215));

        horizontalLayout_42->addWidget(cbToggle5);

        pbReadI5 = new QPushButton(gbInput);
        pbReadI5->setObjectName(QString::fromUtf8("pbReadI5"));
        pbReadI5->setMinimumSize(QSize(50, 0));

        horizontalLayout_42->addWidget(pbReadI5);

        horizontalSpacer_56 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_56);


        verticalLayout_43->addLayout(horizontalLayout_42);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        leIx = new QLineEdit(gbInput);
        leIx->setObjectName(QString::fromUtf8("leIx"));
        leIx->setMinimumSize(QSize(30, 0));
        leIx->setMaximumSize(QSize(25, 16777215));
        leIx->setFont(font11);

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
        label_83->setFont(font11);

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
        label_85->setFont(font11);

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
        leAx->setFont(font11);

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


        verticalLayout_6->addWidget(gbInput);


        verticalLayout_5->addWidget(gbIO);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        scrollArea_2->setWidget(wgJoggingScrollWidget);

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
        twConveyor->setMaximumSize(QSize(16777215, 16777215));
        twConveyor->setTabPosition(QTabWidget::West);
        tConveyor = new QWidget();
        tConveyor->setObjectName(QString::fromUtf8("tConveyor"));
        verticalLayout_16 = new QVBoxLayout(tConveyor);
        verticalLayout_16->setSpacing(10);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        horizontalLayout_48->setContentsMargins(10, -1, -1, -1);
        pbConveyorConnect = new QPushButton(tConveyor);
        pbConveyorConnect->setObjectName(QString::fromUtf8("pbConveyorConnect"));
        pbConveyorConnect->setMinimumSize(QSize(100, 30));
        pbConveyorConnect->setMaximumSize(QSize(120, 40));
        QFont font12;
        font12.setPointSize(12);
        pbConveyorConnect->setFont(font12);
        pbConveyorConnect->setStyleSheet(QString::fromUtf8(""));
        pbConveyorConnect->setCheckable(true);

        horizontalLayout_48->addWidget(pbConveyorConnect);

        lbConveyorCOMName = new QLabel(tConveyor);
        lbConveyorCOMName->setObjectName(QString::fromUtf8("lbConveyorCOMName"));
        QFont font13;
        font13.setPointSize(11);
        lbConveyorCOMName->setFont(font13);
        lbConveyorCOMName->setStyleSheet(QString::fromUtf8("color: rgb(41, 155, 255);"));

        horizontalLayout_48->addWidget(lbConveyorCOMName);


        verticalLayout_16->addLayout(horizontalLayout_48);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setHorizontalSpacing(20);
        gridLayout_7->setVerticalSpacing(10);
        gridLayout_7->setContentsMargins(10, 10, 10, 10);
        label_46 = new QLabel(tConveyor);
        label_46->setObjectName(QString::fromUtf8("label_46"));
        label_46->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_46, 1, 0, 1, 1);

        cbConveyorValueType = new QComboBox(tConveyor);
        cbConveyorValueType->addItem(QString());
        cbConveyorValueType->addItem(QString());
        cbConveyorValueType->setObjectName(QString::fromUtf8("cbConveyorValueType"));
        cbConveyorValueType->setMinimumSize(QSize(0, 20));
        cbConveyorValueType->setMaximumSize(QSize(200, 16777215));
        QFont font14;
        font14.setPointSize(11);
        font14.setBold(false);
        font14.setKerning(true);
        cbConveyorValueType->setFont(font14);
        cbConveyorValueType->setStyleSheet(QString::fromUtf8(""));

        gridLayout_7->addWidget(cbConveyorValueType, 1, 1, 1, 1);

        label_52 = new QLabel(tConveyor);
        label_52->setObjectName(QString::fromUtf8("label_52"));
        label_52->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_52, 0, 0, 1, 1);

        cbConveyorMode = new QComboBox(tConveyor);
        cbConveyorMode->addItem(QString());
        cbConveyorMode->addItem(QString());
        cbConveyorMode->setObjectName(QString::fromUtf8("cbConveyorMode"));
        cbConveyorMode->setMinimumSize(QSize(0, 20));
        cbConveyorMode->setMaximumSize(QSize(200, 16777215));
        cbConveyorMode->setFont(font14);

        gridLayout_7->addWidget(cbConveyorMode, 0, 1, 1, 1);

        label_12 = new QLabel(tConveyor);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_12, 2, 0, 1, 1);

        leConveyorvMovingValue = new QLineEdit(tConveyor);
        leConveyorvMovingValue->setObjectName(QString::fromUtf8("leConveyorvMovingValue"));
        leConveyorvMovingValue->setMinimumSize(QSize(0, 20));
        leConveyorvMovingValue->setMaximumSize(QSize(200, 16777215));
        leConveyorvMovingValue->setFont(font14);

        gridLayout_7->addWidget(leConveyorvMovingValue, 2, 1, 1, 1);

        lbUnitOfConveyorMoving = new QLabel(tConveyor);
        lbUnitOfConveyorMoving->setObjectName(QString::fromUtf8("lbUnitOfConveyorMoving"));
        lbUnitOfConveyorMoving->setEnabled(false);
        lbUnitOfConveyorMoving->setFont(font9);

        gridLayout_7->addWidget(lbUnitOfConveyorMoving, 2, 2, 1, 1);

        label_57 = new QLabel(tConveyor);
        label_57->setObjectName(QString::fromUtf8("label_57"));
        label_57->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_7->addWidget(label_57, 3, 0, 1, 1);

        lbSpeedOfPositionMode = new QLabel(tConveyor);
        lbSpeedOfPositionMode->setObjectName(QString::fromUtf8("lbSpeedOfPositionMode"));
        lbSpeedOfPositionMode->setEnabled(false);
        lbSpeedOfPositionMode->setFont(font9);

        gridLayout_7->addWidget(lbSpeedOfPositionMode, 3, 2, 1, 1);

        leSpeedOfPositionMode = new QLineEdit(tConveyor);
        leSpeedOfPositionMode->setObjectName(QString::fromUtf8("leSpeedOfPositionMode"));
        leSpeedOfPositionMode->setEnabled(false);
        leSpeedOfPositionMode->setMinimumSize(QSize(0, 20));
        leSpeedOfPositionMode->setMaximumSize(QSize(200, 16777215));
        leSpeedOfPositionMode->setFont(font14);
        leSpeedOfPositionMode->setClearButtonEnabled(false);

        gridLayout_7->addWidget(leSpeedOfPositionMode, 3, 1, 1, 1);


        verticalLayout_16->addLayout(gridLayout_7);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_2);

        twConveyor->addTab(tConveyor, QString());
        sSlidingRail = new QWidget();
        sSlidingRail->setObjectName(QString::fromUtf8("sSlidingRail"));
        verticalLayout_18 = new QVBoxLayout(sSlidingRail);
        verticalLayout_18->setSpacing(10);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(10, 10, 10, 10);
        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        horizontalLayout_49->setContentsMargins(10, -1, -1, -1);
        pbSlidingConnect = new QPushButton(sSlidingRail);
        pbSlidingConnect->setObjectName(QString::fromUtf8("pbSlidingConnect"));
        pbSlidingConnect->setMinimumSize(QSize(100, 30));
        pbSlidingConnect->setMaximumSize(QSize(120, 50));
        pbSlidingConnect->setFont(font12);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("icon/connected.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingConnect->setIcon(icon8);

        horizontalLayout_49->addWidget(pbSlidingConnect);

        lbSliderCOMName = new QLabel(sSlidingRail);
        lbSliderCOMName->setObjectName(QString::fromUtf8("lbSliderCOMName"));
        lbSliderCOMName->setFont(font13);
        lbSliderCOMName->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_49->addWidget(lbSliderCOMName);


        verticalLayout_18->addLayout(horizontalLayout_49);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(10);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setContentsMargins(10, 10, 10, 10);
        leSlidingPosition = new QLineEdit(sSlidingRail);
        leSlidingPosition->setObjectName(QString::fromUtf8("leSlidingPosition"));
        leSlidingPosition->setMinimumSize(QSize(0, 30));
        leSlidingPosition->setMaximumSize(QSize(200, 40));

        gridLayout_8->addWidget(leSlidingPosition, 3, 1, 1, 1);

        pbSlidingDisable = new QPushButton(sSlidingRail);
        pbSlidingDisable->setObjectName(QString::fromUtf8("pbSlidingDisable"));
        pbSlidingDisable->setMinimumSize(QSize(0, 30));
        pbSlidingDisable->setMaximumSize(QSize(200, 40));
        pbSlidingDisable->setFont(font13);
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("icon/icons8-sleeping-in-bed-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingDisable->setIcon(icon9);

        gridLayout_8->addWidget(pbSlidingDisable, 0, 1, 1, 1);

        label_58 = new QLabel(sSlidingRail);
        label_58->setObjectName(QString::fromUtf8("label_58"));
        label_58->setFont(font9);

        gridLayout_8->addWidget(label_58, 2, 2, 1, 1);

        label_37 = new QLabel(sSlidingRail);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setFont(font9);
        label_37->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_37, 3, 0, 1, 1);

        pbSlidingHome = new QPushButton(sSlidingRail);
        pbSlidingHome->setObjectName(QString::fromUtf8("pbSlidingHome"));
        pbSlidingHome->setMinimumSize(QSize(0, 30));
        pbSlidingHome->setMaximumSize(QSize(200, 40));
        pbSlidingHome->setFont(font13);
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("icon/icons8-home-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSlidingHome->setIcon(icon10);

        gridLayout_8->addWidget(pbSlidingHome, 1, 1, 1, 1);

        leSlidingSpeed = new QLineEdit(sSlidingRail);
        leSlidingSpeed->setObjectName(QString::fromUtf8("leSlidingSpeed"));
        leSlidingSpeed->setMinimumSize(QSize(0, 30));
        leSlidingSpeed->setMaximumSize(QSize(200, 40));

        gridLayout_8->addWidget(leSlidingSpeed, 2, 1, 1, 1);

        label_36 = new QLabel(sSlidingRail);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setFont(font9);
        label_36->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_8->addWidget(label_36, 2, 0, 1, 1);

        label_59 = new QLabel(sSlidingRail);
        label_59->setObjectName(QString::fromUtf8("label_59"));
        label_59->setFont(font9);

        gridLayout_8->addWidget(label_59, 3, 2, 1, 1);


        verticalLayout_18->addLayout(gridLayout_8);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_3);

        twConveyor->addTab(sSlidingRail, QString());
        tExternalMCU = new QWidget();
        tExternalMCU->setObjectName(QString::fromUtf8("tExternalMCU"));
        verticalLayout_20 = new QVBoxLayout(tExternalMCU);
        verticalLayout_20->setSpacing(5);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        verticalLayout_20->setContentsMargins(10, 10, 10, 10);
        widget1 = new QWidget(tExternalMCU);
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
        QFont font15;
        font15.setPointSize(12);
        font15.setBold(false);
        font15.setKerning(true);
        pbExternalControllerConnect->setFont(font15);

        horizontalLayout_50->addWidget(pbExternalControllerConnect);

        lbExternalCOMName = new QLabel(widget1);
        lbExternalCOMName->setObjectName(QString::fromUtf8("lbExternalCOMName"));
        lbExternalCOMName->setMaximumSize(QSize(16777215, 30));
        lbExternalCOMName->setFont(font13);
        lbExternalCOMName->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_50->addWidget(lbExternalCOMName);


        verticalLayout_20->addWidget(widget1);

        teReceiveFromMCU = new QTextEdit(tExternalMCU);
        teReceiveFromMCU->setObjectName(QString::fromUtf8("teReceiveFromMCU"));

        verticalLayout_20->addWidget(teReceiveFromMCU);

        leTransmitToMCU = new QLineEdit(tExternalMCU);
        leTransmitToMCU->setObjectName(QString::fromUtf8("leTransmitToMCU"));
        leTransmitToMCU->setMinimumSize(QSize(0, 30));

        verticalLayout_20->addWidget(leTransmitToMCU);

        twConveyor->addTab(tExternalMCU, QString());

        verticalLayout_19->addWidget(twConveyor);

        twDeltaGeometry->addTab(xExternal, QString());
        tTerminal = new QWidget();
        tTerminal->setObjectName(QString::fromUtf8("tTerminal"));
        verticalLayout_28 = new QVBoxLayout(tTerminal);
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setContentsMargins(11, 11, 11, 11);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        scrollArea_7 = new QScrollArea(tTerminal);
        scrollArea_7->setObjectName(QString::fromUtf8("scrollArea_7"));
        scrollArea_7->setWidgetResizable(true);
        scrollAreaWidgetContents_7 = new QWidget();
        scrollAreaWidgetContents_7->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_7"));
        scrollAreaWidgetContents_7->setGeometry(QRect(0, 0, 550, 413));
        verticalLayout_27 = new QVBoxLayout(scrollAreaWidgetContents_7);
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setContentsMargins(11, 11, 11, 11);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        teDebug = new QTextEdit(scrollAreaWidgetContents_7);
        teDebug->setObjectName(QString::fromUtf8("teDebug"));
        teDebug->setFont(font3);
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
        cbDeviceSender->setObjectName(QString::fromUtf8("cbDeviceSender"));

        gridLayout_4->addWidget(cbDeviceSender, 1, 2, 1, 1);


        verticalLayout_27->addLayout(gridLayout_4);

        scrollArea_7->setWidget(scrollAreaWidgetContents_7);

        verticalLayout_28->addWidget(scrollArea_7);

        twDeltaGeometry->addTab(tTerminal, QString());

        GeometryTabManagerLayout->addWidget(twDeltaGeometry);

        splitter_2->addWidget(GeometryTabManagerWidget);
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
        twModule->setFont(font6);
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
        gridLayout_30 = new QGridLayout();
        gridLayout_30->setSpacing(6);
        gridLayout_30->setObjectName(QString::fromUtf8("gridLayout_30"));
        pbExecuteGcodes = new QPushButton(tGcodeEditor);
        pbExecuteGcodes->setObjectName(QString::fromUtf8("pbExecuteGcodes"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(pbExecuteGcodes->sizePolicy().hasHeightForWidth());
        pbExecuteGcodes->setSizePolicy(sizePolicy5);
        pbExecuteGcodes->setMinimumSize(QSize(70, 0));
        pbExecuteGcodes->setFont(font8);
        pbExecuteGcodes->setAutoFillBackground(false);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/icon/Play_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon11.addFile(QString::fromUtf8(":/icon/Pause_96px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbExecuteGcodes->setIcon(icon11);
        pbExecuteGcodes->setIconSize(QSize(30, 30));
        pbExecuteGcodes->setCheckable(true);
        pbExecuteGcodes->setFlat(false);

        gridLayout_30->addWidget(pbExecuteGcodes, 0, 3, 3, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_30->addItem(horizontalSpacer_2, 0, 1, 1, 1);

        rbEditorCurrent = new QRadioButton(tGcodeEditor);
        rbEditorCurrent->setObjectName(QString::fromUtf8("rbEditorCurrent"));
        rbEditorCurrent->setChecked(false);

        gridLayout_30->addWidget(rbEditorCurrent, 2, 2, 1, 1);

        rbEditorStart = new QRadioButton(tGcodeEditor);
        rbEditorStart->setObjectName(QString::fromUtf8("rbEditorStart"));
        rbEditorStart->setChecked(true);

        gridLayout_30->addWidget(rbEditorStart, 0, 2, 1, 1);

        cbLockGcodeEditor = new QCheckBox(tGcodeEditor);
        cbLockGcodeEditor->setObjectName(QString::fromUtf8("cbLockGcodeEditor"));
        cbLockGcodeEditor->setFont(font9);

        gridLayout_30->addWidget(cbLockGcodeEditor, 0, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        pbFormat = new QToolButton(tGcodeEditor);
        pbFormat->setObjectName(QString::fromUtf8("pbFormat"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/icon/index.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFormat->setIcon(icon12);
        pbFormat->setIconSize(QSize(30, 30));
        pbFormat->setAutoRaise(true);

        verticalLayout_8->addWidget(pbFormat);


        horizontalLayout_12->addLayout(verticalLayout_8);

        cbFormatColor = new QCheckBox(tGcodeEditor);
        cbFormatColor->setObjectName(QString::fromUtf8("cbFormatColor"));
        cbFormatColor->setChecked(true);

        horizontalLayout_12->addWidget(cbFormatColor);

        cbAutoNumbering = new QCheckBox(tGcodeEditor);
        cbAutoNumbering->setObjectName(QString::fromUtf8("cbAutoNumbering"));
        cbAutoNumbering->setChecked(true);

        horizontalLayout_12->addWidget(cbAutoNumbering);

        lbGcodeProgramingIssues = new QLabel(tGcodeEditor);
        lbGcodeProgramingIssues->setObjectName(QString::fromUtf8("lbGcodeProgramingIssues"));
        lbGcodeProgramingIssues->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_12->addWidget(lbGcodeProgramingIssues);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_3);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        pbSaveGcode = new QToolButton(tGcodeEditor);
        pbSaveGcode->setObjectName(QString::fromUtf8("pbSaveGcode"));
        sizePolicy.setHeightForWidth(pbSaveGcode->sizePolicy().hasHeightForWidth());
        pbSaveGcode->setSizePolicy(sizePolicy);
        pbSaveGcode->setMinimumSize(QSize(30, 30));
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/icon/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSaveGcode->setIcon(icon13);
        pbSaveGcode->setIconSize(QSize(32, 32));
        pbSaveGcode->setAutoRaise(true);

        verticalLayout_9->addWidget(pbSaveGcode);


        horizontalLayout_12->addLayout(verticalLayout_9);


        gridLayout_30->addLayout(horizontalLayout_12, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_30);

        scrollArea = new QScrollArea(tGcodeEditor);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 553, 1200));
        scrollAreaWidgetContents->setMinimumSize(QSize(450, 1200));
        verticalLayout_30 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_30->setSpacing(6);
        verticalLayout_30->setContentsMargins(11, 11, 11, 11);
        verticalLayout_30->setObjectName(QString::fromUtf8("verticalLayout_30"));
        pteGcodeArea = new CodeEditor(scrollAreaWidgetContents);
        pteGcodeArea->setObjectName(QString::fromUtf8("pteGcodeArea"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pteGcodeArea->sizePolicy().hasHeightForWidth());
        pteGcodeArea->setSizePolicy(sizePolicy6);
        pteGcodeArea->setMinimumSize(QSize(310, 500));
        pteGcodeArea->setFont(font9);
        pteGcodeArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pteGcodeArea->setReadOnly(false);
        pteGcodeArea->setTextInteractionFlags(Qt::TextEditorInteraction);

        verticalLayout_30->addWidget(pteGcodeArea);

        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setMinimumSize(QSize(0, 500));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        saProgramFiles = new QScrollArea(tab);
        saProgramFiles->setObjectName(QString::fromUtf8("saProgramFiles"));
        saProgramFiles->setEnabled(true);
        saProgramFiles->setGeometry(QRect(85, 45, 256, 300));
        saProgramFiles->setMinimumSize(QSize(240, 300));
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
        leExProgramName->setFont(font8);
        leExProgramName->setCursor(QCursor(Qt::SizeHorCursor));
        leExProgramName->setStyleSheet(QString::fromUtf8(""));
        pbExDeleteProgram = new QPushButton(frExProgram);
        pbExDeleteProgram->setObjectName(QString::fromUtf8("pbExDeleteProgram"));
        pbExDeleteProgram->setGeometry(QRect(180, 5, 30, 31));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("C:/Users/Admin/.designer/backup/icon/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbExDeleteProgram->setIcon(icon14);
        pbExDeleteProgram->setIconSize(QSize(30, 30));
        pbExDeleteProgram->setAutoDefault(false);
        pbExDeleteProgram->setFlat(true);
        lbExGCodeNumber = new QLabel(frExProgram);
        lbExGCodeNumber->setObjectName(QString::fromUtf8("lbExGCodeNumber"));
        lbExGCodeNumber->setGeometry(QRect(10, 40, 101, 16));
        lbExGCodeNumber->setStyleSheet(QString::fromUtf8(""));
        saProgramFiles->setWidget(wgProgramContainer);
        layoutWidget1 = new QWidget(tab);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(355, 45, 71, 91));
        verticalLayout_13 = new QVBoxLayout(layoutWidget1);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        pbUploadProgram = new QPushButton(layoutWidget1);
        pbUploadProgram->setObjectName(QString::fromUtf8("pbUploadProgram"));
        pbUploadProgram->setMinimumSize(QSize(40, 40));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/icon/icons8-upload-to-cloud-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbUploadProgram->setIcon(icon15);
        pbUploadProgram->setIconSize(QSize(32, 32));
        pbUploadProgram->setFlat(false);

        verticalLayout_13->addWidget(pbUploadProgram);

        pbImportGcodeFiles = new QPushButton(layoutWidget1);
        pbImportGcodeFiles->setObjectName(QString::fromUtf8("pbImportGcodeFiles"));
        pbImportGcodeFiles->setMinimumSize(QSize(40, 40));
        pbImportGcodeFiles->setIconSize(QSize(32, 32));
        pbImportGcodeFiles->setFlat(false);

        verticalLayout_13->addWidget(pbImportGcodeFiles);

        layoutWidget2 = new QWidget(tab);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(5, 45, 66, 183));
        verticalLayout_14 = new QVBoxLayout(layoutWidget2);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        pbAddNewProgram = new QPushButton(layoutWidget2);
        pbAddNewProgram->setObjectName(QString::fromUtf8("pbAddNewProgram"));
        pbAddNewProgram->setMinimumSize(QSize(40, 40));
        QIcon icon16;
        icon16.addFile(QString::fromUtf8(":/icon/new.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbAddNewProgram->setIcon(icon16);
        pbAddNewProgram->setIconSize(QSize(16, 16));
        pbAddNewProgram->setFlat(false);

        verticalLayout_14->addWidget(pbAddNewProgram);

        pbRefreshGcodeFiles = new QPushButton(layoutWidget2);
        pbRefreshGcodeFiles->setObjectName(QString::fromUtf8("pbRefreshGcodeFiles"));
        pbRefreshGcodeFiles->setMinimumSize(QSize(40, 40));
        QIcon icon17;
        icon17.addFile(QString::fromUtf8(":/icon/Restart_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRefreshGcodeFiles->setIcon(icon17);
        pbRefreshGcodeFiles->setIconSize(QSize(16, 16));
        pbRefreshGcodeFiles->setFlat(false);

        verticalLayout_14->addWidget(pbRefreshGcodeFiles);

        pbFindGcodeFile = new QPushButton(layoutWidget2);
        pbFindGcodeFile->setObjectName(QString::fromUtf8("pbFindGcodeFile"));
        pbFindGcodeFile->setMinimumSize(QSize(40, 40));
        QIcon icon18;
        icon18.addFile(QString::fromUtf8(":/icon/Search_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFindGcodeFile->setIcon(icon18);
        pbFindGcodeFile->setIconSize(QSize(16, 16));
        pbFindGcodeFile->setFlat(false);

        verticalLayout_14->addWidget(pbFindGcodeFile);

        pbSortGcodeFiles = new QPushButton(layoutWidget2);
        pbSortGcodeFiles->setObjectName(QString::fromUtf8("pbSortGcodeFiles"));
        pbSortGcodeFiles->setMinimumSize(QSize(40, 40));
        QIcon icon19;
        icon19.addFile(QString::fromUtf8(":/icon/Sort_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbSortGcodeFiles->setIcon(icon19);
        pbSortGcodeFiles->setIconSize(QSize(16, 16));
        pbSortGcodeFiles->setFlat(false);

        verticalLayout_14->addWidget(pbSortGcodeFiles);

        lbExGCodeNumber_2 = new QLabel(tab);
        lbExGCodeNumber_2->setObjectName(QString::fromUtf8("lbExGCodeNumber_2"));
        lbExGCodeNumber_2->setGeometry(QRect(10, 20, 41, 16));
        lbExGCodeNumber_2->setStyleSheet(QString::fromUtf8(""));
        leGcodeProgramPath = new QLineEdit(tab);
        leGcodeProgramPath->setObjectName(QString::fromUtf8("leGcodeProgramPath"));
        leGcodeProgramPath->setGeometry(QRect(85, 15, 251, 22));
        pbOpenGcodeProgramPath = new QPushButton(tab);
        pbOpenGcodeProgramPath->setObjectName(QString::fromUtf8("pbOpenGcodeProgramPath"));
        pbOpenGcodeProgramPath->setGeometry(QRect(355, 10, 30, 30));
        sizePolicy1.setHeightForWidth(pbOpenGcodeProgramPath->sizePolicy().hasHeightForWidth());
        pbOpenGcodeProgramPath->setSizePolicy(sizePolicy1);
        pbOpenGcodeProgramPath->setMaximumSize(QSize(30, 16777215));
        QIcon icon20;
        icon20.addFile(QString::fromUtf8(":/icon/icons8_folder_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenGcodeProgramPath->setIcon(icon20);
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

        verticalLayout_30->addWidget(tabWidget);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_30->addItem(verticalSpacer_9);

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
        wObjectDetecting->setGeometry(QRect(0, 0, 571, 4000));
        wObjectDetecting->setMinimumSize(QSize(450, 4000));
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
        splitter = new QSplitter(wObjectDetecting);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        sizePolicy2.setHeightForWidth(splitter->sizePolicy().hasHeightForWidth());
        splitter->setSizePolicy(sizePolicy2);
        splitter->setStyleSheet(QString::fromUtf8("QSplitter::handle:vertical \n"
"{	\n"
"	background: rgb(37, 197, 255);\n"
"}"));
        splitter->setOrientation(Qt::Vertical);
        splitter->setHandleWidth(10);
        gbImageViewer = new QGroupBox(splitter);
        gbImageViewer->setObjectName(QString::fromUtf8("gbImageViewer"));
        QSizePolicy sizePolicy7(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(gbImageViewer->sizePolicy().hasHeightForWidth());
        gbImageViewer->setSizePolicy(sizePolicy7);
        gbImageViewer->setMinimumSize(QSize(0, 0));
        gbImageViewer->setMaximumSize(QSize(16777215, 16777215));
        gbImageViewer->setFont(font7);
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
        QIcon icon22;
        icon22.addFile(QString::fromUtf8(":/icon/icons8_chessboard_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFindChessboardTool->setIcon(icon22);
        pbFindChessboardTool->setCheckable(true);
        pbFindChessboardTool->setFlat(true);

        verticalLayout_7->addWidget(pbFindChessboardTool);

        pbWarpTool = new QPushButton(frame_16);
        pbWarpTool->setObjectName(QString::fromUtf8("pbWarpTool"));
        pbWarpTool->setMinimumSize(QSize(30, 30));
        QIcon icon23;
        icon23.addFile(QString::fromUtf8(":/icon/icons8_opacity_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbWarpTool->setIcon(icon23);
        pbWarpTool->setCheckable(true);
        pbWarpTool->setFlat(true);

        verticalLayout_7->addWidget(pbWarpTool);

        pbAreaTool = new QPushButton(frame_16);
        pbAreaTool->setObjectName(QString::fromUtf8("pbAreaTool"));
        pbAreaTool->setMinimumSize(QSize(30, 30));
        QIcon icon24;
        icon24.addFile(QString::fromUtf8(":/icon/icons8_rectangle_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbAreaTool->setIcon(icon24);
        pbAreaTool->setCheckable(true);
        pbAreaTool->setFlat(true);

        verticalLayout_7->addWidget(pbAreaTool);

        pbCalibPointTool = new QPushButton(frame_16);
        pbCalibPointTool->setObjectName(QString::fromUtf8("pbCalibPointTool"));
        pbCalibPointTool->setMinimumSize(QSize(30, 30));
        QIcon icon25;
        icon25.addFile(QString::fromUtf8(":/icon/icons8_select_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCalibPointTool->setIcon(icon25);
        pbCalibPointTool->setCheckable(true);
        pbCalibPointTool->setFlat(true);

        verticalLayout_7->addWidget(pbCalibPointTool);

        pbMappingPointTool = new QPushButton(frame_16);
        pbMappingPointTool->setObjectName(QString::fromUtf8("pbMappingPointTool"));
        pbMappingPointTool->setMinimumSize(QSize(30, 30));
        QIcon icon26;
        icon26.addFile(QString::fromUtf8(":/icon/icons8_target_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbMappingPointTool->setIcon(icon26);
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
        QIcon icon27;
        icon27.addFile(QString::fromUtf8(":/icon/icons8_page_size_64px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbGetSizeTool->setIcon(icon27);
        pbGetSizeTool->setCheckable(true);
        pbGetSizeTool->setAutoRaise(true);

        verticalLayout_50->addWidget(pbGetSizeTool);

        pbFilterTool = new QPushButton(frame_8);
        pbFilterTool->setObjectName(QString::fromUtf8("pbFilterTool"));
        pbFilterTool->setMinimumSize(QSize(30, 30));
        QIcon icon28;
        icon28.addFile(QString::fromUtf8(":/icon/Slider 2_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbFilterTool->setIcon(icon28);
        pbFilterTool->setFlat(true);

        verticalLayout_50->addWidget(pbFilterTool);

        pbOpenObjectTable = new QPushButton(frame_8);
        pbOpenObjectTable->setObjectName(QString::fromUtf8("pbOpenObjectTable"));
        pbOpenObjectTable->setMinimumSize(QSize(30, 30));
        QIcon icon29;
        icon29.addFile(QString::fromUtf8(":/icon/icons8-object-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenObjectTable->setIcon(icon29);
        pbOpenObjectTable->setFlat(true);

        verticalLayout_50->addWidget(pbOpenObjectTable);

        pbClearObject = new QPushButton(frame_8);
        pbClearObject->setObjectName(QString::fromUtf8("pbClearObject"));
        pbClearObject->setMinimumSize(QSize(30, 30));
        QIcon icon30;
        icon30.addFile(QString::fromUtf8(":/icon/Eraser_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbClearObject->setIcon(icon30);
        pbClearObject->setFlat(true);

        verticalLayout_50->addWidget(pbClearObject);

        verticalSpacer_13 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_50->addItem(verticalSpacer_13);


        horizontalLayout_30->addWidget(frame_8);

        gvImageViewer = new ImageViewer(fImageViewer);
        gvImageViewer->setObjectName(QString::fromUtf8("gvImageViewer"));
        sizePolicy2.setHeightForWidth(gvImageViewer->sizePolicy().hasHeightForWidth());
        gvImageViewer->setSizePolicy(sizePolicy2);

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
        sizePolicy3.setHeightForWidth(cbImageOutput->sizePolicy().hasHeightForWidth());
        cbImageOutput->setSizePolicy(sizePolicy3);
        cbImageOutput->setMinimumSize(QSize(90, 0));

        verticalLayout_10->addWidget(cbImageOutput);

        pbCameraWindowMode = new QPushButton(frame_17);
        pbCameraWindowMode->setObjectName(QString::fromUtf8("pbCameraWindowMode"));
        sizePolicy.setHeightForWidth(pbCameraWindowMode->sizePolicy().hasHeightForWidth());
        pbCameraWindowMode->setSizePolicy(sizePolicy);
        pbCameraWindowMode->setMinimumSize(QSize(0, 0));
        QIcon icon31;
        icon31.addFile(QString::fromUtf8(":/icon/icons8-maximize-window-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCameraWindowMode->setIcon(icon31);
        pbCameraWindowMode->setFlat(false);

        verticalLayout_10->addWidget(pbCameraWindowMode);

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
        gbImageProvider->setFont(font7);
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

        horizontalLayout_10->addWidget(cbSourceForImageProvider);

        horizontalSpacer_44 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_44);


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
        QFont font16;
        font16.setPointSize(8);
        font16.setBold(false);
        pbLoadCamera->setFont(font16);
        QIcon icon32;
        icon32.addFile(QString::fromUtf8(":/icon/webcam.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLoadCamera->setIcon(icon32);
        pbLoadCamera->setIconSize(QSize(30, 30));
        pbLoadCamera->setCheckable(true);
        pbLoadCamera->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbLoadCamera->setAutoRaise(true);

        horizontalLayout_11->addWidget(pbLoadCamera);

        label_11 = new QLabel(fWebcamSource);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setMaximumSize(QSize(30, 16777215));
        label_11->setFont(font2);

        horizontalLayout_11->addWidget(label_11);

        leFPS = new QLineEdit(fWebcamSource);
        leFPS->setObjectName(QString::fromUtf8("leFPS"));
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(leFPS->sizePolicy().hasHeightForWidth());
        leFPS->setSizePolicy(sizePolicy9);
        leFPS->setMinimumSize(QSize(0, 10));
        leFPS->setMaximumSize(QSize(40, 25));
        leFPS->setFont(font2);
        leFPS->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(leFPS);

        label_124 = new QLabel(fWebcamSource);
        label_124->setObjectName(QString::fromUtf8("label_124"));
        label_124->setFont(font2);
        label_124->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_124);

        leCameraWidth = new QLineEdit(fWebcamSource);
        leCameraWidth->setObjectName(QString::fromUtf8("leCameraWidth"));
        sizePolicy9.setHeightForWidth(leCameraWidth->sizePolicy().hasHeightForWidth());
        leCameraWidth->setSizePolicy(sizePolicy9);
        leCameraWidth->setMinimumSize(QSize(0, 10));
        leCameraWidth->setMaximumSize(QSize(40, 25));
        leCameraWidth->setFont(font2);
        leCameraWidth->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(leCameraWidth);

        label_125 = new QLabel(fWebcamSource);
        label_125->setObjectName(QString::fromUtf8("label_125"));
        label_125->setFont(font2);
        label_125->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_11->addWidget(label_125);

        leCameraHeight = new QLineEdit(fWebcamSource);
        leCameraHeight->setObjectName(QString::fromUtf8("leCameraHeight"));
        sizePolicy9.setHeightForWidth(leCameraHeight->sizePolicy().hasHeightForWidth());
        leCameraHeight->setSizePolicy(sizePolicy9);
        leCameraHeight->setMinimumSize(QSize(0, 10));
        leCameraHeight->setMaximumSize(QSize(40, 25));
        leCameraHeight->setFont(font2);
        leCameraHeight->setAlignment(Qt::AlignCenter);

        horizontalLayout_11->addWidget(leCameraHeight);

        horizontalSpacer_45 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_45);

        pbPlayPauseCamera = new QToolButton(fWebcamSource);
        pbPlayPauseCamera->setObjectName(QString::fromUtf8("pbPlayPauseCamera"));
        pbPlayPauseCamera->setEnabled(false);
        sizePolicy.setHeightForWidth(pbPlayPauseCamera->sizePolicy().hasHeightForWidth());
        pbPlayPauseCamera->setSizePolicy(sizePolicy);
        pbPlayPauseCamera->setMinimumSize(QSize(0, 0));
        pbPlayPauseCamera->setFont(font2);
        QIcon icon33;
        icon33.addFile(QString::fromUtf8(":/icon/icons8-play-48.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon33.addFile(QString::fromUtf8(":/icon/icons8-pause-48.png"), QSize(), QIcon::Normal, QIcon::On);
        icon33.addFile(QString::fromUtf8("icon/icons8-play-48.png"), QSize(), QIcon::Selected, QIcon::Off);
        pbPlayPauseCamera->setIcon(icon33);
        pbPlayPauseCamera->setIconSize(QSize(30, 30));
        pbPlayPauseCamera->setCheckable(true);
        pbPlayPauseCamera->setChecked(false);
        pbPlayPauseCamera->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbPlayPauseCamera->setAutoRaise(true);

        horizontalLayout_11->addWidget(pbPlayPauseCamera);

        pbCaptureCamera = new QToolButton(fWebcamSource);
        pbCaptureCamera->setObjectName(QString::fromUtf8("pbCaptureCamera"));
        pbCaptureCamera->setEnabled(false);
        pbCaptureCamera->setMinimumSize(QSize(0, 0));
        pbCaptureCamera->setFont(font2);
        QIcon icon34;
        icon34.addFile(QString::fromUtf8(":/icon/icons8-screenshot-40.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCaptureCamera->setIcon(icon34);
        pbCaptureCamera->setIconSize(QSize(30, 30));
        pbCaptureCamera->setCheckable(false);
        pbCaptureCamera->setChecked(false);
        pbCaptureCamera->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbCaptureCamera->setAutoRaise(true);

        horizontalLayout_11->addWidget(pbCaptureCamera);

        lbCameraState = new QLabel(fWebcamSource);
        lbCameraState->setObjectName(QString::fromUtf8("lbCameraState"));
        lbCameraState->setEnabled(false);
        lbCameraState->setMaximumSize(QSize(20, 20));
        lbCameraState->setPixmap(QPixmap(QString::fromUtf8("icon/icons8-connection-status-on-48.png")));
        lbCameraState->setScaledContents(true);

        horizontalLayout_11->addWidget(lbCameraState);


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
        pbLoadTestImage->setFont(font2);
        QIcon icon35;
        icon35.addFile(QString::fromUtf8(":/icon/icons8_image_30px_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbLoadTestImage->setIcon(icon35);
        pbLoadTestImage->setIconSize(QSize(30, 30));
        pbLoadTestImage->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbLoadTestImage->setAutoRaise(true);

        horizontalLayout_27->addWidget(pbLoadTestImage);

        horizontalSpacer_64 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_64);


        verticalLayout_51->addWidget(fImageSource);

        fPluginSource = new QFrame(fImageProvider);
        fPluginSource->setObjectName(QString::fromUtf8("fPluginSource"));
        fPluginSource->setMinimumSize(QSize(0, 20));
        fPluginSource->setMaximumSize(QSize(16777215, 50));
        fPluginSource->setStyleSheet(QString::fromUtf8("QFrame#fPluginSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}"));
        fPluginSource->setFrameShape(QFrame::StyledPanel);
        fPluginSource->setFrameShadow(QFrame::Raised);
        horizontalLayout_28 = new QHBoxLayout(fPluginSource);
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalLayout_28->setContentsMargins(5, 5, 5, 5);
        cbExternalImageSource = new QCheckBox(fPluginSource);
        cbExternalImageSource->setObjectName(QString::fromUtf8("cbExternalImageSource"));

        horizontalLayout_28->addWidget(cbExternalImageSource);

        label_177 = new QLabel(fPluginSource);
        label_177->setObjectName(QString::fromUtf8("label_177"));
        label_177->setMaximumSize(QSize(100, 16777215));
        label_177->setFont(font2);

        horizontalLayout_28->addWidget(label_177);

        comboBox_2 = new QComboBox(fPluginSource);
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        sizePolicy.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy);
        comboBox_2->setMinimumSize(QSize(150, 0));

        horizontalLayout_28->addWidget(comboBox_2);

        label_178 = new QLabel(fPluginSource);
        label_178->setObjectName(QString::fromUtf8("label_178"));
        label_178->setFont(font2);
        label_178->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_28->addWidget(label_178);

        leImageWidth = new QLineEdit(fPluginSource);
        leImageWidth->setObjectName(QString::fromUtf8("leImageWidth"));
        sizePolicy9.setHeightForWidth(leImageWidth->sizePolicy().hasHeightForWidth());
        leImageWidth->setSizePolicy(sizePolicy9);
        leImageWidth->setMinimumSize(QSize(0, 10));
        leImageWidth->setMaximumSize(QSize(40, 25));
        leImageWidth->setFont(font2);
        leImageWidth->setAlignment(Qt::AlignCenter);

        horizontalLayout_28->addWidget(leImageWidth);

        label_179 = new QLabel(fPluginSource);
        label_179->setObjectName(QString::fromUtf8("label_179"));
        label_179->setFont(font2);
        label_179->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_28->addWidget(label_179);

        leImageHeight = new QLineEdit(fPluginSource);
        leImageHeight->setObjectName(QString::fromUtf8("leImageHeight"));
        sizePolicy9.setHeightForWidth(leImageHeight->sizePolicy().hasHeightForWidth());
        leImageHeight->setSizePolicy(sizePolicy9);
        leImageHeight->setMinimumSize(QSize(0, 10));
        leImageHeight->setMaximumSize(QSize(40, 25));
        leImageHeight->setFont(font2);
        leImageHeight->setAlignment(Qt::AlignCenter);

        horizontalLayout_28->addWidget(leImageHeight);

        horizontalSpacer_65 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_65);


        verticalLayout_51->addWidget(fPluginSource);


        verticalLayout_39->addWidget(fImageProvider);


        verticalLayout_32->addWidget(gbImageProvider);

        gbCameraCalibration = new QGroupBox(fObjectDetectingTool);
        gbCameraCalibration->setObjectName(QString::fromUtf8("gbCameraCalibration"));
        gbCameraCalibration->setFont(font7);
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
        horizontalSpacer_42 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_27->addItem(horizontalSpacer_42, 1, 3, 1, 1);

        leChessWidth = new QLineEdit(fCalibStep1);
        leChessWidth->setObjectName(QString::fromUtf8("leChessWidth"));
        sizePolicy1.setHeightForWidth(leChessWidth->sizePolicy().hasHeightForWidth());
        leChessWidth->setSizePolicy(sizePolicy1);
        leChessWidth->setMinimumSize(QSize(20, 0));
        leChessWidth->setMaximumSize(QSize(70, 16777215));

        gridLayout_27->addWidget(leChessWidth, 1, 1, 1, 1);

        leChessHeight = new QLineEdit(fCalibStep1);
        leChessHeight->setObjectName(QString::fromUtf8("leChessHeight"));
        sizePolicy9.setHeightForWidth(leChessHeight->sizePolicy().hasHeightForWidth());
        leChessHeight->setSizePolicy(sizePolicy9);
        leChessHeight->setMaximumSize(QSize(70, 16777215));

        gridLayout_27->addWidget(leChessHeight, 1, 2, 1, 1);

        label_109 = new QLabel(fCalibStep1);
        label_109->setObjectName(QString::fromUtf8("label_109"));
        label_109->setMinimumSize(QSize(0, 25));

        gridLayout_27->addWidget(label_109, 0, 1, 1, 2);

        pbTransformPerspective = new QPushButton(fCalibStep1);
        pbTransformPerspective->setObjectName(QString::fromUtf8("pbTransformPerspective"));
        pbTransformPerspective->setMinimumSize(QSize(0, 45));
        pbTransformPerspective->setMaximumSize(QSize(150, 16777215));
        pbTransformPerspective->setAutoFillBackground(false);
        pbTransformPerspective->setIcon(icon23);
        pbTransformPerspective->setIconSize(QSize(30, 30));
        pbTransformPerspective->setCheckable(true);
        pbTransformPerspective->setChecked(false);
        pbTransformPerspective->setAutoDefault(false);
        pbTransformPerspective->setFlat(false);

        gridLayout_27->addWidget(pbTransformPerspective, 3, 0, 1, 2);

        label_110 = new QLabel(fCalibStep1);
        label_110->setObjectName(QString::fromUtf8("label_110"));
        sizePolicy.setHeightForWidth(label_110->sizePolicy().hasHeightForWidth());
        label_110->setSizePolicy(sizePolicy);

        gridLayout_27->addWidget(label_110, 1, 0, 1, 1);

        pbFindChessboard = new QPushButton(fCalibStep1);
        pbFindChessboard->setObjectName(QString::fromUtf8("pbFindChessboard"));
        pbFindChessboard->setMinimumSize(QSize(0, 45));
        pbFindChessboard->setIcon(icon22);
        pbFindChessboard->setIconSize(QSize(32, 32));

        gridLayout_27->addWidget(pbFindChessboard, 2, 0, 1, 2);


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
        pbImageMapping = new QPushButton(fCalibStep2);
        pbImageMapping->setObjectName(QString::fromUtf8("pbImageMapping"));
        pbImageMapping->setMinimumSize(QSize(0, 45));
        pbImageMapping->setMaximumSize(QSize(200, 16777215));
        pbImageMapping->setAutoFillBackground(false);
        QIcon icon36;
        icon36.addFile(QString::fromUtf8(":/icon/icons8_grid_3_48px_1.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbImageMapping->setIcon(icon36);
        pbImageMapping->setIconSize(QSize(30, 30));
        pbImageMapping->setCheckable(true);
        pbImageMapping->setChecked(false);
        pbImageMapping->setAutoDefault(false);
        pbImageMapping->setFlat(false);

        gridLayout_26->addWidget(pbImageMapping, 8, 0, 1, 3);

        label_39 = new QLabel(fCalibStep2);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setAlignment(Qt::AlignCenter);

        gridLayout_26->addWidget(label_39, 4, 4, 1, 1);

        leRealityPoint2Y = new QLineEdit(fCalibStep2);
        leRealityPoint2Y->setObjectName(QString::fromUtf8("leRealityPoint2Y"));
        sizePolicy.setHeightForWidth(leRealityPoint2Y->sizePolicy().hasHeightForWidth());
        leRealityPoint2Y->setSizePolicy(sizePolicy);
        leRealityPoint2Y->setMinimumSize(QSize(0, 0));
        leRealityPoint2Y->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint2Y, 6, 4, 1, 1);

        leRealityPoint1Y = new QLineEdit(fCalibStep2);
        leRealityPoint1Y->setObjectName(QString::fromUtf8("leRealityPoint1Y"));
        sizePolicy.setHeightForWidth(leRealityPoint1Y->sizePolicy().hasHeightForWidth());
        leRealityPoint1Y->setSizePolicy(sizePolicy);
        leRealityPoint1Y->setMinimumSize(QSize(0, 0));
        leRealityPoint1Y->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint1Y, 5, 4, 1, 1);

        label_133 = new QLabel(fCalibStep2);
        label_133->setObjectName(QString::fromUtf8("label_133"));
        label_133->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_133, 5, 5, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_26->addItem(horizontalSpacer_12, 1, 6, 1, 1);

        label_140 = new QLabel(fCalibStep2);
        label_140->setObjectName(QString::fromUtf8("label_140"));
        label_140->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_140, 6, 5, 1, 1);

        pbObjectOrigin = new QPushButton(fCalibStep2);
        pbObjectOrigin->setObjectName(QString::fromUtf8("pbObjectOrigin"));
        pbObjectOrigin->setMinimumSize(QSize(0, 0));
        pbObjectOrigin->setMaximumSize(QSize(200, 16777215));
        pbObjectOrigin->setIcon(icon25);

        gridLayout_26->addWidget(pbObjectOrigin, 7, 4, 1, 1);

        label_38 = new QLabel(fCalibStep2);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setMinimumSize(QSize(0, 0));
        QFont font17;
        font17.setBold(false);
        font17.setItalic(false);
        font17.setUnderline(false);
        font17.setStrikeOut(false);
        font17.setKerning(true);
        label_38->setFont(font17);
        label_38->setMouseTracking(true);
        label_38->setTextFormat(Qt::AutoText);
        label_38->setAlignment(Qt::AlignCenter);

        gridLayout_26->addWidget(label_38, 4, 2, 1, 1);

        leRealityPoint1X = new QLineEdit(fCalibStep2);
        leRealityPoint1X->setObjectName(QString::fromUtf8("leRealityPoint1X"));
        sizePolicy.setHeightForWidth(leRealityPoint1X->sizePolicy().hasHeightForWidth());
        leRealityPoint1X->setSizePolicy(sizePolicy);
        leRealityPoint1X->setMinimumSize(QSize(0, 0));
        leRealityPoint1X->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint1X, 5, 2, 1, 1);

        label_132 = new QLabel(fCalibStep2);
        label_132->setObjectName(QString::fromUtf8("label_132"));
        label_132->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_132, 5, 3, 1, 1);

        leRealityPoint2X = new QLineEdit(fCalibStep2);
        leRealityPoint2X->setObjectName(QString::fromUtf8("leRealityPoint2X"));
        sizePolicy.setHeightForWidth(leRealityPoint2X->sizePolicy().hasHeightForWidth());
        leRealityPoint2X->setSizePolicy(sizePolicy);
        leRealityPoint2X->setMinimumSize(QSize(0, 0));
        leRealityPoint2X->setMaximumSize(QSize(100, 16777215));

        gridLayout_26->addWidget(leRealityPoint2X, 6, 2, 1, 1);

        label_139 = new QLabel(fCalibStep2);
        label_139->setObjectName(QString::fromUtf8("label_139"));
        label_139->setMinimumSize(QSize(0, 30));

        gridLayout_26->addWidget(label_139, 6, 3, 1, 1);

        cbMoveOnConveyor1 = new QCheckBox(fCalibStep2);
        cbMoveOnConveyor1->setObjectName(QString::fromUtf8("cbMoveOnConveyor1"));

        gridLayout_26->addWidget(cbMoveOnConveyor1, 1, 0, 1, 3);

        pbCalibPoint1 = new QPushButton(fCalibStep2);
        pbCalibPoint1->setObjectName(QString::fromUtf8("pbCalibPoint1"));
        pbCalibPoint1->setFlat(true);

        gridLayout_26->addWidget(pbCalibPoint1, 5, 1, 1, 1);

        pbCalibPoint2 = new QPushButton(fCalibStep2);
        pbCalibPoint2->setObjectName(QString::fromUtf8("pbCalibPoint2"));
        pbCalibPoint2->setFlat(true);

        gridLayout_26->addWidget(pbCalibPoint2, 6, 1, 1, 1);


        verticalLayout_52->addWidget(fCalibStep2);


        verticalLayout_29->addWidget(fCameraCalibrationFrame);


        verticalLayout_32->addWidget(gbCameraCalibration);

        gbCameraObject = new QGroupBox(fObjectDetectingTool);
        gbCameraObject->setObjectName(QString::fromUtf8("gbCameraObject"));
        gbCameraObject->setFont(font7);
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

        cbObjectType = new QComboBox(fVisionObjectFrame);
        cbObjectType->addItem(QString());
        cbObjectType->setObjectName(QString::fromUtf8("cbObjectType"));
        cbObjectType->setEnabled(true);
        cbObjectType->setMinimumSize(QSize(0, 30));

        horizontalLayout_29->addWidget(cbObjectType);

        pushButton = new QPushButton(fVisionObjectFrame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_29->addWidget(pushButton);

        pushButton_2 = new QPushButton(fVisionObjectFrame);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        pushButton_2->setMaximumSize(QSize(30, 30));

        horizontalLayout_29->addWidget(pushButton_2);


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
        label_172 = new QLabel(fBlobPanel);
        label_172->setObjectName(QString::fromUtf8("label_172"));
        label_172->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_172, 2, 4, 1, 1);

        leMaxWRec = new QLineEdit(fBlobPanel);
        leMaxWRec->setObjectName(QString::fromUtf8("leMaxWRec"));
        sizePolicy1.setHeightForWidth(leMaxWRec->sizePolicy().hasHeightForWidth());
        leMaxWRec->setSizePolicy(sizePolicy1);
        leMaxWRec->setMinimumSize(QSize(0, 20));
        leMaxWRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMaxWRec, 2, 7, 1, 1);

        leMaxLRec = new QLineEdit(fBlobPanel);
        leMaxLRec->setObjectName(QString::fromUtf8("leMaxLRec"));
        sizePolicy1.setHeightForWidth(leMaxLRec->sizePolicy().hasHeightForWidth());
        leMaxLRec->setSizePolicy(sizePolicy1);
        leMaxLRec->setMinimumSize(QSize(0, 20));
        leMaxLRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMaxLRec, 3, 7, 1, 1);

        label_55 = new QLabel(fBlobPanel);
        label_55->setObjectName(QString::fromUtf8("label_55"));

        gridLayout_14->addWidget(label_55, 3, 2, 1, 1);

        leWRec = new QLineEdit(fBlobPanel);
        leWRec->setObjectName(QString::fromUtf8("leWRec"));
        sizePolicy1.setHeightForWidth(leWRec->sizePolicy().hasHeightForWidth());
        leWRec->setSizePolicy(sizePolicy1);
        leWRec->setMinimumSize(QSize(0, 30));
        leWRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leWRec, 2, 1, 1, 1);

        pbObjectRect = new QToolButton(fBlobPanel);
        pbObjectRect->setObjectName(QString::fromUtf8("pbObjectRect"));
        pbObjectRect->setMinimumSize(QSize(0, 30));
        pbObjectRect->setStyleSheet(QString::fromUtf8(""));
        pbObjectRect->setIcon(icon27);
        pbObjectRect->setIconSize(QSize(30, 30));
        pbObjectRect->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        pbObjectRect->setAutoRaise(true);

        gridLayout_14->addWidget(pbObjectRect, 5, 1, 1, 2);

        label_56 = new QLabel(fBlobPanel);
        label_56->setObjectName(QString::fromUtf8("label_56"));

        gridLayout_14->addWidget(label_56, 4, 2, 1, 1);

        label_44 = new QLabel(fBlobPanel);
        label_44->setObjectName(QString::fromUtf8("label_44"));

        gridLayout_14->addWidget(label_44, 4, 0, 1, 1);

        leMinLRec = new QLineEdit(fBlobPanel);
        leMinLRec->setObjectName(QString::fromUtf8("leMinLRec"));
        sizePolicy1.setHeightForWidth(leMinLRec->sizePolicy().hasHeightForWidth());
        leMinLRec->setSizePolicy(sizePolicy1);
        leMinLRec->setMinimumSize(QSize(0, 20));
        leMinLRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMinLRec, 3, 5, 1, 1);

        leLRec = new QLineEdit(fBlobPanel);
        leLRec->setObjectName(QString::fromUtf8("leLRec"));
        sizePolicy1.setHeightForWidth(leLRec->sizePolicy().hasHeightForWidth());
        leLRec->setSizePolicy(sizePolicy1);
        leLRec->setMinimumSize(QSize(0, 30));
        leLRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leLRec, 3, 1, 1, 1);

        pbFilter = new QPushButton(fBlobPanel);
        pbFilter->setObjectName(QString::fromUtf8("pbFilter"));
        pbFilter->setMinimumSize(QSize(0, 30));
        pbFilter->setMaximumSize(QSize(150, 16777215));
        pbFilter->setIcon(icon28);

        gridLayout_14->addWidget(pbFilter, 0, 0, 1, 2);

        label_43 = new QLabel(fBlobPanel);
        label_43->setObjectName(QString::fromUtf8("label_43"));

        gridLayout_14->addWidget(label_43, 3, 0, 1, 1);

        label_173 = new QLabel(fBlobPanel);
        label_173->setObjectName(QString::fromUtf8("label_173"));
        label_173->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_173, 2, 6, 1, 1);

        leHRec = new QLineEdit(fBlobPanel);
        leHRec->setObjectName(QString::fromUtf8("leHRec"));
        sizePolicy1.setHeightForWidth(leHRec->sizePolicy().hasHeightForWidth());
        leHRec->setSizePolicy(sizePolicy1);
        leHRec->setMinimumSize(QSize(0, 30));
        leHRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leHRec, 4, 1, 1, 1);

        horizontalSpacer_66 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_14->addItem(horizontalSpacer_66, 2, 8, 1, 1);

        label_54 = new QLabel(fBlobPanel);
        label_54->setObjectName(QString::fromUtf8("label_54"));

        gridLayout_14->addWidget(label_54, 2, 2, 1, 1);

        label_174 = new QLabel(fBlobPanel);
        label_174->setObjectName(QString::fromUtf8("label_174"));
        label_174->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_174, 3, 4, 1, 1);

        label_42 = new QLabel(fBlobPanel);
        label_42->setObjectName(QString::fromUtf8("label_42"));

        gridLayout_14->addWidget(label_42, 2, 0, 1, 1);

        leMinWRec = new QLineEdit(fBlobPanel);
        leMinWRec->setObjectName(QString::fromUtf8("leMinWRec"));
        sizePolicy1.setHeightForWidth(leMinWRec->sizePolicy().hasHeightForWidth());
        leMinWRec->setSizePolicy(sizePolicy1);
        leMinWRec->setMinimumSize(QSize(0, 20));
        leMinWRec->setMaximumSize(QSize(50, 16777215));

        gridLayout_14->addWidget(leMinWRec, 2, 5, 1, 1);

        lbTrackingObject = new QLabel(fBlobPanel);
        lbTrackingObject->setObjectName(QString::fromUtf8("lbTrackingObject"));
        lbTrackingObject->setMinimumSize(QSize(100, 100));
        lbTrackingObject->setMaximumSize(QSize(100, 100));
        lbTrackingObject->setStyleSheet(QString::fromUtf8("background-color:rgb(230, 230, 230)"));
        lbTrackingObject->setMargin(0);

        gridLayout_14->addWidget(lbTrackingObject, 5, 0, 1, 1);

        label_175 = new QLabel(fBlobPanel);
        label_175->setObjectName(QString::fromUtf8("label_175"));
        label_175->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_14->addWidget(label_175, 3, 6, 1, 1);


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
        sizePolicy1.setHeightForWidth(pbRunExternalScript->sizePolicy().hasHeightForWidth());
        pbRunExternalScript->setSizePolicy(sizePolicy1);
        pbRunExternalScript->setMaximumSize(QSize(30, 16777215));
        QIcon icon37;
        icon37.addFile(QString::fromUtf8(":/icon/icons8_play_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon37.addFile(QString::fromUtf8(":/icon/Pause_96px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbRunExternalScript->setIcon(icon37);
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
        sizePolicy1.setHeightForWidth(pbExternalScriptOpen->sizePolicy().hasHeightForWidth());
        pbExternalScriptOpen->setSizePolicy(sizePolicy1);
        pbExternalScriptOpen->setMaximumSize(QSize(30, 16777215));
        pbExternalScriptOpen->setIcon(icon20);

        gridLayout_28->addWidget(pbExternalScriptOpen, 0, 2, 1, 1);

        label_184 = new QLabel(fExternalScriptPanel);
        label_184->setObjectName(QString::fromUtf8("label_184"));

        gridLayout_28->addWidget(label_184, 3, 0, 1, 1);

        label_145 = new QLabel(fExternalScriptPanel);
        label_145->setObjectName(QString::fromUtf8("label_145"));

        gridLayout_28->addWidget(label_145, 0, 0, 1, 1);

        pbExternalScriptHelp = new QPushButton(fExternalScriptPanel);
        pbExternalScriptHelp->setObjectName(QString::fromUtf8("pbExternalScriptHelp"));
        sizePolicy1.setHeightForWidth(pbExternalScriptHelp->sizePolicy().hasHeightForWidth());
        pbExternalScriptHelp->setSizePolicy(sizePolicy1);
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

        pushButton_3 = new QPushButton(fExternalScriptPanel);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout_28->addWidget(pushButton_3, 5, 0, 1, 1);


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
        sizePolicy1.setHeightForWidth(leCenterThreshold->sizePolicy().hasHeightForWidth());
        leCenterThreshold->setSizePolicy(sizePolicy1);
        leCenterThreshold->setMinimumSize(QSize(0, 30));
        leCenterThreshold->setMaximumSize(QSize(50, 16777215));

        gridLayout_29->addWidget(leCenterThreshold, 3, 1, 1, 2);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_29->addItem(horizontalSpacer_8, 2, 4, 1, 1);

        leEdgeThreshold = new QLineEdit(fCirclePanel);
        leEdgeThreshold->setObjectName(QString::fromUtf8("leEdgeThreshold"));
        sizePolicy1.setHeightForWidth(leEdgeThreshold->sizePolicy().hasHeightForWidth());
        leEdgeThreshold->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(leMaxRadius->sizePolicy().hasHeightForWidth());
        leMaxRadius->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(leMinRadius->sizePolicy().hasHeightForWidth());
        leMinRadius->setSizePolicy(sizePolicy1);
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
        gbCameraVariable->setFont(font7);
        gbCameraVariable->setStyleSheet(QString::fromUtf8(""));
        gbCameraVariable->setFlat(false);
        gbCameraVariable->setCheckable(true);
        verticalLayout_34 = new QVBoxLayout(gbCameraVariable);
        verticalLayout_34->setSpacing(6);
        verticalLayout_34->setContentsMargins(11, 11, 11, 11);
        verticalLayout_34->setObjectName(QString::fromUtf8("verticalLayout_34"));
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
        pbViewDataObjects->setIcon(icon29);

        horizontalLayout_25->addWidget(pbViewDataObjects);

        pbClearDetectObjects = new QPushButton(fVisionVariableFrame);
        pbClearDetectObjects->setObjectName(QString::fromUtf8("pbClearDetectObjects"));
        pbClearDetectObjects->setMinimumSize(QSize(150, 30));
        pbClearDetectObjects->setMaximumSize(QSize(200, 16777215));
        pbClearDetectObjects->setIcon(icon30);

        horizontalLayout_25->addWidget(pbClearDetectObjects);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_9);


        verticalLayout_35->addLayout(horizontalLayout_25);

        gridLayout_15 = new QGridLayout();
        gridLayout_15->setSpacing(6);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        label_50 = new QLabel(fVisionVariableFrame);
        label_50->setObjectName(QString::fromUtf8("label_50"));
        label_50->setFont(font9);

        gridLayout_15->addWidget(label_50, 2, 0, 1, 1);

        lbVisibleObjectNumber = new QLabel(fVisionVariableFrame);
        lbVisibleObjectNumber->setObjectName(QString::fromUtf8("lbVisibleObjectNumber"));
        lbVisibleObjectNumber->setFont(font9);

        gridLayout_15->addWidget(lbVisibleObjectNumber, 2, 1, 1, 1);

        lbTrackingObjectNumber = new QLabel(fVisionVariableFrame);
        lbTrackingObjectNumber->setObjectName(QString::fromUtf8("lbTrackingObjectNumber"));
        lbTrackingObjectNumber->setFont(font9);

        gridLayout_15->addWidget(lbTrackingObjectNumber, 1, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_7, 1, 2, 1, 1);

        label_48 = new QLabel(fVisionVariableFrame);
        label_48->setObjectName(QString::fromUtf8("label_48"));
        label_48->setFont(font9);

        gridLayout_15->addWidget(label_48, 1, 0, 1, 1);


        verticalLayout_35->addLayout(gridLayout_15);

        frame_9 = new QFrame(fVisionVariableFrame);
        frame_9->setObjectName(QString::fromUtf8("frame_9"));
        frame_9->setMinimumSize(QSize(0, 50));
        frame_9->setFrameShape(QFrame::StyledPanel);
        frame_9->setFrameShadow(QFrame::Raised);
        label_155 = new QLabel(frame_9);
        label_155->setObjectName(QString::fromUtf8("label_155"));
        label_155->setGeometry(QRect(0, 0, 50, 50));
        label_155->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_156 = new QLabel(frame_9);
        label_156->setObjectName(QString::fromUtf8("label_156"));
        label_156->setGeometry(QRect(55, 0, 50, 50));
        label_156->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_157 = new QLabel(frame_9);
        label_157->setObjectName(QString::fromUtf8("label_157"));
        label_157->setGeometry(QRect(110, 0, 50, 50));
        label_157->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_158 = new QLabel(frame_9);
        label_158->setObjectName(QString::fromUtf8("label_158"));
        label_158->setGeometry(QRect(165, 0, 50, 50));
        label_158->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_159 = new QLabel(frame_9);
        label_159->setObjectName(QString::fromUtf8("label_159"));
        label_159->setGeometry(QRect(220, 0, 50, 50));
        label_159->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));

        verticalLayout_35->addWidget(frame_9);


        verticalLayout_34->addWidget(fVisionVariableFrame);


        verticalLayout_32->addWidget(gbCameraVariable);

        gbConveyorForTracking = new QGroupBox(fObjectDetectingTool);
        gbConveyorForTracking->setObjectName(QString::fromUtf8("gbConveyorForTracking"));
        gbConveyorForTracking->setFont(font7);
        gbConveyorForTracking->setCheckable(true);
        verticalLayout_41 = new QVBoxLayout(gbConveyorForTracking);
        verticalLayout_41->setSpacing(6);
        verticalLayout_41->setContentsMargins(11, 11, 11, 11);
        verticalLayout_41->setObjectName(QString::fromUtf8("verticalLayout_41"));
        fTracking = new QFrame(gbConveyorForTracking);
        fTracking->setObjectName(QString::fromUtf8("fTracking"));
        fTracking->setMinimumSize(QSize(0, 200));
        fTracking->setFrameShape(QFrame::StyledPanel);
        fTracking->setFrameShadow(QFrame::Raised);
        verticalLayout_33 = new QVBoxLayout(fTracking);
        verticalLayout_33->setSpacing(5);
        verticalLayout_33->setContentsMargins(11, 11, 11, 11);
        verticalLayout_33->setObjectName(QString::fromUtf8("verticalLayout_33"));
        verticalLayout_33->setContentsMargins(0, 0, 0, 0);
        label_150 = new QLabel(fTracking);
        label_150->setObjectName(QString::fromUtf8("label_150"));
        label_150->setFont(font7);

        verticalLayout_33->addWidget(label_150);

        gridFrame = new QFrame(fTracking);
        gridFrame->setObjectName(QString::fromUtf8("gridFrame"));
        gridFrame->setMinimumSize(QSize(0, 0));
        gridLayout_32 = new QGridLayout(gridFrame);
        gridLayout_32->setSpacing(6);
        gridLayout_32->setContentsMargins(11, 11, 11, 11);
        gridLayout_32->setObjectName(QString::fromUtf8("gridLayout_32"));
        horizontalSpacer_62 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_32->addItem(horizontalSpacer_62, 0, 3, 1, 1);

        label_152 = new QLabel(gridFrame);
        label_152->setObjectName(QString::fromUtf8("label_152"));
        label_152->setMaximumSize(QSize(60, 16777215));
        QFont font18;
        font18.setPointSize(8);
        font18.setBold(false);
        font18.setItalic(true);
        font18.setKerning(true);
        label_152->setFont(font18);

        gridLayout_32->addWidget(label_152, 0, 2, 1, 1);

        label_151 = new QLabel(gridFrame);
        label_151->setObjectName(QString::fromUtf8("label_151"));

        gridLayout_32->addWidget(label_151, 0, 0, 1, 1);

        leTrackingError = new QLineEdit(gridFrame);
        leTrackingError->setObjectName(QString::fromUtf8("leTrackingError"));
        leTrackingError->setMaximumSize(QSize(100, 16777215));

        gridLayout_32->addWidget(leTrackingError, 0, 1, 1, 1);


        verticalLayout_33->addWidget(gridFrame);

        label_127 = new QLabel(fTracking);
        label_127->setObjectName(QString::fromUtf8("label_127"));
        label_127->setFont(font7);

        verticalLayout_33->addWidget(label_127);

        gridLayout_16 = new QGridLayout();
        gridLayout_16->setSpacing(6);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        leConvenyorSpeed = new QLineEdit(fTracking);
        leConvenyorSpeed->setObjectName(QString::fromUtf8("leConvenyorSpeed"));
        leConvenyorSpeed->setMinimumSize(QSize(0, 0));
        leConvenyorSpeed->setMaximumSize(QSize(100, 16777215));

        gridLayout_16->addWidget(leConvenyorSpeed, 6, 1, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_16->addItem(horizontalSpacer_11, 6, 4, 1, 1);

        pbReadProximitySensor = new QPushButton(fTracking);
        pbReadProximitySensor->setObjectName(QString::fromUtf8("pbReadProximitySensor"));
        sizePolicy.setHeightForWidth(pbReadProximitySensor->sizePolicy().hasHeightForWidth());
        pbReadProximitySensor->setSizePolicy(sizePolicy);
        pbReadProximitySensor->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_16->addWidget(pbReadProximitySensor, 17, 4, 1, 1);

        pbBackwardConveyor = new QPushButton(fTracking);
        pbBackwardConveyor->setObjectName(QString::fromUtf8("pbBackwardConveyor"));
        sizePolicy.setHeightForWidth(pbBackwardConveyor->sizePolicy().hasHeightForWidth());
        pbBackwardConveyor->setSizePolicy(sizePolicy);
        pbBackwardConveyor->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_16->addWidget(pbBackwardConveyor, 14, 0, 1, 1);

        leMovingDistanceConveyorControl = new QLineEdit(fTracking);
        leMovingDistanceConveyorControl->setObjectName(QString::fromUtf8("leMovingDistanceConveyorControl"));
        leMovingDistanceConveyorControl->setMaximumSize(QSize(100, 16777215));

        gridLayout_16->addWidget(leMovingDistanceConveyorControl, 11, 1, 1, 1);

        pbResetEncoderPosition = new QPushButton(fTracking);
        pbResetEncoderPosition->setObjectName(QString::fromUtf8("pbResetEncoderPosition"));
        sizePolicy.setHeightForWidth(pbResetEncoderPosition->sizePolicy().hasHeightForWidth());
        pbResetEncoderPosition->setSizePolicy(sizePolicy);
        pbResetEncoderPosition->setMaximumSize(QSize(50, 16777215));

        gridLayout_16->addWidget(pbResetEncoderPosition, 4, 4, 1, 1);

        label_189 = new QLabel(fTracking);
        label_189->setObjectName(QString::fromUtf8("label_189"));
        label_189->setFont(font5);

        gridLayout_16->addWidget(label_189, 16, 0, 1, 1);

        leForwardConveyorGcode = new QLineEdit(fTracking);
        leForwardConveyorGcode->setObjectName(QString::fromUtf8("leForwardConveyorGcode"));
        leForwardConveyorGcode->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_16->addWidget(leForwardConveyorGcode, 13, 1, 1, 2);

        leTurnOffConveyorGcode = new QLineEdit(fTracking);
        leTurnOffConveyorGcode->setObjectName(QString::fromUtf8("leTurnOffConveyorGcode"));
        leTurnOffConveyorGcode->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_16->addWidget(leTurnOffConveyorGcode, 15, 1, 1, 2);

        rbEncoderEnable = new QRadioButton(fTracking);
        rbEncoderEnable->setObjectName(QString::fromUtf8("rbEncoderEnable"));

        gridLayout_16->addWidget(rbEncoderEnable, 2, 1, 1, 1);

        label_148 = new QLabel(fTracking);
        label_148->setObjectName(QString::fromUtf8("label_148"));
        QFont font19;
        font19.setPointSize(8);
        font19.setBold(true);
        font19.setKerning(true);
        label_148->setFont(font19);

        gridLayout_16->addWidget(label_148, 8, 0, 1, 1);

        label_191 = new QLabel(fTracking);
        label_191->setObjectName(QString::fromUtf8("label_191"));
        label_191->setFont(font9);

        gridLayout_16->addWidget(label_191, 17, 0, 1, 1);

        leBackwardConveyorGcode = new QLineEdit(fTracking);
        leBackwardConveyorGcode->setObjectName(QString::fromUtf8("leBackwardConveyorGcode"));
        leBackwardConveyorGcode->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_16->addWidget(leBackwardConveyorGcode, 14, 1, 1, 2);

        label_45 = new QLabel(fTracking);
        label_45->setObjectName(QString::fromUtf8("label_45"));
        label_45->setMinimumSize(QSize(100, 0));
        label_45->setMaximumSize(QSize(150, 16777215));
        label_45->setFont(font9);

        gridLayout_16->addWidget(label_45, 6, 0, 1, 1);

        label_163 = new QLabel(fTracking);
        label_163->setObjectName(QString::fromUtf8("label_163"));
        label_163->setFont(font9);

        gridLayout_16->addWidget(label_163, 12, 1, 1, 1);

        lbProximitySensorValue = new QLabel(fTracking);
        lbProximitySensorValue->setObjectName(QString::fromUtf8("lbProximitySensorValue"));
        lbProximitySensorValue->setFont(font9);

        gridLayout_16->addWidget(lbProximitySensorValue, 17, 1, 1, 1);

        leEncoderCom = new QLabel(fTracking);
        leEncoderCom->setObjectName(QString::fromUtf8("leEncoderCom"));

        gridLayout_16->addWidget(leEncoderCom, 3, 1, 1, 1);

        pbTurnOffConveyor = new QPushButton(fTracking);
        pbTurnOffConveyor->setObjectName(QString::fromUtf8("pbTurnOffConveyor"));
        sizePolicy.setHeightForWidth(pbTurnOffConveyor->sizePolicy().hasHeightForWidth());
        pbTurnOffConveyor->setSizePolicy(sizePolicy);
        pbTurnOffConveyor->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_16->addWidget(pbTurnOffConveyor, 15, 0, 1, 1);

        label_121 = new QLabel(fTracking);
        label_121->setObjectName(QString::fromUtf8("label_121"));
        label_121->setMaximumSize(QSize(60, 16777215));
        label_121->setFont(font18);

        gridLayout_16->addWidget(label_121, 5, 2, 1, 1);

        label_162 = new QLabel(fTracking);
        label_162->setObjectName(QString::fromUtf8("label_162"));
        label_162->setMaximumSize(QSize(60, 16777215));
        label_162->setFont(font18);

        gridLayout_16->addWidget(label_162, 11, 2, 1, 1);

        leEncoderVelocity = new QLineEdit(fTracking);
        leEncoderVelocity->setObjectName(QString::fromUtf8("leEncoderVelocity"));
        leEncoderVelocity->setMaximumSize(QSize(100, 16777215));

        gridLayout_16->addWidget(leEncoderVelocity, 5, 1, 1, 1);

        leConveyorDeviationAngle = new QLineEdit(fTracking);
        leConveyorDeviationAngle->setObjectName(QString::fromUtf8("leConveyorDeviationAngle"));
        leConveyorDeviationAngle->setMinimumSize(QSize(0, 0));
        leConveyorDeviationAngle->setMaximumSize(QSize(100, 16777215));

        gridLayout_16->addWidget(leConveyorDeviationAngle, 8, 1, 1, 1);

        pbConnectEncdoer = new QPushButton(fTracking);
        pbConnectEncdoer->setObjectName(QString::fromUtf8("pbConnectEncdoer"));

        gridLayout_16->addWidget(pbConnectEncdoer, 3, 0, 1, 1);

        label_161 = new QLabel(fTracking);
        label_161->setObjectName(QString::fromUtf8("label_161"));
        label_161->setFont(font9);

        gridLayout_16->addWidget(label_161, 11, 0, 1, 1);

        cbEncoderPositionInverse = new QCheckBox(fTracking);
        cbEncoderPositionInverse->setObjectName(QString::fromUtf8("cbEncoderPositionInverse"));

        gridLayout_16->addWidget(cbEncoderPositionInverse, 4, 3, 1, 1);

        label_49 = new QLabel(fTracking);
        label_49->setObjectName(QString::fromUtf8("label_49"));
        label_49->setMaximumSize(QSize(60, 16777215));
        label_49->setFont(font18);

        gridLayout_16->addWidget(label_49, 6, 2, 1, 1);

        label_160 = new QLabel(fTracking);
        label_160->setObjectName(QString::fromUtf8("label_160"));
        label_160->setFont(font5);

        gridLayout_16->addWidget(label_160, 10, 0, 1, 1);

        label_119 = new QLabel(fTracking);
        label_119->setObjectName(QString::fromUtf8("label_119"));
        label_119->setMaximumSize(QSize(60, 16777215));
        label_119->setFont(font18);

        gridLayout_16->addWidget(label_119, 4, 2, 1, 1);

        rbVirtualEncoderEnable = new QRadioButton(fTracking);
        rbVirtualEncoderEnable->setObjectName(QString::fromUtf8("rbVirtualEncoderEnable"));
        rbVirtualEncoderEnable->setChecked(true);

        gridLayout_16->addWidget(rbVirtualEncoderEnable, 2, 3, 1, 2);

        label_118 = new QLabel(fTracking);
        label_118->setObjectName(QString::fromUtf8("label_118"));

        gridLayout_16->addWidget(label_118, 4, 0, 1, 1);

        pbForwardConveyor = new QPushButton(fTracking);
        pbForwardConveyor->setObjectName(QString::fromUtf8("pbForwardConveyor"));
        sizePolicy.setHeightForWidth(pbForwardConveyor->sizePolicy().hasHeightForWidth());
        pbForwardConveyor->setSizePolicy(sizePolicy);
        pbForwardConveyor->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_16->addWidget(pbForwardConveyor, 13, 0, 1, 1);

        cbConveyorDirectionControl = new QComboBox(fTracking);
        cbConveyorDirectionControl->addItem(QString());
        cbConveyorDirectionControl->addItem(QString());
        cbConveyorDirectionControl->setObjectName(QString::fromUtf8("cbConveyorDirectionControl"));
        cbConveyorDirectionControl->setMinimumSize(QSize(0, 0));
        cbConveyorDirectionControl->setMaximumSize(QSize(100, 16777215));

        gridLayout_16->addWidget(cbConveyorDirectionControl, 11, 3, 1, 1);

        label_120 = new QLabel(fTracking);
        label_120->setObjectName(QString::fromUtf8("label_120"));

        gridLayout_16->addWidget(label_120, 5, 0, 1, 1);

        cbAutoReadProximitySensor = new QCheckBox(fTracking);
        cbAutoReadProximitySensor->setObjectName(QString::fromUtf8("cbAutoReadProximitySensor"));

        gridLayout_16->addWidget(cbAutoReadProximitySensor, 17, 3, 1, 1);

        leEncoderPosition = new QLineEdit(fTracking);
        leEncoderPosition->setObjectName(QString::fromUtf8("leEncoderPosition"));
        leEncoderPosition->setMaximumSize(QSize(100, 16777215));

        gridLayout_16->addWidget(leEncoderPosition, 4, 1, 1, 1);

        frame_11 = new QFrame(fTracking);
        frame_11->setObjectName(QString::fromUtf8("frame_11"));
        frame_11->setMinimumSize(QSize(0, 20));
        frame_11->setFrameShape(QFrame::StyledPanel);
        frame_11->setFrameShadow(QFrame::Raised);
        gridLayout_37 = new QGridLayout(frame_11);
        gridLayout_37->setSpacing(6);
        gridLayout_37->setContentsMargins(11, 11, 11, 11);
        gridLayout_37->setObjectName(QString::fromUtf8("gridLayout_37"));
        gridLayout_37->setHorizontalSpacing(0);
        gridLayout_37->setVerticalSpacing(5);
        gridLayout_37->setContentsMargins(0, 0, 0, 0);
        label_170 = new QLabel(frame_11);
        label_170->setObjectName(QString::fromUtf8("label_170"));
        label_170->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_37->addWidget(label_170, 0, 2, 1, 1);

        leConveyorPoint2X = new QLineEdit(frame_11);
        leConveyorPoint2X->setObjectName(QString::fromUtf8("leConveyorPoint2X"));
        QSizePolicy sizePolicy10(QSizePolicy::Ignored, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(leConveyorPoint2X->sizePolicy().hasHeightForWidth());
        leConveyorPoint2X->setSizePolicy(sizePolicy10);
        leConveyorPoint2X->setMinimumSize(QSize(0, 0));

        gridLayout_37->addWidget(leConveyorPoint2X, 2, 1, 1, 1);

        pbCalibConveyorAngle = new QPushButton(frame_11);
        pbCalibConveyorAngle->setObjectName(QString::fromUtf8("pbCalibConveyorAngle"));
        sizePolicy10.setHeightForWidth(pbCalibConveyorAngle->sizePolicy().hasHeightForWidth());
        pbCalibConveyorAngle->setSizePolicy(sizePolicy10);
        pbCalibConveyorAngle->setMinimumSize(QSize(0, 0));
        pbCalibConveyorAngle->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_37->addWidget(pbCalibConveyorAngle, 4, 1, 1, 1);

        leConveyorPoint1X = new QLineEdit(frame_11);
        leConveyorPoint1X->setObjectName(QString::fromUtf8("leConveyorPoint1X"));
        sizePolicy10.setHeightForWidth(leConveyorPoint1X->sizePolicy().hasHeightForWidth());
        leConveyorPoint1X->setSizePolicy(sizePolicy10);
        leConveyorPoint1X->setMinimumSize(QSize(0, 0));

        gridLayout_37->addWidget(leConveyorPoint1X, 0, 1, 1, 1);

        label_197 = new QLabel(frame_11);
        label_197->setObjectName(QString::fromUtf8("label_197"));
        label_197->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_37->addWidget(label_197, 1, 2, 1, 1);

        label_199 = new QLabel(frame_11);
        label_199->setObjectName(QString::fromUtf8("label_199"));
        label_199->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_37->addWidget(label_199, 3, 2, 1, 1);

        leConveyorPoint1Y = new QLineEdit(frame_11);
        leConveyorPoint1Y->setObjectName(QString::fromUtf8("leConveyorPoint1Y"));
        sizePolicy10.setHeightForWidth(leConveyorPoint1Y->sizePolicy().hasHeightForWidth());
        leConveyorPoint1Y->setSizePolicy(sizePolicy10);
        leConveyorPoint1Y->setMinimumSize(QSize(0, 0));

        gridLayout_37->addWidget(leConveyorPoint1Y, 1, 1, 1, 1);

        label_198 = new QLabel(frame_11);
        label_198->setObjectName(QString::fromUtf8("label_198"));
        label_198->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_37->addWidget(label_198, 2, 2, 1, 1);

        leConveyorPoint2Y = new QLineEdit(frame_11);
        leConveyorPoint2Y->setObjectName(QString::fromUtf8("leConveyorPoint2Y"));
        sizePolicy10.setHeightForWidth(leConveyorPoint2Y->sizePolicy().hasHeightForWidth());
        leConveyorPoint2Y->setSizePolicy(sizePolicy10);
        leConveyorPoint2Y->setMinimumSize(QSize(0, 0));

        gridLayout_37->addWidget(leConveyorPoint2Y, 3, 1, 1, 1);

        pbGetConveyorPoint1X = new QPushButton(frame_11);
        pbGetConveyorPoint1X->setObjectName(QString::fromUtf8("pbGetConveyorPoint1X"));
        sizePolicy1.setHeightForWidth(pbGetConveyorPoint1X->sizePolicy().hasHeightForWidth());
        pbGetConveyorPoint1X->setSizePolicy(sizePolicy1);
        pbGetConveyorPoint1X->setMaximumSize(QSize(50, 16777215));
        pbGetConveyorPoint1X->setFlat(true);

        gridLayout_37->addWidget(pbGetConveyorPoint1X, 0, 0, 1, 1);

        pbGetConveyorPoint1Y = new QPushButton(frame_11);
        pbGetConveyorPoint1Y->setObjectName(QString::fromUtf8("pbGetConveyorPoint1Y"));
        sizePolicy1.setHeightForWidth(pbGetConveyorPoint1Y->sizePolicy().hasHeightForWidth());
        pbGetConveyorPoint1Y->setSizePolicy(sizePolicy1);
        pbGetConveyorPoint1Y->setMaximumSize(QSize(50, 16777215));
        pbGetConveyorPoint1Y->setFlat(true);

        gridLayout_37->addWidget(pbGetConveyorPoint1Y, 1, 0, 1, 1);

        pbGetConveyorPoint2X = new QPushButton(frame_11);
        pbGetConveyorPoint2X->setObjectName(QString::fromUtf8("pbGetConveyorPoint2X"));
        sizePolicy1.setHeightForWidth(pbGetConveyorPoint2X->sizePolicy().hasHeightForWidth());
        pbGetConveyorPoint2X->setSizePolicy(sizePolicy1);
        pbGetConveyorPoint2X->setMaximumSize(QSize(50, 16777215));
        pbGetConveyorPoint2X->setFlat(true);

        gridLayout_37->addWidget(pbGetConveyorPoint2X, 2, 0, 1, 1);

        pbGetConveyorPoint2Y = new QPushButton(frame_11);
        pbGetConveyorPoint2Y->setObjectName(QString::fromUtf8("pbGetConveyorPoint2Y"));
        sizePolicy1.setHeightForWidth(pbGetConveyorPoint2Y->sizePolicy().hasHeightForWidth());
        pbGetConveyorPoint2Y->setSizePolicy(sizePolicy1);
        pbGetConveyorPoint2Y->setMaximumSize(QSize(50, 16777215));
        pbGetConveyorPoint2Y->setFlat(true);

        gridLayout_37->addWidget(pbGetConveyorPoint2Y, 3, 0, 1, 1);


        gridLayout_16->addWidget(frame_11, 8, 4, 1, 1);

        label_196 = new QLabel(fTracking);
        label_196->setObjectName(QString::fromUtf8("label_196"));
        label_196->setFont(font9);

        gridLayout_16->addWidget(label_196, 8, 3, 1, 1);

        label_149 = new QLabel(fTracking);
        label_149->setObjectName(QString::fromUtf8("label_149"));
        label_149->setMaximumSize(QSize(60, 16777215));
        label_149->setFont(font18);

        gridLayout_16->addWidget(label_149, 8, 2, 1, 1);

        frame_12 = new QFrame(fTracking);
        frame_12->setObjectName(QString::fromUtf8("frame_12"));
        frame_12->setMinimumSize(QSize(0, 20));
        frame_12->setFrameShape(QFrame::StyledPanel);
        frame_12->setFrameShadow(QFrame::Raised);
        gridLayout_38 = new QGridLayout(frame_12);
        gridLayout_38->setSpacing(6);
        gridLayout_38->setContentsMargins(11, 11, 11, 11);
        gridLayout_38->setObjectName(QString::fromUtf8("gridLayout_38"));
        gridLayout_38->setHorizontalSpacing(0);
        gridLayout_38->setVerticalSpacing(5);
        gridLayout_38->setContentsMargins(0, 0, 0, 0);
        leConveyorPoint3X = new QLineEdit(frame_12);
        leConveyorPoint3X->setObjectName(QString::fromUtf8("leConveyorPoint3X"));
        sizePolicy10.setHeightForWidth(leConveyorPoint3X->sizePolicy().hasHeightForWidth());
        leConveyorPoint3X->setSizePolicy(sizePolicy10);
        leConveyorPoint3X->setMinimumSize(QSize(0, 0));

        gridLayout_38->addWidget(leConveyorPoint3X, 0, 1, 1, 1);

        leConveyorPoint3Y = new QLineEdit(frame_12);
        leConveyorPoint3Y->setObjectName(QString::fromUtf8("leConveyorPoint3Y"));
        sizePolicy10.setHeightForWidth(leConveyorPoint3Y->sizePolicy().hasHeightForWidth());
        leConveyorPoint3Y->setSizePolicy(sizePolicy10);
        leConveyorPoint3Y->setMinimumSize(QSize(0, 0));

        gridLayout_38->addWidget(leConveyorPoint3Y, 1, 1, 1, 1);

        label_169 = new QLabel(frame_12);
        label_169->setObjectName(QString::fromUtf8("label_169"));
        label_169->setMaximumSize(QSize(20, 16777215));

        gridLayout_38->addWidget(label_169, 1, 0, 1, 1);

        label_168 = new QLabel(frame_12);
        label_168->setObjectName(QString::fromUtf8("label_168"));
        label_168->setMaximumSize(QSize(20, 16777215));

        gridLayout_38->addWidget(label_168, 0, 0, 1, 1);

        label_171 = new QLabel(frame_12);
        label_171->setObjectName(QString::fromUtf8("label_171"));
        label_171->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_38->addWidget(label_171, 0, 2, 1, 1);


        gridLayout_16->addWidget(frame_12, 9, 4, 1, 1);

        label_167 = new QLabel(fTracking);
        label_167->setObjectName(QString::fromUtf8("label_167"));
        label_167->setFont(font9);

        gridLayout_16->addWidget(label_167, 9, 3, 1, 1);


        verticalLayout_33->addLayout(gridLayout_16);


        verticalLayout_41->addWidget(fTracking);

        fVisionConveyorFrame = new QFrame(gbConveyorForTracking);
        fVisionConveyorFrame->setObjectName(QString::fromUtf8("fVisionConveyorFrame"));
        fVisionConveyorFrame->setMinimumSize(QSize(0, 0));
        fVisionConveyorFrame->setFrameShape(QFrame::StyledPanel);
        fVisionConveyorFrame->setFrameShadow(QFrame::Raised);
        verticalLayout_49 = new QVBoxLayout(fVisionConveyorFrame);
        verticalLayout_49->setSpacing(6);
        verticalLayout_49->setContentsMargins(11, 11, 11, 11);
        verticalLayout_49->setObjectName(QString::fromUtf8("verticalLayout_49"));
        verticalLayout_49->setContentsMargins(0, 0, 0, 0);

        verticalLayout_41->addWidget(fVisionConveyorFrame);


        verticalLayout_32->addWidget(gbConveyorForTracking);

        verticalSpacer_11 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_32->addItem(verticalSpacer_11);

        splitter->addWidget(fObjectDetectingTool);

        verticalLayout_17->addWidget(splitter);

        saObjectDetecting->setWidget(wObjectDetecting);

        verticalLayout_25->addWidget(saObjectDetecting);

        twModule->addTab(tObjectDetecting, QString());
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
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 553, 1600));
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
        sizePolicy1.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy1);
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
        QSizePolicy sizePolicy11(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(pbOpenPicture->sizePolicy().hasHeightForWidth());
        pbOpenPicture->setSizePolicy(sizePolicy11);
        pbOpenPicture->setMinimumSize(QSize(0, 0));
        pbOpenPicture->setMaximumSize(QSize(16777215, 16777215));
        pbOpenPicture->setFont(font4);
        pbOpenPicture->setLayoutDirection(Qt::LeftToRight);
        QIcon icon38;
        icon38.addFile(QString::fromUtf8(":/icon/icons8_image_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbOpenPicture->setIcon(icon38);
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

        widget2 = new QWidget(scrollAreaWidgetContents_6);
        widget2->setObjectName(QString::fromUtf8("widget2"));
        widget2->setMaximumSize(QSize(100, 16777215));
        verticalLayout_36 = new QVBoxLayout(widget2);
        verticalLayout_36->setSpacing(6);
        verticalLayout_36->setContentsMargins(11, 11, 11, 11);
        verticalLayout_36->setObjectName(QString::fromUtf8("verticalLayout_36"));
        widget_3 = new QWidget(widget2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setStyleSheet(QString::fromUtf8(""));
        gridLayout_23 = new QGridLayout(widget_3);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        lbImageWidth = new QLabel(widget_3);
        lbImageWidth->setObjectName(QString::fromUtf8("lbImageWidth"));
        lbImageWidth->setFont(font9);
        lbImageWidth->setStyleSheet(QString::fromUtf8(""));

        gridLayout_23->addWidget(lbImageWidth, 0, 0, 1, 1);

        lbImageHeight = new QLabel(widget_3);
        lbImageHeight->setObjectName(QString::fromUtf8("lbImageHeight"));
        lbImageHeight->setFont(font9);
        lbImageHeight->setStyleSheet(QString::fromUtf8(""));

        gridLayout_23->addWidget(lbImageHeight, 1, 0, 1, 1);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_23->addItem(verticalSpacer_4, 2, 0, 1, 1);


        verticalLayout_36->addWidget(widget_3);


        horizontalLayout_24->addWidget(widget2);


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
        leDrawingThreshold->setFont(font9);

        gridLayout_25->addWidget(leDrawingThreshold, 1, 3, 1, 1);

        label_14 = new QLabel(widget_2);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setFont(font9);

        gridLayout_25->addWidget(label_14, 1, 0, 1, 1);

        label_105 = new QLabel(widget_2);
        label_105->setObjectName(QString::fromUtf8("label_105"));
        label_105->setFont(font9);

        gridLayout_25->addWidget(label_105, 2, 0, 1, 1);

        cbReverseDrawing = new QCheckBox(widget_2);
        cbReverseDrawing->setObjectName(QString::fromUtf8("cbReverseDrawing"));

        gridLayout_25->addWidget(cbReverseDrawing, 2, 1, 1, 1);


        verticalLayout_37->addWidget(widget_2);

        frame_5 = new QFrame(scrollAreaWidgetContents_6);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        sizePolicy2.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy2);
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
        sizePolicy11.setHeightForWidth(pbPainting->sizePolicy().hasHeightForWidth());
        pbPainting->setSizePolicy(sizePolicy11);
        pbPainting->setMinimumSize(QSize(0, 0));
        pbPainting->setMaximumSize(QSize(16777215, 16777215));
        pbPainting->setFont(font4);
        QIcon icon39;
        icon39.addFile(QString::fromUtf8(":/icon/icons8_pencil_drawing_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbPainting->setIcon(icon39);
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
        label_20->setFont(font9);

        gridLayout_24->addWidget(label_20, 0, 1, 1, 1);

        label_18 = new QLabel(frame_7);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setFont(font9);

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
        sizePolicy1.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy1);
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
        sizePolicy4.setHeightForWidth(leDrawAg5->sizePolicy().hasHeightForWidth());
        leDrawAg5->setSizePolicy(sizePolicy4);
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
        label_25->setFont(font9);

        horizontalLayout_21->addWidget(label_25);

        leDrawAg4 = new QLineEdit(widget_10);
        leDrawAg4->setObjectName(QString::fromUtf8("leDrawAg4"));
        sizePolicy4.setHeightForWidth(leDrawAg4->sizePolicy().hasHeightForWidth());
        leDrawAg4->setSizePolicy(sizePolicy4);
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
        sizePolicy4.setHeightForWidth(leDrawAg3->sizePolicy().hasHeightForWidth());
        leDrawAg3->setSizePolicy(sizePolicy4);
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
        sizePolicy4.setHeightForWidth(leDrawAg2->sizePolicy().hasHeightForWidth());
        leDrawAg2->setSizePolicy(sizePolicy4);
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
        sizePolicy4.setHeightForWidth(leDrawAg1->sizePolicy().hasHeightForWidth());
        leDrawAg1->setSizePolicy(sizePolicy4);
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
        QSizePolicy sizePolicy12(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(pbDrawLine->sizePolicy().hasHeightForWidth());
        pbDrawLine->setSizePolicy(sizePolicy12);
        pbDrawLine->setMinimumSize(QSize(0, 0));
        pbDrawLine->setMaximumSize(QSize(70, 16777215));
        QIcon icon40;
        icon40.addFile(QString::fromUtf8(":/icon/Line_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawLine->setIcon(icon40);
        pbDrawLine->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawLine->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawLine, 0, 0, 1, 1);

        pbDrawRectangle = new QToolButton(scrollAreaWidgetContents_6);
        pbDrawRectangle->setObjectName(QString::fromUtf8("pbDrawRectangle"));
        sizePolicy12.setHeightForWidth(pbDrawRectangle->sizePolicy().hasHeightForWidth());
        pbDrawRectangle->setSizePolicy(sizePolicy12);
        pbDrawRectangle->setMinimumSize(QSize(0, 0));
        pbDrawRectangle->setMaximumSize(QSize(70, 16777215));
        QIcon icon41;
        icon41.addFile(QString::fromUtf8(":/icon/Rectangular_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawRectangle->setIcon(icon41);
        pbDrawRectangle->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawRectangle->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawRectangle, 0, 1, 1, 1);

        pbZoomIn = new QToolButton(scrollAreaWidgetContents_6);
        pbZoomIn->setObjectName(QString::fromUtf8("pbZoomIn"));
        sizePolicy12.setHeightForWidth(pbZoomIn->sizePolicy().hasHeightForWidth());
        pbZoomIn->setSizePolicy(sizePolicy12);
        pbZoomIn->setMinimumSize(QSize(0, 0));
        pbZoomIn->setMaximumSize(QSize(70, 16777215));
        QIcon icon42;
        icon42.addFile(QString::fromUtf8(":/icon/Zoom In_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomIn->setIcon(icon42);
        pbZoomIn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbZoomIn->setAutoRaise(true);

        gridLayout_11->addWidget(pbZoomIn, 0, 2, 1, 1);

        pbCursor = new QToolButton(scrollAreaWidgetContents_6);
        pbCursor->setObjectName(QString::fromUtf8("pbCursor"));
        sizePolicy12.setHeightForWidth(pbCursor->sizePolicy().hasHeightForWidth());
        pbCursor->setSizePolicy(sizePolicy12);
        pbCursor->setMinimumSize(QSize(0, 0));
        pbCursor->setMaximumSize(QSize(70, 16777215));
        QIcon icon43;
        icon43.addFile(QString::fromUtf8(":/icon/Cursor-color_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbCursor->setIcon(icon43);
        pbCursor->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbCursor->setAutoRaise(true);

        gridLayout_11->addWidget(pbCursor, 0, 3, 1, 1);

        pbDrawArc = new QToolButton(scrollAreaWidgetContents_6);
        pbDrawArc->setObjectName(QString::fromUtf8("pbDrawArc"));
        sizePolicy12.setHeightForWidth(pbDrawArc->sizePolicy().hasHeightForWidth());
        pbDrawArc->setSizePolicy(sizePolicy12);
        pbDrawArc->setMinimumSize(QSize(0, 0));
        pbDrawArc->setMaximumSize(QSize(70, 16777215));
        QIcon icon44;
        icon44.addFile(QString::fromUtf8(":/icon/Circled Notch_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawArc->setIcon(icon44);
        pbDrawArc->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawArc->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawArc, 1, 0, 1, 1);

        pbDrawCircle = new QToolButton(scrollAreaWidgetContents_6);
        pbDrawCircle->setObjectName(QString::fromUtf8("pbDrawCircle"));
        sizePolicy12.setHeightForWidth(pbDrawCircle->sizePolicy().hasHeightForWidth());
        pbDrawCircle->setSizePolicy(sizePolicy12);
        pbDrawCircle->setMinimumSize(QSize(0, 0));
        pbDrawCircle->setMaximumSize(QSize(70, 16777215));
        QIcon icon45;
        icon45.addFile(QString::fromUtf8(":/icon/Circle_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbDrawCircle->setIcon(icon45);
        pbDrawCircle->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbDrawCircle->setAutoRaise(true);

        gridLayout_11->addWidget(pbDrawCircle, 1, 1, 1, 1);

        pbZoomOut = new QToolButton(scrollAreaWidgetContents_6);
        pbZoomOut->setObjectName(QString::fromUtf8("pbZoomOut"));
        sizePolicy12.setHeightForWidth(pbZoomOut->sizePolicy().hasHeightForWidth());
        pbZoomOut->setSizePolicy(sizePolicy12);
        pbZoomOut->setMinimumSize(QSize(0, 0));
        pbZoomOut->setMaximumSize(QSize(70, 16777215));
        QIcon icon46;
        icon46.addFile(QString::fromUtf8(":/icon/Zoom Out_16px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbZoomOut->setIcon(icon46);
        pbZoomOut->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        pbZoomOut->setAutoRaise(true);

        gridLayout_11->addWidget(pbZoomOut, 1, 2, 1, 1);


        verticalLayout_37->addLayout(gridLayout_11);

        frame_6 = new QFrame(scrollAreaWidgetContents_6);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        sizePolicy2.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
        frame_6->setSizePolicy(sizePolicy2);
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
        sizePolicy11.setHeightForWidth(pbExportDrawingGcodes->sizePolicy().hasHeightForWidth());
        pbExportDrawingGcodes->setSizePolicy(sizePolicy11);
        pbExportDrawingGcodes->setMinimumSize(QSize(185, 65));
        pbExportDrawingGcodes->setMaximumSize(QSize(16777215, 16777215));
        pbExportDrawingGcodes->setFont(font4);
        QIcon icon47;
        icon47.addFile(QString::fromUtf8(":/icon/icons8_code_96px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbExportDrawingGcodes->setIcon(icon47);
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
        sizePolicy5.setHeightForWidth(label_96->sizePolicy().hasHeightForWidth());
        label_96->setSizePolicy(sizePolicy5);
        label_96->setMinimumSize(QSize(0, 0));
        label_96->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_96, 4, 0, 1, 1);

        label_101 = new QLabel(scrollAreaWidgetContents_6);
        label_101->setObjectName(QString::fromUtf8("label_101"));
        sizePolicy.setHeightForWidth(label_101->sizePolicy().hasHeightForWidth());
        label_101->setSizePolicy(sizePolicy);
        label_101->setMinimumSize(QSize(0, 0));
        QFont font20;
        font20.setItalic(false);
        label_101->setFont(font20);
        label_101->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_101, 6, 2, 1, 1);

        label_13 = new QLabel(scrollAreaWidgetContents_6);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font9);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_13, 1, 0, 1, 1);

        horizontalSpacer_33 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_22->addItem(horizontalSpacer_33, 0, 2, 1, 1);

        label_97 = new QLabel(scrollAreaWidgetContents_6);
        label_97->setObjectName(QString::fromUtf8("label_97"));
        sizePolicy5.setHeightForWidth(label_97->sizePolicy().hasHeightForWidth());
        label_97->setSizePolicy(sizePolicy5);
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
        sizePolicy2.setHeightForWidth(cbDrawingEffector->sizePolicy().hasHeightForWidth());
        cbDrawingEffector->setSizePolicy(sizePolicy2);
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
        label_102->setFont(font20);
        label_102->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_102, 7, 2, 1, 1);

        label_93 = new QLabel(scrollAreaWidgetContents_6);
        label_93->setObjectName(QString::fromUtf8("label_93"));
        QSizePolicy sizePolicy13(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy13.setHorizontalStretch(0);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(label_93->sizePolicy().hasHeightForWidth());
        label_93->setSizePolicy(sizePolicy13);
        label_93->setMinimumSize(QSize(0, 0));
        label_93->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_93, 0, 0, 1, 1);

        label_95 = new QLabel(scrollAreaWidgetContents_6);
        label_95->setObjectName(QString::fromUtf8("label_95"));
        sizePolicy5.setHeightForWidth(label_95->sizePolicy().hasHeightForWidth());
        label_95->setSizePolicy(sizePolicy5);
        label_95->setMinimumSize(QSize(0, 0));
        label_95->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_95, 3, 0, 1, 1);

        label_100 = new QLabel(scrollAreaWidgetContents_6);
        label_100->setObjectName(QString::fromUtf8("label_100"));
        sizePolicy.setHeightForWidth(label_100->sizePolicy().hasHeightForWidth());
        label_100->setSizePolicy(sizePolicy);
        label_100->setMinimumSize(QSize(0, 0));
        label_100->setFont(font20);
        label_100->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_100, 4, 2, 1, 1);

        label_98 = new QLabel(scrollAreaWidgetContents_6);
        label_98->setObjectName(QString::fromUtf8("label_98"));
        sizePolicy5.setHeightForWidth(label_98->sizePolicy().hasHeightForWidth());
        label_98->setSizePolicy(sizePolicy5);
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
        label_99->setFont(font20);
        label_99->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_99, 3, 2, 1, 1);

        label_23 = new QLabel(scrollAreaWidgetContents_6);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setFont(font9);
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
        label_103->setFont(font20);
        label_103->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout_22->addWidget(label_103, 2, 2, 1, 1);


        verticalLayout_37->addLayout(gridLayout_22);


        verticalLayout_38->addLayout(verticalLayout_37);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_38->addItem(verticalSpacer_6);

        scrollArea_6->setWidget(scrollAreaWidgetContents_6);

        verticalLayout_26->addWidget(scrollArea_6);

        twModule->addTab(tDrawing, QString());

        ModuleTabManagerLayout->addWidget(twModule);

        splitter_2->addWidget(ModuleTabManagerWidget);

        verticalLayout_46->addWidget(splitter_2);


        verticalLayout_15->addWidget(tabManagerLayout);

        RobotWindow->setCentralWidget(centralWidget);
        mbRobot = new QMenuBar(RobotWindow);
        mbRobot->setObjectName(QString::fromUtf8("mbRobot"));
        mbRobot->setGeometry(QRect(0, 0, 1210, 22));
        mbRobot->setLayoutDirection(Qt::RightToLeft);
        mbRobot->setStyleSheet(QString::fromUtf8("QMenuBar\n"
"{\n"
"background-color: rgb(24, 70, 139);\n"
"color: rgb(255, 255, 255);\n"
"}\n"
"QMenuBar:selected\n"
"{\n"
"	background-color: rgb(25, 167, 242);\n"
"}\n"
"QMenu\n"
"{\n"
"background-color: rgb(41, 155, 255);\n"
"color: rgb(255, 255, 255);\n"
"selection-color: rgb(255, 255, 255);\n"
"selection-background-color: rgb(0, 204, 204);\n"
"}\n"
"QMenu::item\n"
"{\n"
"padding-right:20px;\n"
"padding-left:20px;\n"
"}\n"
"\n"
"QMenu::item:selected\n"
"{\n"
"	background-color: rgb(0, 170, 127);\n"
"	\n"
"}\n"
""));
        mbRobot->setDefaultUp(false);
        mbRobot->setNativeMenuBar(true);
        menuHelp = new QMenu(mbRobot);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setLayoutDirection(Qt::RightToLeft);
        menuReferences = new QMenu(menuHelp);
        menuReferences->setObjectName(QString::fromUtf8("menuReferences"));
        menuEditor = new QMenu(mbRobot);
        menuEditor->setObjectName(QString::fromUtf8("menuEditor"));
        menuEditor->setLayoutDirection(Qt::RightToLeft);
        menuExecute = new QMenu(menuEditor);
        menuExecute->setObjectName(QString::fromUtf8("menuExecute"));
        menuSetting = new QMenu(mbRobot);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        menuSetting->setLayoutDirection(Qt::RightToLeft);
        menuSetting->setStyleSheet(QString::fromUtf8(""));
        menuConnection = new QMenu(menuSetting);
        menuConnection->setObjectName(QString::fromUtf8("menuConnection"));
        menuUI = new QMenu(menuSetting);
        menuUI->setObjectName(QString::fromUtf8("menuUI"));
        RobotWindow->setMenuBar(mbRobot);

        mbRobot->addAction(menuSetting->menuAction());
        mbRobot->addAction(menuEditor->menuAction());
        mbRobot->addAction(menuHelp->menuAction());
        menuHelp->addAction(menuReferences->menuAction());
        menuHelp->addAction(actionAbout);
        menuReferences->addAction(actionGcode);
        menuReferences->addAction(actionSoftware);
        menuEditor->addSeparator();
        menuEditor->addAction(menuExecute->menuAction());
        menuExecute->addAction(actionExecute);
        menuExecute->addAction(actionExecute_All);
        menuExecute->addSeparator();
        menuSetting->addAction(menuConnection->menuAction());
        menuSetting->addAction(menuUI->menuAction());
        menuConnection->addAction(actionBaudrate);
        menuUI->addAction(actionScale);

        retranslateUi(RobotWindow);
        QObject::connect(groupRobotConnection, SIGNAL(toggled(bool)), frameRobotConnection, SLOT(setVisible(bool)));
        QObject::connect(gbJoystick, SIGNAL(toggled(bool)), wgJoystickParameter, SLOT(setVisible(bool)));
        QObject::connect(gbConveyorForTracking, SIGNAL(toggled(bool)), fTracking, SLOT(setVisible(bool)));
        QObject::connect(cbLockGcodeEditor, SIGNAL(toggled(bool)), pbExecuteGcodes, SLOT(setDisabled(bool)));
        QObject::connect(pbLoadCamera, SIGNAL(clicked(bool)), pbPlayPauseCamera, SLOT(setEnabled(bool)));
        QObject::connect(pbLoadCamera, SIGNAL(clicked(bool)), pbCaptureCamera, SLOT(setEnabled(bool)));
        QObject::connect(pbCalibStep2, SIGNAL(toggled(bool)), fCalibStep2, SLOT(setVisible(bool)));
        QObject::connect(gbCameraCalibration, SIGNAL(toggled(bool)), fCameraCalibrationFrame, SLOT(setVisible(bool)));
        QObject::connect(gbCameraObject, SIGNAL(toggled(bool)), fVisionObjectFrame, SLOT(setVisible(bool)));
        QObject::connect(gbCameraVariable, SIGNAL(toggled(bool)), fVisionVariableFrame, SLOT(setVisible(bool)));
        QObject::connect(gbImageProvider, SIGNAL(toggled(bool)), fImageProvider, SLOT(setVisible(bool)));
        QObject::connect(pbCalibStep1, SIGNAL(toggled(bool)), fCalibStep1, SLOT(setVisible(bool)));
        QObject::connect(pbTransformPerspective, SIGNAL(clicked()), pbWarpTool, SLOT(toggle()));
        QObject::connect(pbWarpTool, SIGNAL(clicked()), pbTransformPerspective, SLOT(toggle()));

        twDeltaManager->setCurrentIndex(1);
        twDeltaGeometry->setCurrentIndex(3);
        cbDivision->setCurrentIndex(1);
        pbPump->setDefault(false);
        pbLaser->setDefault(false);
        pbGrip->setDefault(false);
        twConveyor->setCurrentIndex(0);
        twModule->setCurrentIndex(1);
        tabWidget->setCurrentIndex(0);
        pbExDeleteProgram->setDefault(true);
        pbTransformPerspective->setDefault(false);
        pbImageMapping->setDefault(false);
        cbImageSource->setCurrentIndex(0);


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
        groupRobotConnection->setTitle(QCoreApplication::translate("RobotWindow", "Robot Connection", nullptr));
        pbConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        lbComName->setText(QCoreApplication::translate("RobotWindow", "NONE", nullptr));
        lbBaudrate->setText(QCoreApplication::translate("RobotWindow", "115200", nullptr));
        label_122->setText(QCoreApplication::translate("RobotWindow", "IP", nullptr));
        label_64->setText(QCoreApplication::translate("RobotWindow", "Method", nullptr));
        label_65->setText(QCoreApplication::translate("RobotWindow", "Baudrate", nullptr));
        label_6->setText(QCoreApplication::translate("RobotWindow", "ID", nullptr));
        label_10->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
        cbRobotModel->setItemText(0, QCoreApplication::translate("RobotWindow", "Delta X 1", nullptr));
        cbRobotModel->setItemText(1, QCoreApplication::translate("RobotWindow", "Delta X 2", nullptr));
        cbRobotModel->setItemText(2, QCoreApplication::translate("RobotWindow", "Delta X S", nullptr));
        cbRobotModel->setItemText(3, QCoreApplication::translate("RobotWindow", "Custom", nullptr));

        cbAutoConnect->setText(QCoreApplication::translate("RobotWindow", "Auto", nullptr));
        label_91->setText(QCoreApplication::translate("RobotWindow", "Model", nullptr));
        lbID->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_123->setText(QCoreApplication::translate("RobotWindow", "Port", nullptr));
        lbIP->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
        lbLocalPort->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
        label_92->setText(QCoreApplication::translate("RobotWindow", "U", nullptr));
        label_84->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_90->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        label_94->setText(QCoreApplication::translate("RobotWindow", "V", nullptr));
        label_88->setText(QCoreApplication::translate("RobotWindow", "Z", nullptr));
        label_86->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        lbX->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbY->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbZ->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbW->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbU->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbV->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        pbTurnOnROS->setText(QCoreApplication::translate("RobotWindow", "Turn On ROS", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("RobotWindow", "Camera", nullptr));
        label->setText(QCoreApplication::translate("RobotWindow", "Change View", nullptr));
        cbROSCameraView->setItemText(0, QCoreApplication::translate("RobotWindow", "0", nullptr));
        cbROSCameraView->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbROSCameraView->setItemText(2, QCoreApplication::translate("RobotWindow", "2", nullptr));

        groupBox_4->setTitle(QCoreApplication::translate("RobotWindow", "Display", nullptr));
        label_7->setText(QCoreApplication::translate("RobotWindow", "Robot", nullptr));
        cbRobotVersion->setItemText(0, QCoreApplication::translate("RobotWindow", "Delta X 1", nullptr));
        cbRobotVersion->setItemText(1, QCoreApplication::translate("RobotWindow", "Delta X 2", nullptr));

        label_2->setText(QCoreApplication::translate("RobotWindow", "End Effector", nullptr));
        cbEndEffector->setItemText(0, QCoreApplication::translate("RobotWindow", "Suction Cup", nullptr));
        cbEndEffector->setItemText(1, QCoreApplication::translate("RobotWindow", "Gripper", nullptr));
        cbEndEffector->setItemText(2, QCoreApplication::translate("RobotWindow", "None", nullptr));

        label_3->setText(QCoreApplication::translate("RobotWindow", "Objects", nullptr));
#if QT_CONFIG(tooltip)
        btDeleteAllObjects->setToolTip(QCoreApplication::translate("RobotWindow", "Update X Position Value", nullptr));
#endif // QT_CONFIG(tooltip)
        btDeleteAllObjects->setText(QCoreApplication::translate("RobotWindow", "Delete All", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t3D), QCoreApplication::translate("RobotWindow", "3D", nullptr));
        label_53->setText(QCoreApplication::translate("RobotWindow", "Size", nullptr));
        cbWorkingSize->setItemText(0, QCoreApplication::translate("RobotWindow", "300 x 300", nullptr));
        cbWorkingSize->setItemText(1, QCoreApplication::translate("RobotWindow", "400 x 400", nullptr));
        cbWorkingSize->setItemText(2, QCoreApplication::translate("RobotWindow", "600 x 600", nullptr));
        cbWorkingSize->setItemText(3, QCoreApplication::translate("RobotWindow", "800 x 800 ", nullptr));

        label_15->setText(QCoreApplication::translate("RobotWindow", "Z", nullptr));
        label_60->setText(QCoreApplication::translate("RobotWindow", "5-Axis", nullptr));
        label_61->setText(QCoreApplication::translate("RobotWindow", "6-Axis", nullptr));
        label_16->setText(QCoreApplication::translate("RobotWindow", "4-Axis", nullptr));
        lb4AxisValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lb5AxisValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lb6AxisValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(t2D), QCoreApplication::translate("RobotWindow", "2D", nullptr));
        gbMovement1->setTitle(QCoreApplication::translate("RobotWindow", "Movement", nullptr));
        pbHome->setText(QCoreApplication::translate("RobotWindow", "Home", nullptr));
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
        pbUp->setToolTip(QCoreApplication::translate("RobotWindow", "Up (shift + r)", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbUp->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbUp->setText(QCoreApplication::translate("RobotWindow", "Z+", nullptr));
#if QT_CONFIG(shortcut)
        pbUp->setShortcut(QCoreApplication::translate("RobotWindow", "Shift+R", nullptr));
#endif // QT_CONFIG(shortcut)
        label_62->setText(QCoreApplication::translate("RobotWindow", "Start", nullptr));
        leVelocity->setText(QString());
        leVelocity->setPlaceholderText(QCoreApplication::translate("RobotWindow", "200", nullptr));
        label_33->setText(QCoreApplication::translate("RobotWindow", "Step", nullptr));
        label_28->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        cbDivision->setItemText(0, QCoreApplication::translate("RobotWindow", "0.5", nullptr));
        cbDivision->setItemText(1, QCoreApplication::translate("RobotWindow", "1", nullptr));
        cbDivision->setItemText(2, QCoreApplication::translate("RobotWindow", "5", nullptr));
        cbDivision->setItemText(3, QCoreApplication::translate("RobotWindow", "10", nullptr));
        cbDivision->setItemText(4, QCoreApplication::translate("RobotWindow", "50", nullptr));
        cbDivision->setItemText(5, QCoreApplication::translate("RobotWindow", "100", nullptr));

        cbDivision->setCurrentText(QCoreApplication::translate("RobotWindow", "1", nullptr));
        label_32->setText(QCoreApplication::translate("RobotWindow", "mm/s2", nullptr));
        label_63->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        label_30->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        label_29->setText(QCoreApplication::translate("RobotWindow", "Velocity", nullptr));
        leAccel->setText(QString());
        leAccel->setPlaceholderText(QCoreApplication::translate("RobotWindow", "1200", nullptr));
        leStartSpeed->setText(QString());
        leStartSpeed->setPlaceholderText(QCoreApplication::translate("RobotWindow", "12", nullptr));
        label_31->setText(QCoreApplication::translate("RobotWindow", "Accel", nullptr));
        label_116->setText(QCoreApplication::translate("RobotWindow", "End", nullptr));
        leEndSpeed->setText(QString());
        leEndSpeed->setPlaceholderText(QCoreApplication::translate("RobotWindow", "12", nullptr));
        label_117->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        gbJoystick->setTitle(QCoreApplication::translate("RobotWindow", "Joystick", nullptr));
        label_79->setText(QCoreApplication::translate("RobotWindow", "Sensibility", nullptr));
        cbJoystickDevice->setCurrentText(QString());
        label_41->setText(QCoreApplication::translate("RobotWindow", "Device", nullptr));
        leJoystickRange->setText(QCoreApplication::translate("RobotWindow", "1", nullptr));
        leJoystickSensibility->setText(QCoreApplication::translate("RobotWindow", "0.7", nullptr));
        label_51->setText(QCoreApplication::translate("RobotWindow", "Range", nullptr));
        gbIO->setTitle(QCoreApplication::translate("RobotWindow", "IO", nullptr));
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
        cbD13->setText(QCoreApplication::translate("RobotWindow", "D13", nullptr));
        cbD7->setText(QCoreApplication::translate("RobotWindow", "D7", nullptr));
        cbD1->setText(QCoreApplication::translate("RobotWindow", "D1", nullptr));
        cbD2->setText(QCoreApplication::translate("RobotWindow", "D2", nullptr));
        cbD5->setText(QCoreApplication::translate("RobotWindow", "D5", nullptr));
        cbD10->setText(QCoreApplication::translate("RobotWindow", "D10", nullptr));
        cbD9->setText(QCoreApplication::translate("RobotWindow", "D9", nullptr));
        cbD3->setText(QCoreApplication::translate("RobotWindow", "D3", nullptr));
        cbD8->setText(QCoreApplication::translate("RobotWindow", "D8", nullptr));
#if QT_CONFIG(shortcut)
        cbD8->setShortcut(QCoreApplication::translate("RobotWindow", "5", nullptr));
#endif // QT_CONFIG(shortcut)
        cbD6->setText(QCoreApplication::translate("RobotWindow", "D6", nullptr));
        cbD12->setText(QCoreApplication::translate("RobotWindow", "D12", nullptr));
        label_68->setText(QCoreApplication::translate("RobotWindow", "Digital", nullptr));
        cbD0->setText(QCoreApplication::translate("RobotWindow", "D0", nullptr));
        cbD4->setText(QCoreApplication::translate("RobotWindow", "D4", nullptr));
        cbD14->setText(QCoreApplication::translate("RobotWindow", "D14", nullptr));
        cbD15->setText(QCoreApplication::translate("RobotWindow", "D15", nullptr));
        cbD11->setText(QCoreApplication::translate("RobotWindow", "D11", nullptr));
        label_69->setText(QCoreApplication::translate("RobotWindow", "PWM", nullptr));
        label_72->setText(QCoreApplication::translate("RobotWindow", "P0", nullptr));
#if QT_CONFIG(tooltip)
        leP0Value->setToolTip(QCoreApplication::translate("RobotWindow", "0 - 255", nullptr));
#endif // QT_CONFIG(tooltip)
        leP0Value->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_73->setText(QCoreApplication::translate("RobotWindow", "P1", nullptr));
#if QT_CONFIG(tooltip)
        leP1Value->setToolTip(QCoreApplication::translate("RobotWindow", "0 - 255", nullptr));
#endif // QT_CONFIG(tooltip)
        leP1Value->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lePx->setText(QCoreApplication::translate("RobotWindow", "P2", nullptr));
#if QT_CONFIG(tooltip)
        lePxValue->setToolTip(QCoreApplication::translate("RobotWindow", "0 - 255", nullptr));
#endif // QT_CONFIG(tooltip)
        lePxValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_71->setText(QCoreApplication::translate("RobotWindow", "RC Servo", nullptr));
        label_75->setText(QCoreApplication::translate("RobotWindow", "S0", nullptr));
#if QT_CONFIG(tooltip)
        leS0Value->setToolTip(QCoreApplication::translate("RobotWindow", "0 - 255", nullptr));
#endif // QT_CONFIG(tooltip)
        leS0Value->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_77->setText(QCoreApplication::translate("RobotWindow", "S1", nullptr));
#if QT_CONFIG(tooltip)
        leS1Value->setToolTip(QCoreApplication::translate("RobotWindow", "0 - 255", nullptr));
#endif // QT_CONFIG(tooltip)
        leS1Value->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        leSx->setText(QCoreApplication::translate("RobotWindow", "S2", nullptr));
#if QT_CONFIG(tooltip)
        leSxValue->setToolTip(QCoreApplication::translate("RobotWindow", "0 - 255", nullptr));
#endif // QT_CONFIG(tooltip)
        leSxValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
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
        label_80->setText(QCoreApplication::translate("RobotWindow", "I4", nullptr));
        lbI4Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
#if QT_CONFIG(tooltip)
        cbToggle4->setToolTip(QCoreApplication::translate("RobotWindow", "The robot will respond when the value of digital input pin changes", nullptr));
#endif // QT_CONFIG(tooltip)
        cbToggle4->setText(QCoreApplication::translate("RobotWindow", "wait toggle", nullptr));
        pbReadI4->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        label_82->setText(QCoreApplication::translate("RobotWindow", "I5", nullptr));
        lbI5Value->setText(QCoreApplication::translate("RobotWindow", "null", nullptr));
#if QT_CONFIG(tooltip)
        cbToggle5->setToolTip(QCoreApplication::translate("RobotWindow", "The robot will respond when the value of digital input pin changes", nullptr));
#endif // QT_CONFIG(tooltip)
        cbToggle5->setText(QCoreApplication::translate("RobotWindow", "wait toggle", nullptr));
        pbReadI5->setText(QCoreApplication::translate("RobotWindow", "read", nullptr));
        leIx->setText(QCoreApplication::translate("RobotWindow", "I6", nullptr));
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
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(tJogging), QCoreApplication::translate("RobotWindow", "Jogging", nullptr));
        pbConveyorConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        lbConveyorCOMName->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
        label_46->setText(QCoreApplication::translate("RobotWindow", "Moving Mode", nullptr));
        cbConveyorValueType->setItemText(0, QCoreApplication::translate("RobotWindow", "Speed", nullptr));
        cbConveyorValueType->setItemText(1, QCoreApplication::translate("RobotWindow", "Position", nullptr));

        label_52->setText(QCoreApplication::translate("RobotWindow", "Control Mode", nullptr));
        cbConveyorMode->setItemText(0, QCoreApplication::translate("RobotWindow", "Manual", nullptr));
        cbConveyorMode->setItemText(1, QCoreApplication::translate("RobotWindow", "UART", nullptr));

#if QT_CONFIG(tooltip)
        cbConveyorMode->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p><a name=\"31\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">310 \342\200\223 Set Mode</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description: .</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Se"
                        "goe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M310 [&lt;index&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">1: Serial Mode.</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">0: Volume Mode.</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_12->setText(QCoreApplication::translate("RobotWindow", "Value of Moving", nullptr));
#if QT_CONFIG(tooltip)
        leConveyorvMovingValue->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \342\200\223 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Seg"
                        "oe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSys"
                        "temFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background"
                        "-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        leConveyorvMovingValue->setText(QCoreApplication::translate("RobotWindow", "-100", nullptr));
        lbUnitOfConveyorMoving->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
        label_57->setText(QCoreApplication::translate("RobotWindow", "Velocity in Position Mode", nullptr));
        lbSpeedOfPositionMode->setText(QCoreApplication::translate("RobotWindow", "mm/s", nullptr));
#if QT_CONFIG(tooltip)
        leSpeedOfPositionMode->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        leSpeedOfPositionMode->setText(QCoreApplication::translate("RobotWindow", "50", nullptr));
        twConveyor->setTabText(twConveyor->indexOf(tConveyor), QCoreApplication::translate("RobotWindow", "Conveyor X", nullptr));
        pbSlidingConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
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
        twConveyor->setTabText(twConveyor->indexOf(sSlidingRail), QCoreApplication::translate("RobotWindow", "Sliding Rail X", nullptr));
#if QT_CONFIG(tooltip)
        pbExternalControllerConnect->setToolTip(QCoreApplication::translate("RobotWindow", "Connect External Controller", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExternalControllerConnect->setText(QCoreApplication::translate("RobotWindow", "Connect", nullptr));
        lbExternalCOMName->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
        leTransmitToMCU->setText(QString());
        leTransmitToMCU->setPlaceholderText(QCoreApplication::translate("RobotWindow", "Transmit to MCU", nullptr));
        twConveyor->setTabText(twConveyor->indexOf(tExternalMCU), QCoreApplication::translate("RobotWindow", "External MCU", nullptr));
        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(xExternal), QCoreApplication::translate("RobotWindow", "External", nullptr));
        teDebug->setHtml(QCoreApplication::translate("RobotWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-size:7.8pt;\"><br /></p></body></html>", nullptr));
        label_4->setText(QCoreApplication::translate("RobotWindow", "Sender", nullptr));
        label_5->setText(QCoreApplication::translate("RobotWindow", "Receiver", nullptr));
        cbDeviceSender->setItemText(0, QCoreApplication::translate("RobotWindow", "Robot", nullptr));
        cbDeviceSender->setItemText(1, QCoreApplication::translate("RobotWindow", "Conveyor", nullptr));
        cbDeviceSender->setItemText(2, QCoreApplication::translate("RobotWindow", "Slider", nullptr));
        cbDeviceSender->setItemText(3, QCoreApplication::translate("RobotWindow", "External MCU", nullptr));
        cbDeviceSender->setItemText(4, QCoreApplication::translate("RobotWindow", "Encoder", nullptr));

        twDeltaGeometry->setTabText(twDeltaGeometry->indexOf(tTerminal), QCoreApplication::translate("RobotWindow", "Terminal", nullptr));
#if QT_CONFIG(tooltip)
        twModule->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pbExecuteGcodes->setToolTip(QCoreApplication::translate("RobotWindow", "Execute Gcode", nullptr));
#endif // QT_CONFIG(tooltip)
        pbExecuteGcodes->setText(QCoreApplication::translate("RobotWindow", "Run", nullptr));
        rbEditorCurrent->setText(QCoreApplication::translate("RobotWindow", "Current", nullptr));
        rbEditorStart->setText(QCoreApplication::translate("RobotWindow", "Start", nullptr));
        cbLockGcodeEditor->setText(QCoreApplication::translate("RobotWindow", "Block Editor", nullptr));
#if QT_CONFIG(tooltip)
        pbFormat->setToolTip(QCoreApplication::translate("RobotWindow", "Format Gcode Lines", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFormat->setText(QCoreApplication::translate("RobotWindow", "Format", nullptr));
        cbFormatColor->setText(QCoreApplication::translate("RobotWindow", "Color", nullptr));
        cbAutoNumbering->setText(QCoreApplication::translate("RobotWindow", "Auto Numbering", nullptr));
        lbGcodeProgramingIssues->setText(QString());
#if QT_CONFIG(tooltip)
        pbSaveGcode->setToolTip(QCoreApplication::translate("RobotWindow", "Save Gcode Into File", nullptr));
#endif // QT_CONFIG(tooltip)
        pbSaveGcode->setText(QString());
        pteGcodeArea->setHtml(QCoreApplication::translate("RobotWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#000000;\">N05</span><span style=\" font-family:'MS Shell Dlg 2';\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G28</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><spa"
                        "n style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Acceleration</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N10 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">M204</span><span style=\" font-family:'MS Shell Dlg 2';\"> A1200</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Speed</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N15 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> F200</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px"
                        "; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Declare variables</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N20 </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> = 0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N30 </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> = </span><span style=\""
                        " font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> + 1</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#55aa00;\">;Call subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N35 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">M98</span><span style=\" font-family:'MS Shell Dlg 2';\"> P2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font"
                        "-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">; Begin subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N40 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">O2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N45 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell D"
                        "lg 2';\"> Z-350</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N50 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> X-100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N55 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-370</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell D"
                        "lg 2';\">N60 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-350</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N65 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> X100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N70 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-370</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N75 M99</span></p>\n"
"<p style=\" margin-top:0px; "
                        "margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;End subprogram</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Loop 5 times</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N80 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#00aa00;\">IF</span><span style=\" font-family:'MS Shell Dlg 2';\"> [</span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</spa"
                        "n><span style=\" font-family:'MS Shell Dlg 2';\"> LE 5] </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#00aa00;\">THEN</span><span style=\" font-family:'MS Shell Dlg 2';\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#ff5500;\">GOTO</span><span style=\" font-family:'MS Shell Dlg 2';\"> 30</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N85 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\"> </span></p></body></html>", nullptr));
        leExProgramName->setText(QCoreApplication::translate("RobotWindow", "Program 1", nullptr));
        pbExDeleteProgram->setText(QString());
        lbExGCodeNumber->setText(QCoreApplication::translate("RobotWindow", "100 Gcode Lines", nullptr));
#if QT_CONFIG(tooltip)
        pbUploadProgram->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbUploadProgram->setText(QString());
#if QT_CONFIG(tooltip)
        pbImportGcodeFiles->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbImportGcodeFiles->setText(QCoreApplication::translate("RobotWindow", "Import", nullptr));
#if QT_CONFIG(tooltip)
        pbAddNewProgram->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbAddNewProgram->setText(QCoreApplication::translate("RobotWindow", "New ", nullptr));
#if QT_CONFIG(tooltip)
        pbRefreshGcodeFiles->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbRefreshGcodeFiles->setText(QCoreApplication::translate("RobotWindow", "F5   ", nullptr));
#if QT_CONFIG(tooltip)
        pbFindGcodeFile->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbFindGcodeFile->setText(QCoreApplication::translate("RobotWindow", "Find", nullptr));
#if QT_CONFIG(tooltip)
        pbSortGcodeFiles->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbSortGcodeFiles->setText(QCoreApplication::translate("RobotWindow", "Sort", nullptr));
        lbExGCodeNumber_2->setText(QCoreApplication::translate("RobotWindow", "Path", nullptr));
        leGcodeProgramPath->setText(QCoreApplication::translate("RobotWindow", "/gcode", nullptr));
        pbOpenGcodeProgramPath->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("RobotWindow", "Offline", nullptr));
        textEdit->setHtml(QCoreApplication::translate("RobotWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt;\">Author:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt;\">Description:</span></p></body></html>", nullptr));
#if QT_CONFIG(tooltip)
        pbUploadProgram_2->setToolTip(QString());
#endif // QT_CONFIG(tooltip)
        pbUploadProgram_2->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("RobotWindow", "Online", nullptr));
        twModule->setTabText(twModule->indexOf(tGcodeEditor), QCoreApplication::translate("RobotWindow", "Gcode Editor", nullptr));
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

#if QT_CONFIG(tooltip)
        pbCameraWindowMode->setToolTip(QCoreApplication::translate("RobotWindow", "Window Mode", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCameraWindowMode->setText(QCoreApplication::translate("RobotWindow", "Window", nullptr));
        lbDisplayRatio->setText(QCoreApplication::translate("RobotWindow", "Ratio: 100%", nullptr));
        lbMatSize->setText(QCoreApplication::translate("RobotWindow", "Re: 800x500", nullptr));
        gbImageProvider->setTitle(QCoreApplication::translate("RobotWindow", "Image Provider", nullptr));
        label_176->setText(QCoreApplication::translate("RobotWindow", "Source", nullptr));
        cbSourceForImageProvider->setItemText(0, QCoreApplication::translate("RobotWindow", "Webcam", nullptr));
        cbSourceForImageProvider->setItemText(1, QCoreApplication::translate("RobotWindow", "Images", nullptr));
        cbSourceForImageProvider->setItemText(2, QCoreApplication::translate("RobotWindow", "Plugin", nullptr));
        cbSourceForImageProvider->setItemText(3, QCoreApplication::translate("RobotWindow", "Socket", nullptr));

#if QT_CONFIG(tooltip)
        pbLoadCamera->setToolTip(QCoreApplication::translate("RobotWindow", "Load Camera", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLoadCamera->setText(QCoreApplication::translate("RobotWindow", "Load Camera", nullptr));
        label_11->setText(QCoreApplication::translate("RobotWindow", "FPS", nullptr));
        leFPS->setText(QCoreApplication::translate("RobotWindow", "5", nullptr));
        label_124->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        leCameraWidth->setText(QCoreApplication::translate("RobotWindow", "800", nullptr));
        label_125->setText(QCoreApplication::translate("RobotWindow", "H", nullptr));
        leCameraHeight->setText(QCoreApplication::translate("RobotWindow", "500", nullptr));
#if QT_CONFIG(tooltip)
        pbPlayPauseCamera->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Play and Pause</p><p>M98 PpauseCamera</p><p>M98 PresumeCamera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pbPlayPauseCamera->setText(QString());
#if QT_CONFIG(tooltip)
        pbCaptureCamera->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Capture</p><p>M98 PcaptureCamera</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pbCaptureCamera->setText(QString());
        lbCameraState->setText(QString());
#if QT_CONFIG(tooltip)
        pbLoadTestImage->setToolTip(QCoreApplication::translate("RobotWindow", "Load Image", nullptr));
#endif // QT_CONFIG(tooltip)
        pbLoadTestImage->setText(QCoreApplication::translate("RobotWindow", "Load Image", nullptr));
        cbExternalImageSource->setText(QCoreApplication::translate("RobotWindow", "Enough", nullptr));
        label_177->setText(QCoreApplication::translate("RobotWindow", "plugin", nullptr));
        comboBox_2->setItemText(0, QCoreApplication::translate("RobotWindow", "IndustryCamera", nullptr));

        label_178->setText(QCoreApplication::translate("RobotWindow", "W", nullptr));
        leImageWidth->setText(QCoreApplication::translate("RobotWindow", "800", nullptr));
        label_179->setText(QCoreApplication::translate("RobotWindow", "H", nullptr));
        leImageHeight->setText(QCoreApplication::translate("RobotWindow", "500", nullptr));
        gbCameraCalibration->setTitle(QCoreApplication::translate("RobotWindow", "Calibration", nullptr));
        pbCalibStep1->setText(QCoreApplication::translate("RobotWindow", "Step 1: Find the 4 points of the square", nullptr));
        leChessWidth->setText(QCoreApplication::translate("RobotWindow", "7", nullptr));
        leChessHeight->setText(QCoreApplication::translate("RobotWindow", "7", nullptr));
        label_109->setText(QCoreApplication::translate("RobotWindow", "Chessboard", nullptr));
#if QT_CONFIG(tooltip)
        pbTransformPerspective->setToolTip(QCoreApplication::translate("RobotWindow", "Perspective Transformation", nullptr));
#endif // QT_CONFIG(tooltip)
        pbTransformPerspective->setText(QCoreApplication::translate("RobotWindow", "Warp Perspective", nullptr));
        label_110->setText(QCoreApplication::translate("RobotWindow", "Dimension", nullptr));
        pbFindChessboard->setText(QCoreApplication::translate("RobotWindow", "Find chessboard", nullptr));
        pbCalibStep2->setText(QCoreApplication::translate("RobotWindow", "Step 2: Coordinate correction", nullptr));
#if QT_CONFIG(tooltip)
        pbImageMapping->setToolTip(QCoreApplication::translate("RobotWindow", "Perspective Transformation", nullptr));
#endif // QT_CONFIG(tooltip)
        pbImageMapping->setText(QCoreApplication::translate("RobotWindow", "Calculate Mapping Matrix", nullptr));
        label_39->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        leRealityPoint2Y->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        leRealityPoint1Y->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_133->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_140->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
#if QT_CONFIG(tooltip)
        pbObjectOrigin->setToolTip(QCoreApplication::translate("RobotWindow", "Set a calibrating point", nullptr));
#endif // QT_CONFIG(tooltip)
        pbObjectOrigin->setText(QCoreApplication::translate("RobotWindow", "Point Tool", nullptr));
        label_38->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        leRealityPoint1X->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_132->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        leRealityPoint2X->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        label_139->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        cbMoveOnConveyor1->setText(QCoreApplication::translate("RobotWindow", "Sync with conveyor", nullptr));
        pbCalibPoint1->setText(QCoreApplication::translate("RobotWindow", "Point 1", nullptr));
#if QT_CONFIG(shortcut)
        pbCalibPoint1->setShortcut(QCoreApplication::translate("RobotWindow", "!", nullptr));
#endif // QT_CONFIG(shortcut)
        pbCalibPoint2->setText(QCoreApplication::translate("RobotWindow", "Point 2", nullptr));
#if QT_CONFIG(shortcut)
        pbCalibPoint2->setShortcut(QCoreApplication::translate("RobotWindow", "@", nullptr));
#endif // QT_CONFIG(shortcut)
        gbCameraObject->setTitle(QCoreApplication::translate("RobotWindow", "Object", nullptr));
        cbObjectType->setItemText(0, QCoreApplication::translate("RobotWindow", "Type 1", nullptr));

        pushButton->setText(QCoreApplication::translate("RobotWindow", "+", nullptr));
        pushButton_2->setText(QCoreApplication::translate("RobotWindow", "-", nullptr));
        label_126->setText(QCoreApplication::translate("RobotWindow", "Detection algorithm", nullptr));
        cbDetectingAlgorithm->setItemText(0, QCoreApplication::translate("RobotWindow", "Find Blobs", nullptr));
        cbDetectingAlgorithm->setItemText(1, QCoreApplication::translate("RobotWindow", "Find Circles", nullptr));
        cbDetectingAlgorithm->setItemText(2, QCoreApplication::translate("RobotWindow", "External Script", nullptr));

        label_172->setText(QCoreApplication::translate("RobotWindow", "Min", nullptr));
        leMaxWRec->setText(QCoreApplication::translate("RobotWindow", "25", nullptr));
        leMaxLRec->setText(QCoreApplication::translate("RobotWindow", "25", nullptr));
        label_55->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        leWRec->setText(QCoreApplication::translate("RobotWindow", "20", nullptr));
#if QT_CONFIG(tooltip)
        pbObjectRect->setToolTip(QCoreApplication::translate("RobotWindow", "Bound the object size", nullptr));
#endif // QT_CONFIG(tooltip)
        pbObjectRect->setText(QCoreApplication::translate("RobotWindow", "Get Size Tool", nullptr));
        label_56->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_44->setText(QCoreApplication::translate("RobotWindow", "Height", nullptr));
        leMinLRec->setText(QCoreApplication::translate("RobotWindow", "15", nullptr));
        leLRec->setText(QCoreApplication::translate("RobotWindow", "20", nullptr));
#if QT_CONFIG(tooltip)
        pbFilter->setToolTip(QCoreApplication::translate("RobotWindow", "Camera Filter", nullptr));
#endif // QT_CONFIG(tooltip)
        pbFilter->setText(QCoreApplication::translate("RobotWindow", "Color Filter Panel", nullptr));
        label_43->setText(QCoreApplication::translate("RobotWindow", "Length", nullptr));
        label_173->setText(QCoreApplication::translate("RobotWindow", "Max", nullptr));
        leHRec->setText(QCoreApplication::translate("RobotWindow", "20", nullptr));
        label_54->setText(QCoreApplication::translate("RobotWindow", "mm", nullptr));
        label_174->setText(QCoreApplication::translate("RobotWindow", "Min", nullptr));
        label_42->setText(QCoreApplication::translate("RobotWindow", "Width", nullptr));
        leMinWRec->setText(QCoreApplication::translate("RobotWindow", "15", nullptr));
        lbTrackingObject->setText(QString());
        label_175->setText(QCoreApplication::translate("RobotWindow", "Max", nullptr));
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
        lePythonUrl->setText(QCoreApplication::translate("RobotWindow", "detect.py", nullptr));
        pushButton_3->setText(QCoreApplication::translate("RobotWindow", "Open script example", nullptr));
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
        pbViewDataObjects->setText(QCoreApplication::translate("RobotWindow", "Object Table", nullptr));
#if QT_CONFIG(tooltip)
        pbClearDetectObjects->setToolTip(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Clear All Objects in Memory</p><p>M98 PclearObjects --&gt; Clear All</p><p>M98 PdeleteFirstObject --&gt; Delete First</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pbClearDetectObjects->setStatusTip(QString());
#endif // QT_CONFIG(statustip)
        pbClearDetectObjects->setText(QCoreApplication::translate("RobotWindow", "Clear Objects", nullptr));
        label_50->setText(QCoreApplication::translate("RobotWindow", "Visible", nullptr));
        lbVisibleObjectNumber->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        lbTrackingObjectNumber->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_48->setText(QCoreApplication::translate("RobotWindow", "Tracking", nullptr));
        label_155->setText(QString());
        label_156->setText(QString());
        label_157->setText(QString());
        label_158->setText(QString());
        label_159->setText(QString());
        gbConveyorForTracking->setTitle(QCoreApplication::translate("RobotWindow", "Tracking", nullptr));
        label_150->setText(QCoreApplication::translate("RobotWindow", "Object", nullptr));
        label_152->setText(QCoreApplication::translate("RobotWindow", "%", nullptr));
        label_151->setText(QCoreApplication::translate("RobotWindow", "Tracking error", nullptr));
        leTrackingError->setText(QCoreApplication::translate("RobotWindow", "0.3", nullptr));
        label_127->setText(QCoreApplication::translate("RobotWindow", "Conveyor", nullptr));
        leConvenyorSpeed->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        pbReadProximitySensor->setText(QCoreApplication::translate("RobotWindow", "Read", nullptr));
        pbBackwardConveyor->setText(QCoreApplication::translate("RobotWindow", "Backward", nullptr));
        pbResetEncoderPosition->setText(QCoreApplication::translate("RobotWindow", "Reset", nullptr));
        label_189->setText(QCoreApplication::translate("RobotWindow", "Sensor", nullptr));
        leForwardConveyorGcode->setText(QCoreApplication::translate("RobotWindow", "M03 D0", nullptr));
        leTurnOffConveyorGcode->setText(QCoreApplication::translate("RobotWindow", "M05 D0, M05 D1", nullptr));
        rbEncoderEnable->setText(QCoreApplication::translate("RobotWindow", "Use Encoder", nullptr));
        label_148->setText(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Deviation angle </p><p><span style=\" font-weight:400; font-style:italic;\">X Axis</span></p></body></html>", nullptr));
        label_191->setText(QCoreApplication::translate("RobotWindow", "Proximity sensor", nullptr));
        leBackwardConveyorGcode->setText(QCoreApplication::translate("RobotWindow", "M03 D1", nullptr));
        label_45->setText(QCoreApplication::translate("RobotWindow", "Constant Velocity", nullptr));
        label_163->setText(QCoreApplication::translate("RobotWindow", "Gcode Setting", nullptr));
        lbProximitySensorValue->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        leEncoderCom->setText(QCoreApplication::translate("RobotWindow", "COM", nullptr));
        pbTurnOffConveyor->setText(QCoreApplication::translate("RobotWindow", "Turn off", nullptr));
        label_121->setText(QCoreApplication::translate("RobotWindow", "(mm/s)", nullptr));
        label_162->setText(QCoreApplication::translate("RobotWindow", "(mm)", nullptr));
        leConveyorDeviationAngle->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        pbConnectEncdoer->setText(QCoreApplication::translate("RobotWindow", "Connect Encoder", nullptr));
        label_161->setText(QCoreApplication::translate("RobotWindow", "Move", nullptr));
        cbEncoderPositionInverse->setText(QCoreApplication::translate("RobotWindow", "Inverse", nullptr));
        label_49->setText(QCoreApplication::translate("RobotWindow", "(mm/s)", nullptr));
        label_160->setText(QCoreApplication::translate("RobotWindow", "Control", nullptr));
        label_119->setText(QCoreApplication::translate("RobotWindow", "(mm)", nullptr));
        rbVirtualEncoderEnable->setText(QCoreApplication::translate("RobotWindow", "Use Virtual Encoder", nullptr));
        label_118->setText(QCoreApplication::translate("RobotWindow", "Current Position", nullptr));
        pbForwardConveyor->setText(QCoreApplication::translate("RobotWindow", "Forward", nullptr));
        cbConveyorDirectionControl->setItemText(0, QCoreApplication::translate("RobotWindow", "Forward", nullptr));
        cbConveyorDirectionControl->setItemText(1, QCoreApplication::translate("RobotWindow", "Backward", nullptr));

        label_120->setText(QCoreApplication::translate("RobotWindow", "Current Velocity", nullptr));
        cbAutoReadProximitySensor->setText(QCoreApplication::translate("RobotWindow", "Auto", nullptr));
        label_170->setText(QCoreApplication::translate("RobotWindow", "(mm)", nullptr));
        leConveyorPoint2X->setText(QCoreApplication::translate("RobotWindow", "100", nullptr));
        pbCalibConveyorAngle->setText(QCoreApplication::translate("RobotWindow", "Calculate", nullptr));
        leConveyorPoint1X->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_197->setText(QCoreApplication::translate("RobotWindow", "(mm)", nullptr));
        label_199->setText(QCoreApplication::translate("RobotWindow", "(mm)", nullptr));
        leConveyorPoint1Y->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_198->setText(QCoreApplication::translate("RobotWindow", "(mm)", nullptr));
        leConveyorPoint2Y->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        pbGetConveyorPoint1X->setText(QCoreApplication::translate("RobotWindow", "X1", nullptr));
        pbGetConveyorPoint1Y->setText(QCoreApplication::translate("RobotWindow", "Y1", nullptr));
        pbGetConveyorPoint2X->setText(QCoreApplication::translate("RobotWindow", "X2", nullptr));
        pbGetConveyorPoint2Y->setText(QCoreApplication::translate("RobotWindow", "Y2", nullptr));
        label_196->setText(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Calib Points</p></body></html>", nullptr));
        label_149->setText(QCoreApplication::translate("RobotWindow", "(deg)", nullptr));
        leConveyorPoint3X->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        leConveyorPoint3Y->setText(QCoreApplication::translate("RobotWindow", "0", nullptr));
        label_169->setText(QCoreApplication::translate("RobotWindow", "Y", nullptr));
        label_168->setText(QCoreApplication::translate("RobotWindow", "X", nullptr));
        label_171->setText(QCoreApplication::translate("RobotWindow", "(mm)", nullptr));
        label_167->setText(QCoreApplication::translate("RobotWindow", "<html><head/><body><p>Test Object</p></body></html>", nullptr));
        twModule->setTabText(twModule->indexOf(tObjectDetecting), QCoreApplication::translate("RobotWindow", "Object Detecting", nullptr));
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
        menuHelp->setTitle(QCoreApplication::translate("RobotWindow", "Help", nullptr));
        menuReferences->setTitle(QCoreApplication::translate("RobotWindow", "References", nullptr));
        menuEditor->setTitle(QCoreApplication::translate("RobotWindow", "Program", nullptr));
        menuExecute->setTitle(QCoreApplication::translate("RobotWindow", "Execute", nullptr));
        menuSetting->setTitle(QCoreApplication::translate("RobotWindow", "Setting", nullptr));
        menuConnection->setTitle(QCoreApplication::translate("RobotWindow", "Connection", nullptr));
        menuUI->setTitle(QCoreApplication::translate("RobotWindow", "UI", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RobotWindow: public Ui_RobotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTWINDOW_H
