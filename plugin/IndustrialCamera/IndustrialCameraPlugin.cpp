#include "IndustrialCameraPlugin.h"

IndustrialCameraPlugin::~IndustrialCameraPlugin()
{
}

QWidget *IndustrialCameraPlugin::GetUI()
{
    pluginForm = new Form();
    qRegisterMetaType< cv::Mat >("cv::Mat");
    connect(pluginForm, SIGNAL(EmitEventFromUI(QString)), this, SLOT(TranferEmit(QString)));
    connect(pluginForm->CameraProcessorThread, SIGNAL(CapturedImage(cv::Mat)), this, SLOT(GetCaptureImageSignal(cv::Mat)));

    return pluginForm;
}

QString IndustrialCameraPlugin::GetName()
{
    return pluginName;
}

QString IndustrialCameraPlugin::GetTitle()
{
    return pluginTitle;
}

void IndustrialCameraPlugin::LoadSettings(QSettings *setting)
{
    pluginForm->LoadSettings(setting);
}

void IndustrialCameraPlugin::SaveSettings(QSettings *setting)
{
    pluginForm->SaveSettings(setting);
}

void IndustrialCameraPlugin::ProcessCommand(QString cmd)
{
    pluginForm->GetMessageFromOtherModule(cmd);
}

void IndustrialCameraPlugin::TranferEmit(QString msg)
{
//    emit EmitCommand(msg);
}

void IndustrialCameraPlugin::GetCaptureImageSignal(cv::Mat mat)
{
    emit CapturedImage(mat);
}
