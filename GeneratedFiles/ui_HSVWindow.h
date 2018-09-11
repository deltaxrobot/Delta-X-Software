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
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_HSVWindow
{
public:
    QSlider *hsminH;
    QSlider *hsmaxH;
    QSlider *hsminS;
    QSlider *hsmaxS;
    QSlider *hsminV;
    QSlider *hsmaxV;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *lbminH;
    QLabel *lbmaxH;
    QLabel *lbminS;
    QLabel *lbmaxS;
    QLabel *lbminV;
    QLabel *lbmaxV;

    void setupUi(QDialog *HSVWindow)
    {
        if (HSVWindow->objectName().isEmpty())
            HSVWindow->setObjectName(QStringLiteral("HSVWindow"));
        HSVWindow->resize(450, 309);
        hsminH = new QSlider(HSVWindow);
        hsminH->setObjectName(QStringLiteral("hsminH"));
        hsminH->setGeometry(QRect(80, 50, 311, 22));
        hsminH->setMaximum(255);
        hsminH->setValue(100);
        hsminH->setOrientation(Qt::Horizontal);
        hsmaxH = new QSlider(HSVWindow);
        hsmaxH->setObjectName(QStringLiteral("hsmaxH"));
        hsmaxH->setGeometry(QRect(80, 90, 311, 22));
        hsmaxH->setMaximum(255);
        hsmaxH->setValue(150);
        hsmaxH->setOrientation(Qt::Horizontal);
        hsminS = new QSlider(HSVWindow);
        hsminS->setObjectName(QStringLiteral("hsminS"));
        hsminS->setGeometry(QRect(80, 130, 311, 22));
        hsminS->setMaximum(255);
        hsminS->setValue(100);
        hsminS->setOrientation(Qt::Horizontal);
        hsmaxS = new QSlider(HSVWindow);
        hsmaxS->setObjectName(QStringLiteral("hsmaxS"));
        hsmaxS->setGeometry(QRect(80, 170, 311, 22));
        hsmaxS->setMaximum(255);
        hsmaxS->setValue(150);
        hsmaxS->setOrientation(Qt::Horizontal);
        hsminV = new QSlider(HSVWindow);
        hsminV->setObjectName(QStringLiteral("hsminV"));
        hsminV->setGeometry(QRect(80, 210, 311, 22));
        hsminV->setMaximum(255);
        hsminV->setValue(100);
        hsminV->setOrientation(Qt::Horizontal);
        hsmaxV = new QSlider(HSVWindow);
        hsmaxV->setObjectName(QStringLiteral("hsmaxV"));
        hsmaxV->setGeometry(QRect(80, 250, 311, 22));
        hsmaxV->setMaximum(255);
        hsmaxV->setValue(150);
        hsmaxV->setOrientation(Qt::Horizontal);
        label = new QLabel(HSVWindow);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 50, 55, 16));
        label_2 = new QLabel(HSVWindow);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 90, 55, 16));
        label_3 = new QLabel(HSVWindow);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 130, 55, 16));
        label_4 = new QLabel(HSVWindow);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 170, 55, 16));
        label_5 = new QLabel(HSVWindow);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 210, 55, 16));
        label_6 = new QLabel(HSVWindow);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 250, 55, 16));
        lbminH = new QLabel(HSVWindow);
        lbminH->setObjectName(QStringLiteral("lbminH"));
        lbminH->setGeometry(QRect(410, 50, 55, 16));
        lbmaxH = new QLabel(HSVWindow);
        lbmaxH->setObjectName(QStringLiteral("lbmaxH"));
        lbmaxH->setGeometry(QRect(410, 90, 55, 16));
        lbminS = new QLabel(HSVWindow);
        lbminS->setObjectName(QStringLiteral("lbminS"));
        lbminS->setGeometry(QRect(410, 130, 55, 16));
        lbmaxS = new QLabel(HSVWindow);
        lbmaxS->setObjectName(QStringLiteral("lbmaxS"));
        lbmaxS->setGeometry(QRect(410, 170, 55, 16));
        lbminV = new QLabel(HSVWindow);
        lbminV->setObjectName(QStringLiteral("lbminV"));
        lbminV->setGeometry(QRect(410, 210, 55, 16));
        lbmaxV = new QLabel(HSVWindow);
        lbmaxV->setObjectName(QStringLiteral("lbmaxV"));
        lbmaxV->setGeometry(QRect(410, 250, 55, 16));

        retranslateUi(HSVWindow);

        QMetaObject::connectSlotsByName(HSVWindow);
    } // setupUi

    void retranslateUi(QDialog *HSVWindow)
    {
        HSVWindow->setWindowTitle(QApplication::translate("HSVWindow", "HSV Panel", Q_NULLPTR));
        label->setText(QApplication::translate("HSVWindow", "min H", Q_NULLPTR));
        label_2->setText(QApplication::translate("HSVWindow", "max H", Q_NULLPTR));
        label_3->setText(QApplication::translate("HSVWindow", "min S", Q_NULLPTR));
        label_4->setText(QApplication::translate("HSVWindow", "max S", Q_NULLPTR));
        label_5->setText(QApplication::translate("HSVWindow", "min V", Q_NULLPTR));
        label_6->setText(QApplication::translate("HSVWindow", "max V", Q_NULLPTR));
        lbminH->setText(QApplication::translate("HSVWindow", "100", Q_NULLPTR));
        lbmaxH->setText(QApplication::translate("HSVWindow", "150", Q_NULLPTR));
        lbminS->setText(QApplication::translate("HSVWindow", "100", Q_NULLPTR));
        lbmaxS->setText(QApplication::translate("HSVWindow", "150", Q_NULLPTR));
        lbminV->setText(QApplication::translate("HSVWindow", "100", Q_NULLPTR));
        lbmaxV->setText(QApplication::translate("HSVWindow", "150", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class HSVWindow: public Ui_HSVWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSVWINDOW_H
