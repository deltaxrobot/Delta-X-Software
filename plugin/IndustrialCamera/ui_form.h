/********************************************************************************
** Form generated from reading UI file 'form.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORM_H
#define UI_FORM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pbRefresh;
    QLabel *label_2;
    QComboBox *cbCameraList;
    QLabel *lbCameraName;
    QLabel *lbWidthUnit;
    QLineEdit *leImageWidth;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QCheckBox *cbStream;
    QPushButton *pbConnectCamera;
    QLabel *lbWidth;
    QLineEdit *leCameraName;
    QLineEdit *leStreamAddress;
    QCheckBox *cbEnoughResize;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QPushButton *pbShotImage;
    QPushButton *pbShotVideo;
    QLabel *label_13;
    QLineEdit *leInterval;
    QLabel *label_14;
    QFrame *frame_3;
    QHBoxLayout *horizontalLayout_8;
    QFrame *fImageCounter;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *tbResetImageCounter;
    QLabel *label_12;
    QLabel *lbImageCounter;
    QFrame *fResolution;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_17;
    QLabel *lbResolution;
    QFrame *fResolution_2;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_18;
    QLabel *lbDisplayRatio;
    QFrame *fResolution_3;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_28;
    QLabel *lbFPS;
    QSpacerItem *horizontalSpacer_2;
    QLabel *lbCameraDisplay;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLabel *label_10;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label;
    QLabel *label_5;
    QLineEdit *leBalanceRatioBlue;
    QLabel *label_7;
    QComboBox *cbTriggerSource;
    QLineEdit *leExposureTime;
    QLineEdit *leGain;
    QLineEdit *leGamma;
    QComboBox *cbBalanceWhite;
    QLineEdit *leBalanceRatioRed;
    QLineEdit *leBalanceRatioGreen;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(502, 607);
        Form->setStyleSheet(QString::fromUtf8("QWidget#Form\n"
"{\n"
"	\n"
"	background-color: rgb(30, 30, 32);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	\n"
"	color: rgb(223, 223, 223);\n"
"}"));
        verticalLayout = new QVBoxLayout(Form);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea = new QScrollArea(Form);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 474, 2000));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        scrollAreaWidgetContents->setMinimumSize(QSize(100, 2000));
        scrollAreaWidgetContents->setStyleSheet(QString::fromUtf8("QWidget#scrollAreaWidgetContents\n"
"{\n"
"	\n"
"	background-color: rgb(38, 38, 41);\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbRefresh = new QPushButton(scrollAreaWidgetContents);
        pbRefresh->setObjectName(QString::fromUtf8("pbRefresh"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icon/icons8_replay_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbRefresh->setIcon(icon);

        gridLayout->addWidget(pbRefresh, 1, 3, 1, 1);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        cbCameraList = new QComboBox(scrollAreaWidgetContents);
        cbCameraList->setObjectName(QString::fromUtf8("cbCameraList"));
        cbCameraList->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(cbCameraList, 1, 2, 1, 1);

        lbCameraName = new QLabel(scrollAreaWidgetContents);
        lbCameraName->setObjectName(QString::fromUtf8("lbCameraName"));
        lbCameraName->setEnabled(false);

        gridLayout->addWidget(lbCameraName, 2, 0, 1, 1);

        lbWidthUnit = new QLabel(scrollAreaWidgetContents);
        lbWidthUnit->setObjectName(QString::fromUtf8("lbWidthUnit"));
        lbWidthUnit->setEnabled(false);

        gridLayout->addWidget(lbWidthUnit, 7, 3, 1, 1);

        leImageWidth = new QLineEdit(scrollAreaWidgetContents);
        leImageWidth->setObjectName(QString::fromUtf8("leImageWidth"));
        leImageWidth->setEnabled(false);
        leImageWidth->setMaximumSize(QSize(100, 16777215));
        leImageWidth->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(leImageWidth, 7, 2, 1, 1);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);

        cbStream = new QCheckBox(scrollAreaWidgetContents);
        cbStream->setObjectName(QString::fromUtf8("cbStream"));
        cbStream->setEnabled(false);

        gridLayout->addWidget(cbStream, 3, 0, 1, 1);

        pbConnectCamera = new QPushButton(scrollAreaWidgetContents);
        pbConnectCamera->setObjectName(QString::fromUtf8("pbConnectCamera"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pbConnectCamera->sizePolicy().hasHeightForWidth());
        pbConnectCamera->setSizePolicy(sizePolicy1);
        QFont font;
        font.setBold(true);
        pbConnectCamera->setFont(font);
        pbConnectCamera->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(pbConnectCamera, 1, 0, 1, 1);

        lbWidth = new QLabel(scrollAreaWidgetContents);
        lbWidth->setObjectName(QString::fromUtf8("lbWidth"));
        lbWidth->setEnabled(false);

        gridLayout->addWidget(lbWidth, 7, 0, 1, 1);

        leCameraName = new QLineEdit(scrollAreaWidgetContents);
        leCameraName->setObjectName(QString::fromUtf8("leCameraName"));
        leCameraName->setEnabled(false);

        gridLayout->addWidget(leCameraName, 2, 2, 1, 1);

        leStreamAddress = new QLineEdit(scrollAreaWidgetContents);
        leStreamAddress->setObjectName(QString::fromUtf8("leStreamAddress"));
        leStreamAddress->setEnabled(false);

        gridLayout->addWidget(leStreamAddress, 3, 2, 1, 1);

        cbEnoughResize = new QCheckBox(scrollAreaWidgetContents);
        cbEnoughResize->setObjectName(QString::fromUtf8("cbEnoughResize"));

        gridLayout->addWidget(cbEnoughResize, 7, 4, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 100));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pbShotImage = new QPushButton(frame);
        pbShotImage->setObjectName(QString::fromUtf8("pbShotImage"));
        pbShotImage->setEnabled(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/icon/icons8_google_images_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        pbShotImage->setIcon(icon1);

        gridLayout_3->addWidget(pbShotImage, 0, 0, 1, 1);

        pbShotVideo = new QPushButton(frame);
        pbShotVideo->setObjectName(QString::fromUtf8("pbShotVideo"));
        pbShotVideo->setEnabled(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/icon/icons8_play_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/icon/icons8_pause_48px.png"), QSize(), QIcon::Normal, QIcon::On);
        pbShotVideo->setIcon(icon2);
        pbShotVideo->setCheckable(true);

        gridLayout_3->addWidget(pbShotVideo, 1, 0, 1, 1);

        label_13 = new QLabel(frame);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_13, 1, 1, 1, 1);

        leInterval = new QLineEdit(frame);
        leInterval->setObjectName(QString::fromUtf8("leInterval"));
        leInterval->setMaximumSize(QSize(100, 16777215));
        leInterval->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(leInterval, 1, 2, 1, 1);

        label_14 = new QLabel(frame);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_3->addWidget(label_14, 1, 3, 1, 1);


        verticalLayout_2->addWidget(frame);

        frame_3 = new QFrame(scrollAreaWidgetContents);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setStyleSheet(QString::fromUtf8("QFrame\n"
"{\n"
"	\n"
"	background-color: rgb(51, 51, 55);\n"
"}"));
        horizontalLayout_8 = new QHBoxLayout(frame_3);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setContentsMargins(0, 0, 0, 0);
        fImageCounter = new QFrame(frame_3);
        fImageCounter->setObjectName(QString::fromUtf8("fImageCounter"));
        fImageCounter->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_5 = new QHBoxLayout(fImageCounter);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(10, 0, 10, 0);
        tbResetImageCounter = new QToolButton(fImageCounter);
        tbResetImageCounter->setObjectName(QString::fromUtf8("tbResetImageCounter"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/icon/icons8_reset_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbResetImageCounter->setIcon(icon3);

        horizontalLayout_5->addWidget(tbResetImageCounter);

        label_12 = new QLabel(fImageCounter);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_5->addWidget(label_12);

        lbImageCounter = new QLabel(fImageCounter);
        lbImageCounter->setObjectName(QString::fromUtf8("lbImageCounter"));
        lbImageCounter->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_5->addWidget(lbImageCounter);


        horizontalLayout_8->addWidget(fImageCounter);

        fResolution = new QFrame(frame_3);
        fResolution->setObjectName(QString::fromUtf8("fResolution"));
        fResolution->setMinimumSize(QSize(0, 0));
        fResolution->setStyleSheet(QString::fromUtf8(""));
        fResolution->setFrameShape(QFrame::StyledPanel);
        fResolution->setFrameShadow(QFrame::Raised);
        horizontalLayout_7 = new QHBoxLayout(fResolution);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalLayout_7->setContentsMargins(10, 0, 10, 0);
        label_17 = new QLabel(fResolution);
        label_17->setObjectName(QString::fromUtf8("label_17"));

        horizontalLayout_7->addWidget(label_17);

        lbResolution = new QLabel(fResolution);
        lbResolution->setObjectName(QString::fromUtf8("lbResolution"));

        horizontalLayout_7->addWidget(lbResolution);


        horizontalLayout_8->addWidget(fResolution);

        fResolution_2 = new QFrame(frame_3);
        fResolution_2->setObjectName(QString::fromUtf8("fResolution_2"));
        fResolution_2->setMinimumSize(QSize(0, 0));
        fResolution_2->setStyleSheet(QString::fromUtf8(""));
        fResolution_2->setFrameShape(QFrame::StyledPanel);
        fResolution_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_9 = new QHBoxLayout(fResolution_2);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(10, 0, 10, 0);
        label_18 = new QLabel(fResolution_2);
        label_18->setObjectName(QString::fromUtf8("label_18"));

        horizontalLayout_9->addWidget(label_18);

        lbDisplayRatio = new QLabel(fResolution_2);
        lbDisplayRatio->setObjectName(QString::fromUtf8("lbDisplayRatio"));

        horizontalLayout_9->addWidget(lbDisplayRatio);


        horizontalLayout_8->addWidget(fResolution_2);

        fResolution_3 = new QFrame(frame_3);
        fResolution_3->setObjectName(QString::fromUtf8("fResolution_3"));
        fResolution_3->setMinimumSize(QSize(0, 0));
        fResolution_3->setStyleSheet(QString::fromUtf8(""));
        fResolution_3->setFrameShape(QFrame::StyledPanel);
        fResolution_3->setFrameShadow(QFrame::Raised);
        horizontalLayout_10 = new QHBoxLayout(fResolution_3);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(10, 0, 10, 0);
        label_28 = new QLabel(fResolution_3);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_10->addWidget(label_28);

        lbFPS = new QLabel(fResolution_3);
        lbFPS->setObjectName(QString::fromUtf8("lbFPS"));

        horizontalLayout_10->addWidget(lbFPS);


        horizontalLayout_8->addWidget(fResolution_3);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_2);


        verticalLayout_2->addWidget(frame_3);

        lbCameraDisplay = new QLabel(scrollAreaWidgetContents);
        lbCameraDisplay->setObjectName(QString::fromUtf8("lbCameraDisplay"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lbCameraDisplay->sizePolicy().hasHeightForWidth());
        lbCameraDisplay->setSizePolicy(sizePolicy2);
        lbCameraDisplay->setMinimumSize(QSize(0, 0));
        lbCameraDisplay->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lbCameraDisplay->setScaledContents(true);

        verticalLayout_2->addWidget(lbCameraDisplay);

        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(false);
        groupBox->setMinimumSize(QSize(0, 100));
        groupBox->setStyleSheet(QString::fromUtf8("QGroupBox::title\n"
"{\n"
"	\n"
"	color: rgb(231, 231, 231);\n"
"}"));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_2->addWidget(label_10, 9, 0, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_2->addWidget(label_8, 8, 0, 1, 1);

        label_9 = new QLabel(groupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_2->addWidget(label_9, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_2->addWidget(label_4, 2, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        leBalanceRatioBlue = new QLineEdit(groupBox);
        leBalanceRatioBlue->setObjectName(QString::fromUtf8("leBalanceRatioBlue"));
        leBalanceRatioBlue->setMaximumSize(QSize(100, 16777215));
        leBalanceRatioBlue->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(leBalanceRatioBlue, 8, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 5, 0, 1, 1);

        cbTriggerSource = new QComboBox(groupBox);
        cbTriggerSource->addItem(QString());
        cbTriggerSource->addItem(QString());
        cbTriggerSource->addItem(QString());
        cbTriggerSource->addItem(QString());
        cbTriggerSource->addItem(QString());
        cbTriggerSource->setObjectName(QString::fromUtf8("cbTriggerSource"));
        cbTriggerSource->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(cbTriggerSource, 9, 1, 1, 1);

        leExposureTime = new QLineEdit(groupBox);
        leExposureTime->setObjectName(QString::fromUtf8("leExposureTime"));
        leExposureTime->setMaximumSize(QSize(100, 16777215));
        leExposureTime->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(leExposureTime, 0, 1, 1, 1);

        leGain = new QLineEdit(groupBox);
        leGain->setObjectName(QString::fromUtf8("leGain"));
        leGain->setMaximumSize(QSize(100, 16777215));
        leGain->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(leGain, 1, 1, 1, 1);

        leGamma = new QLineEdit(groupBox);
        leGamma->setObjectName(QString::fromUtf8("leGamma"));
        leGamma->setMaximumSize(QSize(100, 16777215));
        leGamma->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(leGamma, 2, 1, 1, 1);

        cbBalanceWhite = new QComboBox(groupBox);
        cbBalanceWhite->addItem(QString());
        cbBalanceWhite->addItem(QString());
        cbBalanceWhite->setObjectName(QString::fromUtf8("cbBalanceWhite"));
        cbBalanceWhite->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(cbBalanceWhite, 3, 1, 1, 1);

        leBalanceRatioRed = new QLineEdit(groupBox);
        leBalanceRatioRed->setObjectName(QString::fromUtf8("leBalanceRatioRed"));
        leBalanceRatioRed->setMaximumSize(QSize(100, 16777215));
        leBalanceRatioRed->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(leBalanceRatioRed, 4, 1, 1, 1);

        leBalanceRatioGreen = new QLineEdit(groupBox);
        leBalanceRatioGreen->setObjectName(QString::fromUtf8("leBalanceRatioGreen"));
        leBalanceRatioGreen->setMaximumSize(QSize(100, 16777215));
        leBalanceRatioGreen->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(leBalanceRatioGreen, 5, 1, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        pbRefresh->setText(QString());
        label_2->setText(QCoreApplication::translate("Form", "Supported camera:", nullptr));
        lbCameraName->setText(QCoreApplication::translate("Form", "Camera Name", nullptr));
        lbWidthUnit->setText(QCoreApplication::translate("Form", "px", nullptr));
        leImageWidth->setText(QCoreApplication::translate("Form", "1920", nullptr));
        label_3->setText(QCoreApplication::translate("Form", "Basler, Hikrobot", nullptr));
        cbStream->setText(QCoreApplication::translate("Form", "Stream", nullptr));
        pbConnectCamera->setText(QCoreApplication::translate("Form", "Connect", nullptr));
        lbWidth->setText(QCoreApplication::translate("Form", "Width", nullptr));
        leCameraName->setText(QCoreApplication::translate("Form", "iCam", nullptr));
        leStreamAddress->setText(QCoreApplication::translate("Form", "192.168.50.1:8888", nullptr));
        cbEnoughResize->setText(QCoreApplication::translate("Form", "Resize", nullptr));
        pbShotImage->setText(QCoreApplication::translate("Form", "Single Shot", nullptr));
        pbShotVideo->setText(QCoreApplication::translate("Form", "Continious Shot", nullptr));
        label_13->setText(QCoreApplication::translate("Form", "Interval", nullptr));
        leInterval->setText(QCoreApplication::translate("Form", "500", nullptr));
        label_14->setText(QCoreApplication::translate("Form", "ms", nullptr));
        tbResetImageCounter->setText(QString());
        label_12->setText(QCoreApplication::translate("Form", "Images:", nullptr));
        lbImageCounter->setText(QCoreApplication::translate("Form", "0", nullptr));
        label_17->setText(QCoreApplication::translate("Form", "Resolution:", nullptr));
        lbResolution->setText(QCoreApplication::translate("Form", "0 x 0", nullptr));
        label_18->setText(QCoreApplication::translate("Form", "Display:", nullptr));
        lbDisplayRatio->setText(QCoreApplication::translate("Form", "50%", nullptr));
        label_28->setText(QCoreApplication::translate("Form", "FPS:", nullptr));
        lbFPS->setText(QCoreApplication::translate("Form", "0", nullptr));
        lbCameraDisplay->setText(QString());
        groupBox->setTitle(QCoreApplication::translate("Form", "Camera Setting", nullptr));
        label_10->setText(QCoreApplication::translate("Form", "Trigger Source", nullptr));
        label_6->setText(QCoreApplication::translate("Form", "Balance Ratio Red", nullptr));
        label_8->setText(QCoreApplication::translate("Form", "Balance Ratio Blue", nullptr));
        label_9->setText(QCoreApplication::translate("Form", "Gain", nullptr));
        label_4->setText(QCoreApplication::translate("Form", "Gamma", nullptr));
        label->setText(QCoreApplication::translate("Form", "Exposure Time", nullptr));
        label_5->setText(QCoreApplication::translate("Form", "Balance White", nullptr));
        leBalanceRatioBlue->setText(QCoreApplication::translate("Form", "0", nullptr));
        label_7->setText(QCoreApplication::translate("Form", "Balance Ratio Green", nullptr));
        cbTriggerSource->setItemText(0, QCoreApplication::translate("Form", "Software", nullptr));
        cbTriggerSource->setItemText(1, QCoreApplication::translate("Form", "Line 1", nullptr));
        cbTriggerSource->setItemText(2, QCoreApplication::translate("Form", "Line 2", nullptr));
        cbTriggerSource->setItemText(3, QCoreApplication::translate("Form", "Line 3", nullptr));
        cbTriggerSource->setItemText(4, QCoreApplication::translate("Form", "Line 4", nullptr));

        leExposureTime->setText(QCoreApplication::translate("Form", "0", nullptr));
        leGain->setText(QCoreApplication::translate("Form", "0", nullptr));
        leGamma->setText(QCoreApplication::translate("Form", "0", nullptr));
        cbBalanceWhite->setItemText(0, QCoreApplication::translate("Form", "Off", nullptr));
        cbBalanceWhite->setItemText(1, QCoreApplication::translate("Form", "Continuous", nullptr));

        leBalanceRatioRed->setText(QCoreApplication::translate("Form", "0", nullptr));
        leBalanceRatioGreen->setText(QCoreApplication::translate("Form", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORM_H
