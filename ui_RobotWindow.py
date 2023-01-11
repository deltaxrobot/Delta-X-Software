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
from PySide6.QtWidgets import (QAbstractScrollArea, QApplication, QCheckBox, QComboBox,
    QFrame, QGridLayout, QGroupBox, QHBoxLayout,
    QLabel, QLayout, QLineEdit, QListWidget,
    QListWidgetItem, QMainWindow, QMenu, QMenuBar,
    QPushButton, QRadioButton, QScrollArea, QSizePolicy,
    QSlider, QSpacerItem, QSplitter, QTabWidget,
    QTextEdit, QToolButton, QVBoxLayout, QWidget)

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
"\n"
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
"\n"
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
"Q"
                        "GroupBox{\n"
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
"}\n"
""
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

        self.tabManagerLayout = QWidget(self.centralWidget)
        self.tabManagerLayout.setObjectName(u"tabManagerLayout")
        sizePolicy1 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.tabManagerLayout.sizePolicy().hasHeightForWidth())
        self.tabManagerLayout.setSizePolicy(sizePolicy1)
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
        font2 = QFont()
        font2.setPointSize(11)
        font2.setBold(False)
        self.twModule.setFont(font2)
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
        self.twModule.setUsesScrollButtons(False)
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
        self.pbExecuteGcodes = QPushButton(self.tGcodeEditor)
        self.pbExecuteGcodes.setObjectName(u"pbExecuteGcodes")
        sizePolicy2 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Expanding)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.pbExecuteGcodes.sizePolicy().hasHeightForWidth())
        self.pbExecuteGcodes.setSizePolicy(sizePolicy2)
        self.pbExecuteGcodes.setMinimumSize(QSize(70, 0))
        font3 = QFont()
        font3.setPointSize(10)
        self.pbExecuteGcodes.setFont(font3)
        self.pbExecuteGcodes.setAutoFillBackground(False)
        icon1 = QIcon()
        icon1.addFile(u":/icon/Play_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon1.addFile(u":/icon/Pause_96px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbExecuteGcodes.setIcon(icon1)
        self.pbExecuteGcodes.setIconSize(QSize(30, 30))
        self.pbExecuteGcodes.setCheckable(True)
        self.pbExecuteGcodes.setFlat(False)

        self.gridLayout_30.addWidget(self.pbExecuteGcodes, 0, 3, 3, 1)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_30.addItem(self.horizontalSpacer_2, 0, 1, 1, 1)

        self.rbEditorCurrent = QRadioButton(self.tGcodeEditor)
        self.rbEditorCurrent.setObjectName(u"rbEditorCurrent")
        self.rbEditorCurrent.setChecked(False)

        self.gridLayout_30.addWidget(self.rbEditorCurrent, 2, 2, 1, 1)

        self.rbEditorStart = QRadioButton(self.tGcodeEditor)
        self.rbEditorStart.setObjectName(u"rbEditorStart")
        self.rbEditorStart.setChecked(True)

        self.gridLayout_30.addWidget(self.rbEditorStart, 0, 2, 1, 1)

        self.cbLockGcodeEditor = QCheckBox(self.tGcodeEditor)
        self.cbLockGcodeEditor.setObjectName(u"cbLockGcodeEditor")
        font4 = QFont()
        font4.setPointSize(8)
        font4.setBold(False)
        font4.setKerning(True)
        self.cbLockGcodeEditor.setFont(font4)

        self.gridLayout_30.addWidget(self.cbLockGcodeEditor, 0, 0, 1, 1)

        self.horizontalLayout_12 = QHBoxLayout()
        self.horizontalLayout_12.setSpacing(6)
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.verticalLayout_8 = QVBoxLayout()
        self.verticalLayout_8.setSpacing(6)
        self.verticalLayout_8.setObjectName(u"verticalLayout_8")
        self.pbFormat = QToolButton(self.tGcodeEditor)
        self.pbFormat.setObjectName(u"pbFormat")
        icon2 = QIcon()
        icon2.addFile(u":/icon/index.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFormat.setIcon(icon2)
        self.pbFormat.setIconSize(QSize(30, 30))
        self.pbFormat.setAutoRaise(True)

        self.verticalLayout_8.addWidget(self.pbFormat)


        self.horizontalLayout_12.addLayout(self.verticalLayout_8)

        self.cbFormatColor = QCheckBox(self.tGcodeEditor)
        self.cbFormatColor.setObjectName(u"cbFormatColor")
        self.cbFormatColor.setChecked(True)

        self.horizontalLayout_12.addWidget(self.cbFormatColor)

        self.cbAutoNumbering = QCheckBox(self.tGcodeEditor)
        self.cbAutoNumbering.setObjectName(u"cbAutoNumbering")
        self.cbAutoNumbering.setChecked(True)

        self.horizontalLayout_12.addWidget(self.cbAutoNumbering)

        self.lbGcodeProgramingIssues = QLabel(self.tGcodeEditor)
        self.lbGcodeProgramingIssues.setObjectName(u"lbGcodeProgramingIssues")
        self.lbGcodeProgramingIssues.setStyleSheet(u"color: rgb(255, 0, 0);")

        self.horizontalLayout_12.addWidget(self.lbGcodeProgramingIssues)

        self.horizontalSpacer_3 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_12.addItem(self.horizontalSpacer_3)

        self.verticalLayout_9 = QVBoxLayout()
        self.verticalLayout_9.setSpacing(6)
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.pbSaveGcode = QToolButton(self.tGcodeEditor)
        self.pbSaveGcode.setObjectName(u"pbSaveGcode")
        sizePolicy.setHeightForWidth(self.pbSaveGcode.sizePolicy().hasHeightForWidth())
        self.pbSaveGcode.setSizePolicy(sizePolicy)
        self.pbSaveGcode.setMinimumSize(QSize(30, 30))
        icon3 = QIcon()
        icon3.addFile(u":/icon/save.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSaveGcode.setIcon(icon3)
        self.pbSaveGcode.setIconSize(QSize(32, 32))
        self.pbSaveGcode.setAutoRaise(True)

        self.verticalLayout_9.addWidget(self.pbSaveGcode)


        self.horizontalLayout_12.addLayout(self.verticalLayout_9)


        self.gridLayout_30.addLayout(self.horizontalLayout_12, 2, 0, 1, 1)


        self.verticalLayout.addLayout(self.gridLayout_30)

        self.scrollArea = QScrollArea(self.tGcodeEditor)
        self.scrollArea.setObjectName(u"scrollArea")
        self.scrollArea.setWidgetResizable(True)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 591, 1200))
        self.scrollAreaWidgetContents.setMinimumSize(QSize(450, 1200))
        self.verticalLayout_30 = QVBoxLayout(self.scrollAreaWidgetContents)
        self.verticalLayout_30.setSpacing(6)
        self.verticalLayout_30.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_30.setObjectName(u"verticalLayout_30")
        self.pteGcodeArea = CodeEditor(self.scrollAreaWidgetContents)
        self.pteGcodeArea.setObjectName(u"pteGcodeArea")
        sizePolicy3 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.pteGcodeArea.sizePolicy().hasHeightForWidth())
        self.pteGcodeArea.setSizePolicy(sizePolicy3)
        self.pteGcodeArea.setMinimumSize(QSize(310, 500))
        self.pteGcodeArea.setFont(font4)
        self.pteGcodeArea.setHorizontalScrollBarPolicy(Qt.ScrollBarAsNeeded)
        self.pteGcodeArea.setReadOnly(False)
        self.pteGcodeArea.setTextInteractionFlags(Qt.TextEditorInteraction)

        self.verticalLayout_30.addWidget(self.pteGcodeArea)

        self.tabWidget = QTabWidget(self.scrollAreaWidgetContents)
        self.tabWidget.setObjectName(u"tabWidget")
        self.tabWidget.setMinimumSize(QSize(0, 500))
        self.tab = QWidget()
        self.tab.setObjectName(u"tab")
        self.saProgramFiles = QScrollArea(self.tab)
        self.saProgramFiles.setObjectName(u"saProgramFiles")
        self.saProgramFiles.setEnabled(True)
        self.saProgramFiles.setGeometry(QRect(85, 45, 256, 300))
        self.saProgramFiles.setMinimumSize(QSize(240, 300))
        self.saProgramFiles.setStyleSheet(u"")
        self.saProgramFiles.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.saProgramFiles.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        self.saProgramFiles.setSizeAdjustPolicy(QAbstractScrollArea.AdjustToContents)
        self.saProgramFiles.setWidgetResizable(False)
        self.wgProgramContainer = QWidget()
        self.wgProgramContainer.setObjectName(u"wgProgramContainer")
        self.wgProgramContainer.setGeometry(QRect(0, 0, 279, 589))
        self.frExProgram = QFrame(self.wgProgramContainer)
        self.frExProgram.setObjectName(u"frExProgram")
        self.frExProgram.setGeometry(QRect(5, 10, 221, 61))
        self.frExProgram.setStyleSheet(u"QFrame{\n"
"border-radius: 2px;\n"
"border: 1px solid rgb(50, 50, 50)\n"
"}\n"
"\n"
"QLabel{\n"
"border: none\n"
"}")
        self.frExProgram.setFrameShape(QFrame.StyledPanel)
        self.frExProgram.setFrameShadow(QFrame.Raised)
        self.leExProgramName = QLineEdit(self.frExProgram)
        self.leExProgramName.setObjectName(u"leExProgramName")
        self.leExProgramName.setEnabled(True)
        self.leExProgramName.setGeometry(QRect(10, 5, 160, 30))
        self.leExProgramName.setFont(font3)
        self.leExProgramName.setCursor(QCursor(Qt.SizeHorCursor))
        self.leExProgramName.setStyleSheet(u"")
        self.pbExDeleteProgram = QPushButton(self.frExProgram)
        self.pbExDeleteProgram.setObjectName(u"pbExDeleteProgram")
        self.pbExDeleteProgram.setGeometry(QRect(180, 5, 30, 31))
        icon4 = QIcon()
        icon4.addFile(u"C:/Users/Admin/.designer/backup/icon/delete.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbExDeleteProgram.setIcon(icon4)
        self.pbExDeleteProgram.setIconSize(QSize(30, 30))
        self.pbExDeleteProgram.setAutoDefault(False)
        self.pbExDeleteProgram.setFlat(True)
        self.lbExGCodeNumber = QLabel(self.frExProgram)
        self.lbExGCodeNumber.setObjectName(u"lbExGCodeNumber")
        self.lbExGCodeNumber.setGeometry(QRect(10, 40, 101, 16))
        self.lbExGCodeNumber.setStyleSheet(u"")
        self.saProgramFiles.setWidget(self.wgProgramContainer)
        self.layoutWidget = QWidget(self.tab)
        self.layoutWidget.setObjectName(u"layoutWidget")
        self.layoutWidget.setGeometry(QRect(355, 45, 71, 91))
        self.verticalLayout_13 = QVBoxLayout(self.layoutWidget)
        self.verticalLayout_13.setSpacing(6)
        self.verticalLayout_13.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_13.setObjectName(u"verticalLayout_13")
        self.verticalLayout_13.setContentsMargins(0, 0, 0, 0)
        self.pbUploadProgram = QPushButton(self.layoutWidget)
        self.pbUploadProgram.setObjectName(u"pbUploadProgram")
        self.pbUploadProgram.setMinimumSize(QSize(40, 40))
        icon5 = QIcon()
        icon5.addFile(u":/icon/icons8-upload-to-cloud-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbUploadProgram.setIcon(icon5)
        self.pbUploadProgram.setIconSize(QSize(32, 32))
        self.pbUploadProgram.setFlat(False)

        self.verticalLayout_13.addWidget(self.pbUploadProgram)

        self.pbImportGcodeFiles = QPushButton(self.layoutWidget)
        self.pbImportGcodeFiles.setObjectName(u"pbImportGcodeFiles")
        self.pbImportGcodeFiles.setMinimumSize(QSize(40, 40))
        self.pbImportGcodeFiles.setIconSize(QSize(32, 32))
        self.pbImportGcodeFiles.setFlat(False)

        self.verticalLayout_13.addWidget(self.pbImportGcodeFiles)

        self.layoutWidget1 = QWidget(self.tab)
        self.layoutWidget1.setObjectName(u"layoutWidget1")
        self.layoutWidget1.setGeometry(QRect(5, 45, 66, 183))
        self.verticalLayout_14 = QVBoxLayout(self.layoutWidget1)
        self.verticalLayout_14.setSpacing(6)
        self.verticalLayout_14.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_14.setObjectName(u"verticalLayout_14")
        self.verticalLayout_14.setContentsMargins(0, 0, 0, 0)
        self.pbAddNewProgram = QPushButton(self.layoutWidget1)
        self.pbAddNewProgram.setObjectName(u"pbAddNewProgram")
        self.pbAddNewProgram.setMinimumSize(QSize(40, 40))
        icon6 = QIcon()
        icon6.addFile(u":/icon/new.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbAddNewProgram.setIcon(icon6)
        self.pbAddNewProgram.setIconSize(QSize(16, 16))
        self.pbAddNewProgram.setFlat(False)

        self.verticalLayout_14.addWidget(self.pbAddNewProgram)

        self.pbRefreshGcodeFiles = QPushButton(self.layoutWidget1)
        self.pbRefreshGcodeFiles.setObjectName(u"pbRefreshGcodeFiles")
        self.pbRefreshGcodeFiles.setMinimumSize(QSize(40, 40))
        icon7 = QIcon()
        icon7.addFile(u":/icon/Restart_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbRefreshGcodeFiles.setIcon(icon7)
        self.pbRefreshGcodeFiles.setIconSize(QSize(16, 16))
        self.pbRefreshGcodeFiles.setFlat(False)

        self.verticalLayout_14.addWidget(self.pbRefreshGcodeFiles)

        self.pbFindGcodeFile = QPushButton(self.layoutWidget1)
        self.pbFindGcodeFile.setObjectName(u"pbFindGcodeFile")
        self.pbFindGcodeFile.setMinimumSize(QSize(40, 40))
        icon8 = QIcon()
        icon8.addFile(u":/icon/Search_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFindGcodeFile.setIcon(icon8)
        self.pbFindGcodeFile.setIconSize(QSize(16, 16))
        self.pbFindGcodeFile.setFlat(False)

        self.verticalLayout_14.addWidget(self.pbFindGcodeFile)

        self.pbSortGcodeFiles = QPushButton(self.layoutWidget1)
        self.pbSortGcodeFiles.setObjectName(u"pbSortGcodeFiles")
        self.pbSortGcodeFiles.setMinimumSize(QSize(40, 40))
        icon9 = QIcon()
        icon9.addFile(u":/icon/Sort_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSortGcodeFiles.setIcon(icon9)
        self.pbSortGcodeFiles.setIconSize(QSize(16, 16))
        self.pbSortGcodeFiles.setFlat(False)

        self.verticalLayout_14.addWidget(self.pbSortGcodeFiles)

        self.lbExGCodeNumber_2 = QLabel(self.tab)
        self.lbExGCodeNumber_2.setObjectName(u"lbExGCodeNumber_2")
        self.lbExGCodeNumber_2.setGeometry(QRect(10, 20, 41, 16))
        self.lbExGCodeNumber_2.setStyleSheet(u"")
        self.leGcodeProgramPath = QLineEdit(self.tab)
        self.leGcodeProgramPath.setObjectName(u"leGcodeProgramPath")
        self.leGcodeProgramPath.setGeometry(QRect(85, 15, 251, 22))
        self.pbOpenGcodeProgramPath = QPushButton(self.tab)
        self.pbOpenGcodeProgramPath.setObjectName(u"pbOpenGcodeProgramPath")
        self.pbOpenGcodeProgramPath.setGeometry(QRect(355, 10, 30, 30))
        sizePolicy4 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.pbOpenGcodeProgramPath.sizePolicy().hasHeightForWidth())
        self.pbOpenGcodeProgramPath.setSizePolicy(sizePolicy4)
        self.pbOpenGcodeProgramPath.setMaximumSize(QSize(30, 16777215))
        icon10 = QIcon()
        icon10.addFile(u":/icon/icons8_folder_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbOpenGcodeProgramPath.setIcon(icon10)
        self.tabWidget.addTab(self.tab, "")
        self.tab_3 = QWidget()
        self.tab_3.setObjectName(u"tab_3")
        self.listWidget = QListWidget(self.tab_3)
        self.listWidget.setObjectName(u"listWidget")
        self.listWidget.setGeometry(QRect(5, 10, 171, 136))
        self.textEdit = QTextEdit(self.tab_3)
        self.textEdit.setObjectName(u"textEdit")
        self.textEdit.setGeometry(QRect(185, 10, 166, 91))
        self.pbUploadProgram_2 = QPushButton(self.tab_3)
        self.pbUploadProgram_2.setObjectName(u"pbUploadProgram_2")
        self.pbUploadProgram_2.setGeometry(QRect(185, 110, 56, 36))
        icon11 = QIcon()
        icon11.addFile(u"C:/Users/Admin/.designer/backup/icon/icons8-download-from-cloud-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbUploadProgram_2.setIcon(icon11)
        self.pbUploadProgram_2.setIconSize(QSize(32, 32))
        self.pbUploadProgram_2.setFlat(False)
        self.tabWidget.addTab(self.tab_3, "")

        self.verticalLayout_30.addWidget(self.tabWidget)

        self.verticalSpacer_9 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_30.addItem(self.verticalSpacer_9)

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
        self.wObjectDetecting.setGeometry(QRect(0, 0, 603, 4000))
        self.wObjectDetecting.setMinimumSize(QSize(450, 4000))
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
        self.splitter = QSplitter(self.wObjectDetecting)
        self.splitter.setObjectName(u"splitter")
        sizePolicy1.setHeightForWidth(self.splitter.sizePolicy().hasHeightForWidth())
        self.splitter.setSizePolicy(sizePolicy1)
        self.splitter.setStyleSheet(u"QSplitter::handle:vertical \n"
"{	\n"
"	background: rgb(37, 197, 255);\n"
"}")
        self.splitter.setOrientation(Qt.Vertical)
        self.splitter.setHandleWidth(10)
        self.gbImageViewer = QGroupBox(self.splitter)
        self.gbImageViewer.setObjectName(u"gbImageViewer")
        sizePolicy5 = QSizePolicy(QSizePolicy.Ignored, QSizePolicy.Ignored)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.gbImageViewer.sizePolicy().hasHeightForWidth())
        self.gbImageViewer.setSizePolicy(sizePolicy5)
        self.gbImageViewer.setMinimumSize(QSize(0, 0))
        self.gbImageViewer.setMaximumSize(QSize(16777215, 16777215))
        font5 = QFont()
        font5.setPointSize(10)
        font5.setBold(True)
        self.gbImageViewer.setFont(font5)
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
        icon12 = QIcon()
        icon12.addFile(u":/icon/icons8_chessboard_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFindChessboardTool.setIcon(icon12)
        self.pbFindChessboardTool.setCheckable(True)
        self.pbFindChessboardTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbFindChessboardTool)

        self.pbWarpTool = QPushButton(self.frame_16)
        self.pbWarpTool.setObjectName(u"pbWarpTool")
        self.pbWarpTool.setMinimumSize(QSize(30, 30))
        icon13 = QIcon()
        icon13.addFile(u":/icon/icons8_opacity_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbWarpTool.setIcon(icon13)
        self.pbWarpTool.setCheckable(True)
        self.pbWarpTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbWarpTool)

        self.pbAreaTool = QPushButton(self.frame_16)
        self.pbAreaTool.setObjectName(u"pbAreaTool")
        self.pbAreaTool.setMinimumSize(QSize(30, 30))
        icon14 = QIcon()
        icon14.addFile(u":/icon/icons8_rectangle_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbAreaTool.setIcon(icon14)
        self.pbAreaTool.setCheckable(True)
        self.pbAreaTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbAreaTool)

        self.pbCalibPointTool = QPushButton(self.frame_16)
        self.pbCalibPointTool.setObjectName(u"pbCalibPointTool")
        self.pbCalibPointTool.setMinimumSize(QSize(30, 30))
        icon15 = QIcon()
        icon15.addFile(u":/icon/icons8_select_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCalibPointTool.setIcon(icon15)
        self.pbCalibPointTool.setCheckable(True)
        self.pbCalibPointTool.setFlat(True)

        self.verticalLayout_7.addWidget(self.pbCalibPointTool)

        self.pbMappingPointTool = QPushButton(self.frame_16)
        self.pbMappingPointTool.setObjectName(u"pbMappingPointTool")
        self.pbMappingPointTool.setMinimumSize(QSize(30, 30))
        icon16 = QIcon()
        icon16.addFile(u":/icon/icons8_target_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbMappingPointTool.setIcon(icon16)
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
        icon17 = QIcon()
        icon17.addFile(u":/icon/icons8_page_size_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbGetSizeTool.setIcon(icon17)
        self.pbGetSizeTool.setCheckable(True)
        self.pbGetSizeTool.setAutoRaise(True)

        self.verticalLayout_50.addWidget(self.pbGetSizeTool)

        self.pbFilterTool = QPushButton(self.frame_8)
        self.pbFilterTool.setObjectName(u"pbFilterTool")
        self.pbFilterTool.setMinimumSize(QSize(30, 30))
        icon18 = QIcon()
        icon18.addFile(u":/icon/Slider 2_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFilterTool.setIcon(icon18)
        self.pbFilterTool.setFlat(True)

        self.verticalLayout_50.addWidget(self.pbFilterTool)

        self.pbOpenObjectTable = QPushButton(self.frame_8)
        self.pbOpenObjectTable.setObjectName(u"pbOpenObjectTable")
        self.pbOpenObjectTable.setMinimumSize(QSize(30, 30))
        icon19 = QIcon()
        icon19.addFile(u":/icon/icons8-object-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbOpenObjectTable.setIcon(icon19)
        self.pbOpenObjectTable.setFlat(True)

        self.verticalLayout_50.addWidget(self.pbOpenObjectTable)

        self.pbClearObject = QPushButton(self.frame_8)
        self.pbClearObject.setObjectName(u"pbClearObject")
        self.pbClearObject.setMinimumSize(QSize(30, 30))
        icon20 = QIcon()
        icon20.addFile(u":/icon/Eraser_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbClearObject.setIcon(icon20)
        self.pbClearObject.setFlat(True)

        self.verticalLayout_50.addWidget(self.pbClearObject)

        self.verticalSpacer_13 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_50.addItem(self.verticalSpacer_13)


        self.horizontalLayout_30.addWidget(self.frame_8)

        self.gvImageViewer = ImageViewer(self.fImageViewer)
        self.gvImageViewer.setObjectName(u"gvImageViewer")
        sizePolicy1.setHeightForWidth(self.gvImageViewer.sizePolicy().hasHeightForWidth())
        self.gvImageViewer.setSizePolicy(sizePolicy1)

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
        sizePolicy6 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Preferred)
        sizePolicy6.setHorizontalStretch(0)
        sizePolicy6.setVerticalStretch(0)
        sizePolicy6.setHeightForWidth(self.cbImageOutput.sizePolicy().hasHeightForWidth())
        self.cbImageOutput.setSizePolicy(sizePolicy6)
        self.cbImageOutput.setMinimumSize(QSize(90, 0))

        self.verticalLayout_10.addWidget(self.cbImageOutput)

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
        sizePolicy7 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy7.setHorizontalStretch(0)
        sizePolicy7.setVerticalStretch(30)
        sizePolicy7.setHeightForWidth(self.fObjectDetectingTool.sizePolicy().hasHeightForWidth())
        self.fObjectDetectingTool.setSizePolicy(sizePolicy7)
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
        self.gbImageProvider.setFont(font5)
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

        self.horizontalLayout_10.addWidget(self.cbSourceForImageProvider)

        self.horizontalSpacer_44 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_10.addItem(self.horizontalSpacer_44)


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
        font6 = QFont()
        font6.setPointSize(8)
        font6.setBold(False)
        self.pbLoadCamera.setFont(font6)
        icon21 = QIcon()
        icon21.addFile(u":/icon/webcam.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLoadCamera.setIcon(icon21)
        self.pbLoadCamera.setIconSize(QSize(30, 30))
        self.pbLoadCamera.setCheckable(True)
        self.pbLoadCamera.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbLoadCamera.setAutoRaise(True)

        self.horizontalLayout_11.addWidget(self.pbLoadCamera)

        self.label_11 = QLabel(self.fWebcamSource)
        self.label_11.setObjectName(u"label_11")
        self.label_11.setMaximumSize(QSize(30, 16777215))
        font7 = QFont()
        font7.setPointSize(8)
        self.label_11.setFont(font7)

        self.horizontalLayout_11.addWidget(self.label_11)

        self.leFPS = QLineEdit(self.fWebcamSource)
        self.leFPS.setObjectName(u"leFPS")
        sizePolicy8 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)
        sizePolicy8.setHorizontalStretch(0)
        sizePolicy8.setVerticalStretch(0)
        sizePolicy8.setHeightForWidth(self.leFPS.sizePolicy().hasHeightForWidth())
        self.leFPS.setSizePolicy(sizePolicy8)
        self.leFPS.setMinimumSize(QSize(0, 10))
        self.leFPS.setMaximumSize(QSize(40, 25))
        self.leFPS.setFont(font7)
        self.leFPS.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_11.addWidget(self.leFPS)

        self.label_124 = QLabel(self.fWebcamSource)
        self.label_124.setObjectName(u"label_124")
        self.label_124.setFont(font7)
        self.label_124.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_11.addWidget(self.label_124)

        self.leCameraWidth = QLineEdit(self.fWebcamSource)
        self.leCameraWidth.setObjectName(u"leCameraWidth")
        sizePolicy8.setHeightForWidth(self.leCameraWidth.sizePolicy().hasHeightForWidth())
        self.leCameraWidth.setSizePolicy(sizePolicy8)
        self.leCameraWidth.setMinimumSize(QSize(0, 10))
        self.leCameraWidth.setMaximumSize(QSize(40, 25))
        self.leCameraWidth.setFont(font7)
        self.leCameraWidth.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_11.addWidget(self.leCameraWidth)

        self.label_125 = QLabel(self.fWebcamSource)
        self.label_125.setObjectName(u"label_125")
        self.label_125.setFont(font7)
        self.label_125.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_11.addWidget(self.label_125)

        self.leCameraHeight = QLineEdit(self.fWebcamSource)
        self.leCameraHeight.setObjectName(u"leCameraHeight")
        sizePolicy8.setHeightForWidth(self.leCameraHeight.sizePolicy().hasHeightForWidth())
        self.leCameraHeight.setSizePolicy(sizePolicy8)
        self.leCameraHeight.setMinimumSize(QSize(0, 10))
        self.leCameraHeight.setMaximumSize(QSize(40, 25))
        self.leCameraHeight.setFont(font7)
        self.leCameraHeight.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_11.addWidget(self.leCameraHeight)

        self.horizontalSpacer_45 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_11.addItem(self.horizontalSpacer_45)

        self.pbPlayPauseCamera = QToolButton(self.fWebcamSource)
        self.pbPlayPauseCamera.setObjectName(u"pbPlayPauseCamera")
        self.pbPlayPauseCamera.setEnabled(False)
        sizePolicy.setHeightForWidth(self.pbPlayPauseCamera.sizePolicy().hasHeightForWidth())
        self.pbPlayPauseCamera.setSizePolicy(sizePolicy)
        self.pbPlayPauseCamera.setMinimumSize(QSize(0, 0))
        self.pbPlayPauseCamera.setFont(font7)
        icon22 = QIcon()
        icon22.addFile(u":/icon/icons8-play-48.png", QSize(), QIcon.Normal, QIcon.Off)
        icon22.addFile(u":/icon/icons8-pause-48.png", QSize(), QIcon.Normal, QIcon.On)
        icon22.addFile(u"icon/icons8-play-48.png", QSize(), QIcon.Selected, QIcon.Off)
        self.pbPlayPauseCamera.setIcon(icon22)
        self.pbPlayPauseCamera.setIconSize(QSize(30, 30))
        self.pbPlayPauseCamera.setCheckable(True)
        self.pbPlayPauseCamera.setChecked(False)
        self.pbPlayPauseCamera.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbPlayPauseCamera.setAutoRaise(True)

        self.horizontalLayout_11.addWidget(self.pbPlayPauseCamera)

        self.pbCaptureCamera = QToolButton(self.fWebcamSource)
        self.pbCaptureCamera.setObjectName(u"pbCaptureCamera")
        self.pbCaptureCamera.setEnabled(False)
        self.pbCaptureCamera.setMinimumSize(QSize(0, 0))
        self.pbCaptureCamera.setFont(font7)
        icon23 = QIcon()
        icon23.addFile(u":/icon/icons8-screenshot-40.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCaptureCamera.setIcon(icon23)
        self.pbCaptureCamera.setIconSize(QSize(30, 30))
        self.pbCaptureCamera.setCheckable(False)
        self.pbCaptureCamera.setChecked(False)
        self.pbCaptureCamera.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbCaptureCamera.setAutoRaise(True)

        self.horizontalLayout_11.addWidget(self.pbCaptureCamera)

        self.lbCameraState = QLabel(self.fWebcamSource)
        self.lbCameraState.setObjectName(u"lbCameraState")
        self.lbCameraState.setEnabled(False)
        self.lbCameraState.setMaximumSize(QSize(20, 20))
        self.lbCameraState.setPixmap(QPixmap(u"icon/icons8-connection-status-on-48.png"))
        self.lbCameraState.setScaledContents(True)

        self.horizontalLayout_11.addWidget(self.lbCameraState)


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
        self.pbLoadTestImage.setFont(font7)
        icon24 = QIcon()
        icon24.addFile(u":/icon/icons8_image_30px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLoadTestImage.setIcon(icon24)
        self.pbLoadTestImage.setIconSize(QSize(30, 30))
        self.pbLoadTestImage.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbLoadTestImage.setAutoRaise(True)

        self.horizontalLayout_27.addWidget(self.pbLoadTestImage)

        self.horizontalSpacer_64 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_27.addItem(self.horizontalSpacer_64)


        self.verticalLayout_51.addWidget(self.fImageSource)

        self.fPluginSource = QFrame(self.fImageProvider)
        self.fPluginSource.setObjectName(u"fPluginSource")
        self.fPluginSource.setMinimumSize(QSize(0, 20))
        self.fPluginSource.setMaximumSize(QSize(16777215, 50))
        self.fPluginSource.setStyleSheet(u"QFrame#fPluginSource\n"
"{\n"
"	border: 1px solid rgb(10, 198, 255);\n"
"}")
        self.fPluginSource.setFrameShape(QFrame.StyledPanel)
        self.fPluginSource.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_28 = QHBoxLayout(self.fPluginSource)
        self.horizontalLayout_28.setSpacing(6)
        self.horizontalLayout_28.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_28.setObjectName(u"horizontalLayout_28")
        self.horizontalLayout_28.setContentsMargins(5, 5, 5, 5)
        self.cbExternalImageSource = QCheckBox(self.fPluginSource)
        self.cbExternalImageSource.setObjectName(u"cbExternalImageSource")

        self.horizontalLayout_28.addWidget(self.cbExternalImageSource)

        self.label_177 = QLabel(self.fPluginSource)
        self.label_177.setObjectName(u"label_177")
        self.label_177.setMaximumSize(QSize(100, 16777215))
        self.label_177.setFont(font7)

        self.horizontalLayout_28.addWidget(self.label_177)

        self.comboBox_2 = QComboBox(self.fPluginSource)
        self.comboBox_2.addItem("")
        self.comboBox_2.setObjectName(u"comboBox_2")
        sizePolicy.setHeightForWidth(self.comboBox_2.sizePolicy().hasHeightForWidth())
        self.comboBox_2.setSizePolicy(sizePolicy)
        self.comboBox_2.setMinimumSize(QSize(150, 0))

        self.horizontalLayout_28.addWidget(self.comboBox_2)

        self.label_178 = QLabel(self.fPluginSource)
        self.label_178.setObjectName(u"label_178")
        self.label_178.setFont(font7)
        self.label_178.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_28.addWidget(self.label_178)

        self.leImageWidth = QLineEdit(self.fPluginSource)
        self.leImageWidth.setObjectName(u"leImageWidth")
        sizePolicy8.setHeightForWidth(self.leImageWidth.sizePolicy().hasHeightForWidth())
        self.leImageWidth.setSizePolicy(sizePolicy8)
        self.leImageWidth.setMinimumSize(QSize(0, 10))
        self.leImageWidth.setMaximumSize(QSize(40, 25))
        self.leImageWidth.setFont(font7)
        self.leImageWidth.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_28.addWidget(self.leImageWidth)

        self.label_179 = QLabel(self.fPluginSource)
        self.label_179.setObjectName(u"label_179")
        self.label_179.setFont(font7)
        self.label_179.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.horizontalLayout_28.addWidget(self.label_179)

        self.leImageHeight = QLineEdit(self.fPluginSource)
        self.leImageHeight.setObjectName(u"leImageHeight")
        sizePolicy8.setHeightForWidth(self.leImageHeight.sizePolicy().hasHeightForWidth())
        self.leImageHeight.setSizePolicy(sizePolicy8)
        self.leImageHeight.setMinimumSize(QSize(0, 10))
        self.leImageHeight.setMaximumSize(QSize(40, 25))
        self.leImageHeight.setFont(font7)
        self.leImageHeight.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_28.addWidget(self.leImageHeight)

        self.horizontalSpacer_65 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_28.addItem(self.horizontalSpacer_65)


        self.verticalLayout_51.addWidget(self.fPluginSource)


        self.verticalLayout_39.addWidget(self.fImageProvider)


        self.verticalLayout_32.addWidget(self.gbImageProvider)

        self.gbCameraCalibration = QGroupBox(self.fObjectDetectingTool)
        self.gbCameraCalibration.setObjectName(u"gbCameraCalibration")
        self.gbCameraCalibration.setFont(font5)
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
        self.horizontalSpacer_42 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_27.addItem(self.horizontalSpacer_42, 1, 3, 1, 1)

        self.leChessWidth = QLineEdit(self.fCalibStep1)
        self.leChessWidth.setObjectName(u"leChessWidth")
        sizePolicy4.setHeightForWidth(self.leChessWidth.sizePolicy().hasHeightForWidth())
        self.leChessWidth.setSizePolicy(sizePolicy4)
        self.leChessWidth.setMinimumSize(QSize(20, 0))
        self.leChessWidth.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_27.addWidget(self.leChessWidth, 1, 1, 1, 1)

        self.leChessHeight = QLineEdit(self.fCalibStep1)
        self.leChessHeight.setObjectName(u"leChessHeight")
        sizePolicy8.setHeightForWidth(self.leChessHeight.sizePolicy().hasHeightForWidth())
        self.leChessHeight.setSizePolicy(sizePolicy8)
        self.leChessHeight.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_27.addWidget(self.leChessHeight, 1, 2, 1, 1)

        self.label_109 = QLabel(self.fCalibStep1)
        self.label_109.setObjectName(u"label_109")
        self.label_109.setMinimumSize(QSize(0, 25))

        self.gridLayout_27.addWidget(self.label_109, 0, 1, 1, 2)

        self.pbTransformPerspective = QPushButton(self.fCalibStep1)
        self.pbTransformPerspective.setObjectName(u"pbTransformPerspective")
        self.pbTransformPerspective.setMinimumSize(QSize(0, 45))
        self.pbTransformPerspective.setMaximumSize(QSize(150, 16777215))
        self.pbTransformPerspective.setAutoFillBackground(False)
        self.pbTransformPerspective.setIcon(icon13)
        self.pbTransformPerspective.setIconSize(QSize(30, 30))
        self.pbTransformPerspective.setCheckable(True)
        self.pbTransformPerspective.setChecked(False)
        self.pbTransformPerspective.setAutoDefault(False)
        self.pbTransformPerspective.setFlat(False)

        self.gridLayout_27.addWidget(self.pbTransformPerspective, 3, 0, 1, 2)

        self.label_110 = QLabel(self.fCalibStep1)
        self.label_110.setObjectName(u"label_110")
        sizePolicy.setHeightForWidth(self.label_110.sizePolicy().hasHeightForWidth())
        self.label_110.setSizePolicy(sizePolicy)

        self.gridLayout_27.addWidget(self.label_110, 1, 0, 1, 1)

        self.pbFindChessboard = QPushButton(self.fCalibStep1)
        self.pbFindChessboard.setObjectName(u"pbFindChessboard")
        self.pbFindChessboard.setMinimumSize(QSize(0, 45))
        self.pbFindChessboard.setIcon(icon12)
        self.pbFindChessboard.setIconSize(QSize(32, 32))

        self.gridLayout_27.addWidget(self.pbFindChessboard, 2, 0, 1, 2)


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
        self.pbImageMapping = QPushButton(self.fCalibStep2)
        self.pbImageMapping.setObjectName(u"pbImageMapping")
        self.pbImageMapping.setMinimumSize(QSize(0, 45))
        self.pbImageMapping.setMaximumSize(QSize(200, 16777215))
        self.pbImageMapping.setAutoFillBackground(False)
        icon25 = QIcon()
        icon25.addFile(u":/icon/icons8_grid_3_48px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbImageMapping.setIcon(icon25)
        self.pbImageMapping.setIconSize(QSize(30, 30))
        self.pbImageMapping.setCheckable(True)
        self.pbImageMapping.setChecked(False)
        self.pbImageMapping.setAutoDefault(False)
        self.pbImageMapping.setFlat(False)

        self.gridLayout_26.addWidget(self.pbImageMapping, 8, 0, 1, 3)

        self.label_39 = QLabel(self.fCalibStep2)
        self.label_39.setObjectName(u"label_39")
        self.label_39.setAlignment(Qt.AlignCenter)

        self.gridLayout_26.addWidget(self.label_39, 4, 4, 1, 1)

        self.leRealityPoint2Y = QLineEdit(self.fCalibStep2)
        self.leRealityPoint2Y.setObjectName(u"leRealityPoint2Y")
        sizePolicy.setHeightForWidth(self.leRealityPoint2Y.sizePolicy().hasHeightForWidth())
        self.leRealityPoint2Y.setSizePolicy(sizePolicy)
        self.leRealityPoint2Y.setMinimumSize(QSize(0, 0))
        self.leRealityPoint2Y.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint2Y, 6, 4, 1, 1)

        self.leRealityPoint1Y = QLineEdit(self.fCalibStep2)
        self.leRealityPoint1Y.setObjectName(u"leRealityPoint1Y")
        sizePolicy.setHeightForWidth(self.leRealityPoint1Y.sizePolicy().hasHeightForWidth())
        self.leRealityPoint1Y.setSizePolicy(sizePolicy)
        self.leRealityPoint1Y.setMinimumSize(QSize(0, 0))
        self.leRealityPoint1Y.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint1Y, 5, 4, 1, 1)

        self.label_133 = QLabel(self.fCalibStep2)
        self.label_133.setObjectName(u"label_133")
        self.label_133.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_133, 5, 5, 1, 1)

        self.horizontalSpacer_12 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_26.addItem(self.horizontalSpacer_12, 1, 6, 1, 1)

        self.label_140 = QLabel(self.fCalibStep2)
        self.label_140.setObjectName(u"label_140")
        self.label_140.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_140, 6, 5, 1, 1)

        self.pbObjectOrigin = QPushButton(self.fCalibStep2)
        self.pbObjectOrigin.setObjectName(u"pbObjectOrigin")
        self.pbObjectOrigin.setMinimumSize(QSize(0, 0))
        self.pbObjectOrigin.setMaximumSize(QSize(200, 16777215))
        self.pbObjectOrigin.setIcon(icon15)

        self.gridLayout_26.addWidget(self.pbObjectOrigin, 7, 4, 1, 1)

        self.label_38 = QLabel(self.fCalibStep2)
        self.label_38.setObjectName(u"label_38")
        self.label_38.setMinimumSize(QSize(0, 0))
        font8 = QFont()
        font8.setBold(False)
        font8.setItalic(False)
        font8.setUnderline(False)
        font8.setStrikeOut(False)
        font8.setKerning(True)
        self.label_38.setFont(font8)
        self.label_38.setMouseTracking(True)
        self.label_38.setTextFormat(Qt.AutoText)
        self.label_38.setAlignment(Qt.AlignCenter)

        self.gridLayout_26.addWidget(self.label_38, 4, 2, 1, 1)

        self.leRealityPoint1X = QLineEdit(self.fCalibStep2)
        self.leRealityPoint1X.setObjectName(u"leRealityPoint1X")
        sizePolicy.setHeightForWidth(self.leRealityPoint1X.sizePolicy().hasHeightForWidth())
        self.leRealityPoint1X.setSizePolicy(sizePolicy)
        self.leRealityPoint1X.setMinimumSize(QSize(0, 0))
        self.leRealityPoint1X.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint1X, 5, 2, 1, 1)

        self.label_132 = QLabel(self.fCalibStep2)
        self.label_132.setObjectName(u"label_132")
        self.label_132.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_132, 5, 3, 1, 1)

        self.leRealityPoint2X = QLineEdit(self.fCalibStep2)
        self.leRealityPoint2X.setObjectName(u"leRealityPoint2X")
        sizePolicy.setHeightForWidth(self.leRealityPoint2X.sizePolicy().hasHeightForWidth())
        self.leRealityPoint2X.setSizePolicy(sizePolicy)
        self.leRealityPoint2X.setMinimumSize(QSize(0, 0))
        self.leRealityPoint2X.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint2X, 6, 2, 1, 1)

        self.label_139 = QLabel(self.fCalibStep2)
        self.label_139.setObjectName(u"label_139")
        self.label_139.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_139, 6, 3, 1, 1)

        self.cbMoveOnConveyor1 = QCheckBox(self.fCalibStep2)
        self.cbMoveOnConveyor1.setObjectName(u"cbMoveOnConveyor1")

        self.gridLayout_26.addWidget(self.cbMoveOnConveyor1, 1, 0, 1, 3)

        self.pbCalibPoint1 = QPushButton(self.fCalibStep2)
        self.pbCalibPoint1.setObjectName(u"pbCalibPoint1")
        self.pbCalibPoint1.setFlat(True)

        self.gridLayout_26.addWidget(self.pbCalibPoint1, 5, 1, 1, 1)

        self.pbCalibPoint2 = QPushButton(self.fCalibStep2)
        self.pbCalibPoint2.setObjectName(u"pbCalibPoint2")
        self.pbCalibPoint2.setFlat(True)

        self.gridLayout_26.addWidget(self.pbCalibPoint2, 6, 1, 1, 1)


        self.verticalLayout_52.addWidget(self.fCalibStep2)


        self.verticalLayout_29.addWidget(self.fCameraCalibrationFrame)


        self.verticalLayout_32.addWidget(self.gbCameraCalibration)

        self.gbCameraObject = QGroupBox(self.fObjectDetectingTool)
        self.gbCameraObject.setObjectName(u"gbCameraObject")
        self.gbCameraObject.setFont(font5)
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

        self.cbObjectType = QComboBox(self.fVisionObjectFrame)
        self.cbObjectType.addItem("")
        self.cbObjectType.setObjectName(u"cbObjectType")
        self.cbObjectType.setEnabled(True)
        self.cbObjectType.setMinimumSize(QSize(0, 30))

        self.horizontalLayout_29.addWidget(self.cbObjectType)

        self.pushButton = QPushButton(self.fVisionObjectFrame)
        self.pushButton.setObjectName(u"pushButton")
        sizePolicy4.setHeightForWidth(self.pushButton.sizePolicy().hasHeightForWidth())
        self.pushButton.setSizePolicy(sizePolicy4)
        self.pushButton.setMaximumSize(QSize(30, 16777215))

        self.horizontalLayout_29.addWidget(self.pushButton)

        self.pushButton_2 = QPushButton(self.fVisionObjectFrame)
        self.pushButton_2.setObjectName(u"pushButton_2")
        sizePolicy4.setHeightForWidth(self.pushButton_2.sizePolicy().hasHeightForWidth())
        self.pushButton_2.setSizePolicy(sizePolicy4)
        self.pushButton_2.setMaximumSize(QSize(30, 30))

        self.horizontalLayout_29.addWidget(self.pushButton_2)


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
        self.label_172 = QLabel(self.fBlobPanel)
        self.label_172.setObjectName(u"label_172")
        self.label_172.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_172, 2, 4, 1, 1)

        self.leMaxWRec = QLineEdit(self.fBlobPanel)
        self.leMaxWRec.setObjectName(u"leMaxWRec")
        sizePolicy4.setHeightForWidth(self.leMaxWRec.sizePolicy().hasHeightForWidth())
        self.leMaxWRec.setSizePolicy(sizePolicy4)
        self.leMaxWRec.setMinimumSize(QSize(0, 20))
        self.leMaxWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMaxWRec, 2, 7, 1, 1)

        self.leMaxLRec = QLineEdit(self.fBlobPanel)
        self.leMaxLRec.setObjectName(u"leMaxLRec")
        sizePolicy4.setHeightForWidth(self.leMaxLRec.sizePolicy().hasHeightForWidth())
        self.leMaxLRec.setSizePolicy(sizePolicy4)
        self.leMaxLRec.setMinimumSize(QSize(0, 20))
        self.leMaxLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMaxLRec, 3, 7, 1, 1)

        self.label_55 = QLabel(self.fBlobPanel)
        self.label_55.setObjectName(u"label_55")

        self.gridLayout_14.addWidget(self.label_55, 3, 2, 1, 1)

        self.leWRec = QLineEdit(self.fBlobPanel)
        self.leWRec.setObjectName(u"leWRec")
        sizePolicy4.setHeightForWidth(self.leWRec.sizePolicy().hasHeightForWidth())
        self.leWRec.setSizePolicy(sizePolicy4)
        self.leWRec.setMinimumSize(QSize(0, 30))
        self.leWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leWRec, 2, 1, 1, 1)

        self.pbObjectRect = QToolButton(self.fBlobPanel)
        self.pbObjectRect.setObjectName(u"pbObjectRect")
        self.pbObjectRect.setMinimumSize(QSize(0, 30))
        self.pbObjectRect.setStyleSheet(u"")
        self.pbObjectRect.setIcon(icon17)
        self.pbObjectRect.setIconSize(QSize(30, 30))
        self.pbObjectRect.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbObjectRect.setAutoRaise(True)

        self.gridLayout_14.addWidget(self.pbObjectRect, 5, 1, 1, 2)

        self.label_56 = QLabel(self.fBlobPanel)
        self.label_56.setObjectName(u"label_56")

        self.gridLayout_14.addWidget(self.label_56, 4, 2, 1, 1)

        self.label_44 = QLabel(self.fBlobPanel)
        self.label_44.setObjectName(u"label_44")

        self.gridLayout_14.addWidget(self.label_44, 4, 0, 1, 1)

        self.leMinLRec = QLineEdit(self.fBlobPanel)
        self.leMinLRec.setObjectName(u"leMinLRec")
        sizePolicy4.setHeightForWidth(self.leMinLRec.sizePolicy().hasHeightForWidth())
        self.leMinLRec.setSizePolicy(sizePolicy4)
        self.leMinLRec.setMinimumSize(QSize(0, 20))
        self.leMinLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMinLRec, 3, 5, 1, 1)

        self.leLRec = QLineEdit(self.fBlobPanel)
        self.leLRec.setObjectName(u"leLRec")
        sizePolicy4.setHeightForWidth(self.leLRec.sizePolicy().hasHeightForWidth())
        self.leLRec.setSizePolicy(sizePolicy4)
        self.leLRec.setMinimumSize(QSize(0, 30))
        self.leLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leLRec, 3, 1, 1, 1)

        self.pbFilter = QPushButton(self.fBlobPanel)
        self.pbFilter.setObjectName(u"pbFilter")
        self.pbFilter.setMinimumSize(QSize(0, 30))
        self.pbFilter.setMaximumSize(QSize(150, 16777215))
        self.pbFilter.setIcon(icon18)

        self.gridLayout_14.addWidget(self.pbFilter, 0, 0, 1, 2)

        self.label_43 = QLabel(self.fBlobPanel)
        self.label_43.setObjectName(u"label_43")

        self.gridLayout_14.addWidget(self.label_43, 3, 0, 1, 1)

        self.label_173 = QLabel(self.fBlobPanel)
        self.label_173.setObjectName(u"label_173")
        self.label_173.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_173, 2, 6, 1, 1)

        self.leHRec = QLineEdit(self.fBlobPanel)
        self.leHRec.setObjectName(u"leHRec")
        sizePolicy4.setHeightForWidth(self.leHRec.sizePolicy().hasHeightForWidth())
        self.leHRec.setSizePolicy(sizePolicy4)
        self.leHRec.setMinimumSize(QSize(0, 30))
        self.leHRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leHRec, 4, 1, 1, 1)

        self.horizontalSpacer_66 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_14.addItem(self.horizontalSpacer_66, 2, 8, 1, 1)

        self.label_54 = QLabel(self.fBlobPanel)
        self.label_54.setObjectName(u"label_54")

        self.gridLayout_14.addWidget(self.label_54, 2, 2, 1, 1)

        self.label_174 = QLabel(self.fBlobPanel)
        self.label_174.setObjectName(u"label_174")
        self.label_174.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_174, 3, 4, 1, 1)

        self.label_42 = QLabel(self.fBlobPanel)
        self.label_42.setObjectName(u"label_42")

        self.gridLayout_14.addWidget(self.label_42, 2, 0, 1, 1)

        self.leMinWRec = QLineEdit(self.fBlobPanel)
        self.leMinWRec.setObjectName(u"leMinWRec")
        sizePolicy4.setHeightForWidth(self.leMinWRec.sizePolicy().hasHeightForWidth())
        self.leMinWRec.setSizePolicy(sizePolicy4)
        self.leMinWRec.setMinimumSize(QSize(0, 20))
        self.leMinWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMinWRec, 2, 5, 1, 1)

        self.lbTrackingObject = QLabel(self.fBlobPanel)
        self.lbTrackingObject.setObjectName(u"lbTrackingObject")
        self.lbTrackingObject.setMinimumSize(QSize(100, 100))
        self.lbTrackingObject.setMaximumSize(QSize(100, 100))
        self.lbTrackingObject.setStyleSheet(u"background-color:rgb(230, 230, 230)")
        self.lbTrackingObject.setMargin(0)

        self.gridLayout_14.addWidget(self.lbTrackingObject, 5, 0, 1, 1)

        self.label_175 = QLabel(self.fBlobPanel)
        self.label_175.setObjectName(u"label_175")
        self.label_175.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_175, 3, 6, 1, 1)


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
        sizePolicy4.setHeightForWidth(self.pbRunExternalScript.sizePolicy().hasHeightForWidth())
        self.pbRunExternalScript.setSizePolicy(sizePolicy4)
        self.pbRunExternalScript.setMaximumSize(QSize(30, 16777215))
        icon26 = QIcon()
        icon26.addFile(u":/icon/icons8_play_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon26.addFile(u":/icon/Pause_96px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbRunExternalScript.setIcon(icon26)
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
        sizePolicy4.setHeightForWidth(self.pbExternalScriptOpen.sizePolicy().hasHeightForWidth())
        self.pbExternalScriptOpen.setSizePolicy(sizePolicy4)
        self.pbExternalScriptOpen.setMaximumSize(QSize(30, 16777215))
        self.pbExternalScriptOpen.setIcon(icon10)

        self.gridLayout_28.addWidget(self.pbExternalScriptOpen, 0, 2, 1, 1)

        self.label_184 = QLabel(self.fExternalScriptPanel)
        self.label_184.setObjectName(u"label_184")

        self.gridLayout_28.addWidget(self.label_184, 3, 0, 1, 1)

        self.label_145 = QLabel(self.fExternalScriptPanel)
        self.label_145.setObjectName(u"label_145")

        self.gridLayout_28.addWidget(self.label_145, 0, 0, 1, 1)

        self.pbExternalScriptHelp = QPushButton(self.fExternalScriptPanel)
        self.pbExternalScriptHelp.setObjectName(u"pbExternalScriptHelp")
        sizePolicy4.setHeightForWidth(self.pbExternalScriptHelp.sizePolicy().hasHeightForWidth())
        self.pbExternalScriptHelp.setSizePolicy(sizePolicy4)
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
        sizePolicy8.setHeightForWidth(self.lePythonUrl.sizePolicy().hasHeightForWidth())
        self.lePythonUrl.setSizePolicy(sizePolicy8)
        self.lePythonUrl.setMinimumSize(QSize(0, 30))
        self.lePythonUrl.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_28.addWidget(self.lePythonUrl, 0, 1, 1, 1)

        self.pushButton_3 = QPushButton(self.fExternalScriptPanel)
        self.pushButton_3.setObjectName(u"pushButton_3")

        self.gridLayout_28.addWidget(self.pushButton_3, 5, 0, 1, 1)


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
        sizePolicy4.setHeightForWidth(self.leCenterThreshold.sizePolicy().hasHeightForWidth())
        self.leCenterThreshold.setSizePolicy(sizePolicy4)
        self.leCenterThreshold.setMinimumSize(QSize(0, 30))
        self.leCenterThreshold.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_29.addWidget(self.leCenterThreshold, 3, 1, 1, 2)

        self.horizontalSpacer_8 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_29.addItem(self.horizontalSpacer_8, 2, 4, 1, 1)

        self.leEdgeThreshold = QLineEdit(self.fCirclePanel)
        self.leEdgeThreshold.setObjectName(u"leEdgeThreshold")
        sizePolicy4.setHeightForWidth(self.leEdgeThreshold.sizePolicy().hasHeightForWidth())
        self.leEdgeThreshold.setSizePolicy(sizePolicy4)
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
        sizePolicy4.setHeightForWidth(self.leMaxRadius.sizePolicy().hasHeightForWidth())
        self.leMaxRadius.setSizePolicy(sizePolicy4)
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
        sizePolicy4.setHeightForWidth(self.leMinRadius.sizePolicy().hasHeightForWidth())
        self.leMinRadius.setSizePolicy(sizePolicy4)
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
        self.gbCameraVariable.setFont(font5)
        self.gbCameraVariable.setStyleSheet(u"")
        self.gbCameraVariable.setFlat(False)
        self.gbCameraVariable.setCheckable(True)
        self.verticalLayout_34 = QVBoxLayout(self.gbCameraVariable)
        self.verticalLayout_34.setSpacing(6)
        self.verticalLayout_34.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_34.setObjectName(u"verticalLayout_34")
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
        self.pbViewDataObjects.setIcon(icon19)

        self.horizontalLayout_25.addWidget(self.pbViewDataObjects)

        self.pbClearDetectObjects = QPushButton(self.fVisionVariableFrame)
        self.pbClearDetectObjects.setObjectName(u"pbClearDetectObjects")
        self.pbClearDetectObjects.setMinimumSize(QSize(150, 30))
        self.pbClearDetectObjects.setMaximumSize(QSize(200, 16777215))
        self.pbClearDetectObjects.setIcon(icon20)

        self.horizontalLayout_25.addWidget(self.pbClearDetectObjects)

        self.horizontalSpacer_9 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_25.addItem(self.horizontalSpacer_9)


        self.verticalLayout_35.addLayout(self.horizontalLayout_25)

        self.gridLayout_15 = QGridLayout()
        self.gridLayout_15.setSpacing(6)
        self.gridLayout_15.setObjectName(u"gridLayout_15")
        self.label_50 = QLabel(self.fVisionVariableFrame)
        self.label_50.setObjectName(u"label_50")
        self.label_50.setFont(font4)

        self.gridLayout_15.addWidget(self.label_50, 2, 0, 1, 1)

        self.lbVisibleObjectNumber = QLabel(self.fVisionVariableFrame)
        self.lbVisibleObjectNumber.setObjectName(u"lbVisibleObjectNumber")
        self.lbVisibleObjectNumber.setFont(font4)

        self.gridLayout_15.addWidget(self.lbVisibleObjectNumber, 2, 1, 1, 1)

        self.lbTrackingObjectNumber = QLabel(self.fVisionVariableFrame)
        self.lbTrackingObjectNumber.setObjectName(u"lbTrackingObjectNumber")
        self.lbTrackingObjectNumber.setFont(font4)

        self.gridLayout_15.addWidget(self.lbTrackingObjectNumber, 1, 1, 1, 1)

        self.horizontalSpacer_7 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_15.addItem(self.horizontalSpacer_7, 1, 2, 1, 1)

        self.label_48 = QLabel(self.fVisionVariableFrame)
        self.label_48.setObjectName(u"label_48")
        self.label_48.setFont(font4)

        self.gridLayout_15.addWidget(self.label_48, 1, 0, 1, 1)


        self.verticalLayout_35.addLayout(self.gridLayout_15)

        self.frame_9 = QFrame(self.fVisionVariableFrame)
        self.frame_9.setObjectName(u"frame_9")
        self.frame_9.setMinimumSize(QSize(0, 50))
        self.frame_9.setFrameShape(QFrame.StyledPanel)
        self.frame_9.setFrameShadow(QFrame.Raised)
        self.label_155 = QLabel(self.frame_9)
        self.label_155.setObjectName(u"label_155")
        self.label_155.setGeometry(QRect(0, 0, 50, 50))
        self.label_155.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_156 = QLabel(self.frame_9)
        self.label_156.setObjectName(u"label_156")
        self.label_156.setGeometry(QRect(55, 0, 50, 50))
        self.label_156.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_157 = QLabel(self.frame_9)
        self.label_157.setObjectName(u"label_157")
        self.label_157.setGeometry(QRect(110, 0, 50, 50))
        self.label_157.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_158 = QLabel(self.frame_9)
        self.label_158.setObjectName(u"label_158")
        self.label_158.setGeometry(QRect(165, 0, 50, 50))
        self.label_158.setStyleSheet(u"background-color: rgb(255, 255, 255);")
        self.label_159 = QLabel(self.frame_9)
        self.label_159.setObjectName(u"label_159")
        self.label_159.setGeometry(QRect(220, 0, 50, 50))
        self.label_159.setStyleSheet(u"background-color: rgb(255, 255, 255);")

        self.verticalLayout_35.addWidget(self.frame_9)


        self.verticalLayout_34.addWidget(self.fVisionVariableFrame)


        self.verticalLayout_32.addWidget(self.gbCameraVariable)

        self.gbConveyorForTracking = QGroupBox(self.fObjectDetectingTool)
        self.gbConveyorForTracking.setObjectName(u"gbConveyorForTracking")
        self.gbConveyorForTracking.setFont(font5)
        self.gbConveyorForTracking.setCheckable(True)
        self.verticalLayout_41 = QVBoxLayout(self.gbConveyorForTracking)
        self.verticalLayout_41.setSpacing(6)
        self.verticalLayout_41.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_41.setObjectName(u"verticalLayout_41")
        self.fTracking = QFrame(self.gbConveyorForTracking)
        self.fTracking.setObjectName(u"fTracking")
        self.fTracking.setMinimumSize(QSize(0, 200))
        self.fTracking.setFrameShape(QFrame.StyledPanel)
        self.fTracking.setFrameShadow(QFrame.Raised)
        self.verticalLayout_33 = QVBoxLayout(self.fTracking)
        self.verticalLayout_33.setSpacing(5)
        self.verticalLayout_33.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_33.setObjectName(u"verticalLayout_33")
        self.verticalLayout_33.setContentsMargins(0, 0, 0, 0)
        self.label_150 = QLabel(self.fTracking)
        self.label_150.setObjectName(u"label_150")
        self.label_150.setFont(font5)

        self.verticalLayout_33.addWidget(self.label_150)

        self.gridFrame = QFrame(self.fTracking)
        self.gridFrame.setObjectName(u"gridFrame")
        self.gridFrame.setMinimumSize(QSize(0, 0))
        self.gridLayout_32 = QGridLayout(self.gridFrame)
        self.gridLayout_32.setSpacing(6)
        self.gridLayout_32.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_32.setObjectName(u"gridLayout_32")
        self.horizontalSpacer_62 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_32.addItem(self.horizontalSpacer_62, 0, 3, 1, 1)

        self.label_152 = QLabel(self.gridFrame)
        self.label_152.setObjectName(u"label_152")
        self.label_152.setMaximumSize(QSize(60, 16777215))
        font9 = QFont()
        font9.setPointSize(8)
        font9.setBold(False)
        font9.setItalic(True)
        font9.setKerning(True)
        self.label_152.setFont(font9)

        self.gridLayout_32.addWidget(self.label_152, 0, 2, 1, 1)

        self.label_151 = QLabel(self.gridFrame)
        self.label_151.setObjectName(u"label_151")

        self.gridLayout_32.addWidget(self.label_151, 0, 0, 1, 1)

        self.leTrackingError = QLineEdit(self.gridFrame)
        self.leTrackingError.setObjectName(u"leTrackingError")
        self.leTrackingError.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_32.addWidget(self.leTrackingError, 0, 1, 1, 1)


        self.verticalLayout_33.addWidget(self.gridFrame)

        self.label_127 = QLabel(self.fTracking)
        self.label_127.setObjectName(u"label_127")
        self.label_127.setFont(font5)

        self.verticalLayout_33.addWidget(self.label_127)

        self.gridLayout_16 = QGridLayout()
        self.gridLayout_16.setSpacing(6)
        self.gridLayout_16.setObjectName(u"gridLayout_16")
        self.leConvenyorSpeed = QLineEdit(self.fTracking)
        self.leConvenyorSpeed.setObjectName(u"leConvenyorSpeed")
        self.leConvenyorSpeed.setMinimumSize(QSize(0, 0))
        self.leConvenyorSpeed.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_16.addWidget(self.leConvenyorSpeed, 6, 1, 1, 1)

        self.horizontalSpacer_11 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_16.addItem(self.horizontalSpacer_11, 6, 4, 1, 1)

        self.pbReadProximitySensor = QPushButton(self.fTracking)
        self.pbReadProximitySensor.setObjectName(u"pbReadProximitySensor")
        sizePolicy.setHeightForWidth(self.pbReadProximitySensor.sizePolicy().hasHeightForWidth())
        self.pbReadProximitySensor.setSizePolicy(sizePolicy)
        self.pbReadProximitySensor.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_16.addWidget(self.pbReadProximitySensor, 17, 4, 1, 1)

        self.pbBackwardConveyor = QPushButton(self.fTracking)
        self.pbBackwardConveyor.setObjectName(u"pbBackwardConveyor")
        sizePolicy.setHeightForWidth(self.pbBackwardConveyor.sizePolicy().hasHeightForWidth())
        self.pbBackwardConveyor.setSizePolicy(sizePolicy)
        self.pbBackwardConveyor.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_16.addWidget(self.pbBackwardConveyor, 14, 0, 1, 1)

        self.leMovingDistanceConveyorControl = QLineEdit(self.fTracking)
        self.leMovingDistanceConveyorControl.setObjectName(u"leMovingDistanceConveyorControl")
        self.leMovingDistanceConveyorControl.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_16.addWidget(self.leMovingDistanceConveyorControl, 11, 1, 1, 1)

        self.pbResetEncoderPosition = QPushButton(self.fTracking)
        self.pbResetEncoderPosition.setObjectName(u"pbResetEncoderPosition")
        sizePolicy.setHeightForWidth(self.pbResetEncoderPosition.sizePolicy().hasHeightForWidth())
        self.pbResetEncoderPosition.setSizePolicy(sizePolicy)
        self.pbResetEncoderPosition.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_16.addWidget(self.pbResetEncoderPosition, 4, 4, 1, 1)

        self.label_189 = QLabel(self.fTracking)
        self.label_189.setObjectName(u"label_189")
        font10 = QFont()
        font10.setBold(True)
        self.label_189.setFont(font10)

        self.gridLayout_16.addWidget(self.label_189, 16, 0, 1, 1)

        self.leForwardConveyorGcode = QLineEdit(self.fTracking)
        self.leForwardConveyorGcode.setObjectName(u"leForwardConveyorGcode")
        self.leForwardConveyorGcode.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_16.addWidget(self.leForwardConveyorGcode, 13, 1, 1, 2)

        self.leTurnOffConveyorGcode = QLineEdit(self.fTracking)
        self.leTurnOffConveyorGcode.setObjectName(u"leTurnOffConveyorGcode")
        self.leTurnOffConveyorGcode.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_16.addWidget(self.leTurnOffConveyorGcode, 15, 1, 1, 2)

        self.rbEncoderEnable = QRadioButton(self.fTracking)
        self.rbEncoderEnable.setObjectName(u"rbEncoderEnable")

        self.gridLayout_16.addWidget(self.rbEncoderEnable, 2, 1, 1, 1)

        self.label_148 = QLabel(self.fTracking)
        self.label_148.setObjectName(u"label_148")
        font11 = QFont()
        font11.setPointSize(8)
        font11.setBold(True)
        font11.setKerning(True)
        self.label_148.setFont(font11)

        self.gridLayout_16.addWidget(self.label_148, 8, 0, 1, 1)

        self.label_191 = QLabel(self.fTracking)
        self.label_191.setObjectName(u"label_191")
        self.label_191.setFont(font4)

        self.gridLayout_16.addWidget(self.label_191, 17, 0, 1, 1)

        self.leBackwardConveyorGcode = QLineEdit(self.fTracking)
        self.leBackwardConveyorGcode.setObjectName(u"leBackwardConveyorGcode")
        self.leBackwardConveyorGcode.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_16.addWidget(self.leBackwardConveyorGcode, 14, 1, 1, 2)

        self.label_45 = QLabel(self.fTracking)
        self.label_45.setObjectName(u"label_45")
        self.label_45.setMinimumSize(QSize(100, 0))
        self.label_45.setMaximumSize(QSize(150, 16777215))
        self.label_45.setFont(font4)

        self.gridLayout_16.addWidget(self.label_45, 6, 0, 1, 1)

        self.label_163 = QLabel(self.fTracking)
        self.label_163.setObjectName(u"label_163")
        self.label_163.setFont(font4)

        self.gridLayout_16.addWidget(self.label_163, 12, 1, 1, 1)

        self.lbProximitySensorValue = QLabel(self.fTracking)
        self.lbProximitySensorValue.setObjectName(u"lbProximitySensorValue")
        self.lbProximitySensorValue.setFont(font4)

        self.gridLayout_16.addWidget(self.lbProximitySensorValue, 17, 1, 1, 1)

        self.leEncoderCom = QLabel(self.fTracking)
        self.leEncoderCom.setObjectName(u"leEncoderCom")

        self.gridLayout_16.addWidget(self.leEncoderCom, 3, 1, 1, 1)

        self.pbTurnOffConveyor = QPushButton(self.fTracking)
        self.pbTurnOffConveyor.setObjectName(u"pbTurnOffConveyor")
        sizePolicy.setHeightForWidth(self.pbTurnOffConveyor.sizePolicy().hasHeightForWidth())
        self.pbTurnOffConveyor.setSizePolicy(sizePolicy)
        self.pbTurnOffConveyor.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_16.addWidget(self.pbTurnOffConveyor, 15, 0, 1, 1)

        self.label_121 = QLabel(self.fTracking)
        self.label_121.setObjectName(u"label_121")
        self.label_121.setMaximumSize(QSize(60, 16777215))
        self.label_121.setFont(font9)

        self.gridLayout_16.addWidget(self.label_121, 5, 2, 1, 1)

        self.label_162 = QLabel(self.fTracking)
        self.label_162.setObjectName(u"label_162")
        self.label_162.setMaximumSize(QSize(60, 16777215))
        self.label_162.setFont(font9)

        self.gridLayout_16.addWidget(self.label_162, 11, 2, 1, 1)

        self.leEncoderVelocity = QLineEdit(self.fTracking)
        self.leEncoderVelocity.setObjectName(u"leEncoderVelocity")
        self.leEncoderVelocity.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_16.addWidget(self.leEncoderVelocity, 5, 1, 1, 1)

        self.leConveyorDeviationAngle = QLineEdit(self.fTracking)
        self.leConveyorDeviationAngle.setObjectName(u"leConveyorDeviationAngle")
        self.leConveyorDeviationAngle.setMinimumSize(QSize(0, 0))
        self.leConveyorDeviationAngle.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_16.addWidget(self.leConveyorDeviationAngle, 8, 1, 1, 1)

        self.pbConnectEncdoer = QPushButton(self.fTracking)
        self.pbConnectEncdoer.setObjectName(u"pbConnectEncdoer")

        self.gridLayout_16.addWidget(self.pbConnectEncdoer, 3, 0, 1, 1)

        self.label_161 = QLabel(self.fTracking)
        self.label_161.setObjectName(u"label_161")
        self.label_161.setFont(font4)

        self.gridLayout_16.addWidget(self.label_161, 11, 0, 1, 1)

        self.cbEncoderPositionInverse = QCheckBox(self.fTracking)
        self.cbEncoderPositionInverse.setObjectName(u"cbEncoderPositionInverse")

        self.gridLayout_16.addWidget(self.cbEncoderPositionInverse, 4, 3, 1, 1)

        self.label_49 = QLabel(self.fTracking)
        self.label_49.setObjectName(u"label_49")
        self.label_49.setMaximumSize(QSize(60, 16777215))
        self.label_49.setFont(font9)

        self.gridLayout_16.addWidget(self.label_49, 6, 2, 1, 1)

        self.label_160 = QLabel(self.fTracking)
        self.label_160.setObjectName(u"label_160")
        self.label_160.setFont(font10)

        self.gridLayout_16.addWidget(self.label_160, 10, 0, 1, 1)

        self.label_119 = QLabel(self.fTracking)
        self.label_119.setObjectName(u"label_119")
        self.label_119.setMaximumSize(QSize(60, 16777215))
        self.label_119.setFont(font9)

        self.gridLayout_16.addWidget(self.label_119, 4, 2, 1, 1)

        self.rbVirtualEncoderEnable = QRadioButton(self.fTracking)
        self.rbVirtualEncoderEnable.setObjectName(u"rbVirtualEncoderEnable")
        self.rbVirtualEncoderEnable.setChecked(True)

        self.gridLayout_16.addWidget(self.rbVirtualEncoderEnable, 2, 3, 1, 2)

        self.label_118 = QLabel(self.fTracking)
        self.label_118.setObjectName(u"label_118")

        self.gridLayout_16.addWidget(self.label_118, 4, 0, 1, 1)

        self.pbForwardConveyor = QPushButton(self.fTracking)
        self.pbForwardConveyor.setObjectName(u"pbForwardConveyor")
        sizePolicy.setHeightForWidth(self.pbForwardConveyor.sizePolicy().hasHeightForWidth())
        self.pbForwardConveyor.setSizePolicy(sizePolicy)
        self.pbForwardConveyor.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_16.addWidget(self.pbForwardConveyor, 13, 0, 1, 1)

        self.cbConveyorDirectionControl = QComboBox(self.fTracking)
        self.cbConveyorDirectionControl.addItem("")
        self.cbConveyorDirectionControl.addItem("")
        self.cbConveyorDirectionControl.setObjectName(u"cbConveyorDirectionControl")
        self.cbConveyorDirectionControl.setMinimumSize(QSize(0, 0))
        self.cbConveyorDirectionControl.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_16.addWidget(self.cbConveyorDirectionControl, 11, 3, 1, 1)

        self.label_120 = QLabel(self.fTracking)
        self.label_120.setObjectName(u"label_120")

        self.gridLayout_16.addWidget(self.label_120, 5, 0, 1, 1)

        self.cbAutoReadProximitySensor = QCheckBox(self.fTracking)
        self.cbAutoReadProximitySensor.setObjectName(u"cbAutoReadProximitySensor")

        self.gridLayout_16.addWidget(self.cbAutoReadProximitySensor, 17, 3, 1, 1)

        self.leEncoderPosition = QLineEdit(self.fTracking)
        self.leEncoderPosition.setObjectName(u"leEncoderPosition")
        self.leEncoderPosition.setMaximumSize(QSize(100, 16777215))

        self.gridLayout_16.addWidget(self.leEncoderPosition, 4, 1, 1, 1)

        self.frame_11 = QFrame(self.fTracking)
        self.frame_11.setObjectName(u"frame_11")
        self.frame_11.setMinimumSize(QSize(0, 20))
        self.frame_11.setFrameShape(QFrame.StyledPanel)
        self.frame_11.setFrameShadow(QFrame.Raised)
        self.gridLayout_37 = QGridLayout(self.frame_11)
        self.gridLayout_37.setSpacing(6)
        self.gridLayout_37.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_37.setObjectName(u"gridLayout_37")
        self.gridLayout_37.setHorizontalSpacing(0)
        self.gridLayout_37.setVerticalSpacing(5)
        self.gridLayout_37.setContentsMargins(0, 0, 0, 0)
        self.label_170 = QLabel(self.frame_11)
        self.label_170.setObjectName(u"label_170")
        self.label_170.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_37.addWidget(self.label_170, 0, 2, 1, 1)

        self.leConveyorPoint2X = QLineEdit(self.frame_11)
        self.leConveyorPoint2X.setObjectName(u"leConveyorPoint2X")
        sizePolicy9 = QSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred)
        sizePolicy9.setHorizontalStretch(0)
        sizePolicy9.setVerticalStretch(0)
        sizePolicy9.setHeightForWidth(self.leConveyorPoint2X.sizePolicy().hasHeightForWidth())
        self.leConveyorPoint2X.setSizePolicy(sizePolicy9)
        self.leConveyorPoint2X.setMinimumSize(QSize(0, 0))

        self.gridLayout_37.addWidget(self.leConveyorPoint2X, 2, 1, 1, 1)

        self.pbCalibConveyorAngle = QPushButton(self.frame_11)
        self.pbCalibConveyorAngle.setObjectName(u"pbCalibConveyorAngle")
        sizePolicy9.setHeightForWidth(self.pbCalibConveyorAngle.sizePolicy().hasHeightForWidth())
        self.pbCalibConveyorAngle.setSizePolicy(sizePolicy9)
        self.pbCalibConveyorAngle.setMinimumSize(QSize(0, 0))
        self.pbCalibConveyorAngle.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_37.addWidget(self.pbCalibConveyorAngle, 4, 1, 1, 1)

        self.leConveyorPoint1X = QLineEdit(self.frame_11)
        self.leConveyorPoint1X.setObjectName(u"leConveyorPoint1X")
        sizePolicy9.setHeightForWidth(self.leConveyorPoint1X.sizePolicy().hasHeightForWidth())
        self.leConveyorPoint1X.setSizePolicy(sizePolicy9)
        self.leConveyorPoint1X.setMinimumSize(QSize(0, 0))

        self.gridLayout_37.addWidget(self.leConveyorPoint1X, 0, 1, 1, 1)

        self.label_197 = QLabel(self.frame_11)
        self.label_197.setObjectName(u"label_197")
        self.label_197.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_37.addWidget(self.label_197, 1, 2, 1, 1)

        self.label_199 = QLabel(self.frame_11)
        self.label_199.setObjectName(u"label_199")
        self.label_199.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_37.addWidget(self.label_199, 3, 2, 1, 1)

        self.leConveyorPoint1Y = QLineEdit(self.frame_11)
        self.leConveyorPoint1Y.setObjectName(u"leConveyorPoint1Y")
        sizePolicy9.setHeightForWidth(self.leConveyorPoint1Y.sizePolicy().hasHeightForWidth())
        self.leConveyorPoint1Y.setSizePolicy(sizePolicy9)
        self.leConveyorPoint1Y.setMinimumSize(QSize(0, 0))

        self.gridLayout_37.addWidget(self.leConveyorPoint1Y, 1, 1, 1, 1)

        self.label_198 = QLabel(self.frame_11)
        self.label_198.setObjectName(u"label_198")
        self.label_198.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_37.addWidget(self.label_198, 2, 2, 1, 1)

        self.leConveyorPoint2Y = QLineEdit(self.frame_11)
        self.leConveyorPoint2Y.setObjectName(u"leConveyorPoint2Y")
        sizePolicy9.setHeightForWidth(self.leConveyorPoint2Y.sizePolicy().hasHeightForWidth())
        self.leConveyorPoint2Y.setSizePolicy(sizePolicy9)
        self.leConveyorPoint2Y.setMinimumSize(QSize(0, 0))

        self.gridLayout_37.addWidget(self.leConveyorPoint2Y, 3, 1, 1, 1)

        self.pbGetConveyorPoint1X = QPushButton(self.frame_11)
        self.pbGetConveyorPoint1X.setObjectName(u"pbGetConveyorPoint1X")
        sizePolicy4.setHeightForWidth(self.pbGetConveyorPoint1X.sizePolicy().hasHeightForWidth())
        self.pbGetConveyorPoint1X.setSizePolicy(sizePolicy4)
        self.pbGetConveyorPoint1X.setMaximumSize(QSize(50, 16777215))
        self.pbGetConveyorPoint1X.setFlat(True)

        self.gridLayout_37.addWidget(self.pbGetConveyorPoint1X, 0, 0, 1, 1)

        self.pbGetConveyorPoint1Y = QPushButton(self.frame_11)
        self.pbGetConveyorPoint1Y.setObjectName(u"pbGetConveyorPoint1Y")
        sizePolicy4.setHeightForWidth(self.pbGetConveyorPoint1Y.sizePolicy().hasHeightForWidth())
        self.pbGetConveyorPoint1Y.setSizePolicy(sizePolicy4)
        self.pbGetConveyorPoint1Y.setMaximumSize(QSize(50, 16777215))
        self.pbGetConveyorPoint1Y.setFlat(True)

        self.gridLayout_37.addWidget(self.pbGetConveyorPoint1Y, 1, 0, 1, 1)

        self.pbGetConveyorPoint2X = QPushButton(self.frame_11)
        self.pbGetConveyorPoint2X.setObjectName(u"pbGetConveyorPoint2X")
        sizePolicy4.setHeightForWidth(self.pbGetConveyorPoint2X.sizePolicy().hasHeightForWidth())
        self.pbGetConveyorPoint2X.setSizePolicy(sizePolicy4)
        self.pbGetConveyorPoint2X.setMaximumSize(QSize(50, 16777215))
        self.pbGetConveyorPoint2X.setFlat(True)

        self.gridLayout_37.addWidget(self.pbGetConveyorPoint2X, 2, 0, 1, 1)

        self.pbGetConveyorPoint2Y = QPushButton(self.frame_11)
        self.pbGetConveyorPoint2Y.setObjectName(u"pbGetConveyorPoint2Y")
        sizePolicy4.setHeightForWidth(self.pbGetConveyorPoint2Y.sizePolicy().hasHeightForWidth())
        self.pbGetConveyorPoint2Y.setSizePolicy(sizePolicy4)
        self.pbGetConveyorPoint2Y.setMaximumSize(QSize(50, 16777215))
        self.pbGetConveyorPoint2Y.setFlat(True)

        self.gridLayout_37.addWidget(self.pbGetConveyorPoint2Y, 3, 0, 1, 1)


        self.gridLayout_16.addWidget(self.frame_11, 8, 4, 1, 1)

        self.label_196 = QLabel(self.fTracking)
        self.label_196.setObjectName(u"label_196")
        self.label_196.setFont(font4)

        self.gridLayout_16.addWidget(self.label_196, 8, 3, 1, 1)

        self.label_149 = QLabel(self.fTracking)
        self.label_149.setObjectName(u"label_149")
        self.label_149.setMaximumSize(QSize(60, 16777215))
        self.label_149.setFont(font9)

        self.gridLayout_16.addWidget(self.label_149, 8, 2, 1, 1)

        self.frame_12 = QFrame(self.fTracking)
        self.frame_12.setObjectName(u"frame_12")
        self.frame_12.setMinimumSize(QSize(0, 20))
        self.frame_12.setFrameShape(QFrame.StyledPanel)
        self.frame_12.setFrameShadow(QFrame.Raised)
        self.gridLayout_38 = QGridLayout(self.frame_12)
        self.gridLayout_38.setSpacing(6)
        self.gridLayout_38.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_38.setObjectName(u"gridLayout_38")
        self.gridLayout_38.setHorizontalSpacing(0)
        self.gridLayout_38.setVerticalSpacing(5)
        self.gridLayout_38.setContentsMargins(0, 0, 0, 0)
        self.leConveyorPoint3X = QLineEdit(self.frame_12)
        self.leConveyorPoint3X.setObjectName(u"leConveyorPoint3X")
        sizePolicy9.setHeightForWidth(self.leConveyorPoint3X.sizePolicy().hasHeightForWidth())
        self.leConveyorPoint3X.setSizePolicy(sizePolicy9)
        self.leConveyorPoint3X.setMinimumSize(QSize(0, 0))

        self.gridLayout_38.addWidget(self.leConveyorPoint3X, 0, 1, 1, 1)

        self.leConveyorPoint3Y = QLineEdit(self.frame_12)
        self.leConveyorPoint3Y.setObjectName(u"leConveyorPoint3Y")
        sizePolicy9.setHeightForWidth(self.leConveyorPoint3Y.sizePolicy().hasHeightForWidth())
        self.leConveyorPoint3Y.setSizePolicy(sizePolicy9)
        self.leConveyorPoint3Y.setMinimumSize(QSize(0, 0))

        self.gridLayout_38.addWidget(self.leConveyorPoint3Y, 1, 1, 1, 1)

        self.label_169 = QLabel(self.frame_12)
        self.label_169.setObjectName(u"label_169")
        self.label_169.setMaximumSize(QSize(20, 16777215))

        self.gridLayout_38.addWidget(self.label_169, 1, 0, 1, 1)

        self.label_168 = QLabel(self.frame_12)
        self.label_168.setObjectName(u"label_168")
        self.label_168.setMaximumSize(QSize(20, 16777215))

        self.gridLayout_38.addWidget(self.label_168, 0, 0, 1, 1)

        self.label_171 = QLabel(self.frame_12)
        self.label_171.setObjectName(u"label_171")
        self.label_171.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_38.addWidget(self.label_171, 0, 2, 1, 1)


        self.gridLayout_16.addWidget(self.frame_12, 9, 4, 1, 1)

        self.label_167 = QLabel(self.fTracking)
        self.label_167.setObjectName(u"label_167")
        self.label_167.setFont(font4)

        self.gridLayout_16.addWidget(self.label_167, 9, 3, 1, 1)


        self.verticalLayout_33.addLayout(self.gridLayout_16)


        self.verticalLayout_41.addWidget(self.fTracking)

        self.fVisionConveyorFrame = QFrame(self.gbConveyorForTracking)
        self.fVisionConveyorFrame.setObjectName(u"fVisionConveyorFrame")
        self.fVisionConveyorFrame.setMinimumSize(QSize(0, 0))
        self.fVisionConveyorFrame.setFrameShape(QFrame.StyledPanel)
        self.fVisionConveyorFrame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_49 = QVBoxLayout(self.fVisionConveyorFrame)
        self.verticalLayout_49.setSpacing(6)
        self.verticalLayout_49.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_49.setObjectName(u"verticalLayout_49")
        self.verticalLayout_49.setContentsMargins(0, 0, 0, 0)

        self.verticalLayout_41.addWidget(self.fVisionConveyorFrame)


        self.verticalLayout_32.addWidget(self.gbConveyorForTracking)

        self.verticalSpacer_11 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_32.addItem(self.verticalSpacer_11)

        self.splitter.addWidget(self.fObjectDetectingTool)

        self.verticalLayout_17.addWidget(self.splitter)

        self.saObjectDetecting.setWidget(self.wObjectDetecting)

        self.verticalLayout_25.addWidget(self.saObjectDetecting)

        self.twModule.addTab(self.tObjectDetecting, "")
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
        self.scrollAreaWidgetContents_6.setGeometry(QRect(0, 0, 591, 1600))
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
        sizePolicy4.setHeightForWidth(self.frame_4.sizePolicy().hasHeightForWidth())
        self.frame_4.setSizePolicy(sizePolicy4)
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
        sizePolicy10 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy10.setHorizontalStretch(0)
        sizePolicy10.setVerticalStretch(0)
        sizePolicy10.setHeightForWidth(self.pbOpenPicture.sizePolicy().hasHeightForWidth())
        self.pbOpenPicture.setSizePolicy(sizePolicy10)
        self.pbOpenPicture.setMinimumSize(QSize(0, 0))
        self.pbOpenPicture.setMaximumSize(QSize(16777215, 16777215))
        font12 = QFont()
        font12.setPointSize(10)
        font12.setBold(False)
        self.pbOpenPicture.setFont(font12)
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
        self.lbImageWidth.setFont(font4)
        self.lbImageWidth.setStyleSheet(u"")

        self.gridLayout_23.addWidget(self.lbImageWidth, 0, 0, 1, 1)

        self.lbImageHeight = QLabel(self.widget_3)
        self.lbImageHeight.setObjectName(u"lbImageHeight")
        self.lbImageHeight.setFont(font4)
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
        self.leDrawingThreshold.setFont(font4)

        self.gridLayout_25.addWidget(self.leDrawingThreshold, 1, 3, 1, 1)

        self.label_14 = QLabel(self.widget_2)
        self.label_14.setObjectName(u"label_14")
        self.label_14.setFont(font4)

        self.gridLayout_25.addWidget(self.label_14, 1, 0, 1, 1)

        self.label_105 = QLabel(self.widget_2)
        self.label_105.setObjectName(u"label_105")
        self.label_105.setFont(font4)

        self.gridLayout_25.addWidget(self.label_105, 2, 0, 1, 1)

        self.cbReverseDrawing = QCheckBox(self.widget_2)
        self.cbReverseDrawing.setObjectName(u"cbReverseDrawing")

        self.gridLayout_25.addWidget(self.cbReverseDrawing, 2, 1, 1, 1)


        self.verticalLayout_37.addWidget(self.widget_2)

        self.frame_5 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_5.setObjectName(u"frame_5")
        sizePolicy1.setHeightForWidth(self.frame_5.sizePolicy().hasHeightForWidth())
        self.frame_5.setSizePolicy(sizePolicy1)
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
        sizePolicy10.setHeightForWidth(self.pbPainting.sizePolicy().hasHeightForWidth())
        self.pbPainting.setSizePolicy(sizePolicy10)
        self.pbPainting.setMinimumSize(QSize(0, 0))
        self.pbPainting.setMaximumSize(QSize(16777215, 16777215))
        self.pbPainting.setFont(font12)
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
        self.label_20.setFont(font4)

        self.gridLayout_24.addWidget(self.label_20, 0, 1, 1, 1)

        self.label_18 = QLabel(self.frame_7)
        self.label_18.setObjectName(u"label_18")
        self.label_18.setFont(font4)

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
        sizePolicy4.setHeightForWidth(self.frame_3.sizePolicy().hasHeightForWidth())
        self.frame_3.setSizePolicy(sizePolicy4)
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
        sizePolicy11 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy11.setHorizontalStretch(0)
        sizePolicy11.setVerticalStretch(0)
        sizePolicy11.setHeightForWidth(self.leDrawAg5.sizePolicy().hasHeightForWidth())
        self.leDrawAg5.setSizePolicy(sizePolicy11)
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
        self.label_25.setFont(font4)

        self.horizontalLayout_21.addWidget(self.label_25)

        self.leDrawAg4 = QLineEdit(self.widget_10)
        self.leDrawAg4.setObjectName(u"leDrawAg4")
        sizePolicy11.setHeightForWidth(self.leDrawAg4.sizePolicy().hasHeightForWidth())
        self.leDrawAg4.setSizePolicy(sizePolicy11)
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
        sizePolicy11.setHeightForWidth(self.leDrawAg3.sizePolicy().hasHeightForWidth())
        self.leDrawAg3.setSizePolicy(sizePolicy11)
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
        sizePolicy11.setHeightForWidth(self.leDrawAg2.sizePolicy().hasHeightForWidth())
        self.leDrawAg2.setSizePolicy(sizePolicy11)
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
        sizePolicy11.setHeightForWidth(self.leDrawAg1.sizePolicy().hasHeightForWidth())
        self.leDrawAg1.setSizePolicy(sizePolicy11)
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
        sizePolicy12 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        sizePolicy12.setHorizontalStretch(0)
        sizePolicy12.setVerticalStretch(0)
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
        sizePolicy1.setHeightForWidth(self.frame_6.sizePolicy().hasHeightForWidth())
        self.frame_6.setSizePolicy(sizePolicy1)
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
        sizePolicy10.setHeightForWidth(self.pbExportDrawingGcodes.sizePolicy().hasHeightForWidth())
        self.pbExportDrawingGcodes.setSizePolicy(sizePolicy10)
        self.pbExportDrawingGcodes.setMinimumSize(QSize(185, 65))
        self.pbExportDrawingGcodes.setMaximumSize(QSize(16777215, 16777215))
        self.pbExportDrawingGcodes.setFont(font12)
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
        sizePolicy2.setHeightForWidth(self.label_96.sizePolicy().hasHeightForWidth())
        self.label_96.setSizePolicy(sizePolicy2)
        self.label_96.setMinimumSize(QSize(0, 0))
        self.label_96.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_96, 4, 0, 1, 1)

        self.label_101 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_101.setObjectName(u"label_101")
        sizePolicy.setHeightForWidth(self.label_101.sizePolicy().hasHeightForWidth())
        self.label_101.setSizePolicy(sizePolicy)
        self.label_101.setMinimumSize(QSize(0, 0))
        font13 = QFont()
        font13.setItalic(False)
        self.label_101.setFont(font13)
        self.label_101.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_101, 6, 2, 1, 1)

        self.label_13 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_13.setObjectName(u"label_13")
        self.label_13.setFont(font4)
        self.label_13.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_13, 1, 0, 1, 1)

        self.horizontalSpacer_33 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_22.addItem(self.horizontalSpacer_33, 0, 2, 1, 1)

        self.label_97 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_97.setObjectName(u"label_97")
        sizePolicy2.setHeightForWidth(self.label_97.sizePolicy().hasHeightForWidth())
        self.label_97.setSizePolicy(sizePolicy2)
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
        sizePolicy1.setHeightForWidth(self.cbDrawingEffector.sizePolicy().hasHeightForWidth())
        self.cbDrawingEffector.setSizePolicy(sizePolicy1)
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
        self.label_102.setFont(font13)
        self.label_102.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_102, 7, 2, 1, 1)

        self.label_93 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_93.setObjectName(u"label_93")
        sizePolicy13 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Preferred)
        sizePolicy13.setHorizontalStretch(0)
        sizePolicy13.setVerticalStretch(0)
        sizePolicy13.setHeightForWidth(self.label_93.sizePolicy().hasHeightForWidth())
        self.label_93.setSizePolicy(sizePolicy13)
        self.label_93.setMinimumSize(QSize(0, 0))
        self.label_93.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_93, 0, 0, 1, 1)

        self.label_95 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_95.setObjectName(u"label_95")
        sizePolicy2.setHeightForWidth(self.label_95.sizePolicy().hasHeightForWidth())
        self.label_95.setSizePolicy(sizePolicy2)
        self.label_95.setMinimumSize(QSize(0, 0))
        self.label_95.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_95, 3, 0, 1, 1)

        self.label_100 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_100.setObjectName(u"label_100")
        sizePolicy.setHeightForWidth(self.label_100.sizePolicy().hasHeightForWidth())
        self.label_100.setSizePolicy(sizePolicy)
        self.label_100.setMinimumSize(QSize(0, 0))
        self.label_100.setFont(font13)
        self.label_100.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_100, 4, 2, 1, 1)

        self.label_98 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_98.setObjectName(u"label_98")
        sizePolicy2.setHeightForWidth(self.label_98.sizePolicy().hasHeightForWidth())
        self.label_98.setSizePolicy(sizePolicy2)
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
        self.label_99.setFont(font13)
        self.label_99.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_99, 3, 2, 1, 1)

        self.label_23 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_23.setObjectName(u"label_23")
        self.label_23.setFont(font4)
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
        self.label_103.setFont(font13)
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
        self.scrollAreaWidgetContents_7.setGeometry(QRect(0, 0, 605, 509))
        self.verticalLayout_27 = QVBoxLayout(self.scrollAreaWidgetContents_7)
        self.verticalLayout_27.setSpacing(6)
        self.verticalLayout_27.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_27.setObjectName(u"verticalLayout_27")
        self.gridLayout_4 = QGridLayout()
        self.gridLayout_4.setSpacing(6)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.teDebug = QTextEdit(self.scrollAreaWidgetContents_7)
        self.teDebug.setObjectName(u"teDebug")
        font14 = QFont()
        font14.setBold(False)
        font14.setItalic(False)
        font14.setKerning(True)
        self.teDebug.setFont(font14)
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
        self.cbDeviceSender.setObjectName(u"cbDeviceSender")

        self.gridLayout_4.addWidget(self.cbDeviceSender, 1, 2, 1, 1)


        self.verticalLayout_27.addLayout(self.gridLayout_4)

        self.scrollArea_7.setWidget(self.scrollAreaWidgetContents_7)

        self.verticalLayout_11.addWidget(self.scrollArea_7)

        self.twModule.addTab(self.TermiteTab, "")

        self.ModuleTabManagerLayout.addWidget(self.twModule)

        self.splitter_2.addWidget(self.ModuleTabManagerWidget)
        self.GeometryTabManagerWidget = QWidget(self.splitter_2)
        self.GeometryTabManagerWidget.setObjectName(u"GeometryTabManagerWidget")
        self.GeometryTabManagerWidget.setMinimumSize(QSize(0, 0))
        self.GeometryTabManagerWidget.setMaximumSize(QSize(800, 16777215))
        self.GeometryTabManagerWidget.setStyleSheet(u"")
        self.GeometryTabManagerLayout = QVBoxLayout(self.GeometryTabManagerWidget)
        self.GeometryTabManagerLayout.setSpacing(0)
        self.GeometryTabManagerLayout.setContentsMargins(11, 11, 11, 11)
        self.GeometryTabManagerLayout.setObjectName(u"GeometryTabManagerLayout")
        self.GeometryTabManagerLayout.setContentsMargins(0, 0, 0, 0)
        self.twDeltaGeometry = QTabWidget(self.GeometryTabManagerWidget)
        self.twDeltaGeometry.setObjectName(u"twDeltaGeometry")
        self.twDeltaGeometry.setMinimumSize(QSize(0, 0))
        self.twDeltaGeometry.setFont(font2)
        self.twDeltaGeometry.setStyleSheet(u"")
        self.twDeltaGeometry.setTabPosition(QTabWidget.North)
        self.twDeltaGeometry.setElideMode(Qt.ElideNone)
        self.twDeltaGeometry.setTabsClosable(False)
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
        self.wgJoggingScrollWidget.setGeometry(QRect(0, 0, 535, 800))
        self.wgJoggingScrollWidget.setMinimumSize(QSize(0, 800))
        self.wgJoggingScrollWidget.setMaximumSize(QSize(16777215, 16777215))
        self.verticalLayout_5 = QVBoxLayout(self.wgJoggingScrollWidget)
        self.verticalLayout_5.setSpacing(10)
        self.verticalLayout_5.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(5, 10, 5, 0)
        self.groupRobotConnection = QFrame(self.wgJoggingScrollWidget)
        self.groupRobotConnection.setObjectName(u"groupRobotConnection")
        sizePolicy4.setHeightForWidth(self.groupRobotConnection.sizePolicy().hasHeightForWidth())
        self.groupRobotConnection.setSizePolicy(sizePolicy4)
        self.groupRobotConnection.setMaximumSize(QSize(16777215, 16777215))
        self.groupRobotConnection.setFont(font7)
        self.groupRobotConnection.setStyleSheet(u"")
        self.horizontalLayout_14 = QHBoxLayout(self.groupRobotConnection)
        self.horizontalLayout_14.setSpacing(0)
        self.horizontalLayout_14.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_14.setObjectName(u"horizontalLayout_14")
        self.horizontalLayout_14.setContentsMargins(30, 0, -1, 5)
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
        self.lbW = QLabel(self.fRobotPosition)
        self.lbW.setObjectName(u"lbW")
        self.lbW.setMinimumSize(QSize(30, 20))
        self.lbW.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.lbW, 1, 5, 1, 1)

        self.label_94 = QLabel(self.fRobotPosition)
        self.label_94.setObjectName(u"label_94")
        self.label_94.setMinimumSize(QSize(0, 20))
        self.label_94.setFont(font10)
        self.label_94.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_94, 0, 7, 1, 1)

        self.label_88 = QLabel(self.fRobotPosition)
        self.label_88.setObjectName(u"label_88")
        self.label_88.setMinimumSize(QSize(0, 20))
        self.label_88.setFont(font10)
        self.label_88.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_88, 0, 4, 1, 1)

        self.lbU = QLabel(self.fRobotPosition)
        self.lbU.setObjectName(u"lbU")
        self.lbU.setMinimumSize(QSize(30, 20))
        self.lbU.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.lbU, 1, 6, 1, 1)

        self.label_92 = QLabel(self.fRobotPosition)
        self.label_92.setObjectName(u"label_92")
        self.label_92.setMinimumSize(QSize(0, 20))
        self.label_92.setFont(font10)
        self.label_92.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_92, 0, 6, 1, 1)

        self.lbY = QLabel(self.fRobotPosition)
        self.lbY.setObjectName(u"lbY")
        self.lbY.setMinimumSize(QSize(30, 20))
        self.lbY.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.lbY, 1, 3, 1, 1)

        self.lbZ = QLabel(self.fRobotPosition)
        self.lbZ.setObjectName(u"lbZ")
        self.lbZ.setMinimumSize(QSize(30, 20))
        self.lbZ.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.lbZ, 1, 4, 1, 1)

        self.lbV = QLabel(self.fRobotPosition)
        self.lbV.setObjectName(u"lbV")
        self.lbV.setMinimumSize(QSize(30, 20))
        self.lbV.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.lbV, 1, 7, 1, 1)

        self.label_90 = QLabel(self.fRobotPosition)
        self.label_90.setObjectName(u"label_90")
        self.label_90.setMinimumSize(QSize(0, 20))
        self.label_90.setFont(font10)
        self.label_90.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_90, 0, 5, 1, 1)

        self.label_86 = QLabel(self.fRobotPosition)
        self.label_86.setObjectName(u"label_86")
        self.label_86.setMinimumSize(QSize(0, 20))
        self.label_86.setFont(font10)
        self.label_86.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_86, 0, 3, 1, 1)

        self.horizontalSpacer_4 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_19.addItem(self.horizontalSpacer_4, 0, 8, 1, 1)

        self.lbX = QLabel(self.fRobotPosition)
        self.lbX.setObjectName(u"lbX")
        self.lbX.setMinimumSize(QSize(30, 20))
        self.lbX.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.lbX, 1, 2, 1, 1)

        self.label_84 = QLabel(self.fRobotPosition)
        self.label_84.setObjectName(u"label_84")
        self.label_84.setMinimumSize(QSize(0, 20))
        self.label_84.setFont(font10)
        self.label_84.setAlignment(Qt.AlignCenter)

        self.gridLayout_19.addWidget(self.label_84, 0, 2, 1, 1)


        self.horizontalLayout_14.addWidget(self.fRobotPosition)

        self.verticalLayout_12 = QVBoxLayout()
        self.verticalLayout_12.setSpacing(6)
        self.verticalLayout_12.setObjectName(u"verticalLayout_12")
        self.pbConnect = QPushButton(self.groupRobotConnection)
        self.pbConnect.setObjectName(u"pbConnect")
        self.pbConnect.setMinimumSize(QSize(0, 30))
        self.pbConnect.setFont(font12)
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

        self.verticalLayout_12.addWidget(self.pbConnect)

        self.cbAutoConnect = QCheckBox(self.groupRobotConnection)
        self.cbAutoConnect.setObjectName(u"cbAutoConnect")
        self.cbAutoConnect.setFont(font7)
        self.cbAutoConnect.setStyleSheet(u"")
        self.cbAutoConnect.setChecked(True)

        self.verticalLayout_12.addWidget(self.cbAutoConnect)


        self.horizontalLayout_14.addLayout(self.verticalLayout_12)

        self.frameRobotConnection = QFrame(self.groupRobotConnection)
        self.frameRobotConnection.setObjectName(u"frameRobotConnection")
        self.frameRobotConnection.setMinimumSize(QSize(0, 50))
        self.frameRobotConnection.setMaximumSize(QSize(16777215, 50))
        self.frameRobotConnection.setFont(font14)
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

        self.RobotTabWidget = QTabWidget(self.wgJoggingScrollWidget)
        self.RobotTabWidget.setObjectName(u"RobotTabWidget")
        self.RobotTabWidget.setMinimumSize(QSize(0, 300))
        self.InstallationTab = QWidget()
        self.InstallationTab.setObjectName(u"InstallationTab")
        self.layoutWidget2 = QWidget(self.InstallationTab)
        self.layoutWidget2.setObjectName(u"layoutWidget2")
        self.layoutWidget2.setGeometry(QRect(10, 15, 201, 176))
        self.gridLayout_31 = QGridLayout(self.layoutWidget2)
        self.gridLayout_31.setSpacing(6)
        self.gridLayout_31.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_31.setObjectName(u"gridLayout_31")
        self.gridLayout_31.setContentsMargins(0, 0, 0, 0)
        self.label_65 = QLabel(self.layoutWidget2)
        self.label_65.setObjectName(u"label_65")
        self.label_65.setFont(font10)
        self.label_65.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_65, 7, 0, 1, 1)

        self.lbID = QLabel(self.layoutWidget2)
        self.lbID.setObjectName(u"lbID")
        self.lbID.setFont(font7)
        self.lbID.setStyleSheet(u"")

        self.gridLayout_31.addWidget(self.lbID, 3, 1, 1, 1)

        self.lbComName = QLabel(self.layoutWidget2)
        self.lbComName.setObjectName(u"lbComName")
        self.lbComName.setFont(font7)
        self.lbComName.setStyleSheet(u"")

        self.gridLayout_31.addWidget(self.lbComName, 5, 1, 1, 1)

        self.lbBaudrate = QLabel(self.layoutWidget2)
        self.lbBaudrate.setObjectName(u"lbBaudrate")
        self.lbBaudrate.setFont(font7)
        self.lbBaudrate.setStyleSheet(u"")

        self.gridLayout_31.addWidget(self.lbBaudrate, 7, 1, 1, 1)

        self.lbIP = QLabel(self.layoutWidget2)
        self.lbIP.setObjectName(u"lbIP")
        self.lbIP.setFont(font7)
        self.lbIP.setStyleSheet(u"")

        self.gridLayout_31.addWidget(self.lbIP, 8, 1, 1, 1)

        self.label_91 = QLabel(self.layoutWidget2)
        self.label_91.setObjectName(u"label_91")
        self.label_91.setFont(font10)
        self.label_91.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_91, 1, 0, 1, 1)

        self.cbRobotModel = QComboBox(self.layoutWidget2)
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.setObjectName(u"cbRobotModel")
        self.cbRobotModel.setMinimumSize(QSize(80, 0))

        self.gridLayout_31.addWidget(self.cbRobotModel, 1, 1, 1, 1)

        self.label_6 = QLabel(self.layoutWidget2)
        self.label_6.setObjectName(u"label_6")
        self.label_6.setFont(font10)
        self.label_6.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_6, 3, 0, 1, 1)

        self.label_10 = QLabel(self.layoutWidget2)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setFont(font10)
        self.label_10.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_10, 5, 0, 1, 1)

        self.label_122 = QLabel(self.layoutWidget2)
        self.label_122.setObjectName(u"label_122")
        self.label_122.setFont(font10)
        self.label_122.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_122, 8, 0, 1, 1)

        self.label_123 = QLabel(self.layoutWidget2)
        self.label_123.setObjectName(u"label_123")
        self.label_123.setFont(font10)
        self.label_123.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_123, 9, 0, 1, 1)

        self.lbLocalPort = QLabel(self.layoutWidget2)
        self.lbLocalPort.setObjectName(u"lbLocalPort")
        self.lbLocalPort.setFont(font7)
        self.lbLocalPort.setStyleSheet(u"")

        self.gridLayout_31.addWidget(self.lbLocalPort, 9, 1, 1, 1)

        self.label_113 = QLabel(self.layoutWidget2)
        self.label_113.setObjectName(u"label_113")
        self.label_113.setFont(font10)
        self.label_113.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_113, 2, 0, 1, 1)

        self.cbRobotModel_2 = QComboBox(self.layoutWidget2)
        self.cbRobotModel_2.addItem("")
        self.cbRobotModel_2.addItem("")
        self.cbRobotModel_2.addItem("")
        self.cbRobotModel_2.addItem("")
        self.cbRobotModel_2.setObjectName(u"cbRobotModel_2")
        self.cbRobotModel_2.setMinimumSize(QSize(80, 0))

        self.gridLayout_31.addWidget(self.cbRobotModel_2, 2, 1, 1, 1)

        self.RobotTabWidget.addTab(self.InstallationTab, "")
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
        self.ButtonTab = QWidget()
        self.ButtonTab.setObjectName(u"ButtonTab")
        self.label_28 = QLabel(self.ButtonTab)
        self.label_28.setObjectName(u"label_28")
        self.label_28.setGeometry(QRect(20, 305, 31, 19))
        self.label_28.setStyleSheet(u"color: rgb(95, 95, 95);")
        self.cbDivision = QComboBox(self.ButtonTab)
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.addItem("")
        self.cbDivision.setObjectName(u"cbDivision")
        self.cbDivision.setGeometry(QRect(15, 280, 46, 21))
        self.cbDivision.setMinimumSize(QSize(0, 20))
        self.cbDivision.setMaximumSize(QSize(100, 16777215))
        self.pbHome = QToolButton(self.ButtonTab)
        self.pbHome.setObjectName(u"pbHome")
        self.pbHome.setGeometry(QRect(15, 10, 46, 46))
        self.pbHome.setMinimumSize(QSize(40, 40))
        self.pbHome.setFont(font3)
        icon38 = QIcon()
        icon38.addFile(u":/icon/home.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbHome.setIcon(icon38)
        self.pbHome.setIconSize(QSize(20, 20))
        self.pbHome.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.label_33 = QLabel(self.ButtonTab)
        self.label_33.setObjectName(u"label_33")
        self.label_33.setGeometry(QRect(15, 255, 41, 19))
        self.label_33.setMaximumSize(QSize(60, 16777215))
        self.layoutWidget3 = QWidget(self.ButtonTab)
        self.layoutWidget3.setObjectName(u"layoutWidget3")
        self.layoutWidget3.setGeometry(QRect(75, 10, 209, 147))
        self.gridLayout_2 = QGridLayout(self.layoutWidget3)
        self.gridLayout_2.setSpacing(5)
        self.gridLayout_2.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.gridLayout_2.setContentsMargins(0, 0, 0, 0)
        self.pbLeft = QToolButton(self.layoutWidget3)
        self.pbLeft.setObjectName(u"pbLeft")
        icon39 = QIcon()
        icon39.addFile(u":/icon/icons8-back-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLeft.setIcon(icon39)
        self.pbLeft.setIconSize(QSize(40, 40))
        self.pbLeft.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbLeft, 0, 2, 2, 1)

        self.pbRight = QToolButton(self.layoutWidget3)
        self.pbRight.setObjectName(u"pbRight")
        icon40 = QIcon()
        icon40.addFile(u":/icon/icons8-forward-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbRight.setIcon(icon40)
        self.pbRight.setIconSize(QSize(40, 40))
        self.pbRight.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbRight, 0, 4, 2, 1)

        self.pbBackward = QToolButton(self.layoutWidget3)
        self.pbBackward.setObjectName(u"pbBackward")
        icon41 = QIcon()
        icon41.addFile(u":/icon/icons8-expand-arrow-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbBackward.setIcon(icon41)
        self.pbBackward.setIconSize(QSize(40, 40))
        self.pbBackward.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbBackward, 1, 3, 1, 1)

        self.pbForward = QToolButton(self.layoutWidget3)
        self.pbForward.setObjectName(u"pbForward")
        self.pbForward.setStyleSheet(u"")
        icon42 = QIcon()
        icon42.addFile(u":/icon/icons8-collapse-arrow-48.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbForward.setIcon(icon42)
        self.pbForward.setIconSize(QSize(40, 40))
        self.pbForward.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_2.addWidget(self.pbForward, 0, 3, 1, 1)

        self.pbSubRoll = QToolButton(self.ButtonTab)
        self.pbSubRoll.setObjectName(u"pbSubRoll")
        self.pbSubRoll.setGeometry(QRect(80, 180, 48, 70))
        self.pbSubRoll.setIcon(icon39)
        self.pbSubRoll.setIconSize(QSize(40, 40))
        self.pbSubRoll.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbPlusRoll = QToolButton(self.ButtonTab)
        self.pbPlusRoll.setObjectName(u"pbPlusRoll")
        self.pbPlusRoll.setGeometry(QRect(80, 260, 48, 70))
        self.pbPlusRoll.setIcon(icon40)
        self.pbPlusRoll.setIconSize(QSize(40, 40))
        self.pbPlusRoll.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbPlusYaw = QToolButton(self.ButtonTab)
        self.pbPlusYaw.setObjectName(u"pbPlusYaw")
        self.pbPlusYaw.setGeometry(QRect(155, 260, 48, 70))
        self.pbPlusYaw.setIcon(icon40)
        self.pbPlusYaw.setIconSize(QSize(40, 40))
        self.pbPlusYaw.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbSubYaw = QToolButton(self.ButtonTab)
        self.pbSubYaw.setObjectName(u"pbSubYaw")
        self.pbSubYaw.setGeometry(QRect(155, 180, 48, 70))
        self.pbSubYaw.setIcon(icon39)
        self.pbSubYaw.setIconSize(QSize(40, 40))
        self.pbSubYaw.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbPlusPitch = QToolButton(self.ButtonTab)
        self.pbPlusPitch.setObjectName(u"pbPlusPitch")
        self.pbPlusPitch.setGeometry(QRect(230, 260, 48, 70))
        self.pbPlusPitch.setIcon(icon40)
        self.pbPlusPitch.setIconSize(QSize(40, 40))
        self.pbPlusPitch.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbSubPitch = QToolButton(self.ButtonTab)
        self.pbSubPitch.setObjectName(u"pbSubPitch")
        self.pbSubPitch.setGeometry(QRect(230, 180, 48, 70))
        self.pbSubPitch.setIcon(icon39)
        self.pbSubPitch.setIconSize(QSize(40, 40))
        self.pbSubPitch.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDown = QToolButton(self.ButtonTab)
        self.pbDown.setObjectName(u"pbDown")
        self.pbDown.setGeometry(QRect(315, 85, 48, 67))
        self.pbDown.setIcon(icon41)
        self.pbDown.setIconSize(QSize(40, 40))
        self.pbDown.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbUp = QToolButton(self.ButtonTab)
        self.pbUp.setObjectName(u"pbUp")
        self.pbUp.setGeometry(QRect(315, 10, 48, 67))
        self.pbUp.setIcon(icon42)
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
        self.scrollAreaWidgetContents_3.setGeometry(QRect(0, 0, 501, 600))
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
        self.fXYWorkingArea.setMinimumSize(QSize(0, 230))
        self.wg2D = QWidget(self.fXYWorkingArea)
        self.wg2D.setObjectName(u"wg2D")
        self.wg2D.setGeometry(QRect(30, 5, 200, 200))
        sizePolicy10.setHeightForWidth(self.wg2D.sizePolicy().hasHeightForWidth())
        self.wg2D.setSizePolicy(sizePolicy10)
        self.wg2D.setMinimumSize(QSize(200, 200))
        self.wg2D.setMaximumSize(QSize(16777215, 16777215))
        self.wg2D.setStyleSheet(u"background-color: rgb(240, 240, 240);")
        self.label_15 = QLabel(self.fXYWorkingArea)
        self.label_15.setObjectName(u"label_15")
        self.label_15.setGeometry(QRect(6, 210, 16, 19))
        sizePolicy14 = QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Preferred)
        sizePolicy14.setHorizontalStretch(0)
        sizePolicy14.setVerticalStretch(0)
        sizePolicy14.setHeightForWidth(self.label_15.sizePolicy().hasHeightForWidth())
        self.label_15.setSizePolicy(sizePolicy14)
        self.vsZAdjsution = QSlider(self.fXYWorkingArea)
        self.vsZAdjsution.setObjectName(u"vsZAdjsution")
        self.vsZAdjsution.setGeometry(QRect(6, 6, 16, 201))
        sizePolicy6.setHeightForWidth(self.vsZAdjsution.sizePolicy().hasHeightForWidth())
        self.vsZAdjsution.setSizePolicy(sizePolicy6)
        self.vsZAdjsution.setMaximum(300)
        self.vsZAdjsution.setOrientation(Qt.Vertical)

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

        self.vsAngleAdjsution = QSlider(self.scrollAreaWidgetContents_3)
        self.vsAngleAdjsution.setObjectName(u"vsAngleAdjsution")
        self.vsAngleAdjsution.setMinimumSize(QSize(0, 30))
        self.vsAngleAdjsution.setMinimum(-360)
        self.vsAngleAdjsution.setMaximum(360)
        self.vsAngleAdjsution.setValue(0)
        self.vsAngleAdjsution.setOrientation(Qt.Horizontal)

        self.gridLayout_9.addWidget(self.vsAngleAdjsution, 0, 1, 1, 1)

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

        self.lb4AxisValue = QLabel(self.scrollAreaWidgetContents_3)
        self.lb4AxisValue.setObjectName(u"lb4AxisValue")

        self.gridLayout_9.addWidget(self.lb4AxisValue, 0, 2, 1, 1)

        self.lb5AxisValue = QLabel(self.scrollAreaWidgetContents_3)
        self.lb5AxisValue.setObjectName(u"lb5AxisValue")

        self.gridLayout_9.addWidget(self.lb5AxisValue, 1, 2, 1, 1)

        self.lb6AxisValue = QLabel(self.scrollAreaWidgetContents_3)
        self.lb6AxisValue.setObjectName(u"lb6AxisValue")

        self.gridLayout_9.addWidget(self.lb6AxisValue, 2, 2, 1, 1)


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
        self.gbJoystick.setFont(font5)
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
        self.wgOldOutput = QWidget(self.OutputTab)
        self.wgOldOutput.setObjectName(u"wgOldOutput")
        self.horizontalLayout_7 = QHBoxLayout(self.wgOldOutput)
        self.horizontalLayout_7.setSpacing(6)
        self.horizontalLayout_7.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.gbRelay = QGroupBox(self.wgOldOutput)
        self.gbRelay.setObjectName(u"gbRelay")
        self.gbRelay.setMaximumSize(QSize(150, 16777215))
        self.gbRelay.setFont(font10)
        self.gridLayout_3 = QGridLayout(self.gbRelay)
        self.gridLayout_3.setSpacing(6)
        self.gridLayout_3.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.label_34 = QLabel(self.gbRelay)
        self.label_34.setObjectName(u"label_34")
        self.label_34.setMaximumSize(QSize(16777215, 20))
        self.label_34.setFont(font4)
        self.label_34.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_34, 0, 0, 1, 1)

        self.label_35 = QLabel(self.gbRelay)
        self.label_35.setObjectName(u"label_35")
        self.label_35.setMaximumSize(QSize(16777215, 20))
        self.label_35.setFont(font4)
        self.label_35.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_35, 0, 1, 1, 1)

        self.pbPump = QPushButton(self.gbRelay)
        self.pbPump.setObjectName(u"pbPump")
        self.pbPump.setMinimumSize(QSize(50, 30))
        self.pbPump.setAutoFillBackground(False)
        icon43 = QIcon()
        icon43.addFile(u":/icon/Toggle Off_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon43.addFile(u":/icon/Toggle On_16px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbPump.setIcon(icon43)
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
        self.pbLaser.setIcon(icon43)
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
        self.gbGripper.setFont(font10)
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
        self.label_17.setFont(font4)
        self.label_17.setAlignment(Qt.AlignCenter)

        self.gridLayout_6.addWidget(self.label_17, 0, 1, 1, 1)

        self.label_27 = QLabel(self.gbGripper)
        self.label_27.setObjectName(u"label_27")
        self.label_27.setFont(font4)
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
        sizePolicy11.setHeightForWidth(self.hsGripperAngle.sizePolicy().hasHeightForWidth())
        self.hsGripperAngle.setSizePolicy(sizePolicy11)
        self.hsGripperAngle.setMinimumSize(QSize(0, 30))
        self.hsGripperAngle.setMaximum(20)
        self.hsGripperAngle.setSingleStep(5)
        self.hsGripperAngle.setOrientation(Qt.Horizontal)

        self.horizontalLayout_15.addWidget(self.hsGripperAngle)

        self.lbGripperValue = QLabel(self.gbGripper)
        self.lbGripperValue.setObjectName(u"lbGripperValue")
        self.lbGripperValue.setMinimumSize(QSize(40, 0))
        font15 = QFont()
        font15.setPointSize(7)
        font15.setBold(False)
        font15.setKerning(True)
        self.lbGripperValue.setFont(font15)

        self.horizontalLayout_15.addWidget(self.lbGripperValue)


        self.gridLayout_13.addLayout(self.horizontalLayout_15, 1, 0, 1, 1)


        self.horizontalLayout_7.addWidget(self.gbGripper)

        self.horizontalSpacer_46 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_7.addItem(self.horizontalSpacer_46)


        self.verticalLayout_3.addWidget(self.wgOldOutput)

        self.gbOutput = QGroupBox(self.OutputTab)
        self.gbOutput.setObjectName(u"gbOutput")
        self.gbOutput.setMinimumSize(QSize(0, 180))
        self.gbOutput.setFont(font5)
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
        font16 = QFont()
        font16.setBold(False)
        self.label_67.setFont(font16)

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
        self.label_68.setFont(font16)

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
        self.gbInput.setFont(font5)
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
        self.label_70.setFont(font16)

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
        self.label_74.setFont(font16)

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
        self.label_76.setFont(font16)

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
        self.label_78.setFont(font16)

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

        self.horizontalLayout_41 = QHBoxLayout()
        self.horizontalLayout_41.setSpacing(6)
        self.horizontalLayout_41.setObjectName(u"horizontalLayout_41")
        self.label_80 = QLabel(self.gbInput)
        self.label_80.setObjectName(u"label_80")
        self.label_80.setMinimumSize(QSize(30, 0))
        self.label_80.setMaximumSize(QSize(25, 16777215))
        self.label_80.setFont(font16)

        self.horizontalLayout_41.addWidget(self.label_80)

        self.horizontalSpacer_23 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_41.addItem(self.horizontalSpacer_23)

        self.lbI4Value = QLabel(self.gbInput)
        self.lbI4Value.setObjectName(u"lbI4Value")

        self.horizontalLayout_41.addWidget(self.lbI4Value)

        self.horizontalSpacer_24 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_41.addItem(self.horizontalSpacer_24)

        self.cbToggle4 = QCheckBox(self.gbInput)
        self.cbToggle4.setObjectName(u"cbToggle4")
        self.cbToggle4.setMinimumSize(QSize(110, 0))
        self.cbToggle4.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_41.addWidget(self.cbToggle4)

        self.pbReadI4 = QPushButton(self.gbInput)
        self.pbReadI4.setObjectName(u"pbReadI4")
        self.pbReadI4.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_41.addWidget(self.pbReadI4)

        self.horizontalSpacer_55 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_41.addItem(self.horizontalSpacer_55)


        self.verticalLayout_43.addLayout(self.horizontalLayout_41)

        self.horizontalLayout_42 = QHBoxLayout()
        self.horizontalLayout_42.setSpacing(6)
        self.horizontalLayout_42.setObjectName(u"horizontalLayout_42")
        self.label_82 = QLabel(self.gbInput)
        self.label_82.setObjectName(u"label_82")
        self.label_82.setMinimumSize(QSize(30, 0))
        self.label_82.setMaximumSize(QSize(25, 16777215))
        self.label_82.setFont(font16)

        self.horizontalLayout_42.addWidget(self.label_82)

        self.horizontalSpacer_25 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_42.addItem(self.horizontalSpacer_25)

        self.lbI5Value = QLabel(self.gbInput)
        self.lbI5Value.setObjectName(u"lbI5Value")

        self.horizontalLayout_42.addWidget(self.lbI5Value)

        self.horizontalSpacer_26 = QSpacerItem(40, 20, QSizePolicy.Maximum, QSizePolicy.Minimum)

        self.horizontalLayout_42.addItem(self.horizontalSpacer_26)

        self.cbToggle5 = QCheckBox(self.gbInput)
        self.cbToggle5.setObjectName(u"cbToggle5")
        self.cbToggle5.setMinimumSize(QSize(110, 0))
        self.cbToggle5.setMaximumSize(QSize(110, 16777215))

        self.horizontalLayout_42.addWidget(self.cbToggle5)

        self.pbReadI5 = QPushButton(self.gbInput)
        self.pbReadI5.setObjectName(u"pbReadI5")
        self.pbReadI5.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_42.addWidget(self.pbReadI5)

        self.horizontalSpacer_56 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_42.addItem(self.horizontalSpacer_56)


        self.verticalLayout_43.addLayout(self.horizontalLayout_42)

        self.horizontalLayout_43 = QHBoxLayout()
        self.horizontalLayout_43.setSpacing(6)
        self.horizontalLayout_43.setObjectName(u"horizontalLayout_43")
        self.leIx = QLineEdit(self.gbInput)
        self.leIx.setObjectName(u"leIx")
        self.leIx.setMinimumSize(QSize(30, 0))
        self.leIx.setMaximumSize(QSize(25, 16777215))
        self.leIx.setFont(font16)

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
        self.label_83.setFont(font16)

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
        self.label_85.setFont(font16)

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
        self.leAx.setFont(font16)

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
        self.ParameterTab = QWidget()
        self.ParameterTab.setObjectName(u"ParameterTab")
        self.framePositionParameter = QFrame(self.ParameterTab)
        self.framePositionParameter.setObjectName(u"framePositionParameter")
        self.framePositionParameter.setGeometry(QRect(10, 20, 227, 231))
        self.framePositionParameter.setMaximumSize(QSize(230, 16777215))
        self.framePositionParameter.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(206, 206, 206);\n"
"}\n"
"QLabel\n"
"{\n"
"	border: none;\n"
"}")
        self.verticalLayout_2 = QVBoxLayout(self.framePositionParameter)
        self.verticalLayout_2.setSpacing(5)
        self.verticalLayout_2.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.horizontalLayout = QHBoxLayout()
        self.horizontalLayout.setSpacing(10)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(5, 0, 5, 0)
        self.label_40 = QLabel(self.framePositionParameter)
        self.label_40.setObjectName(u"label_40")
        self.label_40.setFont(font5)

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


        self.verticalLayout_2.addLayout(self.horizontalLayout)

        self.horizontalLayout_2 = QHBoxLayout()
        self.horizontalLayout_2.setSpacing(10)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(5, 0, 5, 0)
        self.label_106 = QLabel(self.framePositionParameter)
        self.label_106.setObjectName(u"label_106")
        self.label_106.setFont(font5)

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


        self.verticalLayout_2.addLayout(self.horizontalLayout_2)

        self.horizontalLayout_3 = QHBoxLayout()
        self.horizontalLayout_3.setSpacing(10)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(5, 0, 5, 0)
        self.label_107 = QLabel(self.framePositionParameter)
        self.label_107.setObjectName(u"label_107")
        self.label_107.setFont(font5)

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


        self.verticalLayout_2.addLayout(self.horizontalLayout_3)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setSpacing(10)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(5, 0, 5, 0)
        self.label_108 = QLabel(self.framePositionParameter)
        self.label_108.setObjectName(u"label_108")
        self.label_108.setFont(font5)

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


        self.verticalLayout_2.addLayout(self.horizontalLayout_4)

        self.horizontalLayout_32 = QHBoxLayout()
        self.horizontalLayout_32.setSpacing(10)
        self.horizontalLayout_32.setObjectName(u"horizontalLayout_32")
        self.horizontalLayout_32.setContentsMargins(5, 0, 5, 0)
        self.label_111 = QLabel(self.framePositionParameter)
        self.label_111.setObjectName(u"label_111")
        self.label_111.setFont(font5)

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


        self.verticalLayout_2.addLayout(self.horizontalLayout_32)

        self.horizontalLayout_33 = QHBoxLayout()
        self.horizontalLayout_33.setSpacing(10)
        self.horizontalLayout_33.setObjectName(u"horizontalLayout_33")
        self.horizontalLayout_33.setContentsMargins(5, 0, 5, 0)
        self.label_112 = QLabel(self.framePositionParameter)
        self.label_112.setObjectName(u"label_112")
        self.label_112.setFont(font5)

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


        self.verticalLayout_2.addLayout(self.horizontalLayout_33)

        self.layoutWidget4 = QWidget(self.ParameterTab)
        self.layoutWidget4.setObjectName(u"layoutWidget4")
        self.layoutWidget4.setGeometry(QRect(260, 20, 209, 176))
        self.gridLayout = QGridLayout(self.layoutWidget4)
        self.gridLayout.setSpacing(6)
        self.gridLayout.setContentsMargins(11, 11, 11, 11)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setContentsMargins(10, 0, 0, 0)
        self.label_30 = QLabel(self.layoutWidget4)
        self.label_30.setObjectName(u"label_30")
        self.label_30.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_30, 0, 2, 1, 1)

        self.label_63 = QLabel(self.layoutWidget4)
        self.label_63.setObjectName(u"label_63")
        self.label_63.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_63, 2, 2, 1, 1)

        self.leEndSpeed = QLineEdit(self.layoutWidget4)
        self.leEndSpeed.setObjectName(u"leEndSpeed")
        self.leEndSpeed.setMinimumSize(QSize(0, 30))
        self.leEndSpeed.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leEndSpeed, 3, 1, 1, 1)

        self.label_32 = QLabel(self.layoutWidget4)
        self.label_32.setObjectName(u"label_32")
        self.label_32.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_32, 1, 2, 1, 1)

        self.label_62 = QLabel(self.layoutWidget4)
        self.label_62.setObjectName(u"label_62")
        self.label_62.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_62, 2, 0, 1, 1)

        self.label_116 = QLabel(self.layoutWidget4)
        self.label_116.setObjectName(u"label_116")
        self.label_116.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_116, 3, 0, 1, 1)

        self.leAccel = QLineEdit(self.layoutWidget4)
        self.leAccel.setObjectName(u"leAccel")
        self.leAccel.setMinimumSize(QSize(0, 30))
        self.leAccel.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leAccel, 1, 1, 1, 1)

        self.leStartSpeed = QLineEdit(self.layoutWidget4)
        self.leStartSpeed.setObjectName(u"leStartSpeed")
        self.leStartSpeed.setMinimumSize(QSize(0, 30))
        self.leStartSpeed.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leStartSpeed, 2, 1, 1, 1)

        self.label_29 = QLabel(self.layoutWidget4)
        self.label_29.setObjectName(u"label_29")
        self.label_29.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_29, 0, 0, 1, 1)

        self.leVelocity = QLineEdit(self.layoutWidget4)
        self.leVelocity.setObjectName(u"leVelocity")
        self.leVelocity.setMinimumSize(QSize(0, 30))
        self.leVelocity.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leVelocity, 0, 1, 1, 1)

        self.label_31 = QLabel(self.layoutWidget4)
        self.label_31.setObjectName(u"label_31")
        self.label_31.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_31, 1, 0, 1, 1)

        self.label_117 = QLabel(self.layoutWidget4)
        self.label_117.setObjectName(u"label_117")
        self.label_117.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_117, 3, 2, 1, 1)

        self.label_47 = QLabel(self.layoutWidget4)
        self.label_47.setObjectName(u"label_47")
        self.label_47.setMaximumSize(QSize(60, 16777215))

        self.gridLayout.addWidget(self.label_47, 4, 0, 1, 1)

        self.leEndSpeed_2 = QLineEdit(self.layoutWidget4)
        self.leEndSpeed_2.setObjectName(u"leEndSpeed_2")
        self.leEndSpeed_2.setMinimumSize(QSize(0, 30))
        self.leEndSpeed_2.setMaximumSize(QSize(100, 16777215))

        self.gridLayout.addWidget(self.leEndSpeed_2, 4, 1, 1, 1)

        self.label_64 = QLabel(self.layoutWidget4)
        self.label_64.setObjectName(u"label_64")
        self.label_64.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout.addWidget(self.label_64, 4, 2, 1, 1)

        self.RobotTabWidget.addTab(self.ParameterTab, "")

        self.verticalLayout_5.addWidget(self.RobotTabWidget)

        self.scrollArea_2.setWidget(self.wgJoggingScrollWidget)

        self.verticalLayout_4.addWidget(self.scrollArea_2)

        icon44 = QIcon()
        icon44.addFile(u":/icon/deltaicon.png", QSize(), QIcon.Normal, QIcon.Off)
        self.twDeltaGeometry.addTab(self.tRobot, icon44, "")
        self.EncoderTab = QWidget()
        self.EncoderTab.setObjectName(u"EncoderTab")
        self.twDeltaGeometry.addTab(self.EncoderTab, "")
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
        font17 = QFont()
        font17.setPointSize(12)
        self.pbConveyorConnect.setFont(font17)
        self.pbConveyorConnect.setStyleSheet(u"")
        self.pbConveyorConnect.setCheckable(True)

        self.horizontalLayout_48.addWidget(self.pbConveyorConnect)

        self.lbConveyorCOMName = QLabel(self.ConveyorTab)
        self.lbConveyorCOMName.setObjectName(u"lbConveyorCOMName")
        font18 = QFont()
        font18.setPointSize(11)
        self.lbConveyorCOMName.setFont(font18)
        self.lbConveyorCOMName.setStyleSheet(u"color: rgb(41, 155, 255);")

        self.horizontalLayout_48.addWidget(self.lbConveyorCOMName)


        self.verticalLayout_22.addLayout(self.horizontalLayout_48)

        self.gridLayout_7 = QGridLayout()
        self.gridLayout_7.setSpacing(6)
        self.gridLayout_7.setObjectName(u"gridLayout_7")
        self.gridLayout_7.setHorizontalSpacing(20)
        self.gridLayout_7.setVerticalSpacing(10)
        self.gridLayout_7.setContentsMargins(10, 10, 10, 10)
        self.label_46 = QLabel(self.ConveyorTab)
        self.label_46.setObjectName(u"label_46")
        self.label_46.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_46, 1, 0, 1, 1)

        self.cbConveyorValueType = QComboBox(self.ConveyorTab)
        self.cbConveyorValueType.addItem("")
        self.cbConveyorValueType.addItem("")
        self.cbConveyorValueType.setObjectName(u"cbConveyorValueType")
        self.cbConveyorValueType.setMinimumSize(QSize(0, 20))
        self.cbConveyorValueType.setMaximumSize(QSize(200, 16777215))
        font19 = QFont()
        font19.setPointSize(11)
        font19.setBold(False)
        font19.setKerning(True)
        self.cbConveyorValueType.setFont(font19)
        self.cbConveyorValueType.setStyleSheet(u"")

        self.gridLayout_7.addWidget(self.cbConveyorValueType, 1, 1, 1, 1)

        self.label_52 = QLabel(self.ConveyorTab)
        self.label_52.setObjectName(u"label_52")
        self.label_52.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_52, 0, 0, 1, 1)

        self.cbConveyorMode = QComboBox(self.ConveyorTab)
        self.cbConveyorMode.addItem("")
        self.cbConveyorMode.addItem("")
        self.cbConveyorMode.setObjectName(u"cbConveyorMode")
        self.cbConveyorMode.setMinimumSize(QSize(0, 20))
        self.cbConveyorMode.setMaximumSize(QSize(200, 16777215))
        self.cbConveyorMode.setFont(font19)

        self.gridLayout_7.addWidget(self.cbConveyorMode, 0, 1, 1, 1)

        self.label_12 = QLabel(self.ConveyorTab)
        self.label_12.setObjectName(u"label_12")
        self.label_12.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_12, 2, 0, 1, 1)

        self.leConveyorvMovingValue = QLineEdit(self.ConveyorTab)
        self.leConveyorvMovingValue.setObjectName(u"leConveyorvMovingValue")
        self.leConveyorvMovingValue.setMinimumSize(QSize(0, 20))
        self.leConveyorvMovingValue.setMaximumSize(QSize(200, 16777215))
        self.leConveyorvMovingValue.setFont(font19)

        self.gridLayout_7.addWidget(self.leConveyorvMovingValue, 2, 1, 1, 1)

        self.lbUnitOfConveyorMoving = QLabel(self.ConveyorTab)
        self.lbUnitOfConveyorMoving.setObjectName(u"lbUnitOfConveyorMoving")
        self.lbUnitOfConveyorMoving.setEnabled(False)
        self.lbUnitOfConveyorMoving.setFont(font4)

        self.gridLayout_7.addWidget(self.lbUnitOfConveyorMoving, 2, 2, 1, 1)

        self.label_57 = QLabel(self.ConveyorTab)
        self.label_57.setObjectName(u"label_57")
        self.label_57.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_57, 3, 0, 1, 1)

        self.lbSpeedOfPositionMode = QLabel(self.ConveyorTab)
        self.lbSpeedOfPositionMode.setObjectName(u"lbSpeedOfPositionMode")
        self.lbSpeedOfPositionMode.setEnabled(False)
        self.lbSpeedOfPositionMode.setFont(font4)

        self.gridLayout_7.addWidget(self.lbSpeedOfPositionMode, 3, 2, 1, 1)

        self.leSpeedOfPositionMode = QLineEdit(self.ConveyorTab)
        self.leSpeedOfPositionMode.setObjectName(u"leSpeedOfPositionMode")
        self.leSpeedOfPositionMode.setEnabled(False)
        self.leSpeedOfPositionMode.setMinimumSize(QSize(0, 20))
        self.leSpeedOfPositionMode.setMaximumSize(QSize(200, 16777215))
        self.leSpeedOfPositionMode.setFont(font19)
        self.leSpeedOfPositionMode.setClearButtonEnabled(False)

        self.gridLayout_7.addWidget(self.leSpeedOfPositionMode, 3, 1, 1, 1)


        self.verticalLayout_22.addLayout(self.gridLayout_7)

        self.verticalSpacer_2 = QSpacerItem(20, 304, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_22.addItem(self.verticalSpacer_2)

        self.twDeltaGeometry.addTab(self.ConveyorTab, "")
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
        self.pbSlidingConnect.setFont(font17)
        icon45 = QIcon()
        icon45.addFile(u"icon/connected.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingConnect.setIcon(icon45)

        self.horizontalLayout_49.addWidget(self.pbSlidingConnect)

        self.lbSliderCOMName = QLabel(self.SliderTab1)
        self.lbSliderCOMName.setObjectName(u"lbSliderCOMName")
        self.lbSliderCOMName.setFont(font18)
        self.lbSliderCOMName.setStyleSheet(u"color: rgb(255, 0, 0);")

        self.horizontalLayout_49.addWidget(self.lbSliderCOMName)


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
        self.pbSlidingDisable.setFont(font18)
        icon46 = QIcon()
        icon46.addFile(u"icon/icons8-sleeping-in-bed-32.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingDisable.setIcon(icon46)

        self.gridLayout_8.addWidget(self.pbSlidingDisable, 0, 1, 1, 1)

        self.label_58 = QLabel(self.SliderTab1)
        self.label_58.setObjectName(u"label_58")
        self.label_58.setFont(font4)

        self.gridLayout_8.addWidget(self.label_58, 2, 2, 1, 1)

        self.label_37 = QLabel(self.SliderTab1)
        self.label_37.setObjectName(u"label_37")
        self.label_37.setFont(font4)
        self.label_37.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_8.addWidget(self.label_37, 3, 0, 1, 1)

        self.pbSlidingHome = QPushButton(self.SliderTab1)
        self.pbSlidingHome.setObjectName(u"pbSlidingHome")
        self.pbSlidingHome.setMinimumSize(QSize(0, 30))
        self.pbSlidingHome.setMaximumSize(QSize(200, 40))
        self.pbSlidingHome.setFont(font18)
        icon47 = QIcon()
        icon47.addFile(u"icon/icons8-home-32.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingHome.setIcon(icon47)

        self.gridLayout_8.addWidget(self.pbSlidingHome, 1, 1, 1, 1)

        self.leSlidingSpeed = QLineEdit(self.SliderTab1)
        self.leSlidingSpeed.setObjectName(u"leSlidingSpeed")
        self.leSlidingSpeed.setMinimumSize(QSize(0, 30))
        self.leSlidingSpeed.setMaximumSize(QSize(200, 40))

        self.gridLayout_8.addWidget(self.leSlidingSpeed, 2, 1, 1, 1)

        self.label_36 = QLabel(self.SliderTab1)
        self.label_36.setObjectName(u"label_36")
        self.label_36.setFont(font4)
        self.label_36.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_8.addWidget(self.label_36, 2, 0, 1, 1)

        self.label_59 = QLabel(self.SliderTab1)
        self.label_59.setObjectName(u"label_59")
        self.label_59.setFont(font4)

        self.gridLayout_8.addWidget(self.label_59, 3, 2, 1, 1)


        self.verticalLayout_23.addLayout(self.gridLayout_8)

        self.verticalSpacer_3 = QSpacerItem(20, 296, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_23.addItem(self.verticalSpacer_3)

        self.twDeltaGeometry.addTab(self.SliderTab1, "")
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
        font20 = QFont()
        font20.setPointSize(12)
        font20.setBold(False)
        font20.setKerning(True)
        self.pbExternalControllerConnect.setFont(font20)

        self.horizontalLayout_50.addWidget(self.pbExternalControllerConnect)

        self.lbExternalCOMName = QLabel(self.widget1)
        self.lbExternalCOMName.setObjectName(u"lbExternalCOMName")
        self.lbExternalCOMName.setMaximumSize(QSize(16777215, 30))
        self.lbExternalCOMName.setFont(font18)
        self.lbExternalCOMName.setStyleSheet(u"color: rgb(255, 0, 0);")

        self.horizontalLayout_50.addWidget(self.lbExternalCOMName)


        self.verticalLayout_24.addWidget(self.widget1)

        self.teReceiveFromMCU = QTextEdit(self.MCUTab)
        self.teReceiveFromMCU.setObjectName(u"teReceiveFromMCU")

        self.verticalLayout_24.addWidget(self.teReceiveFromMCU)

        self.leTransmitToMCU = QLineEdit(self.MCUTab)
        self.leTransmitToMCU.setObjectName(u"leTransmitToMCU")
        self.leTransmitToMCU.setMinimumSize(QSize(0, 30))

        self.verticalLayout_24.addWidget(self.leTransmitToMCU)

        self.twDeltaGeometry.addTab(self.MCUTab, "")
        self.PlusDeviceTab = QWidget()
        self.PlusDeviceTab.setObjectName(u"PlusDeviceTab")
        self.twDeltaGeometry.addTab(self.PlusDeviceTab, "")

        self.GeometryTabManagerLayout.addWidget(self.twDeltaGeometry)

        self.splitter_2.addWidget(self.GeometryTabManagerWidget)

        self.verticalLayout_46.addWidget(self.splitter_2)


        self.verticalLayout_15.addWidget(self.tabManagerLayout)

        RobotWindow.setCentralWidget(self.centralWidget)
        self.mbRobot = QMenuBar(RobotWindow)
        self.mbRobot.setObjectName(u"mbRobot")
        self.mbRobot.setGeometry(QRect(0, 0, 1210, 21))
        self.mbRobot.setLayoutDirection(Qt.RightToLeft)
        self.mbRobot.setStyleSheet(u"QMenuBar\n"
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
"")
        self.mbRobot.setDefaultUp(False)
        self.mbRobot.setNativeMenuBar(True)
        self.menuHelp = QMenu(self.mbRobot)
        self.menuHelp.setObjectName(u"menuHelp")
        self.menuHelp.setLayoutDirection(Qt.RightToLeft)
        self.menuReferences = QMenu(self.menuHelp)
        self.menuReferences.setObjectName(u"menuReferences")
        self.menuEditor = QMenu(self.mbRobot)
        self.menuEditor.setObjectName(u"menuEditor")
        self.menuEditor.setLayoutDirection(Qt.RightToLeft)
        self.menuExecute = QMenu(self.menuEditor)
        self.menuExecute.setObjectName(u"menuExecute")
        self.menuSetting = QMenu(self.mbRobot)
        self.menuSetting.setObjectName(u"menuSetting")
        self.menuSetting.setLayoutDirection(Qt.RightToLeft)
        self.menuSetting.setStyleSheet(u"")
        self.menuConnection = QMenu(self.menuSetting)
        self.menuConnection.setObjectName(u"menuConnection")
        self.menuUI = QMenu(self.menuSetting)
        self.menuUI.setObjectName(u"menuUI")
        RobotWindow.setMenuBar(self.mbRobot)

        self.mbRobot.addAction(self.menuSetting.menuAction())
        self.mbRobot.addAction(self.menuEditor.menuAction())
        self.mbRobot.addAction(self.menuHelp.menuAction())
        self.menuHelp.addAction(self.menuReferences.menuAction())
        self.menuHelp.addAction(self.actionAbout)
        self.menuReferences.addAction(self.actionGcode)
        self.menuReferences.addAction(self.actionSoftware)
        self.menuEditor.addSeparator()
        self.menuEditor.addAction(self.menuExecute.menuAction())
        self.menuExecute.addAction(self.actionExecute)
        self.menuExecute.addAction(self.actionExecute_All)
        self.menuExecute.addSeparator()
        self.menuSetting.addAction(self.menuConnection.menuAction())
        self.menuSetting.addAction(self.menuUI.menuAction())
        self.menuConnection.addAction(self.actionBaudrate)
        self.menuUI.addAction(self.actionScale)

        self.retranslateUi(RobotWindow)
        self.gbConveyorForTracking.toggled.connect(self.fTracking.setVisible)
        self.cbLockGcodeEditor.toggled.connect(self.pbExecuteGcodes.setDisabled)
        self.pbLoadCamera.clicked["bool"].connect(self.pbPlayPauseCamera.setEnabled)
        self.pbLoadCamera.clicked["bool"].connect(self.pbCaptureCamera.setEnabled)
        self.pbCalibStep2.toggled.connect(self.fCalibStep2.setVisible)
        self.gbCameraCalibration.toggled.connect(self.fCameraCalibrationFrame.setVisible)
        self.gbCameraObject.toggled.connect(self.fVisionObjectFrame.setVisible)
        self.gbCameraVariable.toggled.connect(self.fVisionVariableFrame.setVisible)
        self.gbImageProvider.toggled.connect(self.fImageProvider.setVisible)
        self.pbCalibStep1.toggled.connect(self.fCalibStep1.setVisible)
        self.pbTransformPerspective.clicked.connect(self.pbWarpTool.toggle)
        self.pbWarpTool.clicked.connect(self.pbTransformPerspective.toggle)

        self.twDeltaManager.setCurrentIndex(1)
        self.twModule.setCurrentIndex(3)
        self.tabWidget.setCurrentIndex(0)
        self.pbExDeleteProgram.setDefault(True)
        self.pbTransformPerspective.setDefault(False)
        self.pbImageMapping.setDefault(False)
        self.cbImageSource.setCurrentIndex(0)
        self.twDeltaGeometry.setCurrentIndex(0)
        self.RobotTabWidget.setCurrentIndex(0)
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
#if QT_CONFIG(tooltip)
        self.twModule.setToolTip("")
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        self.pbExecuteGcodes.setToolTip(QCoreApplication.translate("RobotWindow", u"Execute Gcode", None))
#endif // QT_CONFIG(tooltip)
        self.pbExecuteGcodes.setText(QCoreApplication.translate("RobotWindow", u"Run", None))
        self.rbEditorCurrent.setText(QCoreApplication.translate("RobotWindow", u"Current", None))
        self.rbEditorStart.setText(QCoreApplication.translate("RobotWindow", u"Begin", None))
        self.cbLockGcodeEditor.setText(QCoreApplication.translate("RobotWindow", u"Block Editor", None))
#if QT_CONFIG(tooltip)
        self.pbFormat.setToolTip(QCoreApplication.translate("RobotWindow", u"Format Gcode Lines", None))
#endif // QT_CONFIG(tooltip)
        self.pbFormat.setText(QCoreApplication.translate("RobotWindow", u"Format", None))
        self.cbFormatColor.setText(QCoreApplication.translate("RobotWindow", u"Color", None))
        self.cbAutoNumbering.setText(QCoreApplication.translate("RobotWindow", u"Auto Numbering", None))
        self.lbGcodeProgramingIssues.setText("")
#if QT_CONFIG(tooltip)
        self.pbSaveGcode.setToolTip(QCoreApplication.translate("RobotWindow", u"Save Gcode Into File", None))
#endif // QT_CONFIG(tooltip)
        self.pbSaveGcode.setText("")
        self.pteGcodeArea.setHtml(QCoreApplication.translate("RobotWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#000000;\">N05</span><span style=\" font-family:'MS Shell Dlg 2';\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G28</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-weight:600;\"><"
                        "br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Acceleration</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N10 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">M204</span><span style=\" font-family:'MS Shell Dlg 2';\"> A1200</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Speed</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N15 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weig"
                        "ht:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> F200</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Declare variables</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N20 </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> = 0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N30 </span><span st"
                        "yle=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> = </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> + 1</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#55aa00;\">;Call subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N35 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">M98</span><span style=\" font-family:'MS Shell Dlg 2';\"> P2000</span></p>\n"
"<p style"
                        "=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">; Begin subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N40 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">O2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS"
                        " Shell Dlg 2';\">N45 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-350</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N50 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> X-100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N55 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-370</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-"
                        "top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N60 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-350</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N65 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> X100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N70 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G01</span><span style=\" font-family:'MS Shell Dlg 2';\"> Z-370</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0p"
                        "x; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N75 M99</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;End subprogram</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Loop 5 times</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N80 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#00aa00;\">"
                        "IF</span><span style=\" font-family:'MS Shell Dlg 2';\"> [</span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic;\">#100</span><span style=\" font-family:'MS Shell Dlg 2';\"> LE 5] </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#00aa00;\">THEN</span><span style=\" font-family:'MS Shell Dlg 2';\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#ff5500;\">GOTO</span><span style=\" font-family:'MS Shell Dlg 2';\"> 30</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\">N85 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; marg"
                        "in-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\"> </span></p></body></html>", None))
        self.leExProgramName.setText(QCoreApplication.translate("RobotWindow", u"Program 1", None))
        self.pbExDeleteProgram.setText("")
        self.lbExGCodeNumber.setText(QCoreApplication.translate("RobotWindow", u"100 Gcode Lines", None))
#if QT_CONFIG(tooltip)
        self.pbUploadProgram.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbUploadProgram.setText("")
#if QT_CONFIG(tooltip)
        self.pbImportGcodeFiles.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbImportGcodeFiles.setText(QCoreApplication.translate("RobotWindow", u"Import", None))
#if QT_CONFIG(tooltip)
        self.pbAddNewProgram.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbAddNewProgram.setText(QCoreApplication.translate("RobotWindow", u"New ", None))
#if QT_CONFIG(tooltip)
        self.pbRefreshGcodeFiles.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbRefreshGcodeFiles.setText(QCoreApplication.translate("RobotWindow", u"F5   ", None))
#if QT_CONFIG(tooltip)
        self.pbFindGcodeFile.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbFindGcodeFile.setText(QCoreApplication.translate("RobotWindow", u"Find", None))
#if QT_CONFIG(tooltip)
        self.pbSortGcodeFiles.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbSortGcodeFiles.setText(QCoreApplication.translate("RobotWindow", u"Sort", None))
        self.lbExGCodeNumber_2.setText(QCoreApplication.translate("RobotWindow", u"Path", None))
        self.leGcodeProgramPath.setText(QCoreApplication.translate("RobotWindow", u"/gcode", None))
        self.pbOpenGcodeProgramPath.setText("")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), QCoreApplication.translate("RobotWindow", u"Offline", None))
        self.textEdit.setHtml(QCoreApplication.translate("RobotWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt;\">Author:</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-size:7.8pt;\">Description:</span></p></body></html>", None))
#if QT_CONFIG(tooltip)
        self.pbUploadProgram_2.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbUploadProgram_2.setText("")
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_3), QCoreApplication.translate("RobotWindow", u"Online", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tGcodeEditor), QCoreApplication.translate("RobotWindow", u"Gcode Editor", None))
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

        self.lbDisplayRatio.setText(QCoreApplication.translate("RobotWindow", u"Ratio: 100%", None))
        self.lbMatSize.setText(QCoreApplication.translate("RobotWindow", u"Re: 800x500", None))
        self.gbImageProvider.setTitle(QCoreApplication.translate("RobotWindow", u"Image Provider", None))
        self.label_176.setText(QCoreApplication.translate("RobotWindow", u"Source", None))
        self.cbSourceForImageProvider.setItemText(0, QCoreApplication.translate("RobotWindow", u"Webcam", None))
        self.cbSourceForImageProvider.setItemText(1, QCoreApplication.translate("RobotWindow", u"Images", None))
        self.cbSourceForImageProvider.setItemText(2, QCoreApplication.translate("RobotWindow", u"Plugin", None))
        self.cbSourceForImageProvider.setItemText(3, QCoreApplication.translate("RobotWindow", u"Socket", None))

#if QT_CONFIG(tooltip)
        self.pbLoadCamera.setToolTip(QCoreApplication.translate("RobotWindow", u"Load Camera", None))
#endif // QT_CONFIG(tooltip)
        self.pbLoadCamera.setText(QCoreApplication.translate("RobotWindow", u"Load Camera", None))
        self.label_11.setText(QCoreApplication.translate("RobotWindow", u"FPS", None))
        self.leFPS.setText(QCoreApplication.translate("RobotWindow", u"5", None))
        self.label_124.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.leCameraWidth.setText(QCoreApplication.translate("RobotWindow", u"800", None))
        self.label_125.setText(QCoreApplication.translate("RobotWindow", u"H", None))
        self.leCameraHeight.setText(QCoreApplication.translate("RobotWindow", u"500", None))
#if QT_CONFIG(tooltip)
        self.pbPlayPauseCamera.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Play and Pause</p><p>M98 PpauseCamera</p><p>M98 PresumeCamera</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.pbPlayPauseCamera.setText("")
#if QT_CONFIG(tooltip)
        self.pbCaptureCamera.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Capture</p><p>M98 PcaptureCamera</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.pbCaptureCamera.setText("")
        self.lbCameraState.setText("")
#if QT_CONFIG(tooltip)
        self.pbLoadTestImage.setToolTip(QCoreApplication.translate("RobotWindow", u"Load Image", None))
#endif // QT_CONFIG(tooltip)
        self.pbLoadTestImage.setText(QCoreApplication.translate("RobotWindow", u"Load Image", None))
        self.cbExternalImageSource.setText(QCoreApplication.translate("RobotWindow", u"Enough", None))
        self.label_177.setText(QCoreApplication.translate("RobotWindow", u"plugin", None))
        self.comboBox_2.setItemText(0, QCoreApplication.translate("RobotWindow", u"IndustryCamera", None))

        self.label_178.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.leImageWidth.setText(QCoreApplication.translate("RobotWindow", u"800", None))
        self.label_179.setText(QCoreApplication.translate("RobotWindow", u"H", None))
        self.leImageHeight.setText(QCoreApplication.translate("RobotWindow", u"500", None))
        self.gbCameraCalibration.setTitle(QCoreApplication.translate("RobotWindow", u"Calibration", None))
        self.pbCalibStep1.setText(QCoreApplication.translate("RobotWindow", u"Step 1: Find the 4 points of the square", None))
        self.leChessWidth.setText(QCoreApplication.translate("RobotWindow", u"7", None))
        self.leChessHeight.setText(QCoreApplication.translate("RobotWindow", u"7", None))
        self.label_109.setText(QCoreApplication.translate("RobotWindow", u"Chessboard", None))
#if QT_CONFIG(tooltip)
        self.pbTransformPerspective.setToolTip(QCoreApplication.translate("RobotWindow", u"Perspective Transformation", None))
#endif // QT_CONFIG(tooltip)
        self.pbTransformPerspective.setText(QCoreApplication.translate("RobotWindow", u"Warp Perspective", None))
        self.label_110.setText(QCoreApplication.translate("RobotWindow", u"Dimension", None))
        self.pbFindChessboard.setText(QCoreApplication.translate("RobotWindow", u"Find chessboard", None))
        self.pbCalibStep2.setText(QCoreApplication.translate("RobotWindow", u"Step 2: Coordinate correction", None))
#if QT_CONFIG(tooltip)
        self.pbImageMapping.setToolTip(QCoreApplication.translate("RobotWindow", u"Perspective Transformation", None))
#endif // QT_CONFIG(tooltip)
        self.pbImageMapping.setText(QCoreApplication.translate("RobotWindow", u"Calculate Mapping Matrix", None))
        self.label_39.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.leRealityPoint2Y.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.leRealityPoint1Y.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_133.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_140.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
#if QT_CONFIG(tooltip)
        self.pbObjectOrigin.setToolTip(QCoreApplication.translate("RobotWindow", u"Set a calibrating point", None))
#endif // QT_CONFIG(tooltip)
        self.pbObjectOrigin.setText(QCoreApplication.translate("RobotWindow", u"Point Tool", None))
        self.label_38.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.leRealityPoint1X.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_132.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.leRealityPoint2X.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.label_139.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.cbMoveOnConveyor1.setText(QCoreApplication.translate("RobotWindow", u"Sync with conveyor", None))
        self.pbCalibPoint1.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
#if QT_CONFIG(shortcut)
        self.pbCalibPoint1.setShortcut(QCoreApplication.translate("RobotWindow", u"!", None))
#endif // QT_CONFIG(shortcut)
        self.pbCalibPoint2.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
#if QT_CONFIG(shortcut)
        self.pbCalibPoint2.setShortcut(QCoreApplication.translate("RobotWindow", u"@", None))
#endif // QT_CONFIG(shortcut)
        self.gbCameraObject.setTitle(QCoreApplication.translate("RobotWindow", u"Object", None))
        self.cbObjectType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Type 1", None))

        self.pushButton.setText(QCoreApplication.translate("RobotWindow", u"+", None))
        self.pushButton_2.setText(QCoreApplication.translate("RobotWindow", u"-", None))
        self.label_126.setText(QCoreApplication.translate("RobotWindow", u"Detection algorithm", None))
        self.cbDetectingAlgorithm.setItemText(0, QCoreApplication.translate("RobotWindow", u"Find Blobs", None))
        self.cbDetectingAlgorithm.setItemText(1, QCoreApplication.translate("RobotWindow", u"Find Circles", None))
        self.cbDetectingAlgorithm.setItemText(2, QCoreApplication.translate("RobotWindow", u"External Script", None))

        self.label_172.setText(QCoreApplication.translate("RobotWindow", u"Min", None))
        self.leMaxWRec.setText(QCoreApplication.translate("RobotWindow", u"25", None))
        self.leMaxLRec.setText(QCoreApplication.translate("RobotWindow", u"25", None))
        self.label_55.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.leWRec.setText(QCoreApplication.translate("RobotWindow", u"20", None))
#if QT_CONFIG(tooltip)
        self.pbObjectRect.setToolTip(QCoreApplication.translate("RobotWindow", u"Bound the object size", None))
#endif // QT_CONFIG(tooltip)
        self.pbObjectRect.setText(QCoreApplication.translate("RobotWindow", u"Get Size Tool", None))
        self.label_56.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_44.setText(QCoreApplication.translate("RobotWindow", u"Height", None))
        self.leMinLRec.setText(QCoreApplication.translate("RobotWindow", u"15", None))
        self.leLRec.setText(QCoreApplication.translate("RobotWindow", u"20", None))
#if QT_CONFIG(tooltip)
        self.pbFilter.setToolTip(QCoreApplication.translate("RobotWindow", u"Camera Filter", None))
#endif // QT_CONFIG(tooltip)
        self.pbFilter.setText(QCoreApplication.translate("RobotWindow", u"Color Filter Panel", None))
        self.label_43.setText(QCoreApplication.translate("RobotWindow", u"Length", None))
        self.label_173.setText(QCoreApplication.translate("RobotWindow", u"Max", None))
        self.leHRec.setText(QCoreApplication.translate("RobotWindow", u"20", None))
        self.label_54.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_174.setText(QCoreApplication.translate("RobotWindow", u"Min", None))
        self.label_42.setText(QCoreApplication.translate("RobotWindow", u"Width", None))
        self.leMinWRec.setText(QCoreApplication.translate("RobotWindow", u"15", None))
        self.lbTrackingObject.setText("")
        self.label_175.setText(QCoreApplication.translate("RobotWindow", u"Max", None))
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
        self.lePythonUrl.setText(QCoreApplication.translate("RobotWindow", u"detect.py", None))
        self.pushButton_3.setText(QCoreApplication.translate("RobotWindow", u"Open script example", None))
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
        self.pbViewDataObjects.setText(QCoreApplication.translate("RobotWindow", u"Object Table", None))
#if QT_CONFIG(tooltip)
        self.pbClearDetectObjects.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Clear All Objects in Memory</p><p>M98 PclearObjects --&gt; Clear All</p><p>M98 PdeleteFirstObject --&gt; Delete First</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbClearDetectObjects.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbClearDetectObjects.setText(QCoreApplication.translate("RobotWindow", u"Clear Objects", None))
        self.label_50.setText(QCoreApplication.translate("RobotWindow", u"Visible", None))
        self.lbVisibleObjectNumber.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbTrackingObjectNumber.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_48.setText(QCoreApplication.translate("RobotWindow", u"Tracking", None))
        self.label_155.setText("")
        self.label_156.setText("")
        self.label_157.setText("")
        self.label_158.setText("")
        self.label_159.setText("")
        self.gbConveyorForTracking.setTitle(QCoreApplication.translate("RobotWindow", u"Tracking", None))
        self.label_150.setText(QCoreApplication.translate("RobotWindow", u"Object", None))
        self.label_152.setText(QCoreApplication.translate("RobotWindow", u"%", None))
        self.label_151.setText(QCoreApplication.translate("RobotWindow", u"Tracking error", None))
        self.leTrackingError.setText(QCoreApplication.translate("RobotWindow", u"0.3", None))
        self.label_127.setText(QCoreApplication.translate("RobotWindow", u"Conveyor", None))
        self.leConvenyorSpeed.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.pbReadProximitySensor.setText(QCoreApplication.translate("RobotWindow", u"Read", None))
        self.pbBackwardConveyor.setText(QCoreApplication.translate("RobotWindow", u"Backward", None))
        self.pbResetEncoderPosition.setText(QCoreApplication.translate("RobotWindow", u"Reset", None))
        self.label_189.setText(QCoreApplication.translate("RobotWindow", u"Sensor", None))
        self.leForwardConveyorGcode.setText(QCoreApplication.translate("RobotWindow", u"M03 D0", None))
        self.leTurnOffConveyorGcode.setText(QCoreApplication.translate("RobotWindow", u"M05 D0, M05 D1", None))
        self.rbEncoderEnable.setText(QCoreApplication.translate("RobotWindow", u"Use Encoder", None))
        self.label_148.setText(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Deviation angle </p><p><span style=\" font-weight:400; font-style:italic;\">X Axis</span></p></body></html>", None))
        self.label_191.setText(QCoreApplication.translate("RobotWindow", u"Proximity sensor", None))
        self.leBackwardConveyorGcode.setText(QCoreApplication.translate("RobotWindow", u"M03 D1", None))
        self.label_45.setText(QCoreApplication.translate("RobotWindow", u"Constant Velocity", None))
        self.label_163.setText(QCoreApplication.translate("RobotWindow", u"Gcode Setting", None))
        self.lbProximitySensorValue.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.leEncoderCom.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.pbTurnOffConveyor.setText(QCoreApplication.translate("RobotWindow", u"Turn off", None))
        self.label_121.setText(QCoreApplication.translate("RobotWindow", u"(mm/s)", None))
        self.label_162.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.leConveyorDeviationAngle.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.pbConnectEncdoer.setText(QCoreApplication.translate("RobotWindow", u"Connect Encoder", None))
        self.label_161.setText(QCoreApplication.translate("RobotWindow", u"Move", None))
        self.cbEncoderPositionInverse.setText(QCoreApplication.translate("RobotWindow", u"Inverse", None))
        self.label_49.setText(QCoreApplication.translate("RobotWindow", u"(mm/s)", None))
        self.label_160.setText(QCoreApplication.translate("RobotWindow", u"Control", None))
        self.label_119.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.rbVirtualEncoderEnable.setText(QCoreApplication.translate("RobotWindow", u"Use Virtual Encoder", None))
        self.label_118.setText(QCoreApplication.translate("RobotWindow", u"Current Position", None))
        self.pbForwardConveyor.setText(QCoreApplication.translate("RobotWindow", u"Forward", None))
        self.cbConveyorDirectionControl.setItemText(0, QCoreApplication.translate("RobotWindow", u"Forward", None))
        self.cbConveyorDirectionControl.setItemText(1, QCoreApplication.translate("RobotWindow", u"Backward", None))

        self.label_120.setText(QCoreApplication.translate("RobotWindow", u"Current Velocity", None))
        self.cbAutoReadProximitySensor.setText(QCoreApplication.translate("RobotWindow", u"Auto", None))
        self.label_170.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.leConveyorPoint2X.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.pbCalibConveyorAngle.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.leConveyorPoint1X.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_197.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.label_199.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.leConveyorPoint1Y.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_198.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.leConveyorPoint2Y.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.pbGetConveyorPoint1X.setText(QCoreApplication.translate("RobotWindow", u"X1", None))
        self.pbGetConveyorPoint1Y.setText(QCoreApplication.translate("RobotWindow", u"Y1", None))
        self.pbGetConveyorPoint2X.setText(QCoreApplication.translate("RobotWindow", u"X2", None))
        self.pbGetConveyorPoint2Y.setText(QCoreApplication.translate("RobotWindow", u"Y2", None))
        self.label_196.setText(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Calib Points</p></body></html>", None))
        self.label_149.setText(QCoreApplication.translate("RobotWindow", u"(deg)", None))
        self.leConveyorPoint3X.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.leConveyorPoint3Y.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_169.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_168.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_171.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.label_167.setText(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Test Object</p></body></html>", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tObjectDetecting), QCoreApplication.translate("RobotWindow", u"Object Detecting", None))
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
        self.cbDeviceSender.setItemText(0, QCoreApplication.translate("RobotWindow", u"Robot", None))
        self.cbDeviceSender.setItemText(1, QCoreApplication.translate("RobotWindow", u"Conveyor", None))
        self.cbDeviceSender.setItemText(2, QCoreApplication.translate("RobotWindow", u"Slider", None))
        self.cbDeviceSender.setItemText(3, QCoreApplication.translate("RobotWindow", u"External MCU", None))
        self.cbDeviceSender.setItemText(4, QCoreApplication.translate("RobotWindow", u"Encoder", None))

        self.twModule.setTabText(self.twModule.indexOf(self.TermiteTab), QCoreApplication.translate("RobotWindow", u"Termite", None))
        self.lbW.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_94.setText(QCoreApplication.translate("RobotWindow", u"V", None))
        self.label_88.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.lbU.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_92.setText(QCoreApplication.translate("RobotWindow", u"U", None))
        self.lbY.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbZ.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbV.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_90.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.label_86.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.lbX.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_84.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.pbConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.cbAutoConnect.setText(QCoreApplication.translate("RobotWindow", u"Auto", None))
        self.label_65.setText(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.lbID.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbComName.setText(QCoreApplication.translate("RobotWindow", u"NONE", None))
        self.lbBaudrate.setText(QCoreApplication.translate("RobotWindow", u"115200", None))
        self.lbIP.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.label_91.setText(QCoreApplication.translate("RobotWindow", u"Model", None))
        self.cbRobotModel.setItemText(0, QCoreApplication.translate("RobotWindow", u"Delta X 1", None))
        self.cbRobotModel.setItemText(1, QCoreApplication.translate("RobotWindow", u"Delta X 2", None))
        self.cbRobotModel.setItemText(2, QCoreApplication.translate("RobotWindow", u"Delta X S", None))
        self.cbRobotModel.setItemText(3, QCoreApplication.translate("RobotWindow", u"Custom", None))

        self.label_6.setText(QCoreApplication.translate("RobotWindow", u"ID", None))
        self.label_10.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.label_122.setText(QCoreApplication.translate("RobotWindow", u"IP", None))
        self.label_123.setText(QCoreApplication.translate("RobotWindow", u"Port", None))
        self.lbLocalPort.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.label_113.setText(QCoreApplication.translate("RobotWindow", u"DOF", None))
        self.cbRobotModel_2.setItemText(0, QCoreApplication.translate("RobotWindow", u"3 DOF", None))
        self.cbRobotModel_2.setItemText(1, QCoreApplication.translate("RobotWindow", u"4 DOF", None))
        self.cbRobotModel_2.setItemText(2, QCoreApplication.translate("RobotWindow", u"5 DOF", None))
        self.cbRobotModel_2.setItemText(3, QCoreApplication.translate("RobotWindow", u"6 DOF", None))

        self.RobotTabWidget.setTabText(self.RobotTabWidget.indexOf(self.InstallationTab), QCoreApplication.translate("RobotWindow", u"Installation", None))
        self.label_28.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.cbDivision.setItemText(0, QCoreApplication.translate("RobotWindow", u"0.5", None))
        self.cbDivision.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbDivision.setItemText(2, QCoreApplication.translate("RobotWindow", u"5", None))
        self.cbDivision.setItemText(3, QCoreApplication.translate("RobotWindow", u"10", None))
        self.cbDivision.setItemText(4, QCoreApplication.translate("RobotWindow", u"50", None))
        self.cbDivision.setItemText(5, QCoreApplication.translate("RobotWindow", u"100", None))

        self.cbDivision.setCurrentText(QCoreApplication.translate("RobotWindow", u"1", None))
        self.pbHome.setText(QCoreApplication.translate("RobotWindow", u"Home", None))
        self.label_33.setText(QCoreApplication.translate("RobotWindow", u"Step", None))
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
        self.label_60.setText(QCoreApplication.translate("RobotWindow", u"5-Axis", None))
        self.label_61.setText(QCoreApplication.translate("RobotWindow", u"6-Axis", None))
        self.label_16.setText(QCoreApplication.translate("RobotWindow", u"4-Axis", None))
        self.lb4AxisValue.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lb5AxisValue.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lb6AxisValue.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.SliderTab), QCoreApplication.translate("RobotWindow", u"Slider", None))
        self.label_79.setText(QCoreApplication.translate("RobotWindow", u"Sensibility", None))
        self.cbJoystickDevice.setCurrentText("")
        self.label_41.setText(QCoreApplication.translate("RobotWindow", u"Device", None))
        self.leJoystickRange.setText(QCoreApplication.translate("RobotWindow", u"1", None))
        self.leJoystickSensibility.setText(QCoreApplication.translate("RobotWindow", u"0.7", None))
        self.label_51.setText(QCoreApplication.translate("RobotWindow", u"Range", None))
        self.tabWidget_2.setTabText(self.tabWidget_2.indexOf(self.tab_2), QCoreApplication.translate("RobotWindow", u"Joystick", None))
        self.RobotTabWidget.setTabText(self.RobotTabWidget.indexOf(self.MoveTab), QCoreApplication.translate("RobotWindow", u"Move", None))
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
        self.gbOutput.setTitle(QCoreApplication.translate("RobotWindow", u"Output", None))
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
        self.gbInput.setTitle(QCoreApplication.translate("RobotWindow", u"Input", None))
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
        self.label_80.setText(QCoreApplication.translate("RobotWindow", u"I4", None))
        self.lbI4Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle4.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle4.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI4.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_82.setText(QCoreApplication.translate("RobotWindow", u"I5", None))
        self.lbI5Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle5.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle5.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI5.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.leIx.setText(QCoreApplication.translate("RobotWindow", u"I6", None))
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
        self.label_30.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_63.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.leEndSpeed.setText("")
        self.leEndSpeed.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_32.setText(QCoreApplication.translate("RobotWindow", u"mm/s2", None))
        self.label_62.setText(QCoreApplication.translate("RobotWindow", u"Start", None))
        self.label_116.setText(QCoreApplication.translate("RobotWindow", u"End", None))
        self.leAccel.setText("")
        self.leAccel.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.leStartSpeed.setText("")
        self.leStartSpeed.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_29.setText(QCoreApplication.translate("RobotWindow", u"Velocity", None))
        self.leVelocity.setText("")
        self.leVelocity.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_31.setText(QCoreApplication.translate("RobotWindow", u"Accel", None))
        self.label_117.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_47.setText(QCoreApplication.translate("RobotWindow", u"Jerk", None))
        self.leEndSpeed_2.setText("")
        self.leEndSpeed_2.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_64.setText(QCoreApplication.translate("RobotWindow", u"mm/s3", None))
        self.RobotTabWidget.setTabText(self.RobotTabWidget.indexOf(self.ParameterTab), QCoreApplication.translate("RobotWindow", u"Parameter", None))
        self.twDeltaGeometry.setTabText(self.twDeltaGeometry.indexOf(self.tRobot), QCoreApplication.translate("RobotWindow", u"Robot", None))
        self.twDeltaGeometry.setTabText(self.twDeltaGeometry.indexOf(self.EncoderTab), QCoreApplication.translate("RobotWindow", u"Encoder", None))
        self.pbConveyorConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.lbConveyorCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.label_46.setText(QCoreApplication.translate("RobotWindow", u"Moving Mode", None))
        self.cbConveyorValueType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Speed", None))
        self.cbConveyorValueType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Position", None))

        self.label_52.setText(QCoreApplication.translate("RobotWindow", u"Control Mode", None))
        self.cbConveyorMode.setItemText(0, QCoreApplication.translate("RobotWindow", u"Manual", None))
        self.cbConveyorMode.setItemText(1, QCoreApplication.translate("RobotWindow", u"UART", None))

#if QT_CONFIG(tooltip)
        self.cbConveyorMode.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"31\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">310 \u2013 Set Mode</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description: .</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI"
                        " Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M310 [&lt;index&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">1: Serial Mode.</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">0: Volume Mode.</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.label_12.setText(QCoreApplication.translate("RobotWindow", u"Value of Moving", None))
#if QT_CONFIG(tooltip)
        self.leConveyorvMovingValue.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \u2013 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI "
                        "Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFon"
                        "t','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color"
                        ":#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.leConveyorvMovingValue.setText(QCoreApplication.translate("RobotWindow", u"-100", None))
        self.lbUnitOfConveyorMoving.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_57.setText(QCoreApplication.translate("RobotWindow", u"Velocity in Position Mode", None))
        self.lbSpeedOfPositionMode.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
#if QT_CONFIG(tooltip)
        self.leSpeedOfPositionMode.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leSpeedOfPositionMode.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.twDeltaGeometry.setTabText(self.twDeltaGeometry.indexOf(self.ConveyorTab), QCoreApplication.translate("RobotWindow", u"Conveyor", None))
        self.pbSlidingConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
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
        self.twDeltaGeometry.setTabText(self.twDeltaGeometry.indexOf(self.SliderTab1), QCoreApplication.translate("RobotWindow", u"Slider", None))
#if QT_CONFIG(tooltip)
        self.pbExternalControllerConnect.setToolTip(QCoreApplication.translate("RobotWindow", u"Connect External Controller", None))
#endif // QT_CONFIG(tooltip)
        self.pbExternalControllerConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.lbExternalCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.leTransmitToMCU.setText("")
        self.leTransmitToMCU.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"Transmit to MCU", None))
        self.twDeltaGeometry.setTabText(self.twDeltaGeometry.indexOf(self.MCUTab), QCoreApplication.translate("RobotWindow", u"MCU", None))
        self.twDeltaGeometry.setTabText(self.twDeltaGeometry.indexOf(self.PlusDeviceTab), QCoreApplication.translate("RobotWindow", u"+", None))
        self.menuHelp.setTitle(QCoreApplication.translate("RobotWindow", u"Help", None))
        self.menuReferences.setTitle(QCoreApplication.translate("RobotWindow", u"References", None))
        self.menuEditor.setTitle(QCoreApplication.translate("RobotWindow", u"Program", None))
        self.menuExecute.setTitle(QCoreApplication.translate("RobotWindow", u"Execute", None))
        self.menuSetting.setTitle(QCoreApplication.translate("RobotWindow", u"Setting", None))
        self.menuConnection.setTitle(QCoreApplication.translate("RobotWindow", u"Connection", None))
        self.menuUI.setTitle(QCoreApplication.translate("RobotWindow", u"UI", None))
    # retranslateUi

