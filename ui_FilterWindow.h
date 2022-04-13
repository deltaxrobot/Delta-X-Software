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
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        QFont font;
        font.setBold(false);
        font.setWeight(50);
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
        lbOriginImage->setScaledContents(true);

        verticalLayout_2->addWidget(lbOriginImage);

        lbProcessImage = new QLabel(frame1);
        lbProcessImage->setObjectName(QString::fromUtf8("lbProcessImage"));
        lbProcessImage->setMinimumSize(QSize(320, 240));
        lbProcessImage->setMaximumSize(QSize(400, 300));
        lbProcessImage->setStyleSheet(QString::fromUtf8("background-color:rgb(226, 226, 226)"));
        lbProcessImage->setScaledContents(true);

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
