#include "IndustrialCameraPlugin.h"

IndustrialCameraPlugin::~IndustrialCameraPlugin()
{
    // Proper cleanup
    if (pluginForm) {
        delete pluginForm;
        pluginForm = nullptr;
    }
}

QWidget *IndustrialCameraPlugin::GetUI()
{
    // Prevent memory leak - only create once
    if (!pluginForm) {
        pluginForm = new Form();
        qRegisterMetaType< cv::Mat >("cv::Mat");
        connect(pluginForm, SIGNAL(EmitEventFromUI(QString)), this, SLOT(TranferEmit(QString)));
        connect(pluginForm->CameraReaderWork, &CameraReader::CapturedImage, this, &IndustrialCameraPlugin::CapturedImage);
        connect(pluginForm->CameraReaderWork, &CameraReader::StartedCapture, this, &IndustrialCameraPlugin::StartedCapture);
        connect(this, &IndustrialCameraPlugin::RequestCapture, pluginForm->CameraReaderWork, &CameraReader::ShotImage);
        connect(this, &IndustrialCameraPlugin::RequestConnect, pluginForm->CameraReaderWork, &CameraReader::ConnectCamera);
    }
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
    if (pluginForm && setting) {
        pluginForm->LoadSettings(setting);
    }
}

void IndustrialCameraPlugin::SaveSettings(QSettings *setting)
{
    if (pluginForm && setting) {
        pluginForm->SaveSettings(setting);
    }
}

void IndustrialCameraPlugin::ProcessCommand(QString cmd)
{
    if (pluginForm) {
        pluginForm->GetMessageFromOtherModule(cmd);
    }
}

void IndustrialCameraPlugin::TranferEmit(QString msg)
{
//    emit EmitCommand(msg);
}
