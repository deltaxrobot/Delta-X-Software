/********************************************************************************
** Form generated from reading UI file 'FilterWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERWINDOW_H
#define UI_FILTERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FilterWindow
{
public:
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_7;
    QComboBox *cbObjectType;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_4;
    QSlider *hsminH;
    QSlider *hsmaxS;
    QLabel *label_5;
    QSlider *hsminS;
    QSlider *hsmaxV;
    QLabel *lbmaxV;
    QLabel *label_3;
    QLabel *lbminS;
    QLabel *label_6;
    QLabel *lbminV;
    QLabel *lbmaxS;
    QSlider *hsminV;
    QLabel *label;
    QSlider *hsmaxH;
    QLabel *lbmaxH;
    QLabel *lbminH;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *lbThreshold;
    QSlider *hsThreshold;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QLabel *lbBlurSize;
    QSlider *hsBlurSize;
    QSpacerItem *verticalSpacer;
    QFrame *frame1;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *cbInvert;
    QLabel *lbOriginImage;
    QLabel *lbProcessImage;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QDialog *FilterWindow)
    {
        if (FilterWindow->objectName().isEmpty())
            FilterWindow->setObjectName(QString::fromUtf8("FilterWindow"));
        FilterWindow->resize(838, 565);
        horizontalLayout = new QHBoxLayout(FilterWindow);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(FilterWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMaximumSize(QSize(400, 16777215));
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(20);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setMinimumSize(QSize(0, 50));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_7 = new QLabel(frame_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_2->addWidget(label_7);

        cbObjectType = new QComboBox(frame_2);
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
        cbObjectType->addItem(QString());
        cbObjectType->setObjectName(QString::fromUtf8("cbObjectType"));

        horizontalLayout_2->addWidget(cbObjectType);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        verticalLayout->addWidget(frame_2);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setBold(false);
        groupBox->setFont(font);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 2, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        hsminH = new QSlider(groupBox);
        hsminH->setObjectName(QString::fromUtf8("hsminH"));
        hsminH->setMaximum(255);
        hsminH->setValue(100);
        hsminH->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hsminH, 0, 1, 1, 1);

        hsmaxS = new QSlider(groupBox);
        hsmaxS->setObjectName(QString::fromUtf8("hsmaxS"));
        hsmaxS->setMaximum(255);
        hsmaxS->setValue(255);
        hsmaxS->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hsmaxS, 4, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 5, 0, 1, 1);

        hsminS = new QSlider(groupBox);
        hsminS->setObjectName(QString::fromUtf8("hsminS"));
        hsminS->setMaximum(255);
        hsminS->setValue(0);
        hsminS->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hsminS, 3, 1, 1, 1);

        hsmaxV = new QSlider(groupBox);
        hsmaxV->setObjectName(QString::fromUtf8("hsmaxV"));
        hsmaxV->setMaximum(255);
        hsmaxV->setValue(255);
        hsmaxV->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hsmaxV, 6, 1, 1, 1);

        lbmaxV = new QLabel(groupBox);
        lbmaxV->setObjectName(QString::fromUtf8("lbmaxV"));

        gridLayout->addWidget(lbmaxV, 6, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        lbminS = new QLabel(groupBox);
        lbminS->setObjectName(QString::fromUtf8("lbminS"));

        gridLayout->addWidget(lbminS, 3, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 6, 0, 1, 1);

        lbminV = new QLabel(groupBox);
        lbminV->setObjectName(QString::fromUtf8("lbminV"));

        gridLayout->addWidget(lbminV, 5, 2, 1, 1);

        lbmaxS = new QLabel(groupBox);
        lbmaxS->setObjectName(QString::fromUtf8("lbmaxS"));

        gridLayout->addWidget(lbmaxS, 4, 2, 1, 1);

        hsminV = new QSlider(groupBox);
        hsminV->setObjectName(QString::fromUtf8("hsminV"));
        hsminV->setMaximum(255);
        hsminV->setValue(0);
        hsminV->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hsminV, 5, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        hsmaxH = new QSlider(groupBox);
        hsmaxH->setObjectName(QString::fromUtf8("hsmaxH"));
        hsmaxH->setMaximum(255);
        hsmaxH->setValue(150);
        hsmaxH->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(hsmaxH, 2, 1, 1, 1);

        lbmaxH = new QLabel(groupBox);
        lbmaxH->setObjectName(QString::fromUtf8("lbmaxH"));

        gridLayout->addWidget(lbmaxH, 2, 2, 1, 1);

        lbminH = new QLabel(groupBox);
        lbminH->setObjectName(QString::fromUtf8("lbminH"));

        gridLayout->addWidget(lbminH, 0, 2, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setFont(font);
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        lbThreshold = new QLabel(groupBox_2);
        lbThreshold->setObjectName(QString::fromUtf8("lbThreshold"));

        gridLayout_2->addWidget(lbThreshold, 0, 1, 1, 1);

        hsThreshold = new QSlider(groupBox_2);
        hsThreshold->setObjectName(QString::fromUtf8("hsThreshold"));
        hsThreshold->setMaximum(255);
        hsThreshold->setValue(150);
        hsThreshold->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(hsThreshold, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setFont(font);
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        lbBlurSize = new QLabel(groupBox_3);
        lbBlurSize->setObjectName(QString::fromUtf8("lbBlurSize"));

        gridLayout_3->addWidget(lbBlurSize, 0, 1, 1, 1);

        hsBlurSize = new QSlider(groupBox_3);
        hsBlurSize->setObjectName(QString::fromUtf8("hsBlurSize"));
        hsBlurSize->setMinimum(1);
        hsBlurSize->setMaximum(51);
        hsBlurSize->setSingleStep(2);
        hsBlurSize->setValue(1);
        hsBlurSize->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(hsBlurSize, 0, 0, 1, 1);


        verticalLayout->addWidget(groupBox_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addWidget(frame);

        frame1 = new QFrame(FilterWindow);
        frame1->setObjectName(QString::fromUtf8("frame1"));
        verticalLayout_2 = new QVBoxLayout(frame1);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        cbInvert = new QCheckBox(frame1);
        cbInvert->setObjectName(QString::fromUtf8("cbInvert"));

        verticalLayout_2->addWidget(cbInvert);

        lbOriginImage = new QLabel(frame1);
        lbOriginImage->setObjectName(QString::fromUtf8("lbOriginImage"));
        lbOriginImage->setMinimumSize(QSize(320, 240));
        lbOriginImage->setMaximumSize(QSize(400, 300));
        lbOriginImage->setStyleSheet(QString::fromUtf8("background-color:rgb(226, 226, 226)"));
        lbOriginImage->setScaledContents(false);

        verticalLayout_2->addWidget(lbOriginImage);

        lbProcessImage = new QLabel(frame1);
        lbProcessImage->setObjectName(QString::fromUtf8("lbProcessImage"));
        lbProcessImage->setMinimumSize(QSize(320, 240));
        lbProcessImage->setMaximumSize(QSize(400, 300));
        lbProcessImage->setStyleSheet(QString::fromUtf8("background-color:rgb(226, 226, 226)"));
        lbProcessImage->setScaledContents(false);

        verticalLayout_2->addWidget(lbProcessImage);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addWidget(frame1);


        retranslateUi(FilterWindow);

        QMetaObject::connectSlotsByName(FilterWindow);
    } // setupUi

    void retranslateUi(QDialog *FilterWindow)
    {
        FilterWindow->setWindowTitle(QCoreApplication::translate("FilterWindow", "Filter Window", nullptr));
        label_7->setText(QCoreApplication::translate("FilterWindow", "Object Type", nullptr));
        cbObjectType->setItemText(0, QCoreApplication::translate("FilterWindow", "0", nullptr));
        cbObjectType->setItemText(1, QCoreApplication::translate("FilterWindow", "1", nullptr));
        cbObjectType->setItemText(2, QCoreApplication::translate("FilterWindow", "2", nullptr));
        cbObjectType->setItemText(3, QCoreApplication::translate("FilterWindow", "3", nullptr));
        cbObjectType->setItemText(4, QCoreApplication::translate("FilterWindow", "4", nullptr));
        cbObjectType->setItemText(5, QCoreApplication::translate("FilterWindow", "5", nullptr));
        cbObjectType->setItemText(6, QCoreApplication::translate("FilterWindow", "6", nullptr));
        cbObjectType->setItemText(7, QCoreApplication::translate("FilterWindow", "7", nullptr));
        cbObjectType->setItemText(8, QCoreApplication::translate("FilterWindow", "8", nullptr));
        cbObjectType->setItemText(9, QCoreApplication::translate("FilterWindow", "9", nullptr));
        cbObjectType->setItemText(10, QCoreApplication::translate("FilterWindow", "10", nullptr));
        cbObjectType->setItemText(11, QCoreApplication::translate("FilterWindow", "11", nullptr));
        cbObjectType->setItemText(12, QCoreApplication::translate("FilterWindow", "12", nullptr));
        cbObjectType->setItemText(13, QCoreApplication::translate("FilterWindow", "13", nullptr));
        cbObjectType->setItemText(14, QCoreApplication::translate("FilterWindow", "14", nullptr));
        cbObjectType->setItemText(15, QCoreApplication::translate("FilterWindow", "15", nullptr));
        cbObjectType->setItemText(16, QCoreApplication::translate("FilterWindow", "16", nullptr));
        cbObjectType->setItemText(17, QCoreApplication::translate("FilterWindow", "17", nullptr));
        cbObjectType->setItemText(18, QCoreApplication::translate("FilterWindow", "18", nullptr));
        cbObjectType->setItemText(19, QCoreApplication::translate("FilterWindow", "19", nullptr));
        cbObjectType->setItemText(20, QCoreApplication::translate("FilterWindow", "20", nullptr));
        cbObjectType->setItemText(21, QCoreApplication::translate("FilterWindow", "21", nullptr));
        cbObjectType->setItemText(22, QCoreApplication::translate("FilterWindow", "22", nullptr));
        cbObjectType->setItemText(23, QCoreApplication::translate("FilterWindow", "23", nullptr));
        cbObjectType->setItemText(24, QCoreApplication::translate("FilterWindow", "24", nullptr));
        cbObjectType->setItemText(25, QCoreApplication::translate("FilterWindow", "25", nullptr));
        cbObjectType->setItemText(26, QCoreApplication::translate("FilterWindow", "26", nullptr));
        cbObjectType->setItemText(27, QCoreApplication::translate("FilterWindow", "27", nullptr));
        cbObjectType->setItemText(28, QCoreApplication::translate("FilterWindow", "28", nullptr));
        cbObjectType->setItemText(29, QCoreApplication::translate("FilterWindow", "29", nullptr));
        cbObjectType->setItemText(30, QCoreApplication::translate("FilterWindow", "+", nullptr));

        groupBox->setTitle(QCoreApplication::translate("FilterWindow", "HSV", nullptr));
        label_2->setText(QCoreApplication::translate("FilterWindow", "max H", nullptr));
        label_4->setText(QCoreApplication::translate("FilterWindow", "max S", nullptr));
        label_5->setText(QCoreApplication::translate("FilterWindow", "min V", nullptr));
        lbmaxV->setText(QCoreApplication::translate("FilterWindow", "255", nullptr));
        label_3->setText(QCoreApplication::translate("FilterWindow", "min S", nullptr));
        lbminS->setText(QCoreApplication::translate("FilterWindow", "0", nullptr));
        label_6->setText(QCoreApplication::translate("FilterWindow", "max V", nullptr));
        lbminV->setText(QCoreApplication::translate("FilterWindow", "0", nullptr));
        lbmaxS->setText(QCoreApplication::translate("FilterWindow", "255", nullptr));
        label->setText(QCoreApplication::translate("FilterWindow", "min H", nullptr));
        lbmaxH->setText(QCoreApplication::translate("FilterWindow", "150", nullptr));
        lbminH->setText(QCoreApplication::translate("FilterWindow", "100", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FilterWindow", "Threshold", nullptr));
        lbThreshold->setText(QCoreApplication::translate("FilterWindow", "100", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("FilterWindow", "Blur", nullptr));
        lbBlurSize->setText(QCoreApplication::translate("FilterWindow", "1", nullptr));
        cbInvert->setText(QCoreApplication::translate("FilterWindow", "Invert", nullptr));
        lbOriginImage->setText(QString());
        lbProcessImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FilterWindow: public Ui_FilterWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERWINDOW_H
