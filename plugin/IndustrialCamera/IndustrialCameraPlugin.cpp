#include "IndustrialCameraPlugin.h"

IndustrialCameraPlugin::~IndustrialCameraPlugin()
{
}

QWidget *IndustrialCameraPlugin::GetUI()
{
    pluginForm = new Form();
    qRegisterMetaType< cv::Mat >("cv::Mat");
    connect(pluginForm, SIGNAL(EmitEventFromUI(QString)), this, SLOT(TranferEmit(QString)));
    connect(pluginForm->CameraReaderWork, &CameraReader::CapturedImage, this, &IndustrialCameraPlugin::CapturedImage);
    connect(pluginForm->CameraReaderWork, &CameraReader::StartedCapture, this, &IndustrialCameraPlugin::StartedCapture);
//    connect(this, &IndustrialCameraPlugin::RequestCapture, pluginForm, &Form::RequestImage);
    connect(this, &IndustrialCameraPlugin::RequestCapture, pluginForm->CameraReaderWork, &CameraReader::ShotImage);
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
