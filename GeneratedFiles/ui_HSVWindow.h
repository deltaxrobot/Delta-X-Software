/********************************************************************************
** Form generated from reading UI file 'HSVWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HSVWINDOW_H
#define UI_HSVWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_HSVWindow
{
public:
    QGroupBox *groupBox;
    QLabel *lbmaxV;
    QLabel *label_3;
    QSlider *hsmaxS;
    QSlider *hsmaxH;
    QLabel *lbminV;
    QLabel *lbmaxS;
    QLabel *label_4;
    QSlider *hsmaxV;
    QLabel *label_2;
    QLabel *lbmaxH;
    QLabel *lbminS;
    QSlider *hsminS;
    QSlider *hsminH;
    QSlider *hsminV;
    QLabel *label_6;
    QLabel *label_5;
    QLabel *label;
    QLabel *lbminH;
    QGroupBox *groupBox_2;
    QSlider *hsThreshold;
    QLabel *lbThreshold;
    QLabel *label_7;
    QCheckBox *cbInvert;
    QLabel *lbOriginImage;
    QLabel *lbProcessImage;

    void setupUi(QDialog *HSVWindow)
    {
        if (HSVWindow->objectName().isEmpty())
            HSVWindow->setObjectName(QStringLiteral("HSVWindow"));
        HSVWindow->resize(1401, 506);
        groupBox = new QGroupBox(HSVWindow);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 20, 511, 311));
        lbmaxV = new QLabel(groupBox);
        lbmaxV->setObjectName(QStringLiteral("lbmaxV"));
        lbmaxV->setGeometry(QRect(420, 240, 55, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 120, 55, 16));
        hsmaxS = new QSlider(groupBox);
        hsmaxS->setObjectName(QStringLiteral("hsmaxS"));
        hsmaxS->setGeometry(QRect(90, 160, 311, 22));
        hsmaxS->setMaximum(255);
        hsmaxS->setValue(255);
        hsmaxS->setOrientation(Qt::Horizontal);
        hsmaxH = new QSlider(groupBox);
        hsmaxH->setObjectName(QStringLiteral("hsmaxH"));
        hsmaxH->setGeometry(QRect(90, 80, 311, 22));
        hsmaxH->setMaximum(255);
        hsmaxH->setValue(150);
        hsmaxH->setOrientation(Qt::Horizontal);
        lbminV = new QLabel(groupBox);
        lbminV->setObjectName(QStringLiteral("lbminV"));
        lbminV->setGeometry(QRect(420, 200, 55, 16));
        lbmaxS = new QLabel(groupBox);
        lbmaxS->setObjectName(QStringLiteral("lbmaxS"));
        lbmaxS->setGeometry(QRect(420, 160, 55, 16));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(30, 160, 55, 16));
        hsmaxV = new QSlider(groupBox);
        hsmaxV->setObjectName(QStringLiteral("hsmaxV"));
        hsmaxV->setGeometry(QRect(90, 240, 311, 22));
        hsmaxV->setMaximum(255);
        hsmaxV->setValue(255);
        hsmaxV->setOrientation(Qt::Horizontal);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 80, 55, 16));
        lbmaxH = new QLabel(groupBox);
        lbmaxH->setObjectName(QStringLiteral("lbmaxH"));
        lbmaxH->setGeometry(QRect(420, 80, 55, 16));
        lbminS = new QLabel(groupBox);
        lbminS->setObjectName(QStringLiteral("lbminS"));
        lbminS->setGeometry(QRect(420, 120, 55, 16));
        hsminS = new QSlider(groupBox);
        hsminS->setObjectName(QStringLiteral("hsminS"));
        hsminS->setGeometry(QRect(90, 120, 311, 22));
        hsminS->setMaximum(255);
        hsminS->setValue(0);
        hsminS->setOrientation(Qt::Horizontal);
        hsminH = new QSlider(groupBox);
        hsminH->setObjectName(QStringLiteral("hsminH"));
        hsminH->setGeometry(QRect(90, 40, 311, 22));
        hsminH->setMaximum(255);
        hsminH->setValue(100);
        hsminH->setOrientation(Qt::Horizontal);
        hsminV = new QSlider(groupBox);
        hsminV->setObjectName(QStringLiteral("hsminV"));
        hsminV->setGeometry(QRect(90, 200, 311, 22));
        hsminV->setMaximum(255);
        hsminV->setValue(0);
        hsminV->setOrientation(Qt::Horizontal);
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(30, 240, 55, 16));
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(30, 200, 55, 16));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 40, 55, 16));
        lbminH = new QLabel(groupBox);
        lbminH->setObjectName(QStringLiteral("lbminH"));
        lbminH->setGeometry(QRect(420, 40, 55, 16));
        groupBox_2 = new QGroupBox(HSVWindow);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 350, 511, 101));
        hsThreshold = new QSlider(groupBox_2);
        hsThreshold->setObjectName(QStringLiteral("hsThreshold"));
        hsThreshold->setGeometry(QRect(90, 50, 311, 22));
        hsThreshold->setMaximum(255);
        hsThreshold->setValue(100);
        hsThreshold->setOrientation(Qt::Horizontal);
        lbThreshold = new QLabel(groupBox_2);
        lbThreshold->setObjectName(QStringLiteral("lbThreshold"));
        lbThreshold->setGeometry(QRect(420, 50, 55, 16));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(30, 50, 55, 16));
        cbInvert = new QCheckBox(HSVWindow);
        cbInvert->setObjectName(QStringLiteral("cbInvert"));
        cbInvert->setGeometry(QRect(450, 470, 81, 20));
        lbOriginImage = new QLabel(HSVWindow);
        lbOriginImage->setObjectName(QStringLiteral("lbOriginImage"));
        lbOriginImage->setGeometry(QRect(560, 30, 401, 321));
        lbOriginImage->setStyleSheet(QStringLiteral("background-color:rgb(226, 226, 226)"));
        lbProcessImage = new QLabel(HSVWindow);
        lbProcessImage->setObjectName(QStringLiteral("lbProcessImage"));
        lbProcessImage->setGeometry(QRect(980, 30, 401, 321));
        lbProcessImage->setStyleSheet(QStringLiteral("background-color:rgb(226, 226, 226)"));

        retranslateUi(HSVWindow);

        QMetaObject::connectSlotsByName(HSVWindow);
    } // setupUi

    void retranslateUi(QDialog *HSVWindow)
    {
        HSVWindow->setWindowTitle(QApplication::translate("HSVWindow", "HSV Panel", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("HSVWindow", "HSV", Q_NULLPTR));
        lbmaxV->setText(QApplication::translate("HSVWindow", "255", Q_NULLPTR));
        label_3->setText(QApplication::translate("HSVWindow", "min S", Q_NULLPTR));
        lbminV->setText(QApplication::translate("HSVWindow", "0", Q_NULLPTR));
        lbmaxS->setText(QApplication::translate("HSVWindow", "255", Q_NULLPTR));
        label_4->setText(QApplication::translate("HSVWindow", "max S", Q_NULLPTR));
        label_2->setText(QApplication::translate("HSVWindow", "max H", Q_NULLPTR));
        lbmaxH->setText(QApplication::translate("HSVWindow", "150", Q_NULLPTR));
        lbminS->setText(QApplication::translate("HSVWindow", "0", Q_NULLPTR));
        label_6->setText(QApplication::translate("HSVWindow", "max V", Q_NULLPTR));
        label_5->setText(QApplication::translate("HSVWindow", "min V", Q_NULLPTR));
        label->setText(QApplication::translate("HSVWindow", "min H", Q_NULLPTR));
        lbminH->setText(QApplication::translate("HSVWindow", "100", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("HSVWindow", "Threshold", Q_NULLPTR));
        lbThreshold->setText(QApplication::translate("HSVWindow", "100", Q_NULLPTR));
        label_7->setText(QApplication::translate("HSVWindow", "min", Q_NULLPTR));
        cbInvert->setText(QApplication::translate("HSVWindow", "Invert", Q_NULLPTR));
        lbOriginImage->setText(QString());
        lbProcessImage->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class HSVWindow: public Ui_HSVWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSVWINDOW_H
