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
from PySide6.QtWidgets import (QApplication, QCheckBox, QComboBox, QFrame,
    QGridLayout, QGroupBox, QHBoxLayout, QHeaderView,
    QLabel, QLineEdit, QListWidget, QListWidgetItem,
    QMainWindow, QPushButton, QRadioButton, QScrollArea,
    QSizePolicy, QSlider, QSpacerItem, QSplitter,
    QTabWidget, QTableView, QTextEdit, QToolButton,
    QTreeView, QVBoxLayout, QWidget)

from DrawingWidget import DrawingWidget
from codeeditor import CodeEditor
from imageviewer import ImageViewer
import resource_rc

class Ui_RobotWindow(object):
    def setupUi(self, RobotWindow):
        if not RobotWindow.objectName():
            RobotWindow.setObjectName(u"RobotWindow")
        RobotWindow.resize(1210, 780)
        sizePolicy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(RobotWindow.sizePolicy().hasHeightForWidth())
        RobotWindow.setSizePolicy(sizePolicy)
        RobotWindow.setMinimumSize(QSize(0, 0))
        font = QFont()
        font.setBold(False)
        font.setKerning(True)
        RobotWindow.setFont(font)
        icon = QIcon()
        icon.addFile(u"delta_x_logo_96x96.ico", QSize(), QIcon.Normal, QIcon.Off)
        RobotWindow.setWindowIcon(icon)
        RobotWindow.setLayoutDirection(Qt.LeftToRight)
        RobotWindow.setStyleSheet(u"")
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
        self.centralWidget.setStyleSheet(u"QWidget#centralWidget\n"
"{	\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"QTextEdit\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}\n"
"\n"
"/* Global Button*/\n"
"QPushButton {\n"
"    background-color: #4A4A4F;\n"
"    border-radius: 5px;\n"
"    \n"
"	color: rgb(208, 208, 209);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	background-color: rgb(49, 149, 239);\n"
"}\n"
"\n"
"QCheckBox\n"
"{\n"
"	\n"
"	color: rgb(208, 208, 209);\n"
"}\n"
"\n"
"QCheckBox::indicator {\n"
"    height: 25px; \n"
"	width:25px;\n"
"    border: none; \n"
"    image: url(:/icon/icons8_switch_off_52px.png); \n"
"}\n"
"\n"
"QCheckBox::indicator:checked {\n"
"    image: url(:/icon/icons8_switch_on_52px.png); \n"
"}\n"
"\n"
"\n"
"QSlider\n"
"{	\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"    background: white;\n"
"    height: 2px;\n"
"}\n"
"\n"
"QSlider::sub-page:horizontal {\n"
"    background:  #2196F3;\n"
"}\n"
"\n"
""
                        "QSlider::add-page:horizontal {\n"
"    background: #D0D0D1;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"    background: #2196F3;\n"
"    width: 12px;\n"
"    margin-top: -5px;\n"
"    margin-bottom: -5px;\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"\n"
"QComboBox {\n"
"    background-color: #4A4A4F;\n"
"    color: #eaeaea;\n"
"    border: 1px solid #555;\n"
"    border-radius: 3px;\n"
"    selection-background-color: #4a4a4a;\n"
"    selection-color: #eaeaea;\n"
"}\n"
"\n"
"QComboBox::drop-down {\n"
"    width: 30px;\n"
"    border: none;\n"
"}\n"
"\n"
"QComboBox::down-arrow {\n"
"    image: url(:/icon/icons8_expand_arrow_10px.png);\n"
"    width: 16px;\n"
"    height: 16px;\n"
"}\n"
"\n"
"QComboBox QAbstractItemView {\n"
"    color: #eaeaea;\n"
"    background-color: #2a2a2a;\n"
"    selection-color: white;\n"
"    selection-background-color: #4a4a4a;\n"
"    border: 1px solid #555;\n"
"}\n"
"\n"
"QComboBox:hover {\n"
"    border: 1px solid #888;\n"
"}\n"
"\n"
"QComboBox:focus {\n"
"    border: 1px solid #"
                        "0078d4;\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"	color: #D0D0D1;\n"
"	background-color: transparent;\n"
"	border: 1px solid #D0D0D1;\n"
"	border-radius: 5px;\n"
"	padding-left: 10px;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #2196F3;\n"
"}\n"
"\n"
"QScrollArea\n"
"{\n"
"	border: none;\n"
"}\n"
"\n"
"/* VERTICAL SCROLLBAR */\n"
" QScrollBar:vertical {\n"
"	border: none;\n"
"    background: #262629;\n"
"    width: 14px;\n"
"    margin: 15px 0 15px 0;\n"
"	border-radius: 0px;\n"
" }\n"
"\n"
"/*  HANDLE BAR VERTICAL */\n"
"QScrollBar::handle:vertical {	\n"
"	background-color: #333337;\n"
"	min-height: 30px;\n"
"	border-radius: 7px;\n"
"}\n"
"QScrollBar::handle:vertical:hover{	\n"
"	background-color: #2196F3;\n"
"}\n"
"QScrollBar::handle:vertical:pressed {	\n"
"	background-color: #70BBF7;\n"
"}\n"
"\n"
"/* BTN TOP - SCROLLBAR */\n"
"QScrollBar::sub-line:vertical {\n"
"	border: none;\n"
"	background-color: rgb(59, 59, 90);\n"
"	height: 15px;\n"
"	subcontrol-position: top;\n"
"	subcontrol-origin: margin;\n"
""
                        "}\n"
"QScrollBar::sub-line:vertical:hover {	\n"
"	background-color: rgb(255, 0, 127);\n"
"}\n"
"QScrollBar::sub-line:vertical:pressed {	\n"
"	background-color: rgb(185, 0, 92);\n"
"}\n"
"\n"
"/* BTN BOTTOM - SCROLLBAR */\n"
"QScrollBar::add-line:vertical {\n"
"	border: none;\n"
"	background-color: #333337;\n"
"	height: 15px;\n"
"	subcontrol-position: bottom;\n"
"	subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::add-line:vertical:hover {	\n"
"	background-color: rgb(255, 0, 127);\n"
"}\n"
"QScrollBar::add-line:vertical:pressed {	\n"
"	background-color: rgb(185, 0, 92);\n"
"}\n"
"\n"
"/* RESET ARROW */\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
"	background: none;\n"
"}\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"	background: none;\n"
"}\n"
"\n"
"QScrollBar:horizontal {\n"
"	border: none;\n"
"    background: #333337;\n"
" }\n"
"\n"
"/* HORIZONTAL SCROLLBAR */\n"
"QScrollBar:horizontal {\n"
"	border: none;\n"
"    background: #262629;\n"
"    height: 14px;\n"
""
                        "    margin: 0 15px 0 15px;\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"/* HANDLE BAR HORIZONTAL */\n"
"QScrollBar::handle:horizontal {	\n"
"	background-color: #333337;\n"
"	min-width: 30px;\n"
"	border-radius: 7px;\n"
"}\n"
"QScrollBar::handle:horizontal:hover{	\n"
"	background-color: #2196F3;\n"
"}\n"
"QScrollBar::handle:horizontal:pressed {	\n"
"	background-color: #70BBF7;\n"
"}\n"
"\n"
"/* BTN LEFT - SCROLLBAR */\n"
"QScrollBar::sub-line:horizontal {\n"
"	border: none;\n"
"	background-color: rgb(59, 59, 90);\n"
"	width: 15px;\n"
"	subcontrol-position: left;\n"
"	subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::sub-line:horizontal:hover {	\n"
"	background-color: rgb(255, 0, 127);\n"
"}\n"
"QScrollBar::sub-line:horizontal:pressed {	\n"
"	background-color: rgb(185, 0, 92);\n"
"}\n"
"\n"
"/* BTN RIGHT - SCROLLBAR */\n"
"QScrollBar::add-line:horizontal {\n"
"	border: none;\n"
"	background-color: #333337;\n"
"	width: 15px;\n"
"	subcontrol-position: right;\n"
"	subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::add-line"
                        ":horizontal:hover {	\n"
"	background-color: rgb(255, 0, 127);\n"
"}\n"
"QScrollBar::add-line:horizontal:pressed {	\n"
"	background-color: rgb(185, 0, 92);\n"
"}\n"
"\n"
"/* RESET ARROW */\n"
"QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal {\n"
"	background: none;\n"
"}\n"
"QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {\n"
"	background: none;\n"
"}\n"
"\n"
"\n"
"")
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
"    border:  none;\n"
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
        self.frame_11.setMinimumSize(QSize(0, 35))
        self.frame_11.setStyleSheet(u"QFrame\n"
"{\n"
"	padding-left: 5px;\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}\n"
"\n"
"QLabel\n"
"{	\n"
"	color: rgb(208, 208, 209);\n"
"}")
        self.frame_11.setFrameShape(QFrame.StyledPanel)
        self.frame_11.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_34 = QHBoxLayout(self.frame_11)
        self.horizontalLayout_34.setSpacing(10)
        self.horizontalLayout_34.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_34.setObjectName(u"horizontalLayout_34")
        self.horizontalLayout_34.setContentsMargins(0, 5, 0, 5)
        self.horizontalSpacer_26 = QSpacerItem(853, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_34.addItem(self.horizontalSpacer_26)

        self.pbReadI0_3 = QPushButton(self.frame_11)
        self.pbReadI0_3.setObjectName(u"pbReadI0_3")
        sizePolicy2 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Preferred)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.pbReadI0_3.sizePolicy().hasHeightForWidth())
        self.pbReadI0_3.setSizePolicy(sizePolicy2)
        self.pbReadI0_3.setMinimumSize(QSize(50, 0))
        self.pbReadI0_3.setFlat(False)

        self.horizontalLayout_34.addWidget(self.pbReadI0_3)

        self.label_161 = QLabel(self.frame_11)
        self.label_161.setObjectName(u"label_161")
        font2 = QFont()
        font2.setBold(False)
        self.label_161.setFont(font2)
        self.label_161.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_34.addWidget(self.label_161)

        self.leIP = QLineEdit(self.frame_11)
        self.leIP.setObjectName(u"leIP")
        sizePolicy3 = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Preferred)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.leIP.sizePolicy().hasHeightForWidth())
        self.leIP.setSizePolicy(sizePolicy3)
        self.leIP.setMinimumSize(QSize(100, 0))
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
        self.lePort.setMinimumSize(QSize(60, 0))
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
        self.tbServerConfig.setAutoRaise(True)

        self.horizontalLayout_34.addWidget(self.tbServerConfig)


        self.verticalLayout_15.addWidget(self.frame_11)

        self.tabManagerLayout = QWidget(self.centralWidget)
        self.tabManagerLayout.setObjectName(u"tabManagerLayout")
        sizePolicy4 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.tabManagerLayout.sizePolicy().hasHeightForWidth())
        self.tabManagerLayout.setSizePolicy(sizePolicy4)
        self.tabManagerLayout.setMinimumSize(QSize(0, 0))
        self.tabManagerLayout.setStyleSheet(u"QTabWidget::pane { /* The tab widget frame */\n"
"    border: none;\n"
"}\n"
"\n"
"QTabWidget::tab-bar \n"
"{\n"
"\n"
"}\n"
"\n"
"QTabBar::tab \n"
"{\n"
"    background: #3f3f3f;\n"
"	color: #f5f5f5;\n"
"   /* border-radius: 13px;*/\n"
"	border: 1px solid rgb(90, 90, 90);\n"
"    height: 25px;\n"
"    padding: 0px 10px 2px 10px;\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"    background: #007cd6;	\n"
"	color: rgb(255, 255, 255);\n"
"	/*border-radius: 13px;*/\n"
"}\n"
"\n"
"QTabBar::tab:hover {\n"
"    background: #6f6f6f;	\n"
"	color: rgb(255, 255, 255);\n"
"	/*border-radius: 13px;*/\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"\n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
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
"}\n"
"\n"
"")
        self.splitter_2.setOrientation(Qt.Horizontal)
        self.splitter_2.setOpaqueResize(False)
        self.splitter_2.setHandleWidth(20)
        self.ModuleTabManagerWidget = QWidget(self.splitter_2)
        self.ModuleTabManagerWidget.setObjectName(u"ModuleTabManagerWidget")
        self.ModuleTabManagerWidget.setMinimumSize(QSize(0, 0))
        self.ModuleTabManagerWidget.setStyleSheet(u"QToolButton\n"
"{\n"
"	\n"
"	color: rgb(255, 255, 255);\n"
"	border-radius: 5px;\n"
"	color: \n"
"}\n"
"\n"
"QToolButton::hover\n"
"{\n"
"border: 2px solid #FFFFFF;\n"
"background-color: rgb(129, 129, 129);;\n"
"}\n"
"QToolButton::pressed\n"
"{\n"
"	background-color: rgb(81, 176, 255);\n"
"}")
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
        self.twModule.setStyleSheet(u"/* General Tab Widget*/\n"
"#tGcodeEditor, #tDrawing, #tObjectDetecting, #tPointTool, #TermiteTab\n"
"{	\n"
"	background-color: rgb(30, 30, 32);\n"
"}\n"
"\n"
"QLabel\n"
"{	\n"
"	color: #D0D0D1;\n"
"}\n"
"\n"
"QGroupBox {\n"
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
"	backgro"
                        "und-color: rgb(33, 125, 206);\n"
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
        self.robotTitile_16 = QFrame(self.tGcodeEditor)
        self.robotTitile_16.setObjectName(u"robotTitile_16")
        self.robotTitile_16.setMinimumSize(QSize(0, 40))
        self.robotTitile_16.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_16.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}\n"
"\n"
"QRadioButton {\n"
"    background-color: #434347;\n"
"    padding: 5px;\n"
"	 width:25px;\n"
"    border: 1px solid #646469;\n"
"	color: #D0D0D1;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"\n"
"QRadioButton:checked {\n"
"    background-color: #646469;\n"
"    border-color: #646469;\n"
"    color: white;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"    border-color: #2196F3;\n"
"}\n"
"\n"
"QRadioButton:disabled {\n"
"    background-color: #D0D0D0;\n"
"    color: #B0B0B0;\n"
"}")
        self.robotTitile_16.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_16.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_114 = QHBoxLayout(self.robotTitile_16)
        self.horizontalLayout_114.setSpacing(6)
        self.horizontalLayout_114.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_114.setObjectName(u"horizontalLayout_114")
        self.horizontalLayout_114.setContentsMargins(-1, 0, -1, 0)
        self.label_28 = QLabel(self.robotTitile_16)
        self.label_28.setObjectName(u"label_28")

        self.horizontalLayout_114.addWidget(self.label_28)

        self.cbProgramThreadID = QComboBox(self.robotTitile_16)
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.addItem("")
        self.cbProgramThreadID.setObjectName(u"cbProgramThreadID")
        sizePolicy5 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.cbProgramThreadID.sizePolicy().hasHeightForWidth())
        self.cbProgramThreadID.setSizePolicy(sizePolicy5)
        self.cbProgramThreadID.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_114.addWidget(self.cbProgramThreadID)

        self.horizontalSpacer_118 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_114.addItem(self.horizontalSpacer_118)

        self.rbEditorStart = QRadioButton(self.robotTitile_16)
        self.rbEditorStart.setObjectName(u"rbEditorStart")
        sizePolicy6 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Minimum)
        sizePolicy6.setHorizontalStretch(0)
        sizePolicy6.setVerticalStretch(0)
        sizePolicy6.setHeightForWidth(self.rbEditorStart.sizePolicy().hasHeightForWidth())
        self.rbEditorStart.setSizePolicy(sizePolicy6)
        self.rbEditorStart.setMinimumSize(QSize(60, 30))
        self.rbEditorStart.setChecked(True)

        self.horizontalLayout_114.addWidget(self.rbEditorStart)

        self.rbEditorCurrent = QRadioButton(self.robotTitile_16)
        self.rbEditorCurrent.setObjectName(u"rbEditorCurrent")
        sizePolicy6.setHeightForWidth(self.rbEditorCurrent.sizePolicy().hasHeightForWidth())
        self.rbEditorCurrent.setSizePolicy(sizePolicy6)
        self.rbEditorCurrent.setMinimumSize(QSize(60, 30))
        self.rbEditorCurrent.setChecked(False)

        self.horizontalLayout_114.addWidget(self.rbEditorCurrent)

        self.pbExecuteGcodes = QPushButton(self.robotTitile_16)
        self.pbExecuteGcodes.setObjectName(u"pbExecuteGcodes")
        sizePolicy7 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Expanding)
        sizePolicy7.setHorizontalStretch(0)
        sizePolicy7.setVerticalStretch(0)
        sizePolicy7.setHeightForWidth(self.pbExecuteGcodes.sizePolicy().hasHeightForWidth())
        self.pbExecuteGcodes.setSizePolicy(sizePolicy7)
        self.pbExecuteGcodes.setMinimumSize(QSize(70, 30))
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

        self.horizontalLayout_114.addWidget(self.pbExecuteGcodes)


        self.verticalLayout.addWidget(self.robotTitile_16)

        self.frame_53 = QFrame(self.tGcodeEditor)
        self.frame_53.setObjectName(u"frame_53")
        self.frame_53.setMinimumSize(QSize(0, 100))
        self.frame_53.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}")
        self.frame_53.setFrameShape(QFrame.StyledPanel)
        self.frame_53.setFrameShadow(QFrame.Raised)
        self.verticalLayout_84 = QVBoxLayout(self.frame_53)
        self.verticalLayout_84.setSpacing(0)
        self.verticalLayout_84.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_84.setObjectName(u"verticalLayout_84")
        self.verticalLayout_84.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_18 = QFrame(self.frame_53)
        self.robotTitile_18.setObjectName(u"robotTitile_18")
        self.robotTitile_18.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_18.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_18.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_18.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_120 = QHBoxLayout(self.robotTitile_18)
        self.horizontalLayout_120.setSpacing(6)
        self.horizontalLayout_120.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_120.setObjectName(u"horizontalLayout_120")
        self.label_81 = QLabel(self.robotTitile_18)
        self.label_81.setObjectName(u"label_81")

        self.horizontalLayout_120.addWidget(self.label_81)

        self.horizontalSpacer_122 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_120.addItem(self.horizontalSpacer_122)

        self.cbProgramSource = QComboBox(self.robotTitile_18)
        self.cbProgramSource.addItem("")
        self.cbProgramSource.addItem("")
        self.cbProgramSource.setObjectName(u"cbProgramSource")
        sizePolicy5.setHeightForWidth(self.cbProgramSource.sizePolicy().hasHeightForWidth())
        self.cbProgramSource.setSizePolicy(sizePolicy5)
        self.cbProgramSource.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_120.addWidget(self.cbProgramSource)


        self.verticalLayout_84.addWidget(self.robotTitile_18)

        self.frame_55 = QFrame(self.frame_53)
        self.frame_55.setObjectName(u"frame_55")
        sizePolicy.setHeightForWidth(self.frame_55.sizePolicy().hasHeightForWidth())
        self.frame_55.setSizePolicy(sizePolicy)
        self.frame_55.setMinimumSize(QSize(0, 0))
        self.frame_55.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_55.setFrameShape(QFrame.StyledPanel)
        self.frame_55.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_2 = QHBoxLayout(self.frame_55)
        self.horizontalLayout_2.setSpacing(6)
        self.horizontalLayout_2.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.verticalLayout_2 = QVBoxLayout()
        self.verticalLayout_2.setSpacing(6)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setSpacing(6)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.label_3 = QLabel(self.frame_55)
        self.label_3.setObjectName(u"label_3")

        self.horizontalLayout_8.addWidget(self.label_3)

        self.tbOpenGcodePath = QToolButton(self.frame_55)
        self.tbOpenGcodePath.setObjectName(u"tbOpenGcodePath")
        icon3 = QIcon()
        icon3.addFile(u":/icon/icons8_folder_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbOpenGcodePath.setIcon(icon3)
        self.tbOpenGcodePath.setAutoRaise(True)

        self.horizontalLayout_8.addWidget(self.tbOpenGcodePath)

        self.leGcodeExplorer = QLineEdit(self.frame_55)
        self.leGcodeExplorer.setObjectName(u"leGcodeExplorer")

        self.horizontalLayout_8.addWidget(self.leGcodeExplorer)


        self.verticalLayout_2.addLayout(self.horizontalLayout_8)

        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setSpacing(6)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.tbBackGcodeFolder = QToolButton(self.frame_55)
        self.tbBackGcodeFolder.setObjectName(u"tbBackGcodeFolder")
        icon4 = QIcon()
        icon4.addFile(u":/icon/icons8_back_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbBackGcodeFolder.setIcon(icon4)
        self.tbBackGcodeFolder.setAutoRaise(True)

        self.horizontalLayout_6.addWidget(self.tbBackGcodeFolder)

        self.tbNewGcodeFile = QToolButton(self.frame_55)
        self.tbNewGcodeFile.setObjectName(u"tbNewGcodeFile")
        icon5 = QIcon()
        icon5.addFile(u":/icon/icons8_add_new_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbNewGcodeFile.setIcon(icon5)

        self.horizontalLayout_6.addWidget(self.tbNewGcodeFile)

        self.tbRefreshExplorer = QToolButton(self.frame_55)
        self.tbRefreshExplorer.setObjectName(u"tbRefreshExplorer")
        icon6 = QIcon()
        icon6.addFile(u":/icon/icons8_refresh_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbRefreshExplorer.setIcon(icon6)

        self.horizontalLayout_6.addWidget(self.tbRefreshExplorer)

        self.tbDeleteGcodeFile = QToolButton(self.frame_55)
        self.tbDeleteGcodeFile.setObjectName(u"tbDeleteGcodeFile")
        icon7 = QIcon()
        icon7.addFile(u":/icon/icons8_close_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbDeleteGcodeFile.setIcon(icon7)

        self.horizontalLayout_6.addWidget(self.tbDeleteGcodeFile)

        self.horizontalSpacer_10 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_6.addItem(self.horizontalSpacer_10)


        self.verticalLayout_2.addLayout(self.horizontalLayout_6)

        self.tvGcodeExplorer = QTreeView(self.frame_55)
        self.tvGcodeExplorer.setObjectName(u"tvGcodeExplorer")
        self.tvGcodeExplorer.setStyleSheet(u"QTreeView\n"
"{\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.tvGcodeExplorer.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.tvGcodeExplorer.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOn)

        self.verticalLayout_2.addWidget(self.tvGcodeExplorer)

        self.tvCurrentVariable = QTreeView(self.frame_55)
        self.tvCurrentVariable.setObjectName(u"tvCurrentVariable")
        self.tvCurrentVariable.setStyleSheet(u"QTreeView\n"
"{\n"
"	color: rgb(224, 224, 224);\n"
"}\n"
"\n"
"QTreeView::header {\n"
"	background-color: rgb(78, 78, 78);\n"
"}")

        self.verticalLayout_2.addWidget(self.tvCurrentVariable)

        self.cbVariableDisplayOption = QComboBox(self.frame_55)
        self.cbVariableDisplayOption.addItem("")
        self.cbVariableDisplayOption.addItem("")
        self.cbVariableDisplayOption.setObjectName(u"cbVariableDisplayOption")

        self.verticalLayout_2.addWidget(self.cbVariableDisplayOption)


        self.horizontalLayout_2.addLayout(self.verticalLayout_2)

        self.verticalLayout_3 = QVBoxLayout()
        self.verticalLayout_3.setSpacing(6)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.frame_10 = QFrame(self.frame_55)
        self.frame_10.setObjectName(u"frame_10")
        self.frame_10.setMinimumSize(QSize(0, 0))
        self.frame_10.setStyleSheet(u"QFrame\n"
"{	\n"
"	background-color: #333337;\n"
"}")
        self.frame_10.setFrameShape(QFrame.StyledPanel)
        self.frame_10.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.frame_10)
        self.horizontalLayout_9.setSpacing(5)
        self.horizontalLayout_9.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.horizontalLayout_9.setContentsMargins(5, 5, 5, 5)
        self.lbSelectedProgram = QLabel(self.frame_10)
        self.lbSelectedProgram.setObjectName(u"lbSelectedProgram")

        self.horizontalLayout_9.addWidget(self.lbSelectedProgram)

        self.pbSaveGcode = QToolButton(self.frame_10)
        self.pbSaveGcode.setObjectName(u"pbSaveGcode")
        sizePolicy.setHeightForWidth(self.pbSaveGcode.sizePolicy().hasHeightForWidth())
        self.pbSaveGcode.setSizePolicy(sizePolicy)
        self.pbSaveGcode.setMinimumSize(QSize(0, 0))
        self.pbSaveGcode.setMaximumSize(QSize(20, 20))
        icon8 = QIcon()
        icon8.addFile(u":/icon/icons8_save_52px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSaveGcode.setIcon(icon8)
        self.pbSaveGcode.setIconSize(QSize(32, 32))
        self.pbSaveGcode.setAutoRaise(True)

        self.horizontalLayout_9.addWidget(self.pbSaveGcode)

        self.pbFormat = QToolButton(self.frame_10)
        self.pbFormat.setObjectName(u"pbFormat")
        icon9 = QIcon()
        icon9.addFile(u":/icon/icons8_view_details_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFormat.setIcon(icon9)
        self.pbFormat.setIconSize(QSize(20, 20))
        self.pbFormat.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.pbFormat.setAutoRaise(True)

        self.horizontalLayout_9.addWidget(self.pbFormat)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_9.addItem(self.horizontalSpacer_2)

        self.cbEditGcodeLock = QCheckBox(self.frame_10)
        self.cbEditGcodeLock.setObjectName(u"cbEditGcodeLock")
        sizePolicy8 = QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Preferred)
        sizePolicy8.setHorizontalStretch(0)
        sizePolicy8.setVerticalStretch(0)
        sizePolicy8.setHeightForWidth(self.cbEditGcodeLock.sizePolicy().hasHeightForWidth())
        self.cbEditGcodeLock.setSizePolicy(sizePolicy8)
        self.cbEditGcodeLock.setMinimumSize(QSize(20, 0))
        font5 = QFont()
        font5.setPointSize(8)
        font5.setBold(False)
        font5.setKerning(True)
        self.cbEditGcodeLock.setFont(font5)
        self.cbEditGcodeLock.setIconSize(QSize(32, 32))
        self.cbEditGcodeLock.setChecked(False)

        self.horizontalLayout_9.addWidget(self.cbEditGcodeLock)

        self.pbOpenGcodeDocs = QToolButton(self.frame_10)
        self.pbOpenGcodeDocs.setObjectName(u"pbOpenGcodeDocs")
        sizePolicy6.setHeightForWidth(self.pbOpenGcodeDocs.sizePolicy().hasHeightForWidth())
        self.pbOpenGcodeDocs.setSizePolicy(sizePolicy6)
        self.pbOpenGcodeDocs.setMaximumSize(QSize(20, 20))
        icon10 = QIcon()
        icon10.addFile(u":/icon/icons8_help_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbOpenGcodeDocs.setIcon(icon10)
        self.pbOpenGcodeDocs.setIconSize(QSize(32, 32))
        self.pbOpenGcodeDocs.setAutoRaise(True)

        self.horizontalLayout_9.addWidget(self.pbOpenGcodeDocs)


        self.verticalLayout_3.addWidget(self.frame_10)

        self.pteGcodeArea = CodeEditor(self.frame_55)
        self.pteGcodeArea.setObjectName(u"pteGcodeArea")
        sizePolicy9 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        sizePolicy9.setHorizontalStretch(0)
        sizePolicy9.setVerticalStretch(0)
        sizePolicy9.setHeightForWidth(self.pteGcodeArea.sizePolicy().hasHeightForWidth())
        self.pteGcodeArea.setSizePolicy(sizePolicy9)
        self.pteGcodeArea.setMinimumSize(QSize(310, 300))
        self.pteGcodeArea.setFont(font5)
        self.pteGcodeArea.setStyleSheet(u"")
        self.pteGcodeArea.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.pteGcodeArea.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.pteGcodeArea.setReadOnly(False)
        self.pteGcodeArea.setTextInteractionFlags(Qt.TextEditorInteraction)

        self.verticalLayout_3.addWidget(self.pteGcodeArea)

        self.frame_25 = QFrame(self.frame_55)
        self.frame_25.setObjectName(u"frame_25")
        self.frame_25.setMinimumSize(QSize(0, 0))
        self.frame_25.setStyleSheet(u"QFrame\n"
"{	\n"
"	background-color: #333337;\n"
"}")
        self.frame_25.setFrameShape(QFrame.StyledPanel)
        self.frame_25.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_30 = QHBoxLayout(self.frame_25)
        self.horizontalLayout_30.setSpacing(5)
        self.horizontalLayout_30.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_30.setObjectName(u"horizontalLayout_30")
        self.horizontalLayout_30.setContentsMargins(5, 5, 5, 5)
        self.lbSelectedProgram_3 = QLabel(self.frame_25)
        self.lbSelectedProgram_3.setObjectName(u"lbSelectedProgram_3")

        self.horizontalLayout_30.addWidget(self.lbSelectedProgram_3)

        self.pbSaveFunctionScripts = QToolButton(self.frame_25)
        self.pbSaveFunctionScripts.setObjectName(u"pbSaveFunctionScripts")
        sizePolicy.setHeightForWidth(self.pbSaveFunctionScripts.sizePolicy().hasHeightForWidth())
        self.pbSaveFunctionScripts.setSizePolicy(sizePolicy)
        self.pbSaveFunctionScripts.setMinimumSize(QSize(0, 0))
        self.pbSaveFunctionScripts.setMaximumSize(QSize(20, 20))
        self.pbSaveFunctionScripts.setIcon(icon8)
        self.pbSaveFunctionScripts.setIconSize(QSize(32, 32))
        self.pbSaveFunctionScripts.setAutoRaise(True)

        self.horizontalLayout_30.addWidget(self.pbSaveFunctionScripts)


        self.verticalLayout_3.addWidget(self.frame_25)

        self.pteScriptFunction = CodeEditor(self.frame_55)
        self.pteScriptFunction.setObjectName(u"pteScriptFunction")
        sizePolicy9.setHeightForWidth(self.pteScriptFunction.sizePolicy().hasHeightForWidth())
        self.pteScriptFunction.setSizePolicy(sizePolicy9)
        self.pteScriptFunction.setMinimumSize(QSize(310, 100))
        self.pteScriptFunction.setFont(font5)
        self.pteScriptFunction.setStyleSheet(u"")
        self.pteScriptFunction.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.pteScriptFunction.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        self.pteScriptFunction.setReadOnly(False)
        self.pteScriptFunction.setTextInteractionFlags(Qt.TextEditorInteraction)

        self.verticalLayout_3.addWidget(self.pteScriptFunction)


        self.horizontalLayout_2.addLayout(self.verticalLayout_3)

        self.horizontalLayout_2.setStretch(0, 1)
        self.horizontalLayout_2.setStretch(1, 3)

        self.verticalLayout_84.addWidget(self.frame_55)


        self.verticalLayout.addWidget(self.frame_53)

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
        self.wObjectDetecting.setGeometry(QRect(0, -1065, 655, 2500))
        self.wObjectDetecting.setMinimumSize(QSize(100, 2500))
        self.wObjectDetecting.setStyleSheet(u"QWidget#wObjectDetecting\n"
"{	\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"")
        self.verticalLayout_17 = QVBoxLayout(self.wObjectDetecting)
        self.verticalLayout_17.setSpacing(6)
        self.verticalLayout_17.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_17.setObjectName(u"verticalLayout_17")
        self.fObjectDetectingTitle = QFrame(self.wObjectDetecting)
        self.fObjectDetectingTitle.setObjectName(u"fObjectDetectingTitle")
        self.fObjectDetectingTitle.setStyleSheet(u"QFrame#fObjectDetectingTitle\n"
"{\n"
"	padding: 3px;\n"
"	background-color: #333337;\n"
"	border: 1px solid rgb(16, 16, 16);\n"
"}")
        self.horizontalLayout_17 = QHBoxLayout(self.fObjectDetectingTitle)
        self.horizontalLayout_17.setSpacing(6)
        self.horizontalLayout_17.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_17.setObjectName(u"horizontalLayout_17")
        self.label_191 = QLabel(self.fObjectDetectingTitle)
        self.label_191.setObjectName(u"label_191")

        self.horizontalLayout_17.addWidget(self.label_191)

        self.cbSelectedDetecting = QComboBox(self.fObjectDetectingTitle)
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.addItem("")
        self.cbSelectedDetecting.setObjectName(u"cbSelectedDetecting")
        sizePolicy10 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Fixed)
        sizePolicy10.setHorizontalStretch(0)
        sizePolicy10.setVerticalStretch(0)
        sizePolicy10.setHeightForWidth(self.cbSelectedDetecting.sizePolicy().hasHeightForWidth())
        self.cbSelectedDetecting.setSizePolicy(sizePolicy10)
        self.cbSelectedDetecting.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_17.addWidget(self.cbSelectedDetecting)

        self.horizontalSpacer_49 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_17.addItem(self.horizontalSpacer_49)


        self.verticalLayout_17.addWidget(self.fObjectDetectingTitle)

        self.splitter = QSplitter(self.wObjectDetecting)
        self.splitter.setObjectName(u"splitter")
        sizePolicy4.setHeightForWidth(self.splitter.sizePolicy().hasHeightForWidth())
        self.splitter.setSizePolicy(sizePolicy4)
        self.splitter.setStyleSheet(u"/*QSplitter::handle:vertical \n"
"{	\n"
"	background: rgb(37, 197, 255);\n"
"}*/\n"
"\n"
"QGroupBox:title\n"
"{\n"
"	padding:2px;\n"
"	color: rgb(208, 208, 209);\n"
"	background-color: rgb(51, 51, 55);\n"
"}\n"
"\n"
"QGroupBox\n"
"{	\n"
"	background-color: rgb(38, 38, 41);\n"
"}\n"
"QFrame\n"
"{	\n"
"	border: none;\n"
"}")
        self.splitter.setOrientation(Qt.Vertical)
        self.splitter.setHandleWidth(10)
        self.gbImageViewer = QGroupBox(self.splitter)
        self.gbImageViewer.setObjectName(u"gbImageViewer")
        sizePolicy1.setHeightForWidth(self.gbImageViewer.sizePolicy().hasHeightForWidth())
        self.gbImageViewer.setSizePolicy(sizePolicy1)
        self.gbImageViewer.setMinimumSize(QSize(0, 300))
        self.gbImageViewer.setMaximumSize(QSize(16777215, 16777215))
        font6 = QFont()
        font6.setPointSize(10)
        font6.setBold(True)
        self.gbImageViewer.setFont(font6)
        self.gbImageViewer.setStyleSheet(u"QPushButton\n"
"{	\n"
"	padding-left:5px;\n"
"	padding-right:5px;\n"
"}")
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
        self.verticalLayout_7 = QVBoxLayout(self.fImageViewer)
        self.verticalLayout_7.setSpacing(6)
        self.verticalLayout_7.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_7.setObjectName(u"verticalLayout_7")
        self.frame_16 = QFrame(self.fImageViewer)
        self.frame_16.setObjectName(u"frame_16")
        self.frame_16.setMinimumSize(QSize(30, 0))
        self.frame_16.setFrameShape(QFrame.StyledPanel)
        self.frame_16.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_3 = QHBoxLayout(self.frame_16)
        self.horizontalLayout_3.setSpacing(5)
        self.horizontalLayout_3.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.horizontalLayout_3.setContentsMargins(0, 0, 0, 0)
        self.pbFindChessboardTool = QPushButton(self.frame_16)
        self.pbFindChessboardTool.setObjectName(u"pbFindChessboardTool")
        sizePolicy5.setHeightForWidth(self.pbFindChessboardTool.sizePolicy().hasHeightForWidth())
        self.pbFindChessboardTool.setSizePolicy(sizePolicy5)
        self.pbFindChessboardTool.setMinimumSize(QSize(0, 30))
        icon11 = QIcon()
        icon11.addFile(u":/icon/icons8_chessboard_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFindChessboardTool.setIcon(icon11)
        self.pbFindChessboardTool.setIconSize(QSize(24, 24))
        self.pbFindChessboardTool.setCheckable(True)
        self.pbFindChessboardTool.setFlat(True)

        self.horizontalLayout_3.addWidget(self.pbFindChessboardTool)

        self.pbAreaTool = QPushButton(self.frame_16)
        self.pbAreaTool.setObjectName(u"pbAreaTool")
        sizePolicy5.setHeightForWidth(self.pbAreaTool.sizePolicy().hasHeightForWidth())
        self.pbAreaTool.setSizePolicy(sizePolicy5)
        self.pbAreaTool.setMinimumSize(QSize(0, 30))
        icon12 = QIcon()
        icon12.addFile(u":/icon/icons8_rectangle_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbAreaTool.setIcon(icon12)
        self.pbAreaTool.setIconSize(QSize(24, 24))
        self.pbAreaTool.setCheckable(True)
        self.pbAreaTool.setFlat(True)

        self.horizontalLayout_3.addWidget(self.pbAreaTool)

        self.pbCalibPointTool = QPushButton(self.frame_16)
        self.pbCalibPointTool.setObjectName(u"pbCalibPointTool")
        sizePolicy5.setHeightForWidth(self.pbCalibPointTool.sizePolicy().hasHeightForWidth())
        self.pbCalibPointTool.setSizePolicy(sizePolicy5)
        self.pbCalibPointTool.setMinimumSize(QSize(0, 30))
        icon13 = QIcon()
        icon13.addFile(u":/icon/icons8_select_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCalibPointTool.setIcon(icon13)
        self.pbCalibPointTool.setIconSize(QSize(24, 24))
        self.pbCalibPointTool.setCheckable(True)
        self.pbCalibPointTool.setFlat(True)

        self.horizontalLayout_3.addWidget(self.pbCalibPointTool)

        self.pbMappingPointTool = QPushButton(self.frame_16)
        self.pbMappingPointTool.setObjectName(u"pbMappingPointTool")
        sizePolicy5.setHeightForWidth(self.pbMappingPointTool.sizePolicy().hasHeightForWidth())
        self.pbMappingPointTool.setSizePolicy(sizePolicy5)
        self.pbMappingPointTool.setMinimumSize(QSize(0, 30))
        icon14 = QIcon()
        icon14.addFile(u":/icon/icons8_target_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbMappingPointTool.setIcon(icon14)
        self.pbMappingPointTool.setIconSize(QSize(24, 24))
        self.pbMappingPointTool.setCheckable(True)
        self.pbMappingPointTool.setFlat(True)

        self.horizontalLayout_3.addWidget(self.pbMappingPointTool)

        self.horizontalSpacer_12 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_3.addItem(self.horizontalSpacer_12)


        self.verticalLayout_7.addWidget(self.frame_16)

        self.frame_8 = QFrame(self.fImageViewer)
        self.frame_8.setObjectName(u"frame_8")
        self.frame_8.setMinimumSize(QSize(20, 0))
        self.frame_8.setFrameShape(QFrame.StyledPanel)
        self.frame_8.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_4 = QHBoxLayout(self.frame_8)
        self.horizontalLayout_4.setSpacing(5)
        self.horizontalLayout_4.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.horizontalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.pbWarpTool = QPushButton(self.frame_8)
        self.pbWarpTool.setObjectName(u"pbWarpTool")
        sizePolicy5.setHeightForWidth(self.pbWarpTool.sizePolicy().hasHeightForWidth())
        self.pbWarpTool.setSizePolicy(sizePolicy5)
        self.pbWarpTool.setMinimumSize(QSize(0, 30))
        icon15 = QIcon()
        icon15.addFile(u":/icon/icons8_opacity_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbWarpTool.setIcon(icon15)
        self.pbWarpTool.setIconSize(QSize(24, 24))
        self.pbWarpTool.setCheckable(True)
        self.pbWarpTool.setFlat(True)

        self.horizontalLayout_4.addWidget(self.pbWarpTool)

        self.pbFilterTool = QPushButton(self.frame_8)
        self.pbFilterTool.setObjectName(u"pbFilterTool")
        sizePolicy5.setHeightForWidth(self.pbFilterTool.sizePolicy().hasHeightForWidth())
        self.pbFilterTool.setSizePolicy(sizePolicy5)
        self.pbFilterTool.setMinimumSize(QSize(0, 30))
        icon16 = QIcon()
        icon16.addFile(u":/icon/Slider 2_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbFilterTool.setIcon(icon16)
        self.pbFilterTool.setIconSize(QSize(24, 24))
        self.pbFilterTool.setFlat(True)

        self.horizontalLayout_4.addWidget(self.pbFilterTool)

        self.pbGetSizeTool = QPushButton(self.frame_8)
        self.pbGetSizeTool.setObjectName(u"pbGetSizeTool")
        sizePolicy5.setHeightForWidth(self.pbGetSizeTool.sizePolicy().hasHeightForWidth())
        self.pbGetSizeTool.setSizePolicy(sizePolicy5)
        self.pbGetSizeTool.setMinimumSize(QSize(0, 30))
        icon17 = QIcon()
        icon17.addFile(u":/icon/icons8_page_size_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbGetSizeTool.setIcon(icon17)
        self.pbGetSizeTool.setIconSize(QSize(24, 24))
        self.pbGetSizeTool.setCheckable(True)
        self.pbGetSizeTool.setFlat(True)

        self.horizontalLayout_4.addWidget(self.pbGetSizeTool)

        self.horizontalSpacer_11 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_4.addItem(self.horizontalSpacer_11)


        self.verticalLayout_7.addWidget(self.frame_8)

        self.frame_15 = QFrame(self.fImageViewer)
        self.frame_15.setObjectName(u"frame_15")
        self.frame_15.setMinimumSize(QSize(20, 0))
        self.frame_15.setFrameShape(QFrame.StyledPanel)
        self.frame_15.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_13 = QHBoxLayout(self.frame_15)
        self.horizontalLayout_13.setSpacing(5)
        self.horizontalLayout_13.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.horizontalLayout_13.setContentsMargins(0, 0, 0, 0)
        self.horizontalSpacer_14 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_13.addItem(self.horizontalSpacer_14)


        self.verticalLayout_7.addWidget(self.frame_15)

        self.horizontalLayout_7 = QHBoxLayout()
        self.horizontalLayout_7.setSpacing(6)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.gvImageViewer = ImageViewer(self.fImageViewer)
        self.gvImageViewer.setObjectName(u"gvImageViewer")
        sizePolicy4.setHeightForWidth(self.gvImageViewer.sizePolicy().hasHeightForWidth())
        self.gvImageViewer.setSizePolicy(sizePolicy4)

        self.horizontalLayout_7.addWidget(self.gvImageViewer)

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
        sizePolicy.setHeightForWidth(self.cbImageOutput.sizePolicy().hasHeightForWidth())
        self.cbImageOutput.setSizePolicy(sizePolicy)
        self.cbImageOutput.setMinimumSize(QSize(90, 0))

        self.verticalLayout_10.addWidget(self.cbImageOutput)

        self.lbDisplayRatio_2 = QLabel(self.frame_17)
        self.lbDisplayRatio_2.setObjectName(u"lbDisplayRatio_2")

        self.verticalLayout_10.addWidget(self.lbDisplayRatio_2)

        self.lbDisplayRatio_3 = QLabel(self.frame_17)
        self.lbDisplayRatio_3.setObjectName(u"lbDisplayRatio_3")

        self.verticalLayout_10.addWidget(self.lbDisplayRatio_3)

        self.pbZoomInCameraView = QPushButton(self.frame_17)
        self.pbZoomInCameraView.setObjectName(u"pbZoomInCameraView")

        self.verticalLayout_10.addWidget(self.pbZoomInCameraView)

        self.pbZoomOutCameraView = QPushButton(self.frame_17)
        self.pbZoomOutCameraView.setObjectName(u"pbZoomOutCameraView")

        self.verticalLayout_10.addWidget(self.pbZoomOutCameraView)

        self.verticalSpacer_10 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_10.addItem(self.verticalSpacer_10)

        self.lbDisplayRatio = QLabel(self.frame_17)
        self.lbDisplayRatio.setObjectName(u"lbDisplayRatio")

        self.verticalLayout_10.addWidget(self.lbDisplayRatio)

        self.lbMatSize = QLabel(self.frame_17)
        self.lbMatSize.setObjectName(u"lbMatSize")

        self.verticalLayout_10.addWidget(self.lbMatSize)


        self.horizontalLayout_7.addWidget(self.frame_17)


        self.verticalLayout_7.addLayout(self.horizontalLayout_7)


        self.vlImageViewer.addWidget(self.fImageViewer)

        self.splitter.addWidget(self.gbImageViewer)
        self.fObjectDetectingTool = QFrame(self.splitter)
        self.fObjectDetectingTool.setObjectName(u"fObjectDetectingTool")
        sizePolicy11 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy11.setHorizontalStretch(0)
        sizePolicy11.setVerticalStretch(30)
        sizePolicy11.setHeightForWidth(self.fObjectDetectingTool.sizePolicy().hasHeightForWidth())
        self.fObjectDetectingTool.setSizePolicy(sizePolicy11)
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

        self.cbTrackingThreadForCamera = QComboBox(self.fImageProvider)
        self.cbTrackingThreadForCamera.addItem("")
        self.cbTrackingThreadForCamera.addItem("")
        self.cbTrackingThreadForCamera.addItem("")
        self.cbTrackingThreadForCamera.addItem("")
        self.cbTrackingThreadForCamera.setObjectName(u"cbTrackingThreadForCamera")
        self.cbTrackingThreadForCamera.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_10.addWidget(self.cbTrackingThreadForCamera)


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
        icon18 = QIcon()
        icon18.addFile(u":/icon/webcam.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLoadCamera.setIcon(icon18)
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
        icon19 = QIcon()
        icon19.addFile(u":/icon/icons8_image_30px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbLoadTestImage.setIcon(icon19)
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
        sizePolicy12 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Minimum)
        sizePolicy12.setHorizontalStretch(0)
        sizePolicy12.setVerticalStretch(0)
        sizePolicy12.setHeightForWidth(self.leImageWidth.sizePolicy().hasHeightForWidth())
        self.leImageWidth.setSizePolicy(sizePolicy12)
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
        sizePolicy12.setHeightForWidth(self.leImageHeight.sizePolicy().hasHeightForWidth())
        self.leImageHeight.setSizePolicy(sizePolicy12)
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
        sizePolicy12.setHeightForWidth(self.leCaptureInterval.sizePolicy().hasHeightForWidth())
        self.leCaptureInterval.setSizePolicy(sizePolicy12)
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
        icon20 = QIcon()
        icon20.addFile(u":/icon/icons8-play-48.png", QSize(), QIcon.Normal, QIcon.Off)
        icon20.addFile(u":/icon/icons8-pause-48.png", QSize(), QIcon.Normal, QIcon.On)
        icon20.addFile(u"icon/icons8-play-48.png", QSize(), QIcon.Selected, QIcon.Off)
        self.pbStartAcquisition.setIcon(icon20)
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
        icon21 = QIcon()
        icon21.addFile(u":/icon/icons8-screenshot-40.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCapture.setIcon(icon21)
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
        sizePolicy.setHeightForWidth(self.fCameraCalibrationFrame.sizePolicy().hasHeightForWidth())
        self.fCameraCalibrationFrame.setSizePolicy(sizePolicy)
        self.fCameraCalibrationFrame.setMinimumSize(QSize(0, 0))
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
        self.fCalibStep1.setMinimumSize(QSize(0, 0))
        self.horizontalLayout_14 = QHBoxLayout(self.fCalibStep1)
        self.horizontalLayout_14.setSpacing(6)
        self.horizontalLayout_14.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_14.setObjectName(u"horizontalLayout_14")
        self.lbWarpGuide = QLabel(self.fCalibStep1)
        self.lbWarpGuide.setObjectName(u"lbWarpGuide")
        sizePolicy6.setHeightForWidth(self.lbWarpGuide.sizePolicy().hasHeightForWidth())
        self.lbWarpGuide.setSizePolicy(sizePolicy6)
        self.lbWarpGuide.setMinimumSize(QSize(400, 91))
        self.lbWarpGuide.setMaximumSize(QSize(400, 91))
        self.lbWarpGuide.setStyleSheet(u"")
        self.lbWarpGuide.setPixmap(QPixmap(u"icon/image-warp.png"))
        self.lbWarpGuide.setScaledContents(True)

        self.horizontalLayout_14.addWidget(self.lbWarpGuide)

        self.horizontalSpacer_7 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_14.addItem(self.horizontalSpacer_7)


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

        self.label_2 = QLabel(self.fCameraCalibrationFrame)
        self.label_2.setObjectName(u"label_2")

        self.verticalLayout_52.addWidget(self.label_2)

        self.lbCalibGuide = QLabel(self.fCameraCalibrationFrame)
        self.lbCalibGuide.setObjectName(u"lbCalibGuide")
        sizePolicy6.setHeightForWidth(self.lbCalibGuide.sizePolicy().hasHeightForWidth())
        self.lbCalibGuide.setSizePolicy(sizePolicy6)
        self.lbCalibGuide.setMinimumSize(QSize(350, 91))
        self.lbCalibGuide.setMaximumSize(QSize(350, 91))
        self.lbCalibGuide.setStyleSheet(u"")
        self.lbCalibGuide.setPixmap(QPixmap(u"icon/image-calib.png"))
        self.lbCalibGuide.setScaledContents(True)

        self.verticalLayout_52.addWidget(self.lbCalibGuide)

        self.label_7 = QLabel(self.fCameraCalibrationFrame)
        self.label_7.setObjectName(u"label_7")

        self.verticalLayout_52.addWidget(self.label_7)

        self.fCalibStep2 = QFrame(self.fCameraCalibrationFrame)
        self.fCalibStep2.setObjectName(u"fCalibStep2")
        self.gridLayout_26 = QGridLayout(self.fCalibStep2)
        self.gridLayout_26.setSpacing(10)
        self.gridLayout_26.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_26.setObjectName(u"gridLayout_26")
        self.leRealityP1P2Distance = QLineEdit(self.fCalibStep2)
        self.leRealityP1P2Distance.setObjectName(u"leRealityP1P2Distance")
        sizePolicy.setHeightForWidth(self.leRealityP1P2Distance.sizePolicy().hasHeightForWidth())
        self.leRealityP1P2Distance.setSizePolicy(sizePolicy)
        self.leRealityP1P2Distance.setMinimumSize(QSize(0, 0))
        self.leRealityP1P2Distance.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_26.addWidget(self.leRealityP1P2Distance, 11, 2, 1, 1)

        self.leCalibOffset_X = QLineEdit(self.fCalibStep2)
        self.leCalibOffset_X.setObjectName(u"leCalibOffset_X")
        sizePolicy.setHeightForWidth(self.leCalibOffset_X.sizePolicy().hasHeightForWidth())
        self.leCalibOffset_X.setSizePolicy(sizePolicy)
        self.leCalibOffset_X.setMinimumSize(QSize(0, 0))
        self.leCalibOffset_X.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_26.addWidget(self.leCalibOffset_X, 9, 2, 1, 1)

        self.label_148 = QLabel(self.fCalibStep2)
        self.label_148.setObjectName(u"label_148")
        self.label_148.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_148, 11, 3, 1, 1)

        self.tbPastePoint1 = QToolButton(self.fCalibStep2)
        self.tbPastePoint1.setObjectName(u"tbPastePoint1")
        icon22 = QIcon()
        icon22.addFile(u":/icon/Paste.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbPastePoint1.setIcon(icon22)
        self.tbPastePoint1.setIconSize(QSize(24, 24))

        self.gridLayout_26.addWidget(self.tbPastePoint1, 5, 7, 1, 1)

        self.pbImageMapping = QPushButton(self.fCalibStep2)
        self.pbImageMapping.setObjectName(u"pbImageMapping")
        sizePolicy.setHeightForWidth(self.pbImageMapping.sizePolicy().hasHeightForWidth())
        self.pbImageMapping.setSizePolicy(sizePolicy)
        self.pbImageMapping.setMinimumSize(QSize(0, 45))
        self.pbImageMapping.setMaximumSize(QSize(16777215, 16777215))
        self.pbImageMapping.setAutoFillBackground(False)
        self.pbImageMapping.setStyleSheet(u"QPushButton\n"
"{	\n"
"	padding-left:5px;\n"
"	padding-right:5px;\n"
"}")
        icon23 = QIcon()
        icon23.addFile(u":/icon/icons8_grid_3_48px_1.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbImageMapping.setIcon(icon23)
        self.pbImageMapping.setIconSize(QSize(30, 30))
        self.pbImageMapping.setCheckable(True)
        self.pbImageMapping.setChecked(False)
        self.pbImageMapping.setAutoDefault(False)
        self.pbImageMapping.setFlat(False)

        self.gridLayout_26.addWidget(self.pbImageMapping, 13, 1, 1, 2)

        self.label_39 = QLabel(self.fCalibStep2)
        self.label_39.setObjectName(u"label_39")
        self.label_39.setAlignment(Qt.AlignCenter)

        self.gridLayout_26.addWidget(self.label_39, 3, 4, 1, 1)

        self.leRealityPoint2Y = QLineEdit(self.fCalibStep2)
        self.leRealityPoint2Y.setObjectName(u"leRealityPoint2Y")
        sizePolicy.setHeightForWidth(self.leRealityPoint2Y.sizePolicy().hasHeightForWidth())
        self.leRealityPoint2Y.setSizePolicy(sizePolicy)
        self.leRealityPoint2Y.setMinimumSize(QSize(0, 0))
        self.leRealityPoint2Y.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint2Y, 6, 4, 1, 1)

        self.tbPastePoint2 = QToolButton(self.fCalibStep2)
        self.tbPastePoint2.setObjectName(u"tbPastePoint2")
        self.tbPastePoint2.setIcon(icon22)
        self.tbPastePoint2.setIconSize(QSize(24, 24))

        self.gridLayout_26.addWidget(self.tbPastePoint2, 6, 7, 1, 1)

        self.pbCalibPoint1 = QPushButton(self.fCalibStep2)
        self.pbCalibPoint1.setObjectName(u"pbCalibPoint1")
        sizePolicy6.setHeightForWidth(self.pbCalibPoint1.sizePolicy().hasHeightForWidth())
        self.pbCalibPoint1.setSizePolicy(sizePolicy6)
        self.pbCalibPoint1.setMinimumSize(QSize(180, 0))
        self.pbCalibPoint1.setFlat(True)

        self.gridLayout_26.addWidget(self.pbCalibPoint1, 5, 6, 1, 1)

        self.leRealityPoint1X = QLineEdit(self.fCalibStep2)
        self.leRealityPoint1X.setObjectName(u"leRealityPoint1X")
        sizePolicy.setHeightForWidth(self.leRealityPoint1X.sizePolicy().hasHeightForWidth())
        self.leRealityPoint1X.setSizePolicy(sizePolicy)
        self.leRealityPoint1X.setMinimumSize(QSize(0, 0))
        self.leRealityPoint1X.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint1X, 5, 2, 1, 1)

        self.label_133 = QLabel(self.fCalibStep2)
        self.label_133.setObjectName(u"label_133")
        self.label_133.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_133, 5, 5, 1, 1)

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

        self.label_10 = QLabel(self.fCalibStep2)
        self.label_10.setObjectName(u"label_10")

        self.gridLayout_26.addWidget(self.label_10, 12, 1, 1, 10)

        self.pbCalibPoint2 = QPushButton(self.fCalibStep2)
        self.pbCalibPoint2.setObjectName(u"pbCalibPoint2")
        sizePolicy6.setHeightForWidth(self.pbCalibPoint2.sizePolicy().hasHeightForWidth())
        self.pbCalibPoint2.setSizePolicy(sizePolicy6)
        self.pbCalibPoint2.setFlat(True)

        self.gridLayout_26.addWidget(self.pbCalibPoint2, 6, 6, 1, 1)

        self.label_40 = QLabel(self.fCalibStep2)
        self.label_40.setObjectName(u"label_40")
        self.label_40.setMinimumSize(QSize(0, 0))
        self.label_40.setFont(font9)
        self.label_40.setMouseTracking(True)
        self.label_40.setTextFormat(Qt.AutoText)
        self.label_40.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_26.addWidget(self.label_40, 5, 1, 1, 1)

        self.label_139 = QLabel(self.fCalibStep2)
        self.label_139.setObjectName(u"label_139")
        self.label_139.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_139, 6, 3, 1, 1)

        self.label_142 = QLabel(self.fCalibStep2)
        self.label_142.setObjectName(u"label_142")
        self.label_142.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_142, 9, 5, 1, 1)

        self.lbCalibType = QLabel(self.fCalibStep2)
        self.lbCalibType.setObjectName(u"lbCalibType")

        self.gridLayout_26.addWidget(self.lbCalibType, 9, 1, 1, 1)

        self.lbCalibType_2 = QLabel(self.fCalibStep2)
        self.lbCalibType_2.setObjectName(u"lbCalibType_2")

        self.gridLayout_26.addWidget(self.lbCalibType_2, 8, 1, 1, 1)

        self.leRealityPoint1Y = QLineEdit(self.fCalibStep2)
        self.leRealityPoint1Y.setObjectName(u"leRealityPoint1Y")
        sizePolicy.setHeightForWidth(self.leRealityPoint1Y.sizePolicy().hasHeightForWidth())
        self.leRealityPoint1Y.setSizePolicy(sizePolicy)
        self.leRealityPoint1Y.setMinimumSize(QSize(0, 0))
        self.leRealityPoint1Y.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint1Y, 5, 4, 1, 1)

        self.lbCalibType_3 = QLabel(self.fCalibStep2)
        self.lbCalibType_3.setObjectName(u"lbCalibType_3")

        self.gridLayout_26.addWidget(self.lbCalibType_3, 11, 1, 1, 1)

        self.leRealityPoint2X = QLineEdit(self.fCalibStep2)
        self.leRealityPoint2X.setObjectName(u"leRealityPoint2X")
        sizePolicy.setHeightForWidth(self.leRealityPoint2X.sizePolicy().hasHeightForWidth())
        self.leRealityPoint2X.setSizePolicy(sizePolicy)
        self.leRealityPoint2X.setMinimumSize(QSize(0, 0))
        self.leRealityPoint2X.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_26.addWidget(self.leRealityPoint2X, 6, 2, 1, 1)

        self.label_141 = QLabel(self.fCalibStep2)
        self.label_141.setObjectName(u"label_141")
        self.label_141.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_141, 9, 3, 1, 1)

        self.label_132 = QLabel(self.fCalibStep2)
        self.label_132.setObjectName(u"label_132")
        self.label_132.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_132, 5, 3, 1, 1)

        self.label_140 = QLabel(self.fCalibStep2)
        self.label_140.setObjectName(u"label_140")
        self.label_140.setMinimumSize(QSize(0, 30))

        self.gridLayout_26.addWidget(self.label_140, 6, 5, 1, 1)

        self.label_41 = QLabel(self.fCalibStep2)
        self.label_41.setObjectName(u"label_41")
        self.label_41.setMinimumSize(QSize(0, 0))
        self.label_41.setFont(font9)
        self.label_41.setMouseTracking(True)
        self.label_41.setTextFormat(Qt.AutoText)
        self.label_41.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_26.addWidget(self.label_41, 6, 1, 1, 1)

        self.leCalibOffset_Y = QLineEdit(self.fCalibStep2)
        self.leCalibOffset_Y.setObjectName(u"leCalibOffset_Y")
        sizePolicy.setHeightForWidth(self.leCalibOffset_Y.sizePolicy().hasHeightForWidth())
        self.leCalibOffset_Y.setSizePolicy(sizePolicy)
        self.leCalibOffset_Y.setMinimumSize(QSize(0, 0))
        self.leCalibOffset_Y.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_26.addWidget(self.leCalibOffset_Y, 9, 4, 1, 1)

        self.horizontalSpacer_3 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_26.addItem(self.horizontalSpacer_3, 5, 8, 1, 1)

        self.cbCalibType = QComboBox(self.fCalibStep2)
        self.cbCalibType.addItem("")
        self.cbCalibType.addItem("")
        self.cbCalibType.setObjectName(u"cbCalibType")
        sizePolicy.setHeightForWidth(self.cbCalibType.sizePolicy().hasHeightForWidth())
        self.cbCalibType.setSizePolicy(sizePolicy)
        self.cbCalibType.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_26.addWidget(self.cbCalibType, 8, 2, 1, 2)


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

        self.leSimilarityThreshold = QLineEdit(self.frame_13)
        self.leSimilarityThreshold.setObjectName(u"leSimilarityThreshold")
        sizePolicy6.setHeightForWidth(self.leSimilarityThreshold.sizePolicy().hasHeightForWidth())
        self.leSimilarityThreshold.setSizePolicy(sizePolicy6)
        self.leSimilarityThreshold.setMinimumSize(QSize(0, 30))
        self.leSimilarityThreshold.setMaximumSize(QSize(50, 16777215))

        self.horizontalLayout_26.addWidget(self.leSimilarityThreshold)


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
        self.leLRec = QLineEdit(self.fBlobPanel)
        self.leLRec.setObjectName(u"leLRec")
        sizePolicy6.setHeightForWidth(self.leLRec.sizePolicy().hasHeightForWidth())
        self.leLRec.setSizePolicy(sizePolicy6)
        self.leLRec.setMinimumSize(QSize(0, 30))
        self.leLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leLRec, 4, 2, 1, 1)

        self.leMaxLRec = QLineEdit(self.fBlobPanel)
        self.leMaxLRec.setObjectName(u"leMaxLRec")
        sizePolicy6.setHeightForWidth(self.leMaxLRec.sizePolicy().hasHeightForWidth())
        self.leMaxLRec.setSizePolicy(sizePolicy6)
        self.leMaxLRec.setMinimumSize(QSize(0, 20))
        self.leMaxLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMaxLRec, 4, 9, 1, 1)

        self.horizontalSpacer_67 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_14.addItem(self.horizontalSpacer_67, 3, 4, 1, 1)

        self.leWRec = QLineEdit(self.fBlobPanel)
        self.leWRec.setObjectName(u"leWRec")
        sizePolicy6.setHeightForWidth(self.leWRec.sizePolicy().hasHeightForWidth())
        self.leWRec.setSizePolicy(sizePolicy6)
        self.leWRec.setMinimumSize(QSize(0, 30))
        self.leWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leWRec, 3, 2, 1, 1)

        self.leMinLRec = QLineEdit(self.fBlobPanel)
        self.leMinLRec.setObjectName(u"leMinLRec")
        sizePolicy6.setHeightForWidth(self.leMinLRec.sizePolicy().hasHeightForWidth())
        self.leMinLRec.setSizePolicy(sizePolicy6)
        self.leMinLRec.setMinimumSize(QSize(0, 20))
        self.leMinLRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMinLRec, 4, 7, 1, 1)

        self.label_42 = QLabel(self.fBlobPanel)
        self.label_42.setObjectName(u"label_42")

        self.gridLayout_14.addWidget(self.label_42, 3, 1, 1, 1)

        self.label_175 = QLabel(self.fBlobPanel)
        self.label_175.setObjectName(u"label_175")
        self.label_175.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_175, 4, 8, 1, 1)

        self.horizontalSpacer_66 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_14.addItem(self.horizontalSpacer_66, 3, 10, 1, 1)

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

        self.label_43 = QLabel(self.fBlobPanel)
        self.label_43.setObjectName(u"label_43")

        self.gridLayout_14.addWidget(self.label_43, 4, 1, 1, 1)

        self.label_163 = QLabel(self.fBlobPanel)
        self.label_163.setObjectName(u"label_163")

        self.gridLayout_14.addWidget(self.label_163, 0, 1, 1, 1)

        self.label_173 = QLabel(self.fBlobPanel)
        self.label_173.setObjectName(u"label_173")
        self.label_173.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_173, 3, 8, 1, 1)

        self.label_174 = QLabel(self.fBlobPanel)
        self.label_174.setObjectName(u"label_174")
        self.label_174.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_174, 4, 6, 1, 1)

        self.label_55 = QLabel(self.fBlobPanel)
        self.label_55.setObjectName(u"label_55")

        self.gridLayout_14.addWidget(self.label_55, 4, 3, 1, 1)

        self.label_54 = QLabel(self.fBlobPanel)
        self.label_54.setObjectName(u"label_54")

        self.gridLayout_14.addWidget(self.label_54, 3, 3, 1, 1)

        self.label_172 = QLabel(self.fBlobPanel)
        self.label_172.setObjectName(u"label_172")
        self.label_172.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_14.addWidget(self.label_172, 3, 6, 1, 1)

        self.leMaxWRec = QLineEdit(self.fBlobPanel)
        self.leMaxWRec.setObjectName(u"leMaxWRec")
        sizePolicy6.setHeightForWidth(self.leMaxWRec.sizePolicy().hasHeightForWidth())
        self.leMaxWRec.setSizePolicy(sizePolicy6)
        self.leMaxWRec.setMinimumSize(QSize(0, 20))
        self.leMaxWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMaxWRec, 3, 9, 1, 1)

        self.leMinWRec = QLineEdit(self.fBlobPanel)
        self.leMinWRec.setObjectName(u"leMinWRec")
        sizePolicy6.setHeightForWidth(self.leMinWRec.sizePolicy().hasHeightForWidth())
        self.leMinWRec.setSizePolicy(sizePolicy6)
        self.leMinWRec.setMinimumSize(QSize(0, 20))
        self.leMinWRec.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_14.addWidget(self.leMinWRec, 3, 7, 1, 1)


        self.verticalLayout_31.addWidget(self.fBlobPanel)

        self.fExternalScriptPanel = QFrame(self.fVisionObjectFrame)
        self.fExternalScriptPanel.setObjectName(u"fExternalScriptPanel")
        self.fExternalScriptPanel.setMinimumSize(QSize(0, 0))
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
        sizePolicy6.setHeightForWidth(self.pbRunExternalScript.sizePolicy().hasHeightForWidth())
        self.pbRunExternalScript.setSizePolicy(sizePolicy6)
        self.pbRunExternalScript.setMaximumSize(QSize(30, 16777215))
        icon24 = QIcon()
        icon24.addFile(u":/icon/icons8_play_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon24.addFile(u":/icon/Pause_96px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbRunExternalScript.setIcon(icon24)
        self.pbRunExternalScript.setCheckable(True)

        self.gridLayout_28.addWidget(self.pbRunExternalScript, 1, 3, 1, 1)

        self.label_145 = QLabel(self.fExternalScriptPanel)
        self.label_145.setObjectName(u"label_145")

        self.gridLayout_28.addWidget(self.label_145, 1, 0, 1, 1)

        self.pbExternalScriptOpen = QPushButton(self.fExternalScriptPanel)
        self.pbExternalScriptOpen.setObjectName(u"pbExternalScriptOpen")
        sizePolicy6.setHeightForWidth(self.pbExternalScriptOpen.sizePolicy().hasHeightForWidth())
        self.pbExternalScriptOpen.setSizePolicy(sizePolicy6)
        self.pbExternalScriptOpen.setMaximumSize(QSize(30, 16777215))
        icon25 = QIcon()
        icon25.addFile(u":/icon/icons8_folder_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbExternalScriptOpen.setIcon(icon25)

        self.gridLayout_28.addWidget(self.pbExternalScriptOpen, 1, 2, 1, 1)

        self.lePythonUrl = QLineEdit(self.fExternalScriptPanel)
        self.lePythonUrl.setObjectName(u"lePythonUrl")
        sizePolicy13 = QSizePolicy(QSizePolicy.Ignored, QSizePolicy.Preferred)
        sizePolicy13.setHorizontalStretch(0)
        sizePolicy13.setVerticalStretch(0)
        sizePolicy13.setHeightForWidth(self.lePythonUrl.sizePolicy().hasHeightForWidth())
        self.lePythonUrl.setSizePolicy(sizePolicy13)
        self.lePythonUrl.setMinimumSize(QSize(0, 30))
        self.lePythonUrl.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_28.addWidget(self.lePythonUrl, 1, 1, 1, 1)

        self.cbImageSource = QComboBox(self.fExternalScriptPanel)
        self.cbImageSource.addItem("")
        self.cbImageSource.addItem("")
        self.cbImageSource.addItem("")
        self.cbImageSource.setObjectName(u"cbImageSource")

        self.gridLayout_28.addWidget(self.cbImageSource, 2, 1, 1, 1)

        self.label_180 = QLabel(self.fExternalScriptPanel)
        self.label_180.setObjectName(u"label_180")

        self.gridLayout_28.addWidget(self.label_180, 3, 0, 1, 1)

        self.label_146 = QLabel(self.fExternalScriptPanel)
        self.label_146.setObjectName(u"label_146")

        self.gridLayout_28.addWidget(self.label_146, 2, 0, 1, 1)

        self.label_186 = QLabel(self.fExternalScriptPanel)
        self.label_186.setObjectName(u"label_186")

        self.gridLayout_28.addWidget(self.label_186, 4, 1, 1, 1)

        self.label_183 = QLabel(self.fExternalScriptPanel)
        self.label_183.setObjectName(u"label_183")

        self.gridLayout_28.addWidget(self.label_183, 3, 3, 1, 2)

        self.label_184 = QLabel(self.fExternalScriptPanel)
        self.label_184.setObjectName(u"label_184")

        self.gridLayout_28.addWidget(self.label_184, 4, 0, 1, 1)

        self.label_185 = QLabel(self.fExternalScriptPanel)
        self.label_185.setObjectName(u"label_185")

        self.gridLayout_28.addWidget(self.label_185, 5, 0, 1, 1)

        self.label_187 = QLabel(self.fExternalScriptPanel)
        self.label_187.setObjectName(u"label_187")

        self.gridLayout_28.addWidget(self.label_187, 5, 1, 1, 3)

        self.pbExternalScriptHelp = QPushButton(self.fExternalScriptPanel)
        self.pbExternalScriptHelp.setObjectName(u"pbExternalScriptHelp")
        sizePolicy6.setHeightForWidth(self.pbExternalScriptHelp.sizePolicy().hasHeightForWidth())
        self.pbExternalScriptHelp.setSizePolicy(sizePolicy6)
        self.pbExternalScriptHelp.setMaximumSize(QSize(30, 16777215))

        self.gridLayout_28.addWidget(self.pbExternalScriptHelp, 1, 4, 1, 1)

        self.label_182 = QLabel(self.fExternalScriptPanel)
        self.label_182.setObjectName(u"label_182")

        self.gridLayout_28.addWidget(self.label_182, 3, 2, 1, 1)

        self.label_181 = QLabel(self.fExternalScriptPanel)
        self.label_181.setObjectName(u"label_181")

        self.gridLayout_28.addWidget(self.label_181, 3, 1, 1, 1)

        self.pbOpenScriptExample = QPushButton(self.fExternalScriptPanel)
        self.pbOpenScriptExample.setObjectName(u"pbOpenScriptExample")
        sizePolicy14 = QSizePolicy(QSizePolicy.Maximum, QSizePolicy.Minimum)
        sizePolicy14.setHorizontalStretch(0)
        sizePolicy14.setVerticalStretch(0)
        sizePolicy14.setHeightForWidth(self.pbOpenScriptExample.sizePolicy().hasHeightForWidth())
        self.pbOpenScriptExample.setSizePolicy(sizePolicy14)
        self.pbOpenScriptExample.setMinimumSize(QSize(0, 30))
        self.pbOpenScriptExample.setStyleSheet(u"QPushButton\n"
"{\n"
"	padding: 5px;\n"
"}")

        self.gridLayout_28.addWidget(self.pbOpenScriptExample, 0, 0, 1, 1)


        self.verticalLayout_31.addWidget(self.fExternalScriptPanel)

        self.fCirclePanel = QFrame(self.fVisionObjectFrame)
        self.fCirclePanel.setObjectName(u"fCirclePanel")
        self.fCirclePanel.setMinimumSize(QSize(0, 0))
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
        self.leCenterThreshold.setMinimumSize(QSize(0, 0))
        self.leCenterThreshold.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_29.addWidget(self.leCenterThreshold, 3, 1, 1, 2)

        self.horizontalSpacer_8 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_29.addItem(self.horizontalSpacer_8, 2, 4, 1, 1)

        self.leEdgeThreshold = QLineEdit(self.fCirclePanel)
        self.leEdgeThreshold.setObjectName(u"leEdgeThreshold")
        sizePolicy10.setHeightForWidth(self.leEdgeThreshold.sizePolicy().hasHeightForWidth())
        self.leEdgeThreshold.setSizePolicy(sizePolicy10)
        self.leEdgeThreshold.setMinimumSize(QSize(0, 0))
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
        self.leMaxRadius.setMinimumSize(QSize(0, 0))
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
        self.leMinRadius.setMinimumSize(QSize(0, 0))
        self.leMinRadius.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_29.addWidget(self.leMinRadius, 4, 1, 1, 1)

        self.label_188 = QLabel(self.fCirclePanel)
        self.label_188.setObjectName(u"label_188")

        self.gridLayout_29.addWidget(self.label_188, 2, 0, 1, 1)

        self.label_198 = QLabel(self.fCirclePanel)
        self.label_198.setObjectName(u"label_198")

        self.gridLayout_29.addWidget(self.label_198, 2, 3, 1, 1)

        self.label_199 = QLabel(self.fCirclePanel)
        self.label_199.setObjectName(u"label_199")

        self.gridLayout_29.addWidget(self.label_199, 3, 3, 1, 1)


        self.verticalLayout_31.addWidget(self.fCirclePanel)


        self.verticalLayout_40.addWidget(self.fVisionObjectFrame)


        self.verticalLayout_32.addWidget(self.gbCameraObject)

        self.gbCameraVariable = QGroupBox(self.fObjectDetectingTool)
        self.gbCameraVariable.setObjectName(u"gbCameraVariable")
        self.gbCameraVariable.setFont(font6)
        self.gbCameraVariable.setStyleSheet(u"QPushButton\n"
"{\n"
"	padding:5px;\n"
"}")
        self.gbCameraVariable.setFlat(False)
        self.gbCameraVariable.setCheckable(True)
        self.verticalLayout_34 = QVBoxLayout(self.gbCameraVariable)
        self.verticalLayout_34.setSpacing(6)
        self.verticalLayout_34.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_34.setObjectName(u"verticalLayout_34")
        self.horizontalLayout_31 = QHBoxLayout()
        self.horizontalLayout_31.setSpacing(6)
        self.horizontalLayout_31.setObjectName(u"horizontalLayout_31")
        self.horizontalSpacer_50 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_31.addItem(self.horizontalSpacer_50)

        self.label_34 = QLabel(self.gbCameraVariable)
        self.label_34.setObjectName(u"label_34")

        self.horizontalLayout_31.addWidget(self.label_34)

        self.cbAutoUpdateObjectsDisplay = QComboBox(self.gbCameraVariable)
        self.cbAutoUpdateObjectsDisplay.addItem("")
        self.cbAutoUpdateObjectsDisplay.addItem("")
        self.cbAutoUpdateObjectsDisplay.setObjectName(u"cbAutoUpdateObjectsDisplay")

        self.horizontalLayout_31.addWidget(self.cbAutoUpdateObjectsDisplay)

        self.pbUpdateObjectToView = QPushButton(self.gbCameraVariable)
        self.pbUpdateObjectToView.setObjectName(u"pbUpdateObjectToView")
        sizePolicy15 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Minimum)
        sizePolicy15.setHorizontalStretch(0)
        sizePolicy15.setVerticalStretch(0)
        sizePolicy15.setHeightForWidth(self.pbUpdateObjectToView.sizePolicy().hasHeightForWidth())
        self.pbUpdateObjectToView.setSizePolicy(sizePolicy15)
        self.pbUpdateObjectToView.setMinimumSize(QSize(0, 0))
        self.pbUpdateObjectToView.setMaximumSize(QSize(16777215, 16777215))
        self.pbUpdateObjectToView.setStyleSheet(u"")
        icon26 = QIcon()
        icon26.addFile(u":/icon/icons8_replay_48px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbUpdateObjectToView.setIcon(icon26)

        self.horizontalLayout_31.addWidget(self.pbUpdateObjectToView)

        self.pbClearDetectObjects = QPushButton(self.gbCameraVariable)
        self.pbClearDetectObjects.setObjectName(u"pbClearDetectObjects")
        sizePolicy.setHeightForWidth(self.pbClearDetectObjects.sizePolicy().hasHeightForWidth())
        self.pbClearDetectObjects.setSizePolicy(sizePolicy)
        self.pbClearDetectObjects.setMinimumSize(QSize(0, 0))
        self.pbClearDetectObjects.setMaximumSize(QSize(16777215, 16777215))
        icon27 = QIcon()
        icon27.addFile(u":/icon/Eraser_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbClearDetectObjects.setIcon(icon27)

        self.horizontalLayout_31.addWidget(self.pbClearDetectObjects)


        self.verticalLayout_34.addLayout(self.horizontalLayout_31)

        self.tvObjectTable = QTableView(self.gbCameraVariable)
        self.tvObjectTable.setObjectName(u"tvObjectTable")
        self.tvObjectTable.setMinimumSize(QSize(0, 400))

        self.verticalLayout_34.addWidget(self.tvObjectTable)

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

        self.verticalLayout_35.addLayout(self.horizontalLayout_25)

        self.gridLayout_15 = QGridLayout()
        self.gridLayout_15.setSpacing(6)
        self.gridLayout_15.setObjectName(u"gridLayout_15")
        self.leLimitMinX = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMinX.setObjectName(u"leLimitMinX")

        self.gridLayout_15.addWidget(self.leLimitMinX, 1, 2, 1, 1)

        self.label_162 = QLabel(self.fVisionVariableFrame)
        self.label_162.setObjectName(u"label_162")

        self.gridLayout_15.addWidget(self.label_162, 2, 3, 1, 1)

        self.label_155 = QLabel(self.fVisionVariableFrame)
        self.label_155.setObjectName(u"label_155")

        self.gridLayout_15.addWidget(self.label_155, 1, 5, 1, 1)

        self.leLimitMaxX = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMaxX.setObjectName(u"leLimitMaxX")

        self.gridLayout_15.addWidget(self.leLimitMaxX, 1, 6, 1, 1)

        self.label_170 = QLabel(self.fVisionVariableFrame)
        self.label_170.setObjectName(u"label_170")

        self.gridLayout_15.addWidget(self.label_170, 1, 7, 1, 1)

        self.horizontalSpacer_25 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_15.addItem(self.horizontalSpacer_25, 1, 4, 1, 1)

        self.leLimitMaxY = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMaxY.setObjectName(u"leLimitMaxY")

        self.gridLayout_15.addWidget(self.leLimitMaxY, 2, 6, 1, 1)

        self.label_171 = QLabel(self.fVisionVariableFrame)
        self.label_171.setObjectName(u"label_171")

        self.gridLayout_15.addWidget(self.label_171, 2, 7, 1, 1)

        self.label_56 = QLabel(self.fVisionVariableFrame)
        self.label_56.setObjectName(u"label_56")

        self.gridLayout_15.addWidget(self.label_56, 1, 1, 1, 1)

        self.label_156 = QLabel(self.fVisionVariableFrame)
        self.label_156.setObjectName(u"label_156")

        self.gridLayout_15.addWidget(self.label_156, 2, 1, 1, 1)

        self.leLimitMinY = QLineEdit(self.fVisionVariableFrame)
        self.leLimitMinY.setObjectName(u"leLimitMinY")

        self.gridLayout_15.addWidget(self.leLimitMinY, 2, 2, 1, 1)

        self.label_159 = QLabel(self.fVisionVariableFrame)
        self.label_159.setObjectName(u"label_159")

        self.gridLayout_15.addWidget(self.label_159, 1, 3, 1, 1)

        self.label_157 = QLabel(self.fVisionVariableFrame)
        self.label_157.setObjectName(u"label_157")

        self.gridLayout_15.addWidget(self.label_157, 2, 5, 1, 1)

        self.label_196 = QLabel(self.fVisionVariableFrame)
        self.label_196.setObjectName(u"label_196")

        self.gridLayout_15.addWidget(self.label_196, 0, 0, 1, 1)

        self.label_44 = QLabel(self.fVisionVariableFrame)
        self.label_44.setObjectName(u"label_44")

        self.gridLayout_15.addWidget(self.label_44, 1, 0, 1, 1)

        self.leDetectingObjectListName = QLineEdit(self.fVisionVariableFrame)
        self.leDetectingObjectListName.setObjectName(u"leDetectingObjectListName")

        self.gridLayout_15.addWidget(self.leDetectingObjectListName, 0, 2, 1, 1)


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
        self.saPointTool = QScrollArea(self.tPointTool)
        self.saPointTool.setObjectName(u"saPointTool")
        self.saPointTool.setLineWidth(1)
        self.saPointTool.setWidgetResizable(True)
        self.wPointTool = QWidget()
        self.wPointTool.setObjectName(u"wPointTool")
        self.wPointTool.setGeometry(QRect(0, -371, 643, 1900))
        self.wPointTool.setMinimumSize(QSize(0, 1900))
        self.wPointTool.setStyleSheet(u"QWidget#wPointTool\n"
"{	\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"QFrame\n"
"{\n"
"	border: none;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: rgb(51, 51, 55);\n"
"}\n"
"\n"
"QGroupBox::title\n"
"{\n"
"	\n"
"	color: rgb(208, 208, 209);\n"
"}\n"
"\n"
"")
        self.verticalLayout_9 = QVBoxLayout(self.wPointTool)
        self.verticalLayout_9.setSpacing(6)
        self.verticalLayout_9.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.fPointTool = QFrame(self.wPointTool)
        self.fPointTool.setObjectName(u"fPointTool")
        sizePolicy.setHeightForWidth(self.fPointTool.sizePolicy().hasHeightForWidth())
        self.fPointTool.setSizePolicy(sizePolicy)
        self.fPointTool.setMinimumSize(QSize(0, 0))
        self.fPointTool.setFrameShape(QFrame.StyledPanel)
        self.fPointTool.setFrameShadow(QFrame.Raised)
        self.verticalLayout_59 = QVBoxLayout(self.fPointTool)
        self.verticalLayout_59.setSpacing(6)
        self.verticalLayout_59.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_59.setObjectName(u"verticalLayout_59")
        self.verticalLayout_59.setContentsMargins(0, 0, 0, 0)
        self.gbTrackingManager = QGroupBox(self.fPointTool)
        self.gbTrackingManager.setObjectName(u"gbTrackingManager")
        self.gbTrackingManager.setEnabled(True)
        self.gbTrackingManager.setFont(font6)
        self.gbTrackingManager.setStyleSheet(u"")
        self.gbTrackingManager.setCheckable(True)
        self.verticalLayout_60 = QVBoxLayout(self.gbTrackingManager)
        self.verticalLayout_60.setSpacing(7)
        self.verticalLayout_60.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_60.setObjectName(u"verticalLayout_60")
        self.verticalLayout_60.setContentsMargins(-1, 10, -1, 11)
        self.fTrackingManager = QFrame(self.gbTrackingManager)
        self.fTrackingManager.setObjectName(u"fTrackingManager")
        self.fTrackingManager.setMinimumSize(QSize(0, 0))
        self.fTrackingManager.setFrameShape(QFrame.StyledPanel)
        self.fTrackingManager.setFrameShadow(QFrame.Raised)
        self.gridLayout_16 = QGridLayout(self.fTrackingManager)
        self.gridLayout_16.setSpacing(6)
        self.gridLayout_16.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_16.setObjectName(u"gridLayout_16")
        self.cbSelectedTracking = QComboBox(self.fTrackingManager)
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.addItem("")
        self.cbSelectedTracking.setObjectName(u"cbSelectedTracking")
        sizePolicy10.setHeightForWidth(self.cbSelectedTracking.sizePolicy().hasHeightForWidth())
        self.cbSelectedTracking.setSizePolicy(sizePolicy10)

        self.gridLayout_16.addWidget(self.cbSelectedTracking, 0, 2, 1, 1)

        self.label_144 = QLabel(self.fTrackingManager)
        self.label_144.setObjectName(u"label_144")

        self.gridLayout_16.addWidget(self.label_144, 1, 0, 1, 1)

        self.cbReverseEncoderValue = QCheckBox(self.fTrackingManager)
        self.cbReverseEncoderValue.setObjectName(u"cbReverseEncoderValue")

        self.gridLayout_16.addWidget(self.cbReverseEncoderValue, 2, 3, 1, 1)

        self.pbSaveTrackingManager = QPushButton(self.fTrackingManager)
        self.pbSaveTrackingManager.setObjectName(u"pbSaveTrackingManager")
        sizePolicy10.setHeightForWidth(self.pbSaveTrackingManager.sizePolicy().hasHeightForWidth())
        self.pbSaveTrackingManager.setSizePolicy(sizePolicy10)
        self.pbSaveTrackingManager.setMinimumSize(QSize(0, 20))

        self.gridLayout_16.addWidget(self.pbSaveTrackingManager, 4, 0, 1, 1)

        self.label_164 = QLabel(self.fTrackingManager)
        self.label_164.setObjectName(u"label_164")

        self.gridLayout_16.addWidget(self.label_164, 2, 0, 1, 1)

        self.leSelectedTrackingObjectList = QLineEdit(self.fTrackingManager)
        self.leSelectedTrackingObjectList.setObjectName(u"leSelectedTrackingObjectList")

        self.gridLayout_16.addWidget(self.leSelectedTrackingObjectList, 1, 2, 1, 1)

        self.leVelocityVector = QLineEdit(self.fTrackingManager)
        self.leVelocityVector.setObjectName(u"leVelocityVector")

        self.gridLayout_16.addWidget(self.leVelocityVector, 3, 2, 1, 1)

        self.horizontalSpacer_24 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_16.addItem(self.horizontalSpacer_24, 1, 4, 1, 1)

        self.cbTrackingEncoderSource = QComboBox(self.fTrackingManager)
        self.cbTrackingEncoderSource.addItem("")
        self.cbTrackingEncoderSource.addItem("")
        self.cbTrackingEncoderSource.addItem("")
        self.cbTrackingEncoderSource.setObjectName(u"cbTrackingEncoderSource")
        sizePolicy.setHeightForWidth(self.cbTrackingEncoderSource.sizePolicy().hasHeightForWidth())
        self.cbTrackingEncoderSource.setSizePolicy(sizePolicy)
        self.cbTrackingEncoderSource.setMinimumSize(QSize(0, 0))

        self.gridLayout_16.addWidget(self.cbTrackingEncoderSource, 2, 2, 1, 1)

        self.label_160 = QLabel(self.fTrackingManager)
        self.label_160.setObjectName(u"label_160")

        self.gridLayout_16.addWidget(self.label_160, 0, 0, 1, 1)

        self.label_168 = QLabel(self.fTrackingManager)
        self.label_168.setObjectName(u"label_168")

        self.gridLayout_16.addWidget(self.label_168, 3, 0, 1, 1)


        self.verticalLayout_60.addWidget(self.fTrackingManager)

        self.frame = QFrame(self.gbTrackingManager)
        self.frame.setObjectName(u"frame")
        self.frame.setMinimumSize(QSize(0, 50))
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.frame.setFrameShadow(QFrame.Raised)
        self.gridLayout = QGridLayout(self.frame)
        self.gridLayout.setSpacing(6)
        self.gridLayout.setContentsMargins(11, 11, 11, 11)
        self.gridLayout.setObjectName(u"gridLayout")
        self.gridLayout.setVerticalSpacing(10)
        self.gridLayout.setContentsMargins(-1, 0, -1, 0)
        self.pbMoveTestTrackingPoint = QPushButton(self.frame)
        self.pbMoveTestTrackingPoint.setObjectName(u"pbMoveTestTrackingPoint")
        sizePolicy10.setHeightForWidth(self.pbMoveTestTrackingPoint.sizePolicy().hasHeightForWidth())
        self.pbMoveTestTrackingPoint.setSizePolicy(sizePolicy10)
        self.pbMoveTestTrackingPoint.setMinimumSize(QSize(0, 20))

        self.gridLayout.addWidget(self.pbMoveTestTrackingPoint, 2, 0, 1, 1)

        self.leTestTrackingPointX = QLineEdit(self.frame)
        self.leTestTrackingPointX.setObjectName(u"leTestTrackingPointX")

        self.gridLayout.addWidget(self.leTestTrackingPointX, 1, 1, 1, 1)

        self.label_231 = QLabel(self.frame)
        self.label_231.setObjectName(u"label_231")
        self.label_231.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_231, 0, 1, 1, 1)

        self.leTestTrackingPointZ = QLineEdit(self.frame)
        self.leTestTrackingPointZ.setObjectName(u"leTestTrackingPointZ")

        self.gridLayout.addWidget(self.leTestTrackingPointZ, 1, 4, 1, 1)

        self.label_11 = QLabel(self.frame)
        self.label_11.setObjectName(u"label_11")

        self.gridLayout.addWidget(self.label_11, 1, 0, 1, 1)

        self.label_232 = QLabel(self.frame)
        self.label_232.setObjectName(u"label_232")
        self.label_232.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout.addWidget(self.label_232, 2, 2, 1, 1)

        self.label_230 = QLabel(self.frame)
        self.label_230.setObjectName(u"label_230")
        self.label_230.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_230, 0, 2, 1, 1)

        self.leTestTrackingPointY = QLineEdit(self.frame)
        self.leTestTrackingPointY.setObjectName(u"leTestTrackingPointY")

        self.gridLayout.addWidget(self.leTestTrackingPointY, 1, 2, 1, 1)

        self.leMovingValue = QLineEdit(self.frame)
        self.leMovingValue.setObjectName(u"leMovingValue")

        self.gridLayout.addWidget(self.leMovingValue, 2, 1, 1, 1)

        self.horizontalSpacer_9 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout.addItem(self.horizontalSpacer_9, 1, 6, 1, 1)

        self.tbCopyTestTrackingPoint = QToolButton(self.frame)
        self.tbCopyTestTrackingPoint.setObjectName(u"tbCopyTestTrackingPoint")
        icon28 = QIcon()
        icon28.addFile(u":/icon/Copy.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbCopyTestTrackingPoint.setIcon(icon28)
        self.tbCopyTestTrackingPoint.setIconSize(QSize(24, 24))

        self.gridLayout.addWidget(self.tbCopyTestTrackingPoint, 1, 5, 1, 1)

        self.label_236 = QLabel(self.frame)
        self.label_236.setObjectName(u"label_236")
        self.label_236.setAlignment(Qt.AlignCenter)

        self.gridLayout.addWidget(self.label_236, 0, 4, 1, 1)


        self.verticalLayout_60.addWidget(self.frame)


        self.verticalLayout_59.addWidget(self.gbTrackingManager)

        self.gbCameraCalibration_3 = QGroupBox(self.fPointTool)
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
        self.pbAddVector = QPushButton(self.frame_19)
        self.pbAddVector.setObjectName(u"pbAddVector")
        sizePolicy12.setHeightForWidth(self.pbAddVector.sizePolicy().hasHeightForWidth())
        self.pbAddVector.setSizePolicy(sizePolicy12)
        self.pbAddVector.setMinimumSize(QSize(80, 20))

        self.gridLayout_44.addWidget(self.pbAddVector, 8, 7, 1, 1)

        self.label_197 = QLabel(self.frame_19)
        self.label_197.setObjectName(u"label_197")
        self.label_197.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_197, 5, 2, 1, 1)

        self.leVectorZ = QLineEdit(self.frame_19)
        self.leVectorZ.setObjectName(u"leVectorZ")

        self.gridLayout_44.addWidget(self.leVectorZ, 8, 6, 1, 1)

        self.lePointAtT1Z = QLineEdit(self.frame_19)
        self.lePointAtT1Z.setObjectName(u"lePointAtT1Z")

        self.gridLayout_44.addWidget(self.lePointAtT1Z, 2, 6, 1, 1)

        self.horizontalSpacer_13 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_44.addItem(self.horizontalSpacer_13, 2, 7, 1, 1)

        self.label_206 = QLabel(self.frame_19)
        self.label_206.setObjectName(u"label_206")
        self.label_206.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_206, 1, 5, 1, 1)

        self.label_229 = QLabel(self.frame_19)
        self.label_229.setObjectName(u"label_229")
        self.label_229.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_229, 7, 2, 1, 1)

        self.pbAnglePoint1 = QPushButton(self.frame_19)
        self.pbAnglePoint1.setObjectName(u"pbAnglePoint1")
        sizePolicy16 = QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Fixed)
        sizePolicy16.setHorizontalStretch(0)
        sizePolicy16.setVerticalStretch(0)
        sizePolicy16.setHeightForWidth(self.pbAnglePoint1.sizePolicy().hasHeightForWidth())
        self.pbAnglePoint1.setSizePolicy(sizePolicy16)
        self.pbAnglePoint1.setMinimumSize(QSize(0, 20))
        self.pbAnglePoint1.setFlat(True)

        self.gridLayout_44.addWidget(self.pbAnglePoint1, 2, 2, 1, 1)

        self.pbCalVector = QPushButton(self.frame_19)
        self.pbCalVector.setObjectName(u"pbCalVector")
        sizePolicy6.setHeightForWidth(self.pbCalVector.sizePolicy().hasHeightForWidth())
        self.pbCalVector.setSizePolicy(sizePolicy6)
        self.pbCalVector.setMinimumSize(QSize(80, 20))

        self.gridLayout_44.addWidget(self.pbCalVector, 6, 2, 1, 1)

        self.leVectorY = QLineEdit(self.frame_19)
        self.leVectorY.setObjectName(u"leVectorY")

        self.gridLayout_44.addWidget(self.leVectorY, 8, 5, 1, 1)

        self.lePointAtT1Y = QLineEdit(self.frame_19)
        self.lePointAtT1Y.setObjectName(u"lePointAtT1Y")

        self.gridLayout_44.addWidget(self.lePointAtT1Y, 2, 5, 1, 1)

        self.label_226 = QLabel(self.frame_19)
        self.label_226.setObjectName(u"label_226")
        self.label_226.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_226, 7, 3, 1, 1)

        self.label_228 = QLabel(self.frame_19)
        self.label_228.setObjectName(u"label_228")
        self.label_228.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_228, 7, 6, 1, 1)

        self.lePointAtT2Z = QLineEdit(self.frame_19)
        self.lePointAtT2Z.setObjectName(u"lePointAtT2Z")

        self.gridLayout_44.addWidget(self.lePointAtT2Z, 4, 6, 1, 1)

        self.label_208 = QLabel(self.frame_19)
        self.label_208.setObjectName(u"label_208")
        self.label_208.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_208, 1, 6, 1, 1)

        self.leVectorName = QLineEdit(self.frame_19)
        self.leVectorName.setObjectName(u"leVectorName")

        self.gridLayout_44.addWidget(self.leVectorName, 8, 2, 1, 1)

        self.lePointAtT2X = QLineEdit(self.frame_19)
        self.lePointAtT2X.setObjectName(u"lePointAtT2X")

        self.gridLayout_44.addWidget(self.lePointAtT2X, 4, 3, 1, 1)

        self.lePointAtT2Y = QLineEdit(self.frame_19)
        self.lePointAtT2Y.setObjectName(u"lePointAtT2Y")

        self.gridLayout_44.addWidget(self.lePointAtT2Y, 4, 5, 1, 1)

        self.label_227 = QLabel(self.frame_19)
        self.label_227.setObjectName(u"label_227")
        self.label_227.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_227, 7, 5, 1, 1)

        self.pbAnglePoint2 = QPushButton(self.frame_19)
        self.pbAnglePoint2.setObjectName(u"pbAnglePoint2")
        self.pbAnglePoint2.setMinimumSize(QSize(0, 20))
        self.pbAnglePoint2.setFlat(True)

        self.gridLayout_44.addWidget(self.pbAnglePoint2, 4, 2, 1, 1)

        self.leVectorValue = QLineEdit(self.frame_19)
        self.leVectorValue.setObjectName(u"leVectorValue")

        self.gridLayout_44.addWidget(self.leVectorValue, 5, 3, 1, 1)

        self.lwVectorList = QListWidget(self.frame_19)
        self.lwVectorList.setObjectName(u"lwVectorList")
        sizePolicy17 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.MinimumExpanding)
        sizePolicy17.setHorizontalStretch(0)
        sizePolicy17.setVerticalStretch(0)
        sizePolicy17.setHeightForWidth(self.lwVectorList.sizePolicy().hasHeightForWidth())
        self.lwVectorList.setSizePolicy(sizePolicy17)
        self.lwVectorList.setMinimumSize(QSize(0, 70))
        self.lwVectorList.setMaximumSize(QSize(16777215, 100))
        self.lwVectorList.setStyleSheet(u"background-color: rgb(118, 118, 118);\n"
"color: rgb(241, 241, 241);\n"
"border-radius: 5px;\n"
"padding: 5px;")

        self.gridLayout_44.addWidget(self.lwVectorList, 9, 6, 1, 2)

        self.label_189 = QLabel(self.frame_19)
        self.label_189.setObjectName(u"label_189")
        self.label_189.setAlignment(Qt.AlignCenter)

        self.gridLayout_44.addWidget(self.label_189, 1, 3, 1, 1)

        self.lePointAtT1X = QLineEdit(self.frame_19)
        self.lePointAtT1X.setObjectName(u"lePointAtT1X")

        self.gridLayout_44.addWidget(self.lePointAtT1X, 2, 3, 1, 1)

        self.leVectorX = QLineEdit(self.frame_19)
        self.leVectorX.setObjectName(u"leVectorX")

        self.gridLayout_44.addWidget(self.leVectorX, 8, 3, 1, 1)


        self.verticalLayout_63.addWidget(self.frame_19)


        self.verticalLayout_59.addWidget(self.gbCameraCalibration_3)

        self.gbCameraCalibration_2 = QGroupBox(self.fPointTool)
        self.gbCameraCalibration_2.setObjectName(u"gbCameraCalibration_2")
        self.gbCameraCalibration_2.setFont(font6)
        self.gbCameraCalibration_2.setCheckable(True)
        self.gbCameraCalibration_2.setChecked(True)
        self.verticalLayout_62 = QVBoxLayout(self.gbCameraCalibration_2)
        self.verticalLayout_62.setSpacing(6)
        self.verticalLayout_62.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_62.setObjectName(u"verticalLayout_62")
        self.frame_18 = QFrame(self.gbCameraCalibration_2)
        self.frame_18.setObjectName(u"frame_18")
        self.frame_18.setMinimumSize(QSize(0, 0))
        self.frame_18.setFrameShape(QFrame.StyledPanel)
        self.frame_18.setFrameShadow(QFrame.Raised)
        self.gridLayout_41 = QGridLayout(self.frame_18)
        self.gridLayout_41.setSpacing(6)
        self.gridLayout_41.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_41.setObjectName(u"gridLayout_41")
        self.gridLayout_41.setVerticalSpacing(4)
        self.label_205 = QLabel(self.frame_18)
        self.label_205.setObjectName(u"label_205")

        self.gridLayout_41.addWidget(self.label_205, 7, 3, 1, 1)

        self.leDestinationPoint2Y = QLineEdit(self.frame_18)
        self.leDestinationPoint2Y.setObjectName(u"leDestinationPoint2Y")

        self.gridLayout_41.addWidget(self.leDestinationPoint2Y, 7, 6, 1, 1)

        self.leSourcePoint1X = QLineEdit(self.frame_18)
        self.leSourcePoint1X.setObjectName(u"leSourcePoint1X")

        self.gridLayout_41.addWidget(self.leSourcePoint1X, 2, 4, 1, 1)

        self.label_201 = QLabel(self.frame_18)
        self.label_201.setObjectName(u"label_201")

        self.gridLayout_41.addWidget(self.label_201, 3, 3, 1, 1)

        self.leDestinationPoint1X = QLineEdit(self.frame_18)
        self.leDestinationPoint1X.setObjectName(u"leDestinationPoint1X")

        self.gridLayout_41.addWidget(self.leDestinationPoint1X, 6, 4, 1, 1)

        self.leSourcePoint2X = QLineEdit(self.frame_18)
        self.leSourcePoint2X.setObjectName(u"leSourcePoint2X")

        self.gridLayout_41.addWidget(self.leSourcePoint2X, 3, 4, 1, 1)

        self.horizontalSpacer_41 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_41.addItem(self.horizontalSpacer_41, 7, 7, 1, 1)

        self.leMatrixName = QLineEdit(self.frame_18)
        self.leMatrixName.setObjectName(u"leMatrixName")

        self.gridLayout_41.addWidget(self.leMatrixName, 2, 1, 1, 1)

        self.leSourcePoint1Y = QLineEdit(self.frame_18)
        self.leSourcePoint1Y.setObjectName(u"leSourcePoint1Y")

        self.gridLayout_41.addWidget(self.leSourcePoint1Y, 2, 6, 1, 1)

        self.label_203 = QLabel(self.frame_18)
        self.label_203.setObjectName(u"label_203")

        self.gridLayout_41.addWidget(self.label_203, 2, 3, 1, 1)

        self.label_165 = QLabel(self.frame_18)
        self.label_165.setObjectName(u"label_165")

        self.gridLayout_41.addWidget(self.label_165, 2, 0, 1, 1)

        self.label_166 = QLabel(self.frame_18)
        self.label_166.setObjectName(u"label_166")
        font10 = QFont()
        font10.setBold(True)
        self.label_166.setFont(font10)

        self.gridLayout_41.addWidget(self.label_166, 1, 3, 1, 1)

        self.leSourcePoint2Y = QLineEdit(self.frame_18)
        self.leSourcePoint2Y.setObjectName(u"leSourcePoint2Y")

        self.gridLayout_41.addWidget(self.leSourcePoint2Y, 3, 6, 1, 1)

        self.pbCalculateMappingMatrixTool = QPushButton(self.frame_18)
        self.pbCalculateMappingMatrixTool.setObjectName(u"pbCalculateMappingMatrixTool")
        self.pbCalculateMappingMatrixTool.setMinimumSize(QSize(0, 20))

        self.gridLayout_41.addWidget(self.pbCalculateMappingMatrixTool, 3, 1, 1, 1)

        self.label_202 = QLabel(self.frame_18)
        self.label_202.setObjectName(u"label_202")
        self.label_202.setAlignment(Qt.AlignCenter)

        self.gridLayout_41.addWidget(self.label_202, 1, 6, 1, 1)

        self.leDestinationPoint2X = QLineEdit(self.frame_18)
        self.leDestinationPoint2X.setObjectName(u"leDestinationPoint2X")

        self.gridLayout_41.addWidget(self.leDestinationPoint2X, 7, 4, 1, 1)

        self.label_204 = QLabel(self.frame_18)
        self.label_204.setObjectName(u"label_204")

        self.gridLayout_41.addWidget(self.label_204, 6, 3, 1, 1)

        self.label_177 = QLabel(self.frame_18)
        self.label_177.setObjectName(u"label_177")
        self.label_177.setAlignment(Qt.AlignCenter)

        self.gridLayout_41.addWidget(self.label_177, 1, 4, 1, 1)

        self.leDestinationPoint1Y = QLineEdit(self.frame_18)
        self.leDestinationPoint1Y.setObjectName(u"leDestinationPoint1Y")

        self.gridLayout_41.addWidget(self.leDestinationPoint1Y, 6, 6, 1, 1)

        self.pbAddMappingMatrix = QPushButton(self.frame_18)
        self.pbAddMappingMatrix.setObjectName(u"pbAddMappingMatrix")
        self.pbAddMappingMatrix.setMinimumSize(QSize(0, 20))

        self.gridLayout_41.addWidget(self.pbAddMappingMatrix, 8, 6, 1, 1)

        self.label_200 = QLabel(self.frame_18)
        self.label_200.setObjectName(u"label_200")
        self.label_200.setFont(font10)

        self.gridLayout_41.addWidget(self.label_200, 5, 3, 1, 1)

        self.lwMappingMatrixList = QListWidget(self.frame_18)
        self.lwMappingMatrixList.setObjectName(u"lwMappingMatrixList")
        sizePolicy17.setHeightForWidth(self.lwMappingMatrixList.sizePolicy().hasHeightForWidth())
        self.lwMappingMatrixList.setSizePolicy(sizePolicy17)
        self.lwMappingMatrixList.setMinimumSize(QSize(0, 70))
        self.lwMappingMatrixList.setMaximumSize(QSize(16777215, 100))
        self.lwMappingMatrixList.setStyleSheet(u"background-color: rgb(118, 118, 118);\n"
"color: rgb(241, 241, 241);\n"
"border-radius: 5px;\n"
"padding: 5px;")

        self.gridLayout_41.addWidget(self.lwMappingMatrixList, 9, 4, 1, 3)

        self.lbMatrixDisplay = QLabel(self.frame_18)
        self.lbMatrixDisplay.setObjectName(u"lbMatrixDisplay")

        self.gridLayout_41.addWidget(self.lbMatrixDisplay, 5, 1, 3, 1)


        self.verticalLayout_62.addWidget(self.frame_18)


        self.verticalLayout_59.addWidget(self.gbCameraCalibration_2)

        self.gbCameraObject_2 = QGroupBox(self.fPointTool)
        self.gbCameraObject_2.setObjectName(u"gbCameraObject_2")
        self.gbCameraObject_2.setFont(font6)
        self.gbCameraObject_2.setCheckable(True)
        self.verticalLayout_64 = QVBoxLayout(self.gbCameraObject_2)
        self.verticalLayout_64.setSpacing(6)
        self.verticalLayout_64.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_64.setObjectName(u"verticalLayout_64")
        self.verticalLayout_64.setContentsMargins(-1, 10, -1, -1)
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

        self.leObjectListName = QLineEdit(self.frame_14)
        self.leObjectListName.setObjectName(u"leObjectListName")

        self.horizontalLayout_5.addWidget(self.leObjectListName)

        self.label_137 = QLabel(self.frame_14)
        self.label_137.setObjectName(u"label_137")

        self.horizontalLayout_5.addWidget(self.label_137)

        self.leObjectX = QLineEdit(self.frame_14)
        self.leObjectX.setObjectName(u"leObjectX")

        self.horizontalLayout_5.addWidget(self.leObjectX)

        self.label_138 = QLabel(self.frame_14)
        self.label_138.setObjectName(u"label_138")

        self.horizontalLayout_5.addWidget(self.label_138)

        self.leObjectY = QLineEdit(self.frame_14)
        self.leObjectY.setObjectName(u"leObjectY")

        self.horizontalLayout_5.addWidget(self.leObjectY)

        self.label_143 = QLabel(self.frame_14)
        self.label_143.setObjectName(u"label_143")

        self.horizontalLayout_5.addWidget(self.label_143)

        self.leObjectZ = QLineEdit(self.frame_14)
        self.leObjectZ.setObjectName(u"leObjectZ")

        self.horizontalLayout_5.addWidget(self.leObjectZ)

        self.pbAddVariablePoint = QPushButton(self.frame_14)
        self.pbAddVariablePoint.setObjectName(u"pbAddVariablePoint")
        sizePolicy12.setHeightForWidth(self.pbAddVariablePoint.sizePolicy().hasHeightForWidth())
        self.pbAddVariablePoint.setSizePolicy(sizePolicy12)
        self.pbAddVariablePoint.setMinimumSize(QSize(80, 20))

        self.horizontalLayout_5.addWidget(self.pbAddVariablePoint)

        self.horizontalSpacer_43 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_5.addItem(self.horizontalSpacer_43)


        self.verticalLayout_64.addWidget(self.frame_14)


        self.verticalLayout_59.addWidget(self.gbCameraObject_2)

        self.gbCameraObject_3 = QGroupBox(self.fPointTool)
        self.gbCameraObject_3.setObjectName(u"gbCameraObject_3")
        self.gbCameraObject_3.setFont(font6)
        self.gbCameraObject_3.setCheckable(True)
        self.verticalLayout_65 = QVBoxLayout(self.gbCameraObject_3)
        self.verticalLayout_65.setSpacing(6)
        self.verticalLayout_65.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_65.setObjectName(u"verticalLayout_65")
        self.verticalLayout_65.setContentsMargins(-1, 10, -1, -1)
        self.frame_20 = QFrame(self.gbCameraObject_3)
        self.frame_20.setObjectName(u"frame_20")
        self.frame_20.setMinimumSize(QSize(0, 0))
        self.frame_20.setFrameShape(QFrame.StyledPanel)
        self.frame_20.setFrameShadow(QFrame.Raised)
        self.gridLayout_42 = QGridLayout(self.frame_20)
        self.gridLayout_42.setSpacing(6)
        self.gridLayout_42.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_42.setObjectName(u"gridLayout_42")
        self.leDPoint2Y = QLineEdit(self.frame_20)
        self.leDPoint2Y.setObjectName(u"leDPoint2Y")

        self.gridLayout_42.addWidget(self.leDPoint2Y, 8, 5, 1, 1)

        self.leSPoint3Y = QLineEdit(self.frame_20)
        self.leSPoint3Y.setObjectName(u"leSPoint3Y")

        self.gridLayout_42.addWidget(self.leSPoint3Y, 4, 5, 1, 1)

        self.leDPoint1X = QLineEdit(self.frame_20)
        self.leDPoint1X.setObjectName(u"leDPoint1X")

        self.gridLayout_42.addWidget(self.leDPoint1X, 7, 3, 1, 1)

        self.label_212 = QLabel(self.frame_20)
        self.label_212.setObjectName(u"label_212")

        self.gridLayout_42.addWidget(self.label_212, 4, 2, 1, 1)

        self.pbAddPointMatrix = QPushButton(self.frame_20)
        self.pbAddPointMatrix.setObjectName(u"pbAddPointMatrix")
        self.pbAddPointMatrix.setMinimumSize(QSize(0, 20))

        self.gridLayout_42.addWidget(self.pbAddPointMatrix, 11, 5, 1, 1)

        self.label_217 = QLabel(self.frame_20)
        self.label_217.setObjectName(u"label_217")

        self.gridLayout_42.addWidget(self.label_217, 2, 2, 1, 1)

        self.leDPoint2X = QLineEdit(self.frame_20)
        self.leDPoint2X.setObjectName(u"leDPoint2X")

        self.gridLayout_42.addWidget(self.leDPoint2X, 8, 3, 1, 1)

        self.leDPoint4X = QLineEdit(self.frame_20)
        self.leDPoint4X.setObjectName(u"leDPoint4X")

        self.gridLayout_42.addWidget(self.leDPoint4X, 10, 3, 1, 1)

        self.label_207 = QLabel(self.frame_20)
        self.label_207.setObjectName(u"label_207")
        self.label_207.setFont(font10)

        self.gridLayout_42.addWidget(self.label_207, 6, 2, 1, 1)

        self.horizontalSpacer_55 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_42.addItem(self.horizontalSpacer_55, 1, 6, 1, 1)

        self.label_211 = QLabel(self.frame_20)
        self.label_211.setObjectName(u"label_211")

        self.gridLayout_42.addWidget(self.label_211, 1, 2, 1, 1)

        self.leSPoint2Y = QLineEdit(self.frame_20)
        self.leSPoint2Y.setObjectName(u"leSPoint2Y")

        self.gridLayout_42.addWidget(self.leSPoint2Y, 2, 5, 1, 1)

        self.leSPoint1X = QLineEdit(self.frame_20)
        self.leSPoint1X.setObjectName(u"leSPoint1X")

        self.gridLayout_42.addWidget(self.leSPoint1X, 1, 3, 1, 1)

        self.label_218 = QLabel(self.frame_20)
        self.label_218.setObjectName(u"label_218")
        self.label_218.setAlignment(Qt.AlignCenter)

        self.gridLayout_42.addWidget(self.label_218, 0, 3, 1, 1)

        self.label_210 = QLabel(self.frame_20)
        self.label_210.setObjectName(u"label_210")
        self.label_210.setAlignment(Qt.AlignCenter)

        self.gridLayout_42.addWidget(self.label_210, 0, 5, 1, 1)

        self.leDPoint3Y = QLineEdit(self.frame_20)
        self.leDPoint3Y.setObjectName(u"leDPoint3Y")

        self.gridLayout_42.addWidget(self.leDPoint3Y, 9, 5, 1, 1)

        self.lePointMatrixName = QLineEdit(self.frame_20)
        self.lePointMatrixName.setObjectName(u"lePointMatrixName")

        self.gridLayout_42.addWidget(self.lePointMatrixName, 1, 1, 1, 1)

        self.leSPoint1Y = QLineEdit(self.frame_20)
        self.leSPoint1Y.setObjectName(u"leSPoint1Y")

        self.gridLayout_42.addWidget(self.leSPoint1Y, 1, 5, 1, 1)

        self.lbPointMatrixDisplay = QLabel(self.frame_20)
        self.lbPointMatrixDisplay.setObjectName(u"lbPointMatrixDisplay")

        self.gridLayout_42.addWidget(self.lbPointMatrixDisplay, 4, 1, 3, 1)

        self.label_219 = QLabel(self.frame_20)
        self.label_219.setObjectName(u"label_219")

        self.gridLayout_42.addWidget(self.label_219, 5, 2, 1, 1)

        self.label_234 = QLabel(self.frame_20)
        self.label_234.setObjectName(u"label_234")

        self.gridLayout_42.addWidget(self.label_234, 9, 2, 1, 1)

        self.leDPoint1Y = QLineEdit(self.frame_20)
        self.leDPoint1Y.setObjectName(u"leDPoint1Y")

        self.gridLayout_42.addWidget(self.leDPoint1Y, 7, 5, 1, 1)

        self.label_216 = QLabel(self.frame_20)
        self.label_216.setObjectName(u"label_216")

        self.gridLayout_42.addWidget(self.label_216, 1, 0, 1, 1)

        self.label_220 = QLabel(self.frame_20)
        self.label_220.setObjectName(u"label_220")

        self.gridLayout_42.addWidget(self.label_220, 7, 2, 1, 1)

        self.label_235 = QLabel(self.frame_20)
        self.label_235.setObjectName(u"label_235")

        self.gridLayout_42.addWidget(self.label_235, 10, 2, 1, 1)

        self.label_167 = QLabel(self.frame_20)
        self.label_167.setObjectName(u"label_167")
        self.label_167.setFont(font10)

        self.gridLayout_42.addWidget(self.label_167, 0, 2, 1, 1)

        self.leSPoint4X = QLineEdit(self.frame_20)
        self.leSPoint4X.setObjectName(u"leSPoint4X")

        self.gridLayout_42.addWidget(self.leSPoint4X, 5, 3, 1, 1)

        self.pbCalculatePointMatrixTool = QPushButton(self.frame_20)
        self.pbCalculatePointMatrixTool.setObjectName(u"pbCalculatePointMatrixTool")
        self.pbCalculatePointMatrixTool.setMinimumSize(QSize(0, 20))

        self.gridLayout_42.addWidget(self.pbCalculatePointMatrixTool, 2, 1, 1, 1)

        self.leDPoint3X = QLineEdit(self.frame_20)
        self.leDPoint3X.setObjectName(u"leDPoint3X")

        self.gridLayout_42.addWidget(self.leDPoint3X, 9, 3, 1, 1)

        self.leDPoint4Y = QLineEdit(self.frame_20)
        self.leDPoint4Y.setObjectName(u"leDPoint4Y")

        self.gridLayout_42.addWidget(self.leDPoint4Y, 10, 5, 1, 1)

        self.leSPoint2X = QLineEdit(self.frame_20)
        self.leSPoint2X.setObjectName(u"leSPoint2X")

        self.gridLayout_42.addWidget(self.leSPoint2X, 2, 3, 1, 1)

        self.leSPoint4Y = QLineEdit(self.frame_20)
        self.leSPoint4Y.setObjectName(u"leSPoint4Y")

        self.gridLayout_42.addWidget(self.leSPoint4Y, 5, 5, 1, 1)

        self.label_233 = QLabel(self.frame_20)
        self.label_233.setObjectName(u"label_233")

        self.gridLayout_42.addWidget(self.label_233, 8, 2, 1, 1)

        self.leSPoint3X = QLineEdit(self.frame_20)
        self.leSPoint3X.setObjectName(u"leSPoint3X")

        self.gridLayout_42.addWidget(self.leSPoint3X, 4, 3, 1, 1)

        self.lwPointMatrixList = QListWidget(self.frame_20)
        self.lwPointMatrixList.setObjectName(u"lwPointMatrixList")
        sizePolicy17.setHeightForWidth(self.lwPointMatrixList.sizePolicy().hasHeightForWidth())
        self.lwPointMatrixList.setSizePolicy(sizePolicy17)
        self.lwPointMatrixList.setMinimumSize(QSize(0, 70))
        self.lwPointMatrixList.setMaximumSize(QSize(16777215, 100))
        self.lwPointMatrixList.setStyleSheet(u"background-color: rgb(118, 118, 118);\n"
"color: rgb(241, 241, 241);\n"
"border-radius: 5px;\n"
"padding: 5px;")

        self.gridLayout_42.addWidget(self.lwPointMatrixList, 12, 3, 1, 3)


        self.verticalLayout_65.addWidget(self.frame_20)


        self.verticalLayout_59.addWidget(self.gbCameraObject_3)

        self.gbCameraObject_4 = QGroupBox(self.fPointTool)
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
        sizePolicy5.setHeightForWidth(self.leTestPointY.sizePolicy().hasHeightForWidth())
        self.leTestPointY.setSizePolicy(sizePolicy5)

        self.gridLayout_43.addWidget(self.leTestPointY, 2, 3, 1, 1)

        self.leTestPointX = QLineEdit(self.frame_21)
        self.leTestPointX.setObjectName(u"leTestPointX")
        sizePolicy5.setHeightForWidth(self.leTestPointX.sizePolicy().hasHeightForWidth())
        self.leTestPointX.setSizePolicy(sizePolicy5)

        self.gridLayout_43.addWidget(self.leTestPointX, 2, 2, 1, 1)

        self.label_223 = QLabel(self.frame_21)
        self.label_223.setObjectName(u"label_223")

        self.gridLayout_43.addWidget(self.label_223, 2, 4, 1, 1)

        self.leTestMatrixName = QLineEdit(self.frame_21)
        self.leTestMatrixName.setObjectName(u"leTestMatrixName")
        sizePolicy18 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Fixed)
        sizePolicy18.setHorizontalStretch(0)
        sizePolicy18.setVerticalStretch(0)
        sizePolicy18.setHeightForWidth(self.leTestMatrixName.sizePolicy().hasHeightForWidth())
        self.leTestMatrixName.setSizePolicy(sizePolicy18)
        self.leTestMatrixName.setMinimumSize(QSize(0, 0))

        self.gridLayout_43.addWidget(self.leTestMatrixName, 2, 5, 1, 1)

        self.leTargetTestPointX = QLineEdit(self.frame_21)
        self.leTargetTestPointX.setObjectName(u"leTargetTestPointX")
        sizePolicy5.setHeightForWidth(self.leTargetTestPointX.sizePolicy().hasHeightForWidth())
        self.leTargetTestPointX.setSizePolicy(sizePolicy5)

        self.gridLayout_43.addWidget(self.leTargetTestPointX, 5, 2, 1, 1)

        self.leTargetTestPointY = QLineEdit(self.frame_21)
        self.leTargetTestPointY.setObjectName(u"leTargetTestPointY")
        sizePolicy5.setHeightForWidth(self.leTargetTestPointY.sizePolicy().hasHeightForWidth())
        self.leTargetTestPointY.setSizePolicy(sizePolicy5)

        self.gridLayout_43.addWidget(self.leTargetTestPointY, 5, 3, 1, 1)

        self.label_214 = QLabel(self.frame_21)
        self.label_214.setObjectName(u"label_214")
        self.label_214.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_214, 4, 3, 1, 1)

        self.label_215 = QLabel(self.frame_21)
        self.label_215.setObjectName(u"label_215")
        self.label_215.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_215, 1, 2, 1, 2)

        self.pbCalculateTestPoint = QPushButton(self.frame_21)
        self.pbCalculateTestPoint.setObjectName(u"pbCalculateTestPoint")
        sizePolicy5.setHeightForWidth(self.pbCalculateTestPoint.sizePolicy().hasHeightForWidth())
        self.pbCalculateTestPoint.setSizePolicy(sizePolicy5)
        self.pbCalculateTestPoint.setMinimumSize(QSize(0, 20))

        self.gridLayout_43.addWidget(self.pbCalculateTestPoint, 3, 2, 1, 1)

        self.label_222 = QLabel(self.frame_21)
        self.label_222.setObjectName(u"label_222")
        self.label_222.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_222, 1, 5, 1, 1)

        self.label_221 = QLabel(self.frame_21)
        self.label_221.setObjectName(u"label_221")
        self.label_221.setAlignment(Qt.AlignCenter)

        self.gridLayout_43.addWidget(self.label_221, 4, 2, 1, 1)

        self.horizontalSpacer_56 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_43.addItem(self.horizontalSpacer_56, 2, 6, 1, 1)


        self.verticalLayout_66.addWidget(self.frame_21)


        self.verticalLayout_59.addWidget(self.gbCameraObject_4)

        self.verticalSpacer_18 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_59.addItem(self.verticalSpacer_18)


        self.verticalLayout_9.addWidget(self.fPointTool)

        self.saPointTool.setWidget(self.wPointTool)

        self.verticalLayout_14.addWidget(self.saPointTool)

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
        self.scrollAreaWidgetContents_6.setGeometry(QRect(0, 0, 643, 1600))
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
        sizePolicy6.setHeightForWidth(self.frame_4.sizePolicy().hasHeightForWidth())
        self.frame_4.setSizePolicy(sizePolicy6)
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
        sizePolicy19 = QSizePolicy(QSizePolicy.Fixed, QSizePolicy.Fixed)
        sizePolicy19.setHorizontalStretch(0)
        sizePolicy19.setVerticalStretch(0)
        sizePolicy19.setHeightForWidth(self.pbOpenPicture.sizePolicy().hasHeightForWidth())
        self.pbOpenPicture.setSizePolicy(sizePolicy19)
        self.pbOpenPicture.setMinimumSize(QSize(0, 0))
        self.pbOpenPicture.setMaximumSize(QSize(16777215, 16777215))
        font11 = QFont()
        font11.setPointSize(10)
        font11.setBold(False)
        self.pbOpenPicture.setFont(font11)
        self.pbOpenPicture.setLayoutDirection(Qt.LeftToRight)
        icon29 = QIcon()
        icon29.addFile(u":/icon/icons8_image_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbOpenPicture.setIcon(icon29)
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
        sizePolicy4.setHeightForWidth(self.frame_5.sizePolicy().hasHeightForWidth())
        self.frame_5.setSizePolicy(sizePolicy4)
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
        sizePolicy19.setHeightForWidth(self.pbPainting.sizePolicy().hasHeightForWidth())
        self.pbPainting.setSizePolicy(sizePolicy19)
        self.pbPainting.setMinimumSize(QSize(0, 0))
        self.pbPainting.setMaximumSize(QSize(16777215, 16777215))
        self.pbPainting.setFont(font11)
        icon30 = QIcon()
        icon30.addFile(u":/icon/icons8_pencil_drawing_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbPainting.setIcon(icon30)
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
        sizePolicy6.setHeightForWidth(self.frame_3.sizePolicy().hasHeightForWidth())
        self.frame_3.setSizePolicy(sizePolicy6)
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
        sizePolicy20 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Preferred)
        sizePolicy20.setHorizontalStretch(0)
        sizePolicy20.setVerticalStretch(0)
        sizePolicy20.setHeightForWidth(self.leDrawAg5.sizePolicy().hasHeightForWidth())
        self.leDrawAg5.setSizePolicy(sizePolicy20)
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
        sizePolicy20.setHeightForWidth(self.leDrawAg4.sizePolicy().hasHeightForWidth())
        self.leDrawAg4.setSizePolicy(sizePolicy20)
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
        sizePolicy20.setHeightForWidth(self.leDrawAg3.sizePolicy().hasHeightForWidth())
        self.leDrawAg3.setSizePolicy(sizePolicy20)
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
        sizePolicy20.setHeightForWidth(self.leDrawAg2.sizePolicy().hasHeightForWidth())
        self.leDrawAg2.setSizePolicy(sizePolicy20)
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
        sizePolicy20.setHeightForWidth(self.leDrawAg1.sizePolicy().hasHeightForWidth())
        self.leDrawAg1.setSizePolicy(sizePolicy20)
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
        sizePolicy18.setHeightForWidth(self.pbDrawLine.sizePolicy().hasHeightForWidth())
        self.pbDrawLine.setSizePolicy(sizePolicy18)
        self.pbDrawLine.setMinimumSize(QSize(0, 0))
        self.pbDrawLine.setMaximumSize(QSize(70, 16777215))
        icon31 = QIcon()
        icon31.addFile(u":/icon/Line_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawLine.setIcon(icon31)
        self.pbDrawLine.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawLine.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawLine, 0, 0, 1, 1)

        self.pbDrawRectangle = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbDrawRectangle.setObjectName(u"pbDrawRectangle")
        sizePolicy18.setHeightForWidth(self.pbDrawRectangle.sizePolicy().hasHeightForWidth())
        self.pbDrawRectangle.setSizePolicy(sizePolicy18)
        self.pbDrawRectangle.setMinimumSize(QSize(0, 0))
        self.pbDrawRectangle.setMaximumSize(QSize(70, 16777215))
        icon32 = QIcon()
        icon32.addFile(u":/icon/Rectangular_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawRectangle.setIcon(icon32)
        self.pbDrawRectangle.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawRectangle.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawRectangle, 0, 1, 1, 1)

        self.pbZoomIn = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbZoomIn.setObjectName(u"pbZoomIn")
        sizePolicy18.setHeightForWidth(self.pbZoomIn.sizePolicy().hasHeightForWidth())
        self.pbZoomIn.setSizePolicy(sizePolicy18)
        self.pbZoomIn.setMinimumSize(QSize(0, 0))
        self.pbZoomIn.setMaximumSize(QSize(70, 16777215))
        icon33 = QIcon()
        icon33.addFile(u":/icon/Zoom In_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbZoomIn.setIcon(icon33)
        self.pbZoomIn.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbZoomIn.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbZoomIn, 0, 2, 1, 1)

        self.pbCursor = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbCursor.setObjectName(u"pbCursor")
        sizePolicy18.setHeightForWidth(self.pbCursor.sizePolicy().hasHeightForWidth())
        self.pbCursor.setSizePolicy(sizePolicy18)
        self.pbCursor.setMinimumSize(QSize(0, 0))
        self.pbCursor.setMaximumSize(QSize(70, 16777215))
        icon34 = QIcon()
        icon34.addFile(u":/icon/Cursor-color_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbCursor.setIcon(icon34)
        self.pbCursor.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbCursor.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbCursor, 0, 3, 1, 1)

        self.pbDrawArc = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbDrawArc.setObjectName(u"pbDrawArc")
        sizePolicy18.setHeightForWidth(self.pbDrawArc.sizePolicy().hasHeightForWidth())
        self.pbDrawArc.setSizePolicy(sizePolicy18)
        self.pbDrawArc.setMinimumSize(QSize(0, 0))
        self.pbDrawArc.setMaximumSize(QSize(70, 16777215))
        icon35 = QIcon()
        icon35.addFile(u":/icon/Circled Notch_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawArc.setIcon(icon35)
        self.pbDrawArc.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawArc.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawArc, 1, 0, 1, 1)

        self.pbDrawCircle = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbDrawCircle.setObjectName(u"pbDrawCircle")
        sizePolicy18.setHeightForWidth(self.pbDrawCircle.sizePolicy().hasHeightForWidth())
        self.pbDrawCircle.setSizePolicy(sizePolicy18)
        self.pbDrawCircle.setMinimumSize(QSize(0, 0))
        self.pbDrawCircle.setMaximumSize(QSize(70, 16777215))
        icon36 = QIcon()
        icon36.addFile(u":/icon/Circle_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbDrawCircle.setIcon(icon36)
        self.pbDrawCircle.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbDrawCircle.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbDrawCircle, 1, 1, 1, 1)

        self.pbZoomOut = QToolButton(self.scrollAreaWidgetContents_6)
        self.pbZoomOut.setObjectName(u"pbZoomOut")
        sizePolicy18.setHeightForWidth(self.pbZoomOut.sizePolicy().hasHeightForWidth())
        self.pbZoomOut.setSizePolicy(sizePolicy18)
        self.pbZoomOut.setMinimumSize(QSize(0, 0))
        self.pbZoomOut.setMaximumSize(QSize(70, 16777215))
        icon37 = QIcon()
        icon37.addFile(u":/icon/Zoom Out_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbZoomOut.setIcon(icon37)
        self.pbZoomOut.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbZoomOut.setAutoRaise(True)

        self.gridLayout_11.addWidget(self.pbZoomOut, 1, 2, 1, 1)


        self.verticalLayout_37.addLayout(self.gridLayout_11)

        self.frame_6 = QFrame(self.scrollAreaWidgetContents_6)
        self.frame_6.setObjectName(u"frame_6")
        sizePolicy4.setHeightForWidth(self.frame_6.sizePolicy().hasHeightForWidth())
        self.frame_6.setSizePolicy(sizePolicy4)
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
        sizePolicy19.setHeightForWidth(self.pbExportDrawingGcodes.sizePolicy().hasHeightForWidth())
        self.pbExportDrawingGcodes.setSizePolicy(sizePolicy19)
        self.pbExportDrawingGcodes.setMinimumSize(QSize(185, 65))
        self.pbExportDrawingGcodes.setMaximumSize(QSize(16777215, 16777215))
        self.pbExportDrawingGcodes.setFont(font11)
        icon38 = QIcon()
        icon38.addFile(u":/icon/icons8_code_96px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbExportDrawingGcodes.setIcon(icon38)
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
        sizePolicy7.setHeightForWidth(self.label_96.sizePolicy().hasHeightForWidth())
        self.label_96.setSizePolicy(sizePolicy7)
        self.label_96.setMinimumSize(QSize(0, 0))
        self.label_96.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_96, 4, 0, 1, 1)

        self.label_101 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_101.setObjectName(u"label_101")
        sizePolicy.setHeightForWidth(self.label_101.sizePolicy().hasHeightForWidth())
        self.label_101.setSizePolicy(sizePolicy)
        self.label_101.setMinimumSize(QSize(0, 0))
        font12 = QFont()
        font12.setItalic(False)
        self.label_101.setFont(font12)
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
        sizePolicy7.setHeightForWidth(self.label_97.sizePolicy().hasHeightForWidth())
        self.label_97.setSizePolicy(sizePolicy7)
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
        sizePolicy4.setHeightForWidth(self.cbDrawingEffector.sizePolicy().hasHeightForWidth())
        self.cbDrawingEffector.setSizePolicy(sizePolicy4)
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
        self.label_102.setFont(font12)
        self.label_102.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_102, 7, 2, 1, 1)

        self.label_93 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_93.setObjectName(u"label_93")
        sizePolicy2.setHeightForWidth(self.label_93.sizePolicy().hasHeightForWidth())
        self.label_93.setSizePolicy(sizePolicy2)
        self.label_93.setMinimumSize(QSize(0, 0))
        self.label_93.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_93, 0, 0, 1, 1)

        self.label_95 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_95.setObjectName(u"label_95")
        sizePolicy7.setHeightForWidth(self.label_95.sizePolicy().hasHeightForWidth())
        self.label_95.setSizePolicy(sizePolicy7)
        self.label_95.setMinimumSize(QSize(0, 0))
        self.label_95.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_95, 3, 0, 1, 1)

        self.label_100 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_100.setObjectName(u"label_100")
        sizePolicy.setHeightForWidth(self.label_100.sizePolicy().hasHeightForWidth())
        self.label_100.setSizePolicy(sizePolicy)
        self.label_100.setMinimumSize(QSize(0, 0))
        self.label_100.setFont(font12)
        self.label_100.setAlignment(Qt.AlignLeading|Qt.AlignLeft|Qt.AlignVCenter)

        self.gridLayout_22.addWidget(self.label_100, 4, 2, 1, 1)

        self.label_98 = QLabel(self.scrollAreaWidgetContents_6)
        self.label_98.setObjectName(u"label_98")
        sizePolicy7.setHeightForWidth(self.label_98.sizePolicy().hasHeightForWidth())
        self.label_98.setSizePolicy(sizePolicy7)
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
        self.label_99.setFont(font12)
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
        self.label_103.setFont(font12)
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
        self.saTermite = QScrollArea(self.TermiteTab)
        self.saTermite.setObjectName(u"saTermite")
        self.saTermite.setWidgetResizable(True)
        self.wgTermite = QWidget()
        self.wgTermite.setObjectName(u"wgTermite")
        self.wgTermite.setGeometry(QRect(0, 0, 657, 684))
        self.wgTermite.setStyleSheet(u"QWidget#wgTermite\n"
"{\n"
"	\n"
"	background-color: rgb(30, 30, 32);\n"
"}")
        self.verticalLayout_27 = QVBoxLayout(self.wgTermite)
        self.verticalLayout_27.setSpacing(6)
        self.verticalLayout_27.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_27.setObjectName(u"verticalLayout_27")
        self.gridLayout_4 = QGridLayout()
        self.gridLayout_4.setSpacing(10)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.gridLayout_4.setContentsMargins(10, 10, 10, 10)
        self.teDebug = QTextEdit(self.wgTermite)
        self.teDebug.setObjectName(u"teDebug")
        font13 = QFont()
        font13.setBold(False)
        font13.setItalic(False)
        font13.setKerning(True)
        self.teDebug.setFont(font13)
        self.teDebug.setStyleSheet(u"color: rgb(255, 82, 87);")

        self.gridLayout_4.addWidget(self.teDebug, 0, 1, 1, 1)

        self.label_4 = QLabel(self.wgTermite)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout_4.addWidget(self.label_4, 1, 0, 1, 1)

        self.label_5 = QLabel(self.wgTermite)
        self.label_5.setObjectName(u"label_5")

        self.gridLayout_4.addWidget(self.label_5, 0, 0, 1, 1)

        self.leTerminal = QLineEdit(self.wgTermite)
        self.leTerminal.setObjectName(u"leTerminal")
        self.leTerminal.setMinimumSize(QSize(0, 30))

        self.gridLayout_4.addWidget(self.leTerminal, 1, 1, 1, 1)

        self.cbDeviceSender = QComboBox(self.wgTermite)
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.addItem("")
        self.cbDeviceSender.setObjectName(u"cbDeviceSender")

        self.gridLayout_4.addWidget(self.cbDeviceSender, 1, 2, 1, 1)


        self.verticalLayout_27.addLayout(self.gridLayout_4)

        self.saTermite.setWidget(self.wgTermite)

        self.verticalLayout_11.addWidget(self.saTermite)

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
        self.twDevices.setMinimumSize(QSize(0, 28))
        self.twDevices.setFont(font3)
        self.twDevices.setStyleSheet(u"")
        self.twDevices.setTabPosition(QTabWidget.North)
        self.twDevices.setElideMode(Qt.ElideNone)
        self.twDevices.setTabsClosable(False)
        self.tRobot = QWidget()
        self.tRobot.setObjectName(u"tRobot")
        self.tRobot.setStyleSheet(u"")
        self.verticalLayout_4 = QVBoxLayout(self.tRobot)
        self.verticalLayout_4.setSpacing(0)
        self.verticalLayout_4.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.verticalLayout_4.setContentsMargins(0, 0, 0, 0)
        self.scrollArea_2 = QScrollArea(self.tRobot)
        self.scrollArea_2.setObjectName(u"scrollArea_2")
        self.scrollArea_2.setWidgetResizable(True)
        self.wgJoggingScrollWidget = QWidget()
        self.wgJoggingScrollWidget.setObjectName(u"wgJoggingScrollWidget")
        self.wgJoggingScrollWidget.setGeometry(QRect(0, 0, 495, 1500))
        self.wgJoggingScrollWidget.setMinimumSize(QSize(0, 1500))
        self.wgJoggingScrollWidget.setMaximumSize(QSize(16777215, 16777215))
        self.wgJoggingScrollWidget.setStyleSheet(u"QWidget#wgJoggingScrollWidget\n"
"{\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"QLabel, QCheckBox\n"
"{	\n"
"	color: rgb(208, 208, 209);\n"
"}\n"
"\n"
"QFrame\n"
"{	\n"
"	border-radius: 5px;\n"
"	background-color: #333337;\n"
"}\n"
"\n"
"/* \u00c1p d\u1ee5ng cho m\u1ed9t ph\u1ea7n t\u1eed c\u1ee5 th\u1ec3, v\u00ed d\u1ee5 QPushButton */\n"
"QPushButton {\n"
"    background-color: #4A4A4F;\n"
"    border-radius: 5px;\n"
"    \n"
"	color: rgb(208, 208, 209);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"QToolButton {\n"
"    background-color: #4A4A4F;\n"
"    border-radius: 5px;\n"
"    \n"
"	color: rgb(208, 208, 209);\n"
"}\n"
"\n"
"QToolButton:hover\n"
"{\n"
"	border: 2px solid #FFFFFF;\n"
"}\n"
"\n"
"QFrame[Func=Title]\n"
"{\n"
"	padding-top: 6px;\n"
"	padding-bottom:6px;\n"
"}")
        self.verticalLayout_5 = QVBoxLayout(self.wgJoggingScrollWidget)
        self.verticalLayout_5.setSpacing(10)
        self.verticalLayout_5.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.verticalLayout_5.setContentsMargins(10, 10, 10, 10)
        self.frame_12 = QFrame(self.wgJoggingScrollWidget)
        self.frame_12.setObjectName(u"frame_12")
        self.frame_12.setMinimumSize(QSize(0, 100))
        self.frame_12.setStyleSheet(u"#frame_23, #robotTitile\n"
"{\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"#frame_12\n"
"{	\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}\n"
"\n"
"")
        self.frame_12.setFrameShape(QFrame.StyledPanel)
        self.frame_12.setFrameShadow(QFrame.Raised)
        self.verticalLayout_28 = QVBoxLayout(self.frame_12)
        self.verticalLayout_28.setSpacing(0)
        self.verticalLayout_28.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_28.setObjectName(u"verticalLayout_28")
        self.verticalLayout_28.setContentsMargins(0, 0, 0, 0)
        self.robotTitile = QFrame(self.frame_12)
        self.robotTitile.setObjectName(u"robotTitile")
        self.robotTitile.setMaximumSize(QSize(16777215, 40))
        self.robotTitile.setStyleSheet(u"")
        self.robotTitile.setFrameShape(QFrame.StyledPanel)
        self.robotTitile.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_36 = QHBoxLayout(self.robotTitile)
        self.horizontalLayout_36.setSpacing(6)
        self.horizontalLayout_36.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_36.setObjectName(u"horizontalLayout_36")
        self.horizontalLayout_36.setContentsMargins(-1, 0, -1, 0)
        self.label_158 = QLabel(self.robotTitile)
        self.label_158.setObjectName(u"label_158")
        self.label_158.setMinimumSize(QSize(100, 0))
        self.label_158.setMaximumSize(QSize(200, 16777215))
        self.label_158.setFont(font11)
        self.label_158.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_36.addWidget(self.label_158)

        self.horizontalSpacer_31 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_36.addItem(self.horizontalSpacer_31)

        self.tbAutoScanRobot = QToolButton(self.robotTitile)
        self.tbAutoScanRobot.setObjectName(u"tbAutoScanRobot")
        sizePolicy.setHeightForWidth(self.tbAutoScanRobot.sizePolicy().hasHeightForWidth())
        self.tbAutoScanRobot.setSizePolicy(sizePolicy)
        self.tbAutoScanRobot.setMinimumSize(QSize(20, 20))
        self.tbAutoScanRobot.setStyleSheet(u"QToolButton\n"
"{\n"
"	background: transparent;\n"
"}")
        icon39 = QIcon()
        icon39.addFile(u":/icon/icons8_switch_off_52px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon39.addFile(u":/icon/icons8_switch_on_52px.png", QSize(), QIcon.Normal, QIcon.On)
        icon39.addFile(u":/icon/icons8_switch_on_52px.png", QSize(), QIcon.Active, QIcon.On)
        self.tbAutoScanRobot.setIcon(icon39)
        self.tbAutoScanRobot.setIconSize(QSize(16, 16))
        self.tbAutoScanRobot.setCheckable(True)
        self.tbAutoScanRobot.setChecked(True)
        self.tbAutoScanRobot.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.tbAutoScanRobot.setAutoRaise(True)

        self.horizontalLayout_36.addWidget(self.tbAutoScanRobot)

        self.pbConnect = QPushButton(self.robotTitile)
        self.pbConnect.setObjectName(u"pbConnect")
        sizePolicy.setHeightForWidth(self.pbConnect.sizePolicy().hasHeightForWidth())
        self.pbConnect.setSizePolicy(sizePolicy)
        self.pbConnect.setMinimumSize(QSize(0, 28))
        self.pbConnect.setFont(font11)
        self.pbConnect.setStyleSheet(u"QPushButton\n"
"{\n"
"	background-color: #3195EF;\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"}\n"
"QPushButton:hover\n"
"{	\n"
"	background-color: rgb(129, 129, 129);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{	\n"
"	background-color: rgb(81, 176, 255);\n"
"}\n"
"")
        icon40 = QIcon()
        icon40.addFile(u"C:/Users/Admin/.designer/backup/icon/disconnected.png", QSize(), QIcon.Normal, QIcon.Off)
        icon40.addFile(u"C:/Users/Admin/.designer/backup/icon/connected.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbConnect.setIcon(icon40)
        self.pbConnect.setIconSize(QSize(30, 20))
        self.pbConnect.setCheckable(True)

        self.horizontalLayout_36.addWidget(self.pbConnect)


        self.verticalLayout_28.addWidget(self.robotTitile)

        self.frame_23 = QFrame(self.frame_12)
        self.frame_23.setObjectName(u"frame_23")
        self.frame_23.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background: #262629;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_23.setFrameShape(QFrame.StyledPanel)
        self.frame_23.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_41 = QHBoxLayout(self.frame_23)
        self.horizontalLayout_41.setSpacing(6)
        self.horizontalLayout_41.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_41.setObjectName(u"horizontalLayout_41")
        self.cbSelectedRobot = QComboBox(self.frame_23)
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.addItem("")
        self.cbSelectedRobot.setObjectName(u"cbSelectedRobot")
        sizePolicy10.setHeightForWidth(self.cbSelectedRobot.sizePolicy().hasHeightForWidth())
        self.cbSelectedRobot.setSizePolicy(sizePolicy10)
        self.cbSelectedRobot.setMinimumSize(QSize(100, 0))
        self.cbSelectedRobot.setMaximumSize(QSize(300, 16777215))
        self.cbSelectedRobot.setFont(font4)

        self.horizontalLayout_41.addWidget(self.cbSelectedRobot)

        self.horizontalSpacer_42 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_41.addItem(self.horizontalSpacer_42)

        self.groupBox = QGroupBox(self.frame_23)
        self.groupBox.setObjectName(u"groupBox")
        self.horizontalLayout_42 = QHBoxLayout(self.groupBox)
        self.horizontalLayout_42.setSpacing(0)
        self.horizontalLayout_42.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_42.setObjectName(u"horizontalLayout_42")
        self.horizontalLayout_42.setContentsMargins(-1, 15, -1, 0)
        self.lbComName = QLabel(self.groupBox)
        self.lbComName.setObjectName(u"lbComName")
        self.lbComName.setFont(font8)
        self.lbComName.setStyleSheet(u"")

        self.horizontalLayout_42.addWidget(self.lbComName)


        self.horizontalLayout_41.addWidget(self.groupBox)

        self.groupBox_2 = QGroupBox(self.frame_23)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.horizontalLayout_52 = QHBoxLayout(self.groupBox_2)
        self.horizontalLayout_52.setSpacing(0)
        self.horizontalLayout_52.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_52.setObjectName(u"horizontalLayout_52")
        self.horizontalLayout_52.setContentsMargins(6, 15, -1, 0)
        self.lbBaudrate = QLabel(self.groupBox_2)
        self.lbBaudrate.setObjectName(u"lbBaudrate")
        self.lbBaudrate.setFont(font8)
        self.lbBaudrate.setStyleSheet(u"")

        self.horizontalLayout_52.addWidget(self.lbBaudrate)


        self.horizontalLayout_41.addWidget(self.groupBox_2)

        self.groupBox_3 = QGroupBox(self.frame_23)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.horizontalLayout_44 = QHBoxLayout(self.groupBox_3)
        self.horizontalLayout_44.setSpacing(0)
        self.horizontalLayout_44.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_44.setObjectName(u"horizontalLayout_44")
        self.horizontalLayout_44.setContentsMargins(6, 15, -1, 0)
        self.cbRobotModel = QComboBox(self.groupBox_3)
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.addItem("")
        self.cbRobotModel.setObjectName(u"cbRobotModel")
        self.cbRobotModel.setMinimumSize(QSize(80, 0))

        self.horizontalLayout_44.addWidget(self.cbRobotModel)


        self.horizontalLayout_41.addWidget(self.groupBox_3)

        self.groupBox_4 = QGroupBox(self.frame_23)
        self.groupBox_4.setObjectName(u"groupBox_4")
        self.horizontalLayout_53 = QHBoxLayout(self.groupBox_4)
        self.horizontalLayout_53.setSpacing(0)
        self.horizontalLayout_53.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_53.setObjectName(u"horizontalLayout_53")
        self.horizontalLayout_53.setContentsMargins(-1, 15, -1, 0)
        self.cbRobotDOF = QComboBox(self.groupBox_4)
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.addItem("")
        self.cbRobotDOF.setObjectName(u"cbRobotDOF")
        self.cbRobotDOF.setMinimumSize(QSize(80, 0))

        self.horizontalLayout_53.addWidget(self.cbRobotDOF)


        self.horizontalLayout_41.addWidget(self.groupBox_4)

        self.fRobotPosition = QFrame(self.frame_23)
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

        self.horizontalLayout_41.addWidget(self.fRobotPosition)


        self.verticalLayout_28.addWidget(self.frame_23)


        self.verticalLayout_5.addWidget(self.frame_12)

        self.frame_28 = QFrame(self.wgJoggingScrollWidget)
        self.frame_28.setObjectName(u"frame_28")
        self.frame_28.setMinimumSize(QSize(0, 100))
        self.frame_28.setStyleSheet(u"#frame_23, #robotTitile\n"
"{\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"#frame_12\n"
"{	\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}\n"
"\n"
"")
        self.frame_28.setFrameShape(QFrame.StyledPanel)
        self.frame_28.setFrameShadow(QFrame.Raised)
        self.verticalLayout_72 = QVBoxLayout(self.frame_28)
        self.verticalLayout_72.setSpacing(0)
        self.verticalLayout_72.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_72.setObjectName(u"verticalLayout_72")
        self.verticalLayout_72.setContentsMargins(0, 0, 0, 0)
        self.positionTitile = QFrame(self.frame_28)
        self.positionTitile.setObjectName(u"positionTitile")
        self.positionTitile.setMaximumSize(QSize(16777215, 40))
        self.positionTitile.setStyleSheet(u"")
        self.positionTitile.setFrameShape(QFrame.StyledPanel)
        self.positionTitile.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_75 = QHBoxLayout(self.positionTitile)
        self.horizontalLayout_75.setSpacing(6)
        self.horizontalLayout_75.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_75.setObjectName(u"horizontalLayout_75")
        self.label_270 = QLabel(self.positionTitile)
        self.label_270.setObjectName(u"label_270")
        self.label_270.setMaximumSize(QSize(100, 16777215))
        self.label_270.setFont(font11)
        self.label_270.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_75.addWidget(self.label_270)

        self.horizontalSpacer_93 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_75.addItem(self.horizontalSpacer_93)

        self.tbDisableRobot = QToolButton(self.positionTitile)
        self.tbDisableRobot.setObjectName(u"tbDisableRobot")
        sizePolicy.setHeightForWidth(self.tbDisableRobot.sizePolicy().hasHeightForWidth())
        self.tbDisableRobot.setSizePolicy(sizePolicy)
        self.tbDisableRobot.setMinimumSize(QSize(20, 20))
        self.tbDisableRobot.setStyleSheet(u"QToolButton\n"
"{\n"
"	background: transparent;\n"
"}")
        self.tbDisableRobot.setIcon(icon39)
        self.tbDisableRobot.setIconSize(QSize(16, 16))
        self.tbDisableRobot.setCheckable(True)
        self.tbDisableRobot.setChecked(True)
        self.tbDisableRobot.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.tbDisableRobot.setAutoRaise(True)

        self.horizontalLayout_75.addWidget(self.tbDisableRobot)

        self.tbRequestPosition = QToolButton(self.positionTitile)
        self.tbRequestPosition.setObjectName(u"tbRequestPosition")
        sizePolicy.setHeightForWidth(self.tbRequestPosition.sizePolicy().hasHeightForWidth())
        self.tbRequestPosition.setSizePolicy(sizePolicy)
        self.tbRequestPosition.setMinimumSize(QSize(20, 20))
        self.tbRequestPosition.setIconSize(QSize(16, 16))
        self.tbRequestPosition.setToolButtonStyle(Qt.ToolButtonTextBesideIcon)
        self.tbRequestPosition.setAutoRaise(True)

        self.horizontalLayout_75.addWidget(self.tbRequestPosition)


        self.verticalLayout_72.addWidget(self.positionTitile)

        self.frame_29 = QFrame(self.frame_28)
        self.frame_29.setObjectName(u"frame_29")
        self.frame_29.setMinimumSize(QSize(0, 0))
        self.frame_29.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background: #262629;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_29.setFrameShape(QFrame.StyledPanel)
        self.frame_29.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_76 = QHBoxLayout(self.frame_29)
        self.horizontalLayout_76.setSpacing(6)
        self.horizontalLayout_76.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_76.setObjectName(u"horizontalLayout_76")
        self.pbHome = QToolButton(self.frame_29)
        self.pbHome.setObjectName(u"pbHome")
        self.pbHome.setMinimumSize(QSize(0, 0))
        self.pbHome.setFont(font4)
        self.pbHome.setStyleSheet(u"QToolButton\n"
"{\n"
"	padding: 5px;\n"
"}")
        icon41 = QIcon()
        icon41.addFile(u":/icon/home.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbHome.setIcon(icon41)
        self.pbHome.setIconSize(QSize(20, 20))
        self.pbHome.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.horizontalLayout_76.addWidget(self.pbHome)

        self.horizontalSpacer_95 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_76.addItem(self.horizontalSpacer_95)

        self.frame_9 = QFrame(self.frame_29)
        self.frame_9.setObjectName(u"frame_9")
        self.frame_9.setMinimumSize(QSize(0, 0))
        self.frame_9.setStyleSheet(u"")
        self.frame_9.setFrameShape(QFrame.StyledPanel)
        self.frame_9.setFrameShadow(QFrame.Raised)
        self.gridLayout_31 = QGridLayout(self.frame_9)
        self.gridLayout_31.setSpacing(6)
        self.gridLayout_31.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_31.setObjectName(u"gridLayout_31")
        self.gridLayout_31.setContentsMargins(-1, 0, -1, 0)
        self.label_92 = QLabel(self.frame_9)
        self.label_92.setObjectName(u"label_92")
        self.label_92.setMinimumSize(QSize(0, 0))
        self.label_92.setFont(font10)
        self.label_92.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_92, 0, 7, 1, 1)

        self.label_90 = QLabel(self.frame_9)
        self.label_90.setObjectName(u"label_90")
        self.label_90.setMinimumSize(QSize(0, 0))
        self.label_90.setFont(font10)
        self.label_90.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_90, 0, 5, 1, 2)

        self.label_94 = QLabel(self.frame_9)
        self.label_94.setObjectName(u"label_94")
        self.label_94.setMinimumSize(QSize(0, 0))
        self.label_94.setFont(font10)
        self.label_94.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_94, 0, 8, 1, 1)

        self.label_84 = QLabel(self.frame_9)
        self.label_84.setObjectName(u"label_84")
        self.label_84.setMinimumSize(QSize(0, 0))
        self.label_84.setFont(font10)
        self.label_84.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_84, 0, 1, 1, 1)

        self.label_88 = QLabel(self.frame_9)
        self.label_88.setObjectName(u"label_88")
        self.label_88.setMinimumSize(QSize(0, 0))
        self.label_88.setFont(font10)
        self.label_88.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_88, 0, 3, 1, 1)

        self.label_86 = QLabel(self.frame_9)
        self.label_86.setObjectName(u"label_86")
        self.label_86.setMinimumSize(QSize(0, 0))
        self.label_86.setFont(font10)
        self.label_86.setAlignment(Qt.AlignCenter)

        self.gridLayout_31.addWidget(self.label_86, 0, 2, 1, 1)

        self.leX = QLineEdit(self.frame_9)
        self.leX.setObjectName(u"leX")
        self.leX.setMinimumSize(QSize(0, 0))
        self.leX.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_31.addWidget(self.leX, 1, 1, 1, 1)

        self.leY = QLineEdit(self.frame_9)
        self.leY.setObjectName(u"leY")
        self.leY.setMinimumSize(QSize(0, 0))
        self.leY.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_31.addWidget(self.leY, 1, 2, 1, 1)

        self.leZ = QLineEdit(self.frame_9)
        self.leZ.setObjectName(u"leZ")
        self.leZ.setMinimumSize(QSize(0, 0))
        self.leZ.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_31.addWidget(self.leZ, 1, 3, 1, 1)

        self.leW = QLineEdit(self.frame_9)
        self.leW.setObjectName(u"leW")
        self.leW.setMinimumSize(QSize(0, 0))
        self.leW.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_31.addWidget(self.leW, 1, 5, 1, 1)

        self.leU = QLineEdit(self.frame_9)
        self.leU.setObjectName(u"leU")
        self.leU.setMinimumSize(QSize(0, 0))
        self.leU.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_31.addWidget(self.leU, 1, 7, 1, 1)

        self.leV = QLineEdit(self.frame_9)
        self.leV.setObjectName(u"leV")
        self.leV.setMinimumSize(QSize(0, 0))
        self.leV.setMaximumSize(QSize(70, 16777215))

        self.gridLayout_31.addWidget(self.leV, 1, 8, 1, 1)

        self.label_277 = QLabel(self.frame_9)
        self.label_277.setObjectName(u"label_277")
        self.label_277.setMaximumSize(QSize(120, 16777215))

        self.gridLayout_31.addWidget(self.label_277, 1, 4, 1, 1)

        self.label_278 = QLabel(self.frame_9)
        self.label_278.setObjectName(u"label_278")
        self.label_278.setMaximumSize(QSize(120, 16777215))

        self.gridLayout_31.addWidget(self.label_278, 1, 9, 1, 1)


        self.horizontalLayout_76.addWidget(self.frame_9)


        self.verticalLayout_72.addWidget(self.frame_29)


        self.verticalLayout_5.addWidget(self.frame_28)

        self.frame_30 = QFrame(self.wgJoggingScrollWidget)
        self.frame_30.setObjectName(u"frame_30")
        self.frame_30.setMinimumSize(QSize(0, 0))
        self.frame_30.setStyleSheet(u"#frame_23, #robotTitile\n"
"{\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"#frame_12\n"
"{	\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}\n"
"\n"
"")
        self.frame_30.setFrameShape(QFrame.StyledPanel)
        self.frame_30.setFrameShadow(QFrame.Raised)
        self.verticalLayout_73 = QVBoxLayout(self.frame_30)
        self.verticalLayout_73.setSpacing(0)
        self.verticalLayout_73.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_73.setObjectName(u"verticalLayout_73")
        self.verticalLayout_73.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_4 = QFrame(self.frame_30)
        self.robotTitile_4.setObjectName(u"robotTitile_4")
        self.robotTitile_4.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_4.setStyleSheet(u"")
        self.robotTitile_4.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_4.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_77 = QHBoxLayout(self.robotTitile_4)
        self.horizontalLayout_77.setSpacing(6)
        self.horizontalLayout_77.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_77.setObjectName(u"horizontalLayout_77")
        self.horizontalLayout_77.setContentsMargins(-1, 0, -1, 0)
        self.label_271 = QLabel(self.robotTitile_4)
        self.label_271.setObjectName(u"label_271")
        self.label_271.setMaximumSize(QSize(100, 16777215))
        self.label_271.setFont(font11)
        self.label_271.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_77.addWidget(self.label_271)

        self.horizontalSpacer_94 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_77.addItem(self.horizontalSpacer_94)


        self.verticalLayout_73.addWidget(self.robotTitile_4)

        self.frame_31 = QFrame(self.frame_30)
        self.frame_31.setObjectName(u"frame_31")
        sizePolicy21 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Maximum)
        sizePolicy21.setHorizontalStretch(0)
        sizePolicy21.setVerticalStretch(0)
        sizePolicy21.setHeightForWidth(self.frame_31.sizePolicy().hasHeightForWidth())
        self.frame_31.setSizePolicy(sizePolicy21)
        self.frame_31.setMinimumSize(QSize(0, 0))
        self.frame_31.setMaximumSize(QSize(16777215, 16777215))
        self.frame_31.setStyleSheet(u"QFrame\n"
"{\n"
"	border-radius:0px;\n"
"	background: #262629;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}\n"
"\n"
"QToolButton\n"
"{\n"
"	background-color: #3195EF;\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"	border-radius: 5px;\n"
"	width: 30px;\n"
"	height: 30px;\n"
"}\n"
"QToolButton:hover\n"
"{	\n"
"	background-color: rgb(129, 129, 129);\n"
"}\n"
"\n"
"QToolButton:pressed\n"
"{	\n"
"	background-color: rgb(81, 176, 255);\n"
"}\n"
"\n"
"QToolButton[Func='Jogging'] \n"
"{\n"
"	padding: 10px;\n"
"}\n"
"")
        self.frame_31.setFrameShape(QFrame.StyledPanel)
        self.frame_31.setFrameShadow(QFrame.Raised)
        self.gridLayout_56 = QGridLayout(self.frame_31)
        self.gridLayout_56.setSpacing(6)
        self.gridLayout_56.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_56.setObjectName(u"gridLayout_56")
        self.pbLeft = QToolButton(self.frame_31)
        self.pbLeft.setObjectName(u"pbLeft")
        self.pbLeft.setIconSize(QSize(40, 40))
        self.pbLeft.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbLeft, 2, 0, 1, 1)

        self.pbBackward = QToolButton(self.frame_31)
        self.pbBackward.setObjectName(u"pbBackward")
        self.pbBackward.setIconSize(QSize(40, 40))
        self.pbBackward.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbBackward, 3, 1, 1, 1)

        self.label_275 = QLabel(self.frame_31)
        self.label_275.setObjectName(u"label_275")
        self.label_275.setMinimumSize(QSize(0, 20))
        self.label_275.setFont(font7)
        self.label_275.setAlignment(Qt.AlignCenter)

        self.gridLayout_56.addWidget(self.label_275, 2, 7, 1, 1)

        self.pbPlusRoll = QToolButton(self.frame_31)
        self.pbPlusRoll.setObjectName(u"pbPlusRoll")
        self.pbPlusRoll.setIconSize(QSize(40, 40))
        self.pbPlusRoll.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbPlusRoll, 3, 6, 1, 1)

        self.label_274 = QLabel(self.frame_31)
        self.label_274.setObjectName(u"label_274")
        self.label_274.setMinimumSize(QSize(0, 20))
        self.label_274.setFont(font7)
        self.label_274.setAlignment(Qt.AlignCenter)

        self.gridLayout_56.addWidget(self.label_274, 2, 8, 1, 1)

        self.pbSubPitch = QToolButton(self.frame_31)
        self.pbSubPitch.setObjectName(u"pbSubPitch")
        self.pbSubPitch.setIconSize(QSize(40, 40))
        self.pbSubPitch.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbSubPitch, 1, 8, 1, 1)

        self.pbSubRoll = QToolButton(self.frame_31)
        self.pbSubRoll.setObjectName(u"pbSubRoll")
        self.pbSubRoll.setIconSize(QSize(40, 40))
        self.pbSubRoll.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbSubRoll, 1, 6, 1, 1)

        self.pbUp = QToolButton(self.frame_31)
        self.pbUp.setObjectName(u"pbUp")
        self.pbUp.setIconSize(QSize(20, 20))
        self.pbUp.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.pbUp.setAutoRaise(False)

        self.gridLayout_56.addWidget(self.pbUp, 1, 5, 1, 1)

        self.pbDown = QToolButton(self.frame_31)
        self.pbDown.setObjectName(u"pbDown")
        self.pbDown.setIconSize(QSize(40, 40))
        self.pbDown.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbDown, 3, 5, 1, 1)

        self.pbForward = QToolButton(self.frame_31)
        self.pbForward.setObjectName(u"pbForward")
        sizePolicy19.setHeightForWidth(self.pbForward.sizePolicy().hasHeightForWidth())
        self.pbForward.setSizePolicy(sizePolicy19)
        self.pbForward.setStyleSheet(u"")
        self.pbForward.setIconSize(QSize(20, 20))
        self.pbForward.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbForward, 1, 1, 1, 1)

        self.pbRight = QToolButton(self.frame_31)
        self.pbRight.setObjectName(u"pbRight")
        self.pbRight.setIconSize(QSize(40, 40))
        self.pbRight.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbRight, 2, 3, 1, 1)

        self.pbPlusPitch = QToolButton(self.frame_31)
        self.pbPlusPitch.setObjectName(u"pbPlusPitch")
        self.pbPlusPitch.setIconSize(QSize(40, 40))
        self.pbPlusPitch.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbPlusPitch, 3, 8, 1, 1)

        self.pbSubYaw = QToolButton(self.frame_31)
        self.pbSubYaw.setObjectName(u"pbSubYaw")
        self.pbSubYaw.setIconSize(QSize(40, 40))
        self.pbSubYaw.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbSubYaw, 1, 7, 1, 1)

        self.horizontalSpacer_4 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_56.addItem(self.horizontalSpacer_4, 2, 9, 1, 1)

        self.label_276 = QLabel(self.frame_31)
        self.label_276.setObjectName(u"label_276")
        self.label_276.setMinimumSize(QSize(0, 20))
        self.label_276.setFont(font7)
        self.label_276.setAlignment(Qt.AlignCenter)

        self.gridLayout_56.addWidget(self.label_276, 2, 6, 1, 1)

        self.pbPlusYaw = QToolButton(self.frame_31)
        self.pbPlusYaw.setObjectName(u"pbPlusYaw")
        self.pbPlusYaw.setIconSize(QSize(40, 40))
        self.pbPlusYaw.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)

        self.gridLayout_56.addWidget(self.pbPlusYaw, 3, 7, 1, 1)


        self.verticalLayout_73.addWidget(self.frame_31)

        self.frame_32 = QFrame(self.frame_30)
        self.frame_32.setObjectName(u"frame_32")
        self.frame_32.setMinimumSize(QSize(0, 0))
        self.frame_32.setMaximumSize(QSize(16777215, 30))
        self.frame_32.setStyleSheet(u"QFrame\n"
"{\n"
"	background: #262629;\n"
"	border-radius:0px;\n"
"}\n"
"\n"
"QRadioButton {\n"
"    background-color: #434347;\n"
"    padding: 5px;\n"
"	 width:30px;\n"
"    border: 1px solid #646469;\n"
"	color: #D0D0D1;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 0px;\n"
"    height: 0px;\n"
"}\n"
"\n"
"QRadioButton:checked {\n"
"    background-color: #646469;\n"
"    border-color: #646469;\n"
"    color: white;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"    border-color: #2196F3;\n"
"}\n"
"\n"
"QRadioButton:disabled {\n"
"    background-color: #D0D0D0;\n"
"    color: #B0B0B0;\n"
"}")
        self.frame_32.setFrameShape(QFrame.StyledPanel)
        self.frame_32.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_81 = QHBoxLayout(self.frame_32)
        self.horizontalLayout_81.setSpacing(0)
        self.horizontalLayout_81.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_81.setObjectName(u"horizontalLayout_81")
        self.horizontalLayout_81.setContentsMargins(0, 0, 0, 0)
        self.label_33 = QLabel(self.frame_32)
        self.label_33.setObjectName(u"label_33")
        self.label_33.setMaximumSize(QSize(120, 16777215))

        self.horizontalLayout_81.addWidget(self.label_33)

        self.rb01 = QRadioButton(self.frame_32)
        self.rb01.setObjectName(u"rb01")

        self.horizontalLayout_81.addWidget(self.rb01)

        self.rb05 = QRadioButton(self.frame_32)
        self.rb05.setObjectName(u"rb05")

        self.horizontalLayout_81.addWidget(self.rb05)

        self.rb10 = QRadioButton(self.frame_32)
        self.rb10.setObjectName(u"rb10")

        self.horizontalLayout_81.addWidget(self.rb10)

        self.rb50 = QRadioButton(self.frame_32)
        self.rb50.setObjectName(u"rb50")

        self.horizontalLayout_81.addWidget(self.rb50)

        self.rb100 = QRadioButton(self.frame_32)
        self.rb100.setObjectName(u"rb100")
        self.rb100.setChecked(True)

        self.horizontalLayout_81.addWidget(self.rb100)

        self.rb500 = QRadioButton(self.frame_32)
        self.rb500.setObjectName(u"rb500")

        self.horizontalLayout_81.addWidget(self.rb500)

        self.rb1000 = QRadioButton(self.frame_32)
        self.rb1000.setObjectName(u"rb1000")

        self.horizontalLayout_81.addWidget(self.rb1000)

        self.label_273 = QLabel(self.frame_32)
        self.label_273.setObjectName(u"label_273")
        self.label_273.setMaximumSize(QSize(120, 16777215))

        self.horizontalLayout_81.addWidget(self.label_273)

        self.horizontalSpacer_27 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_81.addItem(self.horizontalSpacer_27)


        self.verticalLayout_73.addWidget(self.frame_32)


        self.verticalLayout_5.addWidget(self.frame_30)

        self.frame_22 = QFrame(self.wgJoggingScrollWidget)
        self.frame_22.setObjectName(u"frame_22")
        self.frame_22.setMinimumSize(QSize(0, 0))
        self.frame_22.setFrameShape(QFrame.StyledPanel)
        self.frame_22.setFrameShadow(QFrame.Raised)
        self.verticalLayout_12 = QVBoxLayout(self.frame_22)
        self.verticalLayout_12.setSpacing(0)
        self.verticalLayout_12.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_12.setObjectName(u"verticalLayout_12")
        self.verticalLayout_12.setContentsMargins(0, 0, 0, 0)
        self.frame1 = QFrame(self.frame_22)
        self.frame1.setObjectName(u"frame1")
        self.frame1.setStyleSheet(u"QLabel\n"
"{\n"
"	padding-left: 6px;\n"
"}")
        self.horizontalLayout_12 = QHBoxLayout(self.frame1)
        self.horizontalLayout_12.setSpacing(6)
        self.horizontalLayout_12.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.horizontalLayout_12.setContentsMargins(1, -1, -1, -1)
        self.label_272 = QLabel(self.frame1)
        self.label_272.setObjectName(u"label_272")
        self.label_272.setMaximumSize(QSize(16777215, 16777215))
        self.label_272.setFont(font11)
        self.label_272.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_12.addWidget(self.label_272)

        self.horizontalSpacer_96 = QSpacerItem(466, 17, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_12.addItem(self.horizontalSpacer_96)


        self.verticalLayout_12.addWidget(self.frame1)

        self.frame_24 = QFrame(self.frame_22)
        self.frame_24.setObjectName(u"frame_24")
        self.frame_24.setMinimumSize(QSize(0, 50))
        self.frame_24.setStyleSheet(u"QFrame\n"
"{\n"
"	border-radius:0px;\n"
"	background: #262629;\n"
"}")
        self.frame_24.setFrameShape(QFrame.StyledPanel)
        self.frame_24.setFrameShadow(QFrame.Raised)
        self.gridLayout_3 = QGridLayout(self.frame_24)
        self.gridLayout_3.setSpacing(6)
        self.gridLayout_3.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.gridLayout_3.setHorizontalSpacing(10)
        self.leEndSpeed = QLineEdit(self.frame_24)
        self.leEndSpeed.setObjectName(u"leEndSpeed")
        sizePolicy22 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Maximum)
        sizePolicy22.setHorizontalStretch(0)
        sizePolicy22.setVerticalStretch(0)
        sizePolicy22.setHeightForWidth(self.leEndSpeed.sizePolicy().hasHeightForWidth())
        self.leEndSpeed.setSizePolicy(sizePolicy22)
        self.leEndSpeed.setMinimumSize(QSize(0, 0))
        self.leEndSpeed.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.leEndSpeed, 2, 4, 1, 1)

        self.label_62 = QLabel(self.frame_24)
        self.label_62.setObjectName(u"label_62")
        self.label_62.setMaximumSize(QSize(60, 16777215))
        self.label_62.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_62, 1, 3, 1, 1)

        self.leAccel = QLineEdit(self.frame_24)
        self.leAccel.setObjectName(u"leAccel")
        sizePolicy22.setHeightForWidth(self.leAccel.sizePolicy().hasHeightForWidth())
        self.leAccel.setSizePolicy(sizePolicy22)
        self.leAccel.setMinimumSize(QSize(0, 0))
        self.leAccel.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.leAccel, 2, 1, 1, 1)

        self.leVelocity = QLineEdit(self.frame_24)
        self.leVelocity.setObjectName(u"leVelocity")
        sizePolicy23 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Maximum)
        sizePolicy23.setHorizontalStretch(0)
        sizePolicy23.setVerticalStretch(0)
        sizePolicy23.setHeightForWidth(self.leVelocity.sizePolicy().hasHeightForWidth())
        self.leVelocity.setSizePolicy(sizePolicy23)
        self.leVelocity.setMinimumSize(QSize(0, 0))
        self.leVelocity.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.leVelocity, 1, 1, 1, 1)

        self.label_29 = QLabel(self.frame_24)
        self.label_29.setObjectName(u"label_29")
        self.label_29.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.label_29, 1, 0, 1, 1)

        self.horizontalSpacer_61 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_3.addItem(self.horizontalSpacer_61, 1, 7, 1, 1)

        self.leStartSpeed = QLineEdit(self.frame_24)
        self.leStartSpeed.setObjectName(u"leStartSpeed")
        sizePolicy22.setHeightForWidth(self.leStartSpeed.sizePolicy().hasHeightForWidth())
        self.leStartSpeed.setSizePolicy(sizePolicy22)
        self.leStartSpeed.setMinimumSize(QSize(0, 0))
        self.leStartSpeed.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.leStartSpeed, 1, 4, 1, 1)

        self.label_32 = QLabel(self.frame_24)
        self.label_32.setObjectName(u"label_32")
        self.label_32.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout_3.addWidget(self.label_32, 2, 2, 1, 1)

        self.label_30 = QLabel(self.frame_24)
        self.label_30.setObjectName(u"label_30")
        self.label_30.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout_3.addWidget(self.label_30, 1, 2, 1, 1)

        self.label_31 = QLabel(self.frame_24)
        self.label_31.setObjectName(u"label_31")
        self.label_31.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.label_31, 2, 0, 1, 1)

        self.label_63 = QLabel(self.frame_24)
        self.label_63.setObjectName(u"label_63")
        self.label_63.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout_3.addWidget(self.label_63, 1, 5, 1, 1)

        self.label_116 = QLabel(self.frame_24)
        self.label_116.setObjectName(u"label_116")
        self.label_116.setMaximumSize(QSize(60, 16777215))
        self.label_116.setAlignment(Qt.AlignCenter)

        self.gridLayout_3.addWidget(self.label_116, 2, 3, 1, 1)

        self.label_117 = QLabel(self.frame_24)
        self.label_117.setObjectName(u"label_117")
        self.label_117.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout_3.addWidget(self.label_117, 2, 5, 1, 1)

        self.leJerk = QLineEdit(self.frame_24)
        self.leJerk.setObjectName(u"leJerk")
        sizePolicy22.setHeightForWidth(self.leJerk.sizePolicy().hasHeightForWidth())
        self.leJerk.setSizePolicy(sizePolicy22)
        self.leJerk.setMinimumSize(QSize(0, 0))
        self.leJerk.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.leJerk, 3, 1, 1, 1)

        self.label_64 = QLabel(self.frame_24)
        self.label_64.setObjectName(u"label_64")
        self.label_64.setStyleSheet(u"color: rgb(95, 95, 95);")

        self.gridLayout_3.addWidget(self.label_64, 3, 2, 1, 1)

        self.label_47 = QLabel(self.frame_24)
        self.label_47.setObjectName(u"label_47")
        self.label_47.setMaximumSize(QSize(60, 16777215))

        self.gridLayout_3.addWidget(self.label_47, 3, 0, 1, 1)


        self.verticalLayout_12.addWidget(self.frame_24)


        self.verticalLayout_5.addWidget(self.frame_22)

        self.frame_34 = QFrame(self.wgJoggingScrollWidget)
        self.frame_34.setObjectName(u"frame_34")
        self.frame_34.setMinimumSize(QSize(0, 100))
        self.frame_34.setStyleSheet(u"#frame_23, #robotTitile\n"
"{\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"#frame_12\n"
"{	\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}\n"
"\n"
"")
        self.frame_34.setFrameShape(QFrame.StyledPanel)
        self.frame_34.setFrameShadow(QFrame.Raised)
        self.verticalLayout_44 = QVBoxLayout(self.frame_34)
        self.verticalLayout_44.setSpacing(0)
        self.verticalLayout_44.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_44.setObjectName(u"verticalLayout_44")
        self.verticalLayout_44.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_3 = QFrame(self.frame_34)
        self.robotTitile_3.setObjectName(u"robotTitile_3")
        self.robotTitile_3.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_3.setStyleSheet(u"")
        self.robotTitile_3.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_3.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_78 = QHBoxLayout(self.robotTitile_3)
        self.horizontalLayout_78.setSpacing(6)
        self.horizontalLayout_78.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_78.setObjectName(u"horizontalLayout_78")
        self.horizontalLayout_78.setContentsMargins(-1, 0, -1, 0)
        self.label_279 = QLabel(self.robotTitile_3)
        self.label_279.setObjectName(u"label_279")
        self.label_279.setMaximumSize(QSize(100, 16777215))
        self.label_279.setFont(font11)
        self.label_279.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_78.addWidget(self.label_279)

        self.horizontalSpacer_32 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_78.addItem(self.horizontalSpacer_32)


        self.verticalLayout_44.addWidget(self.robotTitile_3)

        self.frame_35 = QFrame(self.frame_34)
        self.frame_35.setObjectName(u"frame_35")
        self.frame_35.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background: #262629;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_35.setFrameShape(QFrame.StyledPanel)
        self.frame_35.setFrameShadow(QFrame.Raised)
        self.verticalLayout_53 = QVBoxLayout(self.frame_35)
        self.verticalLayout_53.setSpacing(6)
        self.verticalLayout_53.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_53.setObjectName(u"verticalLayout_53")
        self.groupBox_9 = QGroupBox(self.frame_35)
        self.groupBox_9.setObjectName(u"groupBox_9")
        self.horizontalLayout = QHBoxLayout(self.groupBox_9)
        self.horizontalLayout.setSpacing(6)
        self.horizontalLayout.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(6, 20, -1, -1)
        self.verticalLayout_6 = QVBoxLayout()
        self.verticalLayout_6.setSpacing(6)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.pbPump = QPushButton(self.groupBox_9)
        self.pbPump.setObjectName(u"pbPump")
        self.pbPump.setMinimumSize(QSize(100, 30))
        self.pbPump.setAutoFillBackground(False)
        icon42 = QIcon()
        icon42.addFile(u":/icon/Toggle Off_16px.png", QSize(), QIcon.Normal, QIcon.Off)
        icon42.addFile(u":/icon/Toggle On_16px.png", QSize(), QIcon.Normal, QIcon.On)
        self.pbPump.setIcon(icon42)
        self.pbPump.setIconSize(QSize(16, 16))
        self.pbPump.setCheckable(True)
        self.pbPump.setChecked(False)
        self.pbPump.setAutoDefault(False)
        self.pbPump.setFlat(False)

        self.verticalLayout_6.addWidget(self.pbPump)

        self.pbLaser = QPushButton(self.groupBox_9)
        self.pbLaser.setObjectName(u"pbLaser")
        self.pbLaser.setMinimumSize(QSize(100, 30))
        self.pbLaser.setAutoFillBackground(False)
        self.pbLaser.setIcon(icon42)
        self.pbLaser.setIconSize(QSize(16, 16))
        self.pbLaser.setCheckable(True)
        self.pbLaser.setChecked(False)
        self.pbLaser.setAutoDefault(False)
        self.pbLaser.setFlat(False)

        self.verticalLayout_6.addWidget(self.pbLaser)


        self.horizontalLayout.addLayout(self.verticalLayout_6)

        self.horizontalSpacer_97 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer_97)

        self.gbGripper = QWidget(self.groupBox_9)
        self.gbGripper.setObjectName(u"gbGripper")
        self.gbGripper.setMaximumSize(QSize(250, 16777215))
        self.gbGripper.setFont(font2)
        self.gbGripper.setStyleSheet(u"#gbGripper\n"
"{	\n"
"	background-color: #4A4A4F;\n"
"	border-radius:5px;\n"
"}\n"
"")
        self.gridLayout_13 = QGridLayout(self.gbGripper)
        self.gridLayout_13.setSpacing(6)
        self.gridLayout_13.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_13.setObjectName(u"gridLayout_13")
        self.gridLayout_13.setContentsMargins(6, 5, 6, 5)
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
        self.pbGrip.setStyleSheet(u"QPushButton\n"
"{\n"
"	\n"
"	background-color: rgb(49, 149, 239);\n"
"}")
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
        sizePolicy20.setHeightForWidth(self.hsGripperAngle.sizePolicy().hasHeightForWidth())
        self.hsGripperAngle.setSizePolicy(sizePolicy20)
        self.hsGripperAngle.setMinimumSize(QSize(0, 30))
        self.hsGripperAngle.setMaximum(20)
        self.hsGripperAngle.setSingleStep(5)
        self.hsGripperAngle.setOrientation(Qt.Horizontal)

        self.horizontalLayout_15.addWidget(self.hsGripperAngle)

        self.lbGripperValue = QLabel(self.gbGripper)
        self.lbGripperValue.setObjectName(u"lbGripperValue")
        self.lbGripperValue.setMinimumSize(QSize(40, 0))
        self.lbGripperValue.setFont(font5)

        self.horizontalLayout_15.addWidget(self.lbGripperValue)


        self.gridLayout_13.addLayout(self.horizontalLayout_15, 1, 0, 1, 1)


        self.horizontalLayout.addWidget(self.gbGripper)

        self.horizontalSpacer_46 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout.addItem(self.horizontalSpacer_46)


        self.verticalLayout_53.addWidget(self.groupBox_9)

        self.gbOutput = QGroupBox(self.frame_35)
        self.gbOutput.setObjectName(u"gbOutput")
        self.gbOutput.setMinimumSize(QSize(0, 0))
        font14 = QFont()
        font14.setPointSize(9)
        font14.setBold(False)
        self.gbOutput.setFont(font14)
        self.verticalLayout_42 = QVBoxLayout(self.gbOutput)
        self.verticalLayout_42.setSpacing(6)
        self.verticalLayout_42.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_42.setObjectName(u"verticalLayout_42")
        self.verticalLayout_42.setContentsMargins(-1, 20, -1, -1)
        self.wgDigitalOutput = QWidget(self.gbOutput)
        self.wgDigitalOutput.setObjectName(u"wgDigitalOutput")
        self.wgDigitalOutput.setMinimumSize(QSize(0, 0))
        self.gridLayout_34 = QGridLayout(self.wgDigitalOutput)
        self.gridLayout_34.setSpacing(6)
        self.gridLayout_34.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_34.setObjectName(u"gridLayout_34")
        self.cbD3 = QCheckBox(self.wgDigitalOutput)
        self.cbD3.setObjectName(u"cbD3")
        self.cbD3.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD3, 1, 9, 1, 1)

        self.cbD0 = QCheckBox(self.wgDigitalOutput)
        self.cbD0.setObjectName(u"cbD0")
        self.cbD0.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD0, 1, 2, 1, 1)

        self.label_71 = QLabel(self.wgDigitalOutput)
        self.label_71.setObjectName(u"label_71")
        self.label_71.setMinimumSize(QSize(30, 0))
        self.label_71.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_71, 2, 6, 1, 1)

        self.label_66 = QLabel(self.wgDigitalOutput)
        self.label_66.setObjectName(u"label_66")
        self.label_66.setMinimumSize(QSize(30, 0))
        self.label_66.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_66, 2, 1, 1, 1)

        self.cbD6 = QCheckBox(self.wgDigitalOutput)
        self.cbD6.setObjectName(u"cbD6")
        self.cbD6.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD6, 2, 7, 1, 1)

        self.label_53 = QLabel(self.wgDigitalOutput)
        self.label_53.setObjectName(u"label_53")
        self.label_53.setMinimumSize(QSize(30, 0))
        self.label_53.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_53, 1, 3, 1, 1)

        self.cbD2 = QCheckBox(self.wgDigitalOutput)
        self.cbD2.setObjectName(u"cbD2")
        self.cbD2.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD2, 1, 7, 1, 1)

        self.cbD7 = QCheckBox(self.wgDigitalOutput)
        self.cbD7.setObjectName(u"cbD7")
        self.cbD7.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD7, 2, 9, 1, 1)

        self.label_72 = QLabel(self.wgDigitalOutput)
        self.label_72.setObjectName(u"label_72")
        self.label_72.setMinimumSize(QSize(30, 0))
        self.label_72.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_72, 2, 8, 1, 1)

        self.cbD1 = QCheckBox(self.wgDigitalOutput)
        self.cbD1.setObjectName(u"cbD1")
        self.cbD1.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD1, 1, 5, 1, 1)

        self.cbD4 = QCheckBox(self.wgDigitalOutput)
        self.cbD4.setObjectName(u"cbD4")
        self.cbD4.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD4, 2, 2, 1, 1)

        self.label_51 = QLabel(self.wgDigitalOutput)
        self.label_51.setObjectName(u"label_51")
        self.label_51.setMinimumSize(QSize(30, 0))
        self.label_51.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_51, 1, 1, 1, 1)

        self.horizontalSpacer_69 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_34.addItem(self.horizontalSpacer_69, 2, 14, 1, 1)

        self.label_69 = QLabel(self.wgDigitalOutput)
        self.label_69.setObjectName(u"label_69")
        self.label_69.setMinimumSize(QSize(30, 0))
        self.label_69.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_69, 2, 3, 1, 1)

        self.label_61 = QLabel(self.wgDigitalOutput)
        self.label_61.setObjectName(u"label_61")
        self.label_61.setMinimumSize(QSize(30, 0))
        self.label_61.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_61, 1, 8, 1, 1)

        self.horizontalSpacer_48 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_34.addItem(self.horizontalSpacer_48, 1, 14, 1, 1)

        self.cbD5 = QCheckBox(self.wgDigitalOutput)
        self.cbD5.setObjectName(u"cbD5")
        self.cbD5.setMinimumSize(QSize(0, 0))

        self.gridLayout_34.addWidget(self.cbD5, 2, 5, 1, 1)

        self.label_60 = QLabel(self.wgDigitalOutput)
        self.label_60.setObjectName(u"label_60")
        self.label_60.setMinimumSize(QSize(30, 0))
        self.label_60.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.label_60, 1, 6, 1, 1)

        self.label_68 = QLabel(self.wgDigitalOutput)
        self.label_68.setObjectName(u"label_68")
        self.label_68.setMinimumSize(QSize(70, 0))
        self.label_68.setFont(font2)

        self.gridLayout_34.addWidget(self.label_68, 1, 0, 1, 1)

        self.label_67 = QLabel(self.wgDigitalOutput)
        self.label_67.setObjectName(u"label_67")
        self.label_67.setMinimumSize(QSize(70, 0))
        self.label_67.setFont(font2)

        self.gridLayout_34.addWidget(self.label_67, 0, 0, 1, 1)

        self.leDx = QLineEdit(self.wgDigitalOutput)
        self.leDx.setObjectName(u"leDx")
        self.leDx.setMaximumSize(QSize(30, 16777215))

        self.gridLayout_34.addWidget(self.leDx, 0, 1, 1, 1)

        self.cbDx = QCheckBox(self.wgDigitalOutput)
        self.cbDx.setObjectName(u"cbDx")
        self.cbDx.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.cbDx, 0, 2, 1, 1)

        self.leRx = QLineEdit(self.wgDigitalOutput)
        self.leRx.setObjectName(u"leRx")
        self.leRx.setMaximumSize(QSize(30, 16777215))

        self.gridLayout_34.addWidget(self.leRx, 0, 3, 1, 1)

        self.cbRx = QCheckBox(self.wgDigitalOutput)
        self.cbRx.setObjectName(u"cbRx")
        self.cbRx.setMaximumSize(QSize(16777215, 16777215))

        self.gridLayout_34.addWidget(self.cbRx, 0, 5, 1, 1)


        self.verticalLayout_42.addWidget(self.wgDigitalOutput)


        self.verticalLayout_53.addWidget(self.gbOutput)


        self.verticalLayout_44.addWidget(self.frame_35)


        self.verticalLayout_5.addWidget(self.frame_34)

        self.frame_36 = QFrame(self.wgJoggingScrollWidget)
        self.frame_36.setObjectName(u"frame_36")
        self.frame_36.setMinimumSize(QSize(0, 100))
        self.frame_36.setStyleSheet(u"#frame_23, #robotTitile\n"
"{\n"
"	border-radius: 0px;\n"
"}\n"
"\n"
"#frame_12\n"
"{	\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}\n"
"\n"
"")
        self.frame_36.setFrameShape(QFrame.StyledPanel)
        self.frame_36.setFrameShadow(QFrame.Raised)
        self.verticalLayout_54 = QVBoxLayout(self.frame_36)
        self.verticalLayout_54.setSpacing(0)
        self.verticalLayout_54.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_54.setObjectName(u"verticalLayout_54")
        self.verticalLayout_54.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_6 = QFrame(self.frame_36)
        self.robotTitile_6.setObjectName(u"robotTitile_6")
        self.robotTitile_6.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_6.setStyleSheet(u"")
        self.robotTitile_6.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_6.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_82 = QHBoxLayout(self.robotTitile_6)
        self.horizontalLayout_82.setSpacing(6)
        self.horizontalLayout_82.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_82.setObjectName(u"horizontalLayout_82")
        self.label_280 = QLabel(self.robotTitile_6)
        self.label_280.setObjectName(u"label_280")
        self.label_280.setMaximumSize(QSize(100, 16777215))
        self.label_280.setFont(font11)
        self.label_280.setAlignment(Qt.AlignCenter)

        self.horizontalLayout_82.addWidget(self.label_280)

        self.horizontalSpacer_102 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_82.addItem(self.horizontalSpacer_102)


        self.verticalLayout_54.addWidget(self.robotTitile_6)

        self.frame_37 = QFrame(self.frame_36)
        self.frame_37.setObjectName(u"frame_37")
        self.frame_37.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background: #262629;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_37.setFrameShape(QFrame.StyledPanel)
        self.frame_37.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_83 = QHBoxLayout(self.frame_37)
        self.horizontalLayout_83.setSpacing(6)
        self.horizontalLayout_83.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_83.setObjectName(u"horizontalLayout_83")
        self.fRobotPosition_4 = QFrame(self.frame_37)
        self.fRobotPosition_4.setObjectName(u"fRobotPosition_4")
        self.fRobotPosition_4.setMinimumSize(QSize(0, 40))
        self.fRobotPosition_4.setMaximumSize(QSize(16777215, 16777215))
        self.fRobotPosition_4.setStyleSheet(u"")
        self.gridLayout_20 = QGridLayout(self.fRobotPosition_4)
        self.gridLayout_20.setSpacing(7)
        self.gridLayout_20.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_20.setObjectName(u"gridLayout_20")
        self.gridLayout_20.setContentsMargins(0, 0, -1, 0)
        self.gbInput = QGroupBox(self.fRobotPosition_4)
        self.gbInput.setObjectName(u"gbInput")
        self.gbInput.setMinimumSize(QSize(0, 380))
        self.gbInput.setFont(font14)
        self.verticalLayout_43 = QVBoxLayout(self.gbInput)
        self.verticalLayout_43.setSpacing(6)
        self.verticalLayout_43.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_43.setObjectName(u"verticalLayout_43")
        self.verticalLayout_43.setContentsMargins(-1, 20, -1, -1)
        self.horizontalLayout_37 = QHBoxLayout()
        self.horizontalLayout_37.setSpacing(6)
        self.horizontalLayout_37.setObjectName(u"horizontalLayout_37")
        self.pbReadI0 = QPushButton(self.gbInput)
        self.pbReadI0.setObjectName(u"pbReadI0")
        self.pbReadI0.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_37.addWidget(self.pbReadI0)

        self.label_70 = QLabel(self.gbInput)
        self.label_70.setObjectName(u"label_70")
        self.label_70.setMinimumSize(QSize(30, 0))
        self.label_70.setMaximumSize(QSize(25, 16777215))
        self.label_70.setFont(font2)

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

        self.horizontalSpacer_51 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_37.addItem(self.horizontalSpacer_51)


        self.verticalLayout_43.addLayout(self.horizontalLayout_37)

        self.horizontalLayout_38 = QHBoxLayout()
        self.horizontalLayout_38.setSpacing(6)
        self.horizontalLayout_38.setObjectName(u"horizontalLayout_38")
        self.pbReadI1 = QPushButton(self.gbInput)
        self.pbReadI1.setObjectName(u"pbReadI1")
        self.pbReadI1.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_38.addWidget(self.pbReadI1)

        self.label_74 = QLabel(self.gbInput)
        self.label_74.setObjectName(u"label_74")
        self.label_74.setMinimumSize(QSize(30, 0))
        self.label_74.setMaximumSize(QSize(25, 16777215))
        self.label_74.setFont(font2)

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

        self.horizontalSpacer_52 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_38.addItem(self.horizontalSpacer_52)


        self.verticalLayout_43.addLayout(self.horizontalLayout_38)

        self.horizontalLayout_39 = QHBoxLayout()
        self.horizontalLayout_39.setSpacing(6)
        self.horizontalLayout_39.setObjectName(u"horizontalLayout_39")
        self.pbReadI2 = QPushButton(self.gbInput)
        self.pbReadI2.setObjectName(u"pbReadI2")
        self.pbReadI2.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_39.addWidget(self.pbReadI2)

        self.label_76 = QLabel(self.gbInput)
        self.label_76.setObjectName(u"label_76")
        self.label_76.setMinimumSize(QSize(30, 0))
        self.label_76.setMaximumSize(QSize(25, 16777215))
        self.label_76.setFont(font2)

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

        self.horizontalSpacer_53 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_39.addItem(self.horizontalSpacer_53)


        self.verticalLayout_43.addLayout(self.horizontalLayout_39)

        self.horizontalLayout_40 = QHBoxLayout()
        self.horizontalLayout_40.setSpacing(6)
        self.horizontalLayout_40.setObjectName(u"horizontalLayout_40")
        self.pbReadI3 = QPushButton(self.gbInput)
        self.pbReadI3.setObjectName(u"pbReadI3")
        self.pbReadI3.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_40.addWidget(self.pbReadI3)

        self.label_78 = QLabel(self.gbInput)
        self.label_78.setObjectName(u"label_78")
        self.label_78.setMinimumSize(QSize(30, 0))
        self.label_78.setMaximumSize(QSize(25, 16777215))
        self.label_78.setFont(font2)

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

        self.horizontalSpacer_54 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_40.addItem(self.horizontalSpacer_54)


        self.verticalLayout_43.addLayout(self.horizontalLayout_40)

        self.horizontalLayout_43 = QHBoxLayout()
        self.horizontalLayout_43.setSpacing(6)
        self.horizontalLayout_43.setObjectName(u"horizontalLayout_43")
        self.pbReadIx = QPushButton(self.gbInput)
        self.pbReadIx.setObjectName(u"pbReadIx")
        self.pbReadIx.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_43.addWidget(self.pbReadIx)

        self.leIx = QLineEdit(self.gbInput)
        self.leIx.setObjectName(u"leIx")
        self.leIx.setMinimumSize(QSize(30, 0))
        self.leIx.setMaximumSize(QSize(25, 16777215))
        self.leIx.setFont(font2)

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

        self.horizontalSpacer_57 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_43.addItem(self.horizontalSpacer_57)


        self.verticalLayout_43.addLayout(self.horizontalLayout_43)

        self.horizontalLayout_45 = QHBoxLayout()
        self.horizontalLayout_45.setSpacing(6)
        self.horizontalLayout_45.setObjectName(u"horizontalLayout_45")
        self.pbReadA0 = QPushButton(self.gbInput)
        self.pbReadA0.setObjectName(u"pbReadA0")
        self.pbReadA0.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_45.addWidget(self.pbReadA0)

        self.label_83 = QLabel(self.gbInput)
        self.label_83.setObjectName(u"label_83")
        self.label_83.setMinimumSize(QSize(30, 0))
        self.label_83.setMaximumSize(QSize(25, 16777215))
        self.label_83.setFont(font2)

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

        self.horizontalSpacer_58 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_45.addItem(self.horizontalSpacer_58)


        self.verticalLayout_43.addLayout(self.horizontalLayout_45)

        self.horizontalLayout_46 = QHBoxLayout()
        self.horizontalLayout_46.setSpacing(6)
        self.horizontalLayout_46.setObjectName(u"horizontalLayout_46")
        self.pbReadA1 = QPushButton(self.gbInput)
        self.pbReadA1.setObjectName(u"pbReadA1")
        self.pbReadA1.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_46.addWidget(self.pbReadA1)

        self.label_85 = QLabel(self.gbInput)
        self.label_85.setObjectName(u"label_85")
        self.label_85.setMinimumSize(QSize(30, 0))
        self.label_85.setMaximumSize(QSize(25, 16777215))
        self.label_85.setFont(font2)

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

        self.horizontalSpacer_59 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_46.addItem(self.horizontalSpacer_59)


        self.verticalLayout_43.addLayout(self.horizontalLayout_46)

        self.horizontalLayout_47 = QHBoxLayout()
        self.horizontalLayout_47.setSpacing(6)
        self.horizontalLayout_47.setObjectName(u"horizontalLayout_47")
        self.pbReadAx = QPushButton(self.gbInput)
        self.pbReadAx.setObjectName(u"pbReadAx")
        self.pbReadAx.setMinimumSize(QSize(50, 0))

        self.horizontalLayout_47.addWidget(self.pbReadAx)

        self.leAx = QLineEdit(self.gbInput)
        self.leAx.setObjectName(u"leAx")
        self.leAx.setMinimumSize(QSize(30, 0))
        self.leAx.setMaximumSize(QSize(25, 16777215))
        self.leAx.setFont(font2)

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

        self.horizontalSpacer_60 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_47.addItem(self.horizontalSpacer_60)


        self.verticalLayout_43.addLayout(self.horizontalLayout_47)


        self.gridLayout_20.addWidget(self.gbInput, 0, 0, 1, 1)


        self.horizontalLayout_83.addWidget(self.fRobotPosition_4)


        self.verticalLayout_54.addWidget(self.frame_37)


        self.verticalLayout_5.addWidget(self.frame_36)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_5.addItem(self.verticalSpacer)

        self.scrollArea_2.setWidget(self.wgJoggingScrollWidget)

        self.verticalLayout_4.addWidget(self.scrollArea_2)

        self.twDevices.addTab(self.tRobot, "")
        self.ConveyorTab = QWidget()
        self.ConveyorTab.setObjectName(u"ConveyorTab")
        self.ConveyorTab.setStyleSheet(u"QWidget#ConveyorTab\n"
"{\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"QLabel\n"
"{	\n"
"	color: #D0D0D1;\n"
"}")
        self.verticalLayout_22 = QVBoxLayout(self.ConveyorTab)
        self.verticalLayout_22.setSpacing(6)
        self.verticalLayout_22.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_22.setObjectName(u"verticalLayout_22")
        self.frame_38 = QFrame(self.ConveyorTab)
        self.frame_38.setObjectName(u"frame_38")
        self.frame_38.setMinimumSize(QSize(0, 100))
        self.frame_38.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}")
        self.frame_38.setFrameShape(QFrame.StyledPanel)
        self.frame_38.setFrameShadow(QFrame.Raised)
        self.verticalLayout_55 = QVBoxLayout(self.frame_38)
        self.verticalLayout_55.setSpacing(0)
        self.verticalLayout_55.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_55.setObjectName(u"verticalLayout_55")
        self.verticalLayout_55.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_7 = QFrame(self.frame_38)
        self.robotTitile_7.setObjectName(u"robotTitile_7")
        self.robotTitile_7.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_7.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_7.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_7.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_84 = QHBoxLayout(self.robotTitile_7)
        self.horizontalLayout_84.setSpacing(6)
        self.horizontalLayout_84.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_84.setObjectName(u"horizontalLayout_84")
        self.horizontalLayout_84.setContentsMargins(-1, 0, -1, 0)
        self.label = QLabel(self.robotTitile_7)
        self.label.setObjectName(u"label")

        self.horizontalLayout_84.addWidget(self.label)

        self.horizontalSpacer_47 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_84.addItem(self.horizontalSpacer_47)

        self.checkBox = QCheckBox(self.robotTitile_7)
        self.checkBox.setObjectName(u"checkBox")

        self.horizontalLayout_84.addWidget(self.checkBox)

        self.pbConveyorConnect = QPushButton(self.robotTitile_7)
        self.pbConveyorConnect.setObjectName(u"pbConveyorConnect")
        sizePolicy.setHeightForWidth(self.pbConveyorConnect.sizePolicy().hasHeightForWidth())
        self.pbConveyorConnect.setSizePolicy(sizePolicy)
        self.pbConveyorConnect.setMinimumSize(QSize(0, 28))
        self.pbConveyorConnect.setMaximumSize(QSize(16777215, 16777215))
        self.pbConveyorConnect.setFont(font4)
        self.pbConveyorConnect.setStyleSheet(u"QPushButton\n"
"{\n"
"	background-color: #3195EF;\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"}\n"
"QPushButton:hover\n"
"{	\n"
"	background-color: rgb(129, 129, 129);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{	\n"
"	background-color: rgb(81, 176, 255);\n"
"}\n"
"")
        self.pbConveyorConnect.setCheckable(True)

        self.horizontalLayout_84.addWidget(self.pbConveyorConnect)


        self.verticalLayout_55.addWidget(self.robotTitile_7)

        self.frame_39 = QFrame(self.frame_38)
        self.frame_39.setObjectName(u"frame_39")
        self.frame_39.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_39.setFrameShape(QFrame.StyledPanel)
        self.frame_39.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_85 = QHBoxLayout(self.frame_39)
        self.horizontalLayout_85.setSpacing(6)
        self.horizontalLayout_85.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_85.setObjectName(u"horizontalLayout_85")
        self.cbSelectedConveyor = QComboBox(self.frame_39)
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.addItem("")
        self.cbSelectedConveyor.setObjectName(u"cbSelectedConveyor")
        sizePolicy5.setHeightForWidth(self.cbSelectedConveyor.sizePolicy().hasHeightForWidth())
        self.cbSelectedConveyor.setSizePolicy(sizePolicy5)
        self.cbSelectedConveyor.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_85.addWidget(self.cbSelectedConveyor)

        self.horizontalSpacer_103 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_85.addItem(self.horizontalSpacer_103)

        self.groupBox_10 = QGroupBox(self.frame_39)
        self.groupBox_10.setObjectName(u"groupBox_10")
        self.horizontalLayout_86 = QHBoxLayout(self.groupBox_10)
        self.horizontalLayout_86.setSpacing(0)
        self.horizontalLayout_86.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_86.setObjectName(u"horizontalLayout_86")
        self.horizontalLayout_86.setContentsMargins(-1, 15, -1, 0)
        self.lbConveyorCOMName = QLabel(self.groupBox_10)
        self.lbConveyorCOMName.setObjectName(u"lbConveyorCOMName")
        self.lbConveyorCOMName.setFont(font8)
        self.lbConveyorCOMName.setStyleSheet(u"")

        self.horizontalLayout_86.addWidget(self.lbConveyorCOMName)


        self.horizontalLayout_85.addWidget(self.groupBox_10)

        self.groupBox_11 = QGroupBox(self.frame_39)
        self.groupBox_11.setObjectName(u"groupBox_11")
        self.horizontalLayout_87 = QHBoxLayout(self.groupBox_11)
        self.horizontalLayout_87.setSpacing(0)
        self.horizontalLayout_87.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_87.setObjectName(u"horizontalLayout_87")
        self.horizontalLayout_87.setContentsMargins(6, 15, -1, 0)
        self.lbBaudrate_3 = QLabel(self.groupBox_11)
        self.lbBaudrate_3.setObjectName(u"lbBaudrate_3")
        self.lbBaudrate_3.setFont(font8)
        self.lbBaudrate_3.setStyleSheet(u"")

        self.horizontalLayout_87.addWidget(self.lbBaudrate_3)


        self.horizontalLayout_85.addWidget(self.groupBox_11)


        self.verticalLayout_55.addWidget(self.frame_39)


        self.verticalLayout_22.addWidget(self.frame_38)

        self.horizontalLayout_48 = QHBoxLayout()
        self.horizontalLayout_48.setSpacing(6)
        self.horizontalLayout_48.setObjectName(u"horizontalLayout_48")
        self.horizontalLayout_48.setContentsMargins(10, -1, -1, -1)

        self.verticalLayout_22.addLayout(self.horizontalLayout_48)

        self.robotTitile_9 = QFrame(self.ConveyorTab)
        self.robotTitile_9.setObjectName(u"robotTitile_9")
        self.robotTitile_9.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_9.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_9.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_9.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_94 = QHBoxLayout(self.robotTitile_9)
        self.horizontalLayout_94.setSpacing(6)
        self.horizontalLayout_94.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_94.setObjectName(u"horizontalLayout_94")
        self.label_8 = QLabel(self.robotTitile_9)
        self.label_8.setObjectName(u"label_8")

        self.horizontalLayout_94.addWidget(self.label_8)

        self.cbConveyorType = QComboBox(self.robotTitile_9)
        self.cbConveyorType.addItem("")
        self.cbConveyorType.addItem("")
        self.cbConveyorType.addItem("")
        self.cbConveyorType.setObjectName(u"cbConveyorType")
        self.cbConveyorType.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_94.addWidget(self.cbConveyorType)

        self.horizontalSpacer_106 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_94.addItem(self.horizontalSpacer_106)


        self.verticalLayout_22.addWidget(self.robotTitile_9)

        self.fConveyorX = QFrame(self.ConveyorTab)
        self.fConveyorX.setObjectName(u"fConveyorX")
        self.fConveyorX.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}")
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
        font15 = QFont()
        font15.setPointSize(11)
        font15.setBold(False)
        font15.setKerning(True)
        self.leConveyorXPosition.setFont(font15)

        self.gridLayout_7.addWidget(self.leConveyorXPosition, 4, 1, 1, 1)

        self.label_12 = QLabel(self.fConveyorX)
        self.label_12.setObjectName(u"label_12")
        self.label_12.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_12, 4, 0, 1, 1)

        self.label_52 = QLabel(self.fConveyorX)
        self.label_52.setObjectName(u"label_52")
        self.label_52.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_52, 1, 0, 1, 1)

        self.label_57 = QLabel(self.fConveyorX)
        self.label_57.setObjectName(u"label_57")
        self.label_57.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_57, 3, 0, 1, 1)

        self.cbConveyorMode = QComboBox(self.fConveyorX)
        self.cbConveyorMode.addItem("")
        self.cbConveyorMode.addItem("")
        self.cbConveyorMode.setObjectName(u"cbConveyorMode")
        self.cbConveyorMode.setMinimumSize(QSize(0, 30))
        self.cbConveyorMode.setMaximumSize(QSize(200, 16777215))
        self.cbConveyorMode.setFont(font15)

        self.gridLayout_7.addWidget(self.cbConveyorMode, 1, 1, 1, 1)

        self.cbConveyorValueType = QComboBox(self.fConveyorX)
        self.cbConveyorValueType.addItem("")
        self.cbConveyorValueType.addItem("")
        self.cbConveyorValueType.setObjectName(u"cbConveyorValueType")
        self.cbConveyorValueType.setMinimumSize(QSize(0, 30))
        self.cbConveyorValueType.setMaximumSize(QSize(200, 16777215))
        self.cbConveyorValueType.setFont(font15)
        self.cbConveyorValueType.setStyleSheet(u"")

        self.gridLayout_7.addWidget(self.cbConveyorValueType, 2, 1, 1, 1)

        self.lbUnitOfConveyorMoving = QLabel(self.fConveyorX)
        self.lbUnitOfConveyorMoving.setObjectName(u"lbUnitOfConveyorMoving")
        self.lbUnitOfConveyorMoving.setEnabled(False)
        self.lbUnitOfConveyorMoving.setFont(font5)

        self.gridLayout_7.addWidget(self.lbUnitOfConveyorMoving, 4, 2, 1, 1)

        self.lbSpeedOfPositionMode = QLabel(self.fConveyorX)
        self.lbSpeedOfPositionMode.setObjectName(u"lbSpeedOfPositionMode")
        self.lbSpeedOfPositionMode.setEnabled(False)
        self.lbSpeedOfPositionMode.setFont(font5)

        self.gridLayout_7.addWidget(self.lbSpeedOfPositionMode, 3, 2, 1, 1)

        self.leConveyorXSpeed = QLineEdit(self.fConveyorX)
        self.leConveyorXSpeed.setObjectName(u"leConveyorXSpeed")
        self.leConveyorXSpeed.setEnabled(True)
        self.leConveyorXSpeed.setMinimumSize(QSize(0, 30))
        self.leConveyorXSpeed.setMaximumSize(QSize(200, 16777215))
        self.leConveyorXSpeed.setFont(font15)
        self.leConveyorXSpeed.setClearButtonEnabled(False)

        self.gridLayout_7.addWidget(self.leConveyorXSpeed, 3, 1, 1, 1)

        self.label_46 = QLabel(self.fConveyorX)
        self.label_46.setObjectName(u"label_46")
        self.label_46.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_7.addWidget(self.label_46, 2, 0, 1, 1)


        self.verticalLayout_22.addWidget(self.fConveyorX)

        self.fConveyorXHub = QFrame(self.ConveyorTab)
        self.fConveyorXHub.setObjectName(u"fConveyorXHub")
        self.fConveyorXHub.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}")
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
        self.leSubConveyor1Position.setFont(font15)
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
        self.cbSubConveyor2Mode.setFont(font15)
        self.cbSubConveyor2Mode.setStyleSheet(u"")

        self.gridLayout_18.addWidget(self.cbSubConveyor2Mode, 1, 2, 1, 1)

        self.leSubConveyor1Speed = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor1Speed.setObjectName(u"leSubConveyor1Speed")
        self.leSubConveyor1Speed.setMinimumSize(QSize(0, 30))
        self.leSubConveyor1Speed.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor1Speed.setFont(font15)

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
        self.leSubConveyor2Position.setFont(font15)
        self.leSubConveyor2Position.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor2Position, 4, 2, 1, 1)

        self.leSubConveyor2Speed = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor2Speed.setObjectName(u"leSubConveyor2Speed")
        self.leSubConveyor2Speed.setEnabled(True)
        self.leSubConveyor2Speed.setMinimumSize(QSize(0, 30))
        self.leSubConveyor2Speed.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor2Speed.setFont(font15)
        self.leSubConveyor2Speed.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor2Speed, 3, 2, 1, 1)

        self.cbSubConveyor3Mode = QComboBox(self.fConveyorXHub)
        self.cbSubConveyor3Mode.addItem("")
        self.cbSubConveyor3Mode.addItem("")
        self.cbSubConveyor3Mode.setObjectName(u"cbSubConveyor3Mode")
        self.cbSubConveyor3Mode.setMinimumSize(QSize(0, 30))
        self.cbSubConveyor3Mode.setMaximumSize(QSize(200, 16777215))
        self.cbSubConveyor3Mode.setFont(font15)
        self.cbSubConveyor3Mode.setStyleSheet(u"")

        self.gridLayout_18.addWidget(self.cbSubConveyor3Mode, 1, 3, 1, 1)

        self.leSubConveyor3Speed = QLineEdit(self.fConveyorXHub)
        self.leSubConveyor3Speed.setObjectName(u"leSubConveyor3Speed")
        self.leSubConveyor3Speed.setEnabled(True)
        self.leSubConveyor3Speed.setMinimumSize(QSize(0, 30))
        self.leSubConveyor3Speed.setMaximumSize(QSize(200, 16777215))
        self.leSubConveyor3Speed.setFont(font15)
        self.leSubConveyor3Speed.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor3Speed, 3, 3, 1, 1)

        self.cbSubConveyor1Mode = QComboBox(self.fConveyorXHub)
        self.cbSubConveyor1Mode.addItem("")
        self.cbSubConveyor1Mode.addItem("")
        self.cbSubConveyor1Mode.setObjectName(u"cbSubConveyor1Mode")
        self.cbSubConveyor1Mode.setMinimumSize(QSize(0, 30))
        self.cbSubConveyor1Mode.setMaximumSize(QSize(200, 16777215))
        self.cbSubConveyor1Mode.setFont(font15)
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
        self.leSubConveyor3Position.setFont(font15)
        self.leSubConveyor3Position.setClearButtonEnabled(False)

        self.gridLayout_18.addWidget(self.leSubConveyor3Position, 4, 3, 1, 1)


        self.verticalLayout_22.addWidget(self.fConveyorXHub)

        self.fConveyorCustom = QFrame(self.ConveyorTab)
        self.fConveyorCustom.setObjectName(u"fConveyorCustom")
        self.fConveyorCustom.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}")
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
        self.pbStopCustomConveyor2Command.setFont(font15)
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
        self.pbStartCustomConveyor2Command.setFont(font15)
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
        self.pbStopCustomConveyor3Command.setFont(font15)
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
        self.pbStopCustomConveyor1Command.setFont(font15)
        self.pbStopCustomConveyor1Command.setClearButtonEnabled(False)

        self.gridLayout_39.addWidget(self.pbStopCustomConveyor1Command, 4, 0, 1, 1)

        self.pbStartCustomConveyor1Command = QLineEdit(self.fConveyorCustom)
        self.pbStartCustomConveyor1Command.setObjectName(u"pbStartCustomConveyor1Command")
        self.pbStartCustomConveyor1Command.setMinimumSize(QSize(0, 30))
        self.pbStartCustomConveyor1Command.setMaximumSize(QSize(200, 16777215))
        self.pbStartCustomConveyor1Command.setFont(font15)

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
        self.pbStartCustomConveyor3Command.setFont(font15)
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
        self.EncoderTab.setStyleSheet(u"QWidget#EncoderTab\n"
"{\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"QLabel\n"
"{	\n"
"	color: #D0D0D1;\n"
"}")
        self.verticalLayout_8 = QVBoxLayout(self.EncoderTab)
        self.verticalLayout_8.setSpacing(6)
        self.verticalLayout_8.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_8.setObjectName(u"verticalLayout_8")
        self.frame_40 = QFrame(self.EncoderTab)
        self.frame_40.setObjectName(u"frame_40")
        self.frame_40.setMinimumSize(QSize(0, 100))
        self.frame_40.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}")
        self.frame_40.setFrameShape(QFrame.StyledPanel)
        self.frame_40.setFrameShadow(QFrame.Raised)
        self.verticalLayout_76 = QVBoxLayout(self.frame_40)
        self.verticalLayout_76.setSpacing(0)
        self.verticalLayout_76.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_76.setObjectName(u"verticalLayout_76")
        self.verticalLayout_76.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_10 = QFrame(self.frame_40)
        self.robotTitile_10.setObjectName(u"robotTitile_10")
        self.robotTitile_10.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_10.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_10.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_10.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_88 = QHBoxLayout(self.robotTitile_10)
        self.horizontalLayout_88.setSpacing(6)
        self.horizontalLayout_88.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_88.setObjectName(u"horizontalLayout_88")
        self.horizontalLayout_88.setContentsMargins(-1, 0, -1, 0)
        self.label_9 = QLabel(self.robotTitile_10)
        self.label_9.setObjectName(u"label_9")

        self.horizontalLayout_88.addWidget(self.label_9)

        self.horizontalSpacer_107 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_88.addItem(self.horizontalSpacer_107)

        self.checkBox_3 = QCheckBox(self.robotTitile_10)
        self.checkBox_3.setObjectName(u"checkBox_3")

        self.horizontalLayout_88.addWidget(self.checkBox_3)

        self.pbConnectEncoder = QPushButton(self.robotTitile_10)
        self.pbConnectEncoder.setObjectName(u"pbConnectEncoder")
        sizePolicy.setHeightForWidth(self.pbConnectEncoder.sizePolicy().hasHeightForWidth())
        self.pbConnectEncoder.setSizePolicy(sizePolicy)
        self.pbConnectEncoder.setMinimumSize(QSize(0, 28))
        self.pbConnectEncoder.setMaximumSize(QSize(16777215, 16777215))
        self.pbConnectEncoder.setFont(font4)
        self.pbConnectEncoder.setStyleSheet(u"QPushButton\n"
"{\n"
"	background-color: #3195EF;\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"}\n"
"QPushButton:hover\n"
"{	\n"
"	background-color: rgb(129, 129, 129);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{	\n"
"	background-color: rgb(81, 176, 255);\n"
"}\n"
"")
        self.pbConnectEncoder.setCheckable(True)

        self.horizontalLayout_88.addWidget(self.pbConnectEncoder)


        self.verticalLayout_76.addWidget(self.robotTitile_10)

        self.frame_42 = QFrame(self.frame_40)
        self.frame_42.setObjectName(u"frame_42")
        self.frame_42.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_42.setFrameShape(QFrame.StyledPanel)
        self.frame_42.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_95 = QHBoxLayout(self.frame_42)
        self.horizontalLayout_95.setSpacing(6)
        self.horizontalLayout_95.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_95.setObjectName(u"horizontalLayout_95")
        self.cbSelectedEncoder = QComboBox(self.frame_42)
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.addItem("")
        self.cbSelectedEncoder.setObjectName(u"cbSelectedEncoder")
        sizePolicy5.setHeightForWidth(self.cbSelectedEncoder.sizePolicy().hasHeightForWidth())
        self.cbSelectedEncoder.setSizePolicy(sizePolicy5)
        self.cbSelectedEncoder.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_95.addWidget(self.cbSelectedEncoder)

        self.horizontalSpacer_108 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_95.addItem(self.horizontalSpacer_108)

        self.groupBox_12 = QGroupBox(self.frame_42)
        self.groupBox_12.setObjectName(u"groupBox_12")
        self.horizontalLayout_96 = QHBoxLayout(self.groupBox_12)
        self.horizontalLayout_96.setSpacing(0)
        self.horizontalLayout_96.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_96.setObjectName(u"horizontalLayout_96")
        self.horizontalLayout_96.setContentsMargins(-1, 15, -1, 0)
        self.lbEncoderCOMname = QLabel(self.groupBox_12)
        self.lbEncoderCOMname.setObjectName(u"lbEncoderCOMname")
        self.lbEncoderCOMname.setFont(font8)
        self.lbEncoderCOMname.setStyleSheet(u"")

        self.horizontalLayout_96.addWidget(self.lbEncoderCOMname)


        self.horizontalLayout_95.addWidget(self.groupBox_12)

        self.groupBox_16 = QGroupBox(self.frame_42)
        self.groupBox_16.setObjectName(u"groupBox_16")
        self.horizontalLayout_97 = QHBoxLayout(self.groupBox_16)
        self.horizontalLayout_97.setSpacing(0)
        self.horizontalLayout_97.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_97.setObjectName(u"horizontalLayout_97")
        self.horizontalLayout_97.setContentsMargins(6, 15, -1, 0)
        self.lbBaudrate_5 = QLabel(self.groupBox_16)
        self.lbBaudrate_5.setObjectName(u"lbBaudrate_5")
        self.lbBaudrate_5.setFont(font8)
        self.lbBaudrate_5.setStyleSheet(u"")

        self.horizontalLayout_97.addWidget(self.lbBaudrate_5)


        self.horizontalLayout_95.addWidget(self.groupBox_16)


        self.verticalLayout_76.addWidget(self.frame_42)


        self.verticalLayout_8.addWidget(self.frame_40)

        self.frame_43 = QFrame(self.EncoderTab)
        self.frame_43.setObjectName(u"frame_43")
        self.frame_43.setMinimumSize(QSize(0, 100))
        self.frame_43.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}")
        self.frame_43.setFrameShape(QFrame.StyledPanel)
        self.frame_43.setFrameShadow(QFrame.Raised)
        self.verticalLayout_77 = QVBoxLayout(self.frame_43)
        self.verticalLayout_77.setSpacing(0)
        self.verticalLayout_77.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_77.setObjectName(u"verticalLayout_77")
        self.verticalLayout_77.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_11 = QFrame(self.frame_43)
        self.robotTitile_11.setObjectName(u"robotTitile_11")
        self.robotTitile_11.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_11.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_11.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_11.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_98 = QHBoxLayout(self.robotTitile_11)
        self.horizontalLayout_98.setSpacing(6)
        self.horizontalLayout_98.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_98.setObjectName(u"horizontalLayout_98")
        self.label_124 = QLabel(self.robotTitile_11)
        self.label_124.setObjectName(u"label_124")

        self.horizontalLayout_98.addWidget(self.label_124)

        self.cbEncoderType = QComboBox(self.robotTitile_11)
        self.cbEncoderType.addItem("")
        self.cbEncoderType.addItem("")
        self.cbEncoderType.addItem("")
        self.cbEncoderType.setObjectName(u"cbEncoderType")
        sizePolicy.setHeightForWidth(self.cbEncoderType.sizePolicy().hasHeightForWidth())
        self.cbEncoderType.setSizePolicy(sizePolicy)
        self.cbEncoderType.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_98.addWidget(self.cbEncoderType)

        self.horizontalSpacer_109 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_98.addItem(self.horizontalSpacer_109)

        self.cbEncoderActive = QCheckBox(self.robotTitile_11)
        self.cbEncoderActive.setObjectName(u"cbEncoderActive")
        self.cbEncoderActive.setChecked(True)

        self.horizontalLayout_98.addWidget(self.cbEncoderActive)


        self.verticalLayout_77.addWidget(self.robotTitile_11)

        self.frame_44 = QFrame(self.frame_43)
        self.frame_44.setObjectName(u"frame_44")
        self.frame_44.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_44.setFrameShape(QFrame.StyledPanel)
        self.frame_44.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_99 = QHBoxLayout(self.frame_44)
        self.horizontalLayout_99.setSpacing(6)
        self.horizontalLayout_99.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_99.setObjectName(u"horizontalLayout_99")
        self.gridLayout_21 = QGridLayout()
        self.gridLayout_21.setSpacing(10)
        self.gridLayout_21.setObjectName(u"gridLayout_21")
        self.gridLayout_21.setContentsMargins(10, -1, -1, -1)
        self.leEncoderCurrentPosition = QLineEdit(self.frame_44)
        self.leEncoderCurrentPosition.setObjectName(u"leEncoderCurrentPosition")
        sizePolicy.setHeightForWidth(self.leEncoderCurrentPosition.sizePolicy().hasHeightForWidth())
        self.leEncoderCurrentPosition.setSizePolicy(sizePolicy)

        self.gridLayout_21.addWidget(self.leEncoderCurrentPosition, 4, 1, 1, 1)

        self.pbSetEncoderInterval = QPushButton(self.frame_44)
        self.pbSetEncoderInterval.setObjectName(u"pbSetEncoderInterval")
        sizePolicy24 = QSizePolicy(QSizePolicy.MinimumExpanding, QSizePolicy.Minimum)
        sizePolicy24.setHorizontalStretch(0)
        sizePolicy24.setVerticalStretch(0)
        sizePolicy24.setHeightForWidth(self.pbSetEncoderInterval.sizePolicy().hasHeightForWidth())
        self.pbSetEncoderInterval.setSizePolicy(sizePolicy24)

        self.gridLayout_21.addWidget(self.pbSetEncoderInterval, 2, 2, 1, 1)

        self.label_129 = QLabel(self.frame_44)
        self.label_129.setObjectName(u"label_129")

        self.gridLayout_21.addWidget(self.label_129, 3, 0, 1, 1)

        self.leEncoderInterval = QLineEdit(self.frame_44)
        self.leEncoderInterval.setObjectName(u"leEncoderInterval")
        sizePolicy.setHeightForWidth(self.leEncoderInterval.sizePolicy().hasHeightForWidth())
        self.leEncoderInterval.setSizePolicy(sizePolicy)

        self.gridLayout_21.addWidget(self.leEncoderInterval, 2, 1, 1, 1)

        self.label_125 = QLabel(self.frame_44)
        self.label_125.setObjectName(u"label_125")

        self.gridLayout_21.addWidget(self.label_125, 2, 0, 1, 1)

        self.pbResetEncoder = QPushButton(self.frame_44)
        self.pbResetEncoder.setObjectName(u"pbResetEncoder")
        sizePolicy8.setHeightForWidth(self.pbResetEncoder.sizePolicy().hasHeightForWidth())
        self.pbResetEncoder.setSizePolicy(sizePolicy8)

        self.gridLayout_21.addWidget(self.pbResetEncoder, 4, 3, 1, 1)

        self.pbSetEncoderVelocity = QPushButton(self.frame_44)
        self.pbSetEncoderVelocity.setObjectName(u"pbSetEncoderVelocity")
        sizePolicy6.setHeightForWidth(self.pbSetEncoderVelocity.sizePolicy().hasHeightForWidth())
        self.pbSetEncoderVelocity.setSizePolicy(sizePolicy6)

        self.gridLayout_21.addWidget(self.pbSetEncoderVelocity, 3, 2, 1, 1)

        self.label_130 = QLabel(self.frame_44)
        self.label_130.setObjectName(u"label_130")

        self.gridLayout_21.addWidget(self.label_130, 4, 0, 1, 1)

        self.leEncoderVelocity = QLineEdit(self.frame_44)
        self.leEncoderVelocity.setObjectName(u"leEncoderVelocity")
        sizePolicy.setHeightForWidth(self.leEncoderVelocity.sizePolicy().hasHeightForWidth())
        self.leEncoderVelocity.setSizePolicy(sizePolicy)

        self.gridLayout_21.addWidget(self.leEncoderVelocity, 3, 1, 1, 1)

        self.horizontalSpacer_23 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_21.addItem(self.horizontalSpacer_23, 2, 4, 1, 1)

        self.pbReadEncoder = QPushButton(self.frame_44)
        self.pbReadEncoder.setObjectName(u"pbReadEncoder")
        sizePolicy6.setHeightForWidth(self.pbReadEncoder.sizePolicy().hasHeightForWidth())
        self.pbReadEncoder.setSizePolicy(sizePolicy6)

        self.gridLayout_21.addWidget(self.pbReadEncoder, 4, 2, 1, 1)

        self.cbConveyorForVirtualEncoder = QComboBox(self.frame_44)
        self.cbConveyorForVirtualEncoder.addItem("")
        self.cbConveyorForVirtualEncoder.addItem("")
        self.cbConveyorForVirtualEncoder.addItem("")
        self.cbConveyorForVirtualEncoder.setObjectName(u"cbConveyorForVirtualEncoder")
        sizePolicy.setHeightForWidth(self.cbConveyorForVirtualEncoder.sizePolicy().hasHeightForWidth())
        self.cbConveyorForVirtualEncoder.setSizePolicy(sizePolicy)
        self.cbConveyorForVirtualEncoder.setMinimumSize(QSize(100, 0))

        self.gridLayout_21.addWidget(self.cbConveyorForVirtualEncoder, 0, 1, 1, 1)

        self.cbLinkToConveyorX = QCheckBox(self.frame_44)
        self.cbLinkToConveyorX.setObjectName(u"cbLinkToConveyorX")
        self.cbLinkToConveyorX.setChecked(True)

        self.gridLayout_21.addWidget(self.cbLinkToConveyorX, 0, 0, 1, 1)


        self.horizontalLayout_99.addLayout(self.gridLayout_21)


        self.verticalLayout_77.addWidget(self.frame_44)


        self.verticalLayout_8.addWidget(self.frame_43)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.verticalLayout_8.addItem(self.horizontalSpacer)

        self.verticalSpacer_14 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_8.addItem(self.verticalSpacer_14)

        self.twDevices.addTab(self.EncoderTab, "")
        self.SliderTab = QWidget()
        self.SliderTab.setObjectName(u"SliderTab")
        self.SliderTab.setStyleSheet(u"QWidget#SliderTab\n"
"{\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"QLabel\n"
"{	\n"
"	border: none;\n"
"	color: #D0D0D1;\n"
"}")
        self.verticalLayout_23 = QVBoxLayout(self.SliderTab)
        self.verticalLayout_23.setSpacing(6)
        self.verticalLayout_23.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_23.setObjectName(u"verticalLayout_23")
        self.frame_45 = QFrame(self.SliderTab)
        self.frame_45.setObjectName(u"frame_45")
        self.frame_45.setMinimumSize(QSize(0, 100))
        self.frame_45.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}")
        self.frame_45.setFrameShape(QFrame.StyledPanel)
        self.frame_45.setFrameShadow(QFrame.Raised)
        self.verticalLayout_79 = QVBoxLayout(self.frame_45)
        self.verticalLayout_79.setSpacing(0)
        self.verticalLayout_79.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_79.setObjectName(u"verticalLayout_79")
        self.verticalLayout_79.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_13 = QFrame(self.frame_45)
        self.robotTitile_13.setObjectName(u"robotTitile_13")
        self.robotTitile_13.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_13.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_13.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_13.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_105 = QHBoxLayout(self.robotTitile_13)
        self.horizontalLayout_105.setSpacing(6)
        self.horizontalLayout_105.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_105.setObjectName(u"horizontalLayout_105")
        self.horizontalLayout_105.setContentsMargins(-1, 0, -1, 0)
        self.label_15 = QLabel(self.robotTitile_13)
        self.label_15.setObjectName(u"label_15")

        self.horizontalLayout_105.addWidget(self.label_15)

        self.horizontalSpacer_113 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_105.addItem(self.horizontalSpacer_113)

        self.checkBox_5 = QCheckBox(self.robotTitile_13)
        self.checkBox_5.setObjectName(u"checkBox_5")

        self.horizontalLayout_105.addWidget(self.checkBox_5)

        self.pbSlidingConnect = QPushButton(self.robotTitile_13)
        self.pbSlidingConnect.setObjectName(u"pbSlidingConnect")
        sizePolicy.setHeightForWidth(self.pbSlidingConnect.sizePolicy().hasHeightForWidth())
        self.pbSlidingConnect.setSizePolicy(sizePolicy)
        self.pbSlidingConnect.setMinimumSize(QSize(0, 0))
        self.pbSlidingConnect.setMaximumSize(QSize(16777215, 16777215))
        self.pbSlidingConnect.setFont(font4)
        self.pbSlidingConnect.setStyleSheet(u"QPushButton\n"
"{\n"
"	background-color: #3195EF;\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"}\n"
"QPushButton:hover\n"
"{	\n"
"	background-color: rgb(129, 129, 129);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{	\n"
"	background-color: rgb(81, 176, 255);\n"
"}\n"
"")
        self.pbSlidingConnect.setCheckable(True)

        self.horizontalLayout_105.addWidget(self.pbSlidingConnect)


        self.verticalLayout_79.addWidget(self.robotTitile_13)

        self.frame_46 = QFrame(self.frame_45)
        self.frame_46.setObjectName(u"frame_46")
        self.frame_46.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_46.setFrameShape(QFrame.StyledPanel)
        self.frame_46.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_106 = QHBoxLayout(self.frame_46)
        self.horizontalLayout_106.setSpacing(6)
        self.horizontalLayout_106.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_106.setObjectName(u"horizontalLayout_106")
        self.cbSelectedSlider = QComboBox(self.frame_46)
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.addItem("")
        self.cbSelectedSlider.setObjectName(u"cbSelectedSlider")
        sizePolicy5.setHeightForWidth(self.cbSelectedSlider.sizePolicy().hasHeightForWidth())
        self.cbSelectedSlider.setSizePolicy(sizePolicy5)
        self.cbSelectedSlider.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_106.addWidget(self.cbSelectedSlider)

        self.horizontalSpacer_114 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_106.addItem(self.horizontalSpacer_114)

        self.groupBox_19 = QGroupBox(self.frame_46)
        self.groupBox_19.setObjectName(u"groupBox_19")
        self.horizontalLayout_107 = QHBoxLayout(self.groupBox_19)
        self.horizontalLayout_107.setSpacing(0)
        self.horizontalLayout_107.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_107.setObjectName(u"horizontalLayout_107")
        self.horizontalLayout_107.setContentsMargins(-1, 15, -1, 0)
        self.lbSliderCOMName = QLabel(self.groupBox_19)
        self.lbSliderCOMName.setObjectName(u"lbSliderCOMName")
        self.lbSliderCOMName.setFont(font8)
        self.lbSliderCOMName.setStyleSheet(u"")

        self.horizontalLayout_107.addWidget(self.lbSliderCOMName)


        self.horizontalLayout_106.addWidget(self.groupBox_19)

        self.groupBox_20 = QGroupBox(self.frame_46)
        self.groupBox_20.setObjectName(u"groupBox_20")
        self.horizontalLayout_108 = QHBoxLayout(self.groupBox_20)
        self.horizontalLayout_108.setSpacing(0)
        self.horizontalLayout_108.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_108.setObjectName(u"horizontalLayout_108")
        self.horizontalLayout_108.setContentsMargins(6, 15, -1, 0)
        self.lbBaudrate_7 = QLabel(self.groupBox_20)
        self.lbBaudrate_7.setObjectName(u"lbBaudrate_7")
        self.lbBaudrate_7.setFont(font8)
        self.lbBaudrate_7.setStyleSheet(u"")

        self.horizontalLayout_108.addWidget(self.lbBaudrate_7)


        self.horizontalLayout_106.addWidget(self.groupBox_20)


        self.verticalLayout_79.addWidget(self.frame_46)


        self.verticalLayout_23.addWidget(self.frame_45)

        self.frame_48 = QFrame(self.SliderTab)
        self.frame_48.setObjectName(u"frame_48")
        sizePolicy.setHeightForWidth(self.frame_48.sizePolicy().hasHeightForWidth())
        self.frame_48.setSizePolicy(sizePolicy)
        self.frame_48.setMinimumSize(QSize(0, 0))
        self.frame_48.setStyleSheet(u"QFrame#frame_48\n"
"{\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}\n"
"\n"
"QPushButton\n"
"{\n"
"	padding: 5px;\n"
"}")
        self.frame_48.setFrameShape(QFrame.StyledPanel)
        self.frame_48.setFrameShadow(QFrame.Raised)
        self.verticalLayout_80 = QVBoxLayout(self.frame_48)
        self.verticalLayout_80.setSpacing(0)
        self.verticalLayout_80.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_80.setObjectName(u"verticalLayout_80")
        self.verticalLayout_80.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_14 = QFrame(self.frame_48)
        self.robotTitile_14.setObjectName(u"robotTitile_14")
        self.robotTitile_14.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_14.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_14.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_14.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_109 = QHBoxLayout(self.robotTitile_14)
        self.horizontalLayout_109.setSpacing(6)
        self.horizontalLayout_109.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_109.setObjectName(u"horizontalLayout_109")
        self.label_284 = QLabel(self.robotTitile_14)
        self.label_284.setObjectName(u"label_284")

        self.horizontalLayout_109.addWidget(self.label_284)

        self.cbEncoderType_2 = QComboBox(self.robotTitile_14)
        self.cbEncoderType_2.addItem("")
        self.cbEncoderType_2.addItem("")
        self.cbEncoderType_2.addItem("")
        self.cbEncoderType_2.setObjectName(u"cbEncoderType_2")
        self.cbEncoderType_2.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_109.addWidget(self.cbEncoderType_2)

        self.horizontalSpacer_115 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_109.addItem(self.horizontalSpacer_115)

        self.cbEncoderActive_2 = QCheckBox(self.robotTitile_14)
        self.cbEncoderActive_2.setObjectName(u"cbEncoderActive_2")
        self.cbEncoderActive_2.setChecked(True)

        self.horizontalLayout_109.addWidget(self.cbEncoderActive_2)


        self.verticalLayout_80.addWidget(self.robotTitile_14)

        self.gridLayout_8 = QGridLayout()
        self.gridLayout_8.setSpacing(10)
        self.gridLayout_8.setObjectName(u"gridLayout_8")
        self.gridLayout_8.setContentsMargins(10, 10, 10, 10)
        self.label_36 = QLabel(self.frame_48)
        self.label_36.setObjectName(u"label_36")
        self.label_36.setFont(font5)
        self.label_36.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_8.addWidget(self.label_36, 2, 0, 1, 1)

        self.pbSlidingHome = QPushButton(self.frame_48)
        self.pbSlidingHome.setObjectName(u"pbSlidingHome")
        sizePolicy16.setHeightForWidth(self.pbSlidingHome.sizePolicy().hasHeightForWidth())
        self.pbSlidingHome.setSizePolicy(sizePolicy16)
        self.pbSlidingHome.setMinimumSize(QSize(0, 0))
        self.pbSlidingHome.setMaximumSize(QSize(200, 40))
        font16 = QFont()
        font16.setPointSize(11)
        self.pbSlidingHome.setFont(font16)
        icon43 = QIcon()
        icon43.addFile(u"icon/icons8-home-32.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingHome.setIcon(icon43)

        self.gridLayout_8.addWidget(self.pbSlidingHome, 1, 1, 1, 1)

        self.leSlidingSpeed = QLineEdit(self.frame_48)
        self.leSlidingSpeed.setObjectName(u"leSlidingSpeed")
        self.leSlidingSpeed.setMinimumSize(QSize(0, 0))
        self.leSlidingSpeed.setMaximumSize(QSize(200, 40))

        self.gridLayout_8.addWidget(self.leSlidingSpeed, 2, 1, 1, 1)

        self.label_59 = QLabel(self.frame_48)
        self.label_59.setObjectName(u"label_59")
        self.label_59.setFont(font5)

        self.gridLayout_8.addWidget(self.label_59, 3, 2, 1, 1)

        self.leSlidingPosition = QLineEdit(self.frame_48)
        self.leSlidingPosition.setObjectName(u"leSlidingPosition")
        self.leSlidingPosition.setMinimumSize(QSize(0, 0))
        self.leSlidingPosition.setMaximumSize(QSize(200, 40))

        self.gridLayout_8.addWidget(self.leSlidingPosition, 3, 1, 1, 1)

        self.pbSlidingDisable = QPushButton(self.frame_48)
        self.pbSlidingDisable.setObjectName(u"pbSlidingDisable")
        sizePolicy24.setHeightForWidth(self.pbSlidingDisable.sizePolicy().hasHeightForWidth())
        self.pbSlidingDisable.setSizePolicy(sizePolicy24)
        self.pbSlidingDisable.setMinimumSize(QSize(0, 0))
        self.pbSlidingDisable.setMaximumSize(QSize(200, 40))
        self.pbSlidingDisable.setFont(font16)
        icon44 = QIcon()
        icon44.addFile(u"icon/icons8-sleeping-in-bed-32.png", QSize(), QIcon.Normal, QIcon.Off)
        self.pbSlidingDisable.setIcon(icon44)

        self.gridLayout_8.addWidget(self.pbSlidingDisable, 0, 1, 1, 1)

        self.label_37 = QLabel(self.frame_48)
        self.label_37.setObjectName(u"label_37")
        self.label_37.setFont(font5)
        self.label_37.setAlignment(Qt.AlignRight|Qt.AlignTrailing|Qt.AlignVCenter)

        self.gridLayout_8.addWidget(self.label_37, 3, 0, 1, 1)

        self.label_58 = QLabel(self.frame_48)
        self.label_58.setObjectName(u"label_58")
        self.label_58.setFont(font5)

        self.gridLayout_8.addWidget(self.label_58, 2, 2, 1, 1)


        self.verticalLayout_80.addLayout(self.gridLayout_8)


        self.verticalLayout_23.addWidget(self.frame_48)

        self.verticalSpacer_3 = QSpacerItem(20, 296, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_23.addItem(self.verticalSpacer_3)

        self.twDevices.addTab(self.SliderTab, "")
        self.MCUTab = QWidget()
        self.MCUTab.setObjectName(u"MCUTab")
        self.MCUTab.setStyleSheet(u"QWidget#MCUTab\n"
"{\n"
"	background-color: #1E1E20;\n"
"}\n"
"\n"
"QLabel\n"
"{	\n"
"	color: #D0D0D1;\n"
"}")
        self.verticalLayout_24 = QVBoxLayout(self.MCUTab)
        self.verticalLayout_24.setSpacing(6)
        self.verticalLayout_24.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_24.setObjectName(u"verticalLayout_24")
        self.frame_49 = QFrame(self.MCUTab)
        self.frame_49.setObjectName(u"frame_49")
        self.frame_49.setMinimumSize(QSize(0, 100))
        self.frame_49.setStyleSheet(u"QFrame\n"
"{\n"
"	border: 1px solid rgb(20, 20, 20);\n"
"}")
        self.frame_49.setFrameShape(QFrame.StyledPanel)
        self.frame_49.setFrameShadow(QFrame.Raised)
        self.verticalLayout_81 = QVBoxLayout(self.frame_49)
        self.verticalLayout_81.setSpacing(0)
        self.verticalLayout_81.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_81.setObjectName(u"verticalLayout_81")
        self.verticalLayout_81.setContentsMargins(0, 0, 0, 0)
        self.robotTitile_15 = QFrame(self.frame_49)
        self.robotTitile_15.setObjectName(u"robotTitile_15")
        self.robotTitile_15.setMaximumSize(QSize(16777215, 40))
        self.robotTitile_15.setStyleSheet(u"QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"	border: none;\n"
"}")
        self.robotTitile_15.setFrameShape(QFrame.StyledPanel)
        self.robotTitile_15.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_110 = QHBoxLayout(self.robotTitile_15)
        self.horizontalLayout_110.setSpacing(6)
        self.horizontalLayout_110.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_110.setObjectName(u"horizontalLayout_110")
        self.horizontalLayout_110.setContentsMargins(-1, 0, -1, 0)
        self.label_16 = QLabel(self.robotTitile_15)
        self.label_16.setObjectName(u"label_16")

        self.horizontalLayout_110.addWidget(self.label_16)

        self.horizontalSpacer_116 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_110.addItem(self.horizontalSpacer_116)

        self.checkBox_6 = QCheckBox(self.robotTitile_15)
        self.checkBox_6.setObjectName(u"checkBox_6")

        self.horizontalLayout_110.addWidget(self.checkBox_6)

        self.pbExternalControllerConnect = QPushButton(self.robotTitile_15)
        self.pbExternalControllerConnect.setObjectName(u"pbExternalControllerConnect")
        sizePolicy.setHeightForWidth(self.pbExternalControllerConnect.sizePolicy().hasHeightForWidth())
        self.pbExternalControllerConnect.setSizePolicy(sizePolicy)
        self.pbExternalControllerConnect.setMinimumSize(QSize(0, 0))
        self.pbExternalControllerConnect.setMaximumSize(QSize(16777215, 16777215))
        self.pbExternalControllerConnect.setFont(font4)
        self.pbExternalControllerConnect.setStyleSheet(u"QPushButton\n"
"{\n"
"	background-color: #3195EF;\n"
"	color: rgb(255, 255, 255);\n"
"	border: none;\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"}\n"
"QPushButton:hover\n"
"{	\n"
"	background-color: rgb(129, 129, 129);\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{	\n"
"	background-color: rgb(81, 176, 255);\n"
"}\n"
"")
        self.pbExternalControllerConnect.setCheckable(True)

        self.horizontalLayout_110.addWidget(self.pbExternalControllerConnect)


        self.verticalLayout_81.addWidget(self.robotTitile_15)

        self.frame_50 = QFrame(self.frame_49)
        self.frame_50.setObjectName(u"frame_50")
        self.frame_50.setStyleSheet(u"QFrame\n"
"{	\n"
"	background: #262629;\n"
"	border: none;\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QGroupBox\n"
"{\n"
"	background-color: transparent;\n"
"	border-radius: 5px;\n"
"	border: 1px solid #4A4A4F;\n"
"	\n"
"	color: rgb(219, 219, 220);\n"
"}")
        self.frame_50.setFrameShape(QFrame.StyledPanel)
        self.frame_50.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_111 = QHBoxLayout(self.frame_50)
        self.horizontalLayout_111.setSpacing(6)
        self.horizontalLayout_111.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_111.setObjectName(u"horizontalLayout_111")
        self.cbSelectedDevice = QComboBox(self.frame_50)
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.addItem("")
        self.cbSelectedDevice.setObjectName(u"cbSelectedDevice")
        sizePolicy5.setHeightForWidth(self.cbSelectedDevice.sizePolicy().hasHeightForWidth())
        self.cbSelectedDevice.setSizePolicy(sizePolicy5)
        self.cbSelectedDevice.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_111.addWidget(self.cbSelectedDevice)

        self.horizontalSpacer_117 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_111.addItem(self.horizontalSpacer_117)

        self.groupBox_21 = QGroupBox(self.frame_50)
        self.groupBox_21.setObjectName(u"groupBox_21")
        self.horizontalLayout_112 = QHBoxLayout(self.groupBox_21)
        self.horizontalLayout_112.setSpacing(0)
        self.horizontalLayout_112.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_112.setObjectName(u"horizontalLayout_112")
        self.horizontalLayout_112.setContentsMargins(-1, 15, -1, 0)
        self.lbExternalCOMName = QLabel(self.groupBox_21)
        self.lbExternalCOMName.setObjectName(u"lbExternalCOMName")
        self.lbExternalCOMName.setFont(font8)
        self.lbExternalCOMName.setStyleSheet(u"")

        self.horizontalLayout_112.addWidget(self.lbExternalCOMName)


        self.horizontalLayout_111.addWidget(self.groupBox_21)

        self.groupBox_22 = QGroupBox(self.frame_50)
        self.groupBox_22.setObjectName(u"groupBox_22")
        self.horizontalLayout_113 = QHBoxLayout(self.groupBox_22)
        self.horizontalLayout_113.setSpacing(0)
        self.horizontalLayout_113.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_113.setObjectName(u"horizontalLayout_113")
        self.horizontalLayout_113.setContentsMargins(6, 15, -1, 0)
        self.lbBaudrate_8 = QLabel(self.groupBox_22)
        self.lbBaudrate_8.setObjectName(u"lbBaudrate_8")
        self.lbBaudrate_8.setFont(font8)
        self.lbBaudrate_8.setStyleSheet(u"")

        self.horizontalLayout_113.addWidget(self.lbBaudrate_8)


        self.horizontalLayout_111.addWidget(self.groupBox_22)


        self.verticalLayout_81.addWidget(self.frame_50)


        self.verticalLayout_24.addWidget(self.frame_49)

        self.widget1 = QWidget(self.MCUTab)
        self.widget1.setObjectName(u"widget1")
        self.widget1.setMaximumSize(QSize(16777215, 40))
        self.horizontalLayout_50 = QHBoxLayout(self.widget1)
        self.horizontalLayout_50.setSpacing(10)
        self.horizontalLayout_50.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_50.setObjectName(u"horizontalLayout_50")
        self.horizontalLayout_50.setContentsMargins(0, 0, 10, 10)

        self.verticalLayout_24.addWidget(self.widget1)

        self.teReceiveFromMCU = QTextEdit(self.MCUTab)
        self.teReceiveFromMCU.setObjectName(u"teReceiveFromMCU")
        self.teReceiveFromMCU.setStyleSheet(u"background-color: rgb(230, 230, 230);")

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
        self.pbCalibStep1.toggled.connect(self.fCalibStep1.setVisible)
        self.gbImageProvider.toggled.connect(self.fImageProvider.setVisible)
        self.gbCameraCalibration.toggled.connect(self.fCameraCalibrationFrame.setVisible)
        self.gbCameraObject.toggled.connect(self.fVisionObjectFrame.setVisible)
        self.gbCameraVariable.toggled.connect(self.fVisionVariableFrame.setVisible)
        self.pbCalibStep2.toggled.connect(self.fCalibStep2.setVisible)
        self.gbTrackingManager.toggled.connect(self.fTrackingManager.setVisible)

        self.twDeltaManager.setCurrentIndex(0)
        self.pbReadI0_3.setDefault(False)
        self.twModule.setCurrentIndex(1)
        self.pbImageMapping.setDefault(False)
        self.cbImageSource.setCurrentIndex(0)
        self.twDevices.setCurrentIndex(0)
        self.pbPump.setDefault(False)
        self.pbLaser.setDefault(False)
        self.pbGrip.setDefault(False)


        QMetaObject.connectSlotsByName(RobotWindow)
    # setupUi

    def retranslateUi(self, RobotWindow):
        RobotWindow.setWindowTitle(QCoreApplication.translate("RobotWindow", u"Delta X Software - Version 1.2", None))
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
        self.pbReadI0_3.setText(QCoreApplication.translate("RobotWindow", u"Server", None))
        self.label_161.setText(QCoreApplication.translate("RobotWindow", u"IP", None))
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
        self.label_28.setText(QCoreApplication.translate("RobotWindow", u"Program Thread", None))
        self.cbProgramThreadID.setItemText(0, QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbProgramThreadID.setItemText(1, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbProgramThreadID.setItemText(2, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbProgramThreadID.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.rbEditorStart.setText(QCoreApplication.translate("RobotWindow", u"Start", None))
        self.rbEditorCurrent.setText(QCoreApplication.translate("RobotWindow", u"Current", None))
#if QT_CONFIG(tooltip)
        self.pbExecuteGcodes.setToolTip(QCoreApplication.translate("RobotWindow", u"Execute Gcode", None))
#endif // QT_CONFIG(tooltip)
        self.pbExecuteGcodes.setText(QCoreApplication.translate("RobotWindow", u"Run", None))
        self.label_81.setText(QCoreApplication.translate("RobotWindow", u"Gcode File", None))
        self.cbProgramSource.setItemText(0, QCoreApplication.translate("RobotWindow", u"Local", None))
        self.cbProgramSource.setItemText(1, QCoreApplication.translate("RobotWindow", u"Online", None))

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
        self.cbVariableDisplayOption.setItemText(0, QCoreApplication.translate("RobotWindow", u"Visible Variables", None))
        self.cbVariableDisplayOption.setItemText(1, QCoreApplication.translate("RobotWindow", u"All Variables", None))

        self.lbSelectedProgram.setText(QCoreApplication.translate("RobotWindow", u"No Name", None))
#if QT_CONFIG(tooltip)
        self.pbSaveGcode.setToolTip(QCoreApplication.translate("RobotWindow", u"Save Gcode Into File", None))
#endif // QT_CONFIG(tooltip)
        self.pbSaveGcode.setText("")
#if QT_CONFIG(tooltip)
        self.pbFormat.setToolTip(QCoreApplication.translate("RobotWindow", u"Format Gcode Lines", None))
#endif // QT_CONFIG(tooltip)
        self.pbFormat.setText(QCoreApplication.translate("RobotWindow", u"Format", None))
        self.cbEditGcodeLock.setText(QCoreApplication.translate("RobotWindow", u"Lock", None))
#if QT_CONFIG(tooltip)
        self.pbOpenGcodeDocs.setToolTip(QCoreApplication.translate("RobotWindow", u"Gcode Docs", None))
#endif // QT_CONFIG(tooltip)
        self.pbOpenGcodeDocs.setText(QCoreApplication.translate("RobotWindow", u"Format", None))
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
                        ":0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N05 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G28</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-weight:600;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Acceleration</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N10 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">M204</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> A1200</span></p>\n"
"<p style=\" margin-top:0"
                        "px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Speed</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N15 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> F200</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Declare variables</span></p>\n"
"<p style=\" margin-top:0px; marg"
                        "in-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N20 </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#dbdbdc;\">#Counter</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> = 0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N30 </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#dbdbdc;\">#Counter</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> = </span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#dbdbdc;\">#Counter</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> + 1</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; f"
                        "ont-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#55aa00;\">;Call subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N35 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">M98</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> P2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; co"
                        "lor:#00aa00;\">; Begin subprogram</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N40 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">O2000</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N45 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 80]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-"
                        "indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N50 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> X-100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N55 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 100]</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell D"
                        "lg 2'; color:#dbdbdc;\">N60 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 80]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N65 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> X100</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N70 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 100]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; ma"
                        "rgin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N75 M99</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;End subprogram</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2';\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#00aa00;\">;Loop 5 times</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">N80 </span><span style=\" font"
                        "-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">IF</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> [</span><span style=\" font-family:'MS Shell Dlg 2'; font-style:italic; color:#dbdbdc;\">#Counter</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> &lt; 5] </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">THEN</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">GOTO</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> 30</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#d"
                        "bdbdc;\">N85 </span><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G28</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2';\"> </span></p></body></html>", None))
        self.lbSelectedProgram_3.setText(QCoreApplication.translate("RobotWindow", u"Function", None))
#if QT_CONFIG(tooltip)
        self.pbSaveFunctionScripts.setToolTip(QCoreApplication.translate("RobotWindow", u"Save Gcode Into File", None))
#endif // QT_CONFIG(tooltip)
        self.pbSaveFunctionScripts.setText("")
        self.pteScriptFunction.setHtml(QCoreApplication.translate("RobotWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:8pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">O2001</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent"
                        ":0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 50]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 30]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 50]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; font-weight:600; color:#"
                        "dbdbdc;\">G01</span><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\"> Z[#robot0.HOME_Z - 30]</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'MS Shell Dlg 2'; color:#dbdbdc;\">M99</span></p></body></html>", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tGcodeEditor), QCoreApplication.translate("RobotWindow", u"G-Script", None))
        self.label_191.setText(QCoreApplication.translate("RobotWindow", u"Detecting Thread", None))
        self.cbSelectedDetecting.setItemText(0, QCoreApplication.translate("RobotWindow", u"detect0", None))
        self.cbSelectedDetecting.setItemText(1, QCoreApplication.translate("RobotWindow", u"detect1", None))
        self.cbSelectedDetecting.setItemText(2, QCoreApplication.translate("RobotWindow", u"detect2", None))
        self.cbSelectedDetecting.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.gbImageViewer.setTitle(QCoreApplication.translate("RobotWindow", u"Image Viewer", None))
#if QT_CONFIG(tooltip)
        self.pbFindChessboardTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Warp Perspective", None))
#endif // QT_CONFIG(tooltip)
        self.pbFindChessboardTool.setText(QCoreApplication.translate("RobotWindow", u"Find Chessboard", None))
#if QT_CONFIG(tooltip)
        self.pbAreaTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Warp Perspective", None))
#endif // QT_CONFIG(tooltip)
        self.pbAreaTool.setText(QCoreApplication.translate("RobotWindow", u"Crop Area", None))
#if QT_CONFIG(tooltip)
        self.pbCalibPointTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Set Calib Point", None))
#endif // QT_CONFIG(tooltip)
        self.pbCalibPointTool.setText(QCoreApplication.translate("RobotWindow", u"Select Calibration Points", None))
#if QT_CONFIG(tooltip)
        self.pbMappingPointTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Check Point Position On Camera", None))
#endif // QT_CONFIG(tooltip)
        self.pbMappingPointTool.setText(QCoreApplication.translate("RobotWindow", u"Test Calibration Point", None))
#if QT_CONFIG(tooltip)
        self.pbWarpTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Warp Perspective", None))
#endif // QT_CONFIG(tooltip)
        self.pbWarpTool.setText(QCoreApplication.translate("RobotWindow", u"Transform Image", None))
#if QT_CONFIG(tooltip)
        self.pbFilterTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Blob Filter", None))
#endif // QT_CONFIG(tooltip)
        self.pbFilterTool.setText(QCoreApplication.translate("RobotWindow", u"Color Filter Tool", None))
#if QT_CONFIG(tooltip)
        self.pbGetSizeTool.setToolTip(QCoreApplication.translate("RobotWindow", u"Blob Filter", None))
#endif // QT_CONFIG(tooltip)
        self.pbGetSizeTool.setText(QCoreApplication.translate("RobotWindow", u"Object Size Tool", None))
        self.label_213.setText(QCoreApplication.translate("RobotWindow", u"Output", None))
        self.cbImageOutput.setItemText(0, QCoreApplication.translate("RobotWindow", u"Calibrating", None))
        self.cbImageOutput.setItemText(1, QCoreApplication.translate("RobotWindow", u"Detecting", None))
        self.cbImageOutput.setItemText(2, QCoreApplication.translate("RobotWindow", u"Original", None))

        self.lbDisplayRatio_2.setText(QCoreApplication.translate("RobotWindow", u"Zoom:", None))
        self.lbDisplayRatio_3.setText(QCoreApplication.translate("RobotWindow", u"Ctrl + Scroll", None))
        self.pbZoomInCameraView.setText(QCoreApplication.translate("RobotWindow", u"Zoom In", None))
        self.pbZoomOutCameraView.setText(QCoreApplication.translate("RobotWindow", u"Zoom Out", None))
        self.lbDisplayRatio.setText(QCoreApplication.translate("RobotWindow", u"Ratio: 100%", None))
        self.lbMatSize.setText(QCoreApplication.translate("RobotWindow", u"Re: 800x500", None))
        self.gbImageProvider.setTitle(QCoreApplication.translate("RobotWindow", u"Image Provider", None))
        self.label_176.setText(QCoreApplication.translate("RobotWindow", u"Source", None))
        self.cbSourceForImageProvider.setItemText(0, QCoreApplication.translate("RobotWindow", u"Webcam", None))
        self.cbSourceForImageProvider.setItemText(1, QCoreApplication.translate("RobotWindow", u"Industrial Camera", None))
        self.cbSourceForImageProvider.setItemText(2, QCoreApplication.translate("RobotWindow", u"Images", None))
        self.cbSourceForImageProvider.setItemText(3, QCoreApplication.translate("RobotWindow", u"Socket", None))

        self.label_6.setText(QCoreApplication.translate("RobotWindow", u"Tracking Thread", None))
        self.cbTrackingThreadForCamera.setItemText(0, QCoreApplication.translate("RobotWindow", u"thread0", None))
        self.cbTrackingThreadForCamera.setItemText(1, QCoreApplication.translate("RobotWindow", u"thread1", None))
        self.cbTrackingThreadForCamera.setItemText(2, QCoreApplication.translate("RobotWindow", u"thread2", None))
        self.cbTrackingThreadForCamera.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

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
        self.lbWarpGuide.setText("")
        self.pbCalibStep2.setText(QCoreApplication.translate("RobotWindow", u"Step 2: Coordinate correction", None))
        self.label_2.setText(QCoreApplication.translate("RobotWindow", u"2.1 Select two points on the camera", None))
        self.lbCalibGuide.setText("")
        self.label_7.setText(QCoreApplication.translate("RobotWindow", u"2.2 Enter the actual coordinates of points P1 and P2", None))
        self.leRealityP1P2Distance.setText(QCoreApplication.translate("RobotWindow", u"80", None))
        self.leCalibOffset_X.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_148.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
#if QT_CONFIG(tooltip)
        self.tbPastePoint1.setToolTip(QCoreApplication.translate("RobotWindow", u"Paste", None))
#endif // QT_CONFIG(tooltip)
        self.tbPastePoint1.setText("")
#if QT_CONFIG(tooltip)
        self.pbImageMapping.setToolTip(QCoreApplication.translate("RobotWindow", u"Perspective Transformation", None))
#endif // QT_CONFIG(tooltip)
        self.pbImageMapping.setText(QCoreApplication.translate("RobotWindow", u"Calculate Mapping Matrix", None))
        self.label_39.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
#if QT_CONFIG(tooltip)
        self.leRealityPoint2Y.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leRealityPoint2Y.setText(QCoreApplication.translate("RobotWindow", u"100", None))
#if QT_CONFIG(tooltip)
        self.tbPastePoint2.setToolTip(QCoreApplication.translate("RobotWindow", u"Paste", None))
#endif // QT_CONFIG(tooltip)
        self.tbPastePoint2.setText("")
        self.pbCalibPoint1.setText(QCoreApplication.translate("RobotWindow", u"Save Robot Position To P1'", None))
#if QT_CONFIG(shortcut)
        self.pbCalibPoint1.setShortcut(QCoreApplication.translate("RobotWindow", u"!", None))
#endif // QT_CONFIG(shortcut)
        self.leRealityPoint1X.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.label_133.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_38.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_10.setText(QCoreApplication.translate("RobotWindow", u"2.3 Press the button to calculate the transformation matrix", None))
        self.pbCalibPoint2.setText(QCoreApplication.translate("RobotWindow", u"Save Robot Position To P2'", None))
#if QT_CONFIG(shortcut)
        self.pbCalibPoint2.setShortcut(QCoreApplication.translate("RobotWindow", u"@", None))
#endif // QT_CONFIG(shortcut)
        self.label_40.setText(QCoreApplication.translate("RobotWindow", u"P1'", None))
        self.label_139.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_142.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.lbCalibType.setText(QCoreApplication.translate("RobotWindow", u"Offset", None))
        self.lbCalibType_2.setText(QCoreApplication.translate("RobotWindow", u"Calib Tool", None))
        self.leRealityPoint1Y.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.lbCalibType_3.setText(QCoreApplication.translate("RobotWindow", u"P1' & P2' Distance", None))
        self.leRealityPoint2X.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.label_141.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_132.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_140.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.label_41.setText(QCoreApplication.translate("RobotWindow", u"P2'", None))
        self.leCalibOffset_Y.setText(QCoreApplication.translate("RobotWindow", u"0", None))
        self.cbCalibType.setItemText(0, QCoreApplication.translate("RobotWindow", u"None", None))
        self.cbCalibType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Calib Paper 0.1", None))

        self.gbCameraObject.setTitle(QCoreApplication.translate("RobotWindow", u"Object", None))
        self.label_126.setText(QCoreApplication.translate("RobotWindow", u"Detecting algorithm", None))
        self.cbDetectingAlgorithm.setItemText(0, QCoreApplication.translate("RobotWindow", u"Find Blobs", None))
        self.cbDetectingAlgorithm.setItemText(1, QCoreApplication.translate("RobotWindow", u"Find Circles", None))
        self.cbDetectingAlgorithm.setItemText(2, QCoreApplication.translate("RobotWindow", u"External Script", None))

        self.label_45.setText(QCoreApplication.translate("RobotWindow", u"Similarity Threshold", None))
        self.leSimilarityThreshold.setText(QCoreApplication.translate("RobotWindow", u"20", None))
        self.leLRec.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.leMaxLRec.setText(QCoreApplication.translate("RobotWindow", u"1.5", None))
        self.leWRec.setText(QCoreApplication.translate("RobotWindow", u"30", None))
        self.leMinLRec.setText(QCoreApplication.translate("RobotWindow", u"0.5", None))
        self.label_42.setText(QCoreApplication.translate("RobotWindow", u"Width", None))
        self.label_175.setText(QCoreApplication.translate("RobotWindow", u"Max", None))
        self.cbObjectType.setItemText(0, QCoreApplication.translate("RobotWindow", u"1", None))
        self.cbObjectType.setItemText(1, QCoreApplication.translate("RobotWindow", u"2", None))
        self.cbObjectType.setItemText(2, QCoreApplication.translate("RobotWindow", u"3", None))
        self.cbObjectType.setItemText(3, QCoreApplication.translate("RobotWindow", u"4", None))
        self.cbObjectType.setItemText(4, QCoreApplication.translate("RobotWindow", u"5", None))
        self.cbObjectType.setItemText(5, QCoreApplication.translate("RobotWindow", u"+", None))

        self.label_43.setText(QCoreApplication.translate("RobotWindow", u"Length", None))
        self.label_163.setText(QCoreApplication.translate("RobotWindow", u"Type", None))
        self.label_173.setText(QCoreApplication.translate("RobotWindow", u"Max", None))
        self.label_174.setText(QCoreApplication.translate("RobotWindow", u"Min", None))
        self.label_55.setText(QCoreApplication.translate("RobotWindow", u"pixel", None))
        self.label_54.setText(QCoreApplication.translate("RobotWindow", u"pixel", None))
        self.label_172.setText(QCoreApplication.translate("RobotWindow", u"Min", None))
        self.leMaxWRec.setText(QCoreApplication.translate("RobotWindow", u"1.5", None))
        self.leMinWRec.setText(QCoreApplication.translate("RobotWindow", u"0.5", None))
        self.pbRunExternalScript.setText("")
        self.label_145.setText(QCoreApplication.translate("RobotWindow", u"Python Url", None))
        self.pbExternalScriptOpen.setText("")
        self.lePythonUrl.setText(QCoreApplication.translate("RobotWindow", u"script-example/mushroom-2.0.py", None))
        self.cbImageSource.setItemText(0, QCoreApplication.translate("RobotWindow", u"Origin Image", None))
        self.cbImageSource.setItemText(1, QCoreApplication.translate("RobotWindow", u"Calibrated Image", None))
        self.cbImageSource.setItemText(2, QCoreApplication.translate("RobotWindow", u"Color Filtered Image", None))

        self.label_180.setText(QCoreApplication.translate("RobotWindow", u"Host IP", None))
        self.label_146.setText(QCoreApplication.translate("RobotWindow", u"Transmission Image", None))
        self.label_186.setText(QCoreApplication.translate("RobotWindow", u"byte: \"[width][height][channel][data]\"", None))
        self.label_183.setText(QCoreApplication.translate("RobotWindow", u"8844", None))
        self.label_184.setText(QCoreApplication.translate("RobotWindow", u"Sending format", None))
        self.label_185.setText(QCoreApplication.translate("RobotWindow", u"Receive format", None))
        self.label_187.setText(QCoreApplication.translate("RobotWindow", u"string: \"#Object = [x],[y],[width],[height],[angle];\"", None))
        self.pbExternalScriptHelp.setText(QCoreApplication.translate("RobotWindow", u"?", None))
        self.label_182.setText(QCoreApplication.translate("RobotWindow", u"Port", None))
        self.label_181.setText(QCoreApplication.translate("RobotWindow", u"127.0.0.1", None))
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
        self.label_198.setText(QCoreApplication.translate("RobotWindow", u"max 250", None))
        self.label_199.setText(QCoreApplication.translate("RobotWindow", u"max 250", None))
        self.gbCameraVariable.setTitle(QCoreApplication.translate("RobotWindow", u"Variable", None))
        self.label_34.setText(QCoreApplication.translate("RobotWindow", u"Auto Update", None))
        self.cbAutoUpdateObjectsDisplay.setItemText(0, QCoreApplication.translate("RobotWindow", u"No", None))
        self.cbAutoUpdateObjectsDisplay.setItemText(1, QCoreApplication.translate("RobotWindow", u"500 ms", None))

        self.pbUpdateObjectToView.setText(QCoreApplication.translate("RobotWindow", u"Update", None))
#if QT_CONFIG(tooltip)
        self.pbClearDetectObjects.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>Clear All Objects in Memory</p><p>M98 PclearObjects --&gt; Clear All</p><p>M98 PdeleteFirstObject --&gt; Delete First</p></body></html>", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbClearDetectObjects.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbClearDetectObjects.setText(QCoreApplication.translate("RobotWindow", u"Clear Objects", None))
        self.leLimitMinX.setText(QCoreApplication.translate("RobotWindow", u"-300", None))
        self.label_162.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.label_155.setText(QCoreApplication.translate("RobotWindow", u"Max X", None))
        self.leLimitMaxX.setText(QCoreApplication.translate("RobotWindow", u"1200", None))
        self.label_170.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.leLimitMaxY.setText(QCoreApplication.translate("RobotWindow", u"400", None))
        self.label_171.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.label_56.setText(QCoreApplication.translate("RobotWindow", u"Min X", None))
        self.label_156.setText(QCoreApplication.translate("RobotWindow", u"Min Y", None))
        self.leLimitMinY.setText(QCoreApplication.translate("RobotWindow", u"-400", None))
        self.label_159.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.label_157.setText(QCoreApplication.translate("RobotWindow", u"Max Y", None))
        self.label_196.setText(QCoreApplication.translate("RobotWindow", u"Object List", None))
        self.label_44.setText(QCoreApplication.translate("RobotWindow", u"Limit Area", None))
        self.leDetectingObjectListName.setText(QCoreApplication.translate("RobotWindow", u"#Objects", None))
        self.twModule.setTabText(self.twModule.indexOf(self.tObjectDetecting), QCoreApplication.translate("RobotWindow", u"Object Detector", None))
        self.gbTrackingManager.setTitle(QCoreApplication.translate("RobotWindow", u"Tracking Manager", None))
        self.cbSelectedTracking.setItemText(0, QCoreApplication.translate("RobotWindow", u"tracking0", None))
        self.cbSelectedTracking.setItemText(1, QCoreApplication.translate("RobotWindow", u"tracking1", None))
        self.cbSelectedTracking.setItemText(2, QCoreApplication.translate("RobotWindow", u"tracking2", None))
        self.cbSelectedTracking.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.label_144.setText(QCoreApplication.translate("RobotWindow", u"Object List", None))
        self.cbReverseEncoderValue.setText(QCoreApplication.translate("RobotWindow", u"Reverse Value", None))
        self.pbSaveTrackingManager.setText(QCoreApplication.translate("RobotWindow", u"Save", None))
        self.label_164.setText(QCoreApplication.translate("RobotWindow", u"Encoder", None))
        self.leSelectedTrackingObjectList.setText(QCoreApplication.translate("RobotWindow", u"#Objects", None))
        self.leVelocityVector.setText(QCoreApplication.translate("RobotWindow", u"#Vector1", None))
        self.cbTrackingEncoderSource.setItemText(0, QCoreApplication.translate("RobotWindow", u"encoder0", None))
        self.cbTrackingEncoderSource.setItemText(1, QCoreApplication.translate("RobotWindow", u"encoder1", None))
        self.cbTrackingEncoderSource.setItemText(2, QCoreApplication.translate("RobotWindow", u"encoder2", None))

        self.label_160.setText(QCoreApplication.translate("RobotWindow", u"Tracking Thread", None))
        self.label_168.setText(QCoreApplication.translate("RobotWindow", u"Velocity Vector", None))
        self.pbMoveTestTrackingPoint.setText(QCoreApplication.translate("RobotWindow", u"Move", None))
        self.label_231.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_11.setText(QCoreApplication.translate("RobotWindow", u"Test Tracking Point", None))
        self.label_232.setText(QCoreApplication.translate("RobotWindow", u"(mm)", None))
        self.label_230.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.leMovingValue.setText(QCoreApplication.translate("RobotWindow", u"200", None))
        self.tbCopyTestTrackingPoint.setText("")
        self.label_236.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.gbCameraCalibration_3.setTitle(QCoreApplication.translate("RobotWindow", u"Vector", None))
        self.pbAddVector.setText(QCoreApplication.translate("RobotWindow", u"Save", None))
        self.label_197.setText(QCoreApplication.translate("RobotWindow", u"Value", None))
        self.label_206.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_229.setText(QCoreApplication.translate("RobotWindow", u"Name", None))
        self.pbAnglePoint1.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.pbCalVector.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.label_226.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_228.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.label_208.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.leVectorName.setText(QCoreApplication.translate("RobotWindow", u"#Vector1", None))
        self.label_227.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.pbAnglePoint2.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.label_189.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.gbCameraCalibration_2.setTitle(QCoreApplication.translate("RobotWindow", u"Matrix", None))
        self.label_205.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.label_201.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.leMatrixName.setText(QCoreApplication.translate("RobotWindow", u"#MappingMatrix1", None))
        self.label_203.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.label_165.setText(QCoreApplication.translate("RobotWindow", u"Name", None))
        self.label_166.setText(QCoreApplication.translate("RobotWindow", u"Source", None))
        self.pbCalculateMappingMatrixTool.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.label_202.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_204.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.label_177.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.pbAddMappingMatrix.setText(QCoreApplication.translate("RobotWindow", u"Add Matrix", None))
        self.label_200.setText(QCoreApplication.translate("RobotWindow", u"Destination", None))
        self.lbMatrixDisplay.setText(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>|m11 , m12, m13 |</p><p>|m21, m22, m23 |</p><p>|m31, m32, m33 |</p></body></html>", None))
        self.gbCameraObject_2.setTitle(QCoreApplication.translate("RobotWindow", u"Object", None))
        self.label_136.setText(QCoreApplication.translate("RobotWindow", u"Object List", None))
        self.leObjectListName.setText(QCoreApplication.translate("RobotWindow", u"#Objects", None))
        self.label_137.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_138.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_143.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.pbAddVariablePoint.setText(QCoreApplication.translate("RobotWindow", u"Add Point", None))
        self.gbCameraObject_3.setTitle(QCoreApplication.translate("RobotWindow", u"Point Matrix", None))
        self.label_212.setText(QCoreApplication.translate("RobotWindow", u"Point 3", None))
        self.pbAddPointMatrix.setText(QCoreApplication.translate("RobotWindow", u"Add Matrix", None))
        self.label_217.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.label_207.setText(QCoreApplication.translate("RobotWindow", u"Destination", None))
        self.label_211.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.label_218.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_210.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.lePointMatrixName.setText(QCoreApplication.translate("RobotWindow", u"#PointMatrix1", None))
        self.lbPointMatrixDisplay.setText(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p>|m11 , m12, m13 |</p><p>|m21, m22, m23 |</p><p>|m31, m32, m33 |</p></body></html>", None))
        self.label_219.setText(QCoreApplication.translate("RobotWindow", u"Point 4", None))
        self.label_234.setText(QCoreApplication.translate("RobotWindow", u"Point 3", None))
        self.label_216.setText(QCoreApplication.translate("RobotWindow", u"Name", None))
        self.label_220.setText(QCoreApplication.translate("RobotWindow", u"Point 1", None))
        self.label_235.setText(QCoreApplication.translate("RobotWindow", u"Point 4", None))
        self.label_167.setText(QCoreApplication.translate("RobotWindow", u"Source", None))
        self.pbCalculatePointMatrixTool.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.label_233.setText(QCoreApplication.translate("RobotWindow", u"Point 2", None))
        self.gbCameraObject_4.setTitle(QCoreApplication.translate("RobotWindow", u"Test", None))
        self.label_223.setText(QCoreApplication.translate("RobotWindow", u"multiply", None))
        self.leTestMatrixName.setText(QCoreApplication.translate("RobotWindow", u"#MappingMatrix1", None))
        self.label_214.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.label_215.setText(QCoreApplication.translate("RobotWindow", u"Point", None))
        self.pbCalculateTestPoint.setText(QCoreApplication.translate("RobotWindow", u"Calculate", None))
        self.label_222.setText(QCoreApplication.translate("RobotWindow", u"Matrix", None))
        self.label_221.setText(QCoreApplication.translate("RobotWindow", u"X", None))
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
        self.label_158.setText(QCoreApplication.translate("RobotWindow", u"Selected Robot", None))
#if QT_CONFIG(tooltip)
        self.tbAutoScanRobot.setToolTip(QCoreApplication.translate("RobotWindow", u"Creat New Editor", None))
#endif // QT_CONFIG(tooltip)
        self.tbAutoScanRobot.setText(QCoreApplication.translate("RobotWindow", u"  Auto Scan", None))
        self.pbConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.cbSelectedRobot.setItemText(0, QCoreApplication.translate("RobotWindow", u"robot0", None))
        self.cbSelectedRobot.setItemText(1, QCoreApplication.translate("RobotWindow", u"robot1", None))
        self.cbSelectedRobot.setItemText(2, QCoreApplication.translate("RobotWindow", u"robot2", None))
        self.cbSelectedRobot.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.groupBox.setTitle(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.lbComName.setText(QCoreApplication.translate("RobotWindow", u"NONE", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.lbBaudrate.setText(QCoreApplication.translate("RobotWindow", u"115200", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("RobotWindow", u"Model", None))
        self.cbRobotModel.setItemText(0, QCoreApplication.translate("RobotWindow", u"Delta X 1", None))
        self.cbRobotModel.setItemText(1, QCoreApplication.translate("RobotWindow", u"Delta X 2", None))
        self.cbRobotModel.setItemText(2, QCoreApplication.translate("RobotWindow", u"Delta X S", None))
        self.cbRobotModel.setItemText(3, QCoreApplication.translate("RobotWindow", u"Custom", None))

        self.groupBox_4.setTitle(QCoreApplication.translate("RobotWindow", u"DOF", None))
        self.cbRobotDOF.setItemText(0, QCoreApplication.translate("RobotWindow", u"3 DOF", None))
        self.cbRobotDOF.setItemText(1, QCoreApplication.translate("RobotWindow", u"4 DOF", None))
        self.cbRobotDOF.setItemText(2, QCoreApplication.translate("RobotWindow", u"5 DOF", None))
        self.cbRobotDOF.setItemText(3, QCoreApplication.translate("RobotWindow", u"6 DOF", None))

        self.label_270.setText(QCoreApplication.translate("RobotWindow", u"Position", None))
#if QT_CONFIG(tooltip)
        self.tbDisableRobot.setToolTip(QCoreApplication.translate("RobotWindow", u"Creat New Editor", None))
#endif // QT_CONFIG(tooltip)
        self.tbDisableRobot.setText(QCoreApplication.translate("RobotWindow", u"  Hold", None))
#if QT_CONFIG(tooltip)
        self.tbRequestPosition.setToolTip(QCoreApplication.translate("RobotWindow", u"Creat New Editor", None))
#endif // QT_CONFIG(tooltip)
        self.tbRequestPosition.setText(QCoreApplication.translate("RobotWindow", u"Refresh", None))
        self.pbHome.setText(QCoreApplication.translate("RobotWindow", u"Homing", None))
        self.label_92.setText(QCoreApplication.translate("RobotWindow", u"U", None))
        self.label_90.setText(QCoreApplication.translate("RobotWindow", u"W", None))
        self.label_94.setText(QCoreApplication.translate("RobotWindow", u"V", None))
        self.label_84.setText(QCoreApplication.translate("RobotWindow", u"X", None))
        self.label_88.setText(QCoreApplication.translate("RobotWindow", u"Z", None))
        self.label_86.setText(QCoreApplication.translate("RobotWindow", u"Y", None))
        self.leX.setText("")
        self.label_277.setText(QCoreApplication.translate("RobotWindow", u" (mm) ", None))
        self.label_278.setText(QCoreApplication.translate("RobotWindow", u" (degree) ", None))
        self.robotTitile_4.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Title", None))
        self.label_271.setText(QCoreApplication.translate("RobotWindow", u"Jogging", None))
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
        self.pbLeft.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
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
        self.pbBackward.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
        self.label_275.setText(QCoreApplication.translate("RobotWindow", u"5-axis", None))
#if QT_CONFIG(tooltip)
        self.pbPlusRoll.setToolTip(QCoreApplication.translate("RobotWindow", u"Right (Shift +d)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbPlusRoll.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbPlusRoll.setText(QCoreApplication.translate("RobotWindow", u"W+", None))
#if QT_CONFIG(shortcut)
        self.pbPlusRoll.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+G", None))
#endif // QT_CONFIG(shortcut)
        self.pbPlusRoll.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
        self.label_274.setText(QCoreApplication.translate("RobotWindow", u"6-axis", None))
#if QT_CONFIG(tooltip)
        self.pbSubPitch.setToolTip(QCoreApplication.translate("RobotWindow", u"Left (shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbSubPitch.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbSubPitch.setText(QCoreApplication.translate("RobotWindow", u"V-", None))
#if QT_CONFIG(shortcut)
        self.pbSubPitch.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+U", None))
#endif // QT_CONFIG(shortcut)
        self.pbSubPitch.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
#if QT_CONFIG(tooltip)
        self.pbSubRoll.setToolTip(QCoreApplication.translate("RobotWindow", u"Left (shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbSubRoll.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbSubRoll.setText(QCoreApplication.translate("RobotWindow", u"W-", None))
#if QT_CONFIG(shortcut)
        self.pbSubRoll.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+T", None))
#endif // QT_CONFIG(shortcut)
        self.pbSubRoll.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
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
        self.pbUp.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
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
        self.pbDown.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
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
        self.pbForward.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
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
        self.pbRight.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
#if QT_CONFIG(tooltip)
        self.pbPlusPitch.setToolTip(QCoreApplication.translate("RobotWindow", u"Right (Shift +d)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbPlusPitch.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbPlusPitch.setText(QCoreApplication.translate("RobotWindow", u"V+", None))
#if QT_CONFIG(shortcut)
        self.pbPlusPitch.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+J", None))
#endif // QT_CONFIG(shortcut)
        self.pbPlusPitch.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
#if QT_CONFIG(tooltip)
        self.pbSubYaw.setToolTip(QCoreApplication.translate("RobotWindow", u"Left (shift + w)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbSubYaw.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbSubYaw.setText(QCoreApplication.translate("RobotWindow", u"U-", None))
#if QT_CONFIG(shortcut)
        self.pbSubYaw.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+Y", None))
#endif // QT_CONFIG(shortcut)
        self.pbSubYaw.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
        self.label_276.setText(QCoreApplication.translate("RobotWindow", u"4-axis", None))
#if QT_CONFIG(tooltip)
        self.pbPlusYaw.setToolTip(QCoreApplication.translate("RobotWindow", u"Right (Shift +d)", None))
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        self.pbPlusYaw.setStatusTip("")
#endif // QT_CONFIG(statustip)
        self.pbPlusYaw.setText(QCoreApplication.translate("RobotWindow", u"U+", None))
#if QT_CONFIG(shortcut)
        self.pbPlusYaw.setShortcut(QCoreApplication.translate("RobotWindow", u"Shift+H", None))
#endif // QT_CONFIG(shortcut)
        self.pbPlusYaw.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Jogging", None))
        self.label_33.setText(QCoreApplication.translate("RobotWindow", u"  Step  ", None))
        self.rb01.setText(QCoreApplication.translate("RobotWindow", u"0.1", None))
        self.rb05.setText(QCoreApplication.translate("RobotWindow", u"0.5", None))
        self.rb10.setText(QCoreApplication.translate("RobotWindow", u"1", None))
        self.rb50.setText(QCoreApplication.translate("RobotWindow", u"5", None))
        self.rb100.setText(QCoreApplication.translate("RobotWindow", u"10", None))
        self.rb500.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.rb1000.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.label_273.setText(QCoreApplication.translate("RobotWindow", u" (mm) ", None))
        self.label_272.setText(QCoreApplication.translate("RobotWindow", u"Motion Parameters", None))
        self.leEndSpeed.setText("")
        self.leEndSpeed.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_62.setText(QCoreApplication.translate("RobotWindow", u"S", None))
        self.leAccel.setText("")
        self.leAccel.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.leVelocity.setText("")
        self.leVelocity.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_29.setText(QCoreApplication.translate("RobotWindow", u"F", None))
        self.leStartSpeed.setText("")
        self.leStartSpeed.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_32.setText(QCoreApplication.translate("RobotWindow", u"mm/s2", None))
        self.label_30.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_31.setText(QCoreApplication.translate("RobotWindow", u"A", None))
        self.label_63.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.label_116.setText(QCoreApplication.translate("RobotWindow", u"E", None))
        self.label_117.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.leJerk.setText("")
        self.leJerk.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"None", None))
        self.label_64.setText(QCoreApplication.translate("RobotWindow", u"mm/s3", None))
        self.label_47.setText(QCoreApplication.translate("RobotWindow", u"J", None))
        self.robotTitile_3.setProperty("Func", QCoreApplication.translate("RobotWindow", u"Title", None))
        self.label_279.setText(QCoreApplication.translate("RobotWindow", u"Output", None))
        self.groupBox_9.setTitle(QCoreApplication.translate("RobotWindow", u"Delta X 1 / Delta X 2", None))
        self.pbPump.setText(QCoreApplication.translate("RobotWindow", u"  Vacuum", None))
        self.pbLaser.setText(QCoreApplication.translate("RobotWindow", u"      Laser", None))
        self.label_17.setText(QCoreApplication.translate("RobotWindow", u"min", None))
        self.label_27.setText(QCoreApplication.translate("RobotWindow", u"max", None))
        self.pbGrip.setText(QCoreApplication.translate("RobotWindow", u"Grip", None))
        self.leGripperMin.setText(QCoreApplication.translate("RobotWindow", u"5", None))
        self.leGripperMax.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.lbGripperValue.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.gbOutput.setTitle(QCoreApplication.translate("RobotWindow", u"Delta X S Output", None))
        self.cbD3.setText("")
        self.cbD0.setText("")
        self.label_71.setText(QCoreApplication.translate("RobotWindow", u"D6", None))
        self.label_66.setText(QCoreApplication.translate("RobotWindow", u"D4", None))
        self.cbD6.setText("")
        self.label_53.setText(QCoreApplication.translate("RobotWindow", u"D1", None))
        self.cbD2.setText("")
        self.cbD7.setText("")
        self.label_72.setText(QCoreApplication.translate("RobotWindow", u"D7", None))
        self.cbD1.setText("")
        self.cbD4.setText("")
        self.label_51.setText(QCoreApplication.translate("RobotWindow", u"D0", None))
        self.label_69.setText(QCoreApplication.translate("RobotWindow", u"D5", None))
        self.label_61.setText(QCoreApplication.translate("RobotWindow", u"D3", None))
        self.cbD5.setText("")
        self.label_60.setText(QCoreApplication.translate("RobotWindow", u"D2", None))
        self.label_68.setText(QCoreApplication.translate("RobotWindow", u"Digital", None))
        self.label_67.setText(QCoreApplication.translate("RobotWindow", u"Custom", None))
        self.leDx.setText(QCoreApplication.translate("RobotWindow", u"D0", None))
        self.cbDx.setText("")
        self.leRx.setText(QCoreApplication.translate("RobotWindow", u"R0", None))
        self.cbRx.setText("")
        self.label_280.setText(QCoreApplication.translate("RobotWindow", u"Input", None))
        self.gbInput.setTitle(QCoreApplication.translate("RobotWindow", u"Delta X S Input", None))
        self.pbReadI0.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_70.setText(QCoreApplication.translate("RobotWindow", u"I0", None))
        self.lbI0Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle0.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle0.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI1.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_74.setText(QCoreApplication.translate("RobotWindow", u"I1", None))
        self.lbI1Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle1.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle1.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI2.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_76.setText(QCoreApplication.translate("RobotWindow", u"I2", None))
        self.lbI2Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle2.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle2.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadI3.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_78.setText(QCoreApplication.translate("RobotWindow", u"I3", None))
        self.lbI3Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbToggle3.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbToggle3.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadIx.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.leIx.setText(QCoreApplication.translate("RobotWindow", u"I4", None))
        self.leIx.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"I", None))
        self.lbIxValue.setText(QCoreApplication.translate("RobotWindow", u"null", None))
#if QT_CONFIG(tooltip)
        self.cbTogglex.setToolTip(QCoreApplication.translate("RobotWindow", u"The robot will respond when the value of digital input pin changes", None))
#endif // QT_CONFIG(tooltip)
        self.cbTogglex.setText(QCoreApplication.translate("RobotWindow", u"wait toggle", None))
        self.pbReadA0.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_83.setText(QCoreApplication.translate("RobotWindow", u"A0", None))
        self.lbA0Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.leA0Delay.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"0 ms", None))
        self.pbReadA1.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.label_85.setText(QCoreApplication.translate("RobotWindow", u"A1", None))
        self.lbA1Value.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.leA1Delay.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"0 ms", None))
        self.pbReadAx.setText(QCoreApplication.translate("RobotWindow", u"read", None))
        self.leAx.setText(QCoreApplication.translate("RobotWindow", u"A2", None))
        self.leAx.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"I", None))
        self.lbAxValue.setText(QCoreApplication.translate("RobotWindow", u"null", None))
        self.leAxDelay.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"0 ms", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.tRobot), QCoreApplication.translate("RobotWindow", u"Robot", None))
        self.label.setText(QCoreApplication.translate("RobotWindow", u"Selected Conveyor", None))
        self.checkBox.setText(QCoreApplication.translate("RobotWindow", u"Auto Scan", None))
        self.pbConveyorConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.cbSelectedConveyor.setItemText(0, QCoreApplication.translate("RobotWindow", u"conveyor0", None))
        self.cbSelectedConveyor.setItemText(1, QCoreApplication.translate("RobotWindow", u"conveyor1", None))
        self.cbSelectedConveyor.setItemText(2, QCoreApplication.translate("RobotWindow", u"conveyor2", None))
        self.cbSelectedConveyor.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.groupBox_10.setTitle(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.lbConveyorCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.groupBox_11.setTitle(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.lbBaudrate_3.setText(QCoreApplication.translate("RobotWindow", u"115200", None))
        self.label_8.setText(QCoreApplication.translate("RobotWindow", u"Type", None))
        self.cbConveyorType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Conveyor X", None))
        self.cbConveyorType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Conveyor Hub X", None))
        self.cbConveyorType.setItemText(2, QCoreApplication.translate("RobotWindow", u"Custom", None))

#if QT_CONFIG(tooltip)
        self.leConveyorXPosition.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"32\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">311 \u2013 Set Speed</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI "
                        "Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M311 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Speed in mm/s</span></p><p><br/></p><p><a name=\"33\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFon"
                        "t','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">312 - Set Position</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M312 [&lt;value&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color"
                        ":#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">[&lt;value&gt;]: Position in mm</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.leConveyorXPosition.setText(QCoreApplication.translate("RobotWindow", u"-100", None))
        self.label_12.setText(QCoreApplication.translate("RobotWindow", u"Position", None))
        self.label_52.setText(QCoreApplication.translate("RobotWindow", u"Control Mode", None))
        self.label_57.setText(QCoreApplication.translate("RobotWindow", u"Speed", None))
        self.cbConveyorMode.setItemText(0, QCoreApplication.translate("RobotWindow", u"Manual", None))
        self.cbConveyorMode.setItemText(1, QCoreApplication.translate("RobotWindow", u"UART", None))

#if QT_CONFIG(tooltip)
        self.cbConveyorMode.setToolTip(QCoreApplication.translate("RobotWindow", u"<html><head/><body><p><a name=\"31\"/><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">M</span><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; font-weight:600; color:#212529;\">310 \u2013 Set Mode</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Description: .</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI"
                        " Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Usage: M310 [&lt;index&gt;]</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">Parameters:</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">1: Serial Mode.</span></p><p><span style=\" font-family:'-apple-system','BlinkMacSystemFont','Segoe UI','Roboto','Helvetica Neue','Arial','Noto Sans','sans-serif','Apple Color Emoji','Segoe UI Emoji','Segoe UI Symbol','Noto Color Emoji'; color:#212529; background-color:#ffffff;\">0: Volume Mode.</span></p></body></html>", None))
#endif // QT_CONFIG(tooltip)
        self.cbConveyorValueType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Continuous", None))
        self.cbConveyorValueType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Position", None))

        self.lbUnitOfConveyorMoving.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
        self.lbSpeedOfPositionMode.setText(QCoreApplication.translate("RobotWindow", u"mm/s2", None))
#if QT_CONFIG(tooltip)
        self.leConveyorXSpeed.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.leConveyorXSpeed.setText(QCoreApplication.translate("RobotWindow", u"50", None))
        self.label_46.setText(QCoreApplication.translate("RobotWindow", u"Moving Mode", None))
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
        self.label_9.setText(QCoreApplication.translate("RobotWindow", u"Selected Encoder", None))
        self.checkBox_3.setText(QCoreApplication.translate("RobotWindow", u"Auto Scan", None))
        self.pbConnectEncoder.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.cbSelectedEncoder.setItemText(0, QCoreApplication.translate("RobotWindow", u"encoder0", None))
        self.cbSelectedEncoder.setItemText(1, QCoreApplication.translate("RobotWindow", u"encoder1", None))
        self.cbSelectedEncoder.setItemText(2, QCoreApplication.translate("RobotWindow", u"encoder2", None))
        self.cbSelectedEncoder.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.groupBox_12.setTitle(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.lbEncoderCOMname.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.groupBox_16.setTitle(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.lbBaudrate_5.setText(QCoreApplication.translate("RobotWindow", u"115200", None))
        self.label_124.setText(QCoreApplication.translate("RobotWindow", u"Type", None))
        self.cbEncoderType.setItemText(0, QCoreApplication.translate("RobotWindow", u"Encoder X", None))
        self.cbEncoderType.setItemText(1, QCoreApplication.translate("RobotWindow", u"Sub Encoder", None))
        self.cbEncoderType.setItemText(2, QCoreApplication.translate("RobotWindow", u"Virtual Encoder", None))

        self.cbEncoderActive.setText(QCoreApplication.translate("RobotWindow", u"Active", None))
        self.leEncoderCurrentPosition.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.pbSetEncoderInterval.setText(QCoreApplication.translate("RobotWindow", u"Set", None))
        self.label_129.setText(QCoreApplication.translate("RobotWindow", u"Velocity (mm/s)", None))
        self.leEncoderInterval.setText(QCoreApplication.translate("RobotWindow", u"1000", None))
        self.label_125.setText(QCoreApplication.translate("RobotWindow", u"Timer (ms)", None))
        self.pbResetEncoder.setText(QCoreApplication.translate("RobotWindow", u"Reset", None))
        self.pbSetEncoderVelocity.setText(QCoreApplication.translate("RobotWindow", u"Set", None))
        self.label_130.setText(QCoreApplication.translate("RobotWindow", u"Current Position (mm)", None))
        self.leEncoderVelocity.setText(QCoreApplication.translate("RobotWindow", u"100", None))
        self.pbReadEncoder.setText(QCoreApplication.translate("RobotWindow", u"Read", None))
        self.cbConveyorForVirtualEncoder.setItemText(0, QCoreApplication.translate("RobotWindow", u"conveyor0", None))
        self.cbConveyorForVirtualEncoder.setItemText(1, QCoreApplication.translate("RobotWindow", u"conveyor1", None))
        self.cbConveyorForVirtualEncoder.setItemText(2, QCoreApplication.translate("RobotWindow", u"conveyor2", None))

        self.cbLinkToConveyorX.setText(QCoreApplication.translate("RobotWindow", u"Link to Conveyor X", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.EncoderTab), QCoreApplication.translate("RobotWindow", u"Encoder", None))
        self.label_15.setText(QCoreApplication.translate("RobotWindow", u"Selected Encoder", None))
        self.checkBox_5.setText(QCoreApplication.translate("RobotWindow", u"Auto Scan", None))
        self.pbSlidingConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.cbSelectedSlider.setItemText(0, QCoreApplication.translate("RobotWindow", u"slider0", None))
        self.cbSelectedSlider.setItemText(1, QCoreApplication.translate("RobotWindow", u"slider1", None))
        self.cbSelectedSlider.setItemText(2, QCoreApplication.translate("RobotWindow", u"slider2", None))
        self.cbSelectedSlider.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.groupBox_19.setTitle(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.lbSliderCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.groupBox_20.setTitle(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.lbBaudrate_7.setText(QCoreApplication.translate("RobotWindow", u"115200", None))
        self.label_284.setText(QCoreApplication.translate("RobotWindow", u"Type", None))
        self.cbEncoderType_2.setItemText(0, QCoreApplication.translate("RobotWindow", u"Encoder X", None))
        self.cbEncoderType_2.setItemText(1, QCoreApplication.translate("RobotWindow", u"Sub Encoder", None))
        self.cbEncoderType_2.setItemText(2, QCoreApplication.translate("RobotWindow", u"Virtual Encoder", None))

        self.cbEncoderActive_2.setText(QCoreApplication.translate("RobotWindow", u"Active", None))
        self.label_36.setText(QCoreApplication.translate("RobotWindow", u"Speed", None))
#if QT_CONFIG(tooltip)
        self.pbSlidingHome.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbSlidingHome.setText(QCoreApplication.translate("RobotWindow", u"Home", None))
        self.label_59.setText(QCoreApplication.translate("RobotWindow", u"mm", None))
#if QT_CONFIG(tooltip)
        self.pbSlidingDisable.setToolTip("")
#endif // QT_CONFIG(tooltip)
        self.pbSlidingDisable.setText(QCoreApplication.translate("RobotWindow", u"Disable motors", None))
        self.label_37.setText(QCoreApplication.translate("RobotWindow", u"Position", None))
        self.label_58.setText(QCoreApplication.translate("RobotWindow", u"mm/s", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.SliderTab), QCoreApplication.translate("RobotWindow", u"Slider", None))
        self.label_16.setText(QCoreApplication.translate("RobotWindow", u"Selected Device", None))
        self.checkBox_6.setText(QCoreApplication.translate("RobotWindow", u"Auto Scan", None))
        self.pbExternalControllerConnect.setText(QCoreApplication.translate("RobotWindow", u"Connect", None))
        self.cbSelectedDevice.setItemText(0, QCoreApplication.translate("RobotWindow", u"device0", None))
        self.cbSelectedDevice.setItemText(1, QCoreApplication.translate("RobotWindow", u"device1", None))
        self.cbSelectedDevice.setItemText(2, QCoreApplication.translate("RobotWindow", u"device2", None))
        self.cbSelectedDevice.setItemText(3, QCoreApplication.translate("RobotWindow", u"+", None))

        self.groupBox_21.setTitle(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.lbExternalCOMName.setText(QCoreApplication.translate("RobotWindow", u"COM", None))
        self.groupBox_22.setTitle(QCoreApplication.translate("RobotWindow", u"Baudrate", None))
        self.lbBaudrate_8.setText(QCoreApplication.translate("RobotWindow", u"115200", None))
        self.leTransmitToMCU.setText("")
        self.leTransmitToMCU.setPlaceholderText(QCoreApplication.translate("RobotWindow", u"Transmit to MCU", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.MCUTab), QCoreApplication.translate("RobotWindow", u"External Device", None))
        self.twDevices.setTabText(self.twDevices.indexOf(self.PlusDeviceTab), QCoreApplication.translate("RobotWindow", u"+", None))
    # retranslateUi

