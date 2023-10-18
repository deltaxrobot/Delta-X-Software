# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'RobotWindow.ui'
##
## Created by: Qt User Interface Compiler version 6.4.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QAction, QBrush, QColor, QConicalGradient,
    QCursor, QFont, QFontDatabase, QGradient,
    QIcon, QImage, QKeySequence, QLinearGradient,
    QPainter, QPalette, QPixmap, QRadialGradient,
    QTransform)
from PySide6.QtWidgets import (QApplication, QCheckBox, QComboBox, QDial,
    QFrame, QGridLayout, QGroupBox, QHBoxLayout,
    QHeaderView, QLabel, QLayout, QLineEdit,
    QMainWindow, QPushButton, QRadioButton, QScrollArea,
    QSizePolicy, QSlider, QSpacerItem, QSplitter,
    QTabWidget, QTextEdit, QToolButton, QTreeView,
    QVBoxLayout, QWidget)

from DrawingWidget import DrawingWidget
from codeeditor import CodeEditor
from imageviewer import ImageViewer
import resource_rc

class Ui_RobotWindow(object):
    def setupUi(self, RobotWindow):
        if not RobotWindow.objectName():
            RobotWindow.setObjectName(u"RobotWindow")
        RobotWindow.resize(1210, 630)
        sizePolicy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(RobotWindow.sizePolicy().hasHeightForWidth())
        RobotWindow.setSizePolicy(sizePolicy)
        RobotWindow.setMinimumSize(QSize(700, 400))
        font = QFont()
        font.setBold(False)
        font.setKerning(True)
        RobotWindow.setFont(font)
        icon = QIcon()
        icon.addFile(u"delta_x_logo_96x96.ico", QSize(), QIcon.Normal, QIcon.Off)
        RobotWindow.setWindowIcon(icon)
        RobotWindow.setLayoutDirection(Qt.LeftToRight)
        RobotWindow.setStyleSheet(u"QLabel\n"
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
"}")
        self.actionAdd = QAction(RobotWindow)
        self.actionAdd.setObjectName(u"actionAdd")
        self.actionRemove = QAction(RobotWindow)
        self.actionRemove.setObjectName(u"actionRemove")
        self.actionAbout = QAction(RobotWindow)
        self.actionAbout.setObjectName(u"actionAbout")
        self.actionGcode = QAction(RobotWindow)
        self.actionGcode.setObjectName(u"actionGcode")
        self.actionSoftware = QAction(RobotWindow)
        self.actionSoftware.setObjectName(u"actionSoftware")
        self.actionExecute_All = QAction(RobotWindow)
        self.actionExecute_All.setObjectName(u"actionExecute_All")
        self.actionDelta_X_1 = QAction(RobotWindow)
        self.actionDelta_X_1.setObjectName(u"actionDelta_X_1")
        self.actionDelta_X_1.setCheckable(True)
        self.actionDelta_X_1.setChecked(True)
        self.actionExecute = QAction(RobotWindow)
        self.actionExecute.setObjectName(u"actionExecute")
        self.actionBaudrate = QAction(RobotWindow)
        self.actionBaudrate.setObjectName(u"actionBaudrate")
        self.actionScale = QAction(RobotWindow)
        self.actionScale.setObjectName(u"actionScale")
        self.centralWidget = QWidget(RobotWindow)
        self.centralWidget.setObjectName(u"centralWidget")
        self.verticalLayout_15 = QVBoxLayout(self.centralWidget)
        self.verticalLayout_15.setSpacing(6)
        self.verticalLayout_15.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_15.setObjectName(u"verticalLayout_15")
        self.twDeltaManager = QTabWidget(self.centralWidget)
        self.twDeltaManager.setObjectName(u"twDeltaManager")
        self.twDeltaManager.setEnabled(True)
        sizePolicy1 = QSizePolicy(QSizePolicy.Ignored, QSizePolicy.Ignored)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.twDeltaManager.sizePolicy().hasHeightForWidth())
        self.twDeltaManager.setSizePolicy(sizePolicy1)
        self.twDeltaManager.setMinimumSize(QSize(0, 0))
        self.twDeltaManager.setMaximumSize(QSize(16777215, 40))
        font1 = QFont()
        font1.setPointSize(10)
        font1.setBold(False)
        font1.setKerning(True)
        self.twDeltaManager.setFont(font1)
        self.twDeltaManager.setLayoutDirection(Qt.LeftToRight)
        self.twDeltaManager.setStyleSheet(u"QTabWidget::pane { /* The tab widget frame */\n"
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
"")
        self.twDeltaManager.setTabPosition(QTabWidget.North)
        self.tabDefaultDelta = QWidget()
        self.tabDefaultDelta.setObjectName(u"tabDefaultDelta")
        self.twDeltaManager.addTab(self.tabDefaultDelta, "")
        self.tabAddNewDelta = QWidget()
        self.tabAddNewDelta.setObjectName(u"tabAddNewDelta")
        self.twDeltaManager.addTab(self.tabAddNewDelta, "")

        self.verticalLayout_15.addWidget(self.twDeltaManager)

        self.frame_11 = QFrame(self.centralWidget)
        self.frame_11.setObjectName(u"frame_11")
        self.frame_11.setMinimumSize(QSize(0, 25))
        self.frame_11.setFrameShape(QFrame.StyledPanel)
        self.frame_11.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_34 = QHBoxLayout(self.frame_11)
        self.horizontalLayout_34.setSpacing(10)
        self.horizontalLayout_34.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_34.setObjectName(u"horizontalLayout_34")
        self.horizontalLayout_34.setContentsMargins(0, 0, 0, 0)
        self.label_122 = QLabel(self.frame_11)
        self.label_122.setObjectName(u"label_122")
        font2 = QFont()
        font2.setBold(True)
        self.label_122.setFont(font2)
        self.label_122.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_34.addWidget(self.label_122)

        self.leIP = QLineEdit(self.frame_11)
        self.leIP.setObjectName(u"leIP")
        sizePolicy2 = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.leIP.sizePolicy().hasHeightForWidth())
        self.leIP.setSizePolicy(sizePolicy2)
        self.leIP.setFrame(False)
        self.leIP.setDragEnabled(False)
        self.leIP.setReadOnly(True)
        self.leIP.setClearButtonEnabled(False)

        self.horizontalLayout_34.addWidget(self.leIP)

        self.label_123 = QLabel(self.frame_11)
        self.label_123.setObjectName(u"label_123")
        self.label_123.setFont(font2)
        self.label_123.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_34.addWidget(self.label_123)

        self.lePort = QLineEdit(self.frame_11)
        self.lePort.setObjectName(u"lePort")
        sizePolicy.setHeightForWidth(self.lePort.sizePolicy().hasHeightForWidth())
        self.lePort.setSizePolicy(sizePolicy)
        self.lePort.setFrame(False)
        self.lePort.setDragEnabled(False)
        self.lePort.setReadOnly(True)
        self.lePort.setClearButtonEnabled(False)

        self.horizontalLayout_34.addWidget(self.lePort)

        self.tbServerConfig = QToolButton(self.frame_11)
        self.tbServerConfig.setObjectName(u"tbServerConfig")
        icon1 = QIcon()
        icon1.addFile(u":/icon/icons8_edit_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbServerConfig.setIcon(icon1)

        self.horizontalLayout_34.addWidget(self.tbServerConfig)

        self.horizontalSpacer_26 = QSpacerItem(853, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_34.addItem(self.horizontalSpacer_26)


        self.verticalLayout_15.addWidget(self.frame_11)

        self.tabManagerLayout = QWidget(self.centralWidget)
        self.tabManagerLayout.setObjectName(u"tabManagerLayout")
        sizePolicy3 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.tabManagerLayout.sizePolicy().hasHeightForWidth())
        self.tabManagerLayout.setSizePolicy(sizePolicy3)
        self.tabManagerLayout.setMinimumSize(QSize(0, 0))
        self.tabManagerLayout.setStyleSheet(u"QTabWidget::pane { /* The tab widget frame */\n"
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
"}")
        self.verticalLayout_46 = QVBoxLayout(self.tabManagerLayout)
        self.verticalLayout_46.setSpacing(0)
        self.verticalLayout_46.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_46.setObjectName(u"verticalLayout_46")
        self.verticalLayout_46.setContentsMargins(0, 0, 0, 0)
        self.splitter_2 = QSplitter(self.tabManagerLayout)
        self.splitter_2.setObjectName(u"splitter_2")
        self.splitter_2.setMinimumSize(QSize(0, 220))
        self.splitter_2.setStyleSheet(u"QSplitter::handle:horizontal {    \n"
"	\n"
"	image: url(:/icon/divider_50px.png);\n"
"}")
        self.splitter_2.setOrientation(Qt.Horizontal)
        self.splitter_2.setOpaqueResize(False)
        self.splitter_2.setHandleWidth(20)
        self.ModuleTabManagerWidget = QWidget(self.splitter_2)
        self.ModuleTabManagerWidget.setObjectName(u"ModuleTabManagerWidget")
        self.ModuleTabManagerWidget.setMinimumSize(QSize(0, 0))
        self.ModuleTabManagerWidget.setStyleSheet(u"")
        self.ModuleTabManagerLayout = QVBoxLayout(self.ModuleTabManagerWidget)
        self.ModuleTabManagerLayout.setSpacing(0)
        self.ModuleTabManagerLayout.setContentsMargins(11, 11, 11, 11)
        self.ModuleTabManagerLayout.setObjectName(u"ModuleTabManagerLayout")
        self.ModuleTabManagerLayout.setContentsMargins(0, 0, 0, 0)
        self.twModule = QTabWidget(self.ModuleTabManagerWidget)
        self.twModule.setObjectName(u"twModule")
        self.twModule.setEnabled(True)
        font3 = QFont()
        font3.setPointSize(11)
        font3.setBold(False)
        self.twModule.setFont(font3)
        self.twModule.setFocusPolicy(Qt.TabFocus)
        self.twModule.setStyleSheet(u"QGroupBox {\n"
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
"}*/")
        self.twModule.setTabShape(QTabWidget.Rounded)
        self.twModule.setUsesScrollButtons(True)
        self.twModule.setDocumentMode(False)
        self.twModule.setTabsClosable(False)
        self.twModule.setMovable(False)
        self.twModule.setTabBarAutoHide(False)
        self.tGcodeEditor = QWidget()
        self.tGcodeEditor.setObjectName(u"tGcodeEditor")
        self.verticalLayout = QVBoxLayout(self.tGcodeEditor)
        self.verticalLayout.setSpacing(6)
        self.verticalLayout.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.gridLayout_30 = QGridLayout()
        self.gridLayout_30.setSpacing(6)
        self.gridLayout_30.setObjectName(u"gridLayout_30")
        self.horizontalSpacer_3 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_30.addItem(self.horizontalSpacer_3, 2, 5, 1, 1)

        self.rbEditorCurrent = QRadioButton(self.tGcodeEditor)
        self.rbEditorCurrent.setObjectName(u"rbEditorCurrent")
        self.rbEditorCurrent.setChecked(False)

        self.gridLayout_30.addWidget(self.rbEditorCurrent, 2, 6, 1, 1)

        self.pbExecuteGcodes = QPushButton(self.tGcodeEditor)
        self.pbExecuteGcodes.setObjectName(u"pbExecuteGcodes")
        sizePolicy4 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Expanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.pbExecuteGcodes.sizePolicy().hasHeightForWidth())
        self.pbExecuteGcodes.setSizePolicy(sizePolicy4)
        self.pbExecuteGcodes.setMinimumSize(QSize(70, 0))
        font4 = QFont()
        font4.setPointSize(10)
        self.pbExecuteGcodes.setFont(font4)
        self.pbExecuteGcodes.setAutoFillBackground(False)
        icon2 = QIcon()
        icon2.addFile(u":/icon/Play_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon2.addFile(u":/icon/Pause_96px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbExecuteGcodes.setIcon(icon2)
        self.pbExecuteGcodes.setIconSize(QSize(30, 30))
        self.pbExecuteGcodes.setCheckable(True)
        self.pbExecuteGcodes.setFlat(False)

        self.gridLayout_30.addWidget(self.pbExecuteGcodes, 0, 7, 3, 1)

        self.label_7 = QLabel(self.tGcodeEditor)
        self.label_7.setObjectName(u"label_7")

        self.gridLayout_30.addWidget(self.label_7, 0, 0, 1, 1)

        self.rbEditorStart = QRadioButton(self.tGcodeEditor)
        self.rbEditorStart.setObjectName(u"rbEditorStart")
        self.rbEditorStart.setChecked(True)

        self.gridLayout_30.addWidget(self.rbEditorStart, 0, 6, 1, 1)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_30.addItem(self.horizontalSpacer_2, 0, 5, 1, 1)

        self.cbProgramThreadID = QComboBox(self.tGcodeEditor)
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.setObjectName(u"cbProgramThreadID")

        self.gridLayout_30.addWidget(self.cbProgramThreadID, 0, 1, 1, 1)


        self.verticalLayout.addLayout(self.gridLayout_30)

        self.frame_10 = QFrame(self.tGcodeEditor)
        self.frame_10.setObjectName(u"frame_10")
        self.frame_10.setMinimumSize(QSize(0, 0))
        self.frame_10.setFrameShape(QFrame.StyledPanel)
        self.frame_10.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.frame_10)
        self.horizontalLayout_9.setSpacing(2)
        self.horizontalLayout_9.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(2, 2, 2, 2)
        self.pbOpenGcodeDocs = QToolButton(self.frame_10)
        self.pbOpenGcodeDocs.setObjectName(u"pbOpenGcodeDocs")
        icon3 = QIcon()
        icon3.addFile(u":/icon/icons8_help_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbOpenGcodeDocs.setIcon(icon3)
        self.pbOpenGcodeDocs.setIconSize(QSize(32, 32))
        self.pbOpenGcodeDocs.setAutoRaise(True)

        self.horizontalLayout_9.addWidget(self.pbOpenGcodeDocs)

        self.pbSaveGcode = QToolButton(self.frame_10)
        self.pbSaveGcode.setObjectName(u"pbSaveGcode")
        sizePolicy.setHeightForWidth(self.pbSaveGcode.sizePolicy().hasHeightForWidth())
        self.pbSaveGcode.setSizePolicy(sizePolicy)
        self.pbSaveGcode.setMinimumSize(QSize(30, 30))
        icon4 = QIcon()
        icon4.addFile(u":/icon/icons8_save_52px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSaveGcode.setIcon(icon4)
        self.pbSaveGcode.setIconSize(QSize(32, 32))
        self.pbSaveGcode.setAutoRaise(True)

        self.horizontalLayout_9.addWidget(self.pbSaveGcode)

        self.pbCreateNewGcode = QToolButton(self.frame_10)
        self.pbCreateNewGcode.setObjectName(u"pbCreateNewGcode")
        sizePolicy.setHeightForWidth(self.pbCreateNewGcode.sizePolicy().hasHeightForWidth())
        self.pbCreateNewGcode.setSizePolicy(sizePolicy)
        self.pbCreateNewGcode.setMinimumSize(QSize(30, 30))
        icon5 = QIcon()
        icon5.addFile(u":/icon/icons8_add_new_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCreateNewGcode.setIcon(icon5)
        self.pbCreateNewGcode.setIconSize(QSize(32, 32))
        self.pbCreateNewGcode.setAutoRaise(True)

        self.horizontalLayout_9.addWidget(self.pbCreateNewGcode)

        self.pbFormat = QToolButton(self.frame_10)
        self.pbFormat.setObjectName(u"pbFormat")
        icon6 = QIcon()
        icon6.addFile(u":/icon/icons8_view_details_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFormat.setIcon(icon6)
        self.pbFormat.setIconSize(QSize(32, 32))
        self.pbFormat.setAutoRaise(True)

        self.horizontalLayout_9.addWidget(self.pbFormat)

        self.horizontalSpacer_13 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_9.addItem(self.horizontalSpacer_13)

        self.cbEditGcodeEditor = QCheckBox(self.frame_10)
        self.cbEditGcodeEditor.setObjectName(u"cbEditGcodeEditor")
        font5 = QFont()
        font5.setPointSize(8)
        font5.setBold(False)
        font5.setKerning(True)
        self.cbEditGcodeEditor.setFont(font5)
        self.cbEditGcodeEditor.setIcon(icon1)
        self.cbEditGcodeEditor.setIconSize(QSize(32, 32))
        self.cbEditGcodeEditor.setChecked(True)

        self.horizontalLayout_9.addWidget(self.cbEditGcodeEditor)


        self.verticalLayout.addWidget(self.frame_10)

        self.scrollArea = QScrollArea(self.tGcodeEditor)
        self.scrollArea.setObjectName(u"scrollArea")
        self.scrollArea.setWidgetResizable(True)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 565, 1200))
        self.scrollAreaWidgetContents.setMinimumSize(QSize(450, 1200))
        self.verticalLayout_19 = QVBoxLayout(self.scrollAreaWidgetContents)
        self.verticalLayout_19.setSpacing(6)
        self.verticalLayout_19.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_19.setObjectName(u"verticalLayout_19")
        self.horizontalLayout_16 = QHBoxLayout()
        self.horizontalLayout_16.setSpacing(6)
        self.horizontalLayout_16.setObjectName(u"horizontalLayout_16")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setSpacing(6)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.label_119 = QLabel(self.scrollAreaWidgetContents)
        self.label_119.setObjectName(u"label_119")

        self.verticalLayout_2.addWidget(self.label_119)

        self.tbAddG28 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddG28.setObjectName(u"tbAddG28")

        self.verticalLayout_2.addWidget(self.tbAddG28)

        self.label_120 = QLabel(self.scrollAreaWidgetContents)
        self.label_120.setObjectName(u"label_120")

        self.verticalLayout_2.addWidget(self.label_120)

        self.tbAddG01 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddG01.setObjectName(u"tbAddG01")

        self.verticalLayout_2.addWidget(self.tbAddG01)

        self.tbAddG02 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddG02.setObjectName(u"tbAddG02")

        self.verticalLayout_2.addWidget(self.tbAddG02)

        self.label_121 = QLabel(self.scrollAreaWidgetContents)
        self.label_121.setObjectName(u"label_121")

        self.verticalLayout_2.addWidget(self.label_121)

        self.tbAddG04 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddG04.setObjectName(u"tbAddG04")

        self.verticalLayout_2.addWidget(self.tbAddG04)

        self.label_127 = QLabel(self.scrollAreaWidgetContents)
        self.label_127.setObjectName(u"label_127")

        self.verticalLayout_2.addWidget(self.label_127)

        self.tbAddM03 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddM03.setObjectName(u"tbAddM03")

        self.verticalLayout_2.addWidget(self.tbAddM03)

        self.tbAddM05 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddM05.setObjectName(u"tbAddM05")

        self.verticalLayout_2.addWidget(self.tbAddM05)

        self.label_131 = QLabel(self.scrollAreaWidgetContents)
        self.label_131.setObjectName(u"label_131")

        self.verticalLayout_2.addWidget(self.label_131)

        self.tbAddM07 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddM07.setObjectName(u"tbAddM07")

        self.verticalLayout_2.addWidget(self.tbAddM07)

        self.tbAddM08 = QToolButton(self.scrollAreaWidgetContents)
        self.tbAddM08.setObjectName(u"tbAddM08")

        self.verticalLayout_2.addWidget(self.tbAddM08)

        self.verticalSpacer_15 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer_15)


        self.horizontalLayout_16.addLayout(self.verticalLayout_2)

        self.verticalLayout_13 = QVBoxLayout()
        self.verticalLayout_13.setSpacing(6)
        self.verticalLayout_13.setObjectName(u"verticalLayout_13")
        self.pteGcodeArea = CodeEditor(self.scrollAreaWidgetContents)
        self.pteGcodeArea.setObjectName(u"pteGcodeArea")
        sizePolicy5 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.pteGcodeArea.sizePolicy().hasHeightForWidth())
        self.pteGcodeArea.setSizePolicy(sizePolicy5)
        self.pteGcodeArea.setMinimumSize(QSize(310, 500))
        self.pteGcodeArea.setFont(font5)
        self.pteGcodeArea.setStyleSheet(u"")
        self.pteGcodeArea.setHorizontalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.pteGcodeArea.setReadOnly(False)
        self.pteGcodeArea.setTextInteractionFlags(Qt.TextEditorInteraction)

        self.verticalLayout_13.addWidget(self.pteGcodeArea)

        self.fGcodePara = QFrame(self.scrollAreaWidgetContents)
        self.fGcodePara.setObjectName(u"fGcodePara")
        self.horizontalLayout_12 = QHBoxLayout(self.fGcodePara)
        self.horizontalLayout_12.setSpacing(6)
        self.horizontalLayout_12.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.label_49 = QLabel(self.fGcodePara)
        self.label_49.setObjectName(u"label_49")

        self.horizontalLayout_12.addWidget(self.label_49)

        self.lineEdit = QLineEdit(self.fGcodePara)
        self.lineEdit.setObjectName(u"lineEdit")

        self.horizontalLayout_12.addWidget(self.lineEdit)

        self.label_118 = QLabel(self.fGcodePara)
        self.label_118.setObjectName(u"label_118")

        self.horizontalLayout_12.addWidget(self.label_118)

        self.lineEdit_2 = QLineEdit(self.fGcodePara)
        self.lineEdit_2.setObjectName(u"lineEdit_2")

        self.horizontalLayout_12.addWidget(self.lineEdit_2)

        self.label_134 = QLabel(self.fGcodePara)
        self.label_134.setObjectName(u"label_134")

        self.horizontalLayout_12.addWidget(self.label_134)

        self.lineEdit_3 = QLineEdit(self.fGcodePara)
        self.lineEdit_3.setObjectName(u"lineEdit_3")

        self.horizontalLayout_12.addWidget(self.lineEdit_3)

        self.horizontalSpacer_11 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_12.addItem(self.horizontalSpacer_11)

        self.label_135 = QLabel(self.fGcodePara)
        self.label_135.setObjectName(u"label_135")

        self.horizontalLayout_12.addWidget(self.label_135)

        self.lineEdit_4 = QLineEdit(self.fGcodePara)
        self.lineEdit_4.setObjectName(u"lineEdit_4")

        self.horizontalLayout_12.addWidget(self.lineEdit_4)

        self.label_141 = QLabel(self.fGcodePara)
        self.label_141.setObjectName(u"label_141")

        self.horizontalLayout_12.addWidget(self.label_141)

        self.lineEdit_5 = QLineEdit(self.fGcodePara)
        self.lineEdit_5.setObjectName(u"lineEdit_5")

        self.horizontalLayout_12.addWidget(self.lineEdit_5)

        self.label_142 = QLabel(self.fGcodePara)
        self.label_142.setObjectName(u"label_142")

        self.horizontalLayout_12.addWidget(self.label_142)

        self.lineEdit_6 = QLineEdit(self.fGcodePara)
        self.lineEdit_6.setObjectName(u"lineEdit_6")

        self.horizontalLayout_12.addWidget(self.lineEdit_6)

        self.label_148 = QLabel(self.fGcodePara)
        self.label_148.setObjectName(u"label_148")

        self.horizontalLayout_12.addWidget(self.label_148)

        self.lineEdit_7 = QLineEdit(self.fGcodePara)
        self.lineEdit_7.setObjectName(u"lineEdit_7")

        self.horizontalLayout_12.addWidget(self.lineEdit_7)

        self.label_149 = QLabel(self.fGcodePara)
        self.label_149.setObjectName(u"label_149")

        self.horizontalLayout_12.addWidget(self.label_149)

        self.lineEdit_8 = QLineEdit(self.fGcodePara)
        self.lineEdit_8.setObjectName(u"lineEdit_8")

        self.horizontalLayout_12.addWidget(self.lineEdit_8)

        self.label_150 = QLabel(self.fGcodePara)
        self.label_150.setObjectName(u"label_150")

        self.horizontalLayout_12.addWidget(self.label_150)

        self.lineEdit_9 = QLineEdit(self.fGcodePara)
        self.lineEdit_9.setObjectName(u"lineEdit_9")

        self.horizontalLayout_12.addWidget(self.lineEdit_9)

        self.label_151 = QLabel(self.fGcodePara)
        self.label_151.setObjectName(u"label_151")

        self.horizontalLayout_12.addWidget(self.label_151)

        self.lineEdit_10 = QLineEdit(self.fGcodePara)
        self.lineEdit_10.setObjectName(u"lineEdit_10")

        self.horizontalLayout_12.addWidget(self.lineEdit_10)

        self.label_152 = QLabel(self.fGcodePara)
        self.label_152.setObjectName(u"label_152")

        self.horizontalLayout_12.addWidget(self.label_152)

        self.lineEdit_11 = QLineEdit(self.fGcodePara)
        self.lineEdit_11.setObjectName(u"lineEdit_11")

        self.horizontalLayout_12.addWidget(self.lineEdit_11)


        self.verticalLayout_13.addWidget(self.fGcodePara)


        self.horizontalLayout_16.addLayout(self.verticalLayout_13)


        self.verticalLayout_19.addLayout(self.horizontalLayout_16)

        self.tabWidget = QTabWidget(self.scrollAreaWidgetContents)
        self.tabWidget.setObjectName(u"tabWidget")
        self.tabWidget.setMinimumSize(QSize(0, 500))
        self.tab_3 = QWidget()
        self.tab_3.setObjectName(u"tab_3")
        self.verticalLayout_9 = QVBoxLayout(self.tab_3)
        self.verticalLayout_9.setSpacing(6)
        self.verticalLayout_9.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setSpacing(6)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.label_3 = QLabel(self.tab_3)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout_8.addWidget(self.label_3)

        self.tbOpenGcodePath = QToolButton(self.tab_3)
        self.tbOpenGcodePath.setObjectName(u"tbOpenGcodePath")
        icon7 = QIcon()
        icon7.addFile(u":/icon/icons8_folder_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbOpenGcodePath.setIcon(icon7)

        self.horizontalLayout_8.addWidget(self.tbOpenGcodePath)

        self.leGcodeExplorer = QLineEdit(self.tab_3)
        self.leGcodeExplorer.setObjectName(u"leGcodeExplorer")

        self.horizontalLayout_8.addWidget(self.leGcodeExplorer)


        self.verticalLayout_9.addLayout(self.horizontalLayout_8)

        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setSpacing(6)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.tbBackGcodeFolder = QToolButton(self.tab_3)
        self.tbBackGcodeFolder.setObjectName(u"tbBackGcodeFolder")
        icon8 = QIcon()
        icon8.addFile(u":/icon/icons8_back_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbBackGcodeFolder.setIcon(icon8)

        self.horizontalLayout_6.addWidget(self.tbBackGcodeFolder)

        self.tbNewGcodeFile = QToolButton(self.tab_3)
        self.tbNewGcodeFile.setObjectName(u"tbNewGcodeFile")
        self.tbNewGcodeFile.setIcon(icon5)

        self.horizontalLayout_6.addWidget(self.tbNewGcodeFile)

        self.tbRefreshExplorer = QToolButton(self.tab_3)
        self.tbRefreshExplorer.setObjectName(u"tbRefreshExplorer")
        icon9 = QIcon()
        icon9.addFile(u":/icon/icons8_refresh_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbRefreshExplorer.setIcon(icon9)

        self.horizontalLayout_6.addWidget(self.tbRefreshExplorer)

        self.tbDeleteGcodeFile = QToolButton(self.tab_3)
        self.tbDeleteGcodeFile.setObjectName(u"tbDeleteGcodeFile")
        icon10 = QIcon()
        icon10.addFile(u":/icon/icons8_close_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbDeleteGcodeFile.setIcon(icon10)

        self.horizontalLayout_6.addWidget(self.tbDeleteGcodeFile)

        self.horizontalSpacer_10 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_6.addItem(self.horizontalSpacer_10)


        self.verticalLayout_9.addLayout(self.horizontalLayout_6)

        self.tvGcodeExplorer = QTreeView(self.tab_3)
        self.tvGcodeExplorer.setObjectName(u"tvGcodeExplorer")

        self.verticalLayout_9.addWidget(self.tvGcodeExplorer)

        self.tabWidget.addTab(self.tab_3, "")
        self.tab = QWidget()
        self.tab.setObjectName(u"tab")
        self.tabWidget.addTab(self.tab, "")

        self.verticalLayout_19.addWidget(self.tabWidget)

        self.verticalSpacer_9 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_19.addItem(self.verticalSpacer_9)

        self.scrollArea.setWidget(self.scrollAreaWidgetContents)

        self.verticalLayout.addWidget(self.scrollArea)

        self.twModule.addTab(self.tGcodeEditor, "")
        self.tObjectDetecting = QWidget()
        self.tObjectDetecting.setObjectName(u"tObjectDetecting")
        self.tObjectDetecting.setStyleSheet(u"")
        self.verticalLayout_25 = QVBoxLayout(self.tObjectDetecting)
        self.verticalLayout_25.setSpacing(5)
        self.verticalLayout_25.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_25.setObjectName(u"verticalLayout_25")
        self.verticalLayout_25.setContentsMargins(0, 5, 0, 0)
        self.saObjectDetecting = QScrollArea(self.tObjectDetecting)
        self.saObjectDetecting.setObjectName(u"saObjectDetecting")
        self.saObjectDetecting.setLineWidth(1)
        self.saObjectDetecting.setWidgetResizable(True)
        self.wObjectDetecting = QWidget()
        self.wObjectDetecting.setObjectName(u"wObjectDetecting")
        self.wObjectDetecting.setGeometry(QRect(0, 0, 577, 4000))
        self.wObjectDetecting.setMinimumSize(QSize(100, 4000))
        self.wObjectDetecting.setStyleSheet(u"QWidget#wObjectDetecting\n"
"{	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"")
        self.verticalLayout_17 = QVBoxLayout(self.wObjectDetecting)
        self.verticalLayout_17.setSpacing(6)
        self.verticalLayout_17.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_17.setObjectName(u"verticalLayout_17")
        self.horizontalLayout_17 = QHBoxLayout()
        self.horizontalLayout_17.setSpacing(6)
        self.horizontalLayout_17.setObjectName(u"horizontalLayout_17")
        self.label_191 = QLabel(self.wObjectDetecting)
        self.label_191.setObjectName(u"label_191")

        self.horizontalLayout_17.addWidget(self.label_191)

        self.cbSelectedDetecting = QComboBox(self.wObjectDetecting)
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.setObjectName(u"cbSelectedDetecting")
        sizePolicy6 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Fixed)
        sizePolicy6.setHorizontalStretch(0)
        sizePolicy6.setVerticalStretch(0)
        sizePolicy6.setHeightForWidth(self.cbSelectedDetecting.sizePolicy().hasHeightForWidth())
        self.cbSelectedDetecting.setSizePolicy(sizePolicy6)

        self.horizontalLayout_17.addWidget(self.cbSelectedDetecting)

        self.horizontalSpacer_49 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_17.addItem(self.horizontalSpacer_49)


        self.verticalLayout_17.addLayout(self.horizontalLayout_17)

        self.splitter = QSplitter(self.wObjectDetecting)
        self.splitter.setObjectName(u"splitter")
        sizePolicy3.setHeightForWidth(self.splitter.sizePolicy().hasHeightForWidth())
        self.splitter.setSizePolicy(sizePolicy3)
        self.splitter.setStyleSheet(u"QSplitter::handle:vertical \n"
"{	\n"
"	background: rgb(37, 197, 255);\n"
"}")
        self.splitter.setOrientation(Qt.Vertical)
        self.splitter.setHandleWidth(10)
        self.gbImageViewer = QGroupBox(self.splitter)
        self.gbImageViewer.setObjectName(u"gbImageViewer")
        sizePolicy1.setHeightForWidth(self.gbImageViewer.sizePolicy().hasHeightForWidth())
        self.gbImageViewer.setSizePolicy(sizePolicy1)
        self.gbImageViewer.setMinimumSize(QSize(0, 0))
        self.gbImageViewer.setMaximumSize(QSize(16777215, 16777215))
        font6 = QFont()
        font6.setPointSize(10)
        font6.setBold(True)
        self.gbImageViewer.setFont(font6)
        self.gbImageViewer.setCheckable(True)
        self.vlImageViewer = QVBoxLayout(self.gbImageViewer)
        self.vlImageViewer.setSpacing(0)
        self.vlImageViewer.setContentsMargins(11, 11, 11, 11)
        self.vlImageViewer.setObjectName(u"vlImageViewer")
        self.vlImageViewer.setContentsMargins(0, 0, 0, 0)
        self.fImageViewer = QFrame(self.gbImageViewer)
        self.fImageViewer.setObjectName(u"fImageViewer")
        self.fImageViewer.setFrameShape(QFrame.StyledPanel)
        self.fImageViewer.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_30 = QHBoxLayout(self.fImageViewer)
        self.horizontalLayout_30.setSpacing(5)
        self.horizontalLayout_30.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_30.setObjectName(u"horizontalLayout_30")
        self.horizontalLayout_30.setContentsMargins(5, 5, 5, 5)
        self.frame_16 = QFrame(self.fImageViewer)
        self.frame_16.setObjectName(u"frame_16")
        self.frame_16.setMinimumSize(QSize(30, 0))
        self.frame_16.setFrameShape(QFrame.StyledPanel)
        self.frame_16.setFrameShadow(QFrame.Raised)
        self.verticalLayout_7 = QVBoxLayout(self.frame_16)
        self.verticalLayout_7.setSpacing(5)
        self.verticalLayout_7.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_7.setObjectName(u"verticalLayout_7")
        self.verticalLayout_7.setContentsMargins(0, 5, 0, 5)
        self.pbFindChessboardTool = QPushButton(self.frame_16)
        self.pbFindChessboardTool.setObjectName(u"pbFindChessboardTool")
        self.pbFindChessboardTool.setMinimumSize(QSize(30, 30))
        icon11 = QIcon()
        icon11.addFile(u":/icon/icons8_chessboard_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFindChessboardTool.setIcon(icon11)
        self.pbFindChessboardTool.setIconSize(QSize(24, 24))
        self.pbFindChessboardTool.setCheckable(True)
        self.pbFindChessboardTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbFindChessboardTool)

        self.pbWarpTool = QPushButton(self.frame_16)
        self.pbWarpTool.setObjectName(u"pbWarpTool")
        self.pbWarpTool.setMinimumSize(QSize(30, 30))
        icon12 = QIcon()
        icon12.addFile(u":/icon/icons8_opacity_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbWarpTool.setIcon(icon12)
        self.pbWarpTool.setIconSize(QSize(24, 24))
        self.pbWarpTool.setCheckable(True)
        self.pbWarpTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbWarpTool)

        self.pbAreaTool = QPushButton(self.frame_16)
        self.pbAreaTool.setObjectName(u"pbAreaTool")
        self.pbAreaTool.setMinimumSize(QSize(30, 30))
        icon13 = QIcon()
        icon13.addFile(u":/icon/icons8_rectangle_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbAreaTool.setIcon(icon13)
        self.pbAreaTool.setIconSize(QSize(24, 24))
        self.pbAreaTool.setCheckable(True)
        self.pbAreaTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbAreaTool)

        self.pbCalibPointTool = QPushButton(self.frame_16)
        self.pbCalibPointTool.setObjectName(u"pbCalibPointTool")
        self.pbCalibPointTool.setMinimumSize(QSize(30, 30))
        icon14 = QIcon()
        icon14.addFile(u":/icon/icons8_select_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCalibPointTool.setIcon(icon14)
        self.pbCalibPointTool.setIconSize(QSize(24, 24))
        self.pbCalibPointTool.setCheckable(True)
        self.pbCalibPointTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbCalibPointTool)

        self.pbMappingPointTool = QPushButton(self.frame_16)
        self.pbMappingPointTool.setObjectName(u"pbMappingPointTool")
        self.pbMappingPointTool.setMinimumSize(QSize(30, 30))
        icon15 = QIcon()
        icon15.addFile(u":/icon/icons8_target_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbMappingPointTool.setIcon(icon15)
        self.pbMappingPointTool.setIconSize(QSize(24, 24))
        self.pbMappingPointTool.setCheckable(True)
        self.pbMappingPointTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbMappingPointTool)

        self.verticalSpacer_12 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_7.addItem(self.verticalSpacer_12)


        self.horizontalLayout_30.addWidget(self.frame_16)

        self.frame_8 = QFrame(self.fImageViewer)
        self.frame_8.setObjectName(u"frame_8")
        self.frame_8.setMinimumSize(QSize(20, 0))
        self.frame_8.setFrameShape(QFrame.StyledPanel)
        self.frame_8.setFrameShadow(QFrame.Raised)
        self.verticalLayout_50 = QVBoxLayout(self.frame_8)
        self.verticalLayout_50.setSpacing(5)
        self.verticalLayout_50.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_50.setObjectName(u"verticalLayout_50")
        self.verticalLayout_50.setContentsMargins(0, 5, 0, 5)
        self.pbGetSizeTool = QToolButton(self.frame_8)
        self.pbGetSizeTool.setObjectName(u"pbGetSizeTool")
        self.pbGetSizeTool.setMinimumSize(QSize(30, 30))
        icon16 = QIcon()
        icon16.addFile(u":/icon/icons8_page_size_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbGetSizeTool.setIcon(icon16)
        self.pbGetSizeTool.setIconSize(QSize(24, 24))
        self.pbGetSizeTool.setCheckable(True)
        self.pbGetSizeTool.setAutoRaise(True)

        self.verticalLayout_50.addWidget(self.pbGetSizeTool)

        self.pbFilterTool = QPushButton(self.frame_8)
        self.pbFilterTool.setObjectName(u"pbFilterTool")
        self.pbFilterTool.setMinimumSize(QSize(30, 30))
        icon17 = QIcon()
        icon17.addFile(u":/icon/Slider 2_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFilterTool.setIcon(icon17)
        self.pbFilterTool.setIconSize(QSize(24, 24))
        self.pbFilterTool.setFlat(True)

        self.verticalLayout_50.addWidget(self.pbFilterTool)

        self.pbOpenObjectTable = QPushButton(self.frame_8)
        self.pbOpenObjectTable.setObjectName(u"pbOpenObjectTable")
        self.pbOpenObjectTable.setMinimumSize(QSize(30, 30))
        icon18 = QIcon()
        icon18.addFile(u":/icon/icons8-object-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbOpenObjectTable.setIcon(icon18)
        self.pbOpenObjectTable.setIconSize(QSize(24, 24))
        self.pbOpenObjectTable.setFlat(True)

        self.verticalLayout_50.addWidget(self.pbOpenObjectTable)

        self.pbClearObject = QPushButton(self.frame_8)
        self.pbClearObject.setObjectName(u"pbClearObject")
        self.pbClearObject.setMinimumSize(QSize(30, 30))
        icon19 = QIcon()
        icon19.addFile(u":/icon/Eraser_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbClearObject.setIcon(icon19)
        self.pbClearObject.setIconSize(QSize(24, 24))
        self.pbClearObject.setFlat(True)

        self.verticalLayout_50.addWidget(self.pbClearObject)

        self.verticalSpacer_13 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_50.addItem(self.verticalSpacer_13)


        self.horizontalLayout_30.addWidget(self.frame_8)

        self.gvImageViewer = ImageViewer(self.fImageViewer)
        self.gvImageViewer.setObjectName(u"gvImageViewer")
        sizePolicy3.setHeightForWidth(self.gvImageViewer.sizePolicy().hasHeightForWidth())
        self.gvImageViewer.setSizePolicy(sizePolicy3)

        self.horizontalLayout_30.addWidget(self.gvImageViewer)

        self.frame_17 = QFrame(self.fImageViewer)
        self.frame_17.setObjectName(u"frame_17")
        self.frame_17.setMinimumSize(QSize(30, 0))
        self.frame_17.setFrameShape(QFrame.StyledPanel)
        self.frame_17.setFrameShadow(QFrame.Raised)
        self.verticalLayout_10 = QVBoxLayout(self.frame_17)
        self.verticalLayout_10.setSpacing(5)
        self.verticalLayout_10.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_10.setObjectName(u"verticalLayout_10")
        self.verticalLayout_10.setContentsMargins(5, 5, 5, 5)
        self.label_213 = QLabel(self.frame_17)
        self.label_213.setObjectName(u"label_213")

        self.verticalLayout_10.addWidget(self.label_213)

        self.cbImageOutput = QComboBox(self.frame_17)
        self.cbImageOutput.addItem("")
        self.cbImageOutput.addItem("")
        self.cbImageOutput.addItem("")
        self.cbImageOutput.setObjectName(u"cbImageOutput")
        self.cbImageOutput.setEnabled(False)
        sizePolicy7 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Preferred)
        sizePolicy7.setHorizontalStretch(0)
        sizePolicy7.setVerticalStretch(0)
        sizePolicy7.setHeightForWidth(self.cbImageOutput.sizePolicy().hasHeightForWidth())
        self.cbImageOutput.setSizePolicy(sizePolicy7)
        self.cbImageOutput.setMinimumSize(QSize(90, 0))

        self.verticalLayout_10.addWidget(self.cbImageOutput)

        self.lbDisplayRatio_2 = QLabel(self.frame_17)
        self.lbDisplayRatio_2.setObjectName(u"lbDisplayRatio_2")

        self.verticalLayout_10.addWidget(self.lbDisplayRatio_2)

        self.lbDisplayRatio_3 = QLabel(self.frame_17)
        self.lbDisplayRatio_3.setObjectName(u"lbDisplayRatio_3")

        self.verticalLayout_10.addWidget(self.lbDisplayRatio_3)

        self.verticalSpacer_10 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_10.addItem(self.verticalSpacer_10)

        self.lbDisplayRatio = QLabel(self.frame_17)
        self.lbDisplayRatio.setObjectName(u"lbDisplayRatio")

        self.verticalLayout_10.addWidget(self.lbDisplayRatio)

        self.lbMatSize = QLabel(self.frame_17)
        self.lbMatSize.setObjectName(u"lbMatSize")

        self.verticalLayout_10.addWidget(self.lbMatSize)


        self.horizontalLayout_30.addWidget(self.frame_17)


        self.vlImageViewer.addWidget(self.fImageViewer)

        self.splitter.addWidget(self.gbImageViewer)
        self.fObjectDetectingTool = QFrame(self.splitter)
        self.fObjectDetectingTool.setObjectName(u"fObjectDetectingTool")
        sizePolicy8 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy8.setHorizontalStretch(0)
        sizePolicy8.setVerticalStretch(30)
        sizePolicy8.setHeightForWidth(self.fObjectDetectingTool.sizePolicy().hasHeightForWidth())
        self.fObjectDetectingTool.setSizePolicy(sizePolicy8)
        self.fObjectDetectingTool.setMinimumSize(QSize(0, 0))
        self.fObjectDetectingTool.setFrameShape(QFrame.StyledPanel)
        self.fObjectDetectingTool.setFrameShadow(QFrame.Raised)
        self.verticalLayout_32 = QVBoxLayout(self.fObjectDetectingTool)
        self.verticalLayout_32.setSpacing(6)
        self.verticalLayout_32.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_32.setObjectName(u"verticalLayout_32")
        self.verticalLayout_32.setContentsMargins(0, 0, 0, 0)
        self.gbImageProvider = QGroupBox(self.fObjectDetectingTool)
        self.gbImageProvider.setObjectName(u"gbImageProvider")
        self.gbImageProvider.setEnabled(True)
        self.gbImageProvider.setFont(font6)
        self.gbImageProvider.setCheckable(True)
        self.verticalLayout_39 = QVBoxLayout(self.gbImageProvider)
        self.verticalLayout_39.setSpacing(7)
        self.verticalLayout_39.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_39.setObjectName(u"verticalLayout_39")
        self.verticalLayout_39.setContentsMargins(-1, 10, -1, 11)
        self.fImageProvider = QFrame(self.gbImageProvider)
        self.fImageProvider.setObjectName(u"fImageProvider")
        self.fImageProvider.setMinimumSize(QSize(0, 100))
        self.fImageProvider.setFrameShape(QFrame.StyledPanel)
        self.fImageProvider.setFrameShadow(QFrame.Raised)
        self.verticalLayout_51 = QVBoxLayout(self.fImageProvider)
        self.verticalLayout_51.setSpacing(5)
        self.verticalLayout_51.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_51.setObjectName(u"verticalLayout_51")
        self.verticalLayout_51.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_10 = QHBoxLayout()
        self.horizontalLayout_10.setSpacing(6)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.label_176 = QLabel(self.fImageProvider)
        self.label_176.setObjectName(u"label_176")

        self.horizontalLayout_10.addWidget(self.label_176)

        self.cbSourceForImageProvider = QComboBox(self.fImageProvider)
        self.cbSourceForImageProvider.addItem("")
        self.cbSourceForImageProvider.addItem("")
        self.cbSourceForImageProvider.addItem("")
        self.cbSourceForImageProvider.addItem("")
        self.cbSourceForImageProvider.setObjectName(u"cbSourceForImageProvider")
        self.cbSourceForImageProvider.setMinimumSize(QSize(200, 0))

        self.horizontalLayout_10.addWidget(self.cbSourceForImageProvider)

        self.horizontalSpacer_44 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_10.addItem(self.horizontalSpacer_44)

        self.label_6 = QLabel(self.fImageProvider)
        self.label_6.setObjectName(u"label_6")

        self.horizontalLayout_10.addWidget(self.label_6)

        self.cbEncoderForCamera = QComboBox(self.fImageProvider)
        self.cbEncoderForCamera.addItem("")
        self.cbEncoderForCamera.addItem("")
        self.cbEncoderForCamera.addItem("")
        self.cbEncoderForCamera.addItem("")
        self.cbEncoderForCamera.setObjectName(u"cbEncoderForCamera")

        self.horizontalLayout_10.addWidget(self.cbEncoderForCamera)


        self.verticalLayout_51.addLayout(self.horizontalLayout_10)

        self.fWebcamSource = QFrame(self.fImageProvider)
        self.fWebcamSource.setObjectName(u"fWebcamSource")
        self.fWebcamSource.setMinimumSize(QSize(0, 20))
        self.fWebcamSource.setMaximumSize(QSize(16777215, 50))
        self.fWebcamSource.setStyleSheet(u"QFrame#fWebcamSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}")
        self.fWebcamSource.setFrameShape(QFrame.StyledPanel)
        self.fWebcamSource.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_11 = QHBoxLayout(self.fWebcamSource)
        self.horizontalLayout_11.setSpacing(6)
        self.horizontalLayout_11.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.horizontalLayout_11.setContentsMargins(5, 5, 5, 5)
        self.pbLoadCamera = QToolButton(self.fWebcamSource)
        self.pbLoadCamera.setObjectName(u"pbLoadCamera")
        sizePolicy.setHeightForWidth(self.pbLoadCamera.sizePolicy().hasHeightForWidth())
        self.pbLoadCamera.setSizePolicy(sizePolicy)
        self.pbLoadCamera.setMinimumSize(QSize(0, 0))
        font7 = QFont()
        font7.setPointSize(8)
        font7.setBold(False)
        self.pbLoadCamera.setFont(font7)
        icon20 = QIcon()
        icon20.addFile(u":/icon/webcam.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLoadCamera.setIcon(icon20)
        self.pbLoadCamera.setIconSize(QSize(30, 30))
        self.pbLoadCamera.setCheckable(True)
        self.pbLoadCamera.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbLoadCamera.setAutoRaise(True)

        self.horizontalLayout_11.addWidget(self.pbLoadCamera)

        self.horizontalSpacer_45 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_11.addItem(self.horizontalSpacer_45)


        self.verticalLayout_51.addWidget(self.fWebcamSource)

        self.fImageSource = QFrame(self.fImageProvider)
        self.fImageSource.setObjectName(u"fImageSource")
        self.fImageSource.setMinimumSize(QSize(0, 20))
        self.fImageSource.setMaximumSize(QSize(16777215, 50))
        self.fImageSource.setStyleSheet(u"QFrame#fImageSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}")
        self.fImageSource.setFrameShape(QFrame.StyledPanel)
        self.fImageSource.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_27 = QHBoxLayout(self.fImageSource)
        self.horizontalLayout_27.setSpacing(6)
        self.horizontalLayout_27.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_27.setObjectName(u"horizontalLayout_27")
        self.horizontalLayout_27.setContentsMargins(5, 5, 5, 5)
        self.pbLoadTestImage = QToolButton(self.fImageSource)
        self.pbLoadTestImage.setObjectName(u"pbLoadTestImage")
        sizePolicy.setHeightForWidth(self.pbLoadTestImage.sizePolicy().hasHeightForWidth())
        self.pbLoadTestImage.setSizePolicy(sizePolicy)
        self.pbLoadTestImage.setMinimumSize(QSize(0, 0))
        self.pbLoadTestImage.setMaximumSize(QSize(120, 16777215))
        font8 = QFont()
        font8.setPointSize(8)
        self.pbLoadTestImage.setFont(font8)
        icon21 = QIcon()
        icon21.addFile(u":/icon/icons8_image_30px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLoadTestImage.setIcon(icon21)
        self.pbLoadTestImage.setIconSize(QSize(30, 30))
        self.pbLoadTestImage.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbLoadTestImage.setAutoRaise(True)

        self.horizontalLayout_27.addWidget(self.pbLoadTestImage)

        self.horizontalSpacer_64 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_27.addItem(self.horizontalSpacer_64)


        self.verticalLayout_51.addWidget(self.fImageSource)

        self.fCameraPara = QFrame(self.fImageProvider)
        self.fCameraPara.setObjectName(u"fCameraPara")
        self.fCameraPara.setMinimumSize(QSize(0, 20))
        self.fCameraPara.setMaximumSize(QSize(16777215, 50))
        self.fCameraPara.setStyleSheet(u"QFrame#fPluginSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}")
        self.fCameraPara.setFrameShape(QFrame.StyledPanel)
        self.fCameraPara.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_28 = QHBoxLayout(self.fCameraPara)
        self.horizontalLayout_28.setSpacing(6)
        self.horizontalLayout_28.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_28.setObjectName(u"horizontalLayout_28")
        self.horizontalLayout_28.setContentsMargins(5, 5, 5, 5)
        self.label_178 = QLabel(self.fCameraPara)
        self.label_178.setObjectName(u"label_178")
        self.label_178.setFont(font8)
        self.label_178.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_28.addWidget(self.label_178)

        self.leImageWidth = QLineEdit(self.fCameraPara)
        self.leImageWidth.setObjectName(u"leImageWidth")
        sizePolicy9 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)
        sizePolicy9.setHorizontalStretch(0)
        sizePolicy9.setVerticalStretch(0)
        sizePolicy9.setHeightForWidth(self.leImageWidth.sizePolicy().hasHeightForWidth())
        self.leImageWidth.setSizePolicy(sizePolicy9)
        self.leImageWidth.setMinimumSize(QSize(0, 10))
        self.leImageWidth.setMaximumSize(QSize(40, 25))
        self.leImageWidth.setFont(font8)
        self.leImageWidth.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_28.addWidget(self.leImageWidth)

        self.label_179 = QLabel(self.fCameraPara)
        self.label_179.setObjectName(u"label_179")
        self.label_179.setFont(font8)
        self.label_179.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_28.addWidget(self.label_179)

        self.leImageHeight = QLineEdit(self.fCameraPara)
        self.leImageHeight.setObjectName(u"leImageHeight")
        sizePolicy9.setHeightForWidth(self.leImageHeight.sizePolicy().hasHeightForWidth())
        self.leImageHeight.setSizePolicy(sizePolicy9)
        self.leImageHeight.setMinimumSize(QSize(0, 10))
        self.leImageHeight.setMaximumSize(QSize(40, 25))
        self.leImageHeight.setFont(font8)
        self.leImageHeight.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_28.addWidget(self.leImageHeight)

        self.label_73 = QLabel(self.fCameraPara)
        self.label_73.setObjectName(u"label_73")
        self.label_73.setMaximumSize(QSize(50, 16777215))
        self.label_73.setFont(font8)

        self.horizontalLayout_28.addWidget(self.label_73)

        self.leCaptureInterval = QLineEdit(self.fCameraPara)
        self.leCaptureInterval.setObjectName(u"leCaptureInterval")
        sizePolicy9.setHeightForWidth(self.leCaptureInterval.sizePolicy().hasHeightForWidth())
        self.leCaptureInterval.setSizePolicy(sizePolicy9)
        self.leCaptureInterval.setMinimumSize(QSize(0, 10))
        self.leCaptureInterval.setMaximumSize(QSize(40, 25))
        self.leCaptureInterval.setFont(font8)
        self.leCaptureInterval.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_28.addWidget(self.leCaptureInterval)

        self.label_128 = QLabel(self.fCameraPara)
        self.label_128.setObjectName(u"label_128")
        self.label_128.setMaximumSize(QSize(50, 16777215))
        self.label_128.setFont(font8)

        self.horizontalLayout_28.addWidget(self.label_128)

        self.pbStartAcquisition = QToolButton(self.fCameraPara)
        self.pbStartAcquisition.setObjectName(u"pbStartAcquisition")
        self.pbStartAcquisition.setEnabled(True)
        sizePolicy.setHeightForWidth(self.pbStartAcquisition.sizePolicy().hasHeightForWidth())
        self.pbStartAcquisition.setSizePolicy(sizePolicy)
        self.pbStartAcquisition.setMinimumSize(QSize(0, 0))
        self.pbStartAcquisition.setFont(font8)
        icon22 = QIcon()
        icon22.addFile(u":/icon/icons8-play-48.png", QSize(), QIcon.Normal, QIcon.Off)
        icon22.addFile(u":/icon/icons8-pause-48.png", QSize(), QIcon.Normal, QIcon.On)
        icon22.addFile(u"icon/icons8-play-48.png", QSize(), QIcon.Selected, QIcon.Off)
        self.pbStartAcquisition.setIcon(icon22)
        self.pbStartAcquisition.setIconSize(QSize(30, 30))
        self.pbStartAcquisition.setCheckable(True)
        self.pbStartAcquisition.setChecked(False)
        self.pbStartAcquisition.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbStartAcquisition.setAutoRaise(True)

        self.horizontalLayout_28.addWidget(self.pbStartAcquisition)

        self.pbCapture = QToolButton(self.fCameraPara)
        self.pbCapture.setObjectName(u"pbCapture")
        self.pbCapture.setEnabled(True)
        self.pbCapture.setMinimumSize(QSize(0, 0))
        self.pbCapture.setFont(font8)
        icon23 = QIcon()
        icon23.addFile(u":/icon/icons8-screenshot-40.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCapture.setIcon(icon23)
        self.pbCapture.setIconSize(QSize(30, 30))
        self.pbCapture.setCheckable(False)
        self.pbCapture.setChecked(False)
        self.pbCapture.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbCapture.setAutoRaise(True)

        self.horizontalLayout_28.addWidget(self.pbCapture)

        self.lbCameraState = QLabel(self.fCameraPara)
        self.lbCameraState.setObjectName(u"lbCameraState")
        self.lbCameraState.setEnabled(True)
        self.lbCameraState.setMaximumSize(QSize(20, 20))
        self.lbCameraState.setPixmap(QPixmap(u"icon/icons8-connection-status-on-48.png"))
        self.lbCameraState.setScaledContents(True)

        self.horizontalLayout_28.addWidget(self.lbCameraState)

        self.horizontalSpacer_65 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_28.addItem(self.horizontalSpacer_65)


        self.verticalLayout_51.addWidget(self.fCameraPara)


        self.verticalLayout_39.addWidget(self.fImageProvider)


        self.verticalLayout_32.addWidget(self.gbImageProvider)

        self.gbCameraCalibration = QGroupBox(self.fObjectDetectingTool)
        self.gbCameraCalibration.setObjectName(u"gbCameraCalibration")
        self.gbCameraCalibration.setFont(font6)
        self.gbCameraCalibration.setCheckable(True)
        self.gbCameraCalibration.setChecked(True)
        self.verticalLayout_29 = QVBoxLayout(self.gbCameraCalibration)
        self.verticalLayout_29.setSpacing(6)
        self.verticalLayout_29.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_29.setObjectName(u"verticalLayout_29")
        self.fCameraCalibrationFrame = QFrame(self.gbCameraCalibration)
        self.fCameraCalibrationFrame.setObjectName(u"fCameraCalibrationFrame")
        self.fCameraCalibrationFrame.setMinimumSize(QSize(0, 200))
        self.fCameraCalibrationFrame.setFrameShape(QFrame.StyledPanel)
        self.fCameraCalibrationFrame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_52 = QVBoxLayout(self.fCameraCalibrationFrame)
        self.verticalLayout_52.setSpacing(6)
        self.verticalLayout_52.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_52.setObjectName(u"verticalLayout_52")
        self.pbCalibStep1 = QPushButton(self.fCameraCalibrationFrame)
        self.pbCalibStep1.setObjectName(u"pbCalibStep1")
        self.pbCalibStep1.setStyleSheet(u"QPushButton\n"
"{\n"
"	height: 25px;\n"
"	text-align: left;\n"
"	padding-left: 50px;\n"
"}")
        self.pbCalibStep1.setCheckable(True)
        self.pbCalibStep1.setChecked(True)

        self.verticalLayout_52.addWidget(self.pbCalibStep1)

        self.fCalibStep1 = QFrame(self.fCameraCalibrationFrame)
        self.fCalibStep1.setObjectName(u"fCalibStep1")
        self.gridLayout_27 = QGridLayout(self.fCalibStep1)
        self.gridLayout_27.setSpacing(6)
        self.gridLayout_27.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_27.setObjectName(u"gridLayout_27")
        self.label_109 = QLabel(self.fCalibStep1)
        self.label_109.setObjectName(u"label_109")
        self.label_109.setMinimumSize(QSize(0, 25))

        self.gridLayout_27.addWidget(self.label_109, 0, 0, 1, 2)

        self.label_110 = QLabel(self.fCalibStep1)
        self.label_110.setObjectName(u"label_110")
        self.label_110.setMinimumSize(QSize(0, 25))

        self.gridLayout_27.addWidget(self.label_110, 1, 0, 1, 1)


        self.verticalLayout_52.addWidget(self.fCalibStep1)

        self.pbCalibStep2 = QPushButton(self.fCameraCalibrationFrame)
        self.pbCalibStep2.setObjectName(u"pbCalibStep2")
        self.pbCalibStep2.setStyleSheet(u"QPushButton\n"
"{\n"
"	height: 25px;\n"
"	text-align: left;\n"
"	padding-left: 50px;\n"
"}")
        self.pbCalibStep2.setCheckable(True)
        self.pbCalibStep2.setChecked(True)

        self.verticalLayout_52.addWidget(self.pbCalibStep2)

        self.fCalibStep2 = QFrame(self.fCameraCalibrationFrame)
        self.fCalibStep2.setObjectName(u"fCalibStep2")
        self.gridLayout_26 = QGridLayout(self.fCalibStep2)
        self.gridLayout_26.setSpacing(6)
        self.gridLayout_26.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_26.setObjectName(u"gridLayout_26")
        self.leRealityPoint2X = QLineEdit(self.fCalibStep2)
        self.leRealityPoint2X.setObjectName(u"leRealityPoint2X")
        sizePolicy.setHeightForWidth(self.leRealityPoint2X.sizePolicy().hasHeightForWidth())
        self.leRealityPoint2X.setSizePolicy(sizePolicy)
        self.leRealityPoint2X.setMinimumSize(QSize(0, 0))
        self.leRealityPoint2X.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint2X, 5, 2, 1, 1)

        self.leRealityPoint1Y = QLineEdit(self.fCalibStep2)
        self.leRealityPoint1Y.setObjectName(u"leRealityPoint1Y")
        sizePolicy.setHeightForWidth(self.leRealityPoint1Y.sizePolicy().hasHeightForWidth())
        self.leRealityPoint1Y.setSizePolicy(sizePolicy)
        self.leRealityPoint1Y.setMinimumSize(QSize(0, 0))
        self.leRealityPoint1Y.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint1Y, 4, 4, 1, 1)

        self.pbCalibPoint1 = QPushButton(self.fCalibStep2)
        self.pbCalibPoint1.setObjectName(u"pbCalibPoint1")
        self.pbCalibPoint1.setFlat(True)

        self.gridLayout_26.addWidget(self.pbCalibPoint1, 4, 1, 1, 1)

        self.label_140 = QLabel(self.fCalibStep2)
        self.label_140.setObjectName(u"label_140")
        self.label_140.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_140, 5, 5, 1, 1)

        self.pbImageMapping = QPushButton(self.fCalibStep2)
        self.pbImageMapping.setObjectName(u"pbImageMapping")
        self.pbImageMapping.setMinimumSize(QSize(0, 45))
        self.pbImageMapping.setMaximumSize(QSize(200, 16777215))
        self.pbImageMapping.setAutoFillBackground(False)
        icon24 = QIcon()
        icon24.addFile(u":/icon/icons8_grid_3_48px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbImageMapping.setIcon(icon24)
        self.pbImageMapping.setIconSize(QSize(30, 30))
        self.pbImageMapping.setCheckable(True)
        self.pbImageMapping.setChecked(False)
        self.pbImageMapping.setAutoDefault(False)
        self.pbImageMapping.setFlat(False)

        self.gridLayout_26.addWidget(self.pbImageMapping, 6, 0, 1, 3)

        self.leRealityPoint2Y = QLineEdit(self.fCalibStep2)
        self.leRealityPoint2Y.setObjectName(u"leRealityPoint2Y")
        sizePolicy.setHeightForWidth(self.leRealityPoint2Y.sizePolicy().hasHeightForWidth())
        self.leRealityPoint2Y.setSizePolicy(sizePolicy)
        self.leRealityPoint2Y.setMinimumSize(QSize(0, 0))
        self.leRealityPoint2Y.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint2Y, 5, 4, 1, 1)

        self.leRealityPoint1X = QLineEdit(self.fCalibStep2)
        self.leRealityPoint1X.setObjectName(u"leRealityPoint1X")
        sizePolicy.setHeightForWidth(self.leRealityPoint1X.sizePolicy().hasHeightForWidth())
        self.leRealityPoint1X.setSizePolicy(sizePolicy)
        self.leRealityPoint1X.setMinimumSize(QSize(0, 0))
        self.leRealityPoint1X.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint1X, 4, 2, 1, 1)

        self.label_133 = QLabel(self.fCalibStep2)
        self.label_133.setObjectName(u"label_133")
        self.label_133.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_133, 4, 5, 1, 1)

        self.label_139 = QLabel(self.fCalibStep2)
        self.label_139.setObjectName(u"label_139")
        self.label_139.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_139, 5, 3, 1, 1)

        self.label_39 = QLabel(self.fCalibStep2)
        self.label_39.setObjectName(u"label_39")
        self.label_39.setAlignment(Qt.AlignCenter)

        self.gridLayout_26.addWidget(self.label_39, 3, 4, 1, 1)

        self.label_132 = QLabel(self.fCalibStep2)
        self.label_132.setObjectName(u"label_132")
        self.label_132.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_132, 4, 3, 1, 1)

        self.label_38 = QLabel(self.fCalibStep2)
        self.label_38.setObjectName(u"label_38")
        self.label_38.setMinimumSize(QSize(0, 0))
        font9 = QFont()
        font9.setBold(False)
        font9.setItalic(False)
        font9.setUnderline(False)
        font9.setStrikeOut(False)
        font9.setKerning(True)
        self.label_38.setFont(font9)
        self.label_38.setMouseTracking(True)
        self.label_38.setTextFormat(Qt.AutoText)
        self.label_38.setAlignment(Qt.AlignCenter)

        self.gridLayout_26.addWidget(self.label_38, 3, 2, 1, 1)

        self.pbCalibPoint2 = QPushButton(self.fCalibStep2)
        self.pbCalibPoint2.setObjectName(u"pbCalibPoint2")
        self.pbCalibPoint2.setFlat(True)

        self.gridLayout_26.addWidget(self.pbCalibPoint2, 5, 1, 1, 1)


        self.verticalLayout_52.addWidget(self.fCalibStep2)


        self.verticalLayout_29.addWidget(self.fCameraCalibrationFrame)


        self.verticalLayout_32.addWidget(self.gbCameraCalibration)

        self.gbCameraObject = QGroupBox(self.fObjectDetectingTool)
        self.gbCameraObject.setObjectName(u"gbCameraObject")
        self.gbCameraObject.setFont(font6)
        self.gbCameraObject.setCheckable(True)
        self.verticalLayout_40 = QVBoxLayout(self.gbCameraObject)
        self.verticalLayout_40.setSpacing(6)
        self.verticalLayout_40.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_40.setObjectName(u"verticalLayout_40")
        self.verticalLayout_40.setContentsMargins(-1, 10, -1, -1)
        self.fVisionObjectFrame = QFrame(self.gbCameraObject)
        self.fVisionObjectFrame.setObjectName(u"fVisionObjectFrame")
        self.fVisionObjectFrame.setMinimumSize(QSize(0, 0))
        self.verticalLayout_31 = QVBoxLayout(self.fVisionObjectFrame)
        self.verticalLayout_31.setSpacing(6)
        self.verticalLayout_31.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_31.setObjectName(u"verticalLayout_31")
        self.verticalLayout_31.setContentsMargins(10, 10, 10, 10)
        self.horizontalLayout_29 = QHBoxLayout()
        self.horizontalLayout_29.setSpacing(6)
        self.horizontalLayout_29.setObjectName(u"horizontalLayout_29")
        self.horizontalSpacer_43 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_29.addItem(self.horizontalSpacer_43)


        self.verticalLayout_31.addLayout(self.horizontalLayout_29)

        self.frame_13 = QFrame(self.fVisionObjectFrame)
        self.frame_13.setObjectName(u"frame_13")
        self.frame_13.setMinimumSize(QSize(0, 0))
        self.frame_13.setFrameShape(QFrame.StyledPanel)
        self.frame_13.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_26 = QHBoxLayout(self.frame_13)
        self.horizontalLayout_26.setSpacing(10)
        self.horizontalLayout_26.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_26.setObjectName(u"horizontalLayout_26")
        self.horizontalLayout_26.setContentsMargins(0, 0, 0, 0)
        self.label_126 = QLabel(self.frame_13)
        self.label_126.setObjectName(u"label_126")

        self.horizontalLayout_26.addWidget(self.label_126)

        self.cbDetectingAlgorithm = QComboBox(self.frame_13)
        self.cbDetectingAlgorithm.addItem("")
        self.cbDetectingAlgorithm.addItem("")
        self.cbDetectingAlgorithm.addItem("")
        self.cbDetectingAlgorithm.setObjectName(u"cbDetectingAlgorithm")

        self.horizontalLayout_26.addWidget(self.cbDetectingAlgorithm)

        self.horizontalSpacer_6 = QSpacerItem(239, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_26.addItem(self.horizontalSpacer_6)

        self.label_45 = QLabel(self.frame_13)
        self.label_45.setObjectName(u"label_45")

        self.horizontalLayout_26.addWidget(self.label_45)

        self.leObjectOverlay = QLineEdit(self.frame_13)
        self.leObjectOverlay.setObjectName(u"leObjectOverlay")
        sizePolicy10 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum)
        sizePolicy10.setHorizontalStretch(0)
        sizePolicy10.setVerticalStretch(0)
        sizePolicy10.setHeightForWidth(self.leObjectOverlay.sizePolicy().hasHeightForWidth())
        self.leObjectOverlay.setSizePolicy(sizePolicy10)
        self.leObjectOverlay.setMinimumSize(QSize(0, 30))
        self.leObjectOverlay.setMaximumSize(QSize(50, 16777215))

        self.horizontalLayout_26.addWidget(self.leObjectOverlay)


        self.verticalLayout_31.addWidget(self.frame_13)

        self.fBlobPanel = QFrame(self.fVisionObjectFrame)
        self.fBlobPanel.setObjectName(u"fBlobPanel")
        self.fBlobPanel.setMinimumSize(QSize(0, 0))
        self.fBlobPanel.setStyleSheet(u"QFrame#fBlobPanel\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}")
        self.fBlobPanel.setFrameShape(QFrame.StyledPanel)
        self.fBlobPanel.setFrameShadow(QFrame.Raised)
        self.gridLayout_14 = QGridLayout(self.fBlobPanel)
        self.gridLayout_14.setSpacing(6)
        self.gridLayout_14.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_14.setObjectName(u"gridLayout_14")
        self.leMaxWRec = QLineEdit(self.fBlobPanel)
        self.leMaxWRec.setObjectName(u"leMaxWRec")
        sizePolicy10.setHeightForWidth(self.leMaxWRec.sizePolicy().hasHeightForWidth())
        self.leMaxWRec.setSizePolicy(sizePolicy10)
        self.leMaxWRec.setMinimumSize(QSize(0, 20))
        self.leMaxWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMaxWRec, 3, 8, 1, 1)

        self.label_172 = QLabel(self.fBlobPanel)
        self.label_172.setObjectName(u"label_172")
        self.label_172.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_172, 3, 5, 1, 1)

        self.leMinLRec = QLineEdit(self.fBlobPanel)
        self.leMinLRec.setObjectName(u"leMinLRec")
        sizePolicy10.setHeightForWidth(self.leMinLRec.sizePolicy().hasHeightForWidth())
        self.leMinLRec.setSizePolicy(sizePolicy10)
        self.leMinLRec.setMinimumSize(QSize(0, 20))
        self.leMinLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMinLRec, 4, 6, 1, 1)

        self.leMaxLRec = QLineEdit(self.fBlobPanel)
        self.leMaxLRec.setObjectName(u"leMaxLRec")
        sizePolicy10.setHeightForWidth(self.leMaxLRec.sizePolicy().hasHeightForWidth())
        self.leMaxLRec.setSizePolicy(sizePolicy10)
        self.leMaxLRec.setMinimumSize(QSize(0, 20))
        self.leMaxLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMaxLRec, 4, 8, 1, 1)

        self.leWRec = QLineEdit(self.fBlobPanel)
        self.leWRec.setObjectName(u"leWRec")
        sizePolicy10.setHeightForWidth(self.leWRec.sizePolicy().hasHeightForWidth())
        self.leWRec.setSizePolicy(sizePolicy10)
        self.leWRec.setMinimumSize(QSize(0, 30))
        self.leWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leWRec, 3, 2, 1, 1)

        self.label_173 = QLabel(self.fBlobPanel)
        self.label_173.setObjectName(u"label_173")
        self.label_173.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_173, 3, 7, 1, 1)

        self.leLRec = QLineEdit(self.fBlobPanel)
        self.leLRec.setObjectName(u"leLRec")
        sizePolicy10.setHeightForWidth(self.leLRec.sizePolicy().hasHeightForWidth())
        self.leLRec.setSizePolicy(sizePolicy10)
        self.leLRec.setMinimumSize(QSize(0, 30))
        self.leLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leLRec, 4, 2, 1, 1)

        self.label_175 = QLabel(self.fBlobPanel)
        self.label_175.setObjectName(u"label_175")
        self.label_175.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_175, 4, 7, 1, 1)

        self.label_43 = QLabel(self.fBlobPanel)
        self.label_43.setObjectName(u"label_43")

        self.gridLayout_14.addWidget(self.label_43, 4, 1, 1, 1)

        self.label_163 = QLabel(self.fBlobPanel)
        self.label_163.setObjectName(u"label_163")

        self.gridLayout_14.addWidget(self.label_163, 0, 1, 1, 1)

        self.label_54 = QLabel(self.fBlobPanel)
        self.label_54.setObjectName(u"label_54")

        self.gridLayout_14.addWidget(self.label_54, 3, 3, 1, 1)

        self.leMinWRec = QLineEdit(self.fBlobPanel)
        self.leMinWRec.setObjectName(u"leMinWRec")
        sizePolicy10.setHeightForWidth(self.leMinWRec.sizePolicy().hasHeightForWidth())
        self.leMinWRec.setSizePolicy(sizePolicy10)
        self.leMinWRec.setMinimumSize(QSize(0, 20))
        self.leMinWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMinWRec, 3, 6, 1, 1)

        self.label_55 = QLabel(self.fBlobPanel)
        self.label_55.setObjectName(u"label_55")

        self.gridLayout_14.addWidget(self.label_55, 4, 3, 1, 1)

        self.cbObjectType = QComboBox(self.fBlobPanel)
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.setObjectName(u"cbObjectType")
        self.cbObjectType.setEnabled(True)
        self.cbObjectType.setMinimumSize(QSize(0, 30))

        self.gridLayout_14.addWidget(self.cbObjectType, 0, 2, 1, 1)

        self.label_42 = QLabel(self.fBlobPanel)
        self.label_42.setObjectName(u"label_42")

        self.gridLayout_14.addWidget(self.label_42, 3, 1, 1, 1)

        self.horizontalSpacer_66 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_14.addItem(self.horizontalSpacer_66, 3, 9, 1, 1)

        self.label_174 = QLabel(self.fBlobPanel)
        self.label_174.setObjectName(u"label_174")
        self.label_174.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_174, 4, 5, 1, 1)


        self.verticalLayout_31.addWidget(self.fBlobPanel)

        self.fExternalScriptPanel = QFrame(self.fVisionObjectFrame)
        self.fExternalScriptPanel.setObjectName(u"fExternalScriptPanel")
        self.fExternalScriptPanel.setMinimumSize(QSize(0, 50))
        self.fExternalScriptPanel.setStyleSheet(u"QFrame#fExternalScriptPanel\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}")
        self.fExternalScriptPanel.setFrameShape(QFrame.StyledPanel)
        self.fExternalScriptPanel.setFrameShadow(QFrame.Raised)
        self.gridLayout_28 = QGridLayout(self.fExternalScriptPanel)
        self.gridLayout_28.setSpacing(6)
        self.gridLayout_28.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_28.setObjectName(u"gridLayout_28")
        self.pbRunExternalScript = QPushButton(self.fExternalScriptPanel)
        self.pbRunExternalScript.setObjectName(u"pbRunExternalScript")
        sizePolicy10.setHeightForWidth(self.pbRunExternalScript.sizePolicy().hasHeightForWidth())
        self.pbRunExternalScript.setSizePolicy(sizePolicy10)
        self.pbRunExternalScript.setMaximumSize(QSize(30, 16777215))
        icon25 = QIcon()
        icon25.addFile(u":/icon/icons8_play_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon25.addFile(u":/icon/Pause_96px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbRunExternalScript.setIcon(icon25)
        self.pbRunExternalScript.setCheckable(True)

        self.gridLayout_28.addWidget(self.pbRunExternalScript, 0, 3, 1, 1)

        self.cbImageSource = QComboBox(self.fExternalScriptPanel)
        self.cbImageSource.addItem("")
        self.cbImageSource.addItem("")
        self.cbImageSource.addItem("")
        self.cbImageSource.setObjectName(u"cbImageSource")

        self.gridLayout_28.addWidget(self.cbImageSource, 1, 1, 1, 1)

        self.label_180 = QLabel(self.fExternalScriptPanel)
        self.label_180.setObjectName(u"label_180")

        self.gridLayout_28.addWidget(self.label_180, 2, 0, 1, 1)

        self.label_183 = QLabel(self.fExternalScriptPanel)
        self.label_183.setObjectName(u"label_183")

        self.gridLayout_28.addWidget(self.label_183, 2, 3, 1, 2)

        self.label_187 = QLabel(self.fExternalScriptPanel)
        self.label_187.setObjectName(u"label_187")

        self.gridLayout_28.addWidget(self.label_187, 4, 1, 1, 3)

        self.label_185 = QLabel(self.fExternalScriptPanel)
        self.label_185.setObjectName(u"label_185")

        self.gridLayout_28.addWidget(self.label_185, 4, 0, 1, 1)

        self.label_146 = QLabel(self.fExternalScriptPanel)
        self.label_146.setObjectName(u"label_146")

        self.gridLayout_28.addWidget(self.label_146, 1, 0, 1, 1)

        self.pbExternalScriptOpen = QPushButton(self.fExternalScriptPanel)
        self.pbExternalScriptOpen.setObjectName(u"pbExternalScriptOpen")
        sizePolicy10.setHeightForWidth(self.pbExternalScriptOpen.sizePolicy().hasHeightForWidth())
        self.pbExternalScriptOpen.setSizePolicy(sizePolicy10)
        self.pbExternalScriptOpen.setMaximumSize(QSize(30, 16777215))
        icon26 = QIcon()
        icon26.addFile(u":/icon/icons8_folder_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbExternalScriptOpen.setIcon(icon26)

        self.gridLayout_28.addWidget(self.pbExternalScriptOpen, 0, 2, 1, 1)

        self.label_184 = QLabel(self.fExternalScriptPanel)
        self.label_184.setObjectName(u"label_184")

        self.gridLayout_28.addWidget(self.label_184, 3, 0, 1, 1)

        self.label_145 = QLabel(self.fExternalScriptPanel)
        self.label_145.setObjectName(u"label_145")

        self.gridLayout_28.addWidget(self.label_145, 0, 0, 1, 1)

        self.pbExternalScriptHelp = QPushButton(self.fExternalScriptPanel)
        self.pbExternalScriptHelp.setObjectName(u"pbExternalScriptHelp")
        sizePolicy10.setHeightForWidth(self.pbExternalScriptHelp.sizePolicy().hasHeightForWidth())
        self.pbExternalScriptHelp.setSizePolicy(sizePolicy10)
        self.pbExternalScriptHelp.setMaximumSize(QSize(30, 16777215))

        self.gridLayout_28.addWidget(self.pbExternalScriptHelp, 0, 4, 1, 1)

        self.label_186 = QLabel(self.fExternalScriptPanel)
        self.label_186.setObjectName(u"label_186")

        self.gridLayout_28.addWidget(self.label_186, 3, 1, 1, 1)

        self.label_182 = QLabel(self.fExternalScriptPanel)
        self.label_182.setObjectName(u"label_182")

        self.gridLayout_28.addWidget(self.label_182, 2, 2, 1, 1)

        self.label_181 = QLabel(self.fExternalScriptPanel)
        self.label_181.setObjectName(u"label_181")

        self.gridLayout_28.addWidget(self.label_181, 2, 1, 1, 1)

        self.lePythonUrl = QLineEdit(self.fExternalScriptPanel)
        self.lePythonUrl.setObjectName(u"lePythonUrl")
        sizePolicy9.setHeightForWidth(self.lePythonUrl.sizePolicy().hasHeightForWidth())
        self.lePythonUrl.setSizePolicy(sizePolicy9)
        self.lePythonUrl.setMinimumSize(QSize(0, 30))
        self.lePythonUrl.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_28.addWidget(self.lePythonUrl, 0, 1, 1, 1)

        self.pbOpenScriptExample = QPushButton(self.fExternalScriptPanel)
        self.pbOpenScriptExample.setObjectName(u"pbOpenScriptExample")

        self.gridLayout_28.addWidget(self.pbOpenScriptExample, 5, 0, 1, 1)


        self.verticalLayout_31.addWidget(self.fExternalScriptPanel)

        self.fCirclePanel = QFrame(self.fVisionObjectFrame)
        self.fCirclePanel.setObjectName(u"fCirclePanel")
        self.fCirclePanel.setMinimumSize(QSize(0, 200))
        self.fCirclePanel.setMaximumSize(QSize(16777215, 16777215))
        self.fCirclePanel.setStyleSheet(u"QFrame#fCirclePanel\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}")
        self.fCirclePanel.setFrameShape(QFrame.StyledPanel)
        self.fCirclePanel.setFrameShadow(QFrame.Raised)
        self.gridLayout_29 = QGridLayout(self.fCirclePanel)
        self.gridLayout_29.setSpacing(6)
        self.gridLayout_29.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_29.setObjectName(u"gridLayout_29")
        self.leCenterThreshold = QLineEdit(self.fCirclePanel)
        self.leCenterThreshold.setObjectName(u"leCenterThreshold")
        sizePolicy10.setHeightForWidth(self.leCenterThreshold.sizePolicy().hasHeightForWidth())
        self.leCenterThreshold.setSizePolicy(sizePolicy10)
        self.leCenterThreshold.setMinimumSize(QSize(0, 30))
        self.leCenterThreshold.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_29.addWidget(self.leCenterThreshold, 3, 1, 1, 2)

        self.horizontalSpacer_8 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_29.addItem(self.horizontalSpacer_8, 2, 4, 1, 1)

        self.leEdgeThreshold = QLineEdit(self.fCirclePanel)
        self.leEdgeThreshold.setObjectName(u"leEdgeThreshold")
        sizePolicy10.setHeightForWidth(self.leEdgeThreshold.sizePolicy().hasHeightForWidth())
        self.leEdgeThreshold.setSizePolicy(sizePolicy10)
        self.leEdgeThreshold.setMinimumSize(QSize(0, 30))
        self.leEdgeThreshold.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_29.addWidget(self.leEdgeThreshold, 2, 1, 1, 2)

        self.label_193 = QLabel(self.fCirclePanel)
        self.label_193.setObjectName(u"label_193")

        self.gridLayout_29.addWidget(self.label_193, 4, 3, 1, 1)

        self.label_190 = QLabel(self.fCirclePanel)
        self.label_190.setObjectName(u"label_190")

        self.gridLayout_29.addWidget(self.label_190, 3, 0, 1, 1)

        self.label_192 = QLabel(self.fCirclePanel)
        self.label_192.setObjectName(u"label_192")

        self.gridLayout_29.addWidget(self.label_192, 4, 0, 1, 1)

        self.leMaxRadius = QLineEdit(self.fCirclePanel)
        self.leMaxRadius.setObjectName(u"leMaxRadius")
        sizePolicy10.setHeightForWidth(self.leMaxRadius.sizePolicy().hasHeightForWidth())
        self.leMaxRadius.setSizePolicy(sizePolicy10)
        self.leMaxRadius.setMinimumSize(QSize(0, 30))
        self.leMaxRadius.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_29.addWidget(self.leMaxRadius, 5, 1, 1, 1)

        self.label_194 = QLabel(self.fCirclePanel)
        self.label_194.setObjectName(u"label_194")

        self.gridLayout_29.addWidget(self.label_194, 5, 0, 1, 1)

        self.label_195 = QLabel(self.fCirclePanel)
        self.label_195.setObjectName(u"label_195")

        self.gridLayout_29.addWidget(self.label_195, 5, 3, 1, 1)

        self.leMinRadius = QLineEdit(self.fCirclePanel)
        self.leMinRadius.setObjectName(u"leMinRadius")
        sizePolicy10.setHeightForWidth(self.leMinRadius.sizePolicy().hasHeightForWidth())
        self.leMinRadius.setSizePolicy(sizePolicy10)
        self.leMinRadius.setMinimumSize(QSize(0, 30))
        self.leMinRadius.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_29.addWidget(self.leMinRadius, 4, 1, 1, 1)

        self.label_188 = QLabel(self.fCirclePanel)
        self.label_188.setObjectName(u"label_188")

        self.gridLayout_29.addWidget(self.label_188, 2, 0, 1, 1)


        self.verticalLayout_31.addWidget(self.fCirclePanel)


        self.verticalLayout_40.addWidget(self.fVisionObjectFrame)

        self.gridLayout_33 = QGridLayout()
        self.gridLayout_33.setSpacing(6)
        self.gridLayout_33.setObjectName(u"gridLayout_33")
        self.gridLayout_12 = QGridLayout()
        self.gridLayout_12.setSpacing(6)
        self.gridLayout_12.setObjectName(u"gridLayout_12")
        self.gridLayout_12.setContentsMargins(6, -1, -1, -1)

        self.gridLayout_33.addLayout(self.gridLayout_12, 1, 0, 2, 1)


        self.verticalLayout_40.addLayout(self.gridLayout_33)


        self.verticalLayout_32.addWidget(self.gbCameraObject)

        self.gbCameraVariable = QGroupBox(self.fObjectDetectingTool)
        self.gbCameraVariable.setObjectName(u"gbCameraVariable")
        self.gbCameraVariable.setFont(font6)
        self.gbCameraVariable.setStyleSheet(u"")
        self.gbCameraVariable.setFlat(False)
        self.gbCameraVariable.setCheckable(True)
        self.verticalLayout_34 = QVBoxLayout(self.gbCameraVariable)
        self.verticalLayout_34.setSpacing(6)
        self.verticalLayout_34.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_34.setObjectName(u"verticalLayout_34")
        self.horizontalLayout_31 = QHBoxLayout()
        self.horizontalLayout_31.setSpacing(6)
        self.horizontalLayout_31.setObjectName(u"horizontalLayout_31")
        self.label_196 = QLabel(self.gbCameraVariable)
        self.label_196.setObjectName(u"label_196")

        self.horizontalLayout_31.addWidget(self.label_196)

        self.leDetectingObjectListName = QLineEdit(self.gbCameraVariable)
        self.leDetectingObjectListName.setObjectName(u"leDetectingObjectListName")

        self.horizontalLayout_31.addWidget(self.leDetectingObjectListName)

        self.horizontalSpacer_50 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_31.addItem(self.horizontalSpacer_50)


        self.verticalLayout_34.addLayout(self.horizontalLayout_31)

        self.fVisionVariableFrame = QFrame(self.gbCameraVariable)
        self.fVisionVariableFrame.setObjectName(u"fVisionVariableFrame")
        self.fVisionVariableFrame.setMinimumSize(QSize(0, 0))
        self.fVisionVariableFrame.setFrameShape(QFrame.StyledPanel)
        self.fVisionVariableFrame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_35 = QVBoxLayout(self.fVisionVariableFrame)
        self.verticalLayout_35.setSpacing(6)
        self.verticalLayout_35.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_35.setObjectName(u"verticalLayout_35")
        self.verticalLayout_35.setContentsMargins(0, 0, 0, 0)
        self.horizontalLayout_25 = QHBoxLayout()
        self.horizontalLayout_25.setSpacing(6)
        self.horizontalLayout_25.setObjectName(u"horizontalLayout_25")
        self.pbViewDataObjects = QPushButton(self.fVisionVariableFrame)
        self.pbViewDataObjects.setObjectName(u"pbViewDataObjects")
        self.pbViewDataObjects.setMinimumSize(QSize(150, 30))
        self.pbViewDataObjects.setMaximumSize(QSize(200, 16777215))
        self.pbViewDataObjects.setStyleSheet(u"")
        self.pbViewDataObjects.setIcon(icon18)

        self.horizontalLayout_25.addWidget(self.pbViewDataObjects)

        self.pbClearDetectObjects = QPushButton(self.fVisionVariableFrame)
        self.pbClearDetectObjects.setObjectName(u"pbClearDetectObjects")
        self.pbClearDetectObjects.setMinimumSize(QSize(150, 30))
        self.pbClearDetectObjects.setMaximumSize(QSize(200, 16777215))
        self.pbClearDetectObjects.setIcon(icon19)

        self.horizontalLayout_25.addWidget(self.pbClearDetectObjects)

        self.horizontalSpacer_9 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_25.addItem(self.horizontalSpacer_9)


        self.verticalLayout_35.addLayout(self.horizontalLayout_25)

        self.gridLayout_15 = QGridLayout()
        self.gridLayout_15.setSpacing(6)
        self.gridLayout_15.setObjectName(u"gridLayout_15")
        self.lbTrackingObjectNumber = QLabel(self.fVisionVariableFrame)
        self.lbTrackingObjectNumber.setObjectName(u"lbTrackingObjectNumber")
        self.lbTrackingObjectNumber.setFont(font5)

        self.gridLayout_15.addWidget(self.lbTrackingObjectNumber, 1, 1, 1, 1)

        self.label_155 = QLabel(self.fVisionVariableFrame)
        self.label_155.setObjectName(u"label_155")

        self.gridLayout_15.addWidget(self.label_155, 3, 3, 1, 1)

        self.label_56 = QLabel(self.fVisionVariableFrame)
        self.label_56.setObjectName(u"label_56")

        self.gridLayout_15.addWidget(self.label_56, 3, 1, 1, 1)

        self.label_50 = QLabel(self.fVisionVariableFrame)
        self.label_50.setObjectName(u"label_50")
        self.label_50.setFont(font5)

        self.gridLayout_15.addWidget(self.label_50, 2, 0, 1, 1)

        self.leLimitMinX = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMinX.setObjectName(u"leLimitMinX")

        self.gridLayout_15.addWidget(self.leLimitMinX, 3, 2, 1, 1)

        self.horizontalSpacer_7 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_15.addItem(self.horizontalSpacer_7, 1, 3, 1, 1)

        self.label_44 = QLabel(self.fVisionVariableFrame)
        self.label_44.setObjectName(u"label_44")

        self.gridLayout_15.addWidget(self.label_44, 3, 0, 1, 1)

        self.lbVisibleObjectNumber = QLabel(self.fVisionVariableFrame)
        self.lbVisibleObjectNumber.setObjectName(u"lbVisibleObjectNumber")
        self.lbVisibleObjectNumber.setFont(font5)

        self.gridLayout_15.addWidget(self.lbVisibleObjectNumber, 2, 1, 1, 1)

        self.label_48 = QLabel(self.fVisionVariableFrame)
        self.label_48.setObjectName(u"label_48")
        self.label_48.setFont(font5)

        self.gridLayout_15.addWidget(self.label_48, 1, 0, 1, 1)

        self.leLimitMaxX = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMaxX.setObjectName(u"leLimitMaxX")

        self.gridLayout_15.addWidget(self.leLimitMaxX, 3, 4, 1, 1)

        self.label_156 = QLabel(self.fVisionVariableFrame)
        self.label_156.setObjectName(u"label_156")

        self.gridLayout_15.addWidget(self.label_156, 4, 1, 1, 1)

        self.label_157 = QLabel(self.fVisionVariableFrame)
        self.label_157.setObjectName(u"label_157")

        self.gridLayout_15.addWidget(self.label_157, 4, 3, 1, 1)

        self.leLimitMinY = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMinY.setObjectName(u"leLimitMinY")

        self.gridLayout_15.addWidget(self.leLimitMinY, 4, 2, 1, 1)

        self.leLimitMaxY = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMaxY.setObjectName(u"leLimitMaxY")

        self.gridLayout_15.addWidget(self.leLimitMaxY, 4, 4, 1, 1)


        self.verticalLayout_35.addLayout(self.gridLayout_15)


        self.verticalLayout_34.addWidget(self.fVisionVariableFrame)


        self.verticalLayout_32.addWidget(self.gbCameraVariable)

        self.verticalSpacer_11 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_32.addItem(self.verticalSpacer_11)

        self.splitter.addWidget(self.fObjectDetectingTool)

        self.verticalLayout_17.addWidget(self.splitter)

        self.saObjectDetecting.setWidget(self.wObjectDetecting)

        self.verticalLayout_25.addWidget(self.saObjectDetecting)

        self.twModule.addTab(self.tObjectDetecting, "")
        self.tPointTool = QWidget()
        self.tPointTool.setObjectName(u"tPointTool")
        self.verticalLayout_14 = QVBoxLayout(self.tPointTool)
        self.verticalLayout_14.setSpacing(6)
        self.verticalLayout_14.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_14.setObjectName(u"verticalLayout_14")
        self.saObjectDetecting_2 = QScrollArea(self.tPointTool)
        self.saObjectDetecting_2.setObjectName(u"saObjectDetecting_2")
        self.saObjectDetecting_2.setLineWidth(1)
        self.saObjectDetecting_2.setWidgetResizable(True)
        self.wObjectDetecting_2 = QWidget()
        self.wObjectDetecting_2.setObjectName(u"wObjectDetecting_2")
        self.wObjectDetecting_2.setGeometry(QRect(0, 0, 565, 4000))
        self.wObjectDetecting_2.setMinimumSize(QSize(100, 4000))
        self.wObjectDetecting_2.setStyleSheet(u"QWidget#wObjectDetecting\n"
"{	\n"
"	background-color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"")
        self.verticalLayout_18 = QVBoxLayout(self.wObjectDetecting_2)
        self.verticalLayout_18.setSpacing(6)
        self.verticalLayout_18.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_18.setObjectName(u"verticalLayout_18")
        self.splitter_3 = QSplitter(self.wObjectDetecting_2)
        self.splitter_3.setObjectName(u"splitter_3")
        sizePolicy3.setHeightForWidth(self.splitter_3.sizePolicy().hasHeightForWidth())
        self.splitter_3.setSizePolicy(sizePolicy3)
        self.splitter_3.setStyleSheet(u"QSplitter::handle:vertical \n"
"{	\n"
"	background: rgb(37, 197, 255);\n"
"}")
        self.splitter_3.setOrientation(Qt.Vertical)
        self.splitter_3.setHandleWidth(10)
        self.fObjectDetectingTool_2 = QFrame(self.splitter_3)
        self.fObjectDetectingTool_2.setObjectName(u"fObjectDetectingTool_2")
        sizePolicy8.setHeightForWidth(self.fObjectDetectingTool_2.sizePolicy().hasHeightForWidth())
        self.fObjectDetectingTool_2.setSizePolicy(sizePolicy8)
        self.fObjectDetectingTool_2.setMinimumSize(QSize(0, 0))
        self.fObjectDetectingTool_2.setFrameShape(QFrame.StyledPanel)
        self.fObjectDetectingTool_2.setFrameShadow(QFrame.Raised)
        self.verticalLayout_59 = QVBoxLayout(self.fObjectDetectingTool_2)
        self.verticalLayout_59.setSpacing(6)
        self.verticalLayout_59.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_59.setObjectName(u"verticalLayout_59")
        self.verticalLayout_59.setContentsMargins(0, 0, 0, 0)
        self.gbImageProvider_2 = QGroupBox(self.fObjectDetectingTool_2)
        self.gbImageProvider_2.setObjectName(u"gbImageProvider_2")
        self.gbImageProvider_2.setEnabled(True)
        self.gbImageProvider_2.setFont(font6)
        self.gbImageProvider_2.setCheckable(True)
        self.verticalLayout_60 = QVBoxLayout(self.gbImageProvider_2)
        self.verticalLayout_60.setSpacing(7)
        self.verticalLayout_60.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_60.setObjectName(u"verticalLayout_60")
        self.verticalLayout_60.setContentsMargins(-1, 10, -1, 11)
        self.frame_15 = QFrame(self.gbImageProvider_2)
        self.frame_15.setObjectName(u"frame_15")
        self.frame_15.setMinimumSize(QSize(0, 0))
        self.frame_15.setFrameShape(QFrame.StyledPanel)
        self.frame_15.setFrameShadow(QFrame.Raised)
        self.gridLayout_16 = QGridLayout(self.frame_15)
        self.gridLayout_16.setSpacing(6)
        self.gridLayout_16.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_16.setObjectName(u"gridLayout_16")
        self.leDeviationAngle = QLineEdit(self.frame_15)
        self.leDeviationAngle.setObjectName(u"leDeviationAngle")

        self.gridLayout_16.addWidget(self.leDeviationAngle, 4, 2, 1, 1)

        self.label_164 = QLabel(self.frame_15)
        self.label_164.setObjectName(u"label_164")

        self.gridLayout_16.addWidget(self.label_164, 2, 0, 1, 1)

        self.cbTrackingEncoderSource = QComboBox(self.frame_15)
        self.cbTrackingEncoderSource.addItem("")
        self.cbTrackingEncoderSource.addItem("")
        self.cbTrackingEncoderSource.addItem("")
        self.cbTrackingEncoderSource.setObjectName(u"cbTrackingEncoderSource")
        sizePolicy.setHeightForWidth(self.cbTrackingEncoderSource.sizePolicy().hasHeightForWidth())
        self.cbTrackingEncoderSource.setSizePolicy(sizePolicy)
        self.cbTrackingEncoderSource.setMinimumSize(QSize(0, 0))

        self.gridLayout_16.addWidget(self.cbTrackingEncoderSource, 2, 2, 1, 1)

        self.label_144 = QLabel(self.frame_15)
        self.label_144.setObjectName(u"label_144")

        self.gridLayout_16.addWidget(self.label_144, 1, 0, 1, 1)

        self.horizontalSpacer_24 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_16.addItem(self.horizontalSpacer_24, 1, 6, 1, 1)

        self.cbReverseEncoderValue = QCheckBox(self.frame_15)
        self.cbReverseEncoderValue.setObjectName(u"cbReverseEncoderValue")

        self.gridLayout_16.addWidget(self.cbReverseEncoderValue, 2, 6, 1, 1)

        self.label_167 = QLabel(self.frame_15)
        self.label_167.setObjectName(u"label_167")

        self.gridLayout_16.addWidget(self.label_167, 3, 0, 1, 1)

        self.cbSelectedTracking = QComboBox(self.frame_15)
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.setObjectName(u"cbSelectedTracking")
        sizePolicy6.setHeightForWidth(self.cbSelectedTracking.sizePolicy().hasHeightForWidth())
        self.cbSelectedTracking.setSizePolicy(sizePolicy6)

        self.gridLayout_16.addWidget(self.cbSelectedTracking, 0, 2, 1, 1)

        self.cbTrackingDirection = QComboBox(self.frame_15)
        self.cbTrackingDirection.addItem("")
        self.cbTrackingDirection.addItem("")
        self.cbTrackingDirection.setObjectName(u"cbTrackingDirection")
        self.cbTrackingDirection.setMinimumSize(QSize(0, 0))

        self.gridLayout_16.addWidget(self.cbTrackingDirection, 3, 2, 1, 1)

        self.label_168 = QLabel(self.frame_15)
        self.label_168.setObjectName(u"label_168")

        self.gridLayout_16.addWidget(self.label_168, 4, 0, 1, 1)

        self.label_160 = QLabel(self.frame_15)
        self.label_160.setObjectName(u"label_160")

        self.gridLayout_16.addWidget(self.label_160, 0, 0, 1, 1)

        self.label_169 = QLabel(self.frame_15)
        self.label_169.setObjectName(u"label_169")

        self.gridLayout_16.addWidget(self.label_169, 4, 3, 1, 1)

        self.leSelectedTrackingObjectList = QLineEdit(self.frame_15)
        self.leSelectedTrackingObjectList.setObjectName(u"leSelectedTrackingObjectList")

        self.gridLayout_16.addWidget(self.leSelectedTrackingObjectList, 1, 2, 1, 1)


        self.verticalLayout_60.addWidget(self.frame_15)

        self.gbCameraCalibration_3 = QGroupBox(self.gbImageProvider_2)
        self.gbCameraCalibration_3.setObjectName(u"gbCameraCalibration_3")
        self.gbCameraCalibration_3.setFont(font6)
        self.gbCameraCalibration_3.setCheckable(True)
        self.gbCameraCalibration_3.setChecked(True)
        self.verticalLayout_63 = QVBoxLayout(self.gbCameraCalibration_3)
        self.verticalLayout_63.setSpacing(6)
        self.verticalLayout_63.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_63.setObjectName(u"verticalLayout_63")
        self.frame_19 = QFrame(self.gbCameraCalibration_3)
        self.frame_19.setObjectName(u"frame_19")
        self.frame_19.setMinimumSize(QSize(0, 0))
        self.frame_19.setFrameShape(QFrame.StyledPanel)
        self.frame_19.setFrameShadow(QFrame.Raised)
        self.gridLayout_44 = QGridLayout(self.frame_19)
        self.gridLayout_44.setSpacing(6)
        self.gridLayout_44.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_44.setObjectName(u"gridLayout_44")
        self.leAnglePoint2X = QLineEdit(self.frame_19)
        self.leAnglePoint2X.setObjectName(u"leAnglePoint2X")

        self.gridLayout_44.addWidget(self.leAnglePoint2X, 3, 3, 1, 1)

        self.pbCalculateAngle = QPushButton(self.frame_19)
        self.pbCalculateAngle.setObjectName(u"pbCalculateAngle")

        self.gridLayout_44.addWidget(self.pbCalculateAngle, 4, 2, 1, 1)

        self.leAnglePoint1Y = QLineEdit(self.frame_19)
        self.leAnglePoint1Y.setObjectName(u"leAnglePoint1Y")

        self.gridLayout_44.addWidget(self.leAnglePoint1Y, 1, 5, 1, 1)

        self.leAnglePoint2Y = QLineEdit(self.frame_19)
        self.leAnglePoint2Y.setObjectName(u"leAnglePoint2Y")

        self.gridLayout_44.addWidget(self.leAnglePoint2Y, 3, 5, 1, 1)

        self.label_189 = QLabel(self.frame_19)
        self.label_189.setObjectName(u"label_189")
        self.label_189.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_189, 0, 3, 1, 1)

        self.label_206 = QLabel(self.frame_19)
        self.label_206.setObjectName(u"label_206")
        self.label_206.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_206, 0, 5, 1, 1)

        self.leAngleResult = QLineEdit(self.frame_19)
        self.leAngleResult.setObjectName(u"leAngleResult")

        self.gridLayout_44.addWidget(self.leAngleResult, 5, 3, 1, 1)

        self.leAnglePoint1X = QLineEdit(self.frame_19)
        self.leAnglePoint1X.setObjectName(u"leAnglePoint1X")

        self.gridLayout_44.addWidget(self.leAnglePoint1X, 1, 3, 1, 1)

        self.label_224 = QLabel(self.frame_19)
        self.label_224.setObjectName(u"label_224")

        self.gridLayout_44.addWidget(self.label_224, 5, 2, 1, 1)

        self.pbAnglePoint1 = QPushButton(self.frame_19)
        self.pbAnglePoint1.setObjectName(u"pbAnglePoint1")
        self.pbAnglePoint1.setFlat(True)

        self.gridLayout_44.addWidget(self.pbAnglePoint1, 1, 2, 1, 1)

        self.pbAnglePoint2 = QPushButton(self.frame_19)
        self.pbAnglePoint2.setObjectName(u"pbAnglePoint2")
        self.pbAnglePoint2.setFlat(True)

        self.gridLayout_44.addWidget(self.pbAnglePoint2, 3, 2, 1, 1)


        self.verticalLayout_63.addWidget(self.frame_19)


        self.verticalLayout_60.addWidget(self.gbCameraCalibration_3)

        self.gbCameraCalibration_4 = QGroupBox(self.gbImageProvider_2)
        self.gbCameraCalibration_4.setObjectName(u"gbCameraCalibration_4")
        self.gbCameraCalibration_4.setFont(font6)
        self.gbCameraCalibration_4.setCheckable(True)
        self.gbCameraCalibration_4.setChecked(True)
        self.verticalLayout_67 = QVBoxLayout(self.gbCameraCalibration_4)
        self.verticalLayout_67.setSpacing(6)
        self.verticalLayout_67.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_67.setObjectName(u"verticalLayout_67")
        self.frame_22 = QFrame(self.gbCameraCalibration_4)
        self.frame_22.setObjectName(u"frame_22")
        self.frame_22.setMinimumSize(QSize(0, 0))
        self.frame_22.setFrameShape(QFrame.StyledPanel)
        self.frame_22.setFrameShadow(QFrame.Raised)
        self.gridLayout_45 = QGridLayout(self.frame_22)
        self.gridLayout_45.setSpacing(6)
        self.gridLayout_45.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_45.setObjectName(u"gridLayout_45")
        self.leAnglePoint2X_2 = QLineEdit(self.frame_22)
        self.leAnglePoint2X_2.setObjectName(u"leAnglePoint2X_2")

        self.gridLayout_45.addWidget(self.leAnglePoint2X_2, 3, 2, 1, 1)

        self.leAnglePoint2Y_2 = QLineEdit(self.frame_22)
        self.leAnglePoint2Y_2.setObjectName(u"leAnglePoint2Y_2")

        self.gridLayout_45.addWidget(self.leAnglePoint2Y_2, 3, 4, 1, 1)

        self.leAngleResult_2 = QLineEdit(self.frame_22)
        self.leAngleResult_2.setObjectName(u"leAngleResult_2")

        self.gridLayout_45.addWidget(self.leAngleResult_2, 3, 1, 1, 1)

        self.label_226 = QLabel(self.frame_22)
        self.label_226.setObjectName(u"label_226")
        self.label_226.setAlignment(Qt.AlignCenter)

        self.gridLayout_45.addWidget(self.label_226, 2, 1, 1, 1)

        self.label_227 = QLabel(self.frame_22)
        self.label_227.setObjectName(u"label_227")
        self.label_227.setAlignment(Qt.AlignCenter)

        self.gridLayout_45.addWidget(self.label_227, 2, 2, 1, 1)

        self.label_228 = QLabel(self.frame_22)
        self.label_228.setObjectName(u"label_228")
        self.label_228.setAlignment(Qt.AlignCenter)

        self.gridLayout_45.addWidget(self.label_228, 2, 4, 1, 1)

        self.leAngleResult_3 = QLineEdit(self.frame_22)
        self.leAngleResult_3.setObjectName(u"leAngleResult_3")

        self.gridLayout_45.addWidget(self.leAngleResult_3, 3, 0, 1, 1)

        self.label_229 = QLabel(self.frame_22)
        self.label_229.setObjectName(u"label_229")
        self.label_229.setAlignment(Qt.AlignCenter)

        self.gridLayout_45.addWidget(self.label_229, 2, 0, 1, 1)

        self.leAnglePoint1X_2 = QLineEdit(self.frame_22)
        self.leAnglePoint1X_2.setObjectName(u"leAnglePoint1X_2")

        self.gridLayout_45.addWidget(self.leAnglePoint1X_2, 1, 0, 1, 1)

        self.label_197 = QLabel(self.frame_22)
        self.label_197.setObjectName(u"label_197")
        self.label_197.setAlignment(Qt.AlignCenter)

        self.gridLayout_45.addWidget(self.label_197, 0, 0, 1, 1)

        self.label_209 = QLabel(self.frame_22)
        self.label_209.setObjectName(u"label_209")
        self.label_209.setAlignment(Qt.AlignCenter)

        self.gridLayout_45.addWidget(self.label_209, 0, 1, 1, 1)

        self.pbCalculateAngle_2 = QPushButton(self.frame_22)
        self.pbCalculateAngle_2.setObjectName(u"pbCalculateAngle_2")

        self.gridLayout_45.addWidget(self.pbCalculateAngle_2, 1, 2, 1, 1)

        self.leAnglePoint1Y_2 = QLineEdit(self.frame_22)
        self.leAnglePoint1Y_2.setObjectName(u"leAnglePoint1Y_2")

        self.gridLayout_45.addWidget(self.leAnglePoint1Y_2, 1, 1, 1, 1)


        self.verticalLayout_67.addWidget(self.frame_22)


        self.verticalLayout_60.addWidget(self.gbCameraCalibration_4)


        self.verticalLayout_59.addWidget(self.gbImageProvider_2)

        self.gbCameraCalibration_2 = QGroupBox(self.fObjectDetectingTool_2)
        self.gbCameraCalibration_2.setObjectName(u"gbCameraCalibration_2")
        self.gbCameraCalibration_2.setFont(font6)
        self.gbCameraCalibration_2.setCheckable(True)
        self.gbCameraCalibration_2.setChecked(True)
        self.verticalLayout_62 = QVBoxLayout(self.gbCameraCalibration_2)
        self.verticalLayout_62.setSpacing(6)
        self.verticalLayout_62.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_62.setObjectName(u"verticalLayout_62")
        self.pbAddVariablePoint_2 = QPushButton(self.gbCameraCalibration_2)
        self.pbAddVariablePoint_2.setObjectName(u"pbAddVariablePoint_2")

        self.verticalLayout_62.addWidget(self.pbAddVariablePoint_2)

        self.frame_18 = QFrame(self.gbCameraCalibration_2)
        self.frame_18.setObjectName(u"frame_18")
        self.frame_18.setMinimumSize(QSize(0, 0))
        self.frame_18.setFrameShape(QFrame.StyledPanel)
        self.frame_18.setFrameShadow(QFrame.Raised)
        self.gridLayout_41 = QGridLayout(self.frame_18)
        self.gridLayout_41.setSpacing(6)
        self.gridLayout_41.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_41.setObjectName(u"gridLayout_41")
        self.label_202 = QLabel(self.frame_18)
        self.label_202.setObjectName(u"label_202")
        self.label_202.setAlignment(Qt.AlignCenter)

        self.gridLayout_41.addWidget(self.label_202, 0, 6, 1, 1)

        self.label_203 = QLabel(self.frame_18)
        self.label_203.setObjectName(u"label_203")

        self.gridLayout_41.addWidget(self.label_203, 1, 3, 1, 1)

        self.label_204 = QLabel(self.frame_18)
        self.label_204.setObjectName(u"label_204")

        self.gridLayout_41.addWidget(self.label_204, 3, 3, 1, 1)

        self.leSourcePoint1X = QLineEdit(self.frame_18)
        self.leSourcePoint1X.setObjectName(u"leSourcePoint1X")

        self.gridLayout_41.addWidget(self.leSourcePoint1X, 1, 4, 1, 1)

        self.label_166 = QLabel(self.frame_18)
        self.label_166.setObjectName(u"label_166")

        self.gridLayout_41.addWidget(self.label_166, 1, 2, 1, 1)

        self.label_200 = QLabel(self.frame_18)
        self.label_200.setObjectName(u"label_200")

        self.gridLayout_41.addWidget(self.label_200, 3, 2, 1, 1)

        self.label_165 = QLabel(self.frame_18)
        self.label_165.setObjectName(u"label_165")

        self.gridLayout_41.addWidget(self.label_165, 1, 0, 1, 1)

        self.label_201 = QLabel(self.frame_18)
        self.label_201.setObjectName(u"label_201")

        self.gridLayout_41.addWidget(self.label_201, 2, 3, 1, 1)

        self.leMatrix1Name = QLineEdit(self.frame_18)
        self.leMatrix1Name.setObjectName(u"leMatrix1Name")

        self.gridLayout_41.addWidget(self.leMatrix1Name, 1, 1, 1, 1)

        self.label_177 = QLabel(self.frame_18)
        self.label_177.setObjectName(u"label_177")
        self.label_177.setAlignment(Qt.AlignCenter)

        self.gridLayout_41.addWidget(self.label_177, 0, 4, 1, 1)

        self.leSourcePoint2Y = QLineEdit(self.frame_18)
        self.leSourcePoint2Y.setObjectName(u"leSourcePoint2Y")

        self.gridLayout_41.addWidget(self.leSourcePoint2Y, 2, 6, 1, 1)

        self.leSourcePoint2X = QLineEdit(self.frame_18)
        self.leSourcePoint2X.setObjectName(u"leSourcePoint2X")

        self.gridLayout_41.addWidget(self.leSourcePoint2X, 2, 4, 1, 1)

        self.leSourcePoint1Y = QLineEdit(self.frame_18)
        self.leSourcePoint1Y.setObjectName(u"leSourcePoint1Y")

        self.gridLayout_41.addWidget(self.leSourcePoint1Y, 1, 6, 1, 1)

        self.label_205 = QLabel(self.frame_18)
        self.label_205.setObjectName(u"label_205")

        self.gridLayout_41.addWidget(self.label_205, 4, 3, 1, 1)

        self.leDestinationPoint1X = QLineEdit(self.frame_18)
        self.leDestinationPoint1X.setObjectName(u"leDestinationPoint1X")

        self.gridLayout_41.addWidget(self.leDestinationPoint1X, 3, 4, 1, 1)

        self.leDestinationPoint2X = QLineEdit(self.frame_18)
        self.leDestinationPoint2X.setObjectName(u"leDestinationPoint2X")

        self.gridLayout_41.addWidget(self.leDestinationPoint2X, 4, 4, 1, 1)

        self.leDestinationPoint1Y = QLineEdit(self.frame_18)
        self.leDestinationPoint1Y.setObjectName(u"leDestinationPoint1Y")

        self.gridLayout_41.addWidget(self.leDestinationPoint1Y, 3, 6, 1, 1)

        self.leDestinationPoint2Y = QLineEdit(self.frame_18)
        self.leDestinationPoint2Y.setObjectName(u"leDestinationPoint2Y")

        self.gridLayout_41.addWidget(self.leDestinationPoint2Y, 4, 6, 1, 1)

        self.pbCalculateMappingMatrixTool = QPushButton(self.frame_18)
        self.pbCalculateMappingMatrixTool.setObjectName(u"pbCalculateMappingMatrixTool")

        self.gridLayout_41.addWidget(self.pbCalculateMappingMatrixTool, 2, 1, 1, 1)


        self.verticalLayout_62.addWidget(self.frame_18)


        self.verticalLayout_59.addWidget(self.gbCameraCalibration_2)

        self.gbCameraObject_2 = QGroupBox(self.fObjectDetectingTool_2)
        self.gbCameraObject_2.setObjectName(u"gbCameraObject_2")
        self.gbCameraObject_2.setFont(font6)
        self.gbCameraObject_2.setCheckable(True)
        self.verticalLayout_64 = QVBoxLayout(self.gbCameraObject_2)
        self.verticalLayout_64.setSpacing(6)
        self.verticalLayout_64.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_64.setObjectName(u"verticalLayout_64")
        self.verticalLayout_64.setContentsMargins(-1, 10, -1, -1)
        self.pbAddVariablePoint = QPushButton(self.gbCameraObject_2)
        self.pbAddVariablePoint.setObjectName(u"pbAddVariablePoint")

        self.verticalLayout_64.addWidget(self.pbAddVariablePoint)

        self.frame_14 = QFrame(self.gbCameraObject_2)
        self.frame_14.setObjectName(u"frame_14")
        self.frame_14.setMinimumSize(QSize(0, 0))
        self.frame_14.setFrameShape(QFrame.StyledPanel)
        self.frame_14.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_5 = QHBoxLayout(self.frame_14)
        self.horizontalLayout_5.setSpacing(6)
        self.horizontalLayout_5.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.label_136 = QLabel(self.frame_14)
        self.label_136.setObjectName(u"label_136")

        self.horizontalLayout_5.addWidget(self.label_136)

        self.lePoint1Name = QLineEdit(self.frame_14)
        self.lePoint1Name.setObjectName(u"lePoint1Name")

        self.horizontalLayout_5.addWidget(self.lePoint1Name)

        self.label_137 = QLabel(self.frame_14)
        self.label_137.setObjectName(u"label_137")

        self.horizontalLayout_5.addWidget(self.label_137)

        self.lePoint1X = QLineEdit(self.frame_14)
        self.lePoint1X.setObjectName(u"lePoint1X")

        self.horizontalLayout_5.addWidget(self.lePoint1X)

        self.label_138 = QLabel(self.frame_14)
        self.label_138.setObjectName(u"label_138")

        self.horizontalLayout_5.addWidget(self.label_138)

        self.lePoint1Y = QLineEdit(self.frame_14)
        self.lePoint1Y.setObjectName(u"lePoint1Y")

        self.horizontalLayout_5.addWidget(self.lePoint1Y)

        self.label_143 = QLabel(self.frame_14)
        self.label_143.setObjectName(u"label_143")

        self.horizontalLayout_5.addWidget(self.label_143)

        self.lePoint1Z = QLineEdit(self.frame_14)
        self.lePoint1Z.setObjectName(u"lePoint1Z")

        self.horizontalLayout_5.addWidget(self.lePoint1Z)


        self.verticalLayout_64.addWidget(self.frame_14)

        self.gbCameraObject_3 = QGroupBox(self.gbCameraObject_2)
        self.gbCameraObject_3.setObjectName(u"gbCameraObject_3")
        self.gbCameraObject_3.setFont(font6)
        self.gbCameraObject_3.setCheckable(True)
        self.verticalLayout_65 = QVBoxLayout(self.gbCameraObject_3)
        self.verticalLayout_65.setSpacing(6)
        self.verticalLayout_65.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_65.setObjectName(u"verticalLayout_65")
        self.verticalLayout_65.setContentsMargins(-1, 10, -1, -1)
        self.pbAddVariablePoint_3 = QPushButton(self.gbCameraObject_3)
        self.pbAddVariablePoint_3.setObjectName(u"pbAddVariablePoint_3")

        self.verticalLayout_65.addWidget(self.pbAddVariablePoint_3)

        self.frame_20 = QFrame(self.gbCameraObject_3)
        self.frame_20.setObjectName(u"frame_20")
        self.frame_20.setMinimumSize(QSize(0, 0))
        self.frame_20.setFrameShape(QFrame.StyledPanel)
        self.frame_20.setFrameShadow(QFrame.Raised)
        self.gridLayout_42 = QGridLayout(self.frame_20)
        self.gridLayout_42.setSpacing(6)
        self.gridLayout_42.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_42.setObjectName(u"gridLayout_42")
        self.label_210 = QLabel(self.frame_20)
        self.label_210.setObjectName(u"label_210")
        self.label_210.setAlignment(Qt.AlignCenter)

        self.gridLayout_42.addWidget(self.label_210, 0, 5, 1, 1)

        self.leMPoint3Y = QLineEdit(self.frame_20)
        self.leMPoint3Y.setObjectName(u"leMPoint3Y")

        self.gridLayout_42.addWidget(self.leMPoint3Y, 3, 5, 1, 1)

        self.label_218 = QLabel(self.frame_20)
        self.label_218.setObjectName(u"label_218")
        self.label_218.setAlignment(Qt.AlignCenter)

        self.gridLayout_42.addWidget(self.label_218, 0, 3, 1, 1)

        self.label_211 = QLabel(self.frame_20)
        self.label_211.setObjectName(u"label_211")

        self.gridLayout_42.addWidget(self.label_211, 1, 2, 1, 1)

        self.leMPoint1Y = QLineEdit(self.frame_20)
        self.leMPoint1Y.setObjectName(u"leMPoint1Y")

        self.gridLayout_42.addWidget(self.leMPoint1Y, 1, 5, 1, 1)

        self.label_212 = QLabel(self.frame_20)
        self.label_212.setObjectName(u"label_212")

        self.gridLayout_42.addWidget(self.label_212, 3, 2, 1, 1)

        self.label_216 = QLabel(self.frame_20)
        self.label_216.setObjectName(u"label_216")

        self.gridLayout_42.addWidget(self.label_216, 1, 0, 1, 1)

        self.lePointMatrixName = QLineEdit(self.frame_20)
        self.lePointMatrixName.setObjectName(u"lePointMatrixName")

        self.gridLayout_42.addWidget(self.lePointMatrixName, 1, 1, 1, 1)

        self.leMPoint4X = QLineEdit(self.frame_20)
        self.leMPoint4X.setObjectName(u"leMPoint4X")

        self.gridLayout_42.addWidget(self.leMPoint4X, 4, 3, 1, 1)

        self.leMPoint2Y = QLineEdit(self.frame_20)
        self.leMPoint2Y.setObjectName(u"leMPoint2Y")

        self.gridLayout_42.addWidget(self.leMPoint2Y, 2, 5, 1, 1)

        self.leMPoint3X = QLineEdit(self.frame_20)
        self.leMPoint3X.setObjectName(u"leMPoint3X")

        self.gridLayout_42.addWidget(self.leMPoint3X, 3, 3, 1, 1)

        self.label_217 = QLabel(self.frame_20)
        self.label_217.setObjectName(u"label_217")

        self.gridLayout_42.addWidget(self.label_217, 2, 2, 1, 1)

        self.leMPoint1X = QLineEdit(self.frame_20)
        self.leMPoint1X.setObjectName(u"leMPoint1X")

        self.gridLayout_42.addWidget(self.leMPoint1X, 1, 3, 1, 1)

        self.leMPoint4Y = QLineEdit(self.frame_20)
        self.leMPoint4Y.setObjectName(u"leMPoint4Y")

        self.gridLayout_42.addWidget(self.leMPoint4Y, 4, 5, 1, 1)

        self.leMPoint2X = QLineEdit(self.frame_20)
        self.leMPoint2X.setObjectName(u"leMPoint2X")

        self.gridLayout_42.addWidget(self.leMPoint2X, 2, 3, 1, 1)

        self.label_219 = QLabel(self.frame_20)
        self.label_219.setObjectName(u"label_219")

        self.gridLayout_42.addWidget(self.label_219, 4, 2, 1, 1)

        self.pbCalculatePointMatrixTool = QPushButton(self.frame_20)
        self.pbCalculatePointMatrixTool.setObjectName(u"pbCalculatePointMatrixTool")

        self.gridLayout_42.addWidget(self.pbCalculatePointMatrixTool, 2, 1, 1, 1)


        self.verticalLayout_65.addWidget(self.frame_20)


        self.verticalLayout_64.addWidget(self.gbCameraObject_3)


        self.verticalLayout_59.addWidget(self.gbCameraObject_2)

        self.gbCameraObject_4 = QGroupBox(self.fObjectDetectingTool_2)
        self.gbCameraObject_4.setObjectName(u"gbCameraObject_4")
        self.gbCameraObject_4.setFont(font6)
        self.gbCameraObject_4.setCheckable(True)
        self.verticalLayout_66 = QVBoxLayout(self.gbCameraObject_4)
        self.verticalLayout_66.setSpacing(6)
        self.verticalLayout_66.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_66.setObjectName(u"verticalLayout_66")
        self.verticalLayout_66.setContentsMargins(-1, 10, -1, -1)
        self.frame_21 = QFrame(self.gbCameraObject_4)
        self.frame_21.setObjectName(u"frame_21")
        self.frame_21.setMinimumSize(QSize(0, 0))
        self.frame_21.setFrameShape(QFrame.StyledPanel)
        self.frame_21.setFrameShadow(QFrame.Raised)
        self.gridLayout_43 = QGridLayout(self.frame_21)
        self.gridLayout_43.setSpacing(6)
        self.gridLayout_43.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_43.setObjectName(u"gridLayout_43")
        self.leTestPointY = QLineEdit(self.frame_21)
        self.leTestPointY.setObjectName(u"leTestPointY")
        sizePolicy11 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy11.setHorizontalStretch(0)
        sizePolicy11.setVerticalStretch(0)
        sizePolicy11.setHeightForWidth(self.leTestPointY.sizePolicy().hasHeightForWidth())
        self.leTestPointY.setSizePolicy(sizePolicy11)

        self.gridLayout_43.addWidget(self.leTestPointY, 2, 3, 1, 1)

        self.leTargetTestPointY = QLineEdit(self.frame_21)
        self.leTargetTestPointY.setObjectName(u"leTargetTestPointY")
        sizePolicy11.setHeightForWidth(self.leTargetTestPointY.sizePolicy().hasHeightForWidth())
        self.leTargetTestPointY.setSizePolicy(sizePolicy11)

        self.gridLayout_43.addWidget(self.leTargetTestPointY, 5, 3, 1, 1)

        self.leTargetTestPointX = QLineEdit(self.frame_21)
        self.leTargetTestPointX.setObjectName(u"leTargetTestPointX")
        sizePolicy11.setHeightForWidth(self.leTargetTestPointX.sizePolicy().hasHeightForWidth())
        self.leTargetTestPointX.setSizePolicy(sizePolicy11)

        self.gridLayout_43.addWidget(self.leTargetTestPointX, 5, 2, 1, 1)

        self.leTestMatrixName = QLineEdit(self.frame_21)
        self.leTestMatrixName.setObjectName(u"leTestMatrixName")
        sizePolicy12 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        sizePolicy12.setHorizontalStretch(0)
        sizePolicy12.setVerticalStretch(0)
        sizePolicy12.setHeightForWidth(self.leTestMatrixName.sizePolicy().hasHeightForWidth())
        self.leTestMatrixName.setSizePolicy(sizePolicy12)
        self.leTestMatrixName.setMinimumSize(QSize(0, 0))

        self.gridLayout_43.addWidget(self.leTestMatrixName, 2, 5, 1, 1)

        self.pbCalculateTestPoint = QPushButton(self.frame_21)
        self.pbCalculateTestPoint.setObjectName(u"pbCalculateTestPoint")
        sizePolicy11.setHeightForWidth(self.pbCalculateTestPoint.sizePolicy().hasHeightForWidth())
        self.pbCalculateTestPoint.setSizePolicy(sizePolicy11)

        self.gridLayout_43.addWidget(self.pbCalculateTestPoint, 3, 2, 1, 1)

        self.leTestPointX = QLineEdit(self.frame_21)
        self.leTestPointX.setObjectName(u"leTestPointX")
        sizePolicy11.setHeightForWidth(self.leTestPointX.sizePolicy().hasHeightForWidth())
        self.leTestPointX.setSizePolicy(sizePolicy11)

        self.gridLayout_43.addWidget(self.leTestPointX, 2, 2, 1, 1)

        self.label_215 = QLabel(self.frame_21)
        self.label_215.setObjectName(u"label_215")
        self.label_215.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_215, 1, 2, 1, 2)

        self.label_223 = QLabel(self.frame_21)
        self.label_223.setObjectName(u"label_223")

        self.gridLayout_43.addWidget(self.label_223, 2, 4, 1, 1)

        self.label_222 = QLabel(self.frame_21)
        self.label_222.setObjectName(u"label_222")
        self.label_222.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_222, 1, 5, 1, 1)

        self.label_221 = QLabel(self.frame_21)
        self.label_221.setObjectName(u"label_221")
        self.label_221.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_221, 4, 2, 1, 1)

        self.label_214 = QLabel(self.frame_21)
        self.label_214.setObjectName(u"label_214")
        self.label_214.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_214, 4, 3, 1, 1)


        self.verticalLayout_66.addWidget(self.frame_21)


        self.verticalLayout_59.addWidget(self.gbCameraObject_4)

        self.verticalSpacer_18 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_59.addItem(self.verticalSpacer_18)

        self.splitter_3.addWidget(self.fObjectDetectingTool_2)

        self.verticalLayout_18.addWidget(self.splitter_3)

        self.saObjectDetecting_2.setWidget(self.wObjectDetecting_2)

        self.verticalLayout_14.addWidget(self.saObjectDetecting_2)

        self.twModule.addTab(self.tPointTool, "")
        self.tDrawing = QWidget()
        self.tDrawing.setObjectName(u"tDrawing")
        self.verticalLayout_26 = QVBoxLayout(self.tDrawing)
        self.verticalLayout_26.setSpacing(6)
        self.verticalLayout_26.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_26.setObjectName(u"verticalLayout_26")
        self.scrollArea_6 = QScrollArea(self.tDrawing)
        self.scrollArea_6.setObjectName(u"scrollArea_6")
        self.scrollArea_6.setWidgetResizable(True)
        self.scrollAreaWidgetContents_6 = QWidget()
        self.scrollAreaWidgetContents_6.setObjectName(u"scrollAreaWidgetContents_6")
        self.scrollAreaWidgetContents_6.setGeometry(QRect(0, 0, 565, 1600))
        self.scrollAreaWidgetContents_6.setMinimumSize(QSize(450, 1600))
        self.scrollAreaWidgetContents_6.setMaximumSize(QSize(16777215, 16777215))
        self.verticalLayout_38 = QVBoxLayout(self.scrollAreaWidgetContents_6)
        self.verticalLayout_38.setSpacing(6)
        self.verticalLayout_38.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_38.setObjectName(u"verticalLayout_38")
        self.verticalLayout_37 = QVBoxLayout()
        self.verticalLayout_37.setSpacing(6)
        self.verticalLayout_37.setObjectName(u"verticalLayout_37")
        self.frame_4 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_4.setObjectName(u"frame_4")
        sizePolicy10.setHeightForWidth(self.frame_4.sizePolicy().hasHeightForWidth())
        self.frame_4.setSizePolicy(sizePolicy10)
        self.frame_4.setMinimumSize(QSize(0, 75))
        self.frame_4.setMaximumSize(QSize(16777215, 16777215))
        self.frame_4.setStyleSheet(u"QFrame\n"
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
"}")
        self.frame_4.setFrameShape(QFrame.StyledPanel)
        self.frame_4.setFrameShadow(QFrame.Raised)
        self.verticalLayout_21 = QVBoxLayout(self.frame_4)
        self.verticalLayout_21.setSpacing(0)
        self.verticalLayout_21.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_21.setObjectName(u"verticalLayout_21")
        self.verticalLayout_21.setContentsMargins(5, 5, 0, 5)
        self.pbOpenPicture = QToolButton(self.frame_4)
        self.pbOpenPicture.setObjectName(u"pbOpenPicture")
        sizePolicy13 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy13.setHorizontalStretch(0)
        sizePolicy13.setVerticalStretch(0)
        sizePolicy13.setHeightForWidth(self.pbOpenPicture.sizePolicy().hasHeightForWidth())
        self.pbOpenPicture.setSizePolicy(sizePolicy13)
        self.pbOpenPicture.setMinimumSize(QSize(0, 0))
        self.pbOpenPicture.setMaximumSize(QSize(16777215, 16777215))
        font10 = QFont()
        font10.setPointSize(10)
        font10.setBold(False)
        self.pbOpenPicture.setFont(font10)
        self.pbOpenPicture.setLayoutDirection(Qt.LeftToRight)
        icon27 = QIcon()
        icon27.addFile(u":/icon/icons8_image_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbOpenPicture.setIcon(icon27)
        self.pbOpenPicture.setIconSize(QSize(64, 64))
        self.pbOpenPicture.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbOpenPicture.setAutoRaise(False)

        self.verticalLayout_21.addWidget(self.pbOpenPicture)


        self.verticalLayout_37.addWidget(self.frame_4)

        self.horizontalLayout_24 = QHBoxLayout()
        self.horizontalLayout_24.setSpacing(6)
        self.horizontalLayout_24.setObjectName(u"horizontalLayout_24")
        self.frame_2 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_2.setObjectName(u"frame_2")
        sizePolicy.setHeightForWidth(self.frame_2.sizePolicy().hasHeightForWidth())
        self.frame_2.setSizePolicy(sizePolicy)
        self.frame_2.setMinimumSize(QSize(0, 250))
        self.frame_2.setFrameShape(QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QFrame.Raised)
        self.lbImageForDrawing = QLabel(self.frame_2)
        self.lbImageForDrawing.setObjectName(u"lbImageForDrawing")
        self.lbImageForDrawing.setGeometry(QRect(10, 10, 281, 226))
        sizePolicy.setHeightForWidth(self.lbImageForDrawing.sizePolicy().hasHeightForWidth())
        self.lbImageForDrawing.setSizePolicy(sizePolicy)
        self.lbImageForDrawing.setMinimumSize(QSize(0, 0))
        self.lbImageForDrawing.setStyleSheet(u"/*background-color: rgb(142, 254, 255);*/\n"
"QLabel\n"
"{\n"
"	/*background-color: rgb(255, 255, 255);*/\n"
"	border: 1px solid rgb(140, 140, 140);\n"
"	border-radius: 5px;\n"
"}")
        self.lbImageForDrawing.setScaledContents(False)

        self.horizontalLayout_24.addWidget(self.frame_2)

        self.widget = QWidget(self.scrollAreaWidgetContents_6)
        self.widget.setObjectName(u"widget")
        self.widget.setMaximumSize(QSize(100, 16777215))
        self.verticalLayout_36 = QVBoxLayout(self.widget)
        self.verticalLayout_36.setSpacing(6)
        self.verticalLayout_36.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_36.setObjectName(u"verticalLayout_36")
        self.widget_3 = QWidget(self.widget)
        self.widget_3.setObjectName(u"widget_3")
        self.widget_3.setStyleSheet(u"")
        self.gridLayout_23 = QGridLayout(self.widget_3)
        self.gridLayout_23.setSpacing(6)
        self.gridLayout_23.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_23.setObjectName(u"gridLayout_23")
        self.lbImageWidth = QLabel(self.widget_3)
        self.lbImageWidth.setObjectName(u"lbImageWidth")
        self.lbImageWidth.setFont(font5)
        self.lbImageWidth.setStyleSheet(u"")

        self.gridLayout_23.addWidget(self.lbImageWidth, 0, 0, 1, 1)

        self.lbImageHeight = QLabel(self.widget_3)
        self.lbImageHeight.setObjectName(u"lbImageHeight")
        self.lbImageHeight.setFont(font5)
        self.lbImageHeight.setStyleSheet(u"")

        self.gridLayout_23.addWidget(self.lbImageHeight, 1, 0, 1, 1)

        self.verticalSpacer_4 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout_23.addItem(self.verticalSpacer_4, 2, 0, 1, 1)


        self.verticalLayout_36.addWidget(self.widget_3)


        self.horizontalLayout_24.addWidget(self.widget)


        self.verticalLayout_37.addLayout(self.horizontalLayout_24)

        self.widget_2 = QWidget(self.scrollAreaWidgetContents_6)
        self.widget_2.setObjectName(u"widget_2")
        self.widget_2.setMinimumSize(QSize(0, 50))
        self.widget_2.setMaximumSize(QSize(16777215, 80))
        self.widget_2.setStyleSheet(u"/*background-color: rgb(171, 225, 224);*/")
        self.gridLayout_25 = QGridLayout(self.widget_2)
        self.gridLayout_25.setSpacing(6)
        self.gridLayout_25.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_25.setObjectName(u"gridLayout_25")
        self.cbConversionTool = QComboBox(self.widget_2)
        self.cbConversionTool.addItem("")
        self.cbConversionTool.addItem("")
        self.cbConversionTool.addItem("")
        self.cbConversionTool.setObjectName(u"cbConversionTool")
        self.cbConversionTool.setMinimumSize(QSize(0, 30))

        self.gridLayout_25.addWidget(self.cbConversionTool, 1, 1, 1, 1)

        self.hsDrawingThreshold = QSlider(self.widget_2)
        self.hsDrawingThreshold.setObjectName(u"hsDrawingThreshold")
        self.hsDrawingThreshold.setMaximum(255)
        self.hsDrawingThreshold.setSingleStep(1)
        self.hsDrawingThreshold.setValue(150)
        self.hsDrawingThreshold.setOrientation(Qt.Horizontal)

        self.gridLayout_25.addWidget(self.hsDrawingThreshold, 1, 2, 1, 1)

        self.leDrawingThreshold = QLineEdit(self.widget_2)
        self.leDrawingThreshold.setObjectName(u"leDrawingThreshold")
        self.leDrawingThreshold.setMinimumSize(QSize(0, 30))
        self.leDrawingThreshold.setMaximumSize(QSize(60, 16777215))
        self.leDrawingThreshold.setFont(font5)

        self.gridLayout_25.addWidget(self.leDrawingThreshold, 1, 3, 1, 1)

        self.label_14 = QLabel(self.widget_2)
        self.label_14.setObjectName(u"label_14")
        self.label_14.setFont(font5)

        self.gridLayout_25.addWidget(self.label_14, 1, 0, 1, 1)

        self.label_105 = QLabel(self.widget_2)
        self.label_105.setObjectName(u"label_105")
        self.label_105.setFont(font5)

        self.gridLayout_25.addWidget(self.label_105, 2, 0, 1, 1)

        self.cbReverseDrawing = QCheckBox(self.widget_2)
        self.cbReverseDrawing.setObjectName(u"cbReverseDrawing")

        self.gridLayout_25.addWidget(self.cbReverseDrawing, 2, 1, 1, 1)


        self.verticalLayout_37.addWidget(self.widget_2)

        self.frame_5 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_5.setObjectName(u"frame_5")
        sizePolicy3.setHeightForWidth(self.frame_5.sizePolicy().hasHeightForWidth())
        self.frame_5.setSizePolicy(sizePolicy3)
        self.frame_5.setMinimumSize(QSize(0, 75))
        self.frame_5.setMaximumSize(QSize(16777215, 16777215))
        self.frame_5.setStyleSheet(u"QFrame\n"
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
"}")
        self.frame_5.setFrameShape(QFrame.StyledPanel)
        self.frame_5.setFrameShadow(QFrame.Raised)
        self.verticalLayout_47 = QVBoxLayout(self.frame_5)
        self.verticalLayout_47.setSpacing(0)
        self.verticalLayout_47.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_47.setObjectName(u"verticalLayout_47")
        self.verticalLayout_47.setContentsMargins(5, 5, 0, 5)
        self.pbPainting = QToolButton(self.frame_5)
        self.pbPainting.setObjectName(u"pbPainting")
        sizePolicy13.setHeightForWidth(self.pbPainting.sizePolicy().hasHeightForWidth())
        self.pbPainting.setSizePolicy(sizePolicy13)
        self.pbPainting.setMinimumSize(QSize(0, 0))
        self.pbPainting.setMaximumSize(QSize(16777215, 16777215))
        self.pbPainting.setFont(font10)
        icon28 = QIcon()
        icon28.addFile(u":/icon/icons8_pencil_drawing_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbPainting.setIcon(icon28)
        self.pbPainting.setIconSize(QSize(64, 64))
        self.pbPainting.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbPainting.setAutoRaise(False)
        self.pbPainting.setArrowType(Qt.NoArrow)

        self.verticalLayout_47.addWidget(self.pbPainting)


        self.verticalLayout_37.addWidget(self.frame_5)

        self.frame_7 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_7.setObjectName(u"frame_7")
        self.frame_7.setMinimumSize(QSize(0, 50))
        self.frame_7.setFrameShape(QFrame.StyledPanel)
        self.frame_7.setFrameShadow(QFrame.Raised)
        self.gridLayout_24 = QGridLayout(self.frame_7)
        self.gridLayout_24.setSpacing(6)
        self.gridLayout_24.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_24.setObjectName(u"gridLayout_24")
        self.label_20 = QLabel(self.frame_7)
        self.label_20.setObjectName(u"label_20")
        self.label_20.setFont(font5)

        self.gridLayout_24.addWidget(self.label_20, 0, 1, 1, 1)

        self.label_18 = QLabel(self.frame_7)
        self.label_18.setObjectName(u"label_18")
        self.label_18.setFont(font5)

        self.gridLayout_24.addWidget(self.label_18, 0, 2, 1, 1)

        self.horizontalSpacer_40 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_24.addItem(self.horizontalSpacer_40, 1, 4, 1, 1)

        self.cbLockDrawingArea = QComboBox(self.frame_7)
        self.cbLockDrawingArea.addItem("")
        self.cbLockDrawingArea.addItem("")
        self.cbLockDrawingArea.setObjectName(u"cbLockDrawingArea")

        self.gridLayout_24.addWidget(self.cbLockDrawingArea, 1, 3, 1, 1)

        self.label_104 = QLabel(self.frame_7)
        self.label_104.setObjectName(u"label_104")

        self.gridLayout_24.addWidget(self.label_104, 0, 3, 1, 1)

        self.leWidthScale = QLineEdit(self.frame_7)
        self.leWidthScale.setObjectName(u"leWidthScale")
        self.leWidthScale.setMinimumSize(QSize(0, 30))
        self.leWidthScale.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_24.addWidget(self.leWidthScale, 1, 2, 1, 1)

        self.leHeightScale = QLineEdit(self.frame_7)
        self.leHeightScale.setObjectName(u"leHeightScale")
        self.leHeightScale.setMinimumSize(QSize(0, 30))
        self.leHeightScale.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_24.addWidget(self.leHeightScale, 1, 1, 1, 1)


        self.verticalLayout_37.addWidget(self.frame_7)

        self.label_21 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_21.setObjectName(u"label_21")

        self.verticalLayout_37.addWidget(self.label_21)

        self.frame_3 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_3.setObjectName(u"frame_3")
        sizePolicy10.setHeightForWidth(self.frame_3.sizePolicy().hasHeightForWidth())
        self.frame_3.setSizePolicy(sizePolicy10)
        self.frame_3.setMinimumSize(QSize(300, 300))
        self.frame_3.setMaximumSize(QSize(300, 300))
        self.frame_3.setFrameShape(QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QFrame.Raised)
        self.lbDrawingArea = DrawingWidget(self.frame_3)
        self.lbDrawingArea.setObjectName(u"lbDrawingArea")
        self.lbDrawingArea.setGeometry(QRect(0, 0, 300, 300))
        sizePolicy.setHeightForWidth(self.lbDrawingArea.sizePolicy().hasHeightForWidth())
        self.lbDrawingArea.setSizePolicy(sizePolicy)
        self.lbDrawingArea.setMinimumSize(QSize(300, 300))
        self.lbDrawingArea.setMaximumSize(QSize(300, 300))
        self.lbDrawingArea.setStyleSheet(u"/*background-color: rgb(142, 254, 255);*/\n"
"QLabel\n"
"{\n"
"	/*background-color: rgb(255, 255, 255);*/\n"
"	border: 1px solid rgb(140, 140, 140);\n"
"	border-radius: 150px;\n"
"}")
        self.lbDrawingArea.setScaledContents(True)

        self.verticalLayout_37.addWidget(self.frame_3)

        self.horizontalLayout_23 = QHBoxLayout()
        self.horizontalLayout_23.setSpacing(0)
        self.horizontalLayout_23.setObjectName(u"horizontalLayout_23")
        self.widget_11 = QWidget(self.scrollAreaWidgetContents_6)
        self.widget_11.setObjectName(u"widget_11")
        self.widget_11.setStyleSheet(u"background-color: rgb(234, 234, 234);")
        self.horizontalLayout_22 = QHBoxLayout(self.widget_11)
        self.horizontalLayout_22.setSpacing(6)
        self.horizontalLayout_22.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_22.setObjectName(u"horizontalLayout_22")
        self.label_26 = QLabel(self.widget_11)
        self.label_26.setObjectName(u"label_26")

        self.horizontalLayout_22.addWidget(self.label_26)

        self.leDrawAg5 = QLineEdit(self.widget_11)
        self.leDrawAg5.setObjectName(u"leDrawAg5")
        sizePolicy14 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy14.setHorizontalStretch(0)
        sizePolicy14.setVerticalStretch(0)
        sizePolicy14.setHeightForWidth(self.leDrawAg5.sizePolicy().hasHeightForWidth())
        self.leDrawAg5.setSizePolicy(sizePolicy14)
        self.leDrawAg5.setMinimumSize(QSize(0, 20))
        self.leDrawAg5.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_22.addWidget(self.leDrawAg5)


        self.horizontalLayout_23.addWidget(self.widget_11)

        self.widget_10 = QWidget(self.scrollAreaWidgetContents_6)
        self.widget_10.setObjectName(u"widget_10")
        self.widget_10.setStyleSheet(u"background-color: rgb(234, 234, 234);")
        self.horizontalLayout_21 = QHBoxLayout(self.widget_10)
        self.horizontalLayout_21.setSpacing(6)
        self.horizontalLayout_21.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_21.setObjectName(u"horizontalLayout_21")
        self.label_25 = QLabel(self.widget_10)
        self.label_25.setObjectName(u"label_25")
        self.label_25.setFont(font5)

        self.horizontalLayout_21.addWidget(self.label_25)

        self.leDrawAg4 = QLineEdit(self.widget_10)
        self.leDrawAg4.setObjectName(u"leDrawAg4")
        sizePolicy14.setHeightForWidth(self.leDrawAg4.sizePolicy().hasHeightForWidth())
        self.leDrawAg4.setSizePolicy(sizePolicy14)
        self.leDrawAg4.setMinimumSize(QSize(0, 20))
        self.leDrawAg4.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_21.addWidget(self.leDrawAg4)


        self.horizontalLayout_23.addWidget(self.widget_10)

        self.widget_9 = QWidget(self.scrollAreaWidgetContents_6)
        self.widget_9.setObjectName(u"widget_9")
        self.widget_9.setStyleSheet(u"background-color: rgb(234, 234, 234);")
        self.horizontalLayout_20 = QHBoxLayout(self.widget_9)
        self.horizontalLayout_20.setSpacing(6)
        self.horizontalLayout_20.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_20.setObjectName(u"horizontalLayout_20")
        self.label_24 = QLabel(self.widget_9)
        self.label_24.setObjectName(u"label_24")

        self.horizontalLayout_20.addWidget(self.label_24)

        self.leDrawAg3 = QLineEdit(self.widget_9)
        self.leDrawAg3.setObjectName(u"leDrawAg3")
        sizePolicy14.setHeightForWidth(self.leDrawAg3.sizePolicy().hasHeightForWidth())
        self.leDrawAg3.setSizePolicy(sizePolicy14)
        self.leDrawAg3.setMinimumSize(QSize(0, 20))
        self.leDrawAg3.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_20.addWidget(self.leDrawAg3)


        self.horizontalLayout_23.addWidget(self.widget_9)

        self.widget_8 = QWidget(self.scrollAreaWidgetContents_6)
        self.widget_8.setObjectName(u"widget_8")
        self.widget_8.setStyleSheet(u"background-color: rgb(234, 234, 234);")
        self.horizontalLayout_19 = QHBoxLayout(self.widget_8)
        self.horizontalLayout_19.setSpacing(6)
        self.horizontalLayout_19.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_19.setObjectName(u"horizontalLayout_19")
        self.label_22 = QLabel(self.widget_8)
        self.label_22.setObjectName(u"label_22")

        self.horizontalLayout_19.addWidget(self.label_22)

        self.leDrawAg2 = QLineEdit(self.widget_8)
        self.leDrawAg2.setObjectName(u"leDrawAg2")
        sizePolicy14.setHeightForWidth(self.leDrawAg2.sizePolicy().hasHeightForWidth())
        self.leDrawAg2.setSizePolicy(sizePolicy14)
        self.leDrawAg2.setMinimumSize(QSize(0, 20))
        self.leDrawAg2.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_19.addWidget(self.leDrawAg2)


        self.horizontalLayout_23.addWidget(self.widget_8)

        self.widget_7 = QWidget(self.scrollAreaWidgetContents_6)
        self.widget_7.setObjectName(u"widget_7")
        self.widget_7.setStyleSheet(u"background-color: rgb(234, 234, 234);")
        self.horizontalLayout_18 = QHBoxLayout(self.widget_7)
        self.horizontalLayout_18.setSpacing(6)
        self.horizontalLayout_18.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_18.setObjectName(u"horizontalLayout_18")
        self.label_19 = QLabel(self.widget_7)
        self.label_19.setObjectName(u"label_19")

        self.horizontalLayout_18.addWidget(self.label_19)

        self.leDrawAg1 = QLineEdit(self.widget_7)
        self.leDrawAg1.setObjectName(u"leDrawAg1")
        sizePolicy14.setHeightForWidth(self.leDrawAg1.sizePolicy().hasHeightForWidth())
        self.leDrawAg1.setSizePolicy(sizePolicy14)
        self.leDrawAg1.setMinimumSize(QSize(0, 20))
        self.leDrawAg1.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_18.addWidget(self.leDrawAg1)


        self.horizontalLayout_23.addWidget(self.widget_7)


        self.verticalLayout_37.addLayout(self.horizontalLayout_23)

        self.gridLayout_11 = QGridLayout()
        self.gridLayout_11.setSpacing(10)
        self.gridLayout_11.setObjectName(u"gridLayout_11")
        self.horizontalSpacer_5 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_11.addItem(self.horizontalSpacer_5, 0, 4, 1, 1)

        self.pbDrawLine = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbDrawLine.setObjectName(u"pbDrawLine")
        sizePolicy12.setHeightForWidth(self.pbDrawLine.sizePolicy().hasHeightForWidth())
        self.pbDrawLine.setSizePolicy(sizePolicy12)
        self.pbDrawLine.setMinimumSize(QSize(0, 0))
        self.pbDrawLine.setMaximumSize(QSize(70, 16777215))
        icon29 = QIcon()
        icon29.addFile(u":/icon/Line_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawLine.setIcon(icon29)
        self.pbDrawLine.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawLine.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawLine, 0, 0, 1, 1)

        self.pbDrawRectangle = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbDrawRectangle.setObjectName(u"pbDrawRectangle")
        sizePolicy12.setHeightForWidth(self.pbDrawRectangle.sizePolicy().hasHeightForWidth())
        self.pbDrawRectangle.setSizePolicy(sizePolicy12)
        self.pbDrawRectangle.setMinimumSize(QSize(0, 0))
        self.pbDrawRectangle.setMaximumSize(QSize(70, 16777215))
        icon30 = QIcon()
        icon30.addFile(u":/icon/Rectangular_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawRectangle.setIcon(icon30)
        self.pbDrawRectangle.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawRectangle.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawRectangle, 0, 1, 1, 1)

        self.pbZoomIn = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbZoomIn.setObjectName(u"pbZoomIn")
        sizePolicy12.setHeightForWidth(self.pbZoomIn.sizePolicy().hasHeightForWidth())
        self.pbZoomIn.setSizePolicy(sizePolicy12)
        self.pbZoomIn.setMinimumSize(QSize(0, 0))
        self.pbZoomIn.setMaximumSize(QSize(70, 16777215))
        icon31 = QIcon()
        icon31.addFile(u":/icon/Zoom In_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbZoomIn.setIcon(icon31)
        self.pbZoomIn.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbZoomIn.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbZoomIn, 0, 2, 1, 1)

        self.pbCursor = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbCursor.setObjectName(u"pbCursor")
        sizePolicy12.setHeightForWidth(self.pbCursor.sizePolicy().hasHeightForWidth())
        self.pbCursor.setSizePolicy(sizePolicy12)
        self.pbCursor.setMinimumSize(QSize(0, 0))
        self.pbCursor.setMaximumSize(QSize(70, 16777215))
        icon32 = QIcon()
        icon32.addFile(u":/icon/Cursor-color_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCursor.setIcon(icon32)
        self.pbCursor.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbCursor.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbCursor, 0, 3, 1, 1)

        self.pbDrawArc = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbDrawArc.setObjectName(u"pbDrawArc")
        sizePolicy12.setHeightForWidth(self.pbDrawArc.sizePolicy().hasHeightForWidth())
        self.pbDrawArc.setSizePolicy(sizePolicy12)
        self.pbDrawArc.setMinimumSize(QSize(0, 0))
        self.pbDrawArc.setMaximumSize(QSize(70, 16777215))
        icon33 = QIcon()
        icon33.addFile(u":/icon/Circled Notch_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawArc.setIcon(icon33)
        self.pbDrawArc.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawArc.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawArc, 1, 0, 1, 1)

        self.pbDrawCircle = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbDrawCircle.setObjectName(u"pbDrawCircle")
        sizePolicy12.setHeightForWidth(self.pbDrawCircle.sizePolicy().hasHeightForWidth())
        self.pbDrawCircle.setSizePolicy(sizePolicy12)
        self.pbDrawCircle.setMinimumSize(QSize(0, 0))
        self.pbDrawCircle.setMaximumSize(QSize(70, 16777215))
        icon34 = QIcon()
        icon34.addFile(u":/icon/Circle_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawCircle.setIcon(icon34)
        self.pbDrawCircle.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawCircle.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawCircle, 1, 1, 1, 1)

        self.pbZoomOut = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbZoomOut.setObjectName(u"pbZoomOut")
        sizePolicy12.setHeightForWidth(self.pbZoomOut.sizePolicy().hasHeightForWidth())
        self.pbZoomOut.setSizePolicy(sizePolicy12)
        self.pbZoomOut.setMinimumSize(QSize(0, 0))
        self.pbZoomOut.setMaximumSize(QSize(70, 16777215))
        icon35 = QIcon()
        icon35.addFile(u":/icon/Zoom Out_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbZoomOut.setIcon(icon35)
        self.pbZoomOut.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbZoomOut.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbZoomOut, 1, 2, 1, 1)


        self.verticalLayout_37.addLayout(self.gridLayout_11)

        self.frame_6 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_6.setObjectName(u"frame_6")
        sizePolicy3.setHeightForWidth(self.frame_6.sizePolicy().hasHeightForWidth())
        self.frame_6.setSizePolicy(sizePolicy3)
        self.frame_6.setMinimumSize(QSize(0, 75))
        self.frame_6.setMaximumSize(QSize(16777215, 16777215))
        self.frame_6.setStyleSheet(u"QFrame\n"
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
"}")
        self.frame_6.setFrameShape(QFrame.StyledPanel)
        self.frame_6.setFrameShadow(QFrame.Raised)
        self.verticalLayout_48 = QVBoxLayout(self.frame_6)
        self.verticalLayout_48.setSpacing(0)
        self.verticalLayout_48.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_48.setObjectName(u"verticalLayout_48")
        self.verticalLayout_48.setContentsMargins(5, 5, 0, 5)
        self.pbExportDrawingGcodes = QToolButton(self.frame_6)
        self.pbExportDrawingGcodes.setObjectName(u"pbExportDrawingGcodes")
        sizePolicy13.setHeightForWidth(self.pbExportDrawingGcodes.sizePolicy().hasHeightForWidth())
        self.pbExportDrawingGcodes.setSizePolicy(sizePolicy13)
        self.pbExportDrawingGcodes.setMinimumSize(QSize(185, 65))
        self.pbExportDrawingGcodes.setMaximumSize(QSize(16777215, 16777215))
        self.pbExportDrawingGcodes.setFont(font10)
        icon36 = QIcon()
        icon36.addFile(u":/icon/icons8_code_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbExportDrawingGcodes.setIcon(icon36)
        self.pbExportDrawingGcodes.setIconSize(QSize(64, 64))
        self.pbExportDrawingGcodes.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbExportDrawingGcodes.setAutoRaise(False)

        self.verticalLayout_48.addWidget(self.pbExportDrawingGcodes)


        self.verticalLayout_37.addWidget(self.frame_6)

        self.gridLayout_22 = QGridLayout()
        self.gridLayout_22.setSpacing(15)
        self.gridLayout_22.setObjectName(u"gridLayout_22")
        self.gridLayout_22.setContentsMargins(-1, 5, -1, 5)
        self.label_96 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_96.setObjectName(u"label_96")
        sizePolicy4.setHeightForWidth(self.label_96.sizePolicy().hasHeightForWidth())
        self.label_96.setSizePolicy(sizePolicy4)
        self.label_96.setMinimumSize(QSize(0, 0))
        self.label_96.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_96, 4, 0, 1, 1)

        self.label_101 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_101.setObjectName(u"label_101")
        sizePolicy.setHeightForWidth(self.label_101.sizePolicy().hasHeightForWidth())
        self.label_101.setSizePolicy(sizePolicy)
        self.label_101.setMinimumSize(QSize(0, 0))
        font11 = QFont()
        font11.setItalic(False)
        self.label_101.setFont(font11)
        self.label_101.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_101, 6, 2, 1, 1)

        self.label_13 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_13.setObjectName(u"label_13")
        self.label_13.setFont(font5)
        self.label_13.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_13, 1, 0, 1, 1)

        self.horizontalSpacer_33 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_22.addItem(self.horizontalSpacer_33, 0, 2, 1, 1)

        self.label_97 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_97.setObjectName(u"label_97")
        sizePolicy4.setHeightForWidth(self.label_97.sizePolicy().hasHeightForWidth())
        self.label_97.setSizePolicy(sizePolicy4)
        self.label_97.setMinimumSize(QSize(0, 0))
        self.label_97.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_97, 6, 0, 1, 1)

        self.leTravelSpeed = QLineEdit(self.scrollAreaWidgetContents_6)
        self.leTravelSpeed.setObjectName(u"leTravelSpeed")
        self.leTravelSpeed.setMinimumSize(QSize(0, 30))
        self.leTravelSpeed.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_22.addWidget(self.leTravelSpeed, 4, 1, 1, 1)

        self.cbDrawMethod = QComboBox(self.scrollAreaWidgetContents_6)
        self.cbDrawMethod.addItem("")
        self.cbDrawMethod.addItem("")
        self.cbDrawMethod.setObjectName(u"cbDrawMethod")
        self.cbDrawMethod.setMinimumSize(QSize(0, 30))
        self.cbDrawMethod.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_22.addWidget(self.cbDrawMethod, 1, 1, 1, 1)

        self.cbDrawingEffector = QComboBox(self.scrollAreaWidgetContents_6)
        self.cbDrawingEffector.addItem("")
        self.cbDrawingEffector.addItem("")
        self.cbDrawingEffector.setObjectName(u"cbDrawingEffector")
        sizePolicy3.setHeightForWidth(self.cbDrawingEffector.sizePolicy().hasHeightForWidth())
        self.cbDrawingEffector.setSizePolicy(sizePolicy3)
        self.cbDrawingEffector.setMinimumSize(QSize(0, 30))
        self.cbDrawingEffector.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_22.addWidget(self.cbDrawingEffector, 0, 1, 1, 1)

        self.leSafeZHeight = QLineEdit(self.scrollAreaWidgetContents_6)
        self.leSafeZHeight.setObjectName(u"leSafeZHeight")
        self.leSafeZHeight.setMinimumSize(QSize(0, 30))
        self.leSafeZHeight.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_22.addWidget(self.leSafeZHeight, 3, 1, 1, 1)

        self.leDrawingAcceleration = QLineEdit(self.scrollAreaWidgetContents_6)
        self.leDrawingAcceleration.setObjectName(u"leDrawingAcceleration")
        self.leDrawingAcceleration.setMinimumSize(QSize(0, 30))
        self.leDrawingAcceleration.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_22.addWidget(self.leDrawingAcceleration, 7, 1, 1, 1)

        self.label_102 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_102.setObjectName(u"label_102")
        sizePolicy.setHeightForWidth(self.label_102.sizePolicy().hasHeightForWidth())
        self.label_102.setSizePolicy(sizePolicy)
        self.label_102.setMinimumSize(QSize(0, 0))
        self.label_102.setFont(font11)
        self.label_102.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_102, 7, 2, 1, 1)

        self.label_93 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_93.setObjectName(u"label_93")
        sizePolicy15 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Preferred)
        sizePolicy15.setHorizontalStretch(0)
        sizePolicy15.setVerticalStretch(0)
        sizePolicy15.setHeightForWidth(self.label_93.sizePolicy().hasHeightForWidth())
        self.label_93.setSizePolicy(sizePolicy15)
        self.label_93.setMinimumSize(QSize(0, 0))
        self.label_93.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_93, 0, 0, 1, 1)

        self.label_95 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_95.setObjectName(u"label_95")
        sizePolicy4.setHeightForWidth(self.label_95.sizePolicy().hasHeightForWidth())
        self.label_95.setSizePolicy(sizePolicy4)
        self.label_95.setMinimumSize(QSize(0, 0))
        self.label_95.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_95, 3, 0, 1, 1)

        self.label_100 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_100.setObjectName(u"label_100")
        sizePolicy.setHeightForWidth(self.label_100.sizePolicy().hasHeightForWidth())
        self.label_100.setSizePolicy(sizePolicy)
        self.label_100.setMinimumSize(QSize(0, 0))
        self.label_100.setFont(font11)
        self.label_100.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_100, 4, 2, 1, 1)

        self.label_98 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_98.setObjectName(u"label_98")
        sizePolicy4.setHeightForWidth(self.label_98.sizePolicy().hasHeightForWidth())
        self.label_98.setSizePolicy(sizePolicy4)
        self.label_98.setMinimumSize(QSize(0, 0))
        self.label_98.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_98, 7, 0, 1, 1)

        self.leDrawingSpeed = QLineEdit(self.scrollAreaWidgetContents_6)
        self.leDrawingSpeed.setObjectName(u"leDrawingSpeed")
        self.leDrawingSpeed.setMinimumSize(QSize(0, 30))
        self.leDrawingSpeed.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_22.addWidget(self.leDrawingSpeed, 6, 1, 1, 1)

        self.label_99 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_99.setObjectName(u"label_99")
        sizePolicy.setHeightForWidth(self.label_99.sizePolicy().hasHeightForWidth())
        self.label_99.setSizePolicy(sizePolicy)
        self.label_99.setMinimumSize(QSize(0, 0))
        self.label_99.setFont(font11)
        self.label_99.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_99, 3, 2, 1, 1)

        self.label_23 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_23.setObjectName(u"label_23")
        self.label_23.setFont(font5)
        self.label_23.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_23, 2, 0, 1, 1)

        self.leSpace = QLineEdit(self.scrollAreaWidgetContents_6)
        self.leSpace.setObjectName(u"leSpace")
        self.leSpace.setMinimumSize(QSize(0, 30))
        self.leSpace.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_22.addWidget(self.leSpace, 2, 1, 1, 1)

        self.label_103 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_103.setObjectName(u"label_103")
        sizePolicy.setHeightForWidth(self.label_103.sizePolicy().hasHeightForWidth())
        self.label_103.setSizePolicy(sizePolicy)
        self.label_103.setMinimumSize(QSize(0, 0))
        self.label_103.setFont(font11)
        self.label_103.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_103, 2, 2, 1, 1)


        self.verticalLayout_37.addLayout(self.gridLayout_22)


        self.verticalLayout_38.addLayout(self.verticalLayout_37)

        self.verticalSpacer_6 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_38.addItem(self.verticalSpacer_6)

        self.scrollArea_6.setWidget(self.scrollAreaWidgetContents_6)

        self.verticalLayout_26.addWidget(self.scrollArea_6)

        self.twModule.addTab(self.tDrawing, "")
        self.TermiteTab = QWidget()
        self.TermiteTab.setObjectName(u"TermiteTab")
        self.verticalLayout_11 = QVBoxLayout(self.TermiteTab)
        self.verticalLayout_11.setSpacing(6)
        self.verticalLayout_11.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_11.setObjectName(u"verticalLayout_11")
        self.scrollArea_7 = QScrollArea(self.TermiteTab)
        self.scrollArea_7.setObjectName(u"scrollArea_7")
        self.scrollArea_7.setWidgetResizable(True)
        self.scrollAreaWidgetContents_7 = QWidget()
        self.scrollAreaWidgetContents_7.setObjectName(u"scrollAreaWidgetContents_7")
        self.scrollAreaWidgetContents_7.setGeometry(QRect(0, 0, 575, 539))
        self.verticalLayout_27 = QVBoxLayout(self.scrollAreaWidgetContents_7)
        self.verticalLayout_27.setSpacing(6)
        self.verticalLayout_27.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_27.setObjectName(u"verticalLayout_27")
        self.gridLayout_4 = QGridLayout()
        self.gridLayout_4.setSpacing(6)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.teDebug = QTextEdit(self.scrollAreaWidgetContents_7)
        self.teDebug.setObjectName(u"teDebug")
        font12 = QFont()
        font12.setBold(False)
        font12.setItalic(False)
        font12.setKerning(True)
        self.teDebug.setFont(font12)
        self.teDebug.setStyleSheet(u"color: rgb(255, 82, 87);")

        self.gridLayout_4.addWidget(self.teDebug, 0, 1, 1, 1)

        self.label_4 = QLabel(self.scrollAreaWidgetContents_7)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout_4.addWidget(self.label_4, 1, 0, 1, 1)

        self.label_5 = QLabel(self.scrollAreaWidgetContents_7)
        self.label_5.setObjectName(u"label_5")

        self.gridLayout_4.addWidget(self.label_5, 0, 0, 1, 1)

        self.leTerminal = QLineEdit(self.scrollAreaWidgetContents_7)
        self.leTerminal.setObjectName(u"leTerminal")
        self.leTerminal.setMinimumSize(QSize(0, 30))

        self.gridLayout_4.addWidget(self.leTerminal, 1, 1, 1, 1)

        self.cbDeviceSender = QComboBox(self.scrollAreaWidgetContents_7)
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.setObjectName(u"cbDeviceSender")

        self.gridLayout_4.addWidget(self.cbDeviceSender, 1, 2, 1, 1)


        self.verticalLayout_27.addLayout(self.gridLayout_4)

        self.scrollArea_7.setWidget(self.scrollAreaWidgetContents_7)

        self.verticalLayout_11.addWidget(self.scrollArea_7)

        self.twModule.addTab(self.TermiteTab, "")

        self.ModuleTabManagerLayout.addWidget(self.twModule)

        self.splitter_2.addWidget(self.ModuleTabManagerWidget)
        self.DeviceTabManagerWidget = QWidget(self.splitter_2)
        self.DeviceTabManagerWidget.setObjectName(u"DeviceTabManagerWidget")
        self.DeviceTabManagerWidget.setMinimumSize(QSize(0, 0))
        self.DeviceTabManagerWidget.setMaximumSize(QSize(900, 16777215))
        self.DeviceTabManagerWidget.setStyleSheet(u"")
        self.GeometryTabManagerLayout = QVBoxLayout(self.DeviceTabManagerWidget)
        self.GeometryTabManagerLayout.setSpacing(0)
        self.GeometryTabManagerLayout.setContentsMargins(11, 11, 11, 11)
        self.GeometryTabManagerLayout.setObjectName(u"GeometryTabManagerLayout")
        self.GeometryTabManagerLayout.setContentsMargins(0, 0, 0, 0)
        self.twDevices = QTabWidget(self.DeviceTabManagerWidget)
        self.twDevices.setObjectName(u"twDevices")
        self.twDevices.setMinimumSize(QSize(0, 0))
        self.twDevices.setFont(font3)
        self.twDevices.setStyleSheet(u"")
        self.twDevices.setTabPosition(QTabWidget.North)
        self.twDevices.setElideMode(Qt.ElideNone)
        self.twDevices.setTabsClosable(False)
        self.tRobot = QWidget()
        self.tRobot.setObjectName(u"tRobot")
        self.verticalLayout_4 = QVBoxLayout(self.tRobot)
        self.verticalLayout_4.setSpacing(6)
        self.verticalLayout_4.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.scrollArea_2 = QScrollArea(self.tRobot)
        self.scrollArea_2.setObjectName(u"scrollArea_2")
        self.scrollArea_2.setWidgetResizable(True)
        self.wgJoggingScrollWidget = QWidget()
        self.wgJoggingScrollWidget.setObjectName(u"wgJoggingScrollWidget")
        self.wgJoggingScrollWidget.setGeometry(QRect(0, 0, 565, 800))
        self.wgJoggingScrollWidget.setMinimumSize(QSize(0, 800))
        self.wgJoggingScrollWidget.setMaximumSize(QSize(16777215, 16777215))
        self.verticalLayout_5 = QVBoxLayout(self.wgJoggingScrollWidget)
        self.verticalLayout_5.setSpacing(10)
        self.verticalLayout_5.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(5, 10, 5, 0)
        self.widget_4 = QWidget(self.wgJoggingScrollWidget)
        self.widget_4.setObjectName(u"widget_4")
        self.widget_4.setMinimumSize(QSize(0, 0))
        self.horizontalLayout_35 = QHBoxLayout(self.widget_4)
        self.horizontalLayout_35.setSpacing(6)
        self.horizontalLayout_35.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_35.setObjectName(u"horizontalLayout_35")
        self.horizontalLayout_35.setContentsMargins(-1, 0, -1, 0)
        self.label = QLabel(self.widget_4)
        self.label.setObjectName(u"label")
        self.label.setMaximumSize(QSize(100, 16777215))
        font13 = QFont()
        font13.setPointSize(9)
        font13.setBold(True)
        self.label.setFont(font13)
        self.label.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_35.addWidget(self.label)

        self.cbSelectedRobot = QComboBox(self.widget_4)
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.setObjectName(u"cbSelectedRobot")
        sizePolicy6.setHeightForWidth(self.cbSelectedRobot.sizePolicy().hasHeightForWidth())
        self.cbSelectedRobot.setSizePolicy(sizePolicy6)
        self.cbSelectedRobot.setMinimumSize(QSize(100, 0))
        self.cbSelectedRobot.setMaximumSize(QSize(300, 16777215))
        self.cbSelectedRobot.setFont(font4)

        self.horizontalLayout_35.addWidget(self.cbSelectedRobot)

        self.horizontalSpacer_28 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_35.addItem(self.horizontalSpacer_28)


        self.verticalLayout_5.addWidget(self.widget_4)

        self.groupRobotConnection = QFrame(self.wgJoggingScrollWidget)
        self.groupRobotConnection.setObjectName(u"groupRobotConnection")
        sizePolicy10.setHeightForWidth(self.groupRobotConnection.sizePolicy().hasHeightForWidth())
        self.groupRobotConnection.setSizePolicy(sizePolicy10)
        self.groupRobotConnection.setMaximumSize(QSize(16777215, 16777215))
        self.groupRobotConnection.setFont(font8)
        self.groupRobotConnection.setStyleSheet(u"")
        self.horizontalLayout_14 = QHBoxLayout(self.groupRobotConnection)
        self.horizontalLayout_14.setSpacing(5)
        self.horizontalLayout_14.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_14.setObjectName(u"horizontalLayout_14")
        self.horizontalLayout_14.setContentsMargins(30, 0, -1, 5)
        self.verticalLayout_12 = QVBoxLayout()
        self.verticalLayout_12.setSpacing(6)
        self.verticalLayout_12.setObjectName(u"verticalLayout_12")
        self.pbConnect = QPushButton(self.groupRobotConnection)
        self.pbConnect.setObjectName(u"pbConnect")
        self.pbConnect.setMinimumSize(QSize(0, 30))
        self.pbConnect.setFont(font10)
        self.pbConnect.setStyleSheet(u"QPushButton\n"
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
"")
        icon37 = QIcon()
        icon37.addFile(u"C:/Users/Admin/.designer/backup/icon/disconnected.png", QSize(), QIcon.Normal, QIcon.Off)
        icon37.addFile(u"C:/Users/Admin/.designer/backup/icon/connected.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbConnect.setIcon(icon37)
        self.pbConnect.setIconSize(QSize(30, 20))
        self.pbConnect.setCheckable(True)

        self.verticalLayout_12.addWidget(self.pbConnect)

        self.cbAutoConnect = QCheckBox(self.groupRobotConnection)
        self.cbAutoConnect.setObjectName(u"cbAutoConnect")
        self.cbAutoConnect.setFont(font8)
        self.cbAutoConnect.setStyleSheet(u"")
        self.cbAutoConnect.setChecked(True)

        self.verticalLayout_12.addWidget(self.cbAutoConnect)


        self.horizontalLayout_14.addLayout(self.verticalLayout_12)

        self.fRobotPosition = QFrame(self.groupRobotConnection)
        self.fRobotPosition.setObjectName(u"fRobotPosition")
        self.fRobotPosition.setMinimumSize(QSize(0, 40))
        self.fRobotPosition.setMaximumSize(QSize(16777215, 16777215))
        self.fRobotPosition.setStyleSheet(u"QLabel\n"
"{	\n"
"	background-color: rgb(239, 252, 255);\n"
"	color: rgb(33, 125, 206)\n"
"}")
        self.gridLayout_19 = QGridLayout(self.fRobotPosition)
        self.gridLayout_19.setSpacing(7)
        self.gridLayout_19.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_19.setObjectName(u"gridLayout_19")
        self.gridLayout_19.setContentsMargins(0, 0, -1, 0)
        self.lbComName = QLabel(self.fRobotPosition)
        self.lbComName.setObjectName(u"lbComName")
        self.lbComName.setFont(font8)
        self.lbComName.setStyleSheet(u"")

        self.gridLayout_19.addWidget(self.lbComName, 1, 0, 1, 1)

        self.label_10 = QLabel(self.fRobotPosition)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setFont(font2)
        self.label_10.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_10, 0, 0, 1, 1)

        self.label_91 = QLabel(self.fRobotPosition)
        self.label_91.setObjectName(u"label_91")
        self.label_91.setFont(font2)
        self.label_91.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_91, 0, 2, 1, 1)

        self.cbRobotDOF = QComboBox(self.fRobotPosition)
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.setObjectName(u"cbRobotDOF")
        self.cbRobotDOF.setMinimumSize(QSize(80, 0))

        self.gridLayout_19.addWidget(self.cbRobotDOF, 1, 3, 1, 1)

        self.lbBaudrate = QLabel(self.fRobotPosition)
        self.lbBaudrate.setObjectName(u"lbBaudrate")
        self.lbBaudrate.setFont(font8)
        self.lbBaudrate.setStyleSheet(u"")

        self.gridLayout_19.addWidget(self.lbBaudrate, 1, 1, 1, 1)

        self.label_65 = QLabel(self.fRobotPosition)
        self.label_65.setObjectName(u"label_65")
        self.label_65.setFont(font2)
        self.label_65.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_65, 0, 1, 1, 1)

        self.cbRobotModel = QComboBox(self.fRobotPosition)
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.setObjectName(u"cbRobotModel")
        self.cbRobotModel.setMinimumSize(QSize(80, 0))

        self.gridLayout_19.addWidget(self.cbRobotModel, 1, 2, 1, 1)

        self.label_113 = QLabel(self.fRobotPosition)
        self.label_113.setObjectName(u"label_113")
        self.label_113.setFont(font2)
        self.label_113.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_113, 0, 3, 1, 1)


        self.horizontalLayout_14.addWidget(self.fRobotPosition)

        self.horizontalSpacer_4 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_14.addItem(self.horizontalSpacer_4)

        self.frameRobotConnection = QFrame(self.groupRobotConnection)
        self.frameRobotConnection.setObjectName(u"frameRobotConnection")
        self.frameRobotConnection.setMinimumSize(QSize(0, 50))
        self.frameRobotConnection.setMaximumSize(QSize(16777215, 50))
        self.frameRobotConnection.setFont(font12)
        self.frameRobotConnection.setStyleSheet(u"border: none;")
        self.frameRobotConnection.setFrameShape(QFrame.StyledPanel)
        self.frameRobotConnection.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_13 = QHBoxLayout(self.frameRobotConnection)
        self.horizontalLayout_13.setSpacing(0)
        self.horizontalLayout_13.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.horizontalLayout_13.setContentsMargins(0, 0, 0, 0)

        self.horizontalLayout_14.addWidget(self.frameRobotConnection)


        self.verticalLayout_5.addWidget(self.groupRobotConnection)

        self.frame_9 = QFrame(self.wgJoggingScrollWidget)
        self.frame_9.setObjectName(u"frame_9")
        self.frame_9.setMinimumSize(QSize(0, 50))
        self.frame_9.setStyleSheet(u"QLabel\n"
"{	\n"
"	background-color: rgb(239, 252, 255);\n"
"	color: rgb(33, 125, 206)\n"
"}")
        self.frame_9.setFrameShape(QFrame.StyledPanel)
        self.frame_9.setFrameShadow(QFrame.Raised)
        self.gridLayout_31 = QGridLayout(self.frame_9)
        self.gridLayout_31.setSpacing(6)
        self.gridLayout_31.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_31.setObjectName(u"gridLayout_31")
        self.label_94 = QLabel(self.frame_9)
        self.label_94.setObjectName(u"label_94")
        self.label_94.setMinimumSize(QSize(0, 20))
        self.label_94.setFont(font2)
        self.label_94.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_94, 0, 8, 1, 1)

        self.tbRequestPosition = QToolButton(self.frame_9)
        self.tbRequestPosition.setObjectName(u"tbRequestPosition")
        sizePolicy.setHeightForWidth(self.tbRequestPosition.sizePolicy().hasHeightForWidth())
        self.tbRequestPosition.setSizePolicy(sizePolicy)
        self.tbRequestPosition.setMinimumSize(QSize(20, 20))
        icon38 = QIcon()
        icon38.addFile(u":/icon/icons8_my_location_52px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbRequestPosition.setIcon(icon38)
        self.tbRequestPosition.setIconSize(QSize(32, 32))
        self.tbRequestPosition.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbRequestPosition.setAutoRaise(True)

        self.gridLayout_31.addWidget(self.tbRequestPosition, 0, 10, 2, 1)

        self.lbV = QLabel(self.frame_9)
        self.lbV.setObjectName(u"lbV")
        self.lbV.setMinimumSize(QSize(30, 20))
        self.lbV.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.lbV, 1, 8, 1, 1)

        self.horizontalSpacer_27 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_31.addItem(self.horizontalSpacer_27, 0, 11, 3, 1)

        self.lbY = QLabel(self.frame_9)
        self.lbY.setObjectName(u"lbY")
        self.lbY.setMinimumSize(QSize(30, 20))
        self.lbY.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.lbY, 1, 2, 1, 1)

        self.tbDisableRobot = QToolButton(self.frame_9)
        self.tbDisableRobot.setObjectName(u"tbDisableRobot")
        sizePolicy.setHeightForWidth(self.tbDisableRobot.sizePolicy().hasHeightForWidth())
        self.tbDisableRobot.setSizePolicy(sizePolicy)
        self.tbDisableRobot.setMinimumSize(QSize(20, 20))
        icon39 = QIcon()
        icon39.addFile(u":/icon/icons8_switch_off_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon39.addFile(u":/icon/icons8_switch_on_52px.png", QSize(), QIcon.Normal, QIcon.On)
        icon39.addFile(u":/icon/icons8_switch_on_52px.png", QSize(), QIcon.Active, QIcon.On)
        self.tbDisableRobot.setIcon(icon39)
        self.tbDisableRobot.setIconSize(QSize(32, 32))
        self.tbDisableRobot.setCheckable(True)
        self.tbDisableRobot.setChecked(True)
        self.tbDisableRobot.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbDisableRobot.setAutoRaise(True)

        self.gridLayout_31.addWidget(self.tbDisableRobot, 0, 9, 3, 1)

        self.lbZ = QLabel(self.frame_9)
        self.lbZ.setObjectName(u"lbZ")
        self.lbZ.setMinimumSize(QSize(30, 20))
        self.lbZ.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.lbZ, 1, 3, 1, 1)

        self.lbW = QLabel(self.frame_9)
        self.lbW.setObjectName(u"lbW")
        self.lbW.setMinimumSize(QSize(30, 20))
        self.lbW.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.lbW, 1, 5, 1, 1)

        self.label_92 = QLabel(self.frame_9)
        self.label_92.setObjectName(u"label_92")
        self.label_92.setMinimumSize(QSize(0, 20))
        self.label_92.setFont(font2)
        self.label_92.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_92, 0, 7, 1, 1)

        self.label_88 = QLabel(self.frame_9)
        self.label_88.setObjectName(u"label_88")
        self.label_88.setMinimumSize(QSize(0, 20))
        self.label_88.setFont(font2)
        self.label_88.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_88, 0, 3, 1, 1)

        self.label_84 = QLabel(self.frame_9)
        self.label_84.setObjectName(u"label_84")
        self.label_84.setMinimumSize(QSize(0, 20))
        self.label_84.setFont(font2)
        self.label_84.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_84, 0, 1, 1, 1)

        self.lbU = QLabel(self.frame_9)
        self.lbU.setObjectName(u"lbU")
        self.lbU.setMinimumSize(QSize(30, 20))
        self.lbU.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.lbU, 1, 7, 1, 1)

        self.lbX = QLabel(self.frame_9)
        self.lbX.setObjectName(u"lbX")
        self.lbX.setMinimumSize(QSize(30, 20))
        self.lbX.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.lbX, 1, 1, 1, 1)

        self.label_90 = QLabel(self.frame_9)
        self.label_90.setObjectName(u"label_90")
        self.label_90.setMinimumSize(QSize(0, 20))
        self.label_90.setFont(font2)
        self.label_90.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_90, 0, 5, 1, 2)

        self.label_86 = QLabel(self.frame_9)
        self.label_86.setObjectName(u"label_86")
        self.label_86.setMinimumSize(QSize(0, 20))
        self.label_86.setFont(font2)
        self.label_86.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_86, 0, 2, 1, 1)

        self.pbHome = QToolButton(self.frame_9)
        self.pbHome.setObjectName(u"pbHome")
        self.pbHome.setMinimumSize(QSize(60, 60))
        self.pbHome.setFont(font4)
        icon40 = QIcon()
        icon40.addFile(u":/icon/home.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbHome.setIcon(icon40)
        self.pbHome.setIconSize(QSize(40, 40))
        self.pbHome.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_31.addWidget(self.pbHome, 0, 0, 2, 1)


        self.verticalLayout_5.addWidget(self.frame_9)

        self.RobotTabWidget = QTabWidget(self.wgJoggingScrollWidget)
        self.RobotTabWidget.setObjectName(u"RobotTabWidget")
        self.RobotTabWidget.setMinimumSize(QSize(0, 300))
        self.MoveTab = QWidget()
        self.MoveTab.setObjectName(u"MoveTab")
        self.verticalLayout_53 = QVBoxLayout(self.MoveTab)
        self.verticalLayout_53.setSpacing(6)
        self.verticalLayout_53.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_53.setObjectName(u"verticalLayout_53")
        self.tabWidget_2 = QTabWidget(self.MoveTab)
        self.tabWidget_2.setObjectName(u"tabWidget_2")
        self.tabWidget_2.setStyleSheet(u"QFrame#ButtonGroupFrame{\n"
"	border: 1px solid rgb(118, 118, 118);\n"
"	border-radius: 5px;\n"
"}")
        self.tabWidget_2.setTabPosition(QTabWidget.North)
        self.tab_4 = QWidget()
        self.tab_4.setObjectName(u"tab_4")
        self.verticalLayout_16 = QVBoxLayout(self.tab_4)
        self.verticalLayout_16.setSpacing(6)
        self.verticalLayout_16.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_16.setObjectName(u"verticalLayout_16")
        self.framePositionParameter = QFrame(self.tab_4)
        self.framePositionParameter.setObjectName(u"framePositionParameter")
        self.framePositionParameter.setMaximumSize(QSize(460, 16777215))
        self.framePositionParameter.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(206, 206, 206);\n"
"}\n"
"QLabel\n"
"{\n"
"	border: none;\n"
"}")
        self.gridLayout_5 = QGridLayout(self.framePositionParameter)
        self.gridLayout_5.setSpacing(6)
        self.gridLayout_5.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_5.setObjectName(u"gridLayout_5")
        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setSpacing(10)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(5, 0, 5, 0)
        self.label_106 = QLabel(self.framePositionParameter)
        self.label_106.setObjectName(u"label_106")
        self.label_106.setFont(font6)

        self.horizontalLayout_2.addWidget(self.label_106)

        self.pbsubY = QPushButton(self.framePositionParameter)
        self.pbsubY.setObjectName(u"pbsubY")
        self.pbsubY.setMinimumSize(QSize(20, 20))
        self.pbsubY.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_2.addWidget(self.pbsubY)

        self.leY = QLineEdit(self.framePositionParameter)
        self.leY.setObjectName(u"leY")
        self.leY.setMinimumSize(QSize(50, 30))
        self.leY.setMaximumSize(QSize(70, 16777215))

        self.horizontalLayout_2.addWidget(self.leY)

        self.pbplusY = QPushButton(self.framePositionParameter)
        self.pbplusY.setObjectName(u"pbplusY")
        self.pbplusY.setMinimumSize(QSize(20, 20))
        self.pbplusY.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_2.addWidget(self.pbplusY)

        self.label_9 = QLabel(self.framePositionParameter)
        self.label_9.setObjectName(u"label_9")
        self.label_9.setMaximumSize(QSize(30, 16777215))

        self.horizontalLayout_2.addWidget(self.label_9)


        self.gridLayout_5.addLayout(self.horizontalLayout_2, 1, 0, 1, 1)

        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setSpacing(10)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(5, 0, 5, 0)
        self.label_40 = QLabel(self.framePositionParameter)
        self.label_40.setObjectName(u"label_40")
        self.label_40.setFont(font6)

        self.horizontalLayout.addWidget(self.label_40)

        self.pbsubX = QPushButton(self.framePositionParameter)
        self.pbsubX.setObjectName(u"pbsubX")
        self.pbsubX.setMinimumSize(QSize(20, 20))
        self.pbsubX.setMaximumSize(QSize(20, 20))

        self.horizontalLayout.addWidget(self.pbsubX)

        self.leX = QLineEdit(self.framePositionParameter)
        self.leX.setObjectName(u"leX")
        self.leX.setMinimumSize(QSize(20, 30))
        self.leX.setMaximumSize(QSize(70, 16777215))

        self.horizontalLayout.addWidget(self.leX)

        self.pbplusX = QPushButton(self.framePositionParameter)
        self.pbplusX.setObjectName(u"pbplusX")
        self.pbplusX.setMinimumSize(QSize(20, 20))
        self.pbplusX.setMaximumSize(QSize(20, 20))

        self.horizontalLayout.addWidget(self.pbplusX)

        self.label_8 = QLabel(self.framePositionParameter)
        self.label_8.setObjectName(u"label_8")
        self.label_8.setMaximumSize(QSize(30, 16777215))

        self.horizontalLayout.addWidget(self.label_8)


        self.gridLayout_5.addLayout(self.horizontalLayout, 0, 0, 1, 1)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setSpacing(10)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(5, 0, 5, 0)
        self.label_107 = QLabel(self.framePositionParameter)
        self.label_107.setObjectName(u"label_107")
        self.label_107.setFont(font6)

        self.horizontalLayout_3.addWidget(self.label_107)

        self.pbsubZ = QPushButton(self.framePositionParameter)
        self.pbsubZ.setObjectName(u"pbsubZ")
        self.pbsubZ.setMinimumSize(QSize(20, 20))
        self.pbsubZ.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_3.addWidget(self.pbsubZ)

        self.leZ = QLineEdit(self.framePositionParameter)
        self.leZ.setObjectName(u"leZ")
        self.leZ.setMinimumSize(QSize(50, 30))
        self.leZ.setMaximumSize(QSize(70, 16777215))

        self.horizontalLayout_3.addWidget(self.leZ)

        self.pbplusZ = QPushButton(self.framePositionParameter)
        self.pbplusZ.setObjectName(u"pbplusZ")
        self.pbplusZ.setMinimumSize(QSize(20, 20))
        self.pbplusZ.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_3.addWidget(self.pbplusZ)

        self.label_66 = QLabel(self.framePositionParameter)
        self.label_66.setObjectName(u"label_66")
        self.label_66.setMaximumSize(QSize(30, 16777215))

        self.horizontalLayout_3.addWidget(self.label_66)


        self.gridLayout_5.addLayout(self.horizontalLayout_3, 2, 0, 1, 1)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setSpacing(10)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(5, 0, 5, 0)
        self.label_108 = QLabel(self.framePositionParameter)
        self.label_108.setObjectName(u"label_108")
        self.label_108.setFont(font6)

        self.horizontalLayout_4.addWidget(self.label_108)

        self.pbsubW = QPushButton(self.framePositionParameter)
        self.pbsubW.setObjectName(u"pbsubW")
        self.pbsubW.setMinimumSize(QSize(20, 20))
        self.pbsubW.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_4.addWidget(self.pbsubW)

        self.leW = QLineEdit(self.framePositionParameter)
        self.leW.setObjectName(u"leW")
        self.leW.setMinimumSize(QSize(50, 30))
        self.leW.setMaximumSize(QSize(70, 16777215))

        self.horizontalLayout_4.addWidget(self.leW)

        self.pbplusW = QPushButton(self.framePositionParameter)
        self.pbplusW.setObjectName(u"pbplusW")
        self.pbplusW.setMinimumSize(QSize(20, 20))
        self.pbplusW.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_4.addWidget(self.pbplusW)

        self.label_81 = QLabel(self.framePositionParameter)
        self.label_81.setObjectName(u"label_81")
        self.label_81.setMaximumSize(QSize(30, 16777215))

        self.horizontalLayout_4.addWidget(self.label_81)


        self.gridLayout_5.addLayout(self.horizontalLayout_4, 0, 1, 1, 1)

        self.horizontalLayout_32 = QHBoxLayout()
        self.horizontalLayout_32.setSpacing(10)
        self.horizontalLayout_32.setObjectName(u"horizontalLayout_32")
        self.horizontalLayout_32.setContentsMargins(5, 0, 5, 0)
        self.label_111 = QLabel(self.framePositionParameter)
        self.label_111.setObjectName(u"label_111")
        self.label_111.setFont(font6)

        self.horizontalLayout_32.addWidget(self.label_111)

        self.pbsubU = QPushButton(self.framePositionParameter)
        self.pbsubU.setObjectName(u"pbsubU")
        self.pbsubU.setMinimumSize(QSize(20, 20))
        self.pbsubU.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_32.addWidget(self.pbsubU)

        self.leU = QLineEdit(self.framePositionParameter)
        self.leU.setObjectName(u"leU")
        self.leU.setMinimumSize(QSize(50, 30))
        self.leU.setMaximumSize(QSize(70, 16777215))

        self.horizontalLayout_32.addWidget(self.leU)

        self.pbplusU = QPushButton(self.framePositionParameter)
        self.pbplusU.setObjectName(u"pbplusU")
        self.pbplusU.setMinimumSize(QSize(20, 20))
        self.pbplusU.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_32.addWidget(self.pbplusU)

        self.label_87 = QLabel(self.framePositionParameter)
        self.label_87.setObjectName(u"label_87")
        self.label_87.setMaximumSize(QSize(30, 16777215))

        self.horizontalLayout_32.addWidget(self.label_87)


        self.gridLayout_5.addLayout(self.horizontalLayout_32, 1, 1, 1, 1)

        self.horizontalLayout_33 = QHBoxLayout()
        self.horizontalLayout_33.setSpacing(10)
        self.horizontalLayout_33.setObjectName(u"horizontalLayout_33")
        self.horizontalLayout_33.setContentsMargins(5, 0, 5, 0)
        self.label_112 = QLabel(self.framePositionParameter)
        self.label_112.setObjectName(u"label_112")
        self.label_112.setFont(font6)

        self.horizontalLayout_33.addWidget(self.label_112)

        self.pbsubV = QPushButton(self.framePositionParameter)
        self.pbsubV.setObjectName(u"pbsubV")
        self.pbsubV.setMinimumSize(QSize(20, 20))
        self.pbsubV.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_33.addWidget(self.pbsubV)

        self.leV = QLineEdit(self.framePositionParameter)
        self.leV.setObjectName(u"leV")
        self.leV.setMinimumSize(QSize(50, 30))
        self.leV.setMaximumSize(QSize(70, 16777215))

        self.horizontalLayout_33.addWidget(self.leV)

        self.pbplusV = QPushButton(self.framePositionParameter)
        self.pbplusV.setObjectName(u"pbplusV")
        self.pbplusV.setMinimumSize(QSize(20, 20))
        self.pbplusV.setMaximumSize(QSize(20, 20))

        self.horizontalLayout_33.addWidget(self.pbplusV)

        self.label_89 = QLabel(self.framePositionParameter)
        self.label_89.setObjectName(u"label_89")
        self.label_89.setMaximumSize(QSize(30, 16777215))

        self.horizontalLayout_33.addWidget(self.label_89)


        self.gridLayout_5.addLayout(self.horizontalLayout_33, 2, 1, 1, 1)


        self.verticalLayout_16.addWidget(self.framePositionParameter)

        self.gridLayout = QGridLayout()
        self.gridLayout.setSpacing(6)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(10, -1, 0, -1)
        self.label_29 = QLabel(self.tab_4)
        self.label_29.setObjectName(u"label_29")
        self.label_29.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_29, 0, 0, 1, 1)

        self.label_116 = QLabel(self.tab_4)
        self.label_116.setObjectName(u"label_116")
        self.label_116.setMaximumSize(QSize(60, 16777215))
        self.label_116.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_116, 1, 3, 1, 1)

        self.label_63 = QLabel(self.tab_4)
        self.label_63.setObjectName(u"label_63")
        self.label_63.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_63, 0, 5, 1, 1)

        self.leAccel = QLineEdit(self.tab_4)
        self.leAccel.setObjectName(u"leAccel")
        self.leAccel.setMinimumSize(QSize(0, 30))
        self.leAccel.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leAccel, 1, 1, 1, 1)

        self.label_32 = QLabel(self.tab_4)
        self.label_32.setObjectName(u"label_32")
        self.label_32.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_32, 1, 2, 1, 1)

        self.label_117 = QLabel(self.tab_4)
        self.label_117.setObjectName(u"label_117")
        self.label_117.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_117, 1, 5, 1, 1)

        self.leVelocity = QLineEdit(self.tab_4)
        self.leVelocity.setObjectName(u"leVelocity")
        self.leVelocity.setMinimumSize(QSize(0, 30))
        self.leVelocity.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leVelocity, 0, 1, 1, 1)

        self.leStartSpeed = QLineEdit(self.tab_4)
        self.leStartSpeed.setObjectName(u"leStartSpeed")
        self.leStartSpeed.setMinimumSize(QSize(0, 30))
        self.leStartSpeed.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leStartSpeed, 0, 4, 1, 1)

        self.label_62 = QLabel(self.tab_4)
        self.label_62.setObjectName(u"label_62")
        self.label_62.setMaximumSize(QSize(60, 16777215))
        self.label_62.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_62, 0, 3, 1, 1)

        self.verticalSpacer_5 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.gridLayout.addItem(self.verticalSpacer_5, 5, 1, 1, 1)

        self.leEndSpeed = QLineEdit(self.tab_4)
        self.leEndSpeed.setObjectName(u"leEndSpeed")
        self.leEndSpeed.setMinimumSize(QSize(0, 30))
        self.leEndSpeed.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leEndSpeed, 1, 4, 1, 1)

        self.label_30 = QLabel(self.tab_4)
        self.label_30.setObjectName(u"label_30")
        self.label_30.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_30, 0, 2, 1, 1)

        self.label_31 = QLabel(self.tab_4)
        self.label_31.setObjectName(u"label_31")
        self.label_31.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_31, 1, 0, 1, 1)

        self.label_64 = QLabel(self.tab_4)
        self.label_64.setObjectName(u"label_64")
        self.label_64.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_64, 2, 2, 1, 1)

        self.label_47 = QLabel(self.tab_4)
        self.label_47.setObjectName(u"label_47")
        self.label_47.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_47, 2, 0, 1, 1)

        self.leJerk = QLineEdit(self.tab_4)
        self.leJerk.setObjectName(u"leJerk")
        self.leJerk.setMinimumSize(QSize(0, 30))
        self.leJerk.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leJerk, 2, 1, 1, 1)


        self.verticalLayout_16.addLayout(self.gridLayout)

        self.tabWidget_2.addTab(self.tab_4, "")
        self.ButtonTab = QWidget()
        self.ButtonTab.setObjectName(u"ButtonTab")
        self.cbDivision = QComboBox(self.ButtonTab)
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.setObjectName(u"cbDivision")
        self.cbDivision.setGeometry(QRect(115, 15, 41, 22))
        self.cbDivision.setMinimumSize(QSize(0, 20))
        self.cbDivision.setMaximumSize(QSize(100, 16777215))
        self.cbDivision.setSizeAdjustPolicy(QComboBox.AdjustToContents)
        self.label_33 = QLabel(self.ButtonTab)
        self.label_33.setObjectName(u"label_33")
        self.label_33.setGeometry(QRect(20, 15, 86, 19))
        self.label_33.setMaximumSize(QSize(120, 16777215))
        self.layoutWidget = QWidget(self.ButtonTab)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.layoutWidget.setGeometry(QRect(75, 45, 209, 147))
        self.gridLayout_2 = QGridLayout(self.layoutWidget)
        self.gridLayout_2.setSpacing(5)
        self.gridLayout_2.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.pbLeft = QToolButton(self.layoutWidget)
        self.pbLeft.setObjectName(u"pbLeft")
        icon41 = QIcon()
        icon41.addFile(u":/icon/icons8-back-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLeft.setIcon(icon41)
        self.pbLeft.setIconSize(QSize(40, 40))
        self.pbLeft.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbLeft, 0, 2, 2, 1)

        self.pbRight = QToolButton(self.layoutWidget)
        self.pbRight.setObjectName(u"pbRight")
        icon42 = QIcon()
        icon42.addFile(u":/icon/icons8-forward-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbRight.setIcon(icon42)
        self.pbRight.setIconSize(QSize(40, 40))
        self.pbRight.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbRight, 0, 4, 2, 1)

        self.pbBackward = QToolButton(self.layoutWidget)
        self.pbBackward.setObjectName(u"pbBackward")
        icon43 = QIcon()
        icon43.addFile(u":/icon/icons8-expand-arrow-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbBackward.setIcon(icon43)
        self.pbBackward.setIconSize(QSize(40, 40))
        self.pbBackward.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbBackward, 1, 3, 1, 1)

        self.pbForward = QToolButton(self.layoutWidget)
        self.pbForward.setObjectName(u"pbForward")
        self.pbForward.setStyleSheet(u"")
        icon44 = QIcon()
        icon44.addFile(u":/icon/icons8-collapse-arrow-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbForward.setIcon(icon44)
        self.pbForward.setIconSize(QSize(40, 40))
        self.pbForward.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbForward, 0, 3, 1, 1)

        self.pbSubRoll = QToolButton(self.ButtonTab)
        self.pbSubRoll.setObjectName(u"pbSubRoll")
        self.pbSubRoll.setGeometry(QRect(80, 205, 48, 70))
        self.pbSubRoll.setIcon(icon41)
        self.pbSubRoll.setIconSize(QSize(40, 40))
        self.pbSubRoll.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbPlusRoll = QToolButton(self.ButtonTab)
        self.pbPlusRoll.setObjectName(u"pbPlusRoll")
        self.pbPlusRoll.setGeometry(QRect(80, 285, 48, 70))
        self.pbPlusRoll.setIcon(icon42)
        self.pbPlusRoll.setIconSize(QSize(40, 40))
        self.pbPlusRoll.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbPlusYaw = QToolButton(self.ButtonTab)
        self.pbPlusYaw.setObjectName(u"pbPlusYaw")
        self.pbPlusYaw.setGeometry(QRect(155, 285, 48, 70))
        self.pbPlusYaw.setIcon(icon42)
        self.pbPlusYaw.setIconSize(QSize(40, 40))
        self.pbPlusYaw.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbSubYaw = QToolButton(self.ButtonTab)
        self.pbSubYaw.setObjectName(u"pbSubYaw")
        self.pbSubYaw.setGeometry(QRect(155, 205, 48, 70))
        self.pbSubYaw.setIcon(icon41)
        self.pbSubYaw.setIconSize(QSize(40, 40))
        self.pbSubYaw.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbPlusPitch = QToolButton(self.ButtonTab)
        self.pbPlusPitch.setObjectName(u"pbPlusPitch")
        self.pbPlusPitch.setGeometry(QRect(230, 285, 48, 70))
        self.pbPlusPitch.setIcon(icon42)
        self.pbPlusPitch.setIconSize(QSize(40, 40))
        self.pbPlusPitch.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbSubPitch = QToolButton(self.ButtonTab)
        self.pbSubPitch.setObjectName(u"pbSubPitch")
        self.pbSubPitch.setGeometry(QRect(230, 205, 48, 70))
        self.pbSubPitch.setIcon(icon41)
        self.pbSubPitch.setIconSize(QSize(40, 40))
        self.pbSubPitch.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDown = QToolButton(self.ButtonTab)
        self.pbDown.setObjectName(u"pbDown")
        self.pbDown.setGeometry(QRect(315, 120, 48, 67))
        self.pbDown.setIcon(icon43)
        self.pbDown.setIconSize(QSize(40, 40))
        self.pbDown.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbUp = QToolButton(self.ButtonTab)
        self.pbUp.setObjectName(u"pbUp")
        self.pbUp.setGeometry(QRect(315, 45, 48, 67))
        self.pbUp.setIcon(icon44)
        self.pbUp.setIconSize(QSize(40, 40))
        self.pbUp.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbUp.setAutoRaise(False)
        self.tabWidget_2.addTab(self.ButtonTab, "")
        self.SliderTab = QWidget()
        self.SliderTab.setObjectName(u"SliderTab")
        self.verticalLayout_55 = QVBoxLayout(self.SliderTab)
        self.verticalLayout_55.setSpacing(6)
        self.verticalLayout_55.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_55.setObjectName(u"verticalLayout_55")
        self.scrollArea_3 = QScrollArea(self.SliderTab)
        self.scrollArea_3.setObjectName(u"scrollArea_3")
        self.scrollArea_3.setWidgetResizable(True)
        self.scrollAreaWidgetContents_3 = QWidget()
        self.scrollAreaWidgetContents_3.setObjectName(u"scrollAreaWidgetContents_3")
        self.scrollAreaWidgetContents_3.setGeometry(QRect(0, 0, 109, 300))
        self.scrollAreaWidgetContents_3.setMinimumSize(QSize(0, 300))
        self.scrollAreaWidgetContents_3.setMaximumSize(QSize(16777215, 600))
        self.verticalLayout_44 = QVBoxLayout(self.scrollAreaWidgetContents_3)
        self.verticalLayout_44.setSpacing(6)
        self.verticalLayout_44.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_44.setObjectName(u"verticalLayout_44")
        self.frame = QFrame(self.scrollAreaWidgetContents_3)
        self.frame.setObjectName(u"frame")
        self.frame.setMaximumSize(QSize(200, 16777215))
        self.gridLayout_10 = QGridLayout(self.frame)
        self.gridLayout_10.setSpacing(6)
        self.gridLayout_10.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_10.setObjectName(u"gridLayout_10")
        self.label_53 = QLabel(self.frame)
        self.label_53.setObjectName(u"label_53")
        self.label_53.setMaximumSize(QSize(40, 16777215))

        self.gridLayout_10.addWidget(self.label_53, 1, 0, 1, 1)

        self.cbWorkingSize = QComboBox(self.frame)
        self.cbWorkingSize.addItem("")
        self.cbWorkingSize.addItem("")
        self.cbWorkingSize.addItem("")
        self.cbWorkingSize.addItem("")
        self.cbWorkingSize.setObjectName(u"cbWorkingSize")
        self.cbWorkingSize.setMinimumSize(QSize(60, 0))
        self.cbWorkingSize.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_10.addWidget(self.cbWorkingSize, 1, 1, 1, 1)


        self.verticalLayout_44.addWidget(self.frame)

        self.fXYWorkingArea = QWidget(self.scrollAreaWidgetContents_3)
        self.fXYWorkingArea.setObjectName(u"fXYWorkingArea")
        self.fXYWorkingArea.setMinimumSize(QSize(0, 320))
        self.wg2D = QWidget(self.fXYWorkingArea)
        self.wg2D.setObjectName(u"wg2D")
        self.wg2D.setGeometry(QRect(30, 5, 200, 200))
        sizePolicy13.setHeightForWidth(self.wg2D.sizePolicy().hasHeightForWidth())
        self.wg2D.setSizePolicy(sizePolicy13)
        self.wg2D.setMinimumSize(QSize(200, 200))
        self.wg2D.setMaximumSize(QSize(16777215, 16777215))
        self.wg2D.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_15 = QLabel(self.fXYWorkingArea)
        self.label_15.setObjectName(u"label_15")
        self.label_15.setGeometry(QRect(6, 210, 16, 19))
        sizePolicy16 = QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Preferred)
        sizePolicy16.setHorizontalStretch(0)
        sizePolicy16.setVerticalStretch(0)
        sizePolicy16.setHeightForWidth(self.label_15.sizePolicy().hasHeightForWidth())
        self.label_15.setSizePolicy(sizePolicy16)
        self.vsZAdjsution = QSlider(self.fXYWorkingArea)
        self.vsZAdjsution.setObjectName(u"vsZAdjsution")
        self.vsZAdjsution.setGeometry(QRect(6, 6, 16, 201))
        sizePolicy7.setHeightForWidth(self.vsZAdjsution.sizePolicy().hasHeightForWidth())
        self.vsZAdjsution.setSizePolicy(sizePolicy7)
        self.vsZAdjsution.setMaximum(300)
        self.vsZAdjsution.setOrientation(Qt.Vertical)
        self.layoutWidget1 = QWidget(self.fXYWorkingArea)
        self.layoutWidget1.setObjectName(u"layoutWidget1")
        self.layoutWidget1.setGeometry(QRect(255, 10, 102, 296))
        self.gridLayout_17 = QGridLayout(self.layoutWidget1)
        self.gridLayout_17.setSpacing(6)
        self.gridLayout_17.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_17.setObjectName(u"gridLayout_17")
        self.gridLayout_17.setContentsMargins(0, 0, 0, 0)
        self.label_72 = QLabel(self.layoutWidget1)
        self.label_72.setObjectName(u"label_72")
        self.label_72.setAlignment(Qt.AlignCenter)

        self.gridLayout_17.addWidget(self.label_72, 5, 0, 1, 1)

        self.d5axis = QDial(self.layoutWidget1)
        self.d5axis.setObjectName(u"d5axis")
        self.d5axis.setMinimum(-180)
        self.d5axis.setMaximum(180)
        self.d5axis.setOrientation(Qt.Horizontal)
        self.d5axis.setInvertedAppearance(False)
        self.d5axis.setInvertedControls(False)
        self.d5axis.setWrapping(False)
        self.d5axis.setNotchesVisible(False)

        self.gridLayout_17.addWidget(self.d5axis, 2, 0, 1, 1)

        self.d6axis = QDial(self.layoutWidget1)
        self.d6axis.setObjectName(u"d6axis")
        self.d6axis.setMinimum(-180)
        self.d6axis.setMaximum(180)
        self.d6axis.setOrientation(Qt.Horizontal)
        self.d6axis.setInvertedAppearance(False)
        self.d6axis.setInvertedControls(False)
        self.d6axis.setWrapping(False)
        self.d6axis.setNotchesVisible(False)

        self.gridLayout_17.addWidget(self.d6axis, 4, 0, 1, 1)

        self.label_69 = QLabel(self.layoutWidget1)
        self.label_69.setObjectName(u"label_69")
        self.label_69.setAlignment(Qt.AlignCenter)

        self.gridLayout_17.addWidget(self.label_69, 1, 0, 1, 1)

        self.label_71 = QLabel(self.layoutWidget1)
        self.label_71.setObjectName(u"label_71")
        self.label_71.setAlignment(Qt.AlignCenter)

        self.gridLayout_17.addWidget(self.label_71, 3, 0, 1, 1)

        self.d4axis = QDial(self.layoutWidget1)
        self.d4axis.setObjectName(u"d4axis")
        self.d4axis.setMinimum(-180)
        self.d4axis.setMaximum(180)
        self.d4axis.setOrientation(Qt.Horizontal)
        self.d4axis.setInvertedAppearance(False)
        self.d4axis.setInvertedControls(False)
        self.d4axis.setWrapping(False)
        self.d4axis.setNotchesVisible(False)

        self.gridLayout_17.addWidget(self.d4axis, 0, 0, 1, 1)

        self.lb4AxisValue = QLabel(self.layoutWidget1)
        self.lb4AxisValue.setObjectName(u"lb4AxisValue")

        self.gridLayout_17.addWidget(self.lb4AxisValue, 0, 1, 1, 1)

        self.lb5AxisValue = QLabel(self.layoutWidget1)
        self.lb5AxisValue.setObjectName(u"lb5AxisValue")

        self.gridLayout_17.addWidget(self.lb5AxisValue, 2, 1, 1, 1)

        self.lb6AxisValue = QLabel(self.layoutWidget1)
        self.lb6AxisValue.setObjectName(u"lb6AxisValue")

        self.gridLayout_17.addWidget(self.lb6AxisValue, 4, 1, 1, 1)


        self.verticalLayout_44.addWidget(self.fXYWorkingArea)

        self.gridLayout_9 = QGridLayout()
        self.gridLayout_9.setSpacing(6)
        self.gridLayout_9.setObjectName(u"gridLayout_9")
        self.label_60 = QLabel(self.scrollAreaWidgetContents_3)
        self.label_60.setObjectName(u"label_60")

        self.gridLayout_9.addWidget(self.label_60, 1, 0, 1, 1)

        self.label_61 = QLabel(self.scrollAreaWidgetContents_3)
        self.label_61.setObjectName(u"label_61")

        self.gridLayout_9.addWidget(self.label_61, 2, 0, 1, 1)

        self.vs6AxisAdjsution = QSlider(self.scrollAreaWidgetContents_3)
        self.vs6AxisAdjsution.setObjectName(u"vs6AxisAdjsution")
        self.vs6AxisAdjsution.setMinimumSize(QSize(0, 30))
        self.vs6AxisAdjsution.setMinimum(-180)
        self.vs6AxisAdjsution.setMaximum(180)
        self.vs6AxisAdjsution.setValue(0)
        self.vs6AxisAdjsution.setOrientation(Qt.Horizontal)

        self.gridLayout_9.addWidget(self.vs6AxisAdjsution, 2, 1, 1, 1)

        self.label_16 = QLabel(self.scrollAreaWidgetContents_3)
        self.label_16.setObjectName(u"label_16")

        self.gridLayout_9.addWidget(self.label_16, 0, 0, 1, 1)

        self.vs5AxisAdjsution = QSlider(self.scrollAreaWidgetContents_3)
        self.vs5AxisAdjsution.setObjectName(u"vs5AxisAdjsution")
        self.vs5AxisAdjsution.setMinimumSize(QSize(0, 30))
        self.vs5AxisAdjsution.setMinimum(-180)
        self.vs5AxisAdjsution.setMaximum(180)
        self.vs5AxisAdjsution.setValue(0)
        self.vs5AxisAdjsution.setOrientation(Qt.Horizontal)

        self.gridLayout_9.addWidget(self.vs5AxisAdjsution, 1, 1, 1, 1)

        self.vsAngleAdjsution = QSlider(self.scrollAreaWidgetContents_3)
        self.vsAngleAdjsution.setObjectName(u"vsAngleAdjsution")
        self.vsAngleAdjsution.setMinimumSize(QSize(0, 30))
        self.vsAngleAdjsution.setMinimum(-360)
        self.vsAngleAdjsution.setMaximum(360)
        self.vsAngleAdjsution.setValue(0)
        self.vsAngleAdjsution.setOrientation(Qt.Horizontal)

        self.gridLayout_9.addWidget(self.vsAngleAdjsution, 0, 1, 1, 1)


        self.verticalLayout_44.addLayout(self.gridLayout_9)

        self.verticalSpacer_7 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_44.addItem(self.verticalSpacer_7)

        self.scrollArea_3.setWidget(self.scrollAreaWidgetContents_3)

        self.verticalLayout_55.addWidget(self.scrollArea_3)

        self.tabWidget_2.addTab(self.SliderTab, "")
        self.tab_2 = QWidget()
        self.tab_2.setObjectName(u"tab_2")
        self.verticalLayout_54 = QVBoxLayout(self.tab_2)
        self.verticalLayout_54.setSpacing(6)
        self.verticalLayout_54.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_54.setObjectName(u"verticalLayout_54")
        self.gbJoystick = QFrame(self.tab_2)
        self.gbJoystick.setObjectName(u"gbJoystick")
        self.gbJoystick.setMaximumSize(QSize(16777215, 16777215))
        self.gbJoystick.setFont(font6)
        self.verticalLayout_45 = QVBoxLayout(self.gbJoystick)
        self.verticalLayout_45.setSpacing(0)
        self.verticalLayout_45.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_45.setObjectName(u"verticalLayout_45")
        self.verticalLayout_45.setContentsMargins(0, 20, 0, 0)
        self.wgJoystickParameter = QWidget(self.gbJoystick)
        self.wgJoystickParameter.setObjectName(u"wgJoystickParameter")
        self.gridLayout_20 = QGridLayout(self.wgJoystickParameter)
        self.gridLayout_20.setSpacing(6)
        self.gridLayout_20.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_20.setObjectName(u"gridLayout_20")
        self.gridLayout_20.setSizeConstraint(QLayout.SetDefaultConstraint)
        self.gridLayout_20.setHorizontalSpacing(20)
        self.gridLayout_20.setVerticalSpacing(5)
        self.gridLayout_20.setContentsMargins(10, 10, 10, 10)
        self.label_79 = QLabel(self.wgJoystickParameter)
        self.label_79.setObjectName(u"label_79")
        self.label_79.setMaximumSize(QSize(300, 16777215))

        self.gridLayout_20.addWidget(self.label_79, 2, 0, 1, 1)

        self.cbJoystickDevice = QComboBox(self.wgJoystickParameter)
        self.cbJoystickDevice.setObjectName(u"cbJoystickDevice")
        self.cbJoystickDevice.setMinimumSize(QSize(0, 0))
        self.cbJoystickDevice.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_20.addWidget(self.cbJoystickDevice, 0, 1, 1, 1)

        self.label_41 = QLabel(self.wgJoystickParameter)
        self.label_41.setObjectName(u"label_41")
        self.label_41.setMaximumSize(QSize(300, 16777215))

        self.gridLayout_20.addWidget(self.label_41, 0, 0, 1, 1)

        self.leJoystickRange = QLineEdit(self.wgJoystickParameter)
        self.leJoystickRange.setObjectName(u"leJoystickRange")
        self.leJoystickRange.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_20.addWidget(self.leJoystickRange, 1, 1, 1, 1)

        self.leJoystickSensibility = QLineEdit(self.wgJoystickParameter)
        self.leJoystickSensibility.setObjectName(u"leJoystickSensibility")
        self.leJoystickSensibility.setMaximumSize(QSize(150, 16777215))

        self.gridLayout_20.addWidget(self.leJoystickSensibility, 2, 1, 1, 1)

        self.label_51 = QLabel(self.wgJoystickParameter)
        self.label_51.setObjectName(u"label_51")
        self.label_51.setMaximumSize(QSize(300, 16777215))

        self.gridLayout_20.addWidget(self.label_51, 1, 0, 1, 1)

        self.horizontalSpacer_32 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_20.addItem(self.horizontalSpacer_32, 0, 2, 1, 1)


        self.verticalLayout_45.addWidget(self.wgJoystickParameter)


        self.verticalLayout_54.addWidget(self.gbJoystick)

        self.verticalSpacer_8 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_54.addItem(self.verticalSpacer_8)

        self.tabWidget_2.addTab(self.tab_2, "")

        self.verticalLayout_53.addWidget(self.tabWidget_2)

        self.RobotTabWidget.addTab(self.MoveTab, "")
        self.IOTab = QWidget()
        self.IOTab.setObjectName(u"IOTab")
        self.verticalLayout_6 = QVBoxLayout(self.IOTab)
        self.verticalLayout_6.setSpacing(6)
        self.verticalLayout_6.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.tabWidget_3 = QTabWidget(self.IOTab)
        self.tabWidget_3.setObjectName(u"tabWidget_3")
        self.tabWidget_3.setTabPosition(QTabWidget.North)
        self.OutputTab = QWidget()
        self.OutputTab.setObjectName(u"OutputTab")
        self.verticalLayout_3 = QVBoxLayout(self.OutputTab)
        self.verticalLayout_3.setSpacing(6)
        self.verticalLayout_3.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.gbDeltaX12Output = QGroupBox(self.OutputTab)
        self.gbDeltaX12Output.setObjectName(u"gbDeltaX12Output")
        self.gbDeltaX12Output.setMinimumSize(QSize(0, 50))
        self.gbDeltaX12Output.setFont(font6)
        self.verticalLayout_20 = QVBoxLayout(self.gbDeltaX12Output)
        self.verticalLayout_20.setSpacing(6)
        self.verticalLayout_20.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_20.setObjectName(u"verticalLayout_20")
        self.wgOldOutput = QWidget(self.gbDeltaX12Output)
        self.wgOldOutput.setObjectName(u"wgOldOutput")
        self.horizontalLayout_7 = QHBoxLayout(self.wgOldOutput)
        self.horizontalLayout_7.setSpacing(6)
        self.horizontalLayout_7.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.gbRelay = QGroupBox(self.wgOldOutput)
        self.gbRelay.setObjectName(u"gbRelay")
        self.gbRelay.setMaximumSize(QSize(150, 16777215))
        self.gbRelay.setFont(font2)
        self.gridLayout_3 = QGridLayout(self.gbRelay)
        self.gridLayout_3.setSpacing(6)
        self.gridLayout_3.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.label_34 = QLabel(self.gbRelay)
        self.label_34.setObjectName(u"label_34")
        self.label_34.setMaximumSize(QSize(16777215, 20))
        self.label_34.setFont(font5)
        self.label_34.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_34, 0, 0, 1, 1)

        self.label_35 = QLabel(self.gbRelay)
        self.label_35.setObjectName(u"label_35")
        self.label_35.setMaximumSize(QSize(16777215, 20))
        self.label_35.setFont(font5)
        self.label_35.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_35, 0, 1, 1, 1)

        self.pbPump = QPushButton(self.gbRelay)
        self.pbPump.setObjectName(u"pbPump")
        self.pbPump.setMinimumSize(QSize(50, 30))
        self.pbPump.setAutoFillBackground(False)
        icon45 = QIcon()
        icon45.addFile(u":/icon/Toggle Off_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon45.addFile(u":/icon/Toggle On_16px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbPump.setIcon(icon45)
        self.pbPump.setIconSize(QSize(16, 16))
        self.pbPump.setCheckable(True)
        self.pbPump.setChecked(False)
        self.pbPump.setAutoDefault(False)
        self.pbPump.setFlat(False)

        self.gridLayout_3.addWidget(self.pbPump, 1, 0, 1, 1)

        self.pbLaser = QPushButton(self.gbRelay)
        self.pbLaser.setObjectName(u"pbLaser")
        self.pbLaser.setMinimumSize(QSize(50, 30))
        self.pbLaser.setAutoFillBackground(False)
        self.pbLaser.setIcon(icon45)
        self.pbLaser.setIconSize(QSize(16, 16))
        self.pbLaser.setCheckable(True)
        self.pbLaser.setChecked(False)
        self.pbLaser.setAutoDefault(False)
        self.pbLaser.setFlat(False)

        self.gridLayout_3.addWidget(self.pbLaser, 1, 1, 1, 1)


        self.horizontalLayout_7.addWidget(self.gbRelay)

        self.gbGripper = QGroupBox(self.wgOldOutput)
        self.gbGripper.setObjectName(u"gbGripper")
        self.gbGripper.setMaximumSize(QSize(250, 16777215))
        self.gbGripper.setFont(font2)
        self.gridLayout_13 = QGridLayout(self.gbGripper)
        self.gridLayout_13.setSpacing(6)
        self.gridLayout_13.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_13.setObjectName(u"gridLayout_13")
        self.gridLayout_13.setContentsMargins(-1, 20, -1, -1)
        self.gridLayout_6 = QGridLayout()
        self.gridLayout_6.setSpacing(6)
        self.gridLayout_6.setObjectName(u"gridLayout_6")
        self.label_17 = QLabel(self.gbGripper)
        self.label_17.setObjectName(u"label_17")
        self.label_17.setFont(font5)
        self.label_17.setAlignment(Qt.AlignCenter)

        self.gridLayout_6.addWidget(self.label_17, 0, 1, 1, 1)

        self.label_27 = QLabel(self.gbGripper)
        self.label_27.setObjectName(u"label_27")
        self.label_27.setFont(font5)
        self.label_27.setAlignment(Qt.AlignCenter)

        self.gridLayout_6.addWidget(self.label_27, 0, 2, 1, 1)

        self.pbGrip = QPushButton(self.gbGripper)
        self.pbGrip.setObjectName(u"pbGrip")
        self.pbGrip.setMinimumSize(QSize(60, 30))
        self.pbGrip.setMaximumSize(QSize(30, 16777215))
        self.pbGrip.setAutoFillBackground(False)
        self.pbGrip.setAutoDefault(False)
        self.pbGrip.setFlat(False)

        self.gridLayout_6.addWidget(self.pbGrip, 1, 0, 1, 1)

        self.leGripperMin = QLineEdit(self.gbGripper)
        self.leGripperMin.setObjectName(u"leGripperMin")
        self.leGripperMin.setMinimumSize(QSize(30, 30))
        self.leGripperMin.setMaximumSize(QSize(40, 16777215))

        self.gridLayout_6.addWidget(self.leGripperMin, 1, 1, 1, 1)

        self.leGripperMax = QLineEdit(self.gbGripper)
        self.leGripperMax.setObjectName(u"leGripperMax")
        self.leGripperMax.setMinimumSize(QSize(30, 30))
        self.leGripperMax.setMaximumSize(QSize(40, 16777215))

        self.gridLayout_6.addWidget(self.leGripperMax, 1, 2, 1, 1)


        self.gridLayout_13.addLayout(self.gridLayout_6, 0, 0, 1, 1)

        self.horizontalLayout_15 = QHBoxLayout()
        self.horizontalLayout_15.setSpacing(6)
        self.horizontalLayout_15.setObjectName(u"horizontalLayout_15")
        self.hsGripperAngle = QSlider(self.gbGripper)
        self.hsGripperAngle.setObjectName(u"hsGripperAngle")
        sizePolicy14.setHeightForWidth(self.hsGripperAngle.sizePolicy().hasHeightForWidth())
        self.hsGripperAngle.setSizePolicy(sizePolicy14)
        self.hsGripperAngle.setMinimumSize(QSize(0, 30))
        self.hsGripperAngle.setMaximum(20)
        self.hsGripperAngle.setSingleStep(5)
        self.hsGripperAngle.setOrientation(Qt.Horizontal)

        self.horizontalLayout_15.addWidget(self.hsGripperAngle)

        self.lbGripperValue = QLabel(self.gbGripper)
        self.lbGripperValue.setObjectName(u"lbGripperValue")
        self.lbGripperValue.setMinimumSize(QSize(40, 0))
        font14 = QFont()
        font14.setPointSize(7)
        font14.setBold(False)
        font14.setKerning(True)
        self.lbGripperValue.setFont(font14)

        self.horizontalLayout_15.addWidget(self.lbGripperValue)


        self.gridLayout_13.addLayout(self.horizontalLayout_15, 1, 0, 1, 1)


        self.horizontalLayout_7.addWidget(self.gbGripper)

        self.horizontalSpacer_46 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_7.addItem(self.horizontalSpacer_46)


        self.verticalLayout_20.addWidget(self.wgOldOutput)


        self.verticalLayout_3.addWidget(self.gbDeltaX12Output)

        self.gbOutput = QGroupBox(self.OutputTab)
        self.gbOutput.setObjectName(u"gbOutput")
        self.gbOutput.setMinimumSize(QSize(0, 180))
        self.gbOutput.setFont(font6)
        self.verticalLayout_42 = QVBoxLayout(self.gbOutput)
        self.verticalLayout_42.setSpacing(6)
        self.verticalLayout_42.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_42.setObjectName(u"verticalLayout_42")
        self.verticalLayout_42.setContentsMargins(-1, 20, -1, -1)
        self.wgRelayOutput = QWidget(self.gbOutput)
        self.wgRelayOutput.setObjectName(u"wgRelayOutput")
        self.wgRelayOutput.setMinimumSize(QSize(0, 40))
        self.gridLayout_35 = QGridLayout(self.wgRelayOutput)
        self.gridLayout_35.setSpacing(6)
        self.gridLayout_35.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_35.setObjectName(u"gridLayout_35")
        self.horizontalSpacer_47 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_35.addItem(self.horizontalSpacer_47, 0, 5, 1, 1)

        self.cbDx = QCheckBox(self.wgRelayOutput)
        self.cbDx.setObjectName(u"cbDx")
        self.cbDx.setMaximumSize(QSize(20, 16777215))

        self.gridLayout_35.addWidget(self.cbDx, 0, 1, 1, 1)

        self.cbRx = QCheckBox(self.wgRelayOutput)
        self.cbRx.setObjectName(u"cbRx")
        self.cbRx.setMaximumSize(QSize(20, 16777215))

        self.gridLayout_35.addWidget(self.cbRx, 0, 3, 1, 1)

        self.label_67 = QLabel(self.wgRelayOutput)
        self.label_67.setObjectName(u"label_67")
        self.label_67.setMinimumSize(QSize(70, 0))
        font15 = QFont()
        font15.setBold(False)
        self.label_67.setFont(font15)

        self.gridLayout_35.addWidget(self.label_67, 0, 0, 1, 1)

        self.leRx = QLineEdit(self.wgRelayOutput)
        self.leRx.setObjectName(u"leRx")
        self.leRx.setMaximumSize(QSize(30, 16777215))

        self.gridLayout_35.addWidget(self.leRx, 0, 4, 1, 1)

        self.leDx = QLineEdit(self.wgRelayOutput)
        self.leDx.setObjectName(u"leDx")
        self.leDx.setMaximumSize(QSize(30, 16777215))

        self.gridLayout_35.addWidget(self.leDx, 0, 2, 1, 1)


        self.verticalLayout_42.addWidget(self.wgRelayOutput)

        self.wgDigitalOutput = QWidget(self.gbOutput)
        self.wgDigitalOutput.setObjectName(u"wgDigitalOutput")
        self.wgDigitalOutput.setMinimumSize(QSize(0, 40))
        self.gridLayout_34 = QGridLayout(self.wgDigitalOutput)
        self.gridLayout_34.setSpacing(6)
        self.gridLayout_34.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_34.setObjectName(u"gridLayout_34")
        self.label_68 = QLabel(self.wgDigitalOutput)
        self.label_68.setObjectName(u"label_68")
        self.label_68.setMinimumSize(QSize(70, 0))
        self.label_68.setFont(font15)

        self.gridLayout_34.addWidget(self.label_68, 0, 0, 1, 1)

        self.horizontalSpacer_48 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_34.addItem(self.horizontalSpacer_48, 0, 9, 1, 1)

        self.cbD1 = QCheckBox(self.wgDigitalOutput)
        self.cbD1.setObjectName(u"cbD1")
        self.cbD1.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD1, 0, 2, 1, 1)

        self.cbD2 = QCheckBox(self.wgDigitalOutput)
        self.cbD2.setObjectName(u"cbD2")
        self.cbD2.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD2, 0, 3, 1, 1)

        self.cbD3 = QCheckBox(self.wgDigitalOutput)
        self.cbD3.setObjectName(u"cbD3")
        self.cbD3.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD3, 0, 4, 1, 1)

        self.cbD0 = QCheckBox(self.wgDigitalOutput)
        self.cbD0.setObjectName(u"cbD0")
        self.cbD0.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD0, 0, 1, 1, 1)

        self.horizontalSpacer_69 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_34.addItem(self.horizontalSpacer_69, 1, 9, 1, 1)

        self.cbD4 = QCheckBox(self.wgDigitalOutput)
        self.cbD4.setObjectName(u"cbD4")
        self.cbD4.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD4, 1, 1, 1, 1)

        self.cbD5 = QCheckBox(self.wgDigitalOutput)
        self.cbD5.setObjectName(u"cbD5")
        self.cbD5.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD5, 1, 2, 1, 1)

        self.cbD6 = QCheckBox(self.wgDigitalOutput)
        self.cbD6.setObjectName(u"cbD6")
        self.cbD6.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD6, 1, 3, 1, 1)

        self.cbD7 = QCheckBox(self.wgDigitalOutput)
        self.cbD7.setObjectName(u"cbD7")
        self.cbD7.setMinimumSize(QSize(45, 0))

        self.gridLayout_34.addWidget(self.cbD7, 1, 4, 1, 1)


        self.verticalLayout_42.addWidget(self.wgDigitalOutput)


        self.verticalLayout_3.addWidget(self.gbOutput)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_3.addItem(self.verticalSpacer)

        self.tabWidget_3.addTab(self.OutputTab, "")
        self.InputTab = QWidget()
        self.InputTab.setObjectName(u"InputTab")
        self.gbInput = QGroupBox(self.InputTab)
        self.gbInput.setObjectName(u"gbInput")
        self.gbInput.setGeometry(QRect(15, 15, 407, 380))
        self.gbInput.setMinimumSize(QSize(0, 380))
        self.gbInput.setFont(font6)
        self.verticalLayout_43 = QVBoxLayout(self.gbInput)
        self.verticalLayout_43.setSpacing(6)
        self.verticalLayout_43.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_43.setObjectName(u"verticalLayout_43")
        self.verticalLayout_43.setContentsMargins(-1, 20, -1, -1)
        self.horizontalLayout_37 = QHBoxLayout()
        self.horizontalLayout_37.setSpacing(6)
        self.horizontalLayout_37.setObjectName(u"horizontalLayout_37")
        self.label_70 = QLabel(self.gbInput)
        self.label_70.setObjectName(u"label_70")
        self.label_70.setMinimumSize(QSize(30, 0))
        self.label_70.setMaximumSize(QSize(25, 16777215))
        self.label_70.setFont(font15)

        self.horizontalLayout_37.addWidget(self.label_70)

        self.horizontalSpacer_16 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_37.addItem(self.horizontalSpacer_16)

        self.lbI0Value = QLabel(self.gbInput)
        self.lbI0Value.setObjectName(u"lbI0Value")

        self.horizontalLayout_37.addWidget(self.lbI0Value)

        self.horizontalSpacer_15 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_37.addItem(self.horizontalSpacer_15)

        self.cbToggle0 = QCheckBox(self.gbInput)
        self.cbToggle0.setObjectName(u"cbToggle0")
        self.cbToggle0.setMinimumSize(QSize(110, 0))
        self.cbToggle0.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_37.addWidget(self.cbToggle0)

        self.pbReadI0 = QPushButton(self.gbInput)
        self.pbReadI0.setObjectName(u"pbReadI0")
        self.pbReadI0.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_37.addWidget(self.pbReadI0)

        self.horizontalSpacer_51 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_37.addItem(self.horizontalSpacer_51)


        self.verticalLayout_43.addLayout(self.horizontalLayout_37)

        self.horizontalLayout_38 = QHBoxLayout()
        self.horizontalLayout_38.setSpacing(6)
        self.horizontalLayout_38.setObjectName(u"horizontalLayout_38")
        self.label_74 = QLabel(self.gbInput)
        self.label_74.setObjectName(u"label_74")
        self.label_74.setMinimumSize(QSize(30, 0))
        self.label_74.setMaximumSize(QSize(25, 16777215))
        self.label_74.setFont(font15)

        self.horizontalLayout_38.addWidget(self.label_74)

        self.horizontalSpacer_17 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_38.addItem(self.horizontalSpacer_17)

        self.lbI1Value = QLabel(self.gbInput)
        self.lbI1Value.setObjectName(u"lbI1Value")

        self.horizontalLayout_38.addWidget(self.lbI1Value)

        self.horizontalSpacer_18 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_38.addItem(self.horizontalSpacer_18)

        self.cbToggle1 = QCheckBox(self.gbInput)
        self.cbToggle1.setObjectName(u"cbToggle1")
        self.cbToggle1.setMinimumSize(QSize(110, 0))
        self.cbToggle1.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_38.addWidget(self.cbToggle1)

        self.pbReadI1 = QPushButton(self.gbInput)
        self.pbReadI1.setObjectName(u"pbReadI1")
        self.pbReadI1.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_38.addWidget(self.pbReadI1)

        self.horizontalSpacer_52 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_38.addItem(self.horizontalSpacer_52)


        self.verticalLayout_43.addLayout(self.horizontalLayout_38)

        self.horizontalLayout_39 = QHBoxLayout()
        self.horizontalLayout_39.setSpacing(6)
        self.horizontalLayout_39.setObjectName(u"horizontalLayout_39")
        self.label_76 = QLabel(self.gbInput)
        self.label_76.setObjectName(u"label_76")
        self.label_76.setMinimumSize(QSize(30, 0))
        self.label_76.setMaximumSize(QSize(25, 16777215))
        self.label_76.setFont(font15)

        self.horizontalLayout_39.addWidget(self.label_76)

        self.horizontalSpacer_19 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_39.addItem(self.horizontalSpacer_19)

        self.lbI2Value = QLabel(self.gbInput)
        self.lbI2Value.setObjectName(u"lbI2Value")

        self.horizontalLayout_39.addWidget(self.lbI2Value)

        self.horizontalSpacer_20 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_39.addItem(self.horizontalSpacer_20)

        self.cbToggle2 = QCheckBox(self.gbInput)
        self.cbToggle2.setObjectName(u"cbToggle2")
        self.cbToggle2.setMinimumSize(QSize(110, 0))
        self.cbToggle2.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_39.addWidget(self.cbToggle2)

        self.pbReadI2 = QPushButton(self.gbInput)
        self.pbReadI2.setObjectName(u"pbReadI2")
        self.pbReadI2.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_39.addWidget(self.pbReadI2)

        self.horizontalSpacer_53 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_39.addItem(self.horizontalSpacer_53)


        self.verticalLayout_43.addLayout(self.horizontalLayout_39)

        self.horizontalLayout_40 = QHBoxLayout()
        self.horizontalLayout_40.setSpacing(6)
        self.horizontalLayout_40.setObjectName(u"horizontalLayout_40")
        self.label_78 = QLabel(self.gbInput)
        self.label_78.setObjectName(u"label_78")
        self.label_78.setMinimumSize(QSize(30, 0))
        self.label_78.setMaximumSize(QSize(25, 16777215))
        self.label_78.setFont(font15)

        self.horizontalLayout_40.addWidget(self.label_78)

        self.horizontalSpacer_21 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_40.addItem(self.horizontalSpacer_21)

        self.lbI3Value = QLabel(self.gbInput)
        self.lbI3Value.setObjectName(u"lbI3Value")

        self.horizontalLayout_40.addWidget(self.lbI3Value)

        self.horizontalSpacer_22 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_40.addItem(self.horizontalSpacer_22)

        self.cbToggle3 = QCheckBox(self.gbInput)
        self.cbToggle3.setObjectName(u"cbToggle3")
        self.cbToggle3.setMinimumSize(QSize(110, 0))
        self.cbToggle3.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_40.addWidget(self.cbToggle3)

        self.pbReadI3 = QPushButton(self.gbInput)
        self.pbReadI3.setObjectName(u"pbReadI3")
        self.pbReadI3.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_40.addWidget(self.pbReadI3)

        self.horizontalSpacer_54 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_40.addItem(self.horizontalSpacer_54)


        self.verticalLayout_43.addLayout(self.horizontalLayout_40)

        self.horizontalLayout_43 = QHBoxLayout()
        self.horizontalLayout_43.setSpacing(6)
        self.horizontalLayout_43.setObjectName(u"horizontalLayout_43")
        self.leIx = QLineEdit(self.gbInput)
        self.leIx.setObjectName(u"leIx")
        self.leIx.setMinimumSize(QSize(30, 0))
        self.leIx.setMaximumSize(QSize(25, 16777215))
        self.leIx.setFont(font15)

        self.horizontalLayout_43.addWidget(self.leIx)

        self.horizontalSpacer_29 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_43.addItem(self.horizontalSpacer_29)

        self.lbIxValue = QLabel(self.gbInput)
        self.lbIxValue.setObjectName(u"lbIxValue")

        self.horizontalLayout_43.addWidget(self.lbIxValue)

        self.horizontalSpacer_30 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_43.addItem(self.horizontalSpacer_30)

        self.cbTogglex = QCheckBox(self.gbInput)
        self.cbTogglex.setObjectName(u"cbTogglex")
        self.cbTogglex.setMinimumSize(QSize(110, 0))
        self.cbTogglex.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_43.addWidget(self.cbTogglex)

        self.pbReadIx = QPushButton(self.gbInput)
        self.pbReadIx.setObjectName(u"pbReadIx")
        self.pbReadIx.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_43.addWidget(self.pbReadIx)

        self.horizontalSpacer_57 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_43.addItem(self.horizontalSpacer_57)


        self.verticalLayout_43.addLayout(self.horizontalLayout_43)

        self.horizontalLayout_45 = QHBoxLayout()
        self.horizontalLayout_45.setSpacing(6)
        self.horizontalLayout_45.setObjectName(u"horizontalLayout_45")
        self.label_83 = QLabel(self.gbInput)
        self.label_83.setObjectName(u"label_83")
        self.label_83.setMinimumSize(QSize(30, 0))
        self.label_83.setMaximumSize(QSize(25, 16777215))
        self.label_83.setFont(font15)

        self.horizontalLayout_45.addWidget(self.label_83)

        self.horizontalSpacer_34 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_45.addItem(self.horizontalSpacer_34)

        self.lbA0Value = QLabel(self.gbInput)
        self.lbA0Value.setObjectName(u"lbA0Value")

        self.horizontalLayout_45.addWidget(self.lbA0Value)

        self.horizontalSpacer_35 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_45.addItem(self.horizontalSpacer_35)

        self.leA0Delay = QLineEdit(self.gbInput)
        self.leA0Delay.setObjectName(u"leA0Delay")
        self.leA0Delay.setMinimumSize(QSize(110, 0))
        self.leA0Delay.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_45.addWidget(self.leA0Delay)

        self.pbReadA0 = QPushButton(self.gbInput)
        self.pbReadA0.setObjectName(u"pbReadA0")
        self.pbReadA0.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_45.addWidget(self.pbReadA0)

        self.horizontalSpacer_58 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_45.addItem(self.horizontalSpacer_58)


        self.verticalLayout_43.addLayout(self.horizontalLayout_45)

        self.horizontalLayout_46 = QHBoxLayout()
        self.horizontalLayout_46.setSpacing(6)
        self.horizontalLayout_46.setObjectName(u"horizontalLayout_46")
        self.label_85 = QLabel(self.gbInput)
        self.label_85.setObjectName(u"label_85")
        self.label_85.setMinimumSize(QSize(30, 0))
        self.label_85.setMaximumSize(QSize(25, 16777215))
        self.label_85.setFont(font15)

        self.horizontalLayout_46.addWidget(self.label_85)

        self.horizontalSpacer_36 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_46.addItem(self.horizontalSpacer_36)

        self.lbA1Value = QLabel(self.gbInput)
        self.lbA1Value.setObjectName(u"lbA1Value")

        self.horizontalLayout_46.addWidget(self.lbA1Value)

        self.horizontalSpacer_37 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_46.addItem(self.horizontalSpacer_37)

        self.leA1Delay = QLineEdit(self.gbInput)
        self.leA1Delay.setObjectName(u"leA1Delay")
        self.leA1Delay.setMinimumSize(QSize(110, 0))
        self.leA1Delay.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_46.addWidget(self.leA1Delay)

        self.pbReadA1 = QPushButton(self.gbInput)
        self.pbReadA1.setObjectName(u"pbReadA1")
        self.pbReadA1.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_46.addWidget(self.pbReadA1)

        self.horizontalSpacer_59 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_46.addItem(self.horizontalSpacer_59)


        self.verticalLayout_43.addLayout(self.horizontalLayout_46)

        self.horizontalLayout_47 = QHBoxLayout()
        self.horizontalLayout_47.setSpacing(6)
        self.horizontalLayout_47.setObjectName(u"horizontalLayout_47")
        self.leAx = QLineEdit(self.gbInput)
        self.leAx.setObjectName(u"leAx")
        self.leAx.setMinimumSize(QSize(30, 0))
        self.leAx.setMaximumSize(QSize(25, 16777215))
        self.leAx.setFont(font15)

        self.horizontalLayout_47.addWidget(self.leAx)

        self.horizontalSpacer_38 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_47.addItem(self.horizontalSpacer_38)

        self.lbAxValue = QLabel(self.gbInput)
        self.lbAxValue.setObjectName(u"lbAxValue")

        self.horizontalLayout_47.addWidget(self.lbAxValue)

        self.horizontalSpacer_39 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_47.addItem(self.horizontalSpacer_39)

        self.leAxDelay = QLineEdit(self.gbInput)
        self.leAxDelay.setObjectName(u"leAxDelay")
        self.leAxDelay.setMinimumSize(QSize(110, 0))
        self.leAxDelay.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_47.addWidget(self.leAxDelay)

        self.pbReadAx = QPushButton(self.gbInput)
        self.pbReadAx.setObjectName(u"pbReadAx")
        self.pbReadAx.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_47.addWidget(self.pbReadAx)

        self.horizontalSpacer_60 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_47.addItem(self.horizontalSpacer_60)


        self.verticalLayout_43.addLayout(self.horizontalLayout_47)

        self.tabWidget_3.addTab(self.InputTab, "")

        self.verticalLayout_6.addWidget(self.tabWidget_3)

        self.RobotTabWidget.addTab(self.IOTab, "")

        self.verticalLayout_5.addWidget(self.RobotTabWidget)

        self.scrollArea_2.setWidget(self.wgJoggingScrollWidget)

        self.verticalLayout_4.addWidget(self.scrollArea_2)

        icon46 = QIcon()
        icon46.addFile(u":/icon/deltaicon.png", QSize(), QIcon.Normal, QIcon.Off)
        self.twDevices.addTab(self.tRobot, icon46, "")
        self.ConveyorTab = QWidget()
        self.ConveyorTab.setObjectName(u"ConveyorTab")
        self.verticalLayout_22 = QVBoxLayout(self.ConveyorTab)
        self.verticalLayout_22.setSpacing(6)
        self.verticalLayout_22.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_22.setObjectName(u"verticalLayout_22")
        self.horizontalLayout_48 = QHBoxLayout()
        self.horizontalLayout_48.setSpacing(6)
        self.horizontalLayout_48.setObjectName(u"horizontalLayout_48")
        self.horizontalLayout_48.setContentsMargins(10, -1, -1, -1)
        self.pbConveyorConnect = QPushButton(self.ConveyorTab)
        self.pbConveyorConnect.setObjectName(u"pbConveyorConnect")
        self.pbConveyorConnect.setMinimumSize(QSize(100, 30))
        self.pbConveyorConnect.setMaximumSize(QSize(120, 40))
        font16 = QFont()
        font16.setPointSize(12)
        self.pbConveyorConnect.setFont(font16)
        self.pbConveyorConnect.setStyleSheet(u"")
        self.pbConveyorConnect.setCheckable(True)

        self.horizontalLayout_48.addWidget(self.pbConveyorConnect)

        self.label_2 = QLabel(self.ConveyorTab)
        self.label_2.setObjectName(u"label_2")

        self.horizontalLayout_48.addWidget(self.label_2)

        self.cbSelectedConveyor = QComboBox(self.ConveyorTab)
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.setObjectName(u"cbSelectedConveyor")

        self.horizontalLayout_48.addWidget(self.cbSelectedConveyor)

        self.label_28 = QLabel(self.ConveyorTab)
        self.label_28.setObjectName(u"label_28")

        self.horizontalLayout_48.addWidget(self.label_28)

        self.cbConveyorType = QComboBox(self.ConveyorTab)
        self.cbConveyorType.addItem("")
        self.cbConveyorType.addItem("")
        self.cbConveyorType.addItem("")
        self.cbConveyorType.setObjectName(u"cbConveyorType")
        self.cbConveyorType.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_48.addWidget(self.cbConveyorType)

        self.lbConveyorCOMName = QLabel(self.ConveyorTab)
        self.lbConveyorCOMName.setObjectName(u"lbConveyorCOMName")
        font17 = QFont()
        font17.setPointSize(11)
        self.lbConveyorCOMName.setFont(font17)
        self.lbConveyorCOMName.setStyleSheet(u"color: rgb(41, 155, 255);")

        self.horizontalLayout_48.addWidget(self.lbConveyorCOMName)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_48.addItem(self.horizontalSpacer)


        self.verticalLayout_22.addLayout(self.horizontalLayout_48)

        self.fConveyorX = QFrame(self.ConveyorTab)
        self.fConveyorX.setObjectName(u"fConveyorX")
        self.gridLayout_7 = QGridLayout(self.fConveyorX)
        self.gridLayout_7.setSpacing(6)
        self.gridLayout_7.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_7.setObjectName(u"gridLayout_7")
        self.gridLayout_7.setHorizontalSpacing(20)
        self.gridLayout_7.setVerticalSpacing(10)
        self.gridLayout_7.setContentsMargins(10, 10, 10, 10)
        self.leConveyorXPosition = QLineEdit(self.fConveyorX)
        self.leConveyorXPosition.setObjectName(u"leConveyorXPosition")
        self.leConveyorXPosition.setMinimumSize(QSize(0, 30))
        self.leConveyorXPosition.setMaximumSize(QSize(200, 16777215))
        font18 = QFont()
        font18.setPointSize(11)
        font18.setBold(False)
        font18.setKerning(True)
        self.leConveyorXPosition.setFont(font18)

        self.gridLayout_7.addWidget(self.leConveyorXPosition, 3, 1, 1, 1)

        self.cbConveyorValueType = QComboBox(self.fConveyorX)
        self.cbConveyorValueType.addItem("")
        self.cbConveyorValueType.addItem("")
        self.cbConveyorValueType.setObjectName(u"cbConveyorValueType")
        self.cbConveyorValueType.setMinimumSize(QSize(0, 30))
        self.cbConveyorValueType.setMaximumSize(QSize(200, 16777215))
        self.cbConveyorValueType.setFont(font18)
        self.cbConveyorValueType.setStyleSheet(u"")

        self.gridLayout_7.addWidget(self.cbConveyorValueType, 1, 1, 1, 1)

        self.lbUnitOfConveyorMoving = QLabel(self.fConveyorX)
        self.lbUnitOfConveyorMoving.setObjectName(u"lbUnitOfConveyorMoving")
        self.lbUnitOfConveyorMoving.setEnabled(False)
        self.lbUnitOfConveyorMoving.setFont(font5)

        self.gridLayout_7.addWidget(self.lbUnitOfConveyorMoving, 3, 2, 1, 1)

        self.label_57 = QLabel(self.fConveyorX)
        self.label_57.setObjectName(u"label_57")
        self.label_57.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_57, 2, 0, 1, 1)

        self.label_46 = QLabel(self.fConveyorX)
        self.label_46.setObjectName(u"label_46")
        self.label_46.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_46, 1, 0, 1, 1)

        self.cbConveyorMode = QComboBox(self.fConveyorX)
        self.cbConveyorMode.addItem("")
        self.cbConveyorMode.addItem("")
        self.cbConveyorMode.setObjectName(u"cbConveyorMode")
        self.cbConveyorMode.setMinimumSize(QSize(0, 30))
        self.cbConveyorMode.setMaximumSize(QSize(200, 16777215))
        self.cbConveyorMode.setFont(font18)

        self.gridLayout_7.addWidget(self.cbConveyorMode, 0, 1, 1, 1)

        self.label_12 = QLabel(self.fConveyorX)
        self.label_12.setObjectName(u"label_12")
        self.label_12.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_12, 3, 0, 1, 1)

        self.leConveyorXSpeed = QLineEdit(self.fConveyorX)
        self.leConveyorXSpeed.setObjectName(u"leConveyorXSpeed")
        self.leConveyorXSpeed.setEnabled(True)
        self.leConveyorXSpeed.setMinimumSize(QSize(0, 30))
        self.leConveyorXSpeed.setMaximumSize(QSize(200, 16777215))
        self.leConveyorXSpeed.setFont(font18)
        self.leConveyorXSpeed.setClearButtonEnabled(False)

        self.gridLayout_7.addWidget(self.leConveyorXSpeed, 2, 1, 1, 1)

        self.label_52 = QLabel(self.fConveyorX)
        self.label_52.setObjectName(u"label_52")
        self.label_52.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_52, 0, 0, 1, 1)

        self.lbSpeedOfPositionMode = QLabel(self.fConveyorX)
        self.lbSpeedOfPositionMode.setObjectName(u"lbSpeedOfPositionMode")
        self.lbSpeedOfPositionMode.setEnabled(False)
        self.lbSpeedOfPositionMode.setFont(font5)

        self.gridLayout_7.addWidget(self.lbSpeedOfPositionMode, 2, 2, 1, 1)


        self.verticalLayout_22.addWidget(self.fConveyorX)

        self.fConveyorXHub = QFrame(self.ConveyorTab)
        self.fConveyorXHub.setObjectName(u"fConveyorXHub")
        self.gridLayout_18 = QGridLayout(self.fConveyorXHub)
        self.gridLayout_18.setSpacing(6)
        self.gridLayout_18.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_18.setObjectName(u"gridLayout_18")
        self.gridLayout_18.setHorizontalSpacing(20)
        self.gridLayout_18.setVerticalSpacing(10)
        self.gridLayout_18.setContentsMargins(10, 10, 10, 10)
        self.label_77 = QLabel(self.fConveyorXHub)
        self.label_77.setObjectName(u"label_77")
        self.label_77.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_18.addWidget(self.label_77, 4, 0, 1, 1)

        self.leSubConveyor1Position = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor1Position.setObjectName(u"leSubConveyor1Position")
        self.leSubConveyor1Position.setEnabled(True)
        self.leSubConveyor1Position.setMinimumSize(QSize(0, 30))
        self.leSubConveyor1Position.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor1Position.setFont(font18)
        self.leSubConveyor1Position.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor1Position, 4, 1, 1, 1)

        self.label_115 = QLabel(self.fConveyorXHub)
        self.label_115.setObjectName(u"label_115")
        self.label_115.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_18.addWidget(self.label_115, 1, 0, 1, 1)

        self.label_114 = QLabel(self.fConveyorXHub)
        self.label_114.setObjectName(u"label_114")
        self.label_114.setAlignment(Qt.AlignCenter)

        self.gridLayout_18.addWidget(self.label_114, 0, 3, 1, 1)

        self.cbSubConveyor2Mode = QComboBox(self.fConveyorXHub)
        self.cbSubConveyor2Mode.addItem("")
        self.cbSubConveyor2Mode.addItem("")
        self.cbSubConveyor2Mode.setObjectName(u"cbSubConveyor2Mode")
        self.cbSubConveyor2Mode.setMinimumSize(QSize(0, 30))
        self.cbSubConveyor2Mode.setMaximumSize(QSize(200, 16777215))
        self.cbSubConveyor2Mode.setFont(font18)
        self.cbSubConveyor2Mode.setStyleSheet(u"")

        self.gridLayout_18.addWidget(self.cbSubConveyor2Mode, 1, 2, 1, 1)

        self.leSubConveyor1Speed = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor1Speed.setObjectName(u"leSubConveyor1Speed")
        self.leSubConveyor1Speed.setMinimumSize(QSize(0, 30))
        self.leSubConveyor1Speed.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor1Speed.setFont(font18)

        self.gridLayout_18.addWidget(self.leSubConveyor1Speed, 3, 1, 1, 1)

        self.label_75 = QLabel(self.fConveyorXHub)
        self.label_75.setObjectName(u"label_75")
        self.label_75.setAlignment(Qt.AlignCenter)

        self.gridLayout_18.addWidget(self.label_75, 0, 1, 1, 1)

        self.label_82 = QLabel(self.fConveyorXHub)
        self.label_82.setObjectName(u"label_82")
        self.label_82.setAlignment(Qt.AlignCenter)

        self.gridLayout_18.addWidget(self.label_82, 0, 2, 1, 1)

        self.leSubConveyor2Position = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor2Position.setObjectName(u"leSubConveyor2Position")
        self.leSubConveyor2Position.setEnabled(True)
        self.leSubConveyor2Position.setMinimumSize(QSize(0, 30))
        self.leSubConveyor2Position.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor2Position.setFont(font18)
        self.leSubConveyor2Position.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor2Position, 4, 2, 1, 1)

        self.leSubConveyor2Speed = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor2Speed.setObjectName(u"leSubConveyor2Speed")
        self.leSubConveyor2Speed.setEnabled(True)
        self.leSubConveyor2Speed.setMinimumSize(QSize(0, 30))
        self.leSubConveyor2Speed.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor2Speed.setFont(font18)
        self.leSubConveyor2Speed.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor2Speed, 3, 2, 1, 1)

        self.cbSubConveyor3Mode = QComboBox(self.fConveyorXHub)
        self.cbSubConveyor3Mode.addItem("")
        self.cbSubConveyor3Mode.addItem("")
        self.cbSubConveyor3Mode.setObjectName(u"cbSubConveyor3Mode")
        self.cbSubConveyor3Mode.setMinimumSize(QSize(0, 30))
        self.cbSubConveyor3Mode.setMaximumSize(QSize(200, 16777215))
        self.cbSubConveyor3Mode.setFont(font18)
        self.cbSubConveyor3Mode.setStyleSheet(u"")

        self.gridLayout_18.addWidget(self.cbSubConveyor3Mode, 1, 3, 1, 1)

        self.leSubConveyor3Speed = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor3Speed.setObjectName(u"leSubConveyor3Speed")
        self.leSubConveyor3Speed.setEnabled(True)
        self.leSubConveyor3Speed.setMinimumSize(QSize(0, 30))
        self.leSubConveyor3Speed.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor3Speed.setFont(font18)
        self.leSubConveyor3Speed.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor3Speed, 3, 3, 1, 1)

        self.cbSubConveyor1Mode = QComboBox(self.fConveyorXHub)
        self.cbSubConveyor1Mode.addItem("")
        self.cbSubConveyor1Mode.addItem("")
        self.cbSubConveyor1Mode.setObjectName(u"cbSubConveyor1Mode")
        self.cbSubConveyor1Mode.setMinimumSize(QSize(0, 30))
        self.cbSubConveyor1Mode.setMaximumSize(QSize(200, 16777215))
        self.cbSubConveyor1Mode.setFont(font18)
        self.cbSubConveyor1Mode.setStyleSheet(u"")

        self.gridLayout_18.addWidget(self.cbSubConveyor1Mode, 1, 1, 1, 1)

        self.label_80 = QLabel(self.fConveyorXHub)
        self.label_80.setObjectName(u"label_80")
        self.label_80.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_18.addWidget(self.label_80, 3, 0, 1, 1)

        self.leSubConveyor3Position = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor3Position.setObjectName(u"leSubConveyor3Position")
        self.leSubConveyor3Position.setEnabled(True)
        self.leSubConveyor3Position.setMinimumSize(QSize(0, 30))
        self.leSubConveyor3Position.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor3Position.setFont(font18)
        self.leSubConveyor3Position.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor3Position, 4, 3, 1, 1)


        self.verticalLayout_22.addWidget(self.fConveyorXHub)

        self.fConveyorCustom = QFrame(self.ConveyorTab)
        self.fConveyorCustom.setObjectName(u"fConveyorCustom")
        self.gridLayout_39 = QGridLayout(self.fConveyorCustom)
        self.gridLayout_39.setSpacing(6)
        self.gridLayout_39.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_39.setObjectName(u"gridLayout_39")
        self.gridLayout_39.setHorizontalSpacing(20)
        self.gridLayout_39.setVerticalSpacing(10)
        self.gridLayout_39.setContentsMargins(10, 10, 10, 10)
        self.pbStopCustomConveyor2Command = QLineEdit(self.fConveyorCustom)
        self.pbStopCustomConveyor2Command.setObjectName(u"pbStopCustomConveyor2Command")
        self.pbStopCustomConveyor2Command.setEnabled(True)
        self.pbStopCustomConveyor2Command.setMinimumSize(QSize(0, 30))
        self.pbStopCustomConveyor2Command.setMaximumSize(QSize(200, 16777215))
        self.pbStopCustomConveyor2Command.setFont(font18)
        self.pbStopCustomConveyor2Command.setClearButtonEnabled(False)

        self.gridLayout_39.addWidget(self.pbStopCustomConveyor2Command, 4, 1, 1, 1)

        self.pbStartCustomConveyor3 = QPushButton(self.fConveyorCustom)
        self.pbStartCustomConveyor3.setObjectName(u"pbStartCustomConveyor3")
        self.pbStartCustomConveyor3.setMinimumSize(QSize(0, 30))

        self.gridLayout_39.addWidget(self.pbStartCustomConveyor3, 1, 2, 1, 1)

        self.pbStopCustomConveyor3 = QPushButton(self.fConveyorCustom)
        self.pbStopCustomConveyor3.setObjectName(u"pbStopCustomConveyor3")
        self.pbStopCustomConveyor3.setMinimumSize(QSize(0, 30))

        self.gridLayout_39.addWidget(self.pbStopCustomConveyor3, 3, 2, 1, 1)

        self.label_147 = QLabel(self.fConveyorCustom)
        self.label_147.setObjectName(u"label_147")
        self.label_147.setAlignment(Qt.AlignCenter)

        self.gridLayout_39.addWidget(self.label_147, 0, 2, 1, 1)

        self.pbStartCustomConveyor2Command = QLineEdit(self.fConveyorCustom)
        self.pbStartCustomConveyor2Command.setObjectName(u"pbStartCustomConveyor2Command")
        self.pbStartCustomConveyor2Command.setEnabled(True)
        self.pbStartCustomConveyor2Command.setMinimumSize(QSize(0, 30))
        self.pbStartCustomConveyor2Command.setMaximumSize(QSize(200, 16777215))
        self.pbStartCustomConveyor2Command.setFont(font18)
        self.pbStartCustomConveyor2Command.setClearButtonEnabled(False)

        self.gridLayout_39.addWidget(self.pbStartCustomConveyor2Command, 2, 1, 1, 1)

        self.pbStopCustomConveyor2 = QPushButton(self.fConveyorCustom)
        self.pbStopCustomConveyor2.setObjectName(u"pbStopCustomConveyor2")
        self.pbStopCustomConveyor2.setMinimumSize(QSize(0, 30))

        self.gridLayout_39.addWidget(self.pbStopCustomConveyor2, 3, 1, 1, 1)

        self.pbStopCustomConveyor3Command = QLineEdit(self.fConveyorCustom)
        self.pbStopCustomConveyor3Command.setObjectName(u"pbStopCustomConveyor3Command")
        self.pbStopCustomConveyor3Command.setEnabled(True)
        self.pbStopCustomConveyor3Command.setMinimumSize(QSize(0, 30))
        self.pbStopCustomConveyor3Command.setMaximumSize(QSize(200, 16777215))
        self.pbStopCustomConveyor3Command.setFont(font18)
        self.pbStopCustomConveyor3Command.setClearButtonEnabled(False)

        self.gridLayout_39.addWidget(self.pbStopCustomConveyor3Command, 4, 2, 1, 1)

        self.label_153 = QLabel(self.fConveyorCustom)
        self.label_153.setObjectName(u"label_153")
        self.label_153.setAlignment(Qt.AlignCenter)

        self.gridLayout_39.addWidget(self.label_153, 0, 0, 1, 1)

        self.pbStartCustomConveyor1 = QPushButton(self.fConveyorCustom)
        self.pbStartCustomConveyor1.setObjectName(u"pbStartCustomConveyor1")
        self.pbStartCustomConveyor1.setMinimumSize(QSize(0, 30))

        self.gridLayout_39.addWidget(self.pbStartCustomConveyor1, 1, 0, 1, 1)

        self.pbStopCustomConveyor1 = QPushButton(self.fConveyorCustom)
        self.pbStopCustomConveyor1.setObjectName(u"pbStopCustomConveyor1")
        self.pbStopCustomConveyor1.setMinimumSize(QSize(0, 30))

        self.gridLayout_39.addWidget(self.pbStopCustomConveyor1, 3, 0, 1, 1)

        self.pbStopCustomConveyor1Command = QLineEdit(self.fConveyorCustom)
        self.pbStopCustomConveyor1Command.setObjectName(u"pbStopCustomConveyor1Command")
        self.pbStopCustomConveyor1Command.setEnabled(True)
        self.pbStopCustomConveyor1Command.setMinimumSize(QSize(0, 30))
        self.pbStopCustomConveyor1Command.setMaximumSize(QSize(200, 16777215))
        self.pbStopCustomConveyor1Command.setFont(font18)
        self.pbStopCustomConveyor1Command.setClearButtonEnabled(False)

        self.gridLayout_39.addWidget(self.pbStopCustomConveyor1Command, 4, 0, 1, 1)

        self.pbStartCustomConveyor1Command = QLineEdit(self.fConveyorCustom)
        self.pbStartCustomConveyor1Command.setObjectName(u"pbStartCustomConveyor1Command")
        self.pbStartCustomConveyor1Command.setMinimumSize(QSize(0, 30))
        self.pbStartCustomConveyor1Command.setMaximumSize(QSize(200, 16777215))
        self.pbStartCustomConveyor1Command.setFont(font18)

        self.gridLayout_39.addWidget(self.pbStartCustomConveyor1Command, 2, 0, 1, 1)

        self.pbStartCustomConveyor2 = QPushButton(self.fConveyorCustom)
        self.pbStartCustomConveyor2.setObjectName(u"pbStartCustomConveyor2")
        self.pbStartCustomConveyor2.setMinimumSize(QSize(0, 30))

        self.gridLayout_39.addWidget(self.pbStartCustomConveyor2, 1, 1, 1, 1)

        self.pbStartCustomConveyor3Command = QLineEdit(self.fConveyorCustom)
        self.pbStartCustomConveyor3Command.setObjectName(u"pbStartCustomConveyor3Command")
        self.pbStartCustomConveyor3Command.setEnabled(True)
        self.pbStartCustomConveyor3Command.setMinimumSize(QSize(0, 30))
        self.pbStartCustomConveyor3Command.setMaximumSize(QSize(200, 16777215))
        self.pbStartCustomConveyor3Command.setFont(font18)
        self.pbStartCustomConveyor3Command.setClearButtonEnabled(False)

        self.gridLayout_39.addWidget(self.pbStartCustomConveyor3Command, 2, 2, 1, 1)

        self.label_154 = QLabel(self.fConveyorCustom)
        self.label_154.setObjectName(u"label_154")
        self.label_154.setAlignment(Qt.AlignCenter)

        self.gridLayout_39.addWidget(self.label_154, 0, 1, 1, 1)


        self.verticalLayout_22.addWidget(self.fConveyorCustom)

        self.verticalSpacer_2 = QSpacerItem(20, 304, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_22.addItem(self.verticalSpacer_2)

        self.twDevices.addTab(self.ConveyorTab, "")
        self.EncoderTab = QWidget()
        self.EncoderTab.setObjectName(u"EncoderTab")
        self.verticalLayout_8 = QVBoxLayout(self.EncoderTab)
        self.verticalLayout_8.setSpacing(6)
        self.verticalLayout_8.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_8.setObjectName(u"verticalLayout_8")
        self.horizontalLayout_51 = QHBoxLayout()
        self.horizontalLayout_51.setSpacing(6)
        self.horizontalLayout_51.setObjectName(u"horizontalLayout_51")
        self.horizontalLayout_51.setContentsMargins(10, -1, -1, -1)
        self.pbConnectEncoder = QPushButton(self.EncoderTab)
        self.pbConnectEncoder.setObjectName(u"pbConnectEncoder")
        self.pbConnectEncoder.setMinimumSize(QSize(100, 30))
        self.pbConnectEncoder.setMaximumSize(QSize(120, 40))
        self.pbConnectEncoder.setFont(font16)
        self.pbConnectEncoder.setStyleSheet(u"")
        self.pbConnectEncoder.setCheckable(True)

        self.horizontalLayout_51.addWidget(self.pbConnectEncoder)

        self.label_11 = QLabel(self.EncoderTab)
        self.label_11.setObjectName(u"label_11")

        self.horizontalLayout_51.addWidget(self.label_11)

        self.cbSelectedEncoder = QComboBox(self.EncoderTab)
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.setObjectName(u"cbSelectedEncoder")

        self.horizontalLayout_51.addWidget(self.cbSelectedEncoder)

        self.label_124 = QLabel(self.EncoderTab)
        self.label_124.setObjectName(u"label_124")

        self.horizontalLayout_51.addWidget(self.label_124)

        self.cbEncoderType = QComboBox(self.EncoderTab)
        self.cbEncoderType.addItem("")
        self.cbEncoderType.addItem("")
        self.cbEncoderType.addItem("")
        self.cbEncoderType.setObjectName(u"cbEncoderType")
        self.cbEncoderType.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_51.addWidget(self.cbEncoderType)

        self.lbEncoderCOMname = QLabel(self.EncoderTab)
        self.lbEncoderCOMname.setObjectName(u"lbEncoderCOMname")
        self.lbEncoderCOMname.setFont(font17)
        self.lbEncoderCOMname.setStyleSheet(u"color: rgb(41, 155, 255);")

        self.horizontalLayout_51.addWidget(self.lbEncoderCOMname)

        self.horizontalSpacer_14 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_51.addItem(self.horizontalSpacer_14)


        self.verticalLayout_8.addLayout(self.horizontalLayout_51)

        self.gridLayout_21 = QGridLayout()
        self.gridLayout_21.setSpacing(6)
        self.gridLayout_21.setObjectName(u"gridLayout_21")
        self.gridLayout_21.setContentsMargins(10, -1, -1, -1)
        self.leEncoderVelocity = QLineEdit(self.EncoderTab)
        self.leEncoderVelocity.setObjectName(u"leEncoderVelocity")
        sizePolicy.setHeightForWidth(self.leEncoderVelocity.sizePolicy().hasHeightForWidth())
        self.leEncoderVelocity.setSizePolicy(sizePolicy)

        self.gridLayout_21.addWidget(self.leEncoderVelocity, 3, 1, 1, 1)

        self.leEncoderInterval = QLineEdit(self.EncoderTab)
        self.leEncoderInterval.setObjectName(u"leEncoderInterval")
        sizePolicy.setHeightForWidth(self.leEncoderInterval.sizePolicy().hasHeightForWidth())
        self.leEncoderInterval.setSizePolicy(sizePolicy)

        self.gridLayout_21.addWidget(self.leEncoderInterval, 2, 1, 1, 1)

        self.leEncoderCurrentPosition = QLineEdit(self.EncoderTab)
        self.leEncoderCurrentPosition.setObjectName(u"leEncoderCurrentPosition")
        sizePolicy.setHeightForWidth(self.leEncoderCurrentPosition.sizePolicy().hasHeightForWidth())
        self.leEncoderCurrentPosition.setSizePolicy(sizePolicy)

        self.gridLayout_21.addWidget(self.leEncoderCurrentPosition, 4, 1, 1, 1)

        self.label_130 = QLabel(self.EncoderTab)
        self.label_130.setObjectName(u"label_130")

        self.gridLayout_21.addWidget(self.label_130, 4, 0, 1, 1)

        self.pbReadEncoder = QPushButton(self.EncoderTab)
        self.pbReadEncoder.setObjectName(u"pbReadEncoder")

        self.gridLayout_21.addWidget(self.pbReadEncoder, 4, 2, 1, 1)

        self.pbSetEncoderVelocity = QPushButton(self.EncoderTab)
        self.pbSetEncoderVelocity.setObjectName(u"pbSetEncoderVelocity")

        self.gridLayout_21.addWidget(self.pbSetEncoderVelocity, 3, 2, 1, 1)

        self.pbSetEncoderInterval = QPushButton(self.EncoderTab)
        self.pbSetEncoderInterval.setObjectName(u"pbSetEncoderInterval")

        self.gridLayout_21.addWidget(self.pbSetEncoderInterval, 2, 2, 1, 1)

        self.horizontalSpacer_23 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_21.addItem(self.horizontalSpacer_23, 2, 4, 1, 1)

        self.pbResetEncoder = QPushButton(self.EncoderTab)
        self.pbResetEncoder.setObjectName(u"pbResetEncoder")

        self.gridLayout_21.addWidget(self.pbResetEncoder, 4, 3, 1, 1)

        self.label_129 = QLabel(self.EncoderTab)
        self.label_129.setObjectName(u"label_129")

        self.gridLayout_21.addWidget(self.label_129, 3, 0, 1, 1)

        self.label_125 = QLabel(self.EncoderTab)
        self.label_125.setObjectName(u"label_125")

        self.gridLayout_21.addWidget(self.label_125, 2, 0, 1, 1)

        self.cbEncoderActive = QCheckBox(self.EncoderTab)
        self.cbEncoderActive.setObjectName(u"cbEncoderActive")
        self.cbEncoderActive.setChecked(True)

        self.gridLayout_21.addWidget(self.cbEncoderActive, 1, 0, 1, 1)


        self.verticalLayout_8.addLayout(self.gridLayout_21)

        self.verticalSpacer_14 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_8.addItem(self.verticalSpacer_14)

        self.twDevices.addTab(self.EncoderTab, "")
        self.SliderTab1 = QWidget()
        self.SliderTab1.setObjectName(u"SliderTab1")
        self.verticalLayout_23 = QVBoxLayout(self.SliderTab1)
        self.verticalLayout_23.setSpacing(6)
        self.verticalLayout_23.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_23.setObjectName(u"verticalLayout_23")
        self.horizontalLayout_49 = QHBoxLayout()
        self.horizontalLayout_49.setSpacing(6)
        self.horizontalLayout_49.setObjectName(u"horizontalLayout_49")
        self.horizontalLayout_49.setContentsMargins(10, -1, -1, -1)
        self.pbSlidingConnect = QPushButton(self.SliderTab1)
        self.pbSlidingConnect.setObjectName(u"pbSlidingConnect")
        self.pbSlidingConnect.setMinimumSize(QSize(100, 30))
        self.pbSlidingConnect.setMaximumSize(QSize(120, 50))
        self.pbSlidingConnect.setFont(font16)
        icon47 = QIcon()
        icon47.addFile(u"icon/connected.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingConnect.setIcon(icon47)

        self.horizontalLayout_49.addWidget(self.pbSlidingConnect)

        self.label_161 = QLabel(self.SliderTab1)
        self.label_161.setObjectName(u"label_161")

        self.horizontalLayout_49.addWidget(self.label_161)

        self.cbSelectedSlider = QComboBox(self.SliderTab1)
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.setObjectName(u"cbSelectedSlider")

        self.horizontalLayout_49.addWidget(self.cbSelectedSlider)

        self.lbSliderCOMName = QLabel(self.SliderTab1)
        self.lbSliderCOMName.setObjectName(u"lbSliderCOMName")
        self.lbSliderCOMName.setFont(font17)
        self.lbSliderCOMName.setStyleSheet(u"color: rgb(255, 0, 0);")

        self.horizontalLayout_49.addWidget(self.lbSliderCOMName)

        self.horizontalSpacer_12 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_49.addItem(self.horizontalSpacer_12)


        self.verticalLayout_23.addLayout(self.horizontalLayout_49)

        self.gridLayout_8 = QGridLayout()
        self.gridLayout_8.setSpacing(10)
        self.gridLayout_8.setObjectName(u"gridLayout_8")
        self.gridLayout_8.setContentsMargins(10, 10, 10, 10)
        self.leSlidingPosition = QLineEdit(self.SliderTab1)
        self.leSlidingPosition.setObjectName(u"leSlidingPosition")
        self.leSlidingPosition.setMinimumSize(QSize(0, 30))
        self.leSlidingPosition.setMaximumSize(QSize(200, 40))

        self.gridLayout_8.addWidget(self.leSlidingPosition, 3, 1, 1, 1)

        self.pbSlidingDisable = QPushButton(self.SliderTab1)
        self.pbSlidingDisable.setObjectName(u"pbSlidingDisable")
        self.pbSlidingDisable.setMinimumSize(QSize(0, 30))
        self.pbSlidingDisable.setMaximumSize(QSize(200, 40))
        self.pbSlidingDisable.setFont(font17)
        icon48 = QIcon()
        icon48.addFile(u"icon/icons8-sleeping-in-bed-32.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingDisable.setIcon(icon48)

        self.gridLayout_8.addWidget(self.pbSlidingDisable, 0, 1, 1, 1)

        self.label_58 = QLabel(self.SliderTab1)
        self.label_58.setObjectName(u"label_58")
        self.label_58.setFont(font5)

        self.gridLayout_8.addWidget(self.label_58, 2, 2, 1, 1)

        self.label_37 = QLabel(self.SliderTab1)
        self.label_37.setObjectName(u"label_37")
        self.label_37.setFont(font5)
        self.label_37.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_8.addWidget(self.label_37, 3, 0, 1, 1)

        self.pbSlidingHome = QPushButton(self.SliderTab1)
        self.pbSlidingHome.setObjectName(u"pbSlidingHome")
        self.pbSlidingHome.setMinimumSize(QSize(0, 30))
        self.pbSlidingHome.setMaximumSize(QSize(200, 40))
        self.pbSlidingHome.setFont(font17)
        icon49 = QIcon()
        icon49.addFile(u"icon/icons8-home-32.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingHome.setIcon(icon49)

        self.gridLayout_8.addWidget(self.pbSlidingHome, 1, 1, 1, 1)

        self.leSlidingSpeed = QLineEdit(self.SliderTab1)
        self.leSlidingSpeed.setObjectName(u"leSlidingSpeed")
        self.leSlidingSpeed.setMinimumSize(QSize(0, 30))
        self.leSlidingSpeed.setMaximumSize(QSize(200, 40))

        self.gridLayout_8.addWidget(self.leSlidingSpeed, 2, 1, 1, 1)

        self.label_36 = QLabel(self.SliderTab1)
        self.label_36.setObjectName(u"label_36")
        self.label_36.setFont(font5)
        self.label_36.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_8.addWidget(self.label_36, 2, 0, 1, 1)

        self.label_59 = QLabel(self.SliderTab1)
        self.label_59.setObjectName(u"label_59")
        self.label_59.setFont(font5)

        self.gridLayout_8.addWidget(self.label_59, 3, 2, 1, 1)


        self.verticalLayout_23.addLayout(self.gridLayout_8)

        self.verticalSpacer_3 = QSpacerItem(20, 296, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_23.addItem(self.verticalSpacer_3)

        self.twDevices.addTab(self.SliderTab1, "")
        self.MCUTab = QWidget()
        self.MCUTab.setObjectName(u"MCUTab")
        self.verticalLayout_24 = QVBoxLayout(self.MCUTab)
        self.verticalLayout_24.setSpacing(6)
        self.verticalLayout_24.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_24.setObjectName(u"verticalLayout_24")
        self.widget1 = QWidget(self.MCUTab)
        self.widget1.setObjectName(u"widget1")
        self.widget1.setMaximumSize(QSize(16777215, 40))
        self.horizontalLayout_50 = QHBoxLayout(self.widget1)
        self.horizontalLayout_50.setSpacing(10)
        self.horizontalLayout_50.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_50.setObjectName(u"horizontalLayout_50")
        self.horizontalLayout_50.setContentsMargins(0, 0, 10, 10)
        self.pbExternalControllerConnect = QPushButton(self.widget1)
        self.pbExternalControllerConnect.setObjectName(u"pbExternalControllerConnect")
        sizePolicy.setHeightForWidth(self.pbExternalControllerConnect.sizePolicy().hasHeightForWidth())
        self.pbExternalControllerConnect.setSizePolicy(sizePolicy)
        self.pbExternalControllerConnect.setMinimumSize(QSize(100, 30))
        self.pbExternalControllerConnect.setMaximumSize(QSize(120, 50))
        font19 = QFont()
        font19.setPointSize(12)
        font19.setBold(False)
        font19.setKerning(True)
        self.pbExternalControllerConnect.setFont(font19)

        self.horizontalLayout_50.addWidget(self.pbExternalControllerConnect)

        self.label_162 = QLabel(self.widget1)
        self.label_162.setObjectName(u"label_162")

        self.horizontalLayout_50.addWidget(self.label_162)

        self.cbSelectedDevice = QComboBox(self.widget1)
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.setObjectName(u"cbSelectedDevice")

        self.horizontalLayout_50.addWidget(self.cbSelectedDevice)

        self.lbExternalCOMName = QLabel(self.widget1)
        self.lbExternalCOMName.setObjectName(u"lbExternalCOMName")
        self.lbExternalCOMName.setMaximumSize(QSize(16777215, 30))
        self.lbExternalCOMName.setFont(font17)
        self.lbExternalCOMName.setStyleSheet(u"color: rgb(255, 0, 0);")

        self.horizontalLayout_50.addWidget(self.lbExternalCOMName)

        self.horizontalSpacer_25 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_50.addItem(self.horizontalSpacer_25)


        self.verticalLayout_24.addWidget(self.widget1)

        self.teReceiveFromMCU = QTextEdit(self.MCUTab)
        self.teReceiveFromMCU.setObjectName(u"teReceiveFromMCU")

        self.verticalLayout_24.addWidget(self.teReceiveFromMCU)

        self.leTransmitToMCU = QLineEdit(self.MCUTab)
        self.leTransmitToMCU.setObjectName(u"leTransmitToMCU")
        self.leTransmitToMCU.setMinimumSize(QSize(0, 30))

        self.verticalLayout_24.addWidget(self.leTransmitToMCU)

        self.twDevices.addTab(self.MCUTab, "")
        self.PlusDeviceTab = QWidget()
        self.PlusDeviceTab.setObjectName(u"PlusDeviceTab")
        self.twDevices.addTab(self.PlusDeviceTab, "")

        self.GeometryTabManagerLayout.addWidget(self.twDevices)

        self.splitter_2.addWidget(self.DeviceTabManagerWidget)

        self.verticalLayout_46.addWidget(self.splitter_2)


        self.verticalLayout_15.addWidget(self.tabManagerLayout)

        RobotWindow.setCentralWidget(self.centralWidget)

        self.retranslateUi(RobotWindow)
        self.pbCalibStep2.toggled.connect(self.fCalibStep2.setVisible)
        self.gbImageProvider.toggled.connect(self.fImageProvider.setVisible)
        self.gbCameraCalibration.toggled.connect(self.fCameraCalibrationFrame.setVisible)
        self.pbCalibStep1.toggled.connect(self.fCalibStep1.setVisible)
        self.gbCameraVariable.toggled.connect(self.fVisionVariableFrame.setVisible)
        self.gbCameraObject.toggled.connect(self.fVisionObjectFrame.setVisible)

        self.twDeltaManager.setCurrentIndex(0)
        self.twModule.setCurrentIndex(1)
        self.tabWidget.setCurrentIndex(0)
        self.pbImageMapping.setDefault(False)
        self.cbImageSource.setCurrentIndex(0)
        self.twDevices.setCurrentIndex(0)
        self.RobotTabWidget.setCurrentIndex(1)
        self.tabWidget_2.setCurrentIndex(0)
        self.cbDivision.setCurrentIndex(1)
        self.tabWidget_3.setCurrentIndex(1)
        self.pbPump.setDefault(False)
        self.pbLaser.setDefault(False)
        self.pbGrip.setDefault(False)


        QMetaObject.connectSlotsByName(RobotWindow)
    # setupUi

    def retranslateUi(self, RobotWindow):
        RobotWindow.setWindowTitle(QCoreApplication.translate("RobotWindow", u"Delta X Software - Version 0.9.5", None))
        self.actionAdd.setText(QCoreApplication.translate("RobotWindow", u"Add New", None))
        self.actionRemove.setText(QCoreApplication.translate("RobotWindow", u"Remove", None))
        self.actionAbout.setText(QCoreApplication.translate("RobotWindow", u"About", None))
        self.actionGcode.setText(QCoreApplication.translate("RobotWindow", u"Gcode", None))
        self.actionSoftware.setText(QCoreApplication.translate("RobotWindow", u"Software", None))
        self.actionExecute_All.setText(QCoreApplication.translate("RobotWindow", u"Execute All", None))
        self.actionDelta_X_1.setText(QCoreApplication.translate("RobotWindow", u"robot 1", None))
        self.actionExecute.setText(QCoreApplication.translate("RobotWindow", u"Execute", None))
        self.actionBaudrate.setText(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.actionScale.setText(QCoreApplication.translate("RobotWindow", u"Scale", None))
        self.twDeltaManager.setTabText(self.twDeltaManager.indexOf(self.tabDefaultDelta), QCoreApplication.translate("RobotWindow", u"robot 1", None))
        self.twDeltaManager.setTabText(self.twDeltaManager.indexOf(self.tabAddNewDelta), QCoreApplication.translate("RobotWindow", u"+", None))
        self.label_122.setText(QCoreApplication.translate("RobotWindow", u"IP", None))
        self.leIP.setText(QCoreApplication.translate("RobotWindow", u"127.0.0.1", None))
        self.label_123.setText(QCoreApplication.translate("RobotWindow", u"Port", None))
        self.lePort.setText(QCoreApplication.translate("RobotWindow", u"8844", None))
#if QT_CONFIG(tooltip)
        self.tbServerConfig.setToolTip(QCoreApplication.translate("RobotWindow", u"Config", None))
#endif // QT_CONFIG(tooltip)
        self.tbServerConfig.setText("")
#if QT_CONFIG(tooltip)
        self.twModule.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.rbEditorCurrent.setText(QCoreApplication.translate("RobotWindow", u"Current", None))
#if QT_CONFIG(tooltip)
        self.pbExecuteGcodes.setToolTip(QCoreApplication.translate("RobotWindow", u"Execute Gcode", None))
#endif // QT_CONFIG(tooltip)
        self.pbExecuteGcodes.setText(QCoreApplication.translate("RobotWindow", u"Run", None))
        self.label_7.setText(QCoreApplication.translate("RobotWindow", u"Thread", None))
        self.rbEditorStart.setText(QCoreApplication.translate("RobotWindow", u"Begin", None))
        self.cbProgramThreadID.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbProgramThreadID.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbProgramThreadID.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbProgramThreadID.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

#if QT_CONFIG(tooltip)
        self.pbOpenGcodeDocs.setToolTip(QCoreApplication.translate("RobotWindow", u"Gcode Docs", None))
#endif // QT_CONFIG(tooltip)
        self.pbOpenGcodeDocs.setText(QCoreApplication.translate("RobotWindow", u"Format", None))
#if QT_CONFIG(tooltip)
        self.pbSaveGcode.setToolTip(QCoreApplication.translate("RobotWindow", u"Save Gcode Into File", None))
#endif // QT_CONFIG(tooltip)
        self.pbSaveGcode.setText("")
#if QT_CONFIG(tooltip)
        self.pbCreateNewGcode.setToolTip(QCoreApplication.translate("RobotWindow", u"Creat New Editor", None))
#endif // QT_CONFIG(tooltip)
        self.pbCreateNewGcode.setText("")
#if QT_CONFIG(tooltip)
        self.pbFormat.setToolTip(QCoreApplication.translate("RobotWindow", u"Format Gcode Lines", None))
#endif // QT_CONFIG(tooltip)
        self.pbFormat.setText(QCoreApplication.translate("RobotWindow", u"Format", None))
        self.cbEditGcodeEditor.setText(QCoreApplication.translate("RobotWindow", u"Edit", None))
        self.label_119.setText(QCoreApplication.translate("RobotWindow", u"Home", None))
#if QT_CONFIG(tooltip)
        self.tbAddG28.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddG28.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddG28.setText(QCoreApplication.translate("RobotWindow", u"G28", None))
        self.label_120.setText(QCoreApplication.translate("RobotWindow", u"Move", None))
#if QT_CONFIG(tooltip)
        self.tbAddG01.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddG01.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddG01.setText(QCoreApplication.translate("RobotWindow", u"G01", None))
#if QT_CONFIG(tooltip)
        self.tbAddG02.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddG02.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddG02.setText(QCoreApplication.translate("RobotWindow", u"G02", None))
        self.label_121.setText(QCoreApplication.translate("RobotWindow", u"Sleep", None))
#if QT_CONFIG(tooltip)
        self.tbAddG04.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddG04.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddG04.setText(QCoreApplication.translate("RobotWindow", u"G04", None))
        self.label_127.setText(QCoreApplication.translate("RobotWindow", u"Output", None))
#if QT_CONFIG(tooltip)
        self.tbAddM03.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddM03.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddM03.setText(QCoreApplication.translate("RobotWindow", u"M03", None))
#if QT_CONFIG(tooltip)
        self.tbAddM05.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddM05.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddM05.setText(QCoreApplication.translate("RobotWindow", u"M05", None))
        self.label_131.setText(QCoreApplication.translate("RobotWindow", u"Input", None))
#if QT_CONFIG(tooltip)
        self.tbAddM07.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddM07.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddM07.setText(QCoreApplication.translate("RobotWindow", u"M07", None))
#if QT_CONFIG(tooltip)
        self.tbAddM08.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbAddM08.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbAddM08.setText(QCoreApplication.translate("RobotWindow", u"M08", None))
        self.pteGcodeArea.setHtml(QCoreApplication.translate("RobotWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Delta X 2 Example</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent"
                        ":0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#000000;\">N05</span><span style=\" font-family:'MS Shell Dlg 2';\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G28</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Acceleration</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N10 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">M204</span><span style=\" font-family:'MS Shell Dlg 2';\"> A1200</span></p>\n"
"<p style=\" margin-top:0px; ma"
                        "rgin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Speed</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N15 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> F200</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Declare variables</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -"
                        "qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N20 </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> = 0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N30 </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> = </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> + 1</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" f"
                        "ont-family:'MS Shell Dlg 2'; font-style:italic; color:#55aa00;\">;Call subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N35 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">M98</span><span style=\" font-family:'MS Shell Dlg 2';\"> P2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">; Begin subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N40 </span>"
                        "<span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">O2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N45 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-350</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N50 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> X-100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; tex"
                        "t-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N55 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-370</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N60 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-350</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N65 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2"
                        "';\"> X100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N70 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-370</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N75 M99</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;End subprogram</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px"
                        "; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Loop 5 times</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N80 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#00aa00;\">IF</span><span style=\" font-family:'MS Shell Dlg 2';\"> [</span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> LE 5] </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#00aa00;\">THEN</span><span style=\" font-family:'MS Shell Dlg 2';\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#ff5500;\">GOTO</span><span style=\" font-family:'MS Shell Dlg 2';\"> 30</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margi"
                        "n-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N85 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\"> </span></p></body></html>", None))
        self.label_49.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_118.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_134.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.label_135.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.label_141.setText(QCoreApplication.translate("RobotWindow", u"U", None))
        self.label_142.setText(QCoreApplication.translate("RobotWindow", u"V", None))
        self.label_148.setText(QCoreApplication.translate("RobotWindow", u"F", None))
        self.label_149.setText(QCoreApplication.translate("RobotWindow", u"A", None))
        self.label_150.setText(QCoreApplication.translate("RobotWindow", u"S", None))
        self.label_151.setText(QCoreApplication.translate("RobotWindow", u"E", None))
        self.label_152.setText(QCoreApplication.translate("RobotWindow", u"J", None))
        self.label_3.setText(QCoreApplication.translate("RobotWindow", u"Path", None))
#if QT_CONFIG(tooltip)
        self.tbOpenGcodePath.setToolTip(QCoreApplication.translate("RobotWindow", u"Open gcode folder", None))
#endif // QT_CONFIG(tooltip)
        self.tbOpenGcodePath.setText("")
#if QT_CONFIG(tooltip)
        self.tbBackGcodeFolder.setToolTip(QCoreApplication.translate("RobotWindow", u"Back", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbBackGcodeFolder.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbBackGcodeFolder.setText("")
#if QT_CONFIG(tooltip)
        self.tbNewGcodeFile.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbNewGcodeFile.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbNewGcodeFile.setText("")
#if QT_CONFIG(tooltip)
        self.tbRefreshExplorer.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbRefreshExplorer.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbRefreshExplorer.setText("")
#if QT_CONFIG(tooltip)
        self.tbDeleteGcodeFile.setToolTip(QCoreApplication.translate("RobotWindow", u"New", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.tbDeleteGcodeFile.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.tbDeleteGcodeFile.setText("")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_3), QCoreApplication.translate("RobotWindow", u"Explorer", None))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), QCoreApplication.translate("RobotWindow", u"Cloud", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tGcodeEditor), QCoreApplication.translate("RobotWindow", u"Gcode Editor", None))
        self.label_191.setText(QCoreApplication.translate("RobotWindow", u"ID", None))
        self.cbSelectedDetecting.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbSelectedDetecting.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbSelectedDetecting.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbSelectedDetecting.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.gbImageViewer.setTitle(QCoreApplication.translate("RobotWindow", u"Image Viewer", None))
#if QT_CONFIG(tooltip)
        self.pbFindChessboardTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Warp Perspective", None))
#endif // QT_CONFIG(tooltip)
        self.pbFindChessboardTool.setText("")
#if QT_CONFIG(tooltip)
        self.pbWarpTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Warp Perspective", None))
#endif // QT_CONFIG(tooltip)
        self.pbWarpTool.setText("")
#if QT_CONFIG(tooltip)
        self.pbAreaTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Warp Perspective", None))
#endif // QT_CONFIG(tooltip)
        self.pbAreaTool.setText("")
#if QT_CONFIG(tooltip)
        self.pbCalibPointTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Set Calib Point", None))
#endif // QT_CONFIG(tooltip)
        self.pbCalibPointTool.setText("")
#if QT_CONFIG(tooltip)
        self.pbMappingPointTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Check Point Position On Camera", None))
#endif // QT_CONFIG(tooltip)
        self.pbMappingPointTool.setText("")
#if QT_CONFIG(tooltip)
        self.pbGetSizeTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Get size tool", None))
#endif // QT_CONFIG(tooltip)
        self.pbGetSizeTool.setText("")
#if QT_CONFIG(tooltip)
        self.pbFilterTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Blob Filter", None))
#endif // QT_CONFIG(tooltip)
        self.pbFilterTool.setText("")
#if QT_CONFIG(tooltip)
        self.pbOpenObjectTable.setToolTip(QCoreApplication.translate("RobotWindow", u"Open Object Table", None))
#endif // QT_CONFIG(tooltip)
        self.pbOpenObjectTable.setText("")
#if QT_CONFIG(tooltip)
        self.pbClearObject.setToolTip(QCoreApplication.translate("RobotWindow", u"Clear All Objects", None))
#endif // QT_CONFIG(tooltip)
        self.pbClearObject.setText("")
        self.label_213.setText(QCoreApplication.translate("RobotWindow", u"Output", None))
        self.cbImageOutput.setItemText(0, QCoreApplication.translate("RobotWindow", u"Calibrating", None))
        self.cbImageOutput.setItemText(1, QCoreApplication.translate("RobotWindow", u"Detecting", None))
        self.cbImageOutput.setItemText(2, QCoreApplication.translate("RobotWindow", u"Original", None))

        self.lbDisplayRatio_2.setText(QCoreApplication.translate("RobotWindow", u"Zoom:", None))
        self.lbDisplayRatio_3.setText(QCoreApplication.translate("RobotWindow", u"Ctrl + Scroll", None))
        self.lbDisplayRatio.setText(QCoreApplication.translate("RobotWindow", u"Ratio: 100%", None))
        self.lbMatSize.setText(QCoreApplication.translate("RobotWindow", u"Re: 800x500", None))
        self.gbImageProvider.setTitle(QCoreApplication.translate("RobotWindow", u"Image Provider", None))
        self.label_176.setText(QCoreApplication.translate("RobotWindow", u"Source", None))
        self.cbSourceForImageProvider.setItemText(0, QCoreApplication.translate("RobotWindow", u"Webcam", None))
        self.cbSourceForImageProvider.setItemText(1, QCoreApplication.translate("RobotWindow", u"Industrial Camera", None))
        self.cbSourceForImageProvider.setItemText(2, QCoreApplication.translate("RobotWindow", u"Images", None))
        self.cbSourceForImageProvider.setItemText(3, QCoreApplication.translate("RobotWindow", u"Socket", None))

        self.label_6.setText(QCoreApplication.translate("RobotWindow", u"Encoder", None))
        self.cbEncoderForCamera.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbEncoderForCamera.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbEncoderForCamera.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbEncoderForCamera.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

#if QT_CONFIG(tooltip)
        self.pbLoadCamera.setToolTip(QCoreApplication.translate("RobotWindow", u"Load Camera", None))
#endif // QT_CONFIG(tooltip)
        self.pbLoadCamera.setText(QCoreApplication.translate("RobotWindow", u"Load Camera", None))
#if QT_CONFIG(tooltip)
        self.pbLoadTestImage.setToolTip(QCoreApplication.translate("RobotWindow", u"Load Image", None))
#endif // QT_CONFIG(tooltip)
        self.pbLoadTestImage.setText(QCoreApplication.translate("RobotWindow", u"Load Image", None))
        self.label_178.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.leImageWidth.setText(QCoreApplication.translate("RobotWindow", u"800", None))
        self.label_179.setText(QCoreApplication.translate("RobotWindow", u"H", None))
        self.leImageHeight.setText(QCoreApplication.translate("RobotWindow", u"500", None))
        self.label_73.setText(QCoreApplication.translate("RobotWindow", u"Interval", None))
        self.leCaptureInterval.setText(QCoreApplication.translate("RobotWindow", u"500", None))
        self.label_128.setText(QCoreApplication.translate("RobotWindow", u"ms", None))
#if QT_CONFIG(tooltip)
        self.pbStartAcquisition.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Play and Pause</p><p>M98 PpauseCamera</p><p>M98 PresumeCamera</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.pbStartAcquisition.setText("")
#if QT_CONFIG(tooltip)
        self.pbCapture.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Capture</p><p>M98 PcaptureCamera</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.pbCapture.setText("")
        self.lbCameraState.setText("")
        self.gbCameraCalibration.setTitle(QCoreApplication.translate("RobotWindow", u"Calibration", None))
        self.pbCalibStep1.setText(QCoreApplication.translate("RobotWindow", u"Step 1: Identify the 4 corners of the square for perspective correction", None))
        self.label_109.setText(QCoreApplication.translate("RobotWindow", u"Image 1", None))
        self.label_110.setText(QCoreApplication.translate("RobotWindow", u"Image 2", None))
        self.pbCalibStep2.setText(QCoreApplication.translate("RobotWindow", u"Step 2: Coordinate correction", None))
        self.leRealityPoint2X.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.leRealityPoint1Y.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.pbCalibPoint1.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
#if QT_CONFIG(shortcut)
        self.pbCalibPoint1.setShortcut(QCoreApplication.translate("RobotWindow", u"!", None))
#endif // QT_CONFIG(shortcut)
        self.label_140.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
#if QT_CONFIG(tooltip)
        self.pbImageMapping.setToolTip(QCoreApplication.translate("RobotWindow", u"Perspective Transformation", None))
#endif // QT_CONFIG(tooltip)
        self.pbImageMapping.setText(QCoreApplication.translate("RobotWindow", u"Calculate Mapping Matrix", None))
        self.leRealityPoint2Y.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.leRealityPoint1X.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_133.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_139.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_39.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_132.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_38.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.pbCalibPoint2.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
#if QT_CONFIG(shortcut)
        self.pbCalibPoint2.setShortcut(QCoreApplication.translate("RobotWindow", u"@", None))
#endif // QT_CONFIG(shortcut)
        self.gbCameraObject.setTitle(QCoreApplication.translate("RobotWindow", u"Object", None))
        self.label_126.setText(QCoreApplication.translate("RobotWindow", u"Detection algorithm", None))
        self.cbDetectingAlgorithm.setItemText(0, QCoreApplication.translate("RobotWindow", u"Find Blobs", None))
        self.cbDetectingAlgorithm.setItemText(1, QCoreApplication.translate("RobotWindow", u"Find Circles", None))
        self.cbDetectingAlgorithm.setItemText(2, QCoreApplication.translate("RobotWindow", u"External Script", None))

        self.label_45.setText(QCoreApplication.translate("RobotWindow", u"Overlay", None))
        self.leObjectOverlay.setText(QCoreApplication.translate("RobotWindow", u"1.0", None))
        self.leMaxWRec.setText(QCoreApplication.translate("RobotWindow", u"1.5", None))
        self.label_172.setText(QCoreApplication.translate("RobotWindow", u"Min", None))
        self.leMinLRec.setText(QCoreApplication.translate("RobotWindow", u"0.5", None))
        self.leMaxLRec.setText(QCoreApplication.translate("RobotWindow", u"1.5", None))
        self.leWRec.setText(QCoreApplication.translate("RobotWindow", u"30", None))
        self.label_173.setText(QCoreApplication.translate("RobotWindow", u"Max", None))
        self.leLRec.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.label_175.setText(QCoreApplication.translate("RobotWindow", u"Max", None))
        self.label_43.setText(QCoreApplication.translate("RobotWindow", u"Length", None))
        self.label_163.setText(QCoreApplication.translate("RobotWindow", u"Type", None))
        self.label_54.setText(QCoreApplication.translate("RobotWindow", u"pixel", None))
        self.leMinWRec.setText(QCoreApplication.translate("RobotWindow", u"0.5", None))
        self.label_55.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.cbObjectType.setItemText(0, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbObjectType.setItemText(1, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbObjectType.setItemText(2, QCoreApplication.translate("RobotWindow", u"3", None))
        self.cbObjectType.setItemText(3, QCoreApplication.translate("RobotWindow", u"4", None))
        self.cbObjectType.setItemText(4, QCoreApplication.translate("RobotWindow", u"5", None))
        self.cbObjectType.setItemText(5, QCoreApplication.translate("RobotWindow", u"+", None))

        self.label_42.setText(QCoreApplication.translate("RobotWindow", u"Width", None))
        self.label_174.setText(QCoreApplication.translate("RobotWindow", u"Min", None))
        self.pbRunExternalScript.setText("")
        self.cbImageSource.setItemText(0, QCoreApplication.translate("RobotWindow", u"Origin Image", None))
        self.cbImageSource.setItemText(1, QCoreApplication.translate("RobotWindow", u"Calibrated Image", None))
        self.cbImageSource.setItemText(2, QCoreApplication.translate("RobotWindow", u"Color Filtered Image", None))

        self.label_180.setText(QCoreApplication.translate("RobotWindow", u"Host IP", None))
        self.label_183.setText(QCoreApplication.translate("RobotWindow", u"8844", None))
        self.label_187.setText(QCoreApplication.translate("RobotWindow", u"string: \"#Object = [x],[y],[width],[height],[angle];\"", None))
        self.label_185.setText(QCoreApplication.translate("RobotWindow", u"Receive format", None))
        self.label_146.setText(QCoreApplication.translate("RobotWindow", u"Transmission Image", None))
        self.pbExternalScriptOpen.setText("")
        self.label_184.setText(QCoreApplication.translate("RobotWindow", u"Sending format", None))
        self.label_145.setText(QCoreApplication.translate("RobotWindow", u"Python Url", None))
        self.pbExternalScriptHelp.setText(QCoreApplication.translate("RobotWindow", u"?", None))
        self.label_186.setText(QCoreApplication.translate("RobotWindow", u"byte: \"[width][height][channel][data]\"", None))
        self.label_182.setText(QCoreApplication.translate("RobotWindow", u"Port", None))
        self.label_181.setText(QCoreApplication.translate("RobotWindow", u"127.0.0.1", None))
        self.lePythonUrl.setText(QCoreApplication.translate("RobotWindow", u"script-example/mushroom-2.0.py", None))
        self.pbOpenScriptExample.setText(QCoreApplication.translate("RobotWindow", u"Open script example", None))
        self.leCenterThreshold.setText(QCoreApplication.translate("RobotWindow", u"30", None))
        self.leEdgeThreshold.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.label_193.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_190.setText(QCoreApplication.translate("RobotWindow", u"Center Threshold", None))
        self.label_192.setText(QCoreApplication.translate("RobotWindow", u"Min Radius", None))
        self.leMaxRadius.setText(QCoreApplication.translate("RobotWindow", u"30", None))
        self.label_194.setText(QCoreApplication.translate("RobotWindow", u"Max Radius", None))
        self.label_195.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.leMinRadius.setText(QCoreApplication.translate("RobotWindow", u"5", None))
        self.label_188.setText(QCoreApplication.translate("RobotWindow", u"Edge Threshold", None))
        self.gbCameraVariable.setTitle(QCoreApplication.translate("RobotWindow", u"Variable", None))
        self.label_196.setText(QCoreApplication.translate("RobotWindow", u"Detecting Object List Name", None))
        self.leDetectingObjectListName.setText(QCoreApplication.translate("RobotWindow", u"#Objects", None))
        self.pbViewDataObjects.setText(QCoreApplication.translate("RobotWindow", u"Object Table", None))
#if QT_CONFIG(tooltip)
        self.pbClearDetectObjects.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Clear All Objects in Memory</p><p>M98 PclearObjects --&gt; Clear All</p><p>M98 PdeleteFirstObject --&gt; Delete First</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbClearDetectObjects.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbClearDetectObjects.setText(QCoreApplication.translate("RobotWindow", u"Clear Objects", None))
        self.lbTrackingObjectNumber.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_155.setText(QCoreApplication.translate("RobotWindow", u"Max X", None))
        self.label_56.setText(QCoreApplication.translate("RobotWindow", u"Min X", None))
        self.label_50.setText(QCoreApplication.translate("RobotWindow", u"Visible", None))
        self.leLimitMinX.setText(QCoreApplication.translate("RobotWindow", u"-300", None))
        self.label_44.setText(QCoreApplication.translate("RobotWindow", u"Limit Area", None))
        self.lbVisibleObjectNumber.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_48.setText(QCoreApplication.translate("RobotWindow", u"Tracking", None))
        self.leLimitMaxX.setText(QCoreApplication.translate("RobotWindow", u"1200", None))
        self.label_156.setText(QCoreApplication.translate("RobotWindow", u"Min Y", None))
        self.label_157.setText(QCoreApplication.translate("RobotWindow", u"Max Y", None))
        self.leLimitMinY.setText(QCoreApplication.translate("RobotWindow", u"-400", None))
        self.leLimitMaxY.setText(QCoreApplication.translate("RobotWindow", u"400", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tObjectDetecting), QCoreApplication.translate("RobotWindow", u"Object Detecting", None))
        self.gbImageProvider_2.setTitle(QCoreApplication.translate("RobotWindow", u"Tracking Manager", None))
        self.leDeviationAngle.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_164.setText(QCoreApplication.translate("RobotWindow", u"Encoder", None))
        self.cbTrackingEncoderSource.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbTrackingEncoderSource.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbTrackingEncoderSource.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))

        self.label_144.setText(QCoreApplication.translate("RobotWindow", u"List", None))
        self.cbReverseEncoderValue.setText(QCoreApplication.translate("RobotWindow", u"Reverse Value", None))
        self.label_167.setText(QCoreApplication.translate("RobotWindow", u"Direction", None))
        self.cbSelectedTracking.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbSelectedTracking.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbSelectedTracking.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbSelectedTracking.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.cbTrackingDirection.setItemText(0, QCoreApplication.translate("RobotWindow", u"X", None))
        self.cbTrackingDirection.setItemText(1, QCoreApplication.translate("RobotWindow", u"Y", None))

        self.label_168.setText(QCoreApplication.translate("RobotWindow", u"Deviation angle", None))
        self.label_160.setText(QCoreApplication.translate("RobotWindow", u"ID", None))
        self.label_169.setText(QCoreApplication.translate("RobotWindow", u"degree", None))
        self.leSelectedTrackingObjectList.setText(QCoreApplication.translate("RobotWindow", u"#Objects", None))
        self.gbCameraCalibration_3.setTitle(QCoreApplication.translate("RobotWindow", u"Angle", None))
        self.pbCalculateAngle.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.label_189.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_206.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_224.setText(QCoreApplication.translate("RobotWindow", u"Angle (degree)", None))
        self.pbAnglePoint1.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.pbAnglePoint2.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.gbCameraCalibration_4.setTitle(QCoreApplication.translate("RobotWindow", u"Vector", None))
        self.label_226.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_227.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_228.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.leAngleResult_3.setText(QCoreApplication.translate("RobotWindow", u"#Vector1", None))
        self.label_229.setText(QCoreApplication.translate("RobotWindow", u"Name", None))
        self.label_197.setText(QCoreApplication.translate("RobotWindow", u"Speed", None))
        self.label_209.setText(QCoreApplication.translate("RobotWindow", u"Angle", None))
        self.pbCalculateAngle_2.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.gbCameraCalibration_2.setTitle(QCoreApplication.translate("RobotWindow", u"Matrix", None))
        self.pbAddVariablePoint_2.setText(QCoreApplication.translate("RobotWindow", u"Add Matrix", None))
        self.label_202.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_203.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.label_204.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.label_166.setText(QCoreApplication.translate("RobotWindow", u"Source", None))
        self.label_200.setText(QCoreApplication.translate("RobotWindow", u"Destination", None))
        self.label_165.setText(QCoreApplication.translate("RobotWindow", u"Name", None))
        self.label_201.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.leMatrix1Name.setText(QCoreApplication.translate("RobotWindow", u"#Matrix1", None))
        self.label_177.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_205.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.pbCalculateMappingMatrixTool.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.gbCameraObject_2.setTitle(QCoreApplication.translate("RobotWindow", u"Point", None))
        self.pbAddVariablePoint.setText(QCoreApplication.translate("RobotWindow", u"Add Point", None))
        self.label_136.setText(QCoreApplication.translate("RobotWindow", u"Name", None))
        self.lePoint1Name.setText(QCoreApplication.translate("RobotWindow", u"#Point1", None))
        self.label_137.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_138.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_143.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.gbCameraObject_3.setTitle(QCoreApplication.translate("RobotWindow", u"Point Matrix", None))
        self.pbAddVariablePoint_3.setText(QCoreApplication.translate("RobotWindow", u"Add Point", None))
        self.label_210.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_218.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_211.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.label_212.setText(QCoreApplication.translate("RobotWindow", u"Point 3", None))
        self.label_216.setText(QCoreApplication.translate("RobotWindow", u"Name", None))
        self.lePointMatrixName.setText(QCoreApplication.translate("RobotWindow", u"#PointMatrix", None))
        self.label_217.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.label_219.setText(QCoreApplication.translate("RobotWindow", u"Point 4", None))
        self.pbCalculatePointMatrixTool.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.gbCameraObject_4.setTitle(QCoreApplication.translate("RobotWindow", u"Test", None))
        self.leTestMatrixName.setText(QCoreApplication.translate("RobotWindow", u"#PointMatrix", None))
        self.pbCalculateTestPoint.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.label_215.setText(QCoreApplication.translate("RobotWindow", u"Point", None))
        self.label_223.setText(QCoreApplication.translate("RobotWindow", u"multiply", None))
        self.label_222.setText(QCoreApplication.translate("RobotWindow", u"Matrix", None))
        self.label_221.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_214.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tPointTool), QCoreApplication.translate("RobotWindow", u"Point Tool", None))
        self.pbOpenPicture.setText(QCoreApplication.translate("RobotWindow", u"Load Image", None))
        self.lbImageForDrawing.setText("")
        self.lbImageWidth.setText(QCoreApplication.translate("RobotWindow", u"W: 300", None))
        self.lbImageHeight.setText(QCoreApplication.translate("RobotWindow", u"H: 100", None))
        self.cbConversionTool.setItemText(0, QCoreApplication.translate("RobotWindow", u"Threshold", None))
        self.cbConversionTool.setItemText(1, QCoreApplication.translate("RobotWindow", u"Vectorize", None))
        self.cbConversionTool.setItemText(2, QCoreApplication.translate("RobotWindow", u"Gray", None))

        self.leDrawingThreshold.setText(QCoreApplication.translate("RobotWindow", u"150", None))
        self.label_14.setText(QCoreApplication.translate("RobotWindow", u"Conversion Tool", None))
        self.label_105.setText(QCoreApplication.translate("RobotWindow", u"Reverse", None))
        self.cbReverseDrawing.setText("")
        self.pbPainting.setText(QCoreApplication.translate("RobotWindow", u"Draw", None))
        self.label_20.setText(QCoreApplication.translate("RobotWindow", u"Height", None))
        self.label_18.setText(QCoreApplication.translate("RobotWindow", u"Width", None))
        self.cbLockDrawingArea.setItemText(0, QCoreApplication.translate("RobotWindow", u"Height", None))
        self.cbLockDrawingArea.setItemText(1, QCoreApplication.translate("RobotWindow", u"Width", None))

        self.label_104.setText(QCoreApplication.translate("RobotWindow", u"Lock", None))
        self.leWidthScale.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.leHeightScale.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.label_21.setText(QCoreApplication.translate("RobotWindow", u"100%", None))
        self.lbDrawingArea.setText("")
        self.label_26.setText(QCoreApplication.translate("RobotWindow", u"O", None))
        self.label_25.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.label_24.setText(QCoreApplication.translate("RobotWindow", u"H", None))
        self.label_22.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_19.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.leDrawAg1.setText("")
        self.pbDrawLine.setText(QCoreApplication.translate("RobotWindow", u"Line", None))
        self.pbDrawRectangle.setText(QCoreApplication.translate("RobotWindow", u"Rectangle", None))
        self.pbZoomIn.setText(QCoreApplication.translate("RobotWindow", u"Zoom In", None))
        self.pbCursor.setText(QCoreApplication.translate("RobotWindow", u"Cursor", None))
        self.pbDrawArc.setText(QCoreApplication.translate("RobotWindow", u"Arc", None))
        self.pbDrawCircle.setText(QCoreApplication.translate("RobotWindow", u"Circle", None))
        self.pbZoomOut.setText(QCoreApplication.translate("RobotWindow", u"Zoom Out", None))
        self.pbExportDrawingGcodes.setText(QCoreApplication.translate("RobotWindow", u"Export G-code", None))
        self.label_96.setText(QCoreApplication.translate("RobotWindow", u"Travel Speed", None))
        self.label_101.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_13.setText(QCoreApplication.translate("RobotWindow", u"Move Type", None))
        self.label_97.setText(QCoreApplication.translate("RobotWindow", u"Drawing Speed", None))
        self.cbDrawMethod.setItemText(0, QCoreApplication.translate("RobotWindow", u"Line", None))
        self.cbDrawMethod.setItemText(1, QCoreApplication.translate("RobotWindow", u"Dot", None))

        self.cbDrawingEffector.setItemText(0, QCoreApplication.translate("RobotWindow", u"Laser", None))
        self.cbDrawingEffector.setItemText(1, QCoreApplication.translate("RobotWindow", u"Pen", None))

        self.label_102.setText(QCoreApplication.translate("RobotWindow", u"mm/s2", None))
        self.label_93.setText(QCoreApplication.translate("RobotWindow", u"Drawing Tool", None))
        self.label_95.setText(QCoreApplication.translate("RobotWindow", u"Drawing Z Height", None))
        self.label_100.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_98.setText(QCoreApplication.translate("RobotWindow", u"Acceleration", None))
        self.label_99.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_23.setText(QCoreApplication.translate("RobotWindow", u"Density", None))
        self.leSpace.setText(QCoreApplication.translate("RobotWindow", u"1", None))
        self.label_103.setText(QCoreApplication.translate("RobotWindow", u"mm/dot(line)", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tDrawing), QCoreApplication.translate("RobotWindow", u"Drawing", None))
        self.teDebug.setHtml(QCoreApplication.translate("RobotWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-size:7.8pt;\"><br /></p></body></html>", None))
        self.label_4.setText(QCoreApplication.translate("RobotWindow", u"Sender", None))
        self.label_5.setText(QCoreApplication.translate("RobotWindow", u"Receiver", None))
        self.cbDeviceSender.setItemText(0, QCoreApplication.translate("RobotWindow", u"Software", None))
        self.cbDeviceSender.setItemText(1, QCoreApplication.translate("RobotWindow", u"Robot", None))
        self.cbDeviceSender.setItemText(2, QCoreApplication.translate("RobotWindow", u"Conveyor", None))
        self.cbDeviceSender.setItemText(3, QCoreApplication.translate("RobotWindow", u"Slider", None))
        self.cbDeviceSender.setItemText(4, QCoreApplication.translate("RobotWindow", u"External MCU", None))
        self.cbDeviceSender.setItemText(5, QCoreApplication.translate("RobotWindow", u"Encoder", None))

        self.twModule.setTabText(self.twModule.indexOf(self.TermiteTab), QCoreApplication.translate("RobotWindow", u"Termite", None))
        self.label.setText(QCoreApplication.translate("RobotWindow", u"Select Robot ID", None))
        self.cbSelectedRobot.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbSelectedRobot.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbSelectedRobot.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbSelectedRobot.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.pbConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.cbAutoConnect.setText(QCoreApplication.translate("RobotWindow", u"Auto", None))
        self.lbComName.setText(QCoreApplication.translate("RobotWindow", u"NONE", None))
        self.label_10.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.label_91.setText(QCoreApplication.translate("RobotWindow", u"Model", None))
        self.cbRobotDOF.setItemText(0, QCoreApplication.translate("RobotWindow", u"3 DOF", None))
        self.cbRobotDOF.setItemText(1, QCoreApplication.translate("RobotWindow", u"4 DOF", None))
        self.cbRobotDOF.setItemText(2, QCoreApplication.translate("RobotWindow", u"5 DOF", None))
        self.cbRobotDOF.setItemText(3, QCoreApplication.translate("RobotWindow", u"6 DOF", None))

        self.lbBaudrate.setText(QCoreApplication.translate("RobotWindow", u"115200", None))
        self.label_65.setText(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.cbRobotModel.setItemText(0, QCoreApplication.translate("RobotWindow", u"Delta X 1", None))
        self.cbRobotModel.setItemText(1, QCoreApplication.translate("RobotWindow", u"Delta X 2", None))
        self.cbRobotModel.setItemText(2, QCoreApplication.translate("RobotWindow", u"Delta X S", None))
        self.cbRobotModel.setItemText(3, QCoreApplication.translate("RobotWindow", u"Custom", None))

        self.label_113.setText(QCoreApplication.translate("RobotWindow", u"DOF", None))
        self.label_94.setText(QCoreApplication.translate("RobotWindow", u"V", None))
#if QT_CONFIG(tooltip)
        self.tbRequestPosition.setToolTip(QCoreApplication.translate("RobotWindow", u"Creat New Editor", None))
#endif // QT_CONFIG(tooltip)
        self.tbRequestPosition.setText(QCoreApplication.translate("RobotWindow", u"Position", None))
        self.lbV.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbY.setText(QCoreApplication.translate("RobotWindow", u"0", None))
#if QT_CONFIG(tooltip)
        self.tbDisableRobot.setToolTip(QCoreApplication.translate("RobotWindow", u"Creat New Editor", None))
#endif // QT_CONFIG(tooltip)
        self.tbDisableRobot.setText(QCoreApplication.translate("RobotWindow", u"Hold", None))
        self.lbZ.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbW.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_92.setText(QCoreApplication.translate("RobotWindow", u"U", None))
        self.label_88.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.label_84.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.lbU.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbX.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_90.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.label_86.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.pbHome.setText(QCoreApplication.translate("RobotWindow", u"Home", None))
        self.label_106.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.pbsubY.setText(QCoreApplication.translate("RobotWindow", u"-", None))
#if QT_CONFIG(shortcut)
        self.pbsubY.setShortcut(QCoreApplication.translate("RobotWindow", u"2", None))
#endif // QT_CONFIG(shortcut)
        self.pbplusY.setText(QCoreApplication.translate("RobotWindow", u"+", None))
#if QT_CONFIG(shortcut)
        self.pbplusY.setShortcut(QCoreApplication.translate("RobotWindow", u"8", None))
#endif // QT_CONFIG(shortcut)
        self.label_9.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_40.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.pbsubX.setText(QCoreApplication.translate("RobotWindow", u"-", None))
#if QT_CONFIG(shortcut)
        self.pbsubX.setShortcut(QCoreApplication.translate("RobotWindow", u"4", None))
#endif // QT_CONFIG(shortcut)
        self.leX.setText("")
        self.pbplusX.setText(QCoreApplication.translate("RobotWindow", u"+", None))
#if QT_CONFIG(shortcut)
        self.pbplusX.setShortcut(QCoreApplication.translate("RobotWindow", u"6", None))
#endif // QT_CONFIG(shortcut)
        self.label_8.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_107.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.pbsubZ.setText(QCoreApplication.translate("RobotWindow", u"-", None))
#if QT_CONFIG(shortcut)
        self.pbsubZ.setShortcut(QCoreApplication.translate("RobotWindow", u"3", None))
#endif // QT_CONFIG(shortcut)
        self.pbplusZ.setText(QCoreApplication.translate("RobotWindow", u"+", None))
#if QT_CONFIG(shortcut)
        self.pbplusZ.setShortcut(QCoreApplication.translate("RobotWindow", u"9", None))
#endif // QT_CONFIG(shortcut)
        self.label_66.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_108.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.pbsubW.setText(QCoreApplication.translate("RobotWindow", u"-", None))
#if QT_CONFIG(shortcut)
        self.pbsubW.setShortcut(QCoreApplication.translate("RobotWindow", u"1", None))
#endif // QT_CONFIG(shortcut)
        self.pbplusW.setText(QCoreApplication.translate("RobotWindow", u"+", None))
#if QT_CONFIG(shortcut)
        self.pbplusW.setShortcut(QCoreApplication.translate("RobotWindow", u"7", None))
#endif // QT_CONFIG(shortcut)
        self.label_81.setText(QCoreApplication.translate("RobotWindow", u"deg", None))
        self.label_111.setText(QCoreApplication.translate("RobotWindow", u"U", None))
        self.pbsubU.setText(QCoreApplication.translate("RobotWindow", u"-", None))
        self.pbplusU.setText(QCoreApplication.translate("RobotWindow", u"+", None))
        self.label_87.setText(QCoreApplication.translate("RobotWindow", u"deg", None))
        self.label_112.setText(QCoreApplication.translate("RobotWindow", u"V", None))
        self.pbsubV.setText(QCoreApplication.translate("RobotWindow", u"-", None))
        self.pbplusV.setText(QCoreApplication.translate("RobotWindow", u"+", None))
        self.label_89.setText(QCoreApplication.translate("RobotWindow", u"deg", None))
        self.label_29.setText(QCoreApplication.translate("RobotWindow", u"Velocity", None))
        self.label_116.setText(QCoreApplication.translate("RobotWindow", u"End", None))
        self.label_63.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.leAccel.setText("")
        self.leAccel.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_32.setText(QCoreApplication.translate("RobotWindow", u"mm/s2", None))
        self.label_117.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.leVelocity.setText("")
        self.leVelocity.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.leStartSpeed.setText("")
        self.leStartSpeed.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_62.setText(QCoreApplication.translate("RobotWindow", u"Start", None))
        self.leEndSpeed.setText("")
        self.leEndSpeed.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_30.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_31.setText(QCoreApplication.translate("RobotWindow", u"Accel", None))
        self.label_64.setText(QCoreApplication.translate("RobotWindow", u"mm/s3", None))
        self.label_47.setText(QCoreApplication.translate("RobotWindow", u"Jerk", None))
        self.leJerk.setText("")
        self.leJerk.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.tab_4), QCoreApplication.translate("RobotWindow", u"Parameter", None))
        self.cbDivision.setItemText(0, QCoreApplication.translate("RobotWindow", u"0.5", None))
        self.cbDivision.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbDivision.setItemText(2, QCoreApplication.translate("RobotWindow", u"5", None))
        self.cbDivision.setItemText(3, QCoreApplication.translate("RobotWindow", u"10", None))
        self.cbDivision.setItemText(4, QCoreApplication.translate("RobotWindow", u"50", None))
        self.cbDivision.setItemText(5, QCoreApplication.translate("RobotWindow", u"100", None))

        self.cbDivision.setCurrentText(QCoreApplication.translate("RobotWindow", u"1", None))
        self.label_33.setText(QCoreApplication.translate("RobotWindow", u"Step (mm)", None))
#if QT_CONFIG(tooltip)
        self.pbLeft.setToolTip(QCoreApplication.translate("RobotWindow", u"Left (shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbLeft.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbLeft.setText(QCoreApplication.translate("RobotWindow", u"X-", None))
#if QT_CONFIG(shortcut)
        self.pbLeft.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+A", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbRight.setToolTip(QCoreApplication.translate("RobotWindow", u"Right (Shift +d)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbRight.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbRight.setText(QCoreApplication.translate("RobotWindow", u"X+", None))
#if QT_CONFIG(shortcut)
        self.pbRight.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+D", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbBackward.setToolTip(QCoreApplication.translate("RobotWindow", u"Backward (shift + s)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbBackward.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbBackward.setText(QCoreApplication.translate("RobotWindow", u"Y-", None))
#if QT_CONFIG(shortcut)
        self.pbBackward.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+S", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbForward.setToolTip(QCoreApplication.translate("RobotWindow", u"Forward (Shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbForward.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbForward.setText(QCoreApplication.translate("RobotWindow", u"Y+", None))
#if QT_CONFIG(shortcut)
        self.pbForward.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+W", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbSubRoll.setToolTip(QCoreApplication.translate("RobotWindow", u"Left (shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbSubRoll.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbSubRoll.setText(QCoreApplication.translate("RobotWindow", u"W-", None))
#if QT_CONFIG(shortcut)
        self.pbSubRoll.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+A", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbPlusRoll.setToolTip(QCoreApplication.translate("RobotWindow", u"Right (Shift +d)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbPlusRoll.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbPlusRoll.setText(QCoreApplication.translate("RobotWindow", u"W+", None))
#if QT_CONFIG(shortcut)
        self.pbPlusRoll.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+D", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbPlusYaw.setToolTip(QCoreApplication.translate("RobotWindow", u"Right (Shift +d)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbPlusYaw.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbPlusYaw.setText(QCoreApplication.translate("RobotWindow", u"U+", None))
#if QT_CONFIG(shortcut)
        self.pbPlusYaw.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+D", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbSubYaw.setToolTip(QCoreApplication.translate("RobotWindow", u"Left (shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbSubYaw.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbSubYaw.setText(QCoreApplication.translate("RobotWindow", u"U-", None))
#if QT_CONFIG(shortcut)
        self.pbSubYaw.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+A", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbPlusPitch.setToolTip(QCoreApplication.translate("RobotWindow", u"Right (Shift +d)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbPlusPitch.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbPlusPitch.setText(QCoreApplication.translate("RobotWindow", u"V+", None))
#if QT_CONFIG(shortcut)
        self.pbPlusPitch.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+D", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbSubPitch.setToolTip(QCoreApplication.translate("RobotWindow", u"Left (shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbSubPitch.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbSubPitch.setText(QCoreApplication.translate("RobotWindow", u"V-", None))
#if QT_CONFIG(shortcut)
        self.pbSubPitch.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+A", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbDown.setToolTip(QCoreApplication.translate("RobotWindow", u"Down (shift + f)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbDown.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbDown.setText(QCoreApplication.translate("RobotWindow", u"Z-", None))
#if QT_CONFIG(shortcut)
        self.pbDown.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+F", None))
#endif // QT_CONFIG(shortcut)
#if QT_CONFIG(tooltip)
        self.pbUp.setToolTip(QCoreApplication.translate("RobotWindow", u"Up (shift + r)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbUp.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbUp.setText(QCoreApplication.translate("RobotWindow", u"Z+", None))
#if QT_CONFIG(shortcut)
        self.pbUp.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+R", None))
#endif // QT_CONFIG(shortcut)
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.ButtonTab), QCoreApplication.translate("RobotWindow", u"Button", None))
        self.label_53.setText(QCoreApplication.translate("RobotWindow", u"Size", None))
        self.cbWorkingSize.setItemText(0, QCoreApplication.translate("RobotWindow", u"300 x 300", None))
        self.cbWorkingSize.setItemText(1, QCoreApplication.translate("RobotWindow", u"400 x 400", None))
        self.cbWorkingSize.setItemText(2, QCoreApplication.translate("RobotWindow", u"600 x 600", None))
        self.cbWorkingSize.setItemText(3, QCoreApplication.translate("RobotWindow", u"800 x 800 ", None))

        self.label_15.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.label_72.setText(QCoreApplication.translate("RobotWindow", u"6-Axis", None))
        self.label_69.setText(QCoreApplication.translate("RobotWindow", u"4-Axis", None))
        self.label_71.setText(QCoreApplication.translate("RobotWindow", u"5-Axis", None))
        self.lb4AxisValue.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lb5AxisValue.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lb6AxisValue.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_60.setText(QCoreApplication.translate("RobotWindow", u"5-Axis", None))
        self.label_61.setText(QCoreApplication.translate("RobotWindow", u"6-Axis", None))
        self.label_16.setText(QCoreApplication.translate("RobotWindow", u"4-Axis", None))
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.SliderTab), QCoreApplication.translate("RobotWindow", u"Slider", None))
        self.label_79.setText(QCoreApplication.translate("RobotWindow", u"Sensibility", None))
        self.cbJoystickDevice.setCurrentText("")
        self.label_41.setText(QCoreApplication.translate("RobotWindow", u"Device", None))
        self.leJoystickRange.setText(QCoreApplication.translate("RobotWindow", u"1", None))
        self.leJoystickSensibility.setText(QCoreApplication.translate("RobotWindow", u"0.7", None))
        self.label_51.setText(QCoreApplication.translate("RobotWindow", u"Range", None))
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.tab_2), QCoreApplication.translate("RobotWindow", u"Joystick", None))
        self.RobotTabWidget.setTabText(self.RobotTabWidget.indexOf(self.MoveTab), QCoreApplication.translate("RobotWindow", u"Move", None))
        self.gbDeltaX12Output.setTitle(QCoreApplication.translate("RobotWindow", u"Delta X 1/ X 2 Output", None))
        self.gbRelay.setTitle(QCoreApplication.translate("RobotWindow", u"On/Off", None))
        self.label_34.setText(QCoreApplication.translate("RobotWindow", u"Vacuum", None))
        self.label_35.setText(QCoreApplication.translate("RobotWindow", u"Laser", None))
        self.pbPump.setText("")
        self.pbLaser.setText("")
        self.gbGripper.setTitle(QCoreApplication.translate("RobotWindow", u"RC Servo Gripper", None))
        self.label_17.setText(QCoreApplication.translate("RobotWindow", u"min", None))
        self.label_27.setText(QCoreApplication.translate("RobotWindow", u"max", None))
        self.pbGrip.setText(QCoreApplication.translate("RobotWindow", u"Grip", None))
        self.leGripperMin.setText(QCoreApplication.translate("RobotWindow", u"5", None))
        self.leGripperMax.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.lbGripperValue.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.gbOutput.setTitle(QCoreApplication.translate("RobotWindow", u"Delta X S Output", None))
        self.cbDx.setText("")
        self.cbRx.setText("")
        self.label_67.setText(QCoreApplication.translate("RobotWindow", u"Custom", None))
        self.leRx.setText(QCoreApplication.translate("RobotWindow", u"R0", None))
        self.leDx.setText(QCoreApplication.translate("RobotWindow", u"D0", None))
        self.label_68.setText(QCoreApplication.translate("RobotWindow", u"Digital", None))
        self.cbD1.setText(QCoreApplication.translate("RobotWindow", u"D1", None))
        self.cbD2.setText(QCoreApplication.translate("RobotWindow", u"D2", None))
        self.cbD3.setText(QCoreApplication.translate("RobotWindow", u"D3", None))
        self.cbD0.setText(QCoreApplication.translate("RobotWindow", u"D0", None))
        self.cbD4.setText(QCoreApplication.translate("RobotWindow", u"D4", None))
        self.cbD5.setText(QCoreApplication.translate("RobotWindow", u"D5", None))
        self.cbD6.setText(QCoreApplication.translate("RobotWindow", u"D6", None))
        self.cbD7.setText(QCoreApplication.translate("RobotWindow", u"D7", None))
        self.tabWidget_3.setTabText(self.tabWidget_3.indexOf(self.OutputTab), QCoreApplication.translate("RobotWindow", u"Output", None))
        self.gbInput.setTitle(QCoreApplication.translate("RobotWindow", u"Delta X S Input", None))
        self.label_70.setText(QCoreApplication.translate("RobotWindow", u"I0", None))
        self.lbI0Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle0.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle0.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI0.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_74.setText(QCoreApplication.translate("RobotWindow", u"I1", None))
        self.lbI1Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle1.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle1.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI1.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_76.setText(QCoreApplication.translate("RobotWindow", u"I2", None))
        self.lbI2Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle2.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle2.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI2.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_78.setText(QCoreApplication.translate("RobotWindow", u"I3", None))
        self.lbI3Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle3.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle3.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI3.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.leIx.setText(QCoreApplication.translate("RobotWindow", u"I4", None))
        self.leIx.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"I", None))
        self.lbIxValue.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbTogglex.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbTogglex.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadIx.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_83.setText(QCoreApplication.translate("RobotWindow", u"A0", None))
        self.lbA0Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.leA0Delay.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"0 ms", None))
        self.pbReadA0.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_85.setText(QCoreApplication.translate("RobotWindow", u"A1", None))
        self.lbA1Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.leA1Delay.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"0 ms", None))
        self.pbReadA1.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.leAx.setText(QCoreApplication.translate("RobotWindow", u"A2", None))
        self.leAx.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"I", None))
        self.lbAxValue.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.leAxDelay.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"0 ms", None))
        self.pbReadAx.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.tabWidget_3.setTabText(self.tabWidget_3.indexOf(self.InputTab), QCoreApplication.translate("RobotWindow", u"Input", None))
        self.RobotTabWidget.setTabText(self.RobotTabWidget.indexOf(self.IOTab), QCoreApplication.translate("RobotWindow", u"IO", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.tRobot), QCoreApplication.translate("RobotWindow", u"Robot", None))
        self.pbConveyorConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.label_2.setText(QCoreApplication.translate("RobotWindow", u"ID", None))
        self.cbSelectedConveyor.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbSelectedConveyor.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbSelectedConveyor.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbSelectedConveyor.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.label_28.setText(QCoreApplication.translate("RobotWindow", u"Type", None))
        self.cbConveyorType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Conveyor X", None))
        self.cbConveyorType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Conveyor Hub X", None))
        self.cbConveyorType.setItemText(2, QCoreApplication.translate("RobotWindow", u"Custom", None))

        self.lbConveyorCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
#if QT_CONFIG(tooltip)
        self.leConveyorXPosition.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \u2013 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI "
                        "Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFon"
                        "t','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color"
                        ":#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.leConveyorXPosition.setText(QCoreApplication.translate("RobotWindow", u"-100", None))
        self.cbConveyorValueType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Continuous", None))
        self.cbConveyorValueType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Position", None))

        self.lbUnitOfConveyorMoving.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_57.setText(QCoreApplication.translate("RobotWindow", u"Speed", None))
        self.label_46.setText(QCoreApplication.translate("RobotWindow", u"Moving Mode", None))
        self.cbConveyorMode.setItemText(0, QCoreApplication.translate("RobotWindow", u"Manual", None))
        self.cbConveyorMode.setItemText(1, QCoreApplication.translate("RobotWindow", u"UART", None))

#if QT_CONFIG(tooltip)
        self.cbConveyorMode.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"31\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">310 \u2013 Set Mode</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description: .</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI"
                        " Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M310 [&lt;index&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">1: Serial Mode.</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">0: Volume Mode.</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.label_12.setText(QCoreApplication.translate("RobotWindow", u"Position", None))
#if QT_CONFIG(tooltip)
        self.leConveyorXSpeed.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leConveyorXSpeed.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.label_52.setText(QCoreApplication.translate("RobotWindow", u"Control Mode", None))
        self.lbSpeedOfPositionMode.setText(QCoreApplication.translate("RobotWindow", u"mm/s2", None))
        self.label_77.setText(QCoreApplication.translate("RobotWindow", u"Position (mm)", None))
#if QT_CONFIG(tooltip)
        self.leSubConveyor1Position.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leSubConveyor1Position.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.label_115.setText(QCoreApplication.translate("RobotWindow", u"Moving Mode", None))
        self.label_114.setText(QCoreApplication.translate("RobotWindow", u"C3", None))
        self.cbSubConveyor2Mode.setItemText(0, QCoreApplication.translate("RobotWindow", u"Continuous", None))
        self.cbSubConveyor2Mode.setItemText(1, QCoreApplication.translate("RobotWindow", u"Position", None))

#if QT_CONFIG(tooltip)
        self.leSubConveyor1Speed.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \u2013 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI "
                        "Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFon"
                        "t','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color"
                        ":#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.leSubConveyor1Speed.setText(QCoreApplication.translate("RobotWindow", u"-100", None))
        self.label_75.setText(QCoreApplication.translate("RobotWindow", u"C1", None))
        self.label_82.setText(QCoreApplication.translate("RobotWindow", u"C2", None))
#if QT_CONFIG(tooltip)
        self.leSubConveyor2Position.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leSubConveyor2Position.setText(QCoreApplication.translate("RobotWindow", u"50", None))
#if QT_CONFIG(tooltip)
        self.leSubConveyor2Speed.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leSubConveyor2Speed.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.cbSubConveyor3Mode.setItemText(0, QCoreApplication.translate("RobotWindow", u"Continuous", None))
        self.cbSubConveyor3Mode.setItemText(1, QCoreApplication.translate("RobotWindow", u"Position", None))

#if QT_CONFIG(tooltip)
        self.leSubConveyor3Speed.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leSubConveyor3Speed.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.cbSubConveyor1Mode.setItemText(0, QCoreApplication.translate("RobotWindow", u"Continuous", None))
        self.cbSubConveyor1Mode.setItemText(1, QCoreApplication.translate("RobotWindow", u"Position", None))

        self.label_80.setText(QCoreApplication.translate("RobotWindow", u"Speed (mm/s2)", None))
#if QT_CONFIG(tooltip)
        self.leSubConveyor3Position.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leSubConveyor3Position.setText(QCoreApplication.translate("RobotWindow", u"50", None))
#if QT_CONFIG(tooltip)
        self.pbStopCustomConveyor2Command.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbStopCustomConveyor2Command.setText(QCoreApplication.translate("RobotWindow", u"robot0 M05 D1", None))
        self.pbStartCustomConveyor3.setText(QCoreApplication.translate("RobotWindow", u"Start", None))
        self.pbStopCustomConveyor3.setText(QCoreApplication.translate("RobotWindow", u"Stop", None))
        self.label_147.setText(QCoreApplication.translate("RobotWindow", u"C3", None))
#if QT_CONFIG(tooltip)
        self.pbStartCustomConveyor2Command.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbStartCustomConveyor2Command.setText(QCoreApplication.translate("RobotWindow", u"robot0 M03 D1", None))
        self.pbStopCustomConveyor2.setText(QCoreApplication.translate("RobotWindow", u"Stop", None))
#if QT_CONFIG(tooltip)
        self.pbStopCustomConveyor3Command.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbStopCustomConveyor3Command.setText(QCoreApplication.translate("RobotWindow", u"robot0 M05 D2", None))
        self.label_153.setText(QCoreApplication.translate("RobotWindow", u"C1", None))
        self.pbStartCustomConveyor1.setText(QCoreApplication.translate("RobotWindow", u"Start", None))
        self.pbStopCustomConveyor1.setText(QCoreApplication.translate("RobotWindow", u"Stop", None))
#if QT_CONFIG(tooltip)
        self.pbStopCustomConveyor1Command.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbStopCustomConveyor1Command.setText(QCoreApplication.translate("RobotWindow", u"robot0 M05 D0", None))
#if QT_CONFIG(tooltip)
        self.pbStartCustomConveyor1Command.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \u2013 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI "
                        "Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFon"
                        "t','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color"
                        ":#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.pbStartCustomConveyor1Command.setText(QCoreApplication.translate("RobotWindow", u"robot0 M03 D0", None))
        self.pbStartCustomConveyor2.setText(QCoreApplication.translate("RobotWindow", u"Start", None))
#if QT_CONFIG(tooltip)
        self.pbStartCustomConveyor3Command.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbStartCustomConveyor3Command.setText(QCoreApplication.translate("RobotWindow", u"robot0 M03 D2", None))
        self.label_154.setText(QCoreApplication.translate("RobotWindow", u"C2", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.ConveyorTab), QCoreApplication.translate("RobotWindow", u"Conveyor", None))
        self.pbConnectEncoder.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.label_11.setText(QCoreApplication.translate("RobotWindow", u"ID", None))
        self.cbSelectedEncoder.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbSelectedEncoder.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbSelectedEncoder.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbSelectedEncoder.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.label_124.setText(QCoreApplication.translate("RobotWindow", u"Type", None))
        self.cbEncoderType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Encoder X", None))
        self.cbEncoderType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Sub Encoder", None))
        self.cbEncoderType.setItemText(2, QCoreApplication.translate("RobotWindow", u"Virtual Encoder", None))

        self.lbEncoderCOMname.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.leEncoderVelocity.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.leEncoderInterval.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.leEncoderCurrentPosition.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.label_130.setText(QCoreApplication.translate("RobotWindow", u"Current Position (mm)", None))
        self.pbReadEncoder.setText(QCoreApplication.translate("RobotWindow", u"Read", None))
        self.pbSetEncoderVelocity.setText(QCoreApplication.translate("RobotWindow", u"Set", None))
        self.pbSetEncoderInterval.setText(QCoreApplication.translate("RobotWindow", u"Set", None))
        self.pbResetEncoder.setText(QCoreApplication.translate("RobotWindow", u"Reset", None))
        self.label_129.setText(QCoreApplication.translate("RobotWindow", u"Velocity (mm/s)", None))
        self.label_125.setText(QCoreApplication.translate("RobotWindow", u"Timer (ms)", None))
        self.cbEncoderActive.setText(QCoreApplication.translate("RobotWindow", u"Active", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.EncoderTab), QCoreApplication.translate("RobotWindow", u"Encoder", None))
        self.pbSlidingConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.label_161.setText(QCoreApplication.translate("RobotWindow", u"ID", None))
        self.cbSelectedSlider.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbSelectedSlider.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbSelectedSlider.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbSelectedSlider.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.lbSliderCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
#if QT_CONFIG(tooltip)
        self.pbSlidingDisable.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbSlidingDisable.setText(QCoreApplication.translate("RobotWindow", u"Disable motors", None))
        self.label_58.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_37.setText(QCoreApplication.translate("RobotWindow", u"Position", None))
#if QT_CONFIG(tooltip)
        self.pbSlidingHome.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbSlidingHome.setText(QCoreApplication.translate("RobotWindow", u"Home", None))
        self.label_36.setText(QCoreApplication.translate("RobotWindow", u"Speed", None))
        self.label_59.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.SliderTab1), QCoreApplication.translate("RobotWindow", u"Slider", None))
#if QT_CONFIG(tooltip)
        self.pbExternalControllerConnect.setToolTip(QCoreApplication.translate("RobotWindow", u"Connect External Controller", None))
#endif // QT_CONFIG(tooltip)
        self.pbExternalControllerConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.label_162.setText(QCoreApplication.translate("RobotWindow", u"ID", None))
        self.cbSelectedDevice.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbSelectedDevice.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbSelectedDevice.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbSelectedDevice.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.lbExternalCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.leTransmitToMCU.setText("")
        self.leTransmitToMCU.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"Transmit to MCU", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.MCUTab), QCoreApplication.translate("RobotWindow", u"External Device", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.PlusDeviceTab), QCoreApplication.translate("RobotWindow", u"+", None))
    # retranslateUi

