# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'MainWindow.ui'
##
## Created by: Qt User Interface Compiler version 6.4.2
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
from PySide6.QtWidgets import (QApplication, QComboBox, QFrame, QGraphicsView,
    QGridLayout, QGroupBox, QHBoxLayout, QHeaderView,
    QLabel, QLineEdit, QListWidget, QListWidgetItem,
    QMainWindow, QPlainTextEdit, QPushButton, QScrollArea,
    QSizePolicy, QSpacerItem, QStackedWidget, QTabWidget,
    QTextEdit, QToolButton, QTreeView, QTreeWidget,
    QTreeWidgetItem, QVBoxLayout, QWidget)
import resource_rc

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        if not MainWindow.objectName():
            MainWindow.setObjectName(u"MainWindow")
        MainWindow.resize(1200, 700)
        sizePolicy = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(MainWindow.sizePolicy().hasHeightForWidth())
        MainWindow.setSizePolicy(sizePolicy)
        MainWindow.setMinimumSize(QSize(800, 480))
        font = QFont()
        font.setBold(False)
        font.setKerning(True)
        MainWindow.setFont(font)
        icon = QIcon()
        icon.addFile(u":/delta_x_logo_96x96.ico", QSize(), QIcon.Normal, QIcon.Off)
        MainWindow.setWindowIcon(icon)
        MainWindow.setStyleSheet(u"")
        self.actionAdd = QAction(MainWindow)
        self.actionAdd.setObjectName(u"actionAdd")
        self.actionRemove = QAction(MainWindow)
        self.actionRemove.setObjectName(u"actionRemove")
        self.actionAbout = QAction(MainWindow)
        self.actionAbout.setObjectName(u"actionAbout")
        self.actionGcode = QAction(MainWindow)
        self.actionGcode.setObjectName(u"actionGcode")
        self.actionSoftware = QAction(MainWindow)
        self.actionSoftware.setObjectName(u"actionSoftware")
        self.actionExecute_All = QAction(MainWindow)
        self.actionExecute_All.setObjectName(u"actionExecute_All")
        self.actionDelta_X_1 = QAction(MainWindow)
        self.actionDelta_X_1.setObjectName(u"actionDelta_X_1")
        self.actionDelta_X_1.setCheckable(True)
        self.actionDelta_X_1.setChecked(True)
        self.actionExecute = QAction(MainWindow)
        self.actionExecute.setObjectName(u"actionExecute")
        self.actionBaudrate = QAction(MainWindow)
        self.actionBaudrate.setObjectName(u"actionBaudrate")
        self.actionScale = QAction(MainWindow)
        self.actionScale.setObjectName(u"actionScale")
        self.actionG_code_Program = QAction(MainWindow)
        self.actionG_code_Program.setObjectName(u"actionG_code_Program")
        self.actionRobot = QAction(MainWindow)
        self.actionRobot.setObjectName(u"actionRobot")
        self.actionProject = QAction(MainWindow)
        self.actionProject.setObjectName(u"actionProject")
        self.actionG_code_Program_2 = QAction(MainWindow)
        self.actionG_code_Program_2.setObjectName(u"actionG_code_Program_2")
        self.actionRobot_2 = QAction(MainWindow)
        self.actionRobot_2.setObjectName(u"actionRobot_2")
        self.actionProject_2 = QAction(MainWindow)
        self.actionProject_2.setObjectName(u"actionProject_2")
        self.actionNew = QAction(MainWindow)
        self.actionNew.setObjectName(u"actionNew")
        self.centralWidget = QWidget(MainWindow)
        self.centralWidget.setObjectName(u"centralWidget")
        self.centralWidget.setStyleSheet(u"/* ===========================================\n"
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
"}")
        self.horizontalLayout = QHBoxLayout(self.centralWidget)
        self.horizontalLayout.setSpacing(0)
        self.horizontalLayout.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.horizontalLayout.setContentsMargins(0, 0, 0, 0)
        self.stackedWidget = QStackedWidget(self.centralWidget)
        self.stackedWidget.setObjectName(u"stackedWidget")
        self.stackedWidget.setStyleSheet(u"")
        self.page = QWidget()
        self.page.setObjectName(u"page")
        self.page.setStyleSheet(u"#page\n"
"{	\n"
"	background-color: rgb(30, 30, 32);\n"
"}")
        self.horizontalLayout_2 = QHBoxLayout(self.page)
        self.horizontalLayout_2.setSpacing(5)
        self.horizontalLayout_2.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.horizontalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.wgLeftPanel = QWidget(self.page)
        self.wgLeftPanel.setObjectName(u"wgLeftPanel")
        self.wgLeftPanel.setMinimumSize(QSize(80, 0))
        self.wgLeftPanel.setMaximumSize(QSize(80, 16777215))
        self.verticalLayout = QVBoxLayout(self.wgLeftPanel)
        self.verticalLayout.setSpacing(0)
        self.verticalLayout.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalSpacer_5 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer_5)

        self.tbOpenProject = QToolButton(self.wgLeftPanel)
        self.tbOpenProject.setObjectName(u"tbOpenProject")
        sizePolicy1 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Fixed)
        sizePolicy1.setHorizontalStretch(0)
        sizePolicy1.setVerticalStretch(0)
        sizePolicy1.setHeightForWidth(self.tbOpenProject.sizePolicy().hasHeightForWidth())
        self.tbOpenProject.setSizePolicy(sizePolicy1)
        self.tbOpenProject.setMinimumSize(QSize(0, 30))
        icon1 = QIcon()
        icon1.addFile(u":/icon/icons8_folder_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbOpenProject.setIcon(icon1)
        self.tbOpenProject.setIconSize(QSize(32, 32))
        self.tbOpenProject.setAutoRaise(True)

        self.verticalLayout.addWidget(self.tbOpenProject)

        self.tbSaveProject = QToolButton(self.wgLeftPanel)
        self.tbSaveProject.setObjectName(u"tbSaveProject")
        sizePolicy1.setHeightForWidth(self.tbSaveProject.sizePolicy().hasHeightForWidth())
        self.tbSaveProject.setSizePolicy(sizePolicy1)
        self.tbSaveProject.setMinimumSize(QSize(0, 30))
        icon2 = QIcon()
        icon2.addFile(u":/icon/save.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbSaveProject.setIcon(icon2)
        self.tbSaveProject.setIconSize(QSize(32, 32))
        self.tbSaveProject.setAutoRaise(True)

        self.verticalLayout.addWidget(self.tbSaveProject)

        self.verticalSpacer_3 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer_3)

        self.tbHome = QToolButton(self.wgLeftPanel)
        self.tbHome.setObjectName(u"tbHome")
        sizePolicy1.setHeightForWidth(self.tbHome.sizePolicy().hasHeightForWidth())
        self.tbHome.setSizePolicy(sizePolicy1)
        self.tbHome.setMinimumSize(QSize(80, 0))
        self.tbHome.setStyleSheet(u"")
        icon3 = QIcon()
        icon3.addFile(u":/icon/home_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbHome.setIcon(icon3)
        self.tbHome.setCheckable(False)
        self.tbHome.setChecked(False)
        self.tbHome.setPopupMode(QToolButton.DelayedPopup)
        self.tbHome.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbHome.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbHome)

        self.tbProject = QToolButton(self.wgLeftPanel)
        self.tbProject.setObjectName(u"tbProject")
        sizePolicy1.setHeightForWidth(self.tbProject.sizePolicy().hasHeightForWidth())
        self.tbProject.setSizePolicy(sizePolicy1)
        self.tbProject.setMinimumSize(QSize(80, 0))
        icon4 = QIcon()
        icon4.addFile(u":/icon/project_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbProject.setIcon(icon4)
        self.tbProject.setCheckable(False)
        self.tbProject.setChecked(False)
        self.tbProject.setPopupMode(QToolButton.DelayedPopup)
        self.tbProject.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbProject.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbProject)

        self.tbVariable = QToolButton(self.wgLeftPanel)
        self.tbVariable.setObjectName(u"tbVariable")
        sizePolicy1.setHeightForWidth(self.tbVariable.sizePolicy().hasHeightForWidth())
        self.tbVariable.setSizePolicy(sizePolicy1)
        self.tbVariable.setMinimumSize(QSize(80, 0))
        self.tbVariable.setStyleSheet(u"")
        icon5 = QIcon()
        icon5.addFile(u":/icon/variable_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbVariable.setIcon(icon5)
        self.tbVariable.setPopupMode(QToolButton.DelayedPopup)
        self.tbVariable.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbVariable.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbVariable)

        self.tbMarket = QToolButton(self.wgLeftPanel)
        self.tbMarket.setObjectName(u"tbMarket")
        sizePolicy1.setHeightForWidth(self.tbMarket.sizePolicy().hasHeightForWidth())
        self.tbMarket.setSizePolicy(sizePolicy1)
        self.tbMarket.setMinimumSize(QSize(80, 0))
        self.tbMarket.setStyleSheet(u"")
        icon6 = QIcon()
        icon6.addFile(u":/icon/shopping_cart_promotion_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbMarket.setIcon(icon6)
        self.tbMarket.setPopupMode(QToolButton.DelayedPopup)
        self.tbMarket.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbMarket.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbMarket)

        self.tbDocument = QToolButton(self.wgLeftPanel)
        self.tbDocument.setObjectName(u"tbDocument")
        sizePolicy1.setHeightForWidth(self.tbDocument.sizePolicy().hasHeightForWidth())
        self.tbDocument.setSizePolicy(sizePolicy1)
        self.tbDocument.setMinimumSize(QSize(80, 0))
        self.tbDocument.setStyleSheet(u"")
        icon7 = QIcon()
        icon7.addFile(u":/icon/document_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbDocument.setIcon(icon7)
        self.tbDocument.setPopupMode(QToolButton.DelayedPopup)
        self.tbDocument.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbDocument.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbDocument)

        self.tbCommunity = QToolButton(self.wgLeftPanel)
        self.tbCommunity.setObjectName(u"tbCommunity")
        sizePolicy1.setHeightForWidth(self.tbCommunity.sizePolicy().hasHeightForWidth())
        self.tbCommunity.setSizePolicy(sizePolicy1)
        self.tbCommunity.setMinimumSize(QSize(80, 0))
        self.tbCommunity.setStyleSheet(u"")
        icon8 = QIcon()
        icon8.addFile(u":/icon/charity_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbCommunity.setIcon(icon8)
        self.tbCommunity.setPopupMode(QToolButton.DelayedPopup)
        self.tbCommunity.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbCommunity.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbCommunity)

        self.tbAuthority = QToolButton(self.wgLeftPanel)
        self.tbAuthority.setObjectName(u"tbAuthority")
        sizePolicy1.setHeightForWidth(self.tbAuthority.sizePolicy().hasHeightForWidth())
        self.tbAuthority.setSizePolicy(sizePolicy1)
        self.tbAuthority.setMinimumSize(QSize(80, 0))
        self.tbAuthority.setStyleSheet(u"")
        icon9 = QIcon()
        icon9.addFile(u":/icon/account_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbAuthority.setIcon(icon9)
        self.tbAuthority.setPopupMode(QToolButton.DelayedPopup)
        self.tbAuthority.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbAuthority.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbAuthority)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer)

        self.tbSetting = QToolButton(self.wgLeftPanel)
        self.tbSetting.setObjectName(u"tbSetting")
        sizePolicy1.setHeightForWidth(self.tbSetting.sizePolicy().hasHeightForWidth())
        self.tbSetting.setSizePolicy(sizePolicy1)
        self.tbSetting.setMinimumSize(QSize(80, 0))
        self.tbSetting.setStyleSheet(u"")
        icon10 = QIcon()
        icon10.addFile(u":/icon/settings_64px.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbSetting.setIcon(icon10)
        self.tbSetting.setPopupMode(QToolButton.DelayedPopup)
        self.tbSetting.setToolButtonStyle(Qt.ToolButtonTextUnderIcon)
        self.tbSetting.setAutoRaise(False)

        self.verticalLayout.addWidget(self.tbSetting)


        self.horizontalLayout_2.addWidget(self.wgLeftPanel)

        self.verticalLayout_11 = QVBoxLayout()
        self.verticalLayout_11.setSpacing(6)
        self.verticalLayout_11.setObjectName(u"verticalLayout_11")
        self.swPageStack = QStackedWidget(self.page)
        self.swPageStack.setObjectName(u"swPageStack")
        sizePolicy2 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Ignored)
        sizePolicy2.setHorizontalStretch(0)
        sizePolicy2.setVerticalStretch(0)
        sizePolicy2.setHeightForWidth(self.swPageStack.sizePolicy().hasHeightForWidth())
        self.swPageStack.setSizePolicy(sizePolicy2)
        self.swPageStack.setMaximumSize(QSize(16777215, 16777215))
        self.swPageStack.setStyleSheet(u"")
        self.swPageStack.setLineWidth(1)
        self.pVariable = QWidget()
        self.pVariable.setObjectName(u"pVariable")
        self.verticalLayout_4 = QVBoxLayout(self.pVariable)
        self.verticalLayout_4.setSpacing(6)
        self.verticalLayout_4.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_4.setObjectName(u"verticalLayout_4")
        self.fVar = QFrame(self.pVariable)
        self.fVar.setObjectName(u"fVar")
        self.fVar.setMinimumSize(QSize(0, 25))
        self.fVar.setFrameShape(QFrame.StyledPanel)
        self.fVar.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_14 = QHBoxLayout(self.fVar)
        self.horizontalLayout_14.setSpacing(6)
        self.horizontalLayout_14.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_14.setObjectName(u"horizontalLayout_14")
        self.label_12 = QLabel(self.fVar)
        self.label_12.setObjectName(u"label_12")

        self.horizontalLayout_14.addWidget(self.label_12)

        self.leUpdateKey = QLineEdit(self.fVar)
        self.leUpdateKey.setObjectName(u"leUpdateKey")

        self.horizontalLayout_14.addWidget(self.leUpdateKey)

        self.label_13 = QLabel(self.fVar)
        self.label_13.setObjectName(u"label_13")

        self.horizontalLayout_14.addWidget(self.label_13)

        self.leUpdateValue = QLineEdit(self.fVar)
        self.leUpdateValue.setObjectName(u"leUpdateValue")

        self.horizontalLayout_14.addWidget(self.leUpdateValue)

        self.pbUpdateVarDisplay = QPushButton(self.fVar)
        self.pbUpdateVarDisplay.setObjectName(u"pbUpdateVarDisplay")

        self.horizontalLayout_14.addWidget(self.pbUpdateVarDisplay)

        self.pbDeleteSelectedVar = QPushButton(self.fVar)
        self.pbDeleteSelectedVar.setObjectName(u"pbDeleteSelectedVar")

        self.horizontalLayout_14.addWidget(self.pbDeleteSelectedVar)

        self.horizontalSpacer_7 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_14.addItem(self.horizontalSpacer_7)


        self.verticalLayout_4.addWidget(self.fVar)

        self.tvVariables = QTreeView(self.pVariable)
        self.tvVariables.setObjectName(u"tvVariables")

        self.verticalLayout_4.addWidget(self.tvVariables)

        self.swPageStack.addWidget(self.pVariable)
        self.pOperator = QWidget()
        self.pOperator.setObjectName(u"pOperator")
        self.verticalLayout_8 = QVBoxLayout(self.pOperator)
        self.verticalLayout_8.setSpacing(6)
        self.verticalLayout_8.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_8.setObjectName(u"verticalLayout_8")
        self.label_21 = QLabel(self.pOperator)
        self.label_21.setObjectName(u"label_21")
        font1 = QFont()
        font1.setPointSize(12)
        font1.setBold(True)
        self.label_21.setFont(font1)

        self.verticalLayout_8.addWidget(self.label_21)

        self.scrollArea_2 = QScrollArea(self.pOperator)
        self.scrollArea_2.setObjectName(u"scrollArea_2")
        self.scrollArea_2.setWidgetResizable(True)
        self.scrollAreaWidgetContents_2 = QWidget()
        self.scrollAreaWidgetContents_2.setObjectName(u"scrollAreaWidgetContents_2")
        self.scrollAreaWidgetContents_2.setGeometry(QRect(0, 0, 662, 297))
        self.verticalLayout_10 = QVBoxLayout(self.scrollAreaWidgetContents_2)
        self.verticalLayout_10.setSpacing(6)
        self.verticalLayout_10.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_10.setObjectName(u"verticalLayout_10")
        self.lbOperatorTitile = QLabel(self.scrollAreaWidgetContents_2)
        self.lbOperatorTitile.setObjectName(u"lbOperatorTitile")
        font2 = QFont()
        font2.setPointSize(20)
        font2.setBold(True)
        self.lbOperatorTitile.setFont(font2)
        self.lbOperatorTitile.setAlignment(Qt.AlignCenter)

        self.verticalLayout_10.addWidget(self.lbOperatorTitile)

        self.horizontalLayout_8 = QHBoxLayout()
        self.horizontalLayout_8.setSpacing(6)
        self.horizontalLayout_8.setObjectName(u"horizontalLayout_8")
        self.frame_2 = QFrame(self.scrollAreaWidgetContents_2)
        self.frame_2.setObjectName(u"frame_2")
        self.frame_2.setMinimumSize(QSize(0, 100))
        self.frame_2.setFrameShape(QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_9 = QHBoxLayout(self.frame_2)
        self.horizontalLayout_9.setSpacing(6)
        self.horizontalLayout_9.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_9.setObjectName(u"horizontalLayout_9")
        self.frame = QFrame(self.frame_2)
        self.frame.setObjectName(u"frame")
        self.frame.setMinimumSize(QSize(0, 100))
        self.frame.setMaximumSize(QSize(200, 16777215))
        self.frame.setFrameShape(QFrame.StyledPanel)
        self.frame.setFrameShadow(QFrame.Raised)
        self.verticalLayout_9 = QVBoxLayout(self.frame)
        self.verticalLayout_9.setSpacing(50)
        self.verticalLayout_9.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_9.setObjectName(u"verticalLayout_9")
        self.pbStartSystem = QPushButton(self.frame)
        self.pbStartSystem.setObjectName(u"pbStartSystem")
        sizePolicy3 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
        sizePolicy3.setHorizontalStretch(0)
        sizePolicy3.setVerticalStretch(0)
        sizePolicy3.setHeightForWidth(self.pbStartSystem.sizePolicy().hasHeightForWidth())
        self.pbStartSystem.setSizePolicy(sizePolicy3)
        self.pbStartSystem.setMaximumSize(QSize(200, 100))
        self.pbStartSystem.setFont(font2)

        self.verticalLayout_9.addWidget(self.pbStartSystem)

        self.pbStopSystem = QPushButton(self.frame)
        self.pbStopSystem.setObjectName(u"pbStopSystem")
        sizePolicy3.setHeightForWidth(self.pbStopSystem.sizePolicy().hasHeightForWidth())
        self.pbStopSystem.setSizePolicy(sizePolicy3)
        self.pbStopSystem.setMaximumSize(QSize(200, 100))
        self.pbStopSystem.setFont(font2)

        self.verticalLayout_9.addWidget(self.pbStopSystem)

        self.verticalSpacer_4 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_9.addItem(self.verticalSpacer_4)

        self.fOperatorRobotOnOffPanel = QFrame(self.frame)
        self.fOperatorRobotOnOffPanel.setObjectName(u"fOperatorRobotOnOffPanel")
        self.fOperatorRobotOnOffPanel.setMinimumSize(QSize(0, 100))
        self.fOperatorRobotOnOffPanel.setFrameShape(QFrame.StyledPanel)
        self.fOperatorRobotOnOffPanel.setFrameShadow(QFrame.Raised)
        self.layoutOperatorRobotOnOff = QGridLayout(self.fOperatorRobotOnOffPanel)
        self.layoutOperatorRobotOnOff.setSpacing(6)
        self.layoutOperatorRobotOnOff.setContentsMargins(11, 11, 11, 11)
        self.layoutOperatorRobotOnOff.setObjectName(u"layoutOperatorRobotOnOff")

        self.verticalLayout_9.addWidget(self.fOperatorRobotOnOffPanel)


        self.horizontalLayout_9.addWidget(self.frame)

        self.wgOperatorDisplay = QWidget(self.frame_2)
        self.wgOperatorDisplay.setObjectName(u"wgOperatorDisplay")
        self.wgOperatorDisplay.setMinimumSize(QSize(400, 400))
        self.horizontalLayout_11 = QHBoxLayout(self.wgOperatorDisplay)
        self.horizontalLayout_11.setSpacing(6)
        self.horizontalLayout_11.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_11.setObjectName(u"horizontalLayout_11")
        self.gvOperatorViewer = QGraphicsView(self.wgOperatorDisplay)
        self.gvOperatorViewer.setObjectName(u"gvOperatorViewer")
        sizePolicy.setHeightForWidth(self.gvOperatorViewer.sizePolicy().hasHeightForWidth())
        self.gvOperatorViewer.setSizePolicy(sizePolicy)

        self.horizontalLayout_11.addWidget(self.gvOperatorViewer)


        self.horizontalLayout_9.addWidget(self.wgOperatorDisplay)

        self.twOperatorParameter = QTreeWidget(self.frame_2)
        self.twOperatorParameter.setObjectName(u"twOperatorParameter")
        self.twOperatorParameter.setMaximumSize(QSize(200, 16777215))

        self.horizontalLayout_9.addWidget(self.twOperatorParameter)

        self.pbOperatorResetParameter = QPushButton(self.frame_2)
        self.pbOperatorResetParameter.setObjectName(u"pbOperatorResetParameter")
        self.pbOperatorResetParameter.setMaximumSize(QSize(50, 16777215))
        self.pbOperatorResetParameter.setLayoutDirection(Qt.LeftToRight)
        self.pbOperatorResetParameter.setFlat(False)

        self.horizontalLayout_9.addWidget(self.pbOperatorResetParameter)


        self.horizontalLayout_8.addWidget(self.frame_2)


        self.verticalLayout_10.addLayout(self.horizontalLayout_8)

        self.pbSwitchProgramer = QPushButton(self.scrollAreaWidgetContents_2)
        self.pbSwitchProgramer.setObjectName(u"pbSwitchProgramer")
        sizePolicy.setHeightForWidth(self.pbSwitchProgramer.sizePolicy().hasHeightForWidth())
        self.pbSwitchProgramer.setSizePolicy(sizePolicy)
        self.pbSwitchProgramer.setMaximumSize(QSize(200, 50))
        self.pbSwitchProgramer.setFont(font1)

        self.verticalLayout_10.addWidget(self.pbSwitchProgramer)

        self.scrollArea_2.setWidget(self.scrollAreaWidgetContents_2)

        self.verticalLayout_8.addWidget(self.scrollArea_2)

        self.swPageStack.addWidget(self.pOperator)
        self.pHome = QWidget()
        self.pHome.setObjectName(u"pHome")
        self.pHome.setMaximumSize(QSize(16777215, 16777215))
        self.pHome.setStyleSheet(u"")
        self.verticalLayout_3 = QVBoxLayout(self.pHome)
        self.verticalLayout_3.setSpacing(6)
        self.verticalLayout_3.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_3.setObjectName(u"verticalLayout_3")
        self.groupBox_4 = QGroupBox(self.pHome)
        self.groupBox_4.setObjectName(u"groupBox_4")
        font3 = QFont()
        font3.setBold(True)
        self.groupBox_4.setFont(font3)
        self.gridLayout_3 = QGridLayout(self.groupBox_4)
        self.gridLayout_3.setSpacing(6)
        self.gridLayout_3.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.label_2 = QLabel(self.groupBox_4)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout_3.addWidget(self.label_2, 0, 1, 1, 1)

        self.label_3 = QLabel(self.groupBox_4)
        self.label_3.setObjectName(u"label_3")

        self.gridLayout_3.addWidget(self.label_3, 1, 0, 1, 1)

        self.label = QLabel(self.groupBox_4)
        self.label.setObjectName(u"label")

        self.gridLayout_3.addWidget(self.label, 0, 0, 1, 1)

        self.label_4 = QLabel(self.groupBox_4)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout_3.addWidget(self.label_4, 2, 0, 1, 1)

        self.label_5 = QLabel(self.groupBox_4)
        self.label_5.setObjectName(u"label_5")

        self.gridLayout_3.addWidget(self.label_5, 1, 1, 1, 1)

        self.label_6 = QLabel(self.groupBox_4)
        self.label_6.setObjectName(u"label_6")

        self.gridLayout_3.addWidget(self.label_6, 2, 1, 1, 1)


        self.verticalLayout_3.addWidget(self.groupBox_4)

        self.groupBox = QGroupBox(self.pHome)
        self.groupBox.setObjectName(u"groupBox")
        self.groupBox.setFont(font3)
        self.gridLayout = QGridLayout(self.groupBox)
        self.gridLayout.setSpacing(6)
        self.gridLayout.setContentsMargins(11, 11, 11, 11)
        self.gridLayout.setObjectName(u"gridLayout")
        self.pushButton = QPushButton(self.groupBox)
        self.pushButton.setObjectName(u"pushButton")
        self.pushButton.setMinimumSize(QSize(0, 0))

        self.gridLayout.addWidget(self.pushButton, 0, 0, 1, 1)

        self.pushButton_2 = QPushButton(self.groupBox)
        self.pushButton_2.setObjectName(u"pushButton_2")
        self.pushButton_2.setMinimumSize(QSize(0, 0))

        self.gridLayout.addWidget(self.pushButton_2, 0, 1, 1, 1)

        self.pushButton_3 = QPushButton(self.groupBox)
        self.pushButton_3.setObjectName(u"pushButton_3")
        self.pushButton_3.setMinimumSize(QSize(0, 0))

        self.gridLayout.addWidget(self.pushButton_3, 1, 0, 1, 1)

        self.pushButton_4 = QPushButton(self.groupBox)
        self.pushButton_4.setObjectName(u"pushButton_4")
        self.pushButton_4.setMinimumSize(QSize(0, 0))

        self.gridLayout.addWidget(self.pushButton_4, 1, 1, 1, 1)


        self.verticalLayout_3.addWidget(self.groupBox)

        self.groupBox_2 = QGroupBox(self.pHome)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.groupBox_2.setFont(font3)
        self.gridLayout_2 = QGridLayout(self.groupBox_2)
        self.gridLayout_2.setSpacing(6)
        self.gridLayout_2.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.pushButton_6 = QPushButton(self.groupBox_2)
        self.pushButton_6.setObjectName(u"pushButton_6")
        self.pushButton_6.setMinimumSize(QSize(0, 0))

        self.gridLayout_2.addWidget(self.pushButton_6, 0, 0, 1, 1)

        self.pushButton_8 = QPushButton(self.groupBox_2)
        self.pushButton_8.setObjectName(u"pushButton_8")
        self.pushButton_8.setMinimumSize(QSize(0, 0))

        self.gridLayout_2.addWidget(self.pushButton_8, 1, 0, 1, 1)

        self.pushButton_7 = QPushButton(self.groupBox_2)
        self.pushButton_7.setObjectName(u"pushButton_7")
        self.pushButton_7.setMinimumSize(QSize(0, 0))

        self.gridLayout_2.addWidget(self.pushButton_7, 0, 1, 1, 1)

        self.pushButton_9 = QPushButton(self.groupBox_2)
        self.pushButton_9.setObjectName(u"pushButton_9")
        self.pushButton_9.setMinimumSize(QSize(0, 0))

        self.gridLayout_2.addWidget(self.pushButton_9, 1, 1, 1, 1)


        self.verticalLayout_3.addWidget(self.groupBox_2)

        self.groupBox_3 = QGroupBox(self.pHome)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.groupBox_3.setFont(font3)
        self.horizontalLayout_3 = QHBoxLayout(self.groupBox_3)
        self.horizontalLayout_3.setSpacing(6)
        self.horizontalLayout_3.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_3.setObjectName(u"horizontalLayout_3")
        self.plainTextEdit = QPlainTextEdit(self.groupBox_3)
        self.plainTextEdit.setObjectName(u"plainTextEdit")
        self.plainTextEdit.setMaximumSize(QSize(16777215, 70))

        self.horizontalLayout_3.addWidget(self.plainTextEdit)

        self.pushButton_5 = QPushButton(self.groupBox_3)
        self.pushButton_5.setObjectName(u"pushButton_5")

        self.horizontalLayout_3.addWidget(self.pushButton_5)


        self.verticalLayout_3.addWidget(self.groupBox_3)

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_3.addItem(self.verticalSpacer_2)

        self.swPageStack.addWidget(self.pHome)
        self.pMarket = QWidget()
        self.pMarket.setObjectName(u"pMarket")
        self.swPageStack.addWidget(self.pMarket)
        self.pDocument = QWidget()
        self.pDocument.setObjectName(u"pDocument")
        self.swPageStack.addWidget(self.pDocument)
        self.pAuthority = QWidget()
        self.pAuthority.setObjectName(u"pAuthority")
        self.pAuthority.setStyleSheet(u"")
        self.verticalLayout_5 = QVBoxLayout(self.pAuthority)
        self.verticalLayout_5.setSpacing(6)
        self.verticalLayout_5.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_5.setObjectName(u"verticalLayout_5")
        self.swAuthority = QStackedWidget(self.pAuthority)
        self.swAuthority.setObjectName(u"swAuthority")
        self.pProgramer = QWidget()
        self.pProgramer.setObjectName(u"pProgramer")
        self.verticalLayout_6 = QVBoxLayout(self.pProgramer)
        self.verticalLayout_6.setSpacing(0)
        self.verticalLayout_6.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_6.setObjectName(u"verticalLayout_6")
        self.verticalLayout_6.setContentsMargins(0, 0, 0, 0)
        self.scrollArea = QScrollArea(self.pProgramer)
        self.scrollArea.setObjectName(u"scrollArea")
        sizePolicy4 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Expanding)
        sizePolicy4.setHorizontalStretch(0)
        sizePolicy4.setVerticalStretch(0)
        sizePolicy4.setHeightForWidth(self.scrollArea.sizePolicy().hasHeightForWidth())
        self.scrollArea.setSizePolicy(sizePolicy4)
        self.scrollArea.setMinimumSize(QSize(0, 600))
        self.scrollArea.setWidgetResizable(True)
        self.scrollAreaWidgetContents = QWidget()
        self.scrollAreaWidgetContents.setObjectName(u"scrollAreaWidgetContents")
        self.scrollAreaWidgetContents.setGeometry(QRect(0, 0, 593, 700))
        self.scrollAreaWidgetContents.setMinimumSize(QSize(0, 700))
        self.verticalLayout_7 = QVBoxLayout(self.scrollAreaWidgetContents)
        self.verticalLayout_7.setSpacing(6)
        self.verticalLayout_7.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_7.setObjectName(u"verticalLayout_7")
        self.label_7 = QLabel(self.scrollAreaWidgetContents)
        self.label_7.setObjectName(u"label_7")
        self.label_7.setFont(font2)

        self.verticalLayout_7.addWidget(self.label_7)

        self.groupBox_5 = QGroupBox(self.scrollAreaWidgetContents)
        self.groupBox_5.setObjectName(u"groupBox_5")
        sizePolicy5 = QSizePolicy(QSizePolicy.Minimum, QSizePolicy.Expanding)
        sizePolicy5.setHorizontalStretch(0)
        sizePolicy5.setVerticalStretch(0)
        sizePolicy5.setHeightForWidth(self.groupBox_5.sizePolicy().hasHeightForWidth())
        self.groupBox_5.setSizePolicy(sizePolicy5)
        self.groupBox_5.setMinimumSize(QSize(0, 0))
        font4 = QFont()
        font4.setBold(False)
        self.groupBox_5.setFont(font4)
        self.gridLayout_4 = QGridLayout(self.groupBox_5)
        self.gridLayout_4.setSpacing(6)
        self.gridLayout_4.setContentsMargins(11, 11, 11, 11)
        self.gridLayout_4.setObjectName(u"gridLayout_4")
        self.lwOperatorDisplayVariable = QListWidget(self.groupBox_5)
        self.lwOperatorDisplayVariable.setObjectName(u"lwOperatorDisplayVariable")
        sizePolicy.setHeightForWidth(self.lwOperatorDisplayVariable.sizePolicy().hasHeightForWidth())
        self.lwOperatorDisplayVariable.setSizePolicy(sizePolicy)

        self.gridLayout_4.addWidget(self.lwOperatorDisplayVariable, 6, 0, 1, 1)

        self.pbApplyOperator = QPushButton(self.groupBox_5)
        self.pbApplyOperator.setObjectName(u"pbApplyOperator")
        self.pbApplyOperator.setFont(font1)

        self.gridLayout_4.addWidget(self.pbApplyOperator, 8, 0, 1, 1)

        self.horizontalLayout_5 = QHBoxLayout()
        self.horizontalLayout_5.setSpacing(6)
        self.horizontalLayout_5.setObjectName(u"horizontalLayout_5")
        self.label_9 = QLabel(self.groupBox_5)
        self.label_9.setObjectName(u"label_9")
        self.label_9.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_5.addWidget(self.label_9)

        self.pbAddOperatorDisplayWidget = QPushButton(self.groupBox_5)
        self.pbAddOperatorDisplayWidget.setObjectName(u"pbAddOperatorDisplayWidget")

        self.horizontalLayout_5.addWidget(self.pbAddOperatorDisplayWidget)

        self.cbOperatorRobotDisplay = QComboBox(self.groupBox_5)
        self.cbOperatorRobotDisplay.setObjectName(u"cbOperatorRobotDisplay")

        self.horizontalLayout_5.addWidget(self.cbOperatorRobotDisplay)

        self.cbOperatorDisplayWidget = QComboBox(self.groupBox_5)
        self.cbOperatorDisplayWidget.addItem("")
        self.cbOperatorDisplayWidget.setObjectName(u"cbOperatorDisplayWidget")
        self.cbOperatorDisplayWidget.setMinimumSize(QSize(150, 0))

        self.horizontalLayout_5.addWidget(self.cbOperatorDisplayWidget)

        self.horizontalSpacer_4 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_5.addItem(self.horizontalSpacer_4)


        self.gridLayout_4.addLayout(self.horizontalLayout_5, 3, 0, 1, 2)

        self.horizontalSpacer_3 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.gridLayout_4.addItem(self.horizontalSpacer_3, 4, 2, 1, 1)

        self.lwOperatorDisplayWidget = QListWidget(self.groupBox_5)
        self.lwOperatorDisplayWidget.setObjectName(u"lwOperatorDisplayWidget")
        sizePolicy.setHeightForWidth(self.lwOperatorDisplayWidget.sizePolicy().hasHeightForWidth())
        self.lwOperatorDisplayWidget.setSizePolicy(sizePolicy)

        self.gridLayout_4.addWidget(self.lwOperatorDisplayWidget, 4, 0, 1, 1)

        self.horizontalLayout_4 = QHBoxLayout()
        self.horizontalLayout_4.setSpacing(6)
        self.horizontalLayout_4.setObjectName(u"horizontalLayout_4")
        self.label_8 = QLabel(self.groupBox_5)
        self.label_8.setObjectName(u"label_8")
        self.label_8.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_4.addWidget(self.label_8)

        self.cbOperatorProject = QComboBox(self.groupBox_5)
        self.cbOperatorProject.setObjectName(u"cbOperatorProject")

        self.horizontalLayout_4.addWidget(self.cbOperatorProject)

        self.label_16 = QLabel(self.groupBox_5)
        self.label_16.setObjectName(u"label_16")

        self.horizontalLayout_4.addWidget(self.label_16)

        self.leOperatorTitle = QLineEdit(self.groupBox_5)
        self.leOperatorTitle.setObjectName(u"leOperatorTitle")
        self.leOperatorTitle.setMinimumSize(QSize(200, 0))
        self.leOperatorTitle.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_4.addWidget(self.leOperatorTitle)

        self.horizontalSpacer_2 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_4.addItem(self.horizontalSpacer_2)


        self.gridLayout_4.addLayout(self.horizontalLayout_4, 0, 0, 1, 2)

        self.pbDeleteOperatorVar = QPushButton(self.groupBox_5)
        self.pbDeleteOperatorVar.setObjectName(u"pbDeleteOperatorVar")
        self.pbDeleteOperatorVar.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_4.addWidget(self.pbDeleteOperatorVar, 6, 1, 1, 1)

        self.lwOperatorRobotGcodeProgram = QListWidget(self.groupBox_5)
        self.lwOperatorRobotGcodeProgram.setObjectName(u"lwOperatorRobotGcodeProgram")
        sizePolicy.setHeightForWidth(self.lwOperatorRobotGcodeProgram.sizePolicy().hasHeightForWidth())
        self.lwOperatorRobotGcodeProgram.setSizePolicy(sizePolicy)

        self.gridLayout_4.addWidget(self.lwOperatorRobotGcodeProgram, 2, 0, 1, 1)

        self.horizontalLayout_6 = QHBoxLayout()
        self.horizontalLayout_6.setSpacing(6)
        self.horizontalLayout_6.setObjectName(u"horizontalLayout_6")
        self.pbAddVarToOperatorDisplay = QPushButton(self.groupBox_5)
        self.pbAddVarToOperatorDisplay.setObjectName(u"pbAddVarToOperatorDisplay")

        self.horizontalLayout_6.addWidget(self.pbAddVarToOperatorDisplay)

        self.label_10 = QLabel(self.groupBox_5)
        self.label_10.setObjectName(u"label_10")
        self.label_10.setMaximumSize(QSize(16777215, 16777215))

        self.horizontalLayout_6.addWidget(self.label_10)

        self.leOperatorVar = QLineEdit(self.groupBox_5)
        self.leOperatorVar.setObjectName(u"leOperatorVar")
        self.leOperatorVar.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_6.addWidget(self.leOperatorVar)

        self.label_14 = QLabel(self.groupBox_5)
        self.label_14.setObjectName(u"label_14")
        self.label_14.setMaximumSize(QSize(50, 16777215))

        self.horizontalLayout_6.addWidget(self.label_14)

        self.leOperatorVarName = QLineEdit(self.groupBox_5)
        self.leOperatorVarName.setObjectName(u"leOperatorVarName")
        self.leOperatorVarName.setMaximumSize(QSize(100, 16777215))

        self.horizontalLayout_6.addWidget(self.leOperatorVarName)

        self.horizontalSpacer_5 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_6.addItem(self.horizontalSpacer_5)


        self.gridLayout_4.addLayout(self.horizontalLayout_6, 5, 0, 1, 2)

        self.horizontalLayout_7 = QHBoxLayout()
        self.horizontalLayout_7.setSpacing(6)
        self.horizontalLayout_7.setObjectName(u"horizontalLayout_7")
        self.label_15 = QLabel(self.groupBox_5)
        self.label_15.setObjectName(u"label_15")

        self.horizontalLayout_7.addWidget(self.label_15)

        self.leAuthorityPassword = QLineEdit(self.groupBox_5)
        self.leAuthorityPassword.setObjectName(u"leAuthorityPassword")
        self.leAuthorityPassword.setFrame(True)
        self.leAuthorityPassword.setEchoMode(QLineEdit.Password)
        self.leAuthorityPassword.setCursorMoveStyle(Qt.LogicalMoveStyle)
        self.leAuthorityPassword.setClearButtonEnabled(False)

        self.horizontalLayout_7.addWidget(self.leAuthorityPassword)


        self.gridLayout_4.addLayout(self.horizontalLayout_7, 7, 0, 1, 1)

        self.horizontalLayout_12 = QHBoxLayout()
        self.horizontalLayout_12.setSpacing(6)
        self.horizontalLayout_12.setObjectName(u"horizontalLayout_12")
        self.label_11 = QLabel(self.groupBox_5)
        self.label_11.setObjectName(u"label_11")
        self.label_11.setMinimumSize(QSize(100, 0))

        self.horizontalLayout_12.addWidget(self.label_11)

        self.pbAddOperatorGcodeProgram = QPushButton(self.groupBox_5)
        self.pbAddOperatorGcodeProgram.setObjectName(u"pbAddOperatorGcodeProgram")

        self.horizontalLayout_12.addWidget(self.pbAddOperatorGcodeProgram)

        self.cbOperatorRobot = QComboBox(self.groupBox_5)
        self.cbOperatorRobot.setObjectName(u"cbOperatorRobot")

        self.horizontalLayout_12.addWidget(self.cbOperatorRobot)

        self.cbOperatorGcodeProgram = QComboBox(self.groupBox_5)
        self.cbOperatorGcodeProgram.setObjectName(u"cbOperatorGcodeProgram")
        self.cbOperatorGcodeProgram.setMinimumSize(QSize(150, 0))

        self.horizontalLayout_12.addWidget(self.cbOperatorGcodeProgram)

        self.horizontalSpacer_6 = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_12.addItem(self.horizontalSpacer_6)


        self.gridLayout_4.addLayout(self.horizontalLayout_12, 1, 0, 1, 1)

        self.pbDeleteOperatorDisplayWidget = QPushButton(self.groupBox_5)
        self.pbDeleteOperatorDisplayWidget.setObjectName(u"pbDeleteOperatorDisplayWidget")
        self.pbDeleteOperatorDisplayWidget.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_4.addWidget(self.pbDeleteOperatorDisplayWidget, 4, 1, 1, 1)

        self.pbDeleteOperatorGcodeProgram = QPushButton(self.groupBox_5)
        self.pbDeleteOperatorGcodeProgram.setObjectName(u"pbDeleteOperatorGcodeProgram")
        self.pbDeleteOperatorGcodeProgram.setMaximumSize(QSize(50, 16777215))

        self.gridLayout_4.addWidget(self.pbDeleteOperatorGcodeProgram, 2, 1, 1, 1)


        self.verticalLayout_7.addWidget(self.groupBox_5)

        self.scrollArea.setWidget(self.scrollAreaWidgetContents)

        self.verticalLayout_6.addWidget(self.scrollArea)

        self.swAuthority.addWidget(self.pProgramer)

        self.verticalLayout_5.addWidget(self.swAuthority)

        self.swPageStack.addWidget(self.pAuthority)
        self.pCommunity = QWidget()
        self.pCommunity.setObjectName(u"pCommunity")
        self.swPageStack.addWidget(self.pCommunity)
        self.pSetting = QWidget()
        self.pSetting.setObjectName(u"pSetting")
        self.verticalLayout_12 = QVBoxLayout(self.pSetting)
        self.verticalLayout_12.setSpacing(5)
        self.verticalLayout_12.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_12.setObjectName(u"verticalLayout_12")
        self.verticalLayout_12.setContentsMargins(10, 10, 10, 10)
        self.lbSettingsTitle = QLabel(self.pSetting)
        self.lbSettingsTitle.setObjectName(u"lbSettingsTitle")
        font5 = QFont()
        font5.setPointSize(16)
        font5.setBold(True)
        self.lbSettingsTitle.setFont(font5)

        self.verticalLayout_12.addWidget(self.lbSettingsTitle)

        self.frame_3 = QFrame(self.pSetting)
        self.frame_3.setObjectName(u"frame_3")
        self.frame_3.setMinimumSize(QSize(0, 50))
        self.frame_3.setFrameShape(QFrame.StyledPanel)
        self.frame_3.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_13 = QHBoxLayout(self.frame_3)
        self.horizontalLayout_13.setSpacing(6)
        self.horizontalLayout_13.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_13.setObjectName(u"horizontalLayout_13")
        self.pbResetSettings = QPushButton(self.frame_3)
        self.pbResetSettings.setObjectName(u"pbResetSettings")
        self.pbResetSettings.setMinimumSize(QSize(100, 30))

        self.horizontalLayout_13.addWidget(self.pbResetSettings)

        self.pbBackupSettings = QPushButton(self.frame_3)
        self.pbBackupSettings.setObjectName(u"pbBackupSettings")
        self.pbBackupSettings.setMinimumSize(QSize(100, 30))

        self.horizontalLayout_13.addWidget(self.pbBackupSettings)

        self.pbRestoreSettings = QPushButton(self.frame_3)
        self.pbRestoreSettings.setObjectName(u"pbRestoreSettings")
        self.pbRestoreSettings.setMinimumSize(QSize(100, 30))

        self.horizontalLayout_13.addWidget(self.pbRestoreSettings)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_13.addItem(self.horizontalSpacer)

        self.pbSaveSetting = QPushButton(self.frame_3)
        self.pbSaveSetting.setObjectName(u"pbSaveSetting")
        self.pbSaveSetting.setMinimumSize(QSize(120, 30))

        self.horizontalLayout_13.addWidget(self.pbSaveSetting)


        self.verticalLayout_12.addWidget(self.frame_3)

        self.twSettingsCategories = QTabWidget(self.pSetting)
        self.twSettingsCategories.setObjectName(u"twSettingsCategories")
        self.tabGeneral = QWidget()
        self.tabGeneral.setObjectName(u"tabGeneral")
        self.vlGeneral = QVBoxLayout(self.tabGeneral)
        self.vlGeneral.setSpacing(6)
        self.vlGeneral.setContentsMargins(11, 11, 11, 11)
        self.vlGeneral.setObjectName(u"vlGeneral")
        self.saGeneral = QScrollArea(self.tabGeneral)
        self.saGeneral.setObjectName(u"saGeneral")
        self.saGeneral.setWidgetResizable(True)
        self.swGeneral = QWidget()
        self.swGeneral.setObjectName(u"swGeneral")
        self.swGeneral.setGeometry(QRect(0, 0, 65, 18))
        self.vlGeneralContent = QVBoxLayout(self.swGeneral)
        self.vlGeneralContent.setSpacing(6)
        self.vlGeneralContent.setContentsMargins(11, 11, 11, 11)
        self.vlGeneralContent.setObjectName(u"vlGeneralContent")
        self.saGeneral.setWidget(self.swGeneral)

        self.vlGeneral.addWidget(self.saGeneral)

        self.twSettingsCategories.addTab(self.tabGeneral, "")
        self.tabDevice = QWidget()
        self.tabDevice.setObjectName(u"tabDevice")
        self.vlDevice = QVBoxLayout(self.tabDevice)
        self.vlDevice.setSpacing(6)
        self.vlDevice.setContentsMargins(11, 11, 11, 11)
        self.vlDevice.setObjectName(u"vlDevice")
        self.saDevice = QScrollArea(self.tabDevice)
        self.saDevice.setObjectName(u"saDevice")
        self.saDevice.setWidgetResizable(True)
        self.swDevice = QWidget()
        self.swDevice.setObjectName(u"swDevice")
        self.swDevice.setGeometry(QRect(0, 0, 65, 18))
        self.vlDeviceContent = QVBoxLayout(self.swDevice)
        self.vlDeviceContent.setSpacing(6)
        self.vlDeviceContent.setContentsMargins(11, 11, 11, 11)
        self.vlDeviceContent.setObjectName(u"vlDeviceContent")
        self.saDevice.setWidget(self.swDevice)

        self.vlDevice.addWidget(self.saDevice)

        self.twSettingsCategories.addTab(self.tabDevice, "")
        self.tabCamera = QWidget()
        self.tabCamera.setObjectName(u"tabCamera")
        self.vlCamera = QVBoxLayout(self.tabCamera)
        self.vlCamera.setSpacing(6)
        self.vlCamera.setContentsMargins(11, 11, 11, 11)
        self.vlCamera.setObjectName(u"vlCamera")
        self.saCamera = QScrollArea(self.tabCamera)
        self.saCamera.setObjectName(u"saCamera")
        self.saCamera.setWidgetResizable(True)
        self.swCamera = QWidget()
        self.swCamera.setObjectName(u"swCamera")
        self.swCamera.setGeometry(QRect(0, 0, 65, 18))
        self.vlCameraContent = QVBoxLayout(self.swCamera)
        self.vlCameraContent.setSpacing(6)
        self.vlCameraContent.setContentsMargins(11, 11, 11, 11)
        self.vlCameraContent.setObjectName(u"vlCameraContent")
        self.saCamera.setWidget(self.swCamera)

        self.vlCamera.addWidget(self.saCamera)

        self.twSettingsCategories.addTab(self.tabCamera, "")
        self.tabEditor = QWidget()
        self.tabEditor.setObjectName(u"tabEditor")
        self.vlEditor = QVBoxLayout(self.tabEditor)
        self.vlEditor.setSpacing(6)
        self.vlEditor.setContentsMargins(11, 11, 11, 11)
        self.vlEditor.setObjectName(u"vlEditor")
        self.saEditor = QScrollArea(self.tabEditor)
        self.saEditor.setObjectName(u"saEditor")
        self.saEditor.setWidgetResizable(True)
        self.swEditor = QWidget()
        self.swEditor.setObjectName(u"swEditor")
        self.swEditor.setGeometry(QRect(0, 0, 65, 18))
        self.vlEditorContent = QVBoxLayout(self.swEditor)
        self.vlEditorContent.setSpacing(6)
        self.vlEditorContent.setContentsMargins(11, 11, 11, 11)
        self.vlEditorContent.setObjectName(u"vlEditorContent")
        self.saEditor.setWidget(self.swEditor)

        self.vlEditor.addWidget(self.saEditor)

        self.twSettingsCategories.addTab(self.tabEditor, "")
        self.tabAdvanced = QWidget()
        self.tabAdvanced.setObjectName(u"tabAdvanced")
        self.vlAdvanced = QVBoxLayout(self.tabAdvanced)
        self.vlAdvanced.setSpacing(6)
        self.vlAdvanced.setContentsMargins(11, 11, 11, 11)
        self.vlAdvanced.setObjectName(u"vlAdvanced")
        self.saAdvanced = QScrollArea(self.tabAdvanced)
        self.saAdvanced.setObjectName(u"saAdvanced")
        self.saAdvanced.setWidgetResizable(True)
        self.swAdvanced = QWidget()
        self.swAdvanced.setObjectName(u"swAdvanced")
        self.swAdvanced.setGeometry(QRect(0, 0, 1073, 462))
        self.vlAdvancedContent = QVBoxLayout(self.swAdvanced)
        self.vlAdvancedContent.setSpacing(6)
        self.vlAdvancedContent.setContentsMargins(11, 11, 11, 11)
        self.vlAdvancedContent.setObjectName(u"vlAdvancedContent")
        self.saAdvanced.setWidget(self.swAdvanced)

        self.vlAdvanced.addWidget(self.saAdvanced)

        self.twSettingsCategories.addTab(self.tabAdvanced, "")
        self.tabAuthority = QWidget()
        self.tabAuthority.setObjectName(u"tabAuthority")
        self.vlAuthority = QVBoxLayout(self.tabAuthority)
        self.vlAuthority.setSpacing(6)
        self.vlAuthority.setContentsMargins(11, 11, 11, 11)
        self.vlAuthority.setObjectName(u"vlAuthority")
        self.saAuthority = QScrollArea(self.tabAuthority)
        self.saAuthority.setObjectName(u"saAuthority")
        self.saAuthority.setWidgetResizable(True)
        self.swAuthority1 = QWidget()
        self.swAuthority1.setObjectName(u"swAuthority1")
        self.swAuthority1.setGeometry(QRect(0, 0, 65, 18))
        self.vlAuthorityContent = QVBoxLayout(self.swAuthority1)
        self.vlAuthorityContent.setSpacing(6)
        self.vlAuthorityContent.setContentsMargins(11, 11, 11, 11)
        self.vlAuthorityContent.setObjectName(u"vlAuthorityContent")
        self.saAuthority.setWidget(self.swAuthority1)

        self.vlAuthority.addWidget(self.saAuthority)

        self.twSettingsCategories.addTab(self.tabAuthority, "")

        self.verticalLayout_12.addWidget(self.twSettingsCategories)

        self.swPageStack.addWidget(self.pSetting)
        self.pProject = QWidget()
        self.pProject.setObjectName(u"pProject")
        self.verticalLayout_2 = QVBoxLayout(self.pProject)
        self.verticalLayout_2.setSpacing(0)
        self.verticalLayout_2.setContentsMargins(11, 11, 11, 11)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.twProjectManager = QTabWidget(self.pProject)
        self.twProjectManager.setObjectName(u"twProjectManager")
        self.twProjectManager.setEnabled(True)
        self.twProjectManager.setMinimumSize(QSize(0, 0))
        self.twProjectManager.setMaximumSize(QSize(16777215, 16777215))
        font6 = QFont()
        font6.setPointSize(12)
        font6.setBold(False)
        font6.setKerning(True)
        self.twProjectManager.setFont(font6)
        self.twProjectManager.setStyleSheet(u"")
        self.twProjectManager.setIconSize(QSize(32, 32))
        self.twProjectManager.setElideMode(Qt.ElideNone)
        self.twProjectManager.setTabsClosable(True)
        self.twProjectManager.setMovable(False)
        self.tabAddNewButton = QWidget()
        self.tabAddNewButton.setObjectName(u"tabAddNewButton")
        self.tabAddNewButton.setStyleSheet(u"")
        self.twProjectManager.addTab(self.tabAddNewButton, "")

        self.verticalLayout_2.addWidget(self.twProjectManager)

        self.swPageStack.addWidget(self.pProject)

        self.verticalLayout_11.addWidget(self.swPageStack)

        self.fFileMenu = QFrame(self.page)
        self.fFileMenu.setObjectName(u"fFileMenu")
        sizePolicy6 = QSizePolicy(QSizePolicy.Preferred, QSizePolicy.Maximum)
        sizePolicy6.setHorizontalStretch(0)
        sizePolicy6.setVerticalStretch(0)
        sizePolicy6.setHeightForWidth(self.fFileMenu.sizePolicy().hasHeightForWidth())
        self.fFileMenu.setSizePolicy(sizePolicy6)
        self.fFileMenu.setMinimumSize(QSize(0, 40))
        self.fFileMenu.setStyleSheet(u"")
        self.fFileMenu.setFrameShape(QFrame.StyledPanel)
        self.fFileMenu.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_10 = QHBoxLayout(self.fFileMenu)
        self.horizontalLayout_10.setSpacing(5)
        self.horizontalLayout_10.setContentsMargins(11, 11, 11, 11)
        self.horizontalLayout_10.setObjectName(u"horizontalLayout_10")
        self.horizontalLayout_10.setContentsMargins(0, 0, 0, 0)
        self.teLoggingBox = QTextEdit(self.fFileMenu)
        self.teLoggingBox.setObjectName(u"teLoggingBox")
        sizePolicy7 = QSizePolicy(QSizePolicy.Expanding, QSizePolicy.Ignored)
        sizePolicy7.setHorizontalStretch(0)
        sizePolicy7.setVerticalStretch(0)
        sizePolicy7.setHeightForWidth(self.teLoggingBox.sizePolicy().hasHeightForWidth())
        self.teLoggingBox.setSizePolicy(sizePolicy7)
        self.teLoggingBox.setMinimumSize(QSize(0, 0))
        self.teLoggingBox.setMaximumSize(QSize(16777215, 16777215))

        self.horizontalLayout_10.addWidget(self.teLoggingBox)

        self.tbExpandLoggingBox = QToolButton(self.fFileMenu)
        self.tbExpandLoggingBox.setObjectName(u"tbExpandLoggingBox")
        icon11 = QIcon()
        icon11.addFile(u":/icon/Collapse Arrow.png", QSize(), QIcon.Normal, QIcon.Off)
        self.tbExpandLoggingBox.setIcon(icon11)
        self.tbExpandLoggingBox.setCheckable(True)
        self.tbExpandLoggingBox.setAutoRaise(True)

        self.horizontalLayout_10.addWidget(self.tbExpandLoggingBox)


        self.verticalLayout_11.addWidget(self.fFileMenu)


        self.horizontalLayout_2.addLayout(self.verticalLayout_11)

        self.stackedWidget.addWidget(self.page)
        self.pFullTabDisplay = QWidget()
        self.pFullTabDisplay.setObjectName(u"pFullTabDisplay")
        self.layoutFullTabDisplay = QVBoxLayout(self.pFullTabDisplay)
        self.layoutFullTabDisplay.setSpacing(0)
        self.layoutFullTabDisplay.setContentsMargins(11, 11, 11, 11)
        self.layoutFullTabDisplay.setObjectName(u"layoutFullTabDisplay")
        self.layoutFullTabDisplay.setContentsMargins(0, 0, 0, 0)
        self.stackedWidget.addWidget(self.pFullTabDisplay)

        self.horizontalLayout.addWidget(self.stackedWidget)

        MainWindow.setCentralWidget(self.centralWidget)

        self.retranslateUi(MainWindow)

        self.stackedWidget.setCurrentIndex(0)
        self.swPageStack.setCurrentIndex(0)
        self.swAuthority.setCurrentIndex(0)
        self.twSettingsCategories.setCurrentIndex(4)
        self.twProjectManager.setCurrentIndex(0)


        QMetaObject.connectSlotsByName(MainWindow)
    # setupUi

    def retranslateUi(self, MainWindow):
        MainWindow.setWindowTitle(QCoreApplication.translate("MainWindow", u"Delta X Software - Version 1.3.0", None))
        self.actionAdd.setText(QCoreApplication.translate("MainWindow", u"Add New", None))
        self.actionRemove.setText(QCoreApplication.translate("MainWindow", u"Remove", None))
        self.actionAbout.setText(QCoreApplication.translate("MainWindow", u"About", None))
        self.actionGcode.setText(QCoreApplication.translate("MainWindow", u"Gcode", None))
        self.actionSoftware.setText(QCoreApplication.translate("MainWindow", u"Software", None))
        self.actionExecute_All.setText(QCoreApplication.translate("MainWindow", u"Execute All", None))
        self.actionDelta_X_1.setText(QCoreApplication.translate("MainWindow", u"Delta X 1", None))
        self.actionExecute.setText(QCoreApplication.translate("MainWindow", u"Execute", None))
        self.actionBaudrate.setText(QCoreApplication.translate("MainWindow", u"Baudrate", None))
        self.actionScale.setText(QCoreApplication.translate("MainWindow", u"Scale", None))
        self.actionG_code_Program.setText(QCoreApplication.translate("MainWindow", u"G-code Program", None))
        self.actionRobot.setText(QCoreApplication.translate("MainWindow", u"Robot", None))
        self.actionProject.setText(QCoreApplication.translate("MainWindow", u"Project", None))
        self.actionG_code_Program_2.setText(QCoreApplication.translate("MainWindow", u"G-code Program", None))
        self.actionRobot_2.setText(QCoreApplication.translate("MainWindow", u"Robot", None))
        self.actionProject_2.setText(QCoreApplication.translate("MainWindow", u"Project", None))
        self.actionNew.setText(QCoreApplication.translate("MainWindow", u"New", None))
        self.tbOpenProject.setText(QCoreApplication.translate("MainWindow", u"...", None))
        self.tbSaveProject.setText(QCoreApplication.translate("MainWindow", u"...", None))
        self.tbHome.setText(QCoreApplication.translate("MainWindow", u"Home", None))
        self.tbProject.setText(QCoreApplication.translate("MainWindow", u"Project", None))
        self.tbVariable.setText(QCoreApplication.translate("MainWindow", u"Variable", None))
        self.tbMarket.setText(QCoreApplication.translate("MainWindow", u"Market", None))
        self.tbDocument.setText(QCoreApplication.translate("MainWindow", u"Document", None))
        self.tbCommunity.setText(QCoreApplication.translate("MainWindow", u"Community", None))
        self.tbAuthority.setText(QCoreApplication.translate("MainWindow", u"Admin", None))
        self.tbSetting.setText(QCoreApplication.translate("MainWindow", u"Setting", None))
        self.label_12.setText(QCoreApplication.translate("MainWindow", u"Key", None))
        self.label_13.setText(QCoreApplication.translate("MainWindow", u"Value", None))
        self.pbUpdateVarDisplay.setText(QCoreApplication.translate("MainWindow", u"Update", None))
        self.pbDeleteSelectedVar.setText(QCoreApplication.translate("MainWindow", u"Delete", None))
        self.label_21.setText(QCoreApplication.translate("MainWindow", u"Operator", None))
        self.lbOperatorTitile.setText(QCoreApplication.translate("MainWindow", u"Delta Robot System", None))
        self.pbStartSystem.setText(QCoreApplication.translate("MainWindow", u"Start", None))
        self.pbStopSystem.setText(QCoreApplication.translate("MainWindow", u"Stop", None))
        ___qtreewidgetitem = self.twOperatorParameter.headerItem()
        ___qtreewidgetitem.setText(1, QCoreApplication.translate("MainWindow", u"Value", None));
        ___qtreewidgetitem.setText(0, QCoreApplication.translate("MainWindow", u"Name", None));
        self.pbOperatorResetParameter.setText(QCoreApplication.translate("MainWindow", u"Reset", None))
        self.pbSwitchProgramer.setText(QCoreApplication.translate("MainWindow", u"> Programer", None))
        self.groupBox_4.setTitle(QCoreApplication.translate("MainWindow", u"Project", None))
        self.label_2.setText(QCoreApplication.translate("MainWindow", u"project 1", None))
        self.label_3.setText(QCoreApplication.translate("MainWindow", u"Delta X S - Pick & Place - Conveyor + Vision", None))
        self.label.setText(QCoreApplication.translate("MainWindow", u"New Project", None))
        self.label_4.setText(QCoreApplication.translate("MainWindow", u"Delta X 2 - Pick & Place", None))
        self.label_5.setText(QCoreApplication.translate("MainWindow", u"Delta X 2 - Object Sorting - Vision", None))
        self.label_6.setText(QCoreApplication.translate("MainWindow", u"3D printing", None))
        self.groupBox.setTitle(QCoreApplication.translate("MainWindow", u"Instruction Manual", None))
        self.pushButton.setText(QCoreApplication.translate("MainWindow", u"Software User Manual", None))
        self.pushButton_2.setText(QCoreApplication.translate("MainWindow", u"G-code Reference", None))
        self.pushButton_3.setText(QCoreApplication.translate("MainWindow", u"Program Syntax", None))
        self.pushButton_4.setText(QCoreApplication.translate("MainWindow", u"Robot Manual", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("MainWindow", u"Application Case", None))
        self.pushButton_6.setText(QCoreApplication.translate("MainWindow", u"Simple Pick and Place", None))
        self.pushButton_8.setText(QCoreApplication.translate("MainWindow", u"Pick and Place with conveyor and vision", None))
        self.pushButton_7.setText(QCoreApplication.translate("MainWindow", u"Sorting with camera", None))
        self.pushButton_9.setText(QCoreApplication.translate("MainWindow", u"3D Printing", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("MainWindow", u"Feedback", None))
        self.pushButton_5.setText(QCoreApplication.translate("MainWindow", u"Submit", None))
        self.label_7.setText(QCoreApplication.translate("MainWindow", u"Administrator", None))
        self.groupBox_5.setTitle(QCoreApplication.translate("MainWindow", u"Operator Setting", None))
        self.pbApplyOperator.setText(QCoreApplication.translate("MainWindow", u"Operator", None))
        self.label_9.setText(QCoreApplication.translate("MainWindow", u"Display", None))
        self.pbAddOperatorDisplayWidget.setText(QCoreApplication.translate("MainWindow", u"Add", None))
        self.cbOperatorDisplayWidget.setItemText(0, QCoreApplication.translate("MainWindow", u"CameraWindow", None))

        self.label_8.setText(QCoreApplication.translate("MainWindow", u"Project", None))
        self.label_16.setText(QCoreApplication.translate("MainWindow", u"Title", None))
        self.leOperatorTitle.setText(QCoreApplication.translate("MainWindow", u"Delta Robot System", None))
        self.pbDeleteOperatorVar.setText(QCoreApplication.translate("MainWindow", u"x", None))
        self.pbAddVarToOperatorDisplay.setText(QCoreApplication.translate("MainWindow", u"Add", None))
        self.label_10.setText(QCoreApplication.translate("MainWindow", u"Variable", None))
#if QT_CONFIG(tooltip)
        self.leOperatorVar.setToolTip("")
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(whatsthis)
        self.leOperatorVar.setWhatsThis("")
#endif // QT_CONFIG(whatsthis)
        self.leOperatorVar.setText("")
        self.leOperatorVar.setPlaceholderText(QCoreApplication.translate("MainWindow", u"#var", None))
        self.label_14.setText(QCoreApplication.translate("MainWindow", u"Name", None))
        self.leOperatorVarName.setText("")
        self.leOperatorVarName.setPlaceholderText(QCoreApplication.translate("MainWindow", u"Name", None))
        self.label_15.setText(QCoreApplication.translate("MainWindow", u"Password", None))
        self.leAuthorityPassword.setText(QCoreApplication.translate("MainWindow", u"1234", None))
        self.label_11.setText(QCoreApplication.translate("MainWindow", u"Program", None))
        self.pbAddOperatorGcodeProgram.setText(QCoreApplication.translate("MainWindow", u"Add", None))
        self.pbDeleteOperatorDisplayWidget.setText(QCoreApplication.translate("MainWindow", u"x", None))
        self.pbDeleteOperatorGcodeProgram.setText(QCoreApplication.translate("MainWindow", u"x", None))
        self.lbSettingsTitle.setText(QCoreApplication.translate("MainWindow", u"Settings", None))
        self.pbResetSettings.setText(QCoreApplication.translate("MainWindow", u"Reset to Defaults", None))
        self.pbBackupSettings.setText(QCoreApplication.translate("MainWindow", u"Backup Settings", None))
        self.pbRestoreSettings.setText(QCoreApplication.translate("MainWindow", u"Restore Settings", None))
        self.pbSaveSetting.setText(QCoreApplication.translate("MainWindow", u"Save Settings", None))
        self.twSettingsCategories.setTabText(self.twSettingsCategories.indexOf(self.tabGeneral), QCoreApplication.translate("MainWindow", u"General", None))
        self.twSettingsCategories.setTabText(self.twSettingsCategories.indexOf(self.tabDevice), QCoreApplication.translate("MainWindow", u"Device", None))
        self.twSettingsCategories.setTabText(self.twSettingsCategories.indexOf(self.tabCamera), QCoreApplication.translate("MainWindow", u"Camera", None))
        self.twSettingsCategories.setTabText(self.twSettingsCategories.indexOf(self.tabEditor), QCoreApplication.translate("MainWindow", u"Editor", None))
        self.twSettingsCategories.setTabText(self.twSettingsCategories.indexOf(self.tabAdvanced), QCoreApplication.translate("MainWindow", u"Advanced", None))
        self.twSettingsCategories.setTabText(self.twSettingsCategories.indexOf(self.tabAuthority), QCoreApplication.translate("MainWindow", u"Authority", None))
        self.twProjectManager.setTabText(self.twProjectManager.indexOf(self.tabAddNewButton), QCoreApplication.translate("MainWindow", u"+", None))
        self.teLoggingBox.setHtml(QCoreApplication.translate("MainWindow", u"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'MS Shell Dlg 2'; font-size:7.8pt;\"><br /></p></body></html>", None))
        self.tbExpandLoggingBox.setText("")
    # retranslateUi

