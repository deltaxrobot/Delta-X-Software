# -*- coding: utf-8 -*-

################################################################################
## Form generated from reading UI file 'FilterWindow.ui'
##
## Created by: Qt User Interface Compiler version 6.4.1
##
## WARNING! All changes made in this file will be lost when recompiling UI file!
################################################################################

from PySide6.QtCore import (QCoreApplication, QDate, QDateTime, QLocale,
    QMetaObject, QObject, QPoint, QRect,
    QSize, QTime, QUrl, Qt)
from PySide6.QtGui import (QBrush, QColor, QConicalGradient, QCursor,
    QFont, QFontDatabase, QGradient, QIcon,
    QImage, QKeySequence, QLinearGradient, QPainter,
    QPalette, QPixmap, QRadialGradient, QTransform)
from PySide6.QtWidgets import (QApplication, QCheckBox, QComboBox, QDialog,
    QFrame, QGridLayout, QGroupBox, QHBoxLayout,
    QLabel, QSizePolicy, QSlider, QSpacerItem,
    QVBoxLayout, QWidget)

class Ui_FilterWindow(object):
    def setupUi(self, FilterWindow):
        if not FilterWindow.objectName():
            FilterWindow.setObjectName(u"FilterWindow")
        FilterWindow.resize(838, 565)
        self.horizontalLayout = QHBoxLayout(FilterWindow)
        self.horizontalLayout.setObjectName(u"horizontalLayout")
        self.frame = QFrame(FilterWindow)
        self.frame.setObjectName(u"frame")
        self.frame.setMaximumSize(QSize(400, 16777215))
        self.verticalLayout = QVBoxLayout(self.frame)
        self.verticalLayout.setSpacing(20)
        self.verticalLayout.setObjectName(u"verticalLayout")
        self.frame_2 = QFrame(self.frame)
        self.frame_2.setObjectName(u"frame_2")
        self.frame_2.setMinimumSize(QSize(0, 50))
        self.frame_2.setFrameShape(QFrame.StyledPanel)
        self.frame_2.setFrameShadow(QFrame.Raised)
        self.horizontalLayout_2 = QHBoxLayout(self.frame_2)
        self.horizontalLayout_2.setObjectName(u"horizontalLayout_2")
        self.label_7 = QLabel(self.frame_2)
        self.label_7.setObjectName(u"label_7")

        self.horizontalLayout_2.addWidget(self.label_7)

        self.cbObjectType = QComboBox(self.frame_2)
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.addItem("")
        self.cbObjectType.setObjectName(u"cbObjectType")

        self.horizontalLayout_2.addWidget(self.cbObjectType)

        self.horizontalSpacer = QSpacerItem(40, 20, QSizePolicy.Expanding, QSizePolicy.Minimum)

        self.horizontalLayout_2.addItem(self.horizontalSpacer)


        self.verticalLayout.addWidget(self.frame_2)

        self.groupBox = QGroupBox(self.frame)
        self.groupBox.setObjectName(u"groupBox")
        font = QFont()
        font.setBold(False)
        self.groupBox.setFont(font)
        self.gridLayout = QGridLayout(self.groupBox)
        self.gridLayout.setObjectName(u"gridLayout")
        self.label_2 = QLabel(self.groupBox)
        self.label_2.setObjectName(u"label_2")

        self.gridLayout.addWidget(self.label_2, 2, 0, 1, 1)

        self.label_4 = QLabel(self.groupBox)
        self.label_4.setObjectName(u"label_4")

        self.gridLayout.addWidget(self.label_4, 4, 0, 1, 1)

        self.hsminH = QSlider(self.groupBox)
        self.hsminH.setObjectName(u"hsminH")
        self.hsminH.setMaximum(255)
        self.hsminH.setValue(100)
        self.hsminH.setOrientation(Qt.Horizontal)

        self.gridLayout.addWidget(self.hsminH, 0, 1, 1, 1)

        self.hsmaxS = QSlider(self.groupBox)
        self.hsmaxS.setObjectName(u"hsmaxS")
        self.hsmaxS.setMaximum(255)
        self.hsmaxS.setValue(255)
        self.hsmaxS.setOrientation(Qt.Horizontal)

        self.gridLayout.addWidget(self.hsmaxS, 4, 1, 1, 1)

        self.label_5 = QLabel(self.groupBox)
        self.label_5.setObjectName(u"label_5")

        self.gridLayout.addWidget(self.label_5, 5, 0, 1, 1)

        self.hsminS = QSlider(self.groupBox)
        self.hsminS.setObjectName(u"hsminS")
        self.hsminS.setMaximum(255)
        self.hsminS.setValue(0)
        self.hsminS.setOrientation(Qt.Horizontal)

        self.gridLayout.addWidget(self.hsminS, 3, 1, 1, 1)

        self.hsmaxV = QSlider(self.groupBox)
        self.hsmaxV.setObjectName(u"hsmaxV")
        self.hsmaxV.setMaximum(255)
        self.hsmaxV.setValue(255)
        self.hsmaxV.setOrientation(Qt.Horizontal)

        self.gridLayout.addWidget(self.hsmaxV, 6, 1, 1, 1)

        self.lbmaxV = QLabel(self.groupBox)
        self.lbmaxV.setObjectName(u"lbmaxV")

        self.gridLayout.addWidget(self.lbmaxV, 6, 2, 1, 1)

        self.label_3 = QLabel(self.groupBox)
        self.label_3.setObjectName(u"label_3")

        self.gridLayout.addWidget(self.label_3, 3, 0, 1, 1)

        self.lbminS = QLabel(self.groupBox)
        self.lbminS.setObjectName(u"lbminS")

        self.gridLayout.addWidget(self.lbminS, 3, 2, 1, 1)

        self.label_6 = QLabel(self.groupBox)
        self.label_6.setObjectName(u"label_6")

        self.gridLayout.addWidget(self.label_6, 6, 0, 1, 1)

        self.lbminV = QLabel(self.groupBox)
        self.lbminV.setObjectName(u"lbminV")

        self.gridLayout.addWidget(self.lbminV, 5, 2, 1, 1)

        self.lbmaxS = QLabel(self.groupBox)
        self.lbmaxS.setObjectName(u"lbmaxS")

        self.gridLayout.addWidget(self.lbmaxS, 4, 2, 1, 1)

        self.hsminV = QSlider(self.groupBox)
        self.hsminV.setObjectName(u"hsminV")
        self.hsminV.setMaximum(255)
        self.hsminV.setValue(0)
        self.hsminV.setOrientation(Qt.Horizontal)

        self.gridLayout.addWidget(self.hsminV, 5, 1, 1, 1)

        self.label = QLabel(self.groupBox)
        self.label.setObjectName(u"label")

        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)

        self.hsmaxH = QSlider(self.groupBox)
        self.hsmaxH.setObjectName(u"hsmaxH")
        self.hsmaxH.setMaximum(255)
        self.hsmaxH.setValue(150)
        self.hsmaxH.setOrientation(Qt.Horizontal)

        self.gridLayout.addWidget(self.hsmaxH, 2, 1, 1, 1)

        self.lbmaxH = QLabel(self.groupBox)
        self.lbmaxH.setObjectName(u"lbmaxH")

        self.gridLayout.addWidget(self.lbmaxH, 2, 2, 1, 1)

        self.lbminH = QLabel(self.groupBox)
        self.lbminH.setObjectName(u"lbminH")

        self.gridLayout.addWidget(self.lbminH, 0, 2, 1, 1)


        self.verticalLayout.addWidget(self.groupBox)

        self.groupBox_2 = QGroupBox(self.frame)
        self.groupBox_2.setObjectName(u"groupBox_2")
        self.groupBox_2.setFont(font)
        self.gridLayout_2 = QGridLayout(self.groupBox_2)
        self.gridLayout_2.setObjectName(u"gridLayout_2")
        self.lbThreshold = QLabel(self.groupBox_2)
        self.lbThreshold.setObjectName(u"lbThreshold")

        self.gridLayout_2.addWidget(self.lbThreshold, 0, 1, 1, 1)

        self.hsThreshold = QSlider(self.groupBox_2)
        self.hsThreshold.setObjectName(u"hsThreshold")
        self.hsThreshold.setMaximum(255)
        self.hsThreshold.setValue(150)
        self.hsThreshold.setOrientation(Qt.Horizontal)

        self.gridLayout_2.addWidget(self.hsThreshold, 0, 0, 1, 1)


        self.verticalLayout.addWidget(self.groupBox_2)

        self.groupBox_3 = QGroupBox(self.frame)
        self.groupBox_3.setObjectName(u"groupBox_3")
        self.groupBox_3.setFont(font)
        self.gridLayout_3 = QGridLayout(self.groupBox_3)
        self.gridLayout_3.setObjectName(u"gridLayout_3")
        self.lbBlurSize = QLabel(self.groupBox_3)
        self.lbBlurSize.setObjectName(u"lbBlurSize")

        self.gridLayout_3.addWidget(self.lbBlurSize, 0, 1, 1, 1)

        self.hsBlurSize = QSlider(self.groupBox_3)
        self.hsBlurSize.setObjectName(u"hsBlurSize")
        self.hsBlurSize.setMinimum(1)
        self.hsBlurSize.setMaximum(51)
        self.hsBlurSize.setSingleStep(2)
        self.hsBlurSize.setValue(1)
        self.hsBlurSize.setOrientation(Qt.Horizontal)

        self.gridLayout_3.addWidget(self.hsBlurSize, 0, 0, 1, 1)


        self.verticalLayout.addWidget(self.groupBox_3)

        self.verticalSpacer = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout.addItem(self.verticalSpacer)


        self.horizontalLayout.addWidget(self.frame)

        self.frame1 = QFrame(FilterWindow)
        self.frame1.setObjectName(u"frame1")
        self.verticalLayout_2 = QVBoxLayout(self.frame1)
        self.verticalLayout_2.setObjectName(u"verticalLayout_2")
        self.cbInvert = QCheckBox(self.frame1)
        self.cbInvert.setObjectName(u"cbInvert")

        self.verticalLayout_2.addWidget(self.cbInvert)

        self.lbOriginImage = QLabel(self.frame1)
        self.lbOriginImage.setObjectName(u"lbOriginImage")
        self.lbOriginImage.setMinimumSize(QSize(320, 240))
        self.lbOriginImage.setMaximumSize(QSize(400, 300))
        self.lbOriginImage.setStyleSheet(u"background-color:rgb(226, 226, 226)")
        self.lbOriginImage.setScaledContents(False)

        self.verticalLayout_2.addWidget(self.lbOriginImage)

        self.lbProcessImage = QLabel(self.frame1)
        self.lbProcessImage.setObjectName(u"lbProcessImage")
        self.lbProcessImage.setMinimumSize(QSize(320, 240))
        self.lbProcessImage.setMaximumSize(QSize(400, 300))
        self.lbProcessImage.setStyleSheet(u"background-color:rgb(226, 226, 226)")
        self.lbProcessImage.setScaledContents(False)

        self.verticalLayout_2.addWidget(self.lbProcessImage)

        self.verticalSpacer_2 = QSpacerItem(20, 40, QSizePolicy.Minimum, QSizePolicy.Expanding)

        self.verticalLayout_2.addItem(self.verticalSpacer_2)


        self.horizontalLayout.addWidget(self.frame1)


        self.retranslateUi(FilterWindow)

        QMetaObject.connectSlotsByName(FilterWindow)
    # setupUi

    def retranslateUi(self, FilterWindow):
        FilterWindow.setWindowTitle(QCoreApplication.translate("FilterWindow", u"Filter Window", None))
        self.label_7.setText(QCoreApplication.translate("FilterWindow", u"Object Type", None))
        self.cbObjectType.setItemText(0, QCoreApplication.translate("FilterWindow", u"0", None))
        self.cbObjectType.setItemText(1, QCoreApplication.translate("FilterWindow", u"1", None))
        self.cbObjectType.setItemText(2, QCoreApplication.translate("FilterWindow", u"2", None))
        self.cbObjectType.setItemText(3, QCoreApplication.translate("FilterWindow", u"3", None))
        self.cbObjectType.setItemText(4, QCoreApplication.translate("FilterWindow", u"4", None))
        self.cbObjectType.setItemText(5, QCoreApplication.translate("FilterWindow", u"5", None))
        self.cbObjectType.setItemText(6, QCoreApplication.translate("FilterWindow", u"6", None))
        self.cbObjectType.setItemText(7, QCoreApplication.translate("FilterWindow", u"7", None))
        self.cbObjectType.setItemText(8, QCoreApplication.translate("FilterWindow", u"8", None))
        self.cbObjectType.setItemText(9, QCoreApplication.translate("FilterWindow", u"9", None))
        self.cbObjectType.setItemText(10, QCoreApplication.translate("FilterWindow", u"10", None))
        self.cbObjectType.setItemText(11, QCoreApplication.translate("FilterWindow", u"11", None))
        self.cbObjectType.setItemText(12, QCoreApplication.translate("FilterWindow", u"12", None))
        self.cbObjectType.setItemText(13, QCoreApplication.translate("FilterWindow", u"13", None))
        self.cbObjectType.setItemText(14, QCoreApplication.translate("FilterWindow", u"14", None))
        self.cbObjectType.setItemText(15, QCoreApplication.translate("FilterWindow", u"15", None))
        self.cbObjectType.setItemText(16, QCoreApplication.translate("FilterWindow", u"16", None))
        self.cbObjectType.setItemText(17, QCoreApplication.translate("FilterWindow", u"17", None))
        self.cbObjectType.setItemText(18, QCoreApplication.translate("FilterWindow", u"18", None))
        self.cbObjectType.setItemText(19, QCoreApplication.translate("FilterWindow", u"19", None))
        self.cbObjectType.setItemText(20, QCoreApplication.translate("FilterWindow", u"20", None))
        self.cbObjectType.setItemText(21, QCoreApplication.translate("FilterWindow", u"21", None))
        self.cbObjectType.setItemText(22, QCoreApplication.translate("FilterWindow", u"22", None))
        self.cbObjectType.setItemText(23, QCoreApplication.translate("FilterWindow", u"23", None))
        self.cbObjectType.setItemText(24, QCoreApplication.translate("FilterWindow", u"24", None))
        self.cbObjectType.setItemText(25, QCoreApplication.translate("FilterWindow", u"25", None))
        self.cbObjectType.setItemText(26, QCoreApplication.translate("FilterWindow", u"26", None))
        self.cbObjectType.setItemText(27, QCoreApplication.translate("FilterWindow", u"27", None))
        self.cbObjectType.setItemText(28, QCoreApplication.translate("FilterWindow", u"28", None))
        self.cbObjectType.setItemText(29, QCoreApplication.translate("FilterWindow", u"29", None))
        self.cbObjectType.setItemText(30, QCoreApplication.translate("FilterWindow", u"+", None))

        self.groupBox.setTitle(QCoreApplication.translate("FilterWindow", u"HSV", None))
        self.label_2.setText(QCoreApplication.translate("FilterWindow", u"max H", None))
        self.label_4.setText(QCoreApplication.translate("FilterWindow", u"max S", None))
        self.label_5.setText(QCoreApplication.translate("FilterWindow", u"min V", None))
        self.lbmaxV.setText(QCoreApplication.translate("FilterWindow", u"255", None))
        self.label_3.setText(QCoreApplication.translate("FilterWindow", u"min S", None))
        self.lbminS.setText(QCoreApplication.translate("FilterWindow", u"0", None))
        self.label_6.setText(QCoreApplication.translate("FilterWindow", u"max V", None))
        self.lbminV.setText(QCoreApplication.translate("FilterWindow", u"0", None))
        self.lbmaxS.setText(QCoreApplication.translate("FilterWindow", u"255", None))
        self.label.setText(QCoreApplication.translate("FilterWindow", u"min H", None))
        self.lbmaxH.setText(QCoreApplication.translate("FilterWindow", u"150", None))
        self.lbminH.setText(QCoreApplication.translate("FilterWindow", u"100", None))
        self.groupBox_2.setTitle(QCoreApplication.translate("FilterWindow", u"Threshold", None))
        self.lbThreshold.setText(QCoreApplication.translate("FilterWindow", u"100", None))
        self.groupBox_3.setTitle(QCoreApplication.translate("FilterWindow", u"Blur", None))
        self.lbBlurSize.setText(QCoreApplication.translate("FilterWindow", u"1", None))
        self.cbInvert.setText(QCoreApplication.translate("FilterWindow", u"Invert", None))
        self.lbOriginImage.setText("")
        self.lbProcessImage.setText("")
    # retranslateUi

