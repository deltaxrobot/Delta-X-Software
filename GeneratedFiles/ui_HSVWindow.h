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
#include <QtWidgets/QSlider>

QT_BEGIN_NAMESPACE

class Ui_DlHSVPanel
{
public:
    QSlider *hsHmin;
    QSlider *hsHmax;
    QSlider *hsSmin;
    QSlider *hsSmax;
    QSlider *hsVmin;
    QSlider *hsVmax;

    void setupUi(QDialog *DlHSVPanel)
    {
        if (DlHSVPanel->objectName().isEmpty())
            DlHSVPanel->setObjectName(QStringLiteral("DlHSVPanel"));
        DlHSVPanel->resize(400, 300);
        hsHmin = new QSlider(DlHSVPanel);
        hsHmin->setObjectName(QStringLiteral("hsHmin"));
        hsHmin->setGeometry(QRect(20, 20, 351, 22));
        hsHmin->setOrientation(Qt::Horizontal);
        hsHmax = new QSlider(DlHSVPanel);
        hsHmax->setObjectName(QStringLiteral("hsHmax"));
        hsHmax->setGeometry(QRect(20, 50, 351, 22));
        hsHmax->setOrientation(Qt::Horizontal);
        hsSmin = new QSlider(DlHSVPanel);
        hsSmin->setObjectName(QStringLiteral("hsSmin"));
        hsSmin->setGeometry(QRect(20, 90, 351, 22));
        hsSmin->setOrientation(Qt::Horizontal);
        hsSmax = new QSlider(DlHSVPanel);
        hsSmax->setObjectName(QStringLiteral("hsSmax"));
        hsSmax->setGeometry(QRect(20, 120, 351, 22));
        hsSmax->setOrientation(Qt::Horizontal);
        hsVmin = new QSlider(DlHSVPanel);
        hsVmin->setObjectName(QStringLiteral("hsVmin"));
        hsVmin->setGeometry(QRect(20, 150, 351, 22));
        hsVmin->setOrientation(Qt::Horizontal);
        hsVmax = new QSlider(DlHSVPanel);
        hsVmax->setObjectName(QStringLiteral("hsVmax"));
        hsVmax->setGeometry(QRect(20, 180, 351, 22));
        hsVmax->setOrientation(Qt::Horizontal);

        retranslateUi(DlHSVPanel);

        QMetaObject::connectSlotsByName(DlHSVPanel);
    } // setupUi

    void retranslateUi(QDialog *DlHSVPanel)
    {
        DlHSVPanel->setWindowTitle(QApplication::translate("DlHSVPanel", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class DlHSVPanel: public Ui_DlHSVPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HSVWINDOW_H
