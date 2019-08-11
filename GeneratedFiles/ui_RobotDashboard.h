/********************************************************************************
** Form generated from reading UI file 'RobotDashboard.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTDASHBOARD_H
#define UI_ROBOTDASHBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotDashboard
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pbTestButton;
    QLabel *lbTestLabel;
    QWidget *tab_2;
    QWidget *wgContainer;

    void setupUi(QWidget *RobotDashboard)
    {
        if (RobotDashboard->objectName().isEmpty())
            RobotDashboard->setObjectName(QStringLiteral("RobotDashboard"));
        RobotDashboard->resize(1335, 824);
        verticalLayout = new QVBoxLayout(RobotDashboard);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(RobotDashboard);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setStyleSheet(QStringLiteral("background-color: rgb(0, 170, 255);"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pbTestButton = new QPushButton(tab);
        pbTestButton->setObjectName(QStringLiteral("pbTestButton"));
        pbTestButton->setGeometry(QRect(70, 190, 93, 28));
        lbTestLabel = new QLabel(tab);
        lbTestLabel->setObjectName(QStringLiteral("lbTestLabel"));
        lbTestLabel->setGeometry(QRect(86, 252, 55, 16));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        wgContainer = new QWidget(tab_2);
        wgContainer->setObjectName(QStringLiteral("wgContainer"));
        wgContainer->setGeometry(QRect(16, 24, 1267, 737));
        wgContainer->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 255);"));
        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);


        retranslateUi(RobotDashboard);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(RobotDashboard);
    } // setupUi

    void retranslateUi(QWidget *RobotDashboard)
    {
        RobotDashboard->setWindowTitle(QApplication::translate("RobotDashboard", "RobotDashboard", Q_NULLPTR));
        pbTestButton->setText(QApplication::translate("RobotDashboard", "Button 1", Q_NULLPTR));
        lbTestLabel->setText(QApplication::translate("RobotDashboard", "label 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("RobotDashboard", "Tab 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("RobotDashboard", "Tab 2", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RobotDashboard: public Ui_RobotDashboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTDASHBOARD_H
